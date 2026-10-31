#include "combat/Simulation.hpp"

namespace dw {
namespace {
// Ground bodies share the same physical radius as projectile hits. Linked
// formations and airborne/intangible states need their own collision policies;
// they must not be torn apart by ordinary crowd steering. Native Mine actors
// retain their existing movement/separation path.
const MonsterDefinition *groundBody(const Enemy &e, const MechanicsLibrary &content) {
    if(e.rockSpider&&e.rockSpider->height<content.rockSpider(e.monster)->gridHeight)return nullptr;
    if(content.mirror(e.monster))return nullptr; // Its reflected position owns translation.
    if (!e.alive || e.dyingEggy() || e.railCarrier || e.kind != EnemyKind::Monster || e.state == EnemyState::Buried ||
        e.state == EnemyState::Teleporting || e.state == EnemyState::Jumping || e.hop.active || e.thrownOffspring ||
        (e.targetHop&&e.targetHop->airborne))
        return nullptr;
    if(const auto *swarm=content.swarmSpider(e.monster);swarm&&swarm->playerObjectsOnly)return nullptr;
    const auto *d = content.monster(e.monster);
    return d && !d->flying && !d->roomHazard && d->motion != MonsterMotion::Chain &&
                   d->motion != MonsterMotion::Orbit ? d : nullptr;
}
bool linked(const Enemy &a, const Enemy &b) {
    // Friendly partners can be attack targets, not attached body parts.
    return !a.friendly && !b.friendly && (a.partner == b.id || b.partner == a.id);
}
Vector3 flat(Vector3 v) { v.y = 0; return v; }
Vector3 separationNormal(Vector3 delta, EntityId a, EntityId b) {
    if (length(delta) > .0001f) return unit(delta);
    // A reproducible direction for exact coincident bodies; no combat RNG use.
    const auto axis = rotateY({1, 0, 0}, float((a ^ b) % 8) * Pi / 4);
    return a < b ? axis : mul(axis, -1);
}
}

void Simulation::moveMonster(Enemy &e, Vector3 velocity, float dt) {
    if(e.railCarrier)return; // Targeting/attacks continue; the carrier owns translation.
    const auto before = e.position;
    const auto *d=content->monster(e.monster);
    const auto *evader=content->evader(e.monster);
    const bool overPits=content->strider(e.monster)||((content->swimmer(e.monster)||(content->slide(e.monster)&&content->slide(e.monster)->floodedPits))&&arena.swimmingRoom(room))||(evader&&evader->hoverHeight>0);
    e.position = overPits?arena.swim(before,mul(velocity,dt),e.radius,room):
        d && d->flying ? arena.fly(before,mul(velocity,dt),e.radius,room) :
        arena.move(before, mul(velocity, dt), e.radius);
    e.velocity = mul(sub(e.position, before), 1 / dt);
}

Vector3 Simulation::steerMonsterBodies(const Enemy &e, Vector3 velocity,bool alignRoute) const {
    const float speed = length(velocity);
    if (speed < .001f || !groundBody(e, *content)) return velocity;
    const auto forward = mul(velocity, 1 / speed);
    const Vector3 side{-forward.z, 0, forward.x};
    Vector3 avoidance{};
    for (const auto &other : enemies) {
        if (e.id == other.id || linked(e, other) || !groundBody(other, *content)) continue;
        const auto away = flat(sub(e.position, other.position));
        const float range = length(away), reach = e.radius + other.radius + .8f;
        if (range >= reach || dot(away, forward) > 0) continue;
        // Two equal bodies cannot enter a one-body opening side by side.
        // Let one approach first while the other backs out of the pinch point;
        // merely adding lateral avoidance wedges both against the jambs.
        if (e.id > other.id && range < e.radius + other.radius + .25f &&
            !arena.clear(e.position, player.position, e.radius))
            return mul(unit(add(separationNormal(away, e.id, other.id), mul(forward, -1))), speed * .6f);
        // Route alignment still yields to a prior body. Suppress only sideways
        // passing, which can press actors against opposite doorway jambs.
        if(alignRoute)continue;
        // Pass around a body ahead instead of repeatedly pressing into its back.
        // On the exact centre line stable entity order breaks left/right ties.
        const float lateral = dot(away, side);
        const float sign = std::abs(lateral) > .03f ? (lateral > 0 ? 1.f : -1.f) : (e.id % 2 ? 1.f : -1.f);
        const float strength = std::clamp((reach - range) / .8f, 0.f, 1.f);
        avoidance = add(avoidance, mul(side, sign * strength));
    }
    const auto steered = add(forward, avoidance);
    return mul(unit(steered), speed); // Steering never grants extra pursuit speed.
}

void Simulation::resolveMonsterBodies(float dt) {
    struct Body { Enemy *enemy; Vector3 before; float mobility; };
    std::vector<Body> bodies;
    bodies.reserve(enemies.size());
    for (auto &e : enemies)
        if (const auto *d = groundBody(e, *content))
            bodies.push_back({&e, e.position, d->speed > 0 ?
                (content->knight(e.monster)?10.f/content->knight(e.monster)->mass:
                 e.rockSpider?(e.rockSpider->phase==RockSpiderPhase::Rock?.1f:2.f):1.f)/(e.radius*e.radius):0.f});
    const auto knightCollision=[&](Enemy &e,Vector3 toward) {
        if(!e.knight||!e.knight->charging||e.knight->blocked)return;
        auto &r=*e.knight;r.blocked=true;r.impactNormal=unit(toward);
        r.impactVelocity=mul(horizontal(e.velocity),1/(content->knight(e.monster)->scale*30));
    };
    bool adjusted = false;
    auto displace = [&](Body &body, Vector3 correction) {
        if (body.mobility == 0) return Vector3{};
        auto &e = *body.enemy;
        const auto before = e.position;
        const auto *evader=content->evader(e.monster);
        const bool overPits=content->strider(e.monster)||((content->swimmer(e.monster)||(content->slide(e.monster)&&content->slide(e.monster)->floodedPits))&&arena.swimmingRoom(room))||(evader&&evader->hoverHeight>0);
        e.position = overPits?arena.swim(before,correction,e.radius,room):
            arena.move(before, correction, e.radius);
        const auto moved = sub(e.position, before);
        if (length(moved) > .00001f) {
            adjusted = true;
            const auto normal = unit(moved);
            const float inward = dot(e.behavior.momentum, normal);
            if (inward < 0) e.behavior.momentum = sub(e.behavior.momentum, mul(normal, inward));
        }
        return moved;
    };
    auto playerContact = [&](Body &body) {
        auto &e = *body.enemy;
        if (e.friendly) return;
        const auto delta = flat(sub(e.position, player.position));
        // Small contact skin remains inside the existing damage test (.48).
        // The player is never displaced/blocked: walking and dodging still work.
        const float gap = e.radius + .475f, range = length(delta);
        if (range < gap) {
            if(e.brain&&e.brain->charging)e.brain->blocked=true;
            knightCollision(e,mul(delta,-1));
            displace(body, mul(separationNormal(delta, e.id, 0), gap - range));
        }
    };
    // Bounded position constraints operate on real bodies, before projectile
    // broad-phase rebuilding. Every correction sweeps through terrain/walls.
    for (int pass = 0; pass < 6; ++pass) {
        adjusted = false;
        for (auto &body : bodies) playerContact(body);
        for (size_t i = 0; i < bodies.size(); ++i) {
            auto &a = bodies[i];
            for (size_t j = i + 1; j < bodies.size(); ++j) {
                auto &b = bodies[j];
                const float mobility = a.mobility + b.mobility;
                if (!mobility || linked(*a.enemy, *b.enemy)) continue;
                const auto delta = flat(sub(a.enemy->position, b.enemy->position));
                const float gap = a.enemy->radius + b.enemy->radius + .025f;
                if (dot(delta, delta) >= (gap - .0001f) * (gap - .0001f)) continue;
                if(a.enemy->brain&&a.enemy->brain->charging)a.enemy->brain->blocked=true;
                if(b.enemy->brain&&b.enemy->brain->charging)b.enemy->brain->blocked=true;
                const float range = length(delta);
                const auto normal = separationNormal(delta, a.enemy->id, b.enemy->id);
                knightCollision(*a.enemy,mul(normal,-1));knightCollision(*b.enemy,normal);
                const float overlap = gap - range;
                const auto movedA = displace(a, mul(normal, overlap * a.mobility / mobility));
                const auto movedB = displace(b, mul(normal, -overlap * b.mobility / mobility));
                // If a wall stops one partner, give the other the remaining
                // correction rather than forcing either one through cover.
                float left = overlap - dot(sub(movedA, movedB), normal);
                if (left > .0001f) {
                    left -= dot(displace(a, mul(normal, left)), normal);
                    if (left > .0001f) displace(b, mul(normal, -left));
                }
            }
        }
        if (!adjusted) break;
    }
    for (auto &body : bodies) {
        playerContact(body);
        auto &e = *body.enemy;
        e.velocity = add(e.velocity, mul(sub(e.position, body.before), 1 / dt));
    }
}
} // namespace dw
