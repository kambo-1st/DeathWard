#include "combat/Simulation.hpp"
#include "combat/reference/NativeGridPath.hpp"

namespace dw {
namespace {
struct ReviewRoute {bool direct=false;std::vector<Vector3> path;};
// Only the private bounded13x7 geometric review. Rasterizing physical cover
// into source costs is a DW adaptation, not native room-mask generation.
std::optional<ReviewRoute> reviewGridRoute(const Arena &arena,Vector3 from,Vector3 target,float radius) {
    if(arena.floorCells.size()!=91||std::abs(arena.bounds.min.x)>.001f||std::abs(arena.bounds.min.z)>.001f||
       std::abs(arena.bounds.max.x-26)>.001f||std::abs(arena.bounds.max.z-14)>.001f)return {};
    for(int x=0;x<13;++x)for(int z=0;z<7;++z)if(!arena.floorCells.contains({x,z}))return {};
    ReviewRoute result;std::vector<int> costs(135,1000);
    for(int z=1;z<=7;++z)for(int x=1;x<=13;++x) {
        const Vector3 centre{float(2*x-1),from.y,float(2*z-1)};
        if(!arena.blocked(centre,radius))costs[z*15+x]=0;
    }
    auto cell=[](Vector3 p){const int x=int(p.x/2)+1,z=int(p.z/2)+1;return x<1||x>13||z<1||z>7?-1:z*15+x;};
    const int start=cell(from),goal=cell(target);
    if(start<0||goal<0||costs[start]!=0||costs[goal]!=0||arena.blocked(target,radius))return result;
    result.direct=native_grid::clearLine(costs,15,9,from.x/.05f+60,from.z/.05f+140,
                                       target.x/.05f+60,target.z/.05f+140)&&arena.clear(from,target,radius);
    if(result.direct){result.path={target};return result;}
    const auto route=native_grid::gaperWaypoint(costs,15,9,start,goal);
    if(route.found) {
        const Vector3 waypoint{float(2*(route.index%15)-1),from.y,float(2*(route.index/15)-1)};
        if(arena.clear(from,waypoint,radius))result.path={waypoint};
    }
    return result;
}
}
bool Simulation::stepGroundPursuit(Enemy &e,const GroundPursuitDefinition &p,Vector3 &momentum,Vector3 &destination,float force,float *appliedRetention,const Vector3 *target,bool nativeDirect) {
    const auto aim=target?*target:player.position;
    if(appliedRetention)*appliedRetention=1;
    if(e.railCarrier)return false;
    e.pathTime-=1.f/30;
    bool directPath=arena.clear(e.position,aim,e.radius);
    const auto grid=nativeDirect?reviewGridRoute(arena,e.position,aim,e.radius):std::nullopt;
    // Native clear-route selection uses the current target each NPC update.
    // Other arenas retain physical route generation for cover/unreachable points.
    if(grid) {
        destination=aim;e.path=grid->path;e.pathTime=1.f/30;directPath=grid->direct;
    } else if(nativeDirect&&!arena.blocked(aim,e.radius)&&directPath) {
        destination=aim;e.path={aim};e.pathTime=1.1f;
    } else if(e.path.empty()||e.pathTime<=0||planarDistance(destination,aim)>.5f||
       !arena.clear(e.position,e.path.front(),e.radius)) {
        destination=aim;e.path=arena.path(e.position,destination,e.radius);e.pathTime=1.1f;
    }
    // Body separation may displace an actor beyond a corner. Advancing is
    // legal only when the complete next segment fits its grounded footprint.
    while(e.path.size()>1&&planarDistance(e.position,e.path.front())<.3f&&
          arena.clear(e.position,e.path[1],e.radius))e.path.erase(e.path.begin());
    const auto delta=horizontal(sub(e.path.empty()?e.position:e.path.front(),e.position));
    const float distance=length(delta),sourceDistance=distance/p.scale;
    const bool noRoute=nativeDirect?e.path.empty():distance==0;
    if(appliedRetention)*appliedRetention=noRoute?p.blockedRetention:sourceDistance<=p.arrival?p.arrivalRetention:p.retention;
    if(noRoute)momentum=mul(momentum,p.blockedRetention);
    else if(sourceDistance<=p.arrival)momentum=mul(momentum,p.arrivalRetention);
    else momentum=add(mul(momentum,p.retention),
        mul(delta,force*std::min(sourceDistance*p.distanceGain,p.maxGain)/distance));
    return directPath;
}
} // namespace dw
