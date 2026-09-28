#include "combat/Simulation.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace dw;
namespace {
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
void damage(Simulation &run, EntityId target, bool execution = false) {
    Event event;
    event.type = EventType::Damage;
    event.target = target;
    event.damage = 100000;
    event.execution = execution;
    run.queueRoot(event);
    run.drainEvents();
}
Simulation fixture(uint64_t seed = 1866) {
    Simulation run(seed, 1, {});
    run.arena = Arena{};
    run.arena.bounds = {{-20, -1, -20}, {20, 4, 20}};
    run.moneyPickups.clear();
    run.enemies.clear();
    for (auto &room : run.rooms)
        room.residents.clear();
    run.debugScenario = run.godMode = true;
    run.player.position = {10, .85f, 10};
    return run;
}
void placement() {
    for (auto theme : {MissionTheme::Mine, MissionTheme::Canyon})
        for (uint64_t seed : {1866ULL, 42ULL, 69175541ULL}) {
            Simulation a(seed, 1, {}, theme), b(seed, 77, {}, theme);
            check(!a.moneyPickups.empty() && a.moneyPickups.size() == b.moneyPickups.size(),
                  "seeded ground money exists independently of campaign run ID");
            int starting = 0;
            for (size_t i = 0; i < a.moneyPickups.size(); ++i) {
                const auto &coin = a.moneyPickups[i];
                check(distance(coin.position, b.moneyPickups[i].position) == 0 &&
                          coin.value == b.moneyPickups[i].value,
                      "the same seed reproduces coin positions and values");
                check(coin.value >= 1 && coin.value <= 5 && !coin.dropped,
                      "ground piles contain one to five coins");
                const int room = a.arena.roomAt(coin.position);
                check(room >= 0 && !a.arena.blocked(coin.position, .55f),
                      "money is on a room's walkable floor, outside obstacles");
                auto start = a.arena.rooms[size_t(room)].center;
                start.y = .85f;
                if (a.arena.blocked(start, .48f))
                    start = a.arena.rooms[size_t(room)].entry;
                check(!a.arena.path(start, coin.position, .48f).empty(),
                      "each ground pile is reachable within its room");
                starting += room == 0;
            }
            check(starting >= 1 && starting <= 2, "the quiet starting room introduces money pickups");
            const auto before = a.moneyPickups.size();
            a.enterRoom(1);
            a.enterRoom(0);
            check(a.moneyPickups.size() == before, "room travel does not recreate ground money");
        }
    Simulation a(1866, 1, {}), b(42, 1, {});
    check(distance(a.moneyPickups.front().position, b.moneyPickups.front().position) > .1f,
          "different seeds change ground loot");
}
void collection() {
    auto run = fixture();
    const auto point = run.player.position;
    run.player.hp = 40;
    run.moneyPickups.push_back({point, 3, 1, false});
    run.moneyPickups.push_back({point, 5, 1, false});
    run.audioCues.clear();
    run.checkpointNeeded = false;
    run.step({});
    check(run.money() == 8 && run.moneyCollected == 8 && run.moneyPickups.empty() &&
              run.summary().moneyCollected == 8 && run.checkpointNeeded,
          "walking onto piles collects their value and requests a checkpoint");
    check(run.player.hp == 40 && run.stats.kills == 0, "money never heals the player or awards a kill");
    check(std::count_if(run.audioCues.cues().begin(), run.audioCues.cues().end(),
                        [](const auto &cue) { return cue.kind == AudioCueKind::Pickup; }) == 2,
          "collecting money emits pickup audio");
    run.step({});
    check(run.money() == 8, "a collected pile cannot pay twice");
    run.moneyPickups.push_back({point, 4, 0, true});
    for (int tick = 0; tick < 20; ++tick)
        run.step({});
    check(run.money() == 8, "new enemy drops finish their bounce before collection");
    for (int tick = 0; tick < 10; ++tick)
        run.step({});
    check(run.money() == 12 && run.moneyPickups.empty(), "settled drops collect normally");
    const auto blocked = add(point, {.9f, 0, 0});
    run.moneyPickups.push_back({blocked, 2, 1, false});
    run.arena.walls.push_back({add(point, {.3f, -1, -2}), add(point, {.5f, 2, 2})});
    run.step({});
    check(run.money() == 12 && run.moneyPickups.size() == 1,
          "nearby money cannot be collected through a solid wall");
    run.arena.walls.clear();
    run.dead = true;
    run.step({});
    check(run.money() == 12, "a dead player cannot collect money");
    WorldState wealthy;
    wealthy.money = MaxMoney - 1;
    Simulation capped(42, 1, wealthy);
    capped.moneyPickups = {{capped.player.position, 5, 1, false}};
    capped.step({});
    check(capped.money() == MaxMoney && capped.moneyCollected == 1 && capped.moneyPickups[0].value == 4,
          "wallet arithmetic stays bounded without losing excess ground money");
}
void drops() {
    auto a = fixture(), b = fixture();
    std::vector<EntityId> targets;
    for (int i = 0; i < 100; ++i) {
        const Vector3 point{float(i % 10) - 5, .85f, float(i / 10) - 5};
        const auto first = i % 2 ? a.spawnMonster(monsterId(12), point) : a.spawn(EnemyKind::Gunman, point);
        const auto second = i % 2 ? b.spawnMonster(monsterId(12), point) : b.spawn(EnemyKind::Gunman, point);
        check(first == second, "drop comparison uses matching enemy identities");
        targets.push_back(first);
    }
    const auto combat = a.combatRng.state, encounter = a.encounterRng.state, reward = a.rewardRng.state;
    for (auto id : targets)
        damage(a, id);
    for (auto it = targets.rbegin(); it != targets.rend(); ++it)
        damage(b, *it);
    check(a.moneyPickups.size() > 15 && a.moneyPickups.size() < 55,
          "both rosters randomly drop money rather than every kill paying");
    check(a.moneyPickups.size() == b.moneyPickups.size(), "kill order does not change drop rolls");
    for (const auto &coin : a.moneyPickups)
        check(std::any_of(b.moneyPickups.begin(), b.moneyPickups.end(),
                          [&](const auto &other) {
                              return distance(coin.position, other.position) == 0 &&
                                     coin.value == other.value;
                          }),
              "drop positions and values match across reversed kill order");
    check(a.combatRng.state == combat && a.encounterRng.state == encounter && a.rewardRng.state == reward,
          "money drops never consume combat, encounter or power-up randomness");
    check(a.money() == 0, "killing an enemy drops money without adding it directly to the wallet");
    const auto count = a.moneyPickups.size();
    for (auto id : targets)
        damage(a, id);
    check(a.moneyPickups.size() == count, "duplicate damage to dead enemies never duplicates drops");
    for (int i = 0; i < 60; ++i) {
        const auto id = a.spawnMonster(monsterId(12), {0, .85f, 0});
        auto &enemy = *a.findEnemy(id);
        enemy.friendly = i % 2 == 0;
        enemy.generation = i % 2;
        damage(a, id, true);
    }
    check(a.moneyPickups.size() == count, "friendly and summoned enemies cannot farm money");
    auto relocated = fixture();
    relocated.arena.walls.push_back({{-1, -1, -1}, {1, 4, 1}});
    for (int i = 0; i < 30; ++i)
        damage(relocated, relocated.spawnMonster(monsterId(12), {0, .85f, 0}));
    check(!relocated.moneyPickups.empty(), "flying-enemy drop fixture produces money");
    for (const auto &coin : relocated.moneyPickups)
        check(!relocated.arena.blocked(coin.position, .55f), "drops over rocks land on nearby clear floor");
    auto collapse = fixture();
    for (int i = 0; i < 30; ++i) {
        const auto id = collapse.spawnMonster(monsterId(24), {0, .85f, 0});
        damage(collapse, id);
    }
    check(collapse.moneyPickups.empty(), "regenerating piles do not pay on a temporary collapse");
}
void persistence(const std::filesystem::path &directory) {
    const auto path = directory / "campaign.save";
    CampaignStore store(path);
    uint64_t total = 0;
    for (auto reason : {EndReason::Victory, EndReason::Retreat, EndReason::Death, EndReason::Interrupted}) {
        const auto id = store.begin(42);
        Simulation run(42, id, store.data().world);
        run.moneyPickups = {{run.player.position, 5, 1, false}};
        run.step({});
        check(run.money() == total + 5, "later missions start with the saved wallet");
        store.checkpoint(run.summary());
        CampaignStore reload(path);
        check(reload.data().pending->moneyCollected == 5, "checkpoint saves collected money");
        if (reason == EndReason::Interrupted)
            check(reload.recover(), "interrupted missions recover collected money");
        else
            reload.resolve(run.summary(), reason);
        total += 5;
        check(reload.data().world.money == total && reload.data().history.back().moneyCollected == 5,
              "every outcome banks money once and records the run's earnings");
        reload.resolve(run.summary(), reason);
        check(reload.data().world.money == total && !reload.recover(), "resolution never pays twice");
        store = CampaignStore(path);
        check(store.data().world.money == total, "wallet survives reopening the save");
    }
    // A real format-1 payload, including pending and historical run summaries.
    const std::string summary = " 42 \"deathward-m1-22\" \"Red Hollow Mine\" \"\" 2 0 0 0 0\n"
                                "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0\n0\n";
    const std::string payload = "3 42 50 50 0 0 0 0 0 0\n0\n"
                                "\"Sheriff Cole\" \"alive\" 0\n\"Mary Bell\" \"alive\" 0\n"
                                "\"Father Gabriel\" \"alive\" 0\n\"Silas Reed\" \"alive\" 0\n"
                                "\"Dr. Whitmore\" \"alive\" 0\n1\n2" +
                                summary + "1\n1" + summary;
    uint64_t checksum = 14695981039346656037ULL;
    for (unsigned char c : payload) {
        checksum ^= c;
        checksum *= 1099511628211ULL;
    }
    const auto legacy = directory / "legacy.save";
    {
        std::ofstream out(legacy);
        out << "DEATHWARD 1 " << checksum << '\n' << payload;
    }
    CampaignStore migrated(legacy);
    check(migrated.data().world.money == 0 && migrated.data().history.size() == 1 &&
              migrated.data().pending->moneyCollected == 0,
          "old saves load with a zero wallet and keep pending/history data");
    migrated.recover();
    CampaignStore reread(legacy);
    check(reread.data().history.size() == 2 && reread.data().world.money == 0,
          "old saves migrate to the new format on the next save");
}
} // namespace
int main() {
    const auto directory =
        std::filesystem::temp_directory_path() /
        ("deathward-money-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    try {
        std::filesystem::create_directories(directory);
        placement();
        collection();
        drops();
        persistence(directory);
        std::filesystem::remove_all(directory);
        std::cout
            << "PASS seeded/reachable money, random drops, collection, collision, wallet and legacy saves\n";
    } catch (const std::exception &e) {
        std::filesystem::remove_all(directory);
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
