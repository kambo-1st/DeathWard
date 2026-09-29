#pragma once
#include "audio/AudioState.hpp"
#include "combat/Monsters.hpp"
#include "core/Types.hpp"
#include "world/Campaign.hpp"
#include "world/Dungeon.hpp"
#include "world/Particles.hpp"
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
    Monster,
    Count
};
inline constexpr int OrdinaryEnemyCount = int(EnemyKind::Boss);
struct EnemyDefinition {
    const char *name;
    float hp, radius, speed, windup, cooldown;
};
const EnemyDefinition &enemyDefinition(EnemyKind kind);
enum class EnemyState {
    Ready,
    Windup,
    Charging,
    Stunned,
    Teleporting,
    Collapsed,
    Buried,
    Jumping,
    Exposed,
    Returning
};
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
    int monster = 0, generation = 0;
    float auxiliary = 0, trailTime = 0, lift = 0;
    Vector3 home{};
    uint64_t observedShots = 0;
    bool awakened = false, friendly = false;
    float idleTime = 0;
    float animationTime() const {
        return age + idleTime;
    }
};
struct Player {
    Vector3 position{0, 0.85f, 10}, aim{0, 0.85f, 0};
    Vector3 velocity{}, facing{0, 0, -1};
    float shootPose = 0;
    bool dodgeMoving = false;
    float baseHealth = StartingHealth, shotDamage = RevolverDamage;
    float hp = StartingHealth, maxHp = StartingHealth, fireCooldown = 0, dodge = 0, dodgeCooldown = 0,
          hurt = 0;
    Vector3 dodgeDirection{0, 0, -1};
    int nextRound = 1;
    Vector3 pullTarget{};
    float pullTime = 0;
    float slowTime = 0;
};
enum class ProjectileKind { Bullet, Hook, Homing, SplitShot, BurstShot, Tar, Flame, ReturningHead, Rock };
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
    bool execution = false;
    int bounces = 0;
    ProjectileKind projectileKind = ProjectileKind::Bullet;
};
enum class HazardKind {
    Dynamite,
    Fire,
    Ring,
    Powder,
    Creep,
    Tar,
    Beam,
    HolyLight,
    Gas,
    MonsterBomb,
    PlayerDynamite
};
struct Hazard {
    HazardKind kind = HazardKind::Dynamite;
    Vector3 position{}, origin{};
    float age = 0, delay = 1, duration = 0, radius = 3, damage = 20;
    bool alive = true, hitPlayer = false;
    Context context;
    Vector3 velocity{};
    bool settled = false;
    bool playerContact = false;
};
// Shared by live charges and the mouse aiming preview.
void advanceDynamite(Hazard &charge, const Arena &arena, float dt);
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
    std::optional<Vector3> dynamiteTarget;
    bool placeDynamite = false;
    bool fire = false, dodge = false, interact = false, standStill = false;
};
struct RoomProgress {
    bool visited = false, cleared = false, rewardTaken = false;
    std::array<ItemId, 2> offers{};
    // The active room uses Simulation::enemies; other rooms keep their actual group here.
    std::vector<Enemy> residents;
};
struct MoneyPickup {
    Vector3 position{};
    int value = 1;
    float age = 0;
    bool dropped = false;
};
enum class ShopOfferKind { Power, Medicine, Dynamite };
struct ShopOffer {
    ItemId item = ItemId::Ricochet;
    int price = 25;
    ShopOfferKind kind = ShopOfferKind::Power;
    bool sold = false;
};

