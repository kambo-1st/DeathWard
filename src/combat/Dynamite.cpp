#include "combat/Simulation.hpp"

namespace dw {
namespace {
constexpr float Gravity = 18, ChargeRadius = .18f, FlightTime = .7f;
constexpr float KickContactRadius = .72f, KickSpeed = 5.5f, KickLift = 1.4f;
} // namespace
void advanceDynamite(Hazard &charge, const Arena &arena, float dt) {
    if (charge.settled || dt <= 0)
        return;
    const Vector3 delta = add(mul(charge.velocity, dt), {0, -.5f * Gravity * dt * dt, 0});
    const auto end = add(charge.position, delta);
    auto hit = arena.trace(charge.position, end, ChargeRadius);
    if (arena.canyon) {
        // At a steep triangle boundary, a sphere can touch the next face before
        // its centre enters that cell. Also sweep the height field so those
        // contacts cannot leave a bouncing charge beneath the surface.
        const auto &terrain = *arena.canyon;
        const int samples = std::max(1, int(std::ceil(length(delta) / .08f)));
        float previous = 0;
        for (int i = 1; i <= samples; ++i) {
            float high = float(i) / float(samples);
            auto p = add(charge.position, mul(delta, high));
            if (terrain.height(p.x, p.z) + ChargeRadius > p.y) {
                float low = previous;
                for (int step = 0; step < 14; ++step) {
                    const float mid = (low + high) * .5f;
                    p = add(charge.position, mul(delta, mid));
                    if (terrain.height(p.x, p.z) + ChargeRadius > p.y)
                        high = mid;
                    else
                        low = mid;
                }
                if (!hit.hit || low < hit.t) {
                    p = add(charge.position, mul(delta, low));
                    const auto normal =
                        unit({terrain.height(p.x - .025f, p.z) - terrain.height(p.x + .025f, p.z), .05f,
                              terrain.height(p.x, p.z - .025f) - terrain.height(p.x, p.z + .025f)});
                    hit = {true, low, normal};
                }
                break;
            }
            previous = high;
        }
    }
    if (!arena.canyon && end.y < ChargeRadius && delta.y < 0) {
        const float floorTime = std::clamp((ChargeRadius - charge.position.y) / delta.y, 0.f, 1.f);
        if (!hit.hit || floorTime < hit.t)
            hit = {true, floorTime, {0, 1, 0}};
    }
    charge.velocity.y -= Gravity * dt;
    if (!hit.hit) {
        charge.position = end;
        return;
    }
    charge.position = add(charge.position, mul(delta, std::max(0.f, hit.t - .002f)));
    charge.position = add(charge.position, mul(hit.normal, .015f));
    if (arena.canyon)
        charge.position.y =
            std::max(charge.position.y,
                     arena.canyon->height(charge.position.x, charge.position.z) + ChargeRadius + .005f);
    const float inward = dot(charge.velocity, hit.normal);
    if (inward < 0)
        charge.velocity = sub(charge.velocity, mul(hit.normal, 1.25f * inward));
    charge.velocity = mul(charge.velocity, .55f);
    if (hit.normal.y > .5f && length(charge.velocity) < 1.2f) {
        charge.velocity = {};
        charge.settled = true;
    }
}
Hazard Simulation::makeDynamite(Vector3 target) const {
    Hazard charge;
    charge.kind = HazardKind::PlayerDynamite;
    charge.position = player.position;
    charge.position.y += .4f;
    // Do not start a charge inside overhead cover or beyond a nearby wall.
    if (arena.trace(player.position, charge.position, ChargeRadius).hit)
        charge.position = player.position;
    charge.origin = charge.position;
    Vector3 offset{target.x - player.position.x, 0, target.z - player.position.z};
    if (length(offset) > DynamiteRange)
        offset = mul(unit(offset), DynamiteRange);
    charge.velocity = mul(offset, 1 / FlightTime);
    charge.velocity.y = (ChargeRadius - charge.position.y) / FlightTime + .5f * Gravity * FlightTime;
    charge.delay = DynamiteFuse;
    charge.radius = DynamiteRadius;
    charge.damage = DynamiteSelfDamage;
    return charge;
}
bool Simulation::throwDynamite(Vector3 target) {
    if (!std::isfinite(target.x) || !std::isfinite(target.z))
        return false;
    return deployDynamite(makeDynamite(target));
}
bool Simulation::placeDynamite() {
    auto charge = makeDynamite(player.position);
    charge.position = player.position;
    const float floor = arena.canyon ? arena.canyon->height(player.position.x, player.position.z) : 0;
    charge.position.y = floor + ChargeRadius;
    charge.origin = player.position;
    charge.velocity = {};
    charge.settled = true;
    charge.playerContact = true; // Step away before walking back into a freshly placed bundle.
    return deployDynamite(charge);
}
void Simulation::kickDynamiteOnContact(Vector3 previousPosition) {
    if (dead || finished || shopOpen || rewardOpen || player.hp <= 0)
        return;
    const Vector3 movement{player.position.x - previousPosition.x, 0, player.position.z - previousPosition.z};
    const float travelSquared = dot(movement, movement);
    for (auto &charge : hazards) {
        if (charge.kind != HazardKind::PlayerDynamite || !charge.alive || charge.age >= charge.delay)
            continue;
        const Vector3 toward{charge.position.x - previousPosition.x, 0,
                             charge.position.z - previousPosition.z};
        const bool low = std::abs(charge.position.y - (player.position.y - .55f)) <= .65f;
        const bool touching = low && length(sub(toward, movement)) <= KickContactRadius;
        // Sweep the feet so a fast step/dodge cannot miss a bundle. Only entering
        // contact while approaching it kicks; overlap is not a kick every frame.
        const float t =
            travelSquared > .000001f ? std::clamp(dot(toward, movement) / travelSquared, 0.f, 1.f) : 0;
        const auto contact = add(previousPosition, mul(movement, t));
        if (!charge.playerContact && low && travelSquared > .000001f && dot(toward, movement) > 0 &&
            length(sub(toward, mul(movement, t))) <= KickContactRadius &&
            arena.sight(add(contact, {0, -.55f, 0}), charge.position)) {
            charge.velocity = add(mul(unit(toward), KickSpeed), {0, KickLift, 0});
            charge.settled = false;
            audioCues.push(arena.theme == MissionTheme::Canyon ? AudioCueKind::StepGravel
                                                               : AudioCueKind::StepMine,
                           charge.position);
        }
        charge.playerContact = touching;
    }
}
bool Simulation::deployDynamite(Hazard charge) {
    if (dead || finished || shopOpen || rewardOpen || player.hp <= 0 || dynamiteCooldown > 0)
        return false;
    if (dynamite <= 0) {
        announce("Out of dynamite. The shop sells a refill pack.");
        return false;
    }
    if (hazards.size() >= limits.hazards) {
        announce("Too many active hazards. Try again in a moment.");
        return false;
    }
    addHazard(charge);
    --dynamite;
    dynamiteCooldown = .45f;
    audioCues.push(AudioCueKind::Warning, player.position);
    return true;
}
std::vector<Vector3> Simulation::dynamiteTrajectory(Vector3 target) const {
    auto charge = makeDynamite(target);
    std::vector<Vector3> points{charge.position};
    for (float elapsed = 0; elapsed < DynamiteFuse && !charge.settled; elapsed += Tick) {
        advanceDynamite(charge, arena, std::min(Tick, DynamiteFuse - elapsed));
        points.push_back(charge.position);
    }
    return points;
}
} // namespace dw
