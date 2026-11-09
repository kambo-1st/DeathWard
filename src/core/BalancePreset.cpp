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
constexpr const char *Contract = "d01-speed-v1";
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
    if(!std::isfinite(playerSpeed)||playerSpeed<MinSpeed||playerSpeed>MaxSpeed)
        throw std::runtime_error("Speed must be between 0.10 and 2.00");
    if(mechanicsFingerprint.empty()||mechanicsFingerprint.size()>128)
        throw std::runtime_error("Preset needs a mechanics fingerprint");
}
std::string BalancePreset::json() const {
    validate();std::ostringstream out;out.imbue(std::locale::classic());out<<std::setprecision(9);
    out<<"{\n  \"format\": \"deathward.balance\",\n  \"schema_version\": 1,\n"
       <<"  \"compatibility\": {\"contract\": "<<quoted(Contract)<<", \"content_version\": "<<quoted(ContentVersion)
       <<", \"mechanics_fingerprint\": "<<quoted(mechanicsFingerprint)<<"},\n"
       <<"  \"reference\": {\"source\": "<<quoted(Source)<<", \"executable_sha256\": "<<quoted(SourceHash)
       <<", \"coverage\": \"Speed configuration only; native balance pending\", \"player_speed\": 1, \"walking_pace_at_speed_one\": 4.8},\n"
       <<"  \"resolved\": {\"player_speed\": "<<numericText(playerSpeed)<<"},\n  \"overrides\": {";
    if(custom())out<<"\"player_speed\": "<<numericText(playerSpeed);
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
    if(root.at("schema_version").numeric()!=1)throw std::runtime_error("Unsupported balance preset schema");
    const auto &compat=root.at("compatibility");compat.keys({"contract","content_version","mechanics_fingerprint"});
    compat.at("contract").equal(Contract);compat.at("content_version").equal(ContentVersion);
    compat.at("mechanics_fingerprint").equal(fingerprint.c_str());
    const auto &ref=root.at("reference");ref.keys({"source","executable_sha256","coverage","player_speed","walking_pace_at_speed_one"});
    ref.at("source").equal(Source);ref.at("executable_sha256").equal(SourceHash);
    ref.at("coverage").equal("Speed configuration only; native balance pending");
    if(ref.at("player_speed").numeric()!=1||ref.at("walking_pace_at_speed_one").numeric()!=4.8)
        throw std::runtime_error("Reference values cannot be overridden; edit resolved and overrides");
    const auto &resolved=root.at("resolved");resolved.keys({"player_speed"});
    const double speed=resolved.at("player_speed").numeric();
    if(speed<.1||speed>2)throw std::runtime_error("Speed must be between 0.10 and 2.00");
    const auto &overrides=root.at("overrides");
    if(speed==1)overrides.keys({});
    else {overrides.keys({"player_speed"});if(overrides.at("player_speed").numeric()!=speed)throw std::runtime_error("Resolved Speed and override disagree");}
    const auto &exceptions=root.at("exceptions");exceptions.keys({"isometric","eight_direction_controls","universal_dodge","immediate_stopping"});
    for(const auto &[name,entry]:exceptions.fields)
        if(entry.kind!=Json::Boolean||!entry.flag)throw std::runtime_error("Retained control exception cannot change: "+name);
    BalancePreset preset{float(speed),fingerprint};preset.validate();return preset;
}
} // namespace dw
