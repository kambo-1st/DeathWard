#include "world/Expedition.hpp"
#include <stdexcept>

namespace dw {
namespace {
uint64_t mix(uint64_t x) {
    x=(x^(x>>30))*0xbf58476d1ce4e5b9ULL;
    x=(x^(x>>27))*0x94d049bb133111ebULL;
    return x^(x>>31);
}
}
const char *expeditionPacingName(ExpeditionPacing pacing) {
    switch(pacing) {
    case ExpeditionPacing::Classic:return "CLASSIC / 15 ROOMS";
    case ExpeditionPacing::ShortCorridors:return "TRIAL / SHORT CORRIDORS";
    case ExpeditionPacing::SmallRooms:return "TRIAL / SMALL ROOMS";
    case ExpeditionPacing::Compact:return "COMPACT / 9 TO 15 ROOMS";
    default:return "GROWING / 9 TO 15 ROOMS";
    }
}
ExpeditionPacing nextExpeditionPacing(ExpeditionPacing pacing) {
    switch(pacing) {
    case ExpeditionPacing::Growing:return ExpeditionPacing::ShortCorridors;
    case ExpeditionPacing::ShortCorridors:return ExpeditionPacing::SmallRooms;
    case ExpeditionPacing::SmallRooms:return ExpeditionPacing::Compact;
    case ExpeditionPacing::Compact:return ExpeditionPacing::Classic;
    default:return ExpeditionPacing::Growing;
    }
}
ExpeditionPlan::ExpeditionPlan(uint64_t value,bool tutorial,WitnessAccount witness,ExpeditionPacing pacingValue)
    :seed(value),account(tutorial?WitnessAccount::None:witness),
     floorCount(tutorial?1:4+int(mix(value^0x464c4f4f52504c4eULL)%5)),pacing(pacingValue) {}
int ExpeditionPlan::roomsOnFloor(int floor) const {
    if(floor<0||floor>=floorCount)throw std::out_of_range("Invalid expedition floor");
    if(floorCount==1)return 5;
    if(pacing==ExpeditionPacing::Classic)return 15;
    // Four floors: 9,11,13,15. Eight: 9,10,11,12,13,14,15,15.
    const int growth=std::max(floor,(6*floor+(floorCount-1)/2)/(floorCount-1));
    return std::min(15,9+growth);
}
FloorDimensions ExpeditionPlan::dimensionsOnFloor(int floor) const {
    if(floor<0||floor>=floorCount)throw std::out_of_range("Invalid expedition floor");
    FloorDimensions result;
    result.smallerRooms=pacing==ExpeditionPacing::SmallRooms||pacing==ExpeditionPacing::Compact;
    result.shorterCorridors=pacing==ExpeditionPacing::ShortCorridors||pacing==ExpeditionPacing::Compact;
    // Keep the authored tutorial's room envelopes. It can still compare shorter
    // connectors without losing any of its five story steps.
    if(floorCount==1)result.smallerRooms=false;
    const int span=std::max(1,floorCount-1);
    if(result.smallerRooms) {
        result.minHalfTiles=5+floor/span;
        result.maxHalfTiles=7+3*floor/span;
    }
    result.minGapTiles=4+2*floor/span;
    result.maxGapTiles=8+4*floor/span;
    return result;
}
BossKind ExpeditionPlan::bossOnFloor(int floor) const {
    if(floor<0||floor>=floorCount)throw std::out_of_range("Invalid expedition floor");
    if(floorCount==1||pacing==ExpeditionPacing::Classic)return BossKind::None;
    static constexpr int weights[4][3]={{6,3,1},{3,6,2},{2,6,4},{2,3,7}};
    const std::array<BossKind,3> kinds{BossKind::Ridgeback,BossKind::PowderForeman,BossKind::StormMarshal};
    int previous=-1;
    for(int at=0;at<=floor;++at) {
        const int band=std::min(3,at*4/floorCount);
        int total=0;for(int k=0;k<3;++k)if(k!=previous)total+=weights[band][k];
        Random rng(floorSeed(at)^0x424f5353504f4f4cULL);
        int roll=int(rng.bounded(uint32_t(total)));
        for(int k=0;k<3;++k)if(k!=previous) {
            roll-=weights[band][k];if(roll<0){previous=k;break;}
        }
    }
    return kinds[size_t(previous)];
}
FloorProfile ExpeditionPlan::profileOnFloor(int floor) const {
    if(floor<0||floor>=floorCount)throw std::out_of_range("Invalid expedition floor");
    if(floorCount==1||pacing==ExpeditionPacing::Classic)return {};
    const int band=std::min(3,floor*4/floorCount);
    static const std::array<FloorProfile,4> profiles{{
        {0,"Outer Washes",{6,2,0,2},9,1,95,1.1f,2,1,1,1,.5f},
        {1,"Broken Quarry",{2,4,5,2},14,3,85,1.f,4,2,1,3,.7f},
        {2,"Abandoned Works",{1,3,2,6},18,4,80,.94f,2,2,3,2,.65f},
        {3,"Storm Cut",{2,4,4,3},22,5,75,.88f,3,1,2,2,1.f}
    }};
    auto result=profiles[size_t(band)];
    result.floor=floor;
    result.stageStep=floor>0&&std::min(3,(floor-1)*4/floorCount)==band?1:0;
    result.boss=bossOnFloor(floor);
    return result;
}
const char *encounterPatternName(EncounterPattern pattern) {
    switch(pattern) {
    case EncounterPattern::Crossfire:return "Staggered crossfire";
    case EncounterPattern::ChargeLane:return "Charge lane";
    case EncounterPattern::SupplyGuard:return "Guarded pocket";
    default:return "Pursuit and cover";
    }
}
uint64_t ExpeditionPlan::floorSeed(int floor) const {
    if(floor<0||floor>=floorCount)throw std::out_of_range("Invalid expedition floor");
    // Preserve the original first-floor layout of ordinary expeditions.
    return floor==0?seed:mix(seed+uint64_t(floor)*0x9e3779b97f4a7c15ULL);
}
StoryRoom ExpeditionPlan::storyAt(int floor) const {
    // Only Rourke's first account is currently authored. Future accounts must
    // supply their own claims and schedule, never reuse his text as objective truth.
    if(account!=WitnessAccount::Rourke)return StoryRoom::None;
    if(floor==0)return StoryRoom::SurveyCamp;
    if(floor==floorCount/3)return StoryRoom::SplitRock;
    if(floor==2*floorCount/3)return StoryRoom::RailwayCutting;
    if(floor==floorCount-1)return StoryRoom::DryCreek;
    return StoryRoom::None;
}
const char *accountName(WitnessAccount account) {
    switch(account) {
    case WitnessAccount::Rourke:return "CALEB ROURKE'S ACCOUNT";
    case WitnessAccount::Eleanor:return "ELEANOR BELL'S ACCOUNT";
    case WitnessAccount::Mercer:return "NATHANIEL MERCER'S ACCOUNT";
    case WitnessAccount::Cole:return "ELIAS COLE'S ACCOUNT";
    default:return "EXPEDITION";
    }
}
const char *storyRoomName(StoryRoom room) {
    switch(room) {
    case StoryRoom::SurveyCamp:return "Survey Camp";
    case StoryRoom::SplitRock:return "The Split Rock";
    case StoryRoom::RailwayCutting:return "Old Railway Cutting";
    case StoryRoom::DryCreek:return "The Dry Creek";
    default:return "The Badlands";
    }
}
const char *storyClaim(StoryRoom room) {
    switch(room) {
    case StoryRoom::SurveyCamp:return "Rourke says Bell hired him to reach the northern survey line, against Lieutenant Mercer's objections.";
    case StoryRoom::SplitRock:return "Rourke says Bell carried an old military map marking a lost payroll wagon. He demanded a share of the money.";
    case StoryRoom::RailwayCutting:return "Rourke says Mercer fled before the shooting. He remembers only himself and Bell exchanging fire across the creek.";
    case StoryRoom::DryCreek:return "Rourke describes a magnificent duel: Bell drew first, fired repeatedly and refused to surrender. 'He died better than most men live.'";
    default:return "";
    }
}
const char *storyObservation(StoryRoom room) {
    switch(room) {
    case StoryRoom::SurveyCamp:return "An abandoned camp contains survey pegs and a weathered route sketch. It establishes a stop along this route, not the party's motives.";
    case StoryRoom::SplitRock:return "The distinctive cleft matches the landmark Rourke described. No payroll cache or money has been recovered here.";
    case StoryRoom::RailwayCutting:return "Spent cartridges and rock impacts mark a firing position outside the duel route Rourke described. Their exact timing is unknown.";
    case StoryRoom::DryCreek:return "Bell's recovered revolver has one discharged chamber. Rourke described Bell firing several times. The weapon's handling after the fight is unknown.";
    default:return "";
    }
}
const char *storyQuestion(StoryRoom room) {
    switch(room) {
    case StoryRoom::SurveyCamp:return "Why did Bell choose this route? A camp does not establish a treasure hunt.";
    case StoryRoom::SplitRock:return "Did the map show payroll money, something else, or only what Rourke wanted to see?";
    case StoryRoom::RailwayCutting:return "Who fired from this position, and when? Rourke's account leaves it unexplained.";
    case StoryRoom::DryCreek:return "Is his duel embellished? Reloading or later handling could also explain the cylinder. This does not establish who killed Bell.";
    default:return "";
    }
}
}
