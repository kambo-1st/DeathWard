#include "editor/TownEditor.hpp"
#include "raymath.h"
#include <cctype>
#include <iomanip>
#include <sstream>

namespace dw {
namespace {
constexpr Color Background{19, 25, 29, 255}, Line{52, 64, 68, 255}, Text{232, 230, 217, 255},
    Muted{152, 165, 164, 255}, Accent{232, 174, 96, 255};
std::string number(float value) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << value;
    return out.str();
}
std::string animalLabel(AnimalKind kind) {
    std::string result = animalName(kind);
    bool initial = true;
    for (auto &c : result) {
        if (c == '_') c = ' ';
        else if (initial) c = char(std::toupper(static_cast<unsigned char>(c)));
        initial = c == ' ';
    }
    return result;
}
std::string lower(std::string value) {
    for (auto &c : value) c = char(std::tolower(static_cast<unsigned char>(c)));
    return value;
}
} // namespace
void TownEditor::importLegacyAnimals() {
    if (!document_.ownsAnimals) {
        document_.animals = legacyAnimals_;
        document_.ownsAnimals = true;
    }
}
void TownEditor::selectAnimal(std::optional<size_t> index) {
    selected_.reset(); selectedCharacter_.reset(); selectedStop_.reset();
    selectedAnimal_ = index && *index < document_.animals.size() ? index : std::nullopt;
    if (selectedAnimal_) animalKind_ = document_.animals[*selectedAnimal_].kind;
    animalClipChoice_ = 0;
    field_ = dragAxis_ = -1;
    characterPlacement_ = 0;
    animalPlacement_ = replacingAnimal_ = false;
    refreshCharacterRoute();
}
bool TownEditor::validAnimalHome(const AnimalPlacement &animal, const HubWorld &ground) const {
    if (!Animals::clearFootprint(animal, animal.home, ground)) return false;
    for (const auto &other : document_.animals) {
        if (other.id == animal.id) continue;
        auto delta = sub(other.home, animal.home);
        delta.y = 0;
        if (length(delta) < animalRadius(animal.kind) * animal.scale +
                            animalRadius(other.kind) * other.scale + .15f) return false;
    }
    return true;
}
void TownEditor::addAnimal(AnimalKind kind) {
    commitField();
    if (document_.animals.size() >= 64) { status = "The town already has 64 animals."; return; }
    if (size_t(kind) >= size_t(AnimalKind::Count)) return;
    AnimalPlacement animal;
    animal.kind = kind;
    animal.id = document_.nextAnimalId();
    animal.seed = uint32_t(18661 + document_.animals.size() * 7919 + nextRevision_);
    bool found = false;
    for (int ring = 0; ring <= 40 && !found; ++ring)
        for (int n = 0; n < (ring ? 32 : 1); ++n) {
            const float angle = float(n) * 2 * Pi / 32;
            animal.home = add(camera.target, {ring * .5f * std::cos(angle), 0, ring * .5f * std::sin(angle)});
            if (validAnimalHome(animal, characterGround_)) { found = true; break; }
        }
    if (!found) { status = "No room for this animal nearby. Move the view to a more open area."; return; }
    animal.home.y = 0; // Scene records store X/Z; terrain supplies the height.
    remember();
    document_.animals.push_back(animal);
    selectAnimal(document_.animals.size() - 1);
    animalTab_ = true; characterTab_ = palette_ = animalPalette_ = false;
    animalAnimationTab_ = false;
    search_.clear(); scroll_ = 0;
    sync();
    animalPlacement_ = true;
    status = "Animal added. Click clear ground to choose its home.";
}
void TownEditor::placeAnimal(Vector3 position) {
    if (!selectedAnimal_) return;
    auto animal = document_.animals[*selectedAnimal_];
    animal.home = position;
    if (!std::isfinite(position.x) || !std::isfinite(position.z) ||
        std::abs(position.x) > 10000 || std::abs(position.z) > 10000 ||
        !validAnimalHome(animal, characterGround_)) {
        status = "Choose room for the whole animal, away from scenery and other homes.";
        return;
    }
    animal.home.y = 0;
    remember();
    document_.animals[*selectedAnimal_] = animal;
    sync();
    animalPlacement_ = false;
    status = "Animal home placed. Save to use it in town.";
}
void TownEditor::setAnimalSettings(float scale, float roam, float yaw, uint32_t seed) {
    if (!selectedAnimal_) return;
    auto animal = document_.animals[*selectedAnimal_];
    animal.scale = scale; animal.roam = roam; animal.yaw = yaw; animal.seed = seed;
    try { validateAnimalPlacements({animal}); }
    catch (const std::exception &) { status = "Size must be 0.25–3, roaming radius 0–20 m, and facing finite."; return; }
    if (scale != document_.animals[*selectedAnimal_].scale && !validAnimalHome(animal, characterGround_)) {
        status = "This size needs more clear ground. Move the home first."; return;
    }
    animal.yaw = std::remainder(yaw, 360.f);
    remember();
    document_.animals[*selectedAnimal_] = animal;
    sync();
    status = "Animal settings updated.";
}
void TownEditor::setAnimalSpecies(AnimalKind kind) {
    if (!selectedAnimal_ || size_t(kind) >= size_t(AnimalKind::Count)) return;
    auto animal = document_.animals[*selectedAnimal_];
    animal.kind = kind;
    const auto &clips = animalModels_.clipNames(kind);
    std::erase_if(animal.activity.clips, [&](const auto &clip) {
        return std::find(clips.begin(), clips.end(), clip) == clips.end();
    });
    if (!validAnimalHome(animal, characterGround_)) {
        status = "This species needs more room. Move the home or reduce its size first."; return;
    }
    remember();
    document_.animals[*selectedAnimal_] = animal;
    animalKind_ = kind;
    animalClipChoice_ = 0;
    animalPalette_ = replacingAnimal_ = false;
    search_.clear(); scroll_ = 0;
    sync();
    status = "Animal species updated.";
}
void TownEditor::setAnimalActivity(AnimalActivity activity) {
    if (!selectedAnimal_) return;
    auto animal = document_.animals[*selectedAnimal_];
    if (animal.activity == activity) return;
    animal.activity = activity;
    try { validateAnimalPlacements({animal}); }
    catch (const std::exception &e) { status = e.what(); return; }
    const auto &available = animalModels_.clipNames(animal.kind);
    for (const auto &clip : activity.clips)
        if (std::find(available.begin(), available.end(), clip) == available.end()) {
            status = "This animal does not have that animation.";
            return;
        }
    remember();
    document_.animals[*selectedAnimal_].activity = std::move(activity);
    sync();
    status = "Animal activity updated. Play preview to watch it.";
}
void TownEditor::dragAnimal(Vector2 mouse, bool shift) {
    const std::array<Vector3, 3> axes{{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
    const auto axis = axes[size_t(dragAxis_)];
    const float size = radius_ * .12f;
    const auto from = GetWorldToScreen(dragAnimalPivot_, camera);
    const auto to = GetWorldToScreen(add(dragAnimalPivot_, mul(axis, size)), camera);
    const auto screen = Vector2Subtract(to, from);
    const float pixels = Vector2DotProduct(Vector2Subtract(mouse, dragMouse_), Vector2Normalize(screen));
    auto next = dragAnimal_;
    if (tool_ == Tool::Move) {
        float amount = pixels / std::max(1.f, Vector2Length(screen)) * size;
        if (snap_ && !shift) amount = std::round(amount / .5f) * .5f;
        next.home = add(next.home, mul(axis, amount));
    } else if (tool_ == Tool::Rotate) {
        float angle = pixels * .8f;
        if (snap_ && !shift) angle = std::round(angle / 15) * 15;
        next.yaw = std::remainder(next.yaw + angle, 360.f);
    } else {
        float factor = std::exp(pixels * .01f);
        if (snap_ && !shift) factor = std::max(.1f, std::round(factor * 10) / 10);
        next.scale = std::clamp(next.scale * factor, .25f, 3.f);
    }
    const auto &current = document_.animals[*selectedAnimal_];
    if (distance(current.home, next.home) < .00001f && current.yaw == next.yaw && current.scale == next.scale) return;
    if (!validAnimalHome(next, characterGround_)) {
        status = "Move toward clear ground; the animal needs room beside scenery.";
        return;
    }
    if (!dragChanged_) { remember(); dragChanged_ = true; }
    document_.animals[*selectedAnimal_] = next;
    sync();
    status = "Animal moved. Save to use this placement in town.";
}
void TownEditor::commitAnimalField() {
    try {
        const auto animal = document_.animals[*selectedAnimal_];
        const int field = field_;
        field_ = -1;
        size_t end = 0;
        if (field == 43) {
            const auto seed = std::stoull(fieldText_, &end);
            if (end != fieldText_.size() || seed > UINT32_MAX || fieldText_.front() == '-')
                throw std::runtime_error("Seed must be a whole number from 0 to 4294967295.");
            setAnimalSettings(animal.scale, animal.roam, animal.yaw, uint32_t(seed));
        } else {
            const float value = std::stof(fieldText_, &end);
            if (end != fieldText_.size() || !std::isfinite(value)) throw std::runtime_error("Enter a finite number.");
            if (field == 44 || field == 45) {
                auto home = animal.home;
                if (field == 44) home.x = value; else home.z = value;
                placeAnimal(home);
            } else if (field == 46) {
                auto activity = animal.activity;
                activity.speed = value;
                setAnimalActivity(activity);
            } else
                setAnimalSettings(field == 40 ? value : animal.scale, field == 41 ? value : animal.roam,
                                  field == 42 ? value : animal.yaw, animal.seed);
        }
    } catch (const std::exception &e) { status = e.what(); }
    field_ = -1;
}
void TownEditor::drawAnimalPalette() {
    auto mode = [&](bool catalog) {
        commitField(); animalPalette_ = catalog; replacingAnimal_ = animalPlacement_ = false;
        scroll_ = 0; search_.clear(); searchFocus_ = false;
    };
    if (button("In town", {14, 231, 115, 28}, !animalPalette_)) mode(false);
    if (button("Species", {139, 231, 115, 28}, animalPalette_)) mode(true);
    std::vector<size_t> filtered;
    const auto query = lower(search_);
    const size_t count = animalPalette_ ? size_t(AnimalKind::Count) : document_.animals.size();
    for (size_t i = 0; i < count; ++i) {
        const auto kind = animalPalette_ ? AnimalKind(i) : document_.animals[i].kind;
        const auto name = animalLabel(kind) + " " + animalName(kind) +
                          (animalPalette_ ? "" : " " + document_.animals[i].id);
        if (lower(name).find(query) != std::string::npos) filtered.push_back(i);
    }
    constexpr int rows = 17;
    if (!closePrompt_ && !reloadPrompt_ && CheckCollisionPointRec(uiMouse(), {0, 290, 272, 491}))
        scroll_ -= int(GetMouseWheelMoveV().y * 3);
    scroll_ = std::clamp(scroll_, 0, std::max(0, int(filtered.size()) - rows));
    label(std::to_string(filtered.size()) + (animalPalette_ ? " animal variants" : " animals in town"), 18, 272, 12, Muted);
    for (int row = 0; row < rows && size_t(row + scroll_) < filtered.size(); ++row) {
        const auto index = filtered[size_t(row + scroll_)];
        const auto name = animalPalette_ ? animalLabel(AnimalKind(index)) : document_.animals[index].id;
        const bool selected = animalPalette_ ? size_t(animalKind_) == index : selectedAnimal_ == index;
        if (button(name, {14, 290 + float(row) * 29, 240, 26}, selected)) {
            commitField(); searchFocus_ = false;
            if (animalPalette_) animalKind_ = AnimalKind(index);
            else selectAnimal(index);
        }
    }
    if (animalPalette_) {
        if (button(replacingAnimal_ ? "Apply species" : "Add animal", {14, 799, 240, 33}, false,
                   replacingAnimal_ || document_.animals.size() < 64)) {
            if (replacingAnimal_) setAnimalSpecies(animalKind_);
            else addAnimal(animalKind_);
        }
    } else if (button("Browse species", {14, 799, 240, 33})) mode(true);
}
void TownEditor::drawAnimalUI() {
    label("ANIMAL", 1132, 108, 13, Accent);
    if (animalPalette_) {
        label("Chosen: " + animalLabel(animalKind_), 1132, 139, 19, Text, 284);
        label(replacingAnimal_ ? "Apply species to the selected animal." : "Add animal, then click its home on the ground.",
              1132, 175, 13, Muted, 284);
    } else if (selectedAnimal_) {
        label(animalLabel(document_.animals[*selectedAnimal_].kind), 1132, 139, 20, Text, 284);
        label(document_.animals[*selectedAnimal_].id, 1132, 175, 13, Muted, 284);
    } else {
        label("Choose or add an animal", 1132, 139, 19, Text, 284);
        label("Browse Species to choose from 98 variants.", 1132, 184, 13, Muted, 284);
    }
    if (!selectedAnimal_) {
        label("Animals roam around the home you place.", 1132, 247, 13, Muted, 284);
        label("Birds and aquatic species also use ground.", 1132, 280, 13, Muted, 284);
        return;
    }
    const auto animal = document_.animals[*selectedAnimal_];
    if (button("Transform", {1132, 201, 137, 28}, !animalAnimationTab_)) {
        commitField(); animalAnimationTab_ = false;
    }
    if (button("Animation", {1281, 201, 137, 28}, animalAnimationTab_)) {
        commitField(); animalAnimationTab_ = true;
    }
    auto field = [&](int id, const std::string &value, Rectangle box) {
        panel(box, field_ == id ? Line : Background);
        label(field_ == id ? fieldText_ : value, box.x + 10, box.y + 9, 14, Text, box.width - 17);
        if (!closePrompt_ && !reloadPrompt_ && CheckCollisionPointRec(uiMouse(), box) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            commitField(); searchFocus_ = false; field_ = id; fieldText_ = value; selectText_ = true;
        }
    };
    if (!animalAnimationTab_) {
        if (button("Move home", {1132, 244, 137, 31}, animalPlacement_)) {
            commitField(); resetPreview(); animalPlacement_ = true;
        }
        if (button("Change species", {1281, 244, 137, 31})) {
            commitField(); animalPalette_ = replacingAnimal_ = true; animalPlacement_ = false;
            animalKind_ = animal.kind; search_.clear(); scroll_ = 0; searchFocus_ = false;
        }
        const std::array<const char *, 3> tools{"Move  1", "Rotate  2", "Scale  3"};
        for (int i = 0; i < 3; ++i)
            if (button(tools[size_t(i)], {1132 + i * 96.f, 281, 94, 24}, int(tool_) == i)) {
                commitField(); resetPreview(); animalPlacement_ = false; tool_ = Tool(i);
            }
        const std::array<const char *, 6> captions{"SIZE", "ROAMING RADIUS / m", "FACING / degrees", "ROAMING SEED", "POSITION X", "POSITION Z"};
        const std::array<std::string, 6> values{number(animal.scale), number(animal.roam), number(animal.yaw),
            std::to_string(animal.seed), number(animal.home.x), number(animal.home.z)};
        for (int i = 0; i < 6; ++i) {
            const float x = 1132 + float(i % 2) * 149, y = i < 4 ? 310 + float(i / 2) * 72 : 465;
            label(captions[size_t(i)], x, y, 11, Muted, 138);
            field(40 + i, values[size_t(i)], {x, y + 22, 137, 31});
        }
        const bool valid = validAnimalHome(animal, characterGround_);
        label(valid ? "Ground height follows the terrain." : "Home blocked: move it before saving.",
              1132, 532, 13, valid ? Muted : Accent, 284);
        if (button(snap_ ? "Snap: ON" : "Snap: OFF", {1132, 552, 137, 27}, snap_)) snap_ = !snap_;
        label("Shift: free drag", 1281, 560, 12, Muted, 135);
    } else {
        auto activity = animal.activity;
        if (button(activity.stationary ? "Movement: Stay in place" : "Movement: Roam",
                   {1132, 244, 286, 31}, activity.stationary)) {
            commitField(); activity.stationary = !activity.stationary; setAnimalActivity(activity);
        }
        const auto &clips = animalModels_.clipNames(animal.kind);
        label("AVAILABLE ANIMATION", 1132, 292, 12, Muted, 284);
        if (!clips.empty()) {
            animalClipChoice_ %= clips.size();
            if (button("<", {1132, 318, 32, 31})) animalClipChoice_ = (animalClipChoice_ + clips.size() - 1) % clips.size();
            if (button(">", {1386, 318, 32, 31})) animalClipChoice_ = (animalClipChoice_ + 1) % clips.size();
            label(clips[animalClipChoice_], 1173, 327, 14, Text, 207);
            if (button("Add to loop", {1132, 359, 137, 31}, false, activity.clips.size() < AnimalActivity::MaxClips)) {
                commitField(); activity.stationary = true;
                activity.clips.push_back(clips[animalClipChoice_]); setAnimalActivity(activity);
            }
        } else label("No animations loaded", 1132, 327, 14, Muted, 284);
        if (button("Idle only", {1281, 359, 137, 31})) {
            commitField(); activity.stationary = true; activity.clips.clear(); setAnimalActivity(activity);
        }
        label("LOOP SEQUENCE / up to 4 clips", 1132, 403, 12, Accent, 284);
        if (activity.clips.empty()) label("Idle", 1132, 432, 14, Muted, 240);
        for (size_t n = 0; n < activity.clips.size(); ++n) {
            const float y = 424 + float(n) * 32;
            label(std::to_string(n + 1) + ". " + activity.clips[n], 1132, y + 8, 14, Text, 244);
            if (button("X", {1386, y, 32, 28})) {
                commitField(); activity.clips.erase(activity.clips.begin() + n); setAnimalActivity(activity); break;
            }
        }
        label("PLAYBACK SPEED", 1132, 564, 12, Muted, 138);
        field(46, number(activity.speed), {1281, 555, 137, 27});
    }
    if (button(previewPlaying_ ? "Pause preview" : "Play preview", {1132, 588, 137, 33}, previewPlaying_))
        setPreviewPlaying(!previewPlaying_);
    if (button("Reset preview", {1281, 588, 137, 33})) resetPreview();
    label("Preview " + number(float(animals_.time())) + " sec", 1132, 644, 13, Muted, 284);
    label(animal.activity.stationary ? "Stays in place; loops the chosen clips." : "Radius 0 also keeps roaming animals at home.",
          1132, 665, 12, Muted, 284);
    if (button("Focus", {1132, 694, 137, 33})) focusSelection();
    if (button("Duplicate", {1281, 694, 137, 33})) { duplicate(); return; }
    if (button("Delete animal", {1132, 747, 286, 33})) remove();
}
} // namespace dw
