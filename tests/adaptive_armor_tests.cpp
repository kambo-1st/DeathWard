#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b){return std::abs(a-b)<.015f;}
Simulation fixture() {
    Simulation s(1866,1,{},MissionTheme::Mine);s.enemies.clear();s.projectiles.clear();s.hazards.clear();
    s.arena=Arena{};s.arena.bounds={{-50,-1,-50},{50,10,50}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-50,-.4f,-50},{50,0,50}}};}
    s.arena.rebuildWalls();s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={30,.85f,30};return s;
}
void tick(Simulation &s,int n=2){while(n-->0)s.step({});}
EntityId spawn(Simulation &s,MonsterId id=monsterId(29,3),Vector3 at={0,.85f,0}) {
    const auto entity=s.spawnMonster(id,at);auto *e=s.findEnemy(entity);e->state=EnemyState::Stunned;e->stateTime=1000;return entity;
}
Event hit(EntityId target,float amount){Event e;e.type=EventType::Damage;e.target=target;e.damage=amount;return e;}
void send(Simulation &s,Event e){check(s.queueRoot(e),"hit accepted");s.drainEvents();}
float multiplier(float cap,float dps){const float r=cap/dps;return dps<=cap?1:r+std::max(.09f-.18f*r,0.f);}
void batching() {
    auto s=fixture();const auto id=spawn(s);const float maximum=s.findEnemy(id)->maxHp;
    send(s,hit(id,10));tick(s,1);check(near(s.findEnemy(id)->hp,maximum),"damage waits for complete30Hz source batch");
    send(s,hit(id,10));tick(s,1);const auto &a=*s.findEnemy(id)->adaptiveArmor;
    check(a.ticks==1&&a.batches==1&&a.history.size()==1&&near(a.recentDps,600),"two60Hz hits form one source-frame batch included before averaging");
    check(near(s.findEnemy(id)->hp,maximum-20*multiplier(maximum/30,600)),"whole batch uses one native multiplier");
    check(near(s.stats.damageDealt,20*multiplier(maximum/30,600)),"actual damage statistics use reduced damage once");
    tick(s,238);check(s.findEnemy(id)->adaptiveArmor->history.size()==120,"history window counts zero frames while stunned");
    tick(s);check(near(s.findEnemy(id)->adaptiveArmor->recentDps,0),"old damage expires after120source ticks");
    const float hp=s.findEnemy(id)->hp;send(s,hit(id,10));tick(s);
    check(near(s.findEnemy(id)->hp,hp-10),"below soft-cap damage remains full after quiet history");
    auto big=fixture();const auto bigId=spawn(big);tick(big,240);big.findEnemy(bigId)->hp=10000;
    send(big,hit(bigId,1000));tick(big);
    check(near(big.findEnemy(bigId)->hp,10000-1000*multiplier(maximum/30,250)),"current large hit participates before reduction, no invented separate clamp");
    std::cout<<"PASS source30Hz full-batch formula, zero frames, rolling expiry and current large hit\n";
}
void bypasses() {
    auto s=fixture();auto id=spawn(s);tick(s,240);auto e=hit(id,100);e.ignoreAdaptiveArmor=true;send(s,e);
    e=hit(id,10);e.armorPiercing=true;send(s,e);e=hit(id,50);e.bypassAdaptiveHistory=true;send(s,e);tick(s);
    const auto *body=s.findEnemy(id);check(body,"mixed batch survives");
    check(near(body->adaptiveArmor->recentDps,27.5f),"IGNORE_ARMOR counts in history; INVINCIBLE does not");
    check(near(body->hp,256-150-10*multiplier(256.f/30,27.5f)),"independent bypasses and piercing does not bypass armor");
    auto ordinary=fixture();id=spawn(ordinary);e=hit(id,10);e.explosionDamage=true;e.areaDamage=true;send(ordinary,e);tick(ordinary);
    check(ordinary.findEnemy(id)->hp>246,"explosion category alone does not invent IGNORE_ARMOR");
    auto bomb=fixture();id=spawn(bomb);bomb.player.position={1,.85f,0};
    check(bomb.placeDynamite(),"real dynamite placement accepted");
    bomb.hazards.back().delay=0;bomb.hazards.back().blastDamage=100;tick(bomb,4);
    check(near(bomb.findEnemy(id)->hp,156)&&bomb.findEnemy(id)->adaptiveArmor->recentDps>0,"actual player dynamite bypasses scaling but enters history");
    auto enemyBomb=fixture();id=spawn(enemyBomb);const auto source=spawn(enemyBomb,monsterId(14),{10,.85f,0});
    check(enemyBomb.throwEnemyBomb("normal",source,{0,.18f,0},{0,.18f,0},true)!=0,"actual enemy bomb placement accepted");
    enemyBomb.enemyBombs.back().charge.delay=0;tick(enemyBomb,4);
    check(near(enemyBomb.findEnemy(id)->hp,156),"actual enemy Bomb body bypasses armor");
    auto marker=fixture();id=spawn(marker);const auto fly=spawn(marker,monsterId(25),{1,.85f,0});
    send(marker,hit(fly,10000));tick(marker);
    check(marker.stats.explosions==1,"actual Boom Fly death produces an NPC explosion marker");
    check(marker.findEnemy(id)->hp>156,"NPC explosion marker does not inherit physical Bomb bypass");
    std::cout<<"PASS separate history/scaling bypasses, piercing distinction and real dynamite\n";
}
void lifecycle() {
    auto s=fixture();auto id=spawn(s);s.limits.queuedEvents=1;
    send(s,hit(id,10));send(s,hit(id,20));check(s.queuedEvents()==1&&s.findEnemy(id)->adaptiveArmor->pending.size()==1,"full buffer retains accepted second hit in ordinary queue");
    tick(s,4);check(s.queuedEvents()==0&&s.findEnemy(id)->adaptiveArmor->batches==2,"capacity frees without dropping or duplicating hits");
    auto room=fixture();id=spawn(room);send(room,hit(id,10));tick(room,1);
    const auto original=room.findEnemy(id)->adaptiveArmor->pending.front().context;const auto accepted=room.chains.at(original.chainId).accepted;
    room.enterRoom(1);spawn(room,monsterId(12),{20,.85f,20});tick(room,120);room.enterRoom(0);
    auto *body=room.findEnemy(id);check(body&&near(body->hp,256)&&body->adaptiveArmor->ticks==0,"inactive room freezes history and pending hit");
    check(room.chains.at(original.chainId).accepted==accepted&&room.chains.at(original.chainId).active==1,"damage chain budget and ownership survive suspension");
    tick(room,1);check(room.findEnemy(id)->hp<256&&room.findEnemy(id)->adaptiveArmor->batches==1,"resume applies original hit once");
    auto dead=fixture();id=spawn(dead);send(dead,hit(id,10));auto execute=hit(id,10000);execute.execution=true;execute.debugExecution=true;send(dead,execute);tick(dead);
    check(!dead.findEnemy(id)&&dead.stats.kills==1&&dead.chains.empty(),"execution bypasses delay, cancels pending hits and releases chain pins");
    auto ordinary=fixture();ordinary.debugScenario=false;id=spawn(ordinary);send(ordinary,hit(id,10000));
    check(ordinary.findEnemy(id)->alive&&!ordinary.roomClear,"queued lethal hit retains room threat");tick(ordinary,4);
    check(!ordinary.findEnemy(id)&&ordinary.stats.kills==1&&ordinary.roomClear,"reduced lethal batch resolves one kill and room completion");
    std::cout<<"PASS bounded admission, chain retention, suspension, execution and ordinary death\n";
}
void derivedEffects() {
    auto s=fixture();s.grant(ItemId::Powder);
    const auto victim=spawn(s),neighbor=spawn(s,monsterId(29,3),{2,.85f,0});
    s.findEnemy(victim)->hp=1;
    auto e=hit(victim,10);e.ignoreAdaptiveArmor=true;e.context.sourceEntity=4000;
    e.context.damageSource=DamageSource::Player;send(s,e);tick(s);
    check(s.stats.kills==1&&s.stats.explosions==1,"one real damage resolution dispatches one Powder death hook");
    const auto &pending=s.findEnemy(neighbor)->adaptiveArmor->pending;
    check(pending.size()==1&&!pending[0].ignoreAdaptiveArmor&&!pending[0].bypassAdaptiveHistory&&
          !pending[0].adaptiveResolved&&pending[0].context.sourceEntity==4000,
          "derived item explosion resets armor bypass and replay marker, retaining removed-source attribution");
    const auto chain=pending[0].context.chainId;tick(s);
    check(s.findEnemy(neighbor)->hp>221&&s.findEnemy(neighbor)->hp<256&&s.chains.find(chain)==s.chains.end(),
          "secondary explosion is reduced once and its complete chain is released");
    std::cout<<"PASS derived item damage, removed-source attribution and chain cleanup\n";
}
void profiles() {
    auto s=fixture();
    const std::array<MonsterId,7> ids{monsterId(14,2),monsterId(22,3),monsterId(25,6),monsterId(29,3),monsterId(31,1),monsterId(61,7),monsterId(855)};
    const std::array<float,7> hp{240,320,64,256,192,44.8f,128},strength{30,30,10,30,30,10,2.5f};
    for(size_t i=0;i<ids.size();++i) {const auto id=spawn(s,ids[i],{float(i)*4,.85f,0});const auto *e=s.findEnemy(id);
        check(e&&e->adaptiveArmor&&near(e->maxHp,hp[i])&&near(s.content->adaptiveArmor(ids[i])->strength,strength[i]),"all existing ordinary shield profiles use source health and strength");}
    check(!s.content->adaptiveArmor(monsterId(29))&&!s.content->adaptiveArmor(monsterId(14)),"ordinary unarmored variants remain unarmored");
    const auto dir=std::filesystem::temp_directory_path()/("dw-adaptive-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(dir);for(const auto &f:std::filesystem::directory_iterator(s.content->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ifstream f(dir/"adaptive_armor.mechanics");const std::string original((std::istreambuf_iterator<char>(f)),{});
    for(const auto &[from,to]:std::array<std::pair<std::string,std::string>,4>{{{"30 120 .09 .18","0 120 .09 .18"},{"30 120 .09 .18","30 0 .09 .18"},{"30 120 .09 .18","30 120 .09 .01"},{"adaptive_armor 14.2.0","adaptive_armor 999.0.0"}}}) {
        auto text=original;text.replace(text.find(from),from.size(),to);std::ofstream(dir/"adaptive_armor.mechanics")<<text;
        bool rejected=false;try{MechanicsLibrary::load(dir);}catch(...){rejected=true;}check(rejected,"invalid armor snapshot rejected");
    }
    auto text=original;auto at=text.find("30 120 .09 .18");text.replace(at,2,"60");std::ofstream(dir/"adaptive_armor.mechanics")<<text;
    auto fresh=MechanicsLibrary::load(dir);check(near(fresh->adaptiveArmor(monsterId(14,2))->strength,60)&&near(s.content->adaptiveArmor(monsterId(14,2))->strength,30),"reload preserves old immutable snapshot");
    std::filesystem::remove_all(dir);std::cout<<"PASS seven source profiles and validated external reload\n";
}
}
int main(){try{batching();bypasses();lifecycle();derivedEffects();profiles();std::cout<<"PASS adaptive armor\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
