#pragma once
#include "world/HubWorld.hpp"

namespace dw {
enum class AnimalKind { Horse, Hen, Cow, Cat, Count };
const char *animalName(AnimalKind kind);
float animalRadius(AnimalKind kind);
float animalWalkSpeed(AnimalKind kind);
struct Animal {
    std::string id;
    AnimalKind kind = AnimalKind::Horse;
    Vector3 home{}, position{}, facing{0, 0, 1}, target{};
    float scale = 1, roam = 3, wait = 1, walking = 0, eating = 0;
    double phase = 0;
    bool moving = false;
    Random random{1};
};
// Ambient hub residents; their motion uses a private random stream and simulation clock.
class Animals {
  public:
    bool load(const std::filesystem::path &file, const HubWorld &ground);
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
    std::string error_;
    double time_ = 0, accumulator_ = 0;
    bool clear(const Animal &animal, Vector3 point, const HubWorld &ground, bool residents) const;
    void step(const HubWorld &ground);
};
} // namespace dw
