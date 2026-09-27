#pragma once
#include "core/Types.hpp"
#include "world/Campaign.hpp"
#include "world/Dungeon.hpp"
#include <deque>
#include <functional>
#include <optional>
#include <unordered_map>

namespace dw {
enum class EnemyKind {
    Rusher,
    Gunman,
    Shotgun,
    Sharpshooter,
    Prospector,
    Ironhide,
    Railbreaker,
    Preacher,
    BellRinger,
    Hangman,
    Spitter,
    Marshal,
    Wraith,
    PowderHusk,
    Chainbound,
    Boss,
    Count
};
inline constexpr int OrdinaryEnemyCount = int(EnemyKind::Boss);
struct EnemyDefinition {
    const char *name;
    float hp, radius, speed, windup, cooldown;
};
const EnemyDefinition &enemyDefinition(EnemyKind kind);
enum class EnemyState { Ready, Windup, Charging, Stunned, Teleporting };
struct Enemy {
    EntityId id = 0;
    EnemyKind kind = EnemyKind::Rusher;
    Vector3 position{}, velocity{};
    float hp = 40, maxHp = 40, radius = 0.65f, cooldown = 1, flash = 0, age = 0;
    int phase = 0;
    bool alive = true;
    EnemyState state = EnemyState::Ready;
    Vector3 facing{0, 0, -1}, target{};
    float stateTime = 0, aura = 0, pathTime = 0;
    EntityId partner = 0;
    std::vector<Vector3> path;
};
struct Player {
    Vector3 position{0, 0.85f, 10}, aim{0, 0.85f, 0};
    Vector3 velocity{}, facing{0, 0, -1};
    float shootPose = 0;
    bool dodgeMoving = false;
    float hp = StartingHealth, maxHp = StartingHealth, fireCooldown = 0, dodge = 0, dodgeCooldown = 0,
          hurt = 0;
    Vector3 dodgeDirection{0, 0, -1};
    int nextRound = 1;
    Vector3 pullTarget{};
    float pullTime = 0;
};
enum class ProjectileKind { Bullet, Hook };
struct Projectile {
    EntityId id = 0;
    Vector3 position{}, previous{}, origin{}, velocity{};
    float damage = RevolverDamage, life = 3.2f, radius = 0.14f;
    bool hostile = false, lastRound = false, ghost = false, alive = true;
    int bounces = 0, pierce = 0;
    ProjectileKind kind = ProjectileKind::Bullet;
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
    bool armorPiercing = false, areaDamage = false;
    int bounces = 0;
    ProjectileKind projectileKind = ProjectileKind::Bullet;
};
enum class HazardKind { Dynamite, Fire, Ring, Powder };
struct Hazard {
    HazardKind kind = HazardKind::Dynamite;
    Vector3 position{}, origin{};
    float age = 0, delay = 1, duration = 0, radius = 3, damage = 20;
    bool alive = true, hitPlayer = false;
    Context context;
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
           enemies = 256, hazards = 256;
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
    std::optional<std::pair<int, int>> doorTarget;
    bool fire = false, dodge = false, interact = false, standStill = false;
};
struct RoomProgress {
    bool visited = false, cleared = false, rewardTaken = false;
    std::array<ItemId, 2> offers{};
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
    std::vector<Hazard> hazards;
    std::vector<ItemId> items;
    std::array<ItemId, 2> offers{};
    std::array<RoomProgress, RoomCount> rooms{};
    int keys = 0, powerUpsTaken = 0;
    std::deque<ChainLog> logs;
    std::unordered_map<uint64_t, Chain> chains;
    bool godMode = false, rewardOpen = false, roomClear = false, finished = false, dead = false;
    bool rescued = false, altarDestroyed = false, bossKilled = false, checkpointNeeded = false;
    bool followup = false, debugScenario = false;
    int room = 0;
    float messageTime = 0;
    std::string message;
    static constexpr int FinalRoom = RoomCount - 1;

    void step(const Input &input, float dt = Tick);
    void grant(ItemId item);
    void chooseReward(int index);
    void enterRoom(int index);
    void clearRoom();
    void requestDoor(int passage, int side);
    bool useDoor(int passage, int side);
    EntityId spawn(EnemyKind kind, Vector3 position);
    void spawnEnemies(int count);
    int roomEnemyCount(int index) const;
    void spawnRoomEnemies();
    void startBoss();
    void killAll();
    void clearRoomDebug();
    void jumpDebug(int index, bool restart = false);
    void healDebug();
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
    const Enemy *findEnemy(EntityId id) const;
    bool chainActive(const Enemy &enemy) const;
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
    std::optional<std::pair<int, int>> doorOnArrival_;
    void requestMove(Vector3 target);
    void cancelMove();
    bool accept(Event event);
    void process(const Event &event);
    void createProjectile(const Event &event);
    void updatePlayer(const Input &input, float dt);
    void beginBossEncounter();
    void updateEnemies(float dt);
    void performEnemyAttack(Enemy &enemy);
    void updateHazards(float dt);
    void addHazard(Hazard hazard);
    void clearHazards();
    bool hurtPlayer(float damage, const Context &context = {});
    float enemyDamage(const Enemy &enemy, const Event &event) const;
    void shootEnemy(const Enemy &enemy, Vector3 direction, float damage, float speed, int bounces = 0,
                    ProjectileKind kind = ProjectileKind::Bullet);
    bool placeEnemy(EnemyKind kind, Random &rng, bool spaced);
    void updateProjectiles(float dt);
    void rebuildGrid();
    std::vector<size_t> candidates(Vector3 from, Vector3 to, float radius) const;
    void collectChains();
    void offerReward();
    void collectKeys();
};
} // namespace dw
