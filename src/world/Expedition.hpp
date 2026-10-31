#pragma once
#include "core/Types.hpp"
#include "world/RailNetwork.hpp"
#include <memory>

namespace dw {
enum class WitnessAccount { None, Rourke, Eleanor, Mercer, Cole };
enum class StoryRoom { None, SurveyCamp, SplitRock, RailwayCutting, DryCreek };
enum class ExpeditionPacing { Growing, Classic, ShortCorridors, SmallRooms, Compact };
const char *expeditionPacingName(ExpeditionPacing pacing);
ExpeditionPacing nextExpeditionPacing(ExpeditionPacing pacing);
enum class EncounterPattern { Pursuit, Crossfire, ChargeLane, SupplyGuard };
enum class FloorVariant { Standard, Scorched, Flooded, Dank, Scarred };
enum class BossKind { None, Sheriff, Ridgeback, PowderForeman, StormMarshal, Isaac };
enum class BossForm { Normal, Cyan, Yellow, Green };
constexpr bool canyonBoss(BossKind kind) {
    return kind==BossKind::Ridgeback||kind==BossKind::PowderForeman||kind==BossKind::StormMarshal||kind==BossKind::Isaac;
}
struct FloorProfile {
    int band = -1; // Disabled for the tutorial and Classic comparison.
    const char *name = "Classic";
    std::array<int,4> patterns{1,0,0,0};
    int maxThreat = 9, maxSpecialists = 1;
    float areaPerThreat = 95, cooldownScale = 1;
    int rocks = 2, seams = 1, barrels = 1, outcrops = 3;
    float dust = 1;
    BossKind boss = BossKind::Ridgeback;
    int floor = 0; // Zero-based expedition floor; service unlocks use this, not the difficulty band.
    FloorVariant variant = FloorVariant::Standard;
    MonsterId bossMonster{};
    BossForm bossForm=BossForm::Normal;
    bool doubleBossRoom=false;
    std::shared_ptr<const RailLayout> bossRails;
    int stageStep=0,sourceStage=1; // Local progression mapping, distinct from source XML stageHP.
    bool active() const { return band >= 0; }
};
const char *encounterPatternName(EncounterPattern pattern);
struct FloorDimensions {
    // Half extents in two-metre floor tiles. Defaults preserve original geometry.
    int minHalfTiles = 6, maxHalfTiles = 10;
    bool smallerRooms = false, shorterCorridors = false;
    int minGapTiles = 4, maxGapTiles = 8;
};
const char *accountName(WitnessAccount account);
const char *storyRoomName(StoryRoom room);
const char *storyClaim(StoryRoom room);
const char *storyObservation(StoryRoom room);
const char *storyQuestion(StoryRoom room);

// A run's floor seeds and narrative schedule never consume combat/loot RNG.
struct ExpeditionPlan {
    uint64_t seed;
    WitnessAccount account;
    int floorCount;
    ExpeditionPacing pacing;
    ExpeditionPlan(uint64_t seed, bool tutorial = false, WitnessAccount account = WitnessAccount::None,
                   ExpeditionPacing pacing = ExpeditionPacing::Compact);
    uint64_t floorSeed(int floor) const;
    int roomsOnFloor(int floor) const;
    FloorDimensions dimensionsOnFloor(int floor) const;
    FloorProfile profileOnFloor(int floor) const;
    BossKind bossOnFloor(int floor) const;
    StoryRoom storyAt(int floor) const;
};
struct StoryEvidence {
    StoryRoom room = StoryRoom::None;
    WitnessAccount account = WitnessAccount::None;
    int floor = 0;
    uint64_t floorSeed = 0;
    bool operator==(const StoryEvidence &) const = default;
};
}
