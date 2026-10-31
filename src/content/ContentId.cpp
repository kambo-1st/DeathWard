#include "content/ContentId.hpp"
#include <array>
#include <charconv>
#include <stdexcept>

namespace dw {
namespace {
constexpr std::array<std::string_view,5> kinds{"collectible","trinket","card","pill","internal"};
uint32_t number(std::string_view s) {
    uint32_t n=0;
    const auto [end,error]=std::from_chars(s.data(),s.data()+s.size(),n);
    if(s.empty()||error!=std::errc{}||end!=s.data()+s.size())throw std::invalid_argument("Invalid content ID number");
    return n;
}
}
std::optional<ItemId> ItemKey::legacy() const {
    if(package=="dw"&&kind==ItemKind::Collectible&&number<uint32_t(ItemId::Count))return ItemId(number);
    return std::nullopt;
}
std::string itemKeyText(const ItemKey &key) {
    return key.package+":"+std::string(kinds.at(size_t(key.kind)))+":"+std::to_string(key.number);
}
ItemKey parseItemKey(std::string_view s) {
    const auto a=s.find(':'),b=a==s.npos?s.npos:s.find(':',a+1);
    if(a==s.npos||b==s.npos||a==0||a>64)throw std::invalid_argument("Expected package:kind:number item ID");
    const auto package=s.substr(0,a),kind=s.substr(a+1,b-a-1);
    for(char ch:package)if(!((ch>='a'&&ch<='z')||(ch>='0'&&ch<='9')||ch=='_'||ch=='-'))
        throw std::invalid_argument("Invalid item package name");
    for(size_t i=0;i<kinds.size();++i)if(kind==kinds[i])return {std::string(package),ItemKind(i),number(s.substr(b+1))};
    throw std::invalid_argument("Unknown item ID kind");
}
std::string monsterIdText(MonsterId id) {
    return std::to_string(id.type)+"."+std::to_string(id.variant)+(id.subtype?"."+std::to_string(id.subtype):"");
}
MonsterId parseMonsterId(std::string_view s) {
    MonsterId id;int *fields[]{&id.type,&id.variant,&id.subtype};size_t start=0;
    for(int i=0;i<3;++i) {
        const auto end=s.find('.',start);const auto n=number(s.substr(start,end==s.npos?s.npos:end-start));
        if(n>2147483647u)throw std::invalid_argument("Monster ID component exceeds signed 32-bit range");
        *fields[i]=int(n);
        if(end==s.npos)return id;
        start=end+1;
    }
    throw std::invalid_argument("Too many monster ID components");
}
} // namespace dw
