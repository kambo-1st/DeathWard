#include "combat/Simulation.hpp"
#include "world/CanyonTerrain.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool b,const char *s){if(!b)throw std::runtime_error(s);}
bool near(float a,float b,float epsilon=.015f){return std::abs(a-b)<epsilon;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={60,.85f,0};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
EntityId spawn(Simulation &s){return s.spawnMonster(monsterId(826),{0,.85f,0});}
void damage(Simulation &s,EntityId id,float amount,bool blast=false,DamageKind kind=DamageKind::Physical,bool debug=false) {
    Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.explosionDamage=blast;e.damageKind=kind;e.execution=e.debugExecution=debug;
    s.queueRoot(e);s.drainEvents();
}
void motion() {
    auto s=fixture();const auto id=spawn(s);
    for(int n=0;n<2000&&s.findEnemy(id)->hardy->phase==0;++n)tick(s);
    auto &e=*s.findEnemy(id);check(e.hardy->phase==1,"natural attack enters telegraph");
    tick(s,35);check(e.hardy->phase==1&&e.hardy->launches==0,"no charge before animation Slide event36");
    s.player.position={0,.85f,60};tick(s);check(e.hardy->phase==2&&e.hardy->launches==1&&near(e.velocity.z,60)&&near(e.velocity.x,0),"launch frame36 samples current target and source20 impulse");
    s.player.position={60,.85f,0};tick(s,3);check(near(e.velocity.x,0)&&e.velocity.z>0,"charge commits direction");
    auto a=fixture(),b=fixture();auto ia=spawn(a),ib=spawn(b);tick(a,120);tick(b,480,1.f/120);
    check(distance(a.findEnemy(ia)->position,b.findEnemy(ib)->position)<.04f,"30/120Hz unobstructed source-tick motion");
    std::cout<<"MOTION natural_start=1 telegraph36=1 late_target=1 commitment=1 partition=1\n";
}
void arm(Enemy &e,int previous=0) {e.hardy->initialized=true;e.hardy->phase=2;e.hardy->impacts=previous;e.hardy->clock=0;e.hardy->slideFrames=0;e.velocity={60,0,0};}
void impacts() {
    for(int prior=0;prior<3;++prior) {
        auto s=fixture();s.arena.obstacles.push_back({{3,0,-20},{4,6,20}});s.arena.rebuildWalls();auto id=spawn(s);arm(*s.findEnemy(id),prior);s.limits.projectiles=0;
        for(int n=0;n<15&&s.findEnemy(id)->hardy->impacts==prior;++n)tick(s);
        const auto &e=*s.findEnemy(id);const auto &r=*e.hardy;
        check(r.impacts==prior+1&&r.phase==3&&e.position.x<2.49f,"swept wall impact at physical contact");
        check(r.pendingShots.size()==size_t(prior==0?8:prior==1?14:8),"exact escalating whole burst retained under capacity");
        int lob=0,burst=0;for(const auto &shot:r.pendingShots){lob+=shot.projectileGravity>10;burst+=shot.projectileBurst.has_value();check(shot.projectileKind==ProjectileKind::Rock&&shot.context.sourceEntity==id,"real attributed rock projectile");}
        check(lob==(prior==0?0:prior==1?6:8)&&burst==(prior==2?8:0),"aimed cluster and third-impact BURST flags");
        if(prior==2) {
            int thrown=0;for(const auto &child:s.enemies)if(child.alive&&child.monster.type==818){++thrown;check(child.rockSpider&&child.rockSpider->height<0&&child.rockSpider->vertical<0,"third-impact offspring are live thrown actors at birth");}
            check(thrown>=2&&thrown<=3,"two or three thrown actors exist at impact");
        }
        tick(s,10);check(s.findEnemy(id)->hardy->impacts==prior+1&&s.projectiles.empty(),"saturation does not reroll or duplicate impact");
        s.limits.projectiles=256;tick(s,2);
        if(prior<2) {check(s.findEnemy(id)&&s.findEnemy(id)->alive,"first two crashes survive");tick(s,26);check(s.findEnemy(id)->hardy->cooldown>0,"hit recovery has cooldown");}
        else {
            int spiders=0,dips=0;
            for(const auto &child:s.enemies)if(child.alive){if(child.monster.type==818){++spiders;check(child.rockSpider.has_value(),"third-impact offspring keep actual rock controller");}if(child.monster==monsterId(217)){++dips;check(near(child.hp,25.6f),"death Dip has twice ordinary health");}}
            check(spiders>=2&&spiders<=3&&dips==1&&s.stats.kills==1,"third impact kills once and retains all exact children");
        }
    }
    std::cout<<"IMPACTS counts8_14_8=1 whole_burst=1 recovery=1 thrown_spiders=1 double_hp_dip=1\n";
}
void breakables() {
    for(auto kind:{BreakableKind::CrackedRock,BreakableKind::CacheGate,BreakableKind::Dung,BreakableKind::OreSeam}) {
        auto s=fixture();Breakable prop;prop.id=7;prop.room=0;prop.kind=kind;prop.bounds={{3,0,-2},{4,4,2}};prop.health=4;prop.initialHealth=4;
        s.arena.breakables.push_back(prop);s.arena.rebuildWalls();auto id=spawn(s);arm(*s.findEnemy(id));
        for(int n=0;n<15&&!s.arena.breakables[0].destroyed;++n)tick(s);
        check(s.arena.breakables[0].destroyed&&s.arena.breakables[0].paid,"impact destroys and pays one contacted breakable");
        check(s.findEnemy(id)->hardy->impacts==1,"opening obstacle still costs one shell layer");
    }
    auto glance=fixture();glance.arena.obstacles.push_back({{3,0,-20},{4,6,20}});glance.arena.rebuildWalls();auto id=spawn(glance);auto &e=*glance.findEnemy(id);arm(e);e.position.x=2.45f;e.velocity={9,0,60};
    tick(glance);check(e.hardy->impacts==0,"glancing collision does not fracture shell");
    std::cout<<"TERRAIN breakable_and_cache=1 grazing=1\n";
}
void canyonFootprint() {
    for(float dt:{1.f/30,1.f/120}) {
        auto s=fixture();auto terrain=std::make_shared<CanyonTerrain>();terrain->x=terrain->z=-20;terrain->step=1;terrain->width=terrain->depth=41;
        terrain->heights.assign(41*41,0);
        for(int z=24;z<41;++z)for(int x=0;x<41;++x)terrain->heights[size_t(z*41+x)]=4;
        terrain->boundaryHeights=terrain->heights;s.arena.canyon=terrain;s.arena.rebuildWalls();s.player.position={-10,.85f,-10};
        const auto id=spawn(s);arm(*s.findEnemy(id));s.findEnemy(id)->velocity={0,0,60};
        for(int n=0;n<int(1/dt)&&s.findEnemy(id)->hardy->impacts==0;++n)tick(s,1,dt);
        const auto &e=*s.findEnemy(id);
        check(e.hardy->impacts==1&&e.position.z<2.6f&&!s.arena.blocked(e.position,e.radius),"sloped canyon footprint fractures at walkable boundary without entering rock");
    }
    std::cout<<"CANYON footprint12cm=1 slope_impact=1 partition=1\n";
}
void lifecycle() {
    auto s=fixture();auto id=spawn(s);const float hp=s.findEnemy(id)->hp;
    damage(s,id,1);check(near(s.findEnemy(id)->hp,hp-1),"ordinary damage unscaled");
    damage(s,id,1,true);check(near(s.findEnemy(id)->hp,hp-3.5f),"explosion vulnerability2.5");
    damage(s,id,1,false,DamageKind::Crush);check(near(s.findEnemy(id)->hp,hp-6),"crush vulnerability2.5");
    s.limits.enemies=0;s.debugScenario=false;damage(s,id,10000);tick(s);check(!s.roomClear,"retained death Dip keeps room sealed at zero capacity");
    s.limits.enemies=1;tick(s);check(s.livingEnemies()==1&&s.enemies.back().monster==monsterId(217)&&near(s.enemies.back().hp,25.6f),"ordinary damage death yields exactly one stronger Dip");
    auto debug=fixture();id=spawn(debug);damage(debug,id,10000,false,DamageKind::Physical,true);tick(debug,2);check(debug.livingEnemies()==0,"debug clear suppresses death child");
    std::cout<<"LIFECYCLE damage_channels=1 retained_death=1 clear=1 debug=1\n";
}
void configAndPlacement() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-hardy-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{dir};std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream input(dir/"hardies.mechanics");const std::string original(std::istreambuf_iterator<char>(input),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture exists");text.replace(at,from.size(),to);std::ofstream(dir/"hardies.mechanics")<<text;return MechanicsLibrary::load(dir);};
    const auto changed=edit(".1 .95 .5 .7 20",".1 .95 .5 .7 18");check(near(changed->hardy(monsterId(826))->launch,18)&&near(defaultMechanics()->hardy(monsterId(826))->launch,20),"external profile uses immutable snapshots");
    for(const auto &invalid:std::vector<std::pair<std::string,std::string>>{{".1 .95 .5 .7 20",".1 1 .5 .7 20"},{"217.0.0 2 818.0.0","27.0.0 2 818.0.0"},{"217.0.0 2 818.0.0","217.0.0 2 818.2.0"},{"hardy_payload 826.0.0","#hardy_payload 826.0.0"}}) {
        bool failed=false;try{edit(invalid.first,invalid.second);}catch(const std::exception&){failed=true;}check(failed,"incompatible or missing Hardy contracts rejected");
    }
    Simulation natural(30,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,2);
    bool found=false;
    for(const auto &e:natural.roomEnemies(7))if(e.monster==monsterId(826)) {
        check(natural.arena.profile.band==1&&e.hardy&&!natural.arena.blocked(e.position,e.radius),"natural Hardy is a legal Quarry resident");
        std::cout<<"NATURAL_HARDY seed=30 floor=2 room=7 hp="<<e.maxHp<<'\n';found=true;
    }
    check(found,"actual seeded Hardy population reached");
    std::cout<<"CONFIG snapshots=1 invalid_contracts=4 placement=1\n";
}
void cross() {
    auto s=fixture();s.spawnMonster(monsterId(27),{60,.85f,60});
    Event e;e.hostile=true;e.position={0,.8f,0};e.direction=unit(Vector3{10,-10,0});e.speed=std::sqrt(200.f);e.damage=10;
    e.projectileKind=ProjectileKind::Rock;e.projectileRadius=.3f;e.projectileLife=5;e.projectileGravity=18.9f;e.projectileFlightRetention=.9f;e.projectileBurst=ProjectileBurstDefinition{};e.context.sourceEntity=987;
    s.queueRoot(e);s.drainEvents();s.limits.projectiles=3;tick(s,3);check(s.projectiles.size()==1&&s.projectiles.front().impactPending,"four-child burst retained atomically");
    s.limits.projectiles=8;tick(s);check(s.projectiles.size()==4,"burst creates four children");
    std::vector<Vector3> directions;
    for(const auto &p:s.projectiles){check(!p.sourceBurst&&p.kind==ProjectileKind::Rock&&p.context.sourceEntity==987&&near(p.radius,.18f),"cross clears recursion and preserves kind,owner,size");directions.push_back(unit(horizontal(p.velocity)));}
    check(std::abs(dot(directions[0],directions[2]))<.001f&&dot(directions[0],directions[1])<-.999f,"randomly oriented perpendicular cross");
    std::cout<<"BURST atomic4=1 perpendicular=1 source_retained=1 no_recursion=1\n";
}
}
int main(){std::cout<<std::unitbuf;try{motion();impacts();breakables();canyonFootprint();lifecycle();cross();configAndPlacement();std::cout<<"PASS Hardy\n";}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
