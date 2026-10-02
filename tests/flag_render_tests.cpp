#include "render/TownScene.hpp"
#include "render/PostProcess.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <cstring>
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const char *message) {if(!ok)throw std::runtime_error(message);}
int main() {
    try {
        SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(1200,800,"Fort flag verification");check(IsWindowReady(),"graphics display required");
        std::filesystem::create_directories("artifacts/flags");
        TownScene scene;PostProcess post;
        for(auto hub:{HubKind::Redstone,HubKind::Frontier}) {
            check(scene.load(TownScene::assetDirectory(hub)),"load fort scene");check(scene.flagCount()==2,"two animated cloth instances");
            size_t flag=0;
            while(!flagFabric(scene.document().assets[scene.document().instances[flag].asset]))++flag;
            const auto &instance=scene.document().instances[flag];
            const auto &asset=scene.document().assets[instance.asset];
            const auto &source=scene.model().meshes[asset.first];
            const std::vector<float> before(source.vertices,source.vertices+source.vertexCount*3);
            const auto focus=Vector3Transform(mul(add(asset.bounds.min,asset.bounds.max),.5f),instance.transform);
            Camera3D camera{add(focus,{4,2,5}),focus,{0,1,0},42,CAMERA_PERSPECTIVE};
            auto render=[&](double time,float storm,const std::string &name) {
                scene.prepareFlags(time,storm);scene.prepareLighting(camera);
                check(scene.shadowsReady(),"cloth uses live sun shadows");
                BeginDrawing();post.begin({142,174,188,255},distance(camera.position,camera.target));
                BeginMode3D(camera);scene.draw(focus);scene.draw(focus,true);EndMode3D();post.end();
                rlDrawRenderBatchActive();auto image=LoadImageFromScreen();
                ExportImage(image,("artifacts/flags/"+name+".png").c_str());UnloadImage(image);EndDrawing();
            };
            const auto name=std::string(hub==HubKind::Redstone?"redstone":"frontier");
            render(2,0,name+"-calm");const auto first=scene.instanceBounds(flag);
            render(2.45,1,name+"-gust");const auto next=scene.instanceBounds(flag);
            check(distance(first.min,next.min)+distance(first.max,next.max)>.01f,"live cloth bounds follow the gust");
            scene.prepareFlags(2.45,1);const auto paused=scene.instanceBounds(flag);
            check(distance(next.min,paused.min)+distance(next.max,paused.max)==0,"paused cloth retains its exact pose");
            check(std::memcmp(source.vertices,before.data(),before.size()*sizeof(float))==0,"original mesh is never deformed in place");
            auto edited=scene.document();edited.instances[flag].castsShadow=false;
            scene.applyDocument(edited);render(2.45,1,name+"-shadow-off");
            auto copy=edited.instances[flag];copy.transform.m12+=.6f;copy.id+="-duplicate";
            edited.instances.push_back(copy);scene.applyDocument(edited);
            check(scene.flagCount()==3,"editor copies bind their own cloth");
            render(2.45,0,name+"-copy");
            scene.unload();check(scene.flagCount()==0,"cloth buffers are released on map change");
        }
        post.unload();CloseWindow();std::cout<<"PASS fort cloth GPU buffers, shadows, preview pause, duplicate and unchanged source geometry\n";
    } catch(const std::exception &e) {if(IsWindowReady())CloseWindow();std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}
}
