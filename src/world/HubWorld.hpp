#pragma once
#include "combat/Simulation.hpp"
#include "world/ObjectAnimation.hpp"
#include <filesystem>
#include <optional>

namespace dw {
// Outdoor navigation sampled from the imported scene's original colliders.
class HubWorld {
  public:
    Player player;
    double time = 0;
    Vector3 spawn{}, mission{};
    std::string error;
    bool load(const std::filesystem::path &path);
    bool loaded() const {
        return !heights_.empty();
    }
    void reset();
    bool walkable(Vector3 point) const;
    float height(Vector3 point) const;
    bool moveTo(Vector3 target);
    void stop();
    void step(Vector3 movement, float dt);
    std::optional<Vector3> pickGround(Ray ray) const;
    std::optional<Vector3> destination() const;
    const std::vector<Vector3> &route() const {
        return route_;
    }
    bool nearMission() const;
    size_t walkableCells() const;
    void setMovingSolids(const std::vector<MovingSolid> &solids);

  private:
    uint32_t width_ = 0, depth_ = 0;
    float minX_ = 0, minZ_ = 0, cell_ = 0;
    std::vector<float> heights_;
    std::vector<Vector3> route_;
    std::vector<MovingSolid> solids_;
    std::vector<bool> occupied_;
    std::vector<size_t> occupiedCells_;
    float repathWait_ = 0;
    size_t next_ = 0;
    int index(Vector3 point) const;
    Vector3 point(int index) const;
    bool traversable(int from, int to) const;
    bool clear(Vector3 from, Vector3 to) const;
};
} // namespace dw
