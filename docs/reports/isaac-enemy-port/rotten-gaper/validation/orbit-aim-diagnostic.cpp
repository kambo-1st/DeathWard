#include "combat/Simulation.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
#include <chrono>
#include <filesystem>
#include <fstream>
using namespace dw;
namespace {
void check(bool ok, const char *message) {
    if (!ok)
        throw std::runtime_error(message);
}
Simulation fixture() {
    Simulation s(1866, 1, {});
    s.arena = Arena{};
    s.rooms.resize(s.arena.rooms.size());
    s.arena.bounds = {{-25, -1, -25}, {25, 4, 25}};
    s.arena.walls = {{{-26, -1, -26}, {-25, 5, 26}},
                     {{25, -1, -26}, {26, 5, 26}},
                     {{-26, -1, -26}, {26, 5, -25}},
                     {{-26, -1, 25}, {26, 5, 26}}};
    for (auto &r : s.arena.rooms) {
        r.bounds = s.arena.bounds;
        r.center = {0, 0, 0};
        r.floors = {{{-25, -.4f, -25}, {25, 0, 25}}};
    }
    s.player.position = {0, .85f, 8};
    s.debugScenario = true;
    s.roomClear = false;
    return s;
}
void tick(Simulation &s, int count) {
    for (int n = 0; n < count; ++n)
        s.step({});
}
}
int main(){std::cout<<std::unitbuf;
 for(int mode=0;mode<4;++mode){auto s=fixture();s.debugScenario=false;s.rooms[0].cleared=false;const auto id=s.spawnMonster(monsterId(10,3,5),{0,.85f,0});int frame=0;
 for(;frame<3600&&!s.dead&&!s.roomClear;++frame){const auto* e=s.findEnemy(id);if(!e)break;Input in;in.fire=true;
 float lead=mode==0?1:mode==1?0:mode==2?.5f:1.5f;
 in.aim=add(e->position,mul(e->velocity,lead*distance(e->position,s.player.position)/30.f));
 in.movement=distance(e->position,s.player.position)<5?unit(sub(s.player.position,e->position)):Vector3{};
 in.dodge=distance(e->position,s.player.position)<2.2f;s.step(in);
 if(frame%600==599)std::cout<<"mode="<<mode<<" frame="<<frame<<" enemyHP="<<(s.findEnemy(id)?s.findEnemy(id)->hp:0)<<" shots="<<s.stats.shots<<" playerHP="<<s.player.hp<<" pos="<<(s.findEnemy(id)?s.findEnemy(id)->position.x:0)<<","<<(s.findEnemy(id)?s.findEnemy(id)->position.z:0)<<'\n';}
 std::cout<<"mode="<<mode<<" frames="<<frame<<" clear="<<s.roomClear<<" playerHP="<<s.player.hp<<'\n';}}
