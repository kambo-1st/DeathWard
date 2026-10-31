#include "combat/Simulation.hpp"
#include <filesystem>
#include <fstream>
#include <chrono>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
struct Pack {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("deathward-boss-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))
        if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(path);}
    void replace(const std::string &from,const std::string &to){const auto f=path/"bosses.mechanics";std::ifstream in(f);std::string text((std::istreambuf_iterator<char>(in)),{});
        auto at=text.find(from);check(at!=std::string::npos,"configuration fixture must match a real row");text.replace(at,from.size(),to);std::ofstream(f)<<text;}
    auto load(){return MechanicsLibrary::load(path);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> library=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,library);
    s.arena=Arena{};s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.arena.bounds={{-25,-1,-25},{25,8,25}};
    s.arena.walls={{{-26,-1,-26},{-25,12,26}},{{25,-1,-26},{26,12,26}},{{-26,-1,-26},{26,12,-25}},{{-26,-1,25},{26,12,26}}};
    s.arena.boundaryWalls=s.arena.walls;s.arena.rebuildWalls();
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.floors={{{-25,-.4f,-25},{25,0,25}}};}
    s.rooms.resize(s.arena.roomCount());s.player.position={0,.85f,8};return s;
}
void ticks(Simulation &s,int count){for(int i=0;i<count;++i)s.step({});}
void damage(Simulation &s,EntityId id,float amount,bool execution=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.execution=execution;s.queueRoot(e);s.drainEvents();
}
EntityId peep(Simulation &s,BossForm form=BossForm::Normal){const auto id=s.spawnMonster(monsterId(68),{0,.85f,0},0,-1,form);check(id!=0,"configured Peep spawns");return id;}
std::vector<EntityId> eyes(const Simulation &s,EntityId owner){std::vector<EntityId> result;for(const auto &e:s.enemies)if(e.alive&&e.componentOwner==owner)result.push_back(e.id);return result;}
void phaseAndLifetime() {
    auto s=fixture();const auto id=peep(s);s.findEnemy(id)->cooldown=1000;
    check(!s.spawnMonster(monsterId(68,10),{4,.85f,0}),"component refuses independent spawning");
    damage(s,id,479);ticks(s,1);check(eyes(s,id).empty(),"no premature threshold eye");
    damage(s,id,1);ticks(s,1);check(eyes(s,id).size()==1&&s.roomThreats()==1,"first eye at exactly two-thirds; only owner gates clear");
    ticks(s,20);damage(s,id,480);ticks(s,1);check(eyes(s,id).size()==2&&s.findEnemy(id)->bossParts==3,"second eye at one-third, unique persistent slots");
    const auto eye=eyes(s,id).front();const auto hp=s.findEnemy(eye)->hp;damage(s,eye,10000);check(s.findEnemy(eye)->hp==hp,"ordinary damage cannot kill an eye");
    damage(s,eye,10000,true);ticks(s,60);check(eyes(s,id).size()==1&&s.findEnemy(id)->bossParts==3,"explicit special execution does not regenerate a detached eye");
    const auto kills=s.stats.kills;damage(s,id,10000,true);
    check(eyes(s,id).empty()&&s.roomThreats()==0&&s.stats.kills==kills+1,"owner death removes components without extra kills");
    const auto paid=s.dynamite;damage(s,id,10000,true);check(s.dynamite==paid,"duplicate owner death never pays again");
    auto cyan=fixture();const auto c=peep(cyan,BossForm::Cyan);ticks(cyan,1);check(eyes(cyan,c).size()==2,"cyan begins with two eyes");
    auto limited=fixture();limited.limits.enemies=1;const auto l=peep(limited);limited.findEnemy(l)->cooldown=1000;damage(limited,l,1000);ticks(limited,2);
    check(eyes(limited,l).empty()&&limited.findEnemy(l)->bossParts==0,"capacity failure does not claim a missing component");
    limited.limits.enemies=3;ticks(limited,25);check(eyes(limited,l).size()==2,"capacity recovery retries both missing slots");
    check(!limited.spawnMonster(monsterId(68,10),{8,.85f,0},l,0),"duplicate slot rejected");
    auto pending=fixture();const auto p=peep(pending,BossForm::Cyan);damage(pending,p,10000,true);ticks(pending,1);
    check(pending.livingEnemies()==0,"death before pending spawn cannot leave an orphan");
    std::cout<<"PEEP_OWNERSHIP thresholds=2/3,1/3 cyan_start=2 capacity_retry=1 no_respawn=1 no_orphans=1\n";
}
void patternsAndJump() {
    for(int attack=0;attack<3;++attack) {
        Pack p;p.replace(".7 1 1 1",".7 "+std::string(attack==0?"1 0 0":attack==1?"0 1 0":"0 0 1"));
        auto s=fixture(p.load());const auto id=peep(s);s.findEnemy(id)->cooldown=0;
        s.step({});check(s.findEnemy(id)->state==EnemyState::Windup&&s.findEnemy(id)->bossAttack==attack,"external choice weights choose actual controller action");
        auto endpoint=s.findEnemy(id)->target;
        if(attack==2) {
            s.player.position={-12,.85f,0};
            while(!s.findEnemy(id)->hop.active)ticks(s,1);
            const auto hp=s.findEnemy(id)->hp;damage(s,id,100);check(s.findEnemy(id)->hp==hp,"documented airborne invulnerability");
            s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=.3f;
            float peak=0;while(s.findEnemy(id)->hop.active){ticks(s,1);peak=std::max(peak,s.findEnemy(id)->position.y);}
            check(distance(s.findEnemy(id)->position,endpoint)<.001f&&peak>4.7f,"committed 3D jump retains destination through target motion and stun");
            check(s.stats.projectiles==12,"landing releases exactly twelve yellow shots once");
            damage(s,id,100);check(s.findEnemy(id)->hp==hp-100,"grounded body is vulnerable again");
        } else ticks(s,65);
        if(attack==0)check(s.hazards.size()==1&&s.hazards[0].kind==HazardKind::Creep&&s.hazards[0].tint.g>100&&s.stats.projectiles==0,"creep action makes a real yellow damaging patch");
        if(attack==1) {
            check(s.stats.projectiles==8,"ordinary burst releases exactly eight yellow shots");
            auto first=s.projectiles.front().velocity;
            while(s.stats.projectiles<16)ticks(s,1);
            auto second=s.projectiles.back().velocity;
            const auto a=std::atan2(first.z,first.x),b=std::atan2(second.z,second.x);
            check(std::abs(std::sin((a-b)*4))>.01f,"successive ring orientations vary");
        }
        for(const auto &shot:s.projectiles)check(shot.kind==ProjectileKind::Yellow,"yellow visuals do not imply tar/fire patches");
    }
    auto normal=fixture();const auto a=peep(normal);auto yellow=fixture();const auto b=peep(yellow,BossForm::Yellow);
    check(std::abs(yellow.findEnemy(b)->radius/normal.findEnemy(a)->radius-.85f)<.001f,"yellow is 15 percent smaller");
    ticks(normal,120);ticks(yellow,120);check(!yellow.hazards.empty()&&yellow.hazards.size()<20,"yellow has bounded continuously refreshed creep");
    auto contact=fixture();contact.godMode=false;const auto c=peep(contact);contact.player.position={0,.85f,0};contact.findEnemy(c)->cooldown=1000;ticks(contact,1);
    check(contact.player.hp==75,"whole-heart source contact adapts to twice ordinary contact, multiplier applied once");
    std::cout<<"PEEP_ATTACKS creep=1 ring=8 landing=12 locked_arc=1 yellow_size=.85 whole_contact=25\n";
}
void eyeMotionAndBlocking() {
    auto s=fixture();const auto owner=peep(s);s.findEnemy(owner)->position={0,1.3f,18};s.findEnemy(owner)->cooldown=1000;
    auto eye=s.spawnMonster(monsterId(68,10),{24,.85f,0},owner,0);check(eye!=0,"owned eye can be explicitly arranged in fixture");
    s.findEnemy(eye)->facing=unit(Vector3{1,0,1});ticks(s,40);check(s.findEnemy(eye)->facing.x<0&&!s.arena.flightBlocked(s.findEnemy(eye)->position,.6f,0),"eye reflects at enclosing wall");
    s.findEnemy(eye)->position={-4,.85f,0};s.findEnemy(eye)->facing={1,0,0};
    const Box rock{{-1,0,-2},{1,2,2}};s.arena.obstacles.push_back(rock);s.arena.rebuildWalls();
    float peak=0;for(int i=0;i<180;++i){ticks(s,1);peak=std::max(peak,s.findEnemy(eye)->position.y);}
    check(s.findEnemy(eye)->position.x>3&&peak>2.8f,"eye crosses interior rocks at actual airborne height");
    s.arena.obstacles.clear();s.arena.rebuildWalls();s.findEnemy(eye)->position={0,.85f,0};s.findEnemy(eye)->facing={1,0,0};
    const auto blocker=s.spawnMonster(monsterId(12),{2,.85f,0});s.findEnemy(blocker)->cooldown=1000;ticks(s,40);
    check(s.findEnemy(eye)->facing.x<0,"eye reflects from another actual monster body");
    s.findEnemy(blocker)->alive=false;s.findEnemy(eye)->position={0,.85f,0};s.findEnemy(eye)->facing=unit(Vector3{-1,0,-1});
    Event blast;blast.type=EventType::Explosion;blast.position={-2,.85f,-2};blast.radius=4;blast.damage=1000;blast.areaDamage=true;
    const auto hp=s.findEnemy(eye)->hp;s.queueRoot(blast);s.drainEvents();
    check(s.findEnemy(eye)->hp==hp&&dot(s.findEnemy(eye)->facing,unit(Vector3{1,0,1}))>.9f,"real explosion deviates direction without damaging eye");
    s.findEnemy(eye)->position={0,.85f,0};s.findEnemy(eye)->facing={0,0,1};s.findEnemy(owner)->position={8,1.3f,0};
    const auto bossHp=s.findEnemy(owner)->hp;s.player.position={-10,.85f,-10};
    Event shot;shot.position={-4,.85f,0};shot.direction={1,0,0};shot.damage=100;shot.speed=26;s.queueRoot(shot);s.drainEvents();ticks(s,20);
    check(s.projectiles.empty()&&s.findEnemy(owner)->hp==bossHp&&s.findEnemy(eye)->hp==hp,"real player bullet stops at invulnerable eye");
    s.godMode=false;s.player.hurt=0;s.player.position=s.findEnemy(eye)->position;ticks(s,1);
    check(s.player.hp==87.5f,"eye deals ordinary contact damage");
    std::cout<<"PEEP_EYES wall_and_body_bounce=1 rocks=1 projectile_block=1 bomb_direction=1 contact=12.5\n";
}
void stageAndCompletion() {
    std::set<BossForm> covered;
    for(uint64_t seed=0;seed<128&&covered.size()<3;++seed) {
        ExpeditionPlan plan(seed);int floor=0;while(plan.profileOnFloor(floor).band<1)++floor;
        auto expected=defaultMechanics()->configureFloor(plan.profileOnFloor(floor),plan.floorSeed(floor));
        if(expected.boss!=BossKind::Isaac||expected.bossMonster!=monsterId(68)||covered.contains(expected.bossForm))continue;
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        const auto initial=s.roomEnemies(s.finalRoom());check(initial.size()==(expected.bossForm==BossForm::Cyan?3u:1u),"initial generated boss/component population matches seeded form");
        s.jumpDebug(s.finalRoom());s.godMode=true;const auto id=s.boss()->id;s.findEnemy(id)->cooldown=1000;
        damage(s,id,1000);ticks(s,20);const auto before=eyes(s,id);check(before.size()==2,"actual seeded encounter realizes both components");
        const auto mask=s.findEnemy(id)->bossParts;s.enterRoom(0);s.enterRoom(s.finalRoom());
        check(eyes(s,id)==before&&s.findEnemy(id)->bossParts==mask,"boss/components survive room re-entry without duplicate phases");
        if(expected.bossForm==BossForm::Normal) {
            s.findEnemy(id)->cooldown=0;
            for(int tick=0;tick<1500&&!s.findEnemy(id)->hop.active;++tick)s.step({});
            check(s.findEnemy(id)->hop.active,"actual seeded boss performs a jump");
            ticks(s,8);const auto position=s.findEnemy(id)->position;const auto elapsed=s.findEnemy(id)->hop.elapsed;
            s.enterRoom(0);s.enterRoom(s.finalRoom());
            check(distance(s.findEnemy(id)->position,position)<.001f&&s.findEnemy(id)->hop.elapsed==elapsed,"re-entry preserves committed boss flight");
            while(s.findEnemy(id)->hop.active)s.step({});
            check(!s.arena.blocked(s.findEnemy(id)->position,s.findEnemy(id)->radius),"resumed boss jump lands legally");
        }
        const auto dynamite=s.dynamite;damage(s,id,10000,true);ticks(s,1);
        check(s.roomClear&&s.bossKilled&&s.rooms.back().bossPaid&&s.roomThreats()==0&&s.livingEnemies()==0&&s.dynamite==dynamite+1,
            "dedicated encounter clears, removes eyes and pays exactly one boss reward");
        const auto money=s.moneyPickups.size();damage(s,id,10000,true);ticks(s,1);check(s.moneyPickups.size()==money&&s.dynamite==dynamite+1,"duplicate completion is inert");
        covered.insert(expected.bossForm);std::cout<<"PEEP_STAGE seed="<<seed<<" floor="<<floor<<" form="<<int(expected.bossForm)<<" components="<<before.size()<<" completion=1\n";
    }
    check(covered.size()==3,"all seeded Peep forms reachable within bounded actual-floor sample");
    for(uint64_t seed=0;seed<100;++seed) {
        ExpeditionPlan plan(seed);for(int floor=0;floor<plan.floorCount;++floor) {
            const auto p=defaultMechanics()->configureFloor(plan.profileOnFloor(floor),plan.floorSeed(floor));
            if(p.boss==BossKind::Isaac&&p.bossMonster==monsterId(68))check(p.band==1,"Peep is restricted to source Caves-equivalent stage");
        }
    }
}
void externalBossPools() {
    Pack p;
    // This snapshot test isolates the Peep/Tuff pools, which share the generic
    // boss clearing. Authored Hornfel arenas intentionally change its footprint.
    {const auto file=p.path/"hornfel.mechanics";std::ifstream in(file);std::string text((std::istreambuf_iterator<char>(in)),{});
        const std::string row="boss_pool 1 906.0.0 normal 2 standard";const auto at=text.find(row);check(at!=std::string::npos,"rail boss isolation fixture");
        text.replace(at,row.size(),"boss_pool 1 906.0.0 normal 0 standard");std::ofstream(file)<<text;}
    auto old=p.load();constexpr uint64_t seed=8;ExpeditionPlan plan(seed);int floor=0;while(plan.profileOnFloor(floor).band<1)++floor;
    Simulation before(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,old);
    check(before.arena.profile.boss==BossKind::Isaac,"snapshot fixture uses a naturally chosen source boss");
    p.replace("boss_pool 1 68.0.0 normal 3","boss_pool 1 68.0.0 normal 0");
    p.replace("boss_pool 1 68.0.0 cyan 1","boss_pool 1 68.0.0 cyan 0");
    p.replace("boss_pool 1 68.0.0 yellow 1","boss_pool 1 68.0.0 yellow 0");
    {const auto f=p.path/"segmented.mechanics";std::ifstream in(f);std::string text((std::istreambuf_iterator<char>(in)),{});
        const std::string from="boss_pool 1 19.2.0 normal 2 standard";const auto at=text.find(from);check(at!=std::string::npos,"Tuff pool fixture exists");
        text.replace(at,from.size(),"boss_pool 1 19.2.0 normal 0 standard");std::ofstream(f)<<text;}
    auto changed=p.load();Simulation after(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor,ExpeditionPacing::Compact,changed);
    check(before.arena.profile.boss==BossKind::Isaac&&after.arena.profile.boss==plan.bossOnFloor(floor)&&old->fingerprint()!=changed->fingerprint(),"boss pool edits affect a new snapshot, not an existing run");
    check(before.arena.canyon->heights==after.arena.canyon->heights&&before.arena.passages.size()==after.arena.passages.size(),"dedicated boss selection does not reroll terrain/topology");
    for(int room=0;room<before.finalRoom();++room)check(before.floorEncounter(room).monsters==after.floorEncounter(room).monsters,"boss selection does not consume ordinary composition RNG");
    check(!old->configureFloor(ExpeditionPlan(0,true).profileOnFloor(0),0).active(),"tutorial never receives boss pool routing");
    std::cout<<"PEEP_CONFIG immutable=1 geometry_unchanged=1 ordinary_pools_unchanged=1 tutorial_unchanged=1\n";
}
void startingKit() {
    for(auto form:{BossForm::Normal,BossForm::Cyan,BossForm::Yellow}) {
        auto s=fixture();s.godMode=false;s.dynamite=0;const auto id=peep(s,form);s.player.position={0,.85f,10};
        for(int n=0;n<9000&&!s.dead&&s.findEnemy(id);++n) {
            const auto *b=s.findEnemy(id);if(!b->alive)break;
            const auto radial=unit(horizontal(s.player.position));const float distance=planarDistance(s.player.position,{0,0,0});
            Input in;in.fire=true;in.aim=b->position;in.movement=unit(add(Vector3{-radial.z,0,radial.x},mul(radial,std::clamp((10-distance)*.8f,-2.f,2.f))));
            if((b->hop.active&&planarDistance(s.player.position,b->hop.end)<3)||
                std::any_of(s.projectiles.begin(),s.projectiles.end(),[&](const auto &p){return p.hostile&&dw::distance(p.position,s.player.position)<2;}))in.dodge=true;
            s.step(in);
        }
        std::cout<<"PEEP_STARTING_KIT form="<<int(form)<<" seconds="<<s.stats.duration<<" hp="<<s.player.hp<<" kills="<<s.stats.kills<<'\n';
        check(!s.dead&&!s.findEnemy(id)&&s.player.hp>0&&s.stats.duration<150,"unmodified 100 HP / 24-damage kit defeats each form without bombs or invulnerability");
    }
}
}
int main(){try{phaseAndLifetime();patternsAndJump();eyeMotionAndBlocking();stageAndCompletion();externalBossPools();startingKit();std::cout<<"PASS Peep multipart encounter, owned eyes and stage routing\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
