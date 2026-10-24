#include "world/Dungeon.hpp"

namespace dw {
void Arena::dressFloor() {
    if(!profile.active()||profile.band<2)return;
    Random rng(visualSeed^0x464c4f4f52445253ULL);
    for(int index=1;index<roomCount()-1;++index) {
        const auto &room=rooms[size_t(index)];
        if(room.kind!=RoomKind::Combat||room.story!=StoryRoom::None)continue;
        std::vector<Vector3> routes{room.entry,room.exit,room.objective};
        for(int link:room.passages)routes.push_back(doorApproach(link,passages[size_t(link)].rooms[0]==index?0:1));
        // Small reused railway-work remnants, physically separate from the narrative props.
        for(int n=0;n<(profile.band==2?3:1);++n)for(int attempt=0;attempt<120;++attempt) {
            Vector3 p{rng.real(room.bounds.min.x+3,room.bounds.max.x-3),.85f,
                      rng.real(room.bounds.min.z+3,room.bounds.max.z-3)};
            const bool rail=n%2==0;
            Box box{{p.x-1.1f,0,p.z-.55f},{p.x+1.1f,rail?.16f:.8f,p.z+.55f}};
            bool safe=true;
            for(auto end:routes)if(segmentBox(room.center,end,box,1.8f).hit)safe=false;
            for(const auto &key:keys)if(sphereBox(key.position,2,box))safe=false;
            for(float x=box.min.x-.6f;x<=box.max.x+.61f;x+=.5f)for(float z=box.min.z-.6f;z<=box.max.z+.61f;z+=.5f) {
                const Vector3 q{x,.85f,z};
                if(roomAt(q)!=index||blocked(q,.6f))safe=false;
                if(canyon&&(std::abs(canyon->height(x,z))>.02f||
                    canyon->roadSample(q).distance<canyon->roadSample(q).width+1||
                    canyon->riverSample(q).distance<canyon->riverSample(q).width+1))safe=false;
            }
            for(const auto &prop:floorProps)if(sphereBox(p,2,prop.bounds))safe=false;
            if(!safe)continue;
            floorProps.push_back({rail?StoryPropKind::Rail:StoryPropKind::Timber,box});
            rebuildWalls();
            for(auto end:routes)if(path(room.center,end,.48f).empty())safe=false;
            if(!safe){floorProps.pop_back();rebuildWalls();continue;}
            break;
        }
    }
}
void Arena::prepareBossArena() {
    if(!profile.active()||theme!=MissionTheme::Canyon)return;
    const int index=roomCount()-1;
    const auto &room=rooms.back();
    // Two low, fragile rocks offer a charge counter. They sit inside the outer
    // dodge loop, away from the entrance, exit, evidence and broad cardinal paths.
    Random rng(visualSeed^0x424f5353434f5645ULL);
    const int turn=int(rng.bounded(4));
    for(int n=0;n<2;++n) {
        Vector3 offset=rotateY({5.2f,0,n?5.2f:-5.2f},float(turn)*Pi/2);
        auto p=add(room.center,offset);
        if(blocked(p,1.8f)||distance(p,room.objective)<3||distance(p,room.entry)<6)continue;
        Breakable prop;prop.id=0x424f53530000ULL+uint64_t(n);prop.room=index;
        prop.kind=BreakableKind::CrackedRock;prop.health=1;prop.paid=true;
        prop.bounds={{p.x-.8f,0,p.z-.8f},{p.x+.8f,1.1f,p.z+.8f}};
        prop.rewardPosition=p;
        breakables.push_back(prop);
    }
    rebuildWalls();
}
} // namespace dw
