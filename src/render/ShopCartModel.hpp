#pragma once
#include "platform/Assets.hpp"
#include "world/ShopCartGeometry.hpp"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <algorithm>
#include <array>
#include <filesystem>
#include <unordered_set>
namespace dw {
// Existing Fort Mercy mesh/material assembly, using the shared mission passes.
class ShopCartModel {
  public:
    ~ShopCartModel(){unload();}
    ShopCartModel()=default;
    ShopCartModel(const ShopCartModel &)=delete;
    ShopCartModel &operator=(const ShopCartModel &)=delete;
    bool ready()const{return model_.meshCount>0;}
    void unload() {
        std::unordered_set<unsigned> textures;
        if(model_.meshCount) {
            for(int i=0;i<model_.materialCount;++i) {
                const auto t=model_.materials[i].maps[MATERIAL_MAP_ALBEDO].texture;
                if(t.id&&t.id!=rlGetTextureIdDefault()&&textures.insert(t.id).second)UnloadTexture(t);
            }
            UnloadModel(model_);model_={};
        }
        attempted_=false;
    }
    bool prepare() {
        if(attempted_)return ready();
        attempted_=true;
#ifdef __EMSCRIPTEN__
        const auto path=std::filesystem::path("/assets/props/shop-cart/shop-cart.glb");
#else
        auto path=sourceAssetDirectory()/"props/shop-cart/shop-cart.glb";
        if(!std::filesystem::is_regular_file(path))path=std::filesystem::path(GetApplicationDirectory())/"assets/props/shop-cart/shop-cart.glb";
#endif
        if(!std::filesystem::is_regular_file(path)){TraceLog(LOG_ERROR,"Shop wagon missing: %s",path.string().c_str());return false;}
        model_=LoadModel(path.string().c_str());return ready();
    }
    void draw(Vector3 center,Shader shader={},Texture2D shadowMap={}) {
        if(!prepare())return;
        const auto transform=MatrixMultiply(model_.transform,MatrixTranslate(center.x,.02f,center.z));
        rlDrawRenderBatchActive();rlDisableBackfaceCulling();
        for(int i=0;i<model_.meshCount;++i) {
            auto material=model_.materials[model_.meshMaterial[i]];
            std::array<MaterialMap,12> maps;std::copy_n(material.maps,maps.size(),maps.begin());material.maps=maps.data();
            if(shader.id){material.shader=shader;maps[MATERIAL_MAP_METALNESS].texture=shadowMap;}
            DrawMesh(model_.meshes[i],material,transform);
        }
        rlEnableBackfaceCulling();
    }
  private:
    Model model_{};bool attempted_=false;
};
} // namespace dw
