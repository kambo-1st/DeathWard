// Read-only asset inspection tool. It never creates Game or loads a save.
#include "AssetInventory.hpp"
#include "FbxPreview.hpp"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

using namespace dw::assetBrowser;
namespace {
constexpr Color Bg{15, 19, 25, 255}, Panel{23, 29, 37, 255}, Edge{44, 54, 65, 255}, Muted{142, 157, 170, 255},
    Ink{226, 233, 235, 255}, Accent{231, 169, 91, 255}, Select{43, 63, 75, 255};
constexpr int FontSize = 18;
std::string bytes(uintmax_t n) {
    std::ostringstream s;
    if (n < 1024)
        s << n << " B";
    else if (n < 1024 * 1024)
        s << std::fixed << std::setprecision(1) << double(n) / 1024 << " KB";
    else
        s << std::fixed << std::setprecision(1) << double(n) / (1024 * 1024) << " MB";
    return s.str();
}
std::string clipped(const std::string &s, int width, int size = FontSize) {
    if (MeasureText(s.c_str(), size) <= width)
        return s;
    std::string result = s;
    while (!result.empty() && MeasureText((result + "...").c_str(), size) > width)
        result.pop_back();
    return result + "...";
}
void label(std::string s, int x, int y, int size = FontSize, Color color = Ink) {
    DrawText(s.c_str(), x, y, size, color);
}
bool button(Rectangle r, const char *name, bool active = false) {
    const bool hover = CheckCollisionPointRec(GetMousePosition(), r);
    DrawRectangleRec(r, active ? Select : (hover ? Color{49, 59, 67, 255} : Panel));
    DrawRectangleLinesEx(r, 1, active ? Accent : Edge);
    const int size = 16;
    label(name, int(r.x + (r.width - MeasureText(name, size)) * .5f), int(r.y + 9), size,
          active ? Accent : Ink);
    return hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}
std::vector<std::string> readLines(const Asset &a, bool &binary, bool &truncated) {
    constexpr size_t Limit = 2 * 1024 * 1024;
    std::ifstream in(a.absolute, std::ios::binary);
    if (!in)
        return {"Unable to read this file."};
    std::string data(std::min<uintmax_t>(a.bytes, Limit), '\0');
    in.read(data.data(), data.size());
    data.resize(size_t(in.gcount()));
    truncated = a.bytes > data.size();
    binary = false;
    for (size_t i = 0; i < std::min<size_t>(data.size(), 4096); ++i)
        if (static_cast<unsigned char>(data[i]) < 9 ||
            (static_cast<unsigned char>(data[i]) > 13 && static_cast<unsigned char>(data[i]) < 32)) {
            binary = true;
            break;
        }
    std::vector<std::string> lines;
    if (binary) {
        for (size_t start = 0; start < std::min<size_t>(data.size(), 4096); start += 16) {
            std::ostringstream line;
            line << std::hex << std::setfill('0') << std::setw(8) << start << "  ";
            for (size_t i = 0; i < 16; ++i) {
                if (start + i < data.size())
                    line << std::setw(2) << unsigned(static_cast<unsigned char>(data[start + i])) << ' ';
                else
                    line << "   ";
            }
            line << "  ";
            for (size_t i = start; i < std::min(data.size(), start + 16); ++i) {
                unsigned char c = data[i];
                line << (c >= 32 && c < 127 ? char(c) : '.');
            }
            lines.push_back(line.str());
        }
        truncated = a.bytes > 4096;
    } else {
        std::istringstream stream(data);
        std::string line;
        while (std::getline(stream, line)) {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();
            std::string expanded;
            for (char c : line)
                expanded += c == '\t' ? "    " : std::string(1, c);
            lines.push_back(std::move(expanded));
        }
    }
    if (lines.empty())
        lines.push_back("(empty file)");
    return lines;
}
void screenshot(const fs::path &path) {
    if (!path.parent_path().empty())
        fs::create_directories(path.parent_path());
    Image image = LoadImageFromScreen();
    const bool saved = ExportImage(image, path.string().c_str());
    UnloadImage(image);
    if (!saved)
        throw std::runtime_error("Cannot save screenshot: " + path.string());
}
const char *VertexShader = R"(#version 330
in vec3 vertexPosition; in vec2 vertexTexCoord; in vec3 vertexNormal; in vec4 vertexColor;
uniform mat4 mvp; uniform mat4 matNormal;
out vec2 fragTexCoord; out vec4 fragColor; out vec3 fragNormal;
void main(){fragTexCoord=vertexTexCoord;fragColor=vertexColor;fragNormal=normalize((matNormal*vec4(vertexNormal,0)).xyz);gl_Position=mvp*vec4(vertexPosition,1);})";
const char *FragmentShader = R"(#version 330
in vec2 fragTexCoord; in vec4 fragColor; in vec3 fragNormal;
uniform sampler2D texture0; uniform vec4 colDiffuse; out vec4 finalColor;
void main(){vec4 c=texture(texture0,fragTexCoord)*colDiffuse*fragColor;if(c.a<0.025)discard;vec3 n=gl_FrontFacing?fragNormal:-fragNormal;float l=0.33+0.67*max(dot(normalize(n),normalize(vec3(0.4,0.85,0.5))),0);finalColor=vec4(c.rgb*l,c.a);})";

