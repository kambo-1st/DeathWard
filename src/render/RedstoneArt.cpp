#include "render/RedstoneArt.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <cstring>

namespace dw {
namespace {
constexpr int MapSize = 1024;
constexpr float MapStart = -128, MapSpan = 256;
bool contains(const std::string &s, const char *part) {
    return s.find(part) != std::string::npos;
}
struct Vertex {
    Vector3 p, n;
    Vector2 uv;
    Color c;
};
using Vertices = std::vector<Vertex>;
void triangle(Vertices &v, Vector3 a, Vector3 b, Vector3 c, Color color, Vector2 ta = {}, Vector2 tb = {},
              Vector2 tc = {}) {
    const auto n = Vector3Normalize(Vector3CrossProduct(sub(b, a), sub(c, a)));
    v.insert(v.end(), {{a, n, ta, color}, {b, n, tb, color}, {c, n, tc, color}});
}
void beam(Vertices &v, Vector3 a, Vector3 b, float radius, Color c) {
    const auto axis = unit(sub(b, a));
    const auto side =
        mul(unit(Vector3CrossProduct(axis, std::abs(axis.y) > .95f ? Vector3{1, 0, 0} : Vector3{0, 1, 0})),
            radius);
    const auto up = Vector3CrossProduct(axis, side);
    for (int n = 0; n < 6; ++n) {
        const float t = n * Pi / 3, t2 = (n + 1) * Pi / 3;
        const auto p = add(mul(side, std::cos(t)), mul(up, std::sin(t)));
        const auto q = add(mul(side, std::cos(t2)), mul(up, std::sin(t2)));
        triangle(v, add(a, p), add(b, p), add(b, q), c);
        triangle(v, add(a, p), add(b, q), add(a, q), c);
    }
}
Model upload(const Vertices &v) {
    if (v.empty())
        return {};
    Mesh m{};
    m.vertexCount = int(v.size());
    m.triangleCount = m.vertexCount / 3;
    m.vertices = static_cast<float *>(MemAlloc(v.size() * 3 * sizeof(float)));
    m.normals = static_cast<float *>(MemAlloc(v.size() * 3 * sizeof(float)));
    m.texcoords = static_cast<float *>(MemAlloc(v.size() * 2 * sizeof(float)));
    m.colors = static_cast<unsigned char *>(MemAlloc(v.size() * 4));
    for (size_t i = 0; i < v.size(); ++i) {
        std::memcpy(m.vertices + i * 3, &v[i].p, sizeof(Vector3));
        std::memcpy(m.normals + i * 3, &v[i].n, sizeof(Vector3));
        std::memcpy(m.texcoords + i * 2, &v[i].uv, sizeof(Vector2));
        std::memcpy(m.colors + i * 4, &v[i].c, 4);
    }
    UploadMesh(&m, false);
    return LoadModelFromMesh(m);
}
} // namespace
bool RedstoneArt::supports(const TownDocument &d) {
    return std::any_of(d.assets.begin(), d.assets.end(),
                       [](const auto &a) { return a.name == "redstone_gate_junction"; });
}
int RedstoneArt::surface(const TownAsset &a) {
    const auto &s = a.label;
    if (a.name.starts_with("redstone_road_") || a.name == "redstone_gate_junction")
        return 6;
    if (contains(s, "Ground") || contains(s, "Road") || contains(s, "DustPile"))
        return 1;
    if (contains(s, "Rock") || contains(s, "Cliff") || contains(s, "Butte"))
        return 2;
    if (contains(s, "Tent") || contains(s, "Wagon") || contains(s, "FlagPole"))
        return 4;
    if (contains(s, "Fort") || contains(s, "Crate") || contains(s, "Barrel") || contains(s, "Wood") ||
        contains(s, "Bench") || contains(s, "Table") || contains(s, "Log"))
        return 3;
    return 0;
}
void RedstoneArt::unload() {
    if (contact_.id)
        UnloadTexture(contact_);
    for (auto *model : {&dressing_, &cloth_, &dressingShadow_, &clothShadow_}) {
        if (model->meshCount)
            UnloadModel(*model);
        *model = {};
    }
    contact_ = {};
    dressing_ = {};
    cloth_ = {};
}
void RedstoneArt::build(const TownDocument &d, const Model &library) {
    unload();
    if (!supports(d))
        return;
    std::vector<Color> pixels(size_t(MapSize) * MapSize, Color{0, 0, 0, 255});
    // R: tight contact dirt, G: broader sand accumulation. Work in each object's
    // local footprint so rotated walls do not produce rectangular world-space stains.
    for (size_t i = 0; i < d.instances.size(); ++i) {
        const auto &instance = d.instances[i];
        const auto &a = d.assets[instance.asset];
        const auto b = d.bounds(i);
        if (a.unlit || instance.animated() || surface(a) == 1 || surface(a) == 6 || b.min.y > 1.0f ||
            b.max.y < -.1f || b.max.y - b.min.y < .22f || b.max.x - b.min.x > 32 || b.max.z - b.min.z > 32 ||
            contains(a.label, "Train_Track"))
            continue;
        const auto inv = MatrixInvert(instance.transform);
        const float scale = std::max(
            .01f,
            std::min(Vector3Length({instance.transform.m0, instance.transform.m1, instance.transform.m2}),
                     Vector3Length({instance.transform.m8, instance.transform.m9, instance.transform.m10})));
        const int x0 = std::clamp(int((b.min.x - 3 - MapStart) / MapSpan * MapSize), 0, MapSize - 1);
        const int x1 = std::clamp(int((b.max.x + 3 - MapStart) / MapSpan * MapSize) + 1, 0, MapSize);
        const int z0 = std::clamp(int((b.min.z - 3 - MapStart) / MapSpan * MapSize), 0, MapSize - 1);
        const int z1 = std::clamp(int((b.max.z + 3 - MapStart) / MapSpan * MapSize) + 1, 0, MapSize);
        for (int z = z0; z < z1; ++z)
            for (int x = x0; x < x1; ++x) {
                const Vector3 p{MapStart + (x + .5f) * MapSpan / MapSize, b.min.y,
                                MapStart + (z + .5f) * MapSpan / MapSize};
                const auto local = Vector3Transform(p, inv);
                const float dx = std::max({a.bounds.min.x - local.x, 0.f, local.x - a.bounds.max.x});
                const float dz = std::max({a.bounds.min.z - local.z, 0.f, local.z - a.bounds.max.z});
                const float distance = std::hypot(dx, dz) * scale;
                auto &pixel = pixels[size_t(z) * MapSize + x];
                pixel.r = std::max(pixel.r, static_cast<unsigned char>(210 * std::exp(-distance * 4.5f)));
                pixel.g = std::max(pixel.g, static_cast<unsigned char>(210 * std::exp(-distance * .95f)));
            }
    }
    Image image{pixels.data(), MapSize, MapSize, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
    contact_ = LoadTextureFromImage(image);
    GenTextureMipmaps(&contact_);
    SetTextureFilter(contact_, TEXTURE_FILTER_TRILINEAR);
    SetTextureWrap(contact_, TEXTURE_WRAP_CLAMP);
    Vertices details, cloth, shadowDetails, shadowCloth;
    std::vector<std::pair<size_t, Box>> ground;
    for (size_t i = 0; i < d.instances.size(); ++i) {
        const auto &asset = d.assets[d.instances[i].asset];
        if (surface(asset) == 1 || surface(asset) == 6)
            ground.emplace_back(i, d.bounds(i));
    }
    const auto groundHeight = [&](Vector3 p) {
        float height = -1e9f;
        const Ray ray{{p.x, p.y + 2, p.z}, {0, -1, 0}};
        for (const auto &[index, bounds] : ground) {
            if (p.x < bounds.min.x || p.x > bounds.max.x || p.z < bounds.min.z || p.z > bounds.max.z)
                continue;
            const auto &instance = d.instances[index];
            const auto &asset = d.assets[instance.asset];
            for (int m = asset.first; m < asset.first + asset.count; ++m) {
                const auto hit = GetRayCollisionMesh(ray, library.meshes[m], instance.transform);
                if (hit.hit)
                    height = std::max(height, hit.point.y);
            }
        }
        return height > -1e8f ? height - .015f : p.y;
    };
    // Small, attached additions stay relative to existing editor placements. They
    // never create a new obstacle or alter the original prefab or its collision.
    for (const auto &instance : d.instances) {
        if (instance.animated())
            continue;
        const size_t detailStart = details.size(), clothStart = cloth.size();
        const auto &a = d.assets[instance.asset];
        const auto point = [&](Vector3 p) { return Vector3Transform(p, instance.transform); };
        if (instance.id.starts_with("story-repair-table:") ||
            instance.id.starts_with("story-market-table:")) {
            // A patched shade sail tied over the work/trading table, all supports
            // beside its footprint. The outer edge flutters; its ties stay pinned.
            const auto b = a.bounds;
            const float y = b.max.y + 1.55f;
            const float x0 = b.min.x - .35f, x1 = b.max.x + .35f, z0 = b.min.z - .35f, z1 = b.max.z + .35f;
            for (float x : {x0, x1})
                for (float z : {z0, z1})
                    beam(details, point({x, b.min.y, z}), point({x, y + .06f, z}), .032f, {88, 77, 58, 255});
            const int segments = 8;
            for (int x = 0; x < segments; ++x)
                for (int z = 0; z < segments; ++z) {
                    auto p = [&](int xx, int zz) {
                        const float u = float(xx) / segments, v = float(zz) / segments;
                        return point({Lerp(x0, x1, u), y - .15f * std::sin(u * Pi) * std::sin(v * Pi),
                                      Lerp(z0, z1, v)});
                    };
                    const Color color = x < 3 && z > 4 ? Color{145, 125, 94, 255} : Color{68, 99, 100, 255};
                    const Vector2 uv0{float(x) / segments, float(z) / segments},
                        uv1{float(x + 1) / segments, float(z + 1) / segments};
                    triangle(cloth, p(x, z), p(x, z + 1), p(x + 1, z + 1), color, uv0, {uv0.x, uv1.y}, uv1);
                    triangle(cloth, p(x, z), p(x + 1, z + 1), p(x + 1, z), color, uv0, uv1, {uv1.x, uv0.y});
                }
        }
        if (surface(a) == 3 && contains(a.label, "Fort_Wall_01") && !contains(a.label, "Walkway")) {
            const auto b = a.bounds;
            // Occasional repair straps break up repeated stock palisade panels.
            if (std::abs(instance.transform.m12) > 25 || std::abs(instance.transform.m14) > 50)
                continue;
            const float z = b.max.z + .035f;
            for (float sign : {-1.f, 1.f})
                beam(details, point({b.min.x * .7f, 1.2f, z * sign}), point({b.max.x * .7f, 1.75f, z * sign}),
                     .045f, {125, 104, 74, 255});
        }
        if (instance.castsShadow) {
            shadowDetails.insert(shadowDetails.end(), details.begin() + detailStart, details.end());
            shadowCloth.insert(shadowCloth.end(), cloth.begin() + clothStart, cloth.end());
        }
    }
    // Reuse small source rocks as irregular gravel clusters beside existing scrub;
    // preserve the source mesh's facets and fit points onto the actual terrain.
    const auto rock = std::find_if(d.assets.begin(), d.assets.end(),
                                   [](const auto &a) { return a.label == "SM_Env_Rocks_04"; });
    if (rock != d.assets.end()) {
        Random rng(0xa47d1866);
        for (const auto &instance : d.instances) {
            if (!instance.id.starts_with("story-frontage-scrub-"))
                continue;
            const size_t detailStart = details.size();
            for (int n = 0; n < 4; ++n) {
                auto location =
                    Vector3Transform({rng.real(-.9f, .9f), -.02f, rng.real(-.7f, .7f)}, instance.transform);
                location.y = groundHeight(location);
                const float scale = rng.real(.08f, .20f);
                const auto matrix = MatrixMultiply(
                    MatrixMultiply(MatrixScale(scale, scale, scale), MatrixRotateY(rng.real(0, 6.28f))),
                    MatrixTranslate(location.x, location.y, location.z));
                for (int k = rock->first; k < rock->first + rock->count; ++k) {
                    const auto &m = library.meshes[k];
                    for (int t = 0; t < m.triangleCount; ++t) {
                        Vector3 p[3];
                        for (int j = 0; j < 3; ++j) {
                            const int index = m.indices ? m.indices[t * 3 + j] : t * 3 + j;
                            p[j] = Vector3Transform(
                                {m.vertices[index * 3], m.vertices[index * 3 + 1], m.vertices[index * 3 + 2]},
                                matrix);
                        }
                        triangle(details, p[0], p[1], p[2],
                                 n % 2 ? Color{104, 98, 84, 255} : Color{146, 127, 99, 255});
                    }
                }
            }
            if (instance.castsShadow)
                shadowDetails.insert(shadowDetails.end(), details.begin() + detailStart, details.end());
        }
    }
    dressing_ = upload(details);
    cloth_ = upload(cloth);
    dressingShadow_ = upload(shadowDetails);
    clothShadow_ = upload(shadowCloth);
}
void RedstoneArt::draw(Shader shader, Texture2D shadow, double time, bool depthOnly) const {
    const int original = 0, detail = 5, cloth = 1;
    const float clock = float(std::fmod(time, 3600.));
    SetShaderValue(shader, GetShaderLocation(shader, "artSurface"), &detail, SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "artTime"), &clock, SHADER_UNIFORM_FLOAT);
    rlDrawRenderBatchActive();
    rlDisableBackfaceCulling();
    const auto *fixed = depthOnly ? &dressingShadow_ : &dressing_;
    const auto *fabric = depthOnly ? &clothShadow_ : &cloth_;
    for (const auto *model : {fixed, fabric}) {
        const int waving = model == fabric ? cloth : original;
        SetShaderValue(shader, GetShaderLocation(shader, "artCloth"), &waving, SHADER_UNIFORM_INT);
        for (int i = 0; i < model->meshCount; ++i) {
            auto material = model->materials[model->meshMaterial[i]];
            std::array<MaterialMap, 12> maps;
            std::copy_n(material.maps, maps.size(), maps.begin());
            material.maps = maps.data();
            material.shader = shader;
            maps[MATERIAL_MAP_METALNESS].texture = shadow;
            DrawMesh(model->meshes[i], material, MatrixIdentity());
        }
    }
    SetShaderValue(shader, GetShaderLocation(shader, "artCloth"), &original, SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "artSurface"), &original, SHADER_UNIFORM_INT);
    rlEnableBackfaceCulling();
}
std::string RedstoneArt::shaderFunctions() {
    return R"GLSL(
uniform int artEnabled;
uniform int artSurface;
uniform sampler2D artContact;
float artHash(vec2 p) {
    vec3 q=fract(vec3(p.xyx)*.1031);
    q+=dot(q,q.yzx+33.33);
    return fract((q.x+q.y)*q.z);
}
float artNoise(vec2 p) {
    vec2 i=floor(p),f=fract(p); f=f*f*(3.-2.*f);
    return mix(mix(artHash(i),artHash(i+vec2(1,0)),f.x),
               mix(artHash(i+vec2(0,1)),artHash(i+vec2(1,1)),f.x),f.y);
}
vec3 artFinish(vec3 c,vec3 p,vec3 n) {
    if (artEnabled==0) return c;
    float value=dot(c,vec3(.26,.60,.14));
    float broad=.55*artNoise(p.xz*.12)+.45*artNoise(p.xz*.57+artNoise(p.xz*.23));
    float fine=artNoise(p.xz*6.7);
    if (artSurface==1 || artSurface==6) {
        // Bone sand / umber silt, with the original facets and worn-road values.
        float facet=clamp(value/.63,.68,1.22);
        vec3 earth=mix(vec3(.52,.435,.33),vec3(.68,.595,.465),smoothstep(.1,.9,broad));
        c=earth*facet*(.96+.08*fine);
        if (artSurface==6) c*=.84; // Preserve the original feathered road and baked wheel-rut shapes.
        vec3 contact=texture(artContact,(p.xz+128.)/256.).rgb;
        c=mix(c,vec3(.63,.565,.45)*facet,contact.g*(.20+.18*artNoise(p.xz*1.7)));
        c*=1.-contact.r*.24;
        // Small, scattered grit; derivative filtering keeps it stable at far zoom.
        vec2 grit=p.xz*8.;
        float aa=max(fwidth(grit.x),fwidth(grit.y));
        float fleck=(1.-smoothstep(.12,.26,length(fract(grit)-.5)))*step(.96,artHash(floor(grit)));
        c*=1.-fleck*.12*(1.-smoothstep(.35,1.3,aa))*(.4+.6*broad);
        // Worn boot impressions on short approach trails, not all over the map.
        float gate=1.-smoothstep(3.,4.7,abs(p.x+.6));
        gate*=smoothstep(-17.,-14.,p.z)*(1.-smoothstep(-2.,0.,p.z));
        float stepIndex=floor(p.z/.67);
        vec2 boot=vec2(p.x+.6+.22*cos(stepIndex*3.14159)+.06*sin(stepIndex*1.9),mod(p.z,.67)-.33);
        boot.x+=boot.y*.18*sin(stepIndex*2.1);
        float print=(1.-smoothstep(.85,1.15,length(boot/vec2(.09,.17))))*gate;
        c*=1.-print*.10;
    } else if (artSurface==2) {
        c=mix(c,vec3(value)*vec3(1.08,.94,.81),.35);
        c*=.89+.17*broad;
        c=mix(c,vec3(.64,.56,.43),smoothstep(.45,.95,n.y)*.16);
    } else {
        c=mix(vec3(value),c,.64);
        if (artSurface==3) {
            c=mix(c,vec3(value)*vec3(.94,1.0,.98),.60);
            // Fine vertical fibers and irregular bleaching, never glossy noise.
            float grain=artNoise(vec2((p.x+p.z)*17.,p.y*.55));
            c*=.91+.16*grain;
        }
        if (artSurface==4) {
            float pale=smoothstep(.40,.70,value)*(1.-smoothstep(.13,.28,max(c.r,max(c.g,c.b))-min(c.r,min(c.g,c.b))));
            vec3 canvas=mix(vec3(.43,.47,.42),vec3(.57,.59,.48),paletteVariation);
            c=mix(c,canvas*(.85+.2*broad),pale*.68);
        }
        // Settled dust is strongest at feet and ledges, leaving face/hat colors.
        float foot=exp(-max(p.y+.2,0.)*1.6)*.19;
        float ledge=smoothstep(.35,.98,n.y)*.07;
        c=mix(c,vec3(.61,.54,.43),(foot+ledge)*(.6+.6*fine));
    }
    return c;
}
)GLSL";
}
} // namespace dw
