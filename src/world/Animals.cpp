#include "world/Animals.hpp"
#include <fstream>
#include <stdexcept>
#include <unordered_set>

namespace dw {
const char *animalName(AnimalKind kind) {
    static constexpr std::array<const char *, 4> names{"horse", "hen", "cow", "cat"};
    return names.at(size_t(kind));
}
float animalRadius(AnimalKind kind) {
    static constexpr std::array<float, 4> radii{1.6f, .35f, 1.5f, .4f};
    return radii.at(size_t(kind));
}
float animalWalkSpeed(AnimalKind kind) {
    static constexpr std::array<float, 4> speeds{1.2f, .55f, .8f, .65f};
    return speeds.at(size_t(kind));
}
bool Animals::clear(const Animal &a, Vector3 point, const HubWorld &ground, bool residents) const {
    const float y = ground.height(point), radius = animalRadius(a.kind) * a.scale;
    if (!std::isfinite(y) || !ground.walkable(point))
        return false;
    for (int n = 0; n < 8; ++n) {
        const float angle = float(n) * Pi / 4;
        const auto edge = add(point, {radius * std::cos(angle), 0, radius * std::sin(angle)});
        if (!ground.walkable(edge) || std::abs(ground.height(edge) - y) > .4f)
            return false;
    }
    auto board = sub(point, ground.mission);
    board.y = 0;
    if (length(board) < radius + 1.4f)
        return false;
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
    animals_.clear();
    error_.clear();
    time_ = accumulator_ = 0;
    if (file.empty())
        return true;
    try {
        std::ifstream in(file);
        std::string token;
        int version = 0;
        if (!(in >> token >> version) || token != "DEATHWARD_ANIMALS" || version != 1)
            throw std::runtime_error("Missing or unsupported animal placements.");
        std::unordered_set<std::string> ids;
        while (in >> token) {
            Animal a;
            std::string species;
            float yaw;
            uint32_t seed;
            if (token != "animal" ||
                !(in >> a.id >> species >> a.home.x >> a.home.z >> yaw >> a.scale >> a.roam >> seed))
                throw std::runtime_error("Invalid animal placement.");
            size_t kind = 0;
            while (kind < size_t(AnimalKind::Count) && species != animalName(AnimalKind(kind)))
                ++kind;
            if (kind == size_t(AnimalKind::Count) || a.id.size() > 128 || !ids.insert(a.id).second ||
                !std::isfinite(a.home.x) || !std::isfinite(a.home.z) || std::abs(a.home.x) > 10000 ||
                std::abs(a.home.z) > 10000 || !std::isfinite(yaw) || !std::isfinite(a.scale) ||
                a.scale < .25f || a.scale > 3 || !std::isfinite(a.roam) || a.roam < 0 || a.roam > 20 ||
                animals_.size() >= 64)
                throw std::runtime_error("Invalid animal species or settings.");
            a.kind = AnimalKind(kind);
            a.random = Random(seed);
            a.facing = {std::sin(yaw * DEG2RAD), 0, std::cos(yaw * DEG2RAD)};
            bool found = false;
            for (int ring = 0; ring <= 10 && !found; ++ring)
                for (int n = 0; n < (ring ? 24 : 1); ++n) {
                    const float angle = float(n) * Pi / 12;
                    const auto point =
                        add(a.home, {ring * .5f * std::cos(angle), 0, ring * .5f * std::sin(angle)});
                    if (clear(a, point, ground, true)) {
                        a.home = a.position = a.target = {point.x, ground.height(point), point.z};
                        found = true;
                        break;
                    }
                }
            // An edited town may no longer have suitable ground near this home.
            if (!found)
                continue;
            a.phase = a.random.real(0, 8);
            a.wait = a.random.real(1, 4);
            animals_.push_back(std::move(a));
        }
        return true;
    } catch (const std::exception &e) {
        error_ = e.what();
        animals_.clear();
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
