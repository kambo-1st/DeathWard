#include "combat/Simulation.hpp"
#include "items/Items.hpp"
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
int main(){std::cout<<std::unitbuf;auto s=fixture();s.godMode=true;s.player.position={0,.85f,8};
 s.arena.walls.push_back({{-25,-1,2},{-1,5,3}});s.arena.walls.push_back({{1,-1,2},{25,5,3}});
 for(int n=0;n<5;++n)s.spawnMonster(monsterId(10,3,4),{float(n-2)*1.3f,.85f,-2});
 for(int frame=0;frame<2400;++frame){s.step({});if(frame>=700&&(frame<730||frame%100==0))for(const auto&e:s.enemies)if(e.position.z<3){
 std::cout<<"frame="<<frame<<" id="<<e.id<<" pos="<<e.position.x<<","<<e.position.z<<" vel="<<e.velocity.x<<","<<e.velocity.z<<" pathTime="<<e.pathTime<<" momentum="<<e.rottenGaper->momentum.x<<","<<e.rottenGaper->momentum.z;
 for(const auto&p:e.path)std::cout<<" path="<<p.x<<","<<p.z<<":"<<s.arena.clear(e.position,p,e.radius);
 std::cout<<'\n';}}
 for(const auto&e:s.enemies)std::cout<<"FINAL "<<e.id<<" pos="<<e.position.x<<","<<e.position.z<<'\n';}
