#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "platform/Assets.hpp"
#include "rlgl.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace dw;
namespace {
constexpr Vector3 Spawn{0,.85f,0};
constexpr float BaselineWalkSpeed=6, CandidateWalkSpeed=4.8f;
constexpr Color Paper{236,226,201,255},Panel{26,34,36,248},Teal{112,204,180,255},Gold{224,168,86,255};
void require(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
std::string number(double n,int precision=2){std::ostringstream s;s<<std::fixed<<std::setprecision(precision)<<n;return s.str();}
struct TemporaryDirectory {
    std::filesystem::path path=std::filesystem::temp_directory_path()/
        ("deathward-movement-review-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    TemporaryDirectory(){std::filesystem::create_directories(path);}
    ~TemporaryDirectory(){std::error_code error;std::filesystem::remove_all(path,error);}
};
std::unique_ptr<Game> fixture(const std::filesystem::path &save,std::shared_ptr<const MechanicsLibrary> library,float walkSpeed=BaselineWalkSpeed) {
    auto game=std::make_unique<Game>(save);game->debug=false;game->seedText="42";
    const auto runId=game->campaign.data().nextRunId;
    game->run=std::make_unique<Simulation>(42,runId,game->campaign.data().world,MissionTheme::Mine,false,false,
        WitnessAccount::None,0,ExpeditionPacing::Compact,std::move(library));
    auto &run=*game->run;
    run.arena=Arena{};auto &a=run.arena;a.visualSeed=42;
    a.bounds={{-20,-1,-16},{20,5,16}};a.rooms.resize(1);
    a.floors={{{-20,-.4f,-16},{20,0,16}}};
    a.boundaryWalls={{{-20.5f,0,-16.5f},{20.5f,1,-16}},{{-20.5f,0,16},{20.5f,1,16.5f}},
        {{-20.5f,0,-16},{-20,1,16}},{{20,0,-16},{20.5f,1,16}}};
    auto &room=a.rooms[0];room.bounds=a.bounds;room.center=room.entry=Spawn;room.floors=a.floors;room.kind=RoomKind::Empty;
    room.objective=room.exit={1000,0,1000};a.entrance=Spawn;a.exit=a.miners=a.altar={1000,0,1000};a.rebuildWalls();
    run.rooms.assign(1,{});run.rooms[0].visited=true;
    run.enemies.clear();run.projectiles.clear();run.hazards.clear();run.moneyPickups.clear();
    run.heartPickups.clear();run.blueFlies.clear();run.items.clear();run.stats={};
    run.player=Player{};run.player.attributes.speed=walkSpeed/Player::AcceptedWalkingPace;run.player.position=Spawn;run.player.aim={0,.85f,-10};
    run.room=0;run.roomClear=false;run.debugScenario=true;run.godMode=false;
    run.dead=run.finished=run.floorExitRequested=run.rewardOpen=run.shopOpen=false;
    run.message.clear();run.messageTime=0;run.audioCues.clear();run.checkpointNeeded=false;
    game->campaign.begin(42,"Movement baseline review",ExpeditionPacing::Compact);
    game->screen=Screen::Expedition;game->paused=game->slow=game->sandstorm=false;game->error.clear();
    game->updateCamera(10);
    return game;
}
void key(unsigned type,int code){PlayAutomationEvent({0,type,{code,0,0,0}});}
void releaseKeys(){for(int k:{KEY_W,KEY_A,KEY_S,KEY_D,KEY_SPACE,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT})key(1,k);}
void verify(const TemporaryDirectory &directory,std::shared_ptr<const MechanicsLibrary> library,const std::filesystem::path &output) {
    std::ostringstream rows;rows<<"case,walk_speed,render_fps,simulation_seconds,distance,speed\n";
    int caseId=0;
    // Exercise the ordinary Player default through actual Game input, separate
    // from both explicitly configured A/B fixtures.
    releaseKeys();auto production=fixture(directory.path/"production-default.save",library,Player{}.walkingSpeed());
    key(2,KEY_W);for(int i=0;i<60;++i)production->update(Tick);releaseKeys();
    const auto productionDistance=distance(horizontal(production->run->player.position),horizontal(Spawn));
    require(std::abs(productionDistance-4.8f)<.002,"ordinary expedition default uses accepted 4.8 walking pace");
    rows<<"production_default,"<<production->run->player.walkingSpeed()<<",60,"<<production->run->stats.duration<<','<<productionDistance<<','<<productionDistance/production->run->stats.duration<<'\n';
    for(float walkSpeed:{BaselineWalkSpeed,CandidateWalkSpeed}) {
        for(int fps:{30,60,144})for(bool diagonal:{false,true}) {
            releaseKeys();auto game=fixture(directory.path/(std::to_string(caseId++)+".save"),library,walkSpeed);
            PlayAutomationEvent({0,7,{1120,250,0,0}});
            key(2,KEY_W);if(diagonal)key(2,KEY_D);
            for(int i=0;i<fps*2;++i)game->update(1.f/fps);
            releaseKeys();const auto &run=*game->run;const double elapsed=run.stats.duration;
            const float traveled=distance(horizontal(run.player.position),horizontal(Spawn));
            require(game->error.empty(),"actual Game update succeeds");
            require(run.enemies.empty()&&run.items.empty()&&!run.godMode,"review has no enemies/upgrades/god mode");
            require(std::abs(elapsed-2)<Tick*1.1,"fixed-step elapsed time is within one tick");
            require(std::abs(traveled/elapsed-walkSpeed)<.002,"straight/diagonal walking matches selected speed");
            rows<<(diagonal?"diagonal":"straight")<<','<<walkSpeed<<','<<fps<<','<<std::setprecision(9)<<elapsed<<','<<traveled<<','<<traveled/elapsed<<'\n';
            const auto stopped=run.player.position;game->update(Tick);
            require(distance(stopped,run.player.position)<.0001,"stopping remains immediate; no inertia added");
        }
        // Exercise the existing mouse-to-walk input in the same fixed camera.
        releaseKeys();auto click=fixture(directory.path/("click"+std::to_string(caseId++)+".save"),library,walkSpeed);
        const auto f=unit(horizontal(sub(click->camera.target,click->camera.position)));
        const auto at=GetWorldToScreen(add(Spawn,mul(f,10)),click->camera);
        PlayAutomationEvent({0,7,{int(at.x),int(at.y),0,0}});
        PlayAutomationEvent({0,6,{MOUSE_BUTTON_LEFT,0,0,0}});click->update(Tick);
        PlayAutomationEvent({0,5,{MOUSE_BUTTON_LEFT,0,0,0}});
        for(int i=0;i<59;++i)click->update(Tick);
        require(click->run->moveDestination().has_value(),"mouse click creates the normal movement route");
        require(std::abs(distance(horizontal(click->run->player.position),horizontal(Spawn))/click->run->stats.duration-walkSpeed)<.02,"mouse walking matches keyboard speed");
        releaseKeys();auto game=fixture(directory.path/("dodge"+std::to_string(caseId++)+".save"),library,walkSpeed);
        Hazard hazard;hazard.kind=HazardKind::Creep;hazard.position=Spawn;hazard.delay=0;hazard.duration=1;hazard.radius=50;hazard.damage=10;
        game->run->hazards.push_back(hazard);key(2,KEY_W);key(2,KEY_SPACE);game->update(Tick);key(1,KEY_SPACE);
        require(game->run->player.dodge>0&&game->run->player.hp==6,"normal input retains dodge and its immunity");
        game->run->hazards.clear();
        require(std::abs(distance(horizontal(game->run->player.position),horizontal(Spawn))/Tick-20.4)<.002,"walking candidate does not reduce absolute dodge boost");
        int boosted=1;while(game->run->player.dodge>0&&boosted<60){game->update(Tick);++boosted;}
        const auto dodgeDistance=distance(horizontal(game->run->player.position),horizontal(Spawn));releaseKeys();
        require(boosted==14&&std::abs(dodgeDistance-4.76f)<.002,"dodge duration/distance unchanged");
        rows<<"dodge,"<<walkSpeed<<",60,"<<game->run->stats.duration<<','<<dodgeDistance<<','<<dodgeDistance/game->run->stats.duration<<'\n';
        for(auto pair:std::array<std::pair<int,int>,8>{{{KEY_UP,0},{KEY_UP,KEY_RIGHT},{KEY_RIGHT,0},{KEY_RIGHT,KEY_DOWN},
            {KEY_DOWN,0},{KEY_DOWN,KEY_LEFT},{KEY_LEFT,0},{KEY_LEFT,KEY_UP}}}) {
            releaseKeys();auto direction=fixture(directory.path/("aim"+std::to_string(caseId++)+".save"),library,walkSpeed);
            key(2,pair.first);if(pair.second)key(2,pair.second);direction->update(Tick);releaseKeys();
            require(direction->run->stats.shots==1&&!direction->run->projectiles.empty(),"all eight retained firing directions work");
            const auto &shot=direction->run->projectiles.front();
            require(shot.attack.damage==24&&shot.attack.speed==8&&std::abs(shot.attack.maxDistance-11)<.0001,"accepted damage/shot speed/range preserved");
        }
    }
    // Confirm the immunity test actually supplied damaging creep.
    releaseKeys();auto exposed=fixture(directory.path/"exposed.save",library);
    Hazard hazard;hazard.kind=HazardKind::Creep;hazard.position=Spawn;hazard.delay=0;hazard.duration=1;hazard.radius=50;hazard.damage=10;
    exposed->run->hazards.push_back(hazard);exposed->update(Tick);require(exposed->run->player.hp==5,"creep harms the same unprotected baseline");
    if(!output.empty()) {if(!output.parent_path().empty())std::filesystem::create_directories(output.parent_path());std::ofstream file(output);file<<rows.str();require(bool(file),"save review measurements");}
    std::cout<<rows.str()<<"PASS walking A/B: 6 baseline / 4.8 candidate; 30/60/144 partitions; mouse+keyboard; no diagonal boost or inertia; dodge20.4, immunity and eight-direction firing retained. 4.8 pace human-selected and enabled by default; exact native speed remains unverified.\n";
}

struct Sample {
    bool armed=false,recording=false,complete=false;
    double elapsed=0,wall=0,path=0;
    void update(double dt,double actualWall,float traveled) {
        if(armed&&!recording&&traveled>.0001f){recording=true;armed=false;}
        if(!recording)return;
        elapsed+=dt;wall+=actualWall;path+=traveled;
        if(elapsed>=2){recording=false;complete=true;}
    }
};
void drawGuides(const Camera3D &camera) {
    BeginMode3D(camera);
    for(int x=-18;x<=18;x+=2)DrawLine3D({float(x),.02f,-16},{float(x),.02f,16},Color{133,123,96,130});
    for(int z=-14;z<=14;z+=2)DrawLine3D({-20,.02f,float(z)},{20,.02f,float(z)},Color{133,123,96,130});
    DrawLine3D({-18,.03f,0},{18,.03f,0},Teal);DrawLine3D({0,.03f,-14},{0,.03f,14},Teal);
    DrawCircle3D({0,.04f,0},12,{1,0,0},90,Gold);
    EndMode3D();
}
void overlay(const Game &game,const Sample &sample,double speed,bool pinned,bool candidate) {
    const float sx=GetScreenWidth()/1280.f,sy=GetScreenHeight()/800.f;
    const auto rect=[&](float x,float y,float w,float h){DrawRectangleRec({x*sx,y*sy,w*sx,h*sy},Panel);};
    const auto text=[&](const std::string &value,float x,float y,int size,Color color=Paper){DrawText(value.c_str(),int(x*sx),int(y*sy),std::max(10,int(size*sy)),color);};
    rect(24,24,350,58);text(candidate?"WALKING CANDIDATE":"ACCEPTED BASELINE",38,34,20,candidate?Gold:Teal);text(candidate?"20% slower walk / playtest value only":"Original 6.00 walking speed",38,61,12);
    rect(380,24,526,102);text("Live speed "+number(speed)+" units/s",394,36,19);
    text("Walk "+number(game.run->player.walkingSpeed())+"   |   dodge 20.40   |   no inertia added",394,62,13);
    text(std::string("Camera: ")+(pinned?"pinned":"follows player")+"   zoom "+number(game.cameraZoomPercent(),0)+"%",394,87,14);
    rect(964,22,292,140);text("WALKING A/B CHECK",978,35,18,Gold);
    text("WASD / click: move",978,65,14);text("Arrows or RMB: fire",978,88,14);text("Space: dodge   H: controls",978,111,14);text("Q/R or middle drag: camera",978,134,12);
    rect(24,90,350,132);text("F8  Reset room / camera",38,102,16);text("F11  Pin / follow camera",38,129,16);text("F7  Arm a 2-second travel sample",38,156,14);
    std::string result=sample.recording?"Recording...":sample.armed?"Ready: start moving":sample.complete?
        number(sample.path)+" units in "+number(sample.elapsed)+" sim s":"No travel sample yet";
    text(result,38,185,14,Teal);
    if(sample.complete)text("Mean "+number(sample.path/sample.elapsed)+" u/s | active wall "+number(sample.wall)+"s (includes stops/dodge)",394,112,12,Teal);
    rect(964,365,292,112);text("1  Baseline: walk 6.00",978,377,14,Teal);text("2  Candidate: walk 4.80",978,400,14,Gold);text("Switch resets the room/camera",978,425,12);text("Grid 2 | gold radius 12 units",978,450,12);
}
}
int main(int argc,char **argv) {
    bool verification=false,candidate=false;int frames=0;std::filesystem::path capture,measurements,mechanics;
    try {
        for(int i=1;i<argc;++i){std::string arg=argv[i];
            if(arg=="--verify")verification=true;
            else if(arg=="--candidate")candidate=true;
            else if(arg=="--capture"&&i+1<argc)capture=argv[++i];
            else if(arg=="--measurements"&&i+1<argc)measurements=argv[++i];
            else if(arg=="--mechanics"&&i+1<argc)mechanics=argv[++i];
            else if(arg=="--frames"&&i+1<argc){frames=std::stoi(argv[++i]);require(frames>0,"--frames must be positive");}
            else if(arg=="--help") {std::cout<<"Walking speed A/B: interactive by default; 1 baseline, 2 candidate.\nF8 reset; F11 camera pin/follow; F7 record travel; existing game controls retained.\n--candidate: start at 20% slower walking (playtest, not verified Isaac speed)\n--verify --measurements PATH: actual Game/input checks\n--frames N --capture PATH: rendering inspection only\n--mechanics PATH: explicit immutable mechanics snapshot\n";return 0;}
            else throw std::runtime_error("Unknown or incomplete option: "+arg);
        }
        require(capture.empty()||frames>0,"--capture requires --frames; ordinary launch stays interactive");
        SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_RESIZABLE|(verification?FLAG_WINDOW_HIDDEN:0));
        InitWindow(1440,900,"DeathWard | Walking speed A/B");require(IsWindowReady(),"graphics window available");SetExitKey(KEY_NULL);SetTargetFPS(verification||frames?0:60);
        if(mechanics.empty()) {
            const auto snapshot=std::filesystem::path(GetApplicationDirectory())/"movement-review-mechanics";
            mechanics=std::filesystem::exists(snapshot)?snapshot:sourceAssetDirectory()/"mechanics";
        }
        auto library=MechanicsLibrary::load(mechanics);TemporaryDirectory temporary;
        if(verification){verify(temporary,library,measurements);CloseWindow();return 0;}
        {
            int reset=0;auto game=fixture(temporary.path/(std::to_string(reset)+".save"),library,candidate?CandidateWalkSpeed:BaselineWalkSpeed);Renderer renderer;
            Camera3D camera=game->camera;bool pinned=true;Sample sample;double liveSpeed=0;
            for(int frame=0;!WindowShouldClose()&&!game->quit&&(!frames||frame<frames);++frame) {
                const bool baselinePressed=IsKeyPressed(KEY_ONE),candidatePressed=IsKeyPressed(KEY_TWO);
                if(baselinePressed)candidate=false;
                if(candidatePressed)candidate=true;
                if(IsKeyPressed(KEY_F8)||baselinePressed||candidatePressed) {
                    game=fixture(temporary.path/(std::to_string(++reset)+".save"),library,candidate?CandidateWalkSpeed:BaselineWalkSpeed);
                    camera=game->camera;pinned=true;sample={};liveSpeed=0;
                }
                if(IsKeyPressed(KEY_F11))pinned=!pinned;
                if(IsKeyPressed(KEY_F7)){sample={};sample.armed=true;}
                const auto position=game->run->player.position;const auto before=game->run->stats.duration;
                const float dt=frames?Tick:GetFrameTime();
                game->update(dt,[&](const Simulation &run,const Camera3D &view,Ray ray){return renderer.pickScenery(run,view,ray);});
                require(game->error.empty(),game->error.c_str());
                if(game->screen!=Screen::Expedition)break;
                const auto elapsed=game->run->stats.duration-before;
                const auto traveled=distance(horizontal(position),horizontal(game->run->player.position));
                if(elapsed>0){liveSpeed=traveled/elapsed;sample.update(elapsed,dt,traveled);}
                if(pinned){const auto offset=sub(game->camera.position,game->camera.target);game->camera.target=camera.target;game->camera.position=add(camera.target,offset);}
                BeginDrawing();const auto action=renderer.draw(*game);
                // Confine measurement guides to the play area, leaving the
                // original controls and overlays unobscured.
                if(!game->paused&&!game->controlsOpen&&!game->buildOpen) {
                    BeginScissorMode(0,int(222*GetScreenHeight()/800.f),int(964*GetScreenWidth()/1280.f),int(452*GetScreenHeight()/800.f));
                    drawGuides(game->camera);EndScissorMode();
                }
                if(!game->paused&&!game->controlsOpen&&!game->buildOpen)overlay(*game,sample,liveSpeed,pinned,candidate);
                if(frames&&frame==frames-1&&!capture.empty()) {
                    rlDrawRenderBatchActive();auto picture=LoadImageFromScreen();
                    if(!capture.parent_path().empty())std::filesystem::create_directories(capture.parent_path());
                    require(ExportImage(picture,capture.string().c_str()),"save review capture");UnloadImage(picture);
                }
                EndDrawing();game->perform(action);
            }
            renderer.unload();
        }
        CloseWindow();return 0;
    }catch(const std::exception &error){std::cerr<<"Movement review: "<<error.what()<<'\n';if(IsWindowReady())CloseWindow();return 1;}
}
