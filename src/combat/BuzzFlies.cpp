#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateBuzzFly(Enemy &e,float dt) {
    const auto &p=*content->buzzFly(e.monster);
    if(!e.buzz)e.buzz=BuzzFlyRuntime{};
    auto &r=*e.buzz;
    auto requestContactDeath=[&] {
        if(std::any_of(queue_.begin(),queue_.end(),[&](const auto &event){return event.type==EventType::Damage&&event.target==e.id&&event.execution;}))return;
        Event death;death.type=EventType::Damage;death.target=e.id;death.position=e.position;
        death.damage=e.hp+1;death.execution=true;death.context.sourceEntity=e.id;queueRoot(death);
    };
    // A full queue must not let an already spent contact fly resume pursuit.
    if(e.selfDetonated){requestContactDeath();return;}
    if(!r.initialized) {
        r.tick=uint64_t(std::max(0.,std::floor((stats.duration-dt)*30+.00001)));
        r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));r.initialized=true;
    }
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    const bool suppressed=p.suppressor&&!e.friendly&&itemStacks(*p.suppressor)>0;
    const bool itemMorph=p.morphItem&&!e.friendly&&itemStacks(*p.morphItem)>0;
    if(!suppressed) {
        e.cooldown=std::max(0.f,e.cooldown-dt);
        // A source delay such as 63 frames must not miss the next seven-frame
        // acquisition check because repeated float subtraction leaves dust.
        if(e.cooldown<.00001f)e.cooldown=0;
    }
    e.lift=0;
    if(e.state==EnemyState::Stunned) {
        r.attackFrame=-1;r.fired=false;r.clock=0;r.momentum={};e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0)e.state=EnemyState::Ready;
        return;
    }
    r.clock+=dt;
    while(r.clock+1e-6f>=1.f/30) {
        r.clock=std::max(0.f,r.clock-1.f/30);++r.tick;
        if(r.healingTicks>0) {
            e.hp=std::min(e.maxHp,e.hp+e.maxHp/float(r.healingDivisor));--r.healingTicks;
        }
        if(itemMorph) {
            const auto *body=content->monster(p.itemMorph);
            e.monster=p.itemMorph;e.maxHp=content->monsterHealth(p.itemMorph,arena.profile.sourceStage);
            e.hp=std::min(e.hp,e.maxHp);e.radius=body->radius;
            e.cooldown=0;e.state=EnemyState::Ready;e.stateTime=0;e.path.clear();e.pathTime=0;e.behavior={};
            r.attackFrame=-1;r.fired=false;r.target={};r.targetReady=false;r.wander={};
            // Morph preserves identity, remaining HP, momentum and the live-
            // summon contact flag. It is not a death or a new reward source.
            return;
        }
        if(p.morphChance&&combatRng.bounded(unsigned(p.morphChance))==0) {
            // The native test checks grid type, including its destroyed remnant.
            // Hurt may do nothing to a spent pile; morphing does not depend on it.
            for(auto &prop:arena.breakables)if(prop.kind==BreakableKind::Dung&&prop.room==room&&
                e.position.x>=prop.bounds.min.x&&e.position.x<prop.bounds.max.x&&
                e.position.z>=prop.bounds.min.z&&e.position.z<prop.bounds.max.z) {
                hitBreakable(prop,1,false);
                const auto *body=content->monster(p.morph);
                e.monster=p.morph;e.hp=e.maxHp=content->monsterHealth(p.morph,arena.profile.sourceStage);
                e.radius=body->radius;e.cooldown=0;e.state=EnemyState::Ready;e.stateTime=0;
                e.path.clear();e.pathTime=0;e.behavior={};r.attackFrame=-1;r.fired=false;r.wander={};
                // Keep actor identity, realized momentum and reward accounting.
                // The new shooter's first update is the next fixed tick.
                particleEffect(ParticleEffect::Dirt,e.position,{0,1,0},.4f);return;
            }
        }
        float friction=1;
        if(p.shot) {
            const auto &s=*p.shot;
            if(r.attackFrame>=0) {
                if(r.attackFrame<s.shootFrame||r.fired||suppressed)++r.attackFrame;
                // An item acquired during the animation consumes its Shoot
                // event silently. Removing the item must not replay that event.
                if(suppressed&&r.attackFrame>=s.shootFrame)r.fired=true;
                if(r.attackFrame==s.shootFrame&&!r.fired&&!suppressed) {
                    const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const auto &event){return event.type==EventType::Shot;});
                    const size_t count=!p.volley.empty()?p.volley.size():(p.paired?2:1);
                    // Reserve the whole volley before any member is queued;
                    // each root event also needs a chain slot.
                    if(queue_.size()+count<=limits.queuedEvents&&projectiles.size()+size_t(queued)+count<=limits.projectiles&&limits.eventsPerChain>0) {
                        auto aim=unit(sub(player.position,e.position));if(length(aim)<.001f)aim=e.facing;
                        for(size_t i=0;i<count;++i) {
                            auto velocity=mul(aim,s.speed);
                            if(p.paired||!p.volley.empty()) {
                                const auto v=p.volley.empty()?Vector2{p.pairForward,i==0?p.pairSide:-p.pairSide}:p.volley[i];
                                velocity={s.speed*(v.x*aim.x-v.y*aim.z),velocity.y,
                                          s.speed*(v.x*aim.z+v.y*aim.x)};
                            }
                            Event shot;shot.hostile=true;shot.context.sourceEntity=e.id;
                            shot.position=shot.origin=e.position;shot.direction=unit(velocity);
                            shot.speed=length(velocity);shot.damage=s.damage;shot.projectileLife=s.life;
                            shot.projectileRadius=p.shotRadius;shot.projectileSplit=p.impactSplit;
                            if(p.impactSplit)shot.projectileKind=ProjectileKind::SplitShot;
                            queueRoot(shot);
                        }
                        r.fired=true;audioCues.push(AudioCueKind::MonsterAttack,e.position);
                    }
                }
                if(r.attackFrame>=s.attackFrames){r.attackFrame=-1;r.fired=false;e.state=EnemyState::Ready;e.stateTime=0;}
                else {e.state=EnemyState::Windup;e.stateTime=float(s.attackFrames-r.attackFrame)/30;}
            }
            if(!suppressed&&r.attackFrame<0&&e.cooldown<=1e-6f&&(r.tick+e.id)%unsigned(s.checkFrames)==0&&
                planarDistance(e.position,player.position)<s.range&&arena.sight(e.position,player.position)) {
                r.attackFrame=0;r.fired=false;e.state=EnemyState::Windup;e.stateTime=float(s.attackFrames)/30;
                e.cooldown=float(s.cooldownFrames)/30;e.target=player.position;
                audioCues.push(AudioCueKind::Warning,e.position);
            }
            if(!suppressed&&e.cooldown>0){friction*=p.cooldownRetention;r.wander=mul(r.wander,p.cooldownWander);}
        }
        if(p.chase) {
            const auto &c=*p.chase;
            if(r.tick%unsigned(c.targetFrames)==0){r.target=player.position;r.targetReady=true;}
            if(r.targetReady&&r.tick%unsigned(c.forceFrames)==0) {
                auto delta=mul(horizontal(sub(r.target,e.position)),1/p.scale);
                delta.z*=c.axisScale;
                if(r.diesOnContact)friction*=r.contactRetention;
                const float distance=length(delta);
                if(distance>c.deadzone)r.momentum=add(r.momentum,mul(unit(delta),std::min((distance-c.deadzone)*c.gain,c.force)*e.championSpeed/friction));
            }
        // Ordinary Fly/Pooter discard their temporary dung-search target. Their
        // actual pursuit is an intermittent impulse, not a path-following chase.
        } else if(combatRng.bounded(unsigned(p.pursuitChance))==0)
            r.momentum=add(r.momentum,mul(unit(horizontal(sub(player.position,e.position))),p.pursuit*e.championSpeed));
        if(r.tick%4==1)
            r.wander=mul(add(r.wander,rotateY({p.jitter,0,0},combatRng.real(0,2*Pi))),p.jitterRetention);
        if(r.tick%3==2) {
            const auto &bounds=arena.rooms[size_t(room)].bounds;
            const float margin=std::min(p.edgeMargin,std::min(bounds.max.x-bounds.min.x,bounds.max.z-bounds.min.z)*.25f);
            if(e.position.x<bounds.min.x+margin)r.wander.x+=p.edge;
            else if(e.position.x>bounds.max.x-margin)r.wander.x-=p.edge;
            if(e.position.z<bounds.min.z+margin)r.wander.z+=p.edge;
            else if(e.position.z>bounds.max.z-margin)r.wander.z-=p.edge;
            // AddVelocity divides its impulse by current friction before the
            // common movement update applies friction. Pooter's cooldown slows
            // existing momentum without suppressing the same-frame buzz force.
            r.momentum=add(r.momentum,mul(r.wander,2*e.championSpeed/friction));friction*=p.retention;
        }
        r.momentum=mul(r.momentum,friction);
    }
    auto velocity=mul(r.momentum,p.scale*30);
    if(length(velocity)>p.speedCap)velocity=mul(unit(velocity),p.speedCap);
    const auto previous=e.position;
    moveMonster(e,velocity,dt);
    r.momentum=mul(horizontal(e.velocity),1/(p.scale*30));
    if(length(horizontal(e.velocity))>.001f)e.facing=unit(horizontal(e.velocity));
    if(r.attackFrame>=0&&!r.fired)e.target=player.position;
    // Preserve vertical separation and test relative motion, including dodges.
    // Fly/Pooter are harmless; a morphed live Hive child still expires on touch.
    if(!e.friendly&&(p.chase||r.diesOnContact)&&
       segmentSphere(sub(previous,playerStepStart_),sub(e.position,player.position),{},e.radius+.48f)<=1&&
       arena.sight(e.position,player.position)) {
        if(p.chase&&!itemMorph){Context source;source.sourceEntity=e.id;hurtPlayer(p.chase->contact,source);}
        if(r.diesOnContact){e.selfDetonated=true;requestContactDeath();}
    }
}

