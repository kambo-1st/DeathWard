#include "combat/Simulation.hpp"
#include "core/BalancePreset.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
std::vector<std::string> columns(const std::string &row){std::istringstream in(row);std::vector<std::string> result;for(std::string s;std::getline(in,s,',');)result.push_back(s);return result;}
std::unique_ptr<Simulation> fixture(bool enabled=true) {
    auto run=std::make_unique<Simulation>(1866,1,WorldState{},MissionTheme::Mine,false);
    run->arena=Arena{};run->arena.bounds={{-100,-1,-100},{100,20,100}};run->arena.rooms.resize(1);
    auto &r=run->arena.rooms[0];r.bounds=run->arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;
    r.floors={{{-100,-.4f,-100},{100,0,100}}};run->arena.rebuildWalls();
    run->enemies.clear();run->projectiles.clear();run->hazards.clear();run->moneyPickups.clear();run->heartPickups.clear();
    run->rooms.assign(1,{});run->room=0;run->stats={};run->debugScenario=true;run->godMode=true;
    run->player.position={40,.85f,0};if(enabled)run->gaperMovementMultiplier=1;
    return run;
}
void step(Simulation &run,int count){for(int n=0;n<count;++n)run.step({},Tick);}
void nativeTrajectories(Vector3 offset={}) {
    // Compare independent preserved native states at the production adapter's
    // scale. Source-native error bounds declared before executing the cases.
    constexpr float scale=Simulation::GaperMovementScale;
    constexpr float positionBound=.002f,velocityBound=.005f;
    auto world=[&](float x,float y){return Vector3{offset.x+(x-320)*scale,.85f,offset.z+(y-280)*scale};};
    std::ifstream in(std::string(DEATHWARD_TEST_ROOT)+"/docs/reports/isaac-first-floor-parity/gaper-trajectories/native-trajectories.csv");
    check(bool(in),"preserved native trajectories available");std::string row,name;std::getline(in,row);
    std::unique_ptr<Simulation> run;EntityId id=0;int cases=0,states=0;float maxPosition=0,maxVelocity=0;
    while(std::getline(in,row)) {
        const auto c=columns(row);check(c.size()==18,"native row schema");if(c[1]!="1")continue;
        const auto target=world(std::stof(c[5]),std::stof(c[6]));
        const auto expected=world(std::stof(c[9]),std::stof(c[10]));
        if(name!=c[0]) {
            if(!name.empty())std::cout<<name<<" position_error="<<maxPosition<<" velocity_error="<<maxVelocity<<'\n';
            name=c[0];++cases;maxPosition=maxVelocity=0;run=fixture();run->player.position=target;
            if(c[7]=="blocked"){run->arena.obstacles={{{offset.x+100*scale,0,-200},{offset.x+110*scale,3,200}}};run->arena.rebuildWalls();}
            id=run->spawnMonster(monsterId(10,1),expected);auto *e=run->findEnemy(id);check(e,"ordinary source body spawns");
            e->friendly=true; // Isolate reference motion from separate physical contact constraints.
            e->velocity={std::stof(c[16])*30*scale,0,std::stof(c[17])*30*scale};
            continue;
        }
        run->player.position=target;run->step({},Tick);const auto *e=run->findEnemy(id);check(e&&e->alive,"reference actor retained");
        const Vector3 expectedVelocity{std::stof(c[14])*30*scale,0,std::stof(c[15])*30*scale};
        maxPosition=std::max(maxPosition,planarDistance(e->position,expected));
        maxVelocity=std::max(maxVelocity,length(sub(e->velocity,expectedVelocity)));
        if(maxPosition>=positionBound||maxVelocity>=velocityBound) {
            std::cerr<<"actual_position="<<e->position.x<<','<<e->position.z<<" expected="<<expected.x<<','<<expected.z
                     <<" actual_velocity="<<e->velocity.x<<','<<e->velocity.z<<" expected_velocity="<<expectedVelocity.x<<','<<expectedVelocity.z<<'\n';
            throw std::runtime_error("D04 source trajectory mismatch: "+row);
        }
        ++states;
    }
    check(cases==8&&states==1260,"all eight ordinary cases/1260 half-step states covered");
    std::cout<<name<<" position_error="<<maxPosition<<" velocity_error="<<maxVelocity<<'\n';
    std::cout<<"PASS native ordinary trajectories: cases="<<cases<<" states="<<states<<" bounds=.002/.005 world units offset="<<offset.x<<','<<offset.z<<'\n';
}
void ratesAndBoundaries() {
    for(float factor:{.1f,.5f,1.f,2.f}) {
        auto run=fixture();run->gaperMovementMultiplier=factor;const auto id=run->spawnMonster(monsterId(10,1),{0,.85f,0});step(*run,240);
        const auto *e=run->findEnemy(id);const float speed=length(e->velocity);
        check(std::abs(speed-1.805062f*factor)<.003f,"native-relative steady speed at editor bounds and intermediate overrides");
        check(e->hp==32&&e->maxHp==32&&e->radius==.6f&&run->player.shotDamage==24,"movement preserves HP, damage and body geometry");
        const auto before=e->position;const auto velocity=e->velocity;run->gaperMovementMultiplier=1;
        check(distance(run->findEnemy(id)->position,before)==0&&distance(run->findEnemy(id)->velocity,velocity)==0,"live tuning does not teleport or reset momentum");
        step(*run,120);check(std::abs(length(run->findEnemy(id)->velocity)-1.805062f)<.003f,"new drive settles to reference");
        std::cout<<"gaper_multiplier="<<factor<<" steady="<<speed<<" base_player_ratio="<<speed/4.8f<<'\n';
    }
    for(int variant:{0,2,3}) {
        auto old=fixture(false),now=fixture();const auto a=old->spawnMonster(monsterId(10,variant,variant==3?1:0),{0,.85f,0});
        const auto b=now->spawnMonster(monsterId(10,variant,variant==3?1:0),{0,.85f,0});now->gaperMovementMultiplier=.5f;
        step(*old,90);step(*now,90);
        check(distance(old->findEnemy(a)->position,now->findEnemy(b)->position)<.00001f,"unselected Gaper variants remain unchanged");
    }
    auto run=fixture();const auto id=run->spawnMonster(monsterId(10,1),{0,.85f,0});step(*run,120);auto *e=run->findEnemy(id);
    e->state=EnemyState::Stunned;e->stateTime=.1f;const auto at=e->position;step(*run,5);
    check(distance(at,run->findEnemy(id)->position)<.00001f,"stun stops tuned movement");
    step(*run,120);check(run->applyEnemyStatus(id,EnemyStatus::Freeze,60),"freeze accepted");step(*run,20);
    check(length(run->findEnemy(id)->velocity)<.01f,"freeze settles existing tuned motion");
    std::cout<<"PASS live drive transition, unselected variants, stun/freeze and unchanged HP/body\n";
}
void physicalRoutesAndContact() {
    for(int scenario=0;scenario<3;++scenario) {
        auto run=fixture();run->player.position={12,.85f,0};
        run->arena.obstacles={scenario==0?Box{{-1,0,-3},{1,3,3}}:Box{{-1,0,-200},{1,3,200}}};run->arena.rebuildWalls();
        const auto id=run->spawnMonster(monsterId(10,1),{-12,.85f,0});run->findEnemy(id)->friendly=true;
        for(int n=0;n<1800;++n) {
            if(scenario==2&&n==120){run->arena.obstacles.clear();run->arena.rebuildWalls();}
            run->step({},Tick);const auto *e=run->findEnemy(id);
            check(!run->arena.blocked(e->position,e->radius),"tuned Gaper footprint respects cover");
            if(scenario==1)check(e->position.x<-1.59f,"sealed barrier prevents crossing");
        }
        const auto *e=run->findEnemy(id);
        if(scenario!=1)check(planarDistance(e->position,run->player.position)<1.2f,"round finite cover or resume after removal");
        std::cout<<"physical_route="<<scenario<<" remaining_distance="<<planarDistance(e->position,run->player.position)<<'\n';
    }
    auto run=fixture();run->godMode=false;run->player.position={0,.85f,0};
    const auto id=run->spawnMonster(monsterId(10,1),{1.2f,.85f,0});run->step({},Tick);
    check(run->player.hp==6,"no contact damage outside existing body reach");step(*run,40);
    check(run->player.hp==5,"one eligible contact removes one half-heart");
    check(!run->arena.blocked(run->findEnemy(id)->position,.6f),"contact body remains on legal terrain");
    const float hp=run->player.hp;step(*run,3);check(run->player.hp==hp,"hurt cooldown prevents immediate repeat contact");
    std::cout<<"PASS physical terrain/contact adaptation; native radius/collision parity is not claimed\n";
}
void naturalInventory() {
    for(unsigned seed:{57u}) {
        Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,defaultMechanics(),1.1f,7,9,.26f);
        run.gaperMovementMultiplier=1;
        for(int passage:run.arena.rooms[0].passages) {
            const auto &link=run.arena.passages[passage];const int room=link.rooms[0]==0?link.rooms[1]:link.rooms[0];
            bool found=false,clearReview=true;
            for(const auto &e:run.roomEnemies(room)) {
                if(e.monster==monsterId(10,1)&&e.champion<0)found=true;
                else if(e.champion>=0||(run.content->monster(e.monster)->speed>0&&e.monster!=monsterId(13)))clearReview=false;
            }
            if(!found||!clearReview)continue;
            std::cout<<"HANDOFF seed="<<seed<<" floor=0 room="<<room<<" displayed_room="<<room+1<<" passage="<<passage<<'\n';
            for(const auto &e:run.roomEnemies(room)) {
                check(!run.arena.blocked(e.position,e.radius),"natural residents have legal footprints");
                std::cout<<"NATURAL id="<<e.monster.type<<'.'<<e.monster.variant<<'.'<<e.monster.subtype<<" entity="<<e.id<<" champion="<<e.champion<<" position="<<e.position.x<<','<<e.position.z<<'\n';
            }
            const auto a=run.arena.rooms[0].center,b=run.arena.rooms[room].center;
            std::cout<<"entrance_center="<<a.x<<','<<a.z<<" encounter_center="<<b.x<<','<<b.z<<'\n';
            return;
        }
    }
    check(false,"natural handoff seed with adjacent ordinary Gapers found");
}
}
int main(int argc,char **argv){std::cout<<std::unitbuf;try{if(argc>1&&std::string(argv[1])=="--inventory"){naturalInventory();return 0;}nativeTrajectories();nativeTrajectories({30,0,-17});nativeTrajectories({-63,0,28});ratesAndBoundaries();physicalRoutesAndContact();naturalInventory();return 0;}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
