#pragma once
#include "core/Types.hpp"

namespace dw {
enum class WitnessAccount { None, Rourke, Eleanor, Mercer, Cole };
enum class StoryRoom { None, SurveyCamp, SplitRock, RailwayCutting, DryCreek };
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
    ExpeditionPlan(uint64_t seed, bool tutorial = false, WitnessAccount account = WitnessAccount::None);
    uint64_t floorSeed(int floor) const;
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
