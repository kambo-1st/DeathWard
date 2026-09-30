#include "world/HubWorld.hpp"
#include "world/TownNavigation.hpp"
#include <cstring>
#include <fstream>
#include <queue>
#include <stdexcept>

namespace dw {
bool HubWorld::load(const std::filesystem::path &path) {
    heights_.clear();
    solids_.clear();
    occupied_.clear();
    occupiedCells_.clear();
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
        if (!f || (std::memcmp(magic, "DWTNAV01", 8) && std::memcmp(magic, "DWTNAV02", 8) && std::memcmp(magic, "DWTNAV03", 8)) || !width_ || !depth_ || width_ > 4096 || depth_ > 4096 ||
            !std::isfinite(cell_) || cell_ < .1f || cell_ > 2 || !std::isfinite(minX_) ||
            !std::isfinite(minZ_))
            throw std::runtime_error("The town navigation asset is missing or invalid.");
        heights_.resize(size_t(width_) * depth_);
        occupied_.resize(heights_.size(), false);
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
    // Use the same precision for cell lookup and boundary crossings. Float
    // cancellation near a grid line can otherwise block very small NPC steps.
    const int x = int(std::floor((double(p.x) - minX_) / cell_)),
              z = int(std::floor((double(p.z) - minZ_) / cell_));
    return x >= 0 && z >= 0 && x < int(width_) && z < int(depth_) ? z * int(width_) + x : -1;
}
Vector3 HubWorld::point(int i) const {
    return {minX_ + (float(i % int(width_)) + .5f) * cell_, heights_[size_t(i)],
            minZ_ + (float(i / int(width_)) + .5f) * cell_};
}
void HubWorld::setMovingSolids(const std::vector<MovingSolid> &solids) {
    for (const auto i : occupiedCells_)
        occupied_[i] = false;
    occupiedCells_.clear();
    solids_ = solids;
    if (!loaded())
        return;
    const float clearance = .45f + cell_ * .7072f;
    for (const auto &solid : solids_) {
        const auto b = solid.bounds();
        const int x0 = std::max(0, int(std::floor((b.min.x - clearance - minX_) / cell_)));
        const int x1 = std::min(int(width_) - 1, int(std::floor((b.max.x + clearance - minX_) / cell_)));
        const int z0 = std::max(0, int(std::floor((b.min.z - clearance - minZ_) / cell_)));
        const int z1 = std::min(int(depth_) - 1, int(std::floor((b.max.z + clearance - minZ_) / cell_)));
        for (int z = z0; z <= z1; ++z)
            for (int x = x0; x <= x1; ++x) {
                const size_t at = size_t(z) * width_ + size_t(x);
                if (occupied_[at] || !std::isfinite(heights_[at]))
                    continue;
                if (solid.contains(add(point(int(at)), {0, .85f, 0}), clearance)) {
                    occupied_[at] = true;
                    occupiedCells_.push_back(at);
                }
            }
    }
}
bool HubWorld::walkable(Vector3 p) const {
    const int i = index(p);
    return i >= 0 && std::isfinite(heights_[size_t(i)]) && !occupied_[size_t(i)];
}
float HubWorld::height(Vector3 p) const {
    const int i = index(p);
    return i >= 0 ? heights_[size_t(i)] : std::numeric_limits<float>::quiet_NaN();
}
bool HubWorld::traversable(int from, int to) const {
    return from >= 0 && to >= 0 && !occupied_[size_t(to)] && std::isfinite(heights_[size_t(to)]) &&
           std::abs(heights_[size_t(from)] - heights_[size_t(to)]) <= .6f;
}
bool HubWorld::clear(Vector3 from, Vector3 to) const {
    int current = index(from);
    const int goal = index(to);
    if (!walkable(from) || !walkable(to))
        return false;
    int x = current % int(width_), z = current / int(width_);
    const double dx = double(to.x) - from.x, dz = double(to.z) - from.z;
    const int sx = dx > 0 ? 1 : -1, sz = dz > 0 ? 1 : -1;
    const double infinity = std::numeric_limits<double>::infinity();
    const double stepX = dx != 0 ? cell_ / std::abs(dx) : infinity;
    const double stepZ = dz != 0 ? cell_ / std::abs(dz) : infinity;
    double crossX = dx != 0 ? (minX_ + double(x + (sx > 0)) * cell_ - from.x) / dx : infinity;
    double crossZ = dz != 0 ? (minZ_ + double(z + (sz > 0)) * cell_ - from.z) / dz : infinity;
    // Check every crossed cell, including both sides of an exact corner. Point
    // sampling can miss a thin corner and produce a shortcut through a barrier.
    while (current != goal) {
        const bool both = std::abs(crossX - crossZ) < .000001f;
        const bool moveX = both || crossX < crossZ, moveZ = both || crossZ < crossX;
        const int nx = x + (moveX ? sx : 0), nz = z + (moveZ ? sz : 0);
        if (nx < 0 || nz < 0 || nx >= int(width_) || nz >= int(depth_))
            return false;
        const int next = nz * int(width_) + nx;
        if (!traversable(current, next))
            return false;
        if (both &&
            (!traversable(current, z * int(width_) + nx) || !traversable(current, nz * int(width_) + x) ||
             !traversable(z * int(width_) + nx, next) || !traversable(nz * int(width_) + x, next)))
            return false;
        if (moveX)
            crossX += stepX;
        if (moveZ)
            crossZ += stepZ;
        x = nx;
        z = nz;
        current = next;
    }
    return true;
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
    auto route = findRoute(player.position, target);
    if (!route) return false;
    route_ = std::move(*route);
    next_ = 0;
    return true;
}
void HubWorld::setNavigation(const TownNavigation &nav) {
    width_ = nav.width; depth_ = nav.depth; minX_ = nav.minX; minZ_ = nav.minZ; cell_ = nav.cell;
    heights_ = nav.heights; spawn = nav.spawn; mission = nav.mission;
    solids_.clear(); occupiedCells_.clear(); occupied_.assign(heights_.size(), false);
    reset();
}
std::optional<std::vector<Vector3>> HubWorld::findRoute(Vector3 from, Vector3 target) const {
    const int start = index(from);
    if (start < 0 || !walkable(from) || !std::isfinite(target.x) || !std::isfinite(target.z))
        return std::nullopt;
    int end = index(target);
    if (end < 0 || !walkable(target)) {
        float best = 36;
        for (size_t i = 0; i < heights_.size(); ++i) {
            if (!std::isfinite(heights_[i]) || occupied_[i])
                continue;
            auto d = sub(point(int(i)), target);
            d.y = 0;
            if (dot(d, d) < best) {
                best = dot(d, d);
                end = int(i);
            }
        }
        if (best == 36)
            return std::nullopt;
        target = point(end);
    }
    target.y = height(target);
    if (clear(from, target)) {
        return std::vector<Vector3>{target};
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
        return std::nullopt;
    std::vector<Vector3> waypoints;
    for (int at = end;; at = previous[size_t(at)]) {
        waypoints.push_back(point(at));
        if (at == start)
            break;
    }
    std::reverse(waypoints.begin(), waypoints.end());
    waypoints.push_back(target); // Keep the exact click instead of the grid-cell center.
    std::vector<Vector3> smooth;
    Vector3 anchor = from;
    for (size_t i = 0; i < waypoints.size();) {
        size_t farthest = i;
        if (!clear(anchor, waypoints[i]))
            return std::nullopt;
        while (farthest + 1 < waypoints.size() && clear(anchor, waypoints[farthest + 1]))
            ++farthest;
        smooth.push_back(waypoints[farthest]);
        anchor = waypoints[farthest];
        i = farthest + 1;
    }
    return smooth;
}
void HubWorld::step(Vector3 movement, float dt) {
    if (!loaded())
        return;
    dt = std::clamp(dt, 0.0f, .1f);
    time += dt;
    repathWait_ = std::max(0.f, repathWait_ - dt);
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
            if (length(delta) < .00001f) {
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
                if (!direct && repathWait_ <= 0) {
                    const auto target = destination();
                    if (target && walkable(*target))
                        moveTo(*target);
                    repathWait_ = .4f;
                }
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
    if (!loaded() || ray.direction.y >= -.001f)
        return {};
    // Intersect each crossed terrain cell analytically. Fixed-distance ray
    // marching could step past small visible patches or shift the clicked point.
    float enter = 0, leave = 700;
    auto clip = [&](float origin, float direction, float low, float high) {
        if (std::abs(direction) < .000001f)
            return origin >= low && origin < high;
        float a = (low - origin) / direction, b = (high - origin) / direction;
        if (a > b)
            std::swap(a, b);
        enter = std::max(enter, a);
        leave = std::min(leave, b);
        return enter <= leave;
    };
    if (!clip(ray.position.x, ray.direction.x, minX_, minX_ + width_ * cell_) ||
        !clip(ray.position.z, ray.direction.z, minZ_, minZ_ + depth_ * cell_))
        return {};
    auto first = add(ray.position, mul(ray.direction, enter));
    int x = std::clamp(int(std::floor((first.x - minX_) / cell_)), 0, int(width_) - 1);
    int z = std::clamp(int(std::floor((first.z - minZ_) / cell_)), 0, int(depth_) - 1);
    const int sx = ray.direction.x > 0 ? 1 : -1, sz = ray.direction.z > 0 ? 1 : -1;
    const float infinity = std::numeric_limits<float>::infinity();
    const float stepX = ray.direction.x != 0 ? cell_ / std::abs(ray.direction.x) : infinity;
    const float stepZ = ray.direction.z != 0 ? cell_ / std::abs(ray.direction.z) : infinity;
    float crossX = ray.direction.x != 0
                       ? (minX_ + float(x + (sx > 0)) * cell_ - ray.position.x) / ray.direction.x
                       : infinity;
    float crossZ = ray.direction.z != 0
                       ? (minZ_ + float(z + (sz > 0)) * cell_ - ray.position.z) / ray.direction.z
                       : infinity;
    while (x >= 0 && z >= 0 && x < int(width_) && z < int(depth_) && enter <= leave) {
        const float exit = std::min({crossX, crossZ, leave});
        const float h = heights_[size_t(z) * width_ + size_t(x)];
        const float t = (h - ray.position.y) / ray.direction.y;
        if (std::isfinite(h) && t >= enter - .00001f && t <= exit + .00001f) {
            auto hit = add(ray.position, mul(ray.direction, t));
            hit.y = h;
            return hit;
        }
        if (exit >= leave)
            break;
        const bool both = std::abs(crossX - crossZ) < .000001f;
        const bool moveX = both || crossX < crossZ, moveZ = both || crossZ < crossX;
        enter = exit;
        if (moveX) {
            x += sx;
            crossX += stepX;
        }
        if (moveZ) {
            z += sz;
            crossZ += stepZ;
        }
    }
    // Like mission clicks on cover, a blocked ground click still requests the
    // nearest walkable edge. The navigation grid has no height in blocked cells.
    const float t = (player.position.y - .85f - ray.position.y) / ray.direction.y;
    const auto projected = add(ray.position, mul(ray.direction, t));
    if (t >= 0 && t <= leave && index(projected) >= 0)
        return projected;
    return {};
}
} // namespace dw
