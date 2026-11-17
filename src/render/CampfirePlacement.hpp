#pragma once
#include "raymath.h"
namespace dw {
inline constexpr const char *TownCampfireLabel="SM_Env_CampFire_01";
// Same local coordinates as Black Creek's fireplace-poc. Fit the retained fire
// contact footprint uniformly; do not scale damage, particles independently or terrain.
inline Matrix campfireTransform(Vector3 position,float radius) {
    const float scale=radius/.76551056f;
    return MatrixMultiply(MatrixScale(scale,scale,scale),MatrixTranslate(position.x,position.y-.85f+.06f,position.z));
}
}
