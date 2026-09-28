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
bool TownEditor::open(const std::filesystem::path &directory, Camera3D view,
                      const std::vector<AnimalPlacement> &legacyAnimals) {
    try {
        directory_ = directory;
        if (!scene_.load(directory))
            throw std::runtime_error("Could not load the town model and scene.");
        document_ = scene_.document();
        legacyAnimals_ = legacyAnimals;
        importLegacyAnimals();
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
        selectedCharacter_.reset();
        selectedStop_.reset();
        characterTab_ = false;
        animalTab_ = animalPalette_ = animalPlacement_ = replacingAnimal_ = false;
        selectedAnimal_.reset();
        characterPlacement_ = 0;
        paletteSelection_.reset();
        revision_ = savedRevision_ = nextRevision_ = 0;
        navigationRevision_ = 0;
        animationTab_ = false;
        resetPreview();
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
    return {document_, navigation_.spawn, navigation_.mission, selected_, selectedCharacter_, selectedStop_, selectedAnimal_, revision_};
}
void TownEditor::restore(Snapshot state) {
    document_ = std::move(state.document);
    navigation_.spawn = state.spawn;
    navigation_.mission = state.mission;
    selected_ = state.selected;
    selectedCharacter_ = state.character;
    selectedStop_ = state.stop;
    selectedAnimal_ = state.animal;
    animalPlacement_ = replacingAnimal_ = false;
    characterPlacement_ = 0;
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
        resetPreview();
    } catch (const std::exception &e) {
        const std::string error = e.what();
        if (!undo_.empty()) {
            auto previous = std::move(undo_.back());
            undo_.pop_back();
            restore(std::move(previous));
        } else {
            document_ = scene_.document();
            importLegacyAnimals();
        }
        status = "Change rejected: " + error;
    }
}
void TownEditor::select(std::optional<size_t> index) {
    selectedAnimal_.reset();
    animalPlacement_ = replacingAnimal_ = false;
    selectedCharacter_.reset();
    selectedStop_.reset();
    characterPlacement_ = 0;
    selected_ = index && *index < document_.instances.size() ? index : std::nullopt;
    field_ = dragAxis_ = -1;
}
Vector3 TownEditor::pivot() const {
    if (selectedAnimal_) return document_.animals[*selectedAnimal_].home;
    if (selectedCharacter_) return document_.characters[*selectedCharacter_].position;
    if (!selected_)
        return camera.target;
    const auto &m = document_.instances[*selected_].transform;
    return {m.m12, m.m13, m.m14};
}
void TownEditor::translate(Vector3 delta) {
    if (selectedAnimal_) { placeAnimal(add(pivot(), delta)); return; }
    if (selectedCharacter_) { placeCharacter(add(pivot(), delta)); return; }
    if (selectedGroup()) {
        status = "Detach this vehicle in Animation before changing its placement.";
        return;
    }
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
    if (selectedGroup())
        return;
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
    if (selectedGroup())
        return;
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
    if (selectedAnimal_) {
        if (document_.animals.size() >= 64) { status = "The town already has 64 animals."; return; }
        remember();
        auto copy = document_.animals[*selectedAnimal_];
        copy.id = document_.nextAnimalId();
        copy.seed += uint32_t(document_.animals.size() + 1);
        document_.animals.push_back(copy);
        selectAnimal(document_.animals.size() - 1);
        sync();
        animalPlacement_ = true;
        status = "Copy created. Click clear ground to place it.";
        return;
    }
    if (selectedCharacter_) {
        if (document_.characters.size() >= 64) return;
        remember();
        auto copy = document_.characters[*selectedCharacter_];
        copy.id = document_.nextCharacterId();
        document_.characters.push_back(copy);
        selectCharacter(document_.characters.size() - 1);
        sync();
        characterPlacement_ = 1;
        status = "Copy created. Click clear ground to place her.";
        return;
    }
    if (selectedGroup()) {
        status = "Detach the vehicle before duplicating its parts.";
        return;
    }
    if (!selected_)
        return;
    remember();
    auto copy = document_.instances[*selected_];
    copy.id = document_.nextInstanceId();
    copy.transform.m12 += 2;
    document_.instances.push_back(copy);
    selected_ = document_.instances.size() - 1;
    sync();
    status = "Object duplicated. Drag an axis handle to place it.";
}
void TownEditor::remove() {
    if (selectedAnimal_) {
        remember();
        document_.animals.erase(document_.animals.begin() + std::ptrdiff_t(*selectedAnimal_));
        selectAnimal({});
        sync();
        return;
    }
    if (selectedCharacter_) {
        remember();
        document_.characters.erase(document_.characters.begin() + std::ptrdiff_t(*selectedCharacter_));
        selectCharacter({});
        sync();
        return;
    }
    if (!selected_ || document_.instances.size() <= 1)
        return;
    remember();
    if (const auto *group = selectedGroup()) {
        const auto id = group->id;
        std::erase_if(document_.instances, [&](const auto &i) { return i.group == id; });
        std::erase_if(document_.groups, [&](const auto &g) { return g.id == id; });
    } else
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
    document_.instances.push_back({asset, MatrixTranslate(p.x, p.y, p.z), document_.nextInstanceId()});
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
        HubWorld ground;
        ground.setNavigation(nav);
        for (const auto &c : document_.characters) {
            auto previous = c.position;
            if (!ground.walkable(previous)) throw std::runtime_error(c.id + ": starting point is blocked.");
            auto stops = c.stops;
            if (c.loop && !stops.empty()) stops.push_back(c.position);
            for (const auto &stop : stops) {
                if (!ground.walkable(stop) || !ground.findRoute(previous, stop))
                    throw std::runtime_error(c.id + ": route crosses disconnected or blocked ground.");
                previous = stop;
            }
        }
        for (const auto &a : document_.animals)
            if (!validAnimalHome(a, ground))
                throw std::runtime_error(a.id + ": home overlaps scenery, the mission board or another animal.");
        saveTownProject(directory_, document_, nav);
        navigation_ = std::move(nav);
        navigationRevision_ = revision_;
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
        importLegacyAnimals();
        selectedAnimal_.reset();
        animalPlacement_ = replacingAnimal_ = false;
        navigation_ = std::move(nav);
        undo_.clear();
        redo_.clear();
        selected_.reset();
        selectedCharacter_.reset();
        selectedStop_.reset();
        characterPlacement_ = 0;
        field_ = -1;
        revision_ = savedRevision_ = ++nextRevision_;
        navigationRevision_ = revision_;
        resetPreview();
        status = "Reloaded the saved town.";
        return true;
    } catch (const std::exception &e) {
        status = e.what();
        return false;
    }
}
void TownEditor::focusSelection() {
    if (!selected_ && !selectedCharacter_ && !selectedAnimal_)
        return;
    const auto b = selectionBounds();
    camera.target = center(b);
    radius_ = std::clamp(length(sub(b.max, b.min)) * 1.7f, 5.0f, 300.0f);
    updateView();
}
Box TownEditor::selectionBounds() const {
    if (selectedAnimal_) return animalBounds_.at(*selectedAnimal_);
    if (selectedCharacter_) {
        const auto &definition = document_.characters[*selectedCharacter_];
        const auto p = characters_.residents().at(*selectedCharacter_).position;
        return {add(p, {-.4f * definition.scale, 0, -.4f * definition.scale}),
                add(p, {.4f * definition.scale, 1.9f * definition.scale, .4f * definition.scale})};
    }
    auto bounds = scene_.instanceBounds(*selected_);
    if (const auto *g = selectedGroup())
        for (size_t n = 0; n < document_.instances.size(); ++n)
            if (document_.instances[n].group == g->id) {
                const auto b = scene_.instanceBounds(n);
                bounds.min = Vector3Min(bounds.min, b.min);
                bounds.max = Vector3Max(bounds.max, b.max);
            }
    return bounds;
}
const TownMotionGroup *TownEditor::selectedGroup() const {
    if (!selected_)
        return nullptr;
    const auto &id = document_.instances[*selected_].group;
    for (const auto &g : document_.groups)
        if (g.id == id)
            return &g;
    return nullptr;
}
void TownEditor::detachVehicle() {
    const auto *group = selectedGroup();
    if (!group)
        return;
    const auto id = group->id;
    remember();
    for (auto &i : document_.instances)
        if (i.group == id) {
            i.group.clear();
            i.wheelRadius = 0;
        }
    std::erase_if(document_.groups, [&](const auto &g) { return g.id == id; });
    sync();
    status = "Vehicle detached at its authored placement. Its parts can now be edited.";
}
void TownEditor::setPathSettings(float speed, float acceleration, float dwell) {
    const auto *group = selectedGroup();
    if (!group)
        return;
    const auto id = group->path;
    remember();
    for (auto &p : document_.paths)
        if (p.id == id) {
            p.speed = speed;
            p.acceleration = acceleration;
            p.dwell = dwell;
        }
    sync();
}
void TownEditor::setMotion(ObjectMotion motion) {
    if (selectedGroup())
        return;
    if (!selected_)
        return;
    remember();
    document_.instances[*selected_].motion = motion;
    sync();
}
void TownEditor::resetPreview() {
    previewPlaying_ = false;
    preview_.reset(document_);
    scene_.applyAnimation(preview_);
    characterGround_.setNavigation(navigation_);
    characterGround_.setMovingSolids(preview_.solids());
    characters_.reset(document_, characterGround_);
    // Keep authored homes visible, even when a later scenery edit obstructs them.
    animals_.reset(document_.animals, characterGround_, false);
    animalBounds_.clear();
    for (const auto &a : animals_.residents()) animalBounds_.push_back(animalModels_.bounds(a));
    refreshCharacterRoute();
}
void TownEditor::setPreviewPlaying(bool playing) {
    commitField();
    if (playing && !previewPlaying_) {
        try {
            previewNavigation_ = navigation_;
            if (revision_ != navigationRevision_)
                previewNavigation_.bake(document_, scene_.model());
            characterGround_.setNavigation(previewNavigation_);
            characterGround_.setMovingSolids(preview_.solids());
            refreshCharacterRoute();
        } catch (const std::exception &e) {
            status = std::string("Preview failed: ") + e.what();
            return;
        }
        field_ = dragAxis_ = -1;
    }
    previewPlaying_ = playing;
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
    if (field_ >= 40 && selectedAnimal_) { commitAnimalField(); return; }
    if (field_ >= 32 && selectedCharacter_) {
        try {
            size_t end = 0;
            const float value = std::stof(fieldText_, &end);
            if (end != fieldText_.size() || !std::isfinite(value)) throw std::runtime_error("Enter a finite number.");
            auto c = document_.characters[*selectedCharacter_];
            if (field_ == 32) c.speed = value;
            if (field_ == 33) c.dwell = value;
            if (field_ == 34) c.scale = value;
            if (field_ == 35) c.yaw = value;
            field_ = -1;
            setCharacterSettings(c.speed, c.dwell, c.loop, c.scale, c.yaw);
        } catch (const std::exception &e) { status = e.what(); }
        field_ = -1;
        return;
    }
    if (field_ < 0 || !selected_)
        return;
    try {
        if (field_ >= 16) {
            size_t end = 0;
            const float value = std::stof(fieldText_, &end);
            if (end != fieldText_.size() || !std::isfinite(value))
                throw std::runtime_error("Enter a finite number.");
            if (const auto *g = selectedGroup()) {
                for (const auto &p : document_.paths)
                    if (p.id == g->path) {
                        const auto copy = p;
                        const int field = field_;
                        field_ = -1;
                        setPathSettings(field == 16 ? value : copy.speed,
                                        field == 17 ? value : copy.acceleration,
                                        field == 18 ? value : copy.dwell);
                        break;
                    }
            }
            field_ = -1;
            return;
        }
        if (selectedGroup()) {
            field_ = -1;
            return;
        }
        if (field_ >= 9) {
            auto motion = document_.instances[*selected_].motion;
            size_t end = 0;
            if (field_ == 12) {
                const auto seed = std::stoull(fieldText_, &end);
                if (end != fieldText_.size() || seed > UINT32_MAX || fieldText_.front() == '-')
                    throw std::runtime_error("Seed must be a whole number from 0 to 4294967295.");
                motion.seed = uint32_t(seed);
            } else {
                const float value = std::stof(fieldText_, &end);
                if (end != fieldText_.size() || !std::isfinite(value))
                    throw std::runtime_error("Enter a finite number.");
                if (field_ == 9)
                    motion.speed = value;
                if (field_ == 10)
                    motion.amplitude = value;
                if (field_ == 11)
                    motion.period = value;
                if (field_ == 13)
                    motion.pivot.x = value;
                if (field_ == 14)
                    motion.pivot.y = value;
                if (field_ == 15)
                    motion.pivot.z = value;
            }
            field_ = -1;
            setMotion(motion);
            return;
        }
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
    if (previewPlaying_) {
        preview_.update(std::min(dt, .1f), [&](Vector3 p) { return previewNavigation_.height(p); });
        scene_.applyAnimation(preview_);
        characterGround_.setMovingSolids(preview_.solids());
        characters_.update(std::min(dt, .1f), characterGround_);
        animals_.update(std::min(dt, .1f), characterGround_);
        for (size_t n = 0; n < animals_.residents().size(); ++n)
            animalBounds_[n] = animalModels_.bounds(animals_.residents()[n]);
    }
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
            } else if (animalPlacement_ || replacingAnimal_) {
                animalPlacement_ = replacingAnimal_ = false;
            } else if (characterPlacement_)
                characterPlacement_ = 0;
            else if (marker_)
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
        if (animalTab_) {
            if (animalPlacement_ && selectedAnimal_) {
                if (const auto point = characterGroundPoint(mouse)) placeAnimal(*point);
                else status = "Choose clear walkable ground for the animal.";
            } else {
                const auto ray = GetScreenToWorldRay(mouse, camera);
                float nearest = 1e9f;
                std::optional<size_t> hit;
                for (size_t n = 0; n < animalBounds_.size(); ++n) {
                    const auto &b = animalBounds_[n];
                    const auto collision = GetRayCollisionBox(ray, {b.min, b.max});
                    if (collision.hit && collision.distance < nearest) { nearest = collision.distance; hit = n; }
                }
                if (hit) { selectAnimal(hit); animalPalette_ = false; search_.clear(); scroll_ = 0; }
            }
            return;
        }
        if (characterPlacement_ && selectedCharacter_) {
            if (auto point = characterGroundPoint(mouse)) {
                if (characterPlacement_ == 1) { placeCharacter(*point); characterPlacement_ = 0; }
                else if (characterPlacement_ == 2) addCharacterStop(*point);
                else if (selectedStop_) { moveCharacterStop(*selectedStop_, *point); characterPlacement_ = 0; }
            } else status = "Choose walkable ground for the character or route stop.";
            return;
        }
        if (characterTab_) {
            const auto ray = GetScreenToWorldRay(mouse, camera);
            float nearest = 1e9f;
            std::optional<size_t> hit;
            for (size_t i = 0; i < characters_.residents().size(); ++i) {
                const auto &c = characters_.residents()[i];
                const float radius = .4f * c.definition.scale;
                auto collision = GetRayCollisionBox(ray, {add(c.position, {-radius, 0, -radius}),
                    add(c.position, {radius, 1.9f * c.definition.scale, radius})});
                if (collision.hit && collision.distance < nearest) { nearest = collision.distance; hit = i; }
            }
            if (hit) selectCharacter(hit);
            if (selectedCharacter_ && !hit) {
                const auto &stops = document_.characters[*selectedCharacter_].stops;
                for (size_t i = 0; i < stops.size(); ++i)
                    if (Vector2Distance(mouse, GetWorldToScreen(add(stops[i], {0, .15f, 0}), camera)) < 14)
                        selectedStop_ = i;
            }
            return;
        }
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
            if (selected_ && !selectedGroup() && preview_.time() == 0) {
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
    characterModels_.prepare(characters_);
    animalModels_.prepare(animals_);
    scene_.prepareLighting(camera, [&](Shader depth) {
        characterModels_.draw(characters_, depth);
        animalModels_.draw(animals_, depth);
    });
    postProcess_.begin({142, 174, 188, 255}, distance(camera.position, camera.target));
    BeginMode3D(camera);
    scene_.draw(camera.target);
    characterModels_.draw(characters_, scene_.actorShader(), scene_.shadowTexture());
    animalModels_.draw(animals_, scene_.actorShader(), scene_.shadowTexture());
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
    if (selected_ || selectedCharacter_ || selectedAnimal_) {
        const auto b = selectionBounds();
        DrawBoundingBox({b.min, b.max}, Teal);
        if (selected_ && !selectedGroup() && preview_.time() == 0) {
            const auto p = pivot();
            const float size = radius_ * .12f;
            rlDisableDepthTest();
            for (size_t i = 0; i < 3; ++i) {
                const auto end = add(p, mul(Axes[i], size));
                DrawCylinderEx(p, end, size * .012f, size * .012f, 8, AxisColors[i]);
                if (tool_ == Tool::Move)
                    DrawCylinderEx(end, add(end, mul(Axes[i], size * .15f)), size * .05f, 0, 8,
                                   AxisColors[i]);
                else if (tool_ == Tool::Scale)
                    DrawCube(end, size * .09f, size * .09f, size * .09f, AxisColors[i]);
                else
                    DrawSphereEx(end, size * .045f, 6, 8, AxisColors[i]);
            }
            rlEnableDepthTest();
        }
    }
    if (const auto *g = selectedGroup())
        for (const auto &p : document_.paths)
            if (p.id == g->path)
                for (size_t n = 0; n < p.points.size(); ++n)
                    DrawLine3D(add(p.points[n], {0, .45f, 0}),
                               add(p.points[(n + 1) % p.points.size()], {0, .45f, 0}), Teal);
    if (selectedCharacter_) {
        const auto &c = document_.characters[*selectedCharacter_];
        for (const auto &line : characterRoute_)
            DrawLine3D(add(line.from, {0, .15f, 0}), add(line.to, {0, .15f, 0}), line.valid ? Teal : RED);
        DrawSphere(add(c.position, {0, .15f, 0}), .18f, Accent);
        for (size_t i = 0; i < c.stops.size(); ++i)
            DrawSphere(add(c.stops[i], {0, .15f, 0}), selectedStop_ == i ? .24f : .16f, selectedStop_ == i ? Accent : Teal);
    }
    if (selectedAnimal_) {
        const auto &a = document_.animals[*selectedAnimal_];
        auto home = a.home;
        home.y = characterGround_.height(home) + .12f;
        const auto color = validAnimalHome(a, characterGround_) ? Teal : RED;
        DrawSphere(home, .15f, Accent);
        const float radius = std::max(.05f, a.roam);
        for (int n = 0; n < 64; ++n) {
            const float t = float(n) * 2 * Pi / 64, next = float(n + 1) * 2 * Pi / 64;
            auto p = add(home, {radius * std::cos(t), 0, radius * std::sin(t)});
            auto q = add(home, {radius * std::cos(next), 0, radius * std::sin(next)});
            const float py = characterGround_.height(p), qy = characterGround_.height(q);
            if (std::isfinite(py)) p.y = py + .12f;
            if (std::isfinite(qy)) q.y = qy + .12f;
            DrawLine3D(p, q, color);
        }
    }
    EndMode3D();
    postProcess_.end();
    drawUI();
}
void TownEditor::selectCharacter(std::optional<size_t> index) {
    selectedAnimal_.reset();
    animalPlacement_ = replacingAnimal_ = false;
    selected_.reset();
    selectedCharacter_ = index && *index < document_.characters.size() ? index : std::nullopt;
    selectedStop_.reset();
    field_ = dragAxis_ = -1;
    characterPlacement_ = 0;
    stopScroll_ = 0;
    refreshCharacterRoute();
}
void TownEditor::addCharacter() {
    if (document_.characters.size() >= 64) { status = "The town already has 64 characters."; return; }
    auto position = camera.target;
    if (!characterGround_.walkable(position)) position = navigation_.spawn;
    position.y = characterGround_.height(position);
    remember();
    TownCharacter c;
    c.id = document_.nextCharacterId();
    c.position = position;
    document_.characters.push_back(c);
    characterTab_ = true;
    selectCharacter(document_.characters.size() - 1);
    sync();
    characterPlacement_ = 1;
    status = "Cowgirl added. Click clear ground to choose her starting point.";
}
std::optional<Vector3> TownEditor::characterGroundPoint(Vector2 pixel) const {
    return characterGround_.pickGround(GetScreenToWorldRay(pixel, camera));
}
bool TownEditor::validCharacterStop(Vector3 point, std::optional<size_t> replacing) const {
    if (!selectedCharacter_ || !characterGround_.walkable(point)) return false;
    const auto &c = document_.characters[*selectedCharacter_];
    const size_t stop = replacing.value_or(c.stops.size());
    const auto previous = stop == 0 ? c.position : c.stops[stop - 1];
    if (distance(previous, point) < .1f || !characterGround_.findRoute(previous, point)) return false;
    if (stop + 1 < c.stops.size() &&
        (distance(c.stops[stop + 1], point) < .1f || !characterGround_.findRoute(point, c.stops[stop + 1]))) return false;
    return true;
}
void TownEditor::placeCharacter(Vector3 position) {
    if (!selectedCharacter_ || !characterGround_.walkable(position)) {
        status = "Place her on clear, walkable ground."; return;
    }
    const auto &c = document_.characters[*selectedCharacter_];
    if (!c.stops.empty() && (distance(c.stops.front(), position) < .1f || !characterGround_.findRoute(position, c.stops.front()))) {
        status = "The starting point must connect to the first route stop."; return;
    }
    position.y = characterGround_.height(position);
    remember();
    document_.characters[*selectedCharacter_].position = position;
    sync();
    status = "Starting point moved. The route stops keep their positions.";
}
void TownEditor::addCharacterStop(Vector3 position) {
    if (!selectedCharacter_) return;
    if (document_.characters[*selectedCharacter_].stops.size() >= 128) { status = "This route already has 128 stops."; return; }
    position.y = characterGround_.height(position);
    if (!validCharacterStop(position)) { status = "Choose a reachable stop, away from the previous stop."; return; }
    remember();
    auto &stops = document_.characters[*selectedCharacter_].stops;
    stops.push_back(position);
    selectedStop_ = stops.size() - 1;
    stopScroll_ = std::max(0, int(stops.size()) - 7);
    sync();
    status = "Stop added. Keep clicking the street to extend the route; Escape finishes.";
}
void TownEditor::moveCharacterStop(size_t stop, Vector3 position) {
    if (!selectedCharacter_ || stop >= document_.characters[*selectedCharacter_].stops.size()) return;
    position.y = characterGround_.height(position);
    if (!validCharacterStop(position, stop)) { status = "This stop must connect to its neighbors."; return; }
    remember();
    document_.characters[*selectedCharacter_].stops[stop] = position;
    sync();
    status = "Route stop moved.";
}
void TownEditor::removeCharacterStop(size_t stop) {
    if (!selectedCharacter_ || stop >= document_.characters[*selectedCharacter_].stops.size()) return;
    remember();
    auto &stops = document_.characters[*selectedCharacter_].stops;
    stops.erase(stops.begin() + std::ptrdiff_t(stop));
    selectedStop_.reset();
    sync();
}
void TownEditor::setCharacterSettings(float speed, float dwell, bool loop, float scale, float yaw) {
    if (!selectedCharacter_) return;
    if (!std::isfinite(speed) || speed < 0 || speed > 4 || !std::isfinite(dwell) || dwell < 0 || dwell > 120 ||
        !std::isfinite(scale) || scale < .25f || scale > 3 || !std::isfinite(yaw)) {
        status = "Speed: 0-4 m/s. Pause: 0-120 s. Size: 0.25-3."; return;
    }
    remember();
    auto &c = document_.characters[*selectedCharacter_];
    c.speed = speed; c.dwell = dwell; c.loop = loop; c.scale = scale; c.yaw = std::remainder(yaw, 360.f);
    sync();
}
void TownEditor::refreshCharacterRoute() {
    characterRoute_.clear();
    if (!selectedCharacter_ || *selectedCharacter_ >= document_.characters.size()) return;
    const auto &c = document_.characters[*selectedCharacter_];
    auto previous = c.position;
    auto destinations = c.stops;
    if (c.loop && !destinations.empty()) destinations.push_back(c.position);
    for (const auto &point : destinations) {
        const auto route = characterGround_.findRoute(previous, point);
        if (route) for (const auto &step : *route) {
            characterRoute_.push_back({previous, step, true}); previous = step;
        }
        else characterRoute_.push_back({previous, point, false});
        previous = point;
    }
}
void TownEditor::drawCharacterUI() {
    label("CHARACTER", 1132, 108, 13, Accent);
    if (!selectedCharacter_) {
        label("Choose or add a cowgirl", 1132, 140, 19, Text, 282);
        label("Use Add cowgirl in the left panel.", 1132, 192, 14, Muted, 282);
        label("Then place her and add route stops.", 1132, 224, 14, Muted, 282);
        return;
    }
    const auto c = document_.characters[*selectedCharacter_];
    label(c.id, 1132, 138, 20, Text, 284);
    label("Start: " + number(c.position.x) + ", " + number(c.position.z), 1132, 170, 13, Muted, 284);
    if (button("Place starting point", {1132, 194, 286, 31}, characterPlacement_ == 1)) {
        resetPreview(); characterPlacement_ = 1;
    }
    if (button("Add route stops", {1132, 233, 286, 31}, characterPlacement_ == 2)) {
        resetPreview(); characterPlacement_ = characterPlacement_ == 2 ? 0 : 2;
    }
    if (button("Move stop", {1132, 272, 137, 31}, characterPlacement_ == 3, selectedStop_.has_value())) {
        resetPreview(); characterPlacement_ = 3;
    }
    if (button("Remove stop", {1281, 272, 137, 31}, false, selectedStop_.has_value())) {
        removeCharacterStop(*selectedStop_); return;
    }
    if (button("Clear route", {1132, 311, 286, 31}, false, !c.stops.empty())) {
        remember(); document_.characters[*selectedCharacter_].stops.clear(); selectedStop_.reset(); sync(); return;
    }
    label("STOPS / scroll to see more", 1132, 351, 12, Accent);
    if (CheckCollisionPointRec(uiMouse(), {1132, 371, 286, 175})) stopScroll_ -= int(GetMouseWheelMoveV().y * 2);
    stopScroll_ = std::clamp(stopScroll_, 0, std::max(0, int(c.stops.size()) - 7));
    for (int row = 0; row < 7 && size_t(row + stopScroll_) < c.stops.size(); ++row) {
        const size_t index = size_t(row + stopScroll_);
        const auto p = c.stops[index];
        if (button(std::to_string(index + 1) + "  " + number(p.x) + ", " + number(p.z),
                   {1132, 371 + float(row) * 25, 286, 23}, selectedStop_ == index)) selectedStop_ = index;
    }
    if (c.stops.empty()) label("No stops: stays at the starting point.", 1132, 386, 13, Muted, 282);
    const std::array<const char *, 4> titles{"SPEED / m/s", "PAUSE / seconds", "SIZE", "FACING / degrees"};
    const std::array<float, 4> values{c.speed, c.dwell, c.scale, c.yaw};
    for (int i = 0; i < 4; ++i) {
        const float x = 1132 + float(i % 2) * 149, y = 553 + float(i / 2) * 60;
        label(titles[size_t(i)], x, y, 12, Muted);
        const Rectangle box{x, y + 18, 137, 31};
        panel(box, field_ == i + 32 ? Line : Background);
        label(field_ == i + 32 ? fieldText_ : number(values[size_t(i)]), x + 10, y + 27, 14, Text, 120);
        if (!closePrompt_ && !reloadPrompt_ && CheckCollisionPointRec(uiMouse(), box) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            commitField(); searchFocus_ = false; field_ = i + 32; fieldText_ = number(values[size_t(i)]); selectText_ = true;
        }
    }
    if (button(c.loop ? "Route: Loop" : "Route: Back and forth", {1132, 675, 286, 31}))
        setCharacterSettings(c.speed, c.dwell, !c.loop, c.scale, c.yaw);
    if (button(previewPlaying_ ? "Pause preview" : "Play preview", {1132, 714, 137, 31}, previewPlaying_))
        setPreviewPlaying(!previewPlaying_);
    if (button("Reset preview", {1281, 714, 137, 31})) resetPreview();
    if (button("Focus", {1132, 753, 137, 31})) focusSelection();
    if (button("Duplicate", {1281, 753, 137, 31})) { duplicate(); return; }
    if (button("Delete character", {1132, 792, 286, 31})) remove();
}
void TownEditor::drawAnimationUI() {
    const auto motion = selected_ ? document_.instances[*selected_].motion : ObjectMotion{};
    const auto *selected = selectedGroup();
    const auto groupValue = selected ? std::optional<TownMotionGroup>(*selected) : std::nullopt;
    const auto *group = groupValue ? &*groupValue : nullptr;
    label(group ? "RAIL VEHICLE" : "MOTION PRESET", 1132, 207, 12, Accent);
    for (int n = 0; !group && n < 4; ++n) {
        const auto kind = ObjectMotionKind(n);
        if (button(motionName(kind), {1132 + float(n % 2) * 149, 232 + float(n / 2) * 38, 137, 31},
                   motion.kind == kind, selected_.has_value())) {
            ObjectMotion next;
            next.kind = kind;
            next.seed = motion.seed;
            if (kind == ObjectMotionKind::Spin)
                next.speed = 30;
            if (kind == ObjectMotionKind::Sway) {
                next.speed = 1;
                next.amplitude = 8;
                next.period = 4;
                next.axis = {0, 0, 1};
            }
            commitField();
            setMotion(next);
        }
    }
    auto field = [&](int id, const std::string &caption, const std::string &value, float y) {
        label(caption, 1132, y + 9, 13, Muted, 145);
        const Rectangle box{1281, y, 137, 31};
        panel(box, field_ == id ? Line : Background);
        label(field_ == id ? fieldText_ : value, 1290, y + 9, 13, Text, 119);
        if (selected_ && !closePrompt_ && !reloadPrompt_ && CheckCollisionPointRec(uiMouse(), box) &&
            IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            commitField();
            searchFocus_ = false;
            field_ = id;
            fieldText_ = value;
            selectText_ = true;
        }
    };
    if (group) {
        label(group->id, 1132, 241, 15, Text, 284);
        label("All parts follow the rail route.", 1132, 274, 13, Muted, 284);
        for (const auto &p : document_.paths)
            if (p.id == group->path) {
                const auto settings = p;
                field(16, "Travel speed", number(settings.speed), 321);
                field(17, "Acceleration", number(settings.acceleration), 367);
                field(18, "Station wait / sec", number(settings.dwell), 413);
                break;
            }
        label("Settings affect both trains on this loop.", 1132, 465, 12, Muted, 284);
        label("Wheels turn with travel; carriages follow.", 1132, 496, 12, Muted, 284);
        if (button("Detach vehicle", {1132, 556, 286, 34})) {
            detachVehicle();
            return;
        }
        label("Detaches every part at the original stop.", 1132, 609, 12, Muted, 284);
    } else if (selected_ && motion.kind != ObjectMotionKind::None) {
        field(9,
              motion.kind == ObjectMotionKind::Spin   ? "Degrees / sec"
              : motion.kind == ObjectMotionKind::Sway ? "Playback speed"
                                                      : "Travel speed",
              number(motion.speed), 321);
        if (motion.kind != ObjectMotionKind::Spin) {
            field(10, motion.kind == ObjectMotionKind::Sway ? "Swing degrees" : "Bounce height",
                  number(motion.amplitude), 367);
            field(11, motion.kind == ObjectMotionKind::Sway ? "Period / sec" : "Gust period / sec",
                  number(motion.period), 413);
        }
        if (motion.kind == ObjectMotionKind::Tumbleweed) {
            field(12, "Wind seed", std::to_string(motion.seed), 459);
            label("Roll follows travel and ground.", 1132, 514, 13, Muted, 284);
            label("Each copy gets its own wind.", 1132, 544, 13, Muted, 284);
        } else {
            label("LOCAL ROTATION AXIS", 1132, 465, 12, Accent);
            for (size_t axis = 0; axis < Axes.size(); ++axis)
                if (button(std::string(1, "XYZ"[axis]), {1132 + float(axis) * 96, 490, 90, 31},
                           distance(motion.axis, Axes[axis]) < .001f)) {
                    auto next = motion;
                    next.axis = Axes[axis];
                    setMotion(next);
                }
            field(13, "Local pivot X", number(motion.pivot.x), 537);
            field(14, "Local pivot Y", number(motion.pivot.y), 574);
            field(15, "Local pivot Z", number(motion.pivot.z), 611);
        }
    }
    if (button(previewPlaying_ ? "Pause preview" : "Play preview", {1132, 683, 137, 32}, previewPlaying_)) {
        const bool play = !previewPlaying_;
        commitField();
        setPreviewPlaying(play);
    }
    if (button("Reset preview", {1281, 683, 137, 32}))
        resetPreview();
    label("Preview " + number(float(preview_.time())) + " sec", 1132, 736, 13, Muted, 284);
    label(group ? "Trains are solid and stop for the player." : "Animated props do not block walking.", 1132,
          771, 12, Muted, 284);
    label(group ? "Route and vehicle placement are linked." : "Reset preview to edit placement.", 1132, 798,
          12, Muted, 284);
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
    auto tab = [&](const char *name, Rectangle box, bool active, int kind) {
        if (!button(name, box, active)) return;
        commitField(); select({}); search_.clear(); searchFocus_ = false; scroll_ = 0; marker_ = 0;
        animalTab_ = kind == 3; characterTab_ = kind == 2; palette_ = kind == 1;
        if (characterTab_) selectCharacter(document_.characters.empty() ? std::nullopt : std::optional<size_t>(0));
        if (animalTab_) {
            animalPalette_ = document_.animals.empty();
            selectAnimal(document_.animals.empty() ? std::nullopt : std::optional<size_t>(0));
        }
    };
    tab("Scene", {14, 103, 115, 31}, !palette_ && !characterTab_ && !animalTab_, 0);
    tab("Assets", {139, 103, 115, 31}, palette_ && !characterTab_ && !animalTab_, 1);
    tab("People", {14, 142, 115, 31}, characterTab_, 2);
    tab("Animals", {139, 142, 115, 31}, animalTab_, 3);
    const Rectangle searchBox{14, 188, 240, 33};
    panel(searchBox, searchFocus_ ? Line : Background);
    label(search_.empty() ? (animalTab_ ? "Search animals..." : "Search objects...") : search_, 24, 198, 14, search_.empty() ? Muted : Text, 218);
    if (!closePrompt_ && !reloadPrompt_ && CheckCollisionPointRec(uiMouse(), searchBox) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        commitField();
        searchFocus_ = true;
        selectText_ = true;
    }
    if (animalTab_) drawAnimalPalette();
    else {
        std::vector<size_t> filtered;
        const auto query = lower(search_);
        const size_t count = characterTab_ ? document_.characters.size() : palette_ ? document_.assets.size() : document_.instances.size();
        for (size_t i = 0; i < count; ++i) {
            if (characterTab_) {
                if (lower(document_.characters[i].id + " cowgirl").find(query) != std::string::npos) filtered.push_back(i);
                continue;
            }
            const auto asset = palette_ ? i : document_.instances[i].asset;
            if (lower(document_.assets[asset].label + " #" + std::to_string(i)).find(query) != std::string::npos)
                filtered.push_back(i);
        }
        constexpr int rows = 18;
        if (!closePrompt_ && !reloadPrompt_ && CheckCollisionPointRec(uiMouse(), {0, 235, 272, 545}))
            scroll_ -= int(GetMouseWheelMoveV().y * 3);
        scroll_ = std::clamp(scroll_, 0, std::max(0, int(filtered.size()) - rows));
        label(std::to_string(filtered.size()) + (characterTab_ ? " characters" : palette_ ? " assets" : " objects"), 18, 235, 12, Muted);
        for (int row = 0; row < rows && size_t(row + scroll_) < filtered.size(); ++row) {
            if (characterTab_) {
                const auto id = filtered[size_t(row + scroll_)];
                if (button(document_.characters[id].id, {14, 258 + float(row) * 29, 240, 26}, selectedCharacter_ == id)) {
                    commitField(); searchFocus_ = false; selectCharacter(id);
                }
                continue;
            }
            const size_t id = filtered[size_t(row + scroll_)],
                         asset = palette_ ? id : document_.instances[id].asset;
            auto name = document_.assets[asset].label;
            if (name.starts_with("SM_"))
                name = name.substr(3);
            const bool chosen =
                palette_ ? (paletteSelection_ && *paletteSelection_ == id) : (selected_ && *selected_ == id);
            if (button(name, {14, 258 + float(row) * 29, 240, 26}, chosen)) {
                commitField();
                searchFocus_ = false;
                if (palette_)
                    paletteSelection_ = id;
                else
                    select(id);
            }
        }
        if (characterTab_) {
            if (button("Add cowgirl", {14, 799, 240, 33}, false, document_.characters.size() < 64)) addCharacter();
        } else if (palette_) {
            if (button("Add at view center", {14, 799, 240, 33}, false, paletteSelection_.has_value()))
                addAsset(*paletteSelection_);
        } else if (button("Focus selection", {14, 799, 240, 33}, false, selected_.has_value()))
            focusSelection();
    }
    if (animalTab_) drawAnimalUI();
    else if (characterTab_) drawCharacterUI();
    else {
    label("INSPECTOR", 1132, 108, 13, Accent);
    label(selected_ ? document_.assets[document_.instances[*selected_].asset].label : "No object selected",
          1132, 136, 18, Text, 284);
    if (button("Transform", {1132, 164, 137, 28}, !animationTab_)) {
        commitField();
        animationTab_ = false;
    }
    if (button("Animation", {1281, 164, 137, 28}, animationTab_)) {
        commitField();
        animationTab_ = true;
    }
    if (animationTab_)
        drawAnimationUI();
    else {
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
        label(tool_ == Tool::Scale ? "Drag: uniform. Fields: per axis." : "Hold Shift to bypass snapping.",
              1132, 566, 13, Muted, 285);
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
    }
    }
    label(animalPlacement_ ? "Click clear ground to place the animal. Escape finishes placement." : characterPlacement_ ? "Click walkable ground. Escape finishes placing route stops." : marker_ ? "Click the street to place the marker. Escape cancels." : status, 18, 862, 14,
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
