#include "render/MissionLighting.hpp"
#include "raymath.h"
#include "render/ShaderPlatform.hpp"
#include "render/WorldPalette.hpp"
#include <array>

namespace dw {
namespace {
constexpr const char *Vertex = R"GLSL(#version 330
in vec3 vertexPosition;
in vec3 vertexNormal;
in vec2 vertexTexCoord;
in vec4 vertexColor;
uniform mat4 mvp;
uniform mat4 matModel;
uniform mat4 matNormal;
#ifdef INSTANCED
// Reserve the same four attributes in color/depth programs. raylib retains
// instance attributes on the mesh VAO between passes.
layout(location=8) in mat4 instanceTransform;
#endif
out vec2 uv;
out vec4 color;
out vec3 world;
out vec3 normal;
void main() {
    uv=vertexTexCoord;
#ifdef INSTANCED
    // Western atlas meshes have no vertex colors. DrawMeshInstanced does not
    // reset this absent VAO attribute; a stale alpha could discard every caster.
    color=vec4(1.);
    world=(instanceTransform*vec4(vertexPosition,1.)).xyz;
    normal=normalize(transpose(inverse(mat3(instanceTransform)))*vertexNormal);
    gl_Position=mvp*vec4(world,1.);
#elif defined(PRIMITIVE)
    color=vertexColor;
    // rlgl has already applied each primitive's local transform to its batch.
    world=vertexPosition;
    normal=vertexNormal;
    gl_Position=mvp*vec4(world,1.);
#else
    color=vertexColor;
    world=(matModel*vec4(vertexPosition,1.)).xyz;
    normal=normalize((matNormal*vec4(vertexNormal,0.)).xyz);
    gl_Position=mvp*vec4(vertexPosition,1.);
#endif
}
)GLSL";
constexpr const char *Depth = R"GLSL(#version 330
in vec2 uv;
in vec4 color;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
out vec4 finalColor;
void main() {
    if ((texture(texture0,uv)*colDiffuse*color).a < .5) discard;
    finalColor=vec4(1.);
}
)GLSL";
constexpr const char *Surface = R"GLSL(#version 330
in vec2 uv;
in vec4 color;
in vec3 world;
in vec3 normal;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
out vec4 finalColor;
void main() {
    vec4 surface=texture(texture0,uv)*colDiffuse*color;
    if (surface.a < .02) discard;
#ifdef PRIMITIVE
    // Some raylib primitives do not supply normals. Derivatives recover their facets.
    vec3 n=normalize(cross(dFdx(world),dFdy(world)));
#else
    vec3 n=gl_FrontFacing ? normalize(normal) : -normalize(normal);
#endif
    finalColor=vec4(surface.rgb*westernDaylight(n,missionSun,missionVisibility(world,n)),surface.a);
}
)GLSL";
constexpr const char *ShadowFunctions = R"GLSL(
uniform sampler2D shadowMap;
uniform mat4 lightVP;
uniform int shadowEnabled;
uniform float shadowTexelDepth;
const vec3 missionSun=normalize(vec3(-.55,.85,.38));
float missionVisibility(vec3 position, vec3 n) {
    if (shadowEnabled==0) return 1.;
    vec4 projected=lightVP*vec4(position,1.);
    vec3 p=projected.xyz/projected.w*.5+.5;
    if (p.z<=0. || p.z>=1. || any(lessThan(p.xy,vec2(0.))) ||
        any(greaterThan(p.xy,vec2(1.)))) return 1.;
    float cosine=clamp(dot(n,missionSun),.15,1.);
    float slope=sqrt(max(0.,1.-cosine*cosine))/cosine;
    float bias=shadowTexelDepth*(.65+1.5*slope);
    vec2 size=vec2(textureSize(shadowMap,0));
    vec2 at=p.xy*size-.5;
    vec2 fraction=fract(at), center=floor(at)+.5;
    float lit=0.;
    for (int x=-1;x<=2;++x)
        for (int y=-1;y<=2;++y) {
            float wx=x==-1 ? 1.-fraction.x : (x==2 ? fraction.x : 1.);
            float wy=y==-1 ? 1.-fraction.y : (y==2 ? fraction.y : 1.);
            lit+=wx*wy*(p.z-bias<=texture(shadowMap,(center+vec2(x,y))/size).r ? 1. : 0.);
        }
    float edge=max(abs(p.x*2.-1.),abs(p.y*2.-1.));
    return mix(lit/9.,1.,smoothstep(.86,1.,edge));
}
)GLSL";
std::string variant(const char *source, const char *define) {
    auto result = std::string(source);
    result.insert(result.find('\n') + 1, std::string("#define ") + define + "\n");
    return result;
}
RenderTexture2D target(int size) {
    RenderTexture2D result{};
    result.id = rlLoadFramebuffer();
    if (!result.id)
        return result;
    result.texture.width = result.texture.height = size;
    result.depth = {loadDepthTexture(size, size), size, size, 1, 0};
    rlFramebufferAttach(result.id, result.depth.id, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_TEXTURE2D, 0);
    depthOnlyFramebuffer(result.id);
    if (!result.depth.id || !rlFramebufferComplete(result.id)) {
        UnloadRenderTexture(result);
        return {};
    }
    return result;
}
} // namespace
Vector3 MissionLighting::sun() {
    return Vector3Normalize({-.55f, .85f, .38f});
}
std::string MissionLighting::withShadows(const char *fragment) {
    auto result = std::string(fragment);
    result.insert(result.find("void main()"), ShadowFunctions);
    return withWorldPalette(result.c_str());
}
MissionLighting::~MissionLighting() {
    unload();
}
void MissionLighting::unload() {
    if (shadow_.id)
        UnloadRenderTexture(shadow_);
    if (staticShadow_.id)
        UnloadRenderTexture(staticShadow_);
    for (auto shader : {instanceDepth_, meshDepth_, primitiveDepth_, actor_, primitive_})
        if (shader.id && shader.id != rlGetShaderIdDefault())
            UnloadShader(shader);
    shadow_ = staticShadow_ = {};
    instanceDepth_ = meshDepth_ = primitiveDepth_ = actor_ = primitive_ = {};
    attempted_ = prepared_ = false;
    dirty_ = true;
    span_ = 0;
}
bool MissionLighting::load() {
    if (attempted_)
        return shadow_.id && staticShadow_.id;
    attempted_ = true;
    instanceDepth_ = loadWorldShader(variant(Vertex, "INSTANCED").c_str(), Depth);
    meshDepth_ = loadWorldShader(Vertex, Depth);
    primitiveDepth_ = loadWorldShader(variant(Vertex, "PRIMITIVE").c_str(), Depth);
    const auto fragment = withShadows(Surface);
    actor_ = loadWorldShader(Vertex, fragment.c_str());
    primitive_ =
        loadWorldShader(variant(Vertex, "PRIMITIVE").c_str(), variant(fragment.c_str(), "PRIMITIVE").c_str());
    bool valid = true;
    for (auto shader : {instanceDepth_, meshDepth_, primitiveDepth_, actor_, primitive_})
        valid &= shader.id && shader.id != rlGetShaderIdDefault();
    if (valid) {
        instanceDepth_.locs[SHADER_LOC_MATRIX_MODEL] =
            GetShaderLocationAttrib(instanceDepth_, "instanceTransform");
        actor_.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(actor_, "shadowMap");
        shadow_ = target(Size);
        staticShadow_ = target(Size);
    }
    if (!valid || !shadow_.id || !staticShadow_.id) {
        unload();
        attempted_ = true;
        TraceLog(LOG_WARNING, "MISSION: Shadow resources unavailable; using unshadowed lighting");
        return false;
    }
    return true;
}
bool MissionLighting::contains(Box b) const {
    Box bounds{{1e9f, 1e9f, 1e9f}, {-1e9f, -1e9f, -1e9f}};
    for (float x : {b.min.x, b.max.x})
        for (float y : {b.min.y, b.max.y})
            for (float z : {b.min.z, b.max.z}) {
                const auto p = Vector3Transform({x, y, z}, view_);
                bounds.min = Vector3Min(bounds.min, p);
                bounds.max = Vector3Max(bounds.max, p);
            }
    const float edge = span_ * .5f + 2;
    return bounds.max.x >= -edge && bounds.min.x <= edge && bounds.max.y >= -edge && bounds.min.y <= edge &&
           bounds.max.z >= -360 && bounds.min.z <= -1;
}
void MissionLighting::prepare(const Camera3D &camera, const std::function<void(Shader, Shader)> &scenery,
                              const std::function<void(Shader, Shader)> &actors) {
    if (!load())
        return;
    const float span =
        std::clamp(std::ceil(distance(camera.position, camera.target) * 2.5f / 16) * 16, 80.f, 256.f);
    const float texel = span / Size;
    const auto direction = sun();
    const Vector3 up{0, 1, 0};
    const auto right = Vector3Normalize(Vector3CrossProduct(up, direction));
    const auto sky = Vector3CrossProduct(direction, right);
    const bool rebuild = dirty_ || span_ != span || distance(camera.target, focus_) > span * .075f;
    if (rebuild) {
        focus_ = camera.target;
        for (auto axis : {right, sky, direction}) {
            const float coordinate = dot(focus_, axis);
            focus_ = add(focus_, mul(axis, std::round(coordinate / texel) * texel - coordinate));
        }
    }
    span_ = span;
    Camera3D light{add(focus_, mul(direction, 180)), focus_, up, span, CAMERA_ORTHOGRAPHIC};
    const auto projection = MatrixOrtho(-span * .5, span * .5, -span * .5, span * .5, 1, 360);
    view_ = GetCameraMatrix(light);
    lightVP_ = MatrixMultiply(view_, projection);
    if (rebuild) {
        BeginTextureMode(staticShadow_);
        ClearBackground(WHITE);
        BeginMode3D(light);
        rlSetMatrixProjection(projection);
        rlDisableBackfaceCulling();
        scenery(instanceDepth_, meshDepth_);
        rlDrawRenderBatchActive();
        rlEnableBackfaceCulling();
        EndMode3D();
        EndTextureMode();
        dirty_ = false;
    }
    BeginTextureMode(shadow_);
    rlBindFramebuffer(RL_READ_FRAMEBUFFER, staticShadow_.id);
    rlBindFramebuffer(RL_DRAW_FRAMEBUFFER, shadow_.id);
    rlBlitFramebuffer(0, 0, Size, Size, 0, 0, Size, Size, 0x00000100);
    rlEnableFramebuffer(shadow_.id);
    BeginMode3D(light);
    rlSetMatrixProjection(projection);
    rlDisableBackfaceCulling();
    if (actors)
        actors(meshDepth_, primitiveDepth_);
    rlDrawRenderBatchActive();
    rlEnableBackfaceCulling();
    EndMode3D();
    EndTextureMode();
    prepared_ = true;
    bind(actor_);
    bind(primitive_);
}
void MissionLighting::bind(Shader shader) const {
    if (!shader.id)
        return;
    const int enabled = prepared_ ? 1 : 0;
    const float depth = span_ / Size / 359;
    SetShaderValue(shader, GetShaderLocation(shader, "shadowEnabled"), &enabled, SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "shadowTexelDepth"), &depth, SHADER_UNIFORM_FLOAT);
    SetShaderValueMatrix(shader, GetShaderLocation(shader, "lightVP"), lightVP_);
}
void MissionLighting::beginPrimitives() const {
    if (!ready())
        return;
    rlDrawRenderBatchActive();
    BeginShaderMode(primitive_);
    const int unit = 1;
    SetShaderValue(primitive_, GetShaderLocation(primitive_, "shadowMap"), &unit, SHADER_UNIFORM_INT);
    // Manual binding survives rlgl's automatic batch flushes. Only primitives may be
    // drawn inside this scope; DrawMesh uses the same material texture unit.
    rlActiveTextureSlot(unit);
    rlEnableTexture(shadow_.depth.id);
    rlActiveTextureSlot(0);
}
void MissionLighting::endPrimitives() const {
    if (!ready())
        return;
    EndShaderMode();
    rlActiveTextureSlot(1);
    rlDisableTexture();
    rlActiveTextureSlot(0);
}
void MissionLighting::draw(Mesh mesh, Material material, Matrix transform) const {
    std::array<MaterialMap, 12> maps;
    std::copy_n(material.maps, maps.size(), maps.begin());
    maps[MATERIAL_MAP_METALNESS].texture = texture();
    material.maps = maps.data();
    DrawMesh(mesh, material, transform);
}
void MissionLighting::drawInstanced(Mesh mesh, Material material, const Matrix *transforms, int count) const {
    std::array<MaterialMap, 12> maps;
    std::copy_n(material.maps, maps.size(), maps.begin());
    maps[MATERIAL_MAP_METALNESS].texture = texture();
    material.maps = maps.data();
    DrawMeshInstanced(mesh, material, transforms, count);
}
} // namespace dw
