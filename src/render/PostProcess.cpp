#include "render/PostProcess.hpp"
#include "render/ShaderPlatform.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <algorithm>

namespace dw {
namespace {
constexpr const char *Silhouette = R"GLSL(#version 330
out vec4 finalColor;
void main() { finalColor = vec4(1.); }
)GLSL";
constexpr const char *Outline = R"GLSL(#version 330
in vec2 fragTexCoord;
uniform sampler2D texture0;
uniform sampler2D modelDepth;
uniform sampler2D sceneDepth;
uniform vec2 texel;
uniform vec2 nearFar;
uniform int orthographic;
out vec4 finalColor;
float eyeDistance(float depth) {
    if (orthographic != 0) return mix(nearFar.x,nearFar.y,depth);
    return nearFar.x*nearFar.y/(nearFar.y-depth*(nearFar.y-nearFar.x));
}
void main() {
    vec2 uv = fragTexCoord;
    // Keep the interior clear; only the external silhouette gets a two-pixel outline.
    if (texture(texture0,uv).r > .5) discard;
    float edge = 0.;
    for (int y=-1;y<=1;++y) for (int x=-1;x<=1;++x) {
        if (x==0 && y==0) continue;
        vec2 p = uv+vec2(x,y)*texel*2.;
        if (any(lessThan(p,vec2(0.))) || any(greaterThan(p,vec2(1.)))) continue;
        if (texture(texture0,p).r <= .5) continue;
        float model = eyeDistance(texture(modelDepth,p).r);
        float scene = eyeDistance(texture(sceneDepth,p).r);
        // Comparing the nearest model surface avoids outlining its own hidden back faces.
        if (model > scene+.06+scene*.0001) edge = 1.;
    }
    if (edge == 0.) discard;
    finalColor = vec4(1.,.34,.20,.9);
}
)GLSL";
constexpr const char *Filter = R"GLSL(#version 330
in vec2 fragTexCoord;
uniform sampler2D texture0;
uniform vec2 texel;
uniform vec2 direction;
uniform int extract;
out vec4 finalColor;
void main() {
    vec2 uv = fragTexCoord;
    vec3 c;
    if (extract != 0) {
        c = (texture(texture0,uv+texel*vec2(-1.,-1.)).rgb +
             texture(texture0,uv+texel*vec2( 1.,-1.)).rgb +
             texture(texture0,uv+texel*vec2(-1., 1.)).rgb +
             texture(texture0,uv+texel*vec2( 1., 1.)).rgb)*.25;
        float brightness = max(c.r,max(c.g,c.b));
        float knee = clamp(brightness-.65+.20,0.,.40);
        float contribution = max(knee*knee/.80,brightness-.65)/max(brightness,.001);
        c *= contribution;
    } else {
        vec2 stepUV = direction * texel;
        c = texture(texture0,uv).rgb*.227027;
        c += (texture(texture0,uv+stepUV*1.384615).rgb +
              texture(texture0,uv-stepUV*1.384615).rgb)*.316216;
        c += (texture(texture0,uv+stepUV*3.230769).rgb +
              texture(texture0,uv-stepUV*3.230769).rgb)*.070270;
    }
    finalColor = vec4(c,1.);
}
)GLSL";
constexpr const char *Composite = R"GLSL(#version 330
in vec2 fragTexCoord;
uniform sampler2D texture0;
uniform sampler2D bloomMap;
uniform sampler2D depthMap;
uniform vec2 texel;
uniform vec2 nearFar;
uniform float fogStart;
uniform float focusDistance;
uniform int fogEnabled;
uniform int artEnabled;
uniform int visualStyle;
uniform float sandstorm;
uniform float weatherTime;
uniform mat4 inverseViewProjection;
out vec4 finalColor;
float luminance(vec3 c) { return dot(c,vec3(.299,.587,.114)); }
float dustHash(vec2 p) {
    vec3 q=fract(vec3(p.xyx)*.1031);
    q+=dot(q,q.yzx+33.33);
    return fract((q.x+q.y)*q.z);
}
float dustNoise(vec2 p) {
    vec2 cell=floor(p), f=fract(p);
    f=f*f*(3.-2.*f);
    return mix(mix(dustHash(cell),dustHash(cell+vec2(1.,0.)),f.x),
               mix(dustHash(cell+vec2(0.,1.)),dustHash(cell+vec2(1.,1.)),f.x),f.y);
}
vec3 stormColor(vec3 c,vec2 uv) {
    if (sandstorm <= 0.) return c;
    float depth=texture(depthMap,uv).r;
    float eye=nearFar.x*nearFar.y/(nearFar.y-depth*(nearFar.y-nearFar.x));
    vec4 world=inverseViewProjection*vec4(uv*2.-1.,depth*2.-1.,1.);
    vec2 p=world.xz/world.w-vec2(7.5,2.4)*weatherTime;
    // Two scales of advected dust give broad gusts and broken, softer edges.
    float billow=dustNoise(p*.045)*.7+dustNoise(p*.12+17.)*.3;
    float gust=.88+.12*sin(weatherTime*.65);
    float opticalDepth=max(eye-fogStart*.45,0.)*.025*(.65+billow)*gust;
    float haze=min(.82,1.-exp(-opticalDepth))*sandstorm;
    vec3 dust=mix(vec3(.58,.47,.34),vec3(.76,.65,.48),billow);
    c=mix(c,dust,haze);
    // Fine suspended grit stays restrained and never touches UI rendered afterward.
    float grit=dustHash(gl_FragCoord.xy+floor(weatherTime*24.)*vec2(37.,11.))-.5;
    return c+grit*.014*sandstorm;
}
vec3 antialias(vec2 uv) {
    vec3 center = texture(texture0,uv).rgb;
    float nw = luminance(texture(texture0,uv+texel*vec2(-1.,-1.)).rgb);
    float ne = luminance(texture(texture0,uv+texel*vec2( 1.,-1.)).rgb);
    float sw = luminance(texture(texture0,uv+texel*vec2(-1., 1.)).rgb);
    float se = luminance(texture(texture0,uv+texel*vec2( 1., 1.)).rgb);
    float middle = luminance(center);
    float low = min(middle,min(min(nw,ne),min(sw,se)));
    float high = max(middle,max(max(nw,ne),max(sw,se)));
    if (high-low < max(.025,high*.10)) return center;
    vec2 direction = vec2(-(nw+ne-sw-se),nw+sw-ne-se);
    float reduce = max((nw+ne+sw+se)*.03125,.0078125);
    direction = clamp(direction/(min(abs(direction.x),abs(direction.y))+reduce),-6.,6.)*texel;
    vec3 a = (texture(texture0,uv-direction/6.).rgb + texture(texture0,uv+direction/6.).rgb)*.5;
    vec3 b = a*.5 + (texture(texture0,uv-direction*.5).rgb + texture(texture0,uv+direction*.5).rgb)*.25;
    float result = luminance(b);
    return result < low || result > high ? a : b;
}
float inkDepth(vec2 uv) {
    float d = texture(depthMap,uv).r;
    return nearFar.x*nearFar.y/(nearFar.y-d*(nearFar.y-nearFar.x));
}
float inkEdge(vec2 uv, float radius) {
    float center = inkDepth(uv);
    float left = inkDepth(uv-vec2(texel.x,0.)*radius);
    float right = inkDepth(uv+vec2(texel.x,0.)*radius);
    float up = inkDepth(uv+vec2(0.,texel.y)*radius);
    float down = inkDepth(uv-vec2(0.,texel.y)*radius);
    // Second differences ignore the steady depth gradient of sloping ground.
    // Texture swatches and transparent dust do not create spurious ink lines.
    float crease = max(abs(left+right-2.*center),abs(up+down-2.*center));
    return smoothstep(.002,.007,crease/max(center,1.));
}
float hatchLine(float phase) {
    // Derivative filtering keeps thin print lines stable at every window size.
    float line = abs(fract(phase)-.5);
    float aa = max(fwidth(phase),.02);
    return 1.-smoothstep(.07,.07+aa,line);
}
vec3 paintedSurface(vec2 uv) {
    vec3 center = antialias(uv);
    float depth = inkDepth(uv);
    vec3 sum = center*2.;
    float total = 2.;
    // A small edge-aware filter joins texture detail into color patches without
    // smearing a character, roof edge or foreground rock into the background.
    for (int y=-1;y<=1;++y) for (int x=-1;x<=1;++x) {
        if (x==0 && y==0) continue;
        vec2 p = uv+vec2(x,y)*texel*1.8;
        vec3 sampleColor = texture(texture0,p).rgb;
        vec3 delta = sampleColor-center;
        float separation = abs(inkDepth(p)-depth)/max(depth,1.);
        float weight = exp(-dot(delta,delta)*24.) *
                       (1.-smoothstep(.001,.006,separation));
        sum += sampleColor*weight;
        total += weight;
    }
    return mix(center,sum/total,.68);
}
float orderedDither(vec2 pixel) {
    const float bayer[16] = float[16](0.,8.,2.,10.,12.,4.,14.,6.,3.,11.,1.,9.,15.,7.,13.,5.);
    ivec2 cell = ivec2(mod(pixel,4.));
    return (bayer[cell.y*4+cell.x]+.5)/16.-.5;
}
// Additional treatments share the same world render and depth; none changes
// scene assets or UI. IDs 7..15 are defined in core/VisualStyle.hpp.
vec3 paperColor(vec2 paper) {
    float tooth = dustNoise(paper*.42)-.5;
    float fibre = dustNoise(paper*vec2(.09,.7))-.5;
    return vec3(.96,.937,.87)*(1.+tooth*.023+fibre*.011);
}
float colorEdge(vec2 uv) {
    float center = luminance(texture(texture0,uv).rgb);
    float laplace = 0.;
    for (int i=0;i<4;++i) {
        float angle = float(i)*1.5707963;
        laplace += luminance(texture(texture0,uv+vec2(cos(angle),sin(angle))*texel*1.6).rgb)-center;
    }
    return smoothstep(.06,.28,abs(laplace));
}
vec3 distanceWash(vec3 c, vec2 uv, vec3 color, float amount) {
    if (fogEnabled == 0) return c;
    float fade = amount*(1.-exp(-max(inkDepth(uv)-fogStart,0.)/48.));
    return mix(c,color,fade);
}
vec3 matteFocus(vec2 uv, float depth) {
    vec3 center = antialias(uv);
    // Keep the camera's subject sharp. A restrained lens cue is strongest at
    // close inspection, never the broad screen-space blur of a tilt-shift mask.
    float defocus = fogEnabled == 0 ? 0. :
        smoothstep(.12,.65,abs(depth-focusDistance)/max(focusDistance,1.))*.65;
    vec3 sum = center*2.;
    float total = 2.;
    for (int i=0;i<8;++i) {
        float angle = float(i)*.78539816;
        vec2 p = uv+vec2(cos(angle),sin(angle))*texel*defocus*3.;
        float weight = 1.-smoothstep(.02,.10,abs(inkDepth(p)-depth)/max(depth,1.));
        sum += texture(texture0,p).rgb*weight;
        total += weight;
    }
    return sum/total;
}
float miniatureContact(vec2 uv, float depth) {
    // Symmetric depth pairs cancel a plane's slope. Avoid per-pixel depth
    // derivatives: depth quantization multiplied by the radius speckles distant
    // ground, even when its actual surface is perfectly flat.
    float occlusion = 0.;
    float radius = clamp(7./(texel.y*1000.),3.,15.);
    for (int i=0;i<4;++i) {
        float angle = float(i)*.78539816;
        vec2 offset = vec2(cos(angle),sin(angle))*radius*texel;
        float forwardDepth = inkDepth(uv+offset);
        float backDepth = inkDepth(uv-offset);
        float crease = depth-(forwardDepth+backDepth)*.5;
        float separation = max(abs(depth-forwardDepth),abs(depth-backDepth));
        occlusion += smoothstep(.10,.65,crease) *
                     (1.-smoothstep(1.,3.,separation));
    }
    return 1.-occlusion/4.*.48;
}
vec3 newStyle(vec2 uv) {
    vec2 paper = gl_FragCoord.xy;
    if (visualStyle == 7) {
        vec3 surface = antialias(uv)*1.12;
        float tone = luminance(surface);
        float wobble = (dustNoise(paper*.035)-.5)*.6;
        float cut = hatchLine(dot(paper,vec2(.052,.088))+wobble);
        float gouge = cut*smoothstep(.11,.42,tone)*(1.-smoothstep(.50,.76,tone));
        vec3 stock = vec3(.94,.86,.67), black = vec3(.09,.115,.135), ochre = vec3(.66,.34,.18);
        // Three base printing inks with cream gouges through the darker blocks.
        vec3 c = mix(black,ochre,smoothstep(.27,.30,tone));
        c = mix(c,stock,smoothstep(.63,.66,tone));
        c = mix(c,stock,gouge*.87);
        c = mix(c,black,inkEdge(uv,1.4)*.90);
        float dryPrint = smoothstep(.82,.94,dustNoise(paper*.5));
        c = mix(c,stock,dryPrint*.22);
        return c*(1.+(dustHash(paper)-.5)*.02);
    }
    if (visualStyle == 8) {
        vec3 surface = paintedSurface(uv)*1.03;
        surface /= 1.+max(surface-.78,vec3(0.))*.6;
        vec3 stock = paperColor(paper);
        float wash = dustNoise(paper*.013)*.6+dustNoise(paper*.047)*.4;
        vec3 c = mix(stock,surface,.70+wash*.13);
        c = mix(c,c*vec3(.88,.97,1.07), (1.-smoothstep(.2,.7,luminance(surface)))*.22);
        // Pigment pools at visible geometry and color boundaries; paper remains
        // beneath translucent washes rather than a blur over the finished frame.
        float pooling = max(inkEdge(uv,1.2)*.65,colorEdge(uv)*.55);
        c *= 1.-pooling*(.10+wash*.12);
        c += (dustNoise(paper*.6)-.5)*.018;
        return distanceWash(c,uv,stock,.35);
    }
    if (visualStyle == 9) {
        vec3 surface = paintedSurface(uv)*1.07;
        surface /= 1.+max(surface-.78,vec3(0.))*.6;
        vec3 stock = paperColor(paper);
        vec3 pigment = clamp(vec3(1.)-surface,0.,1.);
        float wobble = (dustNoise(paper*.037)-.5)*.80;
        float shade = 1.-luminance(surface);
        // Stroke density follows shade; the pigment keeps the local surface hue.
        // Shared color strokes avoid RGB crosshatching that reads as moire.
        float stroke = hatchLine(dot(paper,vec2(.085,.12))+wobble);
        stroke += hatchLine(dot(paper,vec2(-.095,.07))-wobble)*smoothstep(.24,.70,shade)*.65;
        stroke *= .45+.55*dustNoise(paper*vec2(.14,.033));
        vec3 c = stock*(1.-pigment*(.76+stroke*.27));
        float graphite = max(inkEdge(uv,.9)*.65,colorEdge(uv)*.24);
        c = mix(c,c*.47,graphite);
        c *= 1.+(dustNoise(paper*.7)-.5)*.055;
        return distanceWash(c,uv,stock,.18);
    }
    if (visualStyle == 10) {
        float tone = luminance(paintedSurface(uv)*1.10);
        vec3 stock = paperColor(paper);
        float stain = dustNoise(paper*.019)*.65+dustNoise(paper*.083)*.35;
        float ink = pow(1.-smoothstep(.06,.99,tone),1.12);
        ink = clamp(ink*(.89+stain*.26),0.,1.);
        ink = max(ink,inkEdge(uv,1.15)*(.42+ink*.4));
        // Soft brush washes retain a wide range of grays, unlike the binary print.
        vec3 c = mix(stock,vec3(.07,.095,.105),ink);
        c *= 1.+(dustNoise(paper*.45)-.5)*.018;
        return distanceWash(c,uv,stock,.26);
    }
    if (visualStyle == 11) {
        float depth = inkDepth(uv);
        vec3 c = matteFocus(uv,depth)*1.04;
        c = mix(vec3(luminance(c)),c,.92);
        c /= 1.+max(c-.76,vec3(0.))*.65;
        c *= miniatureContact(uv,depth);
        // Matte clay/paint tooth stays tiny; depth and lighting sell the scale.
        c *= 1.+(dustNoise(paper*.42)-.5)*.009;
        return distanceWash(c,uv,vec3(.68,.72,.73),.12);
    }
    if (visualStyle == 12) {
        vec3 surface = max(antialias(uv)*1.18,vec3(0.));
        float tone = luminance(surface);
        vec3 c = mix(vec3(tone),surface,.78);
        c *= mix(vec3(.79,.92,1.07),vec3(1.08,1.025,.88),smoothstep(.12,.75,tone));
        c = max(c-vec3(.016),vec3(0.));
        c /= 1.+max(c-.76,vec3(0.))*.72;
        // Gentle photographic shoulder, sun-bleached color and fine stable grain.
        c += (dustHash(paper)-.5)*.012;
        c *= 1.-smoothstep(.32,.82,length(uv-.5))*.13;
        return distanceWash(c,uv,vec3(.68,.66,.58),.18);
    }
    if (visualStyle == 13) {
        float block = max(1.,floor(1./texel.y/360.));
        vec2 pixel = floor(uv/(texel*block));
        vec2 p = (pixel+.5)*texel*block;
        vec3 c = texture(texture0,p).rgb;
        vec3 bleed = (texture(texture0,p+vec2(texel.x*block,0.)).rgb+
                      texture(texture0,p-vec2(texel.x*block,0.)).rgb)*.5;
        c = mix(c,bleed,.14)*1.19;
        c = mix(vec3(luminance(c)),c,1.16);
        c = max(c,vec3(0.));
        c /= 1.+max(c-.82,vec3(0.))*.5;
        c = floor(clamp(c,0.,1.)*31.+.5+orderedDither(pixel)*.5)/31.;
        // Fixed scanlines and RGB phosphors: no time flicker, screen warp or
        // moving aim coordinates. At low resolution reduce the mask's strength.
        // Align the wave to pixel centers: an unshifted cosine sampled at
        // half-pixels vanishes for two-pixel scanlines.
        float scan = .93+.07*cos((paper.y-.5)/max(block,2.)*6.2831853);
        float stripe = mod(floor(paper.x),3.);
        vec3 mask = stripe < 1. ? vec3(1.,.91,.91) : stripe < 2. ? vec3(.91,1.,.91) : vec3(.91,.91,1.);
        c *= scan*mix(vec3(1.),mask,clamp(block*.4,0.,1.));
        c *= 1.-smoothstep(.25,.79,length(uv-.5))*.15;
        return distanceWash(c,uv,vec3(.46,.48,.62),.14);
    }
    if (visualStyle == 14) {
        // Spectral frontier: cold low-saturation scenery, luminous contour rims and
        // warm saturated accents. Color selection is not a per-object lantern mask.
        vec3 surface = antialias(uv)*1.04;
        float tone = luminance(surface);
        vec3 c = mix(vec3(tone),surface,.18)*vec3(.67,.91,1.06);
        c = c/(1.+max(c-.68,vec3(0.))*.65)+vec3(.015,.025,.038);
        float warmth = smoothstep(.10,.28,surface.r-max(surface.g,surface.b));
        float saturation = (max(surface.r,max(surface.g,surface.b))-min(surface.r,min(surface.g,surface.b)))/max(tone,.01);
        float accent = warmth*smoothstep(.65,1.05,saturation);
        c = mix(c,surface*vec3(1.07,.95,.80),accent*.74);
        float rim = inkEdge(uv,1.05);
        float halo = inkEdge(uv,2.4)*.035;
        c += vec3(.26,.72,.78)*(rim*.24+halo)*(1.-accent*.7);
        c = distanceWash(c,uv,vec3(.27,.41,.48),.24);
        c *= 1.-smoothstep(.32,.80,length(uv-.5))*.10;
        return c;
    }
    // Sumi-e adventure: painted color fields and irregular brush contours, with
    // vermilion/jade accents. An original rendering treatment, no borrowed art.
    vec3 surface = paintedSurface(uv)*1.11;
    float light = luminance(surface);
    vec3 c = mix(vec3(light),surface,1.28);
    float shadow = 1.-smoothstep(.16,.63,light);
    c = mix(c,c*vec3(.89,.85,1.06)+vec3(.045,.019,.042),shadow*.45);
    c *= mix(vec3(1.),vec3(1.08,1.025,.90),smoothstep(.38,.88,light));
    // Redistribute existing pigment, while keeping terrain and characters legible.
    float green = smoothstep(.015,.12,surface.g-max(surface.r,surface.b));
    float red = smoothstep(.12,.32,surface.r-max(surface.g,surface.b));
    c = mix(c,vec3(.18,.57,.40)*(.62+light*.7),green*.62);
    c = mix(c,vec3(.80,.19,.105)*(.65+light*.60),red*.40);
    c = max(c,vec3(0.));
    c /= 1.+max(c-.79,vec3(0.))*.61;
    vec3 stock = paperColor(paper);
    c = mix(c,stock,smoothstep(.66,1.05,light)*.13);
    float brush = dustNoise(paper*.035)*.65+dustNoise(paper*.12)*.35;
    float contour = inkEdge(uv,1.55+brush*.85);
    float bleed = inkEdge(uv,3.)*.12;
    vec3 ink = mix(vec3(.055,.035,.065),vec3(.18,.085,.065),smoothstep(.4,.86,light));
    // A little uneven coverage resembles a loaded brush; no uniform hatch grid.
    c = mix(c,ink,clamp(contour*(.84+brush*.16)+bleed,0.,1.));
    c *= 1.+(dustNoise(paper*.31)-.5)*.025;
    return distanceWash(c,uv,stock,.22);

}
void main() {
    vec2 uv = fragTexCoord;
    if (visualStyle >= 7 && visualStyle <= 15) {
        finalColor = vec4(clamp(stormColor(newStyle(uv),uv),0.,1.),1.);
        return;
    }
    if (visualStyle == 4) {
        vec3 surface = antialias(uv)*1.07;
        float grain = dustHash(gl_FragCoord.xy)-.5;
        float tone = pow(clamp(luminance(surface),0.,1.),.88)+grain*.018;
        // Six printing inks, rather than tinting the existing image sepia.
        vec3 c = tone < .17 ? vec3(.105,.095,.12) :
                 tone < .31 ? vec3(.28,.16,.14) :
                 tone < .46 ? vec3(.49,.29,.20) :
                 tone < .62 ? vec3(.69,.46,.26) :
                 tone < .80 ? vec3(.80,.65,.44) : vec3(.94,.86,.70);
        c = mix(c,vec3(.105,.095,.12),inkEdge(uv,1.)*.78);
        float fibre = dustNoise(gl_FragCoord.xy*vec2(.23,.075))-.5;
        c *= 1.+grain*.030+fibre*.025;
        finalColor = vec4(clamp(stormColor(c,uv),0.,1.),1.);
        return;
    }
    if (visualStyle == 5) {
        vec3 surface = max(antialias(uv)*1.10,vec3(0.));
        float light = luminance(surface);
        float mono = .018+.96*smoothstep(.065,.88,light);
        vec3 c = vec3(mono)*mix(vec3(.95,.98,1.035),vec3(1.025,1.01,.975),mono);
        float high = max(surface.r,max(surface.g,surface.b));
        float low = min(surface.r,min(surface.g,surface.b));
        float saturation = (high-low)/max(high,.001);
        // Selective saturated warm accents and turquoise navigation cues.
        float warm = smoothstep(.09,.23,surface.r-max(surface.g,surface.b));
        float turquoise = smoothstep(.12,.28,min(surface.g,surface.b)-surface.r);
        float accent = max(warm,turquoise)*smoothstep(.48,.72,saturation)*smoothstep(.10,.28,high);
        vec3 color = surface/(1.+max(surface-.80,vec3(0.))*.55);
        c = mix(c,color,accent*.70);
        if (fogEnabled != 0) {
            float fog = .16*(1.-exp(-max(inkDepth(uv)-fogStart,0.)/50.));
            c = mix(c,vec3(.49,.50,.52),fog);
        }
        c += (dustHash(gl_FragCoord.xy)-.5)*.009;
        c *= 1.-smoothstep(.30,.78,length(uv-.5))*.15;
        finalColor = vec4(clamp(stormColor(c,uv),0.,1.),1.);
        return;
    }
    if (visualStyle == 6) {
        // Integer-sized blocks keep the world pixels crisp at any window size.
        // UI is still drawn at full resolution after this world-only pass.
        float block = max(1.,floor(1./texel.y/300.));
        vec2 pixel = floor(uv/(texel*block));
        vec2 sampleUV = (pixel+.5)*texel*block;
        vec3 c = max(texture(texture0,sampleUV).rgb*1.08,vec3(0.));
        c /= 1.+max(c-.78,vec3(0.))*.55;
        if (fogEnabled != 0) {
            float fog = .18*(1.-exp(-max(inkDepth(sampleUV)-fogStart,0.)/45.));
            c = mix(c,vec3(.66,.62,.69),fog);
        }
        c = floor(clamp(c,0.,1.)*15.+.5+orderedDither(pixel))/15.;
        finalColor = vec4(clamp(stormColor(c,sampleUV),0.,1.),1.);
        return;
    }
    if (visualStyle == 2) {
        vec3 c = antialias(uv)*1.09;
        float light = luminance(c);
        c *= mix(vec3(.95,.94,1.04),vec3(1.035,1.005,.94),smoothstep(.25,.80,light));
        c = mix(vec3(luminance(c)),c,1.06);
        c = max(c,vec3(0.));
        c /= 1.+max(c-.80,vec3(0.))*.55;
        // Screen-anchored print texture is intentional: neither paper nor
        // hatching animates with frame time, including when the game is paused.
        vec2 paper = gl_FragCoord.xy;
        float wobble = dustNoise(paper*.022)*.22;
        float hatch = hatchLine(dot(paper,vec2(.083,.061))+wobble) *
                      (1.-smoothstep(.19,.43,light));
        hatch += hatchLine(dot(paper,vec2(-.074,.069))+wobble) *
                 (1.-smoothstep(.10,.24,light))*.7;
        c *= 1.-hatch*.24;
        c = mix(c,vec3(.065,.050,.067),inkEdge(uv,1.25)*.88);
        c *= 1.+(dustHash(paper)-.5)*.024+(dustNoise(paper*.18)-.5)*.015;
        if (fogEnabled != 0) {
            float fog = .14*(1.-exp(-max(inkDepth(uv)-fogStart,0.)/50.));
            c = mix(c,vec3(.73,.67,.64),fog);
        }
        c *= 1.-smoothstep(.35,.78,length(uv-.5))*.05;
        finalColor = vec4(clamp(stormColor(c,uv),0.,1.),1.);
        return;
    }
    if (visualStyle == 3) {
        vec3 c = paintedSurface(uv)*1.05;
        float light = luminance(c);
        float shadow = 1.-smoothstep(.12,.64,light);
        c = mix(c,c*vec3(.85,.96,1.12)+vec3(.022,.022,.038),shadow*.65);
        c *= mix(vec3(1.),vec3(1.045,1.015,.945),smoothstep(.40,.95,light));
        c = mix(vec3(luminance(c)),c,.88);
        c = max(c,vec3(0.));
        c /= 1.+max(c-.76,vec3(0.))*.65;
        // Gentle tonal clustering and a faint static pigment texture, without ink.
        vec3 tones = c*14.;
        c = mix(c,(floor(tones)+smoothstep(.20,.80,fract(tones)))/14.,.28);
        c += (dustNoise(gl_FragCoord.xy*.32)-.5)*.008;
        if (fogEnabled != 0) {
            float fog = .25*(1.-exp(-max(inkDepth(uv)-fogStart,0.)/55.));
            c = mix(c,vec3(.65,.69,.73),fog);
        }
        c *= 1.-smoothstep(.38,.80,length(uv-.5))*.035;
        finalColor = vec4(clamp(stormColor(c,uv),0.,1.),1.);
        return;
    }
    if (visualStyle == 1) {
        vec3 c = antialias(uv);
        // Preserve the Western palette while keeping the light bands crisp.
        c *= 1.08;
        c = mix(vec3(luminance(c)),c,1.10);
        c = max(c,vec3(0.));
        c /= 1.+max(c-.82,vec3(0.))*.45;
        c = mix(c,vec3(.10,.075,.12),inkEdge(uv,1.)*.72);
        if (fogEnabled != 0) {
            float fog = .13*(1.-exp(-max(inkDepth(uv)-fogStart,0.)/45.));
            c = mix(c,vec3(.68,.61,.67),fog);
        }
        c *= 1.-smoothstep(.35,.78,length(uv-.5))*.06;
        finalColor = vec4(clamp(stormColor(c,uv),0.,1.),1.);
        return;
    }
    if (artEnabled != 0) {
        vec3 c=antialias(uv)+texture(bloomMap,uv).rgb*.07;
        c*=1.04;
        c=max(c,vec3(0.));
        c/=1.+max(c-.80,vec3(0.))*.45;
        if (fogEnabled != 0) {
            float depth=texture(depthMap,uv).r;
            float eye=nearFar.x*nearFar.y/(nearFar.y-depth*(nearFar.y-nearFar.x));
            float haze=.28*(1.-exp(-max(eye-fogStart,0.)/65.));
            c=mix(c,vec3(.64,.66,.65),haze);
        }
        float grain=fract(52.9829189*fract(dot(gl_FragCoord.xy,vec2(.06711056,.00583715))))-.5;
        c+=grain*.0025;
        c*=1.-smoothstep(.35,.75,length(uv-.5))*.06;
        finalColor=vec4(clamp(stormColor(c,uv),0.,1.),1.);
        return;
    }
    // A small cross filter softens fine detail without defocusing the character or cover edges.
    vec2 blurStep = texel*1.25;
    vec3 soft = texture(texture0,uv).rgb*.4;
    soft += (texture(texture0,uv+vec2(blurStep.x,0.)).rgb +
             texture(texture0,uv-vec2(blurStep.x,0.)).rgb +
             texture(texture0,uv+vec2(0.,blurStep.y)).rgb +
             texture(texture0,uv-vec2(0.,blurStep.y)).rgb)*.15;
    vec3 c = mix(antialias(uv),soft,.22) + texture(bloomMap,uv).rgb*.42;
    c *= 1.10;
    float luma = luminance(c);
    // Reference palette: lifted plum shadows, saturated amber mids, creamy gold highlights.
    float shade = 1.-smoothstep(.10,.65,luma);
    c += vec3(.10,.025,.16)*shade*.65;
    c *= mix(vec3(.98,.94,1.08),vec3(1.07,1.015,.94),smoothstep(.25,.80,luma));
    c = mix(vec3(luminance(c)),c,1.16);
    // A soft highlight shoulder retains the color of bright sand and pale roof tiles.
    c = max(c,vec3(0.));
    c /= 1.+max(c-.72,vec3(0.))*.60;
    if (fogEnabled != 0) {
        float depth = texture(depthMap,uv).r;
        float eyeDistance = nearFar.x*nearFar.y / (nearFar.y-depth*(nearFar.y-nearFar.x));
        float fog = .18*(1.-exp(-max(eyeDistance-fogStart,0.)/32.));
        c = mix(c,vec3(.68,.58,.64),fog);
    }
    float vignette = smoothstep(.24,.72,length(uv-.5))*.16;
    c = mix(c,c*vec3(.82,.76,.92)+vec3(.025,.008,.04),vignette);
    finalColor = vec4(clamp(stormColor(c,uv),0.,1.),1.);
}
)GLSL";
RenderTexture2D target(int width, int height, bool depth) {
    RenderTexture2D result{};
    result.id = rlLoadFramebuffer();
    if (!result.id)
        return result;
    const int format = worldColorFormat();
    result.texture = {rlLoadTexture(nullptr, width, height, format, 1), width, height, 1, format};
    if (depth) {
        result.depth = {loadDepthTexture(width, height), width, height, 1, 0};
        rlFramebufferAttach(result.id, result.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);
    }
    rlFramebufferAttach(result.id, result.texture.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_TEXTURE2D,
                        0);
    if (!result.texture.id || (depth && !result.depth.id) || !rlFramebufferComplete(result.id)) {
        UnloadRenderTexture(result);
        return {};
    }
    SetTextureFilter(result.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureWrap(result.texture, TEXTURE_WRAP_CLAMP);
    return result;
}
void screenQuad(Texture2D texture, int width, int height) {
    // Each framebuffer pass flips its input once; all intermediate images stay upright.
    DrawTexturePro(texture, {0, 0, float(texture.width), -float(texture.height)},
                   {0, 0, float(width), float(height)}, {0, 0}, 0, WHITE);
}
} // namespace
PostProcess::~PostProcess() {
    unload();
}
void PostProcess::unload() {
    for (auto texture : {scene_, bloom_[0], bloom_[1], silhouette_})
        if (texture.id)
            UnloadRenderTexture(texture);
    for (auto shader : {composite_, filter_, silhouetteShader_, outlineShader_})
        if (shader.id && shader.id != rlGetShaderIdDefault())
            UnloadShader(shader);
    scene_ = bloom_[0] = bloom_[1] = {};
    composite_ = filter_ = {};
    silhouette_ = {};
    silhouetteShader_ = outlineShader_ = {};
    width_ = height_ = 0;
    active_ = false;
    outlineAttempted_ = false;
}
void PostProcess::resize(int width, int height) {
    if (width == width_ && height == height_)
        return;
    unload();
    width_ = width;
    height_ = height;
    composite_ = loadWorldShader(nullptr, Composite);
    filter_ = loadWorldShader(nullptr, Filter);
    if (!composite_.id || !filter_.id || composite_.id == rlGetShaderIdDefault() ||
        filter_.id == rlGetShaderIdDefault()) {
        unload();
        width_ = width;
        height_ = height;
        TraceLog(LOG_WARNING, "POST: Shader unavailable; using direct world rendering");
        return;
    }
    scene_ = target(width, height, true);
    bloom_[0] = target(std::max(1, width / 4), std::max(1, height / 4), false);
    bloom_[1] = target(std::max(1, width / 4), std::max(1, height / 4), false);
    if (!ready()) {
        unload();
        width_ = width;
        height_ = height;
        TraceLog(LOG_WARNING, "POST: Framebuffer unavailable; using direct world rendering");
    }
}
void PostProcess::begin(Color background, float focusDistance, bool artPoc, VisualStyle visualStyle) {
    resize(std::max(1, GetRenderWidth()), std::max(1, GetRenderHeight()));
    focusDistance_ = focusDistance;
    artPoc_ = artPoc;
    visualStyle_ = visualStyle;
    sandstorm_ = 0;
    active_ = ready();
    if (active_)
        BeginTextureMode(scene_);
    ClearBackground(background);
}
void PostProcess::sandstorm(float strength, float time) {
    sandstorm_ = std::clamp(strength, 0.f, 1.f);
    if (sandstorm_ <= 0)
        return;
    weatherTime_ = time;
    inverseViewProjection_ = MatrixInvert(MatrixMultiply(rlGetMatrixModelview(), rlGetMatrixProjection()));
}
void PostProcess::filter(Texture2D source, RenderTexture2D destination, int extract, Vector2 direction) {
    const Vector2 texel{1.0f / source.width, 1.0f / source.height};
    SetShaderValue(filter_, GetShaderLocation(filter_, "texel"), &texel, SHADER_UNIFORM_VEC2);
    SetShaderValue(filter_, GetShaderLocation(filter_, "direction"), &direction, SHADER_UNIFORM_VEC2);
    SetShaderValue(filter_, GetShaderLocation(filter_, "extract"), &extract, SHADER_UNIFORM_INT);
    BeginTextureMode(destination);
    BeginShaderMode(filter_);
    screenQuad(source, destination.texture.width, destination.texture.height);
    EndShaderMode();
    EndTextureMode();
}
void PostProcess::end() {
    if (!active_)
        return;
    EndTextureMode();
    if (visualStyle_ == VisualStyle::Original) {
        filter(scene_.texture, bloom_[0], 1, {});
        filter(bloom_[0].texture, bloom_[1], 0, {2.0f, 0});
        filter(bloom_[1].texture, bloom_[0], 0, {0, 2.0f});
    }
    const Vector2 texel{1.0f / width_, 1.0f / height_};
    SetShaderValue(composite_, GetShaderLocation(composite_, "texel"), &texel, SHADER_UNIFORM_VEC2);
    const Vector2 nearFar{float(rlGetCullDistanceNear()), float(rlGetCullDistanceFar())};
    const float fogStart = std::max(12.0f, focusDistance_ * .85f);
    SetShaderValue(composite_, GetShaderLocation(composite_, "focusDistance"), &focusDistance_, SHADER_UNIFORM_FLOAT);
    const int fogEnabled = focusDistance_ > 0, artEnabled = artPoc_;
    const int style = int(visualStyle_);
    SetShaderValue(composite_, GetShaderLocation(composite_, "visualStyle"), &style, SHADER_UNIFORM_INT);
    SetShaderValue(composite_, GetShaderLocation(composite_, "artEnabled"), &artEnabled, SHADER_UNIFORM_INT);
    SetShaderValue(composite_, GetShaderLocation(composite_, "nearFar"), &nearFar, SHADER_UNIFORM_VEC2);
    SetShaderValue(composite_, GetShaderLocation(composite_, "fogStart"), &fogStart, SHADER_UNIFORM_FLOAT);
    SetShaderValue(composite_, GetShaderLocation(composite_, "fogEnabled"), &fogEnabled, SHADER_UNIFORM_INT);
    SetShaderValue(composite_, GetShaderLocation(composite_, "sandstorm"), &sandstorm_, SHADER_UNIFORM_FLOAT);
    if (sandstorm_ > 0) {
        SetShaderValue(composite_, GetShaderLocation(composite_, "weatherTime"), &weatherTime_, SHADER_UNIFORM_FLOAT);
        SetShaderValueMatrix(composite_, GetShaderLocation(composite_, "inverseViewProjection"), inverseViewProjection_);
    }
    BeginShaderMode(composite_);
    SetShaderValueTexture(composite_, GetShaderLocation(composite_, "bloomMap"), bloom_[0].texture);
    SetShaderValueTexture(composite_, GetShaderLocation(composite_, "depthMap"), scene_.depth);
    screenQuad(scene_.texture, GetScreenWidth(), GetScreenHeight());
    EndShaderMode();
    active_ = false;
}
void PostProcess::outlineOccluded(const Camera3D &camera, const std::function<void()> &drawModels) {
    if (active_ || !ready())
        return;
    if (!outlineAttempted_) {
        outlineAttempted_ = true;
        silhouetteShader_ = loadWorldShader(nullptr, Silhouette);
        outlineShader_ = loadWorldShader(nullptr, Outline);
        silhouette_ = target(width_, height_, true);
        if (silhouette_.id)
            SetTextureFilter(silhouette_.texture, TEXTURE_FILTER_POINT);
    }
    if (!silhouette_.id || !silhouetteShader_.id || !outlineShader_.id ||
        silhouetteShader_.id == rlGetShaderIdDefault() || outlineShader_.id == rlGetShaderIdDefault())
        return;
    // A separate nearest-surface mask preserves the actual animated body and appendages.
    BeginTextureMode(silhouette_);
    ClearBackground(BLACK);
    BeginMode3D(camera);
    BeginShaderMode(silhouetteShader_);
    drawModels();
    EndShaderMode();
    EndMode3D();
    EndTextureMode();

    const Vector2 texel{1.f / width_, 1.f / height_};
    const Vector2 nearFar{float(rlGetCullDistanceNear()), float(rlGetCullDistanceFar())};
    const int orthographic = camera.projection == CAMERA_ORTHOGRAPHIC;
    SetShaderValue(outlineShader_, GetShaderLocation(outlineShader_, "texel"), &texel, SHADER_UNIFORM_VEC2);
    SetShaderValue(outlineShader_, GetShaderLocation(outlineShader_, "nearFar"), &nearFar,
                   SHADER_UNIFORM_VEC2);
    SetShaderValue(outlineShader_, GetShaderLocation(outlineShader_, "orthographic"), &orthographic,
                   SHADER_UNIFORM_INT);
    BeginShaderMode(outlineShader_);
    SetShaderValueTexture(outlineShader_, GetShaderLocation(outlineShader_, "modelDepth"), silhouette_.depth);
    SetShaderValueTexture(outlineShader_, GetShaderLocation(outlineShader_, "sceneDepth"), scene_.depth);
    screenQuad(silhouette_.texture, GetScreenWidth(), GetScreenHeight());
    EndShaderMode();
}
} // namespace dw