struct Preview {
    Texture2D image{};
    Font font{};
    Model model{};
    ModelAnimation *animations = nullptr;
    int animationCount = 0;
    FbxPreview fbx;
    Music music{};
    Wave wave{};
    std::vector<std::string> lines;
    std::vector<float> waveform;
    std::string description, error;
    Kind kind = Kind::Other;
    bool ready = false, isFbx = false, binary = false, truncated = false, playing = false, animate = true;
    size_t clip = 0;
    int section = -1;
    double animationTime = 0;
    float yaw = .7f, pitch = .25f, radius = 4, modelSize = 3, imageZoom = 1;
    Vector3 target{};
    Vector2 imagePan{};
    int textScroll = 0, textColumn = 0;
    void clear() {
        if (IsMusicValid(music)) {
            StopMusicStream(music);
            UnloadMusicStream(music);
        }
        music = {};
        if (IsWaveValid(wave))
            UnloadWave(wave);
        wave = {};
        waveform.clear();
        if (image.id)
            UnloadTexture(image);
        image = {};
        if (font.texture.id)
            UnloadFont(font);
        font = {};
        if (animations)
            UnloadModelAnimations(animations, animationCount);
        animations = nullptr;
        animationCount = 0;
        if (model.meshCount) {
            std::set<unsigned> textureIds;
            for (int i = 0; i < model.materialCount; ++i)
                for (int k = 0; k <= MATERIAL_MAP_BRDF; ++k) {
                    auto t = model.materials[i].maps[k].texture;
                    if (t.id && t.id != rlGetTextureIdDefault() && textureIds.insert(t.id).second)
                        UnloadTexture(t);
                }
            UnloadModel(model);
        }
        model = {};
        fbx.clear();
        lines.clear();
        description.clear();
        error.clear();
        ready = false;
        playing = false;
        animationTime = 0;
        clip = 0;
        section = -1;
        imageZoom = 1;
        imagePan = {};
        textScroll = 0;
        textColumn = 0;
    }
    ~Preview() { clear(); }
    BoundingBox modelBounds() const {
        return isFbx
                   ? fbx.sectionBounds(section)
                   : (section >= 0 ? GetMeshBoundingBox(model.meshes[section]) : GetModelBoundingBox(model));
    }
    int sections() const { return isFbx ? fbx.sections() : model.meshCount; }
    void nextSection(bool reverse = false) {
        const int n = sections();
        if (n) {
            section = (section + 1 + (reverse ? n : 1)) % (n + 1) - 1;
            fit();
        }
    }
    void fit() {
        BoundingBox b = modelBounds();
        target = Vector3Scale(Vector3Add(b.min, b.max), .5f);
        modelSize = std::max(Vector3Distance(b.min, b.max), .0001f);
        const float aspect =
            float(std::max(1, GetScreenWidth() - 670)) / std::max(1, GetScreenHeight() - 350);
        const float halfFov = std::atan(std::tan(20 * DEG2RAD) * std::min(1.f, aspect));
        radius = .5f * modelSize / std::sin(halfFov) * 1.12f;
        pitch = .22f;
        yaw = .7f;
    }
    void load(const Asset &a, const std::unordered_map<std::string, fs::path> &images) {
        clear();
        kind = a.kind;
        isFbx = false;
        if (kind == Kind::Image) {
            image = LoadTexture(a.absolute.string().c_str());
            ready = image.id > 0;
            if (ready) {
                SetTextureFilter(image, TEXTURE_FILTER_POINT);
                description = std::to_string(image.width) + " x " + std::to_string(image.height) + " pixels";
            } else
                error = "Image decoder could not load this format.";
        } else if (kind == Kind::Model) {
            isFbx = a.extension == ".fbx";
            if (isFbx) {
                ready = fbx.load(a.absolute, images);
                description = fbx.notes;
                if (!ready)
                    error = fbx.notes;
            } else {
                model = LoadModel(a.absolute.string().c_str());
                ready = model.meshCount > 0;
                if (ready) {
                    size_t triangles = 0;
                    for (int i = 0; i < model.meshCount; ++i)
                        triangles += model.meshes[i].triangleCount;
                    description = std::to_string(model.meshCount) + " meshes / " + std::to_string(triangles) +
                                  " triangles / " + std::to_string(model.materialCount) + " materials";
                    animations = LoadModelAnimations(a.absolute.string().c_str(), &animationCount);
                }
            }
            if (ready) {
                if (isFbx) {
                    // Mixamo source files also contain unrelated legacy takes.
                    // Keep every clip selectable, but start with the authored Mixamo take.
                    for (size_t i = 0; i < fbx.animations.size(); ++i)
                        if (lower(fbx.animations[i]).find("mixamo") != std::string::npos) {
                            clip = i;
                            break;
                        }
                    if (!fbx.animations.empty())
                        fbx.animate(clip, 0);
                } else {
                    for (int i = 0; i < animationCount; ++i)
                        if (lower(animations[i].name).find("idle") != std::string::npos) {
                            clip = size_t(i);
                            break;
                        }
                }
                fit();
            }
        } else if (kind == Kind::Font) {
            font = LoadFontEx(a.absolute.string().c_str(), 48, nullptr, 0);
            ready = font.texture.id != 0 && font.texture.id != GetFontDefault().texture.id;
            if (ready)
                description = std::to_string(font.glyphCount) + " loaded preview glyphs";
            else {
                font = {};
                error = "Font decoder could not load this file.";
            }
        } else if (kind == Kind::Audio) {
            wave = LoadWave(a.absolute.string().c_str());
            ready = IsWaveValid(wave);
            if (ready) {
                const double seconds = double(wave.frameCount) / wave.sampleRate;
                description =
                    TextFormat("%.2f seconds / %u Hz / %u channels", seconds, wave.sampleRate, wave.channels);
                if (a.bytes < 32 * 1024 * 1024) {
                    float *samples = LoadWaveSamples(wave);
                    if (samples) {
                        const size_t count = std::min<size_t>(1200, wave.frameCount);
                        waveform.resize(count);
                        for (size_t i = 0; i < count; ++i) {
                            const size_t begin = i * wave.frameCount / count,
                                         end = (i + 1) * wave.frameCount / count;
                            float peak = 0;
                            for (size_t j = begin; j < end; ++j)
                                for (size_t c = 0; c < wave.channels; ++c)
                                    peak = std::max(peak, std::abs(samples[j * wave.channels + c]));
                            waveform[i] = peak;
                        }
                        UnloadWaveSamples(samples);
                    }
                }
            } else {
                ready = true;
                description = "Streamed audio; use Play to open the decoder.";
            }
        }
        if (kind == Kind::Text || kind == Kind::Other || !ready) {
            lines = readLines(a, binary, truncated);
            if (kind == Kind::Text || kind == Kind::Other) {
                ready = true;
                description = binary ? "Binary file / hex + ASCII preview"
                                     : "Text file / " + std::to_string(lines.size()) + " preview lines";
            }
        }
    }
    int clips() const { return isFbx ? int(fbx.animations.size()) : animationCount; }
    std::string clipName() const {
        if (!clips())
            return "No animation clips";
        return isFbx ? fbx.animations[clip] : std::string(animations[clip].name);
    }
    void playAudio(const Asset &a) {
        if (!IsAudioDeviceReady())
            InitAudioDevice();
        if (!IsAudioDeviceReady()) {
            error = "No audio output device is available. Waveform inspection remains available.";
            return;
        }
        if (!IsMusicValid(music))
            music = LoadMusicStream(a.absolute.string().c_str());
        if (!IsMusicValid(music)) {
            error = "Audio stream decoder could not open this file.";
            return;
        }
        if (playing) {
            PauseMusicStream(music);
            playing = false;
        } else {
            if (GetMusicTimePlayed(music) > 0)
                ResumeMusicStream(music);
            else
                PlayMusicStream(music);
            playing = true;
        }
    }
    void update(Rectangle canvas) {
        if (IsMusicValid(music))
            UpdateMusicStream(music);
        if (kind == Kind::Model && ready && animate && clips()) {
            animationTime += GetFrameTime();
            if (isFbx)
                fbx.animate(clip, animationTime);
            else if (animations[clip].frameCount > 0)
                UpdateModelAnimation(model, animations[clip],
                                     int(animationTime * 30) % animations[clip].frameCount);
        }
        if (!CheckCollisionPointRec(GetMousePosition(), canvas))
            return;
        const float wheel = GetMouseWheelMove();
        if (kind == Kind::Model && ready) {
            radius = std::clamp(radius * std::pow(1.13f, -wheel), modelSize * .03f, modelSize * 100);
            auto delta = GetMouseDelta();
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                yaw -= delta.x * .008f;
                pitch = std::clamp(pitch + delta.y * .008f, -1.45f, 1.45f);
            }
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                Vector3 right{std::cos(yaw), 0, -std::sin(yaw)};
                target = Vector3Add(target, Vector3Scale(right, -delta.x * radius * .0014f));
                target.y += delta.y * radius * .0014f;
            }
        } else if (kind == Kind::Image && ready) {
            imageZoom = std::clamp(imageZoom * std::pow(1.13f, wheel), .05f, 40.f);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                imagePan = Vector2Add(imagePan, GetMouseDelta());
        } else if (!lines.empty()) {
            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
                textColumn = std::max(0, textColumn - int(wheel * 6));
            else
                textScroll = std::clamp(textScroll - int(wheel * 3), 0, std::max(0, int(lines.size()) - 1));
        }
    }
    void draw(Rectangle canvas, Shader shader, bool wire) {
        DrawRectangleRec(canvas, {19, 24, 31, 255});
        BeginScissorMode(int(canvas.x), int(canvas.y), int(canvas.width), int(canvas.height));
        EndScissorMode();
        if (kind == Kind::Image && ready) {
            BeginScissorMode(int(canvas.x), int(canvas.y), int(canvas.width), int(canvas.height));
            for (int y = int(canvas.y); y < canvas.y + canvas.height; y += 24)
                for (int x = int(canvas.x); x < canvas.x + canvas.width; x += 24)
                    DrawRectangle(x, y, 24, 24,
                                  ((x - int(canvas.x)) / 24 + (y - int(canvas.y)) / 24) % 2
                                      ? Color{42, 47, 55, 255}
                                      : Color{31, 36, 44, 255});
            const float fitScale =
                std::min((canvas.width - 28) / image.width, (canvas.height - 28) / image.height) * imageZoom;
            Rectangle dest{canvas.x + canvas.width * .5f - image.width * fitScale * .5f + imagePan.x,
                           canvas.y + canvas.height * .5f - image.height * fitScale * .5f + imagePan.y,
                           image.width * fitScale, image.height * fitScale};
            DrawTexturePro(image, {0, 0, float(image.width), float(image.height)}, dest, {0, 0}, 0, WHITE);
            EndScissorMode();
        } else if (kind == Kind::Font && ready) {
            BeginScissorMode(int(canvas.x), int(canvas.y), int(canvas.width), int(canvas.height));
            const std::array<const char *, 5> samples{
                "DeathWard  /  Fort Mercy", "The quick brown fox jumps over the lazy dog.",
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "abcdefghijklmnopqrstuvwxyz",
                "0123456789  !? @#$% &* () [] {}"};
            float y = canvas.y + 28;
            for (size_t i = 0; i < samples.size(); ++i) {
                const float size = i == 0 ? 42 : 27;
                DrawTextEx(font, samples[i], {canvas.x + 22, y}, size, 1, Ink);
                y += i == 0 ? 80 : 57;
            }
            EndScissorMode();
        } else if (kind == Kind::Audio && ready) {
            label("AUDIO WAVEFORM", int(canvas.x + 24), int(canvas.y + 24), 18, Muted);
            const float middle = canvas.y + canvas.height * .5f;
            DrawLine(int(canvas.x + 24), int(middle), int(canvas.x + canvas.width - 24), int(middle), Edge);
            for (size_t i = 0; i < waveform.size(); ++i) {
                const float x = canvas.x + 24 + float(i) / waveform.size() * (canvas.width - 48),
                            h = waveform[i] * canvas.height * .3f;
                DrawLine(int(x), int(middle - h), int(x), int(middle + h), Accent);
            }
            if (waveform.empty())
                label("Waveform unavailable. Audio remains available through Play.", int(canvas.x + 24),
                      int(middle - 15), 16, Muted);
        } else if (!lines.empty()) {
            BeginScissorMode(int(canvas.x), int(canvas.y), int(canvas.width), int(canvas.height));
            const int rows = int(canvas.height / 23);
            for (int row = 0; row < rows && textScroll + row < int(lines.size()); ++row) {
                const int index = textScroll + row;
                label(TextFormat("%5d", index + 1), int(canvas.x + 8), int(canvas.y + 12 + 23 * row), 16,
                      Muted);
                const auto &line = lines[index];
                label(textColumn < int(line.size()) ? line.substr(textColumn) : "", int(canvas.x + 68),
                      int(canvas.y + 12 + 23 * row), 16, Ink);
            }
            EndScissorMode();
        }
    }
    void drawModel(RenderTexture2D &texture, Rectangle canvas, Shader shader, bool wire) {
        if (kind != Kind::Model || !ready)
            return;
        const int width = std::max(1, int(canvas.width)), height = std::max(1, int(canvas.height));
        if (texture.texture.width != width || texture.texture.height != height) {
            if (texture.id)
                UnloadRenderTexture(texture);
            texture = LoadRenderTexture(width, height);
        }
        BeginTextureMode(texture);
        ClearBackground({19, 24, 31, 255});
        Camera3D camera{};
        camera.position =
            Vector3Add(target, {std::sin(yaw) * std::cos(pitch) * radius, std::sin(pitch) * radius,
                                std::cos(yaw) * std::cos(pitch) * radius});
        camera.target = target;
        camera.up = {0, 1, 0};
        camera.fovy = 40;
        camera.projection = CAMERA_PERSPECTIVE;
        rlSetClipPlanes(std::max(double(modelSize) * .001, .0000001), std::max(double(modelSize) * 100, 10.));
        BeginMode3D(camera);
        const auto b = modelBounds();
        DrawPlane({target.x, b.min.y - .002f * modelSize, target.z}, {modelSize * 3, modelSize * 3},
                  {27, 34, 42, 255});
        rlPushMatrix();
        rlTranslatef(target.x, b.min.y - .001f * modelSize, target.z);
        DrawGrid(20, modelSize / 10);
        rlPopMatrix();
        if (isFbx)
            fbx.draw(shader, wire, section);
        else {
            rlDisableBackfaceCulling();
            if (wire)
                rlEnableWireMode();
            for (int i = 0; i < model.meshCount; ++i) {
                if (section >= 0 && i != section)
                    continue;
                auto material = model.materials[model.meshMaterial[i]];
                material.shader = shader;
                DrawMesh(model.meshes[i], material, model.transform);
            }
            if (wire)
                rlDisableWireMode();
            rlEnableBackfaceCulling();
        }
        EndMode3D();
        EndTextureMode();
        DrawTextureRec(texture.texture, {0, 0, float(width), -float(height)}, {canvas.x, canvas.y}, WHITE);
    }
};
struct Browser {
    Inventory inventory;
    Preview preview;
    Shader shader{};
    RenderTexture2D modelTexture{};
    std::unordered_map<std::string, fs::path> images;
    std::vector<size_t> visible;
    std::vector<std::pair<std::string, size_t>> folders;
    std::string folder, query;
    int category = -1, selected = -1, listScroll = 0, folderScroll = 0;
    bool searchFocus = false, wire = false;
    std::string notification;
    explicit Browser(const fs::path &root) : inventory(scan(root)) {
        shader = LoadShaderFromMemory(VertexShader, FragmentShader);
        index();
        filter();
    }
    ~Browser() {
        preview.clear();
        if (modelTexture.id)
            UnloadRenderTexture(modelTexture);
        if (shader.id)
            UnloadShader(shader);
    }
    void index() {
        images.clear();
        std::map<std::string, size_t> counts;
        for (const auto &a : inventory.assets) {
            if (a.kind == Kind::Image) {
                auto [it, added] = images.emplace(lower(a.absolute.filename().string()), a.absolute);
                // An ambiguous basename must not silently pick another pack's texture.
                if (!added && it->second != a.absolute)
                    it->second.clear();
            }
            auto p = fs::path(a.folder);
            while (!p.empty() && p != ".") {
                ++counts[p.generic_string()];
                p = p.parent_path();
            }
        }
        folders.assign(counts.begin(), counts.end());
    }
    void filter() {
        visible.clear();
        const auto search = lower(query);
        for (size_t i = 0; i < inventory.assets.size(); ++i) {
            auto &a = inventory.assets[i];
            if (category >= 0 && int(a.kind) != category)
                continue;
            if (!folder.empty() && a.folder != folder && a.folder.rfind(folder + "/", 0) != 0)
                continue;
            if (a.search.find(search) == std::string::npos)
                continue;
            visible.push_back(i);
        }
        listScroll = std::clamp(listScroll, 0, std::max(0, int(visible.size()) - 1));
    }
    void select(size_t index) {
        if (index >= inventory.assets.size())
            return;
        selected = int(index);
        preview.load(inventory.assets[index], images);
        auto pos = std::find(visible.begin(), visible.end(), index);
        if (pos != visible.end())
            listScroll = std::max(0, int(pos - visible.begin()) - 3);
    }
    bool selectPath(const std::string &path) {
        for (size_t i = 0; i < inventory.assets.size(); ++i)
            if (inventory.assets[i].relative == path || inventory.assets[i].absolute.string() == path) {
                select(i);
                return true;
            }
        return false;
    }
    void rescan() {
        const std::string previous = selected >= 0 ? inventory.assets[selected].relative : "";
        preview.clear();
        selected = -1;
        inventory = scan(inventory.root);
        index();
        filter();
        selectPath(previous);
        notification = "Inventory refreshed";
    }
    Rectangle canvas() const {
        return {650, 210, float(GetScreenWidth() - 670), float(GetScreenHeight() - 350)};
    }
    void input() {
        if (searchFocus) {
            for (int c = GetCharPressed(); c; c = GetCharPressed())
                if (c >= 32 && query.size() < 180) {
                    int count = 0;
                    const char *utf = CodepointToUTF8(c, &count);
                    query.append(utf, count);
                    listScroll = 0;
                    filter();
                }
            if (IsKeyPressed(KEY_BACKSPACE) && !query.empty()) {
                do {
                    query.pop_back();
                } while (!query.empty() && (static_cast<unsigned char>(query.back()) & 0xc0) == 0x80);
                listScroll = 0;
                filter();
            }
            if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE))
                searchFocus = false;
        } else {
            if (IsKeyPressed(KEY_R))
                rescan();
            if (IsKeyPressed(KEY_W))
                wire = !wire;
            if (IsKeyPressed(KEY_M) && preview.kind == Kind::Model && preview.ready)
                preview.nextSection(IsKeyDown(KEY_LEFT_SHIFT));
            if (IsKeyPressed(KEY_F)) {
                if (preview.kind == Kind::Model && preview.ready)
                    preview.fit();
                else {
                    preview.imageZoom = 1;
                    preview.imagePan = {};
                }
            }
            if (IsKeyPressed(KEY_SPACE)) {
                if (preview.kind == Kind::Audio && selected >= 0)
                    preview.playAudio(inventory.assets[selected]);
                else
                    preview.animate = !preview.animate;
            }
            if (preview.clips() && (IsKeyPressed(KEY_LEFT_BRACKET) || IsKeyPressed(KEY_RIGHT_BRACKET))) {
                preview.clip = (preview.clip + (IsKeyPressed(KEY_RIGHT_BRACKET) ? 1 : preview.clips() - 1)) %
                               preview.clips();
                preview.animationTime = 0;
            }
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_UP)) {
                auto at = std::find(visible.begin(), visible.end(), size_t(std::max(selected, 0)));
                int pos =
                    at == visible.end() ? 0 : int(at - visible.begin()) + (IsKeyPressed(KEY_DOWN) ? 1 : -1);
                if (!visible.empty())
                    select(visible[std::clamp(pos, 0, int(visible.size()) - 1)]);
            }
        }
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_F))
            searchFocus = true;
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_C) && selected >= 0) {
            SetClipboardText(inventory.assets[selected].absolute.string().c_str());
            notification = "Asset path copied";
        }
        const auto mouse = GetMousePosition();
        const float wheel = GetMouseWheelMove();
        if (CheckCollisionPointRec(mouse, {0, 122, 232, float(GetScreenHeight() - 158)}))
            folderScroll = std::clamp(folderScroll - int(wheel * 3), 0, std::max(0, int(folders.size()) - 1));
        if (CheckCollisionPointRec(mouse, {240, 122, 390, float(GetScreenHeight() - 158)}))
            listScroll = std::clamp(listScroll - int(wheel * 3), 0, std::max(0, int(visible.size()) - 1));
        preview.update(canvas());
    }
    void draw() {
        const int width = GetScreenWidth(), height = GetScreenHeight();
        ClearBackground(Bg);
        DrawRectangle(0, 0, width, 60, Panel);
        label("DEATHWARD", 20, 15, 27, Accent);
        label("ASSET BROWSER", 204, 21, 18, Ink);
        label(std::to_string(inventory.assets.size()) + " assets  /  read-only", width - 300, 21, 17, Muted);
        Rectangle search{244, 74, 386, 34};
        DrawRectangleRec(search, Panel);
        DrawRectangleLinesEx(search, 1, searchFocus ? Accent : Edge);
        label(query.empty() && !searchFocus ? "Search assets...  Ctrl+F" : query, 254, 83, 16,
              query.empty() ? Muted : Ink);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            searchFocus = CheckCollisionPointRec(GetMousePosition(), search);
        const std::array<const char *, 7> tabs{"All", "Models", "Images", "Audio", "Fonts", "Text", "Other"};
        float x = 650;
        for (int i = 0; i < 7; ++i) {
            const float w = float(std::max(55, MeasureText(tabs[i], 15) + 20));
            if (button({x, 74, w, 34}, tabs[i], category == i - 1)) {
                category = i - 1;
                listScroll = 0;
                filter();
            }
            x += w + 5;
        }
        DrawLine(0, 120, width, 120, Edge);
        label("FOLDERS", 16, 83, 16, Muted);
        DrawRectangle(0, 122, 232, height - 158, Panel);
        DrawRectangle(240, 122, 390, height - 158, Panel);
        DrawLine(232, 120, 232, height - 36, Edge);
        DrawLine(630, 120, 630, height - 36, Edge);
        BeginScissorMode(0, 122, 232, height - 158);
        int fy = 134;
        if (folder.empty())
            DrawRectangle(6, fy - 5, 220, 28, Select);
        label("All assets", 16, fy, 17, folder.empty() ? Accent : Ink);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(GetMousePosition(), {6, float(fy - 5), 220, 28})) {
            folder.clear();
            listScroll = 0;
            filter();
        }
        fy += 35;
        for (int i = folderScroll; i < int(folders.size()) && fy < height - 36; ++i) {
            const auto &[path, count] = folders[i];
            int depth = int(std::count(path.begin(), path.end(), '/'));
            const int indent = 14 + std::min(depth, 6) * 12;
            if (path == folder)
                DrawRectangle(6, fy - 4, 220, 27, Select);
            label(clipped(fs::path(path).filename().string(), 204 - indent, 15), indent, fy, 15,
                  path == folder ? Accent : Ink);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                CheckCollisionPointRec(GetMousePosition(), {6, float(fy - 4), 220, 27})) {
                folder = path;
                listScroll = 0;
                filter();
            }
            fy += 28;
        }
        (void)fy;
        EndScissorMode();
        BeginScissorMode(242, 122, 386, height - 158);
        label(std::to_string(visible.size()) + " matching files", 254, 134, 16, Muted);
        int y = 164;
        for (int row = listScroll; row < int(visible.size()) && y < height - 36; ++row) {
            const size_t index = visible[row];
            const auto &a = inventory.assets[index];
            const bool active = selected == int(index);
            Rectangle r{246, float(y), 380, 49};
            if (active || CheckCollisionPointRec(GetMousePosition(), r))
                DrawRectangleRec(r, active ? Select : Color{32, 40, 48, 255});
            label(clipped(a.absolute.filename().string(), 346, 17), 254, y + 5, 17, active ? Accent : Ink);
            label(clipped(a.folder.empty() ? "assets / " + bytes(a.bytes) : a.folder + " / " + bytes(a.bytes),
                          346, 13),
                  254, y + 28, 13, Muted);
            if (CheckCollisionPointRec(GetMousePosition(), r) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                select(index);
            y += 51;
        }
        if (visible.empty())
            label("No matching assets", 260, 180, 18, Muted);
        EndScissorMode();
        if (selected >= 0) {
            const auto &a = inventory.assets[selected];
            label(clipped(a.relative, width - 680, 20), 650, 136, 20, Accent);
            label(std::string(kindName(a.kind)) + "  |  " + bytes(a.bytes) + "  |  " +
                      (a.extension.empty() ? "no extension" : a.extension),
                  650, 164, 15, Muted);
            label(clipped(preview.description, width - 680, 15), 650, 188, 15, Ink);
            preview.draw(canvas(), shader, wire);
            preview.drawModel(modelTexture, canvas(), shader, wire);
            if (a.kind == Kind::Model && preview.ready) {
                const std::string part = preview.section < 0
                                             ? "Sections: all [M]"
                                             : "Section " + std::to_string(preview.section + 1) + "/" +
                                                   std::to_string(preview.sections());
                if (button({float(width - 205), 160, 185, 30}, part.c_str(), preview.section >= 0))
                    preview.nextSection();
            }
            int bottom = height - 126;
            if (a.kind == Kind::Model && preview.ready) {
                if (button({650, float(bottom), 90, 32}, "Fit [F]"))
                    preview.fit();
                if (button({748, float(bottom), 102, 32}, "Wire [W]", wire))
                    wire = !wire;
                if (preview.clips()) {
                    if (button({858, float(bottom), 100, 32}, preview.animate ? "Pause" : "Animate",
                               preview.animate))
                        preview.animate = !preview.animate;
                    if (button({966, float(bottom), 50, 32}, "<")) {
                        preview.clip = (preview.clip + preview.clips() - 1) % preview.clips();
                        preview.animationTime = 0;
                    }
                    if (button({1022, float(bottom), 50, 32}, ">")) {
                        preview.clip = (preview.clip + 1) % preview.clips();
                        preview.animationTime = 0;
                    }
                    label(clipped(preview.clipName(), width - 1096, 15), 1084, bottom + 9, 15, Ink);
                }
                label("Drag: orbit   Right drag: pan   Wheel: zoom   [ ]: animation clip", 650, bottom + 44,
                      15, Muted);
            } else if (a.kind == Kind::Image && preview.ready) {
                if (button({650, float(bottom), 100, 32}, "Fit [F]")) {
                    preview.imageZoom = 1;
                    preview.imagePan = {};
                }
                label("Drag: pan   Wheel: zoom   Checkerboard: transparency", 650, bottom + 44, 15, Muted);
            } else if (a.kind == Kind::Audio) {
                if (button({650, float(bottom), 110, 32}, preview.playing ? "Pause" : "Play [Space]",
                           preview.playing))
                    preview.playAudio(a);
                if (IsMusicValid(preview.music))
                    label(TextFormat("%.1f / %.1f seconds", GetMusicTimePlayed(preview.music),
                                     GetMusicTimeLength(preview.music)),
                          776, bottom + 8, 16, Ink);
                label("Playback starts only when you press Play.", 650, bottom + 44, 15, Muted);
            } else
                label("Wheel: scroll   Shift + wheel: horizontal scroll", 650, bottom + 11, 15, Muted);
            if (button({float(width - 140), float(height - 76), 120, 30}, "Copy path")) {
                SetClipboardText(a.absolute.string().c_str());
                notification = "Asset path copied";
            }
            if (!preview.error.empty())
                label(clipped(preview.error, width - 840, 14), 650, height - 74, 14, {240, 139, 119, 255});
            else if (preview.truncated)
                label("Preview limited to 2 MB of text / 4 KB of binary. Original file is unchanged.", 650,
                      height - 74, 14, Muted);
        } else {
            label("Choose an asset to inspect", 680, 200, 25, Muted);
        }
        DrawRectangle(0, height - 34, width, 34, Panel);
        label(clipped(inventory.root.string(), width - 650, 14), 16, height - 23, 14, Muted);
        label(notification.empty() ? "R: rescan   Ctrl+C: copy path   Ctrl+Q: quit"
                                   : clipped(notification, 550, 14),
              width - 610, height - 23, 14, Muted);
        if (!inventory.errors.empty())
            label(std::to_string(inventory.errors.size()) + " scan errors", width - 140, height - 23, 14,
                  {240, 139, 119, 255});
    }
};
struct Options {
    fs::path root = DEATHWARD_ASSET_DIR;
    std::string select, query, folder;
    int kind = -1, frames = 0;
    bool list = false, json = false, smoke = false;
    fs::path screenshot, screenshotDir;
};
Options options(int argc, char **argv) {
    Options o;
    auto next = [&](int &i) {
        if (++i >= argc)
            throw std::runtime_error("Missing option value");
        return std::string(argv[i]);
    };
    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--root" || a == "--asset-root")
            o.root = next(i);
        else if (a == "--select")
            o.select = next(i);
        else if (a == "--query")
            o.query = next(i);
        else if (a == "--folder")
            o.folder = next(i);
        else if (a == "--kind") {
            auto name = lower(next(i));
            bool found = false;
            for (int k = 0; k < 6; ++k)
                if (lower(kindName(Kind(k))) == name) {
                    o.kind = k;
                    found = true;
                }
            if (!found && name != "all")
                throw std::runtime_error("Kinds: all, models, images, audio, fonts, text, other");
        } else if (a == "--list")
            o.list = true;
        else if (a == "--inventory-json")
            o.json = true;
        else if (a == "--frames")
            o.frames = std::stoi(next(i));
        else if (a == "--screenshot")
            o.screenshot = next(i);
        else if (a == "--screenshot-dir")
            o.screenshotDir = next(i);
        else if (a == "--smoke")
            o.smoke = true;
        else if (a == "--help") {
            std::cout
                << "DeathWard asset browser\n  --root PATH             asset directory (default: checkout "
                   "assets)\n  --list / --inventory-json  headless full inventory\n  --query TEXT --folder "
                   "PATH --kind models|images|audio|fonts|text|other|all\n  --select RELATIVE_PATH   "
                   "initially selected asset\n  --frames N --screenshot PATH   bounded rendered check\n  "
                   "--smoke --screenshot-dir PATH  rendered preview coverage sequence\n";
            std::exit(0);
        } else
            throw std::runtime_error("Unknown option: " + a);
    }
    if (o.frames < 0)
        throw std::runtime_error("Frames must be nonnegative");
    return o;
}
bool matches(const Asset &a, const Options &o) {
    return (o.kind < 0 || int(a.kind) == o.kind) &&
           (o.folder.empty() || a.folder == o.folder || a.folder.rfind(o.folder + "/", 0) == 0) &&
           a.search.find(lower(o.query)) != std::string::npos;
}
} // namespace
int main(int argc, char **argv) {
    try {
        const auto o = options(argc, argv);
        if (o.list || o.json) {
            const auto inventory = scan(o.root);
            if (o.json)
                std::cout << "{\"root\":" << jsonString(inventory.root.string())
                          << ",\"total_files\":" << inventory.assets.size() << ",\"assets\":[";
            bool first = true;
            for (const auto &a : inventory.assets)
                if (matches(a, o)) {
                    if (o.json) {
                        if (!first)
                            std::cout << ',';
                        std::cout << "{\"path\":" << jsonString(a.relative)
                                  << ",\"kind\":" << jsonString(kindName(a.kind)) << ",\"bytes\":" << a.bytes
                                  << '}';
                    } else
                        std::cout << a.relative << '\n';
                    first = false;
                }
            if (o.json) {
                std::cout << "],\"errors\":[";
                for (size_t i = 0; i < inventory.errors.size(); ++i) {
                    if (i)
                        std::cout << ',';
                    std::cout << jsonString(inventory.errors[i]);
                }
                std::cout << "]}\n";
            }
            return inventory.errors.empty() ? 0 : 2;
        }
        SetTraceLogLevel(LOG_WARNING);
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT | (o.smoke ? FLAG_WINDOW_HIDDEN : 0));
        InitWindow(1480, 920, "DeathWard Asset Browser");
        if (!IsWindowReady())
            throw std::runtime_error("Cannot create the asset browser window");
        SetWindowMinSize(1280, 720);
        SetExitKey(KEY_NULL);
        SetTargetFPS(60);
        int result = 0;
        {
            Browser app(o.root);
            app.query = o.query;
            app.folder = o.folder;
            app.category = o.kind;
            app.filter();
            if (!o.select.empty()) {
                if (!app.selectPath(o.select))
                    throw std::runtime_error("Initial asset not found: " + o.select);
            } else if (!o.query.empty() || !o.folder.empty() || o.kind >= 0) {
                if (!app.visible.empty())
                    app.select(app.visible.front());
            } else if (!app.selectPath("art_sample/hero-combined.glb") && !app.visible.empty())
                app.select(app.visible.front());
            const std::vector<std::pair<std::string, std::string>> requested{
                {"fbx", "western/source/Models/SM_Env_Cactus_01.fbx"},
                {"glb", "animals/capybara.glb"},
                {"image", "particles/smoke.png"},
                {"text", "mechanics/regular_enemy_health.mechanics"},
                {"font", "ui/body.ttf"},
                {"audio", ""},
                {"metadata", ""},
                {"binary", ""}};
            std::vector<std::pair<std::string, size_t>> sequence;
            if (o.smoke) {
                for (const auto &[name, path] : requested) {
                    auto it = std::find_if(app.inventory.assets.begin(), app.inventory.assets.end(),
                                           [&](const auto &a) {
                                               if (!path.empty())
                                                   return a.relative == path;
                                               if (name == "audio")
                                                   return a.extension == ".wav";
                                               if (name == "metadata")
                                                   return a.extension == ".meta";
                                               return a.extension == ".nav";
                                           });
                    if (it == app.inventory.assets.end() && name == "fbx")
                        it = std::find_if(app.inventory.assets.begin(), app.inventory.assets.end(),
                                          [](const auto &a) { return a.extension == ".fbx"; });
                    if (it != app.inventory.assets.end())
                        sequence.emplace_back(name, size_t(it - app.inventory.assets.begin()));
                }
                if (sequence.size() != requested.size())
                    throw std::runtime_error("Smoke preview fixtures are missing");
                if (!o.screenshotDir.empty())
                    fs::create_directories(o.screenshotDir);
            }
            const int frames = o.frames ? o.frames : (o.smoke ? int(sequence.size()) * 20 : 0);
            int frame = 0;
            while (!WindowShouldClose() && !(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_Q))) {
                if (o.smoke && frame % 20 == 0) {
                    const auto stage = size_t(frame / 20);
                    if (stage < sequence.size()) {
                        app.select(sequence[stage].second);
                        std::cout << "SMOKE " << sequence[stage].first << ' '
                                  << app.inventory.assets[sequence[stage].second].relative
                                  << " preview=" << (app.preview.ready ? "ready" : "failed") << '\n';
                        if (!app.preview.ready)
                            result = 3;
                    }
                }
                app.input();
                BeginDrawing();
                app.draw();
                EndDrawing();
                if (o.smoke && !o.screenshotDir.empty() && frame % 20 == 19) {
                    const auto stage = size_t(frame / 20);
                    if (stage < sequence.size())
                        screenshot((o.screenshotDir / (sequence[stage].first + ".png")).string().c_str());
                }
                ++frame;
                if (frames && frame >= frames) {
                    if (!o.screenshot.empty()) {
                        if (!o.screenshot.parent_path().empty())
                            fs::create_directories(o.screenshot.parent_path());
                        screenshot(o.screenshot.string().c_str());
                    }
                    break;
                }
            }
        }
        if (IsAudioDeviceReady())
            CloseAudioDevice();
        CloseWindow();
        return result;
    } catch (const std::exception &e) {
        std::cerr << "Asset browser: " << e.what() << '\n';
        return 1;
    }
}
