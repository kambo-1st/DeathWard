#include "combat/Simulation.hpp"
#include <iostream>
#include <map>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
Simulation fixture(uint64_t seed=1866) {
    Simulation s(seed,1,{});s.enemies.clear();s.arena=Arena{};
    s.arena.bounds={{-25,-1,-25},{25,8,25}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.kind=RoomKind::Combat;}
    s.arena.boundaryWalls={{{-26,-1,-26},{-25,8,26}},{{25,-1,-26},{26,8,26}},
        {{-26,-1,-26},{26,8,-25}},{{-26,-1,25},{26,8,26}}};s.arena.rebuildWalls();
    s.rooms.assign(s.arena.rooms.size(),{});s.room=0;s.player.position={0,.85f,18};
    s.godMode=true;s.debugScenario=true;s.roomClear=false;return s;
}
std::vector<EntityId> spawn(Simulation &s,int count,EntityId owner=0) {
    std::vector<EntityId> ids;
    for(int i=0;i<count;++i) {
        auto id=s.spawnMonster(monsterId(222),{float(i%5)-2,.85f,float(i/5)-2});
        s.findEnemy(id)->summoner=owner;ids.push_back(id);
    }
    return ids;
}
void tick(Simulation &s,int n){for(int i=0;i<n;++i)s.step({});}
void kill(Simulation &s,EntityId id){Event e;e.type=EventType::Damage;e.target=id;e.damage=1000;s.queueRoot(e);s.drainEvents();}
void formationAndDeaths() {
    auto s=fixture();const auto ids=spawn(s,10);tick(s,150);
    const auto &groups=s.rooms[0].formations;check(groups.size()==1,"ten flies form one group");
    const auto groupId=groups.front().id;const auto center=groups.front().center;
    std::map<EntityId,float> slots;
    for(const auto &slot:groups.front().slots) {
        slots[slot.member]=slot.angle;
        check(std::abs(planarDistance(s.findEnemy(slot.member)->position,center)-2.4f)<.025f,"assembled members lie on shared circle");
    }
    check(center.z>1,"group center pursues player instead of orbiting spawning point");
    auto before=s.findEnemy(ids[4])->position;const auto angle=groups.front().angle;
    tick(s,30);check(planarDistance(before,s.findEnemy(ids[4])->position)>1,"members rotate rapidly while group moves");
    check(groups.front().angle!=angle&&s.stats.projectiles==0,"contact formation does not fire projectiles");
    auto *stunned=s.findEnemy(ids[4]);stunned->state=EnemyState::Stunned;stunned->stateTime=1;
    const auto frozen=stunned->position;tick(s,30);
    check(distance(stunned->position,frozen)<.00001f,"stunned member stays still while retaining its slot");
    tick(s,150);check(std::abs(planarDistance(stunned->position,groups.front().center)-2.4f)<.025f,"recovered member rejoins its circle");
    kill(s,ids.front());kill(s,ids[3]);tick(s,1);
    check(s.roomThreats()==8&&groups.front().id==groupId,"founder death preserves remaining threats and stable group identity");
    for(const auto &slot:groups.front().slots)if(slot.member)check(slot.angle==slots[slot.member],"member deaths leave angular gaps without reindexing survivors");
    const auto addition=s.spawnMonster(monsterId(222),{0,.85f,0});tick(s,1);
    check(s.findEnemy(addition)->formation==groupId&&groups.front().slots.size()==10,"new arrival fills an empty slot without expanding capacity");
    const auto retained=groups.front();s.enterRoom(1);tick(s,60);
    check(s.rooms[0].formations.front().angle==retained.angle,"inactive room group state is frozen");
    s.enterRoom(0);check(s.rooms[0].formations.front().id==groupId,"room re-entry retains group");
    tick(s,1);check(s.rooms[0].formations.front().angle!=retained.angle,"return resumes group clock");
    s.clearRoomDebug();check(s.rooms[0].formations.empty()&&s.roomClear,"debug clear removes all formation state");
    std::cout<<"FORMATION slots=10 surviving_after_two_deaths=8 founder_independent=1 reentry=1\n";
}
void capacityAndOwnership() {
    auto s=fixture();const auto ids=spawn(s,23);tick(s,1);
    check(s.rooms[0].formations.size()==3,"23 members partition into ten, ten and three");
    for(const auto &g:s.rooms[0].formations)check(g.slots.size()<=10,"group capacity never exceeded");
    auto copy=fixture();spawn(copy,23);tick(copy,1);
    for(size_t i=0;i<ids.size();++i)check(s.enemies[i].formation==copy.enemies[i].formation&&distance(s.enemies[i].position,copy.enemies[i].position)<.0001f,"same spawn order produces deterministic grouping and motion");
    auto owner=fixture();const auto parent=owner.spawnMonster(monsterId(14),{-12,.85f,0});
    const auto children=spawn(owner,5,parent);tick(owner,150);
    const auto center=owner.rooms[0].formations.front().center;
    check(center.z>1&&center.x>-3,"summoned group pursues player independently of summoner position");
    kill(owner,parent);tick(owner,30);
    for(auto id:children)check(owner.findEnemy(id)&&owner.findEnemy(id)->summoner==parent,"owner death leaves Ring Flies alive without clearing their provenance");
    auto &changed=*owner.findEnemy(children[0]);changed.friendly=true;tick(owner,1);
    check(owner.rooms[0].formations.size()==2,"team change separates friendly and hostile group membership");
    changed.monster=monsterId(18);tick(owner,1);check(changed.formation==0,"identity change releases old formation membership");
}
void terrainAndContact() {
    auto s=fixture();s.arena.obstacles.push_back({{-3,0,1},{3,2,7}});s.arena.rebuildWalls();spawn(s,10);
    float peak=0;
    for(int i=0;i<500;++i) {
        s.step({});for(const auto &e:s.enemies) {
            check(!s.arena.flightBlocked(e.position,e.radius,s.room),"formation members stay within flight walls");
            check(!sphereBox(e.position,e.radius,s.arena.obstacles.front()),"formation clears actual cover hitboxes");
            peak=std::max(peak,e.position.y);
        }
    }
    check(peak>=2.85f-.001f,"formation passes above cover");
    s.player.position={0,.85f,100};tick(s,500);
    for(const auto &e:s.enemies)check(!s.arena.flightBlocked(e.position,e.radius,s.room),"formation cannot pursue beyond room boundary");
    auto contact=fixture();spawn(contact,4);tick(contact,160);contact.godMode=false;contact.debugScenario=false;
    contact.player.position=contact.enemies.front().position;contact.step({});
    check(contact.player.hp<StartingHealth,"ring members deal contact damage");
    for(auto &e:contact.enemies)kill(contact,e.id);contact.step({});
    check(contact.roomClear&&contact.roomThreats()==0,"last member death completes room");
    contact.step({});check(contact.rooms[0].formations.empty(),"empty group state is collected");
    auto narrow=fixture();for(auto &r:narrow.arena.rooms)r.bounds={{-1.5f,-1,-10},{1.5f,8,10}};
    narrow.player.position={0,.85f,8};
    for(int i=0;i<3;++i)narrow.spawnMonster(monsterId(222),{float(i-1)*.6f,.85f,-3});
    tick(narrow,240);check(narrow.rooms[0].formations.empty(),"a full ring is not forced into an impossibly narrow room");
    for(const auto &e:narrow.enemies)check(!narrow.arena.flightBlocked(e.position,e.radius,0)&&e.position.z>2,"constrained fallback pursues without crossing solid room edges");
    std::cout<<"FORMATION_TERRAIN cover_peak="<<peak<<" contact_damage="<<StartingHealth-contact.player.hp<<'\n';
}
void budgetsAndBalance() {
    int encounters=0;
    // Adding a weighted specialist can change any one seed's selection. Verify
    // reachability across seeds, and whole-group accounting on every selection.
    for(uint64_t seed=0;seed<32;++seed) {
        auto s=fixture(seed);s.arena.profile.band=0;s.arena.profile.patterns={1,0,0,0};s.arena.profile.maxSpecialists=1;
        s.arena.profile.maxThreat=10;s.arena.profile.areaPerThreat=70;
        for(int room=0;room<s.arena.roomCount();++room) {
            s.arena.rooms[size_t(room)].floors={{{-20,-.4f,-20},{20,0,20}}};
            const auto p=s.floorEncounter(room);const auto count=std::count(p.monsters.begin(),p.monsters.end(),monsterId(222));
            check(count==0||count==4,"pool selects the complete four-member formation");
            if(count) {++encounters;check(p.spent<=p.budget&&p.specialists==4&&p.specialistGroups==1,"group budget and specialist-group count are distinct from actor count");}
        }
    }
    check(encounters>0,"configured group is reachable from ordinary seeded selection");
    std::cout<<"FORMATION_POOL seeds=32 encounters="<<encounters<<'\n';
    auto fight=fixture();spawn(fight,4);fight.player.position={0,.85f,10};fight.godMode=false;fight.debugScenario=false;
    for(int i=0;i<1800&&!fight.roomClear&&!fight.dead;++i) {
        const Enemy *target=nullptr;float nearest=1000;
        for(const auto &e:fight.enemies)if(e.alive&&distance(e.position,fight.player.position)<nearest){nearest=distance(e.position,fight.player.position);target=&e;}
        Input input;if(target){input.fire=true;input.aim=target->position;}fight.step(input);
    }
    check(fight.roomClear&&!fight.dead,"starting revolver can clear a four-fly formation without powers or bombs");
    std::cout<<"FORMATION_STARTING_KIT seconds="<<fight.stats.duration<<" health="<<fight.player.hp<<" kills="<<fight.stats.kills<<'\n';
}
}
int main(){try{formationAndDeaths();capacityAndOwnership();terrainAndContact();budgetsAndBalance();std::cout<<"PASS translating formations, stable slots, ownership, terrain, budgets and basic starting-kit encounter\n";}
catch(const std::exception &e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
