#include "content/Mechanics.hpp"
#include <iostream>
#include <set>
int main(){auto c=dw::defaultMechanics();std::set<dw::MonsterId> ids;for(int b=0;b<4;++b)for(int p=0;p<4;++p){const auto &pool=c->encounterPool(b,dw::EncounterPattern(p));for(const auto &row:pool.basics)if(row.weight>0)ids.insert(row.monster);for(const auto &row:pool.specialists)if(row.weight>0)ids.insert(row.monster);}std::cout<<"fingerprint="<<c->fingerprint()<<" definitions="<<c->monsters().size()<<" direct_pool_id_count="<<ids.size()<<'\n';for(auto id:ids)std::cout<<dw::monsterIdText(id)<<' ';std::cout<<'\n';}
