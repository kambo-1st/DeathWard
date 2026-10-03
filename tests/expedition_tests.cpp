#include "combat/Simulation.hpp"
#include "world/ArrivalQuest.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const std::string &why) {if(!ok)throw std::runtime_error(why);}
void plans() {
    std::set<int> counts;
    for(uint64_t seed=0;seed<256;++seed) {
        const ExpeditionPlan a(seed,false,WitnessAccount::Rourke),b(seed,false,WitnessAccount::Rourke);
        check(a.floorCount>=4&&a.floorCount<=8&&a.floorCount==b.floorCount,"seeded 4-8 floor count");
        counts.insert(a.floorCount);std::set<uint64_t> seeds;std::vector<StoryRoom> sites;
        for(int floor=0;floor<a.floorCount;++floor) {
            check(a.floorSeed(floor)==b.floorSeed(floor),"stable floor seeds");seeds.insert(a.floorSeed(floor));
            if(a.storyAt(floor)!=StoryRoom::None)sites.push_back(a.storyAt(floor));
        }
        check(seeds.size()==size_t(a.floorCount),"distinct floor seeds within a run");
        check(sites==std::vector{StoryRoom::SurveyCamp,StoryRoom::SplitRock,StoryRoom::RailwayCutting,StoryRoom::DryCreek},"four ordered story beats within full floors");
        check(ExpeditionPlan(seed,true).floorCount==1,"tutorial is the one-floor exception");
    }
    check(counts.size()==5,"all expedition lengths occur");
    check(std::string(accountName(WitnessAccount::Cole)).find("ACCOUNT")!=std::string::npos,"Cole is also explicitly attributed");
}
void layouts() {
    for(uint64_t seed:{0ULL,1ULL,42ULL,1866ULL,8192ULL}) {
        const ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            const auto site=plan.storyAt(floor);if(site==StoryRoom::None)continue;
            Arena arena(plan.floorSeed(floor),MissionTheme::Canyon,true,false,site);
            check(arena.roomCount()==15&&arena.shopRoom>=0,"story preserves 15-room floor and shop");
            int tagged=0,powers=0;
            for(const auto &room:arena.rooms) {
                if(room.kind==RoomKind::Power)++powers;
                if(room.story==StoryRoom::None)continue;
                ++tagged;
                check(room.kind!=RoomKind::Power&&room.kind!=RoomKind::Shop,"story does not replace reward rooms");
                check(!arena.blocked(room.objective,.48f)&&!arena.path(room.entry,room.objective,.48f).empty(),"story objective is reachable");
                for(const auto link:room.passages) {
                    const auto &p=arena.passages[size_t(link)];
                    const int index=int(&room-arena.rooms.data());
                    const int side=p.rooms[0]==index?0:1;
                    check(!arena.path(room.objective,arena.doorApproach(link,side),.48f).empty(),"dressing leaves all passage approaches reachable");
                }
                if(site==StoryRoom::DryCreek) {
                    check(distance(room.objective,arena.exit)>5.3f,"inspect and leave footprints do not overlap");
                    check(!arena.path(room.objective,arena.exit,.48f).empty(),"return lantern reachable");
                }
            }
            check(tagged==1&&powers>=1&&powers<=2,"one embedded story site; normal rewards retained");
            check(!arena.storyProps.empty(),"story dressing fits the generated room");
            for(size_t i=0;i<arena.storyProps.size();++i)for(size_t j=i+1;j<arena.storyProps.size();++j) {
                const auto a=arena.storyProps[i].bounds,b=arena.storyProps[j].bounds;
                check(a.max.x<=b.min.x||a.min.x>=b.max.x||a.max.z<=b.min.z||a.min.z>=b.max.z,
                    "story dressing footprints do not overlap, including low rails");
            }
            if(site==StoryRoom::SplitRock)
                check(std::count_if(arena.storyProps.begin(),arena.storyProps.end(),[](const auto &p){return p.kind==StoryPropKind::SplitRock;})==2,"the split landmark has two halves");
            for(const auto &prop:arena.storyProps) {
                auto p=mul(add(prop.bounds.min,prop.bounds.max),.5f);p.y=.85f;
                check(arena.canyon->height(p.x,p.z)<=.06f,"dressing sits on flat terrain");
                const auto road=arena.canyon->roadSample(p);const auto river=arena.canyon->riverSample(p);
                check(road.distance>road.width&&river.distance>river.width,"dressing stays out of roads and rivers");
                if(prop.bounds.max.y>.45f)check(arena.blocked(p,.48f),"substantial props have collision");
            }
        }
    }
}
void inspect(Simulation &run) {
    const int site=run.storyRoomIndex();if(site<0)return;
    run.jumpDebug(site);run.clearRoomDebug();
    Input input;input.moveTarget=run.arena.rooms[size_t(site)].objective;run.step(input);
    for(int tick=0;tick<10000&&run.storyOpen==StoryRoom::None;++tick)run.step({});
    check(run.storyOpen!=StoryRoom::None&&run.storySeen(),"normal click-to-walk examines the site");
    const auto record=run.evidence.back();
    check(record.floor==run.floor&&record.floorSeed==run.expedition.floorSeed(run.floor)&&record.account==WitnessAccount::Rourke,"observation retains its provenance");
    const auto duration=run.stats.duration;const auto position=run.player.position;
    input.movement={1,0,0};input.fire=true;run.step(input);
    check(run.stats.duration==duration&&distance(position,run.player.position)==0,"reading freezes the simulation");
    run.storyOpen=StoryRoom::None;
    const auto count=run.evidence.size();run.interact();run.storyOpen=StoryRoom::None;
    check(run.evidence.size()==count,"rereading does not duplicate evidence");
}
void journey(const std::filesystem::path &path) {
    CampaignStore campaign(path);
    for(const auto *flag:{"redstone.arrived","redstone.evening_conductor","redstone.slept","redstone.morning_conductor","redstone.survey_requested","redstone.search_started","redstone.survey_recovered","redstone.survey_reported","redstone.rourke_heard","redstone.rourke_departed"})campaign.setFlag(flag,true);
    const auto before=campaign.data().world;
    Simulation run(42,campaign.data().nextRunId,before,MissionTheme::Canyon,true,false,WitnessAccount::Rourke);
    campaign.begin(42,run.summary().expedition);run.godMode=true;
    check(campaign.data().pending->account==WitnessAccount::Rourke&&
        campaign.data().pending->floorCount==run.expedition.floorCount,"the very first pending save records the account and plan");
    const int total=run.expedition.floorCount;
    for(int floor=0;floor<total;++floor) {
        check(run.floor==floor&&run.arena.roomCount()==15&&!run.finished,"every floor remains a full ordinary dungeon");
        check(!run.rescued&&!run.altarDestroyed,"story has no inherited miner or altar goals");
        run.jumpDebug(run.finalRoom());run.clearRoomDebug();run.player.position=run.arena.exit;run.interact();
        if(run.storyRoomIndex()>=0)check(!run.floorExitRequested&&!run.finished,"unread required site gates the exit");
        inspect(run);
        // Debug travel heals by design, so set carry-over values after travel.
        run.jumpDebug(run.finalRoom());run.clearRoomDebug();
        run.grant(ItemId::Ricochet);run.player.hp=37;run.player.shotDamage=11;run.player.nextRound=4;
        run.moneyCollected+=13;run.moneySpent+=2;run.keys=3;run.dynamite=2;run.stats.shots+=9;
        run.player.position=run.arena.exit;run.interact();
        const auto hp=run.player.hp;const auto items=run.items;const auto wallet=run.money();const auto stats=run.stats;
        campaign.checkpoint(run.summary());
        CampaignStore saved(path);check(saved.data().pending->evidence==run.evidence&&saved.data().pending->floor==floor,"floor and evidence survive reload");
        if(floor+1<total) {
            check(run.floorExitRequested&&!run.finished&&!run.canReturn(),"intermediate exit continues the run");
            check(run.advanceFloor(),"advancing loads a floor");
            check(run.player.hp==hp&&run.player.shotDamage==11&&run.player.nextRound==4&&run.items==items,"health, damage, loaded round and build carry without healing");
            check(run.money()==wallet&&run.keys==3&&run.dynamite==2,"currency, keys and dynamite carry");
            check(run.stats.kills==stats.kills&&run.stats.duration==stats.duration&&run.stats.rooms==stats.rooms+1,"statistics span all floors");
            check(run.room==0&&run.roomClear&&run.enemies.empty()&&run.projectiles.empty()&&run.chains.empty()&&!run.rewardOpen&&!run.shopOpen&&!run.floorExitRequested,"fresh safe entrance without stale combat or modal state");
            check(run.powerUpsTaken==0&&run.roomEnemies(1).size()>0,"new rewards and populated rooms");
            for(const auto &room:run.rooms)for(const auto &enemy:room.residents)
                check(enemy.observedShots==run.stats.shots,"new mirror enemies do not react to shots from earlier floors");
            check(!run.advanceFloor(),"floor transitions cannot repeat without an exit request");
        } else check(run.finished&&run.canReturn()&&!run.advanceFloor(),"only last floor finishes the expedition");
    }
    check(run.evidence.size()==4,"all four observations recovered");
    const auto result=campaign.resolve(run.summary(),EndReason::Victory);
    check(ArrivalQuest::stage(campaign.data().world)==ArrivalStage::EleanorResponse,"complete account unlocks Eleanor");
    auto unchanged=campaign.data().world;
    unchanged.money=before.money;unchanged.completed=before.completed;unchanged.flags.erase("redstone.rourke_returned");
    check(CampaignStore::worldContext(before)==CampaignStore::worldContext(unchanged),"testimony never applies mine consequences");
    const auto completed=campaign.data().world.completed;
    campaign.resolve(run.summary(),EndReason::Victory);check(campaign.data().world.completed==completed,"resolution remains idempotent");
    CampaignStore reopened(path);check(reopened.data().history.back().evidence==run.evidence,"resolved journal persists");
    ArrivalQuest::advance(reopened,ArrivalStage::EleanorResponse);
    check(ArrivalQuest::stage(reopened.data().world)==ArrivalStage::AccountComplete,"Eleanor response saves without certifying an account");
    Simulation retry(1866,reopened.data().nextRunId,reopened.data().world,MissionTheme::Canyon,true,false,WitnessAccount::Rourke);
    reopened.begin(1866,retry.summary().expedition);inspect(retry);reopened.checkpoint(retry.summary());
    CampaignStore interrupted(path);check(interrupted.recover(),"an interrupted account can recover");
    check(interrupted.data().history.back().evidence==retry.evidence&&interrupted.data().world.completed==completed,"interruption retains observations without completing a run");
    Simulation cheat(7,interrupted.data().nextRunId,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke);
    interrupted.begin(7,cheat.summary().expedition);cheat.finishDebug(true);interrupted.resolve(cheat.summary(),EndReason::Victory);
    check(interrupted.data().world.completed==completed,"victory shortcut cannot invent four story observations");
}
void witnesses() {
    const auto dir=std::filesystem::path(DEATHWARD_ASSET_DIR)/"redstone";
    TownDocument scene;std::string error;check(scene.load(dir/"town.scene",error),error);
    HubWorld ground;check(ground.load(dir/"town.nav"),ground.error);
    ObjectAnimationSystem motion;motion.reset(scene);ground.setMovingSolids(motion.solids());
    TownCharacters residents;residents.reset(scene,ground);ArrivalQuest quest;quest.locate(scene,ground);
    WorldState world;
    for(const auto *flag:{"redstone.arrived","redstone.evening_conductor","redstone.slept","redstone.morning_conductor","redstone.survey_requested","redstone.search_started","redstone.survey_recovered","redstone.survey_reported"})world.flags.insert(flag);
    for(int stage:{8,11}) {
        if(stage==11)for(const auto *flag:{"redstone.rourke_heard","redstone.rourke_departed","redstone.rourke_returned"})world.flags.insert(flag);
        const auto marker=quest.marker(world,residents,ground);check(bool(marker),"witness marker exists");
        check(ground.walkable(marker->approach)&&ground.moveTo(marker->approach),"witness has a reachable approach: "+marker->action);
        for(int tick=0;tick<15000&&ground.destination();++tick)ground.step({},Tick);
        check(!ground.destination()&&distance(sub(ground.player.position,{0,.85f,0}),marker->approach)<=marker->radius,"player walks to the witness: "+marker->action);
    }
}
void saveCompatibility(const std::filesystem::path &path) {
    auto write=[&](int version,const std::string &payload) {
        uint64_t hash=14695981039346656037ULL;for(unsigned char c:payload)hash=(hash^c)*1099511628211ULL;
        std::ofstream out(path);out<<"DEATHWARD "<<version<<' '<<hash<<'\n'<<payload;
    };
    const std::string old="2 42 50 50 0 0 0 0 0 0 100\n6\n"
        "\"redstone.arrived\"\n\"redstone.evening_conductor\"\n\"redstone.slept\"\n"
        "\"redstone.morning_conductor\"\n\"redstone.survey_requested\"\n\"redstone.search_started\"\n"
        "\"Sheriff Cole\" \"alive\" 0\n\"Mary Bell\" \"alive\" 0\n"
        "\"Father Gabriel\" \"alive\" 0\n\"Silas Reed\" \"alive\" 0\n\"Dr. Whitmore\" \"alive\" 0\n1\n"
        "1 42 \"deathward-m1-53\" \"The Lost Survey\" \"\" 2 0 0 0 0 5 0 1\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0\n0\n0\n";
    write(4,old);CampaignStore legacy(path);
    check(legacy.data().pending->floorCount==1&&legacy.data().pending->account==WitnessAccount::None,"format-4 history retains its single-floor meaning");
    check(legacy.recover()&&ArrivalQuest::stage(legacy.data().world)==ArrivalStage::Report,"format-4 document recovery remains valid");
    CampaignStore migrated(path);check(migrated.data().history.back().surveyRecovered&&migrated.data().world.money==105,"format-5 round trip retains old documents and money");
    migrated.begin(42,RourkeExpeditionTitle);
    CampaignStore beforeFirstCheckpoint(path);
    check(beforeFirstCheckpoint.recover()&&beforeFirstCheckpoint.data().world.prosperity==50&&
        !beforeFirstCheckpoint.data().world.flags.contains("something_followed"),"interruption immediately after launch cannot apply mine penalties");
    migrated=CampaignStore(path);
    Simulation run(42,migrated.data().nextRunId,migrated.data().world,MissionTheme::Canyon,true,false,WitnessAccount::Rourke);
    migrated.begin(42,run.summary().expedition);inspect(run);migrated.checkpoint(run.summary());
    std::ifstream in(path);std::string header;std::getline(in,header);
    const std::string payload((std::istreambuf_iterator<char>(in)),{});
    const auto &e=run.evidence.front();
    const std::string valid=std::to_string(int(e.room))+" 1 "+std::to_string(e.floor)+" "+std::to_string(e.floorSeed)+"\n";
    const auto at=payload.find(valid);check(at!=std::string::npos,"saved provenance record is present");
    for(const auto &invalid:{"1 4 0 42\n","1 1 8 42\n","4 1 0 42\n","1 1 0 43\n"}) {
        auto bad=payload;bad.replace(at,valid.size(),invalid);write(5,bad);
        bool rejected=false;try{CampaignStore corrupt(path);}catch(const std::exception &){rejected=true;}
        check(rejected,"invalid witness, floor, site or floor seed is rejected even with a valid checksum");
    }
    write(5,payload);check(CampaignStore(path).data().pending->evidence==run.evidence,"valid provenance reloads");
}
}
int main() {
    const auto path=std::filesystem::temp_directory_path()/("deathward-expedition-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".save");
    try {plans();layouts();journey(path);witnesses();saveCompatibility(path);std::filesystem::remove(path);std::cout<<"PASS multi-floor plans, full room networks, embedded sites, build carry-over, evidence provenance, save migration/validation and witness approaches\n";}
    catch(const std::exception &e) {std::filesystem::remove(path);std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}
}
