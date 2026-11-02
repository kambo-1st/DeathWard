#include "world/CanyonWallFacets.hpp"
#include "world/CanyonAppearance.hpp"
#include <unordered_map>
namespace dw {
namespace {
uint64_t key(Vector3 p) {
    return uint64_t(uint32_t(int32_t(std::lround(p.x * 10000)))) << 32 |
           uint32_t(int32_t(std::lround(p.z * 10000)));
}
Vector3 cross(Vector3 a, Vector3 b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}
float planarLength(Vector3 a, Vector3 b) {
    auto d = sub(a, b);
    return std::hypot(d.x, d.z);
}
} // namespace
void rebuildCanyonWallFacets(CanyonAppearance &look, const std::vector<CanyonBoundaryFace> &faces) {
    const auto &field = look.surface;
    const int columns = field.width - 1, rows = field.depth - 1;
    struct Mapping {
        Vector3 a, b, da, db;
    };
    std::vector<Mapping> maps;
    std::vector<CanyonSurfaceTriangle> replacement;
    auto emit = [&](Vector3 a, Vector3 b, Vector3 c) {
        if (dot(cross(sub(b, a), sub(c, a)), cross(sub(b, a), sub(c, a))) > 1e-10f)
            replacement.push_back({{a, c, b}, true});
    };
    std::unordered_multimap<uint64_t, size_t> next;
    for (size_t i = 0; i < faces.size(); ++i)
        next.emplace(key(faces[i].bottomA), i);
    std::vector<bool> visited(faces.size());
    for (size_t start = 0; start < faces.size(); ++start) {
        if (visited[start])
            continue;
        std::vector<Vector3> bottom, top;
        size_t at = start;
        bool closed = false;
        for (size_t count = 0; count <= faces.size(); ++count) {
            if (visited[at])
                break;
            visited[at] = true;
            const auto &f = faces[at];
            bottom.push_back(f.bottomA);
            top.push_back(f.topA);
            if (key(f.bottomB) == key(faces[start].bottomA)) {
                closed = true;
                break;
            }
            auto range = next.equal_range(key(f.bottomB));
            size_t following = faces.size();
            for (auto it = range.first; it != range.second; ++it)
                if (!visited[it->second]) {
                    following = it->second;
                    break;
                }
            if (following == faces.size()) {
                bottom.push_back(f.bottomB);
                top.push_back(f.topB);
                break;
            }
            at = following;
        }
        if (top.size() < 2)
            continue;
        if (closed) {
            bottom.push_back(bottom.front());
            top.push_back(top.front());
        }
        std::vector<float> along(top.size());
        for (size_t i = 1; i < top.size(); ++i)
            along[i] = along[i - 1] + planarLength(top[i - 1], top[i]);
        std::vector<size_t> anchors{0};
        for (size_t i = 1; i + 1 < top.size(); ++i) {
            float span = along[i] - along[anchors.back()];
            float width = 2.4f + .85f * std::sin(top[i].x * .17f + top[i].z * .13f);
            if (span >= width)
                anchors.push_back(i);
        }
        anchors.push_back(top.size() - 1);
        auto silhouette = top;
        const size_t unique = closed ? top.size() - 1 : top.size();
        for (size_t index : anchors) {
            size_t i = closed ? index % unique : index;
            size_t previous = closed ? (i + unique - 1) % unique : (i ? i - 1 : i);
            size_t following = closed ? (i + 1) % unique : std::min(i + 1, unique - 1);
            auto tangent = unit(sub(top[following], top[previous]));
            Vector3 inward{tangent.z, 0, -tangent.x};
            float offset = std::clamp(.35f + .28f * std::sin(top[i].x * .23f + top[i].z * .17f) +
                                          .12f * std::sin(top[i].x * .61f - top[i].z * .37f),
                                      0.f, .8f);
            auto candidate = add(top[i], mul(inward, offset));
            candidate.y = std::clamp(candidate.y + .42f * std::sin(top[i].x * .27f + top[i].z * .17f) +
                                         .2f * std::sin(top[i].x * .7f - top[i].z * .31f),
                                     1.f, look.parameters.maxHeight);
            const bool within = candidate.x >= field.x && candidate.z >= field.z &&
                                candidate.x <= field.x + (field.width - 1) * field.step &&
                                candidate.z <= field.z + (field.depth - 1) * field.step;
            if (within && field.height(candidate.x, candidate.z, true) > CanyonTerrain::WalkableHeight)
                silhouette[index] = candidate;
        }
        // Each broad upper face spans several original grid cuts. Its short
        // foot fan retains every canonical contact vertex as an erosion toe.
        for (size_t j = 0; j + 1 < anchors.size(); ++j) {
            size_t a = anchors[j], b = anchors[j + 1];
            float span = std::max(.0001f, along[b] - along[a]);
            auto upperA = silhouette[a], upperB = silhouette[b];
            auto middle = [&](size_t i) {
                auto v = add(mul(bottom[i], .15f), mul(silhouette[i], .85f));
                float t = std::clamp(.28f + .18f * std::sin(top[i].x * .6f + top[i].z * .35f) +
                                         .08f * std::sin(top[i].x * .23f - top[i].z * .47f),
                                     .15f, .55f);
                v.y = std::lerp(bottom[i].y, top[i].y, t);
                size_t id = closed ? i % unique : i;
                size_t previous = closed ? (id + unique - 1) % unique : (id ? id - 1 : id);
                size_t following = closed ? (id + 1) % unique : std::min(id + 1, unique - 1);
                auto tangent = unit(sub(top[following], top[previous]));
                Vector3 inward{tangent.z, 0, -tangent.x};
                float relief = .4f * std::sin(top[i].x * .57f + top[i].z * .31f);
                auto candidate = add(v, mul(inward, relief));
                if (field.height(candidate.x, candidate.z, true) > CanyonTerrain::WalkableHeight)
                    v = candidate;
                return v;
            };
            auto ma = middle(a), mb = middle(b);
            for (size_t i = a; i < b; ++i) {
                float ta = (along[i] - along[a]) / span, tb = (along[i + 1] - along[a]) / span;
                auto newA = add(upperA, mul(sub(upperB, upperA), ta));
                auto newB = add(upperA, mul(sub(upperB, upperA), tb));
                maps.push_back({top[i], top[i + 1], sub(newA, top[i]), sub(newB, top[i + 1])});
                auto mi = add(ma, mul(sub(mb, ma), ta));
                auto mn = add(ma, mul(sub(mb, ma), tb));
                emit(bottom[i], mi, mn);
                emit(bottom[i], mn, bottom[i + 1]);
            }
            emit(ma, upperA, upperB);
            emit(ma, upperB, mb);
        }
    }
    std::vector<std::vector<size_t>> bins(size_t(columns * rows));
    auto coordinate = [&](Vector3 p) {
        return std::pair{std::clamp(int(std::floor((p.x - field.x) / field.step)), 0, columns - 1),
                         std::clamp(int(std::floor((p.z - field.z) / field.step)), 0, rows - 1)};
    };
    for (size_t i = 0; i < maps.size(); ++i) {
        auto a = coordinate(sub(maps[i].a, {2.5f, 0, 2.5f})), b = coordinate(add(maps[i].b, {2.5f, 0, 2.5f}));
        auto c = coordinate(sub(maps[i].b, {2.5f, 0, 2.5f})), d = coordinate(add(maps[i].a, {2.5f, 0, 2.5f}));
        for (int z = std::min(a.second, c.second); z <= std::max(b.second, d.second); ++z)
            for (int x = std::min(a.first, c.first); x <= std::max(b.first, d.first); ++x)
                bins[size_t(z * columns + x)].push_back(i);
    }
    for (auto &tri : look.triangles)
        if (tri.rock)
            for (auto &v : tri.vertices) {
                if (v.y <= CanyonTerrain::WalkableHeight + .00001f)
                    continue;
                const float boundary = field.height(v.x, v.z, true);
                if (boundary <= CanyonTerrain::WalkableHeight && field.height(v.x, v.z) > boundary + .08f)
                    continue;
                auto cell = coordinate(v);
                float best = 2.5f;
                Vector3 delta{};
                for (size_t i : bins[size_t(cell.second * columns + cell.first)]) {
                    const auto &m = maps[i];
                    auto edge = sub(m.b, m.a);
                    edge.y = 0;
                    auto local = sub(v, m.a);
                    local.y = 0;
                    float t = std::clamp(dot(local, edge) / std::max(.000001f, dot(edge, edge)), 0.f, 1.f);
                    auto closest = add(m.a, mul(edge, t));
                    float d = planarLength(v, closest);
                    if (d < best) {
                        best = d;
                        delta = add(m.da, mul(sub(m.db, m.da), t));
                    }
                }
                float weight = std::clamp(1 - best / 2.5f, 0.f, 1.f);
                weight = weight * weight * (3 - 2 * weight);
                v = add(v, mul(delta, weight));
                v.y = std::min(v.y, look.parameters.maxHeight);
            }
    look.triangles.insert(look.triangles.end(), replacement.begin(), replacement.end());
    auto owner = [&](const CanyonSurfaceTriangle &t) {
        auto center = mul(add(add(t.vertices[0], t.vertices[1]), t.vertices[2]), 1.f / 3);
        auto c = coordinate(center);
        return size_t(c.second * columns + c.first);
    };
    std::stable_sort(look.triangles.begin(), look.triangles.end(),
                     [&](const auto &a, const auto &b) { return owner(a) < owner(b); });
    look.cellOffsets.assign(size_t(columns * rows) + 1, 0);
    for (const auto &t : look.triangles)
        ++look.cellOffsets[owner(t) + 1];
    for (size_t i = 1; i < look.cellOffsets.size(); ++i)
        look.cellOffsets[i] += look.cellOffsets[i - 1];
}
} // namespace dw
