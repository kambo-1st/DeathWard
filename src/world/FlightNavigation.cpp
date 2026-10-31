#include "world/Dungeon.hpp"

namespace dw {
bool Arena::flightBlocked(Vector3 p, float radius, int room) const {
    const auto &area=rooms.at(size_t(room)).bounds;
    if(p.x-radius<area.min.x||p.x+radius>area.max.x||p.z-radius<area.min.z||p.z+radius>area.max.z)
        return true;
    p.y=.85f;
    for(const auto &body:movementBodies)if(sphereBox(p,radius,body))return true;
    if(canyon) {
        if(canyon->height(p.x,p.z,true)>CanyonTerrain::WalkableHeight)return true;
        for(int i=0;i<8;++i) {
            const auto edge=add(p,rotateY({radius,0,0},float(i)*Pi/4));
            if(canyon->height(edge.x,edge.z,true)>CanyonTerrain::WalkableHeight)return true;
        }
    }
    // Unprepared synthetic arenas retain their explicit solid walls.
    for(const auto &wall:flightCollisionPrepared?flightWalls:walls)
        if(sphereBox(p,radius,wall))return true;
    return false;
}
bool Arena::flightClear(Vector3 from,Vector3 to,float radius,int room) const {
    if(flightBlocked(from,radius,room)||flightBlocked(to,radius,room))return false;
    from.y=to.y=.85f;
    for(const auto &body:movementBodies)if(segmentBox(from,to,body,radius).hit)return false;
    for(const auto &wall:flightCollisionPrepared?flightWalls:walls)
        if(segmentBox(from,to,wall,radius).hit)return false;
    if(canyon) {
        from.y=to.y=CanyonTerrain::WalkableHeight;
        if(canyon->trace(from,to,0,true).hit)return false;
        for(int i=0;i<8;++i) {
            const auto offset=rotateY({radius,0,0},float(i)*Pi/4);
            if(canyon->trace(add(from,offset),add(to,offset),0,true).hit)return false;
        }
    }
    return true;
}
float Arena::flightHeight(Vector3 p,float radius) const {
    float support=0;
    if(canyon) {
        support=std::max(0.f,canyon->height(p.x,p.z));
        for(int i=0;i<8;++i) {
            const auto edge=add(p,rotateY({radius,0,0},float(i)*Pi/4));
            support=std::max(support,canyon->height(edge.x,edge.z));
        }
    }
    for(const auto &cover:flightCover) {
        const float dx=std::max({cover.min.x-p.x,0.f,p.x-cover.max.x});
        const float dz=std::max({cover.min.z-p.z,0.f,p.z-cover.max.z});
        // A two-metre approach/exit ramp prevents a step in altitude at box edges.
        const float t=std::clamp((std::sqrt(dx*dx+dz*dz)-radius)/2.f,0.f,1.f);
        support=std::max(support,cover.max.y*(1-t*t*(3-2*t)));
    }
    return support+std::max(.85f,radius+.15f);
}
Vector3 Arena::fly(Vector3 from,Vector3 delta,float radius,int room) const {
    const auto x=add(from,{delta.x,0,0});
    if(flightClear(from,x,radius,room))from=x;
    const auto z=add(from,{0,0,delta.z});
    if(flightClear(from,z,radius,room))from=z;
    from.y=flightHeight(from,radius);
    return from;
}
} // namespace dw

namespace dw {
bool Arena::swimmingRoom(int room) const {
    if(rooms.at(size_t(room)).flooded)return true;
    return canyon&&std::find(canyon->riverRooms.begin(),canyon->riverRooms.end(),room)!=canyon->riverRooms.end();
}
bool Arena::swimBlocked(Vector3 p,float radius,int room) const {
    const auto &area=rooms.at(size_t(room)).bounds;
    if(p.x-radius<area.min.x||p.x+radius>area.max.x||p.z-radius<area.min.z||p.z+radius>area.max.z)return true;
    p.y=.85f;
    for(const auto &body:movementBodies)if(sphereBox(p,radius,body))return true;
    for(const auto &wall:walls)if(sphereBox(p,radius,wall))return true;
    if(canyon) {
        if(canyon->height(p.x,p.z)>CanyonTerrain::WalkableHeight)return true;
        for(int i=0;i<8;++i) {
            const auto at=add(p,rotateY({radius,0,0},float(i)*Pi/4));
            if(canyon->height(at.x,at.z)>CanyonTerrain::WalkableHeight)return true;
        }
    }
    // Wet-room pits are traversable, but rocks, gates, room edges and raised
    // terrain retain ground collision. This must not use the flying cover mask.
    return false;
}
bool Arena::swimClear(Vector3 from,Vector3 to,float radius,int room) const {
    if(swimBlocked(from,radius,room)||swimBlocked(to,radius,room))return false;
    from.y=to.y=.85f;
    for(const auto &body:movementBodies)if(segmentBox(from,to,body,radius).hit)return false;
    for(const auto &wall:walls)if(segmentBox(from,to,wall,radius).hit)return false;
    if(canyon) {
        from.y=to.y=CanyonTerrain::WalkableHeight;
        if(canyon->trace(from,to).hit)return false;
        for(int i=0;i<8;++i) {
            const auto offset=rotateY({radius,0,0},float(i)*Pi/4);
            if(canyon->trace(add(from,offset),add(to,offset)).hit)return false;
        }
    }
    return true;
}
Vector3 Arena::swim(Vector3 from,Vector3 delta,float radius,int room) const {
    const auto x=add(from,{delta.x,0,0});if(swimClear(from,x,radius,room))from=x;
    const auto z=add(from,{0,0,delta.z});if(swimClear(from,z,radius,room))from=z;
    return from;
}
} // namespace dw
