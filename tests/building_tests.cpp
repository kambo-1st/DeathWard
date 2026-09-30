#include "render/TownScene.hpp"
#include "render/PlayerModel.hpp"
#include "render/PostProcess.hpp"
#include "world/HubWorld.hpp"
#include "world/TownBuildings.hpp"
#include "raymath.h"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool condition,const char *message){if(!condition)throw std::runtime_error(message);}
void doors() {
    TownDocument d;
    d.assets={{"leaf","SM_Bld_Test_Door_01",0,1,0,{{0,0,-.05f},{1.2f,2.2f,.05f}}},
              {"glass","SM_Bld_Test_Door_Window_01",1,1,0,{{-.3f,-.3f,0},{.3f,.3f,0}}}};
    d.instances={{0,MatrixTranslate(2,0,1),"front:leaf"},
                 {1,MatrixTranslate(2.6f,1.2f,1),"front:glass"}};
    ObjectAnimationSystem clock;clock.reset(d);
    check(clock.doorCount()==1,"Automatic doors recognize leaves without duplicating their windows");
    for(int n=0;n<50;++n)clock.update(Tick,{},Vector3{2.6f,.85f,2});
    check(clock.openDoorCount()==1,"Approaching a door opens it without a key");
    const auto leaf=clock.poses()[0].transform,glass=clock.poses()[1].transform;
    check(distance(Vector3Transform({.6f,1.2f,0},leaf),Vector3Transform({},glass))<.001f,
          "The glass follows the leaf around its hinge");
    check(distance(Vector3Transform({},glass),{2.6f,1.2f,1})>.5f,"The leaf actually swings");
    clock.update(0,{},Vector3{20,.85f,20});
    check(clock.poses()[0].transform.m0==leaf.m0,"Pause freezes automatic doors");
    for(int n=0;n<80;++n)clock.update(Tick,{},Vector3{20,.85f,20});
    check(clock.openDoorCount()==0 && distance(Vector3Transform({},clock.poses()[1].transform),{2.6f,1.2f,1})<.001f,
          "Retreat restores the authored leaf and window transforms");
    clock.reset(d);check(clock.openDoorCount()==0,"Editor reset closes preview doors");
}
Vector3 nearestInterior(const HubWorld &hub, Vector3 wanted) {
    Vector3 best{};float distanceSquared=2.25f;
    for(float z=wanted.z-1.4f;z<=wanted.z+1.4f;z+=.2f)
        for(float x=wanted.x-1.4f;x<=wanted.x+1.4f;x+=.2f) {
            Vector3 p{x,0,z};const float h=hub.height(p);
            const float d=(x-wanted.x)*(x-wanted.x)+(z-wanted.z)*(z-wanted.z);
            if(std::isfinite(h) && d<distanceSquared){best={x,h,z};distanceSquared=d;}
        }
    check(distanceSquared<2.25f,"Building interior contains reachable floor");return best;
}
void enter(HubWorld &hub, ObjectAnimationSystem &clock, Vector3 destination) {
    check(hub.moveTo(destination),"Mouse path enters through a connected doorway");
    for(int n=0;n<6000 && hub.destination();++n) {
        clock.update(Tick,[&](Vector3 p){return hub.height(p);},hub.player.position);
        const auto before=hub.player.position;hub.step({},Tick);
        check(hub.walkable(hub.player.position) && distance(before,hub.player.position)<.7f,
              "Entering and leaving cannot teleport or cross a collision barrier");
    }
    check(!hub.destination() && distance(hub.player.position,add(destination,{0,.85f,0}))<.1f,
          "Player reaches the actual interior floor");
}
}
int main(){
    try {
        doors();
        SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1100,800,"Building verification");
        TownScene scene;PlayerModel model;PostProcess post;
        for(auto kind:{HubKind::BlackCreek,HubKind::Frontier}) {
            check(scene.load(TownScene::assetDirectory(kind)),"Town model loads");
            HubWorld hub;check(hub.load(TownScene::assetDirectory(kind)/"town.nav"),"Interior navigation loads");
            ObjectAnimationSystem clock;clock.reset(scene.document());
            check(clock.doorCount()>10,"Imported town has automatic building doors");
            const std::vector<Vector3> targets = kind==HubKind::BlackCreek ?
                std::vector<Vector3>{{11,0,-18.3f},{-11,0,-27.3f},{11,0,-26.2f},{-11,0,-39},
                    {11,0,-46},{10.5f,0,-35.5f},{-38,0,10.8f},{-31,0,-11.7f},
                    {-16.6f,0,119.6f},{11,0,-10.5f},{0,0,-66},{-14,0,-12},{2,0,10.6f}} :
                std::vector<Vector3>{{-4,0,-14},{46,0,34},{66,0,-52},{92,0,-43},{87,0,-54}};
            int visited=0;
            for(auto wanted:targets){
                const auto at=nearestInterior(hub,wanted);
                enter(hub,clock,at);
                Camera3D camera{add(hub.player.position,{8,11,8}),hub.player.position,{0,1,0},45,CAMERA_PERSPECTIVE};
                scene.applyAnimation(clock);scene.setPlayerOcclusion(camera,hub.player.position);
                check(scene.interior().has_value(),"Entering activates a building cutaway");
                if((kind==HubKind::BlackCreek && (visited==11 || visited==12)) || (kind==HubKind::Frontier && visited==0)) {
                    model.update(hub.player,hub.time,&hub);
                    scene.prepareLighting(camera,[&](Shader shader){model.draw(hub.player,false,shader);});
                    BeginDrawing();post.begin({154,186,199,255},distance(camera.position,camera.target));
                    BeginMode3D(camera);scene.draw(hub.player.position);
                    model.draw(hub.player,false,scene.actorShader(),scene.shadowTexture());
                    scene.drawEffects(camera);scene.drawOccluders();scene.draw(hub.player.position,true);
                    EndMode3D();post.end();
                    auto picture=LoadImageFromScreen();
                    ExportImage(picture,kind==HubKind::Frontier?"artifacts/building-frontier-cabin.png":visited==12?"artifacts/building-station.png":"artifacts/building-saloon.png");
                    UnloadImage(picture);EndDrawing();
                }
                enter(hub,clock,hub.spawn);scene.setPlayerOcclusion(camera,hub.player.position);
                check(!scene.interior(),"Leaving restores the exterior view");
                ++visited;
            }
            std::cout<<"PASS "<<visited<<" building round trips in "<<hubName(kind)<<" with automatic doors and interior cutaways\n";
        }
        scene.unload();model.unload();post.unload();CloseWindow();
    }catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}
}
