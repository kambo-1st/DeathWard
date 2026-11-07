#include "RockFormations.hpp"
#include "FormationTiming.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

namespace dw::rockFormations {
namespace {
void append(std::vector<CanyonSurfaceTriangle> &target,const Polygon &p,bool rock) {
    for(size_t i=1;i+1<p.size();++i)target.push_back({{p[0],p[i],p[i+1]},rock});
}
void supportBins(CanyonAppearance &out) {
    const auto &s=out.surface;
    const int columns=s.width-1,rows=s.depth-1;
    std::vector<std::vector<size_t>> bins(size_t(columns*rows));
    for(size_t i=0;i<out.supportTriangles.size();++i) {
        int lx=columns-1,hx=0,lz=rows-1,hz=0;
        for(auto p:out.supportTriangles[i].vertices) {
            const int x=std::clamp(int(std::floor((p.x-s.x)/s.step)),0,columns-1);
            const int z=std::clamp(int(std::floor((p.z-s.z)/s.step)),0,rows-1);
            lx=std::min(lx,x);hx=std::max(hx,x);lz=std::min(lz,z);hz=std::max(hz,z);
        }
        for(int z=lz;z<=hz;++z)for(int x=lx;x<=hx;++x)bins[size_t(z*columns+x)].push_back(i);
    }
    out.supportOffsets.clear();out.supportIndices.clear();
    for(const auto &bin:bins) {
        out.supportOffsets.push_back(out.supportIndices.size());
        out.supportIndices.insert(out.supportIndices.end(),bin.begin(),bin.end());
    }
    out.supportOffsets.push_back(out.supportIndices.size());
}
float radius(const CanyonDecoration &d) {
    // Upper bound for the renderer's rotated asset footprint, before loading
    // assets. Trees use its explicit trunk support radius.
    return d.kind==CanyonDecorationKind::Tree ? .45f :
        d.span*.707107f+(d.kind==CanyonDecorationKind::Cactus ? .35f : .15f);
}
// Conservative projected bounds reject only triangles strictly separated
// from the clipping rectangle; edge contacts retain the exact clipping path.
bool outside(const CanyonSurfaceTriangle &t,float x0,float x1,float z0,float z1) {
    constexpr float padding=.00002f;
    const auto &v=t.vertices;
    return std::max({v[0].x,v[1].x,v[2].x})<x0-padding ||
           std::min({v[0].x,v[1].x,v[2].x})>x1+padding ||
           std::max({v[0].z,v[1].z,v[2].z})<z0-padding ||
           std::min({v[0].z,v[1].z,v[2].z})>z1+padding;
}
bool onFloor(const CanyonAppearance &out,Vector3 p,float r) {
    Volume square;
    square.planes={{{1,0,0},p.x+r},{{-1,0,0},-p.x+r},{{0,0,1},p.z+r},{{0,0,-1},-p.z+r}};
    for(const auto &t:out.triangles)if(!t.rock) {
        if(outside(t,p.x-r,p.x+r,p.z-r,p.z+r))continue;
        auto part=clipToVolume({t.vertices[0],t.vertices[1],t.vertices[2]},square);
        double area=0;
        for(size_t i=1;i+1<part.size();++i)
            area+=std::abs(double(part[i].x-part[0].x)*(part[i+1].z-part[0].z)-
                           double(part[i].z-part[0].z)*(part[i+1].x-part[0].x));
        if(area>1e-9)return true;
    }
    return false;
}
}

bool placeOnSurface(const CanyonAppearance &out,const cliffOptions::Mesh &mesh,
                    Vector3 &p,float r,size_t &tests,float tolerance) {
    ++tests;
    if(!out.supports(p,r,tolerance))return false;
    float low=10000,high=-10000;
    const int steps=std::max(2,int(std::ceil(2*r/.12f)));
    for(int x=0;x<=steps;++x)for(int z=0;z<=steps;++z) {
        const Vector3 from{p.x-r+2*r*x/steps,20,p.z-r+2*r*z/steps};
        const float hit=traceMesh(mesh,from,{0,-1,0});
        // No height-field fallback: a genuine missing patch cannot support a plant.
        if(hit>=1000)return false;
        low=std::min(low,20-hit);high=std::max(high,20-hit);
    }
    if(high-low>tolerance || low<-.015f)return false;
    p.y=low-.025f;
    return true;
}

void addScenery(CanyonAppearance &out,const std::vector<cliffDetail::Quad> &wall,Experiment &rocks,uint64_t seed) {
    ConstructionTiming stageTiming("scenery");
    const auto bounds=rocks.editBounds;
    Volume region;
    region.planes={{{1,0,0},bounds.max.x},{{-1,0,0},-bounds.min.x},
                   {{0,0,1},bounds.max.z},{{0,0,-1},-bounds.min.z}};
    auto inside=[&](Vector3 p,float r) {
        return p.x-r>bounds.min.x && p.x+r<bounds.max.x && p.z-r>bounds.min.z && p.z+r<bounds.max.z;
    };
    // Preserve the old support surface outside this finite work region. Inside,
    // use the final upper shell, including side risers that reject edge-straddling
    // placements. Downward foundation faces are not plant support.
    const auto &original=out.supportTriangles.empty()?out.triangles:out.supportTriangles;
    const std::vector<Volume> regions{region};
    auto supportShell=[&](bool prune) {
        std::vector<CanyonSurfaceTriangle> support;
        support.reserve(original.size());
        for(const auto &t:original) {
            if(prune && outside(t,bounds.min.x,bounds.max.x,bounds.min.z,bounds.max.z)) {support.push_back(t);continue;}
            for(const auto &part:exposed({t.vertices[0],t.vertices[1],t.vertices[2]},regions))append(support,part,t.rock);
        }
        for(const auto &t:out.triangles) {
            if(prune && outside(t,bounds.min.x,bounds.max.x,bounds.min.z,bounds.max.z))continue;
            const auto n=Vector3Normalize(Vector3CrossProduct(sub(t.vertices[1],t.vertices[0]),sub(t.vertices[2],t.vertices[0])));
            if(n.y<-.001f)continue;
            append(support,clipToVolume({t.vertices[0],t.vertices[1],t.vertices[2]},region),t.rock);
        }
        return support;
    };
    auto support=supportShell(true);
    if(std::getenv("DW_CLIFF_VERIFY_SUPPORT")) {
        ValidationTiming measured;
        const auto reference=supportShell(false);
        if(reference.size()!=support.size())throw std::runtime_error("Support pruning changed triangle count");
        for(size_t i=0;i<support.size();++i) {
            if(reference[i].rock!=support[i].rock)throw std::runtime_error("Support pruning changed triangle kind");
            for(int k=0;k<3;++k) {
                const auto a=reference[i].vertices[k],b=support[i].vertices[k];
                if(a.x!=b.x || a.y!=b.y || a.z!=b.z)throw std::runtime_error("Support pruning changed a triangle vertex");
            }
        }
        std::cout<<"FORMATION_SUPPORT_OPTIMIZATION triangles="<<support.size()<<" exact_reference=PASS\n";
    }
    out.supportTriangles=std::move(support);supportBins(out);
    std::vector<CanyonDecoration> decorations;
    for(auto d:out.decorations) {
        // Preserve floor scenery and every placement outside the local edit.
        if(!inside(d.position,0) || onFloor(out,d.position,radius(d))) {
            decorations.push_back(d);continue;
        }
        auto at=d.position;
        if(!inside(at,radius(d)) || !placeOnSurface(out,rocks.assembledMesh,at,radius(d),rocks.scenerySupportTests,
                                                 d.kind==CanyonDecorationKind::Cactus?.1f:.16f)) {
            ++rocks.sceneryRemoved;continue;
        }
        rocks.sceneryReanchored+=std::abs(d.position.y-at.y)>.00001f;
        if(std::abs(d.position.y-at.y)>.00001f)
            std::cout<<"FORMATION_REANCHOR kind="<<int(d.kind)<<" old_y="<<d.position.y
                     <<" position="<<at.x<<','<<at.y<<','<<at.z<<" support_radius="<<radius(d)<<'\n';
        d.position=at;decorations.push_back(d);
    }
    out.decorations=std::move(decorations);
    std::vector<float> lengths{0};
    for(auto q:wall)lengths.push_back(lengths.back()+distance(q.ab,q.bb));
    auto location=[&](float fraction,float depth) {
        const float s=fraction*lengths.back();
        const size_t i=std::min(wall.size()-1,size_t(std::upper_bound(lengths.begin(),lengths.end(),s)-lengths.begin()-1));
        const auto q=wall[i];
        auto tangent=Vector3Normalize(sub(q.bb,q.ab));tangent.y=0;tangent=Vector3Normalize(tangent);
        auto outward=Vector3Normalize(Vector3CrossProduct(tangent,{0,1,0}));
        if(dot(outward,cliffDetail::normal(rocks.seededComposition?q:wall.front()))<0)outward=mul(outward,-1);
        return sub(Vector3Lerp(q.ab,q.bb,(s-lengths[i])/(lengths[i+1]-lengths[i])),mul(outward,depth));
    };
    // A few uneven pockets, rather than continuous rim planting. Detail uses its
    // own seed stream and never changes the primary formation composition.
    Random rng(seed^0x504c414e5453ULL);
    struct Pocket {float along,depth;int count;CanyonDecorationKind kind;};
    const std::array<Pocket,6> pockets{{
        {.18f,2.2f,3,CanyonDecorationKind::Grass},
        {.39f,4.3f,2,CanyonDecorationKind::Grass},
        {.64f,2.5f,3,CanyonDecorationKind::Grass},
        {.81f,4.8f,2,CanyonDecorationKind::Shrub},
        {.28f,6.6f,1,CanyonDecorationKind::Cactus},
        {.87f,1.1f,2,CanyonDecorationKind::Grass}}};
    for(const auto &pocket:pockets)for(int member=0;member<pocket.count;++member) {
        if(!out.parameters.enabled || out.parameters.candidatesPerRoom==0 ||
           (pocket.depth>3?out.parameters.plateauVegetation:out.parameters.terraceVegetation)<=0)continue;
        for(int attempt=0;attempt<24;++attempt) {
            if(int(out.decorations.size())>=out.parameters.maxDecorations)break;
            auto at=location(std::clamp(pocket.along+rng.real(-.035f,.035f),.02f,.98f),pocket.depth+rng.real(-.6f,.6f));
            const bool cactus=pocket.kind==CanyonDecorationKind::Cactus,shrub=pocket.kind==CanyonDecorationKind::Shrub;
            const float span=cactus?.75f:shrub?rng.real(.48f,.6f):rng.real(.32f,.52f);
            CanyonDecoration d{pocket.kind,pocket.depth>3?CanyonZone::Plateau:CanyonZone::Terrace,at,span,
                               cactus?1.4f:shrub?.65f:rng.real(.4f,.65f),rng.real(0,2*Pi),-1,false};
            if(shrub)d.yaw=std::floor(d.yaw*25)*.04f+.0001f;
            const float r=radius(d);
            if(!inside(at,r) || onFloor(out,at,r+.15f))continue;
            if(std::any_of(out.decorations.begin(),out.decorations.end(),[&](const auto &other) {
                return planarDistance(at,other.position)<(span+other.span)*.6f+.22f;
            }))continue;
            if(!placeOnSurface(out,rocks.assembledMesh,at,r,rocks.scenerySupportTests,cactus?.1f:.16f))continue;
            d.position=at;out.decorations.push_back(d);++rocks.sceneryAdded;
            std::cout<<"FORMATION_PLANT kind="<<int(d.kind)<<" zone="<<int(d.zone)<<" position="<<at.x<<','<<at.y<<','<<at.z
                     <<" span="<<d.span<<" height="<<d.height<<" yaw="<<d.yaw<<" support_radius="<<r<<'\n';
            break;
        }
    }
    std::cout<<"FORMATION_SCENERY reanchored="<<rocks.sceneryReanchored<<" unsupported_removed="<<rocks.sceneryRemoved
             <<" added="<<rocks.sceneryAdded<<" support_tests="<<rocks.scenerySupportTests
             <<" support=final_visible_surface outside_and_floor_placements=unchanged\n";
}
} // namespace dw::rockFormations
