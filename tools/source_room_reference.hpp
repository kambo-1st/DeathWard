#pragma once
#include "combat/Simulation.hpp"

namespace dw::source_room_review {
// Live pinned 1.7.9b shape1 room + executed grid/clamp helpers. See
// docs/reports/isaac-first-floor-parity/room-scale-timing/README.md.
inline constexpr float NativeCell=40;
inline constexpr Vector2 NativeTopLeft{60,140},NativeBottomRight{580,420};
// A geometric choice of units: one native tile equals one existing floor tile.
// No accepted player-pace value enters this conversion.
inline constexpr float Scale=FloorTile/NativeCell;
inline constexpr float Width=(NativeBottomRight.x-NativeTopLeft.x)*Scale;
inline constexpr float Depth=(NativeBottomRight.y-NativeTopLeft.y)*Scale;
inline constexpr Vector3 Centre{Width*.5f,.85f,Depth*.5f};
inline Vector3 worldFromNative(Vector2 p) {
    return {(p.x-NativeTopLeft.x)*Scale,.85f,(p.y-NativeTopLeft.y)*Scale};
}
inline Vector2 nativeFromWorld(Vector3 p) {
    return {p.x/Scale+NativeTopLeft.x,p.z/Scale+NativeTopLeft.y};
}
inline void configure(Arena &arena,bool open=false) {
    arena.bounds={{0,-1,0},{Width,5,Depth}};
    arena.floors={{{0,-.4f,0},{Width,0,Depth}}};
    arena.boundaryWalls={{{-.5f,0,-.5f},{Width+.5f,2,0}},{{-.5f,0,Depth},{Width+.5f,2,Depth+.5f}},
        {{-.5f,0,0},{0,2,Depth}},{{Width,0,0},{Width+.5f,2,Depth}}};
    // Explicit open-plane motion fixture for traces only. The interactive
    // reference uses the bounded source-equivalent room above.
    if(open){arena.bounds={{-100,-1,-100},{100,5,100}};arena.floors={{{-100,-.4f,-100},{100,0,100}}};arena.boundaryWalls.clear();}
    arena.floorCells.clear();
    if(!open)for(int x=0;x<13;++x)for(int z=0;z<7;++z)arena.floorCells.insert({x,z});
    arena.rooms.resize(1);auto &room=arena.rooms[0];
    room.bounds={{0,-1,0},{Width,5,Depth}};room.center=room.entry=Centre;room.floors=arena.floors;room.kind=RoomKind::Empty;
    arena.entrance=Centre;arena.rebuildWalls();
}
}
