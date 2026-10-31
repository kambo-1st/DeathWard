#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.005f;}
struct Pack {
    std::filesystem::path dir=std::filesystem::temp_directory_path()/("dw-mulligan-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::string original;
    Pack(){std::filesystem::create_directories(dir);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))
        if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
        std::ifstream in(dir/"mulligans.mechanics");original.assign(std::istreambuf_iterator<char>(in),{});}
    ~Pack(){std::filesystem::remove_all(dir);}
    auto load(const std::string &s){std::ofstream(dir/"mulligans.mechanics")<<s;return MechanicsLibrary::load(dir);}
};
std::string replace(std::string s,const std::string &a,const std::string &b){auto pos=s.find(a);check(pos!=s.npos,"fixture directive exists");s.replace(pos,a.size(),b);return s;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-30,-1,-30},{30,8,30}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.floors={{{-30,-.4f,-30},{30,0,30}}};}
    s.arena.boundaryWalls={{{-31,-1,-31},{-30,8,31}},{{30,-1,-31},{31,8,31}},{{-31,-1,-31},{31,8,-30}},{{-31,-1,30},{31,8,31}}};
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.stats={};s.room=0;s.rooms.assign(s.arena.rooms.size(),{});
    s.debugScenario=true;s.roomClear=false;s.player.position={0,.85f,15};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void damage(Simulation &s,EntityId id,float amount){Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;s.queueRoot(e);s.drainEvents();}
