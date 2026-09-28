#pragma once
#include "combat/Simulation.hpp"

namespace dw {
inline void drawMonsterModel(const Enemy &e, bool drawShadow = true) {
    const auto &d = *monsterDefinition(e.monster);
    const int type = e.monster / 10000, variant = e.monster / 100 % 100;
    const std::array<Color, 8> palette{{{177, 92, 85, 255},
                                        {127, 57, 56, 255},
                                        {114, 140, 127, 255},
                                        {183, 140, 91, 255},
                                        {124, 111, 152, 255},
                                        {115, 138, 68, 255},
                                        {195, 109, 53, 255},
                                        {107, 63, 94, 255}}};
    Color skin = e.flash > 0 ? Color{245, 233, 206, 255} : palette[size_t((type + variant) % 8)];
    const float time = e.animationTime();
    if (type == 884 && std::fmod(time, .7f) < .16f)
        skin = {240, 206, 65, 255};
    const Color dark{41, 31, 35, 255}, bone{210, 193, 154, 255}, blood{153, 42, 49, 255};
    const auto dir = unit(e.facing), side = Vector3{-dir.z, 0, dir.x};
    auto p = e.position;
    p.y += e.lift;
    const float r = e.radius;
    if (drawShadow)
        DrawCircle3D({p.x, .04f, p.z}, r, {1, 0, 0}, 90, {43, 34, 35, 110});
    if (e.state == EnemyState::Buried || e.state == EnemyState::Teleporting) {
        DrawCircle3D({p.x, .08f, p.z}, r * .8f, {1, 0, 0}, 90, skin);
        return;
    }
    if (e.state == EnemyState::Collapsed) {
        DrawCylinder({p.x, .05f, p.z}, r, r * 1.2f, .2f, 9, skin);
        DrawSphereEx({p.x, .3f, p.z}, r * .32f, 5, 7, blood);
        return;
    }
    auto sphere = [&](Vector3 at, float radius, Color c) { DrawSphereEx(at, radius, 7, 10, c); };
    auto eyes = [&](Vector3 at, float scale = 1) {
        for (float sign : {-1.f, 1.f}) {
            auto eye = add(add(at, mul(dir, r * .77f)), mul(side, sign * r * .33f));
            sphere(eye, r * .2f * scale, bone);
            sphere(add(eye, mul(dir, r * .14f)), r * .11f * scale, dark);
        }
    };
    const float bob = std::sin(time * 6 + float(e.id)) * .08f;
    switch (d.shape) {
    case MonsterShape::Fly: {
        p.y += .25f + bob;
        sphere(p, r, skin);
        sphere(add(p, mul(dir, r * .65f)), r * .55f, dark);
        for (float sign : {-1.f, 1.f}) {
            const auto wing =
                add(p, add(mul(side, sign * r * .85f), {0, .25f + std::sin(time * 45) * .15f, 0}));
            DrawSphereEx(wing, r * .63f, 4, 6, {191, 199, 184, 190});
        }
        eyes(add(p, mul(dir, r * .4f)));
        if (type == 80)
            sphere(add(p, mul(dir, -r * .8f)), r * .65f, skin);
        if (type == 25)
            DrawCylinder({p.x, p.y + r * .7f, p.z}, .09f, .09f, .35f, 5, bone);
        if (type == 96)
            DrawCircle3D(add(p, {0, r + .2f, 0}), r * .7f, {1, 0, 0}, 90, bone);
        break;
    }
    case MonsterShape::Worm: {
        p.y = .42f + e.lift;
        for (int n = 3; n >= 0; --n) {
            auto at = add(p, mul(dir, -float(n) * r * .47f));
            at.y += std::sin(time * 8 + float(n)) * .05f;
            sphere(at, r * (1 - float(n) * .15f), n % 2 ? ColorBrightness(skin, -.15f) : skin);
        }
        eyes(p);
        if (type == 23 && variant == 3)
            sphere(add(p, mul(dir, -r * 1.6f)), r * .4f, blood);
        break;
    }
    case MonsterShape::Spider: {
        p.y = .45f + e.lift;
        sphere(p, r, skin);
        for (float sign : {-1.f, 1.f})
            for (int n = 0; n < 4; ++n) {
                const auto joint =
                    add(p, add(mul(side, sign * r * 1.3f), mul(dir, (float(n) - 1.5f) * r * .55f)));
                const auto toe =
                    add(joint, {side.x * sign * r * .5f, -.3f + std::sin(time * 12 + float(n)) * .08f,
                                side.z * sign * r * .5f});
                DrawCylinderEx(p, joint, .055f, .04f, 5, dark);
                DrawCylinderEx(joint, toe, .04f, .02f, 5, dark);
            }
        eyes(p);
        break;
    }
    case MonsterShape::Eye:
        p.y += bob;
        sphere(p, r, bone);
        sphere(add(p, mul(dir, r * .77f)), r * .48f, variant ? blood : skin);
        sphere(add(p, mul(dir, r * .98f)), r * .2f, dark);
        break;
    case MonsterShape::Stone:
        p.y = r;
        DrawCube(p, r * 1.7f, r * 2, r * 1.7f, {111, 112, 100, 255});
        eyes(p);
        sphere(add(p, add(mul(dir, r * .9f), {0, -r * .35f, 0})), r * .28f, dark);
        if (type == 44)
            for (int n = 0; n < 8; ++n) {
                auto end = add(p, rotateY({r * 1.3f, 0, 0}, float(n) * Pi / 4));
                DrawCylinderEx(p, end, .18f, 0, 5, bone);
            }
        break;
    case MonsterShape::Skull:
        if (type == 27) {
            const float lift = e.state == EnemyState::Windup || e.state == EnemyState::Exposed ? .65f : 0;
            DrawCylinder({p.x, .08f, p.z}, r * .6f, r * .8f, .8f + lift, 8, skin);
            p.y += lift;
        } else
            p.y += bob;
        sphere(p, r, type == 41 ? Color{87, 94, 93, 255} : bone);
        eyes(p);
        sphere(add(p, add(mul(dir, r * .85f), {0, -r * .3f, 0})), r * .25f, dark);
        if (type == 41) {
            DrawCube(add(p, mul(dir, r * .55f)), r * 1.65f, r * 1.4f, r * .45f,
                     variant == 4 ? dark : Color{105, 116, 118, 255});
            sphere(add(p, mul(dir, -r * .8f)), r * .3f, blood);
        }
        if (type == 27 && variant == 1)
            sphere(add(p, {0, r * .5f, 0}), r * .4f, blood);
        break;
    case MonsterShape::Blob: {
        const float scale = type == 30 ? .55f + .45f * e.hp / e.maxHp : 1;
        p.y = .55f + e.lift;
        sphere(p, r * scale * (1 + bob * .25f), skin);
        for (int n = 0; n < 4; ++n)
            sphere(add(p, rotateY({r * .55f, -.25f, 0}, float(n) * Pi / 2)), r * .4f, skin);
        eyes(p);
        if (type == 30 || type == 88)
            sphere(add(p, {0, r * .6f, 0}), r * .36f, variant == 2 ? bone : blood);
        if (type == 32 || type == 57 || type == 840)
            for (float x : {-.22f, .22f})
                sphere(add(p, {x, r * .5f, 0}), r * .42f, ColorBrightness(skin, .2f));
        break;
    }
    case MonsterShape::Walker:
    case MonsterShape::Headless: {
        const float step = std::sin(time * 9) * std::min(.16f, length(e.velocity) * .06f);
        for (float sign : {-1.f, 1.f}) {
            auto foot =
                add({p.x, .17f + e.lift, p.z}, add(mul(side, sign * r * .45f), mul(dir, step * sign)));
            DrawCylinder(foot, r * .2f, r * .25f, .5f, 6, skin);
        }
        DrawCylinder({p.x, .4f + e.lift, p.z}, r * .7f, r * .85f, .7f + bob * .25f, 8, skin);
        if (d.shape == MonsterShape::Walker) {
            auto head = add(p, {0, .57f + bob * .25f, 0});
            sphere(head, r * .85f, skin);
            eyes(head);
            sphere(add(head, add(mul(dir, r * .76f), {0, -.25f, 0})), r * .28f, dark);
        } else
            DrawCylinder({p.x, 1.05f + e.lift, p.z}, r * .36f, r * .36f, .08f, 8, blood);
        if (type == 39)
            sphere(add(p, mul(dir, r * .77f)), r * .45f, dark);
        if (type == 22 || type == 16)
            sphere(add(p, {0, -.08f, 0}), r * 1.04f, skin);
        if (type == 38)
            for (float sign : {-1.f, 1.f})
                DrawSphereEx(add(p, mul(side, sign * r)), r * .65f, 4, 6, bone);
        break;
    }
    }
    if ((type == 10 && variant == 2) || type == 54 || (type == 15 && variant == 3)) {
        for (int n = 0; n < 3; ++n)
            DrawCylinder(add(p, rotateY({r * .6f, .2f, 0}, float(n) * 2 * Pi / 3)), 0, .2f,
                         .8f + std::sin(time * 11) * .2f, 5, {227, 143, 47, 255});
    }
}
inline void drawMonsterWarning(const Enemy &e, const Simulation &run) {
    if (e.state != EnemyState::Windup)
        return;
    const auto &d = *monsterDefinition(e.monster);
    const auto direction = unit(sub(e.target, e.position));
    const Color warning{243, 181, 90, 230};
    auto line = [&](Vector3 dir) {
        auto end = add(e.position, mul(dir, 24));
        const auto hit = run.arena.trace(e.position, end);
        if (hit.hit)
            end = add(e.position, mul(sub(end, e.position), hit.t));
        DrawLine3D({e.position.x, .1f, e.position.z}, {end.x, .1f, end.z}, warning);
    };
    if (d.motion == MonsterMotion::Hop || d.attack == MonsterAttack::Lob || d.attack == MonsterAttack::Light)
        DrawCircle3D({e.target.x, .1f, e.target.z}, d.motion == MonsterMotion::Hop ? .8f : 2.2f, {1, 0, 0},
                     90, warning);
    else if (d.attack == MonsterAttack::Cross || d.attack == MonsterAttack::Diagonal ||
             d.attack == MonsterAttack::Ring) {
        const int count = d.attack == MonsterAttack::Ring ? 8 : 4;
        for (int n = 0; n < count; ++n)
            line(rotateY({1, 0, 0}, float(n) * 2 * Pi / float(count) +
                                        (d.attack == MonsterAttack::Diagonal ? Pi / 4 : 0)));
    } else {
        line(direction);
        if (d.attack == MonsterAttack::DoubleBeam)
            line(mul(direction, -1));
        if (d.attack == MonsterAttack::QuadBeam)
            for (int n = 1; n < 4; ++n)
                line(rotateY(direction, float(n) * Pi / 2));
    }
    DrawSphereEx(add(e.position, {0, 1, 0}), .12f, 4, 6, warning);
}
} // namespace dw
