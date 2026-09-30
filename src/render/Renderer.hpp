#pragma once
#include "core/Game.hpp"
#include "render/AnimalModels.hpp"
#include "render/TownActorModels.hpp"
#include "render/PlayerModel.hpp"
#include "render/PostProcess.hpp"
#include "render/TownScene.hpp"
#include "render/WesternScene.hpp"

namespace dw {
class Renderer {
  public:
    Action draw(const Game &game);
    bool artPoc = false;
    bool missionShadowsReady() const {
        return westernScene_.lighting().ready();
    }
    int missionDecorationCount(int room = -1) const {
        return westernScene_.decorationCount(room);
    }
    const ParticleEffects &missionEffects() const { return missionEffects_; }
    bool insideBuilding() const { return townScene_.interior().has_value(); }
    const ParticleEffects &townEffects() const { return townScene_.effects(); }
    std::optional<RayCollision> pickScenery(const Simulation &run, const Camera3D &camera, Ray ray);
    void reloadTown() {
        townScene_.unload();
        loadedHub_.reset();
    }
    void drawWorld(const Simulation &run, const Camera3D &camera, bool collisions, EntityId hoveredEnemy = 0,
                   float deathTime = 0, bool dynamiteArmed = false);
    void unload() {
        playerModel_.unload();
        animalModels_.unload();
        characterModels_.unload();
        westernScene_.unload();
        townScene_.unload();
        postProcess_.unload();
        missionEffects_.unload();
        particlesAttempted_ = false;
        loadedHub_.reset();
    }

  private:
    float sx_ = 1, sy_ = 1;
    PlayerModel playerModel_;
    AnimalModels animalModels_;
    TownActorModels characterModels_;
    PostProcess postProcess_;
    WesternScene westernScene_;
    TownScene townScene_;
    ParticleEffects missionEffects_;
    bool particlesAttempted_ = false;
    std::optional<HubKind> loadedHub_;
    void text(const std::string &value, float x, float y, int size, Color color) const;
    void wrap(const std::string &value, float x, float y, float width, int size, Color color) const;
    void panel(float x, float y, float w, float h, Color color) const;
    bool button(const std::string &title, float x, float y, float w, float h, bool primary = false) const;
    Action hub(const Game &game);
    Action expedition(const Game &game);
    Action summary(const Game &game, const RunSummary &summary, bool history);
    void debugPanel(const Game &game);
    void dungeonMap(const Game &game);
    Action audioPanel(const Game &game);
};
} // namespace dw
