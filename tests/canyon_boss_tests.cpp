#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const std::string &message){if(!ok)throw std::runtime_error(message);}
void schedules() {
    std::set<int> lengths;std::array<std::set<BossKind>,4> bands;
    for(uint64_t seed=0;seed<512;++seed) {
        ExpeditionPlan plan(seed);lengths.insert(plan.floorCount);BossKind previous=BossKind::None;
        for(int f=0;f<plan.floorCount;++f) {
            const auto boss=plan.bossOnFloor(f);check(canyonBoss(boss)&&boss!=previous,"no immediate boss repeats");
            check(boss==ExpeditionPlan(seed).bossOnFloor(f),"boss schedule reproducible");
            check(plan.profileOnFloor(f).boss==boss,"profile carries the scheduled boss");
            bands[size_t(plan.profileOnFloor(f).band)].insert(boss);previous=boss;
        }
        check(ExpeditionPlan(seed,true).bossOnFloor(0)==BossKind::None,"tutorial has no guardian");
        check(ExpeditionPlan(seed,false,WitnessAccount::None,ExpeditionPacing::Classic).bossOnFloor(0)==BossKind::None,"Classic unchanged");
    }
    check(lengths.size()==5,"all 4-8 floor plans covered");
    for(const auto &band:bands)check(band.size()==3,"all three identities can occur in every band");
}
void weakBuilds() {
    for(auto kind:{BossKind::Ridgeback,BossKind::PowderForeman,BossKind::StormMarshal})
        for(uint64_t seed:{7,42,1866})for(int late=0;late<2;++late) {
            const int floor=late?ExpeditionPlan(seed).floorCount-1:0;
            Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor);
            run.startBoss(kind);run.dynamite=0;run.godMode=false;
            const auto center=run.arena.rooms.back().center;
            run.player.position=add(center,{0,0,9.7f});
            for(int i=0;i<7200&&!run.roomClear&&!run.dead;++i) {
                const auto *boss=run.boss();check(boss,"encounter retains living boss");
                auto delta=sub(run.player.position,center);delta.y=0;
                const auto radial=unit(delta);const Vector3 tangent{-radial.z,0,radial.x};
                Input input;input.fire=true;input.aim=boss->position;
                input.movement=unit(add(tangent,mul(radial,std::clamp((9.7f-length(delta))*.7f,-2.f,2.f))));
                input.dodge=kind==BossKind::Ridgeback&&boss->state==EnemyState::Charging&&distance(boss->position,run.player.position)<5;
                run.step(input);
            }
            std::cout<<bossName(kind)<<" seed="<<seed<<" floor="<<floor<<" time="<<run.stats.duration<<" HP="<<run.player.hp<<'\n';
            check(run.roomClear&&!run.dead&&run.player.hp>0,"starting revolver defeats each boss without items, bombs or god mode");
            check(run.stats.duration<120&&run.dynamite==1&&run.items.empty(),"bounded duration and exactly one dynamite reward");
        }
}
void patterns() {
    for(auto kind:{BossKind::PowderForeman,BossKind::StormMarshal}) {
        Simulation run(1866,1,{},MissionTheme::Canyon);run.startBoss(kind);run.godMode=true;
        auto *boss=run.findEnemy(run.boss()->id);const auto center=run.arena.rooms.back().center;
        run.player.position=add(center,{0,0,9});
        std::set<int> attacks;bool recovery=false;int charges=0;Vector3 locked{};bool warned=false;
        for(int i=0;i<1600;++i) {
            run.step({});
            if(boss->state==EnemyState::Windup) {
                attacks.insert(boss->bossAttack);
                if(!warned){locked=boss->facing;warned=true;run.player.position=add(center,{6,0,6});}
                check(distance(locked,boss->facing)<.001f,"warning locks its aim");
            } else warned=false;
            recovery=recovery||boss->state==EnemyState::Stunned;
            for(const auto &h:run.hazards)if(h.kind==HazardKind::BossCharge) {
                ++charges;check(h.radius==2.6f&&h.delay>=2.2f,"charges leave a visible escape fuse");
            }
            if(kind==BossKind::StormMarshal&&boss->bossAttack==1&&boss->state==EnemyState::Charging)
                for(const auto &p:run.projectiles)if(p.hostile&&p.context.sourceEntity==boss->id) {
                    const float angle=std::acos(std::clamp(dot(unit(p.velocity),boss->facing),-1.f,1.f));
                    check(angle>.32f,"sweep leaves the committed gap open");
                }
        }
        check(attacks.size()==2&&recovery,"two distinct attacks with recovery");
        if(kind==BossKind::PowderForeman)check(charges>0,"Foreman throws real physical charges");
        boss->hp=boss->maxHp*.49f;boss->state=EnemyState::Ready;boss->cooldown=0;boss->bossCycles=kind==BossKind::StormMarshal?1:0;
        run.step({});check(boss->phase==1&&boss->state==EnemyState::Windup,"phase two retains windup");
        if(kind==BossKind::PowderForeman)check(boss->bossTargetCount==3,"phase two throws three marked charges");
        else {
            check(boss->bossCombo==1,"phase two schedules warned follow-up");
            bool followup=false;
            for(int i=0;i<600;++i){run.step({});if(boss->state==EnemyState::Windup&&boss->bossAttack==0){followup=true;break;}}
            check(followup,"Marshal executes separately warned follow-up volley");
        }
        const auto frozen=*boss;run.shopOpen=true;for(int i=0;i<20;++i)run.step({});run.shopOpen=false;
        check(boss->age==frozen.age&&boss->stateTime==frozen.stateTime,"boss freezes behind modal UI");
    }
}
void kickAndCleanup() {
    Simulation run(1866,1,{},MissionTheme::Canyon);run.startBoss(BossKind::PowderForeman);run.godMode=true;
    const auto id=run.boss()->id;auto *boss=run.findEnemy(id);const auto center=run.arena.rooms.back().center;
    run.player.position=add(center,{0,0,8});
    for(int i=0;i<400&&run.hazards.empty();++i)run.step({});
    check(!run.hazards.empty()&&run.hazards[0].kind==HazardKind::BossCharge,"actual thrown boss charge");
    auto charge=run.hazards[0];run.hazards.clear();
    charge.position=center;charge.position.y=.18f;charge.velocity={};charge.settled=true;
    charge.age=0;charge.delay=.8f;charge.playerContact=false;charge.kicked=false;
    run.hazards.push_back(charge);
    boss->position=add(center,{3,0,0});boss->state=EnemyState::Stunned;boss->stateTime=100;
    run.player.position=add(center,{-1,0,0});Input kick;kick.movement={1,0,0};
    for(int i=0;i<8;++i)run.step(kick);
    check(run.hazards[0].kicked&&run.hazards[0].velocity.x>0,"walking into charge kicks it without a key");
    const auto hp=boss->hp;
    for(int i=0;i<90;++i)run.step({});
    check(boss->hp<hp,"kicked charge can hurt Foreman");
    // Cancellation suppresses on-expiry descendants as well as live attacks.
    Projectile bullet;bullet.hostile=true;bullet.kind=ProjectileKind::BurstShot;bullet.context.sourceEntity=id;
    bullet.position=add(center,{0,0,5});bullet.alive=true;run.projectiles.push_back(bullet);
    Hazard pending;pending.kind=HazardKind::BossCharge;pending.context.sourceEntity=id;pending.position=center;pending.delay=3;
    run.hazards.push_back(pending);
    for(auto &prop:run.arena.breakables)if(prop.room==run.room&&prop.kind==BreakableKind::PowderBarrel)prop.fuse=.3f;
    Event kill;kill.type=EventType::Damage;kill.target=id;kill.damage=100000;kill.execution=true;run.queueRoot(kill);
    Event shot;shot.hostile=true;shot.context.sourceEntity=id;shot.position=center;run.queueRoot(shot);
    run.drainEvents();
    check(run.queuedEvents()==0,"pending boss shots cancelled at death");
    for(int i=0;i<90;++i)run.step({});
    check(run.hazards.empty()&&std::none_of(run.projectiles.begin(),run.projectiles.end(),[](const auto &p){return p.hostile;}),"death leaves no attacks or burst descendants");
    const int ammo=run.dynamite;const auto coins=run.moneyCollected;
    run.startBoss(BossKind::StormMarshal);run.killAll();run.step({});
    check(run.dynamite==ammo&&run.moneyCollected==coins,"debug replay cannot farm boss payout");
}
}
int main(){try{schedules();patterns();kickAndCleanup();weakBuilds();std::cout<<"PASS canyon boss pool, phases, counterplay, cleanup and weak builds\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