void windup() {
    Pack p;auto text=replace(p.original,"evader_detonation 16.0.0 300 29","evader_detonation 16.0.0 1 29");
    text=replace(text,".8 .5 .9 1.079",".8 0 .9 0");auto lib=p.load(text);
    auto s=fixture(lib);auto id=s.spawnMonster(monsterId(16),{29.39f,.85f,0});s.findEnemy(id)->velocity={10,0,0};
    for(int i=0;i<12&&(!s.findEnemy(id)->evader||s.findEnemy(id)->evader->detonationFrame<0);++i)tick(s);
    auto *e=s.findEnemy(id);check(e&&e->evader&&e->evader->detonationFrame==0,"actual terrain collision starts reviewed random detonation");
    tick(s,57);check(s.findEnemy(id)&&s.findEnemy(id)->alive&&s.stats.projectiles==0,"29-frame animation has not ended at28.5frames");
    tick(s);check(s.stats.kills==1&&s.stats.projectiles==4&&s.stats.explosions==1,"animation completion emits one cardinal burst and real blast");
    check(s.livingEnemies()==4,"voluntary death preserves four ordinary offspring");
    auto calm=fixture(lib);id=calm.spawnMonster(monsterId(16),{0,.85f,0});calm.findEnemy(id)->age=100;
    tick(calm,240);check(calm.findEnemy(id)&&calm.findEnemy(id)->alive&&calm.stats.explosions==0,"age/proximity without grid collision cannot arm explosion");
    auto interrupted=fixture(lib);id=interrupted.spawnMonster(monsterId(16),{29.39f,.85f,0});interrupted.findEnemy(id)->velocity={10,0,0};
    for(int i=0;i<12&&(!interrupted.findEnemy(id)->evader||interrupted.findEnemy(id)->evader->detonationFrame<0);++i)tick(interrupted);
    damage(interrupted,id,interrupted.findEnemy(id)->hp);tick(interrupted,80);
    check(interrupted.stats.projectiles==0&&interrupted.stats.explosions==0&&interrupted.stats.kills==1,"death during windup cancels voluntary blast");
    check(defaultMechanics()->evader(monsterId(16))->detonationChance==300,"production chance is one in300grid-collision updates");
    std::cout<<"PASS grid-triggered detonation,29-frame windup, ordinary death interruption and no fixed-age trigger\n";
}
void deaths() {
    int fly=0,attack=0,pooter=0;auto s=fixture();s.player.position={25,.85f,25};
    for(int i=0;i<300;++i) {
        s.killAll();s.stats={};s.roomClear=false;auto id=s.spawnMonster(monsterId(16),{0,.85f,0});
        check(near(s.findEnemy(id)->hp,41.6f),"source13HPx3.2");damage(s,id,s.findEnemy(id)->hp);tick(s);
        check(s.livingEnemies()==4&&s.stats.projectiles==0&&s.stats.explosions==0,"normal death gives four children without a blast");
        for(const auto &c:s.enemies)if(c.alive) {
            if(c.monster==monsterId(13))++fly;else if(c.monster==monsterId(18)){++attack;check(!c.buzz||!c.buzz->diesOnContact,"death fly is persistent");}
            else {check(c.monster==monsterId(14),"only source child identities");++pooter;}
        }
    }
    check(fly>650&&fly<870&&attack>260&&attack<390&&pooter>65&&pooter<155,"independent7:3:1offspring mixture");
    for(float overkill:{31.f,32.f}) {
        auto b=fixture();auto id=b.spawnMonster(monsterId(16),{0,.85f,0});damage(b,id,b.findEnemy(id)->hp+overkill);tick(b);
        check(b.livingEnemies()==(overkill<32?4u:0u),"source-10overkill uses inclusive scaled-32threshold");
    }
    auto crowded=fixture();auto id=crowded.spawnMonster(monsterId(16),{0,.85f,0});
    for(int i=0;i<8;++i)crowded.spawnMonster(monsterId(12),{float(i*3-12),.85f,-15});
    damage(crowded,id,crowded.findEnemy(id)->hp);tick(crowded);check(crowded.livingEnemies()==12,"Mulligan offspring count is not Hive population-scaled");
    std::cout<<"PASS four independent death draws, scaled overkill, persistent flies and crowd-independent count\n";
}
void goonAndCapacity() {
    std::set<int> fuses;
    for(bool voluntary:{false,true}) {
        auto s=fixture();s.debugScenario=false;auto id=s.spawnMonster(monsterId(16,1),{0,.85f,0});s.findEnemy(id)->selfDetonated=voluntary;
        s.limits.projectiles=3;damage(s,id,s.findEnemy(id)->hp);tick(s);
        check(s.enemyBombs.empty()&&s.projectiles.empty()&&s.stats.explosions==0&&s.findEnemy(id)&&s.findEnemy(id)->deathBlastPending&&!s.roomClear,
            "death payload waits atomically at projectile capacity and keeps completion pending");
        s.limits.projectiles=8;tick(s,2); // Retained events are admitted, then drained next tick.
        std::cout<<"PAYLOAD voluntary="<<voluntary<<" bombs="<<s.enemyBombs.size()<<" shots="<<s.stats.projectiles<<" explosions="<<s.stats.explosions<<'\n';
        check(s.enemyBombs.size()==1&&s.stats.projectiles==(voluntary?8u:4u)&&s.stats.explosions==(voluntary?1u:0u),"whole death ring/bomb and optional self blast resume once");
        check(s.roomClear,"completion resumes after retained death payload is admitted");
        const auto &bomb=s.enemyBombs.front();check(bomb.ordnance==monsterId(4,3)&&bomb.source==id&&near(bomb.charge.blastDamage,320)&&near(bomb.charge.radius,7.5f),"real configured Troll Bomb retains producer after death");
        check(bomb.charge.delay>=1.5f&&bomb.charge.delay<=74.f/30+.001f,"source-initialized Troll fuse range");
        for(const auto &shot:s.projectiles)check(near(length(shot.velocity),21)&&shot.context.sourceEntity==id,"source-speed owned death shots");
        tick(s,180);check(s.stats.explosions==(voluntary?2u:1u)&&s.enemyBombs.empty(),"Troll Bomb survives room clear and explodes exactly once");
    }
    auto s=fixture();s.player.position={25,.85f,25};
    for(int i=0;i<160;++i) {
        s.killAll();auto id=s.spawnMonster(monsterId(16,1),{0,.85f,0});damage(s,id,s.findEnemy(id)->hp);tick(s);
        fuses.insert(int(std::lround(s.enemyBombs.back().charge.delay*30)));
    }
    check(fuses.size()>=27&&*fuses.begin()==45&&*fuses.rbegin()==74,"seeded Troll fuse uses inclusive integer45..74range");
    auto blocked=fixture();auto id=blocked.spawnMonster(monsterId(16,1),{0,.85f,0});blocked.limits.enemyBombs=blocked.limits.pendingEnemyBombs=0;
    damage(blocked,id,1000);tick(blocked);check(blocked.projectiles.empty()&&blocked.findEnemy(id)->deathBlastPending,"full bomb capacity does not leak death shots");
    blocked.limits.enemyBombs=1;tick(blocked,2);check(blocked.enemyBombs.size()==1&&blocked.stats.projectiles==4,"bomb capacity recovery admits one complete payload");
    std::cout<<"PASS Mulligoon4/8shot rings, real randomized Troll Bomb and atomic capacity retry\n";
}
void boom() {
    for(bool shot:{false,true}) {
        auto s=fixture();s.player.position={0,.85f,3.5f};auto id=s.spawnMonster(monsterId(16,2),{0,.85f,0});
        if(shot)damage(s,id,s.findEnemy(id)->hp);
        else {tick(s,8);check(s.findEnemy(id)&&s.findEnemy(id)->alive,"proximity is sampled every five source frames");}
        tick(s,2);check(s.stats.kills==1&&s.stats.explosions==1&&s.enemyBombs.empty()&&s.stats.projectiles==0,"Mulliboom immediate blast has no delayed Troll fuse or contact shot");
        check(near(s.player.hp,StartingHealth-10*EnemyDamageMultiplier),"one half-heart-converted blast hit, no contact double damage");
    }
    auto s=fixture();s.player.position={0,.85f,20};auto id=s.spawnMonster(monsterId(16,2),{0,.85f,0});tick(s,60);
    check(s.findEnemy(id)&&s.findEnemy(id)->position.z>4,"source-based pursuit moves rapidly toward target");
    auto clear=fixture();id=clear.spawnMonster(monsterId(16,1),{0,.85f,0});clear.killAll();tick(clear,100);
    check(clear.enemyBombs.empty()&&clear.projectiles.empty()&&clear.stats.explosions==0,"debug clear emits no payload");
    std::cout<<"PASS source5-frame proximity, immediate blast, half-heart conversion and fast pursuit\n";
}
void blastWorld() {
    auto s=fixture();s.player.position={25,.85f,25};
    Breakable rock;rock.id=1;rock.kind=BreakableKind::CrackedRock;rock.health=1;rock.room=0;
    rock.bounds={{2,0,-.4f},{2.8f,1,.4f}};rock.rewardPosition={2.4f,.85f,0};rock.lootSeed=321;
    s.arena.breakables={rock};s.arena.rebuildWalls();
    const auto victim=s.spawnMonster(monsterId(12),{0,.85f,-2});
    s.findEnemy(victim)->hp=s.findEnemy(victim)->maxHp=500;
    const auto boom=s.spawnMonster(monsterId(16,2),{0,.85f,0});damage(s,boom,42);tick(s);
    check(near(s.findEnemy(victim)->hp,372),"Mulliboom source40x3.2blast damages a nearby enemy");
    check(s.arena.breakables[0].destroyed&&!s.arena.blocked({2.4f,.85f,0},.3f),"real death blast destroys rock and clears collision");
    const auto kills=s.stats.kills;tick(s,60);check(s.stats.explosions==1&&s.stats.kills==kills,"death blast cannot repeat after producer removal");
    std::cout<<"PASS real death blast affects neighboring enemy and destructible terrain once\n";
}
void configAndReachability() {
    Pack p;const auto before=p.load(p.original);
    const auto after=p.load(replace(p.original,"evader_detonation 16.0.0 300 29","evader_detonation 16.0.0 150 29"));
    check(before->evader(monsterId(16))->detonationChance==300&&after->evader(monsterId(16))->detonationChance==150&&before->fingerprint()!=after->fingerprint(),"immutable external controller snapshots");
    for(const auto &bad:{replace(p.original,"300 29","0 29"),replace(p.original,"self 4 8","self 40 8"),replace(p.original,"10 mulligoon_troll","10 missing_bomb")}) {
        bool failed=false;try{p.load(bad);}catch(const std::exception &){failed=true;}check(failed,"invalid detonation/death config rejected");
    }
    FloorProfile floor;floor.band=0;
    for(auto from:{monsterId(16),monsterId(16,1)}) {
        const auto *rule=before->replacement(from,floor,1);
        check(rule&&rule->target==monsterId(16,2)&&rule->chance==100,"both first-floor parents retain one-percent Mulliboom replacement");
    }
    std::set<MonsterId> found;
    // Adding eligible specialists changes weighted draws. Search actual seeded
    // first floors instead of pinning five witnesses to an older roster.
    // Mulligoon must still occur through its real replacement route.
    for(uint64_t seed=0;seed<1024&&!(found.contains(monsterId(16))&&found.contains(monsterId(16,1)));++seed) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,0);
        for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster.type==16&&found.insert(e.monster).second)
            std::cout<<"NATURAL_MULLIGAN id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor=0 room="<<room<<'\n';
    }
    // Search the current weighted production roster, including rare substitutions.
    for(uint64_t seed=0;seed<1024&&!found.contains(monsterId(16,2));++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);int floor=0;while(plan.profileOnFloor(floor).band<1)++floor;
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(16,2)&&found.insert(e.monster).second)
            std::cout<<"NATURAL_MULLIGAN id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
    }
    check(found.size()==3,"all three regular variants naturally reachable through production source/replacement pools");
    std::cout<<"PASS validated snapshots and seeded Mulligan family\n";
}
}
int main(){try{windup();deaths();goonAndCapacity();boom();blastWorld();configAndReachability();std::cout<<"PASS Mulligan family\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
