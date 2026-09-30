#include "render/Renderer.hpp"
#include "items/Items.hpp"
#include "render/MonsterVisuals.hpp"
#include "render/WorldPalette.hpp"
#include "rlgl.h"
#include <iomanip>
#include <sstream>

namespace dw {
namespace {
constexpr Color Ink{17, 23, 26, 255}, Panel{26, 34, 36, 245}, Border{62, 72, 70, 255},
    Paper{236, 226, 201, 255}, Muted{148, 158, 146, 255}, Gold{224, 168, 86, 255}, Teal{112, 204, 180, 255},
    Rust{203, 86, 63, 255};
std::string number(uint64_t n) {
    return std::to_string(n);
}
std::string timeLabel(double seconds) {
    int s = int(seconds);
    return std::to_string(s / 60) + ":" + (s % 60 < 10 ? "0" : "") + std::to_string(s % 60);
}
void shadow(Vector3 p, float radius) {
    DrawCylinder({p.x, 0.025f, p.z}, radius, radius, 0.012f, 12, Color{24, 27, 26, 120});
}
void projectileMesh(Vector3 p, float radius, Color color) {
    // Eight triangle faces remain a real 3D volume, with no per-vertex trigonometry.
    const std::array<Vector3, 6> points{{add(p, {radius, 0, 0}), add(p, {0, 0, radius}),
                                         add(p, {-radius, 0, 0}), add(p, {0, 0, -radius}),
                                         add(p, {0, radius, 0}), add(p, {0, -radius, 0})}};
    rlBegin(RL_TRIANGLES);
    rlColor4ub(color.r, color.g, color.b, color.a);
    for (int i = 0; i < 4; ++i) {
        for (int index : {4, (i + 1) % 4, i, i, (i + 1) % 4, 5}) {
            const auto &v = points[size_t(index)];
            rlVertex3f(v.x, v.y, v.z);
        }
    }
    rlEnd();
}
void effectRings(Vector3 center, float radius, Color color) {
    static const auto circle = [] {
        std::array<Vector2, 24> points{};
        for (size_t i = 0; i < points.size(); ++i) {
            float angle = 2 * Pi * float(i) / float(points.size());
            points[i] = {std::cos(angle), std::sin(angle)};
        }
        return points;
    }();
    rlBegin(RL_LINES);
    rlColor4ub(color.r, color.g, color.b, color.a);
    for (size_t i = 0; i < circle.size(); ++i) {
        for (size_t j : {i, (i + 1) % circle.size()}) {
            rlVertex3f(center.x + circle[j].x * radius, 0.08f, center.z + circle[j].y * radius);
        }
        for (size_t j : {i, (i + 1) % circle.size()}) {
            rlVertex3f(center.x + circle[j].x * radius, center.y + circle[j].y * radius, center.z);
        }
        for (size_t j : {i, (i + 1) % circle.size()}) {
            rlVertex3f(center.x, center.y + circle[j].x * radius, center.z + circle[j].y * radius);
        }
    }
    rlEnd();
}
void lanternPost(Vector3 p) {
    DrawCylinder({p.x, 0, p.z}, 0.10f, 0.15f, 2.4f, 6, Color{65, 54, 43, 255});
}
void lantern(Vector3 p, Color color, bool imported = false) {
    if (imported) {
        DrawSphereEx({p.x, 2.18f, p.z}, 0.14f, 4, 6, color);
        return;
    }
    DrawCube({p.x, 2.25f, p.z}, 0.42f, 0.5f, 0.42f, color);
    DrawCylinder({p.x, 2.55f, p.z}, 0, 0.42f, 0.24f, 4, Color{46, 43, 37, 255});
}
void cowboy(Vector3 p, Vector3 direction, Color coat, float scale, bool boss = false,
            bool drawShadow = true) {
    if (drawShadow)
        shadow(p, 0.7f * scale);
    DrawCube({p.x, 0.45f * scale, p.z}, 0.55f * scale, 0.9f * scale, 0.45f * scale, coat);
    DrawCube({p.x, 1.0f * scale, p.z}, 0.8f * scale, 0.6f * scale, 0.5f * scale, coat);
    DrawSphereEx({p.x, 1.5f * scale, p.z}, 0.27f * scale, 6, 8, boss ? Teal : Color{195, 159, 112, 255});
    DrawCylinder({p.x, 1.66f * scale, p.z}, 0.58f * scale, 0.58f * scale, 0.08f * scale, 12,
                 Color{40, 33, 29, 255});
    DrawCylinder({p.x, 1.7f * scale, p.z}, 0.31f * scale, 0.36f * scale, 0.3f * scale, 8,
                 Color{59, 47, 35, 255});
    Vector3 hand = add({p.x, 1.05f * scale, p.z}, mul(direction, 0.52f * scale));
    DrawCylinderEx(hand, add(hand, mul(direction, 0.55f * scale)), 0.09f * scale, 0.09f * scale, 6,
                   Color{158, 163, 153, 255});
    DrawCube(add({p.x, 1.15f * scale, p.z}, mul(direction, 0.29f * scale)), 0.16f * scale, 0.16f * scale,
             0.16f * scale, Gold);
}
void enemyModel(const Enemy &enemy, bool drawShadow = true) {
    if (enemy.kind == EnemyKind::Monster) {
        drawMonsterModel(enemy, drawShadow);
        return;
    }
    rlPushMatrix();
    rlScalef(1, 1 + .018f * std::sin(enemy.animationTime() * 2.2f + float(enemy.id)), 1);
    static constexpr std::array<Color, size_t(EnemyKind::Count)> coats{{{159, 64, 48, 255},
                                                                        {118, 105, 84, 255},
                                                                        {159, 91, 38, 255},
                                                                        {146, 158, 169, 255},
                                                                        {180, 135, 43, 255},
                                                                        {80, 94, 102, 255},
                                                                        {107, 65, 40, 255},
                                                                        {116, 67, 153, 255},
                                                                        {154, 127, 63, 255},
                                                                        {80, 99, 71, 255},
                                                                        {130, 58, 28, 255},
                                                                        {85, 114, 143, 255},
                                                                        {153, 114, 197, 220},
                                                                        {155, 62, 40, 255},
                                                                        {83, 102, 111, 255},
                                                                        {40, 58, 52, 255}}};
    const Color coat = enemy.flash > 0 ? Paper : coats[size_t(enemy.kind)];
    const Vector3 p = enemy.position, facing = enemy.facing;
    const Vector3 side{-facing.z, 0, facing.x};
    const bool winding = enemy.state == EnemyState::Windup;
    const Vector3 hand = add({p.x, winding ? 1.65f : 1.05f, p.z}, mul(facing, 0.55f));
    const Color metal{153, 164, 169, 255};
    if (enemy.kind == EnemyKind::Spitter) {
        if (drawShadow)
            shadow(p, 0.8f);
        DrawSphereEx({p.x, 0.65f, p.z}, 0.78f, 8, 10, coat);
        DrawSphereEx(add(p, mul(facing, 0.65f)), 0.3f, 6, 8, winding ? Gold : Rust);
        for (float sign : {-1.0f, 1.0f})
            DrawSphereEx(add({p.x, 1.15f, p.z}, mul(side, sign * 0.48f)), 0.16f, 4, 6, Gold);
    } else if (enemy.kind == EnemyKind::PowderHusk) {
        if (drawShadow)
            shadow(p, 0.8f);
        DrawCylinder({p.x, 0.2f, p.z}, 0.6f, 0.55f, 1.25f, 10, coat);
        for (float height : {0.4f, 1.2f})
            DrawCylinder({p.x, height, p.z}, 0.62f, 0.62f, 0.12f, 10, Ink);
        DrawLine3D({p.x, 1.45f, p.z}, {p.x + 0.3f, 1.85f, p.z}, Gold);
        DrawSphereEx({p.x + 0.3f, 1.85f, p.z}, 0.12f, 4, 6, Rust);
    } else if (enemy.kind == EnemyKind::Preacher || enemy.kind == EnemyKind::BellRinger ||
               enemy.kind == EnemyKind::Wraith) {
        const bool wraith = enemy.kind == EnemyKind::Wraith;
        const float lift = wraith ? 0.25f + 0.12f * std::sin(enemy.animationTime() * 3) : 0;
        if (drawShadow)
            shadow(p, 0.7f);
        DrawCylinder({p.x, lift, p.z}, 0.3f, 0.65f, 1.5f, 8, coat);
        DrawSphereEx({p.x, 1.8f + lift, p.z}, 0.32f, 6, 8, coat);
        if (enemy.kind == EnemyKind::Preacher) {
            DrawCube(hand, 0.85f, 0.16f, 0.55f, Paper);
            DrawCube(add(hand, {0, 0.09f, 0}), 0.07f, 0.02f, 0.46f, Rust);
        } else if (enemy.kind == EnemyKind::BellRinger) {
            DrawCylinder(add(hand, {0, -0.55f, 0}), 0.22f, 0.65f, 0.8f, 10, Gold);
            DrawSphereEx(add(hand, {0, -0.58f, 0}), 0.13f, 4, 6, Ink);
        } else {
            const Vector3 light = add(hand, mul(side, 0.6f));
            DrawCube(light, 0.35f, 0.55f, 0.35f, coat);
            DrawSphereWires(light, 0.42f, 5, 8, Paper);
        }
    } else if (enemy.kind == EnemyKind::Rusher || enemy.kind == EnemyKind::Prospector ||
               enemy.kind == EnemyKind::Ironhide || enemy.kind == EnemyKind::Railbreaker) {
        const float scale =
            enemy.kind == EnemyKind::Ironhide || enemy.kind == EnemyKind::Railbreaker ? 1.35f : 1;
        if (drawShadow)
            shadow(p, 0.65f * scale);
        DrawCylinder({p.x, 0, p.z}, 0.38f * scale, 0.58f * scale, 1.25f * scale, 6, coat);
        DrawSphereEx({p.x, 1.5f * scale, p.z}, 0.3f * scale, 6, 8, Color{181, 131, 82, 255});
        if (enemy.kind == EnemyKind::Rusher) {
            DrawCylinderEx(hand, add(hand, {0, 0.75f, 0}), 0.07f, 0.07f, 5, Gold);
            DrawCylinderEx(add(add(hand, {0, 0.65f, 0}), mul(side, -0.48f)),
                           add(add(hand, {0, 0.65f, 0}), mul(side, 0.48f)), 0.09f, 0.04f, 5, metal);
        } else if (enemy.kind == EnemyKind::Prospector) {
            for (float offset : {-0.2f, 0.0f, 0.2f})
                DrawCylinderEx(add(hand, mul(side, offset)), add(add(hand, mul(side, offset)), {0, 0.55f, 0}),
                               0.085f, 0.085f, 6, Rust);
            DrawSphereEx({p.x, 1.72f, p.z}, 0.25f, 5, 6, Gold);
        } else if (enemy.kind == EnemyKind::Ironhide) {
            // Rotate the broad furnace plate with the armor's actual facing.
            rlPushMatrix();
            rlTranslatef(p.x + facing.x * 0.6f, 1.05f, p.z + facing.z * 0.6f);
            rlRotatef(std::atan2(facing.x, facing.z) * 180 / Pi, 0, 1, 0);
            DrawCube({}, 1.45f, 1.7f, 0.22f, metal);
            DrawCube({0, 0.2f, 0.13f}, 0.85f, 0.16f, 0.06f, Rust);
            rlPopMatrix();
        } else {
            for (float offset : {-0.7f, 0.7f}) {
                Vector3 rail = add({p.x, 1.8f, p.z}, mul(side, offset));
                DrawCylinderEx(sub(rail, mul(facing, 0.5f)), add(rail, mul(facing, 0.8f)), 0.18f, 0.18f, 4,
                               metal);
            }
        }
    } else {
        cowboy(p, facing, coat, enemy.kind == EnemyKind::Boss ? 1.7f : 1, enemy.kind == EnemyKind::Boss,
               drawShadow);
        if (enemy.kind == EnemyKind::Shotgun || enemy.kind == EnemyKind::Sharpshooter) {
            Vector3 barrel = add({p.x, 1.05f, p.z}, mul(facing, 0.5f));
            const float reach = enemy.kind == EnemyKind::Sharpshooter ? 1.25f : 0.75f;
            for (float offset : {-0.08f, 0.08f})
                DrawCylinderEx(add(barrel, mul(side, offset)),
                               add(add(barrel, mul(side, offset)), mul(facing, reach)), 0.065f, 0.065f, 6,
                               metal);
            if (enemy.kind == EnemyKind::Sharpshooter)
                DrawSphereEx(add(barrel, {0, 0.2f, 0}), 0.12f, 4, 6, Rust);
        } else if (enemy.kind == EnemyKind::Hangman) {
            DrawCircle3D(add(hand, mul(side, 0.4f)), 0.45f, {0, 1, 0}, 0, Gold);
            DrawCylinderEx(hand, add(hand, {0.25f, 0.45f, 0}), 0.08f, 0.08f, 6, metal);
        } else if (enemy.kind == EnemyKind::Marshal)
            DrawSphereWires({p.x, 1.2f, p.z}, 0.45f, 4, 4, Paper);
        else if (enemy.kind == EnemyKind::Chainbound)
            for (float offset : {-0.6f, 0.6f})
                DrawSphereWires(add(hand, mul(side, offset)), 0.2f, 4, 6, metal);
    }
    rlPopMatrix();
}
void shopkeeper(Vector3 p, float time, bool drawShadow = true) {
    const Color timber{100, 63, 39, 255}, apron{66, 120, 110, 255}, skin{203, 166, 123, 255};
    const float bob = .025f * std::sin(time * 2);
    if (drawShadow)
        shadow(p, .75f);
    DrawCylinder({p.x, .03f, p.z}, 1.6f, 1.6f, .025f, 12, Color{135, 85, 48, 255});
    for (float side : {-.2f, .2f}) {
        DrawCube({p.x + side, .38f, p.z}, .26f, .76f, .34f, Ink);
        DrawCube({p.x + side, .1f, p.z + .09f}, .3f, .2f, .52f, timber);
        DrawCylinderEx({p.x + side * 2, 1.32f + bob, p.z}, {p.x + side * 2.2f, .92f + bob, p.z + .3f}, .12f,
                       .12f, 6, skin);
    }
    DrawCube({p.x, 1.13f + bob, p.z}, .76f, .75f, .5f, Paper);
    DrawCube({p.x, 1 + bob, p.z + .28f}, .6f, .85f, .05f, apron);
    DrawSphereEx({p.x, 1.73f + bob, p.z}, .27f, 6, 8, skin);
    DrawCylinder({p.x, 1.92f + bob, p.z}, .55f, .55f, .08f, 12, timber);
    DrawCylinder({p.x, 1.97f + bob, p.z}, .31f, .35f, .25f, 8, timber);
    DrawCube({p.x, .78f, p.z + 1.1f}, 2.4f, .22f, .85f, timber);
    for (float side : {-.9f, .9f})
        DrawCube({p.x + side, .38f, p.z + 1.1f}, .18f, .76f, .6f, timber);
    DrawCube({p.x - .65f, 1.04f, p.z + 1.1f}, .42f, .34f, .35f, Paper);
    DrawCube({p.x - .65f, 1.04f, p.z + 1.29f}, .09f, .23f, .02f, Rust);
    DrawCube({p.x - .65f, 1.04f, p.z + 1.3f}, .25f, .07f, .02f, Rust);
    DrawSphereEx({p.x + .6f, 1.12f, p.z + 1.1f}, .22f, 6, 8, Teal);
    DrawCylinder({p.x + .1f, .93f, p.z + 1.1f}, .18f, .18f, .09f, 10, Gold);
}
void enemyWarning(const Enemy &enemy, const Simulation &run) {
    if (enemy.kind == EnemyKind::Monster) {
        drawMonsterWarning(enemy, run);
        return;
    }
    auto circle = [](Vector3 at, float radius, Color color) {
        at.y = 0.09f;
        DrawCircle3D(at, radius, {1, 0, 0}, 90, color);
    };
    if (enemy.aura > 0)
        circle(enemy.position, 6, Color{183, 125, 216, 210});
    if (enemy.state == EnemyState::Stunned) {
        DrawSphereWires(add(enemy.position, {0, 1.6f, 0}), 0.35f, 4, 6, Gold);
        return;
    }
    if (enemy.state == EnemyState::Teleporting) {
        circle(enemy.target, 0.9f, Color{193, 148, 234, 255});
        circle(enemy.target, 0.3f + enemy.stateTime, Paper);
        DrawLine3D(enemy.position, enemy.target, Color{158, 119, 192, 120});
        return;
    }
    if (enemy.state != EnemyState::Windup)
        return;
    const float progress = 1 - std::clamp(enemy.stateTime / enemyDefinition(enemy.kind).windup, 0.0f, 1.0f);
    const Color warning{255, static_cast<unsigned char>(115 + progress * 80), 65, 255};
    Vector3 direction = unit(sub(enemy.target, enemy.position));
    auto line = [&](Vector3 aim, float range) {
        Vector3 end = add(enemy.position, mul(aim, range));
        float fraction = 1;
        for (const auto &wall : run.arena.walls) {
            const auto hit = segmentBox(enemy.position, end, wall);
            if (hit.hit)
                fraction = std::min(fraction, hit.t);
        }
        end = add(enemy.position, mul(sub(end, enemy.position), fraction));
        DrawLine3D({enemy.position.x, 0.09f, enemy.position.z}, {end.x, 0.09f, end.z}, warning);
    };
    switch (enemy.kind) {
    case EnemyKind::Prospector:
    case EnemyKind::Spitter:
        circle(enemy.target, enemy.kind == EnemyKind::Prospector ? 2.8f : 2.3f, warning);
        break;
    case EnemyKind::BellRinger:
        circle(enemy.position, 1 + progress * 2, warning);
        circle(enemy.position, 11, Color{203, 86, 63, 110});
        break;
    case EnemyKind::Rusher:
    case EnemyKind::PowderHusk:
    case EnemyKind::Ironhide:
        line(rotateY(direction, -0.7f), enemy.kind == EnemyKind::Ironhide ? 2.6f : 2.1f);
        line(rotateY(direction, 0.7f), enemy.kind == EnemyKind::Ironhide ? 2.6f : 2.1f);
        break;
    case EnemyKind::Shotgun:
        for (float angle : {-0.34f, 0.0f, 0.34f})
            line(rotateY(direction, angle), 9);
        break;
    case EnemyKind::Sharpshooter:
        line(direction, 32);
        break;
    case EnemyKind::Railbreaker:
        line(direction, 15.4f);
        break;
    case EnemyKind::Hangman:
        line(direction, 14);
        break;
    case EnemyKind::Preacher:
        circle(enemy.position, 6, warning);
        break;
    default:
        break;
    }
    DrawSphereEx(add(enemy.position, mul(direction, enemy.radius + 0.2f)), 0.1f + progress * 0.15f, 4, 6,
                 warning);
}
void drawHazard(const Hazard &hazard) {
    if (hazard.kind == HazardKind::PlayerDynamite) {
        const auto p = hazard.position;
        const float fuse = std::clamp(hazard.age / hazard.delay, 0.f, 1.f);
        DrawCircle3D({p.x, .07f, p.z}, hazard.radius, {1, 0, 0}, 90, Rust);
        DrawCircle3D({p.x, .08f, p.z}, hazard.radius * fuse, {1, 0, 0}, 90, Gold);
        shadow(p, .45f);
        rlPushMatrix();
        rlTranslatef(p.x, p.y, p.z);
        rlRotatef(hazard.settled ? 25 : hazard.age * 210, 0, 1, 0);
        for (float z : {-.12f, .12f})
            DrawCylinderEx({-.4f, 0, z}, {.4f, 0, z}, .12f, .12f, 8, Rust);
        DrawCylinderEx({-.4f, .17f, 0}, {.4f, .17f, 0}, .12f, .12f, 8, Color{194, 63, 40, 255});
        DrawCube({0, .055f, 0}, .14f, .38f, .5f, Paper);
        DrawCylinderEx({.4f, .17f, 0}, {.58f, .3f, 0}, .025f, .02f, 4, Gold);
        DrawSphereEx({.58f, .3f, 0}, .09f + .04f * std::sin(hazard.age * 65), 4, 6, Gold);
        for (int i = 0; i < 4; ++i) {
            const float phase = std::fmod(hazard.age * 4 + float(i) * .25f, 1.f);
            DrawLine3D({.58f, .3f, 0}, {.58f + phase * .2f, .3f + phase * .55f, (float(i) - 1.5f) * .1f},
                       Gold);
        }
        rlPopMatrix();
        return;
    }
    if (hazard.kind == HazardKind::Beam) {
        const bool warning = hazard.age < hazard.delay;
        if (warning)
            DrawLine3D(hazard.origin, hazard.position, Gold);
        else {
            DrawCylinderEx(hazard.origin, hazard.position, hazard.radius, hazard.radius, 8, Rust);
            DrawCylinderEx(hazard.origin, hazard.position, hazard.radius * .35f, hazard.radius * .35f, 6,
                           Paper);
        }
        return;
    }
    Vector3 ground{hazard.position.x, 0.09f, hazard.position.z};
    const bool warning = hazard.age < hazard.delay;
    const Color color = hazard.kind == HazardKind::Ring ? Gold : Rust;
    float radius = hazard.radius;
    if (hazard.kind == HazardKind::Ring)
        radius *= std::clamp((hazard.age - hazard.delay) / hazard.duration, 0.0f, 1.0f);
    DrawCircle3D(ground, radius, {1, 0, 0}, 90, color);
    if (warning) {
        const float fraction = hazard.age / hazard.delay;
        DrawCircle3D(ground, hazard.radius * fraction, {1, 0, 0}, 90, Gold);
        Vector3 charge = add(hazard.origin, mul(sub(hazard.position, hazard.origin), fraction));
        charge.y += std::sin(fraction * Pi) * 3;
        if (hazard.kind == HazardKind::Powder) {
            charge = hazard.position;
            DrawCylinder({charge.x, 0, charge.z}, 0.4f, 0.4f, 0.7f, 8, Rust);
        }
        projectileMesh(charge, 0.18f, Gold);
    } else if (hazard.kind == HazardKind::Fire) {
        for (int i = 0; i < 7; ++i) {
            const float angle = float(i) * 2 * Pi / 7;
            Vector3 fire =
                add(ground, {std::cos(angle) * radius * 0.65f, 0.2f, std::sin(angle) * radius * 0.65f});
            DrawCylinder(fire, 0, 0.3f, 0.5f + 0.2f * std::sin(hazard.age * 9 + float(i)), 5, Gold);
        }
    } else if (hazard.kind == HazardKind::Tar || hazard.kind == HazardKind::Creep ||
               hazard.kind == HazardKind::Gas) {
        const Color pool = hazard.kind == HazardKind::Tar   ? Color{42, 35, 46, 200}
                           : hazard.kind == HazardKind::Gas ? Color{117, 141, 62, 140}
                                                            : Color{137, 43, 43, 190};
        DrawCylinder(ground, radius, radius, .04f, 12, pool);
        if (hazard.kind == HazardKind::Gas)
            DrawSphereEx(add(ground, {0, .35f, 0}), radius * .65f, 5, 8, pool);
    } else if (hazard.kind == HazardKind::HolyLight) {
        DrawCylinder(ground, radius * .6f, radius, 8, 10, Color{236, 213, 133, 180});
    } else if (hazard.kind == HazardKind::Ring)
        DrawCircle3D(add(ground, {0, 0.18f, 0}), radius, {1, 0, 0}, 90, Rust);
}
} // namespace
void Renderer::text(const std::string &value, float x, float y, int size, Color color) const {
    DrawText(value.c_str(), int(x * sx_), int(y * sy_), int(float(size) * std::min(sx_, sy_)), color);
}
void Renderer::wrap(const std::string &value, float x, float y, float width, int size, Color color) const {
    std::istringstream words(value);
    std::string word, line;
    const int font = int(float(size) * std::min(sx_, sy_));
    while (words >> word) {
        std::string next = line.empty() ? word : line + " " + word;
        if (!line.empty() && MeasureText(next.c_str(), font) > int(width * sx_)) {
            text(line, x, y, size, color);
            y += float(size + 7);
            line = word;
        } else
            line = next;
    }
    if (!line.empty())
        text(line, x, y, size, color);
}
void Renderer::panel(float x, float y, float w, float h, Color color) const {
    Rectangle rect{x * sx_, y * sy_, w * sx_, h * sy_};
    DrawRectangleRec(rect, color);
    DrawRectangleLinesEx(rect, 1, Border);
}
bool Renderer::button(const std::string &title, float x, float y, float w, float h, bool primary) const {
    Rectangle rect{x * sx_, y * sy_, w * sx_, h * sy_};
    bool hover = CheckCollisionPointRec(GetMousePosition(), rect);
    DrawRectangleRec(rect, primary ? (hover ? Paper : Gold) : (hover ? Color{49, 63, 63, 255} : Panel));
    DrawRectangleLinesEx(rect, 1, primary ? Gold : Border);
    text(title, x + 18, y + (h - 18) / 2, 18, primary ? Ink : Paper);
    return hover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}
std::optional<RayCollision> Renderer::pickScenery(const Simulation &run, const Camera3D &camera, Ray ray) {
    westernScene_.prepare(run.arena);
    if (!westernScene_.loaded() && !westernScene_.terrainReady())
        return std::nullopt;
    westernScene_.setPlayerOcclusion(camera, run.player.position);
    return westernScene_.pick(ray, run.player.position);
}
void Renderer::drawWorld(const Simulation &run, const Camera3D &camera, bool collisions,
                         EntityId hoveredEnemy, float deathTime, bool dynamiteArmed) {
    playerModel_.artPoc = false;
    playerModel_.update(run, deathTime);
    if (!particlesAttempted_) { particlesAttempted_ = true; missionEffects_.load(); }
    missionEffects_.prepareMission(run,camera,playerModel_.muzzlePosition(run.player));
    westernScene_.prepare(run.arena);
    westernScene_.setPlayerOcclusion(camera, run.player.position);
    const auto &theme = missionTheme(run.arena.theme);
    const bool canyon = run.arena.theme == MissionTheme::Canyon;
    const auto &lighting = westernScene_.lighting();
    auto visible = [&](Box box) {
        Vector3 nearest{std::clamp(run.player.position.x, box.min.x, box.max.x), run.player.position.y,
                        std::clamp(run.player.position.z, box.min.z, box.max.z)};
        return distance(nearest, run.player.position) < 65;
    };
    auto enemies = [&](bool depthOnly) {
        for (int room = 0; room < RoomCount; ++room) {
            if (room != run.room && !visible(run.arena.rooms[size_t(room)].bounds))
                continue;
            for (const auto &enemy : run.roomEnemies(room)) {
                if (!enemy.alive)
                    continue;
                if (depthOnly &&
                    (enemy.state == EnemyState::Buried || enemy.state == EnemyState::Teleporting))
                    continue;
                enemyModel(enemy, !depthOnly && !lighting.ready());
            }
        }
    };
    auto solids = [&](bool depthOnly) {
        for (const auto &passage : run.arena.passages) {
            if (!visible(passage.floor))
                continue;
            const auto direction = unit(sub(passage.to, passage.from));
            const Vector3 side{-direction.z, 0, direction.x};
            const bool eastWest = std::abs(direction.x) > .5f;
            for (int end = 0; end < 2; ++end) {
                const auto at = end == 0 ? passage.from : passage.to;
                const Color color = passage.locked ? Gold : passage.closed(end) ? Rust : Teal;
                lanternPost(add(at, mul(side, -3.5f)));
                lanternPost(add(at, mul(side, 3.5f)));
                if (!canyon)
                    DrawCube({at.x, 3.1f, at.z}, eastWest ? .5f : 8, .4f, eastWest ? 8 : .5f, theme.gate);
                if (!passage.closed(end))
                    continue;
                if (!canyon)
                    for (float offset = -3.5f; offset <= 3.5f; offset += .7f) {
                        auto bar = add(at, mul(side, offset));
                        bar.y = 1.5f;
                        DrawCube(bar, .13f, 3, .13f, color);
                    }
                if (passage.locked) {
                    DrawCube({at.x, 1.6f, at.z}, .6f, .7f, .6f, Gold);
                    DrawSphere({at.x, 1.6f, at.z}, .17f, Ink);
                }
            }
        }
        lanternPost(run.arena.entrance);
        lanternPost(run.arena.exit);
        if (run.arena.shopRoom >= 0) {
            const auto merchant = run.arena.rooms[size_t(run.arena.shopRoom)].objective;
            if (distance(run.player.position, merchant) < 60)
                shopkeeper(merchant, float(run.stats.duration), !depthOnly && !lighting.ready());
        }
        for (int i = 0; i < RoomCount; ++i) {
            const auto &room = run.arena.rooms[size_t(i)];
            if (room.kind != RoomKind::Power || distance(run.player.position, room.objective) > 60)
                continue;
            const auto p = room.objective;
            DrawCylinder({p.x, 0, p.z}, 0.8f, 1, 0.7f, 8, Border);
        }
        if (distance(run.player.position, run.arena.miners) < 60) {
            Vector3 p = run.arena.miners;
            for (int i = 0; i < 6; ++i) {
                Vector3 person = add(p, {float(i % 3) * 0.75f - 0.75f, 0, float(i / 3) * 0.7f});
                if (!run.rescued) {
                    DrawCylinder({person.x, 0, person.z}, 0.22f, 0.3f, 0.9f, 6, Color{128, 120, 87, 255});
                    DrawSphere({person.x, 1.1f, person.z}, 0.22f, Gold);
                }
            }
            if (!run.rescued)
                for (int i = 0; i < 5; ++i)
                    DrawCube({p.x - 1.6f + float(i) * 0.8f, 1.0f, p.z + 1.2f}, 0.07f, 2, 0.07f, Muted);
        }
        if (distance(run.player.position, run.arena.altar) < 60) {
            Vector3 p = run.arena.altar;
            DrawCube({p.x, 0.5f, p.z}, 1.8f, 1, 1.4f, Color{63, 51, 51, 255});
            if (!run.altarDestroyed) {
                DrawCube({p.x, 1.7f, p.z}, 0.25f, 2.3f, 0.25f, Rust);
                DrawCube({p.x, 2.1f, p.z}, 1.5f, 0.25f, 0.25f, Rust);
            }
        }
    };
    westernScene_.prepareLighting(camera, [&](Shader meshDepth, Shader primitiveDepth) {
        BeginShaderMode(primitiveDepth);
        solids(true);
        enemies(true);
        if (!westernScene_.loaded() && !westernScene_.terrainReady())
            for (size_t i = 0; i < run.arena.boundaryWalls.size() + run.arena.obstacles.size(); ++i) {
                const auto &wall = run.arena.walls[i];
                if (visible(wall))
                    DrawCubeV(mul(add(wall.min, wall.max), .5f), sub(wall.max, wall.min), WHITE);
            }
        // Flush the primitive batch before DrawMesh changes GPU state.
        rlDrawRenderBatchActive();
        if (playerModel_.loaded())
            playerModel_.draw(run.player, run.dead, meshDepth);
        else
            cowboy(run.player.position, run.player.facing, WHITE, 1, false, false);
        EndShaderMode();
    });
    postProcess_.begin(WorldSky, distance(camera.position, camera.target));
    BeginMode3D(camera);
    lighting.beginPrimitives();
    DrawPlane({camera.target.x, canyon ? -3.f : -.5f, camera.target.z}, {220, 220}, theme.backdrop);
    lighting.endPrimitives();
    if (westernScene_.loaded() || westernScene_.terrainReady())
        westernScene_.draw(run.player.position);
    lighting.beginPrimitives();
    auto floor = [&](Box box, Color color) {
        if (!visible(box))
            return;
        DrawCubeV(mul(add(box.min, box.max), 0.5f), sub(box.max, box.min), color);
        DrawLine3D({box.min.x, 0.012f, box.min.z}, {box.max.x, 0.012f, box.min.z}, Color{108, 91, 69, 255});
    };
    if (!westernScene_.loaded() && !westernScene_.terrainReady())
        for (const auto &box : run.arena.floors)
            floor(box, theme.floor);
    for (size_t i = 0; i < run.arena.walls.size(); ++i) {
        const auto &wall = run.arena.walls[i];
        if (i >= run.arena.boundaryWalls.size() + run.arena.obstacles.size() || !visible(wall))
            continue;
        if (westernScene_.loaded() || westernScene_.terrainReady()) {
            if (collisions)
                DrawBoundingBox({wall.min, wall.max}, Teal);
            continue;
        }
        Vector3 size = sub(wall.max, wall.min), center = mul(add(wall.min, wall.max), 0.5f);
        const bool boundary = i < run.arena.boundaryWalls.size();
        DrawCubeV(center, size, boundary && !canyon ? Color{66, 61, 52, 255} : theme.stone);
        DrawCube({center.x, wall.max.y + 0.025f, center.z}, size.x, 0.05f, size.z, theme.edge);
        if (!boundary) {
            DrawCubeWiresV(center, size, Color{47, 43, 37, 255});
            DrawCube({center.x, center.y, wall.min.z - 0.03f}, size.x, 0.2f, 0.08f, Color{47, 43, 37, 255});
        }
        if (collisions)
            DrawBoundingBox({wall.min, wall.max}, Teal);
    }
    solids(false);
    enemies(false);
    lighting.endPrimitives();
    for (const auto &passage : run.arena.passages) {
        if (!visible(passage.floor))
            continue;
        Vector3 direction = unit(sub(passage.to, passage.from));
        Vector3 side{-direction.z, 0, direction.x};
        const bool eastWest = std::abs(direction.x) > 0.5f;
        const float span = distance(passage.from, passage.to);
        Vector3 midpoint = mul(add(passage.from, passage.to), 0.5f);
        if (!westernScene_.loaded() && !canyon) {
            for (float offset : {-1.3f, 1.3f}) {
                Vector3 rail = add(midpoint, mul(side, offset));
                rail.y = 0.07f;
                DrawCube(rail, eastWest ? span : 0.12f, 0.12f, eastWest ? 0.12f : span, Muted);
            }
            for (float t = 0; t <= span; t += 2) {
                Vector3 tie = add(passage.from, mul(direction, t));
                tie.y = 0.025f;
                DrawCube(tie, eastWest ? 0.25f : 3.4f, 0.06f, eastWest ? 3.4f : 0.25f,
                         Color{51, 45, 38, 255});
            }
        }
        for (int end = 0; end < 2; ++end) {
            const auto at = end == 0 ? passage.from : passage.to;
            const Color color = passage.locked ? Gold : passage.closed(end) ? Rust : Teal;
            lantern(add(at, mul(side, -3.5f)), color, westernScene_.loaded());
            lantern(add(at, mul(side, 3.5f)), color, westernScene_.loaded());
            if (run.roomClear && passage.open() && passage.rooms[size_t(end)] == run.room &&
                distance(run.player.position, at) < 26) {
                // Small floor chevrons indicate open exits without floating instructions.
                const Vector3 outward = mul(direction, end == 0 ? 1.0f : -1.0f);
                for (float inset : {1.0f, 2.0f}) {
                    Vector3 tip = sub(at, mul(outward, inset));
                    tip.y = 0.075f;
                    const Vector3 base = sub(tip, mul(outward, 0.7f));
                    DrawLine3D(add(base, mul(side, 0.7f)), tip, Teal);
                    DrawLine3D(sub(base, mul(side, 0.7f)), tip, Teal);
                }
            }
            if (passage.closed(end)) {
                if (canyon) {
                    auto veil = color;
                    veil.a = 65;
                    DrawCubeV(mul(add(passage.gates[size_t(end)].min, passage.gates[size_t(end)].max), .5f),
                              sub(passage.gates[size_t(end)].max, passage.gates[size_t(end)].min), veil);
                }
                for (float offset = -3.5f; offset <= 3.5f; offset += 0.7f) {
                    Vector3 bar = add(at, mul(side, offset));
                    bar.y = 1.5f;
                    if (canyon)
                        DrawSphere({bar.x, .12f, bar.z}, .09f, color);
                }
                if (collisions)
                    DrawBoundingBox({passage.gates[size_t(end)].min, passage.gates[size_t(end)].max}, color);
            }
        }
    }
    for (const auto &coin : run.moneyPickups) {
        if (distance(run.player.position, coin.position) > 60)
            continue;
        const float phase = float(run.stats.duration) * 2 + coin.position.x + coin.position.z;
        const float bounce = coin.dropped && coin.age < .45f
                                 ? std::abs(std::sin(coin.age / .45f * 2 * Pi)) * (1 - coin.age / .45f) * 1.1f
                                 : 0;
        DrawCircle3D({coin.position.x, .07f, coin.position.z}, .45f, {1, 0, 0}, 90, Color{234, 187, 75, 150});
        for (int i = 0; i < std::min(coin.value, 3); ++i) {
            Vector3 center = add(coin.position, {float(i - 1) * .18f, 0, float(i % 2) * .12f});
            center.y = .4f + bounce + .05f * std::sin(phase + float(i));
            const Vector3 axis{std::cos(phase), 0, std::sin(phase)};
            const auto front = add(center, mul(axis, .07f));
            DrawCylinderEx(sub(center, mul(axis, .07f)), front, .25f, .25f, 12, Gold);
            DrawCylinderEx(front, add(front, mul(axis, .015f)), .16f, .16f, 12, Color{255, 225, 132, 255});
        }
    }
    for (const auto &key : run.arena.keys) {
        if (key.collected || !run.rooms[size_t(key.room)].cleared ||
            distance(run.player.position, key.position) > 60)
            continue;
        auto p = key.position;
        p.y = 1.1f + 0.1f * std::sin(float(run.stats.duration) * 3);
        DrawCircle3D(p, 0.28f, {0, 1, 0}, 0, Gold);
        DrawCube({p.x + 0.43f, p.y, p.z}, 0.65f, 0.12f, 0.12f, Gold);
        DrawCube({p.x + 0.65f, p.y - 0.14f, p.z}, 0.12f, 0.3f, 0.12f, Gold);
        DrawCircle3D({p.x, 0.06f, p.z}, 0.85f, {1, 0, 0}, 90, Gold);
    }
    for (int i = 0; i < RoomCount; ++i) {
        const auto &room = run.arena.rooms[size_t(i)];
        if (room.kind == RoomKind::Power && !run.rooms[size_t(i)].rewardTaken &&
            distance(run.player.position, room.objective) < 60) {
            const auto p = room.objective;
            DrawSphere({p.x, 1.3f, p.z}, .45f, Teal);
            DrawSphereWires({p.x, 1.3f, p.z}, .7f, 6, 8, Gold);
        }
    }
    if (distance(run.player.position, run.arena.miners) < 60) {
        const auto p = run.arena.miners;
        DrawCircle3D({p.x, .1f, p.z}, 2.3f, {1, 0, 0}, 90, run.rescued ? Muted : Teal);
    }
    if (!run.altarDestroyed && distance(run.player.position, run.arena.altar) < 60) {
        const auto p = run.arena.altar;
        DrawSphere({p.x, 1.1f, p.z}, .35f, Teal);
    }
    lantern(run.arena.entrance, Gold, westernScene_.loaded());
    lantern(run.arena.exit, run.room == Simulation::FinalRoom && run.roomClear ? Teal : Gold,
            westernScene_.loaded());
    if (run.room == Simulation::FinalRoom && run.roomClear)
        DrawCircle3D({run.arena.exit.x, 0.1f, run.arena.exit.z}, 1.8f, {1, 0, 0}, 90, Teal);
    std::vector<const Enemy *> drawnEnemies;
    for (int room = 0; room < RoomCount; ++room) {
        if (room != run.room && !visible(run.arena.rooms[size_t(room)].bounds))
            continue;
        const auto &group = run.roomEnemies(room);
        const auto partnerOf = [&](const Enemy &enemy) -> const Enemy * {
            const auto found = std::find_if(group.begin(), group.end(), [&](const Enemy &other) {
                return other.id == enemy.partner && other.alive;
            });
            return found == group.end() ? nullptr : &*found;
        };
        for (const auto &e : group) {
            if (!e.alive)
                continue;
            drawnEnemies.push_back(&e);
            if (e.id == hoveredEnemy)
                DrawCircle3D({e.position.x, 0.08f, e.position.z}, e.radius + 0.25f, {1, 0, 0}, 90, Rust);
            if (room == run.room)
                enemyWarning(e, run);
            const auto *partner = partnerOf(e);
            if (e.monster == monsterId(89) && e.partner) {
                if (partner && distance(e.position, partner->position) < 2.5f &&
                    run.arena.sight(e.position, partner->position))
                    DrawCylinderEx({e.position.x, .35f, e.position.z},
                                   {partner->position.x, .35f, partner->position.z}, .19f, .19f, 6,
                                   Color{133, 86, 81, 255});
            }
            if (e.kind == EnemyKind::Chainbound && e.id < e.partner && partner && partner->partner == e.id &&
                distance(e.position, partner->position) <= 8 &&
                run.arena.sight(e.position, partner->position)) {
                DrawCylinderEx(e.position, partner->position, 0.05f, 0.05f, 5, Rust);
                DrawLine3D(e.position, partner->position, Gold);
            }
            if (collisions)
                DrawSphereWires(e.position, e.radius, 6, 8, Rust);
        }
    }
    for (const auto &hazard : run.hazards)
        drawHazard(hazard);
    if (dynamiteArmed) {
        const auto trajectory = run.dynamiteTrajectory(run.player.aim);
        for (size_t i = 1; i < trajectory.size(); ++i)
            DrawLine3D(trajectory[i - 1], trajectory[i], Gold);
        auto landing = trajectory.back();
        DrawSphereWires(landing, .25f, 4, 8, Paper);
        landing.y = .09f;
        DrawCircle3D(landing, DynamiteRadius, {1, 0, 0}, 90, Gold);
    }
    if (playerModel_.loaded()) {
        if (!lighting.ready())
            shadow(run.player.position, 0.65f);
        if (!run.dead)
            DrawCircle3D({run.player.position.x, 0.06f, run.player.position.z}, 0.65f, {1, 0, 0}, 90, Teal);
        playerModel_.draw(run.player, run.dead, lighting.actorShader(), lighting.texture());
    } else {
        lighting.beginPrimitives();
        cowboy(run.player.position, run.player.facing, run.player.hurt > 0 ? Rust : Color{90, 145, 137, 255},
               1, false, !lighting.ready());
        lighting.endPrimitives();
    }
    if (run.player.dodge > 0)
        DrawSphereWires(run.player.position, 0.9f, 5, 8, Teal);
    for (const auto &p : run.projectiles) {
        Color color = p.hostile     ? (p.bounces > 0 ? Color{204, 132, 232, 255} : Rust)
                      : p.ghost     ? Teal
                      : p.lastRound ? Paper
                                    : Gold;
        if (p.kind == ProjectileKind::Rock || p.kind == ProjectileKind::ReturningHead)
            color = Color{182, 171, 141, 255};
        projectileMesh(p.position, p.radius, color);
    }
    // Keep triangles and lines in separate batches. Alternating for each projectile
    // creates thousands of tiny draw calls during a chain explosion.
    for (const auto &p : run.projectiles) {
        Color color = p.hostile     ? (p.bounces > 0 ? Color{204, 132, 232, 255} : Rust)
                      : p.ghost     ? Teal
                      : p.lastRound ? Paper
                                    : Gold;
        Vector3 tail = sub(p.position, mul(unit(p.velocity), p.hostile ? 0.35f : 0.6f));
        DrawLine3D(tail, p.position, color);
        if (p.kind == ProjectileKind::Hook) {
            DrawLine3D(p.origin, p.position, Gold);
            DrawSphereWires(p.position, 0.3f, 4, 6, Paper);
        }
        if (collisions) {
            DrawLine3D(p.previous, p.position, Paper);
            DrawSphereWires(p.position, p.radius, 4, 6, Teal);
        }
    }
    for (const auto &effect : run.visuals) {
        if (missionEffects_.loaded() && (effect.kind == 5 || effect.kind == 6)) continue;
        float t = 1 - effect.life / effect.maxLife;
        Color color = effect.kind == 0 ? Gold : effect.kind == 2 ? Teal : effect.kind == 4 ? Rust : Paper;
        color.a = static_cast<unsigned char>(180 * (1 - t));
        if (effect.kind == 5) {
            for (int i = 0; i < 8; ++i) {
                const float angle = float(i) * 2 * Pi / 8;
                auto p = add(effect.position, {std::cos(angle) * t * effect.radius * .6f, .3f + t * 1.8f,
                                               std::sin(angle) * t * effect.radius * .6f});
                const Color smoke = t < .3f ? Color{246, 163, 59, color.a} : Color{88, 77, 72, color.a};
                DrawSphereEx(p, (.3f + t * .65f) * (1 - t), 4, 6, smoke);
            }
        } else if (effect.kind == 0 || effect.kind == 4) {
            effectRings(effect.position, effect.radius * (0.3f + 0.7f * t), color);
        } else
            projectileMesh(effect.position, effect.radius * (1 - t), color);
    }
    DrawCircle3D({run.player.aim.x, 0.06f, run.player.aim.z}, 0.32f, {1, 0, 0}, 90, Gold);
    if (const auto goal = run.moveDestination()) {
        DrawCircle3D({goal->x, 0.08f, goal->z}, 0.48f, {1, 0, 0}, 90, Teal);
        DrawLine3D({goal->x - 0.22f, 0.08f, goal->z}, {goal->x + 0.22f, 0.08f, goal->z}, Teal);
        DrawLine3D({goal->x, 0.08f, goal->z - 0.22f}, {goal->x, 0.08f, goal->z + 0.22f}, Teal);
    }
    if (collisions) {
        DrawSphereWires(run.player.position, 0.48f, 6, 8, Teal);
        DrawLine3D(run.player.position, run.player.aim, Teal);
    }
    missionEffects_.draw(camera);
    westernScene_.drawOccluders();
    westernScene_.drawGlass();
    EndMode3D();
    postProcess_.end();
    if (run.room == run.arena.shopRoom) {
        const auto p = run.arena.rooms[size_t(run.room)].objective;
        const auto at = GetWorldToScreen({p.x, 2.6f, p.z}, camera);
        if (at.x > 0 && at.x < GetScreenWidth() && at.y > 0 && at.y < GetScreenHeight())
            text("SHOPKEEPER", at.x / sx_ - 39, at.y / sy_ - 8, 12, Gold);
    }
    auto outlineEligible = [](const Enemy &e) {
        return e.alive && !e.friendly && e.state != EnemyState::Buried && e.state != EnemyState::Teleporting;
    };
    if (std::any_of(drawnEnemies.begin(), drawnEnemies.end(),
                    [&](const Enemy *e) { return outlineEligible(*e); }))
        postProcess_.outlineOccluded(camera, [&] {
            for (const auto *e : drawnEnemies)
                if (outlineEligible(*e))
                    enemyModel(*e, false);
        });
    for (const auto &e : run.enemies)
        if (e.alive && (e.hp < e.maxHp || e.id == hoveredEnemy) && e.kind != EnemyKind::Boss) {
            Vector2 at = GetWorldToScreen(add(e.position, {0, 1.6f, 0}), camera);
            if (e.id == hoveredEnemy && e.kind == EnemyKind::Monster) {
                const auto &d = *monsterDefinition(e.monster);
                const std::string label = monsterIdText(d.id) + " / " + d.name;
                text(label, at.x / sx_ - 60, at.y / sy_ - 25, 12, d.roomHazard ? Gold : Paper);
            }
            DrawRectangle(int(at.x) - 18, int(at.y) - 5, 36, 4, Ink);
            DrawRectangle(int(at.x) - 18, int(at.y) - 5, int(36 * std::max(0.0f, e.hp / e.maxHp)), 4, Rust);
        }
}
Action Renderer::hub(const Game &game) {
    if (!loadedHub_ || *loadedHub_ != game.activeHub) {
        townScene_.load(game.hubDirectory());
        loadedHub_ = game.activeHub;
    }
    townScene_.setArtPoc(artPoc);
    playerModel_.artPoc = characterModels_.artPoc = townScene_.artPoc();
    const auto &town = game.town;
    townScene_.applyAnimation(game.townObjects);
    const auto &world = game.campaign.data().world;
    playerModel_.update(town.player, town.time, &town);
    animalModels_.prepare(game.animals);
    characterModels_.prepare(game.characters);
    townScene_.setPlayerOcclusion(game.camera, town.player.position);
    townScene_.prepareLighting(game.camera, [&](Shader depth) {
        playerModel_.draw(town.player, false, depth);
        animalModels_.draw(game.animals, depth);
        characterModels_.draw(game.characters, depth);
    });
    postProcess_.begin(WorldSky, distance(game.camera.position, game.camera.target), townScene_.artPoc());
    BeginMode3D(game.camera);
    townScene_.draw(town.player.position);
    animalModels_.draw(game.animals, townScene_.actorShader(), townScene_.shadowTexture());
    characterModels_.draw(game.characters, townScene_.actorShader(), townScene_.shadowTexture());
    const auto board = town.mission;
    DrawCylinder({board.x, board.y, board.z}, .09f, .12f, 1.8f, 6, Color{62, 42, 30, 255});
    DrawCube({board.x, board.y + 1.6f, board.z}, 1.5f, .95f, .12f, Color{91, 62, 39, 255});
    DrawCube({board.x, board.y + 1.6f, board.z + .075f}, 1.05f, .65f, .025f, Paper);
    DrawCircle3D({board.x, board.y + .06f, board.z}, 1.2f, {1, 0, 0}, 90, Gold);
    if (playerModel_.loaded())
        playerModel_.draw(town.player, false, townScene_.actorShader(), townScene_.shadowTexture());
    else
        cowboy(town.player.position, town.player.facing, Teal, 1);
    if (auto target = town.destination())
        DrawCircle3D(add(*target, {0, .06f, 0}), .4f, {1, 0, 0}, 90, Teal);
    if (game.collisionDebug)
        for (auto p : town.route())
            DrawCube(add(p, {0, .07f, 0}), .16f, .1f, .16f, Teal);
    townScene_.drawEffects(game.camera);
    townScene_.drawOccluders();
    townScene_.draw(town.player.position, true);
    EndMode3D();
    postProcess_.end();
    if (game.activeHub == HubKind::Redstone) {
        const TownCharacterState *nearest = nullptr;
        const char *caption = nullptr;
        float closest = 8;
        for (const auto &resident : game.characters.residents()) {
            const auto &id = resident.definition.id;
            const char *name = id == "story-commander" ? "COMMANDER" :
                id == "story-outlaw" ? "OUTLAW" : id == "story-wife" ? "SURVEYOR'S WIFE" :
                id == "story-spiritualist" ? "SPIRITUALIST" : id == "story-scout" ? "SCOUT" :
                id == "story-merchant" ? "MERCHANT" : nullptr;
            const float d = distance(resident.position, town.player.position);
            if (name && d < closest) { nearest = &resident; caption = name; closest = d; }
        }
        if (nearest) {
            const auto point = GetWorldToScreen(add(nearest->position, {0,2.6f,0}), game.camera);
            if (point.x > 0 && point.y > 0 && point.x < GetScreenWidth() && point.y < GetScreenHeight()) {
                const float width = MeasureText(caption, int(12 * sy_)) / sx_ + 20;
                panel(point.x / sx_ - width / 2, point.y / sy_ - 8, width, 25, Panel);
                text(caption, point.x / sx_ - width / 2 + 10, point.y / sy_ - 2, 12, Paper);
            }
        }
    }
    const auto at = GetWorldToScreen(add(board, {0, 2.7f, 0}), game.camera);
    if (at.x > 0 && at.x < GetScreenWidth() && at.y > 0 && at.y < GetScreenHeight()) {
        panel(at.x / sx_ - 48, at.y / sy_ - 10, 96, 24, Panel);
        text(game.activeHub == HubKind::Redstone ? "BADLANDS" : "MISSIONS",
             at.x / sx_ - 36, at.y / sy_ - 4, 13, Gold);
    }
    panel(24, 24, 386, 98, Panel);
    text(hubName(game.activeHub), 42, 38, 28, Paper);
    text((game.activeHub == HubKind::Redstone ? "RAIL LINE CLOSED / MONEY " : "HOME / MONEY ") +
             number(world.money), 43, 73, 12, Gold);
    text("PEOPLE " + std::to_string(world.population) + "   PROSPERITY " + std::to_string(world.prosperity) +
             "   LAW " + std::to_string(world.law),
         43, 98, 11, Muted);
    if (!game.missionMenu && !game.paused) {
        panel(24, 700, 676, 76, Panel);
        if (button(game.walkingToMission ? "WALKING TO MISSIONS" : "MISSIONS", 38, 712, 255, 44, true))
            return Action::Missions;
        if (button("RUN HISTORY", 305, 712, 179, 44))
            return Action::History;
        if (button("PAUSE", 496, 712, 188, 44))
            return Action::Pause;
        panel(856, 646, 400, 130, Panel);
        const auto other = secondaryTravelHub(game.activeHub);
        if (button(std::string("TRAVEL TO ") + hubShortName(other), 870, 658, 372, 44))
            return other == HubKind::Redstone ? Action::TravelRedstone : Action::TravelFrontier;
        if (button(std::string("TRAVEL TO ") + hubShortName(primaryTravelHub(game.activeHub)),
                   870, 712, 372, 44))
            return Action::TravelHub;
    }
    if (game.debug && game.debugPanelOpen && !game.missionMenu && !game.paused) {
        panel(24, 140, 456, 105, Panel);
        text("CHEATS ON / F10 route / G haunting", 40, 157, 13, Teal);
        if (button(game.resetArmed ? "CONFIRM RESET (backup saved)" : "RESET CAMPAIGN", 40, 189, 420, 38))
            return Action::Reset;
    }
    if (game.missionMenu) {
        const auto &theme = missionTheme(game.offeredTheme());
        panel(0, 0, 1280, 800, Color{8, 14, 15, 155});
        panel(240, 104, 800, 588, Panel);
        text(std::string(hubName(game.activeHub)) + " / MISSIONS", 270, 130, 17, Gold);
        text(theme.title, 267, 173, 38, Paper);
        wrap(game.offeredTheme() == MissionTheme::Canyon
                 ? "Face Isaac's monsters. Rescue the miners, break the altar and clear the Infested Mesa."
             : world.bossDefeated
                 ? "Bring home anyone still missing and settle unfinished business on the frontier."
                 : "Face Western outlaws. Bring the miners home, break the altar and defeat the Hollow "
                   "Sheriff.",
             270, 238, 727, 21, Paper);
        text("Fifteen changing rooms. Choose the setting; your seed repeats its layout.", 270, 323, 15,
             Muted);
        if (button("SEEDED THEME", 270, 354, 230, 34, game.themeChoice == ThemeChoice::Seeded))
            return Action::ThemeSeeded;
        if (button("WESTERN MINE", 510, 354, 239, 34, game.themeChoice == ThemeChoice::Mine))
            return Action::ThemeMine;
        if (button("ISAAC CANYON", 759, 354, 249, 34, game.themeChoice == ThemeChoice::Canyon))
            return Action::ThemeCanyon;
        panel(270, 402, 460, 65, Ink);
        text("MISSION SEED", 287, 413, 12, Muted);
        text(game.seedText.empty() ? "Type a seed..." : game.seedText, 287, 437, 20, Gold);
        if (button("NEW MISSION", 748, 408, 260, 51))
            return Action::NewSeed;
        if (game.offeredTheme() == MissionTheme::Canyon) {
            if (button(game.visualSettings.canyonRiver ? "RIVER ON" : "RIVER OFF", 748, 480, 260, 34))
                return Action::ToggleCanyonRiver;
            text("Same seed and river setting repeat the terrain.", 270, 490, 13, Muted);
        } else {
            text("Replay with the same seed and theme. New Mission chooses a fresh seed.", 270, 482, 13,
                 Muted);
        }
        if (button(game.offeredTheme() == MissionTheme::Canyon ? "LEAVE FOR THE CANYON"
                                                               : "LEAVE FOR THE MINE",
                   270, 529, 738, 59, true))
            return Action::Launch;
        if (button("BACK TO TOWN", 270, 609, 738, 43))
            return Action::CloseMissions;
    } else if (game.paused) {
        panel(0, 0, 1280, 800, Color{8, 14, 15, 155});
        panel(344, 134, 592, 578, Panel);
        text(hubName(game.activeHub), 377, 167, 30, Paper);
        wrap("Walk with WASD or click the ground. Scroll to zoom; hold the middle button and drag to "
             "rotate. Visit the mission board to depart.",
             378, 226, 514, 17, Muted);
        for (size_t i = 0; i < world.npcs.size(); ++i)
            wrap(world.npcs[i].name + ": " + npcDialogue(world, i), 378, 310 + float(i) * 48, 514, 13, Paper);
        if (button("KEEP EXPLORING", 378, 485, 514, 50, true))
            return Action::Resume;
        if (button("TOWN EDITOR", 378, 547, 250, 43))
            return Action::EditTown;
        if (button("QUIT", 642, 547, 250, 43))
            return Action::Quit;
        if (button(std::string("TRAVEL TO ") + hubShortName(primaryTravelHub(game.activeHub)),
                   378, 603, 514, 43))
            return Action::TravelHub;
        const auto other = secondaryTravelHub(game.activeHub);
        if (button(std::string("TRAVEL TO ") + hubShortName(other), 378, 655, 514, 43))
            return other == HubKind::Redstone ? Action::TravelRedstone : Action::TravelFrontier;
    }
    return Action::None;
}
void Renderer::dungeonMap(const Game &game) {
    const auto &run = *game.run;
    panel(1040, 170, 216, 192, Panel);
    text(run.arena.theme == MissionTheme::Canyon ? "CANYON TRAILS" : "MINE PASSAGES", 1053, 183, 12, Gold);
    const auto totalPowers =
        std::count_if(run.arena.rooms.begin(), run.arena.rooms.end(),
                      [](const RoomLayout &room) { return room.kind == RoomKind::Power; });
    text("KEYS " + std::to_string(run.keys) + "   POWERS " + std::to_string(run.powerUpsTaken) + " / " +
             std::to_string(totalPowers),
         1053, 201, 11, Paper);
    text("MONEY " + number(run.money()), 1053, 216, 11, Gold);
    const auto &bounds = run.arena.bounds;
    const float scale = std::min(188 / (bounds.max.x - bounds.min.x), 120 / (bounds.max.z - bounds.min.z));
    auto point = [&](Vector3 p) -> Vector2 {
        return {1148 + (p.x - (bounds.min.x + bounds.max.x) / 2) * scale,
                287 + (p.z - (bounds.min.z + bounds.max.z) / 2) * scale};
    };
    auto rectangle = [&](Box box, Color color) {
        auto a = point(box.min), b = point(box.max);
        DrawRectangleRec(
            {a.x * sx_, a.y * sy_, std::max(1.0f, (b.x - a.x) * sx_), std::max(1.0f, (b.y - a.y) * sy_)},
            color);
    };
    for (const auto &passage : run.arena.passages)
        rectangle(passage.floor, passage.locked ? Gold : passage.open() ? Teal : Rust);
    for (int i = 0; i < RoomCount; ++i) {
        for (const auto &box : run.arena.rooms[size_t(i)].floors)
            rectangle(box, i == run.room ? Gold : run.rooms[size_t(i)].cleared ? Teal : Border);
        auto at = point(run.arena.rooms[size_t(i)].center);
        const auto kind = run.arena.rooms[size_t(i)].kind;
        std::string label = kind == RoomKind::Shop    ? "S"
                            : kind == RoomKind::Power ? "P"
                            : kind == RoomKind::Boss  ? "B"
                            : kind == RoomKind::Empty ? "E"
                                                      : std::to_string(i + 1);
        for (const auto &key : run.arena.keys)
            if (key.room == i && !key.collected && run.rooms[size_t(i)].visited)
                label = "K";
        text(label, at.x - 4, at.y - 4, 9, run.rooms[size_t(i)].visited ? Ink : Paper);
    }
    auto at = point(run.player.position);
    DrawCircleV({at.x * sx_, at.y * sy_}, 3.5f * std::min(sx_, sy_), Paper);
}
Action Renderer::expedition(const Game &game) {
    const auto &run = *game.run;
    drawWorld(run, game.camera, game.collisionDebug, game.hoveredEnemy, game.deathTime, game.dynamiteArmed);
    panel(24, 22, 358, 90, Panel);
    text(std::string(missionTheme(run.arena.theme).region) + " / " + std::to_string(run.room + 1) + " OF " +
             std::to_string(RoomCount),
         42, 35, 12, Gold);
    const int physicalRoom = run.arena.roomAt(run.player.position);
    text(physicalRoom < 0                     ? missionTheme(run.arena.theme).passage
         : physicalRoom == run.arena.shopRoom ? "Trader's Rest"
                                              : Simulation::roomName(physicalRoom, run.arena.theme),
         41, 58, 25, Paper);
    text("SEED " + game.seedText + "   /   " + timeLabel(run.stats.duration), 42, 91, 12, Muted);
    panel(964, 22, 292, 131, Panel);
    text("BRING SOMETHING BACK", 982, 37, 13, Gold);
    text(run.rescued ? "[+] Six miners safe" : "[ ] Miners / chamber 3", 982, 65, 15,
         run.rescued ? Teal : Paper);
    text(run.altarDestroyed ? "[+] Altar destroyed" : "[ ] Altar / chamber 4", 982, 91, 15,
         run.altarDestroyed ? Teal : Muted);
    text(run.arena.theme == MissionTheme::Canyon
             ? (run.bossKilled ? "[+] Infested Mesa cleared" : "[ ] Clear the Infested Mesa")
             : (run.bossKilled ? "[+] Sheriff defeated" : "[ ] Sheriff / locked court"),
         982, 117, 15, run.bossKilled ? Teal : Muted);
    dungeonMap(game);
    if (const auto *boss = run.boss()) {
        panel(412, 24, 476, 70, Panel);
        text("THE HOLLOW SHERIFF / PHASE " + std::to_string(boss->phase + 1), 429, 37, 14, Paper);
        panel(429, 66, 442, 9, Ink);
        DrawRectangle(int(429 * sx_), int(66 * sy_), int(442 * sx_ * std::max(0.0f, boss->hp / boss->maxHp)),
                      int(9 * sy_), Rust);
    } else {
        const auto kind = run.arena.rooms[size_t(run.room)].kind;
        text(run.roomClear ? (kind == RoomKind::Shop    ? "SHOP / NO ENEMIES"
                              : kind == RoomKind::Empty ? "QUIET ROOM / NO ENEMIES"
                              : kind == RoomKind::Power ? "POWER CACHE"
                                                        : "CHAMBER CLEARED")
                           : number(run.roomThreats()) + " HOSTILES",
             440, 38, 14, run.roomClear ? Teal : Paper);
    }
    panel(24, 674, 344, 101, Panel);
    text("HEALTH", 41, 686, 12, Muted);
    text(std::to_string(int(std::max(0.0f, run.player.hp))) + " / " + std::to_string(int(run.player.maxHp)),
         264, 685, 14, Paper);
    panel(41, 709, 310, 9, Ink);
    DrawRectangle(int(41 * sx_), int(709 * sy_),
                  int(310 * sx_ * std::clamp(run.player.hp / run.player.maxHp, 0.0f, 1.0f)), int(9 * sy_),
                  run.player.hp < run.player.maxHp * 0.3f ? Rust : Teal);
    for (int i = 0; i < 6; ++i) {
        Rectangle r{(43 + float(i) * 25) * sx_, 736 * sy_, 15 * sx_, 23 * sy_};
        DrawRectangleRec(r, i == run.player.nextRound - 1  ? Gold
                            : i < run.player.nextRound - 1 ? Muted
                                                           : Color{54, 58, 52, 255});
    }
    text("ROUND " + std::to_string(run.player.nextRound) + " / 6", 209, 741, 13, Muted);
    text(run.player.dodgeCooldown <= 0 ? "DODGE READY" : "DODGE RECOVERING", 397, 752, 12, Muted);
    text(game.debug ? "F1 / CHEATS ON" : "F1 / CHEATS", 806, 752, 12, game.debug ? Teal : Gold);
    Action controls = Action::None;
    const std::string dynamiteLabel = std::string(game.dynamiteArmed       ? "CANCEL THROW / "
                                                  : game.dynamiteThrowMode ? "THROW DYNAMITE / "
                                                                           : "PLACE DYNAMITE / ") +
                                      std::to_string(run.dynamite);
    if (!game.paused && !run.rewardOpen && !run.shopOpen && !run.dead) {
        if (button(game.dynamiteThrowMode ? "MODE: THROW" : "MODE: PLACE", 24, 594, 276, 28))
            controls = Action::DynamiteMode;
        if (button(dynamiteLabel, 24, 626, 276, 34, game.dynamiteArmed))
            controls = Action::Dynamite;
        const std::string interaction = run.nearbyInteraction();
        if (!interaction.empty()) {
            if (button(interaction, 396, 690, 186, 44, true))
                controls = Action::Interact;
        } else {
            panel(396, 690, 186, 44, Panel);
            text("EXPLORE", 414, 704, 18, Muted);
        }
        if (button("DODGE", 598, 690, 154, 44))
            controls = Action::Dodge;
        if (button("PAUSE", 768, 690, 168, 44))
            controls = Action::Pause;
    }
    if (!run.items.empty()) {
        panel(964, 571, 292, 204, Panel);
        text("BORROWED POWER", 980, 586, 12, Gold);
        for (int i = 0; i < ItemCount; ++i) {
            size_t stacks = run.itemStacks(ItemId(i));
            text(std::string(stacks ? "+ " : "  ") + itemDefinition(ItemId(i)).name +
                     (stacks > 1 ? " x" + number(stacks) : ""),
                 981, 612 + float(i) * 29, 14, stacks ? Paper : Color{79, 89, 82, 255});
        }
    }
    if (run.messageTime > 0) {
        panel(333, 605, 611, 51, Panel);
        wrap(run.message, 351, 620, 575, 14, Paper);
    }
    if (run.rewardOpen && !game.paused) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{9, 15, 18, 210});
        text("THE MINE OFFERS A BARGAIN", 204, 213, 37, Paper);
        text("Take ONE power. The other is lost. This cache can only be used once.", 204, 265, 16, Muted);
        for (int i = 0; i < int(run.offers.size()); ++i) {
            float x = 339 + float(i) * 301;
            const auto &item = itemDefinition(run.offers[size_t(i)]);
            panel(x, 314, 279, 279, Panel);
            text(item.rarity, x + 20, 337, 12, std::string(item.rarity) == "CURSED" ? Rust : Gold);
            wrap(item.name, x + 20, 377, 237, 25, Paper);
            wrap(item.description, x + 20, 453, 237, 16, Muted);
            if (button("TAKE IT  [" + std::to_string(i + 1) + "]", x + 20, 540, 239, 36, true))
                return Action(int(Action::Reward0) + i);
        }
    }
    if (run.shopOpen && !game.paused) {
        panel(0, 0, 1280, 800, Color{9, 15, 18, 210});
        panel(170, 155, 940, 495, Panel);
        text("TRADER'S REST", 199, 181, 34, Paper);
        text("MONEY " + number(run.money()), 854, 189, 20, Gold);
        text("One of each, traveler. Powers last for this expedition.", 200, 231, 17, Muted);
        for (int i = 0; i < 3; ++i) {
            const auto &offer = run.shopOffers[size_t(i)];
            const bool medicine = offer.kind == ShopOfferKind::Medicine;
            const auto &item = itemDefinition(offer.item);
            const float x = 200 + float(i) * 295;
            panel(x, 280, 275, 287, Ink);
            text(medicine ? "SUPPLIES" : item.rarity, x + 18, 298, 12,
                 !medicine && offer.item == ItemId::Judas ? Rust : Gold);
            wrap(medicine ? "Field Medicine" : item.name, x + 18, 335, 235, 25, Paper);
            wrap(medicine ? "Restore up to 40 health. Maximum health stays the same." : item.description,
                 x + 18, 410, 237, 15, Muted);
            text(std::to_string(offer.price) + " COINS", x + 18, 488, 16, Gold);
            const auto unavailable = run.shopUnavailable(i);
            if (unavailable.empty()) {
                if (button("BUY", x + 18, 519, 239, 34, true))
                    return Action(int(Action::BuyShop0) + i);
            } else {
                panel(x + 18, 519, 239, 34, Border);
                text(unavailable, x + 29, 530, 12, Muted);
            }
        }
        const auto refillUnavailable = run.shopUnavailable(3);
        if (refillUnavailable.empty()) {
            if (button("BUY 3 DYNAMITE / 15 COINS", 200, 591, 552, 38, true))
                return Action::BuyShop3;
        } else {
            panel(200, 591, 552, 38, Border);
            text("3 DYNAMITE / " + refillUnavailable, 218, 604, 13, Muted);
        }
        if (button("LEAVE SHOP", 779, 591, 295, 38))
            return Action::CloseShop;
    }
    if (game.paused) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{9, 15, 18, 210});
        panel(407, 240, 466, 318, Panel);
        text("TAKE A BREATH", 435, 269, 30, Paper);
        wrap("Retreat ends your build and changes the town. Closing the game also counts as retreat.", 436,
             326, 402, 17, Muted);
        text("Click to move, attack or interact. Shift holds position.", 436, 389, 12, Muted);
        text("Hold middle + drag to rotate. Scroll to zoom. Space dodges.", 436, 407, 11, Muted);
        if (button("KEEP GOING   [ESC]", 436, 423, 408, 45, true))
            return Action::Resume;
        if (button(std::string("RETREAT TO ") + hubShortName(game.activeHub) + "   [T]",
                   436, 486, 408, 45))
            return Action::Retreat;
        if (game.debug && !run.dead) {
            panel(895, 240, 361, 318, Panel);
            text("PLAYER SETTINGS", 915, 263, 22, Gold);
            text("BASE HEALTH", 915, 309, 13, Muted);
            text(std::to_string(int(run.player.baseHealth)), 915, 333, 25, Paper);
            if (button("-", 1134, 307, 44, 44))
                return Action::HealthDown;
            if (button("+", 1192, 307, 44, 44))
                return Action::HealthUp;
            text("Maximum with items: " + std::to_string(int(run.player.maxHp)), 915, 369, 13, Muted);
            text("SHOT DAMAGE", 915, 403, 13, Muted);
            text(std::to_string(int(run.player.shotDamage)), 915, 427, 25, Paper);
            if (button("-", 1134, 402, 44, 44))
                return Action::DamageDown;
            if (button("+", 1192, 402, 44, 44))
                return Action::DamageUp;
            if (button("RESTORE DEFAULTS", 915, 474, 321, 40))
                return Action::ResetPlayer;
            text("Applies now and to later missions this session.", 915, 532, 11, Muted);
        }
    }
    return controls;
}
Action Renderer::summary(const Game &game, const RunSummary &s, bool history) {
    text(std::string(hubName(game.activeHub)) + (history ? " / RUN HISTORY" : " / EXPEDITION RESOLVED"), 60,
         42, 14, Gold);
    text(outcomeTitle(s), 58, 92, 38, Paper);
    text("RUN " + number(s.id) + "  /  SEED " + number(s.seed) + "  /  " + timeLabel(s.stats.duration) +
             "  /  " + s.expedition + (s.interrupted ? "  /  PARTIAL CHECKPOINT" : ""),
         60, 150, 15, Muted);
    text("WALLET " + number(game.campaign.data().world.money), 60, 178, 13, Gold);
    text("SPENT THIS RUN " + number(s.moneySpent), 730, 178, 13, Muted);
    const std::array<std::pair<std::string, std::string>, 5> values{
        {{"ENEMIES KILLED", number(s.stats.kills)},
         {"BULLETS / PROJECTILES", number(s.stats.shots) + " / " + number(s.stats.projectiles)},
         {"EXPLOSIONS", number(s.stats.explosions)},
         {"LARGEST KILL CHAIN", number(s.stats.largestKillChain)},
         {"MONEY FOUND", number(s.moneyCollected)}}};
    for (size_t i = 0; i < values.size(); ++i) {
        float x = 60 + float(i) * 236;
        panel(x, 203, 216, 99, Panel);
        text(values[i].first, x + 16, 219, 12, Muted);
        text(values[i].second, x + 16, 250, 29, Paper);
    }
    panel(60, 336, 512, 316, Panel);
    text("WHAT YOU LOST", 80, 357, 16, Gold);
    int row = 0;
    for (int i = 0; i < ItemCount; ++i) {
        auto n = std::count(s.items.begin(), s.items.end(), ItemId(i));
        if (n) {
            text(itemDefinition(ItemId(i)).name + (n > 1 ? " x" + std::to_string(n) : ""), 81,
                 399 + float(row++) * 36, 20, Paper);
        }
    }
    if (row == 0)
        wrap("A plain revolver. The next expedition may tell a different story.", 81, 405, 440, 19, Muted);
    text("Deepest chain: " + number(s.stats.maxDepth) +
             "   Peak projectiles: " + number(s.stats.maxProjectiles),
         81, 604, 13, Muted);
    text("Safety suppressions: " + number(s.stats.suppressed), 81, 627, 12, Muted);
    panel(594, 336, 626, 316, Panel);
    text("WHAT THE TOWN KEEPS", 614, 357, 16, Teal);
    float y = 398;
    for (const auto &line : s.consequences) {
        wrap(line, 614, y, 575, 15, Paper);
        y += line.size() > 68 ? 49 : 32;
    }
    text("THE BUILD IS GONE. THE CONSEQUENCES REMAIN.", 60, 693, 23, Gold);
    if (button(std::string("RETURN TO ") + hubShortName(game.activeHub), 60,
               740, 341, 42, true))
        return Action::Hub;
    if (history) {
        text(std::to_string(game.historyIndex + 1) + " / " +
                 std::to_string(game.campaign.data().history.size()),
             641, 752, 14, Muted);
        if (button("< PREVIOUS", 755, 740, 216, 42))
            return Action::Previous;
        if (button("NEXT >", 990, 740, 230, 42))
            return Action::Next;
    } else if (button("INSPECT RUN HISTORY", 871, 740, 349, 42))
        return Action::History;
    return Action::None;
}
void Renderer::debugPanel(const Game &game) {
    if (!game.run)
        return;
    const auto &run = *game.run;
    panel(24, 133, 515, 459, Color{12, 22, 25, 240});
    text("CHEAT SHORTCUTS / ` TO HIDE", 41, 148, 16, Teal);
    text("F2 invincible " + std::string(run.godMode ? "ON" : "OFF") + "    Shift+F2 heal", 41, 179, 13,
         Paper);
    text("F3 kill enemies    Shift+F3 clear whole room", 41, 199, 13, Paper);
    text("F4 spawn 20    F5 spawn 100    Shift+F4 selected", 41, 219, 13, Paper);
    text("F6 all items       Shift+F6 add 3 keys", 41, 239, 13, Paper);
    text("F7 final encounter  F8 win   F9 die", 41, 259, 13, Paper);
    text("F10 collisions     F11 stress scene", 41, 279, 13, Paper);
    text("F12 next room      Shift+F12 restart room", 41, 299, 13, Paper);
    text("P freeze " + std::string(game.paused ? "ON" : "OFF") + "    O slow " + (game.slow ? "ON" : "OFF"),
         41, 319, 13, Paper);
    text("[/] item   I grant   V five   M rescue   ,/. enemy", 41, 339, 13, Paper);
    const auto &testEnemy = monsterCatalog()[size_t(game.selectedMonster)];
    text(monsterIdText(testEnemy.id) + " / " + testEnemy.name, 41, 366, 14, Gold);
    text("ENEMIES " + number(run.livingEnemies()) + "   PROJECTILES " + number(run.projectiles.size()) +
             "   EVENTS " + number(run.queuedEvents()),
         41, 397, 13, Paper);
    text("CHAINS " + number(run.chains.size()) + "   DEPTH " + number(run.stats.maxDepth) + "   SUPPRESSED " +
             number(run.stats.suppressed),
         41, 420, 13, Paper);
    text("SPLITS " + number(run.stats.splits) + "   BOUNCES " + number(run.stats.bounces) + "   GHOSTS " +
             number(run.stats.ghosts),
         41, 443, 13, Paper);
    text("Shift+B refill dynamite   -/+ damage   Home defaults", 41, 466, 13, Teal);
    if (!run.chains.empty()) {
        auto oldest = std::min_element(run.chains.begin(), run.chains.end(),
                                       [](const auto &a, const auto &b) { return a.first < b.first; });
        const auto &chain = oldest->second;
        text("LIVE #" + number(oldest->first) + "  work " + number(chain.accepted) + "  queued " +
                 number(chain.queued) + "  flying " + number(chain.active),
             41, 493, 12, Teal);
    }
    float y = 519;
    int rows = 0;
    for (auto it = run.logs.rbegin(); it != run.logs.rend() && rows < 3; ++it, ++rows) {
        text("#" + number(it->id) + " " + it->reason + " x" + number(it->suppressed), 41, y, 12, Muted);
        y += 20;
    }
    if (run.logs.empty())
        text("No chains have reached a safety limit.", 41, y, 12, Muted);
}
Action Renderer::audioPanel(const Game &game) {
    panel(24, 240, 296, 370, Panel);
    text("AUDIO", 43, 263, 22, Gold);
    const char *status = game.audioStatus == AudioStatus::Disabled      ? "Disabled for this launch"
                         : game.audioStatus == AudioStatus::Unavailable ? "Audio unavailable"
                                                                        : "Sound, music and surroundings";
    text(status, 43, 294, 12, Muted);
    const std::array<const char *, 4> labels{"MASTER", "EFFECTS", "AMBIENCE", "MUSIC"};
    const auto &s = game.audioSettings;
    const std::array<float, 4> values{s.master, s.effects, s.ambience, s.music};
    for (size_t i = 0; i < labels.size(); ++i) {
        const float y = 321 + float(i) * 52;
        text(labels[i], 43, y, 12, Muted);
        text(std::to_string(int(std::round(values[i] * 100))) + "%", 43, y + 19, 18, Paper);
        if (button("-", 211, y, 38, 37))
            return Action(int(Action::MasterDown) + int(i) * 2);
        if (button("+", 264, y, 38, 37))
            return Action(int(Action::MasterUp) + int(i) * 2);
    }
    if (button(s.muted ? "UNMUTE" : "MUTE", 43, 550, 122, 39))
        return Action::AudioMute;
    if (button("TEST", 180, 550, 122, 39))
        return Action::AudioTest;
    return Action::None;
}
Action Renderer::draw(const Game &game) {
    westernScene_.setVegetationDensity(game.visualSettings.vegetation);
    setGroundDetail(game.visualSettings.groundDetail);
    sx_ = float(GetScreenWidth()) / 1280;
    sy_ = float(GetScreenHeight()) / 800;
    ClearBackground(Ink);
    Action action = Action::None;
    switch (game.screen) {
    case Screen::Hub:
        action = hub(game);
        break;
    case Screen::Expedition:
        if (game.run)
            action = expedition(game);
        break;
    case Screen::Summary:
        action = summary(game, game.lastSummary, false);
        break;
    case Screen::History:
        if (const auto *s = game.inspectedHistory())
            action = summary(game, *s, true);
        else {
            text("NO EXPEDITIONS YET", 80, 140, 40, Paper);
            text("Bring back a story worth remembering.", 82, 211, 20, Muted);
            if (button(std::string("BACK TO ") + hubShortName(game.activeHub), 82,
                       290, 365, 51, true))
                action = Action::Hub;
        }
        break;
    }
    if (game.paused && (game.screen == Screen::Hub || game.screen == Screen::Expedition)) {
        const auto audioAction = audioPanel(game);
        if (audioAction != Action::None)
            action = audioAction;
        panel(24, 624, 296, 137, Panel);
        text("VEGETATION", 43, 644, 22, Gold);
        text("Generated missions", 43, 674, 12, Muted);
        text(std::to_string(game.visualSettings.vegetation) + "%", 43, 707, 22, Paper);
        if (button("LESS", 143, 700, 75, 39))
            action = Action::VegetationLess;
        if (button("MORE", 229, 700, 75, 39))
            action = Action::VegetationMore;
        if (game.screen == Screen::Expedition) {
            panel(895, 580, 361, 105, Panel);
            text("GROUND SURFACE", 915, 599, 22, Gold);
            if (button(game.visualSettings.groundDetail ? "DETAIL ON" : "DETAIL OFF", 915, 634, 321, 34))
                action = Action::ToggleGroundDetail;
        }
    }
    if (game.debug && game.debugPanelOpen && game.run && !game.paused && !game.run->rewardOpen &&
        !game.run->shopOpen)
        debugPanel(game);
    if (!game.error.empty()) {
        panel(24, 560, 1232, 81, Color{76, 34, 30, 250});
        wrap(game.error, 42, 578, 1196, 15, Paper);
    }
    if (game.screen == Screen::Hub || game.screen == Screen::Expedition) {
        panel(1040, 2, 116, 18, Panel);
        text("ZOOM " + std::to_string(int(std::lround(game.cameraZoomPercent()))) + "%", 1050, 5, 12, Teal);
    }
    panel(1160, 2, 96, 18, Panel);
    text(std::to_string(GetFPS()) + " FPS", 1170, 5, 12, Teal);
    return action;
}
} // namespace dw
