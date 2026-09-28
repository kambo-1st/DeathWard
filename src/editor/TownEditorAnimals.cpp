#include "editor/TownEditor.hpp"
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
    if (!validAnimalHome(animal, characterGround_)) {
        status = "This species needs more room. Move the home or reduce its size first."; return;
    }
    remember();
    document_.animals[*selectedAnimal_] = animal;
    animalKind_ = kind;
    animalPalette_ = replacingAnimal_ = false;
    search_.clear(); scroll_ = 0;
    sync();
    status = "Animal species updated.";
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
    label("Home: " + number(animal.home.x) + ", " + number(animal.home.z), 1132, 214, 13, Muted, 284);
    if (button("Place home", {1132, 244, 137, 31}, animalPlacement_)) {
        commitField(); resetPreview(); animalPlacement_ = true;
    }
    if (button("Change species", {1281, 244, 137, 31})) {
        commitField(); animalPalette_ = replacingAnimal_ = true; animalPlacement_ = false;
        animalKind_ = animal.kind; search_.clear(); scroll_ = 0; searchFocus_ = false;
    }
    const std::array<const char *, 4> captions{"SIZE", "ROAMING RADIUS / m", "FACING / degrees", "ROAMING SEED"};
    const std::array<std::string, 4> values{number(animal.scale), number(animal.roam), number(animal.yaw), std::to_string(animal.seed)};
    for (int i = 0; i < 4; ++i) {
        const float x = 1132 + float(i % 2) * 149, y = 310 + float(i / 2) * 72;
        label(captions[size_t(i)], x, y, 11, Muted, 138);
        const Rectangle box{x, y + 22, 137, 31};
        panel(box, field_ == 40 + i ? Line : Background);
        label(field_ == 40 + i ? fieldText_ : values[size_t(i)], x + 10, y + 31, 14, Text, 120);
        if (!closePrompt_ && !reloadPrompt_ && CheckCollisionPointRec(uiMouse(), box) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            commitField(); searchFocus_ = false; field_ = 40 + i; fieldText_ = values[size_t(i)]; selectText_ = true;
        }
    }
    label("Radius 0: stays at home and animates.", 1132, 465, 13, Muted, 284);
    label("Birds and aquatic species also use ground.", 1132, 496, 12, Muted, 284);
    const bool valid = validAnimalHome(animal, characterGround_);
    label(valid ? "Home has enough clear ground." : "Home blocked: move it before saving.", 1132, 539, 13, valid ? Muted : Accent, 284);
    if (button(previewPlaying_ ? "Pause preview" : "Play preview", {1132, 588, 137, 33}, previewPlaying_))
        setPreviewPlaying(!previewPlaying_);
    if (button("Reset preview", {1281, 588, 137, 33})) resetPreview();
    label("Preview " + number(float(animals_.time())) + " sec", 1132, 644, 13, Muted, 284);
    if (button("Focus", {1132, 694, 137, 33})) focusSelection();
    if (button("Duplicate", {1281, 694, 137, 33})) { duplicate(); return; }
    if (button("Delete animal", {1132, 747, 286, 33})) remove();
}
} // namespace dw
