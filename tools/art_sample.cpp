// Isolated visual experiment. Does not create Game, load a save, or write a map.
#include "render/MissionLighting.hpp"
#include "render/PlayerModel.hpp"
#include "render/PostProcess.hpp"
#include "platform/Assets.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <array>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <set>
#include <stdexcept>

using namespace dw;
namespace {
constexpr std::array<const char *, 4> Slugs{"original", "shapes", "paint", "combined"};
constexpr std::array<const char *, 4> Labels{"1  ORIGINAL", "2  SILHOUETTES", "3  PAINTED", "4  COMBINED"};
constexpr std::array<const char *, 4> Notes{
    "Current game meshes and textures. Same arrangement, camera and sunlight.",
    "Reshaped hat, shoulder wrap, sagged canvas, uneven fence and repair timber.",
    "Original shapes with local painted canvas, indigo, timber and leather materials.",
    "Custom silhouettes and painted materials together. No additional screen filter."};

void require(bool value, const char *message) {
    if (!value) throw std::runtime_error(message);
}

struct Props {
    Model model{};
    ~Props() {
        std::set<unsigned int> textures;
        for (int i = 0; i < model.materialCount; ++i)
            for (int j = 0; j <= MATERIAL_MAP_BRDF; ++j) {
                const auto texture = model.materials[i].maps[j].texture;
                if (texture.id && texture.id != rlGetTextureIdDefault() && textures.insert(texture.id).second)
                    UnloadTexture(texture);
            }
        if (model.meshCount) UnloadModel(model);
    }
    void load(const std::filesystem::path &path) {
        require(std::filesystem::is_regular_file(path), "Missing sample model: run scripts/create_art_sample.py");
        model = LoadModel(path.string().c_str());
        require(model.meshCount > 0, "Cannot load sample model");
        for (int i = 0; i < model.materialCount; ++i) {
            const auto texture = model.materials[i].maps[MATERIAL_MAP_ALBEDO].texture;
            if (texture.id && texture.id != rlGetTextureIdDefault()) {
                GenTextureMipmaps(&model.materials[i].maps[MATERIAL_MAP_ALBEDO].texture);
                SetTextureFilter(model.materials[i].maps[MATERIAL_MAP_ALBEDO].texture, TEXTURE_FILTER_TRILINEAR);
            }
        }
    }
    void draw(Shader shader, const MissionLighting *lighting = nullptr) const {
        rlDisableBackfaceCulling();
        for (int i = 0; i < model.meshCount; ++i) {
            auto material = model.materials[model.meshMaterial[i]];
            material.shader = shader;
            if (lighting) lighting->draw(model.meshes[i], material, model.transform);
            else DrawMesh(model.meshes[i], material, model.transform);
        }
        rlEnableBackfaceCulling();
    }
};

class Study {
  public:
    std::array<Props, 4> props;
    std::array<PlayerModel, 4> hero;
    MissionLighting lighting;
    PostProcess post;
    Player player;
    Model ground{};
    Font font{};
    int mode = 3, previous = -1;
    float yaw = .48f, pitch = .47f, radius = 15.f;
    Vector3 target{0, 1.0f, .4f};

