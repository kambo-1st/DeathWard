#pragma once
#ifdef DEATHWARD_CLIFF_BOOLEAN_EXPERIMENT
#include "RockFormations.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>
#include <optional>
#include <tuple>
#include <set>
#include <stdexcept>

namespace dw::rockFormations {
// Opt-in construction repair, separate from the vertical-only diagnostic.
// Collapse short manifold edges to a shared float midpoint or endpoint.
// Each original vertex moves at most once, by <=20 um.
// Collapse removes exactly two incident triangles; all retained faces must
// keep their orientation. Every accepted proposal preserves closure, improves
// crossing/degenerate counts and passes source coverage for its entire star.
// Full assembly, cap, floor and world gates are still required afterwards.
inline cliffOptions::Mesh repairBooleanFloatVertices(cliffOptions::Mesh mesh,const std::vector<Volume> &volumes) {
    if(!std::getenv("DW_CLIFF_EXACT_CONTACTS"))throw std::runtime_error("Float vertex repair requires exact contacts");
    using Key=std::array<float,3>;
    auto normal=[](const cliffOptions::Triangle &face) {
        const double x=double(face[1].x)-face[0].x,y=double(face[1].y)-face[0].y,z=double(face[1].z)-face[0].z,
                     u=double(face[2].x)-face[0].x,v=double(face[2].y)-face[0].y,w=double(face[2].z)-face[0].z;
        return std::array<double,3>{y*w-z*v,z*u-x*w,x*v-y*u};
    };
    auto closed=[](const StrictSurfaceAudit &a){return !a.exact.boundaryEdges && !a.exact.nonmanifoldEdges && !a.nonmanifoldVertices && !a.exact.duplicateFaces && !a.exact.windingErrors;};
    auto audit=auditStrictSurface(mesh);const auto initialCrossings=audit.selfIntersections,initialDegenerate=audit.exact.degenerateFaces;
    std::set<Key> moved;size_t trials=0,sourceChecks=0,accepted=0;double maximumDisplacement=0;
    for(int pass=0;pass<8 && closed(audit) && !audit.coplanarOverlaps && audit.selfIntersections<=16 && audit.exact.degenerateFaces<=4 && (audit.selfIntersections || audit.exact.degenerateFaces);++pass) {
        std::map<Key,std::vector<size_t>> stars;std::set<Key> candidates;
        for(size_t f=0;f<mesh.faces.size();++f)for(auto p:mesh.faces[f]){auto &star=stars[{p.x,p.y,p.z}];if(star.empty() || star.back()!=f)star.push_back(f);}
        for(auto pair:audit.problemPairs)for(auto f:pair)for(auto p:mesh.faces[f])candidates.insert({p.x,p.y,p.z});
        for(const auto &face:mesh.faces){const auto n=normal(face);if(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]<1e-28)for(auto p:face)candidates.insert({p.x,p.y,p.z});}
        struct Accepted {
            cliffOptions::Mesh mesh;StrictSurfaceAudit audit;std::map<Key,Key> replacements;
            double displacement;size_t affected,removed;Key before;
        };
        std::optional<Accepted> best;
        auto bestScore=std::tuple{audit.selfIntersections,audit.exact.degenerateFaces,std::numeric_limits<double>::infinity()};
        struct Proposal {std::vector<Key> keys;Key target;};
        std::set<std::pair<Key,Key>> shortEdges;
        for(const auto &key:candidates)for(auto f:stars.at(key))for(int k=0;k<3;++k) {
            const auto p=mesh.faces[f][k],q=mesh.faces[f][(k+1)%3];Key a{p.x,p.y,p.z},b{q.x,q.y,q.z};
            if(a>b)std::swap(a,b);
            if(a==b || moved.contains(a) || moved.contains(b) || std::hypot(double(a[0])-b[0],double(a[1])-b[1],double(a[2])-b[2])>.00004)continue;
            shortEdges.insert({a,b});
        }
        std::vector<Proposal> proposals;
        for(const auto &[a,b]:shortEdges) {
            const Key midpoint{float((double(a[0])+b[0])/2),float((double(a[1])+b[1])/2),float((double(a[2])+b[2])/2)};
            for(const auto &target:{midpoint,a,b})proposals.push_back({{a,b},target});
        }
        for(const auto &proposal:proposals) {
            if(trials>=512)break;
            const auto &key=proposal.keys.front();
            std::map<Key,Key> replacements;double displacement=0;bool valid=true;
            std::set<size_t> star;
            for(const auto &p:proposal.keys) {
                const auto q=proposal.target;
                displacement=std::max(displacement,std::hypot(double(q[0])-p[0],double(q[1])-p[1],double(q[2])-p[2]));
                valid &= std::isfinite(q[0]) && std::isfinite(q[1]) && std::isfinite(q[2]) && displacement<=.00002;
                replacements.emplace(p,q);star.insert(stars.at(p).begin(),stars.at(p).end());
            }
            if(!valid)continue;
            std::vector<bool> changed(mesh.faces.size());for(auto f:star)changed[f]=true;
            size_t unchangedCrossings=0;
            for(auto pair:audit.problemPairs)unchangedCrossings+=!changed[pair[0]] && !changed[pair[1]];
            auto move=[&](Vector3 &p){const auto found=replacements.find({p.x,p.y,p.z});if(found!=replacements.end()){const auto q=found->second;p={q[0],q[1],q[2]};}};
            auto trial=mesh;bool flipped=false;std::set<size_t> removed;
            for(auto f:star) {
                auto &face=trial.faces[f];const auto before=normal(face);
                for(auto &p:face)move(p);
                auto equal=[](Vector3 p,Vector3 q){return p.x==q.x && p.y==q.y && p.z==q.z;};
                if(equal(face[0],face[1]) || equal(face[1],face[2]) || equal(face[2],face[0])){removed.insert(f);continue;}
                const auto after=normal(face);
                if(before[0]*after[0]+before[1]*after[1]+before[2]*after[2]<=0){flipped=true;break;}
            }
            // Closed manifold edge collapse removes exactly its two incident
            // triangles. All other faces must retain their orientation.
            if(flipped || removed.size()!=2)continue;
            ++trials;
            cliffOptions::Mesh ordered,affected;
            for(size_t f=0;f<trial.faces.size();++f)if(!changed[f])ordered.faces.push_back(trial.faces[f]);
            const auto firstChanged=ordered.faces.size();
            for(auto f:star)if(!removed.contains(f)){ordered.faces.push_back(trial.faces[f]);affected.faces.push_back(trial.faces[f]);}
            if(!removed.empty()) {
                std::vector<cliffOptions::Triangle> retained;
                for(size_t f=0;f<trial.faces.size();++f)if(!removed.contains(f))retained.push_back(trial.faces[f]);
                trial.faces=std::move(retained);
            }
            const auto local=auditSurfaceReplacement(ordered,firstChanged);
            const auto crossings=unchangedCrossings+local.selfIntersections;
            if(!closed(local) || local.coplanarOverlaps || local.exact.components!=audit.exact.components ||
               crossings>audit.selfIntersections || local.exact.degenerateFaces>audit.exact.degenerateFaces ||
               (crossings==audit.selfIntersections && local.exact.degenerateFaces==audit.exact.degenerateFaces))continue;
            const auto score=std::tuple{crossings,local.exact.degenerateFaces,displacement};
            if(best && score>=bestScore)continue;
            ++sourceChecks;const auto source=auditBoundaryCoverageQuiet(affected,volumes);
            if(source.buriedFragments || source.detachedFragments)continue;
            const auto full=auditStrictSurface(trial);
            if(!closed(full) || full.coplanarOverlaps || full.exact.components!=audit.exact.components || full.selfIntersections!=crossings || full.exact.degenerateFaces!=local.exact.degenerateFaces)
                throw std::runtime_error("Local/full float vertex repair validation disagrees");
            for(auto &edge:trial.polygonEdges)for(auto &p:edge)move(p);
            std::erase_if(trial.polygonEdges,[](const auto &edge){return edge[0].x==edge[1].x && edge[0].y==edge[1].y && edge[0].z==edge[1].z;});
            best=Accepted{std::move(trial),full,replacements,displacement,star.size(),removed.size(),key};bestScore=score;
            // Prefer a complete repair over an earlier partial improvement.
            // This avoids fixing both endpoints halfway and then freezing a
            // remaining crossing under the one-move-per-vertex constraint.
            if(crossings==0 && full.exact.degenerateFaces==0)break;
        }
        if(!best)break;
        mesh=std::move(best->mesh);audit=std::move(best->audit);
        for(const auto &[p,q]:best->replacements){moved.insert(p);moved.insert(q);}
        ++accepted;maximumDisplacement=std::max(maximumDisplacement,best->displacement);
        std::cout<<"FORMATION_VERTEX_MOVE collapse=1 removed_faces="<<best->removed<<" before="<<best->before[0]<<','<<best->before[1]<<','<<best->before[2]<<" vertices="<<best->replacements.size()<<" displacement_m="<<best->displacement<<" affected_faces="<<best->affected<<" source_boundary=PASS\n";
    }
    std::cout<<"FORMATION_VERTEX_REPAIR initial_crossings="<<initialCrossings<<" final_crossings="<<audit.selfIntersections<<" initial_degenerate="<<initialDegenerate<<" final_degenerate="<<audit.exact.degenerateFaces<<" moves="<<accepted<<" trials="<<trials<<" source_checks="<<sourceChecks<<" maximum_displacement_m="<<maximumDisplacement<<" displacement_limit_m=.00002 short_edge_collapse=1\n";
    return mesh;
}
}
#endif
