#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include "rlgl.h"
#include <chrono>
#include <fstream>
#include <iostream>
using namespace dw;
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
int main(){try {
    SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_HIDDEN);InitWindow(1280,800,"Wider poop review");SetTargetFPS(0);
    const auto report=std::filesystem::path("docs/reports/isaac-first-floor-parity/d14a5-mixed-flies/wider-poop-2");
    Game game(std::filesystem::path("/tmp")/("deathward-poop-width-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()))/"campaign.save");
    game.themeChoice=ThemeChoice::Canyon;game.seedText="11";game.reviewSourceRoomTemplate=414;
    game.nextBalancePreset=BalancePreset::load("/home/kambo/.local/share/deathward/reviews/first-floor-d14a5/campaign.save.balance/export.json",defaultMechanics()->fingerprint());game.launch(true);
    check(game.run&&game.error.empty(),"source414 direct entry");check(game.run->room==4&&game.run->enemies.size()==20&&game.run->player.hp==6&&!game.run->godMode,"same encounter at normal health");
    int count=0;float width=0,height=0;
    for(const auto &p:game.run->arena.breakables)if(p.room==game.run->room&&p.kind==BreakableKind::Dung){++count;width=p.bounds.max.x-p.bounds.min.x;height=p.bounds.max.y-p.bounds.min.y;}
    check(count==20&&std::abs(height-1.155f)<.00001f,"twenty piles and unchanged height");
    check(std::abs(width/game.run->arena.rooms[4].sourcePropCellOverride-1.3125f)<.00001f,"widened solid bounds");
    game.updateCamera(10);Renderer renderer;game.update(Tick);BeginDrawing();renderer.draw(game);rlDrawRenderBatchActive();auto im=LoadImageFromScreen();check(ExportImage(im,(report/"encounter.png").string().c_str()),"capture actual Renderer");UnloadImage(im);EndDrawing();
    std::cout<<"PASS wider poop Game/Renderer: seed=11 room=5 count="<<count<<" width="<<width<<" height="<<height<<" cell="<<game.run->arena.rooms[4].sourcePropCellOverride<<" zoom="<<game.balancePreset.defaultZoomPercent<<" hp="<<game.run->player.hp<<" god="<<game.run->godMode<<'\n';
    game.close();renderer.unload();CloseWindow();return 0;
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
