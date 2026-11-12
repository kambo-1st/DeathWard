#pragma once
#include <algorithm>
#include <cstdint>
#include <vector>

namespace dw {
// Numeric RoomConfig filter and ordinary selection from pinned 1.7.9b.
// Callers supply stage pool, difficulty, shape, door request and seed. These
// inputs, special seed effects and floor generation are separate parity work.
struct SourceRoomQuery {
    int type=1,shape=1;
    uint32_t minVariant=0,maxVariant=0xffffffffu;
    int minDifficulty=1,maxDifficulty=5,doors=0,subtype=-1;
};
// Verified ordinary non-XL Normal Basement I caller. Shape/doors remain the
// explicit canyon compatibility adapter; other stages/modes are not enabled.
inline SourceRoomQuery sourceBasementFirstFloorQuery(int doors) {
    return {1,1,0,0xffffffffu,1,5,doors,0};
}
struct SourceRoomDescriptorSeeds {uint32_t decoration,spawn,award,bossDeath;};
inline SourceRoomDescriptorSeeds sourceRoomDescriptorSeeds(uint32_t selectionSeed) {
    const auto next=[](uint32_t &s){s^=s>>2;s^=s<<7;s^=s>>9;return s;};
    SourceRoomDescriptorSeeds result{};
    result.decoration=next(selectionSeed);
    result.spawn=next(selectionSeed);
    result.award=next(selectionSeed);
    auto boss=result.award;boss^=boss>>11;boss^=boss<<7;boss^=boss>>12;
    result.bossDeath=boss;
    return result;
}
template<class Row> bool sourceRoomEligible(const Row &row,const SourceRoomQuery &q) {
    return row.type==q.type&&(q.shape==13||row.shape==q.shape)&&
        uint32_t(row.variant)>=q.minVariant&&uint32_t(row.variant)<=q.maxVariant&&
        row.difficulty>=q.minDifficulty&&row.difficulty<=q.maxDifficulty&&
        (row.doors&q.doors)==q.doors&&(q.subtype==-1||row.subtype==q.subtype);
}
inline float sourceRoomRandom(uint32_t &state) {
    state^=state>>1;state^=state<<21;state^=state>>20;
    // Native float conversion and constant, including rounding below 1.
    return float(state)*2.3283061589829401e-10f;
}
inline float sourceRoomSpawnRandom(uint32_t &state) {
    state^=state>>2;state^=state<<7;state^=state>>7;
    return float(state)*2.3283061589829401e-10f;
}
template<class Rows> int sourceRoomSpawnChoice(const Rows &rows,int first,int count,float unit) {
    if(count<=0)return -1;
    float total=0;for(int i=0;i<count;++i)total+=rows[size_t(first+i)].weight;
    const float target=unit*total;float accumulated=0;
    for(int i=0;i<count;++i) {
        accumulated+=rows[size_t(first+i)].weight;
        if(accumulated>target)return first+i;
    }
    return first; // Native diagnostic fallback; no reroll or last-entry substitution.
}
template<class Rows> int sourceRoomSelect(const Rows &rows,std::vector<float> &weights,
                                         const SourceRoomQuery &q,uint32_t seed,bool reduce=true) {
    if(!seed||weights.size()!=rows.size())return -1;
    float total=0,exactTotal=0;bool hasExact=false;
    for(size_t i=0;i<rows.size();++i)if(sourceRoomEligible(rows[i],q)) {
        total+=weights[i];
        if(q.doors&&rows[i].doors==q.doors){exactTotal+=weights[i];hasExact=true;}
    }
    if(total<=0)return -1;
    const float roll=sourceRoomRandom(seed);
    const bool exact=hasExact&&sourceRoomRandom(seed)<(exactTotal/total)*9.99f;
    const float target=roll*(exact?exactTotal:total);float accumulated=0;
    for(size_t i=0;i<rows.size();++i) {
        if(!sourceRoomEligible(rows[i],q)||(exact&&rows[i].doors!=q.doors))continue;
        accumulated+=weights[i];
        if(accumulated>target) {
            if(reduce)weights[i]=std::max(1.e-7f,weights[i]*.1f);
            return int(i);
        }
    }
    return -1;
}
} // namespace dw
