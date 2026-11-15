#pragma once
#include "combat/ChestGeometry.hpp"
#include "platform/Assets.hpp"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <algorithm>
#include <array>
#include <filesystem>
#include <unordered_set>

namespace dw {
// Poses the two scene-library parts; lighting is supplied by the scene, using
// the same material/shadow binding as SkinnedModel and Fort Mercy dressing.
class ChestModel {
  public:
    ~ChestModel(){unload();}
    ChestModel()=default;
    ChestModel(const ChestModel &)=delete;
    ChestModel &operator=(const ChestModel &)=delete;
    void unload() {
        std::unordered_set<unsigned> textures;
        for(auto *m:{&base_,&lid_})if(m->meshCount) {
            for(int i=0;i<m->materialCount;++i) {
                auto texture=m->materials[i].maps[MATERIAL_MAP_ALBEDO].texture;
                if(texture.id&&texture.id!=rlGetTextureIdDefault()&&textures.insert(texture.id).second)UnloadTexture(texture);
            }
            UnloadModel(*m);*m={};
        }
        attempted_=false;
    }
    bool ready()const{return base_.meshCount>0&&lid_.meshCount>0;}
    bool prepare() {
        if(attempted_)return ready();
        attempted_=true;
#ifdef __EMSCRIPTEN__
        const auto path=std::filesystem::path("/assets/pickups/chest");
#else
        auto path=sourceAssetDirectory()/"pickups/chest";
        if(!std::filesystem::is_directory(path))path=std::filesystem::path(GetApplicationDirectory())/"assets/pickups/chest";
#endif
        if(!std::filesystem::is_regular_file(path/"base.glb")||!std::filesystem::is_regular_file(path/"lid.glb")) {
            TraceLog(LOG_ERROR,"Chest scene assets missing: %s",path.string().c_str());return false;
        }
        base_=LoadModel((path/"base.glb").string().c_str());
        lid_=LoadModel((path/"lid.glb").string().c_str());
        return ready();
    }
    void draw(Vector3 at,float open,Shader shader={},Texture2D shadowMap={}) {
        if(!prepare())return;
        constexpr float scale=chestGeometry::ModelScale;at.y=.04f;
        const auto body=MatrixMultiply(MatrixScale(scale,scale,scale),MatrixTranslate(at.x,at.y,at.z));
        const auto lid=MatrixMultiply(MatrixMultiply(MatrixScale(scale,scale,scale),MatrixRotateX(-105*DEG2RAD*open)),
                                      MatrixTranslate(at.x,at.y+.48f*scale,at.z-.29f*scale));
        rlDrawRenderBatchActive();
        rlDisableBackfaceCulling(); // Scene-library props include two-sided shells.
        drawPart(base_,body,shader,shadowMap);
        drawPart(lid_,lid,shader,shadowMap);
        rlEnableBackfaceCulling();
    }
  private:
    Model base_{},lid_{};bool attempted_=false;
    static void drawPart(const Model &model,Matrix transform,Shader shader,Texture2D shadowMap) {
        transform=MatrixMultiply(model.transform,transform);
        for(int i=0;i<model.meshCount;++i) {
            auto material=model.materials[model.meshMaterial[i]];
            std::array<MaterialMap,12> maps;
            std::copy_n(material.maps,maps.size(),maps.begin());material.maps=maps.data();
            if(shader.id) {
                material.shader=shader;
                maps[MATERIAL_MAP_METALNESS].texture=shadowMap;
            }
            DrawMesh(model.meshes[i],material,transform);
        }
    }
};
} // namespace dw
