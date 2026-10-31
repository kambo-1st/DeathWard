#include "combat/Simulation.hpp"

namespace dw {
namespace {
template<size_t N> int pick(Random &rng,const std::array<int,N> &weights) {
    int sum=0;for(int w:weights)sum+=w;
    if(!sum)return -1;
    int roll=int(rng.bounded(uint32_t(sum)));
    for(size_t i=0;i<N;++i)if((roll-=weights[i])<0)return int(i);
    return -1;
}
}
EntityId Simulation::spawnHornfel(MonsterId id,Vector3 center) {
    auto &progress=rooms.at(size_t(room));
    if(progress.hornfel&&!progress.hornfel->completed)return 0;
    if(livingEnemies()+pendingMonsters_.size()>=limits.enemies)return 0;
    const auto &p=*content->hornfel(id);const auto &d=*content->monster(id);
    if(!arena.rails) {
        // Isolated test/editor spawn. Generated floors already select dimensions
        // and a source template before terrain and corridor generation.
        arena.profile.bossRails=std::make_shared<RailLayout>(*content->railLayout(p.layouts.front().first));
        arena.prepareRailArena(room);
    }
    HornfelRuntime h;h.owner=spawn(EnemyKind::Boss,center);if(!h.owner)return 0;
    auto &e=enemies.back();e.monster=id;e.bossKind=BossKind::Isaac;
    e.hp=e.maxHp=d.hp;e.radius=d.radius;e.state=EnemyState::Teleporting;
    h.cart.id=nextEntity_++;h.cart.rider=e.id;
    for(auto point:arena.rails->doors)h.doors.push_back({nextEntity_++,monsterId(967),point,0,false});
    h.clock=p.doorTime;progress.hornfel=std::move(h);return e.id;
}

bool Simulation::hornfelCartLoss(Enemy &e,const Event &event) {
    auto &slot=rooms[size_t(room)].hornfel;
    if(!slot||slot->owner!=e.id||!slot->cart.intact||event.debugExecution)return false;
    auto &h=*slot;const auto &p=*content->hornfel(e.monster);
    h.cart.intact=h.cart.visible=false;h.cart.rider=0;
    h.state=HornfelState::Sad;h.clock=32.f/30;h.attack=-1;h.payloads.clear();h.targets.clear();
    h.chargeSelected=false;h.repeatsLeft=0;h.mainReserved=false;
    for(auto &door:h.doors)door.requested=false;
    e.hp=e.maxHp=p.fleeHealth;e.phase=1;e.state=EnemyState::Stunned;e.velocity={};
    // A cart may be over a pit or at a wall when destroyed. Grounded Hornfel
    // dismounts at the nearest legal point, not into terrain he cannot leave.
    auto at=e.position;at.y=e.radius+.05f;bool found=arena.roomAt(at)==room&&!arena.blocked(at,e.radius);
    if(found)e.position=at;
    for(int ring=1;!found&&ring<=24;++ring)for(int n=0;n<32;++n) {
        auto q=add(at,rotateY({float(ring)*.5f,0,0},float(n)*Pi/16));
        if(arena.roomAt(q)==room&&!arena.blocked(q,e.radius)) {e.position=q;found=true;break;}
    }
    if(!found)e.position=arena.rooms[size_t(room)].bossSpawn;
    particleEffect(ParticleEffect::Wood,e.position,{0,1,0},1);checkpointNeeded=true;return true;
}

void Simulation::finishHornfel(Enemy &e,bool escaped) {
    auto &slot=rooms[size_t(room)].hornfel;if(!slot||slot->owner!=e.id||slot->completed)return;
    auto &h=*slot;h.completed=true;h.escaped=escaped;h.state=HornfelState::Finished;
    h.cart.visible=false;h.cart.intact=false;h.cart.rider=0;
    for(auto &door:h.doors)door.requested=false;
    h.mainReserved=false;
    if(escaped) {
        e.alive=false;e.velocity={};bossKilled=true;
        // Escape resolves the encounter, but is not a kill or a three-bomb bonus.
        rewardCanyonBoss(e);checkpointNeeded=true;
    }
}

void Simulation::updateHornfel(Enemy &e,float dt) {
    auto &slot=rooms[size_t(room)].hornfel;if(!slot||slot->owner!=e.id||slot->completed||!arena.rails)return;
    auto &h=*slot;const auto &p=*content->hornfel(e.monster);const auto &network=*arena.rails;
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.velocity={};h.clock-=dt;h.mineCooldown=std::max(0.f,h.mineCooldown-dt);
    h.chargeCooldown=std::max(0.f,h.chargeCooldown-dt);
    h.activeAge+=dt;h.decoyCooldown=std::max(0.f,h.decoyCooldown-dt);
    if(h.state==HornfelState::Outside) {
        if(h.clock>.00001f)return;
        const int next=selectHornfelRoute(false);
        if(next<0){h.clock=p.doorTime;return;}
        h.cart.route=next;h.cart.distance=0;h.mainReserved=true;
        const auto &route=network.paths[size_t(h.cart.route)];
        selectHornfelDecoys();
        // The source decoy branch has priority over charge selection.
        h.chargeSelected=!h.decoySelected&&route.entry!=route.exit&&h.chargeCooldown<=0&&p.chargeChance>0&&
            combatRng.bounded(10000)<uint32_t(p.chargeChance);
        for(auto &door:h.doors)door.requested=false;
        h.doors[size_t(route.entry)].requested=true;h.state=HornfelState::Opening;h.clock=p.doorTime;
        return;
    }
    if(h.state==HornfelState::Opening) {
        if(h.clock>.00001f)return;
        h.state=HornfelState::Riding;h.cart.visible=true;h.clock=p.attackDelay;
        e.state=EnemyState::Ready;e.bossAttack=-1;h.attack=-1;h.attackClock=0;
        if(h.decoySelected) {
            h.state=HornfelState::DecoyRun;e.bossAttack=5;h.clock=1+combatRng.real(0,1);++h.decoyRuns;
        }
        if(h.chargeSelected) {
            h.state=HornfelState::Charging;e.state=EnemyState::Charging;e.bossAttack=3;
            h.drive=p.driveStart;h.nativeVelocity=1;h.driveClock=0;h.bombClock=p.bombInterval;
            h.repeatsChosen=p.repeatMin+int(combatRng.bounded(uint32_t(p.repeatMax-p.repeatMin+1)));
            h.repeatsLeft=h.repeatsChosen;h.chargePasses=0;h.chargeCooldown=p.chargeCooldown;++h.charges;
            h.doors[size_t(network.paths[size_t(h.cart.route)].exit)].requested=true;
        }
        selectHornfelEscorts();
    }
    if(h.state==HornfelState::RecoveryEntry) {
        if(h.clock>.00001f)return;
        h.state=HornfelState::Recovering;h.cart.distance=0;h.cart.visible=true;
        h.nativeVelocity=1;h.driveClock=0;h.recoveryClock=0;h.recoveryShot=false;h.targets.clear();
        e.state=EnemyState::Windup;e.bossAttack=4;
    }
    if(h.state==HornfelState::Sad) {
        if(h.clock>.00001f)return;
        h.state=HornfelState::Fleeing;h.clock=3;h.escapeDoor=-1;h.path.clear();
        e.state=EnemyState::Ready;e.facing=unit(sub(e.position,player.position));return;
    }
    if(h.state==HornfelState::Fleeing) {
        auto destination=add(e.position,mul(unit(sub(e.position,player.position)),3));
        if(h.clock<=0) {
            if(h.escapeDoor<0) {
                std::vector<std::pair<float,size_t>> candidates;
                for(size_t i=0;i<network.doors.size();++i) {
                    candidates.emplace_back(planarDistance(e.position,network.doors[i]),i);
                }
                std::sort(candidates.begin(),candidates.end());
                for(const auto &[distance,i]:candidates) {
                    auto target=sub(network.doors[i],mul(railDirection(network.doorSides[i]),e.radius+.2f));target.y=e.position.y;
                    if(arena.blocked(target,e.radius))continue;
                    auto path=arena.path(e.position,target,e.radius);
                    if(!path.empty()){h.escapeDoor=int(i);h.path=std::move(path);break;}
                }
                if(h.escapeDoor>=0)h.doors[size_t(h.escapeDoor)].requested=true;
            }
            if(h.escapeDoor>=0) {
                destination=sub(network.doors[size_t(h.escapeDoor)],mul(railDirection(network.doorSides[size_t(h.escapeDoor)]),e.radius+.2f));destination.y=e.position.y;
                if(planarDistance(e.position,destination)<.65f&&h.doors[size_t(h.escapeDoor)].openness>.99f){finishHornfel(e,true);return;}
                while(!h.path.empty()&&planarDistance(e.position,h.path.front())<.45f)h.path.erase(h.path.begin());
                if(!h.path.empty())destination=h.path.front();
            }
        }
        // The flattened terrain shoulder can extend beyond the source room.
        // Grounded Hornfel must stay within its navigation footprint until his
        // chosen door resolves the escape; walking off it strands floorPath.
        const auto &bounds=arena.rooms[size_t(room)].bounds;
        destination.x=std::clamp(destination.x,bounds.min.x+e.radius+.1f,bounds.max.x-e.radius-.1f);
        destination.z=std::clamp(destination.z,bounds.min.z+e.radius+.1f,bounds.max.z-e.radius-.1f);
        const auto from=e.position;e.facing=unit(horizontal(sub(destination,from)));
        e.position=arena.move(from,mul(e.facing,std::min(p.fleeSpeed*dt,planarDistance(from,destination))),e.radius);
        e.velocity=mul(sub(e.position,from),1/std::max(dt,.00001f));
        if(planarDistance(from,e.position)<.001f&&h.escapeDoor>=0){h.escapeDoor=-1;h.path.clear();}
        if(segmentSphere(from,e.position,player.position,e.radius+.48f)<=1&&arena.sight(e.position,player.position)) {
            Context source;source.sourceEntity=e.id;hurtPlayer(p.fleeContact,source);
        }
        return;
    }
    const bool charging=h.state==HornfelState::Charging,recovering=h.state==HornfelState::Recovering;
    const bool decoyRun=h.state==HornfelState::DecoyRun;
    if(h.state!=HornfelState::Riding&&!charging&&!recovering&&!decoyRun)return;
    float speed=p.speed;
    if(charging||recovering) {
        // Retain the recovered drive/force/friction relation. Fixed30Hz updates
        // and world conversion are explicit adaptations to DeathWard's60Hz step.
        h.driveClock+=dt;
        while(h.driveClock+.000001f>=1.f/30) {
            h.driveClock-=1.f/30;
            if(charging)h.drive=std::min(p.driveMax,h.drive+p.driveIncrement);
            else h.drive=h.recoveryShot?std::min(p.recoveryDrive,h.drive+p.recoveryAcceleration):
                std::max(p.recoveryFloor,h.drive-p.recoveryDeceleration);
            h.nativeVelocity=(h.nativeVelocity+p.driveForce*h.drive)*p.retention;
        }
        speed=std::min(p.nativeTravelCap,h.nativeVelocity)*p.nativeScale*30;
    }
    const auto &route=network.paths[size_t(h.cart.route)];
    const auto travel=route.advance(h.cart.distance,speed*dt);h.cart.distance=travel.distance;
    h.cart.position=travel.pose.position;h.cart.direction=travel.pose.direction;
    e.position=add(h.cart.position,{0,e.radius+.25f,0});e.facing=travel.pose.direction;e.velocity=mul(e.facing,speed);
    if(route.length()-h.cart.distance<speed*p.doorTime+2)h.doors[size_t(route.exit)].requested=true;
    // Swept contacts follow each actual curve segment, including fast movement.
    Context source;source.sourceEntity=e.id;
    for(auto segment:travel.swept) {
        segment[0].y=segment[1].y=player.position.y;
        if(segmentSphere(segment[0],segment[1],player.position,e.radius+.48f)<=1)hurtPlayer(p.contact,source);
    }
    if(charging) {
        h.bombClock-=dt;
        const auto &bounds=arena.rooms[size_t(room)].bounds;const float inset=20*p.nativeScale;
        const bool inside=e.position.x>=bounds.min.x+inset&&e.position.x<=bounds.max.x-inset&&
            e.position.z>=bounds.min.z+inset&&e.position.z<=bounds.max.z-inset;
        if(h.bombClock<=0&&inside&&!travel.pose.finished) {
            if(h.targets.empty())h.targets.push_back(add(e.position,rotateY({combatRng.real(0,p.bombScatter),0,0},combatRng.real(0,2*Pi))));
            if(throwEnemyBomb("hornfel_normal",e.id,e.position,h.targets.front())) {
                ++h.chargeBombs;h.targets.clear();h.bombClock=p.bombInterval;
            }
        }
        if(travel.pose.finished) {
            ++h.passes;++h.chargePasses;h.targets.clear();
            if(h.repeatsLeft>0) {
                --h.repeatsLeft;h.cart.distance=0;h.nativeVelocity=1;
                const auto entry=route.sample(0);h.cart.position=entry.position;h.cart.direction=entry.direction;
                e.position=add(entry.position,{0,e.radius+.25f,0});e.facing=entry.direction;
                // The reposition has no swept segment: only the real preceding
                // rail traversal above can collide with the player.
                e.velocity={};
            } else {
                h.state=HornfelState::RecoveryEntry;h.clock=p.recoveryDelay;
                h.drive=std::min(h.drive,p.recoveryEntryDrive);h.cart.visible=false;
                e.state=EnemyState::Teleporting;e.velocity={};
            }
        }
        return;
    }
    if(recovering) {
        h.recoveryClock+=dt;
        if(!h.recoveryShot&&h.recoveryClock+.00001f>=46.f/30) {
            if(h.targets.empty()) {
                auto target=add(player.position,mul(player.velocity,p.recoveryPrediction));
                const auto &bounds=arena.rooms[size_t(room)].bounds;
                target.x=std::clamp(target.x,bounds.min.x+.5f,bounds.max.x-.5f);
                target.z=std::clamp(target.z,bounds.min.z+.5f,bounds.max.z-.5f);
                target.y=(arena.canyon?arena.canyon->height(target.x,target.z):0)+.44f;
                h.targets.push_back(target);
            }
            const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &event){return event.type==EventType::Shot;});
            if(projectiles.size()+size_t(queued)<limits.projectiles) {
                const auto start=add(e.position,add(mul(e.facing,.6f),{0,.5f,0}));
                auto velocity=mul(sub(h.targets.front(),start),1/p.recoveryFlight);velocity.y+=.5f*p.recoveryGravity*p.recoveryFlight;
                Event shot;shot.position=shot.origin=start;shot.direction=unit(velocity);shot.speed=length(velocity);
                shot.hostile=true;shot.damage=p.recoveryDamage;shot.projectileGravity=p.recoveryGravity;
                shot.projectileLife=p.recoveryFlight+2;shot.projectileKind=ProjectileKind::Ember;
                shot.fireWave=p.fireWave;shot.context.sourceEntity=e.id;
                if(queueRoot(shot)) {
                    h.recoveryShot=true;++h.recoveryShots;h.targets.clear();e.state=EnemyState::Ready;
                    audioCues.push(AudioCueKind::MonsterAttack,e.position);
                }
            }
        }
        // ChargeFinish's87frames are animation length, not a state timeout.
        if(!travel.pose.finished||!h.recoveryShot)return;
        ++h.attacks;++e.bossCycles;
    }
    if(decoyRun&&h.clock<=0)e.state=EnemyState::Windup; // Taunt while decoys cross.
    if(!decoyRun&&!recovering&&h.attack<0&&h.clock<=0&&!travel.pose.finished) {
        auto weights=p.attacks;if(h.mineCooldown>0)weights[2]=0;
        h.attack=pick(combatRng,weights);h.event=0;h.attackClock=0;h.payloads.clear();h.targets.clear();
        if(h.attack>=0) {
            const int count=h.attack==2?((arena.profile.bossRails->width+2)*(arena.profile.bossRails->height+2)>135?4:3):h.attack+1;
            for(int i=0;i<count;++i)h.payloads.push_back(h.attack==2?"brimstone":std::array{"hornfel_normal","hot","sad"}[size_t(pick(combatRng,p.bombs))]);
            if(h.attack==2)h.mineCooldown=p.mineCooldown;
            e.bossAttack=h.attack;e.state=EnemyState::Windup;
        } else h.clock=p.attackDelay;
    }
    if(h.attack>=0) {
        h.attackClock+=dt;
        const float trigger=h.attack==2?34.f/30:h.event==0?17.f/30:27.f/30;
        if(h.event<int(h.payloads.size())&&h.attackClock+.00001f>=trigger) {
            const int amount=h.attack==2?int(h.payloads.size()):1;
            // One mine salvo is indivisible. Capacity pressure retains its action
            // and targets for retry, without consuming more random choices.
            if(h.targets.empty()) {
                for(int i=0;i<amount;++i) {
                    auto target=player.position;
                    if(h.attack==2) {
                        float best=-1;
                        for(int n=0;n<8;++n) {
                            auto candidate=add(player.position,rotateY({combatRng.real(2,8),0,0},combatRng.real(0,2*Pi)));
                            if(arena.roomAt(candidate)!=room||arena.blocked(candidate,.3f))continue;
                            float spacing=planarDistance(candidate,e.position);
                            for(auto other:h.targets)spacing=std::min(spacing,planarDistance(candidate,other));
                            if(spacing>best){best=spacing;target=candidate;}
                        }
                    } else {
                        // Native prediction uses target velocity, distance and a
                        // random .1-.3 factor. This is an explicit seconds/world-unit adaptation.
                        target=add(target,mul(player.velocity,combatRng.real(.1f,.3f)));
                    }
                    h.targets.push_back(target);
                }
            }
            if(enemyBombs.size()+pendingEnemyBombs.size()+size_t(amount)<=limits.enemyBombs+limits.pendingEnemyBombs) {
                bool emitted=true;
                for(int i=0;i<amount;++i) {
                    auto start=e.position;const auto &b=arena.rooms[size_t(room)].bounds;
                    start.x=std::clamp(start.x,b.min.x+.02f,b.max.x-.02f);start.z=std::clamp(start.z,b.min.z+.02f,b.max.z-.02f);
                    if(!throwEnemyBomb(h.payloads[size_t(h.event+i)],e.id,start,h.targets[size_t(i)])){emitted=false;break;}
                }
                if(emitted){h.event+=amount;h.targets.clear();}
            }
        }
        const float duration=h.attack==2?56.f/30:h.attack==1?40.f/30:1;
        if(h.event==int(h.payloads.size())&&h.attackClock>=duration) {
            ++h.attacks;++e.bossCycles;h.attack=-1;h.clock=p.attackDelay;e.state=EnemyState::Ready;
        }
    }
    if(travel.pose.finished&&h.attack<0) {
        releaseHornfelEscorts(e.id);
        ++h.passes;h.cart.visible=false;h.state=HornfelState::Outside;h.clock=p.outside;
        e.state=EnemyState::Teleporting;e.velocity={};for(auto &door:h.doors)door.requested=false;
    }
}
} // namespace dw
