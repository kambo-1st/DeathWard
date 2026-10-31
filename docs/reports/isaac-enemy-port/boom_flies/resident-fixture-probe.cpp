#include "combat/Simulation.hpp"
#include <iostream>
using namespace dw;
int locate(Simulation &s,MonsterId id,MonsterId from) {
 for(int room=1;room<s.arena.roomCount();++room) {
  const auto plan=s.floorEncounter(room);const auto &actors=s.roomEnemies(room);
  for(size_t slot=0;slot<actors.size();++slot) {
   const auto source=slot<plan.originalMonsters.size()?plan.originalMonsters[slot]:actors[slot].monster;
   if(actors[slot].monster==id&&(!from||source==from))return room;
  }
 }
 return -1;
}
int main(int argc,char**argv){
 if(argc>1) {
  const auto id=parseMonsterId(argv[1]);const auto from=argc>2?parseMonsterId(argv[2]):MonsterId{};const int band=argc>3?std::stoi(argv[3]):1;
  for(uint64_t seed=0;seed<300;++seed) {
   ExpeditionPlan plan(seed);
   for(int floor=0;floor<plan.floorCount;++floor)if(plan.profileOnFloor(floor).band==band) {
    Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);const int room=locate(s,id,from);
    if(room>=0){std::cout<<"FOUND "<<monsterIdText(id)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';return 0;}
   }
  }return 1;
 }
 std::string name,idText,fromText;uint64_t seed;int floor,expected;
 while(std::cin>>name>>idText>>seed>>floor>>expected>>fromText) {
  Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
  const int room=locate(s,parseMonsterId(idText),fromText=="-"?MonsterId{}:parseMonsterId(fromText));
  std::cout<<(room<0?"MISSING":expected>=0&&room!=expected?"MOVED":"OK")<<' '<<name<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<" expected="<<expected<<'\n'<<std::flush;
 }
}
