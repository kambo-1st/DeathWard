#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/SourcePropRooms.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace dw;
namespace {
void check(bool b,const char *why){if(!b)throw std::runtime_error(why);}
const auto Root=std::filesystem::path(DEATHWARD_TEST_ROOT);
std::vector<std::string> cols(const std::string &line){std::istringstream s(line);std::vector<std::string> v;for(std::string x;std::getline(s,x,',');)v.push_back(x);return v;}
Simulation fixture() {
    Simulation s(69,1,{},MissionTheme::Mine,false);
    s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,8,100}};s.arena.rooms.resize(1);
    auto &r=s.arena.rooms[0];r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};s.arena.rebuildWalls();
    s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(1,{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;
    s.player.position={80,.85f,0};s.gaperMovementMultiplier=1;s.frowningMovementMultiplier=1;return s;
}
void trajectories() {
    constexpr float scale=Simulation::GaperMovementScale;
    for(Vector3 offset:std::array<Vector3,3>{{{0,0,0},{30,0,-17},{-63,0,28}}}) {
        auto world=[&](float x,float y){return Vector3{offset.x+(x-320)*scale,.85f,offset.z+(y-280)*scale};};
        std::ifstream f(Root/"docs/reports/isaac-first-floor-parity/gaper-trajectories/native-trajectories.csv");check(bool(f),"native trajectories available");
        std::string line,name;std::getline(f,line);std::unique_ptr<Simulation> s;EntityId id=0;int cases=0,states=0;float ep=0,ev=0;
        while(std::getline(f,line)) {
            const auto c=cols(line);if(c[1]!="0")continue;
            const auto target=world(std::stof(c[5]),std::stof(c[6])),expected=world(std::stof(c[9]),std::stof(c[10]));
            if(name!=c[0]) {
                name=c[0];++cases;s=std::make_unique<Simulation>(fixture());s->player.position=target;id=s->spawnMonster(monsterId(10),expected);auto *e=s->findEnemy(id);check(e,"Frowning spawned");e->friendly=true;
                e->velocity={std::stof(c[16])*30*scale,0,std::stof(c[17])*30*scale};
                if(name=="frowning-awake-turn"){e->gaper->initialized=true;e->gaper->wakeStarted=e->gaper->headPlaying=true;e->gaper->headFrame=1;e->awakened=true;}
                continue;
            }
            s->player.position=target;s->step({},Tick);const auto *e=s->findEnemy(id);check(e&&e->alive,"Frowning retained");
            ep=std::max(ep,planarDistance(e->position,expected));ev=std::max(ev,length(sub(e->velocity,{std::stof(c[14])*30*scale,0,std::stof(c[15])*30*scale})));
            check(ep<.002f&&ev<.005f,"production-scale native Frowning trajectory");++states;
        }
        check(cases==2&&states==360,"both native Frowning trajectories covered");std::cout<<"PASS 360 native trajectory states offset="<<offset.x<<','<<offset.z<<" errors="<<ep<<','<<ev<<'\n';
    }
}
void phases() {
    std::ifstream f(Root/"docs/reports/isaac-first-floor-parity/frowning-phase-review/native-phases.csv");check(bool(f),"native phases available");
    std::string line,name;std::getline(f,line);std::unique_ptr<Simulation> s;EntityId id=0;int cases=0,states=0;
    while(std::getline(f,line)) {
        auto c=cols(line);
        if(name!=c[0]){name=c[0];++cases;s=std::make_unique<Simulation>(fixture());id=s->spawnMonster(monsterId(10),{0,.85f,0});s->findEnemy(id)->friendly=true;if(std::stof(c[3])==.5f)check(s->applyEnemyStatus(id,EnemyStatus::Slow,10000),"supplied half-time fixture");}
        auto *e=s->findEnemy(id);check(std::abs(e->gaper->headFrame+e->gaper->headFraction-std::stof(c[4]))<1e-6f,"native pre-AI head");
        if(std::stoi(c[2]))s->arena.obstacles.clear();else s->arena.obstacles={{{40,0,-100},{41,3,100}}};s->arena.rebuildWalls();
        s->step({},1.f/30);e=s->findEnemy(id);
        check(e->gaper->directPath==bool(std::stoi(c[2])),"supplied route reproduced physically");
        check(std::abs(e->gaper->headFrame+e->gaper->headFraction-std::stof(c[7]))<1e-6f&&std::abs(e->gaper->force-std::stof(c[5]))<1e-6f&&e->gaper->headPlaying==bool(std::stoi(c[8])),"native post-AI head/force/playback");++states;
    }
    check(cases==6&&states==288,"six bounded native phase cases");std::cout<<"PASS 288 native supplied phase states; full Slow scheduler not certified\n";
}
void movement() {
    for(float factor:{.1f,.5f,1.f,2.f})for(int hz:{30,60,120}) {
        auto s=fixture();s.frowningMovementMultiplier=factor;const auto id=s.spawnMonster(monsterId(10),{0,.85f,0});
        for(int i=0;i<4*hz;++i)s.step({},1.f/hz);auto *e=s.findEnemy(id);
        const float expected=2*.720000029f/.3f*30*Simulation::GaperMovementScale*factor;
        check(std::abs(length(e->velocity)-expected)<.003f&&e->gaper->headFrame==19&&!e->gaper->headPlaying,"awake speed and finished overlay at partitions/tuning bounds");
        const auto at=e->position,v=e->velocity;s.frowningMovementMultiplier=1;check(distance(at,e->position)==0&&distance(v,e->velocity)==0,"live edit retains position and momentum");
        check(e->hp==32&&e->radius==.6f&&s.player.shotDamage==24,"existing HP/body and historical fixture damage retained");
        for(int i=0;i<2*hz;++i)s.step({},1.f/hz);check(std::abs(length(e->velocity)-2*.720000029f/.3f*30*Simulation::GaperMovementScale)<.003f,"live drive settles independently");
    }
    for(int variant:{1,2}) {
        auto a=fixture(),b=fixture();a.frowningMovementMultiplier=.1f;b.frowningMovementMultiplier=2;
        const auto x=a.spawnMonster(monsterId(10,variant),{0,.85f,0}),y=b.spawnMonster(monsterId(10,variant),{0,.85f,0});
        for(int n=0;n<120;++n){a.step({});b.step({});}check(distance(a.findEnemy(x)->position,b.findEnemy(y)->position)<.00001f,"ordinary/flaming variant unaffected by Frowning control");
    }
    auto s=fixture();s.godMode=false;s.player.position={0,.85f,0};s.spawnMonster(monsterId(10),{.9f,.85f,0});s.step({});check(s.player.hp==5,"one-half-heart Frowning contact");s.step({});check(s.player.hp==5,"hurt immunity retained");
    auto d=fixture();d.godMode=false;d.player.position={0,.85f,0};d.spawnMonster(monsterId(10),{.9f,.85f,0});d.player.dodge=.3f;d.step({});check(d.player.hp==6,"universal dodge immunity retained");
    auto floor=Simulation(69,1,{},MissionTheme::Canyon);floor.frowningMovementMultiplier=.65f;floor.jumpDebug(floor.finalRoom());floor.clearRoomDebug();floor.step({});floor.floorExitRequested=true;
    check(floor.advanceFloor()&&floor.frowningMovementMultiplier==.65f,"floor transition preserves independent movement");
    std::cout<<"PASS independent movement/live boundaries, 30/60/120Hz, contact/dodge and floor transition\n";
}
Simulation generated(uint64_t seed,float scale=1.1f,int lo=7,int hi=9,int mode=1) {
    auto s=Simulation(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),scale,lo,hi,.26f,true,mode,true,true,true,true,true,true,1,1,{}, {},true,25,{1});
    s.gaperMovementMultiplier=1;s.frowningMovementMultiplier=1;s.applyCombatBalance(3.5f,1);return s;
}
void generation(uint64_t seed,uint64_t largeSeed) {
    for(auto dims:{std::array<float,3>{.75f,5,5},{1.1f,7,9},{1.5f,10,10}}) {
        if(dims[0]==1.5f)seed=largeSeed;
        auto s=generated(seed,dims[0],int(dims[1]),int(dims[2]));check(s.enterSourceRoomReview(51),"natural source51 witness at each size");const int room=s.room;const auto layout=s.arena.rooms[size_t(room)];
        check(s.enemies.size()==2&&s.floorEncounter(room).monsters==std::vector<MonsterId>(2,monsterId(10)),"exact Frowning roster/budget");
        int rocks=0,poop=0;
        for(const auto &b:s.arena.breakables)if(b.room==room){rocks+=b.kind==BreakableKind::CrackedRock;poop+=b.kind==BreakableKind::Dung;check(b.sourceGridIndex>=0,"recorded source grid slot");}
        check(rocks==2&&poop==4&&layout.heartSpawns.empty(),"two rocks/four poops/no initial pickups");
        for(int i=0;i<2;++i){const auto &e=s.enemies[size_t(i)];check(distance(e.position,sourceHeartCell(layout,6,2+i*2))<.0001f&&e.hp==32&&e.champion<0&&!s.arena.blocked(e.position,e.radius),"exact actor cells, ordinary HP and clearance");}
        s.godMode=true;
        std::vector<EntityId> ids;for(const auto &e:s.enemies)ids.push_back(e.id);
        std::vector<bool> reached(2);for(int n=0;n<3600;++n){s.step({});for(size_t i=0;i<2;++i)if(auto *e=s.findEnemy(ids[i]);e&&e->alive){check(!s.arena.blocked(e->position,e->radius),"pursuit respects floor and props");if(planarDistance(e->position,s.player.position)<1.5f){reached[i]=true;e->alive=false;}}}
        check(reached[0]&&reached[1],"both live actors reach entrance around props");
        // Fresh combat instance uses real player projectile damage, including any existing headless lifecycle.
        s=generated(seed,dims[0],int(dims[1]),int(dims[2]));s.enterSourceRoomReview(51);s.godMode=true;
        for(int n=0;n<7200&&!s.roomClear;++n){Input in;for(const auto &e:s.enemies)if(e.alive&&!e.environment){for(auto dir:std::array<Vector3,4>{{{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}}}){auto p=add(e.position,mul(dir,2));if(s.arena.roomAt(p)==room&&!s.arena.blocked(p,.48f)&&s.arena.clear(p,e.position,.15f)){s.player.position=p;in.fire=true;in.aim=e.position;break;}}if(in.fire)break;}s.step(in);}
        check(s.roomClear&&s.stats.shots>=6&&s.stats.kills>=2,"real projectiles clear Frowning and retained lifecycle");
        const auto prop=std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &b){return b.room==room&&b.kind==BreakableKind::Dung;});check(prop!=s.arena.breakables.end(),"poop exists");
        const auto id=prop->id;const auto at=prop->rewardPosition;
        bool shot=false;for(auto dir:std::array<Vector3,4>{{{0,0,-1},{0,0,1},{1,0,0},{-1,0,0}}}){const float standOff=std::max(prop->bounds.max.x-prop->bounds.min.x,prop->bounds.max.z-prop->bounds.min.z)*.5f+.9f;auto p=add(at,mul(dir,standOff));if(s.arena.roomAt(p)==room&&!s.arena.blocked(p,.48f)){s.player.position=p;Input in;in.fire=true;in.aim=at;for(int n=0;n<360&&!prop->destroyed;++n)s.step(in);if(prop->destroyed){shot=true;break;}}}
        check(shot&&prop->destroyed&&prop->propReward.resolved,"real shots destroy poop and resolve reward once");
        // Wider adjacent piles can still cover the destroyed pile's centre.
        // Clear those real neighbours before expecting player-sized access.
        for(auto &other:s.arena.breakables)if(other.room==room&&other.solid()&&sphereBox(at,.48f,other.bounds)) {
            check(other.kind==BreakableKind::Dung,"only an adjacent source pile screens the opened centre");
            Input in;in.fire=true;in.aim=other.rewardPosition;
            for(int n=0;n<360&&!other.destroyed;++n)s.step(in);
            check(other.destroyed&&other.propReward.resolved,"real shots clear the adjacent wider pile");
        }
        check(!s.arena.blocked(at,.48f),"destroyed piles open physical access");const auto reward=prop->propReward.seed;
        s.enterRoom(0);s.enterRoom(room);check(s.roomThreats()==0,"revisit stays clear");auto p=std::find_if(s.arena.breakables.begin(),s.arena.breakables.end(),[&](const auto &b){return b.id==id;});check(p->destroyed&&p->propReward.seed==reward,"revisit keeps destruction/reward identity");
        s.frowningMovementMultiplier=.65f;s.resizeRooms(dims[0],int(dims[1]),int(dims[2]),.26f,std::nullopt,0);check(s.frowningMovementMultiplier==.65f&&s.arena.rooms[size_t(room)].sourceCombatTemplate!=51,"OFF Apply retains movement");s.resizeRooms(dims[0],int(dims[1]),int(dims[2]),.26f,std::nullopt,1);check(s.arena.rooms[size_t(room)].sourceCombatTemplate==51&&s.roomEnemies(room).size()==2,"SOURCE Apply restores source51");
        std::cout<<"PASS source51 seed="<<seed<<" room="<<room+1<<" size="<<dims[0]<<" range="<<dims[1]<<'-'<<dims[2]<<" live route/real kills/poop/revisit/Apply\n";
    }
}
void presets() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-frowning-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));std::filesystem::create_directories(dir);
    for(auto file:{"d03-shooting/user-preset-2026-11-11.json","d14a3-round-worm/tuned-preset.json"}){
        auto p=BalancePreset::load(Root/"docs/reports/isaac-first-floor-parity"/file,defaultMechanics()->fingerprint());check(p.defaultZoomPercent==165&&p.frowningMovementMultiplier==1,"schema5/49 migrations preserve view and add baseline Frowning");
        p.frowningMovementMultiplier=.65f;p.gaperMovementMultiplier=1.2f;p.save(dir/"export.json");check(BalancePreset::load(dir/"export.json",p.mechanicsFingerprint).json()==p.json(),"schema50 exact independent round trip");
        auto bad=p;bad.frowningMovementMultiplier=0;bool refused=false;try{bad.save(dir/"export.json");}catch(...){refused=true;}check(refused&&BalancePreset::load(dir/"export.json",p.mechanicsFingerprint).json()==p.json(),"invalid edit leaves saved preset intact");
    }
    std::filesystem::remove_all(dir);std::cout<<"PASS schema50 export/load, older migrations and invalid-value rejection\n";
}
}
int main(int argc,char **argv){try{std::cout<<std::unitbuf;
 if(argc>1&&std::string(argv[1])=="--find"){for(uint64_t seed=argc>3?std::stoull(argv[3]):0;seed<10000;++seed){if(seed%100==0)std::cout<<"SCAN "<<seed<<std::endl;auto s=argc>2?generated(seed,1.5f,10,10):generated(seed);if(s.enterSourceRoomReview(51)){std::cout<<"FOUND "<<seed<<" room "<<s.room+1<<'\n';return 0;}}return 1;}
 trajectories();phases();movement();if(argc>2)generation(std::stoull(argv[1]),std::stoull(argv[2]));presets();return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
