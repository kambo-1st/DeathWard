#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::platesComplete() const {
    const auto &plates=rooms[size_t(room)].plates;
    return !plates.empty()&&std::all_of(plates.begin(),plates.end(),[](const auto &p){return p.pressed;});
}
void Simulation::refreshStatues() {
    const auto &progress=rooms[size_t(room)];
    for(auto &e:enemies)if(const auto *s=content->statue(e.monster)) {
        e.statueDisabled=s->clear!=StatueClear::Never&&
            (platesComplete()||(s->clear==StatueClear::Combat&&roomClear&&!progress.trapOnly));
        if(e.statueDisabled){e.state=EnemyState::Ready;e.stateTime=0;}
    }
    // A pressure plate closes active beams immediately; an already-emitted
    // projectile keeps its ordinary lifetime and collision behavior.
    for(auto &h:hazards)if(h.ownerBound) {
        const auto *owner=findEnemy(h.context.sourceEntity);
        if(owner&&content->statue(owner->monster)&&owner->statueDisabled)h.duration=0;
    }
    refreshStatueAttraction();
}
void Simulation::refreshStatueAttraction(float dt) {
    statueAttractors_.clear();
    for(auto &e:enemies)if(const auto *s=content->statue(e.monster);s&&s->attack==StatueAttack::Attraction) {
        e.statuePullActive=false;
        if(!e.alive)continue;
        if(s->activeSeconds>0)e.statuePhase=std::fmod(e.statuePhase+double(dt),double(s->activeSeconds)+s->inactiveSeconds);
        const bool disabled=s->clear!=StatueClear::Never&&
            (platesComplete()||(s->clear==StatueClear::Combat&&roomClear&&!rooms[size_t(room)].trapOnly));
        e.statuePullActive=!disabled&&(s->activeSeconds==0||e.statuePhase<double(s->activeSeconds));
        if(e.statuePullActive)statueAttractors_.push_back({e.position,s});
    }
}
Vector3 Simulation::statueAttraction(Vector3 position,bool projectile,float *speedLimit,bool championFields) const {
    Vector3 force{};float maximum=0;
    // Unentered rooms and corridors have no active attraction field.
    if(arena.roomAt(position)!=room)return force;
    for(const auto &field:statueAttractors_) {
        const auto &s=*field.definition;auto toward=horizontal(sub(field.position,position));const float d=length(toward);
        if(d<.0001f||d>=s.range||std::abs(position.y-field.position.y)>s.pullHeight)continue;
        const float strength=(projectile?s.projectilePull:s.playerPull)*(1-d/s.range);
        force=add(force,mul(toward,strength/d));maximum=std::max(maximum,projectile?s.projectilePull:s.playerPull);
        if(speedLimit)*speedLimit=std::max(*speedLimit,s.projectileLimit);
    }
    if(championFields)for(const auto &e:enemies)if(e.alive&&!e.friendly&&!e.affectedBy(EnemyStatus::Freeze)&&
        (e.championEffect(11)||(projectile&&e.champion==16&&std::fmod(e.age,2.f)<.3f))) {
        auto toward=horizontal(sub(e.position,position));const float d=length(toward);
        if(d<.001f||d>=20||std::abs(position.y-e.position.y)>3)continue;
        const float power=projectile?32.f:4.f;
        force=add(force,mul(toward,(e.champion==16?-1:1)*power*(1-d/20)/d));
        maximum=std::max(maximum,power);if(projectile&&speedLimit)*speedLimit=std::max(*speedLimit,80.f);
    }
    // Opposing fields cancel; stacked fields remain counterable. These force
    // units, falloff, vertical extent and aggregate cap are explicit 3D tuning.
    const float magnitude=length(force);
    return magnitude>maximum&&magnitude>0?mul(force,maximum/magnitude):force;
}
void Simulation::updatePressurePlates() {
    bool changed=false;
    for(auto &plate:rooms[size_t(room)].plates)if(!plate.pressed&&
        planarDistance(player.position,plate.position)<.65f&&std::abs(player.position.y-.85f)<.4f) {
        plate.pressed=true;changed=true;
        audioCues.push(AudioCueKind::Door,plate.position);
    }
    if(changed){refreshStatues();checkpointNeeded=true;}
}
void Simulation::syncStatueBodies() {
    arena.movementBodies.clear();
    auto append=[&](const auto &actors) {
        for(const auto &e:actors)if(e.alive&&content->statue(e.monster)) {
            const float half=e.radius*.85f;
            arena.movementBodies.push_back({{e.position.x-half,-1,e.position.z-half},
                                           {e.position.x+half,8,e.position.z+half}});
        }
    };
    append(enemies);
    for(size_t n=0;n<rooms.size();++n)if(int(n)!=room)append(rooms[n].residents);
    refreshStatueAttraction();
}
void Simulation::updateStatue(Enemy &e,float dt) {
    const auto &s=*content->statue(e.monster);
    e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.fireContactCooldown=std::max(0.f,e.fireContactCooldown-dt);
    e.velocity={};e.lift=0;
    e.statueDisabled=s.clear!=StatueClear::Never&&
        (platesComplete()||(s.clear==StatueClear::Combat&&roomClear&&!rooms[size_t(room)].trapOnly));
    if(e.statueDisabled){e.state=EnemyState::Ready;return;}
    if(s.attack==StatueAttack::Attraction) {
        e.state=EnemyState::Ready;
        e.facing=e.statueFacing;return; // A Maw never emits a projectile.
    }
    if(s.attack==StatueAttack::Supply) {
        e.state=EnemyState::Ready;e.facing=e.statueFacing;
        return; // Supplied pickups and lit bombs have their own persistent lifecycle.
    }
    if(s.attack==StatueAttack::Quake) {
        // Left/up/right/down in source room coordinates map to -X/-Z/+X/+Z.
        // The interval is landing-to-landing, not interval plus windup.
        const std::array<Vector3,4> axes{{{-1,0,0},{0,0,-1},{1,0,0},{0,0,1}}};
        e.facing=e.statueFacing=axes[size_t(s.quakeAxis)];
        e.statuePhase+=double(dt);
        if(e.statuePhase>=double(s.interval)) {
            e.statuePhase=std::fmod(e.statuePhase,double(s.interval));
            Hazard wave;wave.kind=HazardKind::RockWave;
            wave.position=wave.previous=wave.origin=add(e.position,mul(e.facing,e.radius+.05f));
            wave.velocity=mul(e.facing,s.speed);wave.radius=s.waveRadius;
            wave.delay=0;wave.duration=s.range/s.speed;wave.damage=s.damage;wave.waveTrail=s.waveTrail;
            wave.context.sourceEntity=e.id;addHazard(wave);++e.statueVolley;
            particleEffect(ParticleEffect::Stone,e.position,{0,1,0},.65f);
            audioCues.push(AudioCueKind::StoneHit,e.position);
        }
        const float hop=float(e.statuePhase)-(s.interval-s.hopSeconds);
        e.state=hop>=0?EnemyState::Windup:EnemyState::Ready;
        e.stateTime=std::max(0.f,s.hopSeconds-hop);
        e.lift=hop>=0?s.hopHeight*std::sin(Pi*hop/s.hopSeconds):0;
        return;
    }
    const bool aimed=s.attack==StatueAttack::Aimed||s.attack==StatueAttack::Triple||s.attack==StatueAttack::Lob;
    if(aimed)e.facing=unit(horizontal(sub(player.position,e.position)));
    else e.facing=rotateY(e.statueFacing,s.turnRate*e.age);
    e.cooldown-=dt;
    if(e.state!=EnemyState::Windup) {
        if(e.cooldown>0||(aimed&&(planarDistance(e.position,player.position)>s.range||!arena.sight(e.position,player.position))))return;
        e.state=EnemyState::Windup;e.stateTime=s.windup;e.target=player.position;
    }
    e.stateTime-=dt;if(e.stateTime>0)return;
    e.state=EnemyState::Ready;e.cooldown=s.interval;
    if(s.attack==StatueAttack::Lob) {
        auto target=player.position;target.y=.22f;const auto start=add(e.position,{0,.2f,0});
        auto velocity=mul(sub(target,start),1/s.lobFlight);velocity.y+=.5f*s.gravity*s.lobFlight;
        Event shot;shot.position=shot.origin=start;shot.direction=unit(velocity);shot.speed=length(velocity);
        shot.hostile=true;shot.damage=0;shot.projectileKind=ProjectileKind::Ipecac;
        shot.projectileGravity=s.gravity;shot.projectileBlastRadius=s.blastRadius;shot.projectileBlastDamage=s.blastDamage;
        shot.projectileLife=s.lobFlight+1;shot.context.sourceEntity=e.id;queueRoot(shot);
    } else if(s.attack==StatueAttack::Beam||s.attack==StatueAttack::RotatingBeam) {
        const auto start=add(e.position,mul(e.facing,e.radius+.05f));
        auto end=add(start,mul(e.facing,s.range));const auto hit=arena.trace(start,end,s.beamRadius);
        if(hit.hit)end=add(start,mul(sub(end,start),std::max(0.f,hit.t-.001f)));
        Hazard beam;beam.kind=HazardKind::Beam;beam.origin=start;beam.position=end;
        beam.radius=s.beamRadius;beam.delay=0;beam.duration=s.beamDuration;beam.damage=s.damage;
        beam.ownerBound=true;beam.context.sourceEntity=e.id;beam.tint={172,36,52,255};addHazard(beam);
    } else if(s.attack==StatueAttack::Cross) {
        const float angle=s.angle+float(e.statueVolley%2)*Pi/4;
        for(int n=0;n<4;++n)shootEnemy(e,rotateY({1,0,0},angle+float(n)*Pi/2),s.damage,s.speed);
    } else if(s.attack==StatueAttack::Triple) {
        for(int n=-1;n<=1;++n)shootEnemy(e,rotateY(e.facing,float(n)*s.spread),s.damage,s.speed);
    } else shootEnemy(e,e.facing,s.damage,s.speed);
    ++e.statueVolley;
}

