#pragma once
#include "core/Types.hpp"
#include <filesystem>
#include <optional>
#include <set>

namespace dw {
enum class EndReason : int { Victory, Death, Retreat, Interrupted };
struct Npc {
    std::string name;
    std::string state = "alive";
    int relationship = 0;
};
struct WorldState {
    int population = 42, prosperity = 50, law = 50;
    bool minersRescued = false, bossDefeated = false, mineOpen = false, altarDestroyed = false;
    int mineDebt = 0;
    uint64_t completed = 0;
    uint64_t money = 0;
    std::set<std::string> flags;
    std::array<Npc, 5> npcs{
        {{"Sheriff Cole"}, {"Mary Bell"}, {"Father Gabriel"}, {"Silas Reed"}, {"Dr. Whitmore"}}};
};
struct RunSummary {
    uint64_t id = 0, seed = 0;
    std::string version = ContentVersion, expedition = "Red Hollow Mine", startingContext;
    EndReason reason = EndReason::Retreat;
    bool rescued = false, bossKilled = false, altarDestroyed = false, interrupted = false;
    Stats stats;
    uint64_t moneyCollected = 0;
    uint64_t moneySpent = 0;
    std::vector<ItemId> items;
    std::vector<std::string> consequences;
};
struct Campaign {
    WorldState world;
    uint64_t nextRunId = 1;
    std::optional<RunSummary> pending;
    std::vector<RunSummary> history;
};
class CampaignStore {
  public:
    explicit CampaignStore(std::filesystem::path path);
    const Campaign &data() const {
        return campaign_;
    }
    const std::filesystem::path &path() const {
        return path_;
    }
    uint64_t begin(uint64_t seed, const std::string &expedition = "Red Hollow Mine");
    void checkpoint(const RunSummary &summary);
    RunSummary resolve(const RunSummary &summary, EndReason reason);
    bool recover();
    void reset();
    void setFlag(const std::string &flag, bool value);
    static std::string worldContext(const WorldState &world);
    static std::filesystem::path defaultPath();

  private:
    std::filesystem::path path_;
    Campaign campaign_;
    void commit(Campaign next);
};
std::string outcomeTitle(const RunSummary &summary);
std::string npcDialogue(const WorldState &world, size_t npc);
} // namespace dw
