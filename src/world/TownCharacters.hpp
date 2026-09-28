#pragma once
#include "world/HubWorld.hpp"
namespace dw {
struct TownCharacterState {
    TownCharacter definition;
    Vector3 position{}, facing{0, 0, 1};
    double phase = 0;
    float walking = 0, alternate = 0, wait = 0, retry = 0;
    size_t destination = 1, next = 0, visits = 0;
    int direction = 1;
    bool blocked = false;
    std::vector<Vector3> route;
};
// Fixed-step ambient characters follow authored stops using the town's navigation.
class TownCharacters {
  public:
    void reset(const TownDocument &document, const HubWorld &ground);
    void update(float dt, const HubWorld &ground);
    const std::vector<TownCharacterState> &residents() const { return characters_; }
    double time() const { return time_; }
  private:
    std::vector<TownCharacterState> characters_;
    double accumulator_ = 0, time_ = 0;
    void step(const HubWorld &ground);
};
}
