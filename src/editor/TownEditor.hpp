#pragma once
#include "render/PostProcess.hpp"
#include "render/TownScene.hpp"
#include "render/TownActorModels.hpp"
#include "render/AnimalModels.hpp"
#include "world/TownNavigation.hpp"
#include <deque>

namespace dw {
class TownEditor {
  public:
    bool active = false, quitRequested = false, saved = false;
    std::string status;
    Camera3D camera{};
    bool open(const std::filesystem::path &directory, Camera3D view,
              const std::vector<AnimalPlacement> &legacyAnimals = {});
    void update(float dt);
    void draw();
    void requestClose(bool quit = false);
    void unload() {
        scene_.unload();
        postProcess_.unload();
        characterModels_.unload();
        animalModels_.unload();
    }
    bool dirty() const {
        return revision_ != savedRevision_;
    }
    const TownDocument &document() const {
        return document_;
    }
    const ParticleEffects &effects() const { return scene_.effects(); }
    const TownNavigation &navigation() const {
        return navigation_;
    }
    std::optional<size_t> selection() const {
        return selected_;
    }
    void select(std::optional<size_t> index);
    void translate(Vector3 delta);
    void rotate(Vector3 axis, float degrees);
    void scale(Vector3 factors);
    void duplicate();
    void remove();
    void addAsset(size_t asset);
    void undo();
    void redo();
    bool save();
    bool reload();
    void focusSelection();
    void setMotion(ObjectMotion motion);
    void setPreviewPlaying(bool playing);
    void resetPreview();
    void detachVehicle();
    void setPathSettings(float speed, float acceleration, float dwell);
    void addAnimal(AnimalKind kind);
    void selectAnimal(std::optional<size_t> index);
    void placeAnimal(Vector3 position);
    void setAnimalSettings(float scale, float roam, float yaw, uint32_t seed);
    void setAnimalSpecies(AnimalKind kind);
    std::optional<size_t> animalSelection() const { return selectedAnimal_; }
    const Animals &animalPreview() const { return animals_; }
    void addCharacter();
    void selectCharacter(std::optional<size_t> index);
    void placeCharacter(Vector3 position);
    void addCharacterStop(Vector3 position);
    void moveCharacterStop(size_t stop, Vector3 position);
    void removeCharacterStop(size_t stop);
    void setCharacterSettings(float speed, float dwell, bool loop, float scale, float yaw);
    std::optional<size_t> characterSelection() const { return selectedCharacter_; }
    const TownCharacters &characterPreview() const { return characters_; }
    bool previewPlaying() const {
        return previewPlaying_;
    }
    const ObjectAnimationSystem &animationPreview() const {
        return preview_;
    }

  private:
    struct Snapshot {
        TownDocument document;
        Vector3 spawn, mission;
        std::optional<size_t> selected;
        std::optional<size_t> character, stop, animal;
        uint64_t revision;
    };
    enum class Tool { Move, Rotate, Scale };
    TownScene scene_;
    PostProcess postProcess_;
    TownDocument document_;
    TownNavigation navigation_;
    TownNavigation previewNavigation_;
    ObjectAnimationSystem preview_;
    TownActorModels characterModels_;
    TownCharacters characters_;
    AnimalModels animalModels_;
    Animals animals_;
    std::vector<AnimalPlacement> legacyAnimals_;
    std::vector<Box> animalBounds_;
    std::optional<size_t> selectedAnimal_;
    AnimalKind animalKind_ = AnimalKind::Horse;
    bool animalTab_ = false, animalPalette_ = false, animalPlacement_ = false, replacingAnimal_ = false;
    HubWorld characterGround_;
    std::optional<size_t> selectedCharacter_, selectedStop_;
    bool characterTab_ = false;
    int characterPlacement_ = 0; // 1: home, 2: append stop, 3: move selected stop.
    int stopScroll_ = 0;
    struct RouteLine { Vector3 from, to; bool valid; };
    std::vector<RouteLine> characterRoute_;
    bool animationTab_ = false, previewPlaying_ = false;
    uint64_t navigationRevision_ = 0;
    std::filesystem::path directory_;
    std::optional<size_t> selected_, paletteSelection_;
    std::deque<Snapshot> undo_, redo_;
    uint64_t revision_ = 0, savedRevision_ = 0, nextRevision_ = 0;
    Tool tool_ = Tool::Move;
    bool palette_ = false, searchFocus_ = false, selectText_ = false, snap_ = true, showGrid_ = true,
         showNavigation_ = false;
    bool closePrompt_ = false, reloadPrompt_ = false, closingWindow_ = false;
    bool orbiting_ = false, panning_ = false, dragChanged_ = false;
    int scroll_ = 0, field_ = -1, dragAxis_ = -1, marker_ = 0;
    std::string search_, fieldText_;
    Matrix dragTransform_{};
    Vector2 previousMouse_{}, dragMouse_{};
    float yaw_ = 0, pitch_ = 0, radius_ = 40, scaleX_ = 1, scaleY_ = 1;
    Snapshot snapshot() const;
    void restore(Snapshot state);
    void remember();
    void sync();
    void updateView();
    bool overUI(Vector2 pixel) const;
    Vector2 uiMouse() const;
    Vector3 pivot() const;
    Vector3 values(int group) const;
    void commitField();
    void closeNow();
    void label(const std::string &text, float x, float y, int size, Color color, float width = 1000) const;
    bool button(const std::string &text, Rectangle r, bool selected = false, bool enabled = true) const;
    void panel(Rectangle r, Color color) const;
    void drawUI();
    void drawAnimationUI();
    void drawCharacterUI();
    void drawAnimalUI();
    void drawAnimalPalette();
    void commitAnimalField();
    bool validAnimalHome(const AnimalPlacement &animal, const HubWorld &ground) const;
    void importLegacyAnimals();
    void refreshCharacterRoute();
    std::optional<Vector3> characterGroundPoint(Vector2 pixel) const;
    bool validCharacterStop(Vector3 point, std::optional<size_t> replacing = {}) const;
    const TownMotionGroup *selectedGroup() const;
    Box selectionBounds() const;
};
} // namespace dw
