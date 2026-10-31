#include "combat/Simulation.hpp"

namespace dw {
void Simulation::updateReturningBody(Enemy &e,float dt) {
    const auto &p=*content->returningBody(e.monster);auto &r=*e.returningBody;
    const auto *owner=findEnemy(e.componentOwner);r.motion.clear();
    if(!owner||!owner->alive||owner->monster!=p.owner){e.alive=false;return;}
    e.age+=dt;float elapsed=0;
    while(elapsed+1e-7f<dt&&e.alive) {
        if(r.clock<1e-6f) {
            // Native519b75 compares the old counter before incrementing it:
            // counter42 is still active; the next controller update removes it.
            if(r.frame>p.removeAfter){e.alive=false;break;}
            const float q=1-float(r.frame)/float(p.reversalFrame);
            if(q>=0)e.velocity=mul(r.initialVelocity,q);
            else {
                auto delta=horizontal(sub(owner->position,e.position));const float distance=length(delta);
                // Native subtraction is not clamped: within the return offset,
                // the vector reverses to keep the final body outside its owner.
                if(distance>1e-6f)delta=mul(delta,(distance-p.returnOffset*p.scale)/distance);
                e.velocity=mul(delta,(-q)*30/float(std::max(p.removeAfter+1-r.frame,1)));
            }
        }
        const float slice=std::min(dt-elapsed,1.f/30-r.clock);
        const auto before=e.position;e.position=add(e.position,mul(e.velocity,slice));
        r.motion.push_back({before,e.position,elapsed/dt,(elapsed+slice)/dt});
        if(segmentSphere(before,e.position,player.position,e.radius+.48f)<=1) {
            Context source;source.sourceEntity=e.id;hurtPlayer(p.contact,source);
        }
        elapsed+=slice;r.clock+=slice;
        if(r.clock+1e-6f>=1.f/30) {
            r.clock=0;
            ++r.frame;
        }
    }
    const auto heading=length(horizontal(e.velocity))>.01f?e.velocity:r.initialVelocity;
    e.facing=unit(horizontal(heading));
}

float Simulation::returningBodyHit(const Enemy &e,Vector3 from,Vector3 to,float radius,float begin,float end) const {
    const auto &motion=e.returningBody->motion;
    if(motion.empty())return segmentSphere(from,to,e.position,e.radius+radius);
    float best=2;
    for(const auto &part:motion) {
        const float first=std::max(begin,part.begin),last=std::min(end,part.end);
        if(last<=first||end<=begin)continue;
        const auto bodyAt=[&](float t){return add(part.from,mul(sub(part.to,part.from),(t-part.begin)/(part.end-part.begin)));};
        const auto shotAt=[&](float t){return add(from,mul(sub(to,from),(t-begin)/(end-begin)));};
        const float hit=segmentSphere(sub(shotAt(first),bodyAt(first)),sub(shotAt(last),bodyAt(last)),{},e.radius+radius);
        if(hit<=1)best=std::min(best,(first-begin+hit*(last-first))/(end-begin));
    }
    return best;
}
} // namespace dw
