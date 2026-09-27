#pragma once
#include "core/Game.hpp"

namespace dw {
class Renderer {
  public:
    Action draw(const Game &game);
    void drawWorld(const Simulation &run, const Camera3D &camera, bool collisions, EntityId hoveredEnemy = 0);

  private:
    float sx_ = 1, sy_ = 1;
    void text(const std::string &value, float x, float y, int size, Color color) const;
    void wrap(const std::string &value, float x, float y, float width, int size, Color color) const;
    void panel(float x, float y, float w, float h, Color color) const;
    bool button(const std::string &title, float x, float y, float w, float h, bool primary = false) const;
    Action hub(const Game &game);
    Action expedition(const Game &game);
    Action summary(const Game &game, const RunSummary &summary, bool history);
    void debugPanel(const Game &game);
};
} // namespace dw
