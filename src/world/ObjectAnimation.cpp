#include "world/ObjectAnimation.hpp"
#include "world/TownBuildings.hpp"
#include "raymath.h"
#include <unordered_map>

namespace dw {
namespace {
constexpr double MotionTick = 1.0 / 60.0;
Matrix about(Matrix base, Vector3 center, Matrix rotation, Vector3 destination) {
    return MatrixMultiply(
        MatrixMultiply(MatrixMultiply(base, MatrixTranslate(-center.x, -center.y, -center.z)), rotation),
        MatrixTranslate(destination.x, destination.y, destination.z));
}
float groundHeight(const ObjectAnimationSystem::Ground &ground, Vector3 p, float radius) {
    if (!ground)
        return std::numeric_limits<float>::quiet_NaN();
    const float y = ground(p);
    if (!std::isfinite(y))
        return y;
    for (int n = 0; n < 8; ++n) {
        const float a = float(n) * Pi / 4;
        const float edge = ground(add(p, {radius * std::cos(a), 0, radius * std::sin(a)}));
        if (!std::isfinite(edge) || std::abs(edge - y) > .4f)
            return std::numeric_limits<float>::quiet_NaN();
    }
    return y;
}
} // namespace
void ObjectAnimationSystem::reset(const TownDocument &document) {
    document.validate();
    poses_.clear();
    moving_.clear();
    doors_.clear();
    paths_.clear();
    groups_.clear();
    members_.clear();
    solids_.clear();
    std::unordered_map<std::string, size_t> pathIds, groupIds;
    for (const auto &definition : document.paths) {
        Path p;
        p.definition = definition;
        p.wait = definition.dwell;
        for (size_t n = 0; n < definition.points.size(); ++n) {
            p.cumulative.push_back(p.length);
            p.length += distance(definition.points[n], definition.points[(n + 1) % definition.points.size()]);
        }
        pathIds[definition.id] = paths_.size();
        paths_.push_back(std::move(p));
    }
    for (const auto &definition : document.groups) {
        groupIds[definition.id] = groups_.size();
        groups_.push_back({pathIds.at(definition.path), definition.offset, definition.wheelbase});
    }
    accumulator_ = time_ = 0;
    for (size_t n = 0; n < document.instances.size(); ++n) {
        const auto &i = document.instances[n];
        const auto local = document.assets[i.asset].bounds;
        const auto bounds = document.bounds(n);
        const auto &asset = document.assets[i.asset];
        poses_.push_back({i.transform, bounds, i.animated() || buildingDoor(asset) || doorGlass(asset)});
        if (buildingDoor(asset) && !i.animated()) {
            Door door;
            door.parts.push_back({n,i.transform,local});
            door.hinge = Vector3Transform({},i.transform);
            door.center = mul(add(bounds.min,bounds.max),.5f);
            door.bottom = bounds.min.y;
            // Align an opened leaf with the nearest exterior wall's outward
            // normal. This retains doors already open in the imported demo.
            float best = 2.f;
            auto leaf = sub(door.center,door.hinge); leaf.y=0;
            for (const auto &body : document.instances) {
                const auto &a = document.assets[body.asset];
                if (!buildingShell(a)) continue;
                const auto at = Vector3Transform(door.hinge,MatrixInvert(body.transform));
                if (at.x<a.bounds.min.x-.8f || at.x>a.bounds.max.x+.8f ||
                    at.z<a.bounds.min.z-.8f || at.z>a.bounds.max.z+.8f) continue;
                const std::array<float,4> edges{std::abs(at.x-a.bounds.min.x),std::abs(at.x-a.bounds.max.x),
                    std::abs(at.z-a.bounds.min.z),std::abs(at.z-a.bounds.max.z)};
                const std::array<Vector3,4> normals{{{-1,0,0},{1,0,0},{0,0,-1},{0,0,1}}};
                for (size_t side=0;side<edges.size();++side) if(edges[side]<best) {
                    best=edges[side];
                    auto normal=Vector3Transform(normals[side],body.transform);
                    normal=sub(normal,Vector3Transform({},body.transform));normal.y=0;
                    door.angle=std::remainder(std::atan2(normal.x,normal.z)-std::atan2(leaf.x,leaf.z),2*Pi);
                }
            }
            doors_.push_back(std::move(door));
        }
        if (!i.group.empty()) {
            const auto group = groupIds.at(i.group);
            const auto bind = MatrixMultiply(i.transform, MatrixInvert(groupFrame(groups_[group])));
            members_.push_back({n, group, i.transform, bind, local, i.wheelRadius});
            const auto b = objectBounds(local, bind);
            auto &g = groups_[group];
            g.bounds.min = Vector3Min(g.bounds.min, b.min);
            g.bounds.max = Vector3Max(g.bounds.max, b.max);
        }
        if (i.motion.kind == ObjectMotionKind::None)
            continue;
        Moving state{n, i.transform, local, i.motion};
        state.center = state.restCenter = mul(add(bounds.min, bounds.max), .5f);
        const auto size = sub(bounds.max, bounds.min);
        state.radius = std::max(.05f, std::max({size.x, size.y, size.z}) * .5f);
        uint64_t seed = i.motion.seed;
        for (unsigned char c : i.id)
            seed = (seed ^ c) * 1099511628211ULL;
        Random random(seed);
        state.phase = random.real(0, 2 * Pi);
        state.heading = {std::cos(state.phase), 0, std::sin(state.phase)};
        moving_.push_back(state);
    }
    // Door window meshes often have their own pivot. Rotate them about the
    // leaf's hinge using their original transform, preserving the UV/material.
    for (size_t n=0;n<document.instances.size();++n) {
        const auto &i=document.instances[n];
        const auto &a=document.assets[i.asset];
        if(!doorGlass(a) || i.animated())continue;
        const auto center=mul(add(poses_[n].bounds.min,poses_[n].bounds.max),.5f);
        Door *nearest=nullptr;float best=1.3f;
        for(auto &door:doors_) {
            const auto &leaf=document.instances[door.parts.front().index];
            const bool related=i.id.substr(0,i.id.find(':'))==leaf.id.substr(0,leaf.id.find(':'));
            const float d=distance(center,door.center)+(related?0.f:.2f);
            if(d<best){best=d;nearest=&door;}
        }
        if(nearest)nearest->parts.push_back({n,i.transform,a.bounds});
    }
    evaluateGroups();
}
size_t ObjectAnimationSystem::openDoorCount() const {
    return size_t(std::count_if(doors_.begin(),doors_.end(),[](const auto &d){return d.openness>.5f;}));
}
void ObjectAnimationSystem::stepDoors(std::optional<Vector3> player) {
    for(auto &door:doors_) {
        float d=1000;
        if(player && std::abs(player->y-.85f-door.bottom)<1.1f)
            d=std::hypot(player->x-door.center.x,player->z-door.center.z);
        if(d<2.4f)door.opening=true;
        if(d>3.1f)door.opening=false;
        const float target=door.opening?1.f:0.f;
        door.openness += (target-door.openness)*.18f;
        if(std::abs(door.openness-target)<.0001f)door.openness=target;
        for(const auto &part:door.parts) {
            const auto pose=about(part.rest,door.hinge,MatrixRotateY(door.angle*door.openness),door.hinge);
            poses_[part.index]={pose,objectBounds(part.local,pose),true};
        }
    }
}
void ObjectAnimationSystem::update(float dt, const Ground &ground, std::optional<Vector3> player) {
    // The scene clock also drives attached effects, including hubs with no rigid motion.
    if (!std::isfinite(dt) || dt <= 0)
        return;
    accumulator_ += std::min(double(dt), .25);
    while (accumulator_ + 1e-9 >= MotionTick) {
        accumulator_ -= MotionTick;
        time_ += MotionTick;
        stepPaths(player);
        stepDoors(player);
        step([&](Vector3 point) {
            const float y = ground ? ground(point) : std::numeric_limits<float>::quiet_NaN();
            for (const auto &solid : solids_)
                if (solid.contains({point.x, y + .3f, point.z}, 0))
                    return std::numeric_limits<float>::quiet_NaN();
            return y;
        });
    }
}
void ObjectAnimationSystem::step(const Ground &ground) {
    for (auto &s : moving_) {
        const auto &m = s.motion;
        Matrix pose = s.rest;
        if (m.kind == ObjectMotionKind::Tumbleweed) {
            const float wave = float(std::fmod(time_ / m.period, 1000.0)) * 2 * Pi;
            const float wind = s.phase + .5f * std::sin(wave * .37f + s.phase);
            const Vector3 desired{std::cos(wind), 0, std::sin(wind)};
            s.heading = unit(add(mul(s.heading, .992f), mul(desired, .008f)));
            const float speed = m.speed * (.8f + .2f * std::sin(wave + s.phase));
            const auto delta = mul(s.heading, speed * float(MotionTick));
            const auto candidate = add(s.center, delta);
            const float y = groundHeight(ground, candidate, s.radius);
            if (std::isfinite(y) && std::abs(y + s.radius - s.center.y) < .6f) {
                const float travel = length(delta);
                s.distance += travel;
                if (travel > .000001f) {
                    const auto axis = unit(Vector3CrossProduct({0, 1, 0}, delta));
                    s.roll = QuaternionNormalize(
                        QuaternionMultiply(QuaternionFromAxisAngle(axis, travel / s.radius), s.roll));
                }
                s.center = candidate;
                s.center.y = y + s.radius;
            } else {
                // Bounce against the blocked axis without teleporting to another street.
                const bool xClear =
                    std::isfinite(groundHeight(ground, add(s.center, {delta.x, 0, 0}), s.radius));
                const bool zClear =
                    std::isfinite(groundHeight(ground, add(s.center, {0, 0, delta.z}), s.radius));
                if (!xClear || zClear)
                    s.heading.x = -s.heading.x;
                if (!zClear || xClear)
                    s.heading.z = -s.heading.z;
            }
            auto center = s.center;
            center.y += m.amplitude * std::abs(std::sin(s.distance / s.radius));
            pose = about(s.rest, s.restCenter, QuaternionToMatrix(s.roll), center);
        } else {
            const float angle =
                m.kind == ObjectMotionKind::Spin
                    ? float(std::fmod(time_ * m.speed, 360.0))
                    : m.amplitude * std::sin(float(std::fmod(time_ * m.speed / m.period, 1.0)) * 2 * Pi);
            const auto local =
                about(MatrixIdentity(), m.pivot, MatrixRotate(unit(m.axis), angle * DEG2RAD), m.pivot);
            pose = MatrixMultiply(local, s.rest);
        }
        poses_[s.index] = {pose, objectBounds(s.local, pose), true};
    }
}
bool MovingSolid::contains(Vector3 point, float radius) const {
    const auto d = sub(point, center);
    if (std::abs(d.y) > halfSize.y + .85f)
        return false;
    const float x = std::max(0.f, std::abs(d.x * forward.x + d.z * forward.z) - halfSize.x);
    const float z = std::max(0.f, std::abs(-d.x * forward.z + d.z * forward.x) - halfSize.z);
    return x * x + z * z <= radius * radius;
}
Box MovingSolid::bounds() const {
    const Vector3 extent{std::abs(forward.x) * halfSize.x + std::abs(forward.z) * halfSize.z, halfSize.y,
                         std::abs(forward.z) * halfSize.x + std::abs(forward.x) * halfSize.z};
    return {sub(center, extent), add(center, extent)};
}
Vector3 ObjectAnimationSystem::sample(const Path &p, float at) const {
    at = std::fmod(at, p.length);
    if (at < 0)
        at += p.length;
    const auto it = std::upper_bound(p.cumulative.begin(), p.cumulative.end(), at);
    const size_t n = size_t(it - p.cumulative.begin() - 1);
    const float end = n + 1 < p.cumulative.size() ? p.cumulative[n + 1] : p.length;
    return Vector3Lerp(p.definition.points[n], p.definition.points[(n + 1) % p.definition.points.size()],
                       (at - p.cumulative[n]) / (end - p.cumulative[n]));
}
Matrix ObjectAnimationSystem::groupFrame(const Group &g) const {
    const auto &p = paths_[g.path];
    const float at = g.offset + p.position, half = std::max(.1f, g.wheelbase * .5f);
    const auto front = sample(p, at + half), back = sample(p, at - half);
    const auto direction = unit(sub(front, back));
    const auto center = g.wheelbase > 0 ? mul(add(front, back), .5f) : sample(p, at);
    auto m = MatrixIdentity();
    m.m0 = direction.x;
    m.m2 = direction.z;
    m.m8 = -direction.z;
    m.m10 = direction.x;
    m.m12 = center.x;
    m.m13 = center.y;
    m.m14 = center.z;
    return m;
}
void ObjectAnimationSystem::evaluateGroups() {
    std::vector<Matrix> frames;
    solids_.clear();
    for (const auto &g : groups_) {
        const auto frame = groupFrame(g);
        frames.push_back(frame);
        solids_.push_back({Vector3Transform(mul(add(g.bounds.min, g.bounds.max), .5f), frame),
                           {frame.m0, 0, frame.m2},
                           mul(sub(g.bounds.max, g.bounds.min), .5f)});
    }
    for (const auto &m : members_) {
        const auto &path = paths_[groups_[m.group].path];
        auto bind = m.bind;
        if (m.wheelRadius > 0)
            bind = MatrixMultiply(MatrixRotateX(float(std::fmod(path.travel / m.wheelRadius, 2 * Pi))), bind);
        // Keep the imported matrices bit-for-bit at rest, including reflection/shear.
        const auto pose = path.travel == 0 ? m.rest : MatrixMultiply(bind, frames[m.group]);
        poses_[m.index] = {pose, objectBounds(m.local, pose), true};
    }
}
bool ObjectAnimationSystem::setPathMotion(const std::string &id, float speed, float acceleration) {
    if (!std::isfinite(speed) || !std::isfinite(acceleration) || speed < 0 || acceleration <= 0)
        return false;
    bool found = false;
    for (auto &path : paths_)
        if (id == "*" || path.definition.id == id) {
            path.definition.speed = speed;
            path.definition.acceleration = acceleration;
            path.definition.dwell = 0;
            path.wait = 0;
            found = true;
        }
    return found;
}
void ObjectAnimationSystem::stepPaths(std::optional<Vector3> player) {
    if (paths_.empty())
        return;
    struct State {
        double travel;
        float position, speed, wait;
    };
    std::vector<State> previous;
    for (auto &p : paths_) {
        previous.push_back({p.travel, p.position, p.speed, p.wait});
        if (p.wait > 0) {
            p.wait = std::max(0.f, p.wait - float(MotionTick));
            continue;
        }
        const float remaining = p.length - p.position;
        const bool station = p.definition.dwell > 0;
        const float limit = station
            ? std::min(p.definition.speed, std::sqrt(2 * p.definition.acceleration * remaining))
            : p.definition.speed;
        const float speed =
            p.speed + std::clamp(limit - p.speed, -p.definition.acceleration * float(MotionTick),
                                 p.definition.acceleration * float(MotionTick));
        const float advance = (p.speed + speed) * .5f * float(MotionTick);
        const float travel = station ? std::min(remaining, advance) : advance;
        p.speed = speed;
        p.position += travel;
        p.travel += travel;
        if (remaining - travel < .00001f) {
            p.position = station ? 0 : std::fmod(p.position, p.length);
            if (station) {
                p.speed = 0;
                p.wait = p.definition.dwell;
            }
        }
    }
    evaluateGroups();
    if (!player)
        return;
    // A blocked route waits as one convoy, so its trains cannot catch each other.
    std::vector<bool> blocked(paths_.size(), false);
    for (size_t n = 0; n < solids_.size(); ++n)
        if (solids_[n].contains(*player, .9f))
            blocked[groups_[n].path] = true;
    bool changed = false;
    for (size_t n = 0; n < paths_.size(); ++n)
        if (blocked[n]) {
            auto &p = paths_[n];
            const auto &old = previous[n];
            p.travel = old.travel;
            p.position = old.position;
            p.wait = old.wait;
            p.speed = 0;
            changed = true;
        }
    if (changed)
        evaluateGroups();
}
} // namespace dw
