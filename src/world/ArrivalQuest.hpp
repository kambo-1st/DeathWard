#pragma once
#include "world/Campaign.hpp"
#include "world/TownCharacters.hpp"

namespace dw {
enum class ArrivalStage { None, Conductor, Tent, MorningConductor, Commander, Trail, Searching };
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
    static bool ready(const WorldState &world) { return stage(world)>=ArrivalStage::Trail; }
    static void begin(CampaignStore &campaign);
    static void advance(CampaignStore &campaign, ArrivalStage expected);
    static std::vector<QuestLine> dialogue(ArrivalStage stage);
    void locate(const TownDocument &scene, const HubWorld &ground);
    std::optional<QuestMarker> marker(const WorldState &world, const TownCharacters &residents,
                                     const HubWorld &ground) const;
    TownCharacter conductor;
  private:
    std::optional<Vector3> tent_, bedApproach_;
};
}
