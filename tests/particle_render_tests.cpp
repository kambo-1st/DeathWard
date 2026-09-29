#include "render/TownScene.hpp"
#include "render/PostProcess.hpp"
#include "raymath.h"
#include "combat/Simulation.hpp"
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
        ParticleEffects effects;
        check(effects.load(),"All imported combat textures and meshes load");
        Simulation mission(1866,1,{});
        mission.arena=Arena{};mission.player.position={0,.85f,8};
        Camera3D combatCamera{{9,10,14},{0,1,0},{0,1,0},38,CAMERA_PERSPECTIVE};
        const auto combatRender=[&](bool draw,bool wall){
            effects.prepareMission(mission,combatCamera,{0,1,0});
            BeginDrawing();ClearBackground({43,48,55,255});BeginMode3D(combatCamera);
            DrawPlane({0,0,0},{40,40},{130,103,72,255});
            if(wall)DrawCube({0,3,4},30,15,.4f,{65,74,82,255});
            if(draw)effects.draw(combatCamera);
            EndMode3D();auto result=LoadImageFromScreen();EndDrawing();return result;
        };
        mission.particleEffect(ParticleEffect::Explosion,{0,.2f,0});
        mission.particleBursts.back().age=.18f;
        auto plain=combatRender(false,false),blast=combatRender(true,false);
        check(effects.count("blastfire")>0 && effects.count("blastsmoke")>0 && effects.count("blastrock")>0,
              "Explosion contains fire, smoke and imported debris layers");
        check(changed(plain,blast)>100,"Layered dynamite effect actually renders");
        ExportImage(blast,"artifacts/particle-explosion.png");
        auto blastRepeat=combatRender(true,false);
        check(changed(blast,blastRepeat)==0,"A paused combat effect renders identically");
        auto coverOff=combatRender(false,true),coverOn=combatRender(true,true);
        check(changed(coverOff,coverOn)==0,"Combat particles obey opaque depth");
        mission.particleBursts.clear();
        for(int n=0;n<5;++n) {
            mission.particleEffect(ParticleEffect(int(ParticleEffect::Stone)+n),{float(n-2)*2,1,0},{0,1,0});
            mission.particleBursts.back().age=.14f;
        }
        auto impacts=combatRender(true,false);
        check(effects.count("woodchip")>0 && effects.count("spark")>0 && effects.count("flesh")>0,
              "Wood atlas, sparks and enemy hit puffs render");
        ExportImage(impacts,"artifacts/particle-impacts.png");
        for(auto picture:{plain,blast,blastRepeat,coverOff,coverOn,impacts})UnloadImage(picture);
        mission.particleBursts.clear();effects.prepareMission(mission,combatCamera,{0,1,0});
        check(effects.count("canyondust")==0,"Mine has no canyon weather");
        Simulation canyon(1866,1,{},MissionTheme::Canyon);
        auto canyonCamera=combatCamera;canyonCamera.target=canyon.player.position;
        canyonCamera.position=add(canyon.player.position,{9,10,14});
        effects.prepareMission(canyon,canyonCamera,canyon.player.position);
        check(effects.count("canyondust")>0,"Seeded canyon dust is visible on walkable ground");
        const auto dust=effects.bounds("canyondust");
        effects.prepareMission(canyon,canyonCamera,canyon.player.position);
        check(distance(dust->min,effects.bounds("canyondust")->min)==0,
              "Canyon dust remains identical on redraw");
        TownDocument train;
        train.assets.push_back({"stack","SM_Veh_Train_01_Alt_Smokestack",0,1,0,{{-1,0,-1},{1,6,1}}});
        train.instances.push_back({0,MatrixIdentity(),"engine",{},"locomotive"});
        TownMotionPath rail{"rail",4,3,0,{}};
        for(int x=0;x<100;x+=10)rail.points.push_back({float(x),0,0});
        for(int z=0;z<30;z+=10)rail.points.push_back({100,0,float(z)});
        for(int x=100;x>0;x-=10)rail.points.push_back({float(x),0,30});
        for(int z=30;z>0;z-=10)rail.points.push_back({0,0,float(z)});
        train.paths.push_back(rail);
        train.groups.push_back({"locomotive","rail",0,0});
        effects.bind(train);ObjectAnimationSystem trainClock;trainClock.reset(train);
        for(int n=0;n<180;++n){trainClock.update(Tick,{});effects.animate(trainClock);}
        const auto stack=Vector3Transform({0,5.8f,3.12f},trainClock.poses()[0].transform);
        Camera3D trainCamera{add(stack,{8,6,12}),stack,{0,1,0},38,CAMERA_PERSPECTIVE};
        effects.prepare(trainCamera);
        check(effects.attachmentCount()==1 && effects.count("steam")>5,"One plume per engine stack");
        const auto plume=effects.bounds("steam");
        check(plume && plume->min.y>stack.y && plume->min.x<stack.x-2,
              "Steam rises above the stack and leaves a world-space trail behind the moving engine");
        effects.animate(trainClock);effects.prepare(trainCamera);
        check(distance(plume->min,effects.bounds("steam")->min)==0,"Paused steam history does not move");
        trainClock.reset(train);effects.animate(trainClock);effects.prepare(combatCamera);
        check(effects.bounds("steam")->max.x<1,"Reset removes the previous train trail");
        train.instances.push_back({0,MatrixTranslate(4,0,0),"copy"});effects.bind(train);
        check(effects.attachmentCount()==2,"Editor duplicates carry their own steam emitter");
        effects.unload();
        scene.unload();post.unload();CloseWindow();
        std::cout<<"PASS fire, textured combat/debris, depth, pause, seeded canyon dust, train trails, reset and editor attachments\n";
    }catch(const std::exception&e){std::cerr<<e.what()<<'\n';return 1;}
}
