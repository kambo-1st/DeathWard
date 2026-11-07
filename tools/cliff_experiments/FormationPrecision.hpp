#pragma once
#include "raylib.h"
namespace dw::rockFormations {
inline thread_local bool worldGridActive=false;
inline thread_local Vector3 worldGridOrigin{};
inline Vector3 canonicalRenderPoint(Vector3 p) {
    if(!worldGridActive)return p;
    p.x=float(float(p.x+worldGridOrigin.x)-worldGridOrigin.x);
    p.z=float(float(p.z+worldGridOrigin.z)-worldGridOrigin.z);
    return p;
}
struct WorldGridScope {
    bool previousActive=worldGridActive;
    Vector3 previousOrigin=worldGridOrigin;
    WorldGridScope(Vector3 origin,bool enabled){worldGridOrigin=origin;worldGridActive=enabled;}
    ~WorldGridScope(){worldGridOrigin=previousOrigin;worldGridActive=previousActive;}
};
}
