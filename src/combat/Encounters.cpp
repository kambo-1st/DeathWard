#include "combat/Simulation.hpp"

namespace dw {
const EnemyDefinition &enemyDefinition(EnemyKind kind) {
    static constexpr std::array<EnemyDefinition, size_t(EnemyKind::Count)> definitions{{
        {"Ash Rusher", 36, 0.6f, 2.6f, 0.45f, 0.8f},
        {"Dust Gunman", 48, 0.6f, 1.8f, 0.5f, 1.9f},
        {"Shotgun Outlaw", 80, 0.65f, 2.1f, 0.75f, 2.5f},
        {"Grave Sharpshooter", 58, 0.6f, 1.5f, 1.15f, 2.8f},
        {"Dynamite Prospector", 64, 0.6f, 1.7f, 0.65f, 3.1f},
        {"Ironhide Brute", 144, 0.8f, 1.4f, 0.85f, 1.5f},
        {"Railbreaker", 110, 0.8f, 1.8f, 0.9f, 2.6f},
        {"Hex Preacher", 72, 0.6f, 1.5f, 1.0f, 5.5f},
        {"Bell Ringer", 96, 0.7f, 1.4f, 1.1f, 3.8f},
        {"Hangman", 80, 0.65f, 1.8f, 0.85f, 3.0f},
        {"Cinder Spitter", 76, 0.7f, 1.5f, 0.75f, 3.8f},
        {"Ricochet Marshal", 72, 0.6f, 1.7f, 0.65f, 2.2f},
        {"Lantern Wraith", 64, 0.6f, 1.6f, 0.75f, 2.0f},
        {"Powder Husk", 48, 0.7f, 1.9f, 0.65f, 1.3f},
        {"Chainbound Outlaw", 68, 0.6f, 1.7f, 0.65f, 2.2f},
        {"Hollow Sheriff", 1100, 1.2f, 1, 0, 1.5f},
    }};
    return definitions.at(size_t(kind));
}

EntityId Simulation::spawn(EnemyKind kind, Vector3 position) {
    if (livingEnemies() >= limits.enemies) {
        suppress({}, "enemy capacity");
        return 0;
    }
    const auto &definition = enemyDefinition(kind);
    Enemy enemy;
    enemy.id = nextEntity_++;
    enemy.kind = kind;
    enemy.position = position;
    enemy.position.y = 0.85f;
    enemy.hp = enemy.maxHp = definition.hp;
    enemy.radius = definition.radius;
    enemy.facing = unit(sub(player.position, enemy.position));
    enemy.cooldown = encounterRng.real(0.6f, 1.8f);
    enemies.push_back(enemy);
    return enemy.id;
}

bool Simulation::placeEnemy(EnemyKind kind, Random &rng, bool spaced) {
    const auto &bounds = arena.rooms[size_t(room)].bounds;
    const float radius = enemyDefinition(kind).radius;
    auto valid = [&](Vector3 point) {
        if (arena.blocked(point, std::max(0.8f, radius)) || distance(point, player.position) < 6)
            return false;
        if (spaced)
            for (const auto &other : enemies)
                if (other.alive && distance(point, other.position) < radius + other.radius + 0.35f)
                    return false;
        return true;
    };
    auto create = [&](Vector3 point) {
        if (!spawn(kind, point))
            return false;
        // Normal rooms use their own stream, independent of prior room visits.
        enemies.back().cooldown = rng.real(0.6f, 1.8f);
        return true;
    };
    for (int attempt = 0; attempt < 240; ++attempt) {
        Vector3 point{rng.real(bounds.min.x + 1, bounds.max.x - 1), 0.85f,
                      rng.real(bounds.min.z + 1, bounds.max.z - 1)};
        if (valid(point))
            return create(point);
    }
    // Deterministic fallback for heavily clipped rooms or crowded cheat spawns.
    for (float x = bounds.min.x + 1; x < bounds.max.x - 1; x += 1)
        for (float z = bounds.min.z + 1; z < bounds.max.z - 1; z += 1)
            if (valid({x, 0.85f, z}))
                return create({x, 0.85f, z});
    return false;
}

void Simulation::spawnEnemies(int count) {
    // Cheat/stress requests retain their explicit count and exercise the whole roster.
    EntityId unpaired = 0;
    for (int i = 0; i < count && livingEnemies() < limits.enemies; ++i) {
        EnemyKind kind =
            unpaired ? EnemyKind::Chainbound : EnemyKind(encounterRng.bounded(OrdinaryEnemyCount));
        if (kind == EnemyKind::Chainbound && !unpaired && i + 1 == count)
            kind = EnemyKind::Gunman;
        if (!placeEnemy(kind, encounterRng, false))
            break;
        if (kind == EnemyKind::Chainbound) {
            if (unpaired) {
                enemies.back().partner = unpaired;
                findEnemy(unpaired)->partner = enemies.back().id;
                unpaired = 0;
            } else
                unpaired = enemies.back().id;
        }
    }
}

int Simulation::roomEnemyCount(int index) const {
    const auto &layout = arena.rooms.at(size_t(index));
    if (layout.kind == RoomKind::Empty || layout.kind == RoomKind::Power)
        return 0;
    if (layout.kind == RoomKind::Boss && !followup)
        return 1;
    return std::clamp(int(std::ceil(layout.usableArea() / 70.0f)), 4, 24);
}

void Simulation::spawnRoomEnemies() {
    const auto &layout = arena.rooms[size_t(room)];
    Random composition(seed_ ^ 0x524f4f4d47524f55ULL ^ (uint64_t(room + 1) * 0x9e3779b97f4a7c15ULL));
    const EnemyKind basic = composition.bounded(2) ? EnemyKind::Rusher : EnemyKind::Gunman;
    std::vector<EnemyKind> pool;
    for (int i = 0; i < OrdinaryEnemyCount; ++i) {
        const auto kind = EnemyKind(i);
        if (kind != basic && (layout.depth > 1 || i <= int(EnemyKind::Ironhide)))
            pool.push_back(kind);
    }
    for (size_t i = 0; i < pool.size(); ++i)
        std::swap(pool[i], pool[i + composition.bounded(uint32_t(pool.size() - i))]);
    const int count = roomEnemyCount(room);
    // Half the group uses a basic role. Each special occupies at most a quarter,
    // rounded up, so a large room never becomes twenty simultaneous hook/sniper casts.
    std::vector<EnemyKind> roster;
    for (int special = 0; special < 2; ++special) {
        const auto kind = pool[size_t(special)];
        int amount = std::max(1, count / 4);
        if (kind == EnemyKind::Chainbound)
            amount = std::max(2, amount - amount % 2);
        for (int i = 0; i < amount; ++i)
            roster.push_back(kind);
    }
    while (int(roster.size()) < count)
        roster.push_back(basic);

    Random placement(seed_ ^ 0x535041574e524f4fULL ^ (uint64_t(room + 1) * 0xbf58476d1ce4e5b9ULL));
    EntityId unpaired = 0;
    for (auto kind : roster) {
        if (!placeEnemy(kind, placement, true))
            break;
        auto &enemy = enemies.back();
        if (kind != EnemyKind::Chainbound)
            continue;
        if (!unpaired) {
            unpaired = enemy.id;
            continue;
        }
        enemy.partner = unpaired;
        auto *partner = findEnemy(unpaired);
        partner->partner = enemy.id;
        // Start the pair close enough to see the tether; never move through cover.
        for (int i = 0; i < 16; ++i) {
            Vector3 point = add(partner->position, rotateY({3, 0, 0}, float(i) * Pi / 8));
            if (arena.roomAt(point) != room || arena.blocked(point, 0.8f) ||
                !arena.sight(point, partner->position) || distance(point, player.position) < 6)
                continue;
            bool occupied = false;
            for (const auto &other : enemies)
                occupied = occupied || (other.id != enemy.id && distance(point, other.position) < 1.6f);
            if (!occupied) {
                enemy.position = point;
                break;
            }
        }
        unpaired = 0;
    }
}
} // namespace dw
