#include "combat/Simulation.hpp"

namespace dw {
EncounterPlan Simulation::floorEncounter(int index) const {
    EncounterPlan result;
    const auto &r=arena.rooms.at(size_t(index));const auto &p=arena.profile;
    if(!p.active()||r.kind!=RoomKind::Combat)return result;
    Random rng(seed_^0x464c4f4f52475250ULL^(uint64_t(index+1)*0x9e3779b97f4a7c15ULL));
    int total=0;for(auto weight:p.patterns)total+=weight;
    int roll=int(rng.bounded(uint32_t(total)));
    for(int i=0;i<4;++i) {roll-=p.patterns[size_t(i)];if(roll<0){result.pattern=EncounterPattern(i);break;}}
    const int capacity=std::clamp(int(std::ceil(r.usableArea()/70.f)),4,14);
    result.budget=std::clamp(int(std::ceil(r.usableArea()/p.areaPerThreat))+p.band,4,p.maxThreat);
    // The immutable content snapshot owns stage eligibility, weights, costs and caps.
    // Selection never consumes combat RNG or depends on discovery/graph depth.
    const auto &pool=content->encounterPool(p.band,result.pattern);
    auto cost=[&](const EncounterEntry &entry) {
        return entry.cost+content->replacementCost(entry.monster,p);
    };
    auto pick=[&](const auto &entries,int available,int slots,int requiredMembers=0)->const EncounterEntry * {
        // The first support selection must leave enough budget for any still
        // missing support actors, including conditional replacement surcharges.
        auto eligible=[&](const auto &e){return e.weight>0&&cost(e)+std::max(0,requiredMembers-e.members)<=available&&e.members<=slots&&
            (!content->mirror(e.monster)||std::none_of(result.monsters.begin(),result.monsters.end(),[&](auto id){return content->mirror(id)!=nullptr;}))&&
            (!e.variant||*e.variant==p.variant)&&
            (!e.maximum||std::count(result.monsters.begin(),result.monsters.end(),e.monster)+e.members<=e.maximum);};
        int weight=0;for(const auto &entry:entries)if(eligible(entry))weight+=entry.weight;
        if(!weight)return nullptr;
        int choice=int(rng.bounded(uint32_t(weight)));
        for(const auto &entry:entries)if(eligible(entry)) {
            choice-=entry.weight;if(choice<0)return &entry;
        }
        return nullptr;
    };
    const int desired=result.pattern==EncounterPattern::Pursuit?1:p.maxSpecialists;
    for(int n=0;n<desired&&int(result.monsters.size())<capacity-2;++n) {
        const auto *entry=pick(pool.specialists,result.budget-result.spent-2,capacity-2-int(result.monsters.size()));
        if(!entry)break;
        result.monsters.insert(result.monsters.end(),size_t(entry->members),entry->monster);
        result.spent+=cost(*entry);result.specialists+=entry->members;++result.specialistGroups;
    }
    while(result.spent<result.budget && int(result.monsters.size())<capacity) {
        const int missingSupport=std::max(0,2-(int(result.monsters.size())-result.specialists));
        const auto *entry=pick(pool.basics,result.budget-result.spent,capacity-int(result.monsters.size()),missingSupport);
        if(!entry)break;
        result.monsters.insert(result.monsters.end(),size_t(entry->members),entry->monster);result.spent+=cost(*entry);
    }
    result.originalMonsters=result.monsters;
    for(size_t i=0;i<result.monsters.size();++i) {
        // One rule per explicit phase. Phase zero preserves existing slot RNG;
        // later phases may transform the prior result without recursive rerolls.
        for(int phase=0;phase<4;++phase) {
            const auto *rule=content->replacement(result.monsters[i],p,phase);if(!rule)continue;
            Random variant(seed_^0x5245504c414345ULL^(uint64_t(index+1)*0x9e3779b97f4a7c15ULL)^((i+1)*0xbf58476d1ce4e5b9ULL)^(uint64_t(phase)*0x94d049bb133111ebULL));
            if(variant.bounded(uint32_t(rule->chanceOutOf))<uint32_t(rule->chance))result.monsters[i]=rule->target;
        }
    }
    Random statueRng(seed_^0x535441545545504cULL^(uint64_t(index+1)*0x9e3779b97f4a7c15ULL));
    if(statueRng.bounded(10000)<uint32_t(content->statueChance(p.band))) {
        const auto &statues=content->statuePool(p.band);int weight=0;
        for(const auto &e:statues)if(e.pattern<0||e.pattern==int(result.pattern))weight+=e.weight;
        if(weight) {
            int choice=int(statueRng.bounded(uint32_t(weight)));
            for(const auto &e:statues)if(e.pattern<0||e.pattern==int(result.pattern))
                if((choice-=e.weight)<0){result.statue=e.monster;break;}
        }
    }
    return result;
}
void Simulation::spawnFloorEnemies() {
    const auto plan=floorEncounter(room);const auto &layout=arena.rooms[size_t(room)];
    Random placement(seed_^0x464c4f4f5253504eULL^(uint64_t(room+1)*0xbf58476d1ce4e5b9ULL));
    auto forward=unit(sub(layout.center,layout.entry));const Vector3 side{-forward.z,0,forward.x};
    const float extent=std::min(layout.bounds.max.x-layout.bounds.min.x,layout.bounds.max.z-layout.bounds.min.z)*.22f;
    for(size_t i=0;i<plan.monsters.size();++i) {
        const auto id=plan.monsters[i];const auto &def=*content->monster(id);
        const bool specialist=int(i)<plan.specialists;
        Vector3 anchor=layout.center;
        switch(plan.pattern) {
        case EncounterPattern::Crossfire:
            anchor=add(anchor,add(mul(side,(i%2?1.f:-1.f)*extent),mul(forward,specialist?2.f:-2.f)));break;
        case EncounterPattern::ChargeLane:
            anchor=add(anchor,add(mul(forward,extent),mul(side,(float(i%3)-1)*2.2f)));break;
        case EncounterPattern::SupplyGuard:
            anchor=add(layout.objective,mul(side,(i%2?1.f:-1.f)*3.f));break;
        default:anchor=add(anchor,add(mul(side,(float(i%3)-1)*extent),mul(forward,specialist?extent:0)));break;
        }
        bool placed=false;
        // Authored intent adapts to actual geometry. A blocked river/road/slope
        // placement falls back to the normal safe, spaced placement search.
        for(int attempt=0;attempt<36;++attempt) {
            const float angle=float(attempt)*2.399963f;
            const float radius=attempt==0?0:1.f+float(attempt/8);
            auto point=add(anchor,{std::cos(angle)*radius,0,std::sin(angle)*radius});point.y=.85f;
            // Check the physical footprint as well as its clearance margin;
            // the sampled canyon boundary need not be monotonic with radius.
            if(arena.blocked(point,def.radius)||(def.radius<.8f&&arena.blocked(point,.8f))||!roomSpawnClear(point,def.radius)||
               distance(point,player.position)<6)continue;
            if(arena.canyon&&arena.canyon->waterBlocked(point))continue;
            auto body=point;if(def.flying)body.y=arena.flightHeight(point,def.radius);
            if(std::any_of(enemies.begin(),enemies.end(),[&](const auto &e){return distance(body,e.position)<e.radius+def.radius+.4f;}))continue;
            // Stationary attackers need a firing line into their own room.
            if(def.motion==MonsterMotion::Still&&!arena.sight(point,layout.center))continue;
            if(!spawnMonster(id,point))break;
            placed=true;break;
        }
        if(!placed&&!placeEnemy(EnemyKind::Monster,placement,true,id))break;
        // Most actors keep the local entry stagger. Headless lobbers retain their
        // configured integral source delay, independent of floor aggression.
        if(const auto *lob=content->lobWalker(id);lob&&!lob->attackFrames)
            enemies.back().cooldown=float(lob->initialMin+int(placement.bounded(unsigned(lob->initialMax-lob->initialMin+1))))/30;
        else if(content->maw(id))enemies.back().cooldown=0;
        else enemies.back().cooldown=(specialist?1.4f+float(i)*.55f:placement.real(.8f,1.6f))*arena.profile.cooldownScale;
    }
    spawnFloorStatue(plan);
}
} // namespace dw
