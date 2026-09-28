#include "render/TownScene.hpp"
#include "render/PostProcess.hpp"
#include "raymath.h"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok, const char *message) { if (!ok) throw std::runtime_error(message); }
int changed(Image a, Image b) {
    auto ca = LoadImageColors(a), cb = LoadImageColors(b);
    int count = 0;
    for (int i=0;i<a.width*a.height;++i)
        if (std::abs(int(ca[i].r)-cb[i].r)+std::abs(int(ca[i].g)-cb[i].g)+std::abs(int(ca[i].b)-cb[i].b)>12) ++count;
    UnloadImageColors(ca); UnloadImageColors(cb);
    return count;
}
int main() {
    try {
        SetTraceLogLevel(LOG_WARNING);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(960,720,"Particle verification");
        TownScene scene;
        check(scene.load(),"Town and effects load");
        check(scene.effects().loaded() && scene.effects().attachmentCount() >= 5,"Campfire props have effects");
        auto document=scene.document();
        auto found=std::find_if(document.assets.begin(),document.assets.end(),[](const auto &a){return a.label=="SM_Env_CampFire_01";});
        check(found!=document.assets.end(),"Original stone-ring fireplace found");
        const auto asset=size_t(found-document.assets.begin());
        document.instances.clear();document.groups.clear();document.paths.clear();
        document.instances.push_back({asset,MatrixIdentity(),"fire-test"});
        scene.applyDocument(document);
        check(scene.effects().attachmentCount()==5,"Exactly five layers attached to one fire");
        ObjectAnimationSystem clock;
        clock.reset(document);
        Camera3D camera{{2.7f,2.3f,3.4f},{0,.5f,0},{0,1,0},38,CAMERA_PERSPECTIVE};
        PostProcess post;
        const auto render=[&](bool effects,bool wall,bool graded=false){
            scene.applyAnimation(clock);
            scene.prepareLighting(camera);
            BeginDrawing();
            if(graded)post.begin({43,48,55,255},distance(camera.position,camera.target));
            else ClearBackground({43,48,55,255});
            BeginMode3D(camera);
            DrawPlane({0,-.11f,0},{30,30},{110,89,66,255});
            scene.draw(camera.target);
            if(wall)DrawCube({0,1,1.4f},12,6,.3f,{65,74,82,255});
            if(effects)scene.drawEffects(camera);
            EndMode3D();
            if(graded)post.end();
            auto image=LoadImageFromScreen();
            EndDrawing();return image;
        };
        auto off=render(false,false),on=render(true,false);
        check(scene.effects().particleCount()>20 && scene.effects().particleCount()<150,"Expected fire population");
        check(changed(off,on)>200,"Imported flames and textured layers actually render");
        auto repeated=render(true,false);
        check(changed(on,repeated)==0,"Paused particle render is identical");
        auto hiddenOff=render(false,true),hiddenOn=render(true,true);
        check(changed(hiddenOff,hiddenOn)==0,"Opaque geometry fully hides particles");
        for(int i=0;i<45;++i)clock.update(1.f/60,[](Vector3){return 0.f;});
        auto moved=render(true,false);
        check(changed(on,moved)>150,"Fire visibly animates without needing player interaction");
        auto graded=render(true,false,true);
        std::filesystem::create_directories("artifacts");
        ExportImage(graded,"artifacts/fireplace-poc-closeup.png");
        ExportImage(on,"artifacts/fireplace-poc-raw.png");
        for(auto image:{off,on,repeated,hiddenOff,hiddenOn,moved,graded})UnloadImage(image);
        document.instances[0].transform=MatrixMultiply(MatrixScale(1.5f,1.5f,1.5f),MatrixTranslate(4,0,2));
        scene.applyDocument(document);clock.reset(document);scene.applyAnimation(clock);scene.prepareLighting(camera);
        auto light=scene.effects().lights().front();
        check(distance(light.position,{3.805f,.66f,2})<.001f && std::abs(light.range-6)<.001f,
              "Particle attachment and light follow editor translation and scale");
        document.instances.push_back({asset,MatrixTranslate(-3,0,0),"fire-copy"});scene.applyDocument(document);
        check(scene.effects().attachmentCount()==10,"Editor duplication duplicates effects");
        document.instances.erase(document.instances.begin());scene.applyDocument(document);
        check(scene.effects().attachmentCount()==5,"Editor deletion removes effects");
        check(scene.load(TownScene::assetDirectory(HubKind::Frontier)),"Frontier effects load on hub switch");
        check(scene.effects().attachmentCount()==22,"Six Frontier campfires bind once each; cooking pots add no duplicate fire");
        scene.unload();post.unload();CloseWindow();
        std::cout<<"PASS original fire mesh, textured particles, depth occlusion, animation, editor attachment transforms and both hubs\n";
    }catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}
}
