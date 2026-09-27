#include "world/TownDocument.hpp"
#include "raymath.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

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
    for (const auto &i : instances) {
        const auto values = MatrixToFloatV(i.transform);
        for (float v : values.v)
            if (!std::isfinite(v) || std::abs(v) > 1000000)
                throw std::runtime_error("Invalid object transform.");
        if (i.asset >= assets.size() || std::abs(MatrixDeterminant(i.transform)) < 1e-10f ||
            std::abs(i.transform.m3) + std::abs(i.transform.m7) + std::abs(i.transform.m11) > .0001f ||
            std::abs(i.transform.m15 - 1) > .0001f)
            throw std::runtime_error("Invalid object reference or singular transform.");
    }
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
        if (!(in >> token >> version) || token != "DEATHWARD_TOWN" || version != 1)
            throw std::runtime_error("Missing or unsupported town scene.");
        TownDocument candidate;
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
                readMatrix(in, i.transform);
                candidate.instances.push_back(i);
            } else if (token == "light") {
                TownLight l;
                in >> l.type >> l.position.x >> l.position.y >> l.position.z >> l.direction.x >>
                    l.direction.y >> l.direction.z >> l.color.x >> l.color.y >> l.color.z >> l.intensity >>
                    l.range;
                candidate.lights.push_back(l);
            } else
                throw std::runtime_error("Unknown town scene entry: " + token);
            if (!in || candidate.assets.size() > 100000 || candidate.instances.size() > 100000)
                throw std::runtime_error("Truncated or oversized town scene.");
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
    out << std::setprecision(std::numeric_limits<float>::max_digits10) << "DEATHWARD_TOWN 1\n";
    for (const auto &a : assets)
        out << "asset " << a.name << ' ' << a.first << ' ' << a.count << ' ' << a.unlit << ' '
            << a.bounds.min.x << ' ' << a.bounds.min.y << ' ' << a.bounds.min.z << ' ' << a.bounds.max.x
            << ' ' << a.bounds.max.y << ' ' << a.bounds.max.z << '\n';
    for (const auto &i : instances) {
        out << "instance " << i.asset << ' ';
        writeMatrix(out, i.transform);
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
    const auto b = assets.at(i.asset).bounds;
    Box result{{1e9f, 1e9f, 1e9f}, {-1e9f, -1e9f, -1e9f}};
    for (float x : {b.min.x, b.max.x})
        for (float y : {b.min.y, b.max.y})
            for (float z : {b.min.z, b.max.z}) {
                const auto p = Vector3Transform({x, y, z}, i.transform);
                result.min = Vector3Min(result.min, p);
                result.max = Vector3Max(result.max, p);
            }
    return result;
}
} // namespace dw
