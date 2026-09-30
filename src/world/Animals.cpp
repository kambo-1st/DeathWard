#include "world/Animals.hpp"
#include <fstream>
#include <stdexcept>
#include <unordered_set>

namespace dw {
const char *animalName(AnimalKind kind) {
    static constexpr std::array<const char *, size_t(AnimalKind::Count)> names{
#define DW_ANIMAL(symbol, name, radius, speed) name,
#include "world/AnimalCatalog.inc"
#undef DW_ANIMAL
    };
    return names.at(size_t(kind));
}
float animalRadius(AnimalKind kind) {
    static constexpr std::array<float, size_t(AnimalKind::Count)> radii{
#define DW_ANIMAL(symbol, name, radius, speed) radius,
#include "world/AnimalCatalog.inc"
#undef DW_ANIMAL
    };
    return radii.at(size_t(kind));
}
float animalWalkSpeed(AnimalKind kind) {
    static constexpr std::array<float, size_t(AnimalKind::Count)> speeds{
#define DW_ANIMAL(symbol, name, radius, speed) speed,
#include "world/AnimalCatalog.inc"
#undef DW_ANIMAL
    };
    return speeds.at(size_t(kind));
}
AnimalPlacement readAnimalPlacement(std::istream &in) {
    AnimalPlacement a;
    std::string species;
    uint64_t seed = 0;
    if (!(in >> a.id >> species >> a.home.x >> a.home.z >> a.yaw >> a.scale >> a.roam >> seed) || seed > UINT32_MAX)
        throw std::runtime_error("Invalid animal placement.");
    size_t kind = 0;
    while (kind < size_t(AnimalKind::Count) && species != animalName(AnimalKind(kind))) ++kind;
    a.kind = AnimalKind(kind);
    a.seed = uint32_t(seed);
    return a;
}
void writeAnimalPlacement(std::ostream &out, const AnimalPlacement &a) {
    out << "animal " << a.id << ' ' << animalName(a.kind) << ' ' << a.home.x << ' ' << a.home.z
        << ' ' << a.yaw << ' ' << a.scale << ' ' << a.roam << ' ' << a.seed << '\n';
}
void validateAnimalPlacements(const std::vector<AnimalPlacement> &animals) {
    if (animals.size() > 64) throw std::runtime_error("A town supports at most 64 animals.");
    std::unordered_set<std::string> ids;
    for (const auto &a : animals) {
        if (size_t(a.kind) >= size_t(AnimalKind::Count) || a.id.empty() || a.id.size() > 128 ||
            a.id.find_first_of(" \t\r\n") != std::string::npos || !ids.insert(a.id).second ||
            !std::isfinite(a.home.x) || !std::isfinite(a.home.z) || std::abs(a.home.x) > 10000 ||
            std::abs(a.home.z) > 10000 || !std::isfinite(a.yaw) || !std::isfinite(a.scale) ||
            a.scale < .25f || a.scale > 3 || !std::isfinite(a.roam) || a.roam < 0 || a.roam > 20)
            throw std::runtime_error("Invalid animal species or settings.");
        if (!std::isfinite(a.activity.speed) || a.activity.speed < .1f || a.activity.speed > 3 ||
            a.activity.clips.size() > AnimalActivity::MaxClips)
            throw std::runtime_error("Animation speed must be 0.1–3, with at most four clips.");
        for (const auto &clip : a.activity.clips)
            if (clip.empty() || clip.size() > 63 || clip.find_first_of(" \t\r\n") != std::string::npos)
                throw std::runtime_error("Invalid animal animation name.");
    }
}
std::vector<AnimalPlacement> loadAnimalPlacements(const std::filesystem::path &file) {
    if (file.empty()) return {};
    std::ifstream in(file);
    std::string token;
    int version = 0;
    if (!(in >> token >> version) || token != "DEATHWARD_ANIMALS" || version != 1)
        throw std::runtime_error("Missing or unsupported animal placements.");
    std::vector<AnimalPlacement> result;
    while (in >> token) {
        if (token != "animal" || result.size() >= 64) throw std::runtime_error("Invalid animal placement.");
        result.push_back(readAnimalPlacement(in));
    }
    validateAnimalPlacements(result);
    return result;
}
bool Animals::clearFootprint(const AnimalPlacement &a, Vector3 point, const HubWorld &ground) {
    const float y = ground.height(point), radius = animalRadius(a.kind) * a.scale;
    if (!std::isfinite(y) || !ground.walkable(point)) return false;
    for (int n = 0; n < 8; ++n) {
        const float angle = float(n) * Pi / 4;
        const auto edge = add(point, {radius * std::cos(angle), 0, radius * std::sin(angle)});
        if (!ground.walkable(edge) || std::abs(ground.height(edge) - y) > .4f) return false;
    }
    auto board = sub(point, ground.mission);
    board.y = 0;
    return length(board) >= radius + 1.4f;
}
bool Animals::clear(const Animal &a, Vector3 point, const HubWorld &ground, bool residents) const {
    AnimalPlacement definition;
    definition.kind = a.kind;
    definition.scale = a.scale;
    if (!clearFootprint(definition, point, ground)) return false;
    const float radius = animalRadius(a.kind) * a.scale;
    if (residents)
        for (const auto &other : animals_)
            if (&a != &other && a.id != other.id) {
                auto d = sub(point, other.position);
                d.y = 0;
                if (length(d) < radius + animalRadius(other.kind) * other.scale + .15f)
                    return false;
            }
    return true;
}
bool Animals::load(const std::filesystem::path &file, const HubWorld &ground) {
    try {
        return reset(loadAnimalPlacements(file), ground);
    } catch (const std::exception &e) {
        animals_.clear(); placements_.clear(); time_ = accumulator_ = 0;
        error_ = e.what();
        return false;
    }
}
bool Animals::reset(const std::vector<AnimalPlacement> &placements, const HubWorld &ground, bool relocate) {
    animals_.clear();
    placements_ = placements;
    error_.clear();
    time_ = accumulator_ = 0;
    try {
        validateAnimalPlacements(placements_);
        for (const auto &definition : placements_) {
            Animal a;
            a.id = definition.id; a.kind = definition.kind; a.home = definition.home;
            a.scale = definition.scale; a.roam = definition.roam;
            a.activity = definition.activity;
            a.random = Random(definition.seed);
            a.facing = {std::sin(definition.yaw * DEG2RAD), 0, std::cos(definition.yaw * DEG2RAD)};
            bool found = false;
            for (int ring = 0; ring <= (relocate ? 10 : 0) && !found; ++ring)
                for (int n = 0; n < (ring ? 24 : 1); ++n) {
                    const float angle = float(n) * Pi / 12;
                    const auto point = add(a.home, {ring * .5f * std::cos(angle), 0, ring * .5f * std::sin(angle)});
                    if (!relocate || clear(a, point, ground, true)) {
                        const float y = ground.height(point);
                        a.home = a.position = a.target = {point.x, std::isfinite(y) ? y : 0, point.z};
                        found = true;
                        break;
                    }
                }
            if (!found) continue;
            a.phase = a.random.real(0, 8);
            if (a.activity.stationary) a.phase = 0;
            a.wait = a.random.real(1, 4);
            animals_.push_back(std::move(a));
        }
        return true;
    } catch (const std::exception &e) {
        error_ = e.what();
        animals_.clear(); placements_.clear();
        return false;
    }
}
void Animals::update(float dt, const HubWorld &ground) {
    if (!std::isfinite(dt) || dt <= 0)
        return;
    accumulator_ += std::min(double(dt), .1);
    constexpr double tick = 1. / 60;
    while (accumulator_ + 1e-9 >= tick) {
        accumulator_ -= tick;
        time_ += tick;
        step(ground);
    }
}
void Animals::step(const HubWorld &ground) {
    constexpr float dt = 1.f / 60;
    for (auto &a : animals_) {
        if (a.activity.stationary) {
            a.moving = false;
            a.walking = a.eating = 0;
            a.phase += dt;
            continue;
        }
        bool walked = false;
        if (a.moving) {
            auto delta = sub(a.target, a.position);
            delta.y = 0;
            const float d = length(delta);
            const auto direction = unit(delta);
            auto next = add(a.position, mul(direction, std::min(d, animalWalkSpeed(a.kind) * a.scale * dt)));
            auto player = sub(next, ground.player.position);
            player.y = 0;
            if (d < .04f || !clear(a, next, ground, true) ||
                length(player) < animalRadius(a.kind) * a.scale + .55f) {
                a.moving = false;
                a.wait = a.random.real(2, 6);
            } else {
                next.y = ground.height(next);
                a.position = next;
                walked = true;
                const float yaw = std::atan2(a.facing.x, a.facing.z),
                            target = std::atan2(direction.x, direction.z);
                const float angle = yaw + std::clamp(std::remainder(target - yaw, 2 * Pi), -3 * dt, 3 * dt);
                a.facing = {std::sin(angle), 0, std::cos(angle)};
            }
        } else if ((a.wait -= dt) <= 0) {
            a.wait = a.random.real(2, 5);
            for (int n = 0; n < 16 && a.roam > .1f; ++n) {
                const float angle = a.random.real(0, 2 * Pi), r = a.random.real(0, a.roam);
                auto candidate = add(a.home, {r * std::cos(angle), 0, r * std::sin(angle)});
                auto delta = sub(candidate, a.position);
                delta.y = 0;
                if (length(delta) < .5f || !clear(a, candidate, ground, true))
                    continue;
                bool path = true;
                for (float t = .2f; t < 1; t += .2f)
                    path &= clear(a, add(a.position, mul(delta, t)), ground, false);
                if (path) {
                    a.target = candidate;
                    a.moving = true;
                    break;
                }
            }
        }
        a.walking = std::clamp(a.walking + (walked ? 1 : -1) * dt * 5, 0.f, 1.f);
        const bool eats = !a.moving && std::sin(float(a.phase) * .17f) > 0;
        a.eating = std::clamp(a.eating + (eats ? 1 : -1) * dt * 2, 0.f, 1.f);
        a.phase += dt;
    }
}
} // namespace dw
