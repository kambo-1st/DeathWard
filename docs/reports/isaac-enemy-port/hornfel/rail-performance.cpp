#include "content/Mechanics.hpp"
#include <chrono>
#include <filesystem>
#include <iostream>
using namespace dw;
using Clock=std::chrono::steady_clock;
double micros(Clock::time_point a,Clock::time_point b){return std::chrono::duration<double,std::micro>(b-a).count();}
void report(const char *label,std::vector<double> times) {
    std::sort(times.begin(),times.end());double sum=0;for(auto value:times)sum+=value;
    std::cout<<label<<" samples="<<times.size()<<" mean_us="<<sum/times.size()<<" p95_us="<<times[times.size()*95/100]<<" max_us="<<times.back()<<'\n';
}
int main() {
    const auto content=defaultMechanics();
    const auto temporary=std::filesystem::temp_directory_path()/("deathward-rail-perf-"+std::to_string(Clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path path;~Cleanup(){std::filesystem::remove_all(path);}} cleanup{temporary};
    std::filesystem::create_directories(temporary);
    for(const auto &f:std::filesystem::directory_iterator(content->directory()))if(f.path().extension()==".mechanics"&&f.path().filename()!="rails.mechanics")
        std::filesystem::copy_file(f.path(),temporary/f.path().filename());
    std::vector<double> baseline,authored;double checksum=0;
    for(int n=0;n<44;++n)for(bool rails:{false,true}) {
        const auto begin=Clock::now();const auto loaded=MechanicsLibrary::load(rails?content->directory():temporary);const auto end=Clock::now();
        if(n>=4)(rails?authored:baseline).push_back(micros(begin,end));
        checksum+=loaded->railLayouts().size();
    }
    report("CONTENT_WITHOUT_RAILS",baseline);report("CONTENT_WITH_15_RAIL_LAYOUTS",authored);
    const auto &layout=*content->railLayout("hornfel_special_5227");
    const auto network=RailNetwork::fit(layout,{{0,0,0},{32.5f,3,35}});
    for(int count:{1,16,128}) {
        std::vector<float> cursors(size_t(count),0);std::vector<double> samples;
        for(int frame=0;frame<2400;++frame) {
            const auto begin=Clock::now();
            for(int n=0;n<count;++n) {
                const auto &path=network.paths[size_t(n)%network.paths.size()];
                auto move=path.advance(cursors[size_t(n)],52*Tick);
                checksum+=move.pose.position.x+move.pose.position.z+move.swept.size();
                cursors[size_t(n)]=move.pose.finished?0:move.distance;
            }
            const auto end=Clock::now();if(frame>=60)samples.push_back(micros(begin,end));
        }
        std::cout<<"RAIL_TRAVERSAL cursors="<<count<<" ";report("CPU_ONLY",samples);
    }
    std::cout<<"checksum="<<checksum<<" render=0 npc_ai=0 wall_door_animation=0\n";
}
