#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
#include <set>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.001f;}
Simulation fixture(){
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.arena.bounds={{-25,-1,-25},{25,8,25}};
    s.arena.boundaryWalls={{{-26,-1,-26},{-25,12,26}},{{25,-1,-26},{26,12,26}},{{-26,-1,-26},{26,12,-25}},{{-26,-1,25},{26,12,26}}};
    s.arena.rebuildWalls();for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.floors={{{-25,-.4f,-25},{25,0,25}}};}
    s.rooms.resize(s.arena.roomCount());s.player.position={0,.85f,8};return s;
}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void hit(Simulation &s,EntityId id,float damage=10000,bool execution=false){Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;e.execution=execution;s.queueRoot(e);s.drainEvents();}
EntityId spawn(Simulation &s,int kind,Vector3 at={0,.85f,0}){return s.spawnMonster(monsterId(kind),at);}
void bouncer(){
    auto s=fixture();auto id=spawn(s,822);ticks(s,1);auto *e=s.findEnemy(id);
    check(near(e->hp,96)&&e->creature&&e->creature->timer>=6&&e->creature->timer<10,"Bouncer native HP and timer initialization");
    ticks(s,3);check(s.findEnemy(id)->position.z<0,"Bouncer flees before inflation");
    const auto timer=s.findEnemy(id)->creature->timer;hit(s,id,3.2f*3.5f);
    check(near(s.findEnemy(id)->creature->timer,timer-1),"source-unit damage accelerates inflation timer");
    e=s.findEnemy(id);e->creature->timer=0;e->creature->near=true;e->age=2;
    for(int i=0;i<240&&!s.findEnemy(id)->creature->inflated;++i)ticks(s,1);
    check(s.findEnemy(id)->creature->inflated&&near(s.findEnemy(id)->radius,.975f),"native inflation event expands collision radius");
    ticks(s,60);check(s.findEnemy(id)->creature->phase==2&&s.findEnemy(id)->velocity.z>0,"inflated Bouncer pursues");
    s=fixture();id=spawn(s,822);hit(s,id);check(s.projectiles.size()==4,"early Bouncer death four diagonal shots");
    for(const auto &p:s.projectiles)check(near(std::abs(p.velocity.x),std::abs(p.velocity.z)),"early death diagonal axes");
    s=fixture();id=spawn(s,822);ticks(s,1);s.findEnemy(id)->creature->inflated=true;s.findEnemy(id)->creature->phase=2;
    hit(s,id);check(s.projectiles.size()==34&&s.stats.explosions==0,"inflated Bouncer emits34shots and no damaging bomb");
    int ramps=0;for(const auto &p:s.projectiles)if(p.sourcePlanarMotion){++ramps;check(near(p.sourcePlanarMotion->accelerationRampFrames,20),"native cloud acceleration ramp");}
    check(ramps==22,"inflated death has22delayed cloud shots plus12cluster shots");
    s=fixture();id=spawn(s,822);ticks(s,1);s.findEnemy(id)->creature->inflated=true;s.findEnemy(id)->creature->phase=2;s.limits.projectiles=2;
    hit(s,id);check(s.findEnemy(id)->creature->deathPending,"Bouncer death retained under projectile pressure");
    s.projectiles.clear();ticks(s,1);check(s.findEnemy(id)&&s.findEnemy(id)->creature->deathPending,"pending corpse remains while more shots await admission");
    s.limits.projectiles=200;s.projectiles.clear();ticks(s,1);check(!s.findEnemy(id),"corpse retires after complete retained volley");
    s=fixture();id=spawn(s,822);ticks(s,1);s.findEnemy(id)->creature->inflated=true;s.findEnemy(id)->creature->phase=2;
    s.godMode=false;s.player.position=s.findEnemy(id)->position;ticks(s,3);
    check(s.stats.kills==1&&s.player.hp<100,"inflated player contact kills Bouncer once and damages player");
    s=fixture();id=spawn(s,822);ticks(s,1);s.findEnemy(id)->creature->inflated=true;s.findEnemy(id)->creature->phase=2;
    s.findEnemy(id)->hp=s.findEnemy(id)->maxHp=100000;
    int reflections=0;
    for(int n=0;n<32;++n) {
        s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=10;s.projectiles.clear();
        Event v;v.type=EventType::Shot;v.position=v.origin={0,.85f,4};v.direction={0,0,-1};v.speed=10;v.damage=1;
        s.queueRoot(v);s.drainEvents();ticks(s,30);
        if(!s.projectiles.empty()&&s.projectiles.front().velocity.z>0){++reflections;check(!s.projectiles.front().hostile&&s.projectiles.front().context.sourceEntity==0,"Bouncer reflects existing shot without changing ownership or allegiance");}
    }
    check(reflections>0&&reflections<32,"inflated Bouncer reflection is intermittent rather than blanket immunity");
    auto wall=fixture();const auto trapped=spawn(wall,822);ticks(wall,1);
    wall.arena.obstacles.push_back({{-5,-1,-1.5f},{5,5,-.8f}});wall.arena.rebuildWalls();
    auto *body=wall.findEnemy(trapped);body->creature->phase=1;body->creature->frame=6;body->state=EnemyState::Windup;
    ticks(wall,3);body=wall.findEnemy(trapped);
    check(body->creature->inflated&&near(body->radius,.975f)&&!wall.arena.blocked(body->position,body->radius)&&body->position.z>=0,"inflation beside cover corrects footprint without crossing the wall");
    std::cout<<"BOUNCER flee=1 inflate=1 damage_timer=1 early4=1 inflated34=1 ramp22=1 retained_death=1 contact=1 intermittent_reflection=1\n";
}
void quakey(){
    auto s=fixture();auto id=spawn(s,823);ticks(s,1);s.findEnemy(id)->creature->timer=0;
    s.player.position={0,.85f,5};ticks(s,3);check(s.findEnemy(id)->state==EnemyState::Windup,"Quakey telegraphs jump");
    ticks(s,30);check(s.findEnemy(id)->state==EnemyState::Jumping&&s.findEnemy(id)->lift>0,"Quakey has visible airborne arc");
    s.player.position={8,.85f,8}; // Locked jump must not teleport to a later target position.
    ticks(s,45);check(s.findEnemy(id)->state!=EnemyState::Jumping&&near(s.findEnemy(id)->lift,0),"Quakey lands");
    check(std::abs(s.findEnemy(id)->position.x)<1,"jump aim was locked at windup");
    int rocks=0;for(const auto &p:s.projectiles)rocks+=p.kind==ProjectileKind::Rock;
    check(rocks>=11,"landing produces ring and falling ceiling rocks");
    s=fixture();id=spawn(s,823);ticks(s,1);s.findEnemy(id)->railCarrier=999;s.findEnemy(id)->creature->timer=0;
    const auto at=s.findEnemy(id)->position;ticks(s,110);check(distance(s.findEnemy(id)->position,at)<.001f&&s.projectiles.size()>=11,"mounted Quakey retains attacks without moving carrier");
    std::cout<<"QUAKEY jump=1 locked_aim=1 landing_ring8=1 ceiling3=1 mounted=1\n";
}
void gas(){
    auto s=fixture();auto id=spawn(s,874);ticks(s,4);
    check(!s.hazards.empty()&&s.hazards.front().explosiveGas&&near(s.hazards.front().damage,0),"Gas Dwarf leaves explosive noncontact-damage gas");
    hit(s,id);check(s.projectiles.size()==1&&s.projectiles.front().kind==ProjectileKind::Ipecac,"death fires real Ipecac shot");
    Event blast;blast.type=EventType::Explosion;blast.position=s.hazards.front().position;blast.radius=1;blast.damage=0;s.queueRoot(blast);s.drainEvents();
    const auto before=s.stats.explosions;ticks(s,4);check(s.stats.explosions>before,"explosion ignites gas cloud");
    s=fixture();id=spawn(s,874);ticks(s,1);s.player.position=s.findEnemy(id)->position;s.godMode=false;
    ticks(s,6);check(s.stats.kills==1&&s.player.hp<100&&s.stats.explosions>0,"contact detonates body and clouds once");
    s=fixture();id=spawn(s,874);ticks(s,4);s.limits.queuedEvents=0;
    s.hazards.front().gasIgnited=true;ticks(s,2);check(!s.hazards.empty()&&s.hazards.front().gasIgnited,"ignited gas retained under queue pressure");
    s.limits.queuedEvents=4096;ticks(s,3);check(s.stats.explosions>0,"retained gas later detonates");
    auto chain=fixture();
    for(int n=0;n<3;++n) {
        Hazard h;h.kind=HazardKind::Gas;h.position={float(n)*3,.85f,0};h.radius=1;h.delay=0;h.duration=10;
        h.explosiveGas=true;h.gasBlastRadius=2.5f;h.gasBlastDamage=10;h.gasPlayerDamage=10;h.damage=0;chain.hazards.push_back(h);
    }
    Event ignition;ignition.type=EventType::Explosion;ignition.position={0,.85f,0};ignition.radius=.1f;
    chain.queueRoot(ignition);chain.drainEvents();ticks(chain,10);
    check(chain.hazards.empty()&&chain.stats.explosions==4,"three linked gas clouds detonate exactly once each");
    std::cout<<"GAS_DWARF gas=1 ipecac=1 ignition=1 contact=1 retained_ignition=1\n";
}
void clack(){
    auto s=fixture();auto a=spawn(s,889,{-4,.85f,0}),b=spawn(s,889,{4,.85f,0});ticks(s,1);
    hit(s,a);check(s.findEnemy(a)->state==EnemyState::Collapsed&&s.stats.kills==0,"Clack collapses without premature kill reward");
    const auto hp=s.findEnemy(a)->hp;hit(s,a);check(near(s.findEnemy(a)->hp,hp),"bone pile blocks damage");
    Event bullet;bullet.type=EventType::Shot;bullet.position=bullet.origin={-4,.85f,4};bullet.direction={0,0,-1};bullet.speed=20;bullet.damage=24;
    s.queueRoot(bullet);s.drainEvents();ticks(s,30);
    check(s.projectiles.empty()&&near(s.findEnemy(a)->hp,hp),"real player projectile is blocked by bone pile");
    ticks(s,200);check(s.findEnemy(a)->state!=EnemyState::Collapsed,"Clack regenerates while another active Clack survives");
    hit(s,a);hit(s,b);ticks(s,4);check(s.enemies.empty()&&s.stats.kills==2,"all-collapsed group disappears and rewards exactly once per body");
    s=fixture();a=spawn(s,889);hit(s,a);ticks(s,4);check(s.enemies.empty()&&s.stats.kills==1,"single Clack cannot softlock room");
    check(!s.championEligible(monsterId(889)),"Clack does not accidentally accept White or other unreviewed champions");
    std::cout<<"CLACK collapse=1 pile_block=1 regrow=1 all_collapsed_cleanup=1 reward_once=1 white_excluded=1\n";
}
void startingKitAndPlacement(){
    for(int kind:{822,823,874,889}) {
        auto s=fixture();const auto id=spawn(s,kind);s.godMode=false;
        int n=0;
        for(;n<3600&&s.findEnemy(id)&&s.findEnemy(id)->alive&&s.player.hp>0;++n) {
            const auto radial=unit(horizontal(s.player.position));const Vector3 tangent{-radial.z,0,radial.x};
            Input in;in.fire=true;in.aim=add(s.findEnemy(id)->position,{0,s.findEnemy(id)->lift,0});
            in.movement=unit(add(tangent,mul(radial,std::clamp((8-length(horizontal(s.player.position)))*.7f,-2.f,2.f))));
            s.step(in);
        }
        for(int post=0;post<90&&s.player.hp>0;++post) {
            const auto radial=unit(horizontal(s.player.position));Input in;in.movement={-radial.z,0,radial.x};s.step(in);
        }
        check(s.player.hp>0&&(!s.findEnemy(id)||!s.findEnemy(id)->alive),"starting kit can defeat each new ordinary creature");
        check(near(s.player.maxHp,100)&&near(s.player.shotDamage,24),"starting kit defaults preserved");
        std::cout<<"CREATURE_STARTING_KIT id="<<kind<<" seconds="<<n*Tick<<" hp="<<s.player.hp<<'\n';
    }
    std::set<MonsterId> found;
    for(int seed=0;seed<256&&found.size()<4;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);int floor=0;while(plan.profileOnFloor(floor).band<1)++floor;
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
        for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(e.monster.type==822||e.monster.type==823||e.monster.type==874||e.monster.type==889) {
            check(!s.arena.blocked(e.position,e.radius),"naturally generated creature has legal footprint");
            if(found.insert(e.monster).second)std::cout<<"CREATURE_NATURAL id="<<e.monster.type<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
        }
    }
    check(found.size()==4,"all four creatures naturally reachable");
    for(int seed=0;seed<8;++seed) {
        Simulation s(seed,1,{},MissionTheme::Canyon,true,false);s.startPractice(4);
        check(s.enemies.size()==5&&!s.godMode&&near(s.player.hp,100)&&near(s.player.shotDamage,24),"practice4 provides five ordinary starting-kit targets");
        for(const auto &e:s.enemies)check(!s.arena.blocked(e.position,e.radius)&&!s.arena.path(s.player.position,e.position,e.radius).empty(),"practice4 actors are legal and reachable");
    }
}

void pools(){
    const auto c=defaultMechanics();
    for(int band=0;band<4;++band){const auto &pool=c->encounterPool(band,EncounterPattern::Pursuit);
        for(int type:{822,823,874,889}){const bool found=std::any_of(pool.specialists.begin(),pool.specialists.end(),[&](const auto &v){return v.monster==monsterId(type);});check(found==(band==1),"four new creatures restricted to Mines/Ashpit-equivalent band");}}
}
}
int main(){try{bouncer();quakey();gas();clack();pools();startingKitAndPlacement();std::cout<<"PASS four creature cycles\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
