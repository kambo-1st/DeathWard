#pragma once
#include "world/HubWorld.hpp"
#include "world/AnimalPlacement.hpp"

namespace dw {
struct Animal {
    std::string id;
    AnimalKind kind = AnimalKind::Horse;
    Vector3 home{}, position{}, facing{0, 0, 1}, target{};
    float scale = 1, roam = 3, wait = 1, walking = 0, eating = 0;
    double phase = 0;
    bool moving = false;
    Random random{1};
    AnimalActivity activity;
};
// Ambient hub residents; their motion uses a private random stream and simulation clock.
class Animals {
  public:
    bool load(const std::filesystem::path &file, const HubWorld &ground);
    bool reset(const std::vector<AnimalPlacement> &placements, const HubWorld &ground, bool relocate = true);
    static bool clearFootprint(const AnimalPlacement &animal, Vector3 point, const HubWorld &ground);
    const std::vector<AnimalPlacement> &placements() const { return placements_; }
    void update(float dt, const HubWorld &ground);
    const std::vector<Animal> &residents() const {
        return animals_;
    }
    const std::string &error() const {
        return error_;
    }
    double time() const {
        return time_;
    }

  private:
    std::vector<Animal> animals_;
    std::vector<AnimalPlacement> placements_;
    std::string error_;
    double time_ = 0, accumulator_ = 0;
    bool clear(const Animal &animal, Vector3 point, const HubWorld &ground, bool residents) const;
    void step(const HubWorld &ground);
};
} // namespace dw
