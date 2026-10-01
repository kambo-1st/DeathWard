#include "cinematic/Cinematic.hpp"
#include "raymath.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
int main() {
    auto file=std::filesystem::temp_directory_path()/"deathward-cinematic-test.cinematic";
    try {
        TownDocument scene;
        scene.assets.push_back({"carriage","SM_Veh_Train_Carriage_01",0,1,0,{{-3,0,-1},{3,4,1}}});
        scene.instances.push_back({0,MatrixIdentity(),"carriage",{},"carriage"});
        TownMotionPath rail{"rail",0,1,0,{}};
        for(int x=0;x<200;x+=10) rail.points.push_back({float(x),0,0});
        for(int z=0;z<50;z+=10) rail.points.push_back({200,0,float(z)});
        for(int x=200;x>0;x-=10) rail.points.push_back({float(x),0,50});
        for(int z=50;z>0;z-=10) rail.points.push_back({0,0,float(z)});
        scene.paths.push_back(rail);
        scene.groups.push_back({"carriage","rail",20,4});
        auto sequence=Cinematic::demo(scene,{{0,10,10},{0,0,0},{0,1,0},45,CAMERA_PERSPECTIVE});
        std::string error;
        check(sequence.save(file,error),"sequence saves atomically");
        Cinematic loaded;check(loaded.load(file,error),"sequence loads");
        check(loaded.sounds[0].duration==11&&loaded.cameras[2].anchor=="carriage","sound durations and carriage attachments survive reload");
        CinematicPlayer a,b;
        a.reset(scene,loaded);b.reset(scene,loaded);
        a.play();check(a.takeSounds().size()==1,"time-zero sound delivered once when playback starts");
        a.pause();a.play();check(a.takeSounds().empty(),"resume does not replay time-zero sound");
        a.advance(10);check(a.takeSounds().size()==1,"forward playback delivers crossed wind cue exactly once");
        check(a.animation().pathSpeed()>5,"train moves before the stop cue");
        a.advance(2);check(a.takeSounds().size()==1,"brake cue fires at its scheduled time");
        check(a.animation().pathSpeed()==0,"emergency stop decelerates the train to rest");
        const auto stopped=a.animation().pathDistance();a.advance(4);
        check(a.animation().pathDistance()==stopped,"train remains stopped after braking");
        b.seek(16);check(b.takeSounds().empty(),"scrubbing never plays sounds");
        check(std::abs(a.animation().pathDistance()-b.animation().pathDistance())<.00001,
              "scrubbing and playback produce the same train placement");
        b.seek(4);b.seek(16);
        check(std::abs(a.animation().pathDistance()-b.animation().pathDistance())<.00001,"rewinding does not accumulate simulation state");
        check(distance(a.camera().position,b.camera().position)<.00001,"attached camera follows deterministic train pose");
        check(scene.paths.front().speed==0,"preview overrides leave authored train settings unchanged");
        check(a.storm()>.8f,"weather intensifies on the sequence clock");
        a.seek(6);b.seek(6);
        a.play();check(a.takeSounds().size()==1,"play after a seek resumes the active train loop");
        a.pause();a.play();check(a.takeSounds().empty(),"pause/resume does not duplicate an active loop");
        const auto start=b.camera().position;b.play();b.advance(1);
        check(distance(start,b.camera().position)>1,"interior camera travels with its carriage");
        const auto anchored=*a.anchor("carriage");
        const auto local=Vector3Transform(a.camera().position,MatrixInvert(anchored));
        check(std::abs(local.z)<.001f&&local.y>2,"interior camera stays inside carriage coordinates");
        a.seek(0);a.play();for(int i=0;i<360;++i)a.advance(Tick);b.seek(6);
        check(distance(a.camera().position,b.camera().position)<.001f,"fixed-frame playback matches direct seek");
        auto unsafe=loaded;unsafe.sounds[0].file="../outside.wav";
        check(!unsafe.save(file,error),"sound paths cannot escape the audio asset directory");
        Cinematic intact;check(intact.load(file,error)&&intact.title==loaded.title,"rejected save leaves previous file intact");
        {std::ofstream bad(file);bad<<"DEATHWARD_CINEMATIC 1\ncamera invalid\n";}
        check(!intact.load(file,error)&&intact.cameras.size()==loaded.cameras.size(),"malformed load preserves the current document");
        std::filesystem::remove(file);
        std::cout<<"PASS cinematic persistence, validation, camera anchors, deterministic seeking, emergency stop and timed sound delivery\n";
    }catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';std::filesystem::remove(file);return 1;}
}
