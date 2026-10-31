#include "world/RailNetwork.hpp"
#include <map>
#include <set>
#include <stdexcept>
#include <tuple>

namespace dw {
namespace {
unsigned port(RailSide side){return 1u<<unsigned(side);}
RailSide opposite(RailSide side){return RailSide((unsigned(side)+2)%4);}
void require(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool finite(Vector3 p){return std::isfinite(p.x)&&std::isfinite(p.y)&&std::isfinite(p.z);}
}
unsigned railPorts(int variant) {
    constexpr unsigned n=1,e=2,s=4,w=8;
    // The vertical end-stop icons and reciprocal installed geometry identify
    // 9 as the south port and 10 as north. Editor display labels are ambiguous.
    constexpr unsigned ports[]{e|w,n|s,e|s,w|s,e|n,w|n,n|e|s|w,e,w,s,n};
    require(variant>=0&&variant<11,"Unsupported rail tile variant");return ports[variant];
}
Vector3 railDirection(RailSide side) {
    constexpr Vector3 directions[]{{0,0,-1},{1,0,0},{0,0,1},{-1,0,0}};
    return directions[unsigned(side)];
}
void RailLayout::compile() {
    require(closedEntrances<16,"Invalid rail player-entrance mask");
    require(width>=2&&height>=2&&width<=52&&height<=52,"Rail dimensions outside [2,52]");
    require(!key.empty()&&key.size()<=64&&!cells.empty()&&cells.size()<=2704,"Invalid rail key or tile count");
    doors.clear();routes.clear();std::map<std::pair<int,int>,int> grid;
    for(const auto *features:{&pitCells,&rockCells}) {
        std::set<std::pair<int,int>> seen;
        for(auto cell:*features)require(cell.first>=0&&cell.first<width&&cell.second>=0&&cell.second<height&&seen.insert(cell).second,"Invalid/duplicate rail terrain cell");
    }
    for(size_t i=0;i<cells.size();++i) {
        const auto &c=cells[i];railPorts(c.variant);
        require(c.x>=0&&c.x<width&&c.z>=0&&c.z<height,"Rail tile outside layout");
        require(grid.emplace(std::pair{c.x,c.z},int(i)).second,"Duplicate rail tile");
    }
    // Deterministic door order follows coordinates, not authoring line order.
    for(const auto &[coordinate,index]:grid) {
        const auto &c=cells[size_t(index)];
        for(int s=0;s<4;++s)if(railPorts(c.variant)&port(RailSide(s))) {
            const auto d=railDirection(RailSide(s));const int x=c.x+int(d.x),z=c.z+int(d.z);
            if(x<0||z<0||x>=width||z>=height){doors.push_back({index,RailSide(s)});continue;}
            auto other=grid.find({x,z});
            require(other!=grid.end()&&(railPorts(cells[size_t(other->second)].variant)&port(opposite(RailSide(s)))),
                    "Rail port has no reciprocal neighbor");
        }
    }
    require(doors.size()>=2&&doors.size()<=208,"Rail layout needs bounded wall-door entries");
    for(size_t entry=0;entry<doors.size();++entry) {
        RailRouteDefinition route;route.entry=int(entry);route.exit=-1;
        auto cell=doors[entry].cell;auto incoming=doors[entry].side;
        std::set<std::pair<int,RailSide>> visited;
        for(size_t n=0;n<cells.size()*4+1;++n) {
            require(visited.emplace(cell,incoming).second,"Rail door route enters a closed loop");
            const auto &c=cells[size_t(cell)];const auto ports=railPorts(c.variant);
            require(ports&port(incoming),"Rail route enters a disconnected side");
            auto outgoing=incoming;
            if(ports&port(opposite(incoming)))outgoing=opposite(incoming);
            else for(int s=0;s<4;++s)if(RailSide(s)!=incoming&&(ports&port(RailSide(s))))outgoing=RailSide(s);
            route.steps.push_back({cell,incoming,outgoing});
            const auto d=railDirection(outgoing);auto next=grid.find({c.x+int(d.x),c.z+int(d.z)});
            if(next==grid.end()) {
                for(size_t i=0;i<doors.size();++i)if(doors[i].cell==cell&&doors[i].side==outgoing)route.exit=int(i);
                require(route.exit>=0,"Rail route exits outside a wall door");break;
            }
            cell=next->second;incoming=opposite(outgoing);
        }
        require(route.exit>=0,"Rail route exceeded traversal bound");routes.push_back(std::move(route));
    }
}
RailLayout RailLayout::reversed() const {
    auto result=*this;result.halfTurns=(halfTurns+1)%2;
    result.closedEntrances=((closedEntrances<<2)|(closedEntrances>>2))&15;
    for(auto &cell:result.cells) {
        cell.x=width-1-cell.x;cell.z=height-1-cell.z;
        const unsigned p=railPorts(cell.variant),rotated=((p<<2)|(p>>2))&15;
        for(int n=0;n<11;++n)if(railPorts(n)==rotated){cell.variant=n;break;}
    }
    for(auto *features:{&result.pitCells,&result.rockCells})for(auto &[x,z]:*features){x=width-1-x;z=height-1-z;}
    result.compile();return result;
}
RailPose RailPath::sample(float travelled) const {
    require(points.size()>=2&&distances.size()==points.size()&&length()>0,"Uncompiled rail path");
    require(std::isfinite(travelled),"Nonfinite rail distance");
    const float at=std::clamp(travelled,0.f,length());
    auto upper=std::upper_bound(distances.begin(),distances.end(),at);
    const auto next=std::clamp(size_t(upper-distances.begin()),size_t(1),points.size()-1);
    const float span=distances[next]-distances[next-1];
    const auto delta=sub(points[next],points[next-1]);
    return {add(points[next-1],mul(delta,(at-distances[next-1])/span)),unit(delta),travelled>=length()};
}
RailTravel RailPath::advance(float from,float amount) const {
    require(std::isfinite(from)&&from>=0&&std::isfinite(amount)&&amount>=0,"Invalid rail advance");
    const float start=std::min(from,length()),used=std::min(amount,length()-start);
    RailTravel result;result.distance=start+used;result.remaining=amount-used;result.pose=sample(result.distance);
    auto previous=sample(start).position;
    for(size_t i=1;i<points.size();++i)if(distances[i]>start&&distances[i]<result.distance) {
        result.swept.push_back({previous,points[i]});previous=points[i];
    }
    if(distance(previous,result.pose.position)>.00001f)result.swept.push_back({previous,result.pose.position});
    return result;
}
RailNetwork RailNetwork::fit(const RailLayout &layout,const Box &bounds,float elevation) {
    require(finite(bounds.min)&&finite(bounds.max)&&std::isfinite(elevation)&&
        bounds.max.x>bounds.min.x&&bounds.max.z>bounds.min.z,"Invalid rail world footprint");
    require(layout.width>0&&layout.height>0&&layout.routes.size()==layout.doors.size()&&!layout.routes.empty(),"Uncompiled rail layout");
    RailNetwork result;result.layout=layout.key;result.bounds=bounds;
    result.cellSize={(bounds.max.x-bounds.min.x)/layout.width,0,(bounds.max.z-bounds.min.z)/layout.height};
    auto center=[&](int index){const auto &c=layout.cells.at(size_t(index));return Vector3{
        bounds.min.x+(float(c.x)+.5f)*result.cellSize.x,elevation,bounds.min.z+(float(c.z)+.5f)*result.cellSize.z};};
    auto edge=[&](int index,RailSide side){const auto d=railDirection(side);return add(center(index),{d.x*result.cellSize.x*.5f,0,d.z*result.cellSize.z*.5f});};
    for(const auto &door:layout.doors){result.doors.push_back(edge(door.cell,door.side));result.doorSides.push_back(door.side);}
    std::set<std::pair<int,int>> pits(layout.pitCells.begin(),layout.pitCells.end());
    for(const auto &cell:layout.cells)if(cell.overPit)pits.emplace(cell.x,cell.z);
    for(const auto &[x,z]:pits) {
        const Vector3 c{bounds.min.x+(x+.5f)*result.cellSize.x,elevation,bounds.min.z+(z+.5f)*result.cellSize.z};
        const Vector3 half{result.cellSize.x*.5f,0,result.cellSize.z*.5f};
        auto a=sub(c,half),b=add(c,half);a.y=-3;b.y=0;result.pits.push_back({a,b});
    }
    for(const auto &route:layout.routes) {
        RailPath path;path.entry=route.entry;path.exit=route.exit;
        auto point=[&](Vector3 p){if(path.points.empty()||distance(path.points.back(),p)>.00001f) {
            path.distances.push_back(path.points.empty()?0:path.distances.back()+distance(path.points.back(),p));path.points.push_back(p);
        }};
        for(const auto &step:route.steps) {
            const auto a=edge(step.cell,step.incoming),b=edge(step.cell,step.outgoing),c=center(step.cell);
            point(a);
            if(step.incoming==step.outgoing) {point(c);point(b);} // Explicit stop and reverse.
            else if(opposite(step.incoming)==step.outgoing)point(b);
            else {
                // Quadratic corner lies wholly inside its authored tile. Six
                // segments are shared by the rail mesh and sampled vehicle path.
                for(int n=1;n<=6;++n){const float t=float(n)/6;point(add(add(mul(a,(1-t)*(1-t)),mul(c,2*(1-t)*t)),mul(b,t*t)));}
            }
        }
        require(path.points.size()>=2&&path.length()>0,"Empty world rail path");result.paths.push_back(std::move(path));
    }
    return result;
}
} // namespace dw
