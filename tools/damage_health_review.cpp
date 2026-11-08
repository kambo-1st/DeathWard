#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "platform/Assets.hpp"
#include "rlgl.h"
#include "damage_health_calibration.hpp"
#include "enemy_movement_calibration.hpp"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace dw;
namespace {
bool movementReview=false,nativePlayerReview=false;
constexpr Vector3 Spawn{0,.85f,0};

constexpr Color Paper{236,226,201,255},Panel{26,34,36,248},Teal{112,204,180,255},Gold{224,168,86,255};
void require(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
std::string number(double n,int precision=2){std::ostringstream s;s<<std::fixed<<std::setprecision(precision)<<n;return s.str();}
struct TemporaryDirectory {
    std::filesystem::path path=std::filesystem::temp_directory_path()/
        ("deathward-damage-health-review-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    TemporaryDirectory(){std::filesystem::create_directories(path);}
    ~TemporaryDirectory(){std::error_code error;std::filesystem::remove_all(path,error);}
};
std::unique_ptr<Game> fixture(const std::filesystem::path &save,std::shared_ptr<const MechanicsLibrary> library,bool source=false,bool open=false) {
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
    run.player=Player{};run.canonicalShooting=true;run.player.shotDamage=source&&!movementReview?run.player.attributes.damage:RevolverDamage;run.player.attributes.speed=1;run.player.position=Spawn;run.player.aim={0,.85f,-10};
    run.room=0;run.roomClear=false;run.debugScenario=true;run.godMode=false;
    run.dead=run.finished=run.floorExitRequested=run.rewardOpen=run.shopOpen=false;
    run.message.clear();run.messageTime=0;run.audioCues.clear();run.checkpointNeeded=false;
    game->campaign.begin(42,"Damage and health review",ExpeditionPacing::Compact);
    game->screen=Screen::Expedition;game->paused=game->slow=game->sandstorm=false;game->error.clear();
    if(nativePlayerReview)run.nativePlayerMovement.emplace(float(movement_review::WorldScale));
    game->updateCamera(10);
    return game;
}
void key(unsigned type,int code){PlayAutomationEvent({0,type,{code,0,0,0}});}
void releaseKeys(){for(int k:{KEY_W,KEY_A,KEY_S,KEY_D,KEY_SPACE,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT})key(1,k);}
struct Case {EntityId body=0;MonsterId identity{};bool ended=false;int hits=0;float lastHp=0;};
constexpr Vector3 PlayerStart{-8,.85f,0},BodyStart{-2,.85f,0};
Case setup(Game &game,bool encounter,int index) {
    releaseKeys();PlayAutomationEvent({0,5,{MOUSE_BUTTON_RIGHT,0,0,0}});PlayAutomationEvent({0,5,{MOUSE_BUTTON_LEFT,0,0,0}});
    auto &run=*game.run;run.arena.profile.sourceStage=1;
    run.player.position=PlayerStart;run.player.aim=BodyStart;
    // Frame the empty fixture before spawning actors, so camera preparation
    // cannot advance enemies or hurt the player before the comparison starts.
    key(2,KEY_PAGE_DOWN);for(int n=0;n<10;++n)game.update(.1f);key(1,KEY_PAGE_DOWN);game.updateCamera(10);
    run.stats={};game.accumulator=0;
    Case result;
    if(encounter) {
        const std::array<int,5> roster{0,1,3,5,7};
        const std::array<Vector3,5> positions{{{-1,.85f,-4},{1,.85f,4},{6,.85f,-4},{6,.85f,4},{4,.85f,0}}};
        for(int n=0;n<5;++n)require(run.spawnMonster(damage_review::Bodies[size_t(roster[n])].id,positions[n])!=0,"spawn live review encounter");
    } else {
        result.identity=damage_review::Bodies[size_t(index)].id;
        result.body=run.spawnMonster(result.identity,BodyStart);require(result.body!=0,"spawn real calibration body");
        auto *e=run.findEnemy(result.body);result.lastHp=e->hp;
        if(!movementReview){e->state=EnemyState::Stunned;e->stateTime=10000;e->velocity={};}
    }
    return result;
}
void holdLab(Simulation &run) {
    // Deliberately pause AI in the body check; encounter mode uses real AI.
    for(auto &e:run.enemies)if(e.alive){e.state=EnemyState::Stunned;e.stateTime=10000;e.velocity={};}
}
std::unique_ptr<Game> restartReview(const std::filesystem::path &save,std::shared_ptr<const MechanicsLibrary> library,
                                  bool candidate,bool encounter,int index,Case &state) {
    auto game=fixture(save,std::move(library),candidate);state=setup(*game,encounter,index);return game;
}
bool restartRequested(const Game &game) {
    return IsKeyPressed(KEY_F8)||(game.run&&game.run->dead&&IsKeyPressed(KEY_ENTER));
}
void advanceReview(Game &game,float dt,const Game::SceneryPicker &pick={}) {
    // Keep this disposable test room visible after death instead of allowing
    // the normal game's timed transition to the expedition summary.
    if(!game.run||!game.run->dead)game.update(dt,pick);
}
void verify(const TemporaryDirectory &temporary,std::shared_ptr<const MechanicsLibrary> current,
            std::shared_ptr<const MechanicsLibrary> source,const std::filesystem::path &output) {
    std::ostringstream rows;rows<<"mode,id,name,hp,damage,expected_body_hits,actual_body_hits,shots_fired,body_end_seconds,offspring_alive\n";
    int serial=0;
    for(bool candidate:{false,true})for(int index=0;index<9;++index) {
        releaseKeys();auto game=fixture(temporary.path/("verify"+std::to_string(serial++)+".save"),candidate?source:current,candidate,true);
        auto result=setup(*game,false,index);const auto &body=damage_review::Bodies[size_t(index)];
        const float hp=result.lastHp,damage=game->run->player.shotDamage;const auto start=game->run->stats.duration;
        const auto at=GetWorldToScreen(BodyStart,game->camera);
        PlayAutomationEvent({0,7,{int(at.x),int(at.y),0,0}});PlayAutomationEvent({0,6,{MOUSE_BUTTON_RIGHT,0,0,0}});
        int hitCount=0;
        for(int n=0;n<300&&!result.ended;++n) {
            holdLab(*game->run);game->update(Tick);
            const auto *e=game->run->findEnemy(result.body);
            const bool ended=!e||!e->alive||e->monster!=body.id;
            if(ended||(e&&e->hp<result.lastHp-.0001f))++hitCount;
            if(e&&!ended)result.lastHp=e->hp;
            result.ended=ended;
        }
        PlayAutomationEvent({0,5,{MOUSE_BUTTON_RIGHT,0,0,0}});
        require(game->error.empty()&&result.ended,"actual Game projectiles defeat each selected body");
        require(hitCount==damage_review::bodyHits(hp,damage),"actual projectile body-hit count matches shared units");
        require(game->run->player.hp==6&&!game->run->godMode,"body check preserves real player health without god mode");
        rows<<(candidate?"source":"current")<<','<<monsterIdText(body.id)<<','<<body.name<<','<<hp<<','<<damage<<','<<damage_review::bodyHits(hp,damage)<<','<<hitCount<<','<<game->run->stats.shots<<','<<game->run->stats.duration-start<<','<<game->run->livingEnemies()<<'\n';
    }
    for(bool candidate:{false,true})for(bool encounter:{false,true}) {
        Case state;auto game=restartReview(temporary.path/("death"+std::to_string(serial++)+".save"),candidate?source:current,candidate,encounter,3,state);
        game->run->player.hp=0;advanceReview(*game,Tick);
        require(game->run->dead,"fixture reaches real simulation death state");
        for(int n=0;n<600;++n)advanceReview(*game,Tick);
        require(game->screen==Screen::Expedition&&game->run->dead,"death stays in review beyond ordinary summary timeout");
        for(int keyCode:{KEY_F8,KEY_ENTER}) {
            key(2,keyCode);require(restartRequested(*game),"F8 and Enter request restart after death");key(1,keyCode);
        }
        game=restartReview(temporary.path/("retry"+std::to_string(serial++)+".save"),candidate?source:current,candidate,encounter,3,state);
        require(!game->run->dead&&game->run->player.hp==6&&game->run->projectiles.empty(),"retry restores healthy player and clean projectile state");
        require(std::abs(game->run->player.shotDamage-(candidate?3.5f:24.f))<.001,"retry keeps selected damage/HP mode");
        require(game->run->livingEnemies()==(encounter?5:1),"retry keeps selected body-check/live-encounter scenario");
        if(!encounter)require(game->run->findEnemy(state.body)->monster==damage_review::Bodies[3].id,"retry keeps selected lab body");
    }
    if(!output.empty()){std::ofstream file(output);file<<rows.str();require(bool(file),"write damage/health measurements");}
    std::cout<<"PASS death/retry: both balances and scenarios, summary timeout held, F8/Enter restart, clean health and preserved selection\n";
    std::cout<<rows.str()<<"PASS actual Game primary projectiles: nine bodies in both unit modes; body identity/death separate from offspring; accepted movement/shooting unchanged\n";
}
void verifyNativePlayerGame(const TemporaryDirectory &temporary,std::shared_ptr<const MechanicsLibrary> library,
                            const std::filesystem::path &output) {
    std::ostringstream rows;rows<<"render_fps,held_native_ticks,held_distance,expected_distance,coast_native_ticks,coast_distance,expected_coast_distance\n";
    for(int fps:{30,60,144}) {
        releaseKeys();auto game=fixture(temporary.path/("native-input-"+std::to_string(fps)+".save"),library,false,true);
        key(2,KEY_D);for(int frame=0;frame<fps*3/2;++frame)game->update(1.f/fps);releaseKeys();
        auto &run=*game->run;const int heldTicks=int(std::lround(run.stats.duration/Tick));
        native_motion::Body expected;for(int n=0;n<heldTicks;++n)expected.playerStep({1,0,0});
        const float held=planarDistance(Spawn,run.player.position),wanted=expected.position.x*float(movement_review::WorldScale);
        require(std::abs(held-wanted)<.003f,"actual Game keyboard acceleration matches executed native reference");
        const float heldDuration=run.stats.duration;
        for(int frame=0;frame<fps;++frame)game->update(1.f/fps);
        const int coastTicks=int(std::lround((run.stats.duration-heldDuration)/Tick));
        for(int n=0;n<coastTicks;++n)expected.playerStep({});
        const float coast=planarDistance(Spawn,run.player.position),wantedCoast=expected.position.x*float(movement_review::WorldScale);
        require(std::abs(coast-wantedCoast)<.003f&&coast>held,"actual Game native stopping matches reference coasting");
        require(game->error.empty()&&run.player.hp==6&&!run.godMode,"real Game reference has no errors or artificial health");
        rows<<fps<<','<<heldTicks<<','<<held<<','<<wanted<<','<<coastTicks<<','<<coast<<','<<wantedCoast<<'\n';
    }
    if(!output.empty()){std::ofstream file(output);file<<rows.str();require(bool(file),"write native Game input measurements");}
    std::cout<<rows.str()<<"PASS native reference Game keyboard movement and stopping at 30/60/144 render FPS; world/room scale remains an adaptation\n";
}
void overlay(const Game &game,bool candidate,bool encounter,int index,const Case &state) {
    const float sx=GetScreenWidth()/1280.f,sy=GetScreenHeight()/800.f;
    auto panel=[&](float x,float y,float w,float h){DrawRectangleRec({x*sx,y*sy,w*sx,h*sy},Panel);};
    auto text=[&](std::string value,float x,float y,int size,Color color=Paper){DrawText(value.c_str(),int(x*sx),int(y*sy),std::max(10,int(size*sy)),color);};
    if(game.run->dead) {
        panel(280,290,720,150);text("YOU DIED",310,312,28,Gold);
        text("Press F8 or Enter to restart this test",310,360,21);
        text("Your balance mode and selected encounter stay the same",310,402,14);
        return;
    }
    if(movementReview) {
        panel(24,24,885,145);text(candidate?"CORRECTED RELATIVE MOVEMENT":"PREVIOUS MOVEMENT",38,36,22,Gold);
        text(encounter?"Encounter: five enemies":std::string("Movement check: ")+damage_review::Bodies[size_t(index)].name,38,70,18);
        text(nativePlayerReview?"Native player curve | shared review scale; room geometry still adapted":"Responsive player curve | HP and player firing unchanged",38,101,16);
        text("Review candidate | enemy projectiles and room/body geometry still need calibration",38,136,13,Gold);
        panel(964,22,292,165);text("MOVEMENT REVIEW",978,35,17,Gold);
        text("1 Previous / 2 Corrected",978,66,14);text("3: native / responsive player",978,89,12);text("T: one enemy / encounter",978,109,12);
        text("[ / ]: enemy | F8: reset",978,132,12);text("Enter: restart after death",978,154,12);
        return;
    }
    panel(24,24,885,160);text(candidate?"SOURCE DAMAGE + HEALTH":"CURRENT DAMAGE + HEALTH",38,36,22,Gold);
    text(encounter?"Live encounter: judge kill times and pressure":std::string("Body check: ")+damage_review::Bodies[size_t(index)].name,38,68,18);
    if(!encounter){
        const auto *e=game.run->findEnemy(state.body);
        const float starting=game.run->content->monsterHealth(state.identity,1);
        text("Expected body hits: "+std::to_string(damage_review::bodyHits(starting,game.run->player.shotDamage))+" | observed hits: "+std::to_string(state.hits),38,97,16);
        text(state.ended?"Body defeated. Surviving morphs/offspring count separately.":"AI paused for this check. Aim at the body and fire.",38,124,14);
        (void)e;
    }else{text("Enemy AI and existing controls are active",38,97,16);text("Clear the room; compare with the same current-balance encounter",38,124,14);}
    text("Review only | movement, firing, dodge and regular-health control preserved",38,150,12,Gold);
    panel(964,22,292,165);text("DAMAGE / HP REVIEW",978,35,17,Gold);text("1 Current / 2 Source",978,66,15);
    text("T: body check / encounter",978,91,13);text("[ / ]: choose body",978,116,14);text("F8 reset | normal controls",978,145,12);
    panel(24,190,420,65);text("Arrows or RMB: fire | Space: dodge",38,204,14);text("WASD / click: move | two scales, same room",38,229,12);
}
} // namespace
int main(int argc,char **argv) {
    bool candidate=true,encounter=false,verification=false;int index=0,frames=0;
    std::filesystem::path capture,output,mechanics;
    try {
        for(int i=1;i<argc;++i){std::string arg=argv[i];
            if(arg=="--native-player-reference"){movementReview=true;nativePlayerReview=true;}
            else if(arg=="--movement-review")movementReview=true;
            else if(arg=="--verify")verification=true;
            else if(arg=="--current")candidate=false;
            else if(arg=="--encounter")encounter=true;
            else if(arg=="--body"&&i+1<argc)index=std::stoi(argv[++i])-1;
            else if(arg=="--frames"&&i+1<argc)frames=std::stoi(argv[++i]);
            else if(arg=="--capture"&&i+1<argc)capture=argv[++i];
            else if(arg=="--measurements"&&i+1<argc)output=argv[++i];
            else if(arg=="--mechanics"&&i+1<argc)mechanics=argv[++i];
            else if(arg=="--help"){std::cout<<"Damage/health review: 1 Current, 2 Source; T lab/live encounter; [ ] select body; F8 reset. --movement-review --native-player-reference (3 toggles player curve) --verify --measurements PATH --current --encounter --body 1..9 --frames N --capture PATH --mechanics PATH\n";return 0;}
            else throw std::runtime_error("Unknown/incomplete option: "+arg);
        }
        require(index>=0&&index<9,"body must be 1 through 9");
        require(!movementReview||(index!=4&&index!=6&&index!=8),"movement candidate supports Gapers, Gusher, Horf, Pooter and Spider");require(capture.empty()||frames>0,"capture requires bounded frames");
        SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_RESIZABLE|(verification?FLAG_WINDOW_HIDDEN:0));
        InitWindow(1440,900,movementReview?"DeathWard | Enemy movement review":"DeathWard | Damage and enemy health review");require(IsWindowReady(),"graphics window available");SetExitKey(KEY_NULL);SetTargetFPS(verification||frames?0:60);
        if(mechanics.empty()){
            const auto snapshot=std::filesystem::path(GetApplicationDirectory())/"damage-review-mechanics";
            mechanics=std::filesystem::exists(snapshot)?snapshot:sourceAssetDirectory()/"mechanics";
        }
        TemporaryDirectory temporary;auto current=MechanicsLibrary::load(mechanics);
        auto source=movementReview?movement_review::makePack(*current,temporary.path/"movement-mechanics"):
            damage_review::makeSourcePack(*current,temporary.path/"source-mechanics");
        if(verification&&nativePlayerReview){verifyNativePlayerGame(temporary,source,output);CloseWindow();return 0;}
        require(!movementReview||!verification,"use dedicated movement calibration test for motion verification");
        if(verification){verify(temporary,current,source,output);CloseWindow();return 0;}
        {
            int reset=0;Case state;auto game=restartReview(temporary.path/"0.save",candidate?source:current,candidate,encounter,index,state);
            Renderer renderer;
            for(int frame=0;!WindowShouldClose()&&!game->quit&&(!frames||frame<frames);++frame){
                const bool nativeToggle=movementReview&&IsKeyPressed(KEY_THREE);
                if(nativeToggle)nativePlayerReview=!nativePlayerReview;
                const bool one=IsKeyPressed(KEY_ONE),two=IsKeyPressed(KEY_TWO),toggle=IsKeyPressed(KEY_T),left=IsKeyPressed(KEY_LEFT_BRACKET),right=IsKeyPressed(KEY_RIGHT_BRACKET);
                if(one)candidate=false;if(two)candidate=true;if(toggle)encounter=!encounter;
                if(left||right) {
                    do {index=(index+(left?8:1))%9;}
                    while(movementReview&&(index==4||index==6||index==8));
                }
                if(nativeToggle||one||two||toggle||left||right||restartRequested(*game)){
                    game=restartReview(temporary.path/(std::to_string(++reset)+".save"),candidate?source:current,candidate,encounter,index,state);
                }
                if(!encounter&&!movementReview)holdLab(*game->run);
                advanceReview(*game,frames?Tick:GetFrameTime(),[&](const Simulation &run,const Camera3D &view,Ray ray){return renderer.pickScenery(run,view,ray);});
                require(game->error.empty(),game->error.c_str());if(game->screen!=Screen::Expedition)break;
                if(!encounter&&!state.ended){const auto *e=game->run->findEnemy(state.body);const bool ended=!e||!e->alive||e->monster!=state.identity;
                    if(ended||(e&&e->hp<state.lastHp-.0001f))++state.hits;if(e&&!ended)state.lastHp=e->hp;state.ended=ended;}
                BeginDrawing();auto action=renderer.draw(*game);if(!game->paused&&!game->controlsOpen&&!game->buildOpen)overlay(*game,candidate,encounter,index,state);
                if(frames&&frame==frames-1&&!capture.empty()){rlDrawRenderBatchActive();auto pic=LoadImageFromScreen();require(ExportImage(pic,capture.string().c_str()),"save capture");UnloadImage(pic);}
                EndDrawing();game->perform(action);
            }
            renderer.unload();
        }
        CloseWindow();return 0;
    }catch(const std::exception &e){std::cerr<<e.what()<<'\n';if(IsWindowReady())CloseWindow();return 1;}
}