void Simulation::spawnFloorStatue(const EncounterPlan &plan) {
    if(!plan.statue)return;
    const auto id=*plan.statue;const auto &definition=*content->monster(id);const auto &s=*content->statue(id);
    const auto &layout=arena.rooms[size_t(room)];
    Random rng(seed_^0x5354415455455350ULL^(uint64_t(room+1)*0xbf58476d1ce4e5b9ULL));
    const auto oldBodies=arena.movementBodies;
    auto connected=[&] {
        if(arena.blocked(layout.center,.8f)||!arena.clear(layout.entry,layout.entry,.8f)||
           arena.path(layout.entry,layout.center,.8f).empty()||arena.path(layout.center,layout.objective,.8f).empty())return false;
        for(int link:layout.passages) {
            const auto &p=arena.passages[size_t(link)];const int side=p.rooms[0]==room?0:1;
            if(arena.path(layout.center,arena.doorApproach(link,side),.8f).empty())return false;
        }
        return true;
    };
    for(int attempt=0;attempt<120;++attempt) {
        Vector3 at{rng.real(layout.bounds.min.x+2,layout.bounds.max.x-2),.85f,rng.real(layout.bounds.min.z+2,layout.bounds.max.z-2)};
        if(arena.blocked(at,definition.radius+1)||!roomSpawnClear(at,definition.radius+1)||
            distance(at,layout.entry)<7||distance(at,layout.center)<3||distance(at,layout.objective)<3||
            !arena.sight(at,layout.center))continue;
        if(std::any_of(enemies.begin(),enemies.end(),[&](const auto &e){return distance(at,e.position)<e.radius+definition.radius+1;}))continue;
        if(arena.canyon) {
            const auto road=arena.canyon->roadSample(at);const auto river=arena.canyon->riverSample(at);
            if(road.distance<road.width+definition.radius+1||river.distance<river.width+definition.radius+1)continue;
        }
        if(s.attack==StatueAttack::Quake) {
            const std::array<Vector3,4> axes{{{-1,0,0},{0,0,-1},{1,0,0},{0,0,1}}};
            const auto facing=axes[size_t(s.quakeAxis)];
            const auto start=add(at,mul(facing,definition.radius+.05f));
            const auto end=add(start,mul(facing,6));
            if(dot(facing,sub(layout.center,at))<2||arena.roomAt(end)!=room||
                !arena.clear(start,end,s.waveRadius))continue;
        }
        const float half=definition.radius*.85f;
        arena.movementBodies.push_back({{at.x-half,-1,at.z-half},{at.x+half,8,at.z+half}});
        if(!connected()){arena.movementBodies=oldBodies;continue;}
        // Persistent turrets have an optional reachable floor plate. Pressing it
        // disables the turret; ordinary enemies still govern combat completion.
        std::optional<Vector3> plate;
        if(s.clear==StatueClear::Plates) {
            for(int n=0;n<32;++n) {
                auto candidate=add(layout.center,rotateY({2+float(n/8),0,0},float(n)*2.399963f));candidate.y=.85f;
                if(!arena.blocked(candidate,.8f)&&roomSpawnClear(candidate,.8f)&&distance(candidate,at)>3&&
                    distance(candidate,layout.objective)>2&& !arena.path(layout.entry,candidate,.48f).empty()) {plate=candidate;break;}
            }
            if(!plate){arena.movementBodies=oldBodies;continue;}
        }
        arena.movementBodies=oldBodies;
        const auto entity=spawnMonster(id,at);if(!entity)return;
        auto *enemy=findEnemy(entity);
        const auto delta=horizontal(sub(layout.center,at));
        if(s.attack!=StatueAttack::Quake)
            enemy->facing=enemy->statueFacing=std::abs(delta.x)>std::abs(delta.z)?Vector3{delta.x>0?1.f:-1.f,0,0}:Vector3{0,0,delta.z>0?1.f:-1.f};
        enemy->cooldown=1.4f;
        if(plate)rooms[size_t(room)].plates.push_back({*plate,false});
        return;
    }
    arena.movementBodies=oldBodies; // Optional hazard omitted when no legal footprint exists.
}
} // namespace dw
