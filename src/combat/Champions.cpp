#include "combat/Simulation.hpp"
namespace dw {
void Simulation::championChild(const Enemy &e,MonsterId kind,Vector3 at,EntityId partner) {
    queueMonster(kind,at,partner,std::min(4,e.generation+1),false,1,0,e.id,0,-1,{},true);
    auto &r=pendingMonsters_.back();r.championFriendly=e.friendly;r.championPermanent=e.permanentCharmed;
    r.championCharm=e.statuses?e.statuses->charm:0;
}
bool Simulation::collapseChampion(Enemy &e) {
    if(e.champion!=12||e.championPile)return false;
    e.championPile=true;e.state=EnemyState::Collapsed;e.stateTime=2.5f;e.hp=e.maxHp*.25f;e.velocity={};return true;
}
void Simulation::championHurt(Enemy &e) {
    if(e.champion!=21||e.championAbility>0)return;
    int count=0;
    for(const auto &child:enemies)if(child.alive&&child.summoner==e.id&&child.monster==monsterId(18))++count;
    for(const auto &child:pendingMonsters_)if(child.summoner==e.id&&child.id==monsterId(18))++count;
    if(count<5){championChild(e,monsterId(18),e.position);e.championAbility=.3f;}
}

bool Simulation::makeChampion(EntityId id,int kind) {
    auto *e=findEnemy(id);const auto *p=content->champion(kind);
    if(!e||!e->alive||e->champion>=0||!p||!championEligible(e->monster))return false;
    if(!championTypeEligible(e->monster,kind))return false;
    // Size changes must preserve a legal footprint, including debug application.
    if(content->monster(e->monster)->flying?arena.flightBlocked(e->position,e->radius*p->collision,room):arena.blocked(e->position,e->radius*p->collision))return false;
    e->champion=kind;e->hp*=p->hp;e->maxHp*=p->hp;
    if(e->statuses&&e->statuses->unshrunkRadius>0)e->statuses->unshrunkRadius*=p->collision;
    e->radius*=p->collision;e->championSpeed=p->speed;e->championVisual=p->visual/p->collision;
    e->championDamage=p->damage;e->championTint=p->tint;
    if(kind==21)e->championAbility=0;
    checkpointNeeded=true;return true;
}
void Simulation::updateChampion(Enemy &e,float dt) {
    e.crowned=e.champion<0&&std::any_of(enemies.begin(),enemies.end(),[&](const Enemy &other){return other.alive&&other.champion==22&&other.friendly==e.friendly;});
    if(e.champion<0||e.affectedBy(EnemyStatus::Freeze))return;
    if(e.champion==21)e.championAbility=std::max(0.f,e.championAbility-dt);
    if(e.championEffect(17)&&!e.championOrbiter) {
        championChild(e,monsterId(96),e.position,e.id);e.championOrbiter=true;
    }
    const auto *head=content->headShooter(e.monster);
    // Sub Horf is reactive rather than walking. Source Green/Brown trails
    // require movement: receiving a modifier must not paint a stationary pile.
    const bool trailMoving=!head||!head->reactive||length(horizontal(e.velocity))>head->velocityScale*.01f;
    if(e.champion==24&&!e.friendly&&trailMoving) {
        e.championTrail-=dt;
        if(e.championTrail<=0&&arena.breakables.size()<1024&&!arena.blocked(e.position,.65f)&&
            std::none_of(arena.breakables.begin(),arena.breakables.end(),[&](const Breakable &p){return p.solid()&&planarDistance(p.rewardPosition,e.position)<2;})) {
            // Small breakable droppings cannot seal a passage or trap a body.
            const auto at=add(e.position,mul(unit(horizontal(e.facing)),-e.radius-1.f));
            bool clear=arena.roomAt(at)==room&&!arena.blocked(at,.65f)&&distance(at,player.position)>1.5f;
            for(const auto &other:enemies)if(other.alive&&distance(other.position,at)<other.radius+1)clear=false;
            const auto &layout=arena.rooms[size_t(room)];
            for(int link:layout.passages)if(distance(arena.doorApproach(link,arena.passages[size_t(link)].rooms[0]==room?0:1),at)<3)clear=false;
            if(clear) {
                Breakable p;p.id=nextEntity_++;p.lootSeed=p.id^seed_;p.kind=BreakableKind::Dung;p.room=room;
                p.bounds={{at.x-.4f,0,at.z-.4f},{at.x+.4f,.55f,at.z+.4f}};p.rewardPosition=at;p.health=p.initialHealth=3;
                arena.breakables.push_back(p);arena.rebuildWalls();
                bool connected=true;
                for(auto destination:{layout.entry,layout.exit,layout.objective})if(!arena.blocked(destination,.48f)&&arena.path(player.position,destination,.48f).empty())connected=false;
                if(!connected){arena.breakables.pop_back();arena.rebuildWalls();}
            }
            e.championTrail=1.5f;
        }
    }
    if(e.championEffect(2)&&!e.friendly&&trailMoving) {
        e.championTrail-=dt;
        if(e.championTrail<=0){bossCreep(e,.65f,3,{89,155,59,180},10);e.championTrail=.3f;}
    }
    if(e.championEffect(10)) {
        e.championAbility-=dt;
        const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const Event &v){return v.type==EventType::Shot;});
        if(e.championAbility<=0&&queue_.size()<limits.queuedEvents&&projectiles.size()+size_t(queued)<limits.projectiles) {
            Event shot;shot.hostile=true;shot.position=shot.origin=add(e.position,mul(e.facing,e.radius+.1f));
            shot.direction=e.facing;shot.speed=7;shot.damage=10;shot.projectileLife=.8f;shot.context.sourceEntity=e.id;
            setEnemyShotAffiliation(e,shot);
            if(queueRoot(shot))e.championAbility=1.2f;
        }
    }
    if(e.champion==20)for(auto &other:enemies)if(other.id!=e.id&&other.alive&&!other.dyingEggy()&&
        other.state!=EnemyState::Collapsed&&other.friendly==e.friendly&&other.champion!=20&&other.monster.type!=805) {
        const auto *d=content->monster(other.monster);
        if(!d||!d->roomHazard)other.hp=std::min(other.maxHp,other.hp+64*dt*content->regularHealthAdjustment(other.monster));
    }
}
bool Simulation::flushChampionDeath(Enemy &e) {
    if(!e.championDeathPending)return true;
    if(e.championEffect(5)&&e.championDeathStage==0) {
        if(queue_.size()>=limits.queuedEvents)return false;
        Event blast;blast.type=EventType::Explosion;blast.position=blast.origin=e.position;
        blast.damage=40;blast.radius=3;blast.playerDamage=e.friendly?0:20;
        blast.context.sourceEntity=e.id;blast.context.damageSource=e.friendly?DamageSource::Ally:DamageSource::Enemy;
        if(!queueRoot(blast))return false;
        e.championDeathStage=1;
    }
    if(e.championEffect(13)) {
        while(e.championDeathShot<8) {
            const auto queued=std::count_if(queue_.begin(),queue_.end(),[](const Event &v){return v.type==EventType::Shot;});
            if(queue_.size()>=limits.queuedEvents||projectiles.size()+size_t(queued)>=limits.projectiles)return false;
            Event shot;shot.hostile=true;shot.position=shot.origin=e.position;shot.context.sourceEntity=e.id;
            shot.direction=rotateY({1,0,0},float(e.championDeathShot)*Pi/4);shot.speed=8;shot.damage=10;shot.projectileLife=2;
            setEnemyShotAffiliation(e,shot);
            if(!queueRoot(shot))return false;
            ++e.championDeathShot;
        }
    }
    if(e.champion==15||e.champion==17) {
        const int count=e.champion==15?2:1;
        while(e.championDeathShot<count) {
            championChild(e,e.champion==15?e.monster:monsterId(18),add(e.position,rotateY({1,0,0},float(e.championDeathShot)*Pi)));
            ++e.championDeathShot;
        }
    }
    if(e.champion==23)while(!e.championTargets.empty()) {
        if(queue_.size()>=limits.queuedEvents)return false;
        Event hit;hit.type=EventType::Damage;hit.target=e.championTargets.back();hit.damage=128;hit.weakPointHit=true;
        hit.position=hit.origin=e.position;hit.context.sourceEntity=e.id;hit.context.damageSource=e.friendly?DamageSource::Ally:DamageSource::Enemy;
        if(!queueRoot(hit))return false;
        e.championTargets.pop_back();
    }
    e.championDeathPending=false;return true;
}
} // namespace dw
