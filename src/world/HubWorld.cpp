#include "world/HubWorld.hpp"
#include <cstring>
#include <fstream>
#include <queue>
#include <stdexcept>

namespace dw {
bool HubWorld::load(const std::filesystem::path &path) {
    heights_.clear();
    error.clear();
    try {
        std::ifstream f(path, std::ios::binary);
        char magic[8]{};
        f.read(magic, 8);
        auto read = [&](auto &value) { f.read(reinterpret_cast<char *>(&value), sizeof(value)); };
        read(width_);
        read(depth_);
        read(minX_);
        read(minZ_);
        read(cell_);
        read(spawn.x);
        read(spawn.y);
        read(spawn.z);
        read(mission.x);
        read(mission.y);
        read(mission.z);
        if (!f || std::memcmp(magic, "DWTNAV01", 8) || !width_ || !depth_ || width_ > 4096 || depth_ > 4096 ||
            !std::isfinite(cell_) || cell_ < .1f || cell_ > 2 || !std::isfinite(minX_) ||
            !std::isfinite(minZ_))
            throw std::runtime_error("The town navigation asset is missing or invalid.");
        heights_.resize(size_t(width_) * depth_);
        f.read(reinterpret_cast<char *>(heights_.data()), std::streamsize(heights_.size() * sizeof(float)));
        if (!f || !walkable(spawn) || !walkable(mission))
            throw std::runtime_error("The town has no valid arrival or mission entrance.");
        reset();
        return true;
    } catch (const std::exception &e) {
        error = e.what();
        heights_.clear();
        return false;
    }
}
int HubWorld::index(Vector3 p) const {
    if (!loaded() || !std::isfinite(p.x) || !std::isfinite(p.z))
        return -1;
    const int x = int(std::floor((p.x - minX_) / cell_)), z = int(std::floor((p.z - minZ_) / cell_));
    return x >= 0 && z >= 0 && x < int(width_) && z < int(depth_) ? z * int(width_) + x : -1;
}
Vector3 HubWorld::point(int i) const {
    return {minX_ + (float(i % int(width_)) + .5f) * cell_, heights_[size_t(i)],
            minZ_ + (float(i / int(width_)) + .5f) * cell_};
}
bool HubWorld::walkable(Vector3 p) const {
    const int i = index(p);
    return i >= 0 && std::isfinite(heights_[size_t(i)]);
}
float HubWorld::height(Vector3 p) const {
    const int i = index(p);
    return i >= 0 ? heights_[size_t(i)] : std::numeric_limits<float>::quiet_NaN();
}
bool HubWorld::traversable(int from, int to) const {
    return from >= 0 && to >= 0 && std::isfinite(heights_[size_t(to)]) &&
           std::abs(heights_[size_t(from)] - heights_[size_t(to)]) <= .6f;
}
void HubWorld::reset() {
    player = {};
    player.position = add(spawn, {0, .85f, 0});
    player.aim = mission;
    stop();
}
void HubWorld::stop() {
    route_.clear();
    next_ = 0;
    player.velocity = {};
}
bool HubWorld::nearMission() const {
    auto d = sub(player.position, mission);
    d.y = 0;
    return length(d) < 3;
}
size_t HubWorld::walkableCells() const {
    return size_t(std::count_if(heights_.begin(), heights_.end(), [](float h) { return std::isfinite(h); }));
}
std::optional<Vector3> HubWorld::destination() const {
    return next_ < route_.size() ? std::optional(route_.back()) : std::nullopt;
}
bool HubWorld::moveTo(Vector3 target) {
    const int start = index(player.position);
    if (start < 0)
        return false;
    int end = index(target);
    if (end < 0 || !walkable(target)) {
        float best = 36;
        for (size_t i = 0; i < heights_.size(); ++i) {
            if (!std::isfinite(heights_[i]))
                continue;
            auto d = sub(point(int(i)), target);
            d.y = 0;
            if (dot(d, d) < best) {
                best = dot(d, d);
                end = int(i);
            }
        }
        if (best == 36)
            return false;
    }
    std::vector<float> costs(heights_.size(), std::numeric_limits<float>::infinity());
    std::vector<int> previous(heights_.size(), -1);
    using Entry = std::pair<float, int>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> open;
    auto heuristic = [&](int a) {
        return float(std::abs(a % int(width_) - end % int(width_)) +
                     std::abs(a / int(width_) - end / int(width_)));
    };
    costs[size_t(start)] = 0;
    open.push({heuristic(start), start});
    while (!open.empty()) {
        auto [priority, at] = open.top();
        open.pop();
        if (priority > costs[size_t(at)] + heuristic(at) + .01f)
            continue;
        if (at == end)
            break;
        const int x = at % int(width_), z = at / int(width_);
        for (const auto &[dx, dz] : std::array<std::pair<int, int>, 4>{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}}) {
            const int xx = x + dx, zz = z + dz;
            if (xx < 0 || zz < 0 || xx >= int(width_) || zz >= int(depth_))
                continue;
            const int next = zz * int(width_) + xx;
            if (!traversable(at, next))
                continue;
            const float cost = costs[size_t(at)] + 1;
            if (cost >= costs[size_t(next)])
                continue;
            costs[size_t(next)] = cost;
            previous[size_t(next)] = at;
            open.push({cost + heuristic(next), next});
        }
    }
    if (start != end && previous[size_t(end)] < 0)
        return false;
    route_.clear();
    next_ = 0;
    for (int at = end; at != start; at = previous[size_t(at)])
        route_.push_back(point(at));
    std::reverse(route_.begin(), route_.end());
    if (route_.empty())
        route_.push_back(point(end));
    return true;
}
void HubWorld::step(Vector3 movement, float dt) {
    if (!loaded())
        return;
    dt = std::clamp(dt, 0.0f, .1f);
    time += dt;
    movement.y = 0;
    const bool direct = length(movement) > .01f;
    if (direct)
        stop();
    const auto previous = player.position;
    float remaining = 6 * dt;
    while (remaining > .0001f) {
        Vector3 direction{};
        float travel = std::min(remaining, .08f);
        if (direct)
            direction = unit(movement);
        else if (next_ < route_.size()) {
            auto delta = sub(route_[next_], player.position);
            delta.y = 0;
            if (length(delta) < .025f) {
                ++next_;
                continue;
            }
            direction = unit(delta);
            travel = std::min(travel, length(delta));
        } else
            break;
        auto candidate = add(player.position, mul(direction, travel));
        if (!traversable(index(player.position), index(candidate))) {
            auto x = player.position;
            x.x = candidate.x;
            auto z = player.position;
            z.z = candidate.z;
            if (direct && traversable(index(player.position), index(x)))
                candidate = x;
            else if (direct && traversable(index(player.position), index(z)))
                candidate = z;
            else {
                if (!direct)
                    stop();
                break;
            }
        }
        candidate.y = height(candidate) + .85f;
        player.position = candidate;
        remaining -= travel;
    }
    player.velocity = dt > 0 ? mul(sub(player.position, previous), 1 / dt) : Vector3{};
    player.velocity.y = 0;
    if (length(player.velocity) > .05f)
        player.facing = unit(player.velocity);
}
std::optional<Vector3> HubWorld::pickGround(Ray ray) const {
    if (ray.direction.y >= -.001f)
        return {};
    // March the terrain heightfield instead of intersecting a flat y=0 plane.
    for (float t = 0; t < 700; t += .2f) {
        const auto p = add(ray.position, mul(ray.direction, t));
        const float h = height(p);
        if (std::isfinite(h) && p.y <= h && p.y > h - .5f)
            return Vector3{p.x, h, p.z};
    }
    return {};
}
} // namespace dw