void Simulation::prepareDung() {
    if(!content->dung()||!arena.profile.active())return;
    const auto &p=*content->dung();
    if(arena.profile.band<p.firstBand||arena.profile.band>p.lastBand)return;
    Random rng(seed_^0x44554e4750524f50ULL);
    std::vector<int> candidates;
    for(int index=1;index<arena.roomCount()-1;++index)
        if(arena.rooms[size_t(index)].kind==RoomKind::Combat&&arena.rooms[size_t(index)].story==StoryRoom::None)candidates.push_back(index);
    for(size_t i=0;i<candidates.size();++i)std::swap(candidates[i],candidates[i+rng.bounded(unsigned(candidates.size()-i))]);
    int placed=0;
    for(int index:candidates) {
        if(placed>=p.count)break;
        const auto &layout=arena.rooms[size_t(index)];
        for(int attempt=0;attempt<100;++attempt) {
            const float margin=p.halfWidth+1;
            if(layout.bounds.max.x-layout.bounds.min.x<margin*2||layout.bounds.max.z-layout.bounds.min.z<margin*2)break;
            Vector3 at{rng.real(layout.bounds.min.x+margin,layout.bounds.max.x-margin),.85f,rng.real(layout.bounds.min.z+margin,layout.bounds.max.z-margin)};
            Box box{{at.x-p.halfWidth,0,at.z-p.halfWidth},{at.x+p.halfWidth,p.height,at.z+p.halfWidth}};
            bool clear=!arena.reservedSupplyCache(at,p.halfWidth+1)&&!arena.blocked(at,p.halfWidth+.6f);
            if(arena.supplyCache.room>=0&&(sphereBox(arena.supplyCache.approach,1.5f,box)||
                segmentBox(arena.supplyCache.approach,arena.supplyCache.reward,box,.6f).hit))clear=false;
            for(const auto &prop:arena.breakables)if(sphereBox(at,p.halfWidth+1,prop.bounds))clear=false;
            for(const auto &key:arena.keys)if(sphereBox(key.position,1.5f,box))clear=false;
            for(auto dest:{layout.entry,layout.exit,layout.objective})
                if(sphereBox(dest,1.4f,box)||segmentBox(layout.center,dest,box,1.25f).hit)clear=false;
            for(int link:layout.passages) {
                const auto dest=arena.doorApproach(link,arena.passages[size_t(link)].rooms[0]==index?0:1);
                if(sphereBox(dest,1.4f,box)||segmentBox(layout.center,dest,box,1.25f).hit)clear=false;
            }
            if(arena.canyon)for(float x:{box.min.x,box.max.x})for(float z:{box.min.z,box.max.z}) {
                const Vector3 point{x,.85f,z};const auto river=arena.canyon->riverSample(point);const auto road=arena.canyon->roadSample(point);
                if(std::abs(arena.canyon->height(x,z))>.035f||river.distance<river.width+1||road.distance<road.width+.7f)clear=false;
            }
            if(!clear||arena.path(layout.center,at,.48f).empty())continue;
            Breakable prop;prop.id=0xd0000000ULL+uint64_t(index);prop.lootSeed=seed_^prop.id;
            prop.kind=BreakableKind::Dung;prop.room=index;prop.bounds=box;prop.rewardPosition=at;prop.health=p.hits;prop.initialHealth=p.hits;
            arena.breakables.push_back(prop);arena.rebuildWalls();++placed;break;
        }
    }
}
} // namespace dw
