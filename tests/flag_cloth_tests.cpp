#include "world/FlagCloth.hpp"
#include "raymath.h"
#define CGLTF_IMPLEMENTATION
#include "cgltf.h"
#include <cstring>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message) {if(!ok)throw std::runtime_error(message);}
struct Library {
    cgltf_data *data=nullptr;
    explicit Library(const std::filesystem::path &path) {
        cgltf_options options{};
        check(cgltf_parse_file(&options,path.string().c_str(),&data)==cgltf_result_success,"load original GLB");
        check(cgltf_load_buffers(&options,data,path.string().c_str())==cgltf_result_success,"read original mesh buffers");
    }
    ~Library() {cgltf_free(data);}
};
struct CpuMesh {
    Mesh mesh{};
    std::vector<float> vertices,normals,uv;
    std::vector<unsigned short> indices;
    explicit CpuMesh(const cgltf_mesh &source) {
        check(source.primitives_count==1,"one material section per catalog entry");
        const auto &part=source.primitives[0];
        for(size_t a=0;a<part.attributes_count;++a) {
            const auto &attr=part.attributes[a];
            std::vector<float> *out=nullptr;size_t components=3;
            if(attr.type==cgltf_attribute_type_position)out=&vertices;
            else if(attr.type==cgltf_attribute_type_normal)out=&normals;
            else if(attr.type==cgltf_attribute_type_texcoord&&attr.index==0){out=&uv;components=2;}
            if(!out)continue;
            out->resize(attr.data->count*components);
            for(size_t n=0;n<attr.data->count;++n)check(cgltf_accessor_read_float(attr.data,n,out->data()+n*components,components),"decode mesh attributes");
        }
        mesh.vertexCount=int(vertices.size()/3);mesh.vertices=vertices.data();mesh.normals=normals.data();mesh.texcoords=uv.data();
        if(part.indices) {
            indices.resize(part.indices->count);
            for(size_t i=0;i<indices.size();++i)indices[i]=static_cast<unsigned short>(cgltf_accessor_read_index(part.indices,i));
            mesh.indices=indices.data();mesh.triangleCount=int(indices.size()/3);
        } else mesh.triangleCount=mesh.vertexCount/3;
    }
};
bool same(const std::vector<Vector3> &a,const std::vector<Vector3> &b) {
    return a.size()==b.size()&&std::memcmp(a.data(),b.data(),a.size()*sizeof(Vector3))==0;
}
}
int main() {
    try {
        for(const char *hub: {"redstone","frontier","town"}) {
            const auto root=std::filesystem::path(DEATHWARD_ASSET_DIR)/hub;
            TownDocument document;std::string error;check(document.load(root/"town.scene",error),error.c_str());
            Library library(root/"town.glb");int fabrics=0,poles=0;
            for(const auto &instance:document.instances) {
                const auto &asset=document.assets[instance.asset];
                if(!flagFabric(asset)) {if(asset.label.find("FlagPole")!=std::string::npos)++poles;continue;}
                ++fabrics;CpuMesh original(library.data->meshes[asset.first]);const auto vertices=original.vertices;
                FlagSurface cloth;cloth.build(original.mesh);
                check(cloth.rest.size()==size_t(original.mesh.triangleCount)*3*16,"subdivide only the original triangles");
                check(original.vertices==vertices,"mesh library is never modified");
                for(int tri=0;tri<original.mesh.triangleCount;++tri) {
                    const int first=original.indices.empty()?tri*3:original.indices[size_t(tri*3)];
                    check(cloth.uv[size_t(tri*48)].x==original.uv[size_t(first*2)]&&
                          cloth.uv[size_t(tri*48)].y==original.uv[size_t(first*2+1)],"original texture coordinates survive subdivision");
                }
                const uint32_t seed=flagSeed(instance.id);
                cloth.pose(instance.transform,8.25,0,seed);const auto calm=cloth.posed;
                cloth.pose(instance.transform,8.25,0,seed);check(same(calm,cloth.posed),"pause is stable");
                cloth.pose(instance.transform,67.5,1,seed);cloth.pose(instance.transform,8.25,0,seed);
                check(same(calm,cloth.posed),"seeking backward reproduces the exact pose");
                cloth.pose(instance.transform,8.25,0,seed+1);check(!same(calm,cloth.posed),"copied flags have individual ripple phases");
                int fixed=0,moved=0;
                for(double t:{0.,.1,8.25,34.,120.})for(float storm:{0.f,1.f}) {
                    cloth.pose(instance.transform,t,storm,seed);
                    for(size_t i=0;i<cloth.rest.size();++i) {
                        const auto p=cloth.posed[i],n=cloth.posedNormals[i];
                        check(std::isfinite(p.x)&&std::isfinite(p.y)&&std::isfinite(p.z),"finite cloth positions");
                        check(std::abs(length(n)-1)<.001f,"normals stay normalized through folds");
                        const float u=(cloth.restBounds.max.z-cloth.rest[i].z)/(cloth.restBounds.max.z-cloth.restBounds.min.z);
                        if(u<1.f/FlagPose::Columns) {check(distance(p,cloth.rest[i])<.00001f,"the pole seam stays exactly pinned");++fixed;}
                        else if(distance(p,cloth.rest[i])>.03f)++moved;
                        check(p.x>=cloth.bounds.min.x&&p.x<=cloth.bounds.max.x&&p.y>=cloth.bounds.min.y&&p.y<=cloth.bounds.max.y&&
                              p.z>=cloth.bounds.min.z&&p.z<=cloth.bounds.max.z,"bounds follow the animated cloth");
                    }
                    FlagPose field(cloth.restBounds,instance.transform,t,storm,seed);
                    const float width=cloth.restBounds.max.z-cloth.restBounds.min.z;
                    const Vector3 sample{0,.11f,cloth.restBounds.max.z-width*.63f};
                    const auto dy=sub(field.position(add(sample,{0,.0001f,0})),field.position(sample));
                    const auto dz=sub(field.position(add(sample,{0,0,.0001f})),field.position(sample));
                    check(dot(field.normal(sample,{1,0,0}),unit(Vector3CrossProduct(mul(dy,10000),mul(dz,10000))))>.995f,
                          "lighting normals follow the actual bent surface");
                    for(int row=0;row<=FlagPose::Rows;++row) {
                        Vector3 rest{0,cloth.restBounds.min.y+(cloth.restBounds.max.y-cloth.restBounds.min.y)*row/FlagPose::Rows,cloth.restBounds.max.z};
                        auto previous=field.position(rest);float arc=0;
                        for(int col=1;col<=FlagPose::Columns;++col) {
                            rest.z=cloth.restBounds.max.z-width*col/FlagPose::Columns;
                            auto p=field.position(rest);arc+=distance(previous,p);previous=p;
                        }
                        check(std::abs(arc-width)<.0001f,"ripples bend the cloth without extending its width");
                    }
                }
                check(fixed>0&&moved>0,"both anchored and moving vertices exist in the real flag");
                double calmSpeed=0,stormSpeed=0;
                const Vector3 tip{0,0,cloth.restBounds.min.z};
                for(int frame=0;frame<180;++frame) {
                    const double t=frame/30.;
                    for(float s:{0.f,1.f}) {
                        FlagPose a(cloth.restBounds,instance.transform,t,s,seed),b(cloth.restBounds,instance.transform,t+.01,s,seed);
                        (s==0?calmSpeed:stormSpeed)+=distance(a.position(tip),b.position(tip));
                    }
                }
                check(stormSpeed>calmSpeed*1.2,"storms produce livelier flutter");
                FlagPose weatherA(cloth.restBounds,instance.transform,10000,.5f,seed),
                         weatherB(cloth.restBounds,instance.transform,10000,.501f,seed);
                check(distance(weatherA.position(tip),weatherB.position(tip))<.01f,
                      "weather strength blends smoothly even late in a session");
            }
            check(fabrics==(std::string(hub)=="town"?0:2),"both fort flags are identified, other town props stay static");
            if(fabrics)check(poles==2,"both poles are excluded from cloth animation");
            std::cout<<"PASS "<<hub<<": "<<fabrics<<" textured flags, pinned seams, gusts, bounds, length and deterministic preview\n";
        }
    } catch(const std::exception &e) {std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}
}
