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
};
struct TownLight {
    int type = 1;
    Vector3 position{}, direction{}, color{};
    float intensity = 1, range = 0;
};
struct TownDocument {
    std::vector<TownAsset> assets;
    std::vector<TownInstance> instances;
    std::vector<TownLight> lights;
    bool load(const std::filesystem::path &path, std::string &error);
    void write(const std::filesystem::path &path) const;
    void validate() const;
    Box bounds(size_t instance) const;
    int meshCount() const;
    std::string nextInstanceId() const;
};
} // namespace dw
