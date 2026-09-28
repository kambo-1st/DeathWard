#include "combat/Simulation.hpp"
#include <iostream>
#include <set>
#include <stdexcept>

using namespace dw;
namespace {
void check(bool value, const char *message) {
    if (!value)
        throw std::runtime_error(message);
}
void verify(uint64_t seed, MissionTheme theme) {
    Simulation run(seed, 1, {}, theme);
    check(run.enemies.empty() && run.roomClear, "arrival room stays empty and clear");
    std::set<EntityId> identities;
    for (int room = 0; room < RoomCount; ++room) {
        const auto &group = run.roomEnemies(room);
        check(int(group.size()) == run.roomEnemyCount(room), "every room is populated before visiting");
        check(room == 0 || !run.rooms[size_t(room)].visited, "population does not discover rooms");
        for (const auto &enemy : group) {
            check(identities.insert(enemy.id).second, "resident entity IDs are unique across rooms");
            check(run.arena.roomAt(enemy.position) == room, "residents stay on their own room floor");
            for (int passage : run.arena.rooms[size_t(room)].passages) {
                const int side = run.arena.passages[size_t(passage)].rooms[0] == room ? 0 : 1;
                check(distance(enemy.position, run.arena.doorApproach(passage, side)) >= enemy.radius + 2.5f,
                      "every possible entrance has a clear landing");
            }
            if (enemy.partner)
                check(std::any_of(group.begin(), group.end(),
                                  [&](const Enemy &other) { return other.id == enemy.partner; }),
                      "companions retain their parent in the same group");
        }
    }
    int passage = -1, side = 0, target = -1;
    for (size_t i = 0; i < run.arena.passages.size() && passage < 0; ++i) {
        const auto &door = run.arena.passages[i];
        if (door.locked)
            continue;
        for (int s = 0; s < 2; ++s)
            if (!run.roomEnemies(door.rooms[size_t(s)]).empty()) {
                const auto start = run.arena.doorApproach(int(i), 1 - s);
                auto route = run.arena.path(start, run.arena.doorApproach(int(i), s), .48f);
                route.insert(route.begin(), start);
                for (size_t leg = 1; leg < route.size() && passage < 0; ++leg)
                    for (float fraction = .1f; fraction < 1; fraction += .1f) {
                        const auto point =
                            add(route[leg - 1], mul(sub(route[leg], route[leg - 1]), fraction));
                        if (run.arena.roomAt(point) < 0) {
                            passage = int(i);
                            side = s;
                            target = door.rooms[size_t(s)];
                            run.player.position = point;
                            break;
                        }
                    }
                if (passage >= 0)
                    break;
            }
    }
    check(passage >= 0, "find an open corridor overlooking a populated room");
    const auto before = run.roomEnemies(target);
    const auto encounterState = run.encounterRng.state, combatState = run.combatRng.state;
    const auto cleared = run.stats.rooms;
    run.audioCues.clear();
    for (int tick = 0; tick < 1200; ++tick)
        run.step({});
    check(run.room == 0 && run.enemies.empty(), "corridor waiting never activates the next room");
    check(run.player.hp == StartingHealth && run.projectiles.empty() && run.hazards.empty() &&
              run.queuedEvents() == 0 && run.stats.rooms == cleared && run.stats.kills == 0 &&
              run.stats.bossDuration == 0 && run.audioCues.cues().empty(),
          "dormant rooms cannot attack, summon, clear themselves or emit combat audio");
    check(run.encounterRng.state == encounterState && run.combatRng.state == combatState,
          "idle animation never consumes gameplay randomness");
    const auto waiting = run.roomEnemies(target);
    check(waiting.size() == before.size(), "long corridor waits do not add offspring");
    for (size_t i = 0; i < waiting.size(); ++i) {
        const auto &enemy = waiting[i];
        check(enemy.id == before[i].id && distance(enemy.position, before[i].position) == 0 &&
                  enemy.hp == before[i].hp && enemy.cooldown == before[i].cooldown && enemy.age == 0 &&
                  enemy.state == EnemyState::Ready && enemy.partner == before[i].partner,
              "waiting preserves the actual enemies and their initial combat state");
        check(enemy.animationTime() > 19, "resident animations run before entry");
    }
    // Use the real threshold check rather than explicitly switching rooms.
    run.player.position = run.arena.doorApproach(passage, side);
    run.step({});
    check(run.room == target && !run.roomClear && run.rooms[size_t(target)].residents.empty(),
          "crossing the threshold activates the existing group exactly once");
    check(run.enemies.size() == waiting.size(), "activation does not duplicate the visible group");
    for (size_t i = 0; i < waiting.size(); ++i) {
        const auto &enemy = run.enemies[i];
        check(enemy.id == waiting[i].id && enemy.monster == waiting[i].monster &&
                  enemy.partner == waiting[i].partner && enemy.age > 0 &&
                  enemy.cooldown < waiting[i].cooldown,
              "the same individuals and companions start normal combat on entry");
        check(std::abs(enemy.animationTime() - waiting[i].animationTime() - Tick) < .001f &&
                  distance(enemy.position, waiting[i].position) < .3f,
              "entry continues animation and movement without a spawn jump");
    }
    run.clearRoomDebug();
    run.enterRoom(0);
    check(run.roomEnemies(target).empty(), "cleared enemies do not reappear after leaving");
    run.enterRoom(target);
    check(run.roomClear && run.enemies.empty(), "revisits stay cleared");
    run.jumpDebug(target, true);
    check(!run.roomClear && int(run.enemies.size()) == run.roomEnemyCount(target),
          "explicit debug replay prepares a fresh encounter");
    for (const auto &enemy : run.enemies)
        check(enemy.age == 0 && enemy.idleTime == 0 && !identities.contains(enemy.id),
              "debug replay resets timers and gives the new group fresh identities");
}
} // namespace
int main() {
    try {
        for (const auto theme : {MissionTheme::Mine, MissionTheme::Canyon})
            for (uint64_t seed : {0, 1, 1866, 69175541})
                verify(seed, theme);
        std::cout << "PASS resident groups, corridor inactivity, ambient animation, entry continuity, "
                     "doorway clearance, companions, cleared revisits and debug replay in both themes\n";
    } catch (const std::exception &error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
