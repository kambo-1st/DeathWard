#include "world/ArrivalQuest.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
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
        check(quest.marker(campaign.data().world,residents,ground)->action=="Retry the recovery","unfinished recovery can be retried");
        const auto before=campaign.data().world;
        Simulation search(1866,campaign.data().nextRunId,before,MissionTheme::Canyon,true,true);
        campaign.begin(1866,search.summary().expedition);
        search.player.position=search.arena.miners;search.interact();
        check(!search.rescued,"tutorial has no miner objective");
        search.player.position=search.arena.altar;search.interact();check(!search.altarDestroyed,"tutorial has no altar objective");
        search.finishDebug(true);
        campaign.resolve(search.summary(),EndReason::Victory);
        check(ArrivalQuest::stage(campaign.data().world)==ArrivalStage::Searching,"victory cheat cannot invent recovered documents");
        check(CampaignStore::worldContext(before)==CampaignStore::worldContext(campaign.data().world),"tutorial never applies mine consequences");
        // Traverse real passages with the normal movement/interaction path. Enemy
        // execution keeps this a navigation/quest test rather than an AI soak.
        Simulation tutorial(42,campaign.data().nextRunId,before,MissionTheme::Canyon,true,true);
        campaign.begin(42,tutorial.summary().expedition);tutorial.godMode=true;
        check(tutorial.arena.roomCount()==5&&tutorial.rooms.size()==5,"one short five-room floor");
        check(tutorial.arena.keys.empty()&&tutorial.arena.shopRoom==-1,"no locked detours or shop tutorial overload");
        check(tutorial.roomEnemies(0).empty()&&tutorial.roomEnemies(4).empty(),"safe entrance and document camp");
        check(tutorial.roomEnemies(1).size()==2&&tutorial.roomEnemies(3).size()==3,"two small readable fights");
        for(int next=1;next<5;++next) {
            tutorial.clearRoomDebug();
            const int link=next-1;
            Input command;command.doorTarget=std::pair{link,0};tutorial.step(command);
            for(int tick=0;tick<10000&&tutorial.room<next;++tick)tutorial.step({});
            check(tutorial.room==next,"normal passage navigation reaches the next room");
        }
        check(tutorial.roomClear&&!tutorial.canReturn(),"the final camp requires the documents, not a boss kill");
        tutorial.player.position=tutorial.arena.exit;tutorial.interact();
        check(!tutorial.finished,"exit cannot bypass document recovery");
        Input approach;approach.moveTarget=tutorial.surveyPosition();tutorial.step(approach);
        for(int tick=0;tick<10000&&!tutorial.letterOpen;++tick)tutorial.step({});
        check(tutorial.surveyRecovered&&tutorial.letterOpen&&tutorial.canReturn(),"clicking the reachable cache reads Eleanor's letter");
        const auto time=tutorial.stats.duration;const auto position=tutorial.player.position;
        Input movement;movement.movement={1,0,0};movement.fire=true;tutorial.step(movement);
        check(tutorial.stats.duration==time&&distance(position,tutorial.player.position)==0,"reading freezes movement and combat");
        campaign.checkpoint(tutorial.summary());
        CampaignStore interrupted(save);check(interrupted.recover(),"document pickup is a recoverable checkpoint");
        check(ArrivalQuest::stage(interrupted.data().world)==ArrivalStage::Report,"reload retains recovered records and letter");
        check(interrupted.data().world.prosperity==before.prosperity&&!interrupted.data().world.flags.contains("something_followed"),"interruption has no mine penalty");
        tutorial.letterOpen=false;tutorial.player.position=tutorial.arena.exit;tutorial.interact();
        check(tutorial.finished,"return lantern ends the single floor");
        check(quest.marker(interrupted.data().world,residents,ground)->action=="Talk to commander","recovery returns to a physical report objective");
        check(!ArrivalQuest::dialogue(ArrivalStage::Report).empty(),"report has authored dialogue");
        ArrivalQuest::advance(interrupted,ArrivalStage::Report);
        CampaignStore completed(save);
        check(ArrivalQuest::stage(completed.data().world)==ArrivalStage::Complete&&!ArrivalQuest::ready(completed.data().world),"report completes the tutorial and stops relaunching it");
        WorldState legacy=before;legacy.flags.erase("redstone.survey_requested");legacy.flags.insert("redstone.daughter_missing");
        check(ArrivalQuest::stage(legacy)==ArrivalStage::Searching,"legacy missing-daughter flags resume at the revised recovery");
        for(uint64_t seed:{0ULL,1ULL,1866ULL}) {
            Arena a(seed,MissionTheme::Canyon,true,true),b(seed,MissionTheme::Canyon,true,true);
            check(a.floorCells==b.floorCells&&a.rooms.size()==5,"tutorial remains seed reproducible");
            check(distance(a.exit,a.rooms.back().objective)>6,"cache interaction cannot trap the player at the return lantern");
            check(!a.blocked(a.rooms.back().objective,.48f)&&!a.path(a.rooms.back().entry,a.rooms.back().objective,.48f).empty(),"survey cache stays reachable across seeds");
            check(!a.path(a.rooms.back().objective,a.exit,.48f).empty(),"return lantern stays reachable");
        }
        // Scene editor changes move the objective rather than leaving a stale world coordinate.
        for(auto &i:scene.instances)if(i.id.starts_with("story-settler-tent-0:"))i.transform.m12+=8;
        quest.locate(scene,ground);
        WorldState evening;evening.flags={"redstone.arrived","redstone.evening_conductor"};
        check(std::abs(quest.marker(evening,residents,ground)->position.x-(-23))<.01f,"sleep marker follows the edited tent");
        // Real format-3 pending run, before the document bit existed.
        const std::string payload="2 42 50 50 0 0 0 0 0 0 100\n6\n"
            "\"redstone.arrived\"\n\"redstone.evening_conductor\"\n\"redstone.slept\"\n"
            "\"redstone.morning_conductor\"\n\"redstone.daughter_missing\"\n\"redstone.search_started\"\n"
            "\"Sheriff Cole\" \"alive\" 0\n\"Mary Bell\" \"alive\" 0\n"
            "\"Father Gabriel\" \"alive\" 0\n\"Silas Reed\" \"alive\" 0\n\"Dr. Whitmore\" \"alive\" 0\n1\n"
            "1 42 \"deathward-m1-53\" \"Before First Light\" \"\" 2 0 0 0 0 5 0\n"
            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0\n0\n0\n";
        uint64_t hash=14695981039346656037ULL;
        for(unsigned char c:payload)hash=(hash^c)*1099511628211ULL;
        {std::ofstream out(save);out<<"DEATHWARD 3 "<<hash<<'\n'<<payload;}
        CampaignStore old(save);check(old.recover(),"version-3 pending search recovers");
        CampaignStore migrated(save);
        check(ArrivalQuest::stage(migrated.data().world)==ArrivalStage::Searching&&
            !migrated.data().history.back().surveyRecovered&&migrated.data().world.money==105&&
            migrated.data().world.prosperity==50,"legacy progress and wallet migrate without invented documents or mine penalties");
        std::filesystem::remove(save);
        std::cout<<"PASS arrival quest ordering, persistence, physical approaches, scene anchors and tutorial navigation, documents, interruption recovery and mine isolation\n";
    } catch(const std::exception &e) {std::filesystem::remove(save);std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}
}
