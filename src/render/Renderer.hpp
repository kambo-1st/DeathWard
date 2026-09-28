#pragma once
#include "core/Game.hpp"
#include "render/PlayerModel.hpp"
#include "render/PostProcess.hpp"
#include "render/TownScene.hpp"
#include "render/WesternScene.hpp"

namespace dw {
class Renderer {
  public:
    Action draw(const Game &game);
    void reloadTown() {
        townScene_.unload();
        loadedHub_.reset();
    }
    void drawWorld(const Simulation &run, const Camera3D &camera, bool collisions, EntityId hoveredEnemy = 0,
                   float deathTime = 0);
    void unload() {
        playerModel_.unload();
        westernScene_.unload();
        townScene_.unload();
        postProcess_.unload();
        loadedHub_.reset();
    }

  private:
    float sx_ = 1, sy_ = 1;
    PlayerModel playerModel_;
    PostProcess postProcess_;
    WesternScene westernScene_;
    TownScene townScene_;
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
