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
ExpeditionPlan::ExpeditionPlan(uint64_t value,bool tutorial,WitnessAccount witness)
    :seed(value),account(tutorial?WitnessAccount::None:witness),
     floorCount(tutorial?1:4+int(mix(value^0x464c4f4f52504c4eULL)%5)) {}
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
