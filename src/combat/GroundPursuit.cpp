#include "combat/Simulation.hpp"

namespace dw {
bool Simulation::stepGroundPursuit(Enemy &e,const GroundPursuitDefinition &p,Vector3 &momentum,Vector3 &destination,float force,float *appliedRetention,const Vector3 *target) {
    const auto aim=target?*target:player.position;
    if(appliedRetention)*appliedRetention=1;
    if(e.railCarrier)return false;
    e.pathTime-=1.f/30;
    if(e.path.empty()||e.pathTime<=0||planarDistance(destination,aim)>.5f||
       !arena.clear(e.position,e.path.front(),e.radius)) {
        destination=aim;e.path=arena.path(e.position,destination,e.radius);e.pathTime=1.1f;
    }
    // Body separation may displace an actor beyond a corner. Advancing is
    // legal only when the complete next segment fits its grounded footprint.
    while(e.path.size()>1&&planarDistance(e.position,e.path.front())<.3f&&
          arena.clear(e.position,e.path[1],e.radius))e.path.erase(e.path.begin());
    const auto delta=horizontal(sub(e.path.empty()?e.position:e.path.front(),e.position));
    const float distance=length(delta),sourceDistance=distance/p.scale;
    if(appliedRetention)*appliedRetention=distance==0?p.blockedRetention:sourceDistance<=p.arrival?p.arrivalRetention:p.retention;
    if(distance==0)momentum=mul(momentum,p.blockedRetention);
    else if(sourceDistance<=p.arrival)momentum=mul(momentum,p.arrivalRetention);
    else momentum=add(mul(momentum,p.retention),
        mul(delta,force*std::min(sourceDistance*p.distanceGain,p.maxGain)/distance));
    return arena.clear(e.position,aim,e.radius);
}
} // namespace dw
