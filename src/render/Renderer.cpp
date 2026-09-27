#include "render/Renderer.hpp"
#include "items/Items.hpp"
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
void lantern(Vector3 p, Color color) {
    DrawCylinder({p.x, 0, p.z}, 0.10f, 0.15f, 2.4f, 6, Color{65, 54, 43, 255});
    DrawCube({p.x, 2.25f, p.z}, 0.42f, 0.5f, 0.42f, color);
    DrawCylinder({p.x, 2.55f, p.z}, 0, 0.42f, 0.24f, 4, Color{46, 43, 37, 255});
}
void cowboy(Vector3 p, Vector3 direction, Color coat, float scale, bool boss = false) {
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
void Renderer::drawWorld(const Simulation &run, const Camera3D &camera, bool collisions,
                         EntityId hoveredEnemy) {
    BeginMode3D(camera);
    DrawPlane({camera.target.x, -0.5f, camera.target.z}, {180, 180}, Color{26, 29, 28, 255});
    auto visible = [&](Box box) {
        Vector3 nearest{std::clamp(run.player.position.x, box.min.x, box.max.x), run.player.position.y,
                        std::clamp(run.player.position.z, box.min.z, box.max.z)};
        return distance(nearest, run.player.position) < 65;
    };
    auto floor = [&](Box box, Color color) {
        if (!visible(box))
            return;
        DrawCubeV(mul(add(box.min, box.max), 0.5f), sub(box.max, box.min), color);
        DrawLine3D({box.min.x, 0.012f, box.min.z}, {box.max.x, 0.012f, box.min.z}, Color{108, 91, 69, 255});
    };
    for (const auto &box : run.arena.floors)
        floor(box, Color{83, 71, 56, 255});
    for (size_t i = 0; i < run.arena.walls.size(); ++i) {
        const auto &wall = run.arena.walls[i];
        if (i >= run.arena.boundaryWalls.size() + run.arena.obstacles.size() || !visible(wall))
            continue;
        Vector3 size = sub(wall.max, wall.min), center = mul(add(wall.min, wall.max), 0.5f);
        const bool boundary = i < run.arena.boundaryWalls.size();
        DrawCubeV(center, size, boundary ? Color{66, 61, 52, 255} : Color{94, 77, 55, 255});
        DrawCube({center.x, wall.max.y + 0.025f, center.z}, size.x, 0.05f, size.z, Color{133, 106, 72, 255});
        if (!boundary) {
            DrawCubeWiresV(center, size, Color{47, 43, 37, 255});
            DrawCube({center.x, center.y, wall.min.z - 0.03f}, size.x, 0.2f, 0.08f, Color{47, 43, 37, 255});
        }
        if (collisions)
            DrawBoundingBox({wall.min, wall.max}, Teal);
    }
    for (const auto &passage : run.arena.passages) {
        if (!visible(passage.floor))
            continue;
        Vector3 direction = unit(sub(passage.to, passage.from));
        Vector3 side{-direction.z, 0, direction.x};
        const bool eastWest = std::abs(direction.x) > 0.5f;
        const float span = distance(passage.from, passage.to);
        Vector3 midpoint = mul(add(passage.from, passage.to), 0.5f);
        for (float offset : {-1.3f, 1.3f}) {
            Vector3 rail = add(midpoint, mul(side, offset));
            rail.y = 0.07f;
            DrawCube(rail, eastWest ? span : 0.12f, 0.12f, eastWest ? 0.12f : span, Muted);
        }
        for (float t = 0; t <= span; t += 2) {
            Vector3 tie = add(passage.from, mul(direction, t));
            tie.y = 0.025f;
            DrawCube(tie, eastWest ? 0.25f : 3.4f, 0.06f, eastWest ? 3.4f : 0.25f, Color{51, 45, 38, 255});
        }
        for (int end = 0; end < 2; ++end) {
            const auto at = end == 0 ? passage.from : passage.to;
            const Color color = passage.locked ? Gold : passage.closed(end) ? Rust : Teal;
            lantern(add(at, mul(side, -3.5f)), color);
            lantern(add(at, mul(side, 3.5f)), color);
            DrawCube({at.x, 3.1f, at.z}, eastWest ? 0.5f : 8, 0.4f, eastWest ? 8 : 0.5f,
                     Color{76, 58, 38, 255});
            if (passage.closed(end)) {
                for (float offset = -3.5f; offset <= 3.5f; offset += 0.7f) {
                    Vector3 bar = add(at, mul(side, offset));
                    bar.y = 1.5f;
                    DrawCube(bar, 0.13f, 3, 0.13f, color);
                }
                if (passage.locked) {
                    DrawCube({at.x, 1.6f, at.z}, 0.6f, 0.7f, 0.6f, Gold);
                    DrawSphere({at.x, 1.6f, at.z}, 0.17f, Ink);
                }
                if (collisions)
                    DrawBoundingBox({passage.gates[size_t(end)].min, passage.gates[size_t(end)].max}, color);
            }
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
        if (room.kind != RoomKind::Power || distance(run.player.position, room.objective) > 60)
            continue;
        const auto p = room.objective;
        DrawCylinder({p.x, 0, p.z}, 0.8f, 1, 0.7f, 8, Border);
        if (!run.rooms[size_t(i)].rewardTaken) {
            DrawSphere({p.x, 1.3f, p.z}, 0.45f, Teal);
            DrawSphereWires({p.x, 1.3f, p.z}, 0.7f, 6, 8, Gold);
        }
    }
    lantern(run.arena.entrance, Gold);
    lantern(run.arena.exit, run.room == Simulation::FinalRoom && run.roomClear ? Teal : Gold);
    if (run.room == Simulation::FinalRoom && run.roomClear)
        DrawCircle3D({run.arena.exit.x, 0.1f, run.arena.exit.z}, 1.8f, {1, 0, 0}, 90, Teal);
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
        DrawCircle3D({p.x, 0.1f, p.z}, 2.3f, {1, 0, 0}, 90, run.rescued ? Muted : Teal);
    }
    if (distance(run.player.position, run.arena.altar) < 60) {
        Vector3 p = run.arena.altar;
        DrawCube({p.x, 0.5f, p.z}, 1.8f, 1, 1.4f, Color{63, 51, 51, 255});
        if (!run.altarDestroyed) {
            DrawCube({p.x, 1.7f, p.z}, 0.25f, 2.3f, 0.25f, Rust);
            DrawCube({p.x, 2.1f, p.z}, 1.5f, 0.25f, 0.25f, Rust);
            DrawSphere({p.x, 1.1f, p.z}, 0.35f, Teal);
        }
    }
    for (const auto &e : run.enemies)
        if (e.alive) {
            if (e.id == hoveredEnemy)
                DrawCircle3D({e.position.x, 0.08f, e.position.z}, e.radius + 0.25f, {1, 0, 0}, 90, Rust);
            Color color = e.flash > 0                   ? Paper
                          : e.kind == EnemyKind::Rusher ? Color{159, 64, 48, 255}
                          : e.kind == EnemyKind::Gunman ? Color{118, 105, 84, 255}
                                                        : Color{40, 58, 52, 255};
            if (e.kind == EnemyKind::Rusher) {
                shadow(e.position, 0.65f);
                DrawCylinder({e.position.x, 0, e.position.z}, 0.35f, 0.6f, 1.1f, 5, color);
                DrawSphereEx({e.position.x, 1.3f, e.position.z}, 0.3f, 6, 8, Color{181, 131, 82, 255});
            } else
                cowboy(e.position, unit(sub(run.player.position, e.position)), color,
                       e.kind == EnemyKind::Boss ? 1.7f : 1, e.kind == EnemyKind::Boss);
            if (collisions)
                DrawSphereWires(e.position, e.radius, 6, 8, Rust);
        }
    cowboy(run.player.position, unit(sub(run.player.aim, run.player.position)),
           run.player.hurt > 0 ? Rust : Color{90, 145, 137, 255}, 1);
    if (run.player.dodge > 0)
        DrawSphereWires(run.player.position, 0.9f, 5, 8, Teal);
    for (const auto &p : run.projectiles) {
        Color color = p.hostile ? Rust : p.ghost ? Teal : p.lastRound ? Paper : Gold;
        projectileMesh(p.position, p.radius, color);
    }
    // Keep triangles and lines in separate batches. Alternating for each projectile
    // creates thousands of tiny draw calls during a chain explosion.
    for (const auto &p : run.projectiles) {
        Color color = p.hostile ? Rust : p.ghost ? Teal : p.lastRound ? Paper : Gold;
        Vector3 tail = sub(p.position, mul(unit(p.velocity), p.hostile ? 0.35f : 0.6f));
        DrawLine3D(tail, p.position, color);
        if (collisions) {
            DrawLine3D(p.previous, p.position, Paper);
            DrawSphereWires(p.position, p.radius, 4, 6, Teal);
        }
    }
    for (const auto &effect : run.visuals) {
        float t = 1 - effect.life / effect.maxLife;
        Color color = effect.kind == 0 ? Gold : effect.kind == 2 ? Teal : effect.kind == 4 ? Rust : Paper;
        color.a = static_cast<unsigned char>(180 * (1 - t));
        if (effect.kind == 0 || effect.kind == 4) {
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
    EndMode3D();
    for (const auto &e : run.enemies)
        if (e.alive && (e.hp < e.maxHp || e.id == hoveredEnemy) && e.kind != EnemyKind::Boss) {
            Vector2 at = GetWorldToScreen(add(e.position, {0, 1.6f, 0}), camera);
            DrawRectangle(int(at.x) - 18, int(at.y) - 5, 36, 4, Ink);
            DrawRectangle(int(at.x) - 18, int(at.y) - 5, int(36 * std::max(0.0f, e.hp / e.maxHp)), 4, Rust);
        }
    auto marker = [&](Vector3 position, const char *label, Color color) {
        Vector2 point = GetWorldToScreen(add(position, {0, 2.6f, 0}), camera);
        int size = int(16 * std::min(sx_, sy_));
        DrawText(label, int(point.x) - MeasureText(label, size) / 2, int(point.y), size, color);
    };
    if (!run.rescued && distance(run.player.position, run.arena.miners) < 30)
        marker(run.arena.miners, "LMB / E: FREE THE MINERS", Teal);
    if (!run.altarDestroyed && distance(run.player.position, run.arena.altar) < 30)
        marker(run.arena.altar, "LMB / E: BREAK THE ALTAR", Rust);
    for (const auto &key : run.arena.keys)
        if (!key.collected && run.rooms[size_t(key.room)].cleared &&
            distance(run.player.position, key.position) < 28)
            marker(key.position, "LMB: TAKE KEY", Gold);
    if (run.arena.rooms[size_t(run.room)].kind == RoomKind::Power && !run.rooms[size_t(run.room)].rewardTaken)
        marker(run.arena.rooms[size_t(run.room)].objective, "LMB / E: CLAIM ONE POWER", Teal);
    if (run.room == Simulation::FinalRoom && run.roomClear)
        marker(run.arena.exit, "LMB / E: RETURN HOME", Teal);
    if (run.roomClear)
        for (int index : run.arena.rooms[size_t(run.room)].passages) {
            const auto &passage = run.arena.passages[size_t(index)];
            const int side = passage.rooms[0] == run.room ? 0 : 1;
            const auto p = run.arena.doorApproach(index, side);
            if (distance(run.player.position, p) < 26)
                marker(p, passage.locked ? "LMB / E: UNLOCK (1 KEY)" : "LMB / E: USE PASSAGE",
                       passage.locked ? Gold : Teal);
        }
}
Action Renderer::hub(const Game &game) {
    const auto &world = game.campaign.data().world;
    // The hub is intentionally a status screen; the expedition carries the 3D experiment.
    for (int i = 0; i < 18; ++i)
        DrawLine(int((float(i) * 95 - 200) * sx_), 0, int((float(i) * 95 + 180) * sx_), GetScreenHeight(),
                 Color{25, 32, 34, 255});
    text("BLACK CREEK  /  FRONTIER TERRITORY", 58, 40, 16, Gold);
    text("DEATHWARD", 54, 92, 76, Paper);
    text("POWER IS BORROWED.", 58, 185, 27, Muted);
    text("THE TOWN REMEMBERS.", 58, 222, 27, Paper);
    wrap("Six miners below ground. A dead man's badge. Every expedition leaves something behind.", 60, 286,
         575, 20, Muted);
    const std::array<std::pair<const char *, int>, 3> metrics{
        {{"POPULATION", world.population}, {"PROSPERITY", world.prosperity}, {"LAW", world.law}}};
    for (size_t i = 0; i < metrics.size(); ++i) {
        float x = 60 + float(i) * 199;
        panel(x, 376, 181, 102, Panel);
        text(metrics[i].first, x + 16, 391, 13, Muted);
        text(std::to_string(metrics[i].second), x + 16, 417, 34, Paper);
    }
    text("VOICES FROM BLACK CREEK", 60, 516, 14, Gold);
    for (size_t i = 0; i < world.npcs.size(); ++i) {
        float y = 550 + float(i) * 39;
        text(world.npcs[i].name, 60, y, 15, Paper);
        std::string line = npcDialogue(world, i);
        if (line.size() > 57)
            line = line.substr(0, 54) + "...";
        text(line, 206, y + 1, 13, Muted);
    }
    panel(732, 65, 488, 613, Panel);
    text("EXPEDITION 01", 760, 91, 14, Gold);
    text("RED HOLLOW", 757, 131, 43, Paper);
    text("MINE", 758, 181, 43, Paper);
    text(world.mineOpen                         ? "OPEN / THE WORK CONTINUES"
         : world.flags.contains("mine_setback") ? "CLOSED / A CHANCE TO MAKE AMENDS"
                                                : "SILENT / SIX SOULS BELOW",
         760, 244, 13, world.mineOpen ? Teal : Rust);
    DrawLine(int(760 * sx_), int(281 * sy_), int(1192 * sx_), int(281 * sy_), Border);
    wrap(world.bossDefeated
             ? "The Sheriff is gone. Return for unfinished rescues, silence the altar, and restore the mine."
             : "Face the Hollow Sheriff. Bring the miners home. Break the altar if you can.",
         760, 302, 415, 20, Paper);
    wrap("Retreat costs the town. Lost ground can be recovered. Your temporary build ends with the "
         "expedition.",
         760, 398, 410, 16, Muted);
    panel(760, 479, 432, 59, Ink);
    text("SEED", 777, 490, 12, Muted);
    text(game.seedText.empty() ? "Type a seed..." : game.seedText, 777, 509, 19, Gold);
    text("Type digits / Backspace to edit / N for a new seed", 761, 548, 12, Muted);
    if (button("ENTER THE MINE   [ENTER]", 760, 584, 432, 60, true))
        return Action::Launch;
    if (button("RUN HISTORY   [H]", 732, 700, 238, 48))
        return Action::History;
    if (button("QUIT", 986, 700, 234, 48))
        return Action::Quit;
    text("F1 / CHEAT MODE", 60, 771, 11, game.debug ? Teal : Muted);
    text("LMB move / attack / interact   SHIFT + LMB / RMB fire   WASD move   MMB / SPACE dodge", 378, 772,
         11, Muted);
    if (game.debug && game.debugPanelOpen) {
        panel(60, 660, 612, 89, Ink);
        text("CHEATS ON / F1 off / G toggles the haunting flag", 76, 674, 14, Teal);
        if (button(game.resetArmed ? "CONFIRM RESET (backup saved)" : "RESET CAMPAIGN", 76, 702, 360, 34))
            return Action::Reset;
    }
    return Action::None;
}
void Renderer::dungeonMap(const Game &game) {
    const auto &run = *game.run;
    panel(1040, 170, 216, 192, Panel);
    text("MINE PASSAGES", 1053, 183, 12, Gold);
    const auto totalPowers =
        std::count_if(run.arena.rooms.begin(), run.arena.rooms.end(),
                      [](const RoomLayout &room) { return room.kind == RoomKind::Power; });
    text("KEYS " + std::to_string(run.keys) + "   POWERS " + std::to_string(run.powerUpsTaken) + " / " +
             std::to_string(totalPowers),
         1053, 201, 11, Paper);
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
        std::string label = kind == RoomKind::Power   ? "P"
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
    drawWorld(run, game.camera, game.collisionDebug, game.hoveredEnemy);
    panel(24, 22, 358, 90, Panel);
    text("RED HOLLOW / " + std::to_string(run.room + 1) + " OF " + std::to_string(RoomCount), 42, 35, 12,
         Gold);
    const int physicalRoom = run.arena.roomAt(run.player.position);
    text(physicalRoom < 0 ? "Mine Passage" : Simulation::roomName(physicalRoom), 41, 58, 25, Paper);
    text("SEED " + game.seedText + "   /   " + timeLabel(run.stats.duration), 42, 91, 12, Muted);
    panel(964, 22, 292, 131, Panel);
    text("BRING SOMETHING BACK", 982, 37, 13, Gold);
    text(run.rescued ? "[+] Six miners safe" : "[ ] Miners / chamber 3", 982, 65, 15,
         run.rescued ? Teal : Paper);
    text(run.altarDestroyed ? "[+] Altar destroyed" : "[ ] Altar / chamber 4", 982, 91, 15,
         run.altarDestroyed ? Teal : Muted);
    text(run.bossKilled ? "[+] Sheriff defeated" : "[ ] Sheriff / locked court", 982, 117, 15,
         run.bossKilled ? Teal : Muted);
    dungeonMap(game);
    if (const auto *boss = run.boss()) {
        panel(412, 24, 476, 70, Panel);
        text("THE HOLLOW SHERIFF / PHASE " + std::to_string(boss->phase + 1), 429, 37, 14, Paper);
        panel(429, 66, 442, 9, Ink);
        DrawRectangle(int(429 * sx_), int(66 * sy_), int(442 * sx_ * std::max(0.0f, boss->hp / boss->maxHp)),
                      int(9 * sy_), Rust);
    } else {
        const auto kind = run.arena.rooms[size_t(run.room)].kind;
        text(run.roomClear ? (kind == RoomKind::Empty   ? "QUIET ROOM / NO ENEMIES"
                              : kind == RoomKind::Power ? "POWER CACHE"
                                                        : "CHAMBER CLEARED")
                           : number(run.livingEnemies()) + " HOSTILES",
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
    text(run.player.dodgeCooldown <= 0 ? "MMB / SPACE: DODGE READY" : "DODGE RECOVERING", 397, 752, 12,
         Muted);
    text("LMB move / attack / interact   SHIFT + LMB / RMB fire   WASD move", 397, 774, 11, Muted);
    text(game.debug ? "F1 / CHEATS ON" : "F1 / CHEATS", 806, 752, 12, game.debug ? Teal : Gold);
    Action controls = Action::None;
    if (!game.paused && !run.rewardOpen) {
        const std::string interaction = run.nearbyInteraction();
        if (!interaction.empty()) {
            if (button(interaction, 396, 690, 186, 44, true))
                controls = Action::Interact;
        } else {
            panel(396, 690, 186, 44, Panel);
            text("LMB / MOVE", 414, 704, 18, Muted);
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
    if (game.paused) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{9, 15, 18, 210});
        panel(407, 240, 466, 318, Panel);
        text("TAKE A BREATH", 435, 269, 30, Paper);
        wrap("Retreat ends your build and changes Black Creek. Closing the game also counts as retreat.", 436,
             326, 402, 17, Muted);
        if (button("KEEP GOING   [ESC]", 436, 423, 408, 45, true))
            return Action::Resume;
        if (button("RETREAT TO BLACK CREEK   [T]", 436, 486, 408, 45))
            return Action::Retreat;
    }
    return controls;
}
Action Renderer::summary(const Game &game, const RunSummary &s, bool history) {
    text(history ? "BLACK CREEK / RUN HISTORY" : "BLACK CREEK / EXPEDITION RESOLVED", 60, 42, 14, Gold);
    text(outcomeTitle(s), 58, 92, 38, Paper);
    text("RUN " + number(s.id) + "  /  SEED " + number(s.seed) + "  /  " + timeLabel(s.stats.duration) +
             (s.interrupted ? "  /  PARTIAL CHECKPOINT" : ""),
         60, 150, 15, Muted);
    const std::array<std::pair<std::string, std::string>, 4> values{
        {{"ENEMIES KILLED", number(s.stats.kills)},
         {"BULLETS / PROJECTILES", number(s.stats.shots) + " / " + number(s.stats.projectiles)},
         {"EXPLOSIONS", number(s.stats.explosions)},
         {"LARGEST KILL CHAIN", number(s.stats.largestKillChain)}}};
    for (size_t i = 0; i < values.size(); ++i) {
        float x = 60 + float(i) * 296;
        panel(x, 203, 276, 99, Panel);
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
    if (button("RETURN TO BLACK CREEK", 60, 740, 341, 42, true))
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
    text("F4 spawn 20    F5 spawn 100 enemies", 41, 219, 13, Paper);
    text("F6 all items       Shift+F6 add 3 keys", 41, 239, 13, Paper);
    text("F7 replay boss     F8 win    F9 die", 41, 259, 13, Paper);
    text("F10 collisions     F11 stress scene", 41, 279, 13, Paper);
    text("F12 next room      Shift+F12 restart room", 41, 299, 13, Paper);
    text("P freeze " + std::string(game.paused ? "ON" : "OFF") + "    O slow " + (game.slow ? "ON" : "OFF"),
         41, 319, 13, Paper);
    text("[/] select   I grant   V random five   M rescue", 41, 339, 13, Paper);
    text("ITEM: " + std::string(itemDefinition(ItemId(game.selectedItem)).name), 41, 366, 15, Gold);
    text("ENEMIES " + number(run.livingEnemies()) + "   PROJECTILES " + number(run.projectiles.size()) +
             "   EVENTS " + number(run.queuedEvents()),
         41, 397, 13, Paper);
    text("CHAINS " + number(run.chains.size()) + "   DEPTH " + number(run.stats.maxDepth) + "   SUPPRESSED " +
             number(run.stats.suppressed),
         41, 420, 13, Paper);
    text("SPLITS " + number(run.stats.splits) + "   BOUNCES " + number(run.stats.bounces) + "   GHOSTS " +
             number(run.stats.ghosts),
         41, 443, 13, Paper);
    text(std::string(game.slow ? "0.2x TIME" : "1.0x TIME") + "   FPS " + std::to_string(GetFPS()), 41, 466,
         13, Teal);
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
Action Renderer::draw(const Game &game) {
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
            if (button("BACK TO BLACK CREEK", 82, 290, 365, 51, true))
                action = Action::Hub;
        }
        break;
    }
    if (game.debug && game.debugPanelOpen && game.run && !game.paused && !game.run->rewardOpen)
        debugPanel(game);
    if (!game.error.empty()) {
        panel(24, 560, 1232, 81, Color{76, 34, 30, 250});
        wrap(game.error, 42, 578, 1196, 15, Paper);
    }
    return action;
}
} // namespace dw
