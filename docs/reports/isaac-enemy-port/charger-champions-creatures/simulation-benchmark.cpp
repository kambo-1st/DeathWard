#include "combat/Simulation.hpp"
#include <chrono>
#include <iostream>
using namespace dw;
int main(){for(int batch:{3,4}){Simulation s(1866,1,{},MissionTheme::Canyon,true,false);s.startPractice(batch);s.godMode=true;double total=0,worst=0;for(int n=0;n<600;++n){Input in;const auto radial=unit(horizontal(sub(s.player.position,s.arena.rooms[size_t(s.room)].center)));in.movement={-radial.z,0,radial.x};const auto start=std::chrono::steady_clock::now();s.step(in);const double t=std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-start).count();total+=t;worst=std::max(worst,t);}std::cout<<"batch="<<batch<<" mean_sim_ms="<<total/600<<" max_sim_ms="<<worst<<" actors="<<s.enemies.size()<<" projectiles="<<s.projectiles.size()<<"\n";}}
