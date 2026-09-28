#pragma once
#include "world/TownDocument.hpp"
#include <functional>

namespace dw {
struct ObjectPose {
    Matrix transform{};
    Box bounds;
    bool animated = false;
};
struct MovingSolid {
    Vector3 center{}, forward{1, 0, 0}, halfSize{}; // X along the vehicle, Z across it.
    bool contains(Vector3 point, float radius = .45f) const;
    Box bounds() const;
};
// CPU-only rigid-object motion. Rendering consumes poses and never advances time.
class ObjectAnimationSystem {
  public:
    using Ground = std::function<float(Vector3)>; // NaN means blocked or outside the ground map.
    void reset(const TownDocument &document);
    void update(float dt, const Ground &ground, std::optional<Vector3> player = {});
    const std::vector<ObjectPose> &poses() const {
        return poses_;
    }
    size_t activeCount() const {
        return moving_.size() + members_.size();
    }
    const ObjectPose *firstPropPose() const {
        return moving_.empty() ? nullptr : &poses_[moving_.front().index];
    }
    const std::vector<MovingSolid> &solids() const {
        return solids_;
    }
    double pathDistance(size_t path = 0) const {
        return paths_.at(path).travel;
    }
    float pathSpeed(size_t path = 0) const {
        return paths_.at(path).speed;
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
    struct Path {
        TownMotionPath definition;
        std::vector<float> cumulative;
        double travel = 0;
        float length = 0, position = 0, speed = 0, wait = 0;
    };
    struct Group {
        size_t path;
        float offset, wheelbase;
        Box bounds{{1e9f, 1e9f, 1e9f}, {-1e9f, -1e9f, -1e9f}};
    };
    struct Member {
        size_t index, group;
        Matrix rest, bind;
        Box local;
        float wheelRadius;
    };
    std::vector<Path> paths_;
    std::vector<Group> groups_;
    std::vector<Member> members_;
    std::vector<MovingSolid> solids_;
    double accumulator_ = 0, time_ = 0;
    void step(const Ground &ground);
    Vector3 sample(const Path &path, float at) const;
    Matrix groupFrame(const Group &group) const;
    void evaluateGroups();
    void stepPaths(std::optional<Vector3> player);
};
} // namespace dw
