#include "world/Dungeon.hpp"

namespace dw {
namespace {
bool overlaps(Box a, Box b, float margin = 0) {
    return a.min.x < b.max.x + margin && a.max.x > b.min.x - margin &&
           a.min.z < b.max.z + margin && a.max.z > b.min.z - margin;
}
}
void Arena::prepareBreakables(uint64_t seed) {
    // Runtime props are deliberately created AFTER the canyon height field and story dressing.
    // Independent placement/loot streams never consume layout, combat or reward randomness.
    Random rng(seed ^ 0x425245414b504f43ULL);
    std::vector<int> candidates;
    for (int i = 1; i < roomCount()-1; ++i)
        if ((rooms[size_t(i)].kind == RoomKind::Combat || rooms[size_t(i)].kind == RoomKind::Empty) &&
            rooms[size_t(i)].story == StoryRoom::None && rooms[size_t(i)].sourceCombatTemplate<0&&rooms[size_t(i)].sourceObstacleTemplate<0)
            candidates.push_back(i);
    for (size_t i = 0; i < candidates.size(); ++i)
        std::swap(candidates[i], candidates[i + rng.bounded(uint32_t(candidates.size()-i))]);
    auto clearSite = [&](int index, Box area) {
        const auto &r = rooms[size_t(index)];
        if (area.min.x < r.bounds.min.x + 1 || area.max.x > r.bounds.max.x - 1 ||
            area.min.z < r.bounds.min.z + 1 || area.max.z > r.bounds.max.z - 1) return false;
        std::vector<Vector3> destinations{r.entry, r.exit, r.objective};
        for (int link : r.passages) destinations.push_back(doorApproach(link, passages[size_t(link)].rooms[0]==index?0:1));
        for (auto p : destinations)
            if (sphereBox(p, 1.4f, area) || segmentBox(r.center, p, area, 1.25f).hit) return false;
        for (const auto &key : keys) if (sphereBox(key.position, 1.5f, area)) return false;
        for (float x = area.min.x; x <= area.max.x+.01f; x += .5f)
            for (float z = area.min.z; z <= area.max.z+.01f; z += .5f) {
                Vector3 p{x,.85f,z};
                if (blocked(p,.6f)) return false;
                if (canyon) {
                    if (std::abs(canyon->height(x,z)) > .035f) return false;
                    auto road = canyon->roadSample(p);
                    if (road.distance < road.width + .7f) return false;
                    auto river = canyon->riverSample(p);
                    if (river.distance < river.width + 1) return false;
                }
            }
        for (const auto &prop : breakables) if (overlaps(area,prop.bounds,1.1f)) return false;
        return true;
    };
    auto append = [&](int room, BreakableKind kind, Box box, Vector3 reward, int health = 1) {
        Breakable p;
        p.id = uint64_t(room+1)*256 + breakables.size()+1;
        p.lootSeed = seed ^ (p.id*0x9e3779b97f4a7c15ULL) ^ 0x425245414b4c4f54ULL;
        p.room=room;p.kind=kind;p.bounds=box;p.rewardPosition=reward;p.health=health;
        breakables.push_back(p);
    };
    std::vector<BreakableKind> mix{BreakableKind::CrackedRock,BreakableKind::CrackedRock,
                                  BreakableKind::OreSeam,BreakableKind::PowderBarrel};
    if(profile.active()) {
        mix.assign(size_t(profile.rocks),BreakableKind::CrackedRock);
        mix.insert(mix.end(),size_t(profile.seams),BreakableKind::OreSeam);
        mix.insert(mix.end(),size_t(profile.barrels),BreakableKind::PowderBarrel);
    }
    for (auto kind : mix) {
        bool placed=false;
        for (int room : candidates) {
            const auto &r=rooms[size_t(room)];
            const float half=kind==BreakableKind::PowderBarrel?.6f:1.0f;
            for (int attempt=0;attempt<220;++attempt) {
                Vector3 p{rng.real(r.bounds.min.x+2,r.bounds.max.x-2),.85f,
                          rng.real(r.bounds.min.z+2,r.bounds.max.z-2)};
                Box bounds{{p.x-half,0,p.z-half},{p.x+half,1.35f,p.z+half}};
                if (!clearSite(room,bounds))continue;
                // The payout point is the prop's own footprint, freed by its destruction.
                if (path(r.center,p,.48f).empty())continue;
                append(room,kind,bounds,p,kind==BreakableKind::PowderBarrel?30:1);
                rebuildWalls();placed=true;break;
            }
            if(placed)break;
        }
    }
}
} // namespace dw
