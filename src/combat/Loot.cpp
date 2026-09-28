#include "combat/Simulation.hpp"

namespace dw {
void Simulation::prepareMoney() {
    // A separate stream keeps loot from changing room layouts, groups or attacks.
    Random rng(seed_ ^ 0x4d4f4e4559475244ULL);
    for (int index = 0; index < RoomCount; ++index) {
        const auto &layout = arena.rooms[size_t(index)];
        const int maximum = std::clamp(int(layout.usableArea() / 260), 1, 4);
        const int count = index == 0 ? 1 + int(rng.bounded(2)) : int(rng.bounded(maximum + 1));
        for (int pile = 0; pile < count; ++pile)
            for (int attempt = 0; attempt < 120; ++attempt) {
                const Vector3 point{rng.real(layout.bounds.min.x + 1, layout.bounds.max.x - 1), .85f,
                                    rng.real(layout.bounds.min.z + 1, layout.bounds.max.z - 1)};
                if (arena.roomAt(point) != index || arena.blocked(point, .65f) ||
                    distance(point, arena.entrance) < 2.5f || distance(point, layout.objective) < 2.5f ||
                    distance(point, layout.entry) < 2.5f || distance(point, layout.exit) < 2.5f)
                    continue;
                if (std::any_of(moneyPickups.begin(), moneyPickups.end(),
                                [&](const auto &coin) { return distance(point, coin.position) < 2; }) ||
                    std::any_of(arena.keys.begin(), arena.keys.end(),
                                [&](const auto &key) { return distance(point, key.position) < 2; }))
                    continue;
                Vector3 start = layout.center;
                start.y = .85f;
                if (arena.blocked(start, .48f))
                    start = layout.entry;
                if (arena.path(start, point, .48f).empty())
                    continue;
                moneyPickups.push_back({point, 1 + int(rng.bounded(5)), 1, false});
                break;
            }
    }
}
void Simulation::dropMoney(const Enemy &enemy) {
    const auto *definition = monsterDefinition(enemy.monster);
    // Summoned offspring and permanent hazards must not become an infinite farm.
    if (enemy.friendly || enemy.generation > 0 || (definition && definition->roomHazard))
        return;
    Random rng(seed_ ^ 0x4d4f4e455944524fULL ^ (enemy.id * 0x9e3779b97f4a7c15ULL));
    if (rng.bounded(100) >= 35)
        return;
    const int value = 1 + int(rng.bounded(5));
    const Vector3 origin{enemy.position.x, .85f, enemy.position.z};
    // Flying enemies can die above rock: find nearby walkable ground for the drop.
    for (int ring = 0; ring <= 12; ++ring)
        for (int direction = 0; direction < (ring ? 16 : 1); ++direction) {
            const auto point =
                add(origin, rotateY({float(ring) * .5f, 0, 0}, float(direction) * 2 * Pi / 16));
            if (arena.blocked(point, .55f))
                continue;
            // Bound long cheat/stress sessions by stacking nearby drops when full.
            if (moneyPickups.size() >= 1024) {
                auto nearest = std::min_element(
                    moneyPickups.begin(), moneyPickups.end(), [&](const auto &a, const auto &b) {
                        return distance(a.position, point) < distance(b.position, point);
                    });
                nearest->value = std::min(1000000, nearest->value + value);
            } else
                moneyPickups.push_back({point, value, 0, true});
            return;
        }
}
void Simulation::updateMoney(float dt) {
    uint64_t collected = 0;
    for (auto &coin : moneyPickups) {
        coin.age += dt;
        if (player.hp <= 0 || (coin.dropped && coin.age < .45f) ||
            distance(player.position, coin.position) > 1.25f ||
            !arena.clear(player.position, coin.position, .1f))
            continue;
        const auto amount = std::min(uint64_t(coin.value), MaxMoney - money());
        if (!amount)
            continue;
        moneyCollected += amount;
        collected += amount;
        coin.value -= int(amount);
        audioCues.push(AudioCueKind::Pickup, coin.position);
        effectVisual(coin.position, .45f, 0, .3f);
    }
    std::erase_if(moneyPickups, [](const auto &coin) { return coin.value == 0; });
    // Keep encounter instructions visible; the wallet itself updates immediately.
    if (collected)
        checkpointNeeded = true;
}
} // namespace dw
