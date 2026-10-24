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
uniform int visualStyle;
float worldDiffuse(float direct, float shade) {
    if (visualStyle == 0 || visualStyle == 6 || visualStyle == 13) return direct*shade;
    float value = direct*shade;
    if (visualStyle == 8 || visualStyle == 9 || visualStyle == 10)
        return mix(value,smoothstep(0.,1.,value),.35);
    if (visualStyle == 11) return pow(value,.85)*.90;
    if (visualStyle == 12) return pow(value,1.12);
    if (visualStyle == 14) return value*.72;
    // Continuous diffuse light: broad matte facets rather than toon bands.
    if (visualStyle == 16) return mix(value,smoothstep(0.,1.,value),.22)*.96;
    if (visualStyle == 15) {
        float edge = max(fwidth(value),.018);
        return .16+.34*smoothstep(.30-edge,.30+edge,value)+
                   .46*smoothstep(.69-edge,.69+edge,value);
    }
    if (visualStyle == 3) return mix(value,smoothstep(0.,1.,value),.25);
    if (visualStyle == 5) return pow(value,1.25);
    // Three light bands; a pixel-wide transition keeps moving edges stable.
    float edge = max(fwidth(value),.012);
    return .10 + .38*smoothstep(.25-edge,.25+edge,value) +
                 .50*smoothstep(.65-edge,.65+edge,value);
}
vec3 worldAmbient(vec3 n) {
    // IDs follow VisualStyle.hpp. New presets opt into their own fill rather
    // than accidentally inheriting the three-band cel treatment.
    if (visualStyle == 7)
        return mix(vec3(.13,.13,.16),vec3(.29,.30,.34),smoothstep(.10,.25,n.y));
    if (visualStyle == 8 || visualStyle == 9)
        return mix(vec3(.33,.34,.40),vec3(.49,.52,.57),n.y*.5+.5);
    if (visualStyle == 10)
        return mix(vec3(.21,.23,.26),vec3(.42,.44,.46),n.y*.5+.5);
    if (visualStyle == 11)
        return mix(vec3(.28,.30,.35),vec3(.48,.51,.55),n.y*.5+.5);
    if (visualStyle == 12)
        return mix(vec3(.16,.19,.23),vec3(.34,.37,.41),n.y*.5+.5);
    if (visualStyle == 14)
        return mix(vec3(.14,.19,.26),vec3(.30,.40,.47),n.y*.5+.5);
    if (visualStyle == 15)
        return mix(vec3(.24,.20,.30),vec3(.40,.44,.48),smoothstep(.08,.28,n.y));
    if (visualStyle == 16)
        return mix(vec3(.22,.215,.195),vec3(.40,.415,.39),n.y*.5+.5);
    if (visualStyle == 5)
        return mix(vec3(.15,.16,.20),vec3(.34,.37,.42),n.y*.5+.5);
    if (visualStyle == 3)
        return mix(vec3(.31,.30,.36),vec3(.49,.53,.58),n.y*.5+.5);
    if (visualStyle == 2)
        return mix(vec3(.19,.17,.22),vec3(.31,.34,.39),smoothstep(.15,.22,n.y));
    if (visualStyle != 0 && visualStyle != 6 && visualStyle != 13)
        return mix(vec3(.24,.21,.28),vec3(.34,.38,.44),smoothstep(.15,.22,n.y));
    return mix(vec3(.27,.245,.215),vec3(.43,.48,.55),n.y*.5+.5);
}
vec3 worldSurfaceColor(vec3 c) {
    if (visualStyle != 16) return c;
    // Quiet, earthy body colors with readable olive foliage. Applied to albedo
    // before lighting, so authored amber lamps retain their own light color.
    float tone=dot(c,vec3(.299,.587,.114));
    float green=smoothstep(.012,.09,c.g-max(c.r,c.b));
    vec3 earthy=mix(vec3(tone),c,.82);
    float ochre=smoothstep(.06,.25,min(c.r,c.g)-c.b);
    earthy*=mix(vec3(1.),vec3(.90,.92,.98),ochre*.65);
    vec3 olive=vec3(.61,.72,.32)*max(tone,.04)*1.32;
    return mix(earthy,olive,green*.42);
}
vec3 westernDaylight(vec3 n, vec3 sun, float shade) {
    // Original Black Creek and Redstone primary sun and weaker golden fill.
    const vec3 sunlight = vec3(.992647052,.950363934,.839370668);
    const vec3 fillColor = vec3(.977941155,.689121246,.172577843)*.300000012;
    const vec3 fillDirection = normalize(vec3(.542538583,.506136358,-.670431137));
    if (visualStyle != 0)
        return worldAmbient(n) + worldSunAttenuation *
            (worldDiffuse(max(dot(n,sun),0.),shade)*sunlight +
             worldDiffuse(max(dot(n,fillDirection),0.),1.)*fillColor);
    return worldAmbient(n) + worldSunAttenuation *
        (max(dot(n,sun),0.)*sunlight*shade + max(dot(n,fillDirection),0.)*fillColor);
}
)GLSL";
    auto source = std::string(fragment);
    source.insert(source.find("void main()"), functions);
    return source;
}
} // namespace dw
