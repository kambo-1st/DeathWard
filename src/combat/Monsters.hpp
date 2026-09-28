#pragma once
#include "core/Types.hpp"
#include <span>
#include <string_view>

namespace dw {
// Keep variant and subtype separate: 25.3.1 is not a decimal number.
constexpr int monsterId(int type, int variant = 0, int subtype = 0) {
    return type * 10000 + variant * 100 + subtype;
}
std::string monsterIdText(int id);
enum class MonsterMotion {
    Still,
    Chase,
    Wander,
    Flee,
    Bounce,
    Charge,
    Hop,
    Burrow,
    Teleport,
    Mirror,
    Wall,
    Chain,
    Orbit
};
enum class MonsterAttack {
    None,
    Shot,
    Spread,
    Cross,
    Diagonal,
    Ring,
    Burst,
    Lob,
    Spawn,
    Beam,
    DoubleBeam,
    QuadBeam,
    Head,
    Light,
    Spitty
};
enum class MonsterShape { Walker, Headless, Fly, Blob, Worm, Skull, Spider, Eye, Stone };
struct MonsterDefinition {
    int id;
    const char *name;
    MonsterMotion motion;
    MonsterAttack attack;
    MonsterShape shape;
    float hp = 72, speed = 2.2f, radius = .6f;
    float cooldown = 2.4f, windup = .55f;
    int depth = 1;
    bool flying = false, contact = true, roomHazard = false, natural = true;
};
std::span<const MonsterDefinition> monsterCatalog();
const MonsterDefinition *monsterDefinition(int id);
} // namespace dw
