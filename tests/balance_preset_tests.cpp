#include "core/BalancePreset.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace dw;
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
std::string replaceOne(std::string s,const std::string &from,const std::string &to) {
    auto at=s.find(from);if(at==s.npos)throw std::runtime_error("Missing mutation fixture: "+from);s.replace(at,from.size(),to);return s;
}
int main() {
    const auto dir=std::filesystem::temp_directory_path()/
        ("deathward-preset-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    try {
        std::filesystem::create_directories(dir);const auto file=dir/"roundtrip.json";
        for(float speed:{.1f,.8f,1.f,1.234567f,2.f}) {
            BalancePreset p{speed,"fixture-content"};p.save(file);
            const auto loaded=BalancePreset::load(file,"fixture-content");
            check(loaded.playerSpeed==speed&&loaded.revision()==p.revision(),"export/import preserves effective value and revision");
        }
        for(float route:{.25f,.99f,1.f,1.01f,2.f})for(float scale:{.75f,1.f,1.25f,1.5f})for(auto range:{std::pair{0,0},std::pair{5,5},std::pair{7,9},std::pair{10,10}}) {
            BalancePreset p{.8f,"fixture-content",scale,range.first,range.second,route};p.save(file);
            check(BalancePreset::load(file,"fixture-content").revision()==p.revision(),"size and range round-trip");
        }
        for(float zoom:{67.f,125.f,159.25f,160.f,285.f}) {
            BalancePreset p{.8f,"fixture-content",1.25f,7,9,.65f,zoom};p.save(file);
            const auto loaded=BalancePreset::load(file,"fixture-content");
            check(loaded.defaultZoomPercent==zoom&&loaded.revision()==p.revision(),"default zoom round-trips with independent Speed/map settings");
        }
        for(float tears:{.1f,BalancePreset::ReferenceTears,2.827f,4.f,10.f})
            for(float speed:{.1f,1.f,1.5f,3.f})for(float range:{.5f,6.5f,8.f,20.f}) {
                BalancePreset p{1,"fixture-content",1.1f,7,9,.3f,165,tears,speed,range};p.save(file);
                const auto loaded=BalancePreset::load(file,"fixture-content");
                check(loaded.tearsPerSecond==tears&&loaded.shotSpeed==speed&&loaded.rangeTiles==range&&loaded.revision()==p.revision(),
                      "shooting and 165 percent view/map preset round-trip including exact default rate");
            }
        for(float appearance:{.25f,.5f,1.f,1.05f,4.f}) {
            BalancePreset p{1,"fixture-content"};p.redHeartAppearanceSpeed=appearance;p.save(file);
            check(BalancePreset::load(file,"fixture-content").redHeartAppearanceSpeed==appearance,"heart appearance override survives export/load");
        }
        const auto v11=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d09a-red-heart-rewards/preset.json","2ccd5b1c274a302e");
        check(v11.redHeartAppearanceSpeed==1&&v11.defaultZoomPercent==165&&v11.playerLuck==5,"v11 migrates appearance without losing selected settings");
        for(int mode:{0,1,2}) {
            BalancePreset p{1,"fixture-content"};p.roomHeartLayouts=mode;p.save(file);
            check(BalancePreset::load(file,"fixture-content").roomHeartLayouts==mode,"room-heart mode export/load");
        }
        const auto v12=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d09a-heart-timing/test-preset.json","2ccd5b1c274a302e");
        check(v12.roomHeartLayouts==1&&v12.redHeartAppearanceSpeed==.5f&&v12.defaultZoomPercent==165,"v12 migration retains timing/view and enables selected layout hearts");
        {
            const auto old=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d09c-keys/preset-v23-clear-off.json";
            const auto p=BalancePreset::load(old,"2ccd5b1c274a302e");
            check(p.bombClearRewards&&!p.keyClearRewards&&p.defaultZoomPercent==165&&p.roomSizeScale==1.1f,"schema23 migrates bombs preserving prior reward/map/view settings");
            p.save(file);const auto q=BalancePreset::load(file,"2ccd5b1c274a302e");
            check(q.revision()==p.revision()&&q.bombClearRewards,"schema24 migrated roundtrip");
        }
        for(bool enabled:{false,true}) {
            BalancePreset p{1,"fixture-content"};p.chestClearRewards=enabled;p.save(file);
            const auto q=BalancePreset::load(file,"fixture-content");
            check(q.chestClearRewards==enabled&&q.revision()==p.revision(),"chest option export/load and revision");
        }
        for(const auto *name:{"preset-v20.json","preset-v20-off.json"}) {
            const auto p=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
                "docs/reports/isaac-first-floor-parity/ordinary-chests"/name,"2ccd5b1c274a302e");
            check(p.roomHeartLayouts==1&&p.defaultZoomPercent==165&&p.shotSpeed==.9f,"schema20 migrates source chest layout policy preserving map/view/shooting");
            p.save(file);const auto q=BalancePreset::load(file,"2ccd5b1c274a302e");
            check(q.chestClearRewards==p.chestClearRewards&&q.revision()==p.revision(),"migrated layout policy preserves independent clear chest toggle");
        }
        for(const auto *name:{"preset-v21.json","preset-v21-off.json"}) {
            const auto p=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
                "docs/reports/isaac-first-floor-parity/preplaced-chests"/name,"2ccd5b1c274a302e");
            check(p.roomHeartLayouts==(std::string(name)=="preset-v21.json"?1:0)&&p.defaultZoomPercent==165&&p.shotSpeed==.9f,"schema21 migrates coin layout policy preserving OFF/SOURCE and accepted settings");
            p.save(file);const auto q=BalancePreset::load(file,"2ccd5b1c274a302e");
            check(q.coinClearRewards==p.coinClearRewards&&q.revision()==p.revision(),"new layout policy round-trip preserves clear-coin switch");
        }
        for(bool enabled:{false,true}) {
            BalancePreset p{1,"fixture-content"};p.keyClearRewards=enabled;p.bombClearRewards=!enabled;p.save(file);
            const auto q=BalancePreset::load(file,"fixture-content");
            check(q.keyClearRewards==enabled&&q.bombClearRewards==!enabled&&q.revision()==p.revision(),"key switch roundtrip");
        }
        for(const auto *name:{"preset-v22-clear-off.json","preset-v22-layout-off.json"}) {
            const auto p=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
                "docs/reports/isaac-first-floor-parity/preplaced-coins"/name,"2ccd5b1c274a302e");
            check(p.keyClearRewards&&p.defaultZoomPercent==165&&p.shotSpeed==.9f,"schema22 migrates keys preserving view/shooting");
            p.save(file);const auto q=BalancePreset::load(file,"2ccd5b1c274a302e");
            check(q.keyClearRewards&&q.coinClearRewards==p.coinClearRewards&&q.roomHeartLayouts==p.roomHeartLayouts&&q.revision()==p.revision(),"schema22 keeps independent map/coin switches");
        }
        const auto previousCoins=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d09b-coins/preset-v19.json","2ccd5b1c274a302e");
        check(previousCoins.chestClearRewards&&previousCoins.defaultZoomPercent==165,"schema19 migration enables selected chests and preserves view");
        const auto legacy=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d01-live-tuning/speed-080.json","2ccd5b1c274a302e");
        check(legacy.playerSpeed==.8f&&legacy.roomSizeScale==1&&legacy.roomMinHalfTiles==0&&legacy.defaultZoomPercent==160,"D01 migration preserves speed and selects automatic room sizes");
        const auto v2=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d02-room-scale/custom-size-range.json","2ccd5b1c274a302e");
        check(v2.roomSizeScale==1.25f&&v2.roomMinHalfTiles==7&&v2.roomMaxHalfTiles==9&&v2.routeLengthScale==1&&v2.defaultZoomPercent==160,
              "schema 2 migration preserves map sizing and defaults route length");
        const auto v3=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d02-room-scale/custom-map.json","2ccd5b1c274a302e");
        check(v3.routeLengthScale==.65f&&v3.defaultZoomPercent==160,"schema 3 migration retains route length and defaults zoom to 160 percent");
        const auto v4=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d02-room-scale/custom-map-zoom.json","2ccd5b1c274a302e");
        check(v4.defaultZoomPercent==125&&v4.tearsPerSecond==BalancePreset::ReferenceTears&&v4.shotSpeed==1&&v4.rangeTiles==6.5f,
              "schema 4 migration retains view/map settings and accepted shooting baseline");
        const auto v5=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json","2ccd5b1c274a302e");
        check(v5.gaperMovementMultiplier==1&&v5.defaultZoomPercent==165&&v5.shotSpeed==.9f&&v5.tearsPerSecond==1.9272734f&&v5.routeLengthScale==.26f,
              "D03 accepted preset migration retains user settings and adds reference Gaper movement");
        for(float movement:{.1f,.5f,.95f,1.f,1.05f,2.f}) {
            auto preset=v5;preset.gaperMovementMultiplier=movement;preset.save(file);
            const auto loaded=BalancePreset::load(file,"2ccd5b1c274a302e");
            check(loaded.gaperMovementMultiplier==movement&&loaded.revision()==preset.revision(),"Gaper overrides round-trip at bounds and small steps");
        }
        check(v5.sourceCombatRoom,"older presets migrate with selected D08 enabled");
        for(bool enabled:{false,true}) {
            auto p=v5;p.sourceCombatRoom=enabled;p.save(file);
            const auto loaded=BalancePreset::load(file,"2ccd5b1c274a302e");
            check(loaded.sourceCombatRoom==enabled&&loaded.revision()==p.revision(),"source room switch round-trips");
        }
        const auto v13=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d09a-room-hearts/test-preset.json","2ccd5b1c274a302e");
        check(v13.roomHeartLayouts==2&&v13.defaultZoomPercent==165&&v13.shotSpeed==.9f&&v13.routeLengthScale==.26f,
              "schema13 migrates native selection policy while preserving test mode and accepted settings");
        v13.save(file);check(BalancePreset::load(file,"2ccd5b1c274a302e").revision()==v13.revision(),"migrated schema13 exports and reloads");
        const auto v14=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/native-heart-rock-room/previous-v14.json","2ccd5b1c274a302e");
        check(v14.roomHeartLayouts==2&&v14.defaultZoomPercent==165&&v14.shotSpeed==.9f&&v14.routeLengthScale==.26f,
              "schema14 migration preserves selected mode and accepted map/view/shooting settings");
        v14.save(file);check(BalancePreset::load(file,"2ccd5b1c274a302e").revision()==v14.revision(),"schema17 reload after migration");
        const auto v15=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/native-room-eligibility/previous-v15.json","2ccd5b1c274a302e");
        check(v15.roomHeartLayouts==1&&v15.defaultZoomPercent==165&&v15.shotSpeed==.9f&&v15.routeLengthScale==.26f,
              "schema15 migrates descriptor policy while preserving the accepted settings");
        v15.save(file);check(BalancePreset::load(file,"2ccd5b1c274a302e").revision()==v15.revision(),"migrated schema15 exports/reloads with retained room exceptions");
        const auto v16=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/native-room-eligibility/preset-v16.json","2ccd5b1c274a302e");
        check(v16.roomHeartLayouts==1&&v16.defaultZoomPercent==165&&v16.shotSpeed==.9f&&v16.routeLengthScale==.26f,
              "schema16 migrates complete combat content while retaining accepted settings");
        v16.save(file);check(BalancePreset::load(file,"2ccd5b1c274a302e").revision()==v16.revision(),"schema17 exports and reloads");
        const auto v17=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/native-combat-rock-room/preset-v17.json","2ccd5b1c274a302e");
        check(v17.roomHeartLayouts==1&&v17.defaultZoomPercent==165&&v17.shotSpeed==.9f&&v17.routeLengthScale==.26f,
              "schema17 migrates added source108 content without changing accepted settings");
        v17.save(file);check(BalancePreset::load(file,"2ccd5b1c274a302e").revision()==v17.revision(),"schema18 round-trip after migration");
        auto v18=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/native-four-gaper-room/preset-v18.json","2ccd5b1c274a302e");
        check(v18.coinClearRewards&&v18.defaultZoomPercent==165&&v18.shotSpeed==.9f,"schema18 migrates coin policy preserving accepted settings");
        for(bool enabled:{false,true}) {
            v18.coinClearRewards=enabled;v18.redHeartClearRewards=false;v18.save(file);
            auto loaded=BalancePreset::load(file,"2ccd5b1c274a302e");
            check(loaded.coinClearRewards==enabled&&!loaded.redHeartClearRewards&&loaded.revision()==v18.revision(),"independent coin/heart toggles round-trip");
        }
        const auto v9=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d07-damage-health/custom-combat.json","2ccd5b1c274a302e");
        check(v9.sourceCombatRoom&&v9.playerDamage==7&&v9.regularHealthMultiplier==.75f,"schema9 migrates combat plus source room");
        const auto v10=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d08-source-room/preset.json","2ccd5b1c274a302e");
        check(v10.redHeartClearRewards&&v10.playerLuck==0&&v10.sourceCombatRoom&&v10.defaultZoomPercent==165,"schema10 migration preserves accepted settings and enables selected red hearts");
        for(bool enabled:{false,true})for(float luck:{-3.f,0.f,1.f,10.f,20.f}) {
            auto p=v10;p.redHeartClearRewards=enabled;p.playerLuck=luck;p.sourceCombatRoom=false;p.save(file);
            const auto loaded=BalancePreset::load(file,"2ccd5b1c274a302e");
            check(loaded.redHeartClearRewards==enabled&&loaded.playerLuck==luck&&loaded.revision()==p.revision(),"reward fields round-trip alongside independent map switch");
        }
        const auto v6=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d04-gaper-movement/custom-gaper.json","2ccd5b1c274a302e");
        check(v6.gaperMovementMultiplier==.65f&&v6.spiderMovementMultiplier==1&&v6.defaultZoomPercent==165,
              "D04 schema6 migration retains Gaper override and adds Spider reference");
        for(float movement:{.1f,.5f,.95f,1.f,1.05f,2.f}) {
            auto preset=v6;preset.spiderMovementMultiplier=movement;preset.save(file);
            const auto loaded=BalancePreset::load(file,"2ccd5b1c274a302e");
            check(loaded.spiderMovementMultiplier==movement&&loaded.gaperMovementMultiplier==.65f&&loaded.revision()==preset.revision(),
                  "Spider overrides round-trip independently from Gaper and player");
        }
        const auto v7=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d05-spider-movement/custom-spider.json","2ccd5b1c274a302e");
        check(v7.spiderMovementMultiplier==.65f&&v7.pooterMovementMultiplier==1&&v7.pooterShotSpeedMultiplier==1&&v7.pooterAttackIntervalMultiplier==1,
              "D05 migration preserves prior enemy tuning and supplies reference Pooter settings");
        for(float movement:{.1f,.65f,1.f,2.f})for(float speed:{.1f,.95f,1.f,2.f})for(float delay:{.25f,1.f,1.05f,2.f}) {
            auto p=v7;p.pooterMovementMultiplier=movement;p.pooterShotSpeedMultiplier=speed;p.pooterAttackIntervalMultiplier=delay;p.save(file);
            check(BalancePreset::load(file,"2ccd5b1c274a302e").revision()==p.revision(),"independent Pooter settings round-trip at bounds");
        }
        const auto v8=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
            "docs/reports/isaac-first-floor-parity/d06-pooter-shots/custom-pooter.json","2ccd5b1c274a302e");
        check(v8.playerDamage==3.5f&&v8.regularHealthMultiplier==1&&v8.pooterShotSpeedMultiplier==.65f&&v8.defaultZoomPercent==165,
              "schema8 migration enables selected damage baseline and retains prior settings");
        for(float damage:{.1f,3.5f,7.f,50.f})for(float hp:{.05f,.75f,1.f,4.f}) {
            auto p=v8;p.playerDamage=damage;p.regularHealthMultiplier=hp;p.save(file);
            check(BalancePreset::load(file,"2ccd5b1c274a302e").revision()==p.revision(),"damage/HP round-trip independently at bounds");
        }
        auto combat=v8;combat.mechanicsFingerprint="fixture-content";combat.playerDamage=7;combat.regularHealthMultiplier=.75f;
        auto pooter=v7;pooter.mechanicsFingerprint="fixture-content";pooter.pooterMovementMultiplier=.75f;pooter.pooterShotSpeedMultiplier=.65f;pooter.pooterAttackIntervalMultiplier=1.5f;
        auto spider=v5;spider.mechanicsFingerprint="fixture-content";spider.spiderMovementMultiplier=.75f;
        auto gaper=v5;gaper.mechanicsFingerprint="fixture-content";gaper.gaperMovementMultiplier=.75f;
        BalancePreset shots{1,"fixture-content",1,0,0,1,160,4,1.5f,8};
        BalancePreset zoomPreset{1,"fixture-content",1,0,0,1,125};
        BalancePreset routePreset{1,"fixture-content",1,0,0,.65f};
        BalancePreset custom{.8f,"fixture-content"};custom.save(file);
        auto appearance=custom;appearance.redHeartAppearanceSpeed=.5f;
        auto layouts=custom;layouts.roomHeartLayouts=2;
        for(float fuse:{.25f,1.f,4.f})for(float radius:{.25f,1.f,3.f})for(int self:{-1,0,1,12}) {
            auto p=custom;p.inventoryBombs={fuse,radius,175,self};p.coinClearRewards=false;p.save(file);
            check(BalancePreset::load(file,"fixture-content").revision()==p.revision(),"D10a independent controls and zero/Auto round-trip");
        }
        for(const auto name:{"preset-v24-clear-off.json","preset-v24-layout-off.json"}) {
            const auto p=BalancePreset::load(std::filesystem::path(__FILE__).parent_path().parent_path()/
                "docs/reports/isaac-first-floor-parity/d09d-bombs"/name,"2ccd5b1c274a302e");
            check(!p.inventoryBombs.custom()&&p.defaultZoomPercent==165&&p.shotSpeed==.9f,"schema24 adds D10a baseline, retaining accepted preset");
        }
        const auto valid=custom.json();
        auto customBomb=custom;customBomb.inventoryBombs={1.5f,1.25f,150,0};
        std::vector<std::string> invalid{
            replaceOne(valid,"source-countdown-shooting-space-v1","invalid-bomb-model"),
            replaceOne(valid,"\"self_damage_half_hearts\": -1","\"self_damage_half_hearts\": -0.5"),
            replaceOne(valid,"\"damage\": 100","\"damage\": 101"),
            replaceOne(customBomb.json(),"\"fuse_multiplier\": 1.5","\"fuse_multiplier\": 0.1"),
            replaceOne(customBomb.json(),"\"radius_multiplier\": 1.25","\"radius_multiplier\": 1.5"),
            replaceOne(customBomb.json(),"\"self_damage_half_hearts\": 0","\"self_damage_half_hearts\": 13"),
            replaceOne(valid,"\"bomb_clear_rewards\": true","\"bomb_clear_rewards\": 1"),
            replaceOne(valid,"\"bomb_clear_rewards\": true","\"bomb_clear_rewards\": false"),
            replaceOne(valid,"\"key_clear_rewards\": true","\"key_clear_rewards\": 1"),
            replaceOne(valid,"\"key_clear_rewards\": true","\"key_clear_rewards\": false"),
            replaceOne(valid,"ordinary-normal-charged-gate-off-v1","invalid-key-policy"),
            replaceOne(layouts.json(),"\"room_heart_layouts\": 2","\"room_heart_layouts\": 3"),
            replaceOne(layouts.json(),"\"room_heart_layouts\": 2","\"room_heart_layouts\": 1.5"),
            replaceOne(layouts.json(),"\"room_heart_layouts\": 2","\"room_heart_layouts\": false"),
            replaceOne(layouts.json(),"\"room_heart_layouts\": 2","\"room_heart_layouts\": 0"),
            replaceOne(valid,"basement-native-descriptor-bomb32-v11","invalid-policy"),
            replaceOne(appearance.json(),"\"red_heart_appearance_speed\": 0.5","\"red_heart_appearance_speed\": 0"),
            replaceOne(appearance.json(),"\"red_heart_appearance_speed\": 0.5","\"red_heart_appearance_speed\": 4.01"),
            replaceOne(appearance.json(),"\"red_heart_appearance_speed\": 0.5","\"red_heart_appearance_speed\": 2"),
            replaceOne(appearance.json(),"\"red_heart_appearance_speed\": 0.5","\"red_heart_appearance_speed\": NaN"),
            replaceOne(combat.json(),"\"player_damage\": 7","\"player_damage\": 0"),
            replaceOne(combat.json(),"\"player_damage\": 7","\"player_damage\": 50.01"),
            replaceOne(combat.json(),"\"player_damage\": 7","\"player_damage\": 6"),
            replaceOne(combat.json(),"\"regular_health_multiplier\": 0.75","\"regular_health_multiplier\": 0.049"),
            replaceOne(combat.json(),"\"regular_health_multiplier\": 0.75","\"regular_health_multiplier\": 4.01"),
            replaceOne(combat.json(),"\"regular_health_multiplier\": 0.75","\"regular_health_multiplier\": 0.7"),
            replaceOne(combat.json(),"source-damage-internal-hp-v1","incorrect-damage-units"),
            replaceOne(valid,"\"source_combat_room\": true","\"source_combat_room\": 1"),
            replaceOne(valid,"basement-1.47.0-canyon-v1","unsupported-template"),
            replaceOne(valid,"\"red_heart_clear_rewards\": true","\"red_heart_clear_rewards\": 1"),
            replaceOne(valid,"ordinary-normal-rare-gates-off-v1","unsupported-reward-policy"),
            replaceOne(valid,"\"player_luck\": 0","\"player_luck\": 21"),
            replaceOne(valid,"\"chest_clear_rewards\": true","\"chest_clear_rewards\": 1"),
            replaceOne(valid,"pickup-batches-adapted-v1","unverified-chest-policy"),
            valid+"garbage", valid.substr(0,valid.size()-3),
            replaceOne(valid,"\"schema_version\": 25","\"schema_version\": 26"),
            replaceOne(valid,"\"red_heart_appearance_speed\": 1","\"red_heart_appearance_speed\": 2"),
            replaceOne(valid,"appear33-drop25-collect12-30hz-v1","unverified-timing"),
            replaceOne(valid,"\"schema_version\": 25","\"schema_version\": 25, \"schema_version\": 25"),
            replaceOne(valid,"d10a-inventory-bombs-v25","future-contract"),
            replaceOne(valid,"fixture-content","different-content"),
            replaceOne(valid,"Repentance 1.7.9b","Repentance 1.7.9a"),
            replaceOne(valid,"\"walking_pace_at_speed_one\": 4.8","\"walking_pace_at_speed_one\": 30"),
            replaceOne(valid,"\"universal_dodge\": true","\"universal_dodge\": false"),
            replaceOne(valid,"\"canyon_room_geometry\": true","\"canyon_room_geometry\": false"),
            replaceOne(valid,"\"canyon_connections\": true","\"canyon_connections\": false"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 0.9"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": -1"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 99"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": NaN"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 1e999"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 00.8"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": .8"),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": \"0.8\""),
            replaceOne(valid,"\"player_speed\": 0.8","\"player_speed\": 0.8, \"damage\": 3.5"),
            replaceOne(valid,"\"room_size_scale\": 1","\"room_size_scale\": 0"),
            replaceOne(valid,"\"room_min_half_tiles\": 0","\"room_min_half_tiles\": 11"),
            replaceOne(valid,"\"route_length_scale\": 1","\"route_length_scale\": 0"),
            replaceOne(routePreset.json(),"\"route_length_scale\": 0.65","\"route_length_scale\": 2.01"),
            replaceOne(routePreset.json(),"\"route_length_scale\": 0.65","\"route_length_scale\": 0.64"),
            replaceOne(valid,"\"default_zoom_percent\": 160","\"default_zoom_percent\": 125"),
            replaceOne(zoomPreset.json(),"\"default_zoom_percent\": 125","\"default_zoom_percent\": 66.99"),
            replaceOne(zoomPreset.json(),"\"default_zoom_percent\": 125","\"default_zoom_percent\": 285.01"),
            replaceOne(zoomPreset.json(),"\"default_zoom_percent\": 125","\"default_zoom_percent\": 126"),
            replaceOne(zoomPreset.json(),"\"default_zoom_percent\": 125","\"default_zoom_percent\": NaN"),
            replaceOne(shots.json(),"\"tears_per_second\": 4","\"tears_per_second\": 0"),
            replaceOne(shots.json(),"\"tears_per_second\": 4","\"tears_per_second\": 10.01"),
            replaceOne(shots.json(),"\"tears_per_second\": 4","\"tears_per_second\": 3.5"),
            replaceOne(shots.json(),"\"shot_speed\": 1.5","\"shot_speed\": 0.09"),
            replaceOne(shots.json(),"\"shot_speed\": 1.5","\"shot_speed\": 3.01"),
            replaceOne(shots.json(),"\"shot_speed\": 1.5","\"shot_speed\": 2"),
            replaceOne(shots.json(),"\"range_tiles\": 8","\"range_tiles\": 0.49"),
            replaceOne(shots.json(),"\"range_tiles\": 8","\"range_tiles\": 20.01"),
            replaceOne(shots.json(),"\"range_tiles\": 8","\"range_tiles\": 7"),
            replaceOne(shots.json(),"\"tears_per_second\": 4","\"tears_per_second\": NaN"),
            replaceOne(valid,"accepted-independent-v1","unverified-new-calibration"),
            replaceOne(gaper.json(),"\"gaper_movement_multiplier\": 0.75","\"gaper_movement_multiplier\": 0.09"),
            replaceOne(gaper.json(),"\"gaper_movement_multiplier\": 0.75","\"gaper_movement_multiplier\": 2.01"),
            replaceOne(gaper.json(),"\"gaper_movement_multiplier\": 0.75","\"gaper_movement_multiplier\": 0.8"),
            replaceOne(gaper.json(),"\"gaper_movement_multiplier\": 0.75","\"gaper_movement_multiplier\": NaN"),
            replaceOne(gaper.json(),"player-relative-v1","unverified-calibration"),
            replaceOne(spider.json(),"\"spider_movement_multiplier\": 0.75","\"spider_movement_multiplier\": 0.09"),
            replaceOne(spider.json(),"\"spider_movement_multiplier\": 0.75","\"spider_movement_multiplier\": 2.01"),
            replaceOne(spider.json(),"\"spider_movement_multiplier\": 0.75","\"spider_movement_multiplier\": 0.8"),
            replaceOne(spider.json(),"\"spider_movement_multiplier\": 0.75","\"spider_movement_multiplier\": NaN"),
            replaceOne(spider.json(),"player-relative-burst-v1","unverified-calibration"),
            replaceOne(pooter.json(),"\"pooter_movement_multiplier\": 0.75","\"pooter_movement_multiplier\": 0.09"),
            replaceOne(pooter.json(),"\"pooter_movement_multiplier\": 0.75","\"pooter_movement_multiplier\": 2.01"),
            replaceOne(pooter.json(),"\"pooter_movement_multiplier\": 0.75","\"pooter_movement_multiplier\": 0.8"),
            replaceOne(pooter.json(),"\"pooter_shot_speed_multiplier\": 0.65","\"pooter_shot_speed_multiplier\": 0.09"),
            replaceOne(pooter.json(),"\"pooter_shot_speed_multiplier\": 0.65","\"pooter_shot_speed_multiplier\": 2.01"),
            replaceOne(pooter.json(),"\"pooter_shot_speed_multiplier\": 0.65","\"pooter_shot_speed_multiplier\": NaN"),
            replaceOne(pooter.json(),"\"pooter_attack_interval_multiplier\": 1.5","\"pooter_attack_interval_multiplier\": 0.24"),
            replaceOne(pooter.json(),"\"pooter_attack_interval_multiplier\": 1.5","\"pooter_attack_interval_multiplier\": 2.01"),
            replaceOne(pooter.json(),"\"pooter_attack_interval_multiplier\": 1.5","\"pooter_attack_interval_multiplier\": 1.4"),
            replaceOne(pooter.json(),"player-relative-mode0-v1","unverified-calibration"),
            std::string(65537,' ')
        };
        for(const auto &bad:invalid) {
            const auto badFile=dir/"invalid.json";{std::ofstream out(badFile);out<<bad;}
            bool rejected=false;try{(void)BalancePreset::load(badFile,"fixture-content");}catch(const std::exception&){rejected=true;}
            check(rejected,"invalid/unsupported configuration rejected");
            check(BalancePreset::load(file,"fixture-content").playerSpeed==.8f,"failed load preserves prior exported file");
        }
        auto nan=custom;nan.playerSpeed=std::numeric_limits<float>::quiet_NaN();
        bool rejected=false;try{nan.save(file);}catch(const std::exception&){rejected=true;}
        check(rejected&&BalancePreset::load(file,"fixture-content").playerSpeed==.8f,"invalid export cannot replace existing preset");
        const auto blocked=dir/"directory.json";std::filesystem::create_directory(blocked);
        rejected=false;try{custom.save(blocked);}catch(const std::exception&){rejected=true;}
        check(rejected&&std::filesystem::is_directory(blocked),"failed atomic replacement preserves destination");
        for(const auto &entry:std::filesystem::directory_iterator(dir))
            check(entry.path().filename().string().find(".tmp-")==std::string::npos,"failed export removes its temporary file");
        std::filesystem::remove_all(dir);
        std::cout<<"PASS preset round-trip, schema migrations and rejection cases, invalid-export protection and atomic replacement failure\n";
        return 0;
    } catch(const std::exception &e){std::cerr<<e.what()<<'\n';std::filesystem::remove_all(dir);return 1;}
}
