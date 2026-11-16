#pragma once
#include "raylib.h"

namespace dw::expeditionHud {
// Logical screen coordinates shared by drawing and input. Empty HUD space stays playable.
inline Rectangle categoryReview(bool choices) {return {340,24,600,choices?116.0f:56.0f};}
inline constexpr Rectangle ReviewFight{354,96,260,32}, ReviewBoss{630,96,294,32};
inline constexpr Rectangle Trinket{708,674,286,34};
inline constexpr Rectangle Active{452,674,242,34};
inline constexpr Rectangle Dynamite{24,626,164,34};
inline constexpr Rectangle Dodge{592,716,100,40}, Pause{704,716,100,40};
inline constexpr Rectangle Tuning{308,626,132,34};
inline constexpr float ItemSize=36, ItemStride=40;
inline Rectangle items(int count) {return {1256-float(count)*ItemStride,736,float(count)*ItemStride,40};}
inline Rectangle exit(Vector2 marker) {return {marker.x-120,marker.y-30,240,56};}
}
