#include "combat/Simulation.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.001f;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false);
    s.arena=Arena{};s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.arena.bounds={{-25,-1,-25},{25,8,25}};
    s.arena.boundaryWalls={{{-26,-1,-26},{-25,12,26}},{{25,-1,-26},{26,12,26}},{{-26,-1,-26},{26,12,-25}},{{-26,-1,25},{26,12,26}}};
    s.arena.rebuildWalls();for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.floors={{{-25,-.4f,-25},{25,0,25}}};}
    s.rooms.resize(s.arena.roomCount());s.player.position={0,.85f,8};return s;
}
void ticks(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void kill(Simulation &s,EntityId id,bool execute=false){Event e;e.type=EventType::Damage;e.target=id;e.damage=10000;e.weakPointHit=true;e.execution=execute;s.queueRoot(e);s.drainEvents();}
EntityId spawn(Simulation &s,MonsterId id){const auto actor=s.spawnMonster(id,{0,.85f,0});s.findEnemy(actor)->cooldown=0;return actor;}
void drowned() {
    auto s=fixture();auto id=spawn(s,monsterId(23,1));check(near(s.findEnemy(id)->hp,70.4f),"Drowned HP is 10 percent over normal Charger");
    ticks(s,1);check(s.findEnemy(id)->state==EnemyState::Charging&&s.findEnemy(id)->velocity.z>12,"Drowned inherits immediate cardinal dash");
    kill(s,id);check(s.projectiles.size()==4&&s.stats.kills==1,"ordinary death emits exactly four real shots and one reward");
    for(const auto &p:s.projectiles)check(p.hostile&&near(std::abs(p.velocity.x),std::abs(p.velocity.z)),"Drowned death shots have fixed diagonal axes");
    s.debugScenario=false;s.rooms[size_t(s.room)].cleared=false;ticks(s,1);
    check(s.roomClear&&s.projectiles.size()==4&&s.stats.rooms==1,"last-enemy volley survives room completion without keeping doors sealed");
    s=fixture();id=spawn(s,monsterId(23,1));kill(s,id,true);check(s.projectiles.empty(),"execution cleanup does not create death attacks");
    std::cout<<"DROWNED hp=70.4 immediate=1 diagonal_death_shots=4 execution_cleanup=1\n";
}
void dank() {
    auto s=fixture();s.player.position={0,.85f,2};
    s.arena.obstacles.push_back({{-10,-1,4},{10,5,5}});s.arena.rebuildWalls();auto id=spawn(s,monsterId(23,2));
    ticks(s,1);s.player.position={8,.85f,8}; // Let the committed dash pass the acquisition point.
    bool bounced=false;
    for(int n=0;n<100;++n){ticks(s,1);const auto *e=s.findEnemy(id);bounced|=e->state==EnemyState::Charging&&e->velocity.z<-15;
        check(!s.arena.blocked(e->position,e->radius),"swept fast reflection never crosses solid cover");}
    check(bounced,"Dank reflects from wall while preserving active dash");
    while(s.findEnemy(id)->state==EnemyState::Charging)ticks(s,1);
    auto *e=s.findEnemy(id);const auto stopped=e->position;check(e->chargeRecovery>0,"Dank has a stationary recovery");
    check(!s.hazards.empty()&&s.hazards.size()<=16,"bounded tar trail created during dash");
    ticks(s,20);check(distance(stopped,s.findEnemy(id)->position)<.0001f,"recovery does not wander or reacquire early");
    auto patch=s.hazards.front();s.player.position=patch.position;s.godMode=false;s.findEnemy(id)->position={15,.85f,15};s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=10;
    ticks(s,1);check(s.player.slowTime>0&&s.player.hp==100,"tar slows without dealing damage");
    s=fixture();id=spawn(s,monsterId(23,2));e=s.findEnemy(id);e->state=EnemyState::Charging;e->stateTime=1;e->facing=unit(Vector3{1,0,1});
    s.arena.obstacles.push_back({{2,-1,-10},{3,5,10}});s.arena.rebuildWalls();
    bool reflected=false;for(int n=0;n<20;++n){ticks(s,1);e=s.findEnemy(id);if(e->facing.x<0){check(e->facing.z>0,"wall normal reflects only the incident component");reflected=true;break;}}
    check(reflected,"oblique reflection observed");
    std::cout<<"DANK fast_dash=1 swept_wall_reflection=1 stationary_recovery=1 slowing_nondamaging_trail=1\n";
}
void shot(Simulation &s,EntityId id,Vector3 from,Vector3 direction,int pierce=0) {
    s.player.position=from;auto *e=s.findEnemy(id);e->state=EnemyState::Stunned;e->stateTime=100;
    Event shot;shot.position=shot.origin=from;shot.direction=direction;shot.damage=24;shot.speed=26;
    AttackSpec attack;attack.damage=24;attack.speed=26;attack.pierce=pierce;shot.attack=attack;
    s.queueRoot(shot);s.drainEvents();ticks(s,20);
}
void princess() {
    auto s=fixture();auto id=spawn(s,monsterId(23,3));s.findEnemy(id)->auxiliary=100;
    ticks(s,1);check(s.findEnemy(id)->state==EnemyState::Ready,"Princess does not acquire cardinal alignment");
    s.findEnemy(id)->position={0,.85f,0};s.player.position={8,.85f,8};ticks(s,1);
    check(s.findEnemy(id)->state==EnemyState::Charging&&near(s.findEnemy(id)->facing.x,s.findEnemy(id)->facing.z),"Princess commits to diagonal axis");
    s=fixture();id=spawn(s,monsterId(23,3));s.findEnemy(id)->facing={0,0,-1};
    shot(s,id,{0,.85f,-4},{0,0,1},2);check(near(s.findEnemy(id)->hp,83.2f),"real piercing shot at armored head remains blocked");
    shot(s,id,{0,.85f,4},{0,0,-1});check(near(s.findEnemy(id)->hp,59.2f),"real rear shot hits exposed tail");
    // An angled shot from behind can hit the armored midsection before the tail.
    shot(s,id,{-4,.85f,0},{1,0,0});
    check(near(s.findEnemy(id)->hp,59.2f),"real side shot hits armored midsection");
    const float before=s.findEnemy(id)->hp;
    Event blast;blast.type=EventType::Explosion;blast.position={0,.85f,-.65f};blast.radius=.2f;blast.damage=12;
    s.queueRoot(blast);s.drainEvents();check(near(s.findEnemy(id)->hp,before),"small front explosion does not reach tail");
    blast.position={0,.85f,.455f};s.queueRoot(blast);s.drainEvents();check(near(s.findEnemy(id)->hp,before-12),"explosion overlapping real tail damages once");
    kill(s,id,true);check(!s.findEnemy(id)->alive,"explicit execution still cleans up armored enemy");
    s=fixture();id=spawn(s,monsterId(23,3));auto *body=s.findEnemy(id);body->facing={0,0,-1};body->state=EnemyState::Stunned;body->stateTime=100;
    s.addFire({0,.85f,-.65f},.2f,2,10,true,false);ticks(s,15);
    check(near(s.findEnemy(id)->hp,83.2f),"flame at armored head cannot damage remote tail");
    s.addFire({0,.85f,.455f},.2f,2,10,true,false);ticks(s,72);
    check(near(s.findEnemy(id)->hp,53.2f),"tail stays vulnerable to repeated fire after contact cooldown expires");
    std::cout<<"PRINCESS diagonal=1 real_tail_projectile=1 head_piercing_blocked=1 spatial_explosions=1\n";
}
void levelTwo() {
    auto s=fixture();const auto id=spawn(s,monsterId(855));ticks(s,1);auto *e=s.findEnemy(id);
    check(e->state==EnemyState::Charging&&near(e->facing.x,0)&&e->velocity.z>10&&e->velocity.z<12,"Level2 begins on cardinal axis and is slower than Charger");
    s.player.position={8,.85f,8};float angle=0;
    for(int n=0;n<30;++n){ticks(s,1);e=s.findEnemy(id);const float next=std::atan2(e->facing.x,e->facing.z);check(next-angle<=1.1f*Tick+.001f,"steering is bounded per tick");angle=next;}
    check(e->position.x>1&&e->facing.x>.4f,"Level2 bends toward moving player during charge");
    s=fixture();const auto second=spawn(s,monsterId(855));s.player.position={0,.85f,.9f};s.godMode=false;ticks(s,1);
    check(s.player.hp==75&&s.findEnemy(second)->maxHp==128,"source double contact has one hostile multiplier; local HP conversion retained");
    std::cout<<"LEVEL2 hp=128 cardinal_start=1 steering=1 slower=1 contact_damage=25\n";
}
void startingKit() {
    for(const auto monster:{monsterId(23),monsterId(23,1),monsterId(23,2),monsterId(23,3),monsterId(855)}) {
        auto s=fixture();const auto id=spawn(s,monster);s.godMode=false;s.dynamite=0;int ticksTaken=0;
        for(;ticksTaken<3600&&s.findEnemy(id)&&s.player.hp>0;++ticksTaken) {
            const auto radial=unit(horizontal(s.player.position));const Vector3 tangent{-radial.z,0,radial.x};
            Input input;input.fire=true;input.aim=s.findEnemy(id)->position;
            input.movement=unit(add(tangent,mul(radial,std::clamp((8-length(horizontal(s.player.position)))*.7f,-2.f,2.f))));
            input.dodge=s.findEnemy(id)->state==EnemyState::Charging&&distance(s.player.position,s.findEnemy(id)->position)<4.5f;
            s.step(input);
        }
        // Keep moving after the body dies so the death volley is part of the trial.
        for(int n=0;n<90&&!s.findEnemy(id)&&s.player.hp>0;++n) {
            const auto radial=unit(horizontal(s.player.position));Input input;
            input.movement={-radial.z,0,radial.x};s.step(input);
        }
        std::cout<<"CHARGER_STARTING_KIT id="<<monsterIdText(monster)<<" seconds="<<float(ticksTaken)*Tick<<" post_death_seconds=1.5 hp="<<s.player.hp<<" kills="<<s.stats.kills<<'\n';
        check(!s.findEnemy(id)&&s.player.hp>0,"synthetic-room starting-kit bot defeats each variant without items, bombs or god mode");
    }
}
void regressions() {
    const std::array<MonsterId,5> cohort{monsterId(23),monsterId(23,1),monsterId(23,2),monsterId(23,3),monsterId(855)};
    for(auto kind:cohort) {
        auto s=fixture();auto id=spawn(s,kind);auto *e=s.findEnemy(id);e->state=EnemyState::Charging;e->stateTime=.025f;e->facing={1,0,0};
        s.player.position={0,.85f,20};const float speed=s.content->charge(kind)->speed*EnemyMovementMultiplier;
        s.step({},.1f);e=s.findEnemy(id);
        check(near(e->position.x,speed*.025f)&&e->state==EnemyState::Ready,"dash distance respects remaining duration under long step");
        s=fixture();id=spawn(s,kind);e=s.findEnemy(id);e->state=EnemyState::Charging;e->stateTime=1;e->facing={1,0,0};
        s.player.position={2,.85f,0};s.godMode=false;s.step({},.3f);
        check(s.player.hp<100,"swept contact detects charge crossing between frames");
        for(int variant:{0,1,2,5,7,13,18,19}) {
            auto c=fixture();auto actor=spawn(c,kind);const auto hp=c.findEnemy(actor)->hp;
            check(c.makeChampion(actor,variant),"champion eligibility for all five chargers");
            check(near(c.findEnemy(actor)->hp,hp*c.content->champion(variant)->hp),"charger champion health");
            c.godMode=false;c.player.position=c.findEnemy(actor)->position;
            c.findEnemy(actor)->state=EnemyState::Charging;c.findEnemy(actor)->stateTime=1;c.findEnemy(actor)->facing={1,0,0};c.step({},Tick);
            const auto *rule=c.content->charge(kind);const auto *champ=c.content->champion(variant);
            check(near(c.player.hp,100-std::max(rule->contactDamage,10.f*champ->damage)*EnemyDamageMultiplier),"champion contact raises damage without multiplying already-strong contact");
            // Measure free charge speed separately from player/body separation.
            c.player.position={20,.85f,20};c.findEnemy(actor)->position={0,.85f,0};
            c.findEnemy(actor)->state=EnemyState::Charging;c.findEnemy(actor)->stateTime=1;c.findEnemy(actor)->facing={1,0,0};c.step({},Tick);
            if(!near(length(c.findEnemy(actor)->velocity),rule->speed*EnemyMovementMultiplier*champ->speed))std::cout<<"CHAMPION_SPEED id="<<monsterIdText(kind)<<" variant="<<variant<<" actual="<<length(c.findEnemy(actor)->velocity)<<" expected="<<rule->speed*EnemyMovementMultiplier*champ->speed<<" state="<<int(c.findEnemy(actor)->state)<<'\n';
            check(near(length(c.findEnemy(actor)->velocity),rule->speed*EnemyMovementMultiplier*champ->speed),"champion movement applies configured speed multiplier");
        }
    }
    auto s=fixture();auto id=spawn(s,monsterId(23,1));s.limits.projectiles=0;kill(s,id);ticks(s,2);
    check(s.findEnemy(id)&&s.findEnemy(id)->chargeDeathPending&&!s.roomClear,"pending death shots retain body and room completion under backpressure");
    s.limits.projectiles=32;ticks(s,10);check(s.stats.projectiles==4&&s.stats.kills==1,"death volley retries exactly once without extra rewards");
    for(int seed=0;seed<8;++seed) {
        Simulation p(seed,1,{},MissionTheme::Canyon,true,false);p.startPractice(3);
        check(p.enemies.size()==5&&!p.godMode&&p.player.hp==100&&p.player.shotDamage==24,"batch3 playable starting kit");
        std::set<MonsterId> actual;for(const auto &e:p.enemies){actual.insert(e.monster);check(!p.arena.blocked(e.position,e.radius),"practice charger footprint legal");}
        check(actual==std::set<MonsterId>(cohort.begin(),cohort.end()),"practice includes all five charger identities");
    }
    std::cout<<"CHARGER_BATCH3 duration=5 swept_contact=5 champion_combinations=40 death_retry=1 practice_seeds=8\n";
}
void natural() {
    const std::set<MonsterId> expected{monsterId(23),monsterId(23,1),monsterId(23,2),monsterId(23,3),monsterId(855)};
    std::set<MonsterId> found;int floors=0;
    for(int seed=0;seed<32&&found!=expected;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int band=0;band<4;++band) {
            int floor=0;while(plan.profileOnFloor(floor).band<band)++floor;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);++floors;
            for(int room=1;room<s.finalRoom();++room)for(const auto &e:s.roomEnemies(room))if(expected.contains(e.monster)) {
                check(!s.arena.blocked(e.position,e.radius),"natural charger footprint legal");
                if(found.insert(e.monster).second)std::cout<<"CHARGER_NATURAL id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
            }
        }
    }
    check(found==expected,"all five charger types naturally reachable at their supported stages");
    std::cout<<"CHARGER_REACHABILITY floors="<<floors<<" identities="<<found.size()<<'\n';
}
void championColors() {
    const std::array<MonsterId,5> cohort{monsterId(23),monsterId(23,1),monsterId(23,2),monsterId(23,3),monsterId(855)};
    for(auto kind:cohort)for(int variant:{3,4,6,9,14}) {
        auto s=fixture();auto id=spawn(s,kind);const auto original=s.findEnemy(id)->hp;
        check(s.makeChampion(id,variant),"new champion modifier applies to every charger");
        check(near(s.findEnemy(id)->hp,original*s.content->champion(variant)->hp),"new champion HP");
        if(variant==4) {
            auto *e=s.findEnemy(id);e->state=EnemyState::Charging;e->stateTime=1;e->facing={1,0,0};s.player.position={20,.85f,20};s.step({},Tick);
            check(near(length(s.findEnemy(id)->velocity),s.content->charge(kind)->speed*EnemyMovementMultiplier*.75f),"dark blue slows dash without changing recovery clock");
        }
        if(variant==9) {
            auto *e=s.findEnemy(id);e->age=0;const auto first=e->championVisibility();e->age=1.5f;
            check(std::abs(e->championVisibility()-first)>.1f,"black champion visibility oscillates");
        }
        if(variant==14){auto *e=s.findEnemy(id);check(near(e->championVisibility(),.12f),"camouflage low visibility");e->flash=.1f;check(near(e->championVisibility(),1),"damage flash reveals camouflage");}
    }
    auto s=fixture();auto a=spawn(s,monsterId(23)),b=spawn(s,monsterId(23)),normal=spawn(s,monsterId(23));
    s.makeChampion(a,6);s.makeChampion(b,6);
    auto damage=[&](EntityId id){Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=1;s.queueRoot(hit);s.drainEvents();};
    const float hp=s.findEnemy(a)->hp;damage(a);check(near(s.findEnemy(a)->hp,hp),"white waits for ordinary threats");
    kill(s,normal,true);damage(a);damage(b);
    check(near(s.findEnemy(a)->hp,hp-1)&&near(s.findEnemy(b)->hp,hp-1),"white champions ignore each other to avoid softlock");
    auto orange=fixture();a=spawn(orange,monsterId(23));orange.makeChampion(a,3);orange.moneyCollected=10;orange.godMode=false;
    orange.player.position=orange.findEnemy(a)->position;orange.findEnemy(a)->state=EnemyState::Charging;orange.findEnemy(a)->stateTime=1;orange.findEnemy(a)->facing={1,0,0};orange.step({},Tick);
    check(orange.player.hp<100,"orange contact hit admitted");
    check(orange.money()>=6&&orange.money()<=8&&!orange.moneyPickups.empty(),"orange removes2to4and drops1to3coins");
    const auto spent=orange.moneySpent;orange.step({},Tick);check(orange.moneySpent==spent,"hurt cooldown prevents duplicate coin loss");
    auto projectile=fixture();a=spawn(projectile,monsterId(23));projectile.makeChampion(a,3);projectile.moneyCollected=10;
    Event shot;shot.hostile=true;shot.context.sourceEntity=a;shot.position=shot.origin={-5,.85f,0};shot.direction={1,0,0};shot.speed=10;
    projectile.queueRoot(shot);projectile.drainEvents();check(projectile.projectiles.front().context.championCoinLoss,"projectile snapshots coin-loss modifier");
    projectile.enemies.clear();projectile.godMode=false;projectile.player.position={0,.85f,0};
    for(int n=0;n<90&&projectile.player.hp==100;++n)projectile.step({},Tick);
    check(projectile.money()<10,"orange projectile retains effect after owner removal");
    std::cout<<"CHAMPION_COLORS new_types=5 charger_combinations=25 white_gate=1 white_softlock=1 coin_loss=1 owner_lifetime=1 visibility=1\n";
}
void pools() {
    const auto c=defaultMechanics();
    for(int band=0;band<4;++band) {
        const auto &pool=c->encounterPool(band,EncounterPattern::ChargeLane);
        auto has=[&](MonsterId id){return std::any_of(pool.specialists.begin(),pool.specialists.end(),[&](const auto &e){return e.weight>0&&e.monster==id;});};
        check(has(monsterId(23,1))==(band==1||band==2),"Drowned approved bands1/2");
        check(has(monsterId(23,2))==(band==2),"Dank approved band2");
        check(has(monsterId(23,3))==(band==1),"Princess approved Ashpit-equivalent band1");
        check(has(monsterId(855))==(band==3),"Level2 approved Corpse-equivalent band3");
    }
}
}
void championFields() {
    for(auto kind:{monsterId(23),monsterId(23,1),monsterId(23,2),monsterId(23,3),monsterId(855)})
    for(int variant:{8,10,11,16,20}) {
        auto s=fixture();const auto actor=spawn(s,kind);check(s.makeChampion(actor,variant),"field champion applies to all Chargers");
        auto *e=s.findEnemy(actor);e->state=EnemyState::Stunned;e->stateTime=10;e->adaptiveArmor.reset();
        if(variant==8) {
            s.arena.obstacles.push_back({{-3,-1,2},{3,5,3}});s.arena.rebuildWalls();
            e->state=EnemyState::Charging;e->stateTime=.6f;e->facing={0,0,1};ticks(s,30);
            check(s.findEnemy(actor)->position.z>3.5f,"ghost dash crosses solid cover");
            Event shot;shot.type=EventType::Shot;shot.position={0,.85f,0};shot.direction={0,0,1};shot.speed=10;shot.hostile=true;shot.context.sourceEntity=actor;
            s.queueRoot(shot);s.drainEvents();check(s.projectiles.back().noWallCollision,"ghost projectiles snapshot spectral flag");
            s.findEnemy(actor)->position.z=24;ticks(s,30);check(s.findEnemy(actor)->position.z<=25-s.findEnemy(actor)->radius+.001f,"ghost stays within sealed room");
        } else if(variant==10) {
            ticks(s,80);check(!s.projectiles.empty(),"magenta fires periodic short-range shot");
            const auto &p=s.projectiles.back();check(p.hostile&&p.life<=.8f&&p.damage>0,"magenta shot has finite short life and hostility");
        } else if(variant==11||variant==16) {
            s.player.position={0,.85f,8};e->age=variant==16?1:0;
            Event shot;shot.type=EventType::Shot;shot.position={0,.85f,8};shot.direction={1,0,0};shot.speed=10;
            s.queueRoot(shot);s.drainEvents();const auto before=s.player.position;
            if(variant==16)ticks(s,70);else ticks(s,10);
            check(!s.projectiles.empty(),"aura test projectile survives");
            check(variant==11?s.projectiles.front().velocity.z<0:s.projectiles.front().velocity.z>0,"attraction and pulse repulsion bend player shots in correct direction");
            if(variant==11)check(s.player.position.z<before.z,"violet pulls player");
            else check(near(s.player.position.z,before.z),"gray repulsion never pushes player");
        } else {
            auto friendId=s.spawnMonster(monsterId(23),{8,.85f,0});auto healer=s.spawnMonster(monsterId(23),{-8,.85f,0});s.makeChampion(healer,20);
            s.findEnemy(friendId)->hp=1;s.findEnemy(healer)->hp=1;const auto own=s.findEnemy(actor)->hp;
            ticks(s,1);check(s.findEnemy(friendId)->hp>1,"red healer restores other enemy HP");
            check(near(s.findEnemy(healer)->hp,1)&&near(s.findEnemy(actor)->hp,own),"healers cannot heal each other or themselves");
            ticks(s,90);check(s.findEnemy(friendId)->hp<=s.findEnemy(friendId)->maxHp,"healing cannot exceed maximum");
        }
    }
    auto spectral=fixture();const auto ghost=spawn(spectral,monsterId(23));spectral.makeChampion(ghost,8);
    Event ray;ray.type=EventType::Shot;ray.hostile=true;ray.context.sourceEntity=ghost;ray.position=ray.origin={0,.85f,24};ray.direction={0,0,1};ray.speed=10;
    spectral.queueRoot(ray);spectral.drainEvents();spectral.enemies.clear();ticks(spectral,20);
    check(spectral.projectiles.empty(),"spectral champion shot retains room-boundary collision after owner removal");
    std::cout<<"CHAMPION_FIELDS new_types=5 charger_combinations=25 ghost=1 spectral=1 magenta=1 attraction=1 repulsion=1 heal=1\n";
}

