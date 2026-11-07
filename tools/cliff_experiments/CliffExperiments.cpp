#include "CliffExperiments.hpp"
#include "PrototypeGeometry.hpp"
#include "RockFormations.hpp"
#include "FormationTiming.hpp"
#include "FormationSections.hpp"
#include "combat/Simulation.hpp"
#include "raymath.h"
#include "rlgl.h"
#include "world/CliffWallTopology.hpp"
#include <chrono>
#include <bit>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
using namespace dw;
namespace {
using Quad = cliffDetail::Quad;
using Triangle = std::array<Vector3, 3>;
std::vector<Triangle> wire;
std::vector<Triangle> massing;
std::vector<std::array<Vector3, 2>> polygonWire;
std::string option() {
    const char *p = std::getenv("DW_CLIFF_OPTION");
    return p ? p : "original";
}
uint64_t fingerprint(const CanyonAppearance &surface) {
    uint64_t hash=1469598103934665603ULL;
    auto word=[&](uint32_t value){hash=(hash^value)*1099511628211ULL;};
    for(const auto &t:surface.triangles) {
        word(t.rock);
        for(auto p:t.vertices)for(float v:{p.x,p.y,p.z})word(std::bit_cast<uint32_t>(v));
    }
    for(const auto &d:surface.decorations) {
        word(uint32_t(d.kind));word(uint32_t(d.zone));word(uint32_t(d.room));word(d.extraVegetation);
        for(float v:{d.position.x,d.position.y,d.position.z,d.span,d.height,d.yaw})word(std::bit_cast<uint32_t>(v));
    }
    return hash;
}
struct Patch {
    std::vector<Quad> quads;
    std::vector<float> s;
    float height = 0;
};
Patch patchFor(const CanyonAppearance &base, const Arena &arena) {
    Simulation init(1866, 1, {}, MissionTheme::Canyon, true);
    int floor = 0;
    while (init.expedition.profileOnFloor(floor).band < 2)
        ++floor;
    Simulation run(1866, 1, {}, MissionTheme::Canyon, true, false, WitnessAccount::None, floor);
    run.jumpDebug(2);
    if (run.arena.visualSeed != arena.visualSeed)
        throw std::runtime_error("Experiment must use --scene profile-works, seed1866");
    auto focus = sub(run.player.position, {1.25f, .85f, 1.25f});
    Camera3D camera{add(focus, {14.375f, 18.75f, 14.375f}), focus, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
    using Key = std::array<int, 6>;
    auto key = [](Vector3 a, Vector3 b) {
        return Key{int(std::lround(a.x * 1000)), int(std::lround(a.y * 1000)), int(std::lround(a.z * 1000)),
                   int(std::lround(b.x * 1000)), int(std::lround(b.y * 1000)), int(std::lround(b.z * 1000))};
    };
    std::vector<Quad> candidates;
    std::map<Key, std::vector<size_t>> start;
    std::ofstream csv("docs/reports/cliff-alternatives/wall-selection.csv");
    csv << "id,screen_x,screen_y,height,width,base_y\n";
    for (size_t i = 0; i + 1 < base.triangles.size(); ++i) {
        const auto &a = base.triangles[i], &b = base.triangles[i + 1];
        if (!a.rock || !b.rock || !cliffDetail::near(a.vertices[0], b.vertices[0]) ||
            !cliffDetail::near(a.vertices[1], b.vertices[2]))
            continue;
        Quad q{a.vertices[0], b.vertices[1], a.vertices[1], a.vertices[2]};
        auto n = cliffDetail::normal(q);
        auto center = mul(add(add(q.ab, q.bb), add(q.at, q.bt)), .25f);
        auto screen = GetWorldToScreenEx(center, camera, 1440, 900);
        float h = std::min(q.at.y - q.ab.y, q.bt.y - q.bb.y);
        if (std::abs(n.y) > .65f || h < .8f || q.ab.y > .35f || q.bb.y > .35f)
            continue;
        csv << candidates.size() << ',' << screen.x << ',' << screen.y << ',' << h << ','
            << distance(q.ab, q.bb) << ',' << q.ab.y << '\n';
        if (screen.x < 450 || screen.x > 980 || screen.y < 75 || screen.y > 255)
            continue;
        start[key(q.ab, q.at)].push_back(candidates.size());
        candidates.push_back(q);
        ++i;
    }
    std::vector<Quad> best;
    float bestWidth = 0;
    for (size_t first = 0; first < candidates.size(); ++first) {
        std::set<size_t> seen;
        std::vector<Quad> chain;
        size_t next = first;
        float width = 0;
        while (!seen.contains(next)) {
            seen.insert(next);
            auto q = candidates[next];
            chain.push_back(q);
            width += distance(q.ab, q.bb);
            auto it = start.find(key(q.bb, q.bt));
            if (it == start.end() || it->second.size() != 1)
                break;
            next = it->second.front();
        }
        if (width > bestWidth) {
            bestWidth = width;
            best = std::move(chain);
        }
    }
    if (best.size() < 3)
        throw std::runtime_error("Cannot identify target wall");
    Patch p;
    p.quads = best;
    p.s = {0};
    for (auto q : best) {
        p.s.push_back(p.s.back() + distance(q.ab, q.bb));
        p.height += ((q.at.y - q.ab.y) + (q.bt.y - q.bb.y)) * .5f / best.size();
    }
    auto l = GetWorldToScreenEx(best.front().ab, camera, 1440, 900),
         r = GetWorldToScreenEx(best.back().bb, camera, 1440, 900);
    std::cout << "SELECTED_WALL segments=" << best.size() << " width=" << p.s.back() << " height=" << p.height
              << " screen_start=" << l.x << ',' << l.y << " screen_end=" << r.x << ',' << r.y
              << " hero=" << run.player.position.x << ',' << run.player.position.z << '\n';
    return p;
}
struct Mapped {
    float s, v, d;
};
Mapped mapped(Vector3 p, const Patch &patch) {
    Mapped best{0, 0, 1e9};
    for (size_t i = 0; i < patch.quads.size(); ++i) {
        auto q = patch.quads[i];
        auto a = q.ab, b = q.bb;
        a.y = b.y = p.y;
        auto e = sub(b, a);
        float t = std::clamp(dot(sub(p, a), e) / dot(e, e), 0.f, 1.f);
        auto lo = Vector3Lerp(q.ab, q.bb, t), hi = Vector3Lerp(q.at, q.bt, t);
        float v = (p.y - lo.y) / (hi.y - lo.y);
        auto on = Vector3Lerp(lo, hi, v);
        float d = planarDistance(on, p);
        if (d < best.d)
            best = {std::lerp(patch.s[i], patch.s[i + 1], t), v, d};
    }
    return best;
}
CanyonAppearance generalizedPreview(const Arena &arena,const CanyonAppearance &base,const CanyonAppearance &original) {
    const int room=std::getenv("DW_CLIFF_ROOM")?std::stoi(std::getenv("DW_CLIFF_ROOM")):2;
    if(room<0 || room>=arena.roomCount())throw std::runtime_error("Invalid generalized preview room");
    const auto constructionStart=std::chrono::steady_clock::now();
    const auto validationStart=rockFormations::validationMilliseconds;
    const auto candidates=rockFormations::selectSections(base,arena.rooms[size_t(room)].bounds);
    const auto setting=std::getenv("DW_CLIFF_DETAIL");
    const bool detail=!setting || std::string_view(setting)!="0";
    const bool baseContext=std::getenv("DW_CLIFF_BASE_CONTEXT")!=nullptr;
    std::cout<<"FORMATION_CONTEXT source="<<(baseContext?"unrefined_terrain":"preserved_A")<<'\n';
    std::string lastReason;size_t attempt=0;
    for(const auto &section:candidates) {
        ++attempt;
        if(const auto filter=std::getenv("DW_CLIFF_ATTEMPT"))if(attempt!=std::stoul(filter))continue;
        if(const auto filter=std::getenv("DW_CLIFF_SECTION"))if(section.key!=std::stoull(filter))continue;
        std::cout<<"FORMATION_SECTION room="<<room<<" attempt="<<attempt<<" key="<<section.key<<" length="<<section.length
                 <<" shape="<<section.shape<<" turn="<<section.turn<<'\n';
        if(!section.fallback.empty()){lastReason=section.fallback;continue;}
        try {
            auto trial=baseContext?base:original,replay=baseContext?base:original;
            const auto seed=arena.visualSeed^section.key;
            auto geometry=rockFormations::buildAndApply(trial,base,section.wall,seed,detail);
            const auto checkedMs=std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-constructionStart).count();
            const auto validationMs=rockFormations::validationMilliseconds-validationStart;
            std::cout<<"FORMATION_CONSTRUCTION checked_ms="<<checkedMs<<" validation_ms="<<validationMs
                     <<" construction_ms="<<checkedMs-validationMs<<" replay_excluded=1 attempts="<<attempt
                     <<" triangles="<<trial.triangles.size()<<" finished_roof="<<geometry.finishedRoof<<'\n';
            auto repeat=rockFormations::buildAndApply(replay,base,section.wall,seed,detail);
            if(trial.triangles.size()!=replay.triangles.size() || trial.decorations.size()!=replay.decorations.size())
                throw std::runtime_error("Generalized replay changed surface or scenery count");
            for(size_t i=0;i<trial.triangles.size();++i) {
                if(trial.triangles[i].rock!=replay.triangles[i].rock)throw std::runtime_error("Generalized replay changed surface type");
                for(int k=0;k<3;++k)if(distance(trial.triangles[i].vertices[k],replay.triangles[i].vertices[k])>1e-7f)
                    throw std::runtime_error("Generalized replay changed a vertex");
            }
            if(fingerprint(trial)!=fingerprint(replay))throw std::runtime_error("Generalized replay changed decoration records");
            if(trial.surface.heights!=original.surface.heights)throw std::runtime_error("Generalized preview changed the terrain height field");
            std::cout<<"FORMATION_DETERMINISM identical_vertices=PASS\nPLATEAU_ASSEMBLY_REPLAY identical_triangles=PASS\n"
                       "FORMATION_SCENERY_REPLAY identical_placements=PASS\n";
            wire=geometry.assembledMesh.faces;polygonWire=geometry.assembledMesh.polygonEdges;massing=geometry.mesh.faces;
            std::cout<<"FORMATION_RESULT outcome=applied attempts="<<attempt<<" section_key="<<section.key
                     <<" geometry_and_scenery_hash="<<fingerprint(trial)
                     <<" inspect_x="<<section.midpoint.x<<" inspect_z="<<section.midpoint.z<<'\n';
            return trial;
        } catch(const std::exception &error) {
            lastReason=error.what();
            std::cout<<"FORMATION_REJECT attempt="<<attempt<<" reason="<<std::quoted(lastReason)<<'\n';
        }
    }
    wire.clear();massing.clear();polygonWire.clear();
    std::cout<<"FORMATION_FALLBACK reason="<<std::quoted(lastReason)<<" rejected_candidates="<<attempt<<" original_surface=unchanged\n";
    std::cout<<"FORMATION_RESULT outcome=fallback geometry_and_scenery_hash="<<fingerprint(original)<<'\n';
    return original;
}
} // namespace
namespace dw {
CanyonAppearance cliffExperimentAppearance(const Arena &arena, const CanyonVisualParameters &params) {
    auto sourceParameters = params;
    if (std::getenv("DW_CLIFF_FREEZE_SURROUNDINGS"))
        sourceParameters.polygonFacets = false;
    const auto baselineStart=std::chrono::steady_clock::now();
    auto out = buildCanyonAppearance(arena, sourceParameters);
    std::cout<<"FORMATION_BASELINE_CONSTRUCTION ms="<<std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-baselineStart).count()
             <<" triangles="<<out.triangles.size()<<'\n';
    auto p = params;
    p.irregularFacets = false;
    auto base = buildCanyonAppearance(arena, p);
    auto mode = option();
    const auto layout=std::getenv("DW_CLIFF_LAYOUT");
    const bool seeded=layout && std::string_view(layout)=="seeded";
    const auto baselineHash=seeded?fingerprint(out):0;
    if(seeded)std::cout<<"FORMATION_BASELINE geometry_and_scenery_hash="<<baselineHash<<'\n';
    if(seeded && mode=="original")return out;
    if(seeded)return generalizedPreview(arena,base,out);
    auto patch=patchFor(base,arena);
    constexpr uint64_t formationSeed=1866;
    if (std::getenv("DW_CLIFF_BENCH"))
        for (auto candidate : {"a", "b", "c"}) {
            std::vector<double> times;
            for (int n = 0; n < 21; ++n) {
                auto start = std::chrono::steady_clock::now();
                auto mesh = cliffOptions::build(patch.quads, candidate, 1866);
                times.push_back(
                    std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start)
                        .count());
            }
            std::sort(times.begin(), times.end());
            std::cout << "BENCH mode=" << candidate << " repetitions=21 median_ms=" << times[10]
                      << " min_ms=" << times.front() << " max_ms=" << times.back() << '\n';
        }
    wire.clear();
    massing.clear();
    polygonWire.clear();
    std::set<size_t> selected;
    for (size_t i = 0; i < out.triangles.size(); ++i) {
        const auto &t = out.triangles[i];
        auto n = Vector3Normalize(
            Vector3CrossProduct(sub(t.vertices[1], t.vertices[0]), sub(t.vertices[2], t.vertices[0])));
        auto mid = mul(add(add(t.vertices[0], t.vertices[1]), t.vertices[2]), 1.f / 3);
        auto m = mapped(mid, patch);
        if (t.rock && std::abs(n.y) < .65f && m.s > .0001f && m.s < patch.s.back() - .0001f && m.v > -.001f &&
            m.v < 1.001f && m.d < .4f) {
            wire.push_back(t.vertices);
            selected.insert(i);
        }
    }
    std::cout << "CLIFF_OPTION=" << mode << " original_triangles=" << selected.size() << '\n';
    if (mode == "formations") {
        const auto physicalBefore = arena.canyon->heights;
        auto started = std::chrono::steady_clock::now();
        const auto detailSetting=std::getenv("DW_CLIFF_DETAIL");
        const bool detail=!detailSetting || std::string(detailSetting)!="0";
        auto replay=out;
        auto geometry=rockFormations::build(patch.quads,base,formationSeed,detail);
        auto repeat=rockFormations::build(patch.quads,base,formationSeed,detail);
        if (geometry.mesh.faces.size() != repeat.mesh.faces.size())
            throw std::runtime_error("Rock union nondeterministic count");
        for (size_t i = 0; i < geometry.mesh.faces.size(); ++i)
            for (int k = 0; k < 3; ++k)
                if (distance(geometry.mesh.faces[i][k], repeat.mesh.faces[i][k]) > 1e-7f)
                    throw std::runtime_error("Rock union nondeterministic vertex");
        std::cout << "FORMATION_DETERMINISM identical_vertices=PASS\n";
        rockFormations::apply(out,patch.quads,geometry);
        rockFormations::apply(replay,patch.quads,repeat);
        if(out.triangles.size()!=replay.triangles.size()) throw std::runtime_error("Plateau assembly replay changed triangle count");
        for(size_t i=0;i<out.triangles.size();++i) {
            if(out.triangles[i].rock!=replay.triangles[i].rock) throw std::runtime_error("Plateau assembly replay changed surface type");
            for(int k=0;k<3;++k)
                if(distance(out.triangles[i].vertices[k],replay.triangles[i].vertices[k])>1e-7f)
                    throw std::runtime_error("Plateau assembly replay changed a vertex");
        }
        std::cout<<"PLATEAU_ASSEMBLY_REPLAY identical_triangles=PASS\n";
        if(out.decorations.size()!=replay.decorations.size())throw std::runtime_error("Scenery replay changed count");
        for(size_t i=0;i<out.decorations.size();++i) {
            const auto &a=out.decorations[i],&b=replay.decorations[i];
            if(a.kind!=b.kind || a.zone!=b.zone || distance(a.position,b.position)>1e-7f ||
               a.span!=b.span || a.height!=b.height || a.yaw!=b.yaw || a.room!=b.room || a.extraVegetation!=b.extraVegetation)
                throw std::runtime_error("Scenery replay changed placement");
        }
        std::cout<<"FORMATION_SCENERY_REPLAY identical_placements=PASS\n";
        if(std::getenv("DW_CLIFF_CONNECTION_AUDIT")) {
            const auto destination=std::getenv("DW_CLIFF_CONNECTION_DIR");
            const auto directory=std::filesystem::path(destination?destination:"docs/reports/cliff-formations/phase2/connection-audit");
            std::filesystem::create_directories(directory);
            for(const auto &[label,surface]:std::array<std::pair<const char*,const cliffOptions::Mesh*>,2>{{{"core",&geometry.mesh},{"assembled",&geometry.assembledMesh}}}) {
                const auto &audit=surface==&geometry.mesh ? geometry.strictAudit : geometry.strictAssembledAudit;
                std::cout<<"STRICT_CONNECTION surface="<<label<<" exact_open="<<audit.exact.boundaryEdges
                         <<" exact_nonmanifold="<<audit.exact.nonmanifoldEdges<<" vertex_links="<<audit.nonmanifoldVertices
                         <<" crossings="<<audit.selfIntersections<<" coplanar_overlap="<<audit.coplanarOverlaps
                         <<" degenerate="<<audit.exact.degenerateFaces<<" tested_pairs="<<audit.testedPairs<<'\n';
                std::ofstream obj(directory/(std::string(label)+".obj"));obj<<std::setprecision(9);
                std::map<std::array<float,3>,size_t> ids;
                std::vector<Vector3> points;
                std::vector<std::array<size_t,3>> faces;
                for(const auto &face:surface->faces) {
                    std::array<size_t,3> indices;
                    for(int k=0;k<3;++k) {
                        const auto p=face[k];
                        const auto [it,added]=ids.try_emplace({p.x,p.y,p.z},points.size()+1);
                        if(added) points.push_back(p);indices[k]=it->second;
                    }
                    faces.push_back(indices);
                }
                for(auto p:points)obj<<"v "<<p.x<<' '<<p.y<<' '<<p.z<<'\n';
                for(auto f:faces)obj<<"f "<<f[0]<<' '<<f[1]<<' '<<f[2]<<'\n';
                std::ofstream failures(directory/(std::string(label)+"-pairs.txt"));
                for(auto pair:audit.problemPairs)failures<<pair[0]<<' '<<pair[1]<<'\n';
            }
        }
        if (physicalBefore != arena.canyon->heights)
            throw std::runtime_error("Authoritative collision field changed");
        wire = geometry.assembledMesh.faces;
        polygonWire = geometry.assembledMesh.polygonEdges;
        massing=geometry.mesh.faces;
        std::cout
            << "FORMATION_BUILD_MS "
            << std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - started).count()
            << '\n';
        return out;
    }
    if (mode != "original") {
        auto begin = std::chrono::steady_clock::now();
        auto geometry = cliffOptions::build(patch.quads, mode, 1866);
        double ms =
            std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - begin).count();
        auto again = cliffOptions::build(patch.quads, mode, 1866);
        if (again.faces.size() != geometry.faces.size())
            throw std::runtime_error("Nondeterministic topology");
        for (size_t i = 0; i < again.faces.size(); ++i)
            for (int j = 0; j < 3; ++j)
                if (distance(again.faces[i][j], geometry.faces[i][j]) > 1e-7)
                    throw std::runtime_error("Nondeterministic vertex");
        if (selected.empty())
            throw std::runtime_error("Empty target selection");
        std::vector<CanyonSurfaceTriangle> triangles;
        std::vector<size_t> offsets;
        for (size_t cell = 0; cell + 1 < out.cellOffsets.size(); ++cell) {
            offsets.push_back(triangles.size());
            for (size_t i = out.cellOffsets[cell]; i < out.cellOffsets[cell + 1]; ++i) {
                if (i == *selected.begin())
                    for (auto t : geometry.faces)
                        triangles.push_back({t, true});
                if (!selected.contains(i))
                    triangles.push_back(out.triangles[i]);
            }
        }
        offsets.push_back(triangles.size());
        out.triangles = std::move(triangles);
        out.cellOffsets = std::move(offsets);
        wire = geometry.faces;
        polygonWire = geometry.polygonEdges;
        std::cout << "PROTOTYPE triangles=" << geometry.faces.size() << " masses=" << geometry.masses
                  << " quads=" << geometry.quads << " ngons=" << geometry.ngons << " chips=" << geometry.chips
                  << " max_vertex_depth_m=" << geometry.maxDepth << " build_ms=" << ms
                  << " area=" << geometry.area
                  << " seed=1866\nPASS boundary_constraints coverage manifold_edges determinism "
                     "unrelated_faces_copied collision_field_unchanged\n";
    }
    return out;
}
void cliffExperimentWire() {
    if (std::getenv("DW_CLIFF_MASSING")) {
        // Diagnostic only: the real mesh, same active camera, neutral directional
        // shading and no background scenery. Normal captures keep game lighting.
        rlDrawRenderBatchActive();
        rlEnableDepthMask();
        ClearBackground({32, 39, 43, 255});
        const auto previousView=rlGetMatrixModelview(),previousProjection=rlGetMatrixProjection();
        const auto &surface=massing.empty() ? wire : massing;
        const bool topView=std::string_view(std::getenv("DW_CLIFF_MASSING"))=="top";
        const std::string_view massingMode=std::getenv("DW_CLIFF_MASSING");
        const bool orbitView=massingMode.starts_with("orbit");
        if((topView || orbitView) && !surface.empty()) {
            Vector3 lo{1e9f,1e9f,1e9f},hi{-1e9f,-1e9f,-1e9f};
            for(const auto &face:surface) for(auto p:face) {
                lo={std::min(lo.x,p.x),std::min(lo.y,p.y),std::min(lo.z,p.z)};
                hi={std::max(hi.x,p.x),std::max(hi.y,p.y),std::max(hi.z,p.z)};
            }
            const auto target=mul(add(lo,hi),.5f);
            const float aspect=float(GetRenderWidth())/GetRenderHeight();
            const float width=std::max(hi.x-lo.x,(hi.z-lo.z)*aspect)*1.2f,height=width/aspect;
            rlSetMatrixProjection(MatrixOrtho(-width*.5,width*.5,-height*.5,height*.5,.1,100));
            if(orbitView) {
                const int quadrant=massingMode.size()>5?massingMode[5]-'0':0;
                const float angle=quadrant*Pi*.5f+.35f;
                rlSetMatrixModelview(MatrixLookAt(add(target,{28*std::cos(angle),24,28*std::sin(angle)}),target,{0,1,0}));
            } else rlSetMatrixModelview(MatrixLookAt(add(target,{0,40,0}),target,{0,0,-1}));
        }
        const Vector3 sun = Vector3Normalize(Vector3{-.4f, 1, .3f});
        for (const auto &t : surface) {
            const auto n = Vector3Normalize(Vector3CrossProduct(sub(t[1],t[0]),sub(t[2],t[0])));
            const auto light = static_cast<unsigned char>(90 + 140 * std::max(0.f, dot(n,sun)));
            DrawTriangle3D(t[0],t[1],t[2],{light,light,light,255});
        }
        rlDrawRenderBatchActive();
        if(topView || orbitView) {rlSetMatrixModelview(previousView);rlSetMatrixProjection(previousProjection);}
        rlDisableDepthMask();
        return;
    }
    if (!std::getenv("DW_CLIFF_WIRE"))
        return;
    rlDrawRenderBatchActive();
    rlSetLineWidth(1.5f);
    if (!polygonWire.empty() && std::string_view(std::getenv("DW_CLIFF_WIRE")) != "triangles") {
        for (auto e : polygonWire)
            DrawLine3D(add(e[0], {.004f, .004f, .004f}), add(e[1], {.004f, .004f, .004f}), {20, 25, 27, 255});
    } else
        for (auto t : wire) {
            auto n = Vector3Normalize(Vector3CrossProduct(sub(t[1], t[0]), sub(t[2], t[0])));
            for (int i = 0; i < 3; ++i)
                DrawLine3D(add(t[i], mul(n, .009f)), add(t[(i + 1) % 3], mul(n, .009f)), {20, 25, 27, 255});
        }
    rlDrawRenderBatchActive();
    rlSetLineWidth(1);
}
} // namespace dw
