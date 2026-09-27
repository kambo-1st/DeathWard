#include "editor/TownEditor.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <cctype>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace dw {
namespace {
constexpr Color Background{19, 25, 29, 255}, Panel{28, 35, 39, 250}, Line{52, 64, 68, 255},
    Text{232, 230, 217, 255}, Muted{152, 165, 164, 255}, Accent{232, 174, 96, 255}, Teal{99, 212, 181, 255};
constexpr std::array<Vector3, 3> Axes{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
constexpr std::array<Color, 3> AxisColors{{{237, 100, 95, 255}, {126, 213, 132, 255}, {111, 165, 244, 255}}};
std::string number(float value) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << value;
    return out.str();
}
std::string lower(std::string s) {
    for (auto &c : s)
        c = char(std::tolower(static_cast<unsigned char>(c)));
    return s;
}
float component(Vector3 v, int axis) {
    return axis == 0 ? v.x : axis == 1 ? v.y : v.z;
}
Vector3 center(Box box) {
    return mul(add(box.min, box.max), .5f);
}
float segmentDistance(Vector2 p, Vector2 a, Vector2 b) {
    const auto d = Vector2Subtract(b, a);
    const float t = std::clamp(
        Vector2DotProduct(Vector2Subtract(p, a), d) / std::max(1.0f, Vector2LengthSqr(d)), 0.0f, 1.0f);
    return Vector2Distance(p, Vector2Add(a, Vector2Scale(d, t)));
}
} // namespace
bool TownEditor::open(const std::filesystem::path &directory, Camera3D view) {
    try {
        directory_ = directory;
        if (!scene_.load(directory))
            throw std::runtime_error("Could not load the town model and scene.");
        document_ = scene_.document();
        navigation_.load(directory / "town.nav");
        camera = view;
        const auto offset = sub(view.position, view.target);
        radius_ = std::clamp(length(offset), 5.0f, 300.0f);
        yaw_ = std::atan2(offset.z, offset.x);
        pitch_ = std::clamp(std::asin(offset.y / radius_), .15f, 1.45f);
        camera.up = {0, 1, 0};
        camera.fovy = 45;
        camera.projection = CAMERA_PERSPECTIVE;
        undo_.clear();
        redo_.clear();
        selected_.reset();
        paletteSelection_.reset();
        revision_ = savedRevision_ = nextRevision_ = 0;
        active = true;
        quitRequested = saved = false;
        closePrompt_ = reloadPrompt_ = closingWindow_ = false;
        orbiting_ = panning_ = dragChanged_ = false;
        field_ = dragAxis_ = -1;
        marker_ = scroll_ = 0;
        search_.clear();
        searchFocus_ = false;
        status = "Select an object in the view or scene list. Changes are saved only with Save.";
        updateView();
        return true;
    } catch (const std::exception &e) {
        status = e.what();
        return false;
    }
}
TownEditor::Snapshot TownEditor::snapshot() const {
    return {document_, navigation_.spawn, navigation_.mission, selected_, revision_};
}
void TownEditor::restore(Snapshot state) {
    document_ = std::move(state.document);
    navigation_.spawn = state.spawn;
    navigation_.mission = state.mission;
    selected_ = state.selected;
    revision_ = state.revision;
    field_ = dragAxis_ = -1;
    sync();
}
void TownEditor::remember() {
    undo_.push_back(snapshot());
    if (undo_.size() > 80)
        undo_.pop_front();
    redo_.clear();
    revision_ = ++nextRevision_;
}
void TownEditor::sync() {
    try {
        scene_.applyDocument(document_);
    } catch (const std::exception &e) {
        const std::string error = e.what();
        if (!undo_.empty()) {
            auto previous = std::move(undo_.back());
            undo_.pop_back();
            restore(std::move(previous));
        } else
            document_ = scene_.document();
        status = "Change rejected: " + error;
    }
}
void TownEditor::select(std::optional<size_t> index) {
    selected_ = index && *index < document_.instances.size() ? index : std::nullopt;
    field_ = dragAxis_ = -1;
}
Vector3 TownEditor::pivot() const {
    if (!selected_)
        return camera.target;
    const auto &m = document_.instances[*selected_].transform;
    return {m.m12, m.m13, m.m14};
}
void TownEditor::translate(Vector3 delta) {
    if (!selected_ || length(delta) < .000001f)
        return;
    remember();
    auto &m = document_.instances[*selected_].transform;
    m.m12 += delta.x;
    m.m13 += delta.y;
    m.m14 += delta.z;
    sync();
}
void TownEditor::rotate(Vector3 axis, float degrees) {
    if (!selected_ || std::abs(degrees) < .000001f)
        return;
    remember();
    auto &m = document_.instances[*selected_].transform;
    const auto p = pivot();
    m = MatrixMultiply(m, MatrixRotate(axis, degrees * DEG2RAD));
    m.m12 = p.x;
    m.m13 = p.y;
    m.m14 = p.z;
    sync();
}
void TownEditor::scale(Vector3 factors) {
    if (!selected_ || std::min({factors.x, factors.y, factors.z}) < .01f ||
        std::max({factors.x, factors.y, factors.z}) > 100)
        return;
    remember();
    auto &m = document_.instances[*selected_].transform;
    m.m0 *= factors.x;
    m.m1 *= factors.x;
    m.m2 *= factors.x;
    m.m4 *= factors.y;
    m.m5 *= factors.y;
    m.m6 *= factors.y;
    m.m8 *= factors.z;
    m.m9 *= factors.z;
    m.m10 *= factors.z;
    sync();
}
void TownEditor::duplicate() {
    if (!selected_)
        return;
    remember();
    auto copy = document_.instances[*selected_];
    copy.transform.m12 += 2;
    document_.instances.push_back(copy);
    selected_ = document_.instances.size() - 1;
    sync();
    status = "Object duplicated. Drag an axis handle to place it.";
}
void TownEditor::remove() {
    if (!selected_ || document_.instances.size() <= 1)
        return;
    remember();
    document_.instances.erase(document_.instances.begin() + std::ptrdiff_t(*selected_));
    selected_.reset();
    field_ = -1;
    sync();
}
void TownEditor::addAsset(size_t asset) {
    if (asset >= document_.assets.size())
        return;
    remember();
    auto p = camera.target;
    p.y = navigation_.spawn.y - document_.assets[asset].bounds.min.y;
    document_.instances.push_back({asset, MatrixTranslate(p.x, p.y, p.z)});
    selected_ = document_.instances.size() - 1;
    sync();
    status = "Added " + document_.assets[asset].label;
}
void TownEditor::undo() {
    if (undo_.empty())
        return;
    redo_.push_back(snapshot());
    auto state = std::move(undo_.back());
    undo_.pop_back();
    restore(std::move(state));
}
void TownEditor::redo() {
    if (redo_.empty())
        return;
    undo_.push_back(snapshot());
    auto state = std::move(redo_.back());
    redo_.pop_back();
    restore(std::move(state));
}
bool TownEditor::save() {
    try {
        commitField();
        auto nav = navigation_;
        nav.bake(document_, scene_.model());
        saveTownProject(directory_, document_, nav);
        navigation_ = std::move(nav);
        savedRevision_ = revision_;
        saved = true;
        status = "Saved scene and rebuilt navigation. Previous files are in town.scene.bak / town.nav.bak.";
        return true;
    } catch (const std::exception &e) {
        status = std::string("Save failed: ") + e.what();
        return false;
    }
}
bool TownEditor::reload() {
    try {
        TownDocument next;
        std::string error;
        if (!next.load(directory_ / "town.scene", error))
            throw std::runtime_error(error);
        TownNavigation nav;
        nav.load(directory_ / "town.nav");
        scene_.applyDocument(next);
        document_ = std::move(next);
        navigation_ = std::move(nav);
        undo_.clear();
        redo_.clear();
        selected_.reset();
        field_ = -1;
        revision_ = savedRevision_ = ++nextRevision_;
        status = "Reloaded the saved town.";
        return true;
    } catch (const std::exception &e) {
        status = e.what();
        return false;
    }
}
void TownEditor::focusSelection() {
    if (!selected_)
        return;
    const auto b = document_.bounds(*selected_);
    camera.target = center(b);
    radius_ = std::clamp(length(sub(b.max, b.min)) * 1.7f, 5.0f, 300.0f);
    updateView();
}
void TownEditor::updateView() {
    camera.position =
        add(camera.target, {radius_ * std::cos(pitch_) * std::cos(yaw_), radius_ * std::sin(pitch_),
                            radius_ * std::cos(pitch_) * std::sin(yaw_)});
}
Vector2 TownEditor::uiMouse() const {
    auto p = GetMousePosition();
    return {p.x / scaleX_, p.y / scaleY_};
}
bool TownEditor::overUI(Vector2 p) const {
    p = {p.x / scaleX_, p.y / scaleY_};
    return p.x < 272 || p.x > 1112 || p.y < 86 || p.y > 848;
}
Vector3 TownEditor::values(int group) const {
    if (!selected_)
        return {};
    const auto m = document_.instances[*selected_].transform;
    if (group == 0)
        return {m.m12, m.m13, m.m14};
    Vector3 p, s;
    Quaternion q;
    MatrixDecompose(m, &p, &q, &s);
    return group == 1 ? mul(QuaternionToEuler(q), RAD2DEG) : s;
}
void TownEditor::commitField() {
    if (field_ < 0 || !selected_)
        return;
    try {
        size_t end = 0;
        const float value = std::stof(fieldText_, &end);
        if (end != fieldText_.size() || !std::isfinite(value) || std::abs(value) > 10000)
            throw std::runtime_error("Enter a finite number between -10000 and 10000.");
        const int group = field_ / 3, axis = field_ % 3;
        const auto current = values(group);
        if (group == 0)
            translate(mul(Axes[size_t(axis)], value - component(current, axis)));
        else if (group == 1) {
            // Replace the rotation while preserving the imported stretch/shear matrix.
            auto angles = mul(current, DEG2RAD);
            auto next = angles;
            if (axis == 0)
                next.x = value * DEG2RAD;
            else if (axis == 1)
                next.y = value * DEG2RAD;
            else
                next.z = value * DEG2RAD;
            const Matrix oldRotation = QuaternionToMatrix(QuaternionFromEuler(angles.x, angles.y, angles.z));
            const Matrix newRotation = QuaternionToMatrix(QuaternionFromEuler(next.x, next.y, next.z));
            remember();
            auto &m = document_.instances[*selected_].transform;
            const auto p = pivot();
            m = MatrixMultiply(MatrixMultiply(m, MatrixTranspose(oldRotation)), newRotation);
            m.m12 = p.x;
            m.m13 = p.y;
            m.m14 = p.z;
            sync();
        } else {
            if (std::abs(value) < .01f)
                throw std::runtime_error("Scale must be at least 0.01 in magnitude.");
            const float factor = value / component(current, axis);
            if (factor <= 0 || factor > 100 || factor < .01f)
                throw std::runtime_error(
                    "Use a scale with the same sign, within 0.01 to 100 times its current size.");
            auto f = Vector3{1, 1, 1};
            if (axis == 0)
                f.x = factor;
            else if (axis == 1)
                f.y = factor;
            else
                f.z = factor;
            scale(f);
        }
    } catch (const std::exception &e) {
        status = e.what();
    }
    field_ = -1;
}
void TownEditor::requestClose(bool quit) {
    commitField();
    closingWindow_ = closingWindow_ || quit;
    if (dirty())
        closePrompt_ = true;
    else
        closeNow();
}
void TownEditor::closeNow() {
    active = false;
    quitRequested = closingWindow_;
    orbiting_ = panning_ = false;
}
void TownEditor::update(float dt) {
    scaleX_ = float(GetScreenWidth()) / 1440;
    scaleY_ = float(GetScreenHeight()) / 900;
    if (!active || closePrompt_ || reloadPrompt_)
        return;
    const auto mouse = GetMousePosition();
    const bool ctrl = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
    const bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
    if (searchFocus_ || field_ >= 0) {
        auto &text = searchFocus_ ? search_ : fieldText_;
        if (ctrl && IsKeyPressed(KEY_A))
            selectText_ = true;
        for (int c = GetCharPressed(); c; c = GetCharPressed())
            if (c >= 32 && c < 127 && text.size() < 80) {
                if (selectText_)
                    text.clear();
                selectText_ = false;
                text.push_back(char(c));
            }
        if (IsKeyPressed(KEY_BACKSPACE) && !text.empty()) {
            if (selectText_)
                text.clear();
            else
                text.pop_back();
            selectText_ = false;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            commitField();
            searchFocus_ = false;
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            field_ = -1;
            searchFocus_ = false;
        }
        if (searchFocus_)
            scroll_ = 0;
    } else {
        if (ctrl && IsKeyPressed(KEY_S))
            save();
        if (ctrl && IsKeyPressed(KEY_Z)) {
            if (shift)
                redo();
            else
                undo();
        }
        if (ctrl && IsKeyPressed(KEY_Y))
            redo();
        if (ctrl && IsKeyPressed(KEY_D))
            duplicate();
        if (IsKeyPressed(KEY_DELETE))
            remove();
        if (IsKeyPressed(KEY_F))
            focusSelection();
        if (IsKeyPressed(KEY_ONE))
            tool_ = Tool::Move;
        if (IsKeyPressed(KEY_TWO))
            tool_ = Tool::Rotate;
        if (IsKeyPressed(KEY_THREE))
            tool_ = Tool::Scale;
        if (IsKeyPressed(KEY_F4))
            requestClose();
        if (IsKeyPressed(KEY_ESCAPE)) {
            if (dragAxis_ >= 0) {
                if (dragChanged_)
                    undo();
                dragAxis_ = -1;
            } else if (marker_)
                marker_ = 0;
            else
                requestClose();
        }
        if (!ctrl && dragAxis_ < 0) {
            const auto forward =
                unit({camera.target.x - camera.position.x, 0, camera.target.z - camera.position.z});
            const Vector3 right{-forward.z, 0, forward.x};
            auto movement = add(mul(forward, float(IsKeyDown(KEY_W)) - float(IsKeyDown(KEY_S))),
                                mul(right, float(IsKeyDown(KEY_D)) - float(IsKeyDown(KEY_A))));
            movement.y = float(IsKeyDown(KEY_E)) - float(IsKeyDown(KEY_Q));
            camera.target = add(camera.target, mul(movement, std::min(dt, .1f) * (shift ? 50.0f : 15.0f)));
        }
    }
    const bool over = overUI(mouse);
    if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
        orbiting_ = !over;
        previousMouse_ = mouse;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        panning_ = !over;
        previousMouse_ = mouse;
    }
    if (!IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        orbiting_ = false;
    if (!IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        panning_ = false;
    const auto delta = Vector2Subtract(mouse, previousMouse_);
    if (dragAxis_ < 0 && orbiting_) {
        yaw_ = std::remainder(yaw_ - delta.x * .006f, 2 * PI);
        pitch_ = std::clamp(pitch_ + delta.y * .004f, .15f, 1.45f);
    }
    if (dragAxis_ < 0 && panning_) {
        const auto forward = unit(sub(camera.target, camera.position));
        const auto right = Vector3Normalize(Vector3CrossProduct(forward, {0, 1, 0}));
        const auto up = Vector3CrossProduct(right, forward);
        camera.target =
            add(camera.target, mul(add(mul(right, -delta.x), mul(up, delta.y)), radius_ * .0014f));
    }
    if (!over && dragAxis_ < 0)
        radius_ = std::clamp(radius_ * std::exp(-GetMouseWheelMoveV().y * .12f), 5.0f, 300.0f);
    updateView();
    previousMouse_ = mouse;
    if (!over && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        commitField();
        searchFocus_ = false;
        if (marker_) {
            const auto ray = GetScreenToWorldRay(mouse, camera);
            if (ray.direction.y < -.001f) {
                const float t = (navigation_.spawn.y - ray.position.y) / ray.direction.y;
                if (t > 0) {
                    remember();
                    auto p = add(ray.position, mul(ray.direction, t));
                    if (marker_ == 1)
                        navigation_.spawn = p;
                    else
                        navigation_.mission = p;
                    marker_ = 0;
                    status = "Marker placed. Saving snaps it onto nearby connected ground.";
                }
            }
        } else {
            dragAxis_ = -1;
            if (selected_) {
                const auto a = GetWorldToScreen(pivot(), camera);
                const float size = radius_ * .12f;
                float best = 10;
                for (int i = 0; i < 3; ++i) {
                    const auto b = GetWorldToScreen(add(pivot(), mul(Axes[size_t(i)], size)), camera);
                    if (Vector2Distance(a, b) < 16)
                        continue;
                    const float d = segmentDistance(mouse, Vector2Lerp(a, b, .2f), b);
                    if (d < best) {
                        best = d;
                        dragAxis_ = i;
                    }
                }
            }
            if (dragAxis_ >= 0) {
                dragTransform_ = document_.instances[*selected_].transform;
                dragMouse_ = mouse;
                dragChanged_ = false;
            } else
                select(scene_.pick(GetScreenToWorldRay(mouse, camera)));
        }
    }
    if (dragAxis_ >= 0 && selected_ && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        const auto p = Vector3{dragTransform_.m12, dragTransform_.m13, dragTransform_.m14};
        const float size = radius_ * .12f;
        const auto axis = Axes[size_t(dragAxis_)];
        const auto a = GetWorldToScreen(p, camera), b = GetWorldToScreen(add(p, mul(axis, size)), camera);
        const auto screenAxis = Vector2Subtract(b, a);
        const float pixels =
            Vector2DotProduct(Vector2Subtract(mouse, dragMouse_), Vector2Normalize(screenAxis));
        if (std::abs(pixels) > .01f) {
            if (!dragChanged_) {
                remember();
                dragChanged_ = true;
            }
            auto m = dragTransform_;
            if (tool_ == Tool::Move) {
                float amount = pixels / std::max(1.0f, Vector2Length(screenAxis)) * size;
                if (snap_ && !shift)
                    amount = std::round(amount / .5f) * .5f;
                auto d = mul(axis, amount);
                m.m12 += d.x;
                m.m13 += d.y;
                m.m14 += d.z;
            } else if (tool_ == Tool::Rotate) {
                float angle = pixels * .8f;
                if (snap_ && !shift)
                    angle = std::round(angle / 15) * 15;
                m = MatrixMultiply(m, MatrixRotate(axis, angle * DEG2RAD));
                m.m12 = p.x;
                m.m13 = p.y;
                m.m14 = p.z;
            } else {
                float factor = std::clamp(std::exp(pixels * .01f), .05f, 20.0f);
                if (snap_ && !shift)
                    factor = std::max(.1f, std::round(factor * 10) / 10);
                // Uniform scaling keeps the asset's proportions; inspector fields also allow per-axis
                // scaling.
                m = MatrixMultiply(MatrixScale(factor, factor, factor), m);
            }
            document_.instances[*selected_].transform = m;
            sync();
        }
    }
    if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        dragAxis_ = -1;
}
void TownEditor::panel(Rectangle r, Color color) const {
    DrawRectangleRec({r.x * scaleX_, r.y * scaleY_, r.width * scaleX_, r.height * scaleY_}, color);
}
void TownEditor::label(const std::string &value, float x, float y, int size, Color color, float width) const {
    std::string text = value;
    const int font = std::max(10, int(float(size) * std::min(scaleX_, scaleY_)));
    if (MeasureText(text.c_str(), font) > width * scaleX_) {
        while (!text.empty() && MeasureText((text + "...").c_str(), font) > width * scaleX_)
            text.pop_back();
        text += "...";
    }
    DrawText(text.c_str(), int(x * scaleX_), int(y * scaleY_), font, color);
}
bool TownEditor::button(const std::string &text, Rectangle r, bool selected, bool enabled) const {
    const bool hovered = CheckCollisionPointRec(uiMouse(), r) && !closePrompt_ && !reloadPrompt_;
    panel(r, selected ? Color{77, 64, 45, 255} : hovered && enabled ? Color{51, 65, 68, 255} : Line);
    label(text, r.x + 10, r.y + (r.height - 15) * .5f, 15, enabled ? (selected ? Accent : Text) : Muted,
          r.width - 16);
    return enabled && hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}
void TownEditor::draw() {
    scaleX_ = float(GetScreenWidth()) / 1440;
    scaleY_ = float(GetScreenHeight()) / 900;
    scene_.prepareLighting(camera);
    postProcess_.begin({142, 174, 188, 255}, distance(camera.position, camera.target));
    BeginMode3D(camera);
    scene_.draw(camera.target);
    scene_.draw(camera.target, true);
    if (showGrid_)
        DrawGrid(80, 2);
    if (showNavigation_) {
        for (size_t i = 0; i < navigation_.heights.size(); ++i) {
            if (!std::isfinite(navigation_.heights[i]))
                continue;
            auto p = navigation_.point(i);
            if (distance(p, camera.target) < 28)
                DrawCube(add(p, {0, .08f, 0}), .26f, .025f, .26f, {66, 209, 166, 130});
        }
    }
    for (int i = 0; i < 2; ++i) {
        auto p = i == 0 ? navigation_.spawn : navigation_.mission;
        DrawCylinder(add(p, {0, .1f, 0}), .45f, .45f, .1f, 16, i == 0 ? Teal : Accent);
        DrawLine3D(p, add(p, {0, 3, 0}), i == 0 ? Teal : Accent);
    }
    if (selected_) {
        const auto b = document_.bounds(*selected_);
        DrawBoundingBox({b.min, b.max}, Teal);
        const auto p = pivot();
        const float size = radius_ * .12f;
        rlDisableDepthTest();
        for (size_t i = 0; i < 3; ++i) {
            const auto end = add(p, mul(Axes[i], size));
            DrawCylinderEx(p, end, size * .012f, size * .012f, 8, AxisColors[i]);
            if (tool_ == Tool::Move)
                DrawCylinderEx(end, add(end, mul(Axes[i], size * .15f)), size * .05f, 0, 8, AxisColors[i]);
            else if (tool_ == Tool::Scale)
                DrawCube(end, size * .09f, size * .09f, size * .09f, AxisColors[i]);
            else
                DrawSphereEx(end, size * .045f, 6, 8, AxisColors[i]);
        }
        rlEnableDepthTest();
    }
    EndMode3D();
    postProcess_.end();
    drawUI();
}
void TownEditor::drawUI() {
    panel({0, 0, 1440, 86}, Background);
    panel({0, 86, 272, 762}, Panel);
    panel({1112, 86, 328, 762}, Panel);
    panel({0, 848, 1440, 52}, Background);
    label("DEATHWARD", 20, 14, 14, Accent);
    label("TOWN EDITOR", 20, 35, 25, Text);
    label(dirty() ? "town.scene  /  Unsaved changes" : "town.scene  /  Saved", 278, 21, 17,
          dirty() ? Accent : Muted, 390);
    if (button("Save", {730, 16, 92, 34}))
        save();
    if (button("Reload", {832, 16, 92, 34})) {
        commitField();
        if (dirty())
            reloadPrompt_ = true;
        else
            reload();
    }
    if (button("Undo", {934, 16, 74, 34}, false, !undo_.empty()))
        undo();
    if (button("Redo", {1018, 16, 74, 34}, false, !redo_.empty()))
        redo();
    if (button("Back to town", {1215, 16, 200, 34}))
        requestClose();
    label(std::to_string(GetFPS()) + " FPS", 1112, 28, 12, Muted, 96);
    label("Middle drag: orbit   Right drag: pan   Wheel: zoom   WASD / Q E: fly   F: focus", 278, 59, 13,
          Muted, 825);
    if (button("Scene", {14, 103, 115, 31}, !palette_)) {
        palette_ = false;
        scroll_ = 0;
    }
    if (button("Assets", {139, 103, 115, 31}, palette_)) {
        palette_ = true;
        scroll_ = 0;
    }
    const Rectangle searchBox{14, 149, 240, 33};
    panel(searchBox, searchFocus_ ? Line : Background);
    label(search_.empty() ? "Search objects..." : search_, 24, 159, 14, search_.empty() ? Muted : Text, 218);
    if (!closePrompt_ && !reloadPrompt_ && CheckCollisionPointRec(uiMouse(), searchBox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        commitField();
        searchFocus_ = true;
        selectText_ = true;
    }
    std::vector<size_t> filtered;
    const auto query = lower(search_);
    const size_t count = palette_ ? document_.assets.size() : document_.instances.size();
    for (size_t i = 0; i < count; ++i) {
        const auto asset = palette_ ? i : document_.instances[i].asset;
        if (lower(document_.assets[asset].label + " #" + std::to_string(i)).find(query) != std::string::npos)
            filtered.push_back(i);
    }
    constexpr int rows = 19;
    if (!closePrompt_ && !reloadPrompt_ && CheckCollisionPointRec(uiMouse(), {0, 190, 272, 610}))
        scroll_ -= int(GetMouseWheelMoveV().y * 3);
    scroll_ = std::clamp(scroll_, 0, std::max(0, int(filtered.size()) - rows));
    label(std::to_string(filtered.size()) + (palette_ ? " assets" : " objects"), 18, 196, 12, Muted);
    for (int row = 0; row < rows && size_t(row + scroll_) < filtered.size(); ++row) {
        const size_t id = filtered[size_t(row + scroll_)],
                     asset = palette_ ? id : document_.instances[id].asset;
        auto name = document_.assets[asset].label;
        if (name.starts_with("SM_"))
            name = name.substr(3);
        const bool chosen =
            palette_ ? (paletteSelection_ && *paletteSelection_ == id) : (selected_ && *selected_ == id);
        if (button(name, {14, 219 + float(row) * 29, 240, 26}, chosen)) {
            commitField();
            searchFocus_ = false;
            if (palette_)
                paletteSelection_ = id;
            else
                select(id);
        }
    }
    if (palette_) {
        if (button("Add at view center", {14, 799, 240, 33}, false, paletteSelection_.has_value()))
            addAsset(*paletteSelection_);
    } else if (button("Focus selection", {14, 799, 240, 33}, false, selected_.has_value()))
        focusSelection();
    label("INSPECTOR", 1132, 108, 13, Accent);
    label(selected_ ? document_.assets[document_.instances[*selected_].asset].label : "No object selected",
          1132, 136, 18, Text, 284);
    label(selected_ ? "Object #" + std::to_string(*selected_) : "Click a mesh or choose one in Scene.", 1132,
          166, 13, Muted, 284);
    if (button("Move  1", {1132, 201, 87, 31}, tool_ == Tool::Move))
        tool_ = Tool::Move;
    if (button("Rotate  2", {1225, 201, 87, 31}, tool_ == Tool::Rotate))
        tool_ = Tool::Rotate;
    if (button("Scale  3", {1318, 201, 100, 31}, tool_ == Tool::Scale))
        tool_ = Tool::Scale;
    for (int group = 0; group < 3; ++group) {
        const float y = 251 + float(group) * 87;
        label(group == 0 ? "POSITION" : group == 1 ? "ROTATION / DEGREES" : "SCALE", 1132, y, 12, Muted);
        const auto v = values(group);
        for (int axis = 0; axis < 3; ++axis) {
            const int id = group * 3 + axis;
            const float x = 1132 + float(axis) * 96;
            label(std::string(1, "XYZ"[axis]), x, y + 26, 13, AxisColors[size_t(axis)]);
            Rectangle r{x + 15, y + 19, 75, 30};
            panel(r, field_ == id ? Line : Background);
            label(field_ == id ? fieldText_
                  : selected_  ? number(component(v, axis))
                               : "--",
                  x + 20, y + 28, 13, Text, 64);
            if (selected_ && !closePrompt_ && !reloadPrompt_ && CheckCollisionPointRec(uiMouse(), r) &&
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                commitField();
                searchFocus_ = false;
                field_ = id;
                fieldText_ = number(component(v, axis));
                selectText_ = true;
            }
        }
    }
    if (button(snap_ ? "Snap: ON" : "Snap: OFF", {1132, 523, 137, 31}, snap_))
        snap_ = !snap_;
    label("0.5 m / 15 deg", 1281, 533, 12, Muted, 135);
    label(tool_ == Tool::Scale ? "Drag: uniform. Fields: per axis." : "Hold Shift to bypass snapping.", 1132,
          566, 13, Muted, 285);
    if (button("Duplicate", {1132, 599, 137, 33}, false, selected_.has_value()))
        duplicate();
    if (button("Delete", {1281, 599, 137, 33}, false, selected_.has_value()))
        remove();
    if (button(showGrid_ ? "Grid: ON" : "Grid: OFF", {1132, 654, 137, 31}, showGrid_))
        showGrid_ = !showGrid_;
    if (button(showNavigation_ ? "Paths: ON" : "Paths: OFF", {1281, 654, 137, 31}, showNavigation_))
        showNavigation_ = !showNavigation_;
    label("GAMEPLAY MARKERS", 1132, 709, 12, Accent);
    if (button("Place Arrival", {1132, 735, 137, 32}, marker_ == 1))
        marker_ = 1;
    if (button("Place Missions", {1281, 735, 137, 32}, marker_ == 2))
        marker_ = 2;
    label("Save rebuilds walkable ground.", 1132, 790, 13, Muted);
    label(marker_ ? "Click the street to place the marker. Escape cancels." : status, 18, 862, 14,
          marker_ ? Accent : Text, 1375);
    label("Ctrl+S save   Ctrl+Z / Ctrl+Y undo / redo   Ctrl+D duplicate   Delete remove   F4 exit", 18, 884,
          11, Muted, 1350);
    if (closePrompt_ || reloadPrompt_) {
        panel({0, 0, 1440, 900}, {7, 12, 16, 205});
        panel({420, 300, 600, 230}, Panel);
        label("Unsaved town changes", 448, 326, 26, Text);
        label(reloadPrompt_ ? "Reloading replaces your edits with the last saved town."
                            : "Save your changes before leaving the editor?",
              448, 377, 16, Muted, 544);
        // Modal buttons are deliberately separate from the blocked controls behind them.
        auto modal = [&](const std::string &text, Rectangle r) {
            const bool hover = CheckCollisionPointRec(uiMouse(), r);
            panel(r, hover ? Line : Background);
            label(text, r.x + 14, r.y + 13, 16, Text, r.width - 24);
            return hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        };
        if (!reloadPrompt_ && modal("Save & leave", {448, 448, 166, 46})) {
            if (save()) {
                closePrompt_ = false;
                closeNow();
            }
        }
        if (modal(reloadPrompt_ ? "Discard & reload" : "Discard & leave",
                  {reloadPrompt_ ? 448.0f : 630.0f, 448, 166, 46})) {
            if (reloadPrompt_) {
                reload();
                reloadPrompt_ = false;
            } else {
                closePrompt_ = false;
                closeNow();
            }
        }
        if (modal("Cancel", {814, 448, 178, 46})) {
            closePrompt_ = reloadPrompt_ = closingWindow_ = false;
        }
    }
}
} // namespace dw
