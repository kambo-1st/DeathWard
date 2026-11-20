#pragma once
#include "platform/Assets.hpp"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <algorithm>
#include <array>
#include <filesystem>
#include <unordered_set>
namespace dw {
// Owned Synty Polygon Generic prop. Normal scene mesh material/shadow binding.
class KeyModel {
public:
    KeyModel()=default;
    KeyModel(const KeyModel&)=delete;
    KeyModel &operator=(const KeyModel&)=delete;
    ~KeyModel(){unload();}
    bool ready()const{return model_.meshCount>0;}
    void unload() {
        if(ready()) {
            std::unordered_set<unsigned> ids;
            for(int i=0;i<model_.materialCount;++i) {
                auto t=model_.materials[i].maps[MATERIAL_MAP_ALBEDO].texture;
                if(t.id&&t.id!=rlGetTextureIdDefault()&&ids.insert(t.id).second)UnloadTexture(t);
            }
            UnloadModel(model_);model_={};
        }
        attempted_=false;
    }
    bool prepare() {
        if(attempted_)return ready();attempted_=true;
#ifdef __EMSCRIPTEN__
        const auto path=std::filesystem::path("/assets/pickups/key/key.glb");
#else
        auto path=sourceAssetDirectory()/"pickups/key/key.glb";
        if(!std::filesystem::is_regular_file(path))path=std::filesystem::path(GetApplicationDirectory())/"assets/pickups/key/key.glb";
#endif
        if(!std::filesystem::is_regular_file(path)){TraceLog(LOG_ERROR,"Key model missing: %s",path.string().c_str());return false;}
        model_=LoadModel(path.string().c_str());return ready();
    }
    void draw(Vector3 at,float scale,bool pair,Shader shader,Texture2D shadowMap,bool golden=false) {
        if(scale<=0||!prepare())return;
        rlDrawRenderBatchActive();
        for(int k=0;k<(pair?2:1);++k) {
            // Face the ordinary isometric camera; a second mesh identifies a double key.
            auto transform=MatrixMultiply(MatrixScale(scale,scale,scale),MatrixRotateY(45*DEG2RAD));
            transform=MatrixMultiply(transform,MatrixTranslate(at.x+k*.16f*scale,at.y+k*.16f*scale,at.z));
            transform=MatrixMultiply(model_.transform,transform);
            for(int i=0;i<model_.meshCount;++i) {
                auto material=model_.materials[model_.meshMaterial[i]];
                std::array<MaterialMap,12> maps;std::copy_n(material.maps,maps.size(),maps.begin());material.maps=maps.data();
                if(golden) {
                    // Reuse the owned mesh with a gold scene material; no source artwork.
                    maps[MATERIAL_MAP_ALBEDO].texture={rlGetTextureIdDefault(),1,1,1,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
                    maps[MATERIAL_MAP_ALBEDO].color={255,202,55,255};
                }
                if(shader.id){material.shader=shader;maps[MATERIAL_MAP_METALNESS].texture=shadowMap;}
                DrawMesh(model_.meshes[i],material,transform);
            }
        }
    }
private:
    Model model_{};bool attempted_=false;
};
} // namespace dw
