#include "FormationSections.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>
#include <map>
#include <set>

namespace dw::rockFormations {
std::vector<Section> selectSections(const CanyonAppearance &base,const Box &room) {
    using Point=std::array<int,3>;
    auto key=[](Vector3 p){return Point{int(std::lround(p.x*1000)),int(std::lround(p.y*1000)),int(std::lround(p.z*1000))};};
    std::vector<cliffDetail::Quad> quads;
    std::map<Point,std::vector<size_t>> starts;
    for(size_t i=0;i+1<base.triangles.size();++i) {
        const auto &a=base.triangles[i],&b=base.triangles[i+1];
        if(!a.rock || !b.rock || !cliffDetail::near(a.vertices[0],b.vertices[0]) ||
           !cliffDetail::near(a.vertices[1],b.vertices[2]))continue;
        const cliffDetail::Quad q{a.vertices[0],b.vertices[1],a.vertices[1],a.vertices[2]};
        const auto n=cliffDetail::normal(q);
        const float h=std::min(q.at.y-q.ab.y,q.bt.y-q.bb.y);
        if(std::abs(n.y)>.65f || h<.8f || q.ab.y>.35f || q.bb.y>.35f)continue;
        starts[key(q.ab)].push_back(quads.size());quads.push_back(q);++i;
    }
    const auto centre=mul(add(room.min,room.max),.5f);
    std::vector<Section> result;
    // Each directed edge is a stable candidate origin. Grow at most 24 m;
    // stop at ambiguous contour junctions rather than choosing a random branch.
    for(float targetLength:{24.f,18.f,14.f}) {
        std::vector<std::pair<float,Section>> ranked;
        for(size_t first=0;first<quads.size();++first) {
            const auto &origin=quads[first];
            if(planarDistance(origin.ab,centre)>35)continue;
            Section section;std::set<size_t> seen;size_t next=first;
            while(seen.insert(next).second) {
                auto q=quads[next];
                const float span=distance(q.ab,q.bb);
                if(section.length+span>targetLength && section.length>=14)break;
                section.length+=span;section.wall.push_back(q);
                const auto it=starts.find(key(q.bb));
                if(it==starts.end() || it->second.size()!=1)break;
                next=it->second.front();
                if(section.length>=targetLength)break;
            }
            if(section.wall.empty())continue;
            Vector3 midpoint{};
            for(auto q:section.wall)midpoint=add(midpoint,mul(add(q.ab,q.bb),.5f/section.wall.size()));
            section.midpoint=midpoint;
            // Compare tangent directions over metre-scale chords, not individual
            // grid stair steps, which alternate by 90 degrees on a smooth bend.
            const auto overall=Vector3Normalize(sub(section.wall.back().bb,section.wall.front().ab));
            for(size_t i=0;i<section.wall.size();++i) {
                auto a=section.wall[i].ab,b=section.wall[i].bb;
                for(size_t j=i+1;j<section.wall.size() && planarDistance(a,b)<2;++j)b=section.wall[j].bb;
                auto tangent=Vector3Normalize(sub(b,a));
                section.turn=std::max(section.turn,std::acos(std::clamp(dot(tangent,overall),-1.f,1.f)));
            }
            section.shape=section.turn<.25f?"straight":section.turn<1.1f?"curved":"folded_corner";
            // Metre-scale equal-distance chords suppress alternating grid steps.
            auto onContour=[&](float at) {
                for(auto q:section.wall) {
                    const float span=planarDistance(q.ab,q.bb);
                    if(at<=span)return Vector3Lerp(q.ab,q.bb,span>0?at/span:0);
                    at-=span;
                }
                return section.wall.back().bb;
            };
            float positive=0,negative=0;
            for(int sample=1;sample<6;++sample) {
                const auto a=sub(onContour(section.length*sample/6),onContour(section.length*(sample-1)/6));
                const auto b=sub(onContour(section.length*(sample+1)/6),onContour(section.length*sample/6));
                const float angle=std::atan2(a.x*b.z-a.z*b.x,a.x*b.x+a.z*b.z);
                positive+=std::max(0.f,angle);negative+=std::max(0.f,-angle);
            }
            // Positive x/z turning bends toward cross(tangent,up), the room side.
            section.curvature=std::max(positive,negative)<.25f?"straight":
                positive>.25f && negative>.25f?"mixed":positive>negative?"concave":"convex";

            if(section.length<14)section.fallback="section shorter than 14 metres";
            else if(section.turn>1.1f)section.fallback="folded or sharp corner requires coordinated sections";
            const float score=planarDistance(midpoint,centre)+(section.fallback.empty()?0:100)+std::abs(section.length-targetLength)*.2f;
            auto startKey=key(section.wall.front().ab);
            section.key=1469598103934665603ULL;
            for(int value:startKey)section.key=(section.key^uint32_t(value))*1099511628211ULL;
            ranked.emplace_back(score,std::move(section));
        }
        std::stable_sort(ranked.begin(),ranked.end(),[](const auto &a,const auto &b){return a.first<b.first;});
        const auto firstResult=result.size();
        for(auto &[score,section]:ranked) {
            if(std::any_of(result.begin()+firstResult,result.end(),[&](const auto &other){return planarDistance(section.midpoint,other.midpoint)<4;}))continue;
            result.push_back(std::move(section));if(result.size()-firstResult==6)break;
        }
    }
    if(result.empty()){Section missing;missing.fallback="no unambiguous floor-level cliff contour near this room";result.push_back(missing);}
    return result;
}
Section selectSection(const CanyonAppearance &base,const Box &room) {return selectSections(base,room).front();}
} // namespace dw::rockFormations
