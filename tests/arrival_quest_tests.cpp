#include "world/ArrivalQuest.hpp"
#include <chrono>
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
int main() {
    const auto save=std::filesystem::temp_directory_path()/("deathward-arrival-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".save");
    try {
        CampaignStore campaign(save);
        check(ArrivalQuest::stage(campaign.data().world)==ArrivalStage::None,"existing campaigns start without a Redstone quest");
        ArrivalQuest::begin(campaign);ArrivalQuest::begin(campaign);
        TownDocument scene;std::string error;
        const auto directory=std::filesystem::path(DEATHWARD_ASSET_DIR)/"redstone";
        check(scene.load(directory/"town.scene",error),error.c_str());
        HubWorld ground;check(ground.load(directory/"town.nav"),ground.error.c_str());
        ObjectAnimationSystem motion;motion.reset(scene);ground.setMovingSolids(motion.solids());
        TownCharacters residents;residents.reset(scene,ground);
        ArrivalQuest quest;quest.locate(scene,ground);
        for(int n=1;n<=5;++n) {
            const auto stage=ArrivalStage(n);check(ArrivalQuest::stage(campaign.data().world)==stage,"quest stages stay ordered");
            const auto marker=quest.marker(campaign.data().world,residents,ground);
            check(bool(marker),"each story stage has an objective marker");
            if(!ground.walkable(marker->approach))throw std::runtime_error("Blocked quest approach: "+marker->action+" at "+std::to_string(marker->approach.x)+","+std::to_string(marker->approach.z));
            check(ground.moveTo(marker->approach),"real routes connect the train, tent, fort and badlands");
            for(int step=0;step<12000&&ground.destination();++step)ground.step({},Tick);
            check(!ground.destination(),"the player reaches each quest approach without teleporting");
            check(!ArrivalQuest::dialogue(stage).empty(),"the action has conversation or confirmation text");
            CampaignStore reopened(save);check(ArrivalQuest::stage(reopened.data().world)==stage,"progress reloads before advancing");
            bool rejected=false;try{ArrivalQuest::advance(campaign,ArrivalStage::None);}catch(...){rejected=true;}
            check(rejected,"out-of-order actions cannot skip conversations");
            ArrivalQuest::advance(campaign,stage);
        }
        check(ArrivalQuest::morning(campaign.data().world)&&ArrivalQuest::ready(campaign.data().world),"sleep and commander unlock the morning search");
        check(quest.marker(campaign.data().world,residents,ground)->action=="Continue the search","returning keeps the unresolved search available");
        const auto before=campaign.data().world;
        Simulation search(1866,campaign.data().nextRunId,before,MissionTheme::Canyon,true);search.missingDaughterSearch=true;
        campaign.begin(1866,search.summary().expedition);
        search.player.position=search.arena.miners;search.interact();
        check(!search.rescued,"the daughter search does not trigger unrelated miner rescues");
        search.player.position=search.arena.altar;search.interact();check(!search.altarDestroyed,"the daughter search has no altar objective");
        search.bossKilled=true;
        campaign.resolve(search.summary(),EndReason::Retreat);
        check(!campaign.data().world.bossDefeated&&!campaign.data().world.minersRescued,"search results do not resolve unrelated storylines");
        CampaignStore reopened(save);check(ArrivalQuest::stage(reopened.data().world)==ArrivalStage::Searching,"search progress survives returning and reloading");
        // Scene editor changes move the objective rather than leaving a stale world coordinate.
        for(auto &i:scene.instances)if(i.id.starts_with("story-settler-tent-0:"))i.transform.m12+=8;
        quest.locate(scene,ground);
        WorldState evening;evening.flags={"redstone.arrived","redstone.evening_conductor"};
        check(std::abs(quest.marker(evening,residents,ground)->position.x-(-23))<.01f,"sleep marker follows the edited tent");
        std::filesystem::remove(save);
        std::cout<<"PASS arrival quest ordering, persistence, physical approaches, scene anchors and search isolation\n";
    } catch(const std::exception &e) {std::filesystem::remove(save);std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}
}
