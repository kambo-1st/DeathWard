#include "combat/Simulation.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace dw;
namespace {
void check(bool ok,const char *message) {if(!ok)throw std::runtime_error(message);}
bool near(float a,float b) {return std::abs(a-b)<.0001f;}
void sourceMatrices() {
    const auto source=std::filesystem::path(__FILE__).parent_path().parent_path()/
        "docs/reports/isaac-first-floor-parity/d10a-dynamite/source";
    std::ifstream radii(source/"native-base-radius.csv"),incoming(source/"native-player-amount.csv");
    check(bool(radii)&&bool(incoming),"pinned native matrices available");
    std::string line;std::getline(radii,line);int radiusCases=0,incomingCases=0;
    while(std::getline(radii,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);float damage,radius;
        row>>damage>>radius;check(bool(row)&&InventoryBombTuning::sourceRadius(damage)==radius,"native radius matrix");++radiusCases;
    }
    std::getline(incoming,line);
    while(std::getline(incoming,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);float damage,halves;uint32_t flags;
        row>>damage>>flags>>halves;check(bool(row),"incoming native row");
        if(flags!=4||damage<=0)continue; // Modifiers/zero admission are outside ordinary positive blasts.
        check(InventoryBombTuning::sourceSelfDamage(damage)==halves,"ordinary admitted native incoming amount matrix");++incomingCases;
    }
    check(radiusCases==12&&incomingCases==6,"all selected native numeric cases consumed");
}
Simulation fixture() {
    Simulation r(1866,1,{});r.arena=Arena{};r.rooms.resize(r.arena.rooms.size());
    r.arena.bounds={{-25,-1,-25},{25,8,25}};
    for(auto &room:r.arena.rooms)room.bounds=r.arena.bounds;
    r.player.position={0,.85f,0};r.debugScenario=true;r.roomClear=false;
    r.enemies.clear();r.hazards.clear();r.inventoryBombTuning=InventoryBombTuning{};
    return r;
}
EntityId target(Simulation &r,Vector3 p) {
    const auto id=r.spawn(EnemyKind::Gunman,p);auto &e=*r.findEnemy(id);
    e.hp=e.maxHp=1000;e.state=EnemyState::Stunned;e.stateTime=30;return id;
}
void countdownAndDamage() {
    for(int hz:{30,60,120}) {
        auto r=fixture();const auto victim=target(r,{1,.85f,0}),outside=target(r,{8,.85f,0});
        check(r.placeDynamite(),"ordinary bomb admitted");const auto birth=r.hazards.back();
        check(birth.tunedInventoryBomb&&near(birth.blastDamage,320)&&near(birth.radius,75*11.f/260)&&birth.damage==20,
              "source 100/75/two half-hearts cross independent explicit adapters");
        const int ticks=46*hz/30;
        for(int i=1;i<ticks;++i)r.step({},1.f/float(hz));
        check(r.stats.explosions==0&&r.hazards.size()==1&&r.player.hp==6,"no explosion on countdown 1 to 0");
        r.step({},1.f/float(hz));
        if(!(r.stats.explosions==1&&r.hazards.empty()&&r.player.hp==4))
            std::cerr<<"clock="<<hz<<" blasts="<<r.stats.explosions<<" charges="<<r.hazards.size()<<" hp="<<r.player.hp
                     <<" age="<<(r.hazards.empty()?0:r.hazards.front().age)<<" delay="<<birth.delay<<'\n';
        check(r.stats.explosions==1&&r.hazards.empty()&&r.player.hp==4,"46th source update explodes once and removes one full heart");
        check(near(r.findEnemy(victim)->hp,680)&&r.findEnemy(outside)->hp==1000,"320 internal damage only reaches nearby recipient");
        for(int i=0;i<30;++i)r.step({},1.f/float(hz));
        check(r.stats.explosions==1&&r.player.hp==4&&r.dynamite==2,"no duplicate damage or inventory spend");
    }
}
void snapshotsAndOverrides() {
    auto r=fixture();r.godMode=true;check(r.placeDynamite(),"first snapshot admitted");const auto first=r.hazards.front();
    r.inventoryBombTuning=InventoryBombTuning{2,1.5f,150,0};r.dynamiteCooldown=0;
    check(r.placeDynamite(),"second snapshot admitted");const auto second=r.hazards.back();
    check(first.delay==r.hazards.front().delay&&r.hazards.front().blastDamage==320&&r.hazards.front().damage==20,
          "live configuration preserves previously placed charge");
    check(near(second.delay,first.delay*2)&&near(second.radius,90*11.f/260*1.5f)&&near(second.blastDamage,480)&&second.damage==0,
          "new charge uses independent edited fuse, radius, source damage and safe self-damage override");
    for(const auto [damage,radius,halves]:{std::array<float,3>{84.999f,75,1},{85,75,2},{140,75,2},{140.001f,90,2},{174.999f,90,2},{175,105,2}}) {
        r.hazards.clear();r.dynamite=3;r.dynamiteCooldown=0;r.inventoryBombTuning=InventoryBombTuning{1,1,damage,-1};
        check(r.placeDynamite(),"source threshold case admitted");const auto &h=r.hazards.front();
        check(near(h.radius,radius*11.f/260)&&h.damage==halves*10,"native radius/self-damage threshold applied before conversion");
    }
    r.hazards.clear();r.inventoryBombTuning=InventoryBombTuning{1,1,100,0};r.dynamiteCooldown=0;r.godMode=false;
    check(r.placeDynamite(),"zero-self-damage override admitted");for(int i=0;i<100;++i)r.step({});
    check(r.player.hp==6,"zero self-damage override does not round up to one half-heart");
    auto dodge=fixture();check(dodge.placeDynamite(),"dodge fixture charge");
    for(int i=0;i<91;++i)dodge.step({});dodge.player.dodge=.2f;dodge.step({});
    check(dodge.player.hp==6&&dodge.stats.explosions==1,"universal dodge immunity retained at detonation");
    auto braid=fixture();braid.grant(ItemId::Braid);check(braid.placeDynamite(),"Braid charge admitted");
    check(!braid.hazards.back().tunedInventoryBomb&&near(braid.hazards.back().blastDamage,70),"existing Braid item contract retained");
    auto legacy=fixture();legacy.inventoryBombTuning.reset();check(legacy.placeDynamite(),"historical fixture admitted");
    check(legacy.hazards.back().delay==DynamiteFuse&&legacy.hazards.back().blastDamage==DynamiteDamage,"historical Simulation behavior remains opt-in");
    for(int hz:{30,60,120}) {
        auto longFuse=fixture();longFuse.inventoryBombTuning->fuseMultiplier=4;
        check(longFuse.placeDynamite(),"long fuse admitted");
        for(int i=1;i<184*hz/30;++i)longFuse.step({},1.f/float(hz));
        check(longFuse.stats.explosions==0,"long fuse does not detonate early");
        longFuse.step({},1.f/float(hz));check(longFuse.stats.explosions==1,"upper fuse bound preserves partition timing");
    }
}
}
int main() {try {sourceMatrices();countdownAndDamage();snapshotsAndOverrides();std::cout<<"PASS D10a native matrices, clock partitions, source thresholds, actual damage, birth snapshots, dodge, Braid and legacy isolation\n";}
catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
