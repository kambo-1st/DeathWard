#include "core/BalancePreset.hpp"
#include "core/Types.hpp"
#include "platform/Browser.hpp"
#include <charconv>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <locale>
#include <map>
#include <sstream>
#include <stdexcept>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOGDI
#define NOUSER
#include <windows.h>
#endif

namespace dw {
namespace {
constexpr const char *Contract = "d09a-room-selection-v14";
constexpr const char *Source = "The Binding of Isaac: Repentance 1.7.9b";
constexpr const char *SourceHash = "04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6";
// Deliberately bounded JSON for this schema (objects, strings, finite numbers,
// booleans). Arrays/null are not part of the configuration contract.
struct Json {
    enum Kind { Object, String, Number, Boolean } kind = Object;
    std::map<std::string, Json> fields;
    std::string text;
    double number = 0;
    bool flag = false;
    const Json &at(const std::string &key) const {
        if (kind != Object || !fields.contains(key)) throw std::runtime_error("Missing preset field: " + key);
        return fields.at(key);
    }
    void keys(std::initializer_list<const char *> expected) const {
        if (kind != Object || fields.size() != expected.size()) throw std::runtime_error("Unexpected preset fields");
        for (const auto key : expected) (void)at(key);
    }
    void equal(const char *value) const {
        if (kind != String || text != value) throw std::runtime_error("Incompatible preset: expected " + std::string(value));
    }
    double numeric() const {
        if (kind != Number) throw std::runtime_error("Preset value must be a number");
        return number;
    }
};
class Parser {
    std::string data;
    size_t pos = 0;
    [[noreturn]] void fail() const { throw std::runtime_error("Invalid preset JSON near byte " + std::to_string(pos)); }
    void space() { while(pos<data.size() && (data[pos]==' '||data[pos]=='\n'||data[pos]=='\r'||data[pos]=='\t')) ++pos; }
    bool take(char c) { space();if(pos<data.size()&&data[pos]==c){++pos;return true;}return false; }
    std::string string() {
        if(!take('"'))fail();
        std::string result;
        while(pos<data.size()) {
            unsigned char c=data[pos++];
            if(c=='"')return result;
            if(c<32)fail();
            if(c=='\\') {
                if(pos>=data.size())fail();
                c=data[pos++];
                switch(c) {
                case '"':case '\\':case '/':result+=char(c);break;
                case 'b':result+='\b';break;case 'f':result+='\f';break;
                case 'n':result+='\n';break;case 'r':result+='\r';break;case 't':result+='\t';break;
                case 'u': {
                    // All schema strings are ASCII. Escaped ASCII is accepted;
                    // non-ASCII schema identifiers cannot be compatible here.
                    unsigned code=0;
                    for(int i=0;i<4;++i) {
                        if(pos>=data.size())fail();
                        const char h=data[pos++];
                        if(h>='0'&&h<='9')code=code*16+h-'0';
                        else if(h>='a'&&h<='f')code=code*16+h-'a'+10;
                        else if(h>='A'&&h<='F')code=code*16+h-'A'+10;
                        else fail();
                    }
                    if(code>127)fail();
                    result+=char(code);break;
                }
                default:fail();
                }
            } else result+=char(c);
        }
        fail();
    }
    Json value(int depth) {
        if(depth>12)fail();
        space();Json j;
        if(take('{')) {
            if(take('}'))return j;
            do {
                auto key=string();if(!take(':'))fail();auto child=value(depth+1);
                if(!j.fields.emplace(std::move(key),std::move(child)).second)fail();
                if(take('}'))return j;
            } while(take(','));
            fail();
        }
        if(pos<data.size()&&data[pos]=='"'){j.kind=Json::String;j.text=string();return j;}
        for(const auto &literal: {std::string("true"),std::string("false")})
            if(data.compare(pos,literal.size(),literal)==0){pos+=literal.size();j.kind=Json::Boolean;j.flag=literal=="true";return j;}
        const auto begin=pos;
        if(pos<data.size()&&data[pos]=='-')++pos;
        if(pos>=data.size())fail();
        if(data[pos]=='0')++pos;
        else {if(data[pos]<'1'||data[pos]>'9')fail();while(pos<data.size()&&data[pos]>='0'&&data[pos]<='9')++pos;}
        if(pos<data.size()&&data[pos]=='.') {
            ++pos;const auto first=pos;while(pos<data.size()&&data[pos]>='0'&&data[pos]<='9')++pos;if(pos==first)fail();
        }
        if(pos<data.size()&&(data[pos]=='e'||data[pos]=='E')) {
            ++pos;if(pos<data.size()&&(data[pos]=='+'||data[pos]=='-'))++pos;
            const auto first=pos;while(pos<data.size()&&data[pos]>='0'&&data[pos]<='9')++pos;if(pos==first)fail();
        }
        j.kind=Json::Number;
        auto parsed=std::from_chars(data.data()+begin,data.data()+pos,j.number);
        if(parsed.ec!=std::errc{}||parsed.ptr!=data.data()+pos||!std::isfinite(j.number))fail();
        return j;
    }
public:
    explicit Parser(std::string input):data(std::move(input)){}
    Json parse(){auto result=value(0);space();if(pos!=data.size())fail();return result;}
};
std::string quoted(const std::string &s) {
    std::string out="\"";
    for(unsigned char c:s) {
        if(c=='"'||c=='\\'){out+='\\';out+=char(c);}
        else if(c<32)throw std::runtime_error("Invalid preset metadata");
        else out+=char(c);
    }
    return out+'"';
}
std::string numericText(float value) {
    char buffer[64];const auto result=std::to_chars(buffer,buffer+sizeof(buffer),value);
    if(result.ec!=std::errc{})throw std::runtime_error("Could not serialize preset value");
    return {buffer,result.ptr};
}
}
void BalancePreset::validate() const {
    if(roomHeartLayouts<0||roomHeartLayouts>2)throw std::runtime_error("Room heart layouts must be off, source pool or full/half test");
    if(!std::isfinite(redHeartAppearanceSpeed)||redHeartAppearanceSpeed<MinHeartAppearanceSpeed||redHeartAppearanceSpeed>MaxHeartAppearanceSpeed)
        throw std::runtime_error("Heart appearance speed must be between 25% and 400%");
    if(!std::isfinite(playerLuck)||playerLuck<MinLuck||playerLuck>MaxLuck)throw std::runtime_error("Luck must be between -3 and 20");
    if(!std::isfinite(playerDamage)||playerDamage<MinDamage||playerDamage>MaxDamage||
       !std::isfinite(regularHealthMultiplier)||regularHealthMultiplier<MinRegularHealth||regularHealthMultiplier>MaxRegularHealth)
        throw std::runtime_error("Damage must be 0.1-50; regular enemy HP must be 5-400%");
    if(!std::isfinite(pooterMovementMultiplier)||pooterMovementMultiplier<MinPooterMovement||pooterMovementMultiplier>MaxPooterMovement||
       !std::isfinite(pooterShotSpeedMultiplier)||pooterShotSpeedMultiplier<MinPooterShotSpeed||pooterShotSpeedMultiplier>MaxPooterShotSpeed||
       !std::isfinite(pooterAttackIntervalMultiplier)||pooterAttackIntervalMultiplier<MinPooterInterval||pooterAttackIntervalMultiplier>MaxPooterInterval)
        throw std::runtime_error("Pooter movement/shot speed must be 10-200%, attack delay 25-200%");
    if(!std::isfinite(spiderMovementMultiplier)||spiderMovementMultiplier<MinSpiderMovement||spiderMovementMultiplier>MaxSpiderMovement)
        throw std::runtime_error("Spider movement must be between 10% and 200%");
    if(!std::isfinite(gaperMovementMultiplier)||gaperMovementMultiplier<MinGaperMovement||gaperMovementMultiplier>MaxGaperMovement)
        throw std::runtime_error("Gaper movement must be between 10% and 200%");
    if(!std::isfinite(tearsPerSecond)||tearsPerSecond<MinTears||tearsPerSecond>MaxTears)
        throw std::runtime_error("Tears must be between 0.10 and 10.00 shots per second");
    if(!std::isfinite(shotSpeed)||shotSpeed<MinShotSpeed||shotSpeed>MaxShotSpeed)
        throw std::runtime_error("Shot Speed must be between 0.10 and 3.00");
    if(!std::isfinite(rangeTiles)||rangeTiles<MinRange||rangeTiles>MaxRange)
        throw std::runtime_error("Range must be between 0.50 and 20.00 tiles");
    if(!std::isfinite(defaultZoomPercent)||defaultZoomPercent<MinZoom||defaultZoomPercent>MaxZoom)
        throw std::runtime_error("Default zoom must be between 67% and 285%");
    if(!std::isfinite(playerSpeed)||playerSpeed<MinSpeed||playerSpeed>MaxSpeed)
        throw std::runtime_error("Speed must be between 0.10 and 2.00");
    if(!std::isfinite(routeLengthScale)||routeLengthScale<.25f||routeLengthScale>2)
        throw std::runtime_error("Route length must be between 25% and 200%");
    if(!std::isfinite(roomSizeScale)||roomSizeScale<.75f||roomSizeScale>1.5f)
        throw std::runtime_error("Room size must be between 75% and 150%");
    if((roomMinHalfTiles||roomMaxHalfTiles)&&(roomMinHalfTiles<5||roomMaxHalfTiles<roomMinHalfTiles||roomMaxHalfTiles>10))
        throw std::runtime_error("Room range must be 10-20 tiles, minimum no larger than maximum");
    if(mechanicsFingerprint.empty()||mechanicsFingerprint.size()>128)
        throw std::runtime_error("Preset needs a mechanics fingerprint");
}
std::string BalancePreset::json() const {
    validate();std::ostringstream out;out.imbue(std::locale::classic());out<<std::setprecision(9);
    out<<"{\n  \"format\": \"deathward.balance\",\n  \"schema_version\": 14,\n"
       <<"  \"compatibility\": {\"contract\": "<<quoted(Contract)<<", \"content_version\": "<<quoted(ContentVersion)
       <<", \"mechanics_fingerprint\": "<<quoted(mechanicsFingerprint)<<"},\n"
       <<"  \"reference\": {\"source\": "<<quoted(Source)<<", \"executable_sha256\": "<<quoted(SourceHash)
       <<", \"coverage\": \"Player, combat, enemy, map and camera configuration; native balance pending\", \"player_speed\": 1, \"walking_pace_at_speed_one\": 4.8, \"room_size_scale\": 1, \"room_size_baseline\": \"larger-compact-v1\", \"route_length_scale\": 1, \"default_zoom_percent\": 160, \"tears_per_second\": "<<numericText(ReferenceTears)<<", \"shot_speed\": 1, \"range_tiles\": 6.5, \"shooting_calibration\": \"accepted-independent-v1\", \"gaper_movement_multiplier\": 1, \"gaper_calibration\": \"player-relative-v1\", \"spider_movement_multiplier\": 1, \"spider_calibration\": \"player-relative-burst-v1\", \"pooter_movement_multiplier\": 1, \"pooter_shot_speed_multiplier\": 1, \"pooter_attack_interval_multiplier\": 1, \"pooter_calibration\": \"player-relative-mode0-v1\", \"player_damage\": 3.5, \"regular_health_multiplier\": 1, \"damage_calibration\": \"source-damage-internal-hp-v1\", \"health_units_per_source\": 3.2, \"combat_room_template\": \"basement-1.47.0-canyon-v1\", \"red_heart_reward_policy\": \"ordinary-normal-rare-gates-off-v1\", \"player_luck\": 0, \"red_heart_timing\": \"appear33-drop25-collect12-30hz-v1\", \"red_heart_appearance_speed\": 1, \"room_heart_layout_policy\": \"basement-normal-1to5-native-selector-v2\", \"room_heart_layouts\": 1},\n"
       <<"  \"resolved\": {\"player_speed\": "<<numericText(playerSpeed)<<", \"room_size_scale\": "<<numericText(roomSizeScale)<<", \"room_min_half_tiles\": "<<roomMinHalfTiles<<", \"room_max_half_tiles\": "<<roomMaxHalfTiles<<", \"route_length_scale\": "<<numericText(routeLengthScale)<<", \"default_zoom_percent\": "<<numericText(defaultZoomPercent)<<", \"tears_per_second\": "<<numericText(tearsPerSecond)<<", \"shot_speed\": "<<numericText(shotSpeed)<<", \"range_tiles\": "<<numericText(rangeTiles)<<", \"gaper_movement_multiplier\": "<<numericText(gaperMovementMultiplier)<<", \"spider_movement_multiplier\": "<<numericText(spiderMovementMultiplier)<<", \"pooter_movement_multiplier\": "<<numericText(pooterMovementMultiplier)<<", \"pooter_shot_speed_multiplier\": "<<numericText(pooterShotSpeedMultiplier)<<", \"pooter_attack_interval_multiplier\": "<<numericText(pooterAttackIntervalMultiplier)<<", \"player_damage\": "<<numericText(playerDamage)<<", \"regular_health_multiplier\": "<<numericText(regularHealthMultiplier)<<", \"source_combat_room\": "<<(sourceCombatRoom?"true":"false")<<", \"red_heart_clear_rewards\": "<<(redHeartClearRewards?"true":"false")<<", \"player_luck\": "<<numericText(playerLuck)<<", \"red_heart_appearance_speed\": "<<numericText(redHeartAppearanceSpeed)<<", \"room_heart_layouts\": "<<roomHeartLayouts<<"},\n  \"overrides\": {";
    bool comma=false;
    const auto field=[&](const char *key,float value){out<<(comma?", ":"")<<quoted(key)<<": "<<numericText(value);comma=true;};
    if(!redHeartClearRewards){out<<"\"red_heart_clear_rewards\": false";comma=true;}
    if(roomHeartLayouts!=1)field("room_heart_layouts",roomHeartLayouts);
    if(redHeartAppearanceSpeed!=1)field("red_heart_appearance_speed",redHeartAppearanceSpeed);
    if(playerLuck!=ReferenceLuck)field("player_luck",playerLuck);
    if(!sourceCombatRoom){out<<(comma?", ":"")<<"\"source_combat_room\": false";comma=true;}
    if(playerDamage!=ReferenceDamage)field("player_damage",playerDamage);
    if(regularHealthMultiplier!=1)field("regular_health_multiplier",regularHealthMultiplier);
    if(playerSpeed!=1)field("player_speed",playerSpeed);
    if(roomSizeScale!=1)field("room_size_scale",roomSizeScale);
    if(roomMinHalfTiles){field("room_min_half_tiles",float(roomMinHalfTiles));field("room_max_half_tiles",float(roomMaxHalfTiles));}
    if(routeLengthScale!=1)field("route_length_scale",routeLengthScale);
    if(defaultZoomPercent!=ReferenceZoom)field("default_zoom_percent",defaultZoomPercent);
    if(tearsPerSecond!=ReferenceTears)field("tears_per_second",tearsPerSecond);
    if(shotSpeed!=ReferenceShotSpeed)field("shot_speed",shotSpeed);
    if(rangeTiles!=ReferenceRange)field("range_tiles",rangeTiles);
    if(gaperMovementMultiplier!=ReferenceGaperMovement)field("gaper_movement_multiplier",gaperMovementMultiplier);
    if(spiderMovementMultiplier!=ReferenceSpiderMovement)field("spider_movement_multiplier",spiderMovementMultiplier);
    if(pooterMovementMultiplier!=1)field("pooter_movement_multiplier",pooterMovementMultiplier);
    if(pooterShotSpeedMultiplier!=1)field("pooter_shot_speed_multiplier",pooterShotSpeedMultiplier);
    if(pooterAttackIntervalMultiplier!=1)field("pooter_attack_interval_multiplier",pooterAttackIntervalMultiplier);
    out<<"},\n  \"exceptions\": {\"isometric\": true, \"eight_direction_controls\": true, \"universal_dodge\": true, \"immediate_stopping\": true}\n}\n";
    return out.str();
}
std::string BalancePreset::revision() const {
    uint64_t hash=14695981039346656037ULL;
    for(unsigned char c:json()){hash^=c;hash*=1099511628211ULL;}
    std::ostringstream out;out<<std::hex<<std::setw(16)<<std::setfill('0')<<hash;return out.str();
}
void BalancePreset::save(const std::filesystem::path &path) const {
    const auto bytes=json();
    if(path.empty())throw std::runtime_error("Choose a preset file");
    if(!path.parent_path().empty())std::filesystem::create_directories(path.parent_path());
    auto temporary=path;temporary+=".tmp-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());
    try {
        std::ofstream out(temporary,std::ios::binary|std::ios::trunc);
        out.write(bytes.data(),std::streamsize(bytes.size()));out.close();
        if(!out)throw std::runtime_error("Could not write preset: "+path.string());
#ifdef _WIN32
        if(!MoveFileExW(temporary.c_str(),path.c_str(),MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH))
            throw std::runtime_error("Could not replace preset: "+path.string());
#else
        std::filesystem::rename(temporary,path);
#endif
        persistBrowserFiles();
    } catch(...) {std::error_code ignored;std::filesystem::remove(temporary,ignored);throw;}
}
BalancePreset BalancePreset::load(const std::filesystem::path &path,const std::string &fingerprint) {
    std::ifstream in(path,std::ios::binary);
    if(!in)throw std::runtime_error("Could not open preset: "+path.string());
    std::string bytes(65537,'\0');in.read(bytes.data(),std::streamsize(bytes.size()));bytes.resize(size_t(in.gcount()));
    if(bytes.size()>65536||in.bad())throw std::runtime_error("Preset unreadable or larger than 64 KiB");
    auto root=Parser(std::move(bytes)).parse();
    root.keys({"format","schema_version","compatibility","reference","resolved","overrides","exceptions"});
    root.at("format").equal("deathward.balance");
    const auto version=root.at("schema_version").numeric();
    if(version!=1&&version!=2&&version!=3&&version!=4&&version!=5&&version!=6&&version!=7&&version!=8&&version!=9&&version!=10&&version!=11&&version!=12&&version!=13&&version!=14)throw std::runtime_error("Unsupported balance preset schema");
    const bool legacy=version==1;
    const auto &compat=root.at("compatibility");compat.keys({"contract","content_version","mechanics_fingerprint"});
    compat.at("contract").equal(legacy?"d01-speed-v1":version==2?"d02-room-size-v2":version==3?"d02-map-v3":version==4?"d02-view-v4":version==5?"d03-shooting-v5":version==6?"d04-gaper-v6":version==7?"d05-spider-v7":version==8?"d06-pooter-v8":version==9?"d07-combat-v9":version==10?"d08-source-room-v10":version==11?"d09a-red-hearts-v11":version==12?"d09a-heart-timing-v12":version==13?"d09a-room-hearts-v13":Contract);compat.at("content_version").equal(ContentVersion);
    compat.at("mechanics_fingerprint").equal(fingerprint.c_str());
    auto ref=root.at("reference");
    if(version>=13) {
        ref.at("room_heart_layout_policy").equal(version==13?"basement-normal-1to5-heart-layer-v1":"basement-normal-1to5-native-selector-v2");
        if(ref.at("room_heart_layouts").numeric()!=1)throw std::runtime_error("Reference room-heart policy cannot change");
        ref.fields.erase("room_heart_layout_policy");ref.fields.erase("room_heart_layouts");
    }
    if(version>=12) {
        ref.at("red_heart_timing").equal("appear33-drop25-collect12-30hz-v1");
        if(ref.at("red_heart_appearance_speed").numeric()!=1)throw std::runtime_error("Reference heart appearance speed cannot change");
        ref.fields.erase("red_heart_timing");ref.fields.erase("red_heart_appearance_speed");
    }
    if(version>=11) {
        ref.at("red_heart_reward_policy").equal("ordinary-normal-rare-gates-off-v1");
        if(ref.at("player_luck").numeric()!=ReferenceLuck)throw std::runtime_error("Reference Luck cannot change");
        ref.fields.erase("red_heart_reward_policy");ref.fields.erase("player_luck");
    }
    if(version>=10) {
        ref.at("combat_room_template").equal("basement-1.47.0-canyon-v1");
        ref.fields.erase("combat_room_template");
    }
    if(legacy)ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one"});
    else {
        if(version==2)ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one","room_size_scale","room_size_baseline"});
        else {
            if(version==3)ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one","room_size_scale","room_size_baseline","route_length_scale"});
            else {
                if(version==4)ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one","room_size_scale","room_size_baseline","route_length_scale","default_zoom_percent"});
                else {
                    if(version==5)ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one","room_size_scale","room_size_baseline","route_length_scale","default_zoom_percent","tears_per_second","shot_speed","range_tiles","shooting_calibration"});
                    else if(version==6)ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one","room_size_scale","room_size_baseline","route_length_scale","default_zoom_percent","tears_per_second","shot_speed","range_tiles","shooting_calibration","gaper_movement_multiplier","gaper_calibration"});
                    else if(version==7)ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one","room_size_scale","room_size_baseline","route_length_scale","default_zoom_percent","tears_per_second","shot_speed","range_tiles","shooting_calibration","gaper_movement_multiplier","gaper_calibration","spider_movement_multiplier","spider_calibration"});
                    else if(version==8)ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one","room_size_scale","room_size_baseline","route_length_scale","default_zoom_percent","tears_per_second","shot_speed","range_tiles","shooting_calibration","gaper_movement_multiplier","gaper_calibration","spider_movement_multiplier","spider_calibration","pooter_movement_multiplier","pooter_shot_speed_multiplier","pooter_attack_interval_multiplier","pooter_calibration"});
                    else ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one","room_size_scale","room_size_baseline","route_length_scale","default_zoom_percent","tears_per_second","shot_speed","range_tiles","shooting_calibration","gaper_movement_multiplier","gaper_calibration","spider_movement_multiplier","spider_calibration","pooter_movement_multiplier","pooter_shot_speed_multiplier","pooter_attack_interval_multiplier","pooter_calibration","player_damage","regular_health_multiplier","damage_calibration","health_units_per_source"});
                    if(version>=6) {
                        ref.at("gaper_calibration").equal("player-relative-v1");
                        if(ref.at("gaper_movement_multiplier").numeric()!=ReferenceGaperMovement)throw std::runtime_error("Reference Gaper movement cannot be overridden");
                    }
                    if(version>=7) {
                        ref.at("spider_calibration").equal("player-relative-burst-v1");
                        if(ref.at("spider_movement_multiplier").numeric()!=ReferenceSpiderMovement)throw std::runtime_error("Reference Spider movement cannot be overridden");
                    }
                    if(version>=8) {
                        ref.at("pooter_calibration").equal("player-relative-mode0-v1");
                        for(const auto key:{"pooter_movement_multiplier","pooter_shot_speed_multiplier","pooter_attack_interval_multiplier"})
                            if(ref.at(key).numeric()!=1)throw std::runtime_error("Reference Pooter values cannot be overridden");
                    }
                    ref.at("shooting_calibration").equal("accepted-independent-v1");
                    if(float(ref.at("tears_per_second").numeric())!=ReferenceTears||ref.at("shot_speed").numeric()!=ReferenceShotSpeed||ref.at("range_tiles").numeric()!=ReferenceRange)
                        throw std::runtime_error("Reference shooting values cannot be overridden");
                }
                if(ref.at("default_zoom_percent").numeric()!=ReferenceZoom)throw std::runtime_error("Reference zoom cannot be overridden");}
            if(ref.at("route_length_scale").numeric()!=1)throw std::runtime_error("Reference route length cannot be overridden");}
        ref.at("room_size_baseline").equal("larger-compact-v1");
        if(ref.at("room_size_scale").numeric()!=1)throw std::runtime_error("Reference room size cannot be overridden");}
    if(version>=9) {
        ref.at("damage_calibration").equal("source-damage-internal-hp-v1");
        if(ref.at("player_damage").numeric()!=ReferenceDamage||ref.at("regular_health_multiplier").numeric()!=1||ref.at("health_units_per_source").numeric()!=3.2)
            throw std::runtime_error("Reference damage/HP values cannot be overridden");
    }
    ref.at("source").equal(Source);ref.at("executable_sha256").equal(SourceHash);
    ref.at("coverage").equal(legacy?"Speed configuration only; native balance pending":version==2?"Speed and room-size configuration; native balance pending":version==3?"Speed and map configuration; native balance pending":version==4?"Speed, map and camera configuration; native balance pending":version==5?"Player, shooting, map and camera configuration; native balance pending":version==6?"Player, shooting, Gaper, map and camera configuration; native balance pending":version==7?"Player, shooting, Gaper, Spider, map and camera configuration; native balance pending":version==8?"Player, shooting, Gaper, Spider, Pooter, map and camera configuration; native balance pending":"Player, combat, enemy, map and camera configuration; native balance pending");
    if(ref.at("player_speed").numeric()!=1||ref.at("walking_pace_at_speed_one").numeric()!=4.8)
        throw std::runtime_error("Reference values cannot be overridden; edit resolved and overrides");
    auto resolved=root.at("resolved");
    double heartLayouts=1;
    if(version>=13) {
        heartLayouts=resolved.at("room_heart_layouts").numeric();
        if(heartLayouts<0||heartLayouts>2||std::floor(heartLayouts)!=heartLayouts)throw std::runtime_error("Invalid room-heart layout mode");
        resolved.fields.erase("room_heart_layouts");
    }
    double heartAppearanceSpeed=1;
    if(version>=12) {
        heartAppearanceSpeed=resolved.at("red_heart_appearance_speed").numeric();
        if(heartAppearanceSpeed<MinHeartAppearanceSpeed||heartAppearanceSpeed>MaxHeartAppearanceSpeed)throw std::runtime_error("Heart appearance speed outside supported range");
        resolved.fields.erase("red_heart_appearance_speed");
    }
    bool heartRewards=true;double luck=ReferenceLuck;
    if(version>=11) {
        const auto &entry=resolved.at("red_heart_clear_rewards");
        if(entry.kind!=Json::Boolean)throw std::runtime_error("Red heart rewards must be boolean");
        heartRewards=entry.flag;luck=resolved.at("player_luck").numeric();
        if(luck<MinLuck||luck>MaxLuck)throw std::runtime_error("Luck outside supported range");
        resolved.fields.erase("red_heart_clear_rewards");resolved.fields.erase("player_luck");
    }
    bool sourceRoom=true;
    if(version>=10) {
        const auto &entry=resolved.at("source_combat_room");
        if(entry.kind!=Json::Boolean)throw std::runtime_error("Source combat room must be boolean");
        sourceRoom=entry.flag;resolved.fields.erase("source_combat_room");
    }
    if(legacy)resolved.keys({"player_speed"});
    else if(version==2)resolved.keys({"player_speed","room_size_scale","room_min_half_tiles","room_max_half_tiles"});
    else if(version==3)resolved.keys({"player_speed","room_size_scale","room_min_half_tiles","room_max_half_tiles","route_length_scale"});
    else if(version==4)resolved.keys({"player_speed","room_size_scale","room_min_half_tiles","room_max_half_tiles","route_length_scale","default_zoom_percent"});
    else if(version==5)resolved.keys({"player_speed","room_size_scale","room_min_half_tiles","room_max_half_tiles","route_length_scale","default_zoom_percent","tears_per_second","shot_speed","range_tiles"});
    else if(version==6)resolved.keys({"player_speed","room_size_scale","room_min_half_tiles","room_max_half_tiles","route_length_scale","default_zoom_percent","tears_per_second","shot_speed","range_tiles","gaper_movement_multiplier"});
    else if(version==7)resolved.keys({"player_speed","room_size_scale","room_min_half_tiles","room_max_half_tiles","route_length_scale","default_zoom_percent","tears_per_second","shot_speed","range_tiles","gaper_movement_multiplier","spider_movement_multiplier"});
    else if(version==8)resolved.keys({"player_speed","room_size_scale","room_min_half_tiles","room_max_half_tiles","route_length_scale","default_zoom_percent","tears_per_second","shot_speed","range_tiles","gaper_movement_multiplier","spider_movement_multiplier","pooter_movement_multiplier","pooter_shot_speed_multiplier","pooter_attack_interval_multiplier"});
    else resolved.keys({"player_speed","room_size_scale","room_min_half_tiles","room_max_half_tiles","route_length_scale","default_zoom_percent","tears_per_second","shot_speed","range_tiles","gaper_movement_multiplier","spider_movement_multiplier","pooter_movement_multiplier","pooter_shot_speed_multiplier","pooter_attack_interval_multiplier","player_damage","regular_health_multiplier"});
    const double damage=version<9?ReferenceDamage:resolved.at("player_damage").numeric();
    const double health=version<9?ReferenceRegularHealth:resolved.at("regular_health_multiplier").numeric();
    if(damage<.1||damage>MaxDamage||health<.05||health>MaxRegularHealth)throw std::runtime_error("Damage/HP outside supported ranges");
    const double pooterMove=version<8?1:resolved.at("pooter_movement_multiplier").numeric();
    const double pooterShot=version<8?1:resolved.at("pooter_shot_speed_multiplier").numeric();
    const double pooterInterval=version<8?1:resolved.at("pooter_attack_interval_multiplier").numeric();
    if(pooterMove<.1||pooterMove>2||pooterShot<.1||pooterShot>2||pooterInterval<.25||pooterInterval>2)
        throw std::runtime_error("Pooter tuning values outside supported ranges");
    const double spider=version<7?ReferenceSpiderMovement:resolved.at("spider_movement_multiplier").numeric();
    if(spider<.1||spider>MaxSpiderMovement)throw std::runtime_error("Spider movement must be between 10% and 200%");
    const double gaper=version<6?ReferenceGaperMovement:resolved.at("gaper_movement_multiplier").numeric();
    if(gaper<.1||gaper>MaxGaperMovement)throw std::runtime_error("Gaper movement must be between 10% and 200%");
    const double tears=version<5?ReferenceTears:resolved.at("tears_per_second").numeric();
    const double shotSpeed=version<5?ReferenceShotSpeed:resolved.at("shot_speed").numeric();
    const double range=version<5?ReferenceRange:resolved.at("range_tiles").numeric();
    if(tears<.1||tears>MaxTears||shotSpeed<.1||shotSpeed>MaxShotSpeed||range<MinRange||range>MaxRange)
        throw std::runtime_error("Shooting values outside the supported tuning ranges");
    // The nominal 30/11 rate is stored as a float. Its shortest JSON decimal
    // must classify as the same baseline, rather than a phantom override.
    const bool customTears=float(tears)!=ReferenceTears;
    const double zoom=version<4?ReferenceZoom:resolved.at("default_zoom_percent").numeric();
    if(zoom<MinZoom||zoom>MaxZoom)throw std::runtime_error("Default zoom must be between 67% and 285%");
    const double routeScale=version<3?1:resolved.at("route_length_scale").numeric();
    if(routeScale<.25||routeScale>2)throw std::runtime_error("Route length must be between 25% and 200%");
    const double minimum=legacy?0:resolved.at("room_min_half_tiles").numeric();
    const double maximum=legacy?0:resolved.at("room_max_half_tiles").numeric();
    if((minimum!=0||maximum!=0)&&(minimum<5||maximum<minimum||maximum>10||std::floor(minimum)!=minimum||std::floor(maximum)!=maximum))
        throw std::runtime_error("Invalid room-size range");
    const double roomScale=legacy?1:resolved.at("room_size_scale").numeric();
    if(roomScale<.75||roomScale>1.5)throw std::runtime_error("Room size must be between 75% and 150%");
    const double speed=resolved.at("player_speed").numeric();
    if(speed<.1||speed>2)throw std::runtime_error("Speed must be between 0.10 and 2.00");
    const auto &overrides=root.at("overrides");
    if(overrides.kind!=Json::Object||overrides.fields.size()!=size_t((speed!=1)+(!legacy&&roomScale!=1)+(minimum!=0?2:0)+(routeScale!=1)+(zoom!=ReferenceZoom)+customTears+(shotSpeed!=ReferenceShotSpeed)+(range!=ReferenceRange)+(gaper!=ReferenceGaperMovement)+(spider!=ReferenceSpiderMovement)+(pooterMove!=1)+(pooterShot!=1)+(pooterInterval!=1)+(damage!=ReferenceDamage)+(health!=1)+(!sourceRoom)+(!heartRewards)+(luck!=ReferenceLuck)+(heartAppearanceSpeed!=1)+(heartLayouts!=1)))
        throw std::runtime_error("Unexpected preset overrides");
    if(!heartRewards) {
        const auto &entry=overrides.at("red_heart_clear_rewards");
        if(entry.kind!=Json::Boolean||entry.flag)throw std::runtime_error("Red heart reward override disagrees");
    }
    if(heartLayouts!=1&&overrides.at("room_heart_layouts").numeric()!=heartLayouts)throw std::runtime_error("Room-heart layout override disagrees");
    if(heartAppearanceSpeed!=1&&overrides.at("red_heart_appearance_speed").numeric()!=heartAppearanceSpeed)throw std::runtime_error("Heart appearance speed override disagrees");
    if(luck!=ReferenceLuck&&overrides.at("player_luck").numeric()!=luck)throw std::runtime_error("Luck override disagrees");
    if(!sourceRoom) {
        const auto &entry=overrides.at("source_combat_room");
        if(entry.kind!=Json::Boolean||entry.flag)throw std::runtime_error("Source room override disagrees");
    }
    if(speed!=1&&overrides.at("player_speed").numeric()!=speed)throw std::runtime_error("Resolved Speed and override disagree");
    if(!legacy&&roomScale!=1&&overrides.at("room_size_scale").numeric()!=roomScale)throw std::runtime_error("Resolved room size and override disagree");
    if(minimum!=0&&(overrides.at("room_min_half_tiles").numeric()!=minimum||overrides.at("room_max_half_tiles").numeric()!=maximum))
        throw std::runtime_error("Resolved room range and overrides disagree");
    if(routeScale!=1&&overrides.at("route_length_scale").numeric()!=routeScale)
        throw std::runtime_error("Resolved route length and override disagree");
    if(zoom!=ReferenceZoom&&overrides.at("default_zoom_percent").numeric()!=zoom)
        throw std::runtime_error("Resolved default zoom and override disagree");
    if(customTears&&overrides.at("tears_per_second").numeric()!=tears)
        throw std::runtime_error("Resolved Tears and override disagree");
    if(shotSpeed!=ReferenceShotSpeed&&overrides.at("shot_speed").numeric()!=shotSpeed)
        throw std::runtime_error("Resolved Shot Speed and override disagree");
    if(range!=ReferenceRange&&overrides.at("range_tiles").numeric()!=range)
        throw std::runtime_error("Resolved Range and override disagree");
    if(gaper!=ReferenceGaperMovement&&overrides.at("gaper_movement_multiplier").numeric()!=gaper)
        throw std::runtime_error("Resolved Gaper movement and override disagree");
    if(spider!=ReferenceSpiderMovement&&overrides.at("spider_movement_multiplier").numeric()!=spider)
        throw std::runtime_error("Resolved Spider movement and override disagree");
    if(pooterMove!=1&&overrides.at("pooter_movement_multiplier").numeric()!=pooterMove)throw std::runtime_error("Pooter movement override disagrees");
    if(pooterShot!=1&&overrides.at("pooter_shot_speed_multiplier").numeric()!=pooterShot)throw std::runtime_error("Pooter shot speed override disagrees");
    if(pooterInterval!=1&&overrides.at("pooter_attack_interval_multiplier").numeric()!=pooterInterval)throw std::runtime_error("Pooter attack delay override disagrees");
    if(damage!=ReferenceDamage&&overrides.at("player_damage").numeric()!=damage)throw std::runtime_error("Damage override disagrees");
    if(health!=1&&overrides.at("regular_health_multiplier").numeric()!=health)throw std::runtime_error("HP override disagrees");
    const auto &exceptions=root.at("exceptions");exceptions.keys({"isometric","eight_direction_controls","universal_dodge","immediate_stopping"});
    for(const auto &[name,entry]:exceptions.fields)
        if(entry.kind!=Json::Boolean||!entry.flag)throw std::runtime_error("Retained control exception cannot change: "+name);
    BalancePreset preset{float(speed),fingerprint,float(roomScale),int(minimum),int(maximum),float(routeScale),float(zoom),float(tears),float(shotSpeed),float(range),float(gaper),float(spider),float(pooterMove),float(pooterShot),float(pooterInterval),float(damage),float(health),sourceRoom,heartRewards,float(luck),float(heartAppearanceSpeed),int(heartLayouts)};preset.validate();return preset;
}
} // namespace dw
