#pragma once
#include "world/SourceShopStock.hpp"
#include "world/SourceHeartRockRoom.hpp"
#include "world/ShopCartGeometry.hpp"
#include "world/SourceRoomSelection.hpp"
namespace dw {
inline constexpr int RecordedShopReview=2000000; // Type2/template0; not normal-room0.
struct RecordedShopSlot {int ordinal,x,y,type,variant,subtype;};
// Original STB slot order. The keeper slot also has a weight-.5 variant0 choice.
// Recorded runtime: keeper17.1.4, purse195/card15, no donation machine actor.
// D14a.13 verifies variant8's custom-run/restriction/jam initializer gates.
// D14a.14 enables this slot in an ordinary eligible DW context. The old capture
// lacks those gate inputs; its absence is not inferred from the numeric seed.
inline constexpr std::array<RecordedShopSlot,8> RecordedShopSlots{{
    {0,3,0,6,8,0},{1,1,1,1000,0,0},{2,5,1,1000,0,0},{3,6,1,17,1,0},
    {4,7,1,1000,0,0},{5,11,1,1000,0,0},{6,5,4,5,150,0},{7,7,4,5,150,0}}};
inline bool matchesRecordedShop(uint64_t seed,int collectiblePool) {
    const int item=collectiblePool==3?195:collectiblePool==1?sourceShopCollectibleChoice(canyonShopCollectibleSeed(seed),true):0;
    const auto stock=sourceShopStock(canyonShopStockSeed(seed));
    return item==195&&stock.categories[0]==8&&stock.categories[1]==6&&stock.discountSlot!=0&&stock.discountSlot!=1;
}
inline float recordedShopCellSize(const RoomLayout &room) {
    return room.sourcePropCellOverride>0?room.sourcePropCellOverride:sourceHeartCellSize(room);
}
inline float recordedShopRockHalf(const RoomLayout &room){return recordedShopCellSize(room)*.42f;}
inline Vector3 recordedShopCell(const RoomLayout &room,int x,int y) {
    const float cell=recordedShopCellSize(room);
    // Retain the existing merchant wagon as the keeper's visual/physical adapter.
    // Anchor source(6,1) to it. Separate adjacent rocks from its wider footprint.
    float dx=(x-6)*cell;
    if(y==1&&(x==5||x==7))dx=(x<6?-1.f:1.f)*std::max(cell,shopCartGeometry::HalfWidth+recordedShopRockHalf(room)+.5f);
    auto at=add(room.center,{dx,0,(y-1)*cell});at.y=.85f;return at;
}
inline uint32_t recordedShopSlotSeed(const RoomLayout &room,int ordinal) {
    auto state=room.sourceRoomSpawnSeed;for(int n=0;n<=ordinal;++n)sourceRoomSpawnRandom(state);return state;
}
}
