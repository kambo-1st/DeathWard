#include "world/TownNavigation.hpp"
#include "world/HubWorld.hpp"
#include "raymath.h"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
struct Geometry {
    std::vector<float> vertices;
    void triangle(Vector3 a,Vector3 b,Vector3 c){for(auto p:{a,b,c})for(float v:{p.x,p.y,p.z})vertices.push_back(v);}
    void quad(Vector3 a,Vector3 b,Vector3 c,Vector3 d){triangle(a,b,c);triangle(a,c,d);}
    void floor(float y,float extent){quad({-extent,y,-extent},{extent,y,-extent},{extent,y,extent},{-extent,y,extent});}
    Mesh mesh(){Mesh m{};m.vertexCount=int(vertices.size()/3);m.triangleCount=m.vertexCount/3;m.vertices=vertices.data();return m;}
};
TownNavigation bake(float opening,float ceiling,float rotation=0) {
    Geometry ground,building,door;
    ground.floor(0,10);building.floor(.15f,4);building.floor(ceiling,4);
    building.quad({-4,0,-4},{4,0,-4},{4,3,-4},{-4,3,-4});
    building.quad({-4,0,4},{-4,0,-4},{-4,3,-4},{-4,3,4});
    building.quad({4,0,-4},{4,0,4},{4,3,4},{4,3,-4});
    building.quad({-4,0,4},{-opening,0,4},{-opening,3,4},{-4,3,4});
    building.quad({opening,0,4},{4,0,4},{4,3,4},{opening,3,4});
    building.quad({-opening,2.4f,4},{opening,2.4f,4},{opening,3,4},{-opening,3,4});
    door.quad({-opening,0,4},{opening,0,4},{opening,2.4f,4},{-opening,2.4f,4});
    Mesh meshes[]{ground.mesh(),building.mesh(),door.mesh()};Model model{};model.meshCount=3;model.meshes=meshes;
    TownDocument document;
    document.assets={{"ground","Ground",0,1,0,{{-10,0,-10},{10,0,10}}},
        {"building","SM_Bld_Single_01",1,1,0,{{-4,0,-4},{4,3,4}}},
        {"door","SM_Bld_Single_Door_01",2,1,0,{{-opening,0,3.99f},{opening,2.4f,4.01f}}}};
    const auto transform=MatrixRotateY(rotation);
    document.instances={{0,MatrixIdentity()},{1,transform},{2,transform}};
    TownNavigation nav;nav.width=nav.depth=50;nav.minX=nav.minZ=-10;nav.cell=.4f;
    nav.spawn=Vector3Transform({0,0,7},transform);nav.mission={7,0,0};nav.bake(document,model);return nav;
}
int main(){try {
    auto nav=bake(.65f,3);
    check(nav.bakeVersion==3 && nav.cell==.2f,"Interior bake refines the navigation resolution");
    check(std::abs(nav.height({0,0,0})-.15f)<.001f,"A combined floor/roof mesh keeps the real floor reachable");
    HubWorld hub;hub.setNavigation(nav);
    check(hub.canTraverse({0,0,6},{0,0,0}),"The automatic door admits a standing player");
    check(!hub.canTraverse({6,0,0},{0,0,0}) && !hub.walkable({4,0,0}),"Side walls remain solid");
    hub.player.position={0,.85f,6};
    for(int n=0;n<60;++n)hub.step({0,0,-1},Tick);
    check(hub.player.position.z<1 && std::abs(hub.player.position.y-1)<.01f,"Keyboard movement crosses the threshold and follows the floor");
    check(hub.moveTo({0,0,7}),"Mouse movement can leave the interior");
    for(int n=0;n<90 && hub.destination();++n)hub.step({},Tick);
    check(!hub.destination(),"Mouse movement exits without trapping the player");
    const auto low=bake(.65f,1.8f),narrow=bake(.35f,3);
    check(!std::isfinite(low.height({0,0,0})),"Low ceilings remain impassable");
    check(!std::isfinite(narrow.height({0,0,0})),"Open doors do not erase jamb clearance");
    const auto angled=bake(.65f,3,Pi/4);
    hub.setNavigation(angled);
    check(hub.canTraverse(Vector3Transform({0,0,6},MatrixRotateY(Pi/4)),{0,0,0}),
          "A rotated doorway retains circular player clearance");
    std::cout<<"PASS hollow building meshes, doorway clearance, solid walls, headroom, keyboard entry and mouse exit\n";
}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
