#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const std::string &msg){if(!ok)throw std::runtime_error(msg);}
Simulation fixture() {
    Simulation run(1,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic);
    run.arena=Arena{};run.arena.bounds={{-30,-1,-30},{30,8,30}};
    for(auto &r:run.arena.rooms)r.bounds=run.arena.bounds;
    for(auto &r:run.rooms)r.residents.clear();
    run.enemies.clear();run.moneyPickups.clear();run.debugScenario=true;run.roomClear=false;
    run.player.position={-15,.85f,-15};
    return run;
}
Breakable prop(int id,BreakableKind kind,Box bounds,int health=1) {
    Breakable p;p.id=id;p.lootSeed=12345+id;p.kind=kind;p.bounds=bounds;p.health=health;
    p.rewardPosition=mul(add(bounds.min,bounds.max),.5f);p.rewardPosition.y=.85f;return p;
}
void blast(Simulation &run,Vector3 at,Demolition permission=Demolition::SpentDynamite,float radius=4.5f) {
    Event e;e.type=EventType::Explosion;e.position=at;e.radius=radius;e.damage=100;
    e.demolition=permission;e.playerDamage=25;run.queueRoot(e);run.drainEvents();
}
void tick(Simulation &run,int count) {for(int i=0;i<count;++i)run.step({});}
void snapshot() {
    for(bool reverse:{false,true}) {
        auto run=fixture();
        run.arena.breakables={prop(1,BreakableKind::CrackedRock,{{-.3f,0,-1.5f},{.3f,2,1.5f}}),
                              prop(2,BreakableKind::OreSeam,{{1.5f,0,-.5f},{2.5f,1.5f,.5f}})};
        if(reverse)std::reverse(run.arena.breakables.begin(),run.arena.breakables.end());
        run.arena.rebuildWalls();
        run.player.position={1,.85f,0};
        auto id=run.spawn(EnemyKind::Gunman,{1,.85f,.5f});
        run.findEnemy(id)->hp=run.findEnemy(id)->maxHp=500;
        blast(run,{-2,.85f,0});
        check(run.findEnemy(id)->hp==500&&run.player.hp==100,"cover protects enemy/player for the entire first blast");
        for(const auto &p:run.arena.breakables)
            check(p.destroyed==(p.id==1),"pre-blast cover protects the second prop independent of iteration order");
        check(run.arena.sight({-2,.85f,0},{1,.85f,0})&&!run.arena.blocked({0,.85f,0},.48f),"destruction removes sight and movement collision together");
        blast(run,{-2,.85f,0});
        check(run.findEnemy(id)->hp==400&&run.player.hp==75,"later blast sees changed geometry and damages both recipients");
        check(std::all_of(run.arena.breakables.begin(),run.arena.breakables.end(),[](const auto &p){return p.destroyed&&p.paid;}),"props transition and pay once");
        const size_t loot=run.moneyPickups.size();blast(run,{-2,.85f,0});
        check(run.moneyPickups.size()==loot,"repeated blast cannot duplicate rewards");
    }
}
void permissions() {
    auto run=fixture();
    run.arena.breakables={prop(1,BreakableKind::CacheGate,{{0,0,-1},{.5f,2,1}},2)};
    run.arena.rebuildWalls();
    blast(run,{-2,.85f,0},Demolition::Soft);
    check(run.arena.breakables[0].health==2,"free blast cannot damage a hard resource gate");
    blast(run,{-2,.85f,0});
    check(run.arena.breakables[0].health==1&&!run.arena.breakables[0].destroyed&&run.moneyPickups.empty(),"reinforced cache retains collision and no loot after one charge");
    run.enterRoom(1);run.enterRoom(0);
    check(run.arena.breakables[0].health==1,"partial damage survives room visits");
    blast(run,{-2,.85f,0});
    check(run.arena.breakables[0].destroyed&&run.moneyPickups.size()==1&&run.arena.keys.size()==1,"second charge opens cache and pays key/coins once");
    run.enterRoom(1);run.enterRoom(0);blast(run,{-2,.85f,0});
    check(run.arena.keys.size()==1&&run.moneyPickups.size()==1,"opened cache and payout persist across visits");
    auto powder=fixture();powder.grant(ItemId::Powder);
    powder.arena.breakables={prop(1,BreakableKind::CacheGate,{{1,0,-1},{1.5f,2,1}},2)};
    powder.arena.rebuildWalls();
    Event kill;kill.type=EventType::EnemyKilled;kill.position={0,.85f,0};kill.demolition=Demolition::SpentDynamite;kill.playerDamage=25;
    powder.queueRoot(kill);powder.drainEvents();
    check(powder.arena.breakables[0].health==2,"Powder descendants cannot inherit spent dynamite permission");
}
void barrels() {
    auto run=fixture();
    run.arena.breakables={prop(1,BreakableKind::PowderBarrel,{{-.6f,0,-.6f},{.6f,1.35f,.6f}},30),
                          prop(2,BreakableKind::CacheGate,{{2,0,-1},{2.5f,2,1}},2)};
    run.arena.rebuildWalls();
    run.player.position={-8,.85f,0};
    auto shoot=[&]{Event e;e.position={-2,.85f,0};e.direction={1,0,0};e.damage=24;run.queueRoot(e);run.drainEvents();tick(run,5);};
    shoot();check(run.arena.breakables[0].health==6&&run.arena.breakables[0].fuse<0,"one normal bullet damages barrel without immediate explosion");
    shoot();check(run.arena.breakables[0].fuse>0&&run.stats.explosions==0,"second hit starts a visible fuse");
    const float fuse=run.arena.breakables[0].fuse;
    run.shopOpen=true;tick(run,60);run.shopOpen=false;
    check(run.arena.breakables[0].fuse==fuse,"modal freezes barrel fuse");
    run.enterRoom(1);run.player.position={100,.85f,100};tick(run,60);
    check(run.arena.breakables[0].fuse==fuse,"inactive rooms preserve remaining fuse");
    run.enterRoom(0);run.player.position={-8,.85f,0};tick(run,45);
    check(run.stats.explosions==1&&run.arena.breakables[0].destroyed,"return resumes fuse and detonates once");
    check(run.arena.breakables[1].health==2,"gun-ignited barrel cannot open the cache");
    tick(run,60);check(run.stats.explosions==1&&run.chains.empty(),"finite barrel work leaves no chain leak");
}
void seedLoot() {
    std::vector<std::pair<uint64_t,int>> expected;
    for(bool reverse:{false,true}) {
        auto run=fixture();
        run.arena.breakables={prop(1,BreakableKind::OreSeam,{{-6,0,-1},{-4,1.35f,1}}),
                              prop(2,BreakableKind::OreSeam,{{4,0,-1},{6,1.35f,1}})};
        run.arena.rebuildWalls();const auto combat=run.combatRng.state,reward=run.rewardRng.state;
        std::vector<std::pair<uint64_t,int>> values;
        for(int i:reverse?std::vector<int>{1,0}:std::vector<int>{0,1}) {
            const auto &p=run.arena.breakables[size_t(i)];
            blast(run,add(p.rewardPosition,{0,0,2.5f}));
            values.push_back({p.id,run.moneyPickups.back().value});
            check(!run.arena.blocked(run.moneyPickups.back().position,.48f),"freed footprint provides walkable loot ground");
        }
        std::sort(values.begin(),values.end());
        if(reverse)check(expected==values,"destruction order cannot reroll deterministic object rewards");else expected=values;
        check(combat==run.combatRng.state&&reward==run.rewardRng.state,"loot consumes neither combat nor item-reward RNG");
    }
}
void protectedInteriorAndChains() {
    for(int variant=0;variant<3;++variant) {
        auto run=fixture();
        run.arena.supplyCache={0,{{-2,0,-2},{2,2,2}},{0,.85f,-3},{0,.85f,0}};
        const Vector3 origin{5,.85f,0};
        const auto id=variant==0?run.spawn(EnemyKind::Wraith,origin):
            run.spawnMonster(monsterId(variant==1?38:56),origin);
        auto &e=*run.findEnemy(id);e.target={0,.85f,0};e.stateTime=0;
        e.state=variant==2?EnemyState::Buried:EnemyState::Teleporting;
        tick(run,1);
        check(distance(run.findEnemy(id)->position,origin)<.01f,"teleporting and burrowing cannot enter the optional enclosure");
    }
    auto run=fixture();
    for(int i=0;i<12;++i)run.arena.breakables.push_back(
        prop(i+1,BreakableKind::PowderBarrel,{{float(i)*2-.5f,0,-.5f},{float(i)*2+.5f,1.35f,.5f}},30));
    run.arena.rebuildWalls();
    blast(run,{-1,.7f,0},Demolition::Soft,1);
    tick(run,700);
    check(std::all_of(run.arena.breakables.begin(),run.arena.breakables.end(),[](const auto &p){return p.destroyed;}),
          "delayed secondary blasts can propagate through newly freed barrel geometry");
    check(run.stats.explosions==13&&run.chains.empty()&&run.queuedEvents()==0,"finite secondary sources finish exactly once without chain leaks");
}
void layouts() {
    int total=0,clustered=0;
    for(uint64_t seed=0;seed<64;++seed)for(auto theme:{MissionTheme::Mine,MissionTheme::Canyon})for(bool final:{false,true}) {
        const int floor=final?ExpeditionPlan(seed,false,WitnessAccount::Rourke).floorCount-1:0;
        Simulation run(seed,1,{},theme,true,false,WitnessAccount::Rourke,floor);
        auto &a=run.arena;
        const std::string tag=" seed "+std::to_string(seed)+" theme "+std::to_string(int(theme))+" floor "+std::to_string(floor);
        check(a.supplyCache.room>=0,"cache must have a safe placement"+tag);
        check(a.breakables.size()==8,"all five destructible props and three cache sides fit"+tag);
        if(std::all_of(a.breakables.begin(),a.breakables.end(),[&](const auto &p){return p.room==a.supplyCache.room;}))++clustered;
        for(const auto &p:a.breakables)check(p.room>0&&p.room<run.finalRoom()&&a.rooms[size_t(p.room)].story==StoryRoom::None,"story, entrance and boss arenas are protected");
        for(auto &p:a.passages){p.locked=false;p.sealed={false,false};}a.rebuildWalls();
        for(const auto &r:a.rooms) {
            check(!a.path(r.center,r.objective,.48f).empty(),"objective remains reachable without dynamite"+tag);
            for(int link:r.passages)check(!a.path(r.center,a.doorApproach(link,a.passages[size_t(link)].rooms[0]==int(&r-a.rooms.data())?0:1),.48f).empty(),"mandatory door approach reachable"+tag);
        }
        for(const auto &key:a.keys)check(!a.path(a.rooms[size_t(key.room)].center,key.position,.48f).empty(),"ordinary key remains free"+tag);
        for(int i=0;i<a.roomCount();++i)for(const auto &e:run.roomEnemies(i))
            check(!sphereBox(e.position,e.radius,a.supplyCache.bounds),"resident cannot be trapped in cache"+tag);
        for(const auto &coin:run.moneyPickups)check(!sphereBox(coin.position,.1f,a.supplyCache.bounds),"ordinary money cannot spawn inside sealed cache");
        check(a.path(a.supplyCache.approach,a.supplyCache.reward,.48f).empty(),"sealed cache cannot be bypassed"+tag);
        run.player.position=a.supplyCache.approach;
        const auto gate=std::find_if(a.breakables.begin(),a.breakables.end(),[](const auto &p){return p.kind==BreakableKind::CacheGate;});
        blast(run,a.supplyCache.approach);check(gate->health==1,"cache approachable from outside for first blast"+tag);
        blast(run,a.supplyCache.approach);check(gate->destroyed,"cache opens with exactly two charges"+tag);
        check(!a.path(a.supplyCache.approach,a.supplyCache.reward,.48f).empty(),"cache loot reachable after opening"+tag);
        ++total;
    }
    Simulation classic(1,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic);
    Simulation tutorial(1,1,{},MissionTheme::Canyon,true,true);
    check(classic.arena.breakables.empty()&&tutorial.arena.breakables.empty(),"Classic comparison and five-room tutorial unchanged");
    std::cout<<"Placement: "<<total<<" floors, "<<clustered<<" complete single-room clusters\n";
}
}
int main(){try{snapshot();permissions();barrels();seedLoot();protectedInteriorAndChains();layouts();std::cout<<"PASS destruction, cover snapshot, permissions, fuses, seeded loot and optional-cache reachability\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
