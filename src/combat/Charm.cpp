#include "combat/Simulation.hpp"

namespace dw {
namespace {
bool charmCandidate(const Enemy &e,const MechanicsLibrary &content,bool contact=false) {
    const auto *p=content.monster(e.monster);
    if(!e.alive||(e.friendly&&!(contact&&e.permanentCharmed))||e.kind!=EnemyKind::Monster||!p||p->roomHazard||e.dyingEggy()||
       e.returningBody||e.thrownOffspring||e.state==EnemyState::Buried||e.state==EnemyState::Teleporting||
       (e.leaper&&e.leaper->phase&&e.targetHop->airborne))return false;
    const int type=e.monster.type;
    return type>=10&&type<=999&&type!=17&&type!=33&&type!=292&&type!=245&&type!=960&&type!=965&&
        !(type==885&&e.monster.variant==10);
}
EntityId rootOf(const Simulation &s,const Enemy &e) {
    auto root=e.id;const Enemy *body=&e;
    // Preserve common ownership even if an ancestor has already been removed.
    for(int n=0;n<64;++n) {
        auto parent=body->componentOwner?body->componentOwner:body->summoner;
        if(!parent||parent==root)return root;
        root=parent;body=s.findEnemy(parent);if(!body)return root;
    }
    return root;
}
}

Vector3 Simulation::resolvedEnemyTarget(Enemy &e) {
    if(!e.affectedBy(EnemyStatus::Charm))return player.position;
    const auto &p=*content->enemyStatuses(e.monster)->charm;auto &r=*e.statuses;
    auto *target=findEnemy(r.charmTarget);
    if(target&&!target->alive){r.charmTarget=0;target=nullptr;}
    const auto pollFrame=r.charmFrame+1;
    const bool poll=!e.affectedBy(EnemyStatus::Freeze)&&(pollFrame+e.id)%unsigned(p.targetFrames)==0;
    if(!target||(poll&&r.charmLastPoll!=pollFrame)) {
        r.charmLastPoll=pollFrame;r.charmTarget=0;target=nullptr;
        float score=p.range*p.range;const auto ownRoot=rootOf(*this,e);
        for(auto &candidate:enemies) {
            if(!charmCandidate(candidate,*content)||candidate.age<2.f/30-1e-6f||
               candidate.id==e.id||rootOf(*this,candidate)==ownRoot||
               (e.monster.type==222&&candidate.monster.type==222))continue;
            const auto delta=horizontal(sub(candidate.position,e.position));
            const float next=dot(delta,delta)+(candidate.affectedBy(EnemyStatus::Charm)?p.targetPenalty:0);
            if(next>=score)continue;
            score=next;r.charmTarget=candidate.id;target=&candidate;
        }
    }
    // Native ordinary fallback is still the player. Temporary Charm does not
    // grant FRIENDLY immunity, remove room threats, or invent idle-only AI.
    return target?target->position:player.position;
}

void Simulation::setEnemyShotAffiliation(const Enemy &e,Event &shot) const {
    if(!e.affectedBy(EnemyStatus::Charm))return;
    shot.projectileHitsEnemies=true;
    shot.projectileIgnoresPlayer=e.friendly;
    shot.projectileNpcDamage=content->enemyStatuses(e.monster)->charm->projectileDamage;
    shot.projectileTint={238,123,173,255};
}

void Simulation::prepareCharmContacts() {
    if(std::none_of(enemies.begin(),enemies.end(),[](const auto &e){return e.alive&&e.affectedBy(EnemyStatus::Charm);}))return;
    for(auto &e:enemies)if(charmCandidate(e,*content,true)) {
        if(!e.charmContact)e.charmContact.emplace();
        if(!e.charmContact->motionReady){e.charmContact->previous=e.position;e.charmContact->motionReady=true;}
    }
}

void Simulation::updateCharmContacts() {
    const bool active=std::any_of(enemies.begin(),enemies.end(),[](const auto &e){return e.alive&&e.affectedBy(EnemyStatus::Charm);});
    const uint64_t frame=uint64_t(std::max(0.,std::floor(stats.duration*30+.00001)));
    const bool sample=frame>charmContactFrame_;charmContactFrame_=frame;
    for(auto &source:enemies) {
        auto flush=[&]() {
            if(!source.charmContact||!source.charmContact->pending)return true;
            auto &pending=source.charmContact->pending;const auto *target=findEnemy(pending->target);
            if(!target||!target->alive){pending.reset();return true;}
            if(queue_.size()>=limits.queuedEvents)return false;
            Event hit;hit.type=EventType::Damage;hit.target=pending->target;
            hit.damage=pending->damage;hit.position=pending->position;hit.origin=pending->origin;
            hit.direction=unit(horizontal(sub(hit.position,hit.origin)));hit.hostile=true;
            hit.context.sourceEntity=source.id;hit.context.damageSource=source.friendly?DamageSource::Ally:DamageSource::Enemy;
            if(!queueRoot(hit))return false;
            pending.reset();return true;
        };
        if(!flush()||!active||!sample||!charmCandidate(source,*content,true)||contactDamage(source)<=0)continue;
        for(const auto &target:enemies) {
            if(source.id==target.id||!charmCandidate(target,*content,true))continue;
            const bool charmed=source.affectedBy(EnemyStatus::Charm),other=target.affectedBy(EnemyStatus::Charm);
            if(charmed==other&&(!source.statuses||source.statuses->charmTarget!=target.id))continue;
            const auto *profile=content->enemyStatuses(charmed?source.monster:target.monster);
            if(!profile||!profile->charm)continue;
            const auto &p=*profile->charm;
            if(!source.charmContact)source.charmContact.emplace();
            auto &r=*source.charmContact;
            const auto cycle=(frame+source.id)/unsigned(p.contactFrames);
            if(r.cycle!=cycle) {
                r.cycle=cycle;
                // Freeze stops IsFrame polling, not physical contact. Preserve
                // the touched set while frozen instead of repeated free hits.
                if(!source.affectedBy(EnemyStatus::Freeze))r.touched.clear();
            }
            const auto from=r.motionReady?r.previous:source.position;
            const auto otherFrom=target.charmContact&&target.charmContact->motionReady?target.charmContact->previous:target.position;
            const auto fraction=segmentSphere(sub(from,otherFrom),sub(source.position,target.position),{},source.radius+target.radius);
            const auto at=add(from,mul(sub(source.position,from),fraction));
            const auto otherAt=add(otherFrom,mul(sub(target.position,otherFrom),fraction));
            if(fraction>1||!arena.sight(at,otherAt)||
               std::find(r.touched.begin(),r.touched.end(),target.id)!=r.touched.end())continue;
            float damage=std::log((source.maxHp/(p.healthScale*content->regularHealthAdjustment(source.monster))+p.contactOffset)/p.contactDivisor)*p.contactGain*p.healthScale;
            if(target.permanentCharmed)damage=std::min(damage*.25f,3.5f*p.healthScale);
            r.touched.push_back(target.id);
            r.pending=CharmContactHit{target.id,damage,at,otherAt};
            // One retained hit per actor under backpressure; no unbounded
            // retries/list and no re-sampling damage after effect expiry.
            if(!flush())break;
        }
    }
    for(auto &e:enemies)if(e.charmContact) {
        if(!active)e.charmContact->motionReady=false;
        else if(sample){e.charmContact->previous=e.position;e.charmContact->motionReady=true;}
    }
}
void Simulation::restoreCharmFollowers() {
    std::erase_if(charmFollowers_,[&](Enemy &e) {
        if(!e.alive)return true;
        if(enemies.size()>=limits.enemies)return false;
        const auto center=arena.rooms[size_t(room)].center;
        for(int ring=0;ring<32;++ring)for(int n=0;n<(ring?32:1);++n) {
            const auto candidate=add(center,rotateY({float(ring)*1.25f,0,0},float(n)*2*Pi/32));
            if(arena.roomAt(candidate)!=room||arena.blocked(candidate,e.radius)||
               std::any_of(enemies.begin(),enemies.end(),[&](const Enemy &b){return b.alive&&distance(b.position,candidate)<b.radius+e.radius+.1f;}))continue;
            e.position=e.home=candidate;e.velocity={};e.path.clear();e.pathTime=0;e.charmContact.reset();
            invalidateStatusPath(e,EnemyStatus::Charm);
            enemies.push_back(std::move(e));return true;
        }
        return false;
    });
}
} // namespace dw