    Study() {
        const auto assets = sourceAssetDirectory();
        const auto sample = assets / "art_sample";
        for (int i = 0; i < 4; ++i) {
            props[i].load(sample / (std::string("stage-") + Slugs[i] + ".glb"));
            require(hero[i].load(i == 0 ? assets / "bandit/bandit.glb" :
                                 sample / (std::string("hero-") + Slugs[i] + ".glb")),
                    "Cannot load sample character with all original animations");
        }
        ground = LoadModelFromMesh(GenMeshPlane(200, 200, 1, 1));
        ground.materials[0].maps[MATERIAL_MAP_ALBEDO].color = {184, 159, 116, 255};
        font = LoadFontEx((assets / "ui/body.ttf").string().c_str(), 48, nullptr, 0);
        player.position = {-.7f, .85f, 1.85f};
        player.facing = {.3f, 0, 1};
        player.aim = Vector3Add(player.position, player.facing);
        pose(.7, false);
    }
    ~Study() {
        UnloadModel(ground);
        UnloadFont(font);
    }
    void pose(double time, bool walking) {
        player.velocity = walking ? Vector3{0, 0, 2} : Vector3{};
        for (auto &model : hero) model.update(player, time, this);
    }
    Camera3D camera() const {
        const auto offset = Vector3{std::sin(yaw) * std::cos(pitch) * radius,
                                   std::sin(pitch) * radius,
                                   std::cos(yaw) * std::cos(pitch) * radius};
        return {Vector3Add(target, offset), target, {0,1,0}, 39, CAMERA_PERSPECTIVE};
    }
    void focus(int view) {
        yaw = .48f; pitch = .47f; radius = 15; target = {0,1,.4f};
        if (view == 1) { radius = 5.3f; pitch = .31f; target = {-.7f,1.15f,1.85f}; }
        if (view == 2) { radius = 8.8f; yaw = -.55f; pitch = .35f; target = {-2.2f,1.3f,.6f}; }
        lighting.invalidate();
    }
    void world() {
        const auto cam = camera();
        if (mode != previous) { lighting.invalidate(); previous = mode; }
        lighting.prepare(cam, [&](Shader, Shader depth) { props[mode].draw(depth); },
                         [&](Shader depth, Shader) { hero[mode].draw(player, false, depth); });
        require(lighting.ready(), "Sample shared lighting failed to compile");
        post.begin({154,186,199,255}, radius, false, VisualStyle::Original);
        BeginMode3D(cam);
        auto material = ground.materials[0]; material.shader = lighting.actorShader();
        lighting.draw(ground.meshes[0], material, ground.transform);
        props[mode].draw(lighting.actorShader(), &lighting);
        rlDisableBackfaceCulling();
        hero[mode].draw(player, false, lighting.actorShader(), lighting.texture());
        rlEnableBackfaceCulling();
        EndMode3D();
        post.end();
    }
    void text(const char *value, float x, float y, float size, Color color) {
        DrawTextEx(font, value, {x,y}, size, .5f, color);
    }
    Rectangle button(int i) const {
        const float width = std::min(228.f, (GetScreenWidth() - 56.f) / 4);
        return {28 + i * width, GetScreenHeight() - 116.f, width - 8, 42};
    }
    void ui(bool animate, bool walking) {
        const Color paper{233,223,202,255}, muted{173,184,179,255}, panel{26,33,35,242};
        DrawRectangle(0,0,GetScreenWidth(),100,panel);
        text("DEATHWARD  /  THE WAYSTATION",28,18,27,paper);
        text("ISOLATED ASSET STUDY   /   NORMAL GAME, MAPS AND SAVES UNCHANGED",28,59,17,muted);
        DrawRectangle(0,GetScreenHeight()-136,GetScreenWidth(),136,panel);
        for (int i=0;i<4;++i) {
            auto r=button(i);
            DrawRectangleRec(r,i==mode ? Color{175,113,66,255} : Color{46,57,59,255});
            text(Labels[i],r.x+12,r.y+12,18,paper);
        }
        text(Notes[mode],28,GetScreenHeight()-63.f,18,paper);
        text("Drag: orbit   Wheel: zoom   Tab: before/after   H: hero   R: reset   Space: animate   W: walk   Esc: close",
             28,GetScreenHeight()-31.f,15,muted);
        text(animate ? (walking ? "WALKING" : "IDLE ANIMATION") : "POSE FROZEN",GetScreenWidth()-200.f,26,17,muted);
    }
    Image capture() {
        BeginDrawing(); world(); rlDrawRenderBatchActive();
        auto image = LoadImageFromScreen(); EndDrawing();
        return image;
    }
};

bool same(Image a, Image b) {
    return a.width==b.width && a.height==b.height && a.format==b.format &&
           std::memcmp(a.data,b.data,GetPixelDataSize(a.width,a.height,a.format))==0;
}

void captureAll(Study &study) {
    const auto out = std::filesystem::path("artifacts/art-sample");
    std::filesystem::create_directories(out);
    for (int view=0;view<3;++view) {
        study.focus(view);
        study.mode=0;
        auto baseline=study.capture();
        std::array<Image,4> images{baseline};
        for (int mode=0;mode<4;++mode) {
            study.mode=mode;
            if (mode) images[mode]=study.capture();
            require(ExportImage(images[mode],(out/(std::string(Slugs[mode])+"-"+std::to_string(view)+".png")).string().c_str()),
                    "Cannot save comparison image");
            if (mode) require(!same(baseline,images[mode]),"Variant must change rendered pixels");
        }
        study.mode=0;
        auto restored=study.capture();
        ExportImage(restored,(out/("restored-"+std::to_string(view)+".png")).string().c_str());
        require(same(baseline,restored),"Returning to original must restore identical pixels");
        UnloadImage(restored);
        for (auto image:images) UnloadImage(image);
    }
    // Exercise retained rig with both idle and walk in the new clothing.
    study.mode=3; study.focus(1); study.pose(1.5,true);
    auto walk=study.capture();
    require(study.hero[3].animation()==PlayerAnimation::Walk,"Custom clothing retains walking animation");
    ExportImage(walk,(out/"combined-walk.png").string().c_str()); UnloadImage(walk);
    std::cout<<"PASS: four asset modes, three views, all nine character clips load, walking animates, original pixels restore exactly\n";
}
} // namespace

