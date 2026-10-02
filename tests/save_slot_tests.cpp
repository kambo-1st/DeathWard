#include "world/SaveSlots.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const char *why) {if(!ok)throw std::runtime_error(why);}
std::string bytes(const std::filesystem::path &p) {std::ifstream in(p,std::ios::binary);return {std::istreambuf_iterator<char>(in),{}};}
int main() {
    const auto root=std::filesystem::temp_directory_path()/("deathward-slots-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    try {
        SaveSlots slots(root/"slots");
        for(size_t i=0;i<SaveSlots::Count;++i)check(slots.inspect(i).state==SlotState::Empty,"all three slots begin empty");
        check(!std::filesystem::exists(root),"browsing empty slots performs no writes");
        CampaignStore old(root/"campaign.save");old.setFlag("unrelated.campaign",true);
        const auto original=bytes(old.path());
        const auto first=slots.start(0);
        check(first.state==SlotState::Ready&&first.opening,"new slot saves before entering the train");
        check(slots.inspect(1).state==SlotState::Empty&&slots.inspect(2).state==SlotState::Empty,"starting one slot leaves the others empty");
        CampaignStore firstCampaign(first.file);ArrivalQuest::begin(firstCampaign);
        ArrivalQuest::advance(firstCampaign,ArrivalStage::Conductor);
        auto progress=bytes(first.file);
        const auto resumed=slots.start(0);
        check(!resumed.opening&&resumed.chapter=="Shelter for the night","continue uses the arrival checkpoint without replaying the train");
        check(bytes(first.file)==progress,"resuming does not reset the selected campaign");
        slots.start(1);CampaignStore second(slots.path(1));
        check(!second.data().world.flags.contains("redstone.arrived"),"slot two has independent story progress");
        firstCampaign.begin(1866,SurveyExpeditionTitle);progress=bytes(first.file);
        check(slots.inspect(0).interrupted,"menu describes a pending expedition");
        check(bytes(first.file)==progress,"inspecting a pending run does not recover it");
        check(bytes(old.path())==original,"legacy single campaign is untouched");
        {std::ofstream bad(slots.path(2));bad<<"damaged save bytes";}
        const auto damaged=bytes(slots.path(2));
        check(slots.inspect(2).state==SlotState::Unavailable,"corrupt slot is visible but unavailable");
        bool rejected=false;try{slots.start(2);}catch(...){rejected=true;}
        check(rejected&&bytes(slots.path(2))==damaged,"corruption is never overwritten by new-game selection");
        bool range=false;try{slots.path(3);}catch(...){range=true;}
        check(range,"there are exactly three slots");
        const auto blocked=root/"not-a-directory";{std::ofstream file(blocked);file<<"keep";}
        rejected=false;try{SaveSlots(blocked).start(0);}catch(...){rejected=true;}
        check(rejected&&bytes(blocked)=="keep","an unusable save folder fails without losing existing data");
        std::filesystem::remove_all(root);
        std::cout<<"PASS three-slot isolation, story resume, read-only browsing, corruption and write failure\n";
    } catch(const std::exception &e) {std::filesystem::remove_all(root);std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}
}
