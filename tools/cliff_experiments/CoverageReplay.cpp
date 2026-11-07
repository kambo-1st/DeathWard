#include "RockFormations.hpp"
#include <bit>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string_view>

// Diagnostic input: face count; nine uint32 float bit patterns per face;
// volume count; plane count and four double coefficients per volume.
int main(int argc,char **argv) {
    try {
        using namespace dw::rockFormations;
        dw::cliffOptions::Mesh mesh;size_t count=0;
        if(!(std::cin>>count))throw std::runtime_error("Missing face count");
        for(size_t i=0;i<count;++i) {
            dw::cliffOptions::Triangle face;
            for(auto &p:face){uint32_t x,y,z;if(!(std::cin>>x>>y>>z))throw std::runtime_error("Truncated face bits");p={std::bit_cast<float>(x),std::bit_cast<float>(y),std::bit_cast<float>(z)};}
            mesh.faces.push_back(face);
        }
        std::vector<Volume> volumes;if(!(std::cin>>count))throw std::runtime_error("Missing volume count");
        for(size_t i=0;i<count;++i) {
            Volume v;size_t planes;if(!(std::cin>>planes))throw std::runtime_error("Missing plane count");
            for(size_t k=0;k<planes;++k){Plane p;p.hasPreciseNormal=true;if(!(std::cin>>p.preciseNormal[0]>>p.preciseNormal[1]>>p.preciseNormal[2]>>p.distance))throw std::runtime_error("Truncated source plane");p.normal={float(p.preciseNormal[0]),float(p.preciseNormal[1]),float(p.preciseNormal[2])};v.planes.push_back(p);}
            volumes.push_back(std::move(v));
        }
        bool simplify=false,boolean=false;double tolerance=.000008;
        for(int k=1;k<argc;++k) {
            const std::string_view arg=argv[k];
            if(arg=="--simplify")simplify=true;
            else if(arg=="--boolean" && k+1<argc){boolean=true;tolerance=std::stod(argv[++k]);}
            else throw std::runtime_error("Unknown mesh replay option");
        }
        const auto before=mesh.faces.size();
        if(boolean) {
            size_t bodyBegin,bodyCount,bodies;if(!(std::cin>>bodyBegin>>bodyCount>>bodies))throw std::runtime_error("Missing Boolean source map");
            std::vector<dw::cliffOptions::Mesh> checked;size_t offset=0;
            for(size_t k=0;k<bodies;++k){size_t faces;if(!(std::cin>>faces) || faces>mesh.faces.size()-offset)throw std::runtime_error("Truncated Boolean body map");dw::cliffOptions::Mesh body;body.faces.insert(body.faces.end(),mesh.faces.begin()+offset,mesh.faces.begin()+offset+faces);offset+=faces;checked.push_back(std::move(body));}
            if(offset!=mesh.faces.size())throw std::runtime_error("Boolean body map loses faces");
            for(size_t k=0;k<checked.size();++k) {
                const auto a=auditStrictSurface(checked[k]);
                std::cout<<"REPLAY_BODY index="<<k<<" faces="<<checked[k].faces.size()<<" crossings="<<a.selfIntersections<<" overlaps="<<a.coplanarOverlaps<<'\n';
                if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")){const auto output=std::string(path)+".body"+std::to_string(k)+".json";writeSurfaceProbe(output.c_str(),checked[k],{},a);}
            }
            mesh=solidBooleanUnion(volumes,tolerance,0,{},checked,bodyBegin,bodyCount);
        }
        if(simplify)mesh=simplifyPlateauSurface(mesh);
        const auto strict=auditStrictSurface(mesh);
        if(const auto path=std::getenv("DW_CLIFF_INVALID_PROBE")){const auto output=std::string(path)+".mesh.json";writeSurfaceProbe(output.c_str(),mesh,volumes,strict);}
        const auto audit=auditBoundaryCoverage(mesh,volumes);
        std::cout<<"COVERAGE_REPLAY input_faces="<<before<<" output_faces="<<mesh.faces.size()<<" open="<<strict.exact.boundaryEdges<<" nonmanifold="<<strict.exact.nonmanifoldEdges<<" links="<<strict.nonmanifoldVertices<<" crossings="<<strict.selfIntersections<<" overlaps="<<strict.coplanarOverlaps<<" degenerate="<<strict.exact.degenerateFaces<<" winding="<<strict.exact.windingErrors<<" duplicates="<<strict.exact.duplicateFaces<<" components="<<strict.exact.components<<" buried="<<audit.buriedFragments<<" detached="<<audit.detachedFragments<<" buried_area="<<audit.buriedArea<<" detached_area="<<audit.detachedArea<<'\n';
        return 0;
    } catch(const std::exception &error){std::cerr<<"COVERAGE_REPLAY_ERROR "<<error.what()<<'\n';return 1;}
}
