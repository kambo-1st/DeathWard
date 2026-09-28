#pragma once
#include "core/Types.hpp"
#include <filesystem>
#include <optional>

namespace dw {
enum class ObjectMotionKind { None, Spin, Sway, Tumbleweed };
struct ObjectMotion {
    ObjectMotionKind kind = ObjectMotionKind::None;
    float speed = 1.2f, amplitude = .04f, period = 6;
    uint32_t seed = 1;
    Vector3 axis{0, 1, 0}, pivot{};
};
const char *motionName(ObjectMotionKind kind);
Box objectBounds(Box local, Matrix transform);
struct TownAsset {
    std::string name, label;
    int first = 0, count = 0, unlit = 0;
    Box bounds;
};
struct TownInstance {
    size_t asset = 0;
    Matrix transform{};
    std::string id{};
    ObjectMotion motion{};
    std::string group{};
    float wheelRadius = 0; // Local X axle; rotation is driven by path distance.
    bool animated() const {
        return motion.kind != ObjectMotionKind::None || !group.empty();
    }
};
struct TownMotionPath {
    std::string id;
    float speed = 3, acceleration = .8f, dwell = 6;
    std::vector<Vector3> points; // Closed, continuous centerline, without repeated final point.
};
struct TownMotionGroup {
    std::string id, path;
    float offset = 0, wheelbase = 0;
};
struct TownLight {
    int type = 1;
    Vector3 position{}, direction{}, color{};
    float intensity = 1, range = 0;
};
struct TownCharacter {
    std::string id, model = "cowgirl";
    Vector3 position{};
    float yaw = 0, scale = 1, speed = 1.2f, dwell = 2;
    bool loop = true;
    std::vector<Vector3> stops; // The placement is the first stop; these are subsequent destinations.
};
struct TownDocument {
    std::vector<TownAsset> assets;
    std::vector<TownInstance> instances;
    std::vector<TownLight> lights;
    std::vector<TownMotionPath> paths;
    std::vector<TownMotionGroup> groups;
    std::vector<TownCharacter> characters;
    bool load(const std::filesystem::path &path, std::string &error);
    void write(const std::filesystem::path &path) const;
    void validate() const;
    Box bounds(size_t instance) const;
    int meshCount() const;
    std::string nextInstanceId() const;
    std::string nextCharacterId() const;
};
} // namespace dw
