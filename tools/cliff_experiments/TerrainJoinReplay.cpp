#include "RockFormations.hpp"
#include "FormationPrecision.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw::rockFormations;
namespace {
size_t count(std::istream &in,size_t limit) {
    size_t n;if(!(in>>n)||n>limit)throw std::runtime_error("Invalid fixture count");return n;
}
std::vector<Polygon> polygons(std::istream &in) {
    std::vector<Polygon> out(count(in,1000000));
    for(auto &f:out){f.resize(count(in,1000));for(auto &p:f)if(!(in>>p.x>>p.y>>p.z))throw std::runtime_error("Truncated polygon");}return out;
}
dw::cliffOptions::Mesh mesh(std::istream &in) {
    dw::cliffOptions::Mesh out;out.faces.resize(count(in,1000000));
    for(auto &f:out.faces)for(auto &p:f)if(!(in>>p.x>>p.y>>p.z))throw std::runtime_error("Truncated core");return out;
}
}
// DWJOIN1: closed CSG operands. DWADAPTER2: visible adapter input and flags.
// Neither format regenerates the floor or reconstructs the checked cliff core.
int main(int argc,char **argv) {
    try {
        const bool sourceOnly=argc==3 && std::string(argv[2])=="--audit-source";
        if(argc!=2 && !sourceOnly)throw std::runtime_error("Usage: terrain-join-replay fixture.txt [--audit-source]");
        std::ifstream in(argv[1]);std::string magic;if(!(in>>magic))throw std::runtime_error("Missing fixture header");
        if(magic=="DWADAPTER1" || magic=="DWADAPTER2") {
            Experiment rocks;bool context,precise,single,grid;Vector3 origin{};
            if(!(in>>context>>precise>>single>>grid>>origin.x>>origin.y>>origin.z>>rocks.seededComposition))throw std::runtime_error("Truncated adapter flags");
            auto &b=rocks.editBounds;if(!(in>>b.min.x>>b.min.y>>b.min.z>>b.max.x>>b.max.y>>b.max.z))throw std::runtime_error("Truncated adapter bounds");
            if(magic=="DWADAPTER2")for(const auto flag:{"DW_CLIFF_ROOF_SHELL","DW_CLIFF_EAR_WELD","DW_CLIFF_EXACT_CONTACTS","DW_CLIFF_JOINT_TERRAIN_JOIN","DW_CLIFF_JOINT_WHOLE_SOURCE"}){bool value;if(!(in>>value))throw std::runtime_error("Missing adapter mode flag");if(value)setenv(flag,"1",1);else unsetenv(flag);}
            auto retained=polygons(in),outside=polygons(in);rocks.protectedFloor=polygons(in);rocks.mesh=mesh(in);
            rocks.volumes.resize(count(in,100000));for(auto &v:rocks.volumes){v.planes.resize(count(in,1000));for(auto &p:v.planes){auto &n=p.preciseNormal;if(!(in>>n[0]>>n[1]>>n[2]>>p.distance))throw std::runtime_error("Truncated source plane");p.normal={float(n[0]),float(n[1]),float(n[2])};p.hasPreciseNormal=true;}v.faces=polygons(in);}
            if(magic=="DWADAPTER1"){setenv("DW_CLIFF_JOINT_TERRAIN_JOIN","1",1);setenv("DW_CLIFF_EXACT_CONTACTS","1",1);}
            if(precise)setenv("DW_CLIFF_PRECISE_JOIN","1",1);else unsetenv("DW_CLIFF_PRECISE_JOIN");
            if(single)setenv("DW_CLIFF_JOIN_SINGLE_ROUND","1",1);else unsetenv("DW_CLIFF_JOIN_SINGLE_ROUND");
            WorldGridScope world(origin,grid);
            if(sourceOnly) {
                auto baseline=[&](const char *name,const std::vector<Polygon> &polys){
                    dw::cliffOptions::Mesh source;
                    for(const auto &f:polys)for(size_t k=1;k+1<f.size();++k)source.faces.push_back({f[0],f[k],f[k+1]});
                    const auto a=auditStrictSurface(source);
                    if(const auto prefix=std::getenv("DW_CLIFF_SOURCE_BASELINE_PROBE"))writeSurfaceProbe((std::string(prefix)+"."+name+".json").c_str(),source,{},a);
                    std::cout<<"SOURCE_BASELINE name="<<name<<" triangles="<<source.faces.size()<<" open="<<a.exact.boundaryEdges<<" nonmanifold="<<a.exact.nonmanifoldEdges<<" links="<<a.nonmanifoldVertices<<" crossings="<<a.selfIntersections<<" overlaps="<<a.coplanarOverlaps<<" degenerate="<<a.exact.degenerateFaces<<" winding="<<a.exact.windingErrors<<" accepted=false diagnostic_only=true\n";
                };
                baseline("selected",retained);auto combined=retained;combined.insert(combined.end(),outside.begin(),outside.end());baseline("with-context",combined);return 0;
            }
            const auto output=assembleSurface(retained,rocks,outside,context);
            std::cout<<"ADAPTER_REPLAY triangles="<<output.faces.size()<<" unexpected_boundary="<<rocks.unexpectedBoundaryEdges<<" crossings="<<rocks.strictAssembledAudit.selfIntersections<<" overlaps="<<rocks.strictAssembledAudit.coplanarOverlaps<<" full_visible_assembly=PASS\n";
            return 0;
        }
        if(magic!="DWJOIN1")throw std::runtime_error("Invalid fixture header");
        std::vector<Volume> old(count(in,100000));for(auto &v:old)v.faces=polygons(in);
        auto core=mesh(in);const auto output=solidBooleanTerrainJoin(old,core);const auto a=auditStrictSurface(output);
        const auto defects=a.exact.boundaryEdges+a.exact.nonmanifoldEdges+a.nonmanifoldVertices+a.exact.degenerateFaces+a.exact.duplicateFaces+a.exact.windingErrors+a.selfIntersections+a.coplanarOverlaps;
        std::cout<<"JOINT_REPLAY defects="<<defects<<" components="<<a.exact.components<<'\n';return defects?2:0;
    } catch(const std::exception &e){std::cerr<<"JOINT_REPLAY_ERROR "<<e.what()<<'\n';return 1;}
}
