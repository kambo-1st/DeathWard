#include "render/PostProcess.hpp"
#include "rlgl.h"
#include <algorithm>

namespace dw {
namespace {
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
uniform int fogEnabled;
out vec4 finalColor;
float luminance(vec3 c) { return dot(c,vec3(.299,.587,.114)); }
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
void main() {
    vec2 uv = fragTexCoord;
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
    finalColor = vec4(clamp(c,0.,1.),1.);
}
)GLSL";
RenderTexture2D target(int width, int height, bool depth) {
    RenderTexture2D result{};
    result.id = rlLoadFramebuffer();
    if (!result.id)
        return result;
    result.texture = {rlLoadTexture(nullptr, width, height, PIXELFORMAT_UNCOMPRESSED_R16G16B16A16, 1), width,
                      height, 1, PIXELFORMAT_UNCOMPRESSED_R16G16B16A16};
    if (depth) {
        result.depth = {rlLoadTextureDepth(width, height, false), width, height, 1, 0};
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
    for (auto texture : {scene_, bloom_[0], bloom_[1]})
        if (texture.id)
            UnloadRenderTexture(texture);
    for (auto shader : {composite_, filter_})
        if (shader.id && shader.id != rlGetShaderIdDefault())
            UnloadShader(shader);
    scene_ = bloom_[0] = bloom_[1] = {};
    composite_ = filter_ = {};
    width_ = height_ = 0;
    active_ = false;
}
void PostProcess::resize(int width, int height) {
    if (width == width_ && height == height_)
        return;
    unload();
    width_ = width;
    height_ = height;
    composite_ = LoadShaderFromMemory(nullptr, Composite);
    filter_ = LoadShaderFromMemory(nullptr, Filter);
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
void PostProcess::begin(Color background, float focusDistance) {
    resize(std::max(1, GetRenderWidth()), std::max(1, GetRenderHeight()));
    focusDistance_ = focusDistance;
    active_ = ready();
    if (active_)
        BeginTextureMode(scene_);
    ClearBackground(background);
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
    filter(scene_.texture, bloom_[0], 1, {});
    filter(bloom_[0].texture, bloom_[1], 0, {2.0f, 0});
    filter(bloom_[1].texture, bloom_[0], 0, {0, 2.0f});
    const Vector2 texel{1.0f / width_, 1.0f / height_};
    SetShaderValue(composite_, GetShaderLocation(composite_, "texel"), &texel, SHADER_UNIFORM_VEC2);
    const Vector2 nearFar{float(rlGetCullDistanceNear()), float(rlGetCullDistanceFar())};
    const float fogStart = std::max(12.0f, focusDistance_ * .85f);
    const int fogEnabled = focusDistance_ > 0;
    SetShaderValue(composite_, GetShaderLocation(composite_, "nearFar"), &nearFar, SHADER_UNIFORM_VEC2);
    SetShaderValue(composite_, GetShaderLocation(composite_, "fogStart"), &fogStart, SHADER_UNIFORM_FLOAT);
    SetShaderValue(composite_, GetShaderLocation(composite_, "fogEnabled"), &fogEnabled, SHADER_UNIFORM_INT);
    BeginShaderMode(composite_);
    SetShaderValueTexture(composite_, GetShaderLocation(composite_, "bloomMap"), bloom_[0].texture);
    SetShaderValueTexture(composite_, GetShaderLocation(composite_, "depthMap"), scene_.depth);
    screenQuad(scene_.texture, GetScreenWidth(), GetScreenHeight());
    EndShaderMode();
    active_ = false;
}
} // namespace dw
