#include "world/Dungeon.hpp"

namespace dw {
void Arena::prepareRailArena(int index) {
    if(!profile.bossRails)return;
    if(index<0)index=roomCount()-1;
    auto &room=rooms.at(size_t(index));const auto &layout=*profile.bossRails;
    rails=RailNetwork::fit(layout,room.bounds);
    // Source room dimensions are selected before graph spacing. A rectangular
    // rail yard cannot be clipped to the generic elliptical canyon basin.
    if(canyon)for(int z=0;z<canyon->depth;++z)for(int x=0;x<canyon->width;++x) {
        auto p=canyon->vertex(x,z);const auto &b=room.bounds;
        if(p.x<b.min.x-2||p.x>b.max.x+2||p.z<b.min.z-2||p.z>b.max.z+2)continue;
        float height=0;
        for(const auto &pit:rails->pits)if(p.x>pit.min.x+.15f&&p.x<pit.max.x-.15f&&p.z>pit.min.z+.15f&&p.z<pit.max.z-.15f){height=-2.4f;break;}
        const auto at=size_t(z*canyon->width+x);canyon->heights[at]=height;
        if(canyon->boundaryHeights.size()==canyon->heights.size())canyon->boundaryHeights[at]=height;
    }
    std::erase_if(breakables,[&](const auto &b){return b.room==index;});
    for(const auto &[x,z]:layout.rockCells) {
        const Vector3 c{room.bounds.min.x+(x+.5f)*rails->cellSize.x,0,room.bounds.min.z+(z+.5f)*rails->cellSize.z};
        // Rocks remain destructible and never occupy a cart's authored track.
        if(std::any_of(layout.cells.begin(),layout.cells.end(),[&](const auto &r){return r.x==x&&r.z==z;}))continue;
        Breakable b;b.id=0x5241494c0000ULL+breakables.size();b.room=index;b.paid=true;
        b.kind=BreakableKind::CrackedRock;b.bounds={sub(c,{rails->cellSize.x*.32f,0,rails->cellSize.z*.32f}),add(c,{rails->cellSize.x*.32f,1.5f,rails->cellSize.z*.32f})};
        b.rewardPosition=add(c,{0,.85f,0});breakables.push_back(b);
    }
    rebuildWalls();
    // buildCanyon derived navigation from the earlier irregular basin. Refresh
    // the authored footprint after flattening it: visible, walkable corners
    // must also exist in the grid used by player and fleeing-boss pathfinding.
    if(canyon)for(int x=int(std::floor(room.bounds.min.x/FloorTile));x<int(std::ceil(room.bounds.max.x/FloorTile));++x)
        for(int z=int(std::floor(room.bounds.min.z/FloorTile));z<int(std::ceil(room.bounds.max.z/FloorTile));++z) {
            const Vector3 p{(x+.5f)*FloorTile,.85f,(z+.5f)*FloorTile};
            if(!blocked(p,0))floorCells.insert({x,z});else floorCells.erase({x,z});
        }
    // Gameplay passage mouths are independent of rail doors. Reserve their
    // existing approaches rather than placing an exit/reward inside a pit.
    auto safe=[&](Vector3 preferred) {
        preferred.y=.85f;
        if(!blocked(preferred,.7f)&&!path(room.entry,preferred,.48f).empty())return preferred;
        for(int ring=1;ring<=20;++ring)for(int n=0;n<32;++n) {
            auto p=add(preferred,rotateY({float(ring),0,0},float(n)*Pi/16));
            if(p.x<room.bounds.min.x+1||p.x>room.bounds.max.x-1||p.z<room.bounds.min.z+1||p.z>room.bounds.max.z-1)continue;
            if(!blocked(p,.7f)&&!path(room.entry,p,.48f).empty())return p;
        }
        return room.entry;
    };
    room.bossSpawn=safe(room.center);room.reward=safe(room.reward);room.objective=safe(room.objective);
    room.exit=safe(room.exit);if(index==roomCount()-1)exit=room.exit;
}
} // namespace dw
