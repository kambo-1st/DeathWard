#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool value,const char *why){if(!value)throw std::runtime_error(why);}
bool near(float a,float b,float epsilon=.01f){return std::abs(a-b)<epsilon;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,content);
    s.arena=Arena{};s.arena.bounds={{-50,-1,-50},{50,20,50}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-50,-.4f,-50},{50,0,50}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={-40,.85f,-40};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
EntityId spawn(Simulation &s,int variant=0,Vector3 at={0,.85f,0}){return s.spawnMonster(monsterId(40,variant),at);}
void heading(Enemy &e,int d=1){e.guts->initialized=true;e.guts->direction=d;e.guts->hasDestination=false;}
void damage(Simulation &s,EntityId id){Event h;h.type=EventType::Damage;h.target=id;h.damage=10000;s.queueRoot(h);s.drainEvents();}
void movement() {
    for(int variant=0;variant<3;++variant) {
        auto s=fixture();const auto id=spawn(s,variant);auto &e=*s.findEnemy(id);
        check(e.guts&&near(e.maxHp,variant?89.6f:80.f),"source health conversion and dedicated runtime");
        tick(s);check(length(e.velocity)<.001f,"initial source update only initializes");heading(e);tick(s);
        const float force=variant==0?3:variant==1?3.3f:2.45f;
        check(near(e.velocity.x,force*3),"source force applies after compensated friction");tick(s);
        check(near(e.velocity.x,force*3*1.6f),"source .6 momentum retention");
    }
    auto a=fixture(),b=fixture();const auto aid=spawn(a),bid=spawn(b);heading(*a.findEnemy(aid));heading(*b.findEnemy(bid));
    b.player.position={40,.85f,40};tick(a,40);tick(b,160,1.f/120);
    check(distance(a.findEnemy(aid)->position,b.findEnemy(bid)->position)<.02f,"30 and120Hz preserve unconstrained trajectory and target independence");
    auto pull=fixture();const auto pid=spawn(pull);auto &pe=*pull.findEnemy(pid);heading(pe);
    pe.guts->hasDestination=true;pe.guts->destination={10,.85f,.25f};tick(pull);
    const float sideForce=3*.25f/std::sqrt(100.f+.25f*.25f);
    check(near(pe.velocity.z,(sideForce+2.5f*.4f)*.6f*3),"cross-axis pull also receives common friction");
    auto contour=fixture();contour.arena.obstacles.push_back({{-4,0,-4},{4,6,4}});contour.arena.rebuildWalls();
    const auto cid=spawn(contour,0,{0,.85f,-6});std::array<bool,4> sides{};
    for(int n=0;n<360;++n) {
        tick(contour);const auto &e=*contour.findEnemy(cid);check(!contour.arena.blocked(e.position,e.radius),"contour never overlaps obstacle or room wall");
        if(std::abs(e.position.z)<4){if(e.position.x<-4)sides[0]=true;if(e.position.x>4)sides[1]=true;}
        if(std::abs(e.position.x)<4){if(e.position.z<-4)sides[2]=true;if(e.position.z>4)sides[3]=true;}
    }
    const auto &r=*contour.findEnemy(cid)->guts;
    std::cout<<"CONTOUR sides="<<sides[0]<<sides[1]<<sides[2]<<sides[3]<<" turns="<<r.turns<<" position="<<contour.findEnemy(cid)->position.x<<','<<contour.findEnemy(cid)->position.z<<'\n';
    check(std::all_of(sides.begin(),sides.end(),[](bool x){return x;}),"follows all sides of an interior obstacle");
    auto removed=fixture();removed.arena.obstacles.push_back({{-10,0,2},{10,6,5}});removed.arena.rebuildWalls();
    const auto rid=spawn(removed);heading(*removed.findEnemy(rid));tick(removed,3);
    removed.arena.obstacles.clear();removed.arena.rebuildWalls();const auto start=removed.findEnemy(rid)->position;tick(removed,12);
    check(removed.findEnemy(rid)->position.x>start.x+3&&std::abs(removed.findEnemy(rid)->position.z-start.z)<.1f,"destroyed anchor leaves forward travel instead of homing to vanished rock");
    std::cout<<"MOVEMENT source_forces=3/3.3/2.45 retention=.6 partition=1 rock_contour=1 removed_obstacle=1\n";
}
void charge() {
    auto s=fixture();const auto id=spawn(s,2);auto &e=*s.findEnemy(id);heading(e);e.guts->recovery=0;s.player.position={20,.85f,0};
    tick(s);check(e.guts->windup==0&&e.guts->charges==1&&!e.guts->charging,"aligned target starts six-frame warning");
    const auto direction=e.guts->chargeDirection;s.player.position={20,.85f,20};tick(s,5);
    check(!e.guts->charging&&e.guts->windup==5,"warning not skipped");tick(s);
    check(e.guts->charging&&e.guts->windup==-1&&near(e.guts->multiplier,1.8f),"charge begins after six frames");
    check(distance(direction,e.guts->chargeDirection)<.001f,"committed charge ignores changed target");
    s.arena.obstacles.push_back({{15,0,-10},{16,6,10}});s.arena.rebuildWalls();
    for(int n=0;n<90&&!e.guts->stops;++n)tick(s);
    check(e.guts->stops==1&&!e.guts->charging&&e.guts->recovery==60,"solid impact ends charge and starts60-frame recovery");
    check(!s.arena.blocked(e.position,e.radius)&&e.guts->hitFrame==0,"impact stays outside cover and starts pose");
    s.player.position={-40,.85f,-40};tick(s,59);check(e.guts->recovery==1,"recovery lasts full60sourceframes");tick(s);check(e.guts->recovery==0,"recovery expires");
    auto cover=fixture();cover.arena.obstacles.push_back({{5,0,-10},{6,6,10}});cover.arena.rebuildWalls();
    const auto cid=spawn(cover,2);heading(*cover.findEnemy(cid));cover.findEnemy(cid)->guts->recovery=0;cover.player.position={20,.85f,0};tick(cover);
    check(!cover.findEnemy(cid)->guts->charges,"cover prevents charge acquisition");
    auto diagonal=fixture();auto did=spawn(diagonal,2);heading(*diagonal.findEnemy(did));diagonal.findEnemy(did)->guts->recovery=0;
    diagonal.player.position={20,.85f,20};tick(diagonal);check(!diagonal.findEnemy(did)->guts->charges,"different row and column cannot trigger charge");
    std::cout<<"SLOG windup6=1 committed=1 impact=1 recovery60=1 cover=1 cardinal=1\n";
}
void trailsAndLifecycle() {
    for(int variant:{1,2}) {
        auto s=fixture();const auto id=spawn(s,variant);heading(*s.findEnemy(id));tick(s,12);
        check(!s.hazards.empty()&&s.findEnemy(id)->guts->creepPatches>0,"variant emits ground trail");
        auto h=s.hazards.back();check(h.kind==(variant==1?HazardKind::Creep:HazardKind::Tar)&&
            near(h.duration,float(variant==1?20:150)/30),"distinct red and tar lifetimes fromsource");
        const auto count=s.hazards.size();damage(s,id);check(s.hazards.size()==count,"trail survives owner death");
        s.enemies.clear();s.hazards.clear();h.age=0;h.fadeAge=-1;s.hazards.push_back(h);s.godMode=false;s.player.hurt=0;s.player.position=h.position;
        tick(s);check(variant==1?near(s.player.hp,87.5f):near(s.player.hp,100)&&s.player.slowTime>0,"red hurts; black slows without damage");
        s.hazards.front().age=s.hazards.front().duration;s.player.slowTime=0;s.player.hurt=0;const auto hp=s.player.hp;tick(s);
        check(near(s.player.hp,hp)&&s.player.slowTime==0,"fading trail is harmless");tick(s,60);check(s.hazards.empty(),"fading trail removed");
    }
    auto s=fixture();const auto id=spawn(s,1);heading(*s.findEnemy(id));s.limits.hazards=0;tick(s,6);
    check(s.findEnemy(id)->guts->pendingCreep.has_value()&&s.hazards.empty(),"capacity keeps due trail pending");
    const auto pending=*s.findEnemy(id)->guts->pendingCreep;const auto pausedTick=s.findEnemy(id)->guts->ticks;
    tick(s,6);check(s.findEnemy(id)->guts->ticks==pausedTick,"capacity wait does not consume more source decisions");
    s.limits.hazards=128;tick(s);
    check(!s.hazards.empty()&&distance(s.hazards.front().position,pending)<.001f,"capacity release emits retained footprint");
    check(s.findEnemy(id)->guts->ticks==pausedTick,"capacity release resumes already processed frame exactly once");
    auto plain=fixture();spawn(plain);tick(plain,60);check(plain.hazards.empty()&&plain.projectiles.empty(),"ordinary Guts has no trail or projectile");
    auto contact=fixture();auto cid=spawn(contact);contact.player.position={.8f,.85f,0};contact.godMode=false;tick(contact);
    check(near(contact.player.hp,87.5f),"body contact maps source one to local12.5damage");
    auto &stunned=*contact.findEnemy(cid);stunned.state=EnemyState::Stunned;stunned.stateTime=1;const auto before=stunned.position;
    tick(contact,20);check(distance(before,stunned.position)<.01f&&stunned.guts->ticks==1,"stun pauses controller and motion");
    std::cout<<"TRAIL red20=1 tar150=1 damage12.5=1 tar_no_damage=1 owner_death=1 fade=1 capacity=1\n";
}
void configuration() {
    const auto root=std::filesystem::temp_directory_path()/("dw-guts-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"guts.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture present");text.replace(at,from.size(),to);std::ofstream(root/"guts.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit(".1 3 .6 40", ".1 4 .6 40");check(changed&&near(changed->guts(monsterId(40))->force,4),"external force reloads");
    check(near(defaultMechanics()->guts(monsterId(40))->force,3),"old content snapshot preserved");
    for(const auto &[from,to]:std::vector<std::pair<std::string,std::string>>{
        {".1 3 .6 40",".1 3 1 40"},{"40 10 .4 10 24","40 30 .4 10 24"},
        {"guts_charge 40.2.0 6","guts_charge 40.2.0 0"},{"tar 4 1 150 40 .75 0","tar 4 1 150 40 .75 10"},
        {"\nguts_creep 40.2.0 tar 4 1 150 40 .75 0 .98", ""}})
        {bool rejected=false;try{edit(from,to);}catch(const std::exception&){rejected=true;}check(rejected,"invalid or incomplete controller rejected");}
    std::cout<<"CONFIG external_reload=1 immutable=1 invalid5=1\n";
}
void placement() {
    const auto content=defaultMechanics();std::array<bool,3> found{};
    int scarred=0,dank=0,replacements=0;
    for(uint64_t seed=0;seed<600;++seed) {
        FloorProfile p;p.band=2;auto works=content->configureFloor(p,seed);dank+=works.variant==FloorVariant::Dank;
        p.band=3;auto storm=content->configureFloor(p,seed);scarred+=storm.variant==FloorVariant::Scarred;
        const auto *replacement=content->replacement(monsterId(40),storm);
        check(bool(replacement)==(storm.variant==FloorVariant::Scarred),"Guts replacement gated to Scarred context");
        if(replacement){check(replacement->chance==5000,"source50percent replacement");++replacements;}
    }
    check(dank>160&&dank<240&&scarred>160&&scarred<240&&replacements==scarred,"seeded contexts sampled at authored weights");
    for(uint64_t seed=0;seed<128&&!std::all_of(found.begin(),found.end(),[](bool x){return x;});++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            if(plan.profileOnFloor(floor).band<2)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);s.godMode=true;
            for(int room=1;room<s.finalRoom();++room) {
                std::vector<EntityId> actors;
                for(const auto &e:s.roomEnemies(room))if(e.monster.type==40) {
                    const int v=e.monster.variant;
                    check(v<3&&e.guts&&!s.arena.blocked(e.position,e.radius),"natural dedicated resident has legal footprint");
                    check(v==0?s.arena.profile.band>=2:v==1?s.arena.profile.band==3:
                        s.arena.profile.band==2&&s.arena.profile.variant==FloorVariant::Dank,"reviewed source habitats respected");
                    if(!found[size_t(v)])std::cout<<"NATURAL_GUTS variant="<<v<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<" context="<<int(s.arena.profile.variant)<<'\n';
                    found[size_t(v)]=true;actors.push_back(e.id);
                }
                if(!actors.empty()){s.enterRoom(room);s.player.position=s.arena.rooms[size_t(room)].entry;tick(s,8);
                    for(auto id:actors)check(s.findEnemy(id)&&s.findEnemy(id)->guts->ticks>0,"natural controller activates");}
            }
        }
    }
    check(std::all_of(found.begin(),found.end(),[](bool x){return x;}),"all three source variants reachable");
}
}
int main(){std::cout<<std::unitbuf;try{movement();charge();trailsAndLifecycle();configuration();placement();std::cout<<"PASS Guts contracts\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
