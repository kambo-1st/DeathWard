#pragma once
#include "world/TownDocument.hpp"
#include <functional>

namespace dw {
struct ObjectPose {
    Matrix transform{};
    Box bounds;
    bool animated = false;
};
// CPU-only rigid-object motion. Rendering consumes poses and never advances time.
class ObjectAnimationSystem {
  public:
    using Ground = std::function<float(Vector3)>; // NaN means blocked or outside the ground map.
    void reset(const TownDocument &document);
    void update(float dt, const Ground &ground);
    const std::vector<ObjectPose> &poses() const {
        return poses_;
    }
    size_t activeCount() const {
        return moving_.size();
    }
    double time() const {
        return time_;
    }

  private:
    struct Moving {
        size_t index;
        Matrix rest;
        Box local;
        ObjectMotion motion;
        Vector3 restCenter{}, center{}, heading{};
        Quaternion roll{0, 0, 0, 1};
        float radius = 1, phase = 0, distance = 0;
    };
    std::vector<ObjectPose> poses_;
    std::vector<Moving> moving_;
    double accumulator_ = 0, time_ = 0;
    void step(const Ground &ground);
};
} // namespace dw
