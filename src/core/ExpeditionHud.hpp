#pragma once
#include "raylib.h"

namespace dw::expeditionHud {
// Logical screen coordinates shared by drawing and input. Empty HUD space stays playable.
inline constexpr Rectangle Dynamite{24,626,164,34}, DynamiteMode{196,626,104,34};
inline constexpr Rectangle Dodge{592,716,100,40}, Pause{704,716,100,40};
inline constexpr float ItemSize=36, ItemStride=40;
inline Rectangle items(int count) {return {1256-float(count)*ItemStride,736,float(count)*ItemStride,40};}
inline Rectangle exit(Vector2 marker) {return {marker.x-120,marker.y-30,240,56};}
}