int main(int argc, char **argv) {
    bool capture=false;
    for(int i=1;i<argc;++i) {
        if(std::strcmp(argv[i],"--capture")==0) capture=true;
        else { std::cerr<<"Unknown option: "<<argv[i]<<"\n"; return 2; }
    }
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(1600,1000,"DeathWard | Reversible art-direction sample");
    SetWindowMinSize(1000,700); SetTargetFPS(60);
    try {
        {
            Study study;
            if(capture) captureAll(study);
            else {
                bool animate=false,walking=false;
                double time=.7;
                int lastCustom=3;
                while(!WindowShouldClose()) {
                    for(int i=0;i<4;++i)
                        if(IsKeyPressed(KEY_ONE+i) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                            CheckCollisionPointRec(GetMousePosition(),study.button(i)))) study.mode=i;
                    if(IsKeyPressed(KEY_TAB)) {
                        if(study.mode) { lastCustom=study.mode; study.mode=0; }
                        else study.mode=lastCustom;
                    }
                    if(IsKeyPressed(KEY_H)) study.focus(1);
                    if(IsKeyPressed(KEY_R)) study.focus(0);
                    if(IsKeyPressed(KEY_SPACE)) animate=!animate;
                    if(IsKeyPressed(KEY_W)) { walking=!walking; animate=true; }
                    if((IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) &&
                       GetMouseY()>100 && GetMouseY()<GetScreenHeight()-136) {
                        const auto delta=GetMouseDelta();
                        study.yaw-=delta.x*.006f;
                        study.pitch=Clamp(study.pitch+delta.y*.006f,.08f,1.25f);
                    }
                    study.radius=Clamp(study.radius*std::pow(.9f,GetMouseWheelMove()),2.5f,30.f);
                    if(animate) time+=GetFrameTime();
                    study.pose(time,walking);
                    BeginDrawing(); study.world(); study.ui(animate,walking); EndDrawing();
                }
            }
        }
        CloseWindow(); return 0;
    } catch(const std::exception &error) {
        std::cerr<<"Art sample: "<<error.what()<<"\n"; CloseWindow(); return 1;
    }
}
