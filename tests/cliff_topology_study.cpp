// Isolated visual acceptance scene; uses the shared wall-only topology implementation.
#include "combat/Simulation.hpp"
#include "raymath.h"
#include "render/GroundSurface.hpp"
#include "render/MissionLighting.hpp"
#include "rlgl.h"
#include "world/CanyonAppearance.hpp"
#include "world/CliffWallTopology.hpp"
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <stdexcept>
using namespace dw;
namespace {
void require(bool value, const char *what) {
    if (!value)
        throw std::runtime_error(what);
}
using namespace dw::cliffDetail;
std::vector<Quad> selectPatch(const CanyonAppearance &plain) {
    std::vector<Quad> quads;
    for (size_t i = 0; i + 1 < plain.triangles.size(); ++i) {
        auto a = plain.triangles[i], b = plain.triangles[i + 1];
        if (!a.rock || !b.rock || !near(a.vertices[0], b.vertices[0]) || !near(a.vertices[1], b.vertices[2]))
            continue;
        Quad q{a.vertices[0], b.vertices[1], a.vertices[1], a.vertices[2]};
        auto n = normal(q);
        if (std::abs(n.y) < .15f && q.at.y - q.ab.y > 1.5f && q.bt.y - q.bb.y > 1.5f &&
            distance(q.ab, q.bb) > .45f)
            quads.push_back(q);
    }
    std::vector<Quad> best;
    for (auto start : quads) {
        std::vector<Quad> chain{start};
        float width = distance(start.ab, start.bb);
        while (chain.size() < 7) {
            auto last = chain.back();
            auto found = std::find_if(quads.begin(), quads.end(), [&](auto q) {
                return near(last.bb, q.ab) && near(last.bt, q.at) &&
                       Vector3DotProduct(normal(start), normal(q)) > .96f;
            });
            if (found == quads.end() || width + distance(found->ab, found->bb) > 11)
                break;
            chain.push_back(*found);
            width += distance(found->ab, found->bb);
        }
        if (chain.size() > best.size())
            best = chain;
    }
    require(best.size() >= 4, "No suitable connected source wall patch");
    return best;
}
Mesh meshOf(const std::vector<std::array<Vector3, 3>> &faces) {
    Mesh m{};
    m.vertexCount = int(faces.size() * 3);
    m.triangleCount = int(faces.size());
    m.vertices = (float *)MemAlloc(m.vertexCount * 3 * sizeof(float));
    m.normals = (float *)MemAlloc(m.vertexCount * 3 * sizeof(float));
    m.texcoords = (float *)MemAlloc(m.vertexCount * 2 * sizeof(float));
    m.colors = (unsigned char *)MemAlloc(m.vertexCount * 4);
    int i = 0;
    for (auto t : faces) {
        auto n = Vector3Normalize(Vector3CrossProduct(sub(t[1], t[0]), sub(t[2], t[0])));
        for (auto v : t) {
            m.vertices[i * 3] = v.x;
            m.vertices[i * 3 + 1] = v.y;
            m.vertices[i * 3 + 2] = v.z;
            m.normals[i * 3] = n.x;
            m.normals[i * 3 + 1] = n.y;
            m.normals[i * 3 + 2] = n.z;
            m.texcoords[i * 2] = m.texcoords[i * 2 + 1] = 0;
            for (int k = 0; k < 4; ++k)
                m.colors[i * 4 + k] = 255;
            ++i;
        }
    }
    UploadMesh(&m, false);
    return m;
}
} // namespace
int main(int argc, char **argv) {
    try {
        std::filesystem::path output = argc > 1 ? argv[1] : "docs/reports/cliff-topology";
        std::filesystem::create_directories(output);
        Simulation sim(1866, 1, {}, MissionTheme::Canyon, true);
        int floor = 0;
        while (sim.expedition.profileOnFloor(floor).band < 2)
            ++floor;
        Simulation run(1866, 1, {}, MissionTheme::Canyon, true, false, WitnessAccount::None, floor);
        run.jumpDebug(2);
        CanyonVisualParameters p;
        p.debris = p.floorVegetation = p.baseVegetation = p.terraceVegetation = p.plateauVegetation = 0;
        p.irregularFacets = false;
        auto plain = buildCanyonAppearance(run.arena, p);
        auto patch = selectPatch(plain);
        auto study = build(patch);
        std::cout << "PATCH segments=" << patch.size() << " triangles=" << study.triangles.size()
                  << " broad=" << study.broad << " max_abs_normal_y=" << study.maxTilt
                  << "\nPASS boundary, coverage, manifold, aspect and steepness checks\n";
        auto repeat = build(patch);
        require(study.triangles.size() == repeat.triangles.size() &&
                    study.vertices.size() == repeat.vertices.size(),
                "Nondeterministic mesh");
        for (size_t i = 0; i < study.vertices.size(); ++i)
            require(near(study.vertices[i], repeat.vertices[i]), "Nondeterministic vertices");
        // Frozen 6d13c1a baseline, so future runs keep an honest before image.
        auto hash = [](int x, int z, uint64_t seed) {
            uint64_t v = seed ^ uint64_t(int64_t(x)) * 0x9e3779b97f4a7c15ULL ^
                         uint64_t(int64_t(z)) * 0xbf58476d1ce4e5b9ULL;
            v = (v ^ (v >> 30)) * 0xbf58476d1ce4e5b9ULL;
            v = (v ^ (v >> 27)) * 0x94d049bb133111ebULL;
            return float((v ^ (v >> 31)) >> 40) / 16777215.f;
        };
        auto noise = [&](float x, float z, uint64_t seed) {
            int ix = int(std::floor(x)), iz = int(std::floor(z));
            float u = x - ix, v = z - iz;
            u = u * u * (3 - 2 * u);
            v = v * v * (3 - 2 * v);
            return std::lerp(std::lerp(hash(ix, iz, seed), hash(ix + 1, iz, seed), u),
                             std::lerp(hash(ix, iz + 1, seed), hash(ix + 1, iz + 1, seed), u), v);
        };
        std::vector<std::array<Vector3, 3>> before, after;
        for (auto q : patch) {
            auto mid = mul(add(q.at, q.bt), .5f);
            int x = int(std::floor(mid.x * 1.7f)), z = int(std::floor(mid.z * 1.7f));
            float u = .28f + .44f * hash(x, z, plain.seed ^ 0x4641434554ULL),
                  v = .28f + .44f * hash(x, z, plain.seed ^ 0x484549474854ULL);
            auto lo = Vector3Lerp(q.ab, q.bb, u), hi = Vector3Lerp(q.at, q.bt, u),
                 center = Vector3Lerp(lo, hi, v);
            float rise = std::min(q.at.y - q.ab.y, q.bt.y - q.bb.y), width = distance(q.at, q.bt);
            float relief = std::min(width, rise) *
                           (.08f + .12f * noise(mid.x / 2.5f, mid.z / 2.5f, plain.seed ^ 0x524f434bULL));
            relief = std::min(relief, rise * std::min(v, 1 - v) * .28f);
            auto n = normal(q);
            center = add(center, mul(Vector3Normalize({-n.x, 0, -n.z}), relief));
            before.insert(
                before.end(),
                {{q.ab, q.bb, center}, {q.bb, q.bt, center}, {q.bt, q.at, center}, {q.at, q.ab, center}});
        }
        for (auto t : study.triangles)
            after.push_back({study.vertices[t.a], study.vertices[t.b], study.vertices[t.c]});
        SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIDDEN);
        InitWindow(1440, 900, "Isolated cliff topology");
        // Load the production terrain shader verbatim. No new palette or lighting code.
        std::ifstream file(std::filesystem::path(DEATHWARD_SOURCE_DIR) / "src/render/CanyonScene.cpp");
        std::string code((std::istreambuf_iterator<char>(file)), {});
        auto extract = [&](const char *name) {
            size_t start = code.find("R\"GLSL(", code.find(name)) + 7;
            return code.substr(start, code.find(")GLSL\"", start) - start);
        };
        auto vertex = extract("TerrainVertex"), fragment = extract("TerrainFragment");
        fragment = MissionLighting::withShadows(GroundSurface::withDetail(fragment.c_str()).c_str());
        // Occlusion is disabled in this isolated wall test; the production surface body is unchanged.
        auto at = fragment.find("void main()");
        fragment.insert(at, "vec4 playerOcclusionSurface(vec3 p,vec4 c){return c;}\n");
        auto shader = LoadShaderFromMemory(vertex.c_str(), fragment.c_str());
        require(shader.id != rlGetShaderIdDefault(), "Production shader compile failed");
        int enabled = 1, underlay = 0;
        SetShaderValue(shader, GetShaderLocation(shader, "terracedCliffs"), &enabled, SHADER_UNIFORM_INT);
        SetShaderValue(shader, GetShaderLocation(shader, "terrainUnderlay"), &underlay, SHADER_UNIFORM_INT);
        auto material = LoadMaterialDefault();
        material.shader = shader;
        MissionLighting light;
        auto n = normal(patch.front());
        auto mid = Vector3Lerp(patch.front().ab, patch.back().bt, .5f);
        float span = std::max(study.width, study.height * 2);
        Camera3D camera{add(add(mid, mul(n, span * 1.25f)), {span * .18f, span * .35f, 0}),
                        mid,
                        {0, 1, 0},
                        40,
                        CAMERA_PERSPECTIVE};
        auto oldMesh = meshOf(before), newMesh = meshOf(after);
        for (int view = 0; view < 3; ++view) {
            auto mesh = view == 0 ? oldMesh : newMesh;
            light.invalidate();
            light.prepare(camera, [&](Shader, Shader) { light.draw(mesh, material, MatrixIdentity()); });
            for (int frame = 0; frame < 3; ++frame) {
                BeginDrawing();
                ClearBackground({40, 42, 44, 255});
                BeginMode3D(camera);
                light.bind(shader);
                DrawMesh(mesh, material, MatrixIdentity());
                if (view == 2) {
                    for (auto t : after) {
                        auto edge = [&](Vector3 a, Vector3 b) {
                            auto off = mul(n, .004f);
                            DrawLine3D(add(a, off), add(b, off), {25, 22, 20, 255});
                        };
                        edge(t[0], t[1]);
                        edge(t[1], t[2]);
                        edge(t[2], t[0]);
                    }
                }
                EndMode3D();
                EndDrawing();
            }
            auto image = LoadImageFromScreen();
            auto name = view == 0 ? "before.png" : view == 1 ? "after.png" : "wireframe.png";
            ExportImage(image, (output / name).c_str());
            UnloadImage(image);
        }
        UnloadMesh(oldMesh);
        UnloadMesh(newMesh);
        material.shader = {};
        UnloadMaterial(material);
        UnloadShader(shader);
        light.unload();
        CloseWindow();
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << "\n";
        return 1;
    }
}
