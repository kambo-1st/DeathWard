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
constexpr const char *Contract = "d02-view-v4";
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
    out<<"{\n  \"format\": \"deathward.balance\",\n  \"schema_version\": 4,\n"
       <<"  \"compatibility\": {\"contract\": "<<quoted(Contract)<<", \"content_version\": "<<quoted(ContentVersion)
       <<", \"mechanics_fingerprint\": "<<quoted(mechanicsFingerprint)<<"},\n"
       <<"  \"reference\": {\"source\": "<<quoted(Source)<<", \"executable_sha256\": "<<quoted(SourceHash)
       <<", \"coverage\": \"Speed, map and camera configuration; native balance pending\", \"player_speed\": 1, \"walking_pace_at_speed_one\": 4.8, \"room_size_scale\": 1, \"room_size_baseline\": \"larger-compact-v1\", \"route_length_scale\": 1, \"default_zoom_percent\": 160},\n"
       <<"  \"resolved\": {\"player_speed\": "<<numericText(playerSpeed)<<", \"room_size_scale\": "<<numericText(roomSizeScale)<<", \"room_min_half_tiles\": "<<roomMinHalfTiles<<", \"room_max_half_tiles\": "<<roomMaxHalfTiles<<", \"route_length_scale\": "<<numericText(routeLengthScale)<<", \"default_zoom_percent\": "<<numericText(defaultZoomPercent)<<"},\n  \"overrides\": {";
    if(playerSpeed!=1)out<<"\"player_speed\": "<<numericText(playerSpeed);
    if(roomSizeScale!=1)out<<(playerSpeed!=1?", ":"")<<"\"room_size_scale\": "<<numericText(roomSizeScale);
    if(roomMinHalfTiles)out<<(playerSpeed!=1||roomSizeScale!=1?", ":"")<<"\"room_min_half_tiles\": "<<roomMinHalfTiles<<", \"room_max_half_tiles\": "<<roomMaxHalfTiles;
    if(routeLengthScale!=1)out<<(playerSpeed!=1||roomSizeScale!=1||roomMinHalfTiles?", ":"")<<"\"route_length_scale\": "<<numericText(routeLengthScale);
    if(defaultZoomPercent!=ReferenceZoom)out<<(playerSpeed!=1||roomSizeScale!=1||roomMinHalfTiles||routeLengthScale!=1?", ":"")<<"\"default_zoom_percent\": "<<numericText(defaultZoomPercent);
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
    if(version!=1&&version!=2&&version!=3&&version!=4)throw std::runtime_error("Unsupported balance preset schema");
    const bool legacy=version==1;
    const auto &compat=root.at("compatibility");compat.keys({"contract","content_version","mechanics_fingerprint"});
    compat.at("contract").equal(legacy?"d01-speed-v1":version==2?"d02-room-size-v2":version==3?"d02-map-v3":Contract);compat.at("content_version").equal(ContentVersion);
    compat.at("mechanics_fingerprint").equal(fingerprint.c_str());
    const auto &ref=root.at("reference");
    if(legacy)ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one"});
    else {
        if(version==2)ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one","room_size_scale","room_size_baseline"});
        else {
            if(version==3)ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one","room_size_scale","room_size_baseline","route_length_scale"});
            else {ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one","room_size_scale","room_size_baseline","route_length_scale","default_zoom_percent"});
                if(ref.at("default_zoom_percent").numeric()!=ReferenceZoom)throw std::runtime_error("Reference zoom cannot be overridden");}
            if(ref.at("route_length_scale").numeric()!=1)throw std::runtime_error("Reference route length cannot be overridden");}
        ref.at("room_size_baseline").equal("larger-compact-v1");
        if(ref.at("room_size_scale").numeric()!=1)throw std::runtime_error("Reference room size cannot be overridden");}
    ref.at("source").equal(Source);ref.at("executable_sha256").equal(SourceHash);
    ref.at("coverage").equal(legacy?"Speed configuration only; native balance pending":version==2?"Speed and room-size configuration; native balance pending":version==3?"Speed and map configuration; native balance pending":"Speed, map and camera configuration; native balance pending");
    if(ref.at("player_speed").numeric()!=1||ref.at("walking_pace_at_speed_one").numeric()!=4.8)
        throw std::runtime_error("Reference values cannot be overridden; edit resolved and overrides");
    const auto &resolved=root.at("resolved");
    if(legacy)resolved.keys({"player_speed"});
    else if(version==2)resolved.keys({"player_speed","room_size_scale","room_min_half_tiles","room_max_half_tiles"});
    else if(version==3)resolved.keys({"player_speed","room_size_scale","room_min_half_tiles","room_max_half_tiles","route_length_scale"});
    else resolved.keys({"player_speed","room_size_scale","room_min_half_tiles","room_max_half_tiles","route_length_scale","default_zoom_percent"});
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
    if(overrides.kind!=Json::Object||overrides.fields.size()!=size_t((speed!=1)+(!legacy&&roomScale!=1)+(minimum!=0?2:0)+(routeScale!=1)+(zoom!=ReferenceZoom)))
        throw std::runtime_error("Unexpected preset overrides");
    if(speed!=1&&overrides.at("player_speed").numeric()!=speed)throw std::runtime_error("Resolved Speed and override disagree");
    if(!legacy&&roomScale!=1&&overrides.at("room_size_scale").numeric()!=roomScale)throw std::runtime_error("Resolved room size and override disagree");
    if(minimum!=0&&(overrides.at("room_min_half_tiles").numeric()!=minimum||overrides.at("room_max_half_tiles").numeric()!=maximum))
        throw std::runtime_error("Resolved room range and overrides disagree");
    if(routeScale!=1&&overrides.at("route_length_scale").numeric()!=routeScale)
        throw std::runtime_error("Resolved route length and override disagree");
    if(zoom!=ReferenceZoom&&overrides.at("default_zoom_percent").numeric()!=zoom)
        throw std::runtime_error("Resolved default zoom and override disagree");
    const auto &exceptions=root.at("exceptions");exceptions.keys({"isometric","eight_direction_controls","universal_dodge","immediate_stopping"});
    for(const auto &[name,entry]:exceptions.fields)
        if(entry.kind!=Json::Boolean||!entry.flag)throw std::runtime_error("Retained control exception cannot change: "+name);
    BalancePreset preset{float(speed),fingerprint,float(roomScale),int(minimum),int(maximum),float(routeScale),float(zoom)};preset.validate();return preset;
}
} // namespace dw
