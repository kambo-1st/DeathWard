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
// Owned Synty Polygon Western register and crate. Normal scene mesh material/shadow binding.
class DonationModel {
public:
    DonationModel()=default;
    DonationModel(const DonationModel&)=delete;
    DonationModel &operator=(const DonationModel&)=delete;
    ~DonationModel(){unload();}
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
        if(attempted_)return ready();
        attempted_=true;
#ifdef __EMSCRIPTEN__
        const auto path=std::filesystem::path("/assets/props/donation/donation.glb");
#else
        auto path=sourceAssetDirectory()/"props/donation/donation.glb";
        if(!std::filesystem::is_regular_file(path))path=std::filesystem::path(GetApplicationDirectory())/"assets/props/donation/donation.glb";
#endif
        if(!std::filesystem::is_regular_file(path)){TraceLog(LOG_ERROR,"Donation model missing: %s",path.string().c_str());return false;}
        model_=LoadModel(path.string().c_str());return ready();
    }
    void draw(Vector3 at,Shader shader,Texture2D shadowMap) {
        if(!prepare())return;
        rlDrawRenderBatchActive();
        // Grounded mesh, aligned to the ordinary collision footprint.
        const auto transform=MatrixMultiply(model_.transform,MatrixTranslate(at.x,at.y,at.z));
        for(int i=0;i<model_.meshCount;++i) {
            auto material=model_.materials[model_.meshMaterial[i]];
            std::array<MaterialMap,12> maps;std::copy_n(material.maps,maps.size(),maps.begin());material.maps=maps.data();
            if(shader.id){material.shader=shader;maps[MATERIAL_MAP_METALNESS].texture=shadowMap;}
            DrawMesh(model_.meshes[i],material,transform);
        }
    }

private:
    Model model_{};bool attempted_=false;
};
} // namespace dw