void championLifecycles() {
    for(auto kind:{monsterId(23),monsterId(23,1),monsterId(23,2),monsterId(23,3),monsterId(855)})
    for(int variant:{12,15,17,21,22,23,24,25}) {
        auto s=fixture();const auto actor=spawn(s,kind);check(s.makeChampion(actor,variant),"lifecycle modifier applies to all Chargers");
        auto *e=s.findEnemy(actor);e->state=EnemyState::Stunned;e->stateTime=10;e->adaptiveArmor.reset();
        if(variant==12) {
            kill(s,actor);check(s.findEnemy(actor)->alive&&s.findEnemy(actor)->championPile&&s.stats.kills==0,"dark red collapses without reward");
            ticks(s,151);check(s.findEnemy(actor)->alive&&!s.findEnemy(actor)->championPile&&near(s.findEnemy(actor)->hp,s.findEnemy(actor)->maxHp),"dark red regenerates");
            kill(s,actor);kill(s,actor);check(!s.findEnemy(actor)->alive&&s.stats.kills==1,"pile can be finished for one reward");
        } else if(variant==15) {
            kill(s,actor);ticks(s,1);int copies=0;for(const auto &child:s.enemies)if(child.alive&&child.monster==kind){++copies;check(child.champion<0,"split copies are ordinary");}
            check(copies==2,"pulsing green produces exactly two copies");
        } else if(variant==17) {
            ticks(s,6);int orbiters=0;for(const auto &child:s.enemies)orbiters+=child.alive&&child.monster==monsterId(96)&&child.partner==actor;
            check(orbiters==1,"light white has one owned Eternal Fly");
            kill(s,actor);ticks(s,1);int flies=0;for(const auto &child:s.enemies)flies+=child.alive&&child.monster==monsterId(18);
            check(flies==2,"orbiter releases and one additional Attack Fly is born");
        } else if(variant==21) {
            for(int n=0;n<8;++n){Event hit;hit.type=EventType::Damage;hit.target=actor;hit.damage=.01f;hit.weakPointHit=true;s.queueRoot(hit);s.drainEvents();ticks(s,19);}
            int flies=0;for(const auto &child:s.enemies)flies+=child.alive&&child.summoner==actor&&child.monster==monsterId(18);
            check(flies==5,"pulsating spawn population capped at five");
        } else if(variant==22) {
            const auto other=s.spawnMonster(monsterId(23),{8,.85f,0});const auto hp=s.findEnemy(other)->hp;ticks(s,1);
            check(s.findEnemy(other)->crowned&&s.findEnemy(other)->champion<0&&near(s.findEnemy(other)->hp,hp)&&near(s.findEnemy(other)->championSpeed,1),"crown changes color without granting combat stats");
            kill(s,actor);ticks(s,1);check(!s.findEnemy(other)->crowned,"crown effect ends with owner");
        } else if(variant==23) {
            const auto other=s.spawnMonster(monsterId(23),{8,.85f,0});s.arena.obstacles.push_back({{3,-1,-5},{4,5,5}});s.arena.rebuildWalls();
            kill(s,actor);check(!s.findEnemy(other)->alive,"skull damages enemies across room through cover");
            check(near(s.player.hp,100),"skull room effect does not hurt player");
        } else if(variant==24) {
            ticks(s,1);check(!s.arena.breakables.empty()&&s.arena.breakables.back().kind==BreakableKind::Dung,"brown deposits real destructible dung");
            check(!s.arena.blocked(s.findEnemy(actor)->position,s.findEnemy(actor)->radius),"dung does not trap emitting actor");
        } else {
            ticks(s,80);check(!s.hazards.empty()&&!s.projectiles.empty(),"rainbow combines creep and periodic shots");
            s.projectiles.clear();kill(s,actor);check(s.projectiles.size()>=8,"rainbow emits eight death shots with explosion");
        }
    }
    // Integration keeps Level2's real source-frame armor and delayed damage.
    auto armored=fixture();auto actor=spawn(armored,monsterId(855));armored.makeChampion(actor,12);
    kill(armored,actor);check(!armored.findEnemy(actor)->championPile,"adaptive armor delays first lethal hit until source frame");
    ticks(armored,3);check(armored.findEnemy(actor)&&armored.findEnemy(actor)->championPile,"real armored Level2 enters champion pile after damage replay");
    kill(armored,actor);ticks(armored,3);check(!armored.findEnemy(actor)&&armored.stats.kills==1,"real armored champion pile can be finished once");
    auto rainbow=fixture();actor=spawn(rainbow,monsterId(23));rainbow.makeChampion(actor,25);rainbow.limits.projectiles=2;
    kill(rainbow,actor);check(rainbow.findEnemy(actor)->championDeathPending&&rainbow.stats.explosions==1,"rainbow retains partial volley after one explosion");
    rainbow.projectiles.clear();ticks(rainbow,1);check(rainbow.stats.explosions==1,"rainbow retry never repeats death explosion");
    rainbow.limits.projectiles=100;rainbow.projectiles.clear();ticks(rainbow,1);check(!rainbow.findEnemy(actor)&&rainbow.stats.explosions==1,"rainbow completes retained volley and retires");
    std::cout<<"CHAMPION_LIFECYCLES new_types=8 charger_combinations=40 collapse=1 split=1 orbiter=1 capped_spawn=1 crown=1 skull=1 dung=1 rainbow=1\n";
}

int main(){try{drowned();dank();princess();levelTwo();startingKit();regressions();pools();natural();championColors();championFields();championLifecycles();std::cout<<"PASS Charger variants and weak-point collision\n";return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
