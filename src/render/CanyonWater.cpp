#include "render/CanyonWater.hpp"
#include "raymath.h"
#include "render/ShaderPlatform.hpp"
#include <map>

namespace dw {
namespace {
constexpr const char *Vertex = R"GLSL(#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;
uniform mat4 mvp;
out vec3 world;
out vec2 flow;
out float depth;
void main() {
    world = vertexPosition;
    flow = vertexTexCoord;
    depth = vertexColor.r * 1.8;
    gl_Position = mvp * vec4(world,1.);
}
)GLSL";
constexpr const char *Fragment = R"GLSL(#version 330
in vec3 world;
in vec2 flow;
in float depth;
uniform float riverTime;
out vec4 finalColor;
float sandHash(vec2 p) {
    vec3 q=fract(vec3(p.xyx)*.1031);
    q+=dot(q,q.yzx+33.33);
    return fract((q.x+q.y)*q.z);
}
float sandNoise(vec2 p) {
    vec2 i=floor(p), f=fract(p);
    f=f*f*(3.-2.*f);
    return mix(mix(sandHash(i),sandHash(i+vec2(1,0)),f.x),
               mix(sandHash(i+vec2(0,1)),sandHash(i+vec2(1,1)),f.x),f.y);
}
void main() {
    // Longitudinal coordinates follow the curved channel, so ripples cannot
    // slide sideways across bends. Opaque depth-colored water avoids sorting
    // artifacts against faded cliffs and works identically in WebGL 2.
    float ripple = sin(flow.x*2.6-riverTime*1.1+sin(flow.y*1.9)*.5);
    float small = sin(flow.x*6.7-riverTime*1.8+flow.y*3.1);
    vec3 n = normalize(vec3(ripple*.025,1.,small*.016));
    float shade = missionVisibility(world,vec3(0,1,0));
    // The light, sandy fords remain readable at the normal gameplay zoom.
    // Darker water begins near the movement depth limit, not metres below it.
    float deep = smoothstep(.045,.20,depth);
    float bed = sandNoise(world.xz*8.3)-.5;
    float pixel = max(length(dFdx(world.xz)),length(dFdy(world.xz)));
    vec3 shallow = vec3(.34,.405,.365)*(1.+bed*.045*(1.-smoothstep(.06,.18,pixel)));
    vec3 water = mix(shallow,vec3(.175,.275,.26),deep);
    water *= 1.+ripple*.018+small*.007;
    float glint = pow(max(0.,ripple*.7+small*.3),12.);
    water += vec3(.16,.19,.17)*glint*.18*shade;
    finalColor = vec4(water*westernDaylight(n,missionSun,shade),1.);
    // The shallow bed is only centimetres below the surface. Two depth-buffer
    // steps prevent distant fords from fighting the bed at the game's near clip.
    gl_FragDepth = max(0.,gl_FragCoord.z-.00000012);
}
)GLSL";
struct VertexData {
    Vector3 p;
    Vector2 flow;
    float depth;
};
} // namespace
void CanyonWater::unload() {
    for (auto &chunk : chunks_)
        UnloadMesh(chunk.mesh);
    chunks_.clear();
    if (shader_.id)
        UnloadShader(shader_);
    if (material_.maps)
        MemFree(material_.maps);
    shader_ = {};
    material_ = {};
}
void CanyonWater::prepare(const CanyonTerrain &field) {
    unload();
    if (field.river.empty())
        return;
    shader_ = loadWorldShader(Vertex, MissionLighting::withShadows(Fragment).c_str());
    material_ = LoadMaterialDefault();
    material_.shader = shader_;
    shader_.locs[SHADER_LOC_MAP_METALNESS] = GetShaderLocation(shader_, "shadowMap");
    std::map<int, std::vector<VertexData>> sections;
    // Clip against the very same triangles used for terrain and collision. No
    // rectangular water cards protrude onto land, and neighboring edges agree.
    auto vertex = [&](Vector3 p) {
        const auto sample = field.riverSample(p);
        return VertexData{p, {sample.along, sample.side}, CanyonTerrain::WaterLevel - p.y};
    };
    for (int z = 0; z + 1 < field.depth; ++z)
        for (int x = 0; x + 1 < field.width; ++x) {
            const auto a = field.vertex(x, z), b = field.vertex(x + 1, z), c = field.vertex(x, z + 1),
                       d = field.vertex(x + 1, z + 1);
            if (std::min({a.y, b.y, c.y, d.y}) >= CanyonTerrain::WaterLevel)
                continue;
            for (auto tri : {std::array{a, d, b}, std::array{a, c, d}}) {
                std::vector<VertexData> clipped;
                for (int i = 0; i < 3; ++i) {
                    auto v = vertex(tri[size_t(i)]), w = vertex(tri[size_t((i + 1) % 3)]);
                    const bool inside = v.depth > 0, nextInside = w.depth > 0;
                    if (inside)
                        clipped.push_back(v);
                    if (inside != nextInside) {
                        const float t = v.depth / (v.depth - w.depth);
                        clipped.push_back(
                            {add(v.p, mul(sub(w.p, v.p), t)),
                             {std::lerp(v.flow.x, w.flow.x, t), std::lerp(v.flow.y, w.flow.y, t)},
                             0});
                    }
                }
                auto &out = sections[(z / 24) * ((field.width + 22) / 24) + x / 24];
                for (size_t n = 1; n + 1 < clipped.size(); ++n)
                    for (auto v : {clipped[0], clipped[n], clipped[n + 1]}) {
                        v.p.y = CanyonTerrain::WaterLevel;
                        out.push_back(v);
                    }
            }
        }
    for (const auto &[key, vertices] : sections) {
        (void)key;
        if (vertices.empty())
            continue;
        Mesh mesh{};
        mesh.vertexCount = int(vertices.size());
        mesh.triangleCount = mesh.vertexCount / 3;
        mesh.vertices = static_cast<float *>(MemAlloc(unsigned(vertices.size() * 3 * sizeof(float))));
        mesh.texcoords = static_cast<float *>(MemAlloc(unsigned(vertices.size() * 2 * sizeof(float))));
        mesh.colors = static_cast<unsigned char *>(MemAlloc(unsigned(vertices.size() * 4)));
        for (size_t i = 0; i < vertices.size(); ++i) {
            const auto &v = vertices[i];
            mesh.vertices[i * 3] = v.p.x;
            mesh.vertices[i * 3 + 1] = v.p.y;
            mesh.vertices[i * 3 + 2] = v.p.z;
            mesh.texcoords[i * 2] = v.flow.x;
            mesh.texcoords[i * 2 + 1] = v.flow.y;
            mesh.colors[i * 4] = static_cast<unsigned char>(std::clamp(v.depth / 1.8f, 0.f, 1.f) * 255);
            mesh.colors[i * 4 + 1] = mesh.colors[i * 4 + 2] = mesh.colors[i * 4 + 3] = 255;
        }
        UploadMesh(&mesh, false);
        const auto box = GetMeshBoundingBox(mesh);
        chunks_.push_back({mesh, {box.min, box.max}});
    }
}
void CanyonWater::draw(Vector3 focus, const MissionLighting &lighting) const {
    if (chunks_.empty())
        return;
    const float time = float(std::fmod(GetTime(), 4096.));
    SetShaderValue(shader_, GetShaderLocation(shader_, "riverTime"), &time, SHADER_UNIFORM_FLOAT);
    lighting.bind(shader_);
    for (const auto &chunk : chunks_) {
        const Vector3 closest{std::clamp(focus.x, chunk.bounds.min.x, chunk.bounds.max.x), focus.y,
                              std::clamp(focus.z, chunk.bounds.min.z, chunk.bounds.max.z)};
        if (distance(focus, closest) < 110)
            lighting.draw(chunk.mesh, material_, MatrixIdentity());
    }
}
} // namespace dw
