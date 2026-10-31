#pragma once
#include "combat/Simulation.hpp"
#include "rlgl.h"

namespace dw {
inline void drawBonyModel(const Enemy &e,bool drawShadow=true) {
    const float r=e.radius;
    const auto direction=e.behavior.state==0?e.facing:unit(horizontal(sub(e.target,e.position)));
    const auto front=unit(horizontal(direction));const Vector3 side{-front.z,0,front.x};
    auto at=[&](float x,float y,float z){return add(e.position,add(mul(side,x),add(Vector3{0,y,0},mul(front,z))));};
    const bool black=e.monster.type==277;
    const Color bone=e.flash>0?Color{250,238,210,255}:black?Color{76,70,62,255}:Color{210,193,154,255};
    const Color dark=black?Color{24,20,18,255}:Color{55,40,33,255};
    if(drawShadow)DrawCircle3D({e.position.x,e.position.y-.81f,e.position.z},r,{1,0,0},90,{43,34,35,90});
    const float gait=e.behavior.state==0?std::sin(e.animationTime()*10)*.17f:0;
    for(float s:{-1.f,1.f}) {
        DrawCylinderEx(at(s*.17f,-.3f,0),at(s*.2f,-.72f,s*gait),.075f,.06f,5,bone);
        DrawCubeV(at(s*.2f,-.76f,.12f+s*gait),{.16f,.13f,.3f},bone);
    }
    DrawCylinderEx(at(0,-.3f,0),at(0,.38f,0),.085f,.06f,5,bone);
    for(int n=0;n<3;++n)for(float s:{-1.f,1.f}) {
        const float y=-.04f+float(n)*.14f;
        DrawCylinderEx(at(0,y,-.05f),at(s*(.2f+float(n)*.035f),y,.08f),.04f,.04f,5,bone);
        DrawCylinderEx(at(s*(.2f+float(n)*.035f),y,.08f),at(s*.08f,y-.04f,.19f),.04f,.035f,5,bone);
    }
    DrawSphereEx(at(0,.55f,.03f),r*.57f,6,8,bone);
    DrawCubeV(at(0,.3f,.22f),{.32f,.13f,.2f},bone);
    for(float s:{-1.f,1.f})DrawSphereEx(at(s*.13f,.56f,.34f),.1f,4,6,dark);
    DrawSphereEx(at(0,.41f,.34f),.045f,4,5,dark);
    for(float s:{-1.f,1.f}) {
        const bool throwing=s>0&&e.state==EnemyState::Windup;
        const auto elbow=at(s*.4f,throwing?.55f:.04f,throwing?-.12f:.1f);
        const auto hand=at(s*.47f,throwing?.83f:-.16f,throwing?-.27f:.2f);
        DrawCylinderEx(at(s*.24f,.24f,0),elbow,.06f,.055f,5,bone);
        DrawCylinderEx(elbow,hand,.055f,.055f,5,bone);
        if(throwing){DrawCylinderEx(sub(hand,mul(front,.2f)),add(hand,mul(front,.2f)),.07f,.07f,5,bone);
            for(float a:{-1.f,1.f})DrawSphereEx(add(hand,mul(front,a*.22f)),.1f,4,5,bone);}
    }
}
inline void drawPassengerCart(const RailCartRuntime &cart) {
    if(!cart.visible||!cart.intact)return;
    const Color wood{103,77,53,255},iron{62,63,65,255};
    rlPushMatrix();rlTranslatef(cart.position.x,cart.position.y,cart.position.z);
    rlRotatef(std::atan2(cart.direction.x,cart.direction.z)*180/Pi,0,1,0);
    for(float s:{-1.f,1.f})for(float f:{-.6f,.6f})DrawCylinderEx({s*.7f,.35f,f},{s*.95f,.35f,f},.26f,.26f,8,iron);
    DrawCubeV({0,.65f,0},{1.65f,.55f,1.8f},wood);
    for(float s:{-1.f,1.f})DrawCubeV({s*.8f,.78f,0},{.13f,.65f,1.9f},iron);
    rlPopMatrix();
}
inline void drawRockSpiderShell(const Enemy &e,Vector3 center,float radius,bool coal) {
    const float heat=e.environment?std::clamp(e.hp/e.maxHp,0.f,1.f):1;
    const Color stone=e.flash>0?Color{245,229,199,255}:coal?Color{57,46,43,255}:Color{156,140,118,255};
    const int shape=std::max(1,e.monster.subtype);
    rlPushMatrix();rlTranslatef(center.x,center.y,center.z);
    rlRotatef(float(shape)*43,0,1,0);rlScalef(shape==2?1.15f:1,shape==3?.78f:1,shape==1?.82f:1);
    DrawSphereEx({},radius*1.15f,3,5,stone);
    if(shape!=1)DrawSphereEx({radius*.5f,-radius*.05f,radius*.15f},radius*.6f,3,5,ColorBrightness(stone,-.12f));
    const Color crack=coal?Color{static_cast<unsigned char>(120+120*heat),static_cast<unsigned char>(45+75*heat),25,255}:Color{92,80,66,255};
    DrawCylinderEx({-radius*.5f,radius*.98f,-radius*.2f},{radius*.25f,radius*1.16f,radius*.2f},.035f,.025f,4,crack);
    DrawCylinderEx({radius*.25f,radius*1.16f,radius*.2f},{radius*.8f,radius*.32f,radius*.75f},.025f,.015f,4,crack);
    if(coal)for(int n=0;n<2;++n) {
        const float x=(float(n)-.5f)*radius;
        const float height=radius*(2.1f+.3f*std::sin(e.age*12+n));
        DrawCylinderEx({x,radius*.9f,0},{x+.07f,height,.02f},radius*.24f,.005f,4,
            {static_cast<unsigned char>(190+60*heat),static_cast<unsigned char>(80+65*heat),28,255});
        DrawCylinderEx({x,radius*1.05f,-.015f},{x+.05f,height*.85f,.02f},radius*.13f,.005f,4,{255,211,101,255});
    }
    rlPopMatrix();
}
inline void drawEnvironmentActorModel(const Enemy &e,const EnvironmentActorDefinition &rules,bool drawShadow=true) {
    if(e.state==EnemyState::Teleporting)return;
    const bool spent=e.environment&&e.environment->spent;
    const auto p=e.position;const float r=e.radius;
    const float base=e.railCarrier?p.y-r+.55f:p.y-r;
    if(drawShadow)DrawCircle3D({p.x,.035f,p.z},r,{1,0,0},90,{43,34,35,90});
    if(rules.kind==EnvironmentActorKind::HotCoal) {
        drawRockSpiderShell(e,{p.x,p.y-.42f+e.lift,p.z},r,true);
    } else if(rules.kind==EnvironmentActorKind::Fireplace) {
        const Color ash{63,57,51,255},wood=e.flash>0?Color{237,215,175,255}:Color{91,51,30,255};
        for(int n=0;n<5;++n) {
            const auto v=rotateY({r*.7f,0,0},float(n)*2*Pi/5);
            DrawCylinderEx(add({p.x,base+.09f,p.z},v),sub(Vector3{p.x,base+.09f,p.z},v),r*.16f,r*.13f,5,spent?ash:wood);
        }
        if(!spent)for(int n=0;n<3;++n) {
            const auto v=rotateY({r*.25f,0,0},float(n)*2*Pi/3);
            const float flicker=.8f+.12f*std::sin(e.age*13+float(n)*2);
            const auto a=add({p.x,base+.13f,p.z},v);
            DrawCylinderEx(a,add(a,{v.x*.3f,r*flicker*1.8f,v.z*.3f}),r*.36f,.015f,5,{220,103,31,255});
            DrawCylinderEx(a,add(a,{0,r*flicker,0}),r*.23f,.01f,5,{255,207,92,255});
        }
    } else {
        const Color timber=e.flash>0?Color{237,215,175,255}:Color{131,80,48,255},red{159,51,40,255},iron{61,58,53,255};
        if(spent) {
            for(int n=0;n<4;++n)DrawCubeV({p.x+float(n%2)*.5f-.25f,base+.06f,p.z+float(n/2)*.45f-.2f},{.65f,.12f,.18f},timber);
            return;
        }
        rlPushMatrix();rlTranslatef(p.x,base,p.z);
        rlRotatef(std::atan2(e.facing.x,e.facing.z)*180/Pi,0,1,0);
        DrawCubeV({0,.65f,0},{1.25f,1.3f,1.25f},timber);
        for(float s:{-.44f,.44f}) {
            DrawCubeV({s,.65f,0},{.11f,1.36f,1.29f},iron);
            DrawCubeV({0,.65f,s},{1.29f,1.36f,.11f},iron);
        }
        for(float s:{-1.f,1.f}) {
            DrawCubeV({0,.72f,s*.64f},{.7f,.68f,.025f},red);
            // Contrasting diagonal warning slashes remain legible at game zoom.
            DrawCylinderEx({-.23f,.47f,s*.67f},{.23f,.97f,s*.67f},.045f,.045f,4,{235,201,142,255});
            DrawCylinderEx({-.23f,.97f,s*.67f},{.23f,.47f,s*.67f},.045f,.045f,4,{235,201,142,255});
            if(e.hp<3)DrawCylinderEx({-.42f,.28f,s*.66f},{.25f,1.13f,s*.66f},.035f,.025f,4,iron);
        }
        rlPopMatrix();
    }
}
inline void drawHornfelModel(const Enemy &e,bool drawShadow=true) {
    if(e.state==EnemyState::Teleporting)return;
    const bool decoy=e.monster==monsterId(906,1);
    const bool sick=!e.phase&&e.bossAttack==4;
    const Color skin=e.flash>0?Color{245,233,206,255}:sick?Color{161,143,86,255}:decoy?Color{161,128,80,255}:Color{157,94,70,255};
    const Color coat{87,60,50,255},iron{62,63,65,255},wood{103,77,53,255};
    const auto front=unit(horizontal(e.facing));const Vector3 side{-front.z,0,front.x};
    auto at=[&](float x,float y,float z){return add(e.position,add(mul(side,x),add(Vector3{0,y,0},mul(front,z))));};
    auto cartBox=[&](Vector3 center,Vector3 size,Color color) {
        rlPushMatrix();rlTranslatef(center.x,center.y,center.z);
        rlRotatef(std::atan2(front.x,front.z)*180/Pi,0,1,0);
        DrawCubeV({},size,color);rlPopMatrix();
    };
    if(drawShadow)DrawCircle3D({e.position.x,.035f,e.position.z},e.radius,{1,0,0},90,{43,34,35,90});
    if(!e.phase) {
        for(float s:{-1.f,1.f})for(float f:{-.6f,.6f})DrawCylinderEx(at(s*.7f,-.72f,f),at(s*.95f,-.72f,f),.26f,.26f,8,iron);
        cartBox(at(0,-.38f,0),{1.65f,.7f,1.8f},wood);
        for(float s:{-1.f,1.f})cartBox(at(s*.8f,-.23f,0),{.13f,.7f,1.9f},iron);
    } else for(float s:{-1.f,1.f}) {
        const float gait=std::sin(e.age*11+s)*.15f;
        DrawCylinderEx(at(s*.25f,-.1f,0),at(s*.3f,-.7f,gait),.18f,.14f,6,coat);
    }
    DrawSphereEx(at(0,.1f,0),.65f,6,8,coat);
    const float lean=sick?.3f:e.state==EnemyState::Charging?.18f:0;
    DrawSphereEx(at(0,.65f-lean,.08f+lean),.47f,6,8,skin);
    DrawCylinderEx(at(0,.95f-lean,.03f+lean),at(0,1.12f-lean,.03f+lean),.58f,.44f,8,wood);
    DrawSphereEx(at(0,1-lean,.48f+lean),.16f,5,6,{239,202,108,255});
    for(float s:{-1.f,1.f}) {
        DrawSphereEx(at(s*.18f,.7f-lean,.47f+lean),.1f,4,6,{40,31,31,255});
        const float raise=e.state==EnemyState::Windup?.4f:0;
        DrawCylinderEx(at(s*.49f,.35f,0),at(s*.8f,.15f+raise,.38f),.15f,.13f,6,skin);
    }
    if(!decoy&&!e.phase&&e.state==EnemyState::Windup&&!sick&&e.bossAttack!=5)DrawSphereEx(at(.83f,.6f,.4f),.24f,5,8,iron);
    if(sick)DrawSphereEx(at(0,.38f-lean,.52f+lean),.14f,4,6,{58,39,29,255});
}
inline void drawRailEncounter(const Simulation &run) {
    if(!run.arena.rails)return;
    const auto &rail=*run.arena.rails;
    for(const auto &room:run.rooms)if(room.hornfel)
        for(const auto &passenger:room.hornfel->traffic.passengers)drawPassengerCart(passenger.cart);
    std::set<std::array<int,4>> drawn;
    for(const auto &path:rail.paths)for(size_t i=1;i<path.points.size();++i) {
        auto a=path.points[i-1],b=path.points[i];
        std::array<int,2> first{int(std::lround(a.x*1000)),int(std::lround(a.z*1000))},second{int(std::lround(b.x*1000)),int(std::lround(b.z*1000))};
        if(second<first)std::swap(first,second);
        if(!drawn.insert({first[0],first[1],second[0],second[1]}).second)continue;
        const auto direction=unit(sub(b,a));const Vector3 side{-direction.z*.55f,0,direction.x*.55f};
        DrawCylinderEx(add(a,side),add(b,side),.07f,.07f,5,{78,70,60,255});
        DrawCylinderEx(sub(a,side),sub(b,side),.07f,.07f,5,{78,70,60,255});
        const int ties=std::max(1,int(std::ceil(distance(a,b)/.85f)));
        for(int n=0;n<ties;++n) {
            auto c=add(a,mul(sub(b,a),(float(n)+.5f)/ties));c.y-=.07f;
            DrawCylinderEx(sub(c,mul(side,1.4f)),add(c,mul(side,1.4f)),.1f,.1f,4,{100,73,48,255});
        }
    }
    for(const auto &room:run.rooms)if(room.hornfel)for(size_t i=0;i<room.hornfel->doors.size();++i) {
        const auto &door=room.hornfel->doors[i];const auto p=door.position;
        const auto direction=railDirection(rail.doorSides[i]);const Vector3 side{-direction.z,0,direction.x};
        const Color timber{80,59,45,255},dark{29,27,27,255};
        for(float s:{-1.25f,1.25f})DrawCubeV(add(p,add(mul(side,s),{0,1.45f,0})),{.3f,2.9f,.3f},timber);
        DrawCylinderEx(add(p,add(mul(side,-1.4f),{0,2.9f,0})),add(p,add(mul(side,1.4f),{0,2.9f,0})),.2f,.2f,4,timber);
        const float width=1.25f*(1-door.openness);
        for(float s:{-1.f,1.f}) {
            const auto center=add(p,add(mul(side,s*(1.25f-width*.5f)),{0,1.3f,0}));
            DrawCubeV(center,{std::abs(side.x)*width+.12f,2.5f,std::abs(side.z)*width+.12f},dark);
        }
    }
}
inline void drawLokiModel(const Enemy &e,bool drawShadow=true) {
    if(e.state==EnemyState::Teleporting)return;
    const bool split=e.monster.variant==1;const float sign=e.bossHalf?1.f:-1.f,r=e.radius;
    const auto p=e.position;const Color skin=e.flash>0?Color{245,233,206,255}:Color{161,67,60,255};
    const Color flesh{106,38,46,255},horn{220,198,157,255},dark{46,27,33,255};
    if(drawShadow)DrawCircle3D({p.x,.04f,p.z},r,{1,0,0},90,{43,34,35,100});
    if(!split)DrawSphereEx(p,r,8,12,skin);
    else {
        // A real cut half, including a closed flesh-colored plane; no mask or
        // shared full-body silhouette pretending that the second half is absent.
        auto point=[&](int row,int col) {
            const float theta=float(row)*Pi/8,phi=-Pi/2+float(col)*Pi/8;
            return add(p,{sign*r*std::sin(theta)*std::cos(phi),r*std::cos(theta),r*std::sin(theta)*std::sin(phi)});
        };
        auto triangle=[&](Vector3 a,Vector3 b,Vector3 c,Color color) {
            if(sign>0)DrawTriangle3D(a,c,b,color);else DrawTriangle3D(a,b,c,color);
        };
        for(int row=0;row<8;++row)for(int col=0;col<8;++col) {
            const auto a=point(row,col),b=point(row+1,col),c=point(row+1,col+1),d=point(row,col+1);
            triangle(a,b,c,skin);triangle(a,c,d,skin);
        }
        for(int n=0;n<16;++n) {
            auto edge=[&](int i){return add(p,{0,r*std::cos(float(i)*Pi/8),r*std::sin(float(i)*Pi/8)});};
            triangle(p,edge(n),edge(n+1),flesh);
        }
        for(int n=-1;n<=1;++n)DrawSphereEx(add(p,{0,float(n)*r*.43f,0}),r*.19f,4,6,{194,114,98,255});
    }
    for(float side:{-1.f,1.f}) {
        if(split&&side!=sign)continue;
        const auto eye=add(p,{side*r*.37f,r*.22f,r*.82f});
        DrawSphereEx(eye,r*.25f,5,8,horn);
        DrawSphereEx(add(eye,{0,0,r*.16f}),r*.13f,4,6,dark);
        DrawCylinderEx(add(p,{side*r*.6f,r*.62f,0}),add(p,{side*r*.9f,r*1.26f,-r*.1f}),r*.22f,.025f,6,horn);
        DrawCylinderEx(add(p,{side*r*.78f,-r*.15f,0}),add(p,{side*r*1.18f,-r*.55f,r*.18f}),r*.17f,r*.12f,6,skin);
        DrawCubeV(add(p,{side*r*.43f,-r*.87f,r*.2f}),{r*.32f,r*.28f,r*.5f},dark);
    }
    const auto mouth=add(p,{split?sign*r*.25f:0,-r*.37f,r*.85f});
    DrawCubeV(mouth,{r*(split?.4f:.8f),r*.17f,r*.1f},dark);
}
inline void drawBoomFlyModel(const Enemy &e,const BoomFlyDefinition &rules,bool drawShadow=true) {
    const auto p=e.position;const float r=e.radius;
    const auto front=unit(horizontal(e.facing));const Vector3 side{-front.z,0,front.x};
    const std::array<Color,7> palette{{{58,52,55,255},{168,62,63,255},{102,146,148,255},{188,117,62,255},
        {216,200,163,255},{115,139,67,255},{103,73,100,255}}};
    const Color skin=e.flash>0?Color{245,233,206,255}:palette[size_t(rules.kind)],dark{39,29,34,255},bone{228,215,179,255};
    if(drawShadow)DrawCircle3D({p.x,.045f,p.z},r,{1,0,0},90,{43,34,35,100});
    DrawSphereEx(p,r,6,8,skin);
    const float flap=r*.25f*std::sin(e.animationTime()*35);
    for(float sign:{-1.f,1.f}) {
        const auto wing=add(p,add(mul(side,sign*r*1.3f),{0,r*.6f+flap,0}));
        DrawCylinderEx(add(p,{0,r*.45f,0}),wing,r*.13f,r*.3f,5,{181,178,154,255});
        const auto eye=add(p,add(mul(front,r*.82f),add(mul(side,sign*r*.4f),{0,r*.2f,0})));
        if(rules.kind==BoomFlyKind::Dragon) {
            // Actual cross/diagonal pattern is visible on the face, even without color.
            for(float slope:{-1.f,1.f}) {
                const auto delta=rules.diagonal?add(mul(side,r*.19f),{0,slope*r*.19f,0}):
                    slope<0?mul(side,r*.22f):Vector3{0,r*.22f,0};
                DrawCylinderEx(sub(eye,delta),add(eye,delta),r*.055f,r*.055f,5,dark);
            }
        } else {
            DrawSphereEx(eye,r*(rules.kind==BoomFlyKind::Bone?.27f:.2f),4,6,dark);
            if(rules.kind!=BoomFlyKind::Bone)DrawSphereEx(add(eye,mul(front,r*.1f)),r*.075f,4,6,bone);
        }
    }
    if(rules.kind==BoomFlyKind::Dragon) {
        // The fly can face away from the camera. Repeat the actual world-space
        // death pattern on its upper shell so the X/cross is still readable.
        const auto top=add(p,{0,r*.88f,0});
        for(int n=0;n<2;++n) {
            const auto axis=rotateY({1,0,0},float(n)*Pi/2+(rules.diagonal?Pi/4:0));
            DrawCylinderEx(sub(top,mul(axis,r*.52f)),add(top,mul(axis,r*.52f)),r*.08f,r*.08f,5,bone);
        }
    }
    if(rules.kind==BoomFlyKind::Bone) {
        for(int n=-1;n<=1;++n)DrawCubeV(add(p,add(mul(front,r*.85f),add(mul(side,float(n)*r*.23f),{0,-r*.4f,0}))),{r*.18f,r*.27f,r*.18f},bone);
    } else if(rules.kind==BoomFlyKind::Sick) {
        for(int n=0;n<3;++n)DrawSphereEx(add(p,add(mul(side,(float(n)-1)*r*.5f),{0,-r*.55f,0})),r*.28f,5,7,{158,166,69,255});
    } else if(rules.kind==BoomFlyKind::Drowned) {
        for(float sign:{-1.f,1.f})DrawCylinderEx(add(p,mul(side,sign*r*.6f)),add(p,add(mul(side,sign*r*.6f),{0,-r*1.1f,0})),r*.09f,r*.025f,5,skin);
    } else if(rules.kind==BoomFlyKind::Tainted) {
        for(const auto axis:{side,Vector3{0,1,0}}) {
            const auto center=add(p,mul(front,r*.95f));
            DrawCylinderEx(sub(center,mul(axis,r*.35f)),add(center,mul(axis,r*.35f)),r*.07f,r*.07f,5,bone);
        }
    }
}
inline void drawFlyBombModel(const Enemy &e,bool drawShadow=true) {
    const auto p=e.position;const float r=e.radius;
    const auto forward=unit(horizontal(e.facing));const Vector3 side{-forward.z,0,forward.x};
    const bool eternal=e.monster.variant==1;
    const Color skin=e.flash>0?Color{245,233,206,255}:eternal?Color{183,103,149,255}:Color{49,47,52,255};
    if(drawShadow)DrawCircle3D({p.x,.045f,p.z},r,{1,0,0},90,{43,34,35,100});
    DrawSphereEx(p,r,6,8,skin);
    const float flap=.14f*std::sin(e.animationTime()*38);
    for(float sign:{-1.f,1.f}) {
        const auto wing=add(p,add(mul(side,sign*r*1.15f),{0,r*.45f+flap,0}));
        DrawCylinderEx(add(p,{0,r*.3f,0}),wing,r*.12f,r*.22f,5,{204,201,175,255});
        const auto eye=add(p,add(mul(forward,r*.8f),add(mul(side,sign*r*.35f),{0,r*.18f,0})));
        DrawSphereEx(eye,r*.19f,4,6,{235,219,174,255});
        DrawSphereEx(add(eye,mul(forward,r*.12f)),r*.09f,4,6,{35,28,32,255});
    }
    DrawCylinderEx(add(p,{0,r*.85f,0}),add(p,{r*.25f,r*1.4f,0}),r*.08f,r*.05f,5,{190,162,105,255});
    DrawSphereEx(add(p,{r*.25f,r*1.4f,0}),r*.11f,4,6,{244,154,58,255});
    if(eternal) {
        // The lit primitive pass derives normals from triangles. A GL line
        // halo has degenerate derivatives and can contaminate post-processing.
        const auto center=add(p,{0,r*1.7f,0});
        for(int n=0;n<12;++n)DrawCylinderEx(
            add(center,rotateY({r*.6f,0,0},float(n)*2*Pi/12)),
            add(center,rotateY({r*.6f,0,0},float(n+1)*2*Pi/12)),
            r*.025f,r*.025f,4,{239,177,218,255});
    }
}
inline void drawSegmentedBossModel(const Enemy &e,bool drawShadow=true) {
    const auto p=e.position;const float r=e.radius;
    if(e.monster==monsterId(19,3)) {
        const auto forward=unit(horizontal(e.facing));const Vector3 side{-forward.z,0,forward.x};
        const Color bone=e.flash>0?Color{245,233,206,255}:Color{215,199,160,255};
        const Color dark{55,36,39,255},flesh{157,65,73,255};
        if(drawShadow)DrawCircle3D({p.x,.04f,p.z},r,{1,0,0},90,{43,34,35,100});
        DrawSphereEx(p,r*.78f,6,8,e.segmentHead||e.segmentArmor>0?dark:flesh);
        if(e.segmentHead) {
            DrawSphereEx(add(p,{0,r*.3f,0}),r*.9f,6,8,bone);
            for(float sign:{-1.f,1.f}) {
                const auto socket=add(p,add(mul(forward,r*.75f),mul(side,sign*r*.4f)));
                DrawSphereEx(socket,r*.3f,5,7,dark);
                DrawCylinderEx(add(p,mul(side,sign*r*.75f)),add(p,add(mul(side,sign*r*.85f),{0,-r*.55f,0})),r*.2f,r*.1f,5,bone);
            }
            DrawCubeV(add(p,add(mul(forward,r*.7f),{0,-r*.4f,0})),{r*.7f,r*.2f,r*.45f},bone);
        } else if(e.segmentArmor>0) {
            for(int rib=-1;rib<=1;++rib)for(float sign:{-1.f,1.f}) {
                const auto top=add(p,add(mul(forward,float(rib)*r*.5f),{0,r*.8f,0}));
                const auto edge=add(top,add(mul(side,sign*r*.9f),{0,-r*.65f,0}));
                DrawCylinderEx(top,edge,r*.18f,r*.14f,5,bone);
                DrawCylinderEx(edge,add(edge,{0,-r*.55f,0}),r*.14f,r*.08f,5,bone);
            }
        } else {
            for(float sign:{-1.f,1.f})DrawSphereEx(add(p,mul(side,sign*r*.6f)),r*.4f,5,7,{103,43,57,255});
            DrawSphereEx(add(p,mul(forward,r*.7f)),r*.25f,5,7,dark);
        }
        return;
    }
    Color skin=e.segmentArmor>0?Color{141,119,91,255}:Color{155,67,71,255};
    if(e.flash>0)skin={245,233,206,255};
    const auto facing=unit(horizontal(e.facing));const Vector3 side{-facing.z,0,facing.x};
    if(drawShadow)DrawCircle3D({p.x,.04f,p.z},r,{1,0,0},90,{43,34,35,110});
    DrawSphereEx(p,r,6,8,skin);
    if(e.segmentArmor>0) {
        for(int i=-1;i<=1;++i)DrawCubeV(add(p,add(mul(side,float(i)*r*.48f),{0,r*.48f,0})),{r*.48f,r*.75f,r*1.1f},{162,143,113,255});
    } else for(int i:{-1,1})DrawSphereEx(add(p,mul(side,float(i)*r*.7f)),r*.3f,5,7,{101,42,52,255});
    if(e.segmentHead) {
        for(float s:{-1.f,1.f}) {
            const auto eye=add(p,add(mul(facing,r*.7f),add(mul(side,s*r*.35f),{0,r*.25f,0})));
            DrawSphereEx(eye,r*.18f,4,6,{226,213,174,255});
            DrawSphereEx(add(eye,mul(facing,r*.12f)),r*.09f,4,6,{38,29,32,255});
        }
        DrawSphereEx(add(p,mul(facing,r*.85f)),r*.28f,5,7,{40,28,32,255});
    }
}
inline void drawPeepModel(const Enemy &e,bool drawShadow=true) {
    const auto p=e.position;const float r=e.radius;
    const bool bloat=e.monster==monsterId(68,1);
    Color skin=e.bossForm==BossForm::Green?Color{100,135,72,255}:bloat?Color{146,80,79,255}:e.bossForm==BossForm::Cyan?Color{119,161,158,255}:
        e.bossForm==BossForm::Yellow?Color{201,167,70,255}:Color{183,147,108,255};
    if(e.flash>0)skin={245,233,206,255};
    const Color dark{53,35,37,255},bone{227,211,169,255};
    const auto forward=unit(horizontal(e.facing));const Vector3 side{-forward.z,0,forward.x};
    auto sphere=[](Vector3 at,float radius,Color c){DrawSphereEx(at,radius,8,12,c);};
    if(drawShadow)DrawCircle3D({p.x,.04f,p.z},r*1.05f,{1,0,0},90,{43,34,35,110});
    sphere(p,r,skin);sphere(add(p,{0,r*.35f,0}),r*.82f,skin);
    for(int slot=0;slot<2;++slot) {
        const float sign=slot?1.f:-1.f;
        const auto socket=add(p,add(mul(forward,r*(bloat?.8f:.7f)),add(mul(side,sign*r*.45f),{0,bloat?0:r*.24f,0})));
        sphere(socket,r*.35f,dark);
        if(!(e.bossParts&(1u<<slot))) {
            const auto eye=add(socket,mul(forward,r*.1f));sphere(eye,r*.3f,bone);
            sphere(add(eye,mul(forward,r*.23f)),r*.12f,dark);
        }
        sphere(add(p,add(mul(side,sign*r*.8f),{0,-r*.65f,0})),r*.3f,skin);
    }
    sphere(add(p,add(mul(forward,r*.86f),{0,-r*.3f,0})),r*.24f,dark);
    if(bloat) {
        // Open belly and inflamed sockets distinguish the variant without a map filter.
        sphere(add(p,add(mul(forward,r*.9f),{0,-r*.52f,0})),r*.35f,dark);
        for(int n:{-1,1})sphere(add(p,add(mul(side,float(n)*r*.55f),add(mul(forward,r*.85f),{0,r*.12f,0}))),r*.16f,{169,46,51,255});
    }
}
inline void drawMonsterModel(const Enemy &e, const MonsterDefinition &d, bool drawShadow = true, const ChargeDefinition *charge=nullptr) {
    const int type = e.monster.type, variant = e.monster.variant;
    const std::array<Color, 8> palette{{{177, 92, 85, 255},
                                        {127, 57, 56, 255},
                                        {114, 140, 127, 255},
                                        {183, 140, 91, 255},
                                        {124, 111, 152, 255},
                                        {115, 138, 68, 255},
                                        {195, 109, 53, 255},
                                        {107, 63, 94, 255}}};
    Color skin = e.flash > 0 ? Color{245, 233, 206, 255} : palette[size_t((type + variant) % 8)];
    if(e.leaper&&e.flash<=0)skin=variant==1?Color{62,53,61,255}:Color{180,105,93,255};
    if(e.mirror&&e.flash<=0)skin=variant==1?Color{66,57,66,255}:Color{177,82,76,255};
    if(type==827&&e.flash<=0)skin=variant==1?Color{76,60,68,255}:Color{178,124,105,255};
    if(type==10&&variant<=2&&e.flash<=0)skin=variant==2?Color{93,69,57,255}:Color{178,124,105,255};
    if(type==11&&e.flash<=0)skin=variant==0?Color{178,124,105,255}:Color{145,122,111,255};
    if(type>=278&&type<=280&&e.flash<=0)skin={62,54,61,255};
    if(e.willo&&e.flash<=0) {
        const bool warning=e.willo->warning;
        skin=warning&&(e.willo->attackFrame/2)%2==0?Color{255,240,136,255}:Color{180,198,111,255};
    }
    if(type==222&&e.flash<=0)skin={184,105,142,255};
    if(e.flash<=0&&(type==238||(type==87&&variant==0)))skin={112,145,72,255};
    if(e.flash<=0&&type==87&&variant==1)skin={178,91,45,255};
    if(e.flash<=0&&(type==30||type==88)) {
        const std::array<Color,3> boilSkin{{{157,68,70,255},{121,148,68,255},{190,174,132,255}}};
        skin=boilSkin[size_t(std::clamp(variant,0,2))];
    }
    if(type==15&&e.flash<=0) {
        const std::array<Color,4> clotSkin{{{153,76,78,255},{61,52,60,255},
            {190,159,142,255},{83,57,45,255}}};
        skin=clotSkin[size_t(std::clamp(variant,0,3))];
    }
    if(type==872&&e.flash<=0)skin={139,105,69,255};
    if(e.flash<=0&&(type==23||type==855)) {
        if(type==855)skin={129,146,88,255};
        else if(variant==1)skin={105,157,159,255};
        else if(variant==2)skin={49,45,59,255};
        else if(variant==3)skin={194,178,143,255};
        else skin={181,126,115,255};
    }
    if(e.friendly&&e.flash<=0)skin={39,37,48,255};
    const int rotten = type==10 && variant==3 ? std::clamp(e.monster.subtype,1,5) : 0;
    if(type==205&&e.flash<=0)skin={187,176,145,255};
    if(e.headless&&e.headless->scarred&&e.flash<=0)skin={139,132,140,255};
    if(rotten && e.flash<=0) {
        // Original procedural bodies, with stable subtype cues: no render filter.
        const std::array<Color,5> rottenSkin{{{132,148,104,255},{113,117,147,255},
            {163,137,92,255},{114,142,135,255},{150,100,108,255}}};
        skin=rottenSkin[size_t(rotten-1)];
    }
    const float time = e.animationTime();
    if(e.flash<=0&&e.affectedBy(EnemyStatus::Fear))skin=ColorLerp(skin,{147,176,188,255},.4f);
    if(e.flash<=0&&e.affectedBy(EnemyStatus::Confusion))skin=ColorLerp(skin,{186,142,201,255},.35f);
    const bool charmed=e.affectedBy(EnemyStatus::Charm);
    if(e.flash<=0&&charmed)skin=ColorLerp(skin,{232,118,161,255},.6f);
    const bool slowed=e.affectedBy(EnemyStatus::Slow);
    if(e.flash<=0&&slowed)skin=ColorLerp(skin,{177,154,93,255},.55f);
    const bool poisoned=e.affectedBy(EnemyStatus::Poison),burning=e.affectedBy(EnemyStatus::Burn);
    if(e.flash<=0&&poisoned)skin=ColorLerp(skin,{118,177,76,255},.6f);
    if(e.flash<=0&&burning)skin=ColorLerp(skin,{218,103,48,255},.55f);
    const bool frozen=e.affectedBy(EnemyStatus::Freeze);
    if(e.flash<=0&&frozen)skin=ColorLerp(skin,{133,204,235,255},.65f);
    if (type == 884 && std::fmod(time, .7f) < .16f)
        skin = {240, 206, 65, 255};
    const Color dark{41, 31, 35, 255}, bone=frozen?Color{155,208,227,255}:burning?Color{218,103,48,255}:poisoned?Color{118,177,76,255}:slowed?Color{177,154,93,255}:Color{210,193,154,255}, blood{153, 42, 49, 255};
    auto dir = unit(e.facing);
    if(type==205&&e.evader&&e.evader->attackFrame>=0)dir=unit(horizontal(sub(e.target,e.position)));
    if(e.hopRings&&e.targetHop&&e.targetHop->airborne) {
        // Original procedural body follows the alternating Hop/Hop2 twist.
        const float progress=e.targetHop->arc;
        dir=rotateY(dir,(e.hopRings->animationStage%2?-1.f:1.f)*2*Pi*progress);
    }
    const Vector3 side{-dir.z,0,dir.x};
    auto p = e.position;
    p.y += e.lift;
    const float base=e.position.y-.85f;
    const float r = e.statuses&&e.statuses->unshrunkRadius>0?e.statuses->unshrunkRadius:e.radius;
    // Small distinct cues remain legible above the low-poly body, including
    // Horf's bone-colored skull; neither cue changes collision or targeting.
    if(e.affectedBy(EnemyStatus::Fear))for(float side:{-1.f,1.f}) {
        const Vector3 a{p.x+side*r*.8f,p.y+r*2.3f,p.z};
        DrawCylinderEx(a,add(a,{side*.12f,-.32f,0}),.08f,.035f,4,{125,205,229,255});
    }
    if(e.affectedBy(EnemyStatus::Confusion))for(int n=0;n<3;++n) {
        const auto offset=rotateY({r*.8f,0,0},time*3+float(n)*2*Pi/3);
        DrawSphereEx(add(p,add(offset,{0,r*2.3f,0})),.12f,3,4,{216,153,231,255});
    }
    if(charmed) {
        const auto center=add(p,{0,r*2.7f,0});const Color pink{250,126,180,255};
        // Two lobes and a tapered point distinguish Charm from Confusion dots.
        DrawSphereEx(add(center,mul(side,-.12f)),.15f,4,6,pink);
        DrawSphereEx(add(center,mul(side,.12f)),.15f,4,6,pink);
        DrawCylinderEx(add(center,{0,-.28f,0}),center,0,.23f,4,pink);
    }
    if(frozen) {
        // A still six-spoke frost mark is distinct from Fear's two strokes;
        // no opaque ice block hides the enemy silhouette or attack pose.
        const auto center=add(p,{0,r*2.3f,0});
        for(int n=0;n<3;++n) {
            const Vector3 spoke=add(mul(side,std::cos(float(n)*Pi/3)*.3f),{0,std::sin(float(n)*Pi/3)*.3f,0});
            DrawCylinderEx(sub(center,spoke),add(center,spoke),.04f,.04f,4,{180,234,249,255});
        }
    }
    if(slowed&&!frozen) {
        const auto center=add(p,{0,r*2.3f,0});
        const auto left=mul(side,.24f),up=Vector3{0,.24f,0};
        const Color ochre{239,191,83,255};
        for(float sign:{-1.f,1.f}) {
            DrawCylinderEx(sub(add(center,mul(up,sign)),left),add(add(center,mul(up,sign)),left),.04f,.04f,4,ochre);
            DrawCylinderEx(sub(add(center,up),mul(left,sign)),add(sub(center,up),mul(left,sign)),.04f,.04f,4,ochre);
        }
    }
    // Damage statuses keep ticking through Freeze. Their small side cues
    // use real actor age, leaving the held pose and central frost glyph clear.
    if(poisoned)for(int n=0;n<2;++n) {
        const float rise=std::fmod(e.age*1.4f+float(n)*.5f,1.f);
        const auto offset=mul(side,(n?1.f:-1.f)*r*1.35f);
        DrawSphereEx(add(p,add(offset,{0,r*(.9f+rise),0})),.13f,3,4,{153,220,83,255});
    }
    if(burning)for(float sign:{-1.f,1.f}) {
        const auto at=add(p,add(mul(side,sign*r*1.35f),{0,r*.8f,0}));
        const float height=.5f+.1f*std::sin(e.age*15+sign);
        DrawCylinderEx(at,add(at,{0,height,0}),.16f,0,4,{234,113,37,255});
        DrawCylinderEx(at,add(at,{0,height*.7f,0}),.1f,0,4,{255,209,92,255});
    }
    if(e.adultLeech&&e.adultLeech->visibility<=.01f)return;
    if(e.lump&&e.lump->visibility<=.01f)return;
    if (drawShadow)
        DrawCircle3D({p.x, (e.hop.active?0.f:base)+.04f, p.z}, r, {1, 0, 0}, 90, {43, 34, 35, 110});
    if(e.adultLeech) {
        const auto &adult=*e.adultLeech;
        const Color flesh=e.flash>0?Color{245,233,206,255}:Color{131,92,81,255};
        const float phase=(adult.walkPhase+e.idleTime*.5f)*2*Pi;
        const bool charging=adult.phase==AdultLeechPhase::Charge;
        const float height=adult.visibility;
        rlPushMatrix();rlTranslatef(p.x,base,p.z);rlScalef(1,height,1);
        for(int n=0;n<5;++n) {
            const float offset=float(n)-2;
            auto at=mul(dir,offset*r*.3f);
            at.y=p.y-base+std::sin(phase+float(n))*(charging?.025f:.055f);
            DrawSphereEx(at,r*(.64f-std::abs(offset)*.09f),6,8,n%2?ColorBrightness(flesh,-.13f):flesh);
        }
        auto mouth=add(mul(dir,r*.78f),{0,p.y-base,0});
        DrawSphereEx(mouth,r*(charging?.39f:.3f),6,8,dark);
        for(int tooth=0;tooth<6;++tooth) {
            const float a=float(tooth)*Pi/3;
            const auto edge=add(mouth,add(mul(side,std::cos(a)*r*.25f),{0,std::sin(a)*r*.25f,0}));
            DrawSphereEx(add(edge,mul(dir,r*.17f)),r*.075f,4,5,bone);
        }
        rlPopMatrix();return;
    }
    if(e.lump) {
        const auto &lump=*e.lump;
        const Color flesh=e.flash>0?Color{245,233,206,255}:Color{164,96,102,255};
        const float height=lump.visibility;
        rlPushMatrix();rlTranslatef(p.x,base,p.z);rlScalef(1,height,1);
        DrawSphereEx({0,r*.45f,0},r*.85f,6,8,flesh);
        for(float sign:{-1.f,1.f}) {
            DrawSphereEx(mul(side,sign*r*.55f),r*.37f,5,7,flesh);
            DrawSphereEx(add(mul(dir,r*.68f),add(mul(side,sign*r*.26f),{0,r*.66f,0})),r*.12f,4,6,dark);
        }
        const bool spit=lump.phase==LumpPhase::Spitting;
        DrawSphereEx(add(mul(dir,r*.8f),{0,r*.35f,0}),r*(spit?.29f:.13f),5,7,dark);
        rlPopMatrix();return;
    }

    if(e.baby) {
        const auto &baby=*e.baby;
        const bool angel=variant==1,wrinkly=variant==3;
        const Color flesh=e.flash>0?Color{245,233,206,255}:angel?Color{213,199,166,255}:
            wrinkly?Color{135,109,117,255}:Color{188,133,125,255};
        if(baby.phase==BabyPhase::Vanishing||baby.phase==BabyPhase::Appearing)
            DrawCircle3D({p.x,base+.08f,p.z},r*(1.2f-baby.visibility*.4f),{1,0,0},90,flesh);
        if(baby.visibility<=.01f)return;
        const float size=r*baby.visibility;
        p.y+=.15f+std::sin(baby.walkPhase*2*Pi)*.06f;
        auto orb=[&](Vector3 at,float radius,Color color){DrawSphereEx(at,radius,6,8,color);};
        orb(add(p,{0,-size*.35f,0}),size*.72f,flesh);
        orb(add(p,{0,size*.35f,0}),size*.84f,flesh);
        for(float sign:{-1.f,1.f}) {
            orb(add(p,add(mul(dir,size*.72f),add(mul(side,sign*size*.31f),{0,size*.42f,0}))),size*.16f,dark);
            orb(add(p,add(mul(side,sign*size*.65f),{0,-size*.42f,0})),size*.22f,flesh);
            if(angel) {
                const auto wing=add(p,add(mul(side,sign*size*1.2f),{0,size*(.2f+.17f*std::sin(time*11)),0}));
                DrawCylinderEx(add(p,mul(side,sign*size*.55f)),wing,size*.3f,size*.08f,5,bone);
                for(int feather=0;feather<3;++feather)
                    orb(add(wing,add(mul(dir,-size*.2f*float(feather)),{0,-size*.14f*float(feather),0})),size*.26f,bone);
            }
        }
        const bool attack=baby.attackFrame>=0;
        orb(add(p,add(mul(dir,size*.79f),{0,-size*.02f,0})),size*(attack?.28f:.14f),dark);
        if(wrinkly) {
            for(int crease=0;crease<3;++crease) {
                const auto brow=add(p,add(mul(dir,size*.72f),{0,size*(.64f+.13f*float(crease)),0}));
                DrawCylinderEx(add(brow,mul(side,-size*.45f)),add(brow,mul(side,size*.45f)),size*.035f,size*.035f,4,dark);
            }
            if(baby.phase==BabyPhase::DashStart)
                DrawCircle3D({p.x,base+.09f,p.z},r*1.35f,{1,0,0},90,{204,135,93,255});
        }
        return;
    }
    if (e.state == EnemyState::Buried || e.state == EnemyState::Teleporting) {
        DrawCircle3D({p.x, .08f, p.z}, r * .8f, {1, 0, 0}, 90, skin);
        return;
    }
    if (e.state == EnemyState::Collapsed) {
        DrawCylinder({p.x, .05f, p.z}, r, r * 1.2f, .2f, 9, skin);
        DrawSphereEx({p.x, .3f, p.z}, r * .32f, 5, 7, blood);
        return;
    }
    auto sphere = [&](Vector3 at, float radius, Color c) { DrawSphereEx(at, radius, 7, 10, c); };
    if(e.returningBody) {
        // Original canyon palette, with a long segmented silhouette distinct
        // from the walking parent. This is our geometry, not imported artwork.
        const Color hide{171,128,95,255},ridge{114,76,64,255};
        for(int n=3;n>=0;--n) {
            auto at=add(p,mul(dir,r*(.45f-float(n)*.43f)));
            at.y=base+r*(.38f+.035f*std::sin(time*15+float(n)));
            sphere(at,r*(.51f-float(n)*.065f),n%2?ridge:hide);
        }
        const auto mouth=add(p,add(mul(dir,r*.82f),{0,-.28f,0}));
        sphere(mouth,r*.35f,dark);
        for(float sign:{-1.f,1.f}) {
            const auto tooth=add(mouth,mul(side,sign*r*.23f));
            DrawCylinderEx(tooth,add(tooth,add(mul(dir,r*.24f),{0,-r*.2f,0})),r*.11f,0,5,bone);
        }
        return;
    }
    if(e.linkedHead) {
        const Color flesh=e.flash>0?Color{245,233,206,255}:
            variant>=2?Color{163,67,67,255}:Color{186,139,120,255};
        if(d.flying) {
            for(int n=0;n<e.linkedHead->neckCount;++n)
                sphere(e.linkedHead->neckPoints[size_t(n)],e.linkedHead->neckRadius,{148,81,72,255});
            sphere(p,r,flesh);
            for(float sign:{-1.f,1.f})sphere(add(p,add(mul(dir,r*.84f),mul(side,sign*r*.31f))),r*.18f,dark);
            sphere(add(p,add(mul(dir,r*.86f),{0,-r*.35f,0})),r*.26f,dark);
        } else {
            sphere(add(p,{0,-r*.2f,0}),r*.72f,flesh);
            for(float sign:{-1.f,1.f}) {
                const float step=std::sin(e.linkedHead->walkPhase*2*Pi+sign*Pi/2)*.16f;
                auto ankle=add(p,add(mul(side,sign*r*.35f),mul(dir,step)));ankle.y=base+.2f;
                DrawCylinderEx(add(p,mul(side,sign*r*.35f)),ankle,r*.18f,r*.12f,5,flesh);
                sphere(add(p,add(mul(side,sign*r*.8f),{0,-r*.2f,0})),r*.23f,flesh);
            }
            sphere(add(p,{0,r*.25f,0}),r*.27f,blood);
        }
        return;
    }
    auto eyes = [&](Vector3 at, float scale = 1) {
        for (float sign : {-1.f, 1.f}) {
            auto eye = add(add(at, mul(dir, r * .77f)), mul(side, sign * r * .33f));
            sphere(eye, r * .2f * scale, bone);
            sphere(add(eye, mul(dir, r * .14f)), r * .11f * scale, dark);
        }
    };
    const float bob = std::sin(time * 6 + float(e.id)) * .08f;
    switch (d.shape) {
    case MonsterShape::Fly: {
        p.y += .25f + bob;
        sphere(p, r, type==96?Color{225,218,193,255}:skin);
        sphere(add(p, mul(dir, r * .65f)), r * .55f, dark);
        for (float sign : {-1.f, 1.f}) {
            const auto wing =
                add(p, add(mul(side, sign * r * .85f), {0, .25f + std::sin(time * 45) * .15f, 0}));
            DrawSphereEx(wing, r * .63f, 4, 6, {191, 199, 184, 190});
        }
        eyes(add(p, mul(dir, r * .4f)));
        if (type == 80)
            sphere(add(p, mul(dir, -r * .8f)), r * .65f, skin);
        if (type == 25)
            DrawCylinder({p.x, p.y + r * .7f, p.z}, .09f, .09f, .35f, 5, bone);
        if (type == 96)
            DrawCircle3D(add(p, {0, r + .2f, 0}), r * .7f, {1, 0, 0}, 90, bone);
        break;
    }
    case MonsterShape::Worm: {
        if(e.leech) {
            const Color flesh=e.flash>0?skin:variant==2?Color{220,211,175,255}:
                variant==1?Color{84,65,73,255}:Color{155,82,77,255};
            const bool dash=e.leech->charging;
            const float phase=float(e.leech->walkFrame)*2*Pi/float(dash?6:8);
            for(int n=0;n<4;++n) {
                const float offset=float(n)-1.5f;
                auto at=add(p,mul(dir,offset*r*.38f));
                at.y+=std::sin(phase+float(n))*(dash?.02f:.05f);
                sphere(at,r*(.52f-std::abs(offset)*.08f),n%2?ColorBrightness(flesh,-.13f):flesh);
            }
            const auto mouth=add(p,mul(dir,r*.76f));sphere(mouth,r*(dash?.3f:.22f),dark);
            if(variant>0) {
                const auto eye=add(mouth,mul(dir,r*.14f));sphere(eye,r*.16f,bone);
                sphere(add(eye,mul(dir,r*.13f)),r*.075f,variant==2?Color{168,132,65,255}:Color{194,74,64,255});
            }
            break;
        }
        if(e.smallMaggot) {
            const Color flesh=e.flash>0?skin:Color{188,174,127,255};
            p.y=base+r*.55f;
            const float phase=float(e.smallMaggot->walkFrame)*2*Pi/13;
            const float gait=std::min(.035f,length(e.velocity)*.006f);
            for(int n=0;n<4;++n) {
                auto at=add(p,mul(dir,(float(n)-1.5f)*r*.34f));
                at.y+=gait*std::sin(phase+float(n)*Pi/2);
                sphere(at,r*(n==0?.35f:n==3?.43f:.52f),n%2?ColorBrightness(flesh,-.13f):flesh);
            }
            sphere(add(p,mul(dir,r*.69f)),r*.15f,dark);
            break;
        }
        if(e.cardinalWalker) {
            // Blind, low, segmented body. Keep the entire silhouette inside
            // the collision radius instead of extending an unhittable tail.
            const Color flesh=e.flash>0?skin:Color{190,167,127,255};
            p.y=base+r*.6f;
            const float phase=float(e.cardinalWalker->walkFrame)*Pi/6;
            const float gait=std::min(.04f,length(e.velocity)*.004f);
            for(int n=0;n<4;++n) {
                const float offset=float(n)-1.5f;
                auto at=add(p,mul(dir,offset*r*.36f));
                at.y+=gait*std::sin(phase+float(n)*Pi/2);
                sphere(at,r*(.5f-std::abs(offset)*.07f),n%2?ColorBrightness(flesh,-.12f):flesh);
            }
            break;
        }
        if(e.spitty) {
            const bool conjoined=type==243,tainted=type==31&&variant==1;
            const Color flesh=e.flash>0?skin:tainted?Color{115,59,78,255}:Color{174,111,97,255};
            p.y=base+r*.67f;
            const float gait=std::sin(time*10)*std::min(.055f,length(e.velocity)*.006f);
            for(int n=-1;n<=1;++n) {
                auto at=add(p,mul(dir,float(n)*r*.37f));at.y+=gait*float(n);
                sphere(at,r*(n==0?.8f:.6f),n==0?ColorBrightness(flesh,-.12f):flesh);
            }
            for(int end=0;end<(conjoined?2:1);++end) {
                const float sign=end?-1.f:1.f;
                const auto face=add(p,mul(dir,sign*r*.78f));
                const float mouth=r*(e.state==EnemyState::Windup?.23f:.15f);
                sphere(add(face,{0,-r*.13f,0}),mouth,dark);
                for(float s:{-1.f,1.f}) {
                    const auto eye=add(face,add(mul(side,s*r*.25f),{0,r*.28f,0}));
                    sphere(eye,r*.13f,bone);sphere(add(eye,mul(dir,sign*r*.1f)),r*.07f,dark);
                }
            }
            if(tainted)for(int n=-1;n<=1;++n) {
                const auto sore=add(p,add(mul(dir,float(n)*r*.5f),{0,r*.65f,0}));
                sphere(sore,r*.22f,{167,70,74,255});sphere(add(sore,{0,r*.11f,0}),r*.1f,bone);
            }
            break;
        }
        if(charge&&charge->tailRadius>0) {
            sphere(add(p,mul(dir,r*.25f)),r*.7f,bone);
            sphere(add(p,mul(dir,-r*.15f)),r*.55f,ColorBrightness(bone,-.2f));
            sphere(add(p,mul(dir,-r*charge->tailOffset)),r*charge->tailRadius,{228,108,151,255});
            eyes(add(p,mul(dir,r*.25f)));
            break;
        }
        p.y = charge?e.position.y:base + .42f + e.lift;
        for (int n = 3; n >= 0; --n) {
            auto at = add(p, mul(dir, -float(n) * r * .47f));
            at.y += std::sin(time * 8 + float(n)) * .05f;
            sphere(at, r * (1 - float(n) * .15f), n % 2 ? ColorBrightness(skin, -.15f) : skin);
        }
        eyes(p);
        if(type==855) {
            for(int n=0;n<3;++n)sphere(add(p,add(mul(dir,-float(n)*r*.47f),{0,r*.7f,0})),r*.23f,bone);
        }
        break;
    }
    case MonsterShape::Spider: {
        const bool longLegs=type==206||type==207;
        const float legsHeight=longLegs?(variant==1?.45f:.75f):type==814?e.lift:0;
        p.y = base + .45f + e.lift+(longLegs?legsHeight:0);
        if(type==94) {
            const auto abdomen=add(p,mul(dir,-r*1.15f));
            sphere(abdomen,r*1.25f,e.flash>0?skin:Color{39,33,43,255});
        }
        const bool eggy=bool(e.eggy);
        if(e.dyingEggy())p.y=base+.22f;
        const float bodyRadius=type==884||(longLegs&&variant==1)?r*.65f:e.dyingEggy()?r*.8f:r;
        const Color spiderSkin=e.swarmSpider&&e.swarmSpider->airborne?Color{235,211,68,255}:
            eggy?Color{218,207,164,255}:type==814?Color{99,135,146,255}:type==206?Color{195,180,151,255}:type==207?Color{74,48,57,255}:skin;
        if(e.rockSpider) {
            drawRockSpiderShell(e,p,bodyRadius,variant==2);
            if(e.rockSpider->phase==RockSpiderPhase::Rock)break;
        } else sphere(p, bodyRadius, e.flash>0?skin:spiderSkin);
        if(eggy)for(int n=0;n<3;++n) {
            auto mark=add(p,add(mul(dir,(float(n)-1)*bodyRadius*.55f),{0,bodyRadius*.8f,0}));
            sphere(mark,bodyRadius*(e.dyingEggy()?.18f:.09f),Color{95,78,54,255});
        }
        for (float sign : {-1.f, 1.f})
            for (int n = 0; n < 4; ++n) {
                const auto joint =
                    add(p, add(mul(side, sign * r * 1.3f), mul(dir, (float(n) - 1.5f) * r * .55f)));
                const auto toe =
                    add(joint, {side.x * sign * r * .5f, -.3f - legsHeight + std::sin(time * (longLegs&&variant==1?6:12) + float(n)) *
                        (longLegs?std::min(.1f,length(e.velocity)*.02f):e.strider?(e.strider->frame>=0?.12f:0):
                         e.spider||e.rockSpider||e.swarmSpider||eggy?std::min(.08f,length(e.velocity)*.006f):.08f),
                                side.z * sign * r * .5f});
                DrawCylinderEx(p, joint, .055f, .04f, 5, dark);
                DrawCylinderEx(joint, toe, .04f, .02f, 5, dark);
            }
        eyes(p);
        break;
    }
    case MonsterShape::Eye:
        p.y += bob;
        sphere(p, r, bone);
        sphere(add(p, mul(dir, r * .77f)), r * .48f, variant ? blood : skin);
        if(!e.statueDisabled)sphere(add(p, mul(dir, r * .98f)), r * .2f, dark);
        else DrawCylinderEx(add(p,add(mul(dir,r*.98f),mul(side,-r*.4f))),add(p,add(mul(dir,r*.98f),mul(side,r*.4f))),.035f,.035f,5,dark);
        break;
    case MonsterShape::Stone: {
        if(e.danny) {
            const bool coal=variant==1;
            const bool attacking=e.danny->frame>=0;
            const float walk=std::sin(e.age*9)*std::min(.13f,length(e.velocity)*.012f);
            const Color body=coal?Color{59,47,46,255}:Color{121,108,89,255};
            const auto center=add(e.position,{0,-.22f,0});
            for(float sign:{-1.f,1.f}) {
                auto foot=add(center,add(mul(side,sign*r*.55f),mul(dir,sign*walk)));foot.y=.17f;
                DrawCube(foot,r*.52f,.32f,r*.72f,body);
            }
            drawRockSpiderShell(e,center,r*1.12f,coal);
            const auto head=add(center,{0,r*.95f+(attacking?.06f:walk*.15f),0});
            drawRockSpiderShell(e,head,r*.82f,coal);eyes(head);
            auto mouth=add(head,add(mul(dir,r*.79f),{0,-r*.3f,0}));
            sphere(mouth,r*(attacking?.4f:.15f),coal&&attacking?Color{226,101,25,255}:dark);
            if(coal)for(int n=0;n<3;++n) {
                auto glow=add(head,{float(n-1)*r*.4f,r*.65f+.08f*std::sin(e.age*7+n),0});
                DrawCylinderEx(glow,add(glow,{0,.2f,0}),.07f,0,4,Color{235,121,26,255});
            }
            break;
        }
        if(e.hardy) {
            const int layers=3-std::min(2,e.hardy->impacts);
            const float squash=e.hardy->phase==1?1-.18f*std::sin(float(e.hardy->frame)*Pi/36):1;
            for(int layer=0;layer<layers;++layer) {
                const float size=r*(1-.16f*float(layer));
                const auto center=add(e.position,{0,-.55f+float(layer)*r*.65f*squash,0});
                drawRockSpiderShell(e,center,size,false);
            }
            const auto face=add(e.position,add(mul(dir,r*.8f),{0,r*.3f*float(layers)-.35f,0}));
            eyes(face);
            if(e.hardy->phase==2)for(int n=0;n<3;++n) {
                auto dust=add(e.position,mul(dir,-r*(1.1f+float(n)*.4f)));dust.y=.09f;
                sphere(dust,.09f+float(n)*.025f,Color{167,143,105,150});
            }
            break;
        }
        const bool maw=type==235||type==236;
        const bool open=!e.statueDisabled&&(!maw||e.statuePullActive);
        p.y = base + r + e.lift;
        DrawCube(p, r * 1.7f, r * 2, r * 1.7f, type==42&&variant==1?Color{106,126,84,255}:Color{111,112,100,255});
        if(open) {
            eyes(p);
            for(int n=0;n<(type==42&&variant==2?3:1);++n) {
                const auto mouth=add(p,add(add(mul(dir,r*.9f),{0,-r*.35f,0}),mul(side,(float(n)-(type==42&&variant==2?1.f:0.f))*r*.4f)));
                sphere(mouth,r*(maw?.48f:type==42&&variant==2?.15f:.28f),type==203?blood:dark);
            }
            if(maw)for(int n=0;n<4;++n) {
                const float phase=std::fmod(e.age*.85f+float(n)*.25f,1.f),angle=phase*Pi*2+float(n)*Pi/2;
                const float reach=r*(2.4f-1.7f*phase);
                auto dust=add(p,add(mul(side,std::cos(angle)*reach),mul(dir,r*.95f+reach*.5f)));
                dust.y=.16f+phase*r*.5f;sphere(dust,.035f+.025f*(1-phase),Color{218,189,137,220});
            }
        } else {
            for(float height:{-.35f,.2f}) {
                const auto face=add(p,add(mul(dir,r*.88f),{0,r*height,0}));
                DrawCylinderEx(add(face,mul(side,-r*.4f)),add(face,mul(side,r*.4f)),.03f,.03f,5,dark);
            }
        }
        if(type==202)DrawCylinderEx(add(p,{-r*.3f,r*.96f,0}),add(p,{r*.3f,r*.96f,r*.4f}),.025f,.025f,5,dark);
        if(type==236) {
            const auto top=add(p,{0,r,0});
            DrawCylinderEx(add(top,{-r*.6f,0,-r*.4f}),top,.04f,.04f,5,dark);
            DrawCylinderEx(top,add(top,{r*.5f,0,r*.6f}),.04f,.04f,5,dark);
            DrawCylinderEx(add(p,add(mul(dir,r*.87f),{0,r,0})),add(p,add(mul(dir,r*.87f),mul(side,r*.6f))),.035f,.035f,5,dark);
        }
        if(type==804) {
            // A broad stone brow and forward wedge make the fixed attack axis visible.
            DrawCube(add(p,{0,r*.65f,0}),r*1.95f,r*.35f,r*1.95f,bone);
            DrawCylinderEx(add(p,add(mul(dir,r*.88f),{0,-r*.7f,0})),
                add(p,add(mul(dir,r*1.6f),{0,-r*.7f,0})),r*.28f,0,4,bone);
        }
        if(type==809) {
            const auto mark=add(p,add(mul(dir,r*.9f),{0,-r*.15f,0}));
            sphere(mark,r*.3f,{48,44,40,255});
            DrawCylinderEx(add(mark,{0,r*.25f,0}),add(mark,{0,r*.55f,0}),.035f,.025f,5,bone);
            DrawCube(add(p,{0,r*.95f,0}),r*1.85f,r*.18f,r*1.85f,{182,151,96,255});
        }
        if (type == 44)
            for (int n = 0; n < 8; ++n) {
                auto end = add(p, rotateY({r * 1.3f, 0, 0}, float(n) * Pi / 4));
                DrawCylinderEx(p, end, .18f, 0, 5, bone);
            }
        break;
    }
    case MonsterShape::Skull:
        if(e.mushroom) {
            const float opening=e.mushroom->opening;
            const Color stem=e.flash>0?skin:Color{198,177,137,255};
            const Color cap=e.flash>0?skin:Color{127,73,43,255};
            const float height=base+r*(.35f+opening*1.3f);
            DrawCylinderEx({p.x,base+.02f,p.z},{p.x,height,p.z},r*.46f,r*.4f,7,stem);
            // Broad low-poly cap and pale irregular spots give this ordinary
            // enemy its own silhouette without importing source artwork.
            DrawCylinderEx({p.x,height,p.z},{p.x,height+r*.3f,p.z},r*1.22f,r*.88f,9,cap);
            DrawCylinderEx({p.x,height+r*.3f,p.z},{p.x,height+r*.52f,p.z},r*.88f,r*.2f,9,cap);
            for(int n=0;n<5;++n) {
                const auto spot=rotateY({r*(n%2?.52f:.7f),0,0},float(n)*2*Pi/5);
                const float y=height+r*(n%2?.42f:.35f);
                DrawCylinderEx({p.x+spot.x,y,p.z+spot.z},{p.x+spot.x,y+.025f,p.z+spot.z},r*(n%2?.11f:.15f),r*.08f,5,stem);
            }
            if(opening>.3f) {
                auto face=add(Vector3{p.x,height-r*.28f,p.z},mul(dir,r*.38f));
                for(float sign:{-1.f,1.f})sphere(add(face,mul(side,sign*r*.2f)),r*.095f,dark);
                sphere(add(face,{0,-r*.2f,0}),r*(e.mushroom->phase==MushroomPhase::Reveal?.2f:.12f),dark);
            }
            break;
        }
        if (type == 27&&!e.host) {
            const float lift = e.state == EnemyState::Windup || e.state == EnemyState::Exposed ? .65f : 0;
            DrawCylinder({p.x, base+.08f, p.z}, r * .6f, r * .8f, .8f + lift, 8, skin);
            p.y += lift;
        } else if(!e.host)
            p.y += bob;
        if(type==26) {
            const Color mawColor=e.flash>0?Color{255,239,210,255}:variant==1?Color{177,76,78,255}:variant==2?Color{169,157,181,255}:Color{213,199,175,255};
            sphere(p,r,mawColor);
            const auto face=add(p,mul(dir,r*.84f));
            auto stitch=[&](Vector3 at,float width) {
                DrawCylinderEx(add(at,mul(side,-width)),add(at,mul(side,width)),.02f,.02f,4,dark);
                for(int n=-1;n<=1;++n){const auto mark=add(at,mul(side,float(n)*width*.7f));
                    DrawCylinderEx(add(mark,{0,-r*.11f,0}),add(mark,{0,r*.11f,0}),.015f,.015f,4,dark);}
            };
            for(float sign:{-1.f,1.f}) {
                const auto eye=add(face,add(mul(side,sign*r*.34f),{0,r*.19f,0}));
                if(variant==2)stitch(eye,r*.16f);else sphere(eye,r*.16f,dark);
            }
            const auto mouth=add(face,{0,-r*.33f,0});
            if(variant)stitch(mouth,r*.3f);
            else {sphere(mouth,r*(e.state==EnemyState::Windup?.36f:.24f),dark);
                for(float sign:{-1.f,1.f})DrawCubeV(add(mouth,add(mul(side,sign*r*.12f),{0,r*.13f,0})),{r*.12f,r*.2f,r*.15f},bone);}
            if(variant==2) {
                const auto eye=add(face,{0,r*.48f,0});sphere(eye,r*.2f,dark);sphere(add(eye,mul(dir,r*.09f)),r*.11f,{191,101,224,255});
                const auto flame=add(p,{0,r*1.04f,0});DrawCylinderEx(flame,add(flame,{0,r*(.4f+.1f*std::sin(time*9)),0}),r*.15f,0,5,{161,89,198,255});
            }
            break;
        }
        if(e.host) {
            const bool hard=type==27&&variant==3;
            const bool mobile=type==204||type==247,floating=type==859;
            const bool armored=type!=247&&!(type==27&&variant==1);
            const float opening=e.host->exposed?1.f:0.f;
            auto body=Vector3{p.x,floating?p.y-r*.38f:base+(mobile?.55f:r*.7f),p.z};
            const Color flesh=e.flash>0?skin:Color{157,65,65,255};
            if(mobile)for(float sign:{-1.f,1.f}) {
                const float step=std::sin(time*8+sign*Pi/2)*std::min(.18f,length(e.velocity)*.035f);
                auto foot=add(body,add(mul(side,sign*r*.5f),{0,-r*.45f,step}));
                DrawCylinderEx(body,foot,r*.13f,r*.2f,5,flesh);
                sphere(foot,r*.22f,flesh);
            }
            if(!armored||opening>0) {
                const auto root=mobile||floating?add(body,{0,-r*.1f,0}):Vector3{p.x,base+.03f,p.z};
                DrawCylinderEx(root,add(body,{0,r*(armored?1.3f:1.f),0}),r*.47f,r*.52f,8,flesh);
                sphere(add(body,add(mul(dir,r*.5f),{0,r*.5f,0})),r*.22f,dark);
            }
            auto cap=add(body,{0,r*(armored?.35f+opening:1.05f)+(floating?bob:0),0});
            if(e.host->shake&&e.host->frame<0)cap=add(cap,mul(side,std::sin(time*30)*r*.08f));
            const Color shell=hard?Color{137,129,111,255}:bone;
            if(hard) {
                DrawCubeV(cap,{r*1.7f,r*1.3f,r*1.65f},shell);
                sphere(add(cap,{0,r*.35f,0}),r*.75f,{155,146,124,255});
            } else sphere(cap,r*(armored?.94f:.58f),armored?bone:flesh);
            for(float sign:{-1.f,1.f}) {
                auto socket=add(cap,add(mul(dir,r*(armored?.77f:.46f)),mul(side,sign*r*(armored?.31f:.2f))));
                sphere(socket,r*(armored?.21f:.12f),dark);
            }
            if(armored&&!hard)for(int tooth=-2;tooth<=2;++tooth)
                DrawCubeV(add(cap,add(mul(dir,r*.75f),add(mul(side,float(tooth)*r*.22f),{0,-r*.48f,0}))),{r*.16f,r*.3f,r*.18f},bone);
            break;
        }
        sphere(p, r, type == 41 ? Color{87, 94, 93, 255} : bone);
        eyes(p);
        sphere(add(p, add(mul(dir, r * .85f), {0, -r * .3f, 0})), r * .25f, dark);
        if (type == 41) {
            // Knight protection uses the displayed cardinal mask. Rotate the
            // plate with it so side-facing masks do not advertise a false front.
            rlPushMatrix();rlTranslatef(p.x,p.y,p.z);
            rlRotatef(std::atan2(dir.x,dir.z)*RAD2DEG,0,1,0);
            DrawCube({0,0,r*.55f},r*1.65f,r*1.4f,r*.45f,
                     variant==4?dark:Color{105,116,118,255});rlPopMatrix();
            sphere(add(p, mul(dir, -r * .8f)), r * .3f, blood);
        }
        if (type == 27 && variant == 1)
            sphere(add(p, {0, r * .5f, 0}), r * .4f, blood);
        break;
    case MonsterShape::Blob: {
        if(e.leperFlesh) {
            const auto &f=*e.leperFlesh;
            const Color tissue=e.flash>0?Color{250,238,210,255}:Color{166,124,139,255};
            const float pulse=1+.04f*std::sin(f.animation*2*Pi);
            const float angle=(f.flip?-1.f:1.f)*float(f.shape)*Pi/3;
            const auto axis=rotateY({1,0,0},angle);
            const auto center=add(p,{0,-r*.25f,0});
            rlPushMatrix();rlTranslatef(center.x,center.y,center.z);
            rlRotatef(angle*RAD2DEG,0,1,0);rlScalef(1.15f*pulse,.65f,.8f/pulse);
            sphere({},r*.7f,tissue);rlPopMatrix();
            sphere(add(center,mul(axis,r*.45f)),r*(.25f+.025f*f.shape),ColorBrightness(tissue,.1f));
            sphere(add(center,{0,r*.3f,0}),r*.22f,{97,55,70,255});
            break;
        }
        if(type==840&&e.landingCreep) {
            const Color tissue=e.flash>0?Color{250,238,210,255}:Color{170,93,105,255};
            sphere(p,r*.76f,{98,48,63,255});
            for(int n=0;n<6;++n) {
                const auto lobe=rotateY({r*.42f,0,0},float(n)*Pi/3);
                sphere(add(p,add(lobe,{0,r*.2f,0})),r*.46f,tissue);
            }
            sphere(add(p,{0,r*.48f,0}),r*.38f,tissue);break;
        }
        if(e.slide||type==223) {
            const bool water=type==870||type==871,corn=type==217&&variant>0;
            const Color body=e.flash>0?Color{250,238,210,255}:water?Color{105,128,106,255}:
                type==220&&variant==1?Color{60,51,66,255}:corn&&variant==1?Color{210,171,66,255}:
                corn&&variant==2?Color{104,66,36,255}:type==223?Color{119,73,43,255}:type==220?Color{139,87,44,255}:Color{157,102,51,255};
            const float wave=std::sin((e.slide?e.slide->animation:e.memBrain?e.memBrain->walkPhase:0)*2*Pi+e.idleTime*5);
            const float windup=e.slide&&e.slide->phase==1?std::clamp(float(e.slide->frame)/(e.slide->secondDash?8:36),0.f,1.f):0;
            const float pulse=1+.035f*wave+.1f*windup;
            const auto center=Vector3{p.x,base+r*.55f+e.lift,p.z};
            sphere(center,r*.78f*pulse,body);
            sphere(add(center,{0,r*.48f,0}),r*.55f,ColorBrightness(body,.08f));
            sphere(add(center,add(mul(dir,-r*.1f),{0,r*.82f,0})),r*.31f,ColorBrightness(body,.12f));
            if(corn) {
                const auto kernel=add(center,{0,r*(variant==3?1.05f:.8f),0});
                sphere(kernel,r*(variant==3?.4f:.2f),{224,189,74,255});
            }
            if(water)for(float sign:{-1.f,1.f})
                sphere(add(center,add(mul(side,sign*r*.68f),{0,-r*.18f,0})),r*.26f,{142,157,107,255});
            const auto face=add(center,mul(dir,r*.7f));
            for(float sign:{-1.f,1.f}) {
                const auto eye=add(face,add(mul(side,sign*r*.27f),{0,r*.3f,0}));
                sphere(eye,r*.13f,{224,204,157,255});sphere(add(eye,mul(dir,r*.08f)),r*.075f,dark);
            }
            sphere(add(face,{0,-r*.03f,0}),r*(type==223?.24f:windup>0?.19f:.12f),dark);
            break;
        }
        if(e.memBrain) {
            const auto &mem=*e.memBrain;
            const Color tissue=e.flash>0?Color{250,238,210,255}:variant==2?Color{147,153,99,255}:
                variant==1?Color{164,98,109,255}:Color{180,111,120,255};
            const auto center=Vector3{p.x,base+r*.66f+e.lift,p.z};
            const float pulse=1+.035f*std::sin((mem.walkPhase+e.idleTime)*2*Pi);
            for(float sign:{-1.f,1.f}) {
                const auto lobe=add(center,mul(side,sign*r*.32f));
                sphere(lobe,r*.62f*pulse,tissue);
                for(int n=-1;n<=1;++n)
                    sphere(add(lobe,add(mul(dir,float(n)*r*.32f),{0,r*.34f,0})),r*.24f,ColorBrightness(tissue,.1f));
            }
            if(variant>0) {
                const auto face=add(center,mul(dir,r*.68f));
                sphere(face,r*(mem.attackFrame>=0?.27f:.16f),dark);
                for(float sign:{-1.f,1.f})sphere(add(face,add(mul(side,sign*r*.35f),{0,r*.28f,0})),r*.1f,dark);
            }
            break;
        }
        if(e.guts) {
            const auto &roll=*e.guts;
            const Color body=e.flash>0?Color{250,238,210,255}:type==862?Color{147,153,99,255}:variant==2?Color{71,57,66,255}:
                variant==1?Color{195,152,151,255}:Color{163,89,94,255};
            const float phase=2*Pi*(roll.rollPhase+e.idleTime*1.25f);
            const auto center=Vector3{p.x,base+r*.78f,p.z};
            sphere(center,r*.83f,body);
            for(int n=0;n<5;++n) {
                const float angle=phase+float(n)*2*Pi/5;
                sphere(add(center,add(mul(dir,std::cos(angle)*r*.62f),{0,std::sin(angle)*r*.62f,0})),r*.28f,ColorBrightness(body,.12f));
            }
            if(type==862) {
                const auto mouth=add(center,mul(roll.gaze,r*.78f));
                sphere(mouth,r*(roll.shotFrame>=0?.27f:.13f),dark);
            }
            if(variant==2) {
                const auto look=roll.gaze;
                const auto eye=add(center,mul(look,r*.74f));
                sphere(eye,r*(roll.windup>=0?.4f:.3f),Color{231,182,70,255});
                sphere(add(eye,mul(look,r*.14f)),r*.13f,dark);
            }
            break;
        }
        if(e.brain) {
            if(type==279) {
                const auto head=Vector3{p.x,base+r*.62f,p.z};
                sphere(head,r*.9f,skin);
                eyes(add(head,mul(dir,r*.18f)));
                for(float sign:{-1.f,1.f})
                    sphere(add(head,add(mul(side,sign*r*.37f),{0,-r*.46f,0})),r*.25f,blood);
                break;
            }
            // Two folded lobes, without a generic face. The charge changes pose
            // through the same source Walk clock; geometry stays inside the hit body.
            const float pulse=std::sin(e.brain->walkPhase*2*Pi)*.025f;
            const Color cortex=e.flash>0?Color{250,238,210,255}:Color{178,111,119,255};
            for(float sign:{-1.f,1.f}) {
                const auto lobe=add(Vector3{p.x,base+r*.58f+pulse,p.z},mul(side,sign*r*.27f));
                sphere(lobe,r*.59f,cortex);
                for(int n=-1;n<=1;++n)
                    sphere(add(lobe,add(mul(dir,float(n)*r*.27f),{0,r*.31f,0})),r*.24f,ColorBrightness(cortex,.09f));
            }
            break;
        }
        const float scale = type == 30 ? .55f + .45f * e.hp / e.maxHp : 1;
        const bool boil=type==30||type==88;
        const float attackSwell=boil&&e.sack&&e.sack->frame>=0&&!e.sack->shake?
            .12f*std::sin(Pi*float(std::min(e.sack->frame,24))/24):0;
        p.y = base + (boil?r*scale+.05f:.55f) + e.lift;
        sphere(p, r * scale * (1 + bob * .25f+attackSwell), skin);
        for (int n = 0; n < 4; ++n)
            sphere(add(p, rotateY({r * .55f, -.25f, 0}, float(n) * Pi / 2)), r * .4f, skin);
        eyes(p);
        if(type==15&&variant==3) {
            // Ember nodules distinguish the quick burned variant without
            // inventing a new collision silhouette or ground-fire attack.
            for(int n=0;n<3;++n)
                sphere(add(p,rotateY({r*.65f,r*.4f,0},float(n)*2*Pi/3)),r*.16f,{231,135,56,255});
        }
        if (boil) {
            sphere(add(p, {0, r * scale * .6f, 0}), r * scale * .36f, variant == 2 ? bone : variant==1?Color{81,109,42,255}:blood);
            if(type==88)for(float sign:{-1.f,1.f}) {
                const float step=std::sin(time*8+sign*Pi/2)*std::min(.16f,length(e.velocity)*.035f);
                const auto ankle=add(p,add(mul(side,sign*r*.5f),{0,-r*.65f,step}));
                DrawCylinderEx(ankle,add(ankle,{0,-r*.35f,0}),r*.12f,r*.15f,5,dark);
            }
        }
        if (type == 32 || type == 57 || type == 840)
            for (float x : {-.22f, .22f})
                sphere(add(p, {x, r * .5f, 0}), r * .42f, ColorBrightness(skin, .2f));
        break;
    }
    case MonsterShape::Walker:
    case MonsterShape::Headless: {
        if(type==310&&variant==0&&e.leper) {
            const Color tissue=e.flash>0?Color{245,233,206,255}:Color{155,126,137,255};
            const float stride=std::sin(e.leper->walkPhase*2*Pi)*std::min(.16f,length(e.velocity)*.06f);
            for(float sign:{-1.f,1.f}) {
                const auto foot=add({p.x,base+.2f,p.z},add(mul(side,sign*r*.42f),mul(dir,stride*sign)));
                DrawCylinder(foot,r*.2f,r*.25f,.5f,6,ColorBrightness(tissue,-.18f));
            }
            const auto torso=Vector3{p.x,base+.62f,p.z};
            sphere(torso,r*.76f,ColorBrightness(tissue,-.14f));
            const auto head=add(torso,{0,r*.9f,0});
            const float shake=e.leper->transition>0?std::sin(time*55)*r*.09f:0;
            // Each form removes another pale lobe and exposes a dark wound.
            for(int n=0;n<4;++n) {
                const auto offset=rotateY({r*.28f,0,0},float(n)*Pi/2);
                const auto at=add(head,add(offset,{shake,r*(n%2?.08f:.28f),0}));
                sphere(at,r*(n>=e.monster.subtype?.46f:.23f),n>=e.monster.subtype?tissue:Color{91,55,67,255});
            }
            if(e.monster.subtype<2)eyes(add(head,mul(dir,r*.18f)),r*.45f);
            break;
        }
        const float step = std::sin(e.gaper?e.gaper->walkPhase*2*Pi:e.blackGlobin?e.blackGlobin->walkPhase*2*Pi:e.rottenGaper?e.rottenGaper->walkPhase*2*Pi:time*9) * std::min(.16f, e.animationSpeed() * .06f);
        for (float sign : {-1.f, 1.f}) {
            auto foot =
                add({p.x, base + .17f + e.lift, p.z}, add(mul(side, sign * r * .45f), mul(dir, step * sign)));
            DrawCylinder(foot, r * .2f, r * .25f, .5f, 6, skin);
        }
        DrawCylinder({p.x, base + .4f + e.lift, p.z}, r * .7f, r * .85f, .7f + bob * .25f, 8, skin);
        if(e.hopRings||e.leaper)for(float sign:{-1.f,1.f}) {
            const auto shoulder=add(p,add(mul(side,sign*r*.64f),{0,.03f,0}));
            const auto elbow=add(shoulder,add(mul(side,sign*r*.52f),mul(dir,sign*r*.4f)));
            const auto hand=add(elbow,add(mul(dir,sign*r*.4f),{0,-r*.22f,0}));
            DrawCylinderEx(shoulder,elbow,r*.2f,r*.16f,6,skin);
            DrawCylinderEx(elbow,hand,r*.16f,r*.12f,6,skin);sphere(hand,r*.17f,dark);
        }
        if (d.shape == MonsterShape::Walker) {
            auto head = add(p, {0, .57f + bob * .25f, 0});
            if(rotten==2||rotten==5)head=add(head,mul(dir,r*.2f));
            sphere(head, r * (type==205?1.08f:type==827&&variant==1?1.04f:rotten==2?.72f:rotten==3?1.f:.85f), skin);
            if(type==205) {
                // A hollow swollen nest with uneven openings and web seams;
                // its profile remains distinguishable from the ordinary walkers.
                auto openingPatch=[&](Vector3 at,float size) {
                    rlPushMatrix();rlTranslatef(at.x,at.y,at.z);
                    rlRotatef(std::atan2(dir.x,dir.z)*180/Pi,0,1,0);rlScalef(1,1,.12f);
                    sphere({},size,dark);rlPopMatrix();
                };
                for(float sign:{-1.f,1.f}) {
                    const auto hole=add(head,add(mul(dir,r*.98f),add(mul(side,sign*r*.49f),{0,r*.23f,0})));
                    openingPatch(hole,r*(sign<0?.22f:.3f));
                    const auto rim=add(head,add(mul(side,sign*r*.9f),{0,r*.35f,-r*.05f}));
                    DrawCylinderEx(rim,add(rim,add(mul(dir,r*.25f),{0,-r*.55f,0})),r*.032f,r*.02f,4,bone);
                }
                const int frame=e.evader?e.evader->attackFrame:-1;
                const float opening=frame>=0?(frame<4?.32f+.09f*float(frame):.62f-.018f*float(frame-4)):.3f;
                const auto mouth=add(head,add(mul(dir,r*1.07f),{0,-r*.3f,0}));
                openingPatch(mouth,r*opening);
                if(frame>=1&&frame<4) {
                    const auto child=add(mouth,mul(dir,r*.2f));sphere(child,r*.19f,dark);
                    for(float sign:{-1.f,1.f})for(int leg=0;leg<3;++leg)
                        DrawCylinderEx(child,add(child,add(mul(side,sign*r*.35f),mul(dir,(float(leg)-1)*r*.18f))),r*.025f,r*.018f,4,dark);
                }
            } else if(e.monster.type==827) {
                // A raw, eyeless facial cavity; Tainted has a larger scarred rim.
                const bool tainted=variant==1;
                const bool open=e.faceless&&e.faceless->frame>=0;
                auto facePatch=[&](float offset,float size,float depth,Color color) {
                    const auto face=add(head,mul(dir,r*offset));
                    rlPushMatrix();rlTranslatef(face.x,face.y,face.z);
                    rlRotatef(std::atan2(dir.x,dir.z)*180/Pi,0,1,0);rlScalef(1,1,depth);
                    sphere({},r*size,color);rlPopMatrix();
                };
                // Flatten the cavity against the head so its side silhouette
                // reads as an open face rather than a separate spherical snout.
                facePatch(tainted?.98f:.8f,tainted?.68f:.59f,.16f,blood);
                facePatch(tainted?1.02f:.85f,open?.5f:.36f,.12f,dark);
                for(float sign:{-1.f,1.f}) {
                    const auto fold=add(head,add(mul(side,sign*r*.57f),mul(dir,r*.6f)));
                    DrawCylinderEx(add(fold,{0,r*.34f,0}),add(fold,{0,-r*.3f,0}),r*.11f,r*.07f,5,tainted?dark:skin);
                }
            } else if(e.gaper&&variant==0) {
                // Head animation starts shut, then opens across20 source frames.
                const float opening=e.gaper->eyeOpenness;
                for(float sign:{-1.f,1.f}) {
                    const auto eye=add(head,add(mul(dir,r*.77f),mul(side,sign*r*.33f)));
                    if(opening<=0)DrawCylinderEx(add(eye,mul(side,-r*.19f)),add(eye,mul(side,r*.19f)),r*.035f,r*.035f,5,dark);
                    else {
                        rlPushMatrix();rlTranslatef(eye.x,eye.y,eye.z);rlScalef(1,std::max(.08f,opening),1);
                        sphere({},r*.2f,bone);sphere(mul(dir,r*.14f),r*.11f,dark);rlPopMatrix();
                    }
                }
            } else if(rotten==2) {
                auto eye=add(head,mul(dir,r*.72f));sphere(eye,r*.3f,bone);
                sphere(add(eye,mul(dir,r*.13f)),r*.17f,dark);
            } else eyes(head,rotten==4?.65f:1.f);
            if(e.mirror&&variant==1) {
                const auto third=add(head,add(mul(dir,r*.78f),{0,r*.35f,0}));
                sphere(third,r*.17f,bone);sphere(add(third,mul(dir,r*.08f)),r*.08f,blood);
            }
            if(type!=827&&type!=205)sphere(add(head, add(mul(dir, r * .76f), {0, -.25f, 0})), r * .28f, dark);
            if(e.mirror&&e.mirror->shootFrame>0)
                sphere(add(head,add(mul(dir,r*.83f),{0,-.25f,0})),r*.18f,blood);
            if(rotten==1)for(float sign:{-1.f,1.f}) {
                auto brow=add(head,add(mul(dir,r*.77f),add(mul(side,sign*r*.33f),{0,r*.21f,0})));
                DrawCylinderEx(add(brow,mul(side,-r*.22f)),add(brow,mul(side,r*.22f)),r*.06f,r*.06f,5,dark);
            }
            if(rotten==3) {
                sphere(add(p,{0,-.08f,0}),r*1.07f,skin);
                for(int n=0;n<3;++n) {
                    auto at=add(p,add(mul(dir,-r*.8f),add(mul(side,(float(n)-1)*r*.5f),{0,.3f,0})));
                    sphere(at,r*.25f,bone);
                }
            }
            if(rotten==5)for(float sign:{-1.f,1.f}) {
                auto cheek=add(head,add(mul(side,sign*r*.64f),mul(dir,-r*.1f)));
                DrawCylinderEx(cheek,add(cheek,mul(dir,-r*.6f)),r*.22f,.02f,5,skin);
            }
        } else {
            const bool pacer=e.headless&&d.id==monsterId(11,1);
            DrawCylinder({p.x, base + 1.05f + e.lift, p.z}, r * .36f, r * .36f, .08f, 8, pacer?dark:blood);
        }
        if(e.headless&&type==11) {
            // Readable silhouette at gameplay zoom: the bleeding body holds
            // its shoulders high; the quiet body has low, dangling hands.
            // This is an Original-style pose adaptation, not an attack tell.
            const bool gushing=variant==0;
            for(float sign:{-1.f,1.f}) {
                const auto shoulder=add(Vector3{p.x,base+.88f+e.lift,p.z},mul(side,sign*r*.65f));
                const auto elbow=add(shoulder,add(mul(side,sign*r*.48f),{0,gushing?.15f:-.3f,0}));
                const auto hand=add(elbow,add(mul(dir,r*.23f),{0,gushing?.14f:-.16f,0}));
                DrawCylinderEx(shoulder,elbow,r*.13f,r*.11f,5,skin);
                DrawCylinderEx(elbow,hand,r*.11f,r*.14f,5,skin);
            }
        }
        if(e.headless&&d.id==monsterId(11)) {
            // Source Blood is a continuous ten-frame loop, not an attack cue.
            const float phase=float(e.headless->animationTicks%10)/10;
            for(int n=0;n<3;++n) {
                const float t=std::fmod(phase+float(n)/3,1.f);
                sphere({p.x,base+1.08f+e.lift+t*.9f,p.z},r*.17f*(1-t*.5f),blood);
            }
        }
        if(e.headless&&d.id==monsterId(11,1))
            DrawCylinder({p.x,base+1.14f+e.lift,p.z},r*.24f,r*.24f,.025f,8,dark);
        if(e.headless&&type==280) {
            // Native eight-frame Spiders overlay: small moving legs around
            // the open neck, not Gusher's blood jet or an attack windup.
            const float phase=float(e.headless->animationTicks%8)*Pi/4;
            for(int n=0;n<3;++n) {
                const auto tip=add(Vector3{p.x,base+1.15f,p.z},rotateY({r*.3f,.07f*std::sin(phase+n),0},float(n)*2*Pi/3));
                sphere(tip,r*.1f,dark);
                for(float sign:{-1.f,1.f})DrawCylinderEx(tip,add(tip,mul(side,sign*r*.19f)),r*.025f,r*.015f,4,dark);
            }
        }
        if (type == 39) {
            const int mouths=variant==3?4:variant==1?2:1;
            const float windup=e.vis?float(e.vis->attackFrame)+e.stateTime*30:0;
            const float charge=e.vis&&windup>0&&e.vis->attackFrame>=0&&!e.vis->fired?
                std::clamp(float(e.vis->attackFrame)/windup,0.f,1.f):0;
            const std::array<Vector3,4> axes{{dir,mul(dir,-1),side,mul(side,-1)}};
            for(int n=0;n<mouths;++n) {
                const auto mouth=add(p,mul(axes[size_t(n)],r*.77f));
                sphere(mouth,r*(.38f+charge*.14f),dark);
                if(charge>0)sphere(add(mouth,mul(axes[size_t(n)],r*.14f)),r*(.08f+charge*.19f),blood);
                if(variant==2&&charge>.35f) {
                    const auto snout=add(mouth,mul(axes[size_t(n)],r*charge*.7f));
                    sphere(snout,r*.29f,{171,128,95,255});
                    sphere(add(snout,mul(axes[size_t(n)],r*.22f)),r*.15f,dark);
                }
            }
        }
        if (type == 22 || type == 16)
            sphere(add(p, {0, -.08f, 0}), r * 1.04f, skin);
        if (type == 38)
            for (float sign : {-1.f, 1.f})
                DrawSphereEx(add(p, mul(side, sign * r)), r * .65f, 4, 6, bone);
        break;
    }
    }
    if(type==10&&variant==2) {
        // Keep the flame outside the head silhouette; the old torso cones
        // were buried inside the body and barely visible at gameplay zoom.
        const float phase=e.gaper?float(e.gaper->headFrame)*2*Pi/12:time*11;
        for(int n=0;n<5;++n) {
            const float angle=float(n)*2*Pi/5;
            const auto foot=add(p,rotateY({r*.72f,.63f,0},angle));
            const auto tip=add(foot,{.06f*std::sin(phase+n),.72f+.15f*std::sin(phase+n*2),.04f});
            DrawCylinderEx(foot,tip,r*.3f,0,5,{227,115,36,255});
            DrawCylinderEx(add(foot,{0,.06f,0}),add(foot,mul(sub(tip,foot),.78f)),r*.17f,0,5,{255,209,99,255});
        }
    } else if (type == 54 || (type == 15 && variant == 3)) {
        for (int n = 0; n < 3; ++n)
            DrawCylinder(add(p, rotateY({r * .6f, .2f, 0}, float(n) * 2 * Pi / 3)), 0, .2f,
                         .8f + std::sin(time * 11) * .2f, 5, {227, 143, 47, 255});
    }
}
inline void drawMonsterWarning(const Enemy &e, const Simulation &run) {
    if(e.adultLeech)return; // Body pose, falling silhouette and audio signal its attacks.
    if(e.slide)return; // Squirt body squash telegraphs its committed slide.
    if(e.memBrain)return; // Body hop and recovery telegraph the radial packet.
    if(e.lump)return; // Mouth/Hide/Appear poses carry the source warning, without an aim laser.
    if(e.vis)return; // Distinct mouths show every committed lane and charge on the body.
    if(e.spitty)return; // The mouth telegraphs its committed facing; no destination-aimed laser.
    if(e.faceless)return; // Opening face telegraphs the fixed ring, not an aimed shot.
    if (e.state != EnemyState::Windup)
        return;
    const auto &d = *run.content->monster(e.monster);
    const auto direction = unit(sub(e.target, e.position));
    const Color warning{243, 181, 90, 230};
    if(const auto *s=run.content->statue(e.monster);s&&s->attack==StatueAttack::Quake) {
        const Vector3 side{-e.facing.z,0,e.facing.x};
        for(float distance:{1.3f,2.3f,3.3f}) {
            auto tip=add(e.position,mul(e.facing,distance));
            if(run.arena.roomAt(tip)!=run.room||run.arena.trace(e.position,tip,s->waveRadius).hit)break;
            tip.y=.1f;const auto back=sub(tip,mul(e.facing,.35f));
            DrawLine3D(add(back,mul(side,.25f)),tip,warning);
            DrawLine3D(sub(back,mul(side,.25f)),tip,warning);
        }
        return;
    }
    auto line = [&](Vector3 dir) {
        auto end = add(e.position, mul(dir, 24));
        const auto hit = run.arena.trace(e.position, end);
        if (hit.hit)
            end = add(e.position, mul(sub(end, e.position), hit.t));
        DrawLine3D({e.position.x, .1f, e.position.z}, {end.x, .1f, end.z}, warning);
    };
    if (d.motion == MonsterMotion::Hop || d.attack == MonsterAttack::Lob || d.attack == MonsterAttack::Light)
        DrawCircle3D({e.target.x, .1f, e.target.z}, d.motion == MonsterMotion::Hop ? .8f : 2.2f, {1, 0, 0},
                     90, warning);
    else if (d.attack == MonsterAttack::Cross || d.attack == MonsterAttack::Diagonal ||
             d.attack == MonsterAttack::Ring) {
        const int count = d.attack == MonsterAttack::Ring ? 8 : 4;
        for (int n = 0; n < count; ++n)
            line(rotateY({1, 0, 0}, float(n) * 2 * Pi / float(count) +
                                        (d.attack == MonsterAttack::Diagonal ? Pi / 4 : 0)));
    } else {
        line(direction);
        if (d.attack == MonsterAttack::DoubleBeam)
            line(mul(direction, -1));
        if (d.attack == MonsterAttack::QuadBeam)
            for (int n = 1; n < 4; ++n)
                line(rotateY(direction, float(n) * Pi / 2));
    }
    DrawSphereEx(add(e.position, {0, 1, 0}), .12f, 4, 6, warning);
}
} // namespace dw
