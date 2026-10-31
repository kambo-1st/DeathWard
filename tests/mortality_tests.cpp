#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *m){if(!b)throw std::runtime_error(m);}
bool near(float a,float b){return std::abs(a-b)<.003f;}
struct Pack {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-mortality-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(path);}
    void replace(const std::string &from,const std::string &to,const char *file="gurgle.mechanics"){const auto p=path/file;std::ifstream in(p);std::string s((std::istreambuf_iterator<char>(in)),{});auto n=s.find(from);check(n!=std::string::npos,"fixture row exists");s.replace(n,from.size(),to);std::ofstream(p)<<s;}
    auto certain(){replace("1500 80","10000 80");return MechanicsLibrary::load(path);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,content);
    s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();s.stats={};s.arena=Arena{};
    s.arena.bounds={{-30,-1,-30},{30,8,30}};s.arena.rooms.resize(2);
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;}
    s.rooms.assign(2,{});s.room=0;s.arena.profile.sourceStage=3;s.godMode=true;s.debugScenario=true;
    s.roomClear=false;s.player.position={20,.85f,20};return s;
}
void hit(Simulation &s,EntityId id,float amount,DamageSource source=DamageSource::Player,bool explosion=false,DamageKind kind=DamageKind::Physical,bool execution=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.damageKind=kind;e.explosionDamage=explosion;
    e.execution=execution;e.context.damageSource=source;s.queueRoot(e);s.drainEvents();
}
void immunity() {
    for(auto id:{monsterId(87),monsterId(87,1),monsterId(238)}) {
        auto s=fixture();const auto actor=s.spawnMonster(id,{0,.85f,0});const float hp=s.findEnemy(actor)->hp;
        hit(s,actor,10,DamageSource::Enemy,true);hit(s,actor,10,DamageSource::Environment,true);
        check(near(s.findEnemy(actor)->hp,hp),"non-player explosions resisted");
        for(auto source:{DamageSource::Player,DamageSource::Ally,DamageSource::Tnt})hit(s,actor,1,source,true);
        check(near(s.findEnemy(actor)->hp,hp-3),"player, ally, and TNT bypass blast immunity");
        hit(s,actor,2,DamageSource::Enemy,false,DamageKind::Flame);
        const float after=hp-3-(id.type==238?2:0);
        check(near(s.findEnemy(actor)->hp,after),"Splasher alone remains vulnerable to enemy flame");
        hit(s,actor,1,DamageSource::Enemy,false,DamageKind::Burning);
        hit(s,actor,1,DamageSource::Enemy);
        check(near(s.findEnemy(actor)->hp,after-2),"burning status and physical damage are not fire immunity");
        hit(s,actor,999,DamageSource::Enemy,true,DamageKind::Flame,true);
        check(!s.findEnemy(actor)->alive,"execution bypasses resistance and morph");
    }
    std::cout<<"SOURCE_IMMUNITY channels=1 exceptions=1 execution=1\n";
}
void sourceLifetime() {
    for(bool friendly:{false,true}) {
        auto s=fixture();const auto victim=s.spawnMonster(monsterId(87),{0,.85f,0});
        const auto producer=s.spawnMonster(monsterId(10),{4,.85f,0});s.findEnemy(producer)->friendly=friendly;
        Event shot;shot.hostile=true;shot.context.sourceEntity=producer;shot.position=shot.origin={4,2,0};
        shot.direction={1,0,0};shot.damage=0;s.queueRoot(shot);s.drainEvents();
        check(s.projectiles.size()==1,"source probe projectile exists");const auto context=s.projectiles.back().context;
        check(context.damageSource==(friendly?DamageSource::Ally:DamageSource::Enemy),"producer captured at launch");
        std::erase_if(s.enemies,[&](const auto &e){return e.id==producer;});
        Event blast;blast.type=EventType::Explosion;blast.position=blast.origin={0,.85f,0};blast.radius=2;blast.damage=5;
        blast.context=context;s.queueRoot(blast);s.drainEvents();
        check(near(s.findEnemy(victim)->hp,friendly?123:128),"attribution survives producer removal and new root chain");
    }
    auto s=fixture();const auto victim=s.spawnMonster(monsterId(87),{0,.85f,0});
    const auto tnt=s.spawnMonster(monsterId(292),{1,.85f,0});check(tnt!=0,"TNT exists");
    Event blast;blast.type=EventType::Explosion;blast.context.sourceEntity=tnt;blast.position=blast.origin={0,.85f,0};blast.damage=5;blast.radius=2;
    blast.explosionIgnore=tnt;s.queueRoot(blast);s.drainEvents();check(near(s.findEnemy(victim)->hp,123),"real TNT producer is exempt");
    hit(s,tnt,10,DamageSource::Player,true);s.drainEvents();check(!s.findEnemy(victim)->alive,"live TNT detonation bypasses immunity");
    auto fire=fixture();const auto g=fire.spawnMonster(monsterId(87),{0,.85f,0});
    fire.addFire({0,.85f,0},1,2,10,true,false);fire.step({});
    check(near(fire.findEnemy(g)->hp,128),"unowned environment fire is not incorrectly attributed to the player");
    fire.hazards.clear();fire.findEnemy(g)->fireContactCooldown=0;
    Context playerFire;playerFire.damageSource=DamageSource::Player;
    fire.addFire(fire.findEnemy(g)->position,1,2,10,true,false,playerFire);fire.step({});
    check(near(fire.findEnemy(g)->hp,118),"explicit player fire remains exempt through hazard creation");
    std::cout<<"SOURCE_LIFETIME dead_producer=1 allied_source=1 tnt=1\n";
}
void morph() {
    Pack pack;auto lib=pack.certain();auto s=fixture(lib);const auto id=s.spawnMonster(monsterId(87),{0,.85f,0});
    auto *e=s.findEnemy(id);e->summoner=1234;e->hp=e->maxHp=256;e->state=EnemyState::Windup;
    const auto at=e->position;const auto money=s.moneyPickups.size();s.limits.enemies=1;
    hit(s,id,257);e=s.findEnemy(id);
    check(e&&e->alive&&e->id==id&&e->monster==monsterId(238)&&e->summoner==1234,"lethal morph preserves identity and owner at full capacity");
    check(near(e->hp,102.4f)&&near(e->maxHp,102.4f),"full target stage health preserves scale");
    check(near(e->radius,.65f)&&distance(e->position,at)<.001f,"collision and placement retained");
    check(e->cooldown>=20.f/30&&e->cooldown<=39.f/30&&near(e->cooldown*30,std::round(e->cooldown*30)),"integral source delay20..39");
    check(s.stats.kills==0&&s.moneyPickups.size()==money&&s.roomThreats()==1&&!s.roomClear,"morph gives no kill reward or room-clear gap");
    s.enterRoom(1);s.enterRoom(0);e=s.findEnemy(id);
    check(e&&e->monster==monsterId(238)&&near(e->hp,102.4f),"morph survives room re-entry");
    hit(s,id,200);check(s.stats.kills==1&&!s.findEnemy(id)->alive,"final body dies exactly once");
    for(float extra:{79.99f,80.f,80.01f}) {
        auto b=fixture(lib);const auto g=b.spawnMonster(monsterId(87),{0,.85f,0});hit(b,g,128+extra);
        check(b.findEnemy(g)->alive==(extra<80),"strict residual-health overkill threshold");
    }
    auto b=fixture(lib);const auto g=b.spawnMonster(monsterId(87),{0,.85f,0});b.findEnemy(g)->hp=b.findEnemy(g)->maxHp=256;
    hit(b,g,336);check(!b.findEnemy(g)->alive,"overkill cutoff does not scale with champion health");
    auto crackle=fixture(lib);const auto c=crackle.spawnMonster(monsterId(87,1),{0,.85f,0});hit(crackle,c,129);
    check(!crackle.findEnemy(c)->alive&&crackle.stats.kills==1,"Crackle never morphs");
    std::cout<<"LETHAL_MORPH same_id=1 stage_hp=1 capacity=1 no_reward=1 reentry=1 overkill=1\n";
}
void chanceAndConfig() {
    auto run=[] {
        auto s=fixture();s.combatRng=Random(845);int count=0;
        for(int i=0;i<1000;++i){s.enemies.clear();const auto id=s.spawnMonster(monsterId(87),{0,.85f,0});hit(s,id,129);count+=s.findEnemy(id)->alive;}
        return count;
    };
    const int n=run();check(n==run()&&n>110&&n<190,"15 percent deterministic seeded morph, not old50 percent offspring");
    const auto original=defaultMechanics()->fingerprint();
    for(const auto &row:{"source_immunity 87.0.0 1 1\n","source_immunity 9999.0.0 1 1\n","lethal_morph 238.0.0 87.0.0 1500 80 0 1\n","lethal_morph 87.1.0 10.0.0 1500 80 0 1\n"}) {
        Pack p;std::ofstream(p.path/"gurgle.mechanics",std::ios::app)<<row;bool rejected=false;
        try{MechanicsLibrary::load(p.path);}catch(const std::exception &){rejected=true;}
        check(rejected,"invalid or incompatible external mortality rule rejected atomically");
    }
    check(defaultMechanics()->fingerprint()==original,"failed config leaves live library unchanged");
    std::cout<<"LETHAL_CHANCE transformed="<<n<<" trials=1000 seeded=1 config=1\n";
}
unsigned morphSeed(unsigned choice) {
    for(unsigned seed=0;seed<10000;++seed){Random r(seed);if(r.bounded(2)==0&&r.bounded(3)==choice)return seed;}
    throw std::runtime_error("no deterministic morph witness");
}
void gaperMorph() {
    for(int variant:{0,1,2})for(unsigned choice:{0u,1u,2u}) {
        auto s=fixture();const auto id=s.spawnMonster(monsterId(10,variant),{0,.85f,0});
        auto *e=s.findEnemy(id);const float base=e->hp;
        e->hp=e->maxHp=base*2;e->velocity={3,0,-6};e->age=7.2f;
        e->summoner=1234;e->spawnerType=906;e->state=EnemyState::Windup;e->path={{5,.85f,5}};
        s.limits.enemies=1;s.limits.projectiles=0;
        const unsigned seed=morphSeed(choice);s.combatRng=Random(seed);Random expected(seed);
        expected.bounded(2);expected.bounded(3);const int timer=20+int(expected.bounded(20));
        hit(s,id,e->hp+1);e=s.findEnemy(id);
        const int child=(choice==0&&variant!=2)?1:0;
        check(e&&e->alive&&e->id==id&&e->monster==monsterId(11,child),"Gaper source weighted morph keeps original entity at capacity");
        check(e->summoner==1234&&e->spawnerType==906&&near(e->hp,64)&&near(e->maxHp,64),"Gaper ownership and health multiplier survive morph");
        check(distance(e->velocity,{3,0,-6})<.001f&&distance(e->position,{0,.85f,0})<.001f&&near(e->radius,.6f),"Gaper momentum and body placement survive");
        check(e->state==EnemyState::Ready&&e->headless&&e->headless->initialized&&e->headless->cooldown==timer&&e->path.empty(),"morphed headless body resumes initialized with source timer");
        check(s.combatRng.state==expected.state,"success consumes chance, modulo-three choice (including Flaming), then delay exactly once");
        check(s.stats.kills==0&&s.moneyPickups.empty()&&s.roomThreats()==1&&!s.roomClear,"decapitation gives no kill, loot or room-clear gap");
        s.step({},1.f/30);e=s.findEnemy(id);
        check(e&&e->headless->initialized&&e->headless->cooldown==(child==0?timer-1:timer)&&e->headless->shots==0,"first morphed update does not redraw spawn timer or fire early");
        s.enterRoom(1);s.enterRoom(0);e=s.findEnemy(id);
        check(e&&e->alive&&e->headless&&e->monster==monsterId(11,child),"same-entity morph survives room re-entry");
        hit(s,id,e->hp+1);check(!s.findEnemy(id)->alive&&s.stats.kills==1,"only final headless death awards the kill");
    }
    for(int variant:{0,1,2})for(float overkill:{79.99f,80.f,80.01f}) {
        auto s=fixture();const auto id=s.spawnMonster(monsterId(10,variant),{0,.85f,0});
        s.combatRng=Random(morphSeed(0));const float hp=s.findEnemy(id)->hp;
        hit(s,id,hp+overkill);check(s.findEnemy(id)->alive==(overkill<80),"Gaper strict native -25 overkill converted at x3.2");
    }
    for(int variant:{0,1,2}) {
        auto s=fixture();int dead=0,pacer=0,gusher=0;s.combatRng=Random(845);
        for(int n=0;n<1200;++n) {
            s.enemies.clear();s.moneyPickups.clear();const auto id=s.spawnMonster(monsterId(10,variant),{0,.85f,0});
            hit(s,id,s.findEnemy(id)->hp);const auto &e=*s.findEnemy(id);
            if(!e.alive)++dead;else if(e.monster==monsterId(11,1))++pacer;else if(e.monster==monsterId(11))++gusher;
            else check(false,"unexpected Gaper morph outcome");
        }
        check(dead>500&&dead<700,"source half probability retains real deaths");
        check(variant==2?(pacer==0&&gusher>500):(pacer>140&&pacer<260&&gusher>310&&gusher<490),"source Gusher/Pacer weights and Flaming Gusher-only outcome");
        std::cout<<"GAPER_DISTRIBUTION variant="<<variant<<" dead="<<dead<<" pacer="<<pacer<<" gusher="<<gusher<<" trials=1200\n";
        s.enemies.clear();const auto id=s.spawnMonster(monsterId(10,variant),{0,.85f,0});s.combatRng=Random(morphSeed(0));
        hit(s,id,999,DamageSource::Player,false,DamageKind::Physical,true);
        check(!s.findEnemy(id)->alive&&s.findEnemy(id)->monster.type==10,"execution does not transform Gaper");
    }
    std::cout<<"GAPER_MORPH same_entity=1 ownership=1 capacity=1 momentum=1 timer=1 source_draws=1 no_reward=1 reentry=1 overkill=1 execution=1\n";
}
void morphChoiceConfig() {
    const auto original=defaultMechanics()->fingerprint();
    for(const auto &row:{"lethal_morph_roll 10.1.0 1 2\n","lethal_morph_choice 10.1.0 11.0.0 1\n",
            "lethal_morph_choice 10.1.0 10.1.0 1\n","lethal_morph_choice 10.1.0 9999.0.0 1\n",
            "lethal_morph_choice 10.1.0 238.0.0 1\n","lethal_morph_choice 9999.0.0 11.0.0 1\n",
            "lethal_morph_choice 10.1.0 14.0.0 0\n","lethal_morph_choice 10.1.0 14.0.0 8001\n"}) {
        Pack p;std::ofstream(p.path/"deaths.mechanics",std::ios::app)<<row;bool rejected=false;
        try{MechanicsLibrary::load(p.path);}catch(const std::exception &){rejected=true;}
        check(rejected,"invalid weighted morph rule rejected atomically");
    }
    Pack p;p.replace("lethal_morph_roll 10.1.0 1 2","lethal_morph_roll 10.1.0 0 2","deaths.mechanics");
    auto changed=MechanicsLibrary::load(p.path);auto a=fixture(),b=fixture(changed);
    for(auto *s:{&a,&b}){const auto id=s->spawnMonster(monsterId(10,1),{0,.85f,0});s->combatRng=Random(morphSeed(0));hit(*s,id,s->findEnemy(id)->hp);}
    check(a.enemies.front().alive&&!b.enemies.front().alive,"new library changes morph policy without mutating existing simulation snapshot");
    check(defaultMechanics()->fingerprint()==original,"external mortality edits preserve original immutable content");
    Pack bad;bad.replace("lethal_morph_roll 10.1.0 1 2","lethal_morph_roll 10.1.0 3 2","deaths.mechanics");bool rejected=false;
    try{MechanicsLibrary::load(bad.path);}catch(const std::exception &){rejected=true;}
    check(rejected,"invalid rational probability rejected");
    std::cout<<"GAPER_CONFIG invalid_contracts=9 immutable_reload=1\n";
}
}
int main(){try{immunity();sourceLifetime();morph();chanceAndConfig();gaperMorph();morphChoiceConfig();std::cout<<"MORTALITY_PASS\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
