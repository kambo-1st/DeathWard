#pragma once
#include "raylib.h"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

namespace dw {
inline constexpr const char *ContentVersion = "deathward-m1-29";
inline constexpr int StartingDynamite = 3, MaxDynamite = 9;
inline constexpr float DynamiteFuse = 2, DynamiteRange = 12, DynamiteRadius = 4.5f;
inline constexpr float DynamiteDamage = 100, DynamiteSelfDamage = 25;
inline constexpr uint64_t MaxMoney = 999999999;
inline constexpr float StartingHealth = 100;
inline constexpr float RevolverDamage = 24;
inline constexpr float EnemyDamageMultiplier = 1.25f;
inline constexpr float EnemyMovementMultiplier = 1.10f;
inline constexpr float EnemyCooldownMultiplier = .85f;
inline constexpr float Tick = 1.0f / 60.0f;
inline constexpr float Pi = 3.14159265358979323846f;
inline Vector3 add(Vector3 a, Vector3 b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}
inline Vector3 sub(Vector3 a, Vector3 b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}
inline Vector3 mul(Vector3 a, float s) {
    return {a.x * s, a.y * s, a.z * s};
}
inline float dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline float length(Vector3 a) {
    return std::sqrt(dot(a, a));
}
inline float distance(Vector3 a, Vector3 b) {
    return length(sub(a, b));
}
inline Vector3 unit(Vector3 a) {
    const float n = length(a);
    return n > 0.0001f ? mul(a, 1 / n) : Vector3{0, 0, -1};
}
inline Vector3 rotateY(Vector3 a, float angle) {
    return {a.x * std::cos(angle) + a.z * std::sin(angle), a.y,
            -a.x * std::sin(angle) + a.z * std::cos(angle)};
}

// SplitMix64 with explicit integer-to-range conversion: independent of stdlib distributions.
struct Random {
    uint64_t state;
    explicit Random(uint64_t seed = 1) : state(seed) {}
    uint64_t next() {
        uint64_t z = (state += 0x9e3779b97f4a7c15ULL);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
        return z ^ (z >> 31);
    }
    uint32_t bounded(uint32_t count) {
        if (!count)
            return 0;
        const uint64_t threshold = -uint64_t(count) % count;
        uint64_t n;
        do {
            n = next();
        } while (n < threshold);
        return uint32_t(n % count);
    }
    float real(float lo, float hi) {
        return lo + (hi - lo) * float(next() >> 40) / 16777216.0f;
    }
};

using EntityId = uint64_t; // Monotonic per run; IDs are never reused.
enum class ItemId : int { Ricochet, Split, Judas, Powder, Ghost, Count };
inline constexpr int ItemCount = int(ItemId::Count);
struct Context {
    uint64_t chainId = 0;
    int generation = 0;
    EntityId sourceEntity = 0;
    int sourceEffect = -1;
};
struct Stats {
    double duration = 0, bossDuration = 0;
    float damageDealt = 0, damageTaken = 0;
    uint64_t shots = 0, projectiles = 0, kills = 0, explosions = 0, bounces = 0, splits = 0, ghosts = 0;
    uint64_t maxProjectiles = 0, maxDepth = 0, largestKillChain = 0, rooms = 0, suppressed = 0;
};
struct Box {
    Vector3 min{}, max{};
};
struct SegmentHit {
    bool hit = false;
    float t = 1;
    Vector3 normal{};
};
inline SegmentHit segmentBox(Vector3 start, Vector3 end, Box box, float inflate = 0) {
    box.min = sub(box.min, {inflate, inflate, inflate});
    box.max = add(box.max, {inflate, inflate, inflate});
    const Vector3 d = sub(end, start);
    const float s[] = {start.x, start.y, start.z}, v[] = {d.x, d.y, d.z},
                lo[] = {box.min.x, box.min.y, box.min.z}, hi[] = {box.max.x, box.max.y, box.max.z};
    float enter = 0, leave = 1;
    Vector3 normal{};
    for (int axis = 0; axis < 3; ++axis) {
        if (std::abs(v[axis]) < 0.000001f) {
            if (s[axis] < lo[axis] || s[axis] > hi[axis])
                return {};
            continue;
        }
        float a = (lo[axis] - s[axis]) / v[axis], b = (hi[axis] - s[axis]) / v[axis];
        float sign = -1;
        if (a > b) {
            std::swap(a, b);
            sign = 1;
        }
        if (a > enter) {
            enter = a;
            normal = {};
            if (axis == 0)
                normal.x = sign;
            if (axis == 1)
                normal.y = sign;
            if (axis == 2)
                normal.z = sign;
        }
        leave = std::min(leave, b);
        if (enter > leave)
            return {};
    }
    return {true, enter, normal};
}
inline float segmentSphere(Vector3 start, Vector3 end, Vector3 center, float radius) {
    Vector3 m = sub(start, center), d = sub(end, start);
    float a = dot(d, d), b = dot(m, d), c = dot(m, m) - radius * radius;
    if (c <= 0)
        return 0;
    if (a < 0.0000001f)
        return 2;
    float disc = b * b - a * c;
    if (disc < 0)
        return 2;
    float t = (-b - std::sqrt(disc)) / a;
    return t >= 0 && t <= 1 ? t : 2;
}
inline bool sphereBox(Vector3 p, float radius, Box b) {
    Vector3 q{std::clamp(p.x, b.min.x, b.max.x), std::clamp(p.y, b.min.y, b.max.y),
              std::clamp(p.z, b.min.z, b.max.z)};
    return dot(sub(p, q), sub(p, q)) < radius * radius;
}
} // namespace dw
