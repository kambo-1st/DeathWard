#include "world/FlagCloth.hpp"
#include "raymath.h"
#include <stdexcept>

namespace dw {
namespace {
float coord(Vector3 p,int axis) {return axis==0?p.x:p.z;}
float smooth(float t) {t=std::clamp(t,0.f,1.f);return t*t*(3-2*t);}
Vector3 mix(Vector3 a,Vector3 b,float t) {return add(mul(a,1-t),mul(b,t));}
void include(Box &box,Vector3 p) {
    box.min={std::min(box.min.x,p.x),std::min(box.min.y,p.y),std::min(box.min.z,p.z)};
    box.max={std::max(box.max.x,p.x),std::max(box.max.y,p.y),std::max(box.max.z,p.z)};
}
constexpr Box EmptyBounds{{1e9f,1e9f,1e9f},{-1e9f,-1e9f,-1e9f}};
struct Vertex {Vector3 p,n;Vector2 uv;Color color;};
Vertex midpoint(const Vertex &a,const Vertex &b) {
    return {mul(add(a.p,b.p),.5f),unit(add(a.n,b.n)),{(a.uv.x+b.uv.x)*.5f,(a.uv.y+b.uv.y)*.5f},
        {static_cast<unsigned char>((int(a.color.r)+b.color.r)/2),static_cast<unsigned char>((int(a.color.g)+b.color.g)/2),
         static_cast<unsigned char>((int(a.color.b)+b.color.b)/2),static_cast<unsigned char>((int(a.color.a)+b.color.a)/2)}};
}
void triangle(FlagSurface &out,Vertex a,Vertex b,Vertex c,int depth) {
    if(depth) {
        auto ab=midpoint(a,b),bc=midpoint(b,c),ca=midpoint(c,a);
        triangle(out,a,ab,ca,depth-1);triangle(out,ab,b,bc,depth-1);
        triangle(out,ca,bc,c,depth-1);triangle(out,ab,bc,ca,depth-1);
    } else for(auto v:{a,b,c}) {
        out.rest.push_back(v.p);out.normals.push_back(v.n);out.uv.push_back(v.uv);out.colors.push_back(v.color);
    }
}
}
bool flagFabric(const TownAsset &asset) {
    const auto size=sub(asset.bounds.max,asset.bounds.min);
    return asset.label.find("Flag")!=std::string::npos && asset.count==1 &&
        size.y>.2f && std::max(size.x,size.z)>.4f &&
        std::min(size.x,size.z)<std::max(size.x,size.z)*.08f;
}
uint32_t flagSeed(const std::string &id) {
    uint32_t hash=2166136261u;for(unsigned char c:id)hash=(hash^c)*16777619u;return hash;
}
FlagPose::FlagPose(Box rest,Matrix placement,double time,float storm,uint32_t seed):bounds_(rest) {
    axis_=rest.max.x-rest.min.x>rest.max.z-rest.min.z?0:2;
    width_=std::max(.001f,coord(rest.max,axis_)-coord(rest.min,axis_));
    height_=std::max(.001f,rest.max.y-rest.min.y);
    if(!std::isfinite(time))time=0;
    storm=std::isfinite(storm)?std::clamp(storm,0.f,1.f):0;
    // The existing prefab is attached along its maximum horizontal coordinate.
    // World wind matches the blowing sand's 7.5 / 2.4 direction in weather.particles.
    const Vector3 away=axis_==2?Vector3{0,0,-1}:Vector3{-1,0,0};
    const Vector3 across=axis_==2?Vector3{1,0,0}:Vector3{0,0,1};
    const auto inverse=MatrixInvert(placement);
    const auto wind=unit(sub(Vector3Transform({7.5f,0,2.4f},inverse),Vector3Transform({},inverse)));
    const float heading=std::clamp(std::atan2(dot(wind,across),dot(wind,away)),-1.35f,1.35f);
    const float phase=float(seed%65521u)/65521.f*2*Pi;
    const float gust=float(.5+.32*std::sin(time*.63)+.18*std::sin(time*1.17+.8));
    const float flutter=.40f+.23f*gust+.24f*storm;
    // Storm blends the faster ripple's amplitude, not time * frequency. Changing
    // frequency with the weather would jump phase after a long-running session.
    const double wave=time*4.7;
    const double ripple=time*11.7;
    for(int row=0;row<=Rows;++row) {
        const float v=float(row)/Rows;
        Vector3 displacement{};
        for(int col=1;col<=Columns;++col) {
            const float u=(col-.5f)/Columns;
            const float freedom=smooth((u-.03f)/.82f);
            const float billow=flutter*(1+.12f*(1-v))*float(std::sin(2*Pi*u*1.55-wave+phase+.9f*v)+
                (.20+.24*storm)*std::sin(2*Pi*u*3.7-ripple+phase*1.7+1.4*v));
            const float yaw=freedom*(heading+billow);
            const float pitch=freedom*(-.26f*(1-.68f*storm)*(1-.3f*gust)+
                .085f*float(std::sin(2*Pi*u*2-wave*.81+phase+v*1.3f)));
            const auto tangent=add(add(mul(away,std::cos(yaw)*std::cos(pitch)),
                                       mul(across,std::sin(yaw)*std::cos(pitch))),{0,std::sin(pitch),0});
            displacement=add(displacement,mul(sub(tangent,away),width_/Columns));
            offsets_[size_t(row*(Columns+1)+col)]=displacement;
        }
    }
}
void FlagPose::field(Vector3 rest,Vector3 &offset,Vector3 &along,Vector3 &vertical) const {
    const float u=std::clamp((coord(bounds_.max,axis_)-coord(rest,axis_))/width_,0.f,1.f);
    const float v=std::clamp((rest.y-bounds_.min.y)/height_,0.f,1.f);
    const float x=u*Columns,y=v*Rows;
    const int c=std::min(int(x),Columns-1),r=std::min(int(y),Rows-1);
    const float a=x-c,b=y-r;
    const auto p00=offsets_[size_t(r*(Columns+1)+c)],p10=offsets_[size_t(r*(Columns+1)+c+1)];
    const auto p01=offsets_[size_t((r+1)*(Columns+1)+c)],p11=offsets_[size_t((r+1)*(Columns+1)+c+1)];
    offset=mix(mix(p00,p10,a),mix(p01,p11,a),b);
    along=mul(mix(sub(p10,p00),sub(p11,p01),b),-Columns/width_);
    vertical=mul(mix(sub(p01,p00),sub(p11,p10),a),Rows/height_);
}
Vector3 FlagPose::position(Vector3 rest) const {
    Vector3 offset,along,vertical;field(rest,offset,along,vertical);return add(rest,offset);
}
Vector3 FlagPose::normal(Vector3 rest,Vector3 normal) const {
    Vector3 offset,along,vertical;field(rest,offset,along,vertical);
    const auto dx=add({1,0,0},axis_==0?along:Vector3{}),dy=add({0,1,0},vertical),
               dz=add({0,0,1},axis_==2?along:Vector3{});
    return unit(add(add(mul(Vector3CrossProduct(dy,dz),normal.x),mul(Vector3CrossProduct(dz,dx),normal.y)),
                    mul(Vector3CrossProduct(dx,dy),normal.z)));
}
void FlagSurface::build(const Mesh &source) {
    *this={};restBounds=EmptyBounds;
    if(!source.vertices||source.vertexCount<3||source.triangleCount<1||source.triangleCount>2048)
        throw std::runtime_error("Unsupported flag fabric mesh");
    const auto count=size_t(source.triangleCount)*3*16;
    rest.reserve(count);normals.reserve(count);uv.reserve(count);colors.reserve(count);
    for(int face=0;face<source.triangleCount;++face) {
        Vertex vertices[3];
        for(int n=0;n<3;++n) {
            const int i=source.indices?source.indices[face*3+n]:face*3+n;
            if(i>=source.vertexCount)throw std::runtime_error("Invalid flag triangle");
            vertices[n]={{source.vertices[3*i],source.vertices[3*i+1],source.vertices[3*i+2]},
                source.normals?Vector3{source.normals[3*i],source.normals[3*i+1],source.normals[3*i+2]}:Vector3{1,0,0},
                source.texcoords?Vector2{source.texcoords[2*i],source.texcoords[2*i+1]}:Vector2{},
                source.colors?Color{source.colors[4*i],source.colors[4*i+1],source.colors[4*i+2],source.colors[4*i+3]}:WHITE};
            include(restBounds,vertices[n].p);
        }
        triangle(*this,vertices[0],vertices[1],vertices[2],2);
    }
    posed=rest;posedNormals=normals;bounds=restBounds;
}
void FlagSurface::pose(Matrix placement,double time,float storm,uint32_t seed) {
    const FlagPose field(restBounds,placement,time,storm,seed);
    bounds=EmptyBounds;
    for(size_t i=0;i<rest.size();++i) {
        posed[i]=field.position(rest[i]);posedNormals[i]=field.normal(rest[i],normals[i]);include(bounds,posed[i]);
    }
}
}
