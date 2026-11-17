#pragma once
#include "combat/BrotherBobby.hpp"
#include "combat/HaloOfFlies.hpp"
#include "combat/ActiveItem.hpp"
#include "combat/Trinket.hpp"
#include "combat/InventoryBombTuning.hpp"
#include <filesystem>
#include <string>

namespace dw {
// Versioned player/shooting/view configuration and staged map settings.
// This is not player inventory, a gameplay save or certification of native parity.
struct BalancePreset {
    static constexpr float ReferenceSpeed = 1, MinSpeed = .1f, MaxSpeed = 2;
    static constexpr float ReferenceZoom = 160, MinZoom = 67, MaxZoom = 285;
    static constexpr float ReferenceTears = 30.f/11.f, MinTears = .1f, MaxTears = 10;
    static constexpr float ReferenceShotSpeed = 1, MinShotSpeed = .1f, MaxShotSpeed = 3;
    static constexpr float ReferenceRange = 6.5f, MinRange = .5f, MaxRange = 20;
    static constexpr float ReferenceGaperMovement = 1, MinGaperMovement = .1f, MaxGaperMovement = 2;
    static constexpr float ReferenceSpiderMovement = 1, MinSpiderMovement = .1f, MaxSpiderMovement = 2;
    static constexpr float MinPooterMovement=.1f, MaxPooterMovement=2, MinPooterShotSpeed=.1f, MaxPooterShotSpeed=2, MinPooterInterval=.25f, MaxPooterInterval=2;
    static constexpr float ReferenceDamage=3.5f, MinDamage=.1f, MaxDamage=50;
    static constexpr float ReferenceRegularHealth=1, MinRegularHealth=.05f, MaxRegularHealth=4;
    static constexpr float MinHeartAppearanceSpeed=.25f, MaxHeartAppearanceSpeed=4;
    static constexpr float ReferenceLuck=0, MinLuck=-3, MaxLuck=20;
    float playerSpeed = ReferenceSpeed;
    std::string mechanicsFingerprint;
    float roomSizeScale = 1;
    int roomMinHalfTiles = 0, roomMaxHalfTiles = 0; // 0/0 uses the selected pacing profile.
    float routeLengthScale = 1;
    float defaultZoomPercent = ReferenceZoom;
    float tearsPerSecond = ReferenceTears, shotSpeed = ReferenceShotSpeed, rangeTiles = ReferenceRange;
    float gaperMovementMultiplier = ReferenceGaperMovement;
    float spiderMovementMultiplier = ReferenceSpiderMovement;
    float pooterMovementMultiplier=1, pooterShotSpeedMultiplier=1, pooterAttackIntervalMultiplier=1;
    float playerDamage=ReferenceDamage, regularHealthMultiplier=ReferenceRegularHealth;
    bool sourceCombatRoom = true; // First-floor recorded formation; staged map setting.
    bool redHeartClearRewards=true;
    float playerLuck=ReferenceLuck;
    float redHeartAppearanceSpeed=1;
    int roomHeartLayouts=1; // Staged: 0 off, 1 source heart layers, 2 full/half test pair.
    bool coinClearRewards=true;
    bool chestClearRewards=true; // Pickup-batch adaptation; not complete native chest contents.
    bool keyClearRewards=true;
    bool bombClearRewards=true;
    InventoryBombTuning inventoryBombs{};
    int keyedDoorCost=1;
    bool sourceRoomLocks=true; // Staged: source first-stage/later locks versus legacy comparison.
    bool sourceTreasureUpgrade=true; // Opening-floor single collectible pedestal; staged.
    float sadOnionStrength=1; // Live per-copy source tear-stat contribution, 0-2x.
    bool sourceShopHeart=true; // Staged opening-floor stock policy.
    int shopHeartPrice=3; // Live whole-coin price, 0-15 testing range.
    bool sourceShopKey=true; // Staged additional stock, active with the source shop policy.
    int shopKeyPrice=5; // Live whole-coin price, 0-15 testing range.
    bool sourceShopVariation=true; // Staged bounded source category schedule.
    bool steamSaleDiscounts=true; // Live owned-item effect comparison.
    int shopUpgradePrice=15; // Live base price, whole coins 0-30.
    int shopBombPrice=5; // Live ordinary dynamite base price, whole coins 0-15.
    int shopSoulHeartPrice=5; // Live soul-heart base price, whole coins 0-15.
    int shopCollectiblePool=1; // Staged: restricted pool; 0 Steam Sale / 2 BOGO test.
    int treasureCollectiblePool=1; // Staged: pool, 0 Onion test / 2 Cricket test.
    float cricketHeadStrength=1; // Live next-attack effect, 0-2x; default source contribution.
    BrotherBobbyTuning brotherBobby{};
    YumHeartTuning yumHeart{};
    TrinketTuning trinkets{};
    HaloOfFliesTuning haloOfFlies{};
    BookOfShadowsTuning bookOfShadows{};
    bool custom() const { return bookOfShadows.custom() || haloOfFlies.custom() || trinkets.custom() || yumHeart.custom() || brotherBobby.custom() || treasureCollectiblePool!=1 || cricketHeadStrength!=1 || shopCollectiblePool!=1 || shopSoulHeartPrice!=5 || shopBombPrice!=5 || !sourceShopVariation || !steamSaleDiscounts || shopUpgradePrice!=15 || !sourceShopKey || shopKeyPrice!=5 || !sourceShopHeart || shopHeartPrice!=3 || !sourceTreasureUpgrade || sadOnionStrength!=1 || !sourceRoomLocks || keyedDoorCost!=1 || inventoryBombs.custom() || !bombClearRewards || !keyClearRewards || !chestClearRewards || !coinClearRewards || roomHeartLayouts!=1 || redHeartAppearanceSpeed!=1 || !redHeartClearRewards || playerLuck!=ReferenceLuck || !sourceCombatRoom || playerDamage != ReferenceDamage || regularHealthMultiplier != ReferenceRegularHealth || playerSpeed != ReferenceSpeed || roomSizeScale != 1 || roomMinHalfTiles != 0 || routeLengthScale != 1 || defaultZoomPercent != ReferenceZoom || tearsPerSecond != ReferenceTears || shotSpeed != ReferenceShotSpeed || rangeTiles != ReferenceRange || gaperMovementMultiplier != ReferenceGaperMovement || spiderMovementMultiplier != ReferenceSpiderMovement || pooterMovementMultiplier != 1 || pooterShotSpeedMultiplier != 1 || pooterAttackIntervalMultiplier != 1; }
    void validate() const;
    std::string json() const;
    std::string revision() const;
    void save(const std::filesystem::path &path) const;
    static BalancePreset load(const std::filesystem::path &path, const std::string &mechanicsFingerprint);
};
} // namespace dw
