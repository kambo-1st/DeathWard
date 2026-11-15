#pragma once
#include "core/Types.hpp"
#include "world/CanyonTerrain.hpp"
#include "world/MissionTheme.hpp"
#include "world/Expedition.hpp"
#include <memory>
#include <optional>
#include <set>

namespace dw {
// Original comparison preset. Runtime loops must use arena.roomCount().
inline constexpr int RoomCount = 15;
inline constexpr int MinFloorRooms = 9;
inline constexpr float FloorTile = 2;
using FloorCell = std::pair<int, int>;
enum class RoomKind { Combat, Power, Boss, Empty, Shop, Service };
enum class RoomService { None, Exchange, Surgeon, Smuggler };
const char *roomServiceName(RoomService service);
struct RoomGraph {
    std::vector<FloorCell> cells = std::vector<FloorCell>(RoomCount);
    std::vector<std::array<int, 2>> links;
    int powerRooms = 1;
};
RoomGraph generateRoomGraph(uint64_t seed, bool tutorial = false, int rooms = RoomCount);
struct RoomHeartSpawn {
    Vector3 preferred{};
    uint32_t pickupSeed=0;
    int x=0,y=0,sourceSubtype=0,subtype=0;
};
struct RoomChestSpawn {
    Vector3 preferred{};
    uint32_t pickupSeed=0;
    int x=0,y=0,ordinal=0;
};
struct RoomCoinSpawn {
    Vector3 preferred{};
    uint32_t pickupSeed=0;
    int x=0,y=0,ordinal=0,sourceSubtype=0,subtype=0;
};
using RoomBombSpawn = RoomCoinSpawn;
using RoomKeySpawn = RoomCoinSpawn; // Same original-cell/ordinal/identity descriptor.
struct RoomLayout {
    Box bounds;
    Vector3 center{}, entry{}, exit{}, objective{}, bossSpawn{};
    int shape = 0, depth = 0;
    float floorArea = -1;
    RoomKind kind = RoomKind::Combat;
    StoryRoom story = StoryRoom::None;
    RoomService service = RoomService::None;
    // Room-wide condition (e.g. a future Flush effect). A river crossing is
    // not automatically a flooded room: dry banks must remain dry gameplay.
    bool flooded = false;
    int sourceCombatTemplate = -1; // Recorded opening-floor encounter, -1 = generated pool.
    int sourceHeartTemplate=-1; // Heart layer only; not a full source encounter.
    int sourceObstacleTemplate=-1; // Selected complete rock/pickup arrangement.
    uint32_t sourceRoomSelectionSeed=0, sourceRoomSpawnSeed=0;
    std::vector<RoomHeartSpawn> heartSpawns;
    std::vector<RoomChestSpawn> chestSpawns;
    std::vector<RoomCoinSpawn> coinSpawns;
    std::vector<RoomKeySpawn> keySpawns;
    std::vector<RoomBombSpawn> bombSpawns;
    Vector3 reward{};
    std::vector<int> passages;
    std::vector<Box> floors, obstacles;
    float usableArea() const;
};
struct Passage {
    std::array<int, 2> rooms{};
    Vector3 from{}, to{};
    Box floor;
    std::array<Box, 2> gates;
    std::array<bool, 2> sealed{};
    bool locked = false;
    bool closed(int side) const {
        return locked || sealed[size_t(side)];
    }
    bool open() const {
        return !closed(0) && !closed(1);
    }
};
struct KeyPickup {
    int room = 0;
    Vector3 position{};
    bool collected = false;
};
enum class StoryPropKind { Cart, Crate, SplitRock, Rail, Timber };
struct StoryProp { StoryPropKind kind; Box bounds; };
struct ScorchPatch { Vector3 position; float radius=1, angle=0; };
enum class BreakableKind { CrackedRock, OreSeam, PowderBarrel, CacheGate, CacheSide, Dung };
struct Breakable {
    uint64_t id = 0, lootSeed = 0;
    int room = 0;
    BreakableKind kind = BreakableKind::CrackedRock;
    Box bounds{};
    Vector3 rewardPosition{};
    int health = 1;
    float fuse = -1;
    bool destroyed = false, paid = false;
    int initialHealth = 1;
    int sourceGridIndex = -1;
    bool solid() const { return !destroyed; }
};
struct SupplyCache {
    int room = -1;
    Box bounds{}; // Reserved interior: residents and ordinary loot cannot spawn here.
    Vector3 approach{}, reward{};
};
struct Arena {
    uint64_t visualSeed = 0;
    MissionTheme theme = MissionTheme::Mine;
    FloorProfile profile;
    std::shared_ptr<CanyonTerrain> canyon;
    std::optional<RailNetwork> rails;
    // Default construction provides an empty test arena; expeditions always supply a seed.
    Box bounds{{-15, -1, -15}, {15, 4, 15}};
    std::vector<RoomLayout> rooms = std::vector<RoomLayout>(RoomCount);
    int roomCount() const { return int(rooms.size()); }
    std::vector<Passage> passages;
    std::vector<KeyPickup> keys;
    int shopRoom = -1;
    std::vector<Box> floors, boundaryWalls, obstacles, walls;
    // Solid actor/prop footprints affect movement and navigation, not world-ray
    // hits. Statues still receive their actual projectile/entity damage hooks;
    // chest bodies do not become bullet cover merely by blocking characters.
    std::vector<Box> movementBodies;
    std::vector<Box> flightWalls, flightCover;
    bool flightCollisionPrepared = false;
    std::vector<StoryProp> storyProps, floorProps;
    std::vector<ScorchPatch> scorchPatches, dampPatches;
    std::vector<Breakable> breakables;
    SupplyCache supplyCache;
    std::set<FloorCell> floorCells;
    Vector3 entrance{0, 0.85f, 10}, exit{0, 0.85f, -13}, miners{-10, 0.85f, -8}, altar{10, 0.85f, -8};
    Arena() = default;
    explicit Arena(uint64_t seed, MissionTheme missionTheme = MissionTheme::Mine, bool canyonRiver = true,
                   bool tutorial = false, StoryRoom story = StoryRoom::None, int rooms = RoomCount,
                   FloorDimensions dimensions = {}, FloorProfile profile = {}, bool sourceCombatRoom = false, int roomHeartLayouts = 0);
    void prepareRoomHeartLayouts(uint64_t seed,int mode);
    void prepareSourceHeartRocks();
    void sealRoom(int index);
    Vector3 doorPosition(int passage, int side) const;
    Vector3 doorApproach(int passage, int side) const;
    void rebuildWalls();
    void dressStoryRoom();
    void dressFloor();
    void allocateServices();
    void prepareBossArena();
    void prepareRailArena(int index=-1);
    void prepareBreakables(uint64_t seed);
    bool reservedSupplyCache(Vector3 point, float radius) const {
        return supplyCache.room >= 0 && sphereBox(point,radius,supplyCache.bounds);
    }
    int roomAt(Vector3 p) const;
    bool contains(Vector3 p) const;
    bool blocked(Vector3 p, float radius) const;
    bool sight(Vector3 from, Vector3 to) const;
    bool clear(Vector3 from, Vector3 to, float radius) const;
    SegmentHit trace(Vector3 from, Vector3 to, float radius = 0) const;
    Vector3 move(Vector3 from, Vector3 delta, float radius) const;
    bool flightBlocked(Vector3 point, float radius, int room) const;
    bool flightClear(Vector3 from, Vector3 to, float radius, int room) const;
    float flightHeight(Vector3 point, float radius) const;
    Vector3 fly(Vector3 from, Vector3 delta, float radius, int room) const;
    bool swimmingRoom(int room) const;
    bool swimBlocked(Vector3 point, float radius, int room) const;
    bool swimClear(Vector3 from, Vector3 to, float radius, int room) const;
    Vector3 swim(Vector3 from, Vector3 delta, float radius, int room) const;
    std::vector<Vector3> flightPath(Vector3 from, Vector3 target, float radius, int room) const;
    std::vector<Vector3> path(Vector3 from, Vector3 target, float radius) const;
    std::vector<Vector3> swimPath(Vector3 from,Vector3 target,float radius,int room) const;
};
} // namespace dw
