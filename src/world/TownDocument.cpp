#include "world/TownDocument.hpp"
#include "raymath.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

namespace dw {
namespace {
void readMatrix(std::istream &in, Matrix &m) {
    in >> m.m0 >> m.m4 >> m.m8 >> m.m12 >> m.m1 >> m.m5 >> m.m9 >> m.m13 >> m.m2 >> m.m6 >> m.m10 >> m.m14 >>
        m.m3 >> m.m7 >> m.m11 >> m.m15;
}
void writeMatrix(std::ostream &out, Matrix m) {
    out << m.m0 << ' ' << m.m4 << ' ' << m.m8 << ' ' << m.m12 << ' ' << m.m1 << ' ' << m.m5 << ' ' << m.m9
        << ' ' << m.m13 << ' ' << m.m2 << ' ' << m.m6 << ' ' << m.m10 << ' ' << m.m14 << ' ' << m.m3 << ' '
        << m.m7 << ' ' << m.m11 << ' ' << m.m15;
}
bool finite(Vector3 p) {
    return std::isfinite(p.x) && std::isfinite(p.y) && std::isfinite(p.z);
}
} // namespace
const char *motionName(ObjectMotionKind kind) {
    switch (kind) {
    case ObjectMotionKind::Spin:
        return "Spin";
    case ObjectMotionKind::Sway:
        return "Sway";
    case ObjectMotionKind::Tumbleweed:
        return "Tumbleweed";
    default:
        return "Static";
    }
}
std::string TownDocument::nextInstanceId() const {
    std::unordered_set<std::string> ids;
    for (const auto &i : instances)
        ids.insert(i.id);
    for (size_t n = 1;; ++n) {
        auto id = "object-" + std::to_string(n);
        if (!ids.contains(id))
            return id;
    }
}
std::string TownDocument::nextCharacterId() const {
    for (size_t n = 1;; ++n) {
        auto id = "cowgirl-" + std::to_string(n);
        if (std::none_of(characters.begin(), characters.end(), [&](const auto &c) { return c.id == id; }))
            return id;
    }
}
int TownDocument::meshCount() const {
    return assets.empty() ? 0 : assets.back().first + assets.back().count;
}
void TownDocument::validate() const {
    if (assets.empty() || instances.empty() || assets.size() > 100000 || instances.size() > 100000)
        throw std::runtime_error("The town must contain assets and at least one object.");
    int next = 0;
    for (const auto &a : assets) {
        if (a.name.empty() || a.name.find_first_of(" \t\n\r") != std::string::npos || a.first != next ||
            a.count <= 0 || a.count > 100000 || !finite(a.bounds.min) || !finite(a.bounds.max) ||
            a.bounds.min.x > a.bounds.max.x || a.bounds.min.y > a.bounds.max.y ||
            a.bounds.min.z > a.bounds.max.z)
            throw std::runtime_error("Invalid town mesh catalog.");
        next += a.count;
    }
    auto validId = [](const std::string &s) {
        return !s.empty() && s.size() <= 128 && s.find_first_of(" \t\n\r") == std::string::npos;
    };
    if (characters.size() > 64)
        throw std::runtime_error("A town supports at most 64 characters.");
    std::unordered_set<std::string> characterIds;
    for (const auto &c : characters) {
        if (!validId(c.id) || !characterIds.insert(c.id).second || c.model != "cowgirl" ||
            !finite(c.position) || length(c.position) > 10000 || !std::isfinite(c.yaw) ||
            !std::isfinite(c.scale) || c.scale < .25f || c.scale > 3 ||
            !std::isfinite(c.speed) || c.speed < 0 || c.speed > 4 ||
            !std::isfinite(c.dwell) || c.dwell < 0 || c.dwell > 120 || c.stops.size() > 128)
            throw std::runtime_error("Invalid character placement or walking settings.");
        auto previous = c.position;
        for (const auto &stop : c.stops) {
            if (!finite(stop) || length(stop) > 10000 || distance(previous, stop) < .1f)
                throw std::runtime_error("Route stops must be finite and at least 0.1 m apart.");
            previous = stop;
        }
    }
    std::unordered_set<std::string> pathIds, groupIds;
    if (paths.size() > 256 || groups.size() > 4096)
        throw std::runtime_error("Too many motion paths or groups.");
    for (const auto &p : paths) {
        if (!validId(p.id) || !pathIds.insert(p.id).second || !std::isfinite(p.speed) || p.speed < 0 ||
            p.speed > 10 || !std::isfinite(p.acceleration) || p.acceleration < .1f || p.acceleration > 5 ||
            !std::isfinite(p.dwell) || p.dwell < 0 || p.dwell > 120 || p.points.size() < 3 ||
            p.points.size() > 4096)
            throw std::runtime_error("Invalid motion path.");
        for (size_t n = 0; n < p.points.size(); ++n) {
            const auto a = p.points[n], b = p.points[(n + 1) % p.points.size()];
            if (!finite(a) || length(a) > 10000 || distance(a, b) < .001f || distance(a, b) > 15 ||
                std::abs(a.y - b.y) > .001f)
                throw std::runtime_error("Motion path must be a continuous level loop.");
        }
    }
    for (const auto &g : groups) {
        if (!validId(g.id) || !groupIds.insert(g.id).second || !pathIds.contains(g.path) ||
            !std::isfinite(g.offset) || std::abs(g.offset) > 100000 || !std::isfinite(g.wheelbase) ||
            g.wheelbase < 0 || g.wheelbase > 30)
            throw std::runtime_error("Invalid motion group or path binding.");
        const auto &p =
            *std::find_if(paths.begin(), paths.end(), [&](const auto &p) { return p.id == g.path; });
        float length = 0;
        for (size_t n = 0; n < p.points.size(); ++n)
            length += distance(p.points[n], p.points[(n + 1) % p.points.size()]);
        if (length < std::max(1.f, g.wheelbase * 2))
            throw std::runtime_error("The rail loop is too short for this vehicle.");
    }
    std::unordered_set<std::string> ids, usedGroups;
    for (const auto &i : instances) {
        if ((!i.group.empty() && (!groupIds.contains(i.group) || i.motion.kind != ObjectMotionKind::None)) ||
            !std::isfinite(i.wheelRadius) || i.wheelRadius < 0 ||
            (i.wheelRadius > 0 && i.wheelRadius < .05f) || i.wheelRadius > 10 ||
            (i.wheelRadius > 0 && i.group.empty()))
            throw std::runtime_error("Invalid vehicle or wheel binding.");
        usedGroups.insert(i.group);
        if (!i.id.empty() && (i.id.size() > 128 || i.id.find_first_of(" \t\n\r") != std::string::npos ||
                              !ids.insert(i.id).second))
            throw std::runtime_error("Invalid or duplicate object ID.");
        const auto &m = i.motion;
        if (int(m.kind) < 0 || int(m.kind) > int(ObjectMotionKind::Tumbleweed) || !std::isfinite(m.speed) ||
            m.speed < 0 || m.speed > 360 || (m.kind == ObjectMotionKind::Tumbleweed && m.speed > 5) ||
            !std::isfinite(m.amplitude) || m.amplitude < 0 || m.amplitude > 90 ||
            (m.kind == ObjectMotionKind::Tumbleweed && m.amplitude > .25f) || !std::isfinite(m.period) ||
            m.period < .5f || m.period > 120 || !finite(m.axis) || length(m.axis) < .001f ||
            length(m.axis) > 10000 || !finite(m.pivot) || length(m.pivot) > 10000)
            throw std::runtime_error("Invalid object animation settings.");
        const auto values = MatrixToFloatV(i.transform);
        for (float v : values.v)
            if (!std::isfinite(v) || std::abs(v) > 1000000)
                throw std::runtime_error("Invalid object transform.");
        if (i.asset >= assets.size() || std::abs(MatrixDeterminant(i.transform)) < 1e-10f ||
            std::abs(i.transform.m3) + std::abs(i.transform.m7) + std::abs(i.transform.m11) > .0001f ||
            std::abs(i.transform.m15 - 1) > .0001f)
            throw std::runtime_error("Invalid object reference or singular transform.");
    }
    for (const auto &g : groups)
        if (!usedGroups.contains(g.id))
            throw std::runtime_error("A motion group must contain objects.");
    for (const auto &l : lights)
        if (!finite(l.position) || !finite(l.direction) || !finite(l.color) || !std::isfinite(l.intensity) ||
            !std::isfinite(l.range))
            throw std::runtime_error("Invalid town light.");
}
bool TownDocument::load(const std::filesystem::path &path, std::string &error) {
    try {
        std::ifstream in(path);
        std::string token;
        int version = 0;
        if (!(in >> token >> version) || token != "DEATHWARD_TOWN" || (version < 1 || version > 4))
            throw std::runtime_error("Missing or unsupported town scene.");
        TownDocument candidate;
        std::vector<std::pair<std::string, ObjectMotion>> motions;
        struct Binding {
            std::string id, group;
            float radius;
        };
        std::vector<Binding> bindings;
        while (in >> token) {
            if (token == "asset") {
                TownAsset a;
                in >> a.name >> a.first >> a.count >> a.unlit >> a.bounds.min.x >> a.bounds.min.y >>
                    a.bounds.min.z >> a.bounds.max.x >> a.bounds.max.y >> a.bounds.max.z;
                a.label = a.name;
                candidate.assets.push_back(a);
            } else if (token == "instance") {
                TownInstance i;
                in >> i.asset;
                if (version >= 2)
                    in >> i.id;
                else
                    i.id = "legacy-" + std::to_string(candidate.instances.size() + 1);
                readMatrix(in, i.transform);
                candidate.instances.push_back(i);
            } else if (token == "motion" && version >= 2) {
                std::string id;
                ObjectMotion m;
                int kind = 0;
                in >> id >> kind >> m.speed >> m.amplitude >> m.period >> m.seed >> m.axis.x >> m.axis.y >>
                    m.axis.z >> m.pivot.x >> m.pivot.y >> m.pivot.z;
                m.kind = ObjectMotionKind(kind);
                motions.emplace_back(id, m);
            } else if (token == "path" && version >= 3) {
                TownMotionPath p;
                size_t count = 0;
                in >> p.id >> p.speed >> p.acceleration >> p.dwell >> count;
                if (!in || count > 4096)
                    throw std::runtime_error("Invalid path point count.");
                p.points.resize(count);
                for (auto &point : p.points)
                    in >> point.x >> point.y >> point.z;
                candidate.paths.push_back(std::move(p));
            } else if (token == "group" && version >= 3) {
                TownMotionGroup g;
                in >> g.id >> g.path >> g.offset >> g.wheelbase;
                candidate.groups.push_back(g);
            } else if (token == "member" && version >= 3) {
                Binding b;
                in >> b.id >> b.group >> b.radius;
                bindings.push_back(b);
            } else if (token == "character" && version >= 4) {
                TownCharacter c;
                size_t count = 0;
                int loop = 0;
                in >> c.id >> c.model >> c.position.x >> c.position.y >> c.position.z >> c.yaw >>
                    c.scale >> c.speed >> c.dwell >> loop >> count;
                if (!in || count > 128 || (loop != 0 && loop != 1))
                    throw std::runtime_error("Invalid character route.");
                c.loop = loop != 0;
                c.stops.resize(count);
                for (auto &p : c.stops) in >> p.x >> p.y >> p.z;
                candidate.characters.push_back(std::move(c));
            } else if (token == "light") {
                TownLight l;
                in >> l.type >> l.position.x >> l.position.y >> l.position.z >> l.direction.x >>
                    l.direction.y >> l.direction.z >> l.color.x >> l.color.y >> l.color.z >> l.intensity >>
                    l.range;
                candidate.lights.push_back(l);
            } else
                throw std::runtime_error("Unknown town scene entry: " + token);
            if (!in || candidate.assets.size() > 100000 || candidate.instances.size() > 100000 ||
                motions.size() > 100000 || bindings.size() > 100000 || candidate.paths.size() > 256 ||
                candidate.groups.size() > 4096 || candidate.characters.size() > 64)
                throw std::runtime_error("Truncated or oversized town scene.");
        }
        std::unordered_set<std::string> bound;
        for (const auto &[id, motion] : motions) {
            auto at = std::find_if(candidate.instances.begin(), candidate.instances.end(),
                                   [&](const auto &i) { return i.id == id; });
            if (at == candidate.instances.end() || !bound.insert(id).second)
                throw std::runtime_error("Animation references a missing or duplicate object.");
            at->motion = motion;
        }
        bound.clear();
        for (const auto &binding : bindings) {
            auto at = std::find_if(candidate.instances.begin(), candidate.instances.end(),
                                   [&](const auto &i) { return i.id == binding.id; });
            if (at == candidate.instances.end() || !bound.insert(binding.id).second)
                throw std::runtime_error("Vehicle references a missing or duplicate object.");
            at->group = binding.group;
            at->wheelRadius = binding.radius;
        }
        candidate.validate();
        // Optional human-readable labels do not change the original scene format.
        std::ifstream labels(path.parent_path() / "town.labels");
        std::string line;
        while (std::getline(labels, line)) {
            std::istringstream row(line);
            std::string key, label;
            row >> key >> std::ws;
            std::getline(row, label);
            for (auto &a : candidate.assets)
                if (a.name == key && !label.empty())
                    a.label = label;
        }
        *this = std::move(candidate);
        error.clear();
        return true;
    } catch (const std::exception &e) {
        error = e.what();
        return false;
    }
}
void TownDocument::write(const std::filesystem::path &path) const {
    validate();
    std::ofstream out(path, std::ios::trunc);
    auto identified = *this;
    for (auto &i : identified.instances)
        if (i.id.empty())
            i.id = identified.nextInstanceId();
    out << std::setprecision(std::numeric_limits<float>::max_digits10) << "DEATHWARD_TOWN "
        << (!characters.empty() ? 4 : paths.empty() ? 2 : 3) << '\n';
    for (const auto &a : assets)
        out << "asset " << a.name << ' ' << a.first << ' ' << a.count << ' ' << a.unlit << ' '
            << a.bounds.min.x << ' ' << a.bounds.min.y << ' ' << a.bounds.min.z << ' ' << a.bounds.max.x
            << ' ' << a.bounds.max.y << ' ' << a.bounds.max.z << '\n';
    for (const auto &i : identified.instances) {
        out << "instance " << i.asset << ' ' << i.id << ' ';
        writeMatrix(out, i.transform);
        out << '\n';
        if (!i.group.empty())
            out << "member " << i.id << ' ' << i.group << ' ' << i.wheelRadius << '\n';
        const auto &m = i.motion;
        if (m.kind != ObjectMotionKind::None)
            out << "motion " << i.id << ' ' << int(m.kind) << ' ' << m.speed << ' ' << m.amplitude << ' '
                << m.period << ' ' << m.seed << ' ' << m.axis.x << ' ' << m.axis.y << ' ' << m.axis.z << ' '
                << m.pivot.x << ' ' << m.pivot.y << ' ' << m.pivot.z << '\n';
    }
    for (const auto &p : paths) {
        out << "path " << p.id << ' ' << p.speed << ' ' << p.acceleration << ' ' << p.dwell << ' '
            << p.points.size();
        for (const auto &point : p.points)
            out << ' ' << point.x << ' ' << point.y << ' ' << point.z;
        out << '\n';
    }
    for (const auto &g : groups)
        out << "group " << g.id << ' ' << g.path << ' ' << g.offset << ' ' << g.wheelbase << '\n';
    for (const auto &c : characters) {
        out << "character " << c.id << ' ' << c.model << ' ' << c.position.x << ' ' << c.position.y << ' '
            << c.position.z << ' ' << c.yaw << ' ' << c.scale << ' ' << c.speed << ' ' << c.dwell << ' '
            << int(c.loop) << ' ' << c.stops.size();
        for (const auto &p : c.stops) out << ' ' << p.x << ' ' << p.y << ' ' << p.z;
        out << '\n';
    }
    for (const auto &l : lights)
        out << "light " << l.type << ' ' << l.position.x << ' ' << l.position.y << ' ' << l.position.z << ' '
            << l.direction.x << ' ' << l.direction.y << ' ' << l.direction.z << ' ' << l.color.x << ' '
            << l.color.y << ' ' << l.color.z << ' ' << l.intensity << ' ' << l.range << '\n';
    out.close();
    if (!out)
        throw std::runtime_error("Could not write town scene: " + path.string());
}
Box TownDocument::bounds(size_t instance) const {
    const auto &i = instances.at(instance);
    return objectBounds(assets.at(i.asset).bounds, i.transform);
}
Box objectBounds(Box b, Matrix transform) {
    Box result{{1e9f, 1e9f, 1e9f}, {-1e9f, -1e9f, -1e9f}};
    for (float x : {b.min.x, b.max.x})
        for (float y : {b.min.y, b.max.y})
            for (float z : {b.min.z, b.max.z}) {
                const auto p = Vector3Transform({x, y, z}, transform);
                result.min = Vector3Min(result.min, p);
                result.max = Vector3Max(result.max, p);
            }
    return result;
}
} // namespace dw
