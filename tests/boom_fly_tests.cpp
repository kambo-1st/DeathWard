#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.001f;}
struct Pack {
    std::filesystem::path root=std::filesystem::temp_directory_path()/("deathward-boom-flies-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(root);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))
        if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(root);}
    void edit(const char *file,const std::string &from,const std::string &to) {
        std::ifstream in(root/file);std::string data((std::istreambuf_iterator<char>(in)),{});const auto pos=data.find(from);
        check(pos!=std::string::npos,"External fixture edit exists");data.replace(pos,from.size(),to);in.close();std::ofstream(root/file)<<data;
    }
    void extra(const std::string &text){std::ofstream(root/"z-boom-test.mechanics")<<"DEATHWARD_MECHANICS 1\n"<<text;}
    auto load(){return MechanicsLibrary::load(root);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> rules=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic,std::move(rules));
    s.arena=Arena{};s.arena.bounds={{-25,-1,-25},{200,12,25}};
    for(size_t i=0;i<s.arena.rooms.size();++i) {
        auto &r=s.arena.rooms[i];const float x=float(i)*60;
        r.bounds={{x-25,-1,-25},{x+25,12,25}};r.center={x,.85f,0};r.kind=RoomKind::Combat;
    }
    for(auto &r:s.rooms){r.residents.clear();r.cleared=false;r.segmented.clear();r.plates.clear();}
    s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.enemyBombs.clear();s.suppliedBombs.clear();s.moneyPickups.clear();s.stats={};
    s.player.position={20,.85f,20};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.bossKilled=false;return s;
}
void tick(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void kill(Simulation &s,EntityId id,bool execution=false,bool debug=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=10000;e.execution=execution;e.debugExecution=debug;
    e.position=s.findEnemy(id)->position;s.queueRoot(e);s.drainEvents();
    if(s.findEnemy(id)->adaptiveArmor&&!execution) {
        // Keep the isolated death origin fixed while the real source-frame
        // armor batch resolves; ordinary damage still passes through armor.
        s.findEnemy(id)->facing={};
        tick(s,2);
    }
}
void healthAndMotion() {
    auto lib=defaultMechanics();
    const std::array<float,13> source{{11,14,17,20,20,22.4f,24.8f,27.2f,29.6f,32,32,32,32}};
    for(int stage=1;stage<=13;++stage)check(near(lib->monsterHealth(monsterId(25),stage),source[size_t(stage-1)]*3.2f),"Stage HP has source plateau at five and cap at ten");
    std::set<int> lengths;
    for(uint64_t seed=0;seed<64;++seed) {
        ExpeditionPlan plan(seed);lengths.insert(plan.floorCount);int previous=0;
        for(int floor=0;floor<plan.floorCount;++floor) {
            const auto p=lib->configureFloor(plan.profileOnFloor(floor),plan.floorSeed(floor));
            check(p.sourceStage==1+2*p.band+p.stageStep&&p.sourceStage>previous,"Every expedition length uses explicit advancing stage mapping");previous=p.sourceStage;
        }
    }
    check(lengths.size()==5,"All four-to-eight-floor lengths exercised");
    auto s=fixture();s.arena.profile.sourceStage=4;
    const auto id=s.spawnMonster(monsterId(25),{24.43f,.85f,0});auto &fly=*s.findEnemy(id);
    check(near(fly.hp,64)&&near(std::abs(fly.facing.x),std::abs(fly.facing.z)),"Spawn uses stage health and a diagonal bearing");
    fly.facing=unit({1,0,1});s.step({});
    check(s.findEnemy(id)->facing.x<0&&s.findEnemy(id)->facing.z>0,"Single blocked axis reflects while free axis keeps its sign");
    const auto start=s.findEnemy(id)->position;s.player.position={-20,.85f,-20};tick(s,20);
    check(s.findEnemy(id)->position.x<start.x&&s.findEnemy(id)->position.z>start.z,"Player movement does not steer a Boom Fly");
    auto contact=fixture();contact.player.position={0,.85f,0};contact.godMode=false;contact.spawnMonster(monsterId(25,6),{0,.85f,0});contact.step({});
    check(near(contact.player.hp,75)&&contact.stats.explosions==0,"Tainted has doubled contact damage and does not contact-detonate");
    auto cover=fixture();cover.arena.obstacles={{{-1,0,-1},{1,2,1}}};cover.arena.rebuildWalls();
    const auto high=cover.spawnMonster(monsterId(25),{-4,.85f,-4});cover.findEnemy(high)->facing=unit({1,0,1});float peak=0;
    for(int n=0;n<180;++n){cover.step({});const auto &e=*cover.findEnemy(high);peak=std::max(peak,e.position.y);check(!sphereBox(e.position,e.radius,cover.arena.obstacles[0]),"Diagonal flyer stays above interior cover");}
    check(peak>2.8f,"Diagonal path crosses raised cover");
    std::cout<<"BOOM_HEALTH source_stages_1_to_13=1 floor_lengths=5 diagonal_axis_reflection=1 contact=1 cover=1\n";
}
void deathPatterns() {
    for(auto id:{monsterId(25),monsterId(25,1),monsterId(25,2),monsterId(25,3),monsterId(25,3,1),monsterId(25,4),monsterId(25,5)}) {
        auto s=fixture();s.player.position={3,.85f,12};const auto actor=s.spawnMonster(id,{0,.85f,0});kill(s,actor);
        const auto &p=*s.content->boomFly(id);
        check(s.stats.kills==1&&!s.findEnemy(actor)->alive,"Death rewards once and removes ordinary threat");
        check(s.projectiles.size()==size_t(p.shots),"Variant emits exact configured death count");
        const bool blast=id.variant==0||id.variant==2;
        check(s.stats.explosions==(blast?1u:0u)&&s.enemyBombs.empty(),"Only normal and Drowned have immediate explosions");
        for(const auto &shot:s.projectiles) {
            check(shot.hostile&&shot.context.sourceEntity==actor&&near(shot.damage,p.shotDamage),"Death projectile preserves identity and damage");
            if(id.variant==2)check(std::min(std::abs(shot.velocity.x),std::abs(shot.velocity.z))<.001f,"Drowned shots are cardinal");
            if(id.variant==4)check(shot.kind==ProjectileKind::Bone,"Bone Fly has actual bone projectiles");
            if(id.variant==5)check(shot.kind==ProjectileKind::Green&&shot.blastRadius==0,"Sick shots are green but not Ipecac explosives");
        }
        if(id.variant==4) {
            const auto first=unit(horizontal(s.projectiles[0].velocity));check(near(first.x,0)&&first.z>.99f,"First death bone aligns to nearest cardinal toward player");
            check(near(dot(first,unit(horizontal(s.projectiles[1].velocity))),-.5f),"Three death bones are evenly spaced at 120 degrees");
        }
        if(id.variant==3) {
            check(s.hazards.size()>40,"Dragon fire extends across this room");
            for(const auto &h:s.hazards)check(h.kind==HazardKind::Fire&&
                (id.subtype?near(std::abs(h.position.x),std::abs(h.position.z)):std::min(std::abs(h.position.x),std::abs(h.position.z))<.001f),
                "Dragon fire follows its actual cardinal/diagonal pattern");
        }
        if(id.variant==5) {
            check(s.hazards.size()==8,"Sick death produces eight distinct gas clouds");
            for(const auto &h:s.hazards)check(h.kind==HazardKind::Gas&&near(h.duration,12)&&near(planarDistance({},h.position),2.25f),"Death clouds have their own longer duration and ring positions");
        }
    }
    auto collateral=fixture();collateral.godMode=false;collateral.player.position={2.5f,.85f,0};
    const auto root=collateral.spawnMonster(monsterId(25),{}),victim=collateral.spawnMonster(monsterId(14),{1,.85f,0});collateral.findEnemy(victim)->hp=500;
    kill(collateral,root);check(near(collateral.findEnemy(victim)->hp,400)&&near(collateral.player.hp,75),"Actual immediate explosion uses configured enemy/player damage");
    auto ordinary=fixture();kill(ordinary,ordinary.spawnMonster(monsterId(25),{}),true);check(ordinary.stats.explosions==1,"Non-debug execution preserves death attack");
    auto demolition=fixture();Breakable prop;prop.id=1;prop.room=0;prop.kind=BreakableKind::CrackedRock;
    prop.bounds={{1,0,-.5f},{1.5f,1.5f,.5f}};prop.health=1;demolition.arena.breakables.push_back(prop);demolition.arena.rebuildWalls();
    kill(demolition,demolition.spawnMonster(monsterId(25),{}));
    check(demolition.arena.breakables[0].destroyed&&demolition.arena.breakables[0].paid&&demolition.dynamite==StartingDynamite,
        "Immediate Boom Fly explosion uses actual rock demolition without player inventory");
    auto debug=fixture();kill(debug,debug.spawnMonster(monsterId(25),{}),true,true);check(debug.stats.explosions==0,"Explicit debug execution suppresses death attack");
    std::cout<<"BOOM_DEATH seven_patterns=1 bone_alignment=1 green_not_ipecac=1 actual_blast=1 execution_policy=1\n";
}
void liveAttacksAndLifecycle() {
    auto bone=fixture();bone.player.position={8,.85f,8};const auto id=bone.spawnMonster(monsterId(25,4),{});bone.findEnemy(id)->cooldown=0;
    bone.step({});check(bone.stats.projectiles==0,"Unaligned Bone Fly cannot aim arbitrarily at player");
    bone.player.position=add(bone.findEnemy(id)->position,{12,0,0});bone.step({});
    check(bone.projectiles.size()==1&&bone.projectiles[0].kind==ProjectileKind::Bone&&std::abs(bone.projectiles[0].velocity.z)<.001f,"Cardinal acquisition emits a real fixed-axis bone");
    tick(bone,15);check(bone.stats.projectiles==1,"Bone volley respects cooldown");
    auto sick=fixture();const auto sickId=sick.spawnMonster(monsterId(25,5),{});tick(sick,80);
    check(sick.hazards.size()>=2&&sick.hazards.size()<=4,"Sick trails short-lived gas on configured cadence");
    for(const auto &h:sick.hazards)check(near(h.duration,2.5f),"Trail duration differs from death clouds");
    kill(sick,sickId);sick.debugScenario=false;sick.step({});check(sick.roomClear&&sick.hazards.empty(),"Sick death gas dissipates at ordinary room clear");
    auto tainted=fixture();kill(tainted,tainted.spawnMonster(monsterId(25,6),{}));
    check(tainted.stats.explosions==0&&tainted.enemyBombs.size()==49,"Tainted death queues central warning plus room-spanning four explosion lines");
    for(const auto &b:tainted.enemyBombs)check(b.blastMarker&&std::min(std::abs(b.charge.position.x),std::abs(b.charge.position.z))<.001f,"Explosion markers form a cardinal cross without physical bombs");
    tainted.debugScenario=false;tick(tainted,30);check(tainted.roomClear&&tainted.stats.explosions==0,"Warning survives ordinary clear without early explosion");
    tick(tainted,8);check(tainted.stats.explosions==1,"Central blast precedes the outward chain");
    tick(tainted,100);check(tainted.stats.explosions==49&&tainted.enemyBombs.empty(),"Each staged explosion occurs exactly once after clear");
    auto boundary=fixture();boundary.arena.boundaryWalls={{{6,-1,-25},{7,12,25}}};
    boundary.arena.obstacles={{{2,0,-1},{3,2,1}}};boundary.arena.rebuildWalls();
    kill(boundary,boundary.spawnMonster(monsterId(25,6),{}));
    bool beyondCover=false;for(const auto &b:boundary.enemyBombs) {
        check(b.charge.position.x<6,"Tainted explosion chain cannot extend through the actual room boundary");
        beyondCover|=b.charge.position.x>3&&std::abs(b.charge.position.z)<.001f;
    }
    check(beyondCover,"Tainted chain crosses interior cover before stopping at boundary");
    auto pending=fixture();pending.limits.enemyBombs=1;kill(pending,pending.spawnMonster(monsterId(25,6),{}));
    check(pending.enemyBombs.size()==1&&pending.pendingEnemyBombs.size()==48,"Bounded active ordnance retains pending chain work");
    const float warningAge=pending.enemyBombs[0].charge.age;
    pending.enterRoom(1);tick(pending,60);check(pending.enemyBombs[0].charge.age==warningAge,"Inactive room pauses warning without resetting its elapsed time");
    pending.enterRoom(0);pending.clearRoomDebug();check(pending.enemyBombs.empty()&&pending.pendingEnemyBombs.empty(),"Debug clear removes active and queued blast chain");
    std::cout<<"BOOM_LIFECYCLE aligned_live_bones=1 gas_trail=1 gas_clear=1 tainted_cross=49 clear_persistence=1 bounded_pending=1\n";
}
void childAndExternal() {
    Pack p;p.edit("boom_flies.mechanics","boom_child 25.2.0 23.1.0 5000","boom_child 25.2.0 23.1.0 10000");
    p.extra("stage_health 23.1.0 12 10 3.2\n");auto rules=p.load();auto land=fixture(rules);land.arena.profile.sourceStage=4;
    kill(land,land.spawnMonster(monsterId(25,2),{}));land.step({});
    check(land.livingEnemies()==1&&land.enemies[0].monster==monsterId(23,1)&&near(land.enemies[0].hp,166.4f),"Drowned child preserves actual stage health through queued spawning");
    auto rock=fixture(rules);rock.arena.obstacles={{{-2,0,-2},{2,2,2}}};rock.arena.rebuildWalls();
    kill(rock,rock.spawnMonster(monsterId(25,2),{}));rock.step({});check(rock.livingEnemies()==0,"Death above obstacle cannot relocate child onto neighboring ground");
    auto old=fixture(rules);kill(old,old.spawnMonster(monsterId(25),{}));
    p.edit("boom_flies.mechanics","normal 10 100 20 3 0 0","normal 10 150 20 3 1 0");auto changed=p.load();auto fresh=fixture(changed);
    kill(fresh,fresh.spawnMonster(monsterId(25),{}));check(old.stats.explosions==1&&fresh.stats.explosions==0&&fresh.enemyBombs[0].charge.blastDamage==150,
        "File-only blast edits affect fresh snapshot without mutating old one");
    p.extra("stage_health 23.1.0 12 10 3.2\nboom_shots 25.1.0 6 8 10 2 .8 24\n");
    bool rejected=false;try{p.load();}catch(const std::exception&){rejected=true;}check(rejected,"Duplicate variant attack configuration rejected");
    std::cout<<"BOOM_EXTERNAL stage_scaled_child=1 illegal_birth_suppressed=1 immutable_blast_config=1 validation=1\n";
}
void replacementAndRouting() {
    Pack p;
    for(const auto &file:std::filesystem::directory_iterator(p.root))if(file.path().extension()==".mechanics") {
        std::ifstream in(file.path());std::string line,data;while(std::getline(in,line)){std::istringstream row(line);std::string cmd;row>>cmd;if(cmd!="encounter")data+=line+'\n';}
        in.close();std::ofstream(file.path())<<data;
    }
    p.extra("encounter 0 3 any basic 10.1.0 1 1 0\nencounter 0 3 any specialist 25.0.0 1 3 1\n");
    auto s=fixture(p.load());s.arena.profile.band=1;s.arena.profile.patterns={1,0,0,0};s.arena.profile.maxThreat=12;s.arena.profile.areaPerThreat=95;
    s.arena.rooms.resize(10000);for(auto &r:s.arena.rooms){r.kind=RoomKind::Combat;r.floorArea=800;}
    for(const auto variant:{FloorVariant::Standard,FloorVariant::Flooded}) {
        s.arena.profile.variant=variant;int normal=0,red=0,drowned=0;
        for(int room=0;room<10000;++room) {
            const auto plan=s.floorEncounter(room);check(plan.originalMonsters[0]==monsterId(25)&&plan.spent<=plan.budget,"Ordered replacement retains authored slot within reserved threat");
            const auto id=plan.monsters[0];normal+=id==monsterId(25);red+=id==monsterId(25,1);drowned+=id==monsterId(25,2);
        }
        check(normal+red+drowned==10000,"Only configured replacement outcomes occur");
        check(variant==FloorVariant::Standard?(red>850&&red<1050&&drowned==0):(red>390&&red<570&&drowned>4800&&drowned<5200),
            "Two ordered passes retain 9.49% Red and independently replace normal/Red 50% in Flooded Quarry");
        std::cout<<"BOOM_REPLACEMENT flooded="<<(variant==FloorVariant::Flooded)<<" normal="<<normal<<" red="<<red<<" drowned="<<drowned<<" samples=10000\n";
    }
    std::set<MonsterId> found;int floors=0;
    // Retain the original seed0..79 coverage and the independently discovered
    // dry-Quarry Bone Fly witness after adding Host specialists.
    for(uint64_t sample=0;sample<81&&found.size()<7;++sample) {
        const uint64_t seed=sample==0?93:sample-1;
        ExpeditionPlan plan(seed);
        for(int floor=0;floor<plan.floorCount;++floor) {
            Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor);++floors;
            for(int room=0;room<run.arena.roomCount();++room)for(const auto &e:run.roomEnemies(room))if(e.monster.type==25) {
                check(e.monster.variant!=6&&run.arena.profile.band>0,"No Tainted ordinary spawns or opening-band Boom Flies");
                if(e.monster.variant==3||e.monster.variant==4)check(run.arena.profile.band==1&&run.arena.profile.variant==FloorVariant::Standard,"Mines/Ashpit variants have dry Quarry routes");
                if(e.monster.variant==5)check(run.arena.profile.band==3,"Corpse variant stays in Storm Cut");
                check(near(e.maxHp,run.content->monsterHealth(e.monster,run.arena.profile.sourceStage)),"Generated resident uses actual mapped stage health");
                if(found.insert(e.monster).second)std::cout<<"BOOM_RESIDENT id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<" stage="<<run.arena.profile.sourceStage<<" hp="<<e.hp<<'\n';
            }
        }
    }
    check(found.size()==7,"All seven ordinary family identities reached through real generated rooms");
    std::cout<<"BOOM_ROUTING identities="<<found.size()<<" generated_floors="<<floors<<" tainted_dedicated_pending=1\n";
}
}
int main(){try{healthAndMotion();deathPatterns();liveAttacksAndLifecycle();childAndExternal();replacementAndRouting();
    std::cout<<"PASS Boom Fly family behavior, stage health, ordered replacements and natural routing\n";
}catch(const std::exception &e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
