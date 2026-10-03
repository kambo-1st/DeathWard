#include "world/SaveSlots.hpp"
#include <stdexcept>

namespace dw {
std::filesystem::path SaveSlots::path(size_t slot) const {
    if (slot >= Count) throw std::out_of_range("Save slot must be between 1 and 3");
    return directory_ / ("slot-" + std::to_string(slot + 1) + ".save");
}
SaveSlot SaveSlots::inspect(size_t slot) const {
    SaveSlot result;
    result.file = path(slot);
    try {
        if (!std::filesystem::exists(result.file)) return result;
        CampaignStore campaign(result.file);
        result.state = SlotState::Ready;
        const auto &data = campaign.data();
        const auto stage = ArrivalQuest::stage(data.world);
        result.opening = stage == ArrivalStage::None;
        result.interrupted = data.pending.has_value();
        result.expeditions = data.history.size();
        switch (stage) {
        case ArrivalStage::None: result.chapter = "Westbound"; result.detail = "Aboard the evening train"; break;
        case ArrivalStage::Conductor: result.chapter = "An unexpected stop"; result.detail = "Speak to the conductor"; break;
        case ArrivalStage::Tent: result.chapter = "Shelter for the night"; result.detail = "Find your tent in the camp"; break;
        case ArrivalStage::MorningConductor: result.chapter = "Still stranded"; result.detail = "Ask about the morning departure"; break;
        case ArrivalStage::Commander: result.chapter = "Something is wrong"; result.detail = "Speak to the fort commander"; break;
        case ArrivalStage::Trail: result.chapter = "The lost survey"; result.detail = "Recover Bell's records"; break;
        case ArrivalStage::Searching: result.chapter = "The lost survey"; result.detail = "Retry the recovery trail"; break;
        case ArrivalStage::Report: result.chapter = "The recovered papers"; result.detail = "Report to the commander"; break;
        case ArrivalStage::Complete: result.chapter = "He died fighting"; result.detail = "Hear Caleb Rourke's account"; break;
        case ArrivalStage::RourkeTrail: result.chapter = "Rourke's account"; result.detail = "Follow his route into the badlands"; break;
        case ArrivalStage::RourkeSearching: result.chapter = "Rourke's account"; result.detail = "Continue the investigation"; break;
        case ArrivalStage::EleanorResponse: result.chapter = "Another account"; result.detail = "Speak to Eleanor Bell"; break;
        case ArrivalStage::AccountComplete: result.chapter = "Questions remain"; result.detail = "Rourke's account examined"; break;
        }
        if (result.interrupted) result.detail = "Interrupted at floor "+std::to_string(data.pending->floor+1)+
            " / "+std::to_string(data.pending->floorCount)+": return to the fort";
    } catch (const std::exception &e) {
        result.state = SlotState::Unavailable;
        result.chapter = "Save unavailable";
        result.detail = "The original file has been kept";
        result.error = e.what();
    }
    return result;
}
SaveSlot SaveSlots::start(size_t slot) const {
    const auto info = inspect(slot);
    if (info.state == SlotState::Unavailable) throw std::runtime_error(info.error);
    if (info.state == SlotState::Empty) {
        CampaignStore campaign(info.file);
        campaign.setFlag("journey.started", true);
    }
    return inspect(slot);
}
}
