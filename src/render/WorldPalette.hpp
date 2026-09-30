#pragma once
#include "raylib.h"
#include <string>

namespace dw {
inline constexpr Color WorldSky{154, 186, 199, 255};

// Keep the established hub color treatment in one place. Imported hubs supply
// their authored lights; generated missions use Black Creek/Redstone's daylight
// colors with their existing sun direction. PostProcess supplies the shared grade.
inline std::string withWorldPalette(const char *fragment) {
    constexpr const char *functions = R"GLSL(
const float worldSunAttenuation = .90;
vec3 worldAmbient(vec3 n) {
    return mix(vec3(.27,.245,.215),vec3(.43,.48,.55),n.y*.5+.5);
}
vec3 westernDaylight(vec3 n, vec3 sun, float shade) {
    // Original Black Creek and Redstone primary sun and weaker golden fill.
    const vec3 sunlight = vec3(.992647052,.950363934,.839370668);
    const vec3 fillColor = vec3(.977941155,.689121246,.172577843)*.300000012;
    const vec3 fillDirection = normalize(vec3(.542538583,.506136358,-.670431137));
    return worldAmbient(n) + worldSunAttenuation *
        (max(dot(n,sun),0.)*sunlight*shade + max(dot(n,fillDirection),0.)*fillColor);
}
)GLSL";
    auto source = std::string(fragment);
    source.insert(source.find("void main()"), functions);
    return source;
}
} // namespace dw
