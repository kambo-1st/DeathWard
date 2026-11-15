#pragma once
#include "core/Types.hpp"

namespace dw::pedestalGeometry {
// The retained eight-sided stone model and its grounded footprint share sizes.
// Movement uses the full base prism (not the tapered top). Inflated face planes
// give a conservative swept character footprint, including fast dodge steps.
inline constexpr float BaseRadius=1, TopRadius=.8f, Height=.7f;
inline constexpr int Sides=8;
inline constexpr float PlayerRadius=.48f, ContactMargin=.08f;
inline constexpr float C=.923879533f, S=.382683432f;
inline constexpr std::array<Vector3,Sides> Normals{{
    {C,0,S},{S,0,C},{-S,0,C},{-C,0,S},
    {-C,0,-S},{-S,0,-C},{S,0,-C},{C,0,-S}}};
inline Box bounds(Vector3 at) {
    return {{at.x-BaseRadius,0,at.z-BaseRadius},{at.x+BaseRadius,Height,at.z+BaseRadius}};
}
inline bool intersects(Vector3 from,Vector3 to,Vector3 at,float radius) {
    float enter=0,leave=1;
    const auto clip=[&](float a,float b,float limit) {
        const float d=b-a;
        if(std::abs(d)<.000001f)return a<=limit;
        const float t=(limit-a)/d;
        if(d>0)leave=std::min(leave,t);else enter=std::max(enter,t);
        return enter<=leave;
    };
    if(!clip(from.y,to.y,Height+radius)||!clip(-from.y,-to.y,radius))return false;
    from=sub(from,at);to=sub(to,at);
    for(auto n:Normals)
        if(!clip(from.x*n.x+from.z*n.z,to.x*n.x+to.z*n.z,BaseRadius*C+radius))return false;
    return true;
}
inline Vector3 approach(Vector3 at,Vector3 direction,float y) {
    direction=unit(horizontal(direction));
    if(length(direction)<.001f)direction={1,0,0};
    float projection=0;
    for(auto n:Normals)projection=std::max(projection,direction.x*n.x+direction.z*n.z);
    auto point=add(at,mul(direction,(BaseRadius*C+PlayerRadius+.04f)/projection));
    point.y=y;return point;
}
inline bool touching(Vector3 player,Vector3 at) {
    return intersects(player,player,at,PlayerRadius+ContactMargin);
}
} // namespace dw::pedestalGeometry
