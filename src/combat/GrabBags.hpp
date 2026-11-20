#pragma once
#include "combat/ChestLoot.hpp"
#include "combat/Trinket.hpp"
namespace dw {
struct GrabBagTuning {
    bool enabled=true;
    int price=7;
    float bombFuse=1, bombMovement=1;
    bool goldenKeys=true; // Future bag-drop admission; never revokes an owned floor flag.
    bool operator==(const GrabBagTuning &)const=default;
    bool custom()const{return *this!=GrabBagTuning{};}
    void validate()const{if(price<0||price>30||!std::isfinite(bombFuse)||bombFuse<.25f||bombFuse>4||!std::isfinite(bombMovement)||bombMovement<.1f||bombMovement>2)throw std::runtime_error("Invalid grab bag controls");}
};
// Ordinary5.69.1 contents: original DropRNG, weighted copied RNG, discarded
// draw and spawn seed order. Source descriptor/factory mapping remains separate.
inline std::vector<ChestDrop> sourceGrabBagContents(uint32_t seed) {
    if(!seed)throw std::invalid_argument("Grab bag needs a nonzero seed");
    const auto next=[&]{seed^=seed>>4;seed^=seed<<3;seed^=seed>>17;return seed;};
    const int count=2+int(next()%2);std::vector<ChestDrop> out;
    for(int i=0;i<count;++i){
        SourceAwardRng choice{next()};const auto roll=choice.bounded(58);
        const int variant=roll<15?40:roll<35?30:roll<50?20:roll<54?90:300;
        next();out.push_back({variant,0,next(),false});
    }
    return out;
}
// Installed bag35/25/16; only Collect is used by preplaced shop stock.
struct GrabBagPickup {
    Vector3 position{};int room=-1,shopSlot=-1;uint32_t seed=1;
    bool opened=false;TrinketTiming timing{};
    std::vector<ChestDrop> contents;
};
}
