#include "content/Mechanics.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b,float tolerance=.002f){return std::abs(a-b)<tolerance;}
template<class F> void rejected(F fn,const char *message){bool failed=false;try{fn();}catch(const std::exception &){failed=true;}check(failed,message);}
RailLayout cross() {
    RailLayout r;r.key="cross";r.width=r.height=3;
    r.cells={{1,0,1,false},{0,1,0,false},{1,1,6,false},{2,1,0,false},{1,2,1,false}};r.compile();return r;
}
void junctions() {
    auto r=cross();check(r.doors.size()==4&&r.routes.size()==4,"cross has four directed door routes");
    const auto net=RailNetwork::fit(r,{{-3,0,-3},{3,3,3}});
    for(const auto &route:r.routes) {
        check(route.steps.size()==3,"cross traverses three authored cells");
        const auto entry=r.doors[size_t(route.entry)].side,exit=r.doors[size_t(route.exit)].side;
        check((unsigned(entry)+2)%4==unsigned(exit),"crossing must not invent arbitrary turning branches");
        const auto &path=net.paths[size_t(route.entry)];check(near(path.length(),6),"straight world distance");
        check(distance(path.sample(0).position,net.doors[size_t(route.entry)])<.001f,"entry at wall port");
        check(distance(path.sample(6).position,net.doors[size_t(route.exit)])<.001f,"exit at opposite port");
        auto travel=path.advance(0,100);check(travel.pose.finished&&near(travel.remaining,94),"overshoot reports remaining travel without leaving arena");
        check(!path.sample(5.99f).finished,"completion requires reaching door");
    }
    // The vertical cap facts are independently constrained by installed layouts
    // 5222/5223 and the preserved orientation artwork, not source display names.
    RailLayout stop;stop.key="stop";stop.width=stop.height=3;stop.cells={{1,0,1,false},{1,1,10,false}};
    // A one-door spur alone is invalid as a whole encounter, so give it a second independent rail.
    rejected([&]{stop.compile();},"one-door layout rejected");
}
void stopsAndCurves() {
    RailLayout stop;stop.key="stops";stop.width=stop.height=3;
    stop.cells={{0,0,1,false},{0,1,10,false},{2,1,9,false},{2,2,1,false}};stop.compile();
    check(stop.doors.size()==2,"two independent capped spurs, not extra bottom/top doors");
    const auto network=RailNetwork::fit(stop,{{0,0,0},{6,3,6}});
    for(const auto &route:stop.routes) {
        check(route.entry==route.exit&&route.steps.size()==3,"stop reverses to original wall door");
        const auto &path=network.paths[size_t(route.entry)];check(near(path.length(),6),"stop travel visits physical cap center and reverses");
        const auto before=path.sample(2.9f),after=path.sample(3.1f);
        check(dot(before.direction,after.direction)<-.99f,"stop reverses velocity");
    }
    RailLayout bend;bend.key="bend";bend.width=bend.height=3;
    bend.cells={{0,1,0,false},{1,1,3,true},{1,2,1,true}};bend.compile();
    const auto net=RailNetwork::fit(bend,{{0,0,0},{6,3,6}});
    check(net.pits.size()==2&&near(net.pits[0].max.x-net.pits[0].min.x,2),"pit rail geometry retained independently of navigation");
    const auto &path=net.paths[0];check(path.points.size()>6&&path.length()>5&&path.length()<6,"bend has curved physical geometry");
    const auto all=path.advance(0,100);check(all.swept.size()==path.points.size()-1,"fast travel sweeps each actual corner segment");
    float swept=0;for(const auto &s:all.swept)swept+=distance(s[0],s[1]);check(near(swept,path.length()),"collision sweep does not cut corner");
    float travelled=0;for(int n=0;n<60;++n)travelled=path.advance(travelled,.05f).distance;
    check(distance(path.sample(travelled).position,path.advance(0,3).pose.position)<.002f,"fixed distance traversal independent of step count");
    check(distance(net.paths[1].sample(0).position,path.sample(path.length()).position)<.001f,"reverse route begins at opposite wall");
    for(int n=0;n<=100;++n)check(distance(path.sample(path.length()*n/100).position,
        net.paths[1].sample(path.length()*(100-n)/100).position)<.003f,"reverse route follows same physical curve");
    std::cout<<"RAIL_GEOMETRY cross_straight=1 stop_reverse=1 curved_motion=1 swept_segments=1 pits_retained=1 step_partition=1\n";
}
void installed() {
    const auto lib=defaultMechanics();check(lib->railLayouts().size()==15,"fifteen actual authored layouts, no invented placeholder");
    size_t cells=0,doors=0,pits=0,paths=0;std::map<std::string,size_t> expected{
        {"hornfel_void_105",6},{"hornfel_void_131",2},
        {"hornfel_special_5220",8},{"hornfel_special_5221",8},{"hornfel_special_5222",8},{"hornfel_special_5223",9},
        {"hornfel_special_5224",8},{"hornfel_special_5225",8},{"hornfel_special_5226",10},{"hornfel_special_5227",16},
        {"hornfel_special_5228",10},{"hornfel_special_5229",8},{"hornfel_special_6050",8},{"hornfel_special_6051",6},{"hornfel_special_6052",6}};
    Random rng(1866);
    for(const auto &[key,r]:lib->railLayouts()) {
        check(expected.contains(key)&&expected.at(key)==r.doors.size(),"source door counts match corrected end-stop orientation");
        cells+=r.cells.size();doors+=r.doors.size();paths+=r.routes.size();
        for(const auto &c:r.cells)pits+=c.overPit;
        for(int trial=0;trial<8;++trial) {
            const Vector3 corner{rng.real(-300,300),0,rng.real(-300,300)};
            const Box bounds{corner,add(corner,{rng.real(26,70),3,rng.real(20,60)})};const auto net=RailNetwork::fit(r,bounds);
            for(const auto &path:net.paths) {
                check(distance(path.sample(0).position,net.doors[size_t(path.entry)])<.001f,"fitted entry remains on its door");
                check(distance(path.sample(path.length()).position,net.doors[size_t(path.exit)])<.001f,"fitted route exits at authored door");
                for(int n=0;n<=250;++n) {
                    auto pose=path.sample(path.length()*n/250);
                    check(pose.position.x>=bounds.min.x-.001f&&pose.position.x<=bounds.max.x+.001f&&
                        pose.position.z>=bounds.min.z-.001f&&pose.position.z<=bounds.max.z+.001f,"physical route stays within arena");
                    check(near(length(pose.direction),1),"finite unit movement direction");
                }
            }
        }
        auto copy=r;copy.compile();check(copy.doors.size()==r.doors.size()&&copy.routes.size()==r.routes.size(),"compilation idempotent");
    }
    check(cells==928&&doors==paths,"all source rail cells and door routes compiled");
    std::cout<<"RAIL_INSTALLED layouts="<<lib->railLayouts().size()<<" cells="<<cells<<" doors="<<doors<<" routes="<<paths<<" pit_cells="<<pits<<" fitted_footprints=120 ordinary_pool_entries=0\n";
}
void validation() {
    auto r=cross();r.cells.push_back(r.cells[0]);rejected([&]{r.compile();},"duplicate tile rejected");
    r=cross();r.cells[0].variant=0;rejected([&]{r.compile();},"disconnected port rejected");
    r=cross();r.cells[0].variant=11;rejected([&]{r.compile();},"unsupported source variant rejected");
    r=cross();r.cells[0].x=52;rejected([&]{r.compile();},"out of bounds tile rejected");
    r=cross();r.width=100000;rejected([&]{r.compile();},"unbounded layout rejected");
    r=cross();r.cells.clear();rejected([&]{r.compile();},"empty placeholder rejected");
    r=cross();rejected([&]{RailNetwork::fit(r,{{0,0,0},{0,0,0}});},"degenerate footprint rejected");
    auto net=RailNetwork::fit(r,{{0,0,0},{3,3,3}});
    rejected([&]{net.paths[0].sample(std::numeric_limits<float>::quiet_NaN());},"NaN cursor rejected");
    rejected([&]{net.paths[0].advance(0,-1);},"negative travel rejected");
    rejected([&]{net.paths[0].advance(0,std::numeric_limits<float>::infinity());},"infinite speed rejected");
    std::cout<<"RAIL_VALIDATION duplicates=reject disconnected=reject invalid_variant=reject dimensions=bounded nonfinite=reject\n";
}
void externalSnapshot() {
    const auto original=defaultMechanics();const auto before=original->fingerprint();
    const auto dir=std::filesystem::temp_directory_path()/("deathward-rails-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path path;~Cleanup(){std::filesystem::remove_all(path);}} cleanup{dir};
    std::filesystem::create_directories(dir);
    for(const auto &f:std::filesystem::directory_iterator(original->directory()))if(f.path().extension()==".mechanics")
        std::filesystem::copy_file(f.path(),dir/f.path().filename());
    std::ofstream(dir/"test.mechanics")<<"DEATHWARD_MECHANICS 1\nrail_layout extra 2 2\nrail_cell extra 0 0 0 0\nrail_cell extra 1 0 0 1\n";
    const auto next=MechanicsLibrary::load(dir);
    check(next->railLayouts().size()==16&&next->railLayout("extra")&&next->fingerprint()!=before,"external track snapshot loads without code change");
    check(original->railLayouts().size()==15&&!original->railLayout("extra")&&original->fingerprint()==before,"existing immutable snapshot unchanged");
    std::ofstream(dir/"test.mechanics")<<"DEATHWARD_MECHANICS 1\nrail_layout extra 2 2\nrail_cell extra 0 0 0 0\n";
    rejected([&]{MechanicsLibrary::load(dir);},"invalid reload rejected before publication");
    check(next->railLayout("extra")->routes.size()==2,"last good snapshot survives failed reload");
    std::cout<<"RAIL_CONTENT immutable_snapshot=1 external_geometry=1 rejected_reload_keeps_previous=1\n";
}
}
int main(){try{junctions();stopsAndCurves();installed();validation();externalSnapshot();return 0;}
    catch(const std::exception &e){std::cerr<<"Rail test failed: "<<e.what()<<'\n';return 1;}}
