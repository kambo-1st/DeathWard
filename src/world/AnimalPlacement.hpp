#pragma once
#include "core/Types.hpp"
#include <filesystem>
#include <iosfwd>

namespace dw {
enum class AnimalKind {
#define DW_ANIMAL(symbol, name, radius, speed) symbol,
#include "world/AnimalCatalog.inc"
#undef DW_ANIMAL
    Count
};
const char *animalName(AnimalKind kind);
float animalRadius(AnimalKind kind);
float animalWalkSpeed(AnimalKind kind);
struct AnimalActivity {
    static constexpr size_t MaxClips = 4;
    bool stationary = false;
    float speed = 1;
    std::vector<std::string> clips; // Empty uses idle; otherwise repeat this sequence in order.
    bool operator==(const AnimalActivity &) const = default;
};
struct AnimalPlacement {
    std::string id;
    AnimalKind kind = AnimalKind::Horse;
    Vector3 home{};
    float yaw = 0, scale = 1, roam = 3;
    uint32_t seed = 1;
    AnimalActivity activity;
};
AnimalPlacement readAnimalPlacement(std::istream &in);
void writeAnimalPlacement(std::ostream &out, const AnimalPlacement &animal);
void validateAnimalPlacements(const std::vector<AnimalPlacement> &animals);
std::vector<AnimalPlacement> loadAnimalPlacements(const std::filesystem::path &file);
} // namespace dw
