#pragma once
#include "core/Types.hpp"

namespace dw {
inline std::string withPlayerOcclusion(const char *fragment) {
    constexpr const char *opacity = R"GLSL(
uniform int objectFaded;
vec4 playerOcclusionSurface(vec3 world, vec4 surface) {
    if (objectFaded != 0) surface.a *= .22;
    return surface;
}
)GLSL";
    std::string source(fragment);
    source.insert(source.find('\n') + 1, opacity);
    return source;
}

struct PlayerOcclusion {
    bool enabled = false;
    Camera3D camera{};
    Vector3 player{};
    void set(const Camera3D &view, Vector3 position) {
        enabled = true;
        camera = view;
        player = add(position, {0, .1f, 0});
    }
    bool intersects(Box bounds) const {
        if (!enabled || bounds.max.y <= player.y - .85f)
            return false;
        constexpr Vector3 margin{1.4f, 1.4f, 1.4f};
        const auto hit =
            GetRayCollisionBox(rayTo(player), {sub(bounds.min, margin), add(bounds.max, margin)});
        return hit.hit && hit.distance <= distance(rayTo(player).position, player) + 1.4f;
    }
    Ray rayTo(Vector3 target) const {
        if (camera.projection == CAMERA_ORTHOGRAPHIC) {
            const auto direction = unit(sub(camera.target, camera.position));
            return {sub(target, mul(direction, dot(sub(target, camera.position), direction))), direction};
        }
        return {camera.position, unit(sub(target, camera.position))};
    }
    std::array<Vector3, 5> targets() const {
        const auto forward = unit(sub(camera.target, camera.position));
        const auto right = unit(Vector3{-forward.z, 0, forward.x});
        return {player, add(player, {0, .6f, 0}), add(player, {0, -.5f, 0}), add(player, mul(right, .3f)),
                sub(player, mul(right, .3f))};
    }
    bool blocks(const Mesh &mesh, Matrix transform) const {
        if (!enabled)
            return false;
        // Check the body, head and shoulders; a box alone would fade empty space under roofs.
        for (auto target : targets()) {
            const auto ray = rayTo(target);
            const auto hit = GetRayCollisionMesh(ray, mesh, transform);
            if (hit.hit && hit.distance > .05f && hit.distance < distance(ray.position, target) - .15f &&
                hit.point.y > player.y - .85f)
                return true;
        }
        return false;
    }
    void bind(Shader shader, bool faded) const {
        const int active = enabled && faded;
        SetShaderValue(shader, GetShaderLocation(shader, "objectFaded"), &active, SHADER_UNIFORM_INT);
    }
};
} // namespace dw
