#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float eps=.003f){return std::abs(a-b)<eps;}
Simulation fixture(){
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0);
    s.arena=Arena{};s.arena.bounds={{-60,-1,-60},{60,8,60}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-60,-.4f,-60},{60,0,60}}};}
    s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={0,.85f,10};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void hit(Simulation &s,EntityId id,float damage,DamageKind kind=DamageKind::Physical,bool area=false){
    Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;e.damageKind=kind;e.areaDamage=area;s.queueRoot(e);s.drainEvents();
}
void acquire(Simulation &s,EntityId id){for(int i=0;i<600&&s.findEnemy(id)->host->frame<0;++i)tick(s);check(s.findEnemy(id)->host->frame>=0,"Host acquisition");}
void frame(Simulation &s,EntityId id,int target){for(int i=0;i<600&&s.findEnemy(id)->host->frame!=target;++i)tick(s);check(s.findEnemy(id)->host->frame==target,"source animation frame reached");}
void armor(){
    for(auto key:{monsterId(27),monsterId(204),monsterId(859)}) {
        auto s=fixture();auto id=s.spawnMonster(key,{0,.85f,0});const auto &p=*s.content->host(key);const float hp=s.findEnemy(id)->hp;
        hit(s,id,4);check(near(s.findEnemy(id)->hp,hp),"closed skull blocks physical");
        hit(s,id,4,DamageKind::Burning);check(near(s.findEnemy(id)->hp,hp-4),"status burning bypasses closed skull");
        hit(s,id,4,DamageKind::Flame);check(near(s.findEnemy(id)->hp,hp-4),"direct flame does not bypass skull");
        acquire(s,id);frame(s,id,p.openFrame-1);hit(s,id,4);check(near(s.findEnemy(id)->hp,hp-4),"opening anticipation remains armored");
        frame(s,id,p.openFrame);hit(s,id,4);check(near(s.findEnemy(id)->hp,hp-8),"Open event admits damage");
        frame(s,id,p.closeFrame);hit(s,id,4,DamageKind::Physical,true);check(near(s.findEnemy(id)->hp,hp-8),"Close event blocks even explosions");
    }
    for(auto key:{monsterId(27,1),monsterId(247)}){auto s=fixture();auto id=s.spawnMonster(key,{0,.85f,0});const float hp=s.findEnemy(id)->hp;hit(s,id,4);check(near(s.findEnemy(id)->hp,hp-4),"flesh variants always vulnerable");}
    auto s=fixture();auto id=s.spawnMonster(monsterId(27),{0,.85f,0});s.player.position.z=40;
    hit(s,id,3.2f);hit(s,id,3.2f);tick(s,2);check(s.findEnemy(id)->host->delay==1,"same-frame pellets aggregate before source rounding");
    hit(s,id,1000);tick(s,2);check(s.findEnemy(id)->host->delay>=9&&s.findEnemy(id)->host->shake,"delay capped and high blocked damage shakes shell");
    tick(s,160);check(s.findEnemy(id)->host->delay==0,"idle delay decays in seven-frame checks");
    for(auto key:{monsterId(27),monsterId(27,1),monsterId(204),monsterId(247),monsterId(859)}) {
        auto c=fixture();auto body=c.spawnMonster(key,c.player.position);c.godMode=false;tick(c,2);
        check((c.player.hp<100)==(key.type!=27),"only mobile/floating Hosts inflict contact damage");check(c.findEnemy(body)!=nullptr,"contact does not remove Host");
    }
}
void volleys(){
    for(auto key:{monsterId(27),monsterId(27,1),monsterId(204),monsterId(247),monsterId(859)}) {
        auto s=fixture();auto id=s.spawnMonster(key,{0,.85f,0});const auto &p=*s.content->host(key);
        acquire(s,id);frame(s,id,p.shootFrame-1);check(s.stats.projectiles==0,"no early volley");
        s.player.position={35,.85f,0};frame(s,id,p.shootFrame);check(s.projectiles.size()==p.volley.size(),"native3/5 physical volley count");
        std::vector<float> forward,side;for(auto c:p.volley){forward.push_back(c.x*p.speed);side.push_back(c.y*p.speed);}
        for(size_t i=0;i<p.volley.size();++i){const auto &b=s.projectiles[i];check(near(length(horizontal(b.velocity)),p.speed*std::hypot(p.volley[i].x,p.volley[i].y)),"native nonnormalized shot speeds");check(b.velocity.x>15,"live firing aim changes outside acquisition range");}
        frame(s,id,p.frames-1);tick(s,2);check(s.findEnemy(id)->host->frame==-1,"animation ends before reacquisition");
    }
    auto s=fixture();auto id=s.spawnMonster(monsterId(27),{0,.85f,0});acquire(s,id);s.limits.projectiles=2;tick(s,170);
    check(s.stats.projectiles==0&&s.findEnemy(id)->host->frame==24,"capacity holds full volley at event");s.limits.projectiles=3;tick(s,2);check(s.stats.projectiles==3,"capacity recovery emits exactly one volley");
    auto cover=fixture();id=cover.spawnMonster(monsterId(27),{0,.85f,0});cover.arena.walls={{{-10,-1,3},{10,8,3.5f}}};tick(cover,240);check(cover.stats.projectiles==0,"wall blocks acquisition");
    auto stun=fixture();id=stun.spawnMonster(monsterId(27),{0,.85f,0});acquire(stun,id);stun.findEnemy(id)->state=EnemyState::Stunned;stun.findEnemy(id)->stateTime=1;tick(stun,30);
    check(stun.stats.projectiles==0&&!stun.findEnemy(id)->host->exposed,"stun cancels cast and closes armor");
}
void movement(){
    auto s=fixture();s.player.position.z=50;auto id=s.spawnMonster(monsterId(204),{0,.85f,0});tick(s,2);check(near(s.findEnemy(id)->velocity.z,2.4f),"walking source force conversion");
    tick(s,2);check(near(s.findEnemy(id)->velocity.z,(.8f*.56f+.8f)*3),"walking source retention");
    s.player.position.z=10;acquire(s,id);const float speed=length(s.findEnemy(id)->velocity);tick(s,2);check(near(length(s.findEnemy(id)->velocity),speed*.5f),"attack coasts at half velocity");
    auto f=fixture();f.player.position.z=50;id=f.spawnMonster(monsterId(859),{0,.85f,0});tick(f,2);check(near(f.findEnemy(id)->velocity.x,1.65f)&&near(f.findEnemy(id)->velocity.z,1.65f),"Floast diagonal acceleration");
    f.arena.walls={{{2,-1,-60},{2.5f,8,60}}};bool bounced=false;for(int n=0;n<100;++n){tick(f);if(f.findEnemy(id)->host->momentum.x<0)bounced=true;check(f.findEnemy(id)->position.x<1.31f,"Floast respects solid wall");}check(bounced,"Floast reflects blocked axis");
}
void lifecycle(){
    auto s=fixture();auto id=s.spawnMonster(monsterId(27),{0,.85f,0});acquire(s,id);frame(s,id,12);
    const auto before=*s.findEnemy(id)->host;s.enterRoom(1);s.enterRoom(0);
    check(s.findEnemy(id)&&s.findEnemy(id)->host->frame==before.frame&&s.findEnemy(id)->host->exposed,"room round trip preserves open Host state");
    hit(s,id,1000);tick(s,90);check(s.stats.projectiles==0&&s.livingEnemies()==0,"death before Shoot cancels cast and releases room threat");
    auto c=fixture();id=c.spawnMonster(monsterId(27),{0,.85f,0});acquire(c,id);frame(c,id,60);tick(c,2);
    check(c.findEnemy(id)->host->cooldown==7&&c.findEnemy(id)->host->frame==-1,"stationary cooldown retained through attack");
    tick(c,84);check(c.findEnemy(id)->host->frame==-1,"seven idle checks required before new acquisition");
    tick(c,30);check(c.findEnemy(id)->host->frame>=0,"stationary reacquires after idle check countdown");
}
void configuration(){
    auto root=std::filesystem::temp_directory_path()/("dw-host-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    const auto file=root/"hosts.mechanics";std::ifstream in(file);std::string original((std::istreambuf_iterator<char>(in)),{});
    for(auto replacement:{std::pair{"61 9 24 55","61 24 9 55"},std::pair{"still 1","bad 1"},std::pair{".1 0 .7 .7",".1 0 1 .7"}}){auto text=original;const auto at=text.find(replacement.first);check(at!=text.npos,"mutation fixture");text.replace(at,std::string(replacement.first).size(),replacement.second);std::ofstream(file)<<text;bool rejected=false;try{MechanicsLibrary::load(root);}catch(...){rejected=true;}check(rejected,"invalid Host external config rejected");}
    std::ofstream(file)<<original;auto before=MechanicsLibrary::load(root);auto text=original;const auto at=text.find("61 9 24 55");text.replace(at,10,"61 8 24 55");std::ofstream(file)<<text;auto after=MechanicsLibrary::load(root);
    check(before->host(monsterId(27))->openFrame==9&&after->host(monsterId(27))->openFrame==8&&before->fingerprint()!=after->fingerprint(),"reload immutable and fingerprinted");std::filesystem::remove_all(root);
}
void placement(){
    const std::array<MonsterId,5> ids{monsterId(27),monsterId(27,1),monsterId(204),monsterId(247),monsterId(859)};std::array<bool,5> found{};
    for(int band:{1,3})for(uint64_t seed=0;seed<256;++seed){if(std::all_of(found.begin(),found.end(),[](bool x){return x;}))break;
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);int floor=0;while(plan.profileOnFloor(floor).band<band)++floor;
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))for(size_t k=0;k<ids.size();++k)if(e.monster==ids[k]&&!found[k]){
            found[k]=true;check(s.arena.profile.band>=(k==4?3:1),"Host stage restriction");check(near(e.hp,s.content->monsterHealth(e.monster,s.arena.profile.sourceStage)),"source-stage HP");
            std::cout<<"NATURAL_HOST "<<e.monster.type<<'.'<<e.monster.variant<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
        }
        if(band==1&&std::all_of(found.begin(),found.begin()+4,[](bool x){return x;}))break;
    }
    check(std::all_of(found.begin(),found.end(),[](bool x){return x;}),"all five Host ports have seeded witnesses");
}
}
int main(){try{armor();volleys();movement();lifecycle();configuration();placement();std::cout<<"PASS Hosts: armor events, delayed openings, burning exception, contact, physical volleys, motion, lifecycle, config and seeded rooms\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
