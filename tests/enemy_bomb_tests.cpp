#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool value,const char *message){if(!value)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.002f;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic,lib);
    s.arena=Arena{};s.arena.bounds={{-25,-1,-25},{200,12,25}};
    for(size_t i=0;i<s.arena.rooms.size();++i) {
        const float x=float(i)*60;auto &r=s.arena.rooms[i];
        r.bounds={{x-25,-1,-25},{x+25,12,25}};r.center={x,.85f,0};r.kind=RoomKind::Combat;
    }
    s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.enemyBombs.clear();s.pendingEnemyBombs.clear();s.stats={};
    for(auto &r:s.rooms){r.residents.clear();r.segmented.clear();r.cleared=false;r.plates.clear();}
    s.player.position={20,.85f,20};s.godMode=true;s.debugScenario=true;s.roomClear=s.bossKilled=false;return s;
}
EntityId owner(Simulation &s,Vector3 p={-15,.85f,-15}) {
    const auto id=s.spawnMonster(monsterId(69),p);check(id!=0,"Fixture owner exists");s.findEnemy(id)->cooldown=1000;return id;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void damage(Simulation &s,EntityId id,float amount) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.execution=true;s.queueRoot(e);s.drainEvents();
}
void blastAndThrow() {
    auto s=fixture();const auto root=owner(s,{0,.85f,0});const auto victim=s.spawnMonster(monsterId(14),{1.5f,.85f,0});
    s.findEnemy(victim)->hp=500;s.findEnemy(victim)->cooldown=1000;
    const auto bomb=s.throwEnemyBomb("normal",root,{0,.18f,0},{},true);
    check(bomb&&s.enemyBombs[0].source==root&&s.enemyBombs[0].ordnance==monsterId(4,3),"Actual source and ordnance identities retained");
    tick(s,89);check(s.stats.explosions==0,"Fuse does not explode early");tick(s,3);
    check(s.stats.explosions==1&&s.enemyBombs.empty(),"One accepted explosion retires normal bomb");
    check(near(s.findEnemy(root)->hp,1120)&&near(s.findEnemy(victim)->hp,400),"Declared producer immunity does not suppress collateral blast damage");
    auto thrown=fixture();const auto producer=owner(thrown);thrown.arena.obstacles={{{-1,0,-3},{1,4,3}}};thrown.arena.rebuildWalls();
    check(thrown.throwEnemyBomb("normal",producer,{-8,1,0},{8,.18f,0})!=0,"Throw uses a real ballistic charge");
    float peak=0;for(int n=0;n<92;++n){tick(thrown);for(const auto &b:thrown.enemyBombs){peak=std::max(peak,b.charge.position.y);check(b.charge.position.x<1,"Tall cover stops the actual thrown bomb");}}
    check(peak>1.1f&&thrown.stats.explosions==1,"Bomb rises and detonates once after terrain collision");
    std::cout<<"ENEMY_BOMB_BLAST source=1 collateral=100 exactly_once=1 ballistic_cover=1\n";
}
void nativeIdentities() {
    auto s=fixture();const auto producer=owner(s);
    const std::array<std::pair<std::string_view,int>,5> variants{{{"normal",3},{"hornfel_normal",0},{"hot",8},{"sad",16},{"brimstone",15}}};
    for(size_t i=0;i<variants.size();++i) {
        const auto &[key,variant]=variants[i];
        const auto id=s.throwEnemyBomb(key,producer,{float(i)*3,.18f,0},{},true);
        check(id&&s.enemyBombs.back().ordnance==monsterId(4,variant),"Native Hornfel bomb identity preserved separately from Troll Bombs");
        check(s.enemyBombs.back().source==producer,"Source NPC not replaced by ordnance identity");
    }
    std::cout<<"ORDNANCE_IDENTITIES troll=4.3 hornfel_normal=4.0 hot=4.8 bloody_sad=4.16 brimstone=4.15\n";
}
void sadAndLimits() {
    auto s=fixture();const auto root=owner(s);const auto bomb=s.throwEnemyBomb("sad",root,{0,.18f,0},{},true);
    s.grant(ItemId::Judas);s.grant(ItemId::Scatter);s.grant(ItemId::Rail);
    s.limits.queuedEvents=10;tick(s,100);
    check(s.stats.explosions==0&&s.stats.projectiles==0&&s.enemyBombs.size()==1,"Insufficient event capacity retains complete blast/ring");
    s.limits.queuedEvents=64;s.limits.projectiles=9;tick(s,2);
    check(s.stats.explosions==0&&s.projectiles.empty(),"Projectile capacity also preserves the complete ring");
    s.limits.projectiles=64;tick(s);
    check(s.stats.explosions==1&&s.stats.projectiles==10&&s.projectiles.size()==10&&s.enemyBombs.empty(),"Recovery emits ten shots and one blast once");
    std::vector<float> angles;
    for(const auto &p:s.projectiles) {
        check(p.hostile&&p.context.sourceEntity==bomb&&near(p.damage,10)&&near(length(p.velocity),8),"Hostile ring uses configured damage/speed and ordnance attribution");
        angles.push_back(std::atan2(p.velocity.z,p.velocity.x));
    }
    std::sort(angles.begin(),angles.end());for(size_t i=1;i<angles.size();++i)check(near(angles[i]-angles[i-1],2*Pi/10),"Ten evenly spaced ring bearings");
    tick(s,10);check(s.stats.explosions==1&&s.stats.projectiles==10,"No duplicate after queue recovery");
    auto cap=fixture();const auto producer=owner(cap);cap.limits.enemyBombs=1;cap.limits.pendingEnemyBombs=1;
    check(cap.throwEnemyBomb("normal",producer,{0,.18f,0},{},true)&&cap.throwEnemyBomb("normal",producer,{5,.18f,0},{},true),"Active and pending capacities accept two bombs");
    check(!cap.throwEnemyBomb("normal",producer,{10,.18f,0},{},true),"Overflow fails visibly to producer without unbounded storage");
    tick(cap,190);check(cap.stats.explosions==2&&cap.enemyBombs.empty()&&cap.pendingEnemyBombs.empty(),"Pending fuse starts when admitted and drains");
    std::cout<<"ENEMY_BOMB_SAD ring=10 independent_damage=1 bounded_queues=1 atomic_backpressure=1\n";
}
void hotAndPersistence() {
    auto s=fixture();const auto root=owner(s);s.godMode=false;s.player.position={0,.85f,0};
    s.throwEnemyBomb("hot",root,{0,.18f,0},{},true);tick(s);
    check(near(s.player.hp,87.5f),"Armed Hot bomb contact deals hostile damage");s.player.position={20,.85f,20};
    tick(s,91);check(s.enemyBombs.size()==1&&s.enemyBombs[0].detonated&&s.enemyBombs[0].effectAge>0,"Hot detonation creates persistent flame");
    damage(s,root,10000);s.clearRoom();
    check(s.enemyBombs.size()==1&&s.enemyBombs[0].detonated,"Owner death and room clear preserve actual lingering flame");
    s.player.hp=100;s.player.hurt=0;s.player.position={0,.85f,0};tick(s);
    check(near(s.player.hp,87.5f),"Remaining fire damages player after owner/room cleanup");
    const auto age=s.enemyBombs[0].effectAge;s.enterRoom(1);s.player.position={60,.85f,0};tick(s,120);
    check(s.enemyBombs[0].effectAge==age,"Inactive room pauses active payload lifetime");
    s.enterRoom(0);s.player.position={20,.85f,20};tick(s,610);
    check(s.enemyBombs.empty()&&s.stats.explosions==1,"Returned flame expires without repeating its explosion");
    std::cout<<"ENEMY_BOMB_HOT contact=1 lingering_fire=1 owner_independent=1 clear_survival=1 dormant_pause=1\n";
}
void brimstone() {
    for(bool blocked:{false,true}) {
        auto s=fixture();const auto root=owner(s);s.godMode=false;s.player.position={0,.85f,6};
        if(blocked){s.arena.obstacles={{{-2,0,2},{2,4,3}}};s.arena.rebuildWalls();}
        s.throwEnemyBomb("brimstone",root,{0,.18f,0},{},true);tick(s,90);
        check(s.stats.explosions==1&&s.enemyBombs.size()==1&&s.enemyBombs[0].detonated,"Brimstone leaves active beam payload");
        check(near(s.player.hp,blocked?100:87.5f),"Cardinal beam hits unblocked player beyond blast radius and respects cover");
        const auto &b=s.enemyBombs[0];check(b.beamEnds.size()==4,"Four cardinal rays");
        for(auto end:b.beamEnds){auto d=sub(end,add(b.charge.position,{0,.67f,0}));check(std::min(std::abs(d.x),std::abs(d.z))<.001f,"Beam axes remain cardinal");}
        if(!blocked){s.player.position={0,.85f,0};s.player.hp=100;s.player.hurt=0;tick(s);check(near(s.player.hp,87.5f),"Four overlapping beams share player hurt cooldown");}
        tick(s,60);check(s.enemyBombs.empty(),"Finite beam lifetime retires payload");
    }
    std::cout<<"ENEMY_BOMB_BRIMSTONE cardinal=4 clipped_by_cover=1 shared_hurt_cooldown=1 finite_lifetime=1\n";
}
void companions() {
    for(const std::string profile:{"hot","brimstone"}) {
        auto s=fixture();const auto root=owner(s);s.throwEnemyBomb(profile,root,{0,.18f,0},{},true);
        tick(s,profile=="hot"?92:74);
        const auto id=s.spawnMonster(monsterId(23,0,1),{0,.85f,profile=="hot"?0.f:5.f});
        auto *ally=s.findEnemy(id);ally->state=EnemyState::Stunned;ally->stateTime=100;
        tick(s);check(near(s.findEnemy(id)->hp,60.8f),"Typed hostile aftermath reaches allies once through their shared hurt window");
        check(s.stats.kills==0&&s.stats.damageDealt==0,"Ally hazard damage grants no enemy kill or player damage credit");
    }
    std::cout<<"ENEMY_BOMB_ALLIES hostile_fire=1 hostile_beam=1 shared_hurt_window=1 no_player_credit=1\n";
}
struct Pack {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("deathward-ordnance-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))
        if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(path);}
};
void configuration() {
    Pack p;std::ofstream(p.path/"enemy_bombs.mechanics",std::ios::app)<<"enemy_bomb fast 4.3.0 blast .2 3 17 10 .7 14 1\n";
    const auto fresh=MechanicsLibrary::load(p.path);auto s=fixture(fresh);const auto id=owner(s,{0,.85f,0});
    check(!defaultMechanics()->enemyBomb("fast")&&fresh->enemyBomb("fast"),"New content snapshot does not mutate an existing run");
    s.throwEnemyBomb("fast",id,{0,.18f,0},{},true);tick(s,14);
    check(s.stats.explosions==1&&near(s.findEnemy(id)->hp,1103),"External fuse, damage and source vulnerability take effect");
    std::ofstream(p.path/"enemy_bombs.mechanics",std::ios::app)<<"enemy_bomb missing 4.7.0 sad 1 3 100 20 .7 14 0\n";
    bool rejected=false;try{MechanicsLibrary::load(p.path);}catch(const std::exception &e){rejected=std::string(e.what()).find("requires its effect")!=std::string::npos;}
    check(rejected,"Incomplete payload profile rejected transactionally");
    auto a=fixture();const auto source=owner(a);
    check(!a.throwEnemyBomb("absent",source,{0,.18f,0},{},true)&&!a.throwEnemyBomb("hot",0,{0,.18f,0},{},true),"Unknown profiles and missing producers fail");
    a.findEnemy(source)->friendly=true;check(!a.throwEnemyBomb("hot",source,{0,.18f,0},{},true),"Allied producers cannot silently emit hostile payloads");
    std::cout<<"ENEMY_BOMB_CONTENT snapshot=1 configurable_damage_fuse_faction=1 missing_effect_rejected=1 invalid_producer_rejected=1\n";
}
}
int main(){try{blastAndThrow();nativeIdentities();sadAndLimits();hotAndPersistence();brimstone();companions();configuration();std::cout<<"PASS hostile bomb payload foundation; boss producers remain missing\n";}
catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
