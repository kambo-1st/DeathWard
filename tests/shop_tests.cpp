#include "combat/Simulation.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <stdexcept>

using namespace dw;
namespace {
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
void approach(Simulation &run) {
    run.enterRoom(run.arena.shopRoom);
    run.player.position = add(run.arena.rooms[size_t(run.room)].objective, {0, 0, -1.8f});
    run.interact();
    check(run.shopOpen, "approaching and interacting opens the peaceful shop");
}
void generation() {
    std::set<int> locations, items;
    for (auto theme : {MissionTheme::Mine, MissionTheme::Canyon})
        for (uint64_t seed : {0ULL, 1ULL, 42ULL, 1866ULL, 69175541ULL}) {
            Simulation a(seed, 1, {}, theme), b(seed, 2, {}, theme);
            const int shop = a.arena.shopRoom;
            check(shop >= 4 && shop < Simulation::FinalRoom && shop == b.arena.shopRoom,
                  "shop location is seeded and keeps mission objectives intact");
            locations.insert(shop);
            check(std::count_if(a.arena.rooms.begin(), a.arena.rooms.end(),
                                [](const auto &r) { return r.kind == RoomKind::Shop; }) == 1,
                  "each mission has exactly one shop");
            check(a.roomEnemyCount(shop) == 0 && a.roomEnemies(shop).empty(),
                  "shop has no active or prepopulated enemies");
            std::set<int> reachable{0};
            std::queue<int> pending;
            pending.push(0);
            while (!pending.empty()) {
                const auto current = pending.front();
                pending.pop();
                for (int passage : a.arena.rooms[size_t(current)].passages) {
                    const auto &door = a.arena.passages[size_t(passage)];
                    const int next = door.rooms[0] == current ? door.rooms[1] : door.rooms[0];
                    if (!door.locked && reachable.insert(next).second)
                        pending.push(next);
                }
            }
            check(reachable.contains(shop), "shop can be reached without spending a key");
            const auto &layout = a.arena.rooms[size_t(shop)];
            check(!a.arena.blocked(layout.objective, .6f) &&
                      !a.arena.path(layout.center, layout.objective, .48f).empty(),
                  "the shopkeeper and approach stand on reachable floor");
            check(a.shopOffers[1].item != a.shopOffers[2].item, "shop power-ups are distinct");
            for (int slot = 0; slot < 3; ++slot) {
                check(a.shopOffers[size_t(slot)].item == b.shopOffers[size_t(slot)].item &&
                          a.shopOffers[size_t(slot)].price == (slot == 0 ? 10 : 25),
                      "stock and prices reproduce from the seed");
                if (slot)
                    items.insert(int(a.shopOffers[size_t(slot)].item));
            }
            approach(a);
            check(a.roomClear && a.rooms[size_t(shop)].cleared && a.enemies.empty(),
                  "entering the shop stays peaceful and does not seal exits");
            for (const auto &door : a.arena.passages)
                check(!door.sealed[0] && !door.sealed[1], "shop entry clears combat seals");
        }
    check(locations.size() > 1 && items.size() > 2, "different seeds vary the shop and its power-ups");
}
void purchases() {
    WorldState world;
    world.money = 100;
    Simulation run(1866, 1, world, MissionTheme::Canyon);
    run.openShop();
    check(!run.shopOpen && !run.buyShop(1), "remote shop access cannot spend money");
    approach(run);
    const auto combat = run.combatRng.state, rewards = run.rewardRng.state,
               encounters = run.encounterRng.state;
    check(!run.buyShop(-1) && !run.buyShop(4), "invalid stock indexes are rejected");
    check(!run.buyShop(0) && run.money() == 100 && !run.shopOffers[0].sold,
          "full health never consumes medicine or money");
    const auto duration = run.stats.duration;
    const auto position = run.player.position;
    Input input;
    input.fire = input.dodge = true;
    input.movement = {1, 0, 0};
    for (int i = 0; i < 120; ++i)
        run.step(input);
    check(run.stats.duration == duration && run.stats.shots == 0 &&
              distance(position, run.player.position) == 0,
          "shop menus freeze simulation, firing, movement and timers");
    run.player.hp = 75;
    check(run.buyShop(0) && run.player.hp == 100 && run.money() == 90 && run.moneySpent == 10,
          "medicine charges once and heals up to the maximum");
    run.player.hp = 20;
    check(!run.buyShop(0) && run.player.hp == 20 && run.money() == 90, "sold medicine cannot be repurchased");
    check(run.buyShop(1) && run.itemStacks(run.shopOffers[1].item) == 1 && run.money() == 65,
          "buying a power-up applies its actual item effect and deducts its price");
    check(run.buyShop(2) && run.items.size() == 2 && run.money() == 40 && run.moneySpent == 60 &&
              run.powerUpsTaken == 0 && run.checkpointNeeded,
          "paid stock is separate from free caches and requests a checkpoint");
    check(run.combatRng.state == combat && run.rewardRng.state == rewards &&
              run.encounterRng.state == encounters,
          "shop purchases never consume combat or reward randomness");
    run.closeShop();
    check(!run.buyShop(1), "a closed shop rejects purchase actions");
    run.enterRoom(0);
    approach(run);
    check(run.shopOffers[0].sold && run.shopOffers[1].sold && run.shopOffers[2].sold && run.money() == 40,
          "stock and spending persist across room revisits");
    run.jumpDebug(run.arena.shopRoom, true);
    check(!run.shopOpen && run.enemies.empty() && run.shopOffers[1].sold,
          "debug room replay does not add enemies or restock the shop");
    Simulation poor(42, 1, {});
    approach(poor);
    check(!poor.buyShop(1) && poor.money() == 0 && poor.items.empty() && !poor.shopOffers[1].sold,
          "insufficient funds leave the wallet, stock and inventory unchanged");
    Simulation full(42, 1, world);
    approach(full);
    full.items.resize(256, ItemId::Ricochet);
    check(!full.buyShop(1) && full.money() == 100, "full inventory never consumes money");
    full.dead = true;
    full.player.hp = 5;
    check(!full.buyShop(0), "dead players cannot trade");
}
void saving(const std::filesystem::path &directory) {
    for (auto reason : {EndReason::Victory, EndReason::Retreat, EndReason::Death, EndReason::Interrupted}) {
        const auto path = directory / (std::to_string(int(reason)) + ".save");
        CampaignStore store(path);
        auto id = store.begin(1);
        auto funding = *store.data().pending;
        funding.moneyCollected = 100;
        store.resolve(funding, EndReason::Victory);
        id = store.begin(1866);
        Simulation run(1866, id, store.data().world);
        run.moneyPickups = {{run.player.position, 5, 1, false}};
        run.step({});
        approach(run);
        run.player.hp = 50;
        check(run.buyShop(0) && run.buyShop(1) && run.money() == 70,
              "purchases use saved and newly earned money");
        store.checkpoint(run.summary());
        CampaignStore reload(path);
        check(reload.data().pending->moneySpent == 35 && reload.data().pending->moneyCollected == 5,
              "purchase checkpoint persists the debit and earnings separately");
        if (reason == EndReason::Interrupted)
            reload.recover();
        else
            reload.resolve(run.summary(), reason);
        check(reload.data().world.money == 70 && reload.data().history.back().moneySpent == 35,
              "every outcome retains spending instead of refunding purchases");
        reload.resolve(run.summary(), reason);
        check(reload.data().world.money == 70 && !reload.recover(), "resolve/recovery never double-charge");
        CampaignStore again(path);
        check(again.data().world.money == 70 && again.data().history.back().items.size() == 1,
              "wallet debit and purchased-item history survive reload");
    }
    // Version 2 already has a wallet and earnings, but no spending field.
    const std::string summary = "1 42 \"deathward-m1-23\" \"Red Hollow Mine\" \"\" 2 0 0 0 0 5\n"
                                "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0\n0\n";
    const std::string payload = "2 42 50 50 0 0 0 0 0 0 100\n0\n"
                                "\"Sheriff Cole\" \"alive\" 0\n\"Mary Bell\" \"alive\" 0\n"
                                "\"Father Gabriel\" \"alive\" 0\n\"Silas Reed\" \"alive\" 0\n"
                                "\"Dr. Whitmore\" \"alive\" 0\n1\n" +
                                summary + "0\n";
    uint64_t checksum = 14695981039346656037ULL;
    for (unsigned char c : payload) {
        checksum ^= c;
        checksum *= 1099511628211ULL;
    }
    const auto legacy = directory / "v2.save";
    {
        std::ofstream out(legacy, std::ios::binary);
        out << "DEATHWARD 2 " << checksum << '\n' << payload;
    }
    CampaignStore old(legacy);
    check(old.data().world.money == 100 && old.data().pending->moneyCollected == 5 &&
              old.data().pending->moneySpent == 0,
          "money-era saves retain their existing balances on migration");
    old.recover();
    CampaignStore migrated(legacy);
    check(migrated.data().world.money == 105, "legacy pending earnings settle once under the new format");
}
} // namespace
int main() {
    const auto directory =
        std::filesystem::temp_directory_path() /
        ("deathward-shop-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    try {
        std::filesystem::create_directories(directory);
        generation();
        purchases();
        saving(directory);
        std::filesystem::remove_all(directory);
        std::cout
            << "PASS peaceful seeded shops, stock, purchases, menu freeze, spending and save migration\n";
    } catch (const std::exception &e) {
        std::filesystem::remove_all(directory);
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
