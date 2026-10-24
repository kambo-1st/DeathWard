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
    // Every role has an explicit threat cost. Higher bands change combinations,
    // never multiply everyone's HP. The same floor graph depth cannot unlock late roles.
    struct Role { int id,cost; };
    const std::array<int,3> basics{monsterId(10,1),monsterId(21),monsterId(11,1)};
    const int basic=basics[rng.bounded(uint32_t(basics.size()))];
    std::vector<Role> specials;
    if(result.pattern==EncounterPattern::ChargeLane) {
        specials.push_back({monsterId(23),3});
        if(p.band>=1)specials.push_back({monsterId(14),2});
        if(p.band>=3)specials.push_back({monsterId(41,2),3});
    } else if(result.pattern==EncounterPattern::SupplyGuard && p.band>=2) {
        specials={{monsterId(30,1),3},{monsterId(25),3}};
        if(p.band==3)specials.push_back({monsterId(39),4});
    } else {
        specials={{rng.bounded(2)?monsterId(12):monsterId(14),2}};
        if(p.band>=1)specials.push_back({monsterId(15),3});
        if(p.band>=2)specials.push_back({monsterId(34),3});
        if(p.band>=3)specials.push_back({monsterId(60),4});
    }
    const int desired=result.pattern==EncounterPattern::Pursuit?1:p.maxSpecialists;
    for(int n=0;n<desired&&int(result.monsters.size())<capacity-2;++n) {
        const auto role=specials[size_t(n)%specials.size()];
        if(result.spent+role.cost+2>result.budget)break;
        result.monsters.push_back(role.id);result.spent+=role.cost;++result.specialists;
    }
    while(result.spent<result.budget && int(result.monsters.size())<capacity) {
        result.monsters.push_back(basic);++result.spent;
    }
    return result;
}
void Simulation::spawnFloorEnemies() {
    const auto plan=floorEncounter(room);const auto &layout=arena.rooms[size_t(room)];
    Random placement(seed_^0x464c4f4f5253504eULL^(uint64_t(room+1)*0xbf58476d1ce4e5b9ULL));
    auto forward=unit(sub(layout.center,layout.entry));const Vector3 side{-forward.z,0,forward.x};
    const float extent=std::min(layout.bounds.max.x-layout.bounds.min.x,layout.bounds.max.z-layout.bounds.min.z)*.22f;
    for(size_t i=0;i<plan.monsters.size();++i) {
        const int id=plan.monsters[i];const auto &def=*monsterDefinition(id);
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
            const auto point=add(anchor,{std::cos(angle)*radius,0,std::sin(angle)*radius});
            if(arena.blocked(point,std::max(.8f,def.radius))||!roomSpawnClear(point,def.radius)||
               distance(point,player.position)<6)continue;
            if(arena.canyon&&arena.canyon->waterBlocked(point))continue;
            if(std::any_of(enemies.begin(),enemies.end(),[&](const auto &e){return distance(point,e.position)<e.radius+def.radius+.4f;}))continue;
            // Stationary attackers need a firing line into their own room.
            if(def.motion==MonsterMotion::Still&&!arena.sight(point,layout.center))continue;
            if(!spawnMonster(id,point))break;
            placed=true;break;
        }
        if(!placed&&!placeEnemy(EnemyKind::Monster,placement,true,id))break;
        // Stagger the first attacks. Subsequent cooldowns use the band multiplier.
        enemies.back().cooldown=(specialist?1.4f+float(i)*.55f:placement.real(.8f,1.6f))*arena.profile.cooldownScale;
    }
}
} // namespace dw
