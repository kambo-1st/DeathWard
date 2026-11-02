#include "combat/Simulation.hpp"
#include "raylib.h"
#include "raymath.h"
#include "world/CanyonAppearance.hpp"
#include <chrono>
#include <iostream>
// Standalone diagnostic. It does not change game rendering, lighting or materials.
int main(int argc, char **argv) {
    if (argc < 2)
        return 2;
    dw::Simulation initial(1866, 1, {}, dw::MissionTheme::Canyon, true);
    int floor = 0;
    while (initial.expedition.profileOnFloor(floor).band < 2)
        ++floor;
    dw::Simulation run(1866, 1, {}, dw::MissionTheme::Canyon, true, false, dw::WitnessAccount::None, floor);
    run.jumpDebug(2);
    auto p = dw::CanyonVisualParameters::load(argc > 2 ? std::filesystem::path(argv[2])
                                                       : std::filesystem::path(DEATHWARD_ASSET_DIR) /
                                                             "visual/canyon.cfg");
    p.debris = p.floorVegetation = p.baseVegetation = p.terraceVegetation = p.plateauVegetation = 0;
    const auto begin = std::chrono::steady_clock::now();
    auto appearance = dw::buildCanyonAppearance(run.arena, p);
    const double meshMs =
        std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - begin).count();
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIDDEN);
    InitWindow(1440, 900, "DeathWard boundary geometry diagnostic");
    auto shader = LoadShaderFromMemory(R"(#version 330
in vec3 vertexPosition;in vec3 vertexNormal;uniform mat4 mvp;out vec3 normal;
void main(){normal=vertexNormal;gl_Position=mvp*vec4(vertexPosition,1.);})",
                                       R"(#version 330
in vec3 normal;out vec4 finalColor;void main(){float light=.45+.55*max(dot(normalize(normal),normalize(vec3(.5,.8,.35))),0.);finalColor=vec4(vec3(.7,.7,.7)*light,1.);})");
    Mesh mesh{};
    mesh.vertexCount = int(appearance.triangles.size() * 3);
    mesh.triangleCount = mesh.vertexCount / 3;
    mesh.vertices = (float *)MemAlloc(unsigned(mesh.vertexCount * 3 * sizeof(float)));
    mesh.normals = (float *)MemAlloc(unsigned(mesh.vertexCount * 3 * sizeof(float)));
    int index = 0;
    for (const auto &t : appearance.triangles) {
        auto n = Vector3Normalize(Vector3CrossProduct(dw::sub(t.vertices[1], t.vertices[0]),
                                                      dw::sub(t.vertices[2], t.vertices[0])));
        for (auto v : t.vertices) {
            mesh.vertices[index] = v.x;
            mesh.vertices[index + 1] = v.y;
            mesh.vertices[index + 2] = v.z;
            mesh.normals[index] = n.x;
            mesh.normals[index + 1] = n.y;
            mesh.normals[index + 2] = n.z;
            index += 3;
        }
    }
    UploadMesh(&mesh, false);
    auto material = LoadMaterialDefault();
    material.shader = shader;
    auto hero = run.player.position;
    auto focus = dw::sub(hero, {1.25f, .85f, 1.25f});
    Camera3D camera{dw::add(focus, {14.375f, 18.75f, 14.375f}), focus, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
    if (argc > 3 && std::string_view(argv[3]) == "detail") {
        auto original = p;
        original.irregularFacets = false;
        const auto control = dw::buildCanyonAppearance(run.arena, original);
        float best = 1e9f;
        for (const auto &face : control.triangles) {
            if (!face.rock)
                continue;
            auto a = face.vertices[0], b = face.vertices[1], c = face.vertices[2];
            auto normal = Vector3Normalize(Vector3CrossProduct(dw::sub(b, a), dw::sub(c, a)));
            auto center = dw::mul(dw::add(dw::add(a, b), c), 1.f / 3);
            if (std::abs(normal.y) > .35f || normal.x + normal.z < .6f || center.y < .5f ||
                run.arena.canyon->height(center.x, center.z, true) < .1f)
                continue;
            float d = std::hypot(center.x - hero.x, center.z - hero.z);
            if (d < best) {
                best = d;
                focus = center;
            }
        }
        camera.target = focus;
        camera.position = dw::add(focus, {4.5f, 3.f, 4.5f});
    }
    for (int frame = 0; frame < 3; ++frame) {
        BeginDrawing();
        ClearBackground({35, 39, 42, 255});
        BeginMode3D(camera);
        DrawMesh(mesh, material, MatrixIdentity());
        DrawCylinder({hero.x, 0, hero.z}, .24f, .24f, 1.8f, 6, {160, 87, 55, 255});
        EndMode3D();
        EndDrawing();
    }
    auto image = LoadImageFromScreen();
    ExportImage(image, argv[1]);
    UnloadImage(image);
    std::cout << "GEOMETRY_CAPTURE zoom=160 fov=45 seed=1866 triangles=" << appearance.triangles.size()
              << " floor=" << floor << " hero_height=1.8 appearance_ms=" << meshMs << "\n";
    UnloadMesh(mesh);
    material.shader = {};
    UnloadMaterial(material);
    UnloadShader(shader);
    CloseWindow();
}
