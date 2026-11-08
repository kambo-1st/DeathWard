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

constexpr Color Paper{236,226,201,255},Panel{26,34,36,248},Teal{112,204,180,255},Gold{224,168,86,255};
void require(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
std::string number(double n,int precision=2){std::ostringstream s;s<<std::fixed<<std::setprecision(precision)<<n;return s.str();}
struct TemporaryDirectory {
    std::filesystem::path path=std::filesystem::temp_directory_path()/
        ("deathward-movement-review-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    TemporaryDirectory(){std::filesystem::create_directories(path);}
    ~TemporaryDirectory(){std::error_code error;std::filesystem::remove_all(path,error);}
};
std::unique_ptr<Game> fixture(const std::filesystem::path &save,std::shared_ptr<const MechanicsLibrary> library,bool candidate=false,bool open=true,float shotSpeed=8) {
    auto game=std::make_unique<Game>(save);game->debug=false;game->seedText="42";
    const auto runId=game->campaign.data().nextRunId;
    game->run=std::make_unique<Simulation>(42,runId,game->campaign.data().world,MissionTheme::Mine,false,false,
        WitnessAccount::None,0,ExpeditionPacing::Compact,std::move(library));
    auto &run=*game->run;
    run.arena=Arena{};auto &a=run.arena;a.visualSeed=42;
    a.bounds={{-100,-1,-100},{100,5,100}};a.rooms.resize(1);
    a.floors={{{-100,-.4f,-100},{100,0,100}}};
    a.boundaryWalls={};
    if(!open) {
        a.bounds={{-12,-1,-12},{12,5,12}};a.floors={{{-12,-.4f,-12},{12,0,12}}};
        a.boundaryWalls={{{-12.5f,0,-12.5f},{12.5f,2,-12}},{{-12.5f,0,12},{12.5f,2,12.5f}},
            {{-12.5f,0,-12},{-12,2,12}},{{12,0,-12},{12.5f,2,12}}};
    }
    auto &room=a.rooms[0];room.bounds={{-12,-1,-12},{12,5,12}};room.center=room.entry=Spawn;room.floors=a.floors;room.kind=RoomKind::Empty;
    room.objective=room.exit={1000,0,1000};a.entrance=Spawn;a.exit=a.miners=a.altar={1000,0,1000};a.rebuildWalls();
    run.rooms.assign(1,{});run.rooms[0].visited=true;
    run.enemies.clear();run.projectiles.clear();run.hazards.clear();run.moneyPickups.clear();
    run.heartPickups.clear();run.blueFlies.clear();run.items.clear();run.stats={};
    run.player=Player{};run.canonicalShooting=candidate;run.player.attributes.shotSpeed=shotSpeed/8.f;run.player.attributes.speed=1;run.player.position=Spawn;run.player.aim={0,.85f,-10};
    run.room=0;run.roomClear=false;run.debugScenario=true;run.godMode=false;
    run.dead=run.finished=run.floorExitRequested=run.rewardOpen=run.shopOpen=false;
    run.message.clear();run.messageTime=0;run.audioCues.clear();run.checkpointNeeded=false;
    game->campaign.begin(42,"Projectile A/B review",ExpeditionPacing::Compact);
    game->screen=Screen::Expedition;game->paused=game->slow=game->sandstorm=false;game->error.clear();
    game->updateCamera(10);
    return game;
}
void key(unsigned type,int code){PlayAutomationEvent({0,type,{code,0,0,0}});}
void releaseKeys(){for(int k:{KEY_W,KEY_A,KEY_S,KEY_D,KEY_SPACE,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT})key(1,k);}
void nativeFlightCheck() {
    std::ifstream file(sourceAssetDirectory().parent_path()/"docs/reports/isaac-first-floor-parity/player-tears/native-flight.csv");
    require(bool(file),"native flight fixture available");
    std::string line;std::getline(file,line);int rows=0;
    while(std::getline(file,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream row(line);
        uint32_t rng;int invocation,grounded;float before,fallBefore,after,fallAfter;
        require(bool(row>>rng>>invocation>>before>>fallBefore>>after>>fallAfter>>grounded),"parse independent native row");
        PlayerTearFlight flight;flight.height=before;flight.fallingSpeed=fallBefore;
        require(sourceTearGrounded(flight)==bool(grounded),"native floor boundary");
        if(!grounded)sourceTearFlightFrame(flight);
        require(std::abs(flight.height-after)<.00003f&&std::abs(flight.fallingSpeed-fallAfter)<.000003f,"171 native flight states match");
        if(invocation==0)require(std::abs(sourceTearBirthFallingSpeed(rng)-fallBefore)<.000003f,"native birth RNG conversion");
        ++rows;
    }
    require(rows==171,"complete independent native flight fixture");
}
EntityId target(Simulation &run,Vector3 position,float health=1000) {
    Enemy e;e.id=100000+run.enemies.size();e.monster={12,0,0};e.kind=EnemyKind::Monster;
    e.position=position;e.hp=e.maxHp=health;e.radius=.65f;e.alive=true;
    run.enemies.push_back(e);require(run.applyEnemyStatus(e.id,EnemyStatus::Freeze,-18000),"review target must actually be frozen");
    return e.id;
}
void verify(const TemporaryDirectory &directory,std::shared_ptr<const MechanicsLibrary> library,const std::filesystem::path &output) {
    nativeFlightCheck();require(std::abs(Player{}.walkingSpeed()-4.8f)<.0001,"accepted walking default preserved");
    std::ostringstream rows;rows<<"mode,input_fps,direction,last_observed_distance,observed_alive_seconds,launch_speed\n";
    int count=0;
    const std::array<std::pair<int,int>,8> directions{{{KEY_UP,0},{KEY_UP,KEY_RIGHT},{KEY_RIGHT,0},{KEY_RIGHT,KEY_DOWN},
        {KEY_DOWN,0},{KEY_DOWN,KEY_LEFT},{KEY_LEFT,0},{KEY_LEFT,KEY_UP}}};
    for(bool candidate:{false,true})for(int fps:{30,60,144})for(auto keys:directions) {
        releaseKeys();auto game=fixture(directory.path/(std::to_string(count++)+".save"),library,candidate);
        key(2,keys.first);if(keys.second)key(2,keys.second);
        // One fixed tick uses the real eight-direction Game firing producer.
        game->update(Tick);releaseKeys();require(game->run->projectiles.size()==1,"one ordinary projectile per trigger");
        auto p=game->run->projectiles.front();const float launchSpeed=length(p.velocity);
        require(std::abs(launchSpeed-(candidate?8.f:26.f))<.001,"selected launch speed");
        require(p.damage==24&&p.radius==.14f,"damage and hit radius preserved");
        require(bool(p.playerFlight)==candidate,"candidate flight is isolated from normal bullets");
        int updates=0;while(!game->run->projectiles.empty()&&updates++<fps*5) {
            p=game->run->projectiles.front();game->update(1.f/fps);
        }
        require(game->run->projectiles.empty(),"projectile terminates in open space");
        require(p.traveled>(candidate?10.1f:81.f)&&p.traveled<(candidate?11.01f:84.f),"bounded actual reach across all eight directions and input partitions");
        rows<<(candidate?"candidate":"baseline")<<','<<fps<<','<<keys.first<<'+'<<keys.second<<','<<p.traveled<<','<<game->run->stats.duration<<','<<launchSpeed<<'\n';
    }
    // Direct primary inputs test positive/transverse inheritance and removing
    // only backward contribution. Movement remains immediate, without glide.
    for(Vector3 move:std::array<Vector3,3>{{{0,0,-1},{1,0,0},{0,0,1}}}) {
        auto game=fixture(directory.path/("inherit"+std::to_string(count++)+".save"),library,true);
        auto &run=*game->run;Input in;in.movement=move;run.step(in);
        in.fire=true;in.aimDirection=Vector3{0,0,-1};in.aim={0,.85f,-50};run.step(in);
        require(run.projectiles.size()==1,"moving primary emits once");
        const auto v=run.projectiles.front().velocity;
        if(move.z<0)require(std::abs(length(v)-10.88f)<.002,"forward walking contributes 2.88 units/s");
        if(move.x>0)require(std::abs(v.x-2.88f)<.02,"transverse walking survives inheritance");
        if(move.z>0)require(std::abs(v.z+8)<.002,"backward contribution removed");
    }
    for(bool candidate:{false,true})for(float range:{6.f,9.f,10.5f,11.8f})for(bool wall:{false,true}) {
        auto game=fixture(directory.path/("hit"+std::to_string(count++)+".save"),library,candidate);auto &run=*game->run;
        auto id=target(run,{0,.85f,-range});
        if(wall)run.arena.walls={{{-2,0,-4.3f},{2,3,-4}}};
        Input in;in.fire=true;in.aimDirection=Vector3{0,0,-1};in.aim={0,.85f,-50};run.step(in);
        for(int n=0;n<250;++n)run.step({});
        const auto *enemy=run.findEnemy(id);require(enemy,"target remains available");
        const bool hit=enemy->hp<1000;
        if(!hit)require(distance(horizontal(enemy->position),Vector3{0,0,-range})<.001,"unhit range witness stays stationary");
        if(hit!=(!wall&&(!candidate||range<11.8f)))
            std::cerr<<"target mismatch: candidate="<<candidate<<" range="<<range<<" wall="<<wall<<" hp="<<enemy->hp<<" z="<<enemy->position.z<<'\n';
        require(hit==(!wall&&(!candidate||range<11.8f)),"short/medium/far/out-of-range target and intervening wall behavior");
    }
    for(bool candidate:{false,true}) {
        auto game=fixture(directory.path/(candidate?"kill-candidate.save":"kill-baseline.save"),library,candidate);
        auto &run=*game->run;auto id=target(run,{0,.85f,-6},48);
        Input in;in.fire=true;in.aim={0,.85f,-50};run.step(in);
        for(int n=0;n<80;++n)run.step({});
        require(run.findEnemy(id)&&std::abs(run.findEnemy(id)->hp-24)<.001,"interactive target survives first normal shot with 24 HP");
        run.step(in);for(int n=0;n<80;++n)run.step({});
        require(!run.findEnemy(id)||!run.findEnemy(id)->alive,"interactive target dies to two normal shots in either mode");
    }
    // Flight speed must not change canonical Tears emission count or reach.
    for(float shotSpeed:{3.f,5.f,8.f,10.f,11.f,12.f})for(int fps:{30,60,144}) {
        releaseKeys();auto game=fixture(directory.path/("stream"+std::to_string(int(shotSpeed))+"-"+std::to_string(fps)+".save"),library,true,false,shotSpeed);
        int peak=0;float maxDistance=0;key(2,KEY_UP);
        const int seconds=8;
        for(int n=0;n<fps*seconds;++n) {
            game->update(1.f/fps);peak=std::max(peak,int(game->run->projectiles.size()));
            for(const auto &p:game->run->projectiles) {
                maxDistance=std::max(maxDistance,p.traveled);
                require(p.traveled<=11.0001f,"shot never exceeds half-room minus one unit");
                require(std::abs(length(p.velocity)-shotSpeed)<.001,"actual Game uses chosen 3/5/8/10/11/12 launch speed");
                require(p.damage==24&&p.radius==.14f&&p.attack.life>=11.f/shotSpeed,"pace choices preserve damage/radius and allow full travel time");
            }
        }
        releaseKeys();require(peak>=3,"no renderer-only or artificial three-shot cap");
        require(maxDistance>11.f-shotSpeed*Tick*2.1f,"every pace reaches the same half-room boundary within observation sampling");
        require(game->run->stats.shots==22,"all flight speeds keep the same canonical Tears emission count");
        rows<<"speed_choice_"<<int(shotSpeed)<<','<<fps<<",sustained_peak_"<<peak<<','<<maxDistance<<','<<game->run->stats.duration<<','<<shotSpeed<<'\n';
    }
    for(float pace:{3.f,5.f,8.f})for(Vector3 direction:std::array<Vector3,3>{{{1,0,0},{0,0,-1},{.70710678f,0,.70710678f}}}) {
        auto game=fixture(directory.path/("reach"+std::to_string(count++)+".save"),library,true,false,pace);
        auto &run=*game->run;Input in;in.fire=true;in.aimDirection=direction;run.step(in);
        float terminal=0;for(int n=0;n<300;++n){for(const auto &p:run.projectiles)terminal=std::max(terminal,p.traveled);run.step({});}
        require(terminal<=11.0001f&&11-terminal<pace*Tick*1.1f,"each pace reaches the same boundary within one observation tick");
    }
    // Changing one canonical stat must leave the other two consumers intact.
    for(int preset=0;preset<4;++preset)for(int fps:{30,60,144}) {
        releaseKeys();auto game=fixture(directory.path/("independent"+std::to_string(preset)+"-"+std::to_string(fps)+".save"),library,true);
        auto &stats=game->run->player.attributes;
        if(preset==1)stats.tearsPerSecond*=2;
        if(preset==2)stats.shotSpeed*=1.5f;
        if(preset==3)stats.rangeTiles*=2;
        const float expectedSpeed=preset==2?12.f:8.f,expectedRange=preset==3?22.f:11.f;
        float observed=0;key(2,KEY_UP);
        for(int n=0;n<fps*8;++n){
            game->update(1.f/fps);
            for(const auto &p:game->run->projectiles){
                require(std::abs(p.attack.speed-expectedSpeed)<.001,"only Shot Speed changes launch speed");
                require(std::abs(p.attack.maxDistance-expectedRange)<.001,"only Range changes reach");
                require(p.traveled<=expectedRange+.0001f,"reach obeys its own stat, not room size or a fixed cap");
                observed=std::max(observed,p.traveled);
            }
        }
        releaseKeys();require(game->run->stats.shots==uint64_t(preset==1?44:22),"only Tears changes emission count");
        require(expectedRange-observed<expectedSpeed*Tick*2.1f,"all stat combinations can traverse their full configured reach");
        rows<<"independent_preset_"<<preset<<','<<fps<<",shots_"<<game->run->stats.shots<<','<<observed<<','<<game->run->stats.duration<<','<<expectedSpeed<<'\n';
    }
    for(int disabled=0;disabled<3;++disabled){
        auto game=fixture(directory.path/("disabled"+std::to_string(disabled)+".save"),library,true);
        auto &stats=game->run->player.attributes;
        if(disabled==0)stats.tearsPerSecond=0;if(disabled==1)stats.shotSpeed=0;if(disabled==2)stats.rangeTiles=0;
        Input fire;fire.fire=true;fire.aimDirection=Vector3{0,0,-1};
        for(int n=0;n<120;++n)game->run->step(fire);
        require(game->run->stats.shots==0,"disabled shooting does not divide by zero or emit unbounded stationary shots");
    }
    auto idle=fixture(directory.path/"idle-fire.save",library,true);
    for(int n=0;n<300;++n)idle->run->step({});
    Input trigger;trigger.fire=true;trigger.aimDirection=Vector3{0,0,-1};idle->run->step(trigger);
    require(idle->run->stats.shots==1,"idle time cannot bank a firing burst");
    // Moving/dodging fire must obey the distance cap even with inheritance.
    auto capped=fixture(directory.path/"cap.save",library,true,false);auto &cap=*capped->run;
    cap.player.velocity={20.4f,0,0};Input capInput;capInput.fire=true;capInput.aimDirection=Vector3{1,0,0};cap.step(capInput);
    for(int n=0;n<80;++n){for(const auto &p:cap.projectiles)require(p.traveled<=11.0001f,"inherited shot cannot exceed room-relative cap");cap.step({});}
    releaseKeys();auto dodge=fixture(directory.path/"dodge.save",library,true);auto &run=*dodge->run;
    Hazard hazard;hazard.kind=HazardKind::Creep;hazard.position=Spawn;hazard.delay=0;hazard.duration=1;hazard.radius=50;hazard.damage=10;run.hazards.push_back(hazard);
    Input in;in.movement={1,0,0};in.dodge=true;run.step(in);
    require(run.player.hp==6&&std::abs(distance(run.player.position,Spawn)/Tick-20.4f)<.002,"universal dodge speed and immunity preserved");
    require(Simulation(42,1,{},MissionTheme::Mine).canonicalShooting,"normal expeditions now use the accepted canonical shooting default");
    if(!output.empty()){std::ofstream file(output);file<<rows.str();require(bool(file),"write measurements");}
    std::cout<<rows.str()<<"PASS native flight 171 states; actual eight-direction Game shots at 30/60/144 input partitions; inheritance; near/medium/far targets; walls; dodge. Human candidate acceptance pending.\n";
}
constexpr Vector3 ReviewSpawn{-8,.85f,0};
const std::array<const char *,4> PresetNames{"Base build","Quicker firing","Faster travel","Longer reach"};
void setup(Game &game,int preset,int targetChoice) {
    auto &run=*game.run;run.player.position=ReviewSpawn;run.player.aim=add(ReviewSpawn,{10,0,0});
    if(preset==1)run.player.attributes.tearsPerSecond*=2;
    if(preset==2)run.player.attributes.shotSpeed*=1.5f;
    if(preset==3)run.player.attributes.rangeTiles*=2;
    if(targetChoice)target(run,add(ReviewSpawn,{std::array<float,5>{0,2,6,10,16}[targetChoice],0,0}),48);
    // Use the existing camera controls to frame the comparison lane. This
    // updates native picking and rendering together, without a second camera.
    key(2,KEY_PAGE_DOWN);for(int n=0;n<10;++n)game.update(.1f);key(1,KEY_PAGE_DOWN);
    game.updateCamera(10);
}
void guides(const Camera3D &camera) {
    BeginMode3D(camera);
    DrawCircle3D({ReviewSpawn.x,.03f,ReviewSpawn.z},11,{1,0,0},90,Gold);
    DrawLine3D({-8,.03f,0},{11.7f,.03f,0},Teal);
    for(float distance:{2.f,6.f,10.f,16.f}) {
        auto at=add(ReviewSpawn,{distance,0,0});at.y=.02f;DrawCylinder(at,.04f,.04f,1.5f,6,Teal);
    }
    EndMode3D();
}
void overlay(const Game &game,int preset,int targets) {
    const float sx=GetScreenWidth()/1280.f,sy=GetScreenHeight()/800.f;
    auto panel=[&](float x,float y,float w,float h){DrawRectangleRec({x*sx,y*sy,w*sx,h*sy},Panel);};
    auto text=[&](std::string value,float x,float y,int size,Color color=Paper){DrawText(value.c_str(),int(x*sx),int(y*sy),std::max(10,int(size*sy)),color);};
    panel(24,24,885,160);text("INDEPENDENT SHOOTING STATS",38,36,22,Gold);
    text(std::string("Selected: ")+PresetNames[size_t(preset)],38,68,18);
    text(preset==1?"Only Tears changes: more frequent shots":preset==2?"Only Shot Speed changes: same firing rhythm and reach":preset==3?"Only Range changes: same firing rhythm and travel speed":"Base shooting stats with your selected projectile feel",38,97,15);
    text("Active bullets: "+std::to_string(game.run->projectiles.size())+" | no artificial three-bullet cap",38,124,14);
    text("Review candidate; source timing / full calibration remain open",38,150,13,Gold);
    panel(964,22,292,162);text("COMPARE ONE STAT",978,35,18,Gold);
    text("1 Base / 2 Quicker firing",978,65,14);text("3 Faster travel / 4 Longer reach",978,88,12);
    text("Arrows or RMB: fire",978,112,14);text("WASD / click: move",978,135,14);text("Space: dodge",978,157,13);
    panel(24,190,420,115);text("F8 reset | T: "+std::array<std::string,5>{"no target","close target","middle target","near base limit","far target"}[targets],38,204,15);
    text("Aim across the room along the guide",38,231,14);
    text("Gold ring = base reach from starting spot",38,255,13);
    text("F11 follow shot | target takes two hits",38,279,13);
}
} // namespace
int main(int argc,char **argv) {
    bool verification=false,followShot=false;int frames=0,preset=0;
    std::filesystem::path capture,output,mechanics;
    try {
        for(int i=1;i<argc;++i){std::string arg=argv[i];
            if(arg=="--verify")verification=true;
            else if(arg=="--preset"&&i+1<argc)preset=std::stoi(argv[++i])-1;
            else if(arg=="--frames"&&i+1<argc)frames=std::stoi(argv[++i]);
            else if(arg=="--capture"&&i+1<argc)capture=argv[++i];
            else if(arg=="--measurements"&&i+1<argc)output=argv[++i];
            else if(arg=="--mechanics"&&i+1<argc)mechanics=argv[++i];
            else if(arg=="--help"){std::cout<<"Independent stats review: 1 Base, 2 Quicker firing, 3 Faster travel, 4 Longer reach. F8 reset; T targets; F11 shot follow. --preset 1|2|3|4 --verify --measurements PATH --frames N --capture PATH --mechanics PATH\n";return 0;}
            else throw std::runtime_error("Unknown/incomplete option: "+arg);
        }
        require(preset>=0&&preset<4,"preset must be 1 through 4");require(capture.empty()||frames>0,"capture requires bounded frames");
        SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_RESIZABLE|(verification?FLAG_WINDOW_HIDDEN:0));
        InitWindow(1440,900,"DeathWard | Independent shooting stats");require(IsWindowReady(),"graphics window available");SetExitKey(KEY_NULL);SetTargetFPS(verification||frames?0:60);
        if(mechanics.empty()){
            const auto snapshot=std::filesystem::path(GetApplicationDirectory())/"projectile-review-mechanics";
            mechanics=std::filesystem::exists(snapshot)?snapshot:sourceAssetDirectory()/"mechanics";
        }
        auto library=MechanicsLibrary::load(mechanics);TemporaryDirectory temporary;
        if(verification){verify(temporary,library,output);CloseWindow();return 0;}
        {
            int reset=0,targets=0;auto game=fixture(temporary.path/"0.save",library,true,false);setup(*game,preset,targets);Renderer renderer;
            for(int frame=0;!WindowShouldClose()&&!game->quit&&(!frames||frame<frames);++frame) {
                const bool cycle=IsKeyPressed(KEY_T);int selected=-1;
                for(int n=0;n<4;++n)if(IsKeyPressed(KEY_ONE+n))selected=n;
                if(IsKeyPressed(KEY_F11))followShot=!followShot;
                if(selected>=0)preset=selected;if(cycle)targets=(targets+1)%5;
                if(selected>=0||cycle||IsKeyPressed(KEY_F8)){
                    game=fixture(temporary.path/(std::to_string(++reset)+".save"),library,true,false);setup(*game,preset,targets);
                }
                game->update(frames?Tick:GetFrameTime(),[&](const Simulation &run,const Camera3D &view,Ray ray){return renderer.pickScenery(run,view,ray);});
                require(game->error.empty(),game->error.c_str());if(game->screen!=Screen::Expedition)break;
                if(followShot&&!game->run->projectiles.empty()){
                    const auto offset=sub(game->camera.position,game->camera.target);game->camera.target=game->run->projectiles.front().position;game->camera.position=add(game->camera.target,offset);
                }
                BeginDrawing();auto action=renderer.draw(*game);
                if(!game->paused&&!game->controlsOpen&&!game->buildOpen){BeginScissorMode(0,int(306*GetScreenHeight()/800.f),int(964*GetScreenWidth()/1280.f),int(368*GetScreenHeight()/800.f));guides(game->camera);EndScissorMode();overlay(*game,preset,targets);}
                if(frames&&frame==frames-1&&!capture.empty()){rlDrawRenderBatchActive();auto pic=LoadImageFromScreen();require(ExportImage(pic,capture.string().c_str()),"save capture");UnloadImage(pic);}
                EndDrawing();game->perform(action);
            }
            renderer.unload();
        }
        CloseWindow();return 0;
    }catch(const std::exception &e){std::cerr<<e.what()<<'\n';if(IsWindowReady())CloseWindow();return 1;}
}
