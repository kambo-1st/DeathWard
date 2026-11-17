#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include "world/PedestalGeometry.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool value,const char *why){if(!value)throw std::runtime_error(why);}
bool near(float a,float b){return std::abs(a-b)<.0002f;}
auto read(const char *name) {
    std::ifstream f(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/monstro/"+name);
    check(bool(f),"native trace exists");std::string line;std::getline(f,line);
    std::vector<std::vector<std::string>> rows;
    while(std::getline(f,line)){std::istringstream in(line);std::string field;std::vector<std::string> row;while(std::getline(in,field,','))row.push_back(field);rows.push_back(std::move(row));}
    return rows;
}
void kernels() {
    const auto decisions=read("native-decisions.csv"),forces=read("native-forces.csv"),payloads=read("native-projectile-payload.csv");
    for(const auto &r:decisions)check(sourceMonstroAction(uint32_t(std::stoul(r[1])),std::stoi(r[0]))==std::stoi(r[2]),"native unsigned action/subtype branch");
    for(const auto &r:forces) {
        const bool large=r[0]=="large_jump";
        const auto value=sourceMonstroForce({std::stof(r[3]),0,std::stof(r[4])},{std::stof(r[1]),0,std::stof(r[2])},large);
        check(near(value.x,std::stof(r[5]))&&near(value.z,std::stof(r[6]))&&near(sourceMonstroFriction(true,large),std::stof(r[7])),"native ordinary jump force/friction");
    }
    for(const auto &r:payloads) {
        const auto shot=sourceBossShot({},uint32_t(std::stoul(r[1])),uint32_t(std::stoul(r[2])),uint32_t(std::stoul(r[3])),std::stof(r[0]));
        check(near(shot.fallingSpeed,std::stof(r[4]))&&near(shot.fallingAcceleration,std::stof(r[5]))&&near(shot.size,std::stof(r[6])),"native boss-projectile payload");
    }
    check(decisions.size()==48&&forces.size()==32&&payloads.size()==24,"entire native matrices compared");
}

Simulation generated(float scale=1.1f,int lo=7,int hi=9) {
 return Simulation(69,17,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,
    defaultMechanics(),scale,lo,hi,.26f,true,1,true,true,true,true,true,true,1,1,MonstroTuning{});
}
void hit(Simulation &s,EntityId id,float amount,bool area=false) {
 Event e;e.type=EventType::Damage;e.target=id;e.damage=amount;e.areaDamage=area;s.queueRoot(e);s.drainEvents();
}
Enemy &boss(Simulation &s) {for(auto &e:s.enemies)if(e.alive&&e.monstro)return e;throw std::runtime_error("no live Monstro");}
void ticks(Simulation &s,int n) {for(int i=0;i<n;++i)s.step({});}
void fightAndLoop() {
 for(auto dim:std::array<std::array<float,3>,3>{{{.75f,5,5},{1.1f,7,9},{1.5f,10,10}}}) {
  auto s=generated(dim[0],int(dim[1]),int(dim[2]));s.jumpDebug(s.finalRoom());
  check(s.livingEnemies()==1&&s.hasSourceBoss(s.room),"one selected ordinary Monstro in actual generated boss room");
  auto id=boss(s).id;check(boss(s).hp==800,"source250 uses shared3.2 damage unit");
  check(!s.canUseFloorExit()&&!s.rewardAvailable(s.room)&&!s.arena.bossRewardPedestal,"fight seals reward and exit");
  check(near(s.player.attributes.speed,1)&&s.player.maxHp==6,"accepted movement and starting red health retained");
  hit(s,id,200);auto tuning=s.monstroTuning;tuning.health=.5f;s.applyMonstroTuning(tuning);
  check(boss(s).maxHp==400&&boss(s).hp==300,"live boss HP preserves injury fraction");
  s.applyCombatBalance(3.5f,.75f);check(boss(s).maxHp==400,"regular health override excludes boss");
  s.grant(BookOfShadowsKey);s.activeItem->charge=1;s.grant(CancerKey);s.grant({"isaac",ItemKind::Collectible,8});
  const auto beforeMoney=s.money();const auto beforeBombs=s.dynamite;
  s.player.hp=3;s.player.position=add(s.arena.rooms.back().center,{3,.85f,0});
  hit(s,id,400);ticks(s,2);
  check(s.roomClear&&s.canUseFloorExit()&&s.rewardAvailable(s.room),"actual damage kill unlocks room, collectible and exit");
  check(s.money()==beforeMoney&&s.dynamite==beforeBombs,"no legacy boss currency or bomb payout");
  check(s.arena.bossRewardPedestal&&planarDistance(s.rewardPosition(s.room),s.arena.rooms.back().center)<.001f,"centered admitted pedestal");
  check(s.arena.blocked(s.rewardPosition(s.room),.48f),"pedestal collision exists");
  s.player.position=pedestalGeometry::approach(s.rewardPosition(s.room),{1,0,0},.85f);
  check(s.collectTreasureUpgrade(),"touch collection grants Breakfast");
  check(s.player.maxHp==8&&s.player.hp==7,"installed XML maxhearts2 then hearts4");
  check(!s.collectTreasureUpgrade()&&s.itemStacks({"isaac",ItemKind::Collectible,25})==1,"single once-only reward");
  check(s.activeItem->item==BookOfShadowsKey&&s.activeItem->charge==2&&s.heldTrinket==CancerKey,"passive reward preserves active slot/clear charge/trinket");
  const int old=s.room;s.enterRoom(0);s.enterRoom(old);check(!s.rewardAvailable(old),"revisit cannot recreate reward");
  s.player.position=s.arena.exit;s.interact();check(s.floorExitRequested,"ordinary exit interaction requests descent");
  check(s.advanceFloor()&&s.floor==1&&s.player.maxHp==8&&s.player.hp==7,"descent retains Breakfast health");
  check(s.activeItem&&s.heldTrinket==CancerKey&&s.itemStacks({"isaac",ItemKind::Collectible,8})==1,"descent carries all owned categories");
  check(s.monstroTuning.health==.5f&&!s.hasSourceBoss(s.finalRoom()),"tuning carries but boss replacement is opening-floor-only");
 }
}
void attackWindows() {
 auto s=generated();s.jumpDebug(s.finalRoom());s.godMode=true;auto &e=boss(s);const auto id=e.id;
 e.monstro->initialized=true;e.monstro->action=MonstroAction::Spit;e.monstro->frame=20;e.monstro->clock=0;
 const auto count=s.stats.projectiles;ticks(s,2);check(s.stats.projectiles-count==13,"Shoot21 thirteen aimed shots");
 e.monstro->action=MonstroAction::JumpDown;e.monstro->frame=33;e.monstro->fired=false;e.monstro->clock=0;
 const auto count2=s.stats.projectiles;ticks(s,2);check(s.stats.projectiles-count2==18,"Shoot34 eighteen independent radial shots");
 e.monstro->action=MonstroAction::Walk;e.monstro->frame=5;e.monstro->clock=0;ticks(s,2);
 check(e.monstro->intangible,"Jump6 disables body contact");
 const float beforeTear=e.hp;
 Event tear;tear.position=tear.origin=sub(e.position,{2,0,0});tear.direction={1,0,0};tear.speed=30;tear.damage=10;
 s.queueRoot(tear);s.drainEvents();ticks(s,10);check(e.hp==beforeTear,"actual projectile passes through airborne body");
 const float hp=e.hp;hit(s,id,10,true);check(e.hp==hp,"airborne blast excludes body");hit(s,id,10);check(e.hp==hp-10,"direct damage is distinct from collision");
 ticks(s,22);check(!e.monstro->intangible,"Land22 restores body collision");
 e.monstro->action=MonstroAction::Spit;e.monstro->frame=20;e.monstro->fired=false;e.monstro->clock=0;s.limits.queuedEvents=0;
 ticks(s,2);check(e.monstro->pendingShots.size()==13,"capacity retains selected volley");const auto saved=e.monstro->shotSpeed;
 auto tuning=s.monstroTuning;tuning.shotSpeed=2;s.applyMonstroTuning(tuning);check(e.monstro->shotSpeed==saved,"pending volley keeps birth speed");
 s.limits.queuedEvents=256;const auto shots=s.stats.projectiles;ticks(s,1);check(s.stats.projectiles-shots==13,"capacity recovery emits once");
}
void persistence() {
 const auto fp=defaultMechanics()->fingerprint();BalancePreset p{1,fp};p.monstro={false,.5f,.75f,1.25f};p.defaultZoomPercent=165;
 const auto path=std::filesystem::temp_directory_path()/"deathward-d13a-preset-test.json";p.save(path);
 auto loaded=BalancePreset::load(path,fp);check(loaded.monstro==p.monstro&&loaded.defaultZoomPercent==165,"schema43 exact round trip");std::filesystem::remove(path);
 auto old=BalancePreset::load(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json",fp);
 check(old.defaultZoomPercent==165&&old.monstro.enabled&&old.playerSpeed==1,"preserved schema5 migrates without balance loss");
}
}
int main(){try{kernels();attackWindows();fightAndLoop();persistence();std::cout<<"PASS D13a native bounded kernels, attack windows, three generated size loops, injury-preserving tuning, reward/descent and presets\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
