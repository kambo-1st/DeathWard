#include "world/TownCharacters.hpp"
namespace dw {
void TownCharacters::reset(const TownDocument &document, const HubWorld &ground) {
    characters_.clear();
    accumulator_ = time_ = 0;
    for (const auto &definition : document.characters) {
        TownCharacterState c;
        c.definition = definition;
        c.position = definition.position;
        const float y = ground.height(c.position);
        if (std::isfinite(y)) c.position.y = y;
        c.blocked = !ground.walkable(c.position);
        c.facing = {std::sin(definition.yaw * DEG2RAD), 0, std::cos(definition.yaw * DEG2RAD)};
        c.wait = definition.dwell;
        c.phase = double(characters_.size()) * .37;
        characters_.push_back(std::move(c));
    }
}
void TownCharacters::update(float dt, const HubWorld &ground) {
    if (!std::isfinite(dt) || dt <= 0) return;
    accumulator_ += std::min(double(dt), .1);
    constexpr double tick = 1. / 60;
    while (accumulator_ + 1e-9 >= tick) {
        accumulator_ -= tick;
        step(ground);
        time_ += tick;
    }
}
void TownCharacters::step(const HubWorld &ground) {
    for (auto &c : characters_) {
        const auto &d = c.definition;
        bool moving = false;
        c.retry = std::max(0.f, c.retry - Tick);
        if (c.wait > 0) c.wait = std::max(0.f, c.wait - Tick);
        else if (!d.stops.empty() && d.speed > 0) {
            const auto destination = c.destination == 0 ? d.position : d.stops[c.destination - 1];
            if (c.route.empty() && c.retry == 0) {
                auto route = ground.walkable(destination) ? ground.findRoute(c.position, destination) : std::nullopt;
                c.blocked = !route;
                if (route) { c.route = std::move(*route); c.next = 0; }
                else c.retry = 1;
            }
            float remaining = d.speed * Tick;
            while (c.next < c.route.size() && remaining > .00001f) {
                auto delta = sub(c.route[c.next], c.position);
                delta.y = 0;
                const float distance = length(delta);
                if (distance < .015f) { ++c.next; continue; }
                const float amount = std::min({remaining, distance, .06f});
                const auto direction = unit(delta);
                auto next = add(c.position, mul(direction, amount));
                if (!ground.canTraverse(c.position, next)) {
                    c.route.clear(); c.next = 0; c.retry = .5f; c.blocked = true;
                    break;
                }
                next.y = ground.height(next);
                c.position = next;
                c.facing = unit(add(mul(c.facing, .85f), mul(direction, .15f)));
                remaining -= amount;
                moving = true;
                c.blocked = false;
                if (distance <= amount + .015f) ++c.next;
            }
            if (!c.route.empty() && c.next == c.route.size()) {
                c.route.clear(); c.next = 0; c.wait = d.dwell; ++c.visits;
                if (d.loop) c.destination = (c.destination + 1) % (d.stops.size() + 1);
                else {
                    if (c.destination == d.stops.size()) c.direction = -1;
                    else if (c.destination == 0) c.direction = 1;
                    c.destination = size_t(int(c.destination) + c.direction);
                }
            }
        }
        const float target = moving ? 1.f : 0.f;
        c.walking += std::clamp(target - c.walking, -Tick * 6, Tick * 6);
        const float alternate = c.visits % 2 ? 1.f : 0.f;
        c.alternate += std::clamp(alternate - c.alternate, -Tick * 3, Tick * 3);
        c.phase += Tick * (moving ? d.speed / 1.2f : 1.f);
    }
}
}