class Simulation {
  public:
    Simulation(uint64_t seed, uint64_t runId, const WorldState &world,
               MissionTheme theme = MissionTheme::Mine);
    Player player;
    Arena arena;
    Stats stats;
    Limits limits;
    Random encounterRng, rewardRng, combatRng;
    std::vector<Enemy> enemies;
    std::vector<Projectile> projectiles;
    std::vector<VisualEffect> visuals;
    std::vector<ParticleBurst> particleBursts;
    std::vector<Hazard> hazards;
    std::vector<MoneyPickup> moneyPickups;
    uint64_t moneyCollected = 0;
    uint64_t moneySpent = 0;
    std::array<ShopOffer, 4> shopOffers{};
    bool shopOpen = false;
    AudioCueQueue audioCues;
    uint64_t audioEpoch = 0;
    std::vector<ItemId> items;
    std::array<ItemId, 2> offers{};
    std::array<RoomProgress, RoomCount> rooms{};
    int keys = 0, powerUpsTaken = 0;
    int dynamite = StartingDynamite;
    float dynamiteCooldown = 0;
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
    EntityId spawnMonster(int id, Vector3 position);
    void spawnMonsterDebug(int id);
    size_t roomThreats() const;
    void spawnEnemies(int count);
    int roomEnemyCount(int index) const;
    const std::vector<Enemy> &roomEnemies(int index) const;
    void spawnRoomEnemies();
    void startBoss();
    void killAll();
    void clearRoomDebug();
    void jumpDebug(int index, bool restart = false);
    void healDebug();
    void tunePlayer(float baseHealth, float shotDamage);
    void startStress();
    void interact();
    void openShop();
    void closeShop();
    bool buyShop(int index);
    bool throwDynamite(Vector3 target);
    bool placeDynamite();
    std::vector<Vector3> dynamiteTrajectory(Vector3 target) const;
    std::string shopUnavailable(int index) const;
    std::string nearbyInteraction() const;
    std::optional<Vector3> moveDestination() const {
        return movePath_.empty() ? std::nullopt : std::optional<Vector3>(movePath_.back());
    }
    void finishDebug(bool victory);
    RunSummary summary() const;
    uint64_t money() const {
        return startingWorld_.money + moneyCollected - moneySpent;
    }
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
    static std::string roomName(int index, MissionTheme theme = MissionTheme::Mine);
    void announce(std::string text, float seconds = 3);
    void queueRoot(Event event);
    void emit(Event event, const Context &parent, int effect = -1);
    void drainEvents();
    void suppress(const Context &context, const std::string &reason);
    void particleEffect(ParticleEffect kind, Vector3 position, Vector3 direction = {0,1,0}, float scale = 1);
    ParticleEffect impactMaterial(Vector3 position, Vector3 normal) const;
    void effectVisual(Vector3 position, float radius, int kind, float duration = 0.4f);

  private:
    uint64_t seed_, runId_, nextEntity_ = 1, nextChain_ = 1;
    uint32_t nextParticle_ = 1; // Cosmetic stream: never consumes gameplay RNG.
    WorldState startingWorld_;
    std::deque<Event> queue_;
    // 4-unit XZ cells are a broad phase only; narrow phase uses swept 3D volumes.
    std::array<std::vector<size_t>, 100> grid_;
    std::vector<Vector3> movePath_;
    size_t waypoint_ = 0;
    bool interactOnArrival_ = false;
    std::optional<std::pair<int, int>> doorOnArrival_;
    struct MonsterSpawn {
        int id;
        Vector3 position;
        EntityId partner = 0;
        int generation = 0;
        bool collapsed = false;
    };
    std::vector<MonsterSpawn> pendingMonsters_;
    void flushMonsterSpawns(Random *placement = nullptr, float playerClearance = 0);
    void queueMonster(int id, Vector3 position, EntityId partner = 0, int generation = 0,
                      bool collapsed = false);
    void updateMonster(Enemy &enemy, float dt);
    void attackMonster(Enemy &enemy);
    bool collapseMonster(Enemy &enemy);
    void monsterDeath(const Enemy &enemy, const Event &event);
    void monsterPattern(const Enemy &enemy, int count, float angle = 0, float speed = 9,
                        ProjectileKind kind = ProjectileKind::Bullet);
    void monsterPatch(const Enemy &enemy, HazardKind kind, Vector3 position, float radius, float delay = .5f,
                      float duration = 3);
    void monsterBeam(const Enemy &enemy, Vector3 direction, float delay = .4f);
    void monsterLines(const Enemy &enemy, HazardKind kind, bool diagonal = false);
    void moveMonster(Enemy &enemy, Vector3 velocity, float dt);
    void requestMove(Vector3 target);
    void cancelMove();
    bool accept(Event event);
    void process(const Event &event);
    void createProjectile(const Event &event);
    void updatePlayer(const Input &input, float dt);
    void kickDynamiteOnContact(Vector3 previousPosition);
    void beginBossEncounter();
    void prepareRoomEnemies(int index);
    bool roomSpawnClear(Vector3 position, float radius) const;
    void updateEnemies(float dt);
    void performEnemyAttack(Enemy &enemy);
    void updateHazards(float dt);
    void addHazard(Hazard hazard);
    void clearHazards();
    bool hurtPlayer(float damage, const Context &context = {}, bool hostile = true);
    float enemyDamage(const Enemy &enemy, const Event &event) const;
    void shootEnemy(const Enemy &enemy, Vector3 direction, float damage, float speed, int bounces = 0,
                    ProjectileKind kind = ProjectileKind::Bullet);
    bool placeEnemy(EnemyKind kind, Random &rng, bool spaced, int monster = 0);
    void updateProjectiles(float dt);
    void rebuildGrid();
    std::vector<size_t> candidates(Vector3 from, Vector3 to, float radius) const;
    void collectChains();
    void offerReward();
    void collectKeys();
    void prepareMoney();
    void dropMoney(const Enemy &enemy);
    void updateMoney(float dt);
    void prepareShop();
    Hazard makeDynamite(Vector3 target) const;
    bool deployDynamite(Hazard charge);
};
} // namespace dw
