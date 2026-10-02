#pragma once
#include "world/Campaign.hpp"
#include "world/TownCharacters.hpp"

namespace dw {
enum class ArrivalStage { None, Conductor, Tent, MorningConductor, Commander, Trail, Searching, Report, Complete };
struct QuestLine { std::string speaker, text; };
struct QuestMarker {
    std::string title, instruction, action, symbol;
    Vector3 position{}, approach{};
    float radius = 2.2f;
};
// Small, persisted story prototype. Scene references are resolved on each map load;
// quest progress belongs to the campaign, not to the editable town document.
class ArrivalQuest {
  public:
    static ArrivalStage stage(const WorldState &world);
    static bool morning(const WorldState &world) { return stage(world)>=ArrivalStage::MorningConductor; }
    static bool ready(const WorldState &world) { const auto s=stage(world);return s==ArrivalStage::Trail||s==ArrivalStage::Searching; }
    static void begin(CampaignStore &campaign);
    static void advance(CampaignStore &campaign, ArrivalStage expected);
    static std::vector<QuestLine> dialogue(ArrivalStage stage);
    static constexpr const char *Letter =
        "Father, the northern cutting is not on the route you showed the lieutenant. "
        "I have put the survey sheets back in the leather case. Please tell him yourself why we are going there. "
        "You asked me to come west and learn to stand on my own feet. Then let me ask questions without calling it weakness. "
        "Eleanor";
    void locate(const TownDocument &scene, const HubWorld &ground);
    std::optional<QuestMarker> marker(const WorldState &world, const TownCharacters &residents,
                                     const HubWorld &ground) const;
    TownCharacter conductor;
  private:
    std::optional<Vector3> tent_, bedApproach_;
};
}
