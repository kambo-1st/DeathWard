#pragma once
#include <compare>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

namespace dw {
// These are convenient aliases for the original eleven powers, not the registry size.
enum class ItemId : int { Ricochet, Split, Judas, Powder, Ghost, Scatter, Rail, Lodestone, Return, Cap, Braid, Count };
enum class ItemKind { Collectible, Trinket, Card, Pill, Internal };
struct ItemKey {
    std::string package = "dw";
    ItemKind kind = ItemKind::Collectible;
    uint32_t number = 0;
    ItemKey() = default;
    ItemKey(ItemId legacy) : number(uint32_t(legacy)) {}
    ItemKey(std::string source, ItemKind category, uint32_t id)
        : package(std::move(source)), kind(category), number(id) {}
    auto operator<=>(const ItemKey &) const = default;
    std::optional<ItemId> legacy() const;
};
std::string itemKeyText(const ItemKey &key);
ItemKey parseItemKey(std::string_view text);

// Never pack decimal digits: 912.100.0 and 913.0.0 are different identities.
struct MonsterId {
    int type = 0, variant = 0, subtype = 0;
    auto operator<=>(const MonsterId &) const = default;
    explicit operator bool() const { return type != 0; }
};
constexpr MonsterId monsterId(int type, int variant = 0, int subtype = 0) { return {type,variant,subtype}; }
std::string monsterIdText(MonsterId id);
MonsterId parseMonsterId(std::string_view text);
} // namespace dw
