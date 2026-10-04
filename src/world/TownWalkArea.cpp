#include "world/TownDocument.hpp"
#include <stdexcept>

namespace dw {
namespace {
double turn(Vector3 a, Vector3 b, Vector3 c) {
    return (double(b.x) - a.x) * (double(c.z) - a.z) - (double(b.z) - a.z) * (double(c.x) - a.x);
}
float segmentDistance(Vector3 p, Vector3 a, Vector3 b) {
    const double dx = double(b.x) - a.x, dz = double(b.z) - a.z;
    const double t = std::clamp(((p.x - a.x) * dx + (p.z - a.z) * dz) /
                                  std::max(1e-12, dx * dx + dz * dz), 0., 1.);
    return float(std::hypot(p.x - a.x - t * dx, p.z - a.z - t * dz));
}
bool intersects(Vector3 a, Vector3 b, Vector3 c, Vector3 d) {
    const auto abC = turn(a, b, c), abD = turn(a, b, d), cdA = turn(c, d, a), cdB = turn(c, d, b);
    return ((abC > 0) != (abD > 0) && (cdA > 0) != (cdB > 0)) ||
           segmentDistance(a, c, d) < .0001f || segmentDistance(b, c, d) < .0001f ||
           segmentDistance(c, a, b) < .0001f || segmentDistance(d, a, b) < .0001f;
}
} // namespace
void TownWalkArea::validate() const {
    if (id.empty() || id.size() > 128 || id.find_first_of(" \t\r\n") != std::string::npos ||
        points.size() < 3 || points.size() > 128)
        throw std::runtime_error("A walk area needs a unique name and 3-128 points.");
    double area = 0;
    for (size_t i = 0; i < points.size(); ++i) {
        const auto a = points[i], b = points[(i + 1) % points.size()];
        if (!std::isfinite(a.x) || !std::isfinite(a.y) || !std::isfinite(a.z) || length(a) > 10000 ||
            std::hypot(a.x - b.x, a.z - b.z) < .1f)
            throw std::runtime_error("Walk-area points must be finite and at least 0.1 m apart.");
        area += double(a.x) * b.z - double(b.x) * a.z;
        for (size_t j = i + 1; j < points.size(); ++j) {
            if (j == i + 1 || (i == 0 && j + 1 == points.size())) continue;
            if (intersects(a, b, points[j], points[(j + 1) % points.size()]))
                throw std::runtime_error("Walk-area edges cannot cross or touch each other.");
        }
    }
    if (std::abs(area) < .02)
        throw std::runtime_error("A walk area must enclose ground, not a straight line.");
}
float TownWalkArea::edgeDistance(Vector3 p) const {
    float distance = std::numeric_limits<float>::infinity();
    for (size_t i = 0; i < points.size(); ++i)
        distance = std::min(distance, segmentDistance(p, points[i], points[(i + 1) % points.size()]));
    return distance;
}
bool TownWalkArea::contains(Vector3 p) const {
    bool inside = false;
    for (size_t i = 0; i < points.size(); ++i) {
        const auto a = points[i], b = points[(i + 1) % points.size()];
        if (std::abs(turn(a, b, p)) < .00001 &&
            p.x >= std::min(a.x, b.x) - .00001f && p.x <= std::max(a.x, b.x) + .00001f &&
            p.z >= std::min(a.z, b.z) - .00001f && p.z <= std::max(a.z, b.z) + .00001f) return true;
        if ((a.z > p.z) != (b.z > p.z) &&
            double(p.x) < a.x + (double(b.x) - a.x) * (double(p.z) - a.z) / (double(b.z) - a.z))
            inside = !inside;
    }
    return inside;
}
bool TownDocument::walkAllowed(Vector3 p, float blockedMargin) const {
    bool limited = false, inside = false;
    for (const auto &area : walkAreas) {
        if (area.blocked) {
            if (area.contains(p) || (blockedMargin > 0 && area.edgeDistance(p) <= blockedMargin)) return false;
        } else {
            limited = true;
            inside |= area.contains(p);
        }
    }
    return !limited || inside;
}
std::string TownDocument::nextWalkAreaId() const {
    for (size_t n = 1;; ++n) {
        auto id = "walk-area-" + std::to_string(n);
        if (std::none_of(walkAreas.begin(), walkAreas.end(), [&](const auto &a) { return a.id == id; })) return id;
    }
}
} // namespace dw
