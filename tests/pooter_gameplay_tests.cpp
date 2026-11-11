#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include <fstream>
#include <chrono>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
std::vector<std::string> columns(const std::string &row){std::istringstream in(row);std::vector<std::string> result;for(std::string s;std::getline(in,s,',');)result.push_back(s);return result;}
std::unique_ptr<Simulation> fixture(bool enabled=true) {
    auto run=std::make_unique<Simulation>(1866,1,WorldState{},MissionTheme::Mine,false);
    run->arena=Arena{};run->arena.bounds={{-100,-1,-100},{100,20,100}};run->arena.rooms.resize(1);
    auto &r=run->arena.rooms[0];r.bounds=run->arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;
    r.floors={{{-100,-.4f,-100},{100,0,100}}};run->arena.rebuildWalls();
    run->enemies.clear();run->projectiles.clear();run->hazards.clear();run->moneyPickups.clear();run->heartPickups.clear();
    run->rooms.assign(1,{});run->room=0;run->stats={};run->debugScenario=true;run->godMode=true;
    run->player.position={40,.85f,0};if(enabled)run->pooterTuning=PooterTuning{};
    return run;
}
void step(Simulation &run,int count){for(int n=0;n<count;++n)run.step({},Tick);}

constexpr float scale=Simulation::GaperMovementScale;
const std::string root=std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/";
Vector3 world(float x,float z){return {(x-60)*scale,.85f,(z-140)*scale};}
struct QuietPack {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-d06-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::shared_ptr<const MechanicsLibrary> library;
    QuietPack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());
        auto file=path/"buzz_flies.mechanics";std::ifstream in(file);std::string text((std::istreambuf_iterator<char>(in)),{});
        const std::string row="buzz_fly 14.0.0 .1 5 .7 .6 .4 .6 .06 3 24";const auto at=text.find(row);check(at!=text.npos,"quiet source profile exists");
        text.replace(at,row.size(),"buzz_fly 14.0.0 .1 5 0 0 .4 .6 0 3 24");{std::ofstream out(file);out<<text;}library=MechanicsLibrary::load(path);
    }
    ~QuietPack(){std::filesystem::remove_all(path);}
};
void nativeMotion(int partitions) {
    std::ifstream in(root+"spider-pooter-movement/pooter-native.csv");check(bool(in),"native wandering reference");
    std::string row,name;std::getline(in,row);std::unique_ptr<Simulation> run;EntityId id=0;float maxError=0;int samples=0;
    while(std::getline(in,row)) {
        const auto c=columns(row);
        if(name!=c[0]) {
            name=c[0];run=fixture();run->arena.rooms[0].bounds={{0,-1,0},{520*scale,8,280*scale}};run->player.position=world(1000,280);
            id=run->spawnMonster(monsterId(14),world(std::stof(c[2]),std::stof(c[3])));auto *e=run->findEnemy(id);check(e,"ordinary Pooter spawns");
            // The native capture excludes collision. Its edge points would clip
            // the retained DW body at the new scale; isolate arithmetic here.
            e->radius=.01f;e->friendly=true;e->buzz.emplace();e->buzz->initialized=true;e->buzz->wander={.2f,0,.1f};
            e->velocity={(name=="right"?-4:2)*scale*30,0,(name=="bottom"?-2:1)*scale*30};e->cooldown=std::stof(c[4])/30;run->combatRng=Random(123456);
        }
        for(int i=0;i<partitions;++i)run->step({},1.f/(30*partitions));const auto &e=*run->findEnemy(id);
        const float error=planarDistance(e.position,world(std::stof(c[7]),std::stof(c[8])));maxError=std::max(maxError,error);
        if(error>=.002f||length(sub(e.velocity,{std::stof(c[9])*scale*30,0,std::stof(c[10])*scale*30}))>=.005f||length(sub(e.buzz->wander,{std::stof(c[11]),0,std::stof(c[12])}))>=.0001f)
            std::cerr<<"native row="<<row<<" actual="<<e.position.x<<','<<e.position.z<<" velocity="<<e.velocity.x<<','<<e.velocity.z<<" wander="<<e.buzz->wander.x<<','<<e.buzz->wander.z<<" cooldown="<<e.cooldown<<'\n';
        check(error<.002f&&length(sub(e.velocity,{std::stof(c[9])*scale*30,0,std::stof(c[10])*scale*30}))<.005f&&
              length(sub(e.buzz->wander,{std::stof(c[11]),0,std::stof(c[12])}))<.0001f,"main-game Pooter matches preserved native wandering states");
        check(run->combatRng.state==std::stoull(c[6])&&run->projectiles.empty(),"identical supplied random stream; movement fixture excludes attacks");++samples;
    }
    check(samples==144,"all native Pooter motion states");std::cout<<"PASS native wandering states="<<samples<<" hz="<<30*partitions<<" max_position_error="<<maxError<<'\n';
}
std::unique_ptr<Simulation> quiet(const QuietPack &pack) {
    auto run=fixture();run->content=pack.library;run->player.position={0,.85f,2};return run;
}
EntityId spawn(Simulation &run){auto id=run.spawnMonster(monsterId(14),{0,.85f,0});run.findEnemy(id)->cooldown=0;return id;}
void acquire(Simulation &run,EntityId id) {
    for(int n=0;n<16&&run.findEnemy(id)->buzz.value_or(BuzzFlyRuntime{}).attackFrame<0;++n)step(run,1);
    check(run.findEnemy(id)->buzz&&run.findEnemy(id)->buzz->attackFrame==0,"acquires at source interval");
}
void attacks(const QuietPack &pack) {
    // Execute all source modulo gates with initialized ready/cooldown-free actors.
    std::ifstream gates(root+"d06-pooter-shots/native-interval.csv");check(bool(gates),"native interval reference");std::string row;std::getline(gates,row);int checked=0;
    while(std::getline(gates,row)) {
        auto c=columns(row);auto run=quiet(pack);auto id=spawn(*run);auto *e=run->findEnemy(id);
        e->id=unsigned(std::stoi(c[0])+7);e->buzz.emplace();e->buzz->initialized=true;e->buzz->tick=unsigned(std::stoi(c[1])-1);
        run->step({},1.f/30);e=&run->enemies[0];check((e->buzz->attackFrame==0)==(c[2]=="1"),"source global-frame/entity-index gate");++checked;
    }
    std::ifstream delays(root+"d06-pooter-shots/native-cooldown.csv");check(bool(delays),"native cooldown reference");std::getline(delays,row);int counters=0;
    while(std::getline(delays,row)) {
        const auto c=columns(row);auto run=quiet(pack);run->player.position={40,.85f,0};auto id=spawn(*run);auto *e=run->findEnemy(id);
        e->buzz.emplace();e->buzz->initialized=true;e->buzz->tick=2;e->buzz->wander={.2f,0,0};e->cooldown=std::stof(c[0])/30;e->velocity={scale*30,0,0};
        run->step({},1.f/30);e=run->findEnemy(id);
        check(std::abs(e->cooldown*30-std::stof(c[1]))<.001f&&std::abs(e->velocity.x/(scale*30)-std::stof(c[2]))<.001f&&std::abs(e->buzz->wander.x-std::stof(c[3]))<.0001f,"native cooldown decrements after its damping, including last positive frame");++counters;
    }
    std::ifstream shots(root+"d06-pooter-shots/native-shot-velocity.csv");check(bool(shots),"native shot vector reference");std::getline(shots,row);int vectors=0;
    while(std::getline(shots,row)) {
        const auto c=columns(row);auto run=quiet(pack);auto id=spawn(*run);acquire(*run,id);const double start=run->stats.duration;
        step(*run,11);check(run->projectiles.empty(),"no shot before Shoot6");run->player.position={std::stof(c[0])*10,.85f,std::stof(c[1])*10};step(*run,1);
        check(run->projectiles.size()==1,"Shoot6 fires one current-target shot outside acquisition range");const auto &shot=run->projectiles[0];
        check(length(sub(shot.velocity,{std::stof(c[2])*scale*30,0,std::stof(c[3])*scale*30}))<.0001f&&shot.pooterFlight&&shot.pooterFlight->height==-23,"native shot vector and birth height");
        check(std::abs(run->stats.duration-start-.2)<.0001&&shot.damage==10&&shot.radius==.22f,"source windup; existing damage/radius retained");
        step(*run,16);check(run->findEnemy(id)->buzz->attackFrame==-1,"recovers after animation14");++vectors;
    }
    auto run=quiet(pack);const auto id=spawn(*run);acquire(*run,id);const double first=run->stats.duration;
    step(*run,4);const auto wait=run->findEnemy(id)->cooldown;run->pooterTuning=PooterTuning{.5f,.5f,2};
    check(run->findEnemy(id)->cooldown==wait&&run->findEnemy(id)->buzz->attackFrame==2,"tuning does not reset active cooldown/animation");step(*run,8);
    check(run->projectiles.size()==1&&std::abs(length(run->projectiles[0].velocity)-7*scale*30)<.0001f,"active attack retains selected shot speed");
    const auto projectile=run->projectiles[0].id;run->pooterTuning->shotSpeed=.65f;step(*run,2);
    check(std::abs(length(run->projectiles[0].velocity)-7*scale*30)<.0001f&&run->projectiles[0].id==projectile,"flying bullet birth specs survive tuning");
    run->player.position={0,.85f,2};while(run->stats.projectiles<2&&run->stats.duration-first<3)step(*run,1);
    check(run->stats.projectiles==2&&std::abs(run->stats.duration-first-41./30)<.0002,"reference first wait survives live edit");
    check(std::abs(length(run->projectiles.back().velocity)-7*scale*30*.65f)<.0001f&&run->findEnemy(id)->buzz->attackIntervalMultiplier==2,"next attack latches both overrides");
    const double second=run->stats.duration;while(run->stats.projectiles<3&&run->stats.duration-second<3)step(*run,1);
    check(run->stats.projectiles==3&&std::abs(run->stats.duration-second-70./30)<.0002,"200 percent delay applies to subsequent attack interval");
    std::cout<<"PASS source gates="<<checked<<" cooldown cases="<<counters<<" shot vectors="<<vectors<<" windup/recovery and safe live boundaries\n";
}
void flight(const QuietPack &pack,int partitions) {
    auto run=quiet(pack);const auto id=spawn(*run);acquire(*run,id);step(*run,12);check(run->projectiles.size()==1,"actual emitted flight fixture");
    run->player.position={40,.85f,40};run->findEnemy(id)->cooldown=100;
    const auto origin=run->projectiles[0].origin;std::ifstream in(root+"d06-pooter-shots/native-flight.csv");check(bool(in),"native flight exists");std::string row;std::getline(in,row);int states=0;
    while(std::getline(in,row)) {
        const auto c=columns(row);for(int i=0;i<partitions;++i)run->step({},1.f/(30*partitions));
        if(c[4]=="1")check(run->projectiles.empty(),"bullet lands on native update31");
        else {check(run->projectiles.size()==1,"bullet remains airborne before native landing");const auto &p=run->projectiles[0];
            check(std::abs(planarDistance(origin,p.position)-(std::stof(c[1])-320)*scale)<.001f&&std::abs(p.pooterFlight->height-std::stof(c[2]))<.0001f&&
                  std::abs(p.pooterFlight->fallingSpeed-std::stof(c[3]))<.0001f,"native horizontal and falling trajectory");}
        ++states;
    }
    check(states==31,"entire native flight compared");std::cout<<"PASS emitted flight states="<<states<<" hz="<<partitions*30<<'\n';
}
void safety(const QuietPack &pack) {
    auto blocked=quiet(pack);spawn(*blocked);blocked->arena.obstacles={{{-10,0,.8f},{10,5,1.2f}}};blocked->arena.rebuildWalls();step(*blocked,180);check(blocked->stats.projectiles==0,"no acquisition through cover");
    auto impact=quiet(pack);auto id=spawn(*impact);acquire(*impact,id);step(*impact,12);impact->player.position={30,.85f,0};impact->findEnemy(id)->cooldown=100;
    impact->arena.obstacles={{{-10,0,1},{10,5,1.3f}}};impact->arena.rebuildWalls();step(*impact,30);check(impact->projectiles.empty(),"flying projectile collides with newly inserted wall");
    auto harm=quiet(pack);harm->godMode=false;spawn(*harm);step(*harm,60);check(harm->player.hp==5,"Pooter bullet deals exactly one red half-heart");
    auto elevated=quiet(pack);elevated->arena.obstacles={{{-.5f,0,-.5f},{.5f,2,.5f}}};elevated->arena.rebuildWalls();
    elevated->player.position={0,.85f,3};elevated->godMode=false;id=spawn(*elevated);check(elevated->findEnemy(id)->position.y>2,"Pooter is above actual cover");
    step(*elevated,110);check(elevated->player.hp==5,"source-speed Pooter projectile reaches ground player from elevated cover");
    auto touch=quiet(pack);touch->godMode=false;spawn(*touch);touch->player.position={0,.85f,0};step(*touch,1);check(touch->player.hp==6,"Pooter body stays harmless");
    auto capacity=quiet(pack);id=spawn(*capacity);capacity->limits.projectiles=0;step(*capacity,45);check(capacity->findEnemy(id)->buzz->attackFrame==6&&capacity->stats.projectiles==0,"capacity retains pending Shoot");
    capacity->pooterTuning->shotSpeed=.5f;capacity->limits.projectiles=512;step(*capacity,2);check(capacity->stats.projectiles==1&&std::abs(length(capacity->projectiles[0].velocity)-7*scale*30)<.0001f,"retained attack admits once at original speed");
    auto stun=quiet(pack);id=spawn(*stun);acquire(*stun,id);const auto before=stun->findEnemy(id)->cooldown;
    stun->findEnemy(id)->state=EnemyState::Stunned;stun->findEnemy(id)->stateTime=.3f;step(*stun,2);
    check(stun->findEnemy(id)->buzz->attackFrame==-1&&stun->findEnemy(id)->cooldown<before&&stun->stats.projectiles==0,"stun cancels pending attack while retaining cooldown progress");
    auto item=quiet(pack);id=spawn(*item);acquire(*item,id);step(*item,4);const auto remaining=item->findEnemy(id)->cooldown;item->grant(parseItemKey("isaac:collectible:9"));step(*item,10);
    check(item->stats.projectiles==0&&item->findEnemy(id)->cooldown==remaining,"Skatole retains existing suppression semantics");item->items.clear();step(*item,14);check(item->stats.projectiles==0,"suppressed Shoot does not replay");
    for(auto monster:{monsterId(13),monsterId(14,1),monsterId(14,2),monsterId(12)}) {
        auto a=fixture(false),b=fixture();auto x=a->spawnMonster(monster,{0,.85f,0}),y=b->spawnMonster(monster,{0,.85f,0});
        for(int n=0;n<120;++n){step(*a,1);step(*b,1);check(distance(a->findEnemy(x)->position,b->findEnemy(y)->position)<.0001f&&a->stats.projectiles==b->stats.projectiles,"unselected fly/shooter variants unchanged");}
    }
    std::cout<<"PASS terrain, incoming damage/contact, capacity, suppressor and unselected identities\n";
}
void inventory() {
    for(unsigned seed=0;seed<256;++seed) {
        Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),1.1f,7,9,.26f);
        for(int passage:run.arena.rooms[0].passages) {
            const auto &link=run.arena.passages[passage];const int room=link.rooms[0]==0?link.rooms[1]:link.rooms[0];bool found=false,suitable=true;
            for(const auto &e:run.roomEnemies(room)){found|=e.monster==monsterId(14);suitable&=e.champion<0&&(e.monster==monsterId(14)||e.monster==monsterId(10,1)||e.monster==monsterId(85));}
            if(!found||!suitable)continue;
            std::cout<<"HANDOFF seed="<<seed<<" room="<<room<<" displayed_room="<<room+1<<'\n';
            for(const auto &e:run.roomEnemies(room))std::cout<<"NATURAL "<<monsterIdText(e.monster)<<" entity="<<e.id<<" position="<<e.position.x<<','<<e.position.z<<'\n';return;
        }
    }
    check(false,"natural accessible Pooter encounter found");
}
}
int main(int argc,char **argv){std::cout<<std::unitbuf;try {
    if(argc>1&&std::string(argv[1])=="--inventory"){inventory();return 0;}
    for(int partitions:{1,2,4})nativeMotion(partitions);
    QuietPack pack;attacks(pack);for(int partitions:{1,2,4})flight(pack,partitions);safety(pack);
    std::cout<<"PASS D06 Pooter main-game consumer\n";
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
