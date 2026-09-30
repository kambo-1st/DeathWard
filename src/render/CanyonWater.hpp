#pragma once
#include "render/MissionLighting.hpp"
#include "world/CanyonTerrain.hpp"

namespace dw {
class CanyonWater {
  public:
    ~CanyonWater() {
        unload();
    }
    CanyonWater() = default;
    CanyonWater(const CanyonWater &) = delete;
    CanyonWater &operator=(const CanyonWater &) = delete;
    void prepare(const CanyonTerrain &field);
    void unload();
    void draw(Vector3 focus, const MissionLighting &lighting) const;
    bool ready() const {
        return !chunks_.empty();
    }

  private:
    struct Chunk {
        Mesh mesh{};
        Box bounds{};
    };
    std::vector<Chunk> chunks_;
    Shader shader_{};
    Material material_{};
};
} // namespace dw
