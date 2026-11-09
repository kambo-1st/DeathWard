#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <stdexcept>
#include <vector>

namespace dw::native_grid {
// Bounded 1.7.9b FindGridPath flood/gradient reference, 7a4383..7a46b5.
// Supplied cost mask, start and target; no direct-line test, cache, footprint
// expansion, room-shape16 exception, collision or world-coordinate conversion.
// Private geometric-room review supplies adapted masks; production stays off.
// Ordinary no-object fallback and explicit object collision override,7aeec0.
inline int collisionClass(int cost,int objectCollision=-1) {
    return objectCollision>=0?objectCollision:cost>=3000&&cost<=3999?1:cost>=1000?3:0;
}
// Ordinary mode0 CheckLine,7af4b0. Native coordinates,10-coordinate steps,
// four +/-5 probes and at most8 positive-cost samples outside the start cell.
// Supplied cost mask only: native object/status/room-config exceptions excluded.
inline bool clearLine(const std::vector<int> &costs,int width,int height,
                      float x,float y,float targetX,float targetY,int threshold=0) {
    if(width<=0||height<=0||width*height>448||int(costs.size())!=width*height)
        throw std::invalid_argument("native line reference requires valid supplied grid");
    auto index=[&](float px,float py) {
        const int c=int((px-40)/40+.5f),r=int((py-120)/40+.5f);
        return c<0||c>=width||r<0||r>=height?-1:r*width+c;
    };
    const float dx=x-targetX,dy=y-targetY,distance=std::sqrt(dx*dx+dy*dy);
    if(distance<=0)return true;
    const float stepX=dx/distance*10,stepY=dy/distance*10;
    const int start=index(x,y);int positive=0;float walked=0;
    do {
        x-=stepX;y-=stepY;
        for(const auto offset:std::array<std::array<float,2>,4>{{{{-5,-5}},{{-5,5}},{{5,5}},{{5,-5}}}}) {
            const int cell=index(x+offset[0],y+offset[1]);
            if(cell<0||collisionClass(costs[cell])!=0)return false;
            if(cell!=start&&costs[cell]>threshold)++positive;
        }
        walked+=10;
    }while(distance>walked);
    return positive<=8;
}
struct Waypoint {bool found=false;int index=-1;};
inline Waypoint gaperWaypoint(std::vector<int> costs,int width,int height,int start,int goal) {
    if(width<=0||height<=0||width*height>448||int(costs.size())!=width*height||
       start<0||start>=width*height||goal<0||goal>=width*height)
        throw std::invalid_argument("native grid reference requires valid supplied cells");
    struct Entry {int cell,cost;};
    auto later=[](const Entry &a,const Entry &b){return a.cost>b.cost;};
    auto neighbors=[&](int i) {
        const int x=i%width,y=i/width;
        return std::vector<int>{x>0?i-1:-1,y>0?i-width:-1,
                                x+1<width?i+1:-1,y+1<height?i+width:-1};
    };
    std::vector<Entry> heap{{goal,0}};
    bool found=false;
    while(!heap.empty()&&!found) {
        const auto current=heap.front();
        if(current.cost>=width*height/2)break;
        std::pop_heap(heap.begin(),heap.end(),later);heap.pop_back();
        for(const int cell:neighbors(current.cell)) {
            if(cell<0||costs[cell]<0||costs[cell]>=950)continue;
            const int cost=current.cost+(costs[cell]>0?7:1);
            costs[cell]=-cost;
            if(cell==start)found=true;
            heap.push_back({cell,cost});std::push_heap(heap.begin(),heap.end(),later);
        }
    }
    if(!found)return {};
    int selected=start,best=-1000;
    for(const int cell:neighbors(start))if(cell>=0&&costs[cell]<0&&costs[cell]>best) {
        selected=cell;best=costs[cell];
    }
    return {true,selected};
}
} // namespace dw::native_grid
