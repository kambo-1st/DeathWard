#include "cinematic/CinematicCast.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool b,const char *m){if(!b)throw std::runtime_error(m);}
int main(){try{
    SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1400,800,"Cinematic cast verification");
    std::array<SkinnedModel,4> models;
    const std::array<const char *,4> names{"bandit","elder_man","elder_woman","conductor"};
    for(size_t i=0;i<models.size();++i){
        auto p=i==0?TownActorModels::modelPath("bandit"):std::filesystem::path(DEATHWARD_ASSET_DIR)/"cinematic_cast"/(std::string(names[i])+".glb");
        check(models[i].load(p,true),"Textured cast model loads with animations");
        const auto &model=models[i].model();
        for(int n=0;n<model.boneCount;++n)check(std::string(model.bones[n].name)!="neutral_bone","All weighted vertices bind to the retained rig");
        for(int n=0;n<model.meshCount;++n) {
            const auto &mesh=model.meshes[n];
            if(mesh.colors)for(int v=0;v<mesh.vertexCount;++v)check(mesh.colors[v*4+3]==255,"Unity vertex masks cannot hide cast surfaces");
        }
    }
    for(int pose=0;pose<2;++pose){
        BeginDrawing();ClearBackground({120,145,165,255});BeginMode3D({{0,4.5f,10},{0,1,0},{0,1,0},45,CAMERA_PERSPECTIVE});
        DrawPlane({0,-.02f,0},{20,20},{192,156,111,255});
        for(size_t i=0;i<models.size();++i){
            auto &model=models[i];auto b=GetModelBoundingBox(model.model());float scale=1.9f/(b.max.y-b.min.y);
            model.poseCinematic(6,pose==1,false,true);
            auto bb=model.bounds({float(i)*2-3,0,0},{0,0,1},scale);
            check(std::isfinite(bb.min.x)&&bb.max.y<2.5f&&bb.min.y>-.6f,"Cast poses stay human-sized and finite");
            rlDisableBackfaceCulling();model.draw({float(i)*2-3,0,0},{0,0,1},scale);rlEnableBackfaceCulling();
            if(pose==1)DrawCubeWires({float(i)*2-3,.35f,-.16f},.7f,.15f,.4f,DARKBROWN);
        }
        EndMode3D();auto image=LoadImageFromScreen();ExportImage(image,("artifacts/opening/cast-"+std::to_string(pose)+".png").c_str());UnloadImage(image);EndDrawing();
    }
    for(auto &m:models)m.unload();CloseWindow();std::cout<<"PASS cinematic cast, textures, clips and seated poses\n";
}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
