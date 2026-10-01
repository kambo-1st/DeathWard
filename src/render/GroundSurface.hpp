#pragma once
#include "world/Dungeon.hpp"
#include <span>
#include <string>

namespace dw {
// Cosmetic material detail only. No mesh displacement or changes to navigation.
class GroundSurface {
  public:
    ~GroundSurface() {
        unload();
    }
    GroundSurface() = default;
    GroundSurface(const GroundSurface &) = delete;
    GroundSurface &operator=(const GroundSurface &) = delete;
    bool enabled = true;
    void prepare(const Arena &arena, std::span<const Box> rocks);
    void unload();
    void bind(Shader shader, bool floor = true) const;
    Texture2D texture() const {
        return soil_;
    }
    static std::string withDetail(const char *fragment);

  private:
    Texture2D soil_{};
    bool roads_ = false;
    Vector4 rectangle_{};
    Vector2 seed_{};
};
} // namespace dw
