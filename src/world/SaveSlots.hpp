#pragma once
#include "world/ArrivalQuest.hpp"

namespace dw {
enum class SlotState { Empty, Ready, Unavailable };
struct SaveSlot {
    SlotState state = SlotState::Empty;
    std::filesystem::path file;
    std::string chapter = "A ticket west", detail = "Begin a new journey", error;
    bool opening = true, interrupted = false;
    size_t expeditions = 0;
};
// Reading the menu never creates, repairs or recovers a campaign. Only the
// selected slot is opened for play; CampaignStore remains the save authority.
class SaveSlots {
  public:
    static constexpr size_t Count = 3;
    explicit SaveSlots(std::filesystem::path directory) : directory_(std::move(directory)) {}
    std::filesystem::path path(size_t slot) const;
    SaveSlot inspect(size_t slot) const;
    SaveSlot start(size_t slot) const;
  private:
    std::filesystem::path directory_;
};
}
