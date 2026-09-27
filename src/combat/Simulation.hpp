#pragma once
#include "core/Types.hpp"
#include "world/Campaign.hpp"
#include "world/Dungeon.hpp"
#include <deque>
#include <functional>
#include <optional>
#include <unordered_map>

namespace dw {
enum class EnemyKind { Rusher, Gunman, Boss };
struct Enemy {
    EntityId id = 0;
    EnemyKind kind = EnemyKind::Rusher;
    Vector3 position{}, velocity{};
    float hp = 40, maxHp = 40, radius = 0.65f, cooldown = 1, flash = 0, age = 0;
    int phase = 0;
    bool alive = true;
};
struct Player {
    Vector3 position{0, 0.85f, 10}, aim{0, 0.85f, 0};
    float hp = StartingHealth, maxHp = StartingHealth, fireCooldown = 0, dodge = 0, dodgeCooldown = 0,
          hurt = 0;
    Vector3 dodgeDirection{0, 0, -1};
    int nextRound = 1;
};
struct Projectile {
    EntityId id = 0;
    Vector3 position{}, previous{}, origin{}, velocity{};
    float damage = RevolverDamage, life = 3.2f, radius = 0.14f;
    bool hostile = false, lastRound = false, ghost = false, alive = true;
    int bounces = 0, pierce = 0;
    Context context;
    std::vector<EntityId> hitEntities;
};
enum class EventType {
    Shot,
    ProjectileHit,
    ProjectileBounce,
    Damage,
    EnemyDamaged,
    EnemyKilled,
    Explosion,
    PlayerDamaged,
    RoomCleared,
    Pickup
};
struct Event {
    EventType type = EventType::Shot;
    Context context;
    EntityId target = 0;
    Vector3 position{}, direction{0, 0, -1}, origin{};
    float damage = RevolverDamage, radius = 3.3f, speed = 26;
    bool hostile = false, lastRound = false, ghost = false;
};
struct VisualEffect {
    Vector3 position{};
    float radius = 1, life = 0.4f, maxLife = 0.4f;
    int kind = 0;
};
struct Chain {
    uint64_t accepted = 0, queued = 0, active = 0, kills = 0;
    bool stopped = false;
};
struct Limits {
    int maxDepth = 16;
    size_t eventsPerChain = 8192, eventsPerTick = 2048, queuedEvents = 16384, projectiles = 4096,
           enemies = 256;
};
struct ChainLog {
    uint64_t id = 0;
    int generation = 0, effect = -1;
    std::string reason;
    uint64_t suppressed = 1;
};
struct Input {
    Vector3 movement{}, aim{0, 0.85f, 0};
    std::optional<Vector3> moveTarget;
    bool fire = false, dodge = false, interact = false, standStill = false;
};

class Simulation {
  public:
    Simulation(uint64_t seed, uint64_t runId, const WorldState &world);
    Player player;
    Arena arena;
    Stats stats;
    Limits limits;
    Random encounterRng, rewardRng, combatRng;
    std::vector<Enemy> enemies;
    std::vector<Projectile> projectiles;
    std::vector<VisualEffect> visuals;
    std::vector<ItemId> items;
    std::array<ItemId, 3> offers{};
    std::deque<ChainLog> logs;
    std::unordered_map<uint64_t, Chain> chains;
    bool godMode = false, rewardOpen = false, roomClear = false, finished = false, dead = false;
    bool rescued = false, altarDestroyed = false, bossKilled = false, checkpointNeeded = false;
    bool followup = false, debugScenario = false;
    int room = 0, wave = 0;
    float waveDelay = 1.0f, messageTime = 0;
    std::string message;
    static constexpr int FinalRoom = 6;

    void step(const Input &input, float dt = Tick);
    void grant(ItemId item);
    void chooseReward(int index);
    void nextRoom();
    void enterRoom(int index);
    Vector3 onwardDestination() const;
    EntityId spawn(EnemyKind kind, Vector3 position);
    void spawnWave(int count);
    void startBoss();
    void killAll();
    void startStress();
    void interact();
    std::string nearbyInteraction() const;
    std::optional<Vector3> moveDestination() const {
        return movePath_.empty() ? std::nullopt : std::optional<Vector3>(movePath_.back());
    }
    void finishDebug(bool victory);
    RunSummary summary() const;
    size_t livingEnemies() const;
    size_t queuedEvents() const {
        return queue_.size();
    }
    size_t itemStacks(ItemId item) const;
    Enemy *findEnemy(EntityId id);
    const Enemy *boss() const;
    std::string roomName() const;
    static std::string roomName(int index);
    void announce(std::string text, float seconds = 3);
    void queueRoot(Event event);
    void emit(Event event, const Context &parent, int effect = -1);
    void drainEvents();
    void suppress(const Context &context, const std::string &reason);
    void effectVisual(Vector3 position, float radius, int kind, float duration = 0.4f);

  private:
    uint64_t seed_, runId_, nextEntity_ = 1, nextChain_ = 1;
    WorldState startingWorld_;
    std::deque<Event> queue_;
    // 4-unit XZ cells are a broad phase only; narrow phase uses swept 3D volumes.
    std::array<std::vector<size_t>, 100> grid_;
    std::vector<Vector3> movePath_;
    size_t waypoint_ = 0;
    bool interactOnArrival_ = false;
    void requestMove(Vector3 target);
    void cancelMove();
    bool accept(Event event);
    void process(const Event &event);
    void createProjectile(const Event &event);
    void updatePlayer(const Input &input, float dt);
    void beginBossEncounter();
    void updateEnemies(float dt);
    void updateProjectiles(float dt);
    void rebuildGrid();
    std::vector<size_t> candidates(Vector3 from, Vector3 to, float radius) const;
    void collectChains();
    void offerReward();
};
} // namespace dw
