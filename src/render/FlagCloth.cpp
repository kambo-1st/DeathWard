#include "render/FlagCloth.hpp"
#include <cstring>

namespace dw {
FlagCloth::FlagCloth(const Mesh &source,uint32_t seed):seed_(seed) {
    surface_.build(source);
    mesh_.vertexCount=int(surface_.rest.size());mesh_.triangleCount=mesh_.vertexCount/3;
    const auto copy=[](const void *data,size_t bytes) {auto *out=MemAlloc(unsigned(bytes));std::memcpy(out,data,bytes);return out;};
    mesh_.vertices=static_cast<float *>(copy(surface_.rest.data(),surface_.rest.size()*sizeof(Vector3)));
    mesh_.normals=static_cast<float *>(copy(surface_.normals.data(),surface_.normals.size()*sizeof(Vector3)));
    mesh_.texcoords=static_cast<float *>(copy(surface_.uv.data(),surface_.uv.size()*sizeof(Vector2)));
    mesh_.colors=static_cast<unsigned char *>(copy(surface_.colors.data(),surface_.colors.size()*sizeof(Color)));
    UploadMesh(&mesh_,true);
}
FlagCloth::~FlagCloth() {UnloadMesh(mesh_);}
void FlagCloth::update(Matrix placement,double time,float storm) {
    if(time==time_&&storm==storm_&&std::memcmp(&placement,&placement_,sizeof(Matrix))==0)return;
    surface_.pose(placement,time,storm,seed_);
    const auto bytes=surface_.posed.size()*sizeof(Vector3);
    std::memcpy(mesh_.vertices,surface_.posed.data(),bytes);
    std::memcpy(mesh_.normals,surface_.posedNormals.data(),bytes);
    UpdateMeshBuffer(mesh_,0,mesh_.vertices,int(bytes),0);
    UpdateMeshBuffer(mesh_,2,mesh_.normals,int(bytes),0);
    time_=time;storm_=storm;placement_=placement;
}
}
