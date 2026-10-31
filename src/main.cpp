#include "audio/AudioSystem.hpp"
#include "core/Game.hpp"
#include "core/FrontEnd.hpp"
#include "editor/TownEditor.hpp"
#include "editor/CinematicEditor.hpp"
#include "platform/Browser.hpp"
#include "render/Renderer.hpp"
#include <algorithm>
#include <charconv>
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>

#ifdef __EMSCRIPTEN__
EM_ASYNC_JS(void, nextBrowserFrame, (), { await new Promise(requestAnimationFrame); });
#endif

namespace {
bool upgradeTownNavigation(dw::HubKind hub) {
    const auto directory = dw::TownScene::assetDirectory(hub);
    dw::TownNavigation navigation;
    navigation.load(directory / "town.nav");
    if (navigation.bakeVersion >= 3) return false;
    dw::TownDocument document;
    std::string error;
    if (!document.load(directory / "town.scene", error)) throw std::runtime_error(error);
#ifdef __EMSCRIPTEN__
    const auto modelFile = std::filesystem::path("/assets") / dw::hubFolder(hub) / "town.glb";
#else
    const auto modelFile = directory / "town.glb";
#endif
    auto model = LoadModel(modelFile.string().c_str());
    try {
        navigation.bake(document, model);
        dw::saveTownNavigation(directory, navigation);
    } catch (...) {
        if (model.meshCount) UnloadModel(model);
        throw;
    }
    UnloadModel(model);
    return true;
}
} // namespace

int main(int argc, char **argv) {
    std::filesystem::path save = dw::CampaignStore::defaultPath();
    bool smoke = false, benchmark = false, startEditor = false, artPoc = false, startExpedition = false;
    std::optional<dw::VisualStyle> styleChoice;
    bool startCinematic = false, intro = false, fullExperience = false, explicitSave = false;
    bool mute = false, explicitAudio = false, sandstorm = false;
    std::optional<bool> canyonRiver;
    dw::ThemeChoice themeChoice = dw::ThemeChoice::Canyon;
    dw::ExpeditionPacing expeditionPacing = dw::ExpeditionPacing::Compact;
    dw::HubKind initialHub = dw::HubKind::BlackCreek;
    std::filesystem::path editorDirectory;
    std::filesystem::path sequenceFile;
    std::filesystem::path slotsDirectory;
    std::optional<float> cinematicTime;
    std::string screenshot, scene = "combat";
    std::optional<dw::MonsterId> enemyScene;
    std::string enemyPlayerSide;
    std::string enemyBombProfile;
    int enemySegment=-1;
    bool residentScene=false;
    std::optional<uint64_t> residentSeed;
    std::optional<int> residentFloor;
    std::optional<dw::MonsterId> residentFrom;
    dw::MonsterId probeOriginal{};
    std::string enemyTerrain;
    bool enemyCameraFollow=false;
    Vector3 enemyCameraTarget{};
    int enemyCount=1;
    std::optional<dw::BossForm> enemyBossForm;
    Vector3 probeStart{};
    dw::EntityId probeEnemy=0;
    struct EnemyHit {int frame;float damage;dw::DamageKind kind;bool execution=false,explosion=false,decoy=false,partner=false;};
    std::vector<EnemyHit> enemyHits;
    struct EnemyStatusEvent {int frame;dw::EnemyStatus status;int duration;};
    std::vector<EnemyStatusEvent> enemyStatuses;
    struct EnemyPlayerMove {int frame;float x,z;};
    std::vector<EnemyPlayerMove> enemyPlayerMoves, enemyPlayerAttacks;
    struct EnemyProbeShot {int frame;bool hostile;Vector3 offset,velocity;};
    std::vector<EnemyProbeShot> enemyProbeShots;
    std::vector<int> enemyFires;
    std::vector<int> enemyClears,enemyReentries;
    std::vector<dw::ItemKey> enemyItems;
    bool enemyFlooded=false;
    int frames = 180;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--save" && i + 1 < argc) {
            save = argv[++i]; explicitSave = true;
        }
        else if (arg == "--full-experience")
            fullExperience = true;
        else if (arg == "--expedition")
            startExpedition = true;
        else if (arg == "--slots" && i + 1 < argc)
            slotsDirectory = argv[++i];
        else if (arg == "--art-poc")
            artPoc = true;
        else if (arg == "--cel-shading")
            styleChoice = dw::VisualStyle::Cel;
        else if (arg == "--style" && i + 1 < argc) {
            styleChoice = dw::parseVisualStyle(argv[++i]);
            if (!styleChoice) {
                std::cerr << "--style must be original, cel, comic, painted, poster, noir, retro, woodcut, watercolor, pencil, ink, diorama, cinema, crt, spectral, sumi (alias: okami) or matte\n";
                return 2;
            }
        }
        else if (arg == "--sandstorm")
            sandstorm = true;
        else if (arg == "--editor")
            startEditor = true;
        else if (arg == "--intro")
            intro = true;
        else if (arg == "--cinematic")
            startCinematic = true;
        else if (arg == "--sequence" && i + 1 < argc)
            sequenceFile = argv[++i];
        else if (arg == "--cinematic-at" && i + 1 < argc) {
            const std::string value=argv[++i]; float time=0;
            auto parsed=std::from_chars(value.data(),value.data()+value.size(),time);
            if(parsed.ec!=std::errc{}||parsed.ptr!=value.data()+value.size()||!std::isfinite(time)||time<0) {
                std::cerr<<"--cinematic-at needs a nonnegative time in seconds\n";return 2;
            }
            cinematicTime=time;
        }
        else if (arg == "--town" && i + 1 < argc)
            editorDirectory = argv[++i];
        else if (arg == "--smoke")
            smoke = true;
        else if (arg == "--benchmark")
            benchmark = true;
        else if (arg == "--mute")
            mute = true;
        else if (arg == "--audio")
            explicitAudio = true;
        else if (arg == "--canyon-river" && i + 1 < argc) {
            const std::string setting = argv[++i];
            if (setting != "on" && setting != "off") {
                std::cerr << "--canyon-river must be on or off\n";
                return 2;
            }
            canyonRiver = setting == "on";
        } else if (arg == "--expedition-pacing" && i + 1 < argc) {
            const std::string pacing = argv[++i];
            if (pacing == "growing") expeditionPacing = dw::ExpeditionPacing::Growing;
            else if (pacing == "classic") expeditionPacing = dw::ExpeditionPacing::Classic;
            else if (pacing == "corridors") expeditionPacing = dw::ExpeditionPacing::ShortCorridors;
            else if (pacing == "rooms") expeditionPacing = dw::ExpeditionPacing::SmallRooms;
            else if (pacing == "compact") expeditionPacing = dw::ExpeditionPacing::Compact;
            else { std::cerr << "--expedition-pacing must be growing, classic, corridors, rooms or compact\n"; return 2; }
        } else if (arg == "--theme" && i + 1 < argc) {
            const std::string theme = argv[++i];
            if (theme == "seeded")
                themeChoice = dw::ThemeChoice::Seeded;
            else if (theme == "mine")
                themeChoice = dw::ThemeChoice::Mine;
            else if (theme == "canyon")
                themeChoice = dw::ThemeChoice::Canyon;
            else {
                std::cerr << "--theme must be seeded, mine or canyon\n";
                return 2;
            }
        } else if (arg == "--hub" && i + 1 < argc) {
            const std::string hub = argv[++i];
            if (hub == "black-creek")
                initialHub = dw::HubKind::BlackCreek;
            else if (hub == "frontier")
                initialHub = dw::HubKind::Frontier;
            else if (hub == "redstone" || hub == "canyon")
                initialHub = dw::HubKind::Redstone;
            else {
                std::cerr << "--hub must be black-creek, frontier or redstone\n";
                return 2;
            }
        } else if (arg == "--screenshot" && i + 1 < argc)
            screenshot = argv[++i];
        else if (arg == "--scene" && i + 1 < argc)
            scene = argv[++i];
        else if (arg == "--enemy-bomb" && i + 1 < argc)
            enemyBombProfile=argv[++i];
        else if (arg == "--resident-seed" && i + 1 < argc) {
            const std::string value=argv[++i];uint64_t seed=0;
            const auto parsed=std::from_chars(value.data(),value.data()+value.size(),seed);
            if(parsed.ec!=std::errc{}||parsed.ptr!=value.data()+value.size()){std::cerr<<"--resident-seed needs an unsigned integer\n";return 2;}
            residentSeed=seed;
        }
        else if (arg == "--resident-floor" && i + 1 < argc) {
            const std::string value=argv[++i];int floor=0;
            const auto parsed=std::from_chars(value.data(),value.data()+value.size(),floor);
            if(parsed.ec!=std::errc{}||parsed.ptr!=value.data()+value.size()||floor<0||floor>7){std::cerr<<"--resident-floor needs a zero-based floor 0..7\n";return 2;}
            residentFloor=floor;
        }
        else if (arg == "--resident-from" && i + 1 < argc) {
            try {residentFrom=dw::parseMonsterId(argv[++i]);}
            catch(const std::exception &e){std::cerr<<"Invalid resident source: "<<e.what()<<'\n';return 2;}
        }
        else if (arg == "--enemy-count" && i + 1 < argc) {
            const std::string value=argv[++i];const auto parsed=std::from_chars(value.data(),value.data()+value.size(),enemyCount);
            if(parsed.ec!=std::errc{}||parsed.ptr!=value.data()+value.size()||enemyCount<1||enemyCount>64){std::cerr<<"--enemy-count must be 1..64\n";return 2;}
        }
        else if (arg == "--enemy-terrain" && i + 1 < argc) {
            enemyTerrain=argv[++i];
            if(enemyTerrain!="cover"&&enemyTerrain!="river"&&enemyTerrain!="hop-cover"&&enemyTerrain!="dung") {std::cerr<<"--enemy-terrain must be cover, river, hop-cover or dung\n";return 2;}
        }
        else if (arg == "--enemy-camera-follow") enemyCameraFollow=true;
        else if (arg == "--enemy-flooded") enemyFlooded=true;
        else if (arg == "--enemy-boss-form" && i + 1 < argc) {
            const std::string form=argv[++i];
            if(form=="normal")enemyBossForm=dw::BossForm::Normal;
            else if(form=="cyan")enemyBossForm=dw::BossForm::Cyan;
            else if(form=="yellow")enemyBossForm=dw::BossForm::Yellow;
            else if(form=="green")enemyBossForm=dw::BossForm::Green;
            else {std::cerr<<"--enemy-boss-form must be normal, cyan, yellow or green\n";return 2;}
        }
        else if(arg=="--enemy-segment"&&i+1<argc) {
            char *end=nullptr;const long value=std::strtol(argv[++i],&end,10);
            if(!end||*end||value<0||value>63){std::cerr<<"--enemy-segment requires an index 0..63\n";return 2;}
            enemySegment=int(value);
        }
        else if(arg=="--enemy-player-side"&&i+1<argc) {
            enemyPlayerSide=argv[++i];
            if(enemyPlayerSide!="above"&&enemyPlayerSide!="below"&&enemyPlayerSide!="left"&&enemyPlayerSide!="right"&&enemyPlayerSide!="diagonal") {
                std::cerr<<"--enemy-player-side must be above, below, left, right or diagonal\n";return 2;
            }
        }
        else if((arg=="--enemy-player-at"||arg=="--enemy-player-attack")&&i+3<argc) {
            const std::string when=argv[++i],x=argv[++i],z=argv[++i];EnemyPlayerMove move{};
            auto &events=arg=="--enemy-player-at"?enemyPlayerMoves:enemyPlayerAttacks;
            const auto a=std::from_chars(when.data(),when.data()+when.size(),move.frame);
            const auto b=std::from_chars(x.data(),x.data()+x.size(),move.x),c=std::from_chars(z.data(),z.data()+z.size(),move.z);
            if(a.ec!=std::errc{}||a.ptr!=when.data()+when.size()||move.frame<1||move.frame>1000000||
               b.ec!=std::errc{}||b.ptr!=x.data()+x.size()||c.ec!=std::errc{}||c.ptr!=z.data()+z.size()||
               !std::isfinite(move.x)||!std::isfinite(move.z)||std::abs(move.x)>100||std::abs(move.z)>100||events.size()>=64) {
                std::cerr<<arg<<" needs FRAME X Z, offsets within 100 units; at most 64 events\n";return 2;
            }
            events.push_back(move);
        }
        else if(arg=="--enemy-shot"&&i+6<argc) {
            EnemyProbeShot shot{};const std::string at=argv[++i],team=argv[++i];
            const auto frame=std::from_chars(at.data(),at.data()+at.size(),shot.frame);
            bool valid=frame.ec==std::errc{}&&frame.ptr==at.data()+at.size()&&shot.frame>=1&&shot.frame<=1000000&&(team=="player"||team=="hostile");
            shot.hostile=team=="hostile";
            for(float *value:{&shot.offset.x,&shot.offset.z,&shot.velocity.x,&shot.velocity.z}) {
                const std::string text=argv[++i];const auto parsed=std::from_chars(text.data(),text.data()+text.size(),*value);
                valid&=parsed.ec==std::errc{}&&parsed.ptr==text.data()+text.size()&&std::isfinite(*value)&&std::abs(*value)<=100;
            }
            if(!valid||dw::length(shot.velocity)<.1f||dw::length(shot.velocity)>50||enemyProbeShots.size()>=64) {
                std::cerr<<"--enemy-shot needs FRAME player|hostile X Z VX VZ; speed .1..50, at most 64 shots\n";return 2;
            }
            enemyProbeShots.push_back(shot);
        }
        else if (arg == "--enemy-item" && i + 1 < argc) {
            try{enemyItems.push_back(dw::parseItemKey(argv[++i]));}
            catch(const std::exception &e){std::cerr<<"Invalid enemy test item: "<<e.what()<<'\n';return 2;}
            if(enemyItems.size()>16){std::cerr<<"At most sixteen test items are allowed\n";return 2;}
        }
        else if ((arg == "--enemy-fire"||arg=="--enemy-clear"||arg=="--enemy-reenter") && i + 1 < argc) {
            const std::string at=argv[++i];int atFrame=0;
            const auto parsed=std::from_chars(at.data(),at.data()+at.size(),atFrame);
            auto &events=arg=="--enemy-fire"?enemyFires:arg=="--enemy-clear"?enemyClears:enemyReentries;
            if(parsed.ec!=std::errc{}||parsed.ptr!=at.data()+at.size()||atFrame<1||atFrame>1000000||events.size()>=64){std::cerr<<arg<<" needs FRAME (1..1000000), at most 64 events\n";return 2;}
            events.push_back(atFrame);
        }
        else if(arg=="--enemy-status"&&i+3<argc) {
            const std::string at=argv[++i],kind=argv[++i],duration=argv[++i];int atFrame=0,ticks=0;
            const auto a=std::from_chars(at.data(),at.data()+at.size(),atFrame);
            const auto b=std::from_chars(duration.data(),duration.data()+duration.size(),ticks);
            if(a.ec!=std::errc{}||a.ptr!=at.data()+at.size()||atFrame<1||atFrame>1000000||
               b.ec!=std::errc{}||b.ptr!=duration.data()+duration.size()||ticks < -18000||ticks>18000||
               (kind!="fear"&&kind!="confusion"&&kind!="freeze"&&kind!="slow"&&kind!="poison"&&kind!="burn"&&kind!="shrink"&&kind!="charm")||(kind=="charm"&&ticks<0)||enemyStatuses.size()>=64) {
                std::cerr<<"--enemy-status needs FRAME fear|confusion|freeze|slow|poison|burn|shrink|charm DURATION (-18000..18000 source frames; Charm requires >=0; 0 removes); at most 64 events\n";return 2;
            }
            enemyStatuses.push_back({atFrame,kind=="fear"?dw::EnemyStatus::Fear:kind=="confusion"?dw::EnemyStatus::Confusion:kind=="freeze"?dw::EnemyStatus::Freeze:kind=="slow"?dw::EnemyStatus::Slow:kind=="poison"?dw::EnemyStatus::Poison:kind=="burn"?dw::EnemyStatus::Burn:kind=="shrink"?dw::EnemyStatus::Shrink:dw::EnemyStatus::Charm,ticks});
        }
        else if ((arg == "--enemy-hit"||arg=="--enemy-flame-hit"||arg=="--enemy-burn-hit"||arg=="--enemy-execute"||arg=="--enemy-blast"||arg=="--enemy-decoy-hit"||arg=="--enemy-decoy-blast"||arg=="--enemy-partner-hit") && i + 2 < argc) {
            const std::string at=argv[++i],amount=argv[++i];int hitFrame=0;float damage=0;
            const auto a=std::from_chars(at.data(),at.data()+at.size(),hitFrame);
            const auto b=std::from_chars(amount.data(),amount.data()+amount.size(),damage);
            if(a.ec!=std::errc{}||a.ptr!=at.data()+at.size()||hitFrame<1||hitFrame>1000000||
               b.ec!=std::errc{}||b.ptr!=amount.data()+amount.size()||!std::isfinite(damage)||damage<=0||damage>1000000||enemyHits.size()>=64) {
                std::cerr<<"--enemy-hit needs FRAME (1..1000000) and DAMAGE (0..1000000]; at most 64 hits\n";return 2;
            }
            enemyHits.push_back({hitFrame,damage,arg=="--enemy-flame-hit"?dw::DamageKind::Flame:
                arg=="--enemy-burn-hit"?dw::DamageKind::Burning:dw::DamageKind::Physical,arg=="--enemy-execute",arg=="--enemy-blast"||arg=="--enemy-decoy-blast",arg=="--enemy-decoy-hit"||arg=="--enemy-decoy-blast",arg=="--enemy-partner-hit"});
        }
        else if (arg == "--frames" && i + 1 < argc) {
            const std::string value = argv[++i];
            auto parsed = std::from_chars(value.data(), value.data() + value.size(), frames);
            if (parsed.ec != std::errc{} || parsed.ptr != value.data() + value.size() || frames < 1) {
                std::cerr << "--frames needs a positive whole number\n";
                return 2;
            }
        } else if (arg == "--help") {
            std::cout << "DeathWard\n  --expedition         Start directly in a playable expedition\n  --editor             Open the 3D town editor\n  --town DIRECTORY     "
                         "Town pack to edit (with --editor)\n  --save PATH          Separate campaign file\n "
                         " --theme NAME         seeded, mine or canyon (default)\n  --hub NAME           "
                         "black-creek"
                         ", frontier or redstone\n  --smoke              "
                         "Render a scripted scene, then exit\n  --scene NAME         combat, hub, key, "
                         "power, reward, empty, cheats, "
                         "boss, summary, demolition, demolition-open, demolition-run,\n"
                         "                      build-bank, build-shrapnel, build-return, build-braid,\n"
                         "                      ridgeback, foreman, marshal (also -late or -fight),\n"
                         "                      profile-quarry, profile-works, profile-storm,\n"
                         "                      service-exchange, service-surgeon, service-bargain, boss-reward,\n"
                         "                      enemy-TYPE.VARIANT.SUBTYPE (isolated enemy capture; with --smoke)\n  --benchmark          Render the 100-enemy / "
                         "600-shot stress scenario\n  --frames N           Scripted frame count (default "
                         "180)\n  --screenshot PATH    Save a PNG before scripted exit\n"
                         "  --enemy-hit FRAME DAMAGE  Damage the isolated enemy on this frame; repeat for scripted phases\n"
                         "  --enemy-status FRAME fear|confusion|freeze|slow|poison|burn|shrink|charm DURATION  Apply source-frame status; 0 removes (isolated smoke scene)\n"
                         "  --enemy-partner-hit FRAME DAMAGE  Damage its current linked part (smoke capture only)\n"
                         "  --enemy-terrain MODE  cover, river, hop-cover or dung; isolated collision capture\n"
                         "  --enemy-camera-follow  Keep the captured enemy/death position in view (smoke only)\n"
                         "  --enemy-flame-hit FRAME DAMAGE / --enemy-burn-hit FRAME DAMAGE  Typed damage probes\n"
                         "  --enemy-fire FRAME  Place a real damaging flame at the isolated enemy\n"
                         "  --enemy-player-attack FRAME X Z  Use the actual attack input toward a relative target\n"
                         "  --enemy-item KEY  Grant an installed item in the isolated enemy test\n"
                         "  --enemy-clear FRAME / --enemy-reenter FRAME  Exercise room lifecycle in an isolated enemy test\n"
                         "  --enemy-flooded  Set the isolated room's flooded gameplay condition\n"
                         "  --enemy-count N       1..64 actors in an isolated enemy smoke scene\n"
                         "  --art-poc           Redstone art experiment (F6 compares in hub/editor)\n"
                         "  --style NAME        original, cel, comic, painted, poster, noir, retro,\n"
                         "                      woodcut, watercolor, pencil, ink, diorama, cinema, crt, spectral, sumi (alias: okami), matte\n"
                         "                      F6 cycles in hubs/editors; Pause selects in missions\n"
                         "  --cel-shading       Alias for --style cel\n"
                         "  --sandstorm         Start with the sandstorm on; K toggles in any map\n"
                         "  --intro             Play the Westbound opening (combine with --cinematic to edit)\n"
                         "  --full-experience   Logos, three save slots, settings and the story opening\n"
                         "  --slots DIRECTORY   Store full-experience slots in a separate folder\n"
                         "  --cinematic         Open the separate Cinematic Editor\n"
                         "  --sequence PATH     Cinematic file to edit (default: arrival.cinematic in hub)\n"
                         "  --cinematic-at SEC  Preview a specific timeline time\n"
                         "  --expedition-pacing NAME  compact (default), growing, classic, corridors or rooms\n"
                         "  --canyon-river MODE  on (default) or off; applies to new canyon missions\n"
                         "  --mute              Skip audio initialization\n"
                         "  --audio             Enable audio in scripted checks (silent by default)\n";
            return 0;
        } else {
            std::cerr << "Unknown or incomplete option: " << arg << '\n';
            return 2;
        }
    }
    if (fullExperience && (explicitSave || startEditor || startCinematic || intro || smoke || benchmark ||
                           !editorDirectory.empty() || !sequenceFile.empty())) {
        std::cerr << "--full-experience starts the story menu; use --slots DIRECTORY for separate saves. "
                     "Run editor, cinematic and scripted checks separately.\n";
        return 2;
    }
    if (!fullExperience && !slotsDirectory.empty()) {
        std::cerr << "--slots requires --full-experience\n";
        return 2;
    }
    residentScene=scene.starts_with("resident-");
    if(scene.starts_with("enemy-")||residentScene) {
        try {enemyScene=dw::parseMonsterId(scene.substr(residentScene?9:6));}
        catch(const std::exception &e){std::cerr<<"Invalid enemy scene: "<<e.what()<<'\n';return 2;}
        if(!smoke||benchmark){std::cerr<<"Enemy captures require --smoke without --benchmark\n";return 2;}
    }
    if((residentSeed||residentFloor||residentFrom)&&!residentScene){std::cerr<<"Resident options require --smoke --scene resident-ID\n";return 2;}
    if(!enemyBombProfile.empty()&&(!enemyScene||residentScene)){std::cerr<<"--enemy-bomb requires an isolated enemy-ID capture\n";return 2;}
    if(enemyBossForm&&(!enemyScene||residentScene)){std::cerr<<"--enemy-boss-form requires an isolated enemy-ID capture\n";return 2;}
    if(!enemyPlayerMoves.empty()&&(!enemyScene||residentScene)){std::cerr<<"--enemy-player-at requires an isolated enemy-ID capture\n";return 2;}
    if(!enemyPlayerAttacks.empty()&&(!enemyScene||residentScene)){std::cerr<<"--enemy-player-attack requires an isolated enemy-ID capture\n";return 2;}
    if(!enemyProbeShots.empty()&&(!enemyScene||residentScene)){std::cerr<<"--enemy-shot requires an isolated enemy-ID capture\n";return 2;}
    if(!enemyItems.empty()&&(!enemyScene||residentScene)){std::cerr<<"--enemy-item requires an isolated enemy-ID capture\n";return 2;}
    if((!enemyClears.empty()||!enemyReentries.empty())&&(!enemyScene||residentScene)){std::cerr<<"Room lifecycle controls require an isolated enemy-ID capture\n";return 2;}
    if(!enemyPlayerSide.empty()&&(!enemyScene||residentScene)){std::cerr<<"--enemy-player-side requires an isolated enemy-ID capture\n";return 2;}
    if(enemySegment>=0&&(!enemyScene||residentScene)){std::cerr<<"--enemy-segment requires an isolated enemy-ID capture\n";return 2;}
    if(residentScene&&(!enemyTerrain.empty()||enemyCount!=1||enemyFlooded||!enemyFires.empty()||!enemyHits.empty())) {
        std::cerr<<"Resident captures preserve generated populations and terrain; use enemy-ID for isolated mutation probes\n";return 2;
    }
    if(!enemyHits.empty()&&!enemyScene) {std::cerr<<"--enemy-hit requires an isolated --smoke --scene enemy-ID capture\n";return 2;}
    if(!enemyStatuses.empty()&&(!smoke||!enemyScene||residentScene)) {std::cerr<<"--enemy-status requires an isolated --smoke --scene enemy-ID capture\n";return 2;}
    if(!enemyTerrain.empty()&&!enemyScene) {std::cerr<<"--enemy-terrain requires an isolated enemy capture\n";return 2;}
    if(enemyCameraFollow&&(!smoke||!enemyScene)){std::cerr<<"--enemy-camera-follow requires an enemy/resident smoke capture\n";return 2;}
    if(enemyCount!=1&&!enemyScene) {std::cerr<<"--enemy-count requires an isolated enemy capture\n";return 2;}
    if((enemyFlooded||!enemyFires.empty())&&!enemyScene){std::cerr<<"Fire/flood probes require an isolated enemy capture\n";return 2;}
    if (!enemyScene && scene != "combat" && scene != "hub" && scene != "key" && scene != "power" && scene != "reward" &&
        scene != "boss" && scene != "summary" && scene != "empty" && scene != "cheats" &&
        scene != "demolition" && scene != "demolition-open" && scene != "demolition-run" &&
        scene != "build-bank" && scene != "build-shrapnel" && scene != "build-return" && scene != "build-braid" &&
        scene != "ridgeback" && scene != "ridgeback-late" && scene != "ridgeback-fight" &&
        scene != "service-exchange" && scene != "service-surgeon" && scene != "service-bargain" && scene != "boss-reward" &&
        scene != "foreman" && scene != "foreman-late" && scene != "foreman-fight" &&
        scene != "marshal" && scene != "marshal-late" && scene != "marshal-fight" &&
        scene != "profile-quarry" && scene != "profile-works" && scene != "profile-storm") {
        std::cerr << "Unknown smoke scene: " << scene << '\n';
        return 2;
    }
    const bool guardianScene=scene.starts_with("ridgeback")||scene.starts_with("foreman")||scene.starts_with("marshal");
    if (smoke && (enemyScene || guardianScene || scene.starts_with("profile-") || scene.starts_with("service-") || scene=="boss-reward") &&
        (themeChoice != dw::ThemeChoice::Canyon || expeditionPacing == dw::ExpeditionPacing::Classic)) {
        std::cerr << "Canyon progression scenes require --theme canyon and a non-Classic pacing preset.\n";
        return 2;
    }
    // Scripted verification never modifies the player's campaign by default.
    if (smoke || benchmark || startEditor || startCinematic) {
        if (!explicitSave)
            save = std::filesystem::temp_directory_path() /
                   ("deathward-check-" +
                    std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + ".save");
    }
    try {
        dw::prepareBrowserFiles();
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
        InitWindow(1440, 900, "DeathWard | The consequences remain");
        if (!IsWindowReady())
            throw std::runtime_error("Cannot create a graphics window");
#ifndef __EMSCRIPTEN__
        // Web sizing comes from the canvas below. raylib's minimum-size call
        // resizes it to the entire browser window, including the HTML toolbar.
        SetWindowMinSize(1024, 640);
#endif
        SetExitKey(KEY_NULL);
#ifdef __EMSCRIPTEN__
        // The browser schedules frames. Never busy-wait or nanosleep on its UI thread.
        SetTargetFPS(0);
#else
        SetTargetFPS(benchmark ? 0 : 60);
#endif
        dw::AudioSystem audio;
        const auto preferencesDirectory = slotsDirectory.empty() ? save.parent_path() : slotsDirectory;
        const auto audioPreferences =
            smoke || benchmark || startEditor || startCinematic ? std::filesystem::path{} : preferencesDirectory / "audio.cfg";
        const auto visualPreferences =
            smoke || benchmark || startEditor || startCinematic ? std::filesystem::path{} : preferencesDirectory / "visual.cfg";
        auto audioSettings = dw::loadAudioSettings(audioPreferences);
        auto visualSettings = dw::loadVisualSettings(visualPreferences);
        if (canyonRiver)
            visualSettings.canyonRiver = *canyonRiver;
        const auto audioStatus = audio.initialize(!mute && (!(smoke || benchmark) || explicitAudio));
        bool menuExit = false;
        if (fullExperience) {
            dw::FrontEnd frontEnd(slotsDirectory.empty() ? save.parent_path() / "slots" : slotsDirectory,
                                  audioPreferences, visualPreferences, audioSettings, visualSettings, audioStatus);
#ifdef __EMSCRIPTEN__
            EM_ASM({ if (Module.gameReady) Module.gameReady(); });
#endif
            while (!frontEnd.launch && !frontEnd.quit) {
#ifdef __EMSCRIPTEN__
                nextBrowserFrame();
                const int width = EM_ASM_INT({ return Math.round(Module.canvas.clientWidth); });
                const int height = EM_ASM_INT({ return Math.round(Module.canvas.clientHeight); });
                if (width > 0 && height > 0 && (width != GetScreenWidth() || height != GetScreenHeight())) {
                    SetWindowSize(width, height + 1); SetWindowSize(width, height);
                }
#else
                if (WindowShouldClose()) { frontEnd.quit = true; break; }
#endif
                frontEnd.update(GetFrameTime());
                BeginDrawing(); frontEnd.draw(); EndDrawing();
                frontEnd.publish();
                dw::AudioFrame frame;
                frame.dt = GetFrameTime(); frame.context = 0x46524f4e54;
                frame.environment = dw::AudioEnvironment::Canyon; frame.footsteps = false;
                frame.music = frontEnd.page == dw::FrontPage::Studio ? dw::MusicScene::Silent : dw::MusicScene::Canyon;
                audio.update(frame, frontEnd.audioSettings, {});
            }
            menuExit = frontEnd.quit;
            if (frontEnd.launch) {
                save = frontEnd.launch->file;
                intro = frontEnd.launch->opening;
                initialHub = intro ? dw::HubKind::BlackCreek : dw::HubKind::Redstone;
                audioSettings = frontEnd.audioSettings; visualSettings = frontEnd.visualSettings;
            }
        }
        if (menuExit) {
            audio.unload(); CloseWindow();
#ifdef __EMSCRIPTEN__
            EM_ASM({ Module.gameFinished = true; if (Module.showEnd) Module.showEnd(); });
#endif
            return 0;
        }
        dw::Game game(save, initialHub);
        game.sandstorm = sandstorm || game.arrivalActive();
        game.themeChoice = themeChoice;
        game.expeditionPacing = expeditionPacing;
        if (smoke || benchmark) game.seedText = "1866";
        game.audioSettings = audioSettings; game.visualSettings = visualSettings; game.audioStatus = audioStatus;
        game.visualStyle = styleChoice.value_or(dw::VisualStyle::Original);
        auto savedAudioSettings = audioSettings;
        auto savedVisualSettings = visualSettings;
        for (const auto hub : dw::Hubs)
            if (upgradeTownNavigation(hub) && hub == game.activeHub) {
                if (!game.town.load(game.hubDirectory() / "town.nav") || !game.reloadTownObjects())
                    throw std::runtime_error("Could not reload the upgraded town navigation.");
                game.updateCamera(1);
            }
        if(startExpedition&&!startEditor&&!startCinematic&&!intro&&!fullExperience&&!smoke&&!benchmark) {
            game.launch(true);
            if(!game.run)throw std::runtime_error(game.error);
        }
        dw::Renderer renderer;
        const dw::Game::SceneryPicker pickScenery = [&](const auto &run, const auto &camera, Ray ray) {
            return renderer.pickScenery(run, camera, ray);
        };
        dw::TownEditor editor;
        dw::CinematicEditor cinematic;
        if (startEditor) {
            editor.sandstorm = game.sandstorm;
            const auto directory = editorDirectory.empty() ? game.hubDirectory() : editorDirectory;
            if (!editor.open(directory, game.camera, editorDirectory.empty() ? game.animals.placements() : std::vector<dw::AnimalPlacement>{}))
                throw std::runtime_error(editor.status);
            SetWindowTitle("DeathWard | Town editor");
        }
        if (startCinematic || intro) {
            if (!cinematic.open(intro?dw::CinematicEditor::openingDirectory():editorDirectory.empty()?game.hubDirectory():editorDirectory,game.camera,
                                 startEditor&&!intro?&editor.document():nullptr,sequenceFile))
                throw std::runtime_error(cinematic.status);
            if(cinematicTime) cinematic.seek(*cinematicTime);
            if(intro&&!startCinematic)cinematic.playIntro(!cinematicTime.has_value());
            else if(smoke&&!cinematicTime) cinematic.play();
            SetWindowTitle(intro&&!startCinematic?"DeathWard | Westbound":"DeathWard | Cinematic Editor");
        }
        if (!startCinematic && !intro && ((smoke && scene != "hub") || benchmark)) {
            game.launch(true);
            if (!game.run)
                throw std::runtime_error(game.error);
            if(smoke&&((guardianScene&&scene.ends_with("-late"))||scene.starts_with("profile-"))) {
                int floor=game.run->expedition.floorCount-1;
                if(scene.starts_with("profile-")) {
                    const int band=scene=="profile-quarry"?1:scene=="profile-works"?2:3;
                    floor=0;while(game.run->expedition.profileOnFloor(floor).band<band)++floor;
                }
                game.run=std::make_unique<dw::Simulation>(1866,1,game.campaign.data().world,dw::MissionTheme::Canyon,
                    canyonRiver.value_or(true),false,dw::WitnessAccount::None,floor,expeditionPacing);
            }
            game.run->godMode = true;
            game.run->debugScenario = true;
            if (benchmark)
                game.run->startStress();
            else {
                if (scene == "combat" || scene == "cheats")
                    game.run->jumpDebug(2);
                if (scene == "combat" || scene == "boss" || scene == "summary")
                    for (int i = 0; i < dw::ItemCount; ++i)
                        game.run->grant(dw::ItemId(i));
            }
            if (smoke && scene == "boss")
                game.run->startBoss();
            if(smoke&&guardianScene) {
                game.run->startBoss(scene.starts_with("foreman")?dw::BossKind::PowderForeman:
                    scene.starts_with("marshal")?dw::BossKind::StormMarshal:dw::BossKind::Ridgeback);
                game.run->player.position=dw::add(game.run->arena.rooms.back().center,{0,0,9.7f});
                if(scene.ends_with("-late")&&game.run->boss()) {
                    auto *boss=game.run->findEnemy(game.run->boss()->id);boss->hp=boss->maxHp*.49f;
                }
                if(scene.ends_with("-fight")) {game.run->godMode=false;game.run->dynamite=0;}
            }
            if(smoke&&scene.starts_with("profile-"))game.run->jumpDebug(2);
            if(residentScene) {
                const auto seed=residentSeed.value_or(1866);const int floor=residentFloor.value_or(0);
                // Match the Rourke account used by the seeded stage regression.
                const dw::ExpeditionPlan plan(seed,false,dw::WitnessAccount::Rourke,expeditionPacing);
                if(floor>=plan.floorCount)throw std::runtime_error("Requested resident floor exceeds seeded expedition length");
                game.run=std::make_unique<dw::Simulation>(seed,1,game.campaign.data().world,dw::MissionTheme::Canyon,
                    canyonRiver.value_or(true),false,dw::WitnessAccount::Rourke,floor,expeditionPacing);
                int selectedRoom=-1;
                for(int room=1;room<game.run->finalRoom()&&selectedRoom<0;++room) {
                    const auto encounter=game.run->floorEncounter(room);const auto &actors=game.run->roomEnemies(room);
                    for(size_t slot=0;slot<actors.size();++slot) {
                        // Optional hazards follow the ordinary threat slots and
                        // have their own seeded pool, without a replacement source.
                        const auto source=slot<encounter.originalMonsters.size()?encounter.originalMonsters[slot]:actors[slot].monster;
                        if(actors[slot].monster==*enemyScene&&(!residentFrom||source==*residentFrom)) {
                            selectedRoom=room;probeEnemy=actors[slot].id;probeOriginal=source;
                            probeStart=actors[slot].position;break;
                        }
                    }
                }
                // Dedicated bosses have no ordinary encounter slots. Preserve the
                // seeded boss form and all attached components in this capture too.
                if(selectedRoom<0&&!residentFrom)for(const auto &actor:game.run->roomEnemies(game.run->finalRoom()))
                    if(actor.monster==*enemyScene&&actor.kind==dw::EnemyKind::Boss) {
                        selectedRoom=game.run->finalRoom();probeEnemy=actor.id;probeOriginal=actor.monster;
                        probeStart=actor.position;break;
                    }
                if(selectedRoom<0)throw std::runtime_error("Requested natural resident/source does not occur in this seeded floor");
                game.run->jumpDebug(selectedRoom);game.run->godMode=true;game.run->debugScenario=true;
                // Keep every actual resident, its cooldown and position. Only the
                // invulnerable spectator moves to a legal nearby viewing point.
                for(int n=0;n<24;++n) {
                    auto point=dw::add(probeStart,dw::rotateY({0,0,7},float(n)*dw::Pi/12));point.y=.85f;
                    if(game.run->arena.roomAt(point)!=selectedRoom||game.run->arena.blocked(point,.48f)||
                        !game.run->arena.sight(point,probeStart))continue;
                    if(std::any_of(game.run->enemies.begin(),game.run->enemies.end(),[&](const auto &e){return dw::distance(point,e.position)<3;}))continue;
                    game.run->player.position=point;break;
                }
                game.updateCamera(1);
                std::cout<<"RESIDENT_PROBE seed="<<seed<<" floor="<<floor<<" room="<<selectedRoom
                    <<" source="<<dw::monsterIdText(probeOriginal)<<" target="<<dw::monsterIdText(*enemyScene)
                    <<" scorched="<<(game.run->arena.profile.variant==dw::FloorVariant::Scorched)
                    <<" patches="<<game.run->arena.scorchPatches.size()<<'\n';
            }
            if(enemyScene&&!residentScene) {
                if(!game.run->content->monster(*enemyScene))throw std::runtime_error("Enemy is not implemented: "+dw::monsterIdText(*enemyScene));
                if(enemyBossForm&&!game.run->content->bossFormAllowed(*enemyScene,*enemyBossForm))throw std::runtime_error("This enemy does not support that boss form");
                int probeRoom=game.run->finalRoom();Vector3 riverStart{},riverGoal{};
                if(enemyTerrain=="river") {
                    auto crossing=[&] {
                        const auto &arena=game.run->arena;const auto &field=*arena.canyon;
                        if(field.riverKind!=dw::CanyonRiverKind::Interior)return false;
                        for(size_t i=1;i+1<field.river.size();++i) {
                            const auto &at=field.river[i];if(field.height(at.position.x,at.position.z)>-.4f)continue;
                            const auto tangent=dw::unit(dw::sub(field.river[i+1].position,field.river[i-1].position));
                            const Vector3 side{-tangent.z,0,tangent.x};
                            auto a=dw::add(at.position,dw::mul(side,at.width+2.5f));
                            auto b=dw::sub(at.position,dw::mul(side,at.width+2.5f));a.y=b.y=.85f;
                            const int room=arena.roomAt(a);
                            if(room<0||arena.roomAt(b)!=room||arena.blocked(a,.8f)||arena.blocked(b,.8f)||
                                !arena.flightClear(a,b,.6f,room)||!arena.sight(a,b)||arena.clear(a,b,.48f))continue;
                            probeRoom=room;riverStart=a;riverGoal=b;return true;
                        }
                        return false;
                    };
                    bool found=crossing();
                    for(uint64_t seed=0;seed<16&&!found;++seed) {
                        game.run=std::make_unique<dw::Simulation>(seed,1,game.campaign.data().world,dw::MissionTheme::Canyon,
                            true,false,dw::WitnessAccount::None,0,expeditionPacing);
                        found=crossing();
                    }
                    if(!found)throw std::runtime_error("No safe interior-river flight probe found");
                    game.run->godMode=true;
                }
                // Reuse the flat canyon boss clearing for comparable original-style captures.
                game.run->jumpDebug(probeRoom);game.run->clearRoomDebug();
                game.run->debugScenario=true;game.run->roomClear=false;game.run->bossKilled=false;
                game.run->rooms[size_t(probeRoom)].cleared=false;game.run->stats={};game.run->moneyPickups.clear();
                game.run->rooms[size_t(probeRoom)].bossPaid=false;
                game.run->arena.rooms[size_t(probeRoom)].flooded=enemyFlooded;
                auto center=game.run->arena.rooms[size_t(probeRoom)].center;center.y=.85f;
                game.run->player.position=dw::add(center,{0,0,8});
                if(enemyPlayerSide=="above")game.run->player.position=dw::add(center,{0,0,-8});
                if(enemyPlayerSide=="left")game.run->player.position=dw::add(center,{-8,0,.4f});
                if(enemyPlayerSide=="right")game.run->player.position=dw::add(center,{8,0,.4f});
                if(enemyPlayerSide=="diagonal")game.run->player.position=dw::add(center,{8,0,8});
                if(enemyTerrain=="cover") {
                    game.run->arena.floorProps.push_back({dw::StoryPropKind::Crate,
                        {{center.x-1,0,center.z-1},{center.x+1,2,center.z+1}}});
                    game.run->arena.rebuildWalls();
                    if(enemyScene->type==18||game.run->content->headShooter(*enemyScene)||
                        game.run->content->rottenGaper(*enemyScene)||game.run->content->smallMaggot(*enemyScene)||game.run->content->gaper(*enemyScene)||game.run->content->headless(*enemyScene)||game.run->content->faceless(*enemyScene)||game.run->content->danny(*enemyScene)||game.run->content->hardy(*enemyScene)||game.run->content->strider(*enemyScene)||game.run->content->rockSpider(*enemyScene)||game.run->content->longLegs(*enemyScene)||
                        game.run->content->sack(*enemyScene)||game.run->content->boil(*enemyScene)||
                        game.run->content->spitty(*enemyScene)||game.run->content->cardinalWalker(*enemyScene)||
                        game.run->content->brain(*enemyScene)||game.run->content->baby(*enemyScene))center.z-=5;
                } else if(enemyTerrain=="hop-cover") {
                    if(!game.run->content->hop(*enemyScene)&&!game.run->content->targetHop(*enemyScene))throw std::runtime_error("hop-cover requires a configured hopper");
                    game.run->arena.floorProps.push_back({dw::StoryPropKind::Crate,
                        {{center.x-1.5f,0,center.z-.6f},{center.x+1.5f,2,center.z+.6f}}});
                    game.run->arena.rebuildWalls();game.run->player.position=dw::add(center,{0,0,3});center.z-=2;
                } else if(enemyTerrain=="dung") {
                    if(!game.run->content->dung())throw std::runtime_error("dung capture requires an installed dung profile");
                    const auto &p=*game.run->content->dung();dw::Breakable pile;
                    pile.id=0xdf000001;pile.room=probeRoom;pile.kind=dw::BreakableKind::Dung;
                    pile.bounds={{center.x-p.halfWidth,0,center.z-p.halfWidth},{center.x+p.halfWidth,p.height,center.z+p.halfWidth}};
                    pile.health=pile.initialHealth=p.hits;pile.rewardPosition=center;
                    game.run->arena.breakables.push_back(pile);game.run->arena.rebuildWalls();
                } else if(enemyTerrain=="river") {center=riverStart;game.run->player.position=riverGoal;}
                probeStart=center;
                for(const auto &item:enemyItems) {
                    if(!game.run->content->item(item))throw std::runtime_error("Test item is not installed: "+dw::itemKeyText(item));
                    game.run->grant(item);
                }
                for(int n=0;n<enemyCount;++n) {
                    const auto at=enemyCount==1?center:dw::add(center,dw::rotateY({4,0,0},float(n)*2*dw::Pi/float(enemyCount)));
                    const auto *fly=game.run->content->flyBomb(*enemyScene);
                    auto entity=fly&&fly->orbitOwner?game.run->spawnBombFlyHost(*enemyScene,at):
                        game.run->spawnMonster(*enemyScene,at,0,-1,enemyBossForm.value_or(dw::BossForm::Normal));
                    if(!entity)throw std::runtime_error("Failed to create enemy capture");
                    if(fly&&fly->orbitOwner) {
                        const auto owner=entity;
                        for(const auto &child:game.run->enemies)if(child.componentOwner==owner&&child.componentSlot==0){entity=child.id;break;}
                    }
                    if(enemySegment>=0) {
                        const auto &groups=game.run->rooms[size_t(probeRoom)].segmented;
                        if(groups.empty()||size_t(enemySegment)>=groups.back().allMembers.size())throw std::runtime_error("Capture segment does not exist");
                        entity=groups.back().allMembers[size_t(enemySegment)];
                    }
                    if(n==0)probeEnemy=entity;
                    auto *enemy=game.run->findEnemy(entity);enemy->cooldown=0;
                    if(!enemyBombProfile.empty()) {
                        enemy->cooldown=1000;
                        const auto start=dw::add(enemy->position,{0,.5f,0});
                        const auto target=dw::add(center,{3,0,-4});
                        if(!game.run->throwEnemyBomb(enemyBombProfile,entity,start,target))throw std::runtime_error("Failed to create hostile bomb component probe");
                    }
                    if(!enemy->segmentedEncounter&&!game.run->content->boomFly(enemy->monster))enemy->facing={1,0,0};
                    enemy->auxiliary=1;
                    if(const auto *statue=game.run->content->statue(*enemyScene)) {
                        if(statue->attack!=dw::StatueAttack::Quake)enemy->facing=enemy->statueFacing={0,0,1};
                        else enemy->facing=enemy->statueFacing;
                    }
                }
                if(game.run->content->statue(*enemyScene)) {
                    const auto at=dw::add(center,{-5,0,5});
                    if(game.run->arena.blocked(at,.8f))throw std::runtime_error("Statue probe plate footprint is blocked");
                    game.run->rooms[size_t(probeRoom)].plates={{{at.x,.85f,at.z},false}};
                }
            }
            if(smoke&&scene.starts_with("service-")) {
                int at=-1;for(int i=0;i<game.run->arena.roomCount();++i)
                    if(game.run->arena.rooms[size_t(i)].kind==dw::RoomKind::Service){at=i;break;}
                if(at<0)throw std::runtime_error("No service room in smoke floor");
                game.run->arena.rooms[size_t(at)].service=scene=="service-exchange"?dw::RoomService::Exchange:
                    scene=="service-surgeon"?dw::RoomService::Surgeon:dw::RoomService::Smuggler;
                game.run->rooms[size_t(at)].offers={dw::ItemId::Judas,dw::ItemId::Cap};
                game.run->jumpDebug(at);game.run->player.position=game.run->arena.rooms[size_t(at)].objective;
                game.run->keys=2;game.run->moneyCollected=100;game.run->player.hp=50;game.run->openShop();
            }
            if(smoke&&scene=="boss-reward") {
                game.run->startBoss();game.run->killAll();game.run->clearRoom();
                game.run->player.position=game.run->rewardPosition(game.run->room);game.run->interact();
            }
            if(smoke&&scene.starts_with("build-")) {
                game.run->jumpDebug(2);
                const auto build=scene=="build-bank"?std::vector<dw::ItemId>{dw::ItemId::Ricochet,dw::ItemId::Rail,dw::ItemId::Lodestone}:
                    scene=="build-shrapnel"?std::vector<dw::ItemId>{dw::ItemId::Scatter,dw::ItemId::Split,dw::ItemId::Cap}:
                    scene=="build-return"?std::vector<dw::ItemId>{dw::ItemId::Return,dw::ItemId::Ricochet,dw::ItemId::Lodestone}:
                    std::vector<dw::ItemId>{dw::ItemId::Braid};
                for(auto item:build)game.run->grant(item);
            }
            if (smoke && (scene.starts_with("demolition")||scene=="build-braid")) {
                const auto cache=game.run->arena.supplyCache;
                if(cache.room<0)throw std::runtime_error("No supply cache on this floor");
                game.run->jumpDebug(cache.room);game.run->clearRoomDebug();
                game.run->player.position=cache.approach;
                if(scene=="demolition-open")for(int i=0;i<2;++i) {
                    dw::Event blast;blast.type=dw::EventType::Explosion;blast.position=cache.approach;
                    blast.damage=100;blast.radius=4.5f;blast.demolition=dw::Demolition::SpentDynamite;
                    game.run->queueRoot(blast);game.run->drainEvents();
                }
            }
            if (smoke && scene == "cheats")
                game.debug = true;
            if (smoke && scene == "empty") {
                for (int i = 0; i < game.run->arena.roomCount(); ++i)
                    if (game.run->arena.rooms[size_t(i)].kind == dw::RoomKind::Empty) {
                        game.run->jumpDebug(i);
                        game.run->announce("QUIET ROOM / no enemies. Explore the open passages.", 5);
                        break;
                    }
            }
            if (smoke && scene == "key") {
                game.run->enterRoom(game.run->arena.keys.front().room);
                game.run->player.position = game.run->arena.rooms[size_t(game.run->room)].center;
                game.run->clearRoomDebug();
            }
            if (smoke && (scene == "power" || scene == "reward")) {
                const int passage = game.run->arena.rooms[game.run->arena.roomCount() - 2].passages.front();
                game.run->arena.passages[size_t(passage)].locked = false;
                game.run->enterRoom(game.run->arena.roomCount() - 2);
                game.run->player.position = game.run->arena.rooms[size_t(game.run->room)].center;
            }
            if (smoke && scene == "reward") {
                game.run->enterRoom(game.run->arena.roomCount() - 2);
                game.run->player.position = game.run->arena.rooms[size_t(game.run->room)].objective;
                game.run->interact();
            }
            if (smoke && scene == "summary") {
                game.run->rescued = true;
                game.run->bossKilled = true;
                game.finish(dw::EndReason::Victory);
            }
        }
        bool artCompare = artPoc;
        bool styleCompare = styleChoice.has_value();
        std::vector<double> timings;
        double simulationMs = 0, drawMs = 0, presentMs = 0;
        size_t minEnemies = 1000, minProjectiles = 100000;
        uint64_t totalSuppressed = 0, maxProjectiles = 0, maxChain = 0, totalKills = 0;
        int frame = 0;
#ifdef __EMSCRIPTEN__
        EM_ASM({
            if (Module.gameReady)
                Module.gameReady();
        });
#endif
        while (!game.quit) {
#ifdef __EMSCRIPTEN__
            nextBrowserFrame();
            const int browserWidth = EM_ASM_INT({ return Math.round(Module.canvas.clientWidth); });
            const int browserHeight = EM_ASM_INT({ return Math.round(Module.canvas.clientHeight); });
            if (browserWidth > 0 && browserHeight > 0 &&
                (browserWidth != GetScreenWidth() || browserHeight != GetScreenHeight())) {
                // raylib's DOM callback measures the entire browser, while
                // GLFW caches its own dimensions. Force a callback even when
                // the canvas happens to match GLFW's original 1440x900 size.
                SetWindowSize(browserWidth, browserHeight + 1);
                SetWindowSize(browserWidth, browserHeight);
            }
#else
            if (WindowShouldClose()) {
                if (cinematic.active)
                    cinematic.requestClose(true);
                else if (editor.active)
                    editor.requestClose(true);
                else
                    break;
            }
#endif
            if (editor.quitRequested || cinematic.quitRequested)
                break;
#ifdef __EMSCRIPTEN__
            if (EM_ASM_INT({
                    const pause = Module.pauseRequested || document.hidden || !document.hasFocus();
                    Module.pauseRequested = false;
                    return pause;
                })) {
                game.paused = true;
                if(cinematic.active && cinematic.preview().playing()) cinematic.play();
            }
#endif
            if (game.editorRequested) {
                game.editorRequested = false;
                editor.sandstorm = game.sandstorm;
                if (!editor.open(game.hubDirectory(), game.camera, game.animals.placements()))
                    game.error = editor.status;
                else
                    SetWindowTitle("DeathWard | Town editor");
            }
            if (editor.cinematicRequested) {
                editor.cinematicRequested=false;
                if(!cinematic.open(editor.directory(),editor.camera,&editor.document()))
                    editor.status=cinematic.status;
                else {++game.audioContext;SetWindowTitle("DeathWard | Cinematic Editor");}
            }
            if(cinematic.openingRequested) {
                cinematic.openingRequested=false;
                if(!cinematic.open(dw::CinematicEditor::openingDirectory(),game.camera))game.error=cinematic.status;
            }
            // F6 is otherwise a mission cheat; comparisons are confined to hubs/editor.
            if (game.visualStyle != dw::VisualStyle::Original) artPoc = artCompare = false;
            const bool canCompareArt =
                cinematic.active || !artCompare ? false : editor.active ? dw::RedstoneArt::supports(editor.document())
                              : game.screen == dw::Screen::Hub && game.activeHub == dw::HubKind::Redstone;
            const bool canCompareStyle = !artCompare && (cinematic.active ? !cinematic.runtimeIntro() :
                                         editor.active || game.screen == dw::Screen::Hub);
            if (canCompareStyle && IsKeyPressed(KEY_F6)) {
                game.visualStyle = dw::nextVisualStyle(game.visualStyle);
                styleCompare = true;
                TraceLog(LOG_INFO, "VISUAL STYLE: %s", dw::visualStyleName(game.visualStyle));
            }
            if (canCompareArt && IsKeyPressed(KEY_F6)) {
                artCompare = true;
                artPoc = !artPoc;
                TraceLog(LOG_INFO, "ART: %s (Redstone only)", artPoc ? "weathered POC" : "original look");
            }
            renderer.artPoc = editor.artPoc = artPoc;
            renderer.visualStyle = editor.visualStyle = cinematic.visualStyle = game.visualStyle;
            const bool filming = cinematic.active;
            const bool editing = editor.active && !filming;
            const auto start = std::chrono::steady_clock::now();
            if (filming) {
                cinematic.update(smoke ? dw::Tick : GetFrameTime(),game.audioSettings);
            } else if (editing) {
                editor.update(GetFrameTime());
            } else if ((smoke || benchmark) && game.run) {
                dw::Input input;
                input.aim = game.run->arena.rooms[size_t(game.run->room)].center;
                input.fire = frame % 45 < 30;
                if (benchmark && frame % 60 == 0 && frame > 0)
                    game.run->startStress();
                if (!benchmark)
                    input.movement = {std::sin(float(frame) * 0.03f) * 0.3f, 0, 0};
                if (scene.starts_with("demolition")||scene=="build-braid") {
                    input={};
                    input.aim=game.run->arena.supplyCache.reward;
                    if(scene=="demolition-run") {
                        input.placeDynamite=frame==30||frame==190;
                        if(frame==350)input.moveTarget=game.run->arena.supplyCache.reward;
                    }
                    if(scene=="build-braid")input.placeDynamite=frame==30;
                }
                if(guardianScene) {
                    input={};
                    if(const auto *boss=game.run->boss();boss&&scene.ends_with("-fight")) {
                        const auto center=game.run->arena.rooms.back().center;
                        auto delta=dw::sub(game.run->player.position,center);delta.y=0;
                        const auto radial=dw::unit(delta);const Vector3 tangent{-radial.z,0,radial.x};
                        input.fire=true;input.aim=boss->position;
                        input.movement=dw::unit(dw::add(tangent,dw::mul(radial,std::clamp((9.7f-dw::length(delta))*.7f,-2.f,2.f))));
                        input.dodge=boss->state==dw::EnemyState::Charging&&dw::distance(boss->position,game.run->player.position)<5;
                    }
                }
                if(enemyScene) {
                    input={};
                    for(const auto &shot:enemyProbeShots)if(frame==shot.frame) {
                        dw::Event event;event.position=event.origin=dw::add(probeStart,shot.offset);
                        if(game.run->arena.blocked(event.position,.14f)||game.run->arena.roomAt(event.position)!=game.run->room)
                            throw std::runtime_error("Scripted projectile origin is outside legal capture-room floor");
                        event.direction=dw::unit(shot.velocity);event.speed=dw::length(shot.velocity);
                        event.hostile=shot.hostile;event.damage=shot.hostile?10:24;
                        game.run->queueRoot(event);game.run->drainEvents();
                    }
                    for(int at:enemyClears)if(frame==at)game.run->clearRoom();
                    for(int at:enemyReentries)if(frame==at) {
                        const int original=game.run->room;game.run->enterRoom(original?0:1);game.run->enterRoom(original);
                    }
                    for(const auto &move:enemyPlayerMoves)if(frame==move.frame) {
                        auto at=dw::add(probeStart,{move.x,0,move.z});at.y=.85f;
                        if(game.run->arena.blocked(at,.48f)||game.run->arena.roomAt(at)!=game.run->room)
                            throw std::runtime_error("Scripted player position is outside legal capture-room floor");
                        game.run->player.position=at;
                    }
                    for(const auto &attack:enemyPlayerAttacks)if(frame==attack.frame) {
                        input.fire=true;input.aim=dw::add(probeStart,{attack.x,0,attack.z});
                    }
                    for(const auto &event:enemyStatuses)if(frame==event.frame) {
                        if(event.duration==0)game.run->removeEnemyStatus(probeEnemy,event.status);
                        else if(!game.run->applyEnemyStatus(probeEnemy,event.status,event.duration))
                            throw std::runtime_error("Scripted status has no live supported recipient");
                        std::cout<<"ENEMY_STATUS frame="<<frame<<" kind="<<(event.status==dw::EnemyStatus::Fear?"fear":event.status==dw::EnemyStatus::Confusion?"confusion":event.status==dw::EnemyStatus::Freeze?"freeze":event.status==dw::EnemyStatus::Slow?"slow":event.status==dw::EnemyStatus::Poison?"poison":event.status==dw::EnemyStatus::Burn?"burn":event.status==dw::EnemyStatus::Shrink?"shrink":"charm")
                                 <<" duration="<<event.duration<<'\n';
                    }
                    for(const auto &[at,amount,kind,execution,explosion,decoy,partner]:enemyHits)if(frame==at) {
                        dw::Event hit;hit.type=dw::EventType::Damage;hit.target=probeEnemy;
                        if(partner) {
                            const auto *owner=game.run->findEnemy(probeEnemy);
                            const auto *part=owner?game.run->findEnemy(owner->partner):nullptr;
                            if(!part||!part->alive)throw std::runtime_error("No live linked partner at scripted hit frame");
                            hit.target=part->id;
                        }
                        if(decoy) {
                            const auto it=std::find_if(game.run->enemies.begin(),game.run->enemies.end(),[&](const auto &actor){
                                return actor.alive&&actor.state!=dw::EnemyState::Teleporting&&game.run->content->hornfelDecoy(actor.monster);
                            });
                            if(it==game.run->enemies.end())throw std::runtime_error("No visible decoy at scripted hit frame");
                            hit.target=it->id;
                        }
                        hit.damage=amount;hit.damageKind=kind;hit.direction={0,0,-1};hit.execution=execution;hit.debugExecution=execution;
                        if(explosion) {
                            const auto *target=game.run->findEnemy(hit.target);if(!target||!target->alive)continue;
                            hit.type=dw::EventType::Explosion;hit.position=hit.origin=target->position;hit.radius=4.5f;
                            hit.demolition=dw::Demolition::SuppliedBomb;
                        }
                        game.run->queueRoot(hit);game.run->drainEvents();
                    }
                    for(int at:enemyFires)if(frame==at)
                        if(const auto *e=game.run->findEnemy(probeEnemy);e&&e->alive)
                            game.run->addFire(e->position,1.2f,6,10,true,false);
                }
                game.run->step(input);
                game.updateCamera(dw::Tick);
                if(enemyCameraFollow) {
                    if(const auto *actor=game.run->findEnemy(probeEnemy))enemyCameraTarget=actor->position;
                    const auto delta=dw::sub(enemyCameraTarget,game.camera.target);
                    game.camera.target=enemyCameraTarget;game.camera.position=dw::add(game.camera.position,delta);
                }
                minEnemies = std::min(minEnemies, game.run->livingEnemies());
                minProjectiles = std::min(minProjectiles, game.run->projectiles.size());
                totalSuppressed = game.run->stats.suppressed;
                maxProjectiles = game.run->stats.maxProjectiles;
                maxChain = game.run->stats.maxDepth;
                totalKills = game.run->stats.kills;
            } else if (!smoke && !benchmark)
                game.update(GetFrameTime(), pickScenery);
            const auto simulated = std::chrono::steady_clock::now();
#ifdef __EMSCRIPTEN__
            if(enemyScene&&game.run) {
                const auto *enemy=game.run->findEnemy(probeEnemy);
                EM_ASM({if(Module.verify)Module.enemyProbe=({type:$0,variant:$1,subtype:$2,alive:!!$3,
                    hp:$4,state:$5,graphState:$6,x:$7,z:$8,shots:$9,projectiles:$10,threats:$11,kills:$12,entity:$13,
                    playerX:$14,playerZ:$15,actors:[],dung:[]});},
                    enemyScene->type,enemyScene->variant,enemyScene->subtype,enemy&&enemy->alive,
                    enemy?enemy->hp:0,enemy?int(enemy->state):-1,enemy?int(enemy->behavior.state):-1,
                    enemy?enemy->position.x:0,enemy?enemy->position.z:0,
                    int(game.run->stats.projectiles),int(game.run->projectiles.size()),int(game.run->roomThreats()),int(game.run->stats.kills),double(probeEnemy),
                    game.run->player.position.x,game.run->player.position.z);
                // This Emscripten version exposes at most sixteen EM_ASM arguments.
                for(const auto &prop:game.run->arena.breakables)if(prop.kind==dw::BreakableKind::Dung&&prop.room==game.run->room)
                    EM_ASM({if(Module.verify)Module.enemyProbe.dung.push({id:$0,health:$1,destroyed:!!$2,x:$3,z:$4});},
                        double(prop.id),prop.health,prop.destroyed,(prop.bounds.min.x+prop.bounds.max.x)*.5f,(prop.bounds.min.z+prop.bounds.max.z)*.5f);
                EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe,{startX:$0,startZ:$1,y:$2,playerY:$3,
                    flightBlocked:!!$4,waterBlocked:!!$5,groundBlocked:!!$6,swimBlocked:!!$7});},probeStart.x,probeStart.z,enemy?enemy->position.y:0,
                    game.run->player.position.y,enemy?game.run->arena.flightBlocked(enemy->position,enemy->radius,game.run->room):false,
                    enemy&&game.run->arena.canyon?game.run->arena.canyon->waterBlocked(enemy->position):false,
                    enemy?game.run->arena.blocked({enemy->position.x,.85f,enemy->position.z},enemy->radius):false,
                    enemy?game.run->arena.swimBlocked(enemy->position,enemy->radius,game.run->room):false);
                EM_ASM({if(Module.verify)Module.enemyProbe.resident=({natural:!!$0,source:[$1,$2,$3],
                    floor:$4,room:$5,scorched:!!$6,patches:$7});},residentScene,probeOriginal.type,probeOriginal.variant,probeOriginal.subtype,
                    game.run->arena.profile.floor,game.run->room,game.run->arena.profile.variant==dw::FloorVariant::Scorched,
                    int(game.run->arena.scorchPatches.size()));
                EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.resident,{variant:$0,dampPatches:$1});},
                    int(game.run->arena.profile.variant),int(game.run->arena.dampPatches.size()));
                EM_ASM({if(Module.verify)Module.enemyProbe.charge=({fx:$0,fz:$1,recovery:$2});},
                    enemy?enemy->facing.x:0,enemy?enemy->facing.z:0,enemy?enemy->chargeRecovery:0);
                EM_ASM({if(Module.verify)Module.enemyProbe.boss=({form:$0,parts:$1,attack:$2,cycles:$3});},
                    enemy?int(enemy->bossForm):0,enemy?int(enemy->bossParts):0,enemy?enemy->bossAttack:0,enemy?enemy->bossCycles:0);
                for(const auto &actor:game.run->enemies)if(actor.alive) {
                    EM_ASM({if(Module.verify)Module.enemyProbe.actors.push({type:$0,variant:$1,subtype:$2,
                        hp:$3,maxHp:$4,state:$5,x:$6,z:$7,entity:$8,summoner:$9,vx:$10,vz:$11,radius:$12,y:$13,vy:$14,formation:$15});},actor.monster.type,actor.monster.variant,actor.monster.subtype,
                        actor.hp,actor.maxHp,int(actor.state),actor.position.x,actor.position.z,double(actor.id),double(actor.summoner),actor.velocity.x,actor.velocity.z,actor.radius,actor.position.y,actor.velocity.y,double(actor.formation));
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.actors.at(-1),{componentOwner:$0,componentSlot:$1});},double(actor.componentOwner),actor.componentSlot);
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.actors.at(-1),{carrier:$0,environment:!!$1,spent:!!$2,destructionPending:!!$3});},
                        double(actor.railCarrier),bool(actor.environment),actor.environment&&actor.environment->spent,actor.environment&&actor.environment->destructionPending);
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.actors.at(-1),{followParent:$0,followTick:$1});},
                        double(actor.flyFollow?actor.flyFollow->parent:0),double(actor.flyFollow?actor.flyFollow->tick:0));
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.actors.at(-1),{bossGroup:$0,half:$1,attack:$2,step:$3,cycles:$4});},
                        double(actor.bossGroup),actor.bossHalf,actor.bossAttack,actor.bossStep,actor.bossCycles);
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.actors.at(-1),{friendly:!!$0,hurtCooldown:$1});},actor.friendly,actor.companionHurtCooldown);
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.actors.at(-1),{swimming:!!$0,swimAcceleration:$1,hopFrame:$2,
                        thrown:!!$3,throwFrame:$4,throwDuration:$5,lift:$6});},actor.swimmer&&actor.swimmer->swimming,
                        actor.swimmer?actor.swimmer->acceleration:0,actor.swimmer?actor.swimmer->hopFrame:-1,
                        bool(actor.thrownOffspring),actor.thrownOffspring?actor.thrownOffspring->frames:0,
                        actor.thrownOffspring?actor.thrownOffspring->duration:0,actor.lift);
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.actors.at(-1),{segmented:$0,armor:$1,head:!!$2,settling:!!$3});},double(actor.segmentedEncounter),actor.segmentArmor,actor.segmentHead,actor.segmentSettling);
                    if(actor.willo)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).willo=({angle:$0,slot:$1,
                        attackSlot:$2,attackFrame:$3,warning:!!$4,fired:!!$5});},actor.willo->angle,actor.willo->slot,
                        actor.willo->attackSlot,actor.willo->attackFrame,actor.willo->warning,actor.willo->fired);
                    if(actor.strider)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).strider=({frame:$0,
                        chasing:!!$1,strokes:$2,angle:$3});},actor.strider->frame,actor.strider->chasing,actor.strider->strokes,actor.strider->angle);
                    if(actor.swarmSpider)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).swarmSpider=({frame:$0,
                        kind:$1,airborne:!!$2,hops:$3,launchX:$4,launchZ:$5});},actor.swarmSpider->frame,actor.swarmSpider->kind,
                        actor.swarmSpider->airborne,actor.swarmSpider->hops,actor.swarmSpider->launch.x,actor.swarmSpider->launch.z);
                    if(actor.longLegs)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).longLegs=({frame:$0,
                        attacks:$1,evade:$2,fired:!!$3,ready:!!$4});},actor.longLegs->frame,actor.longLegs->attacks,
                        actor.longLegs->evadeChecks,actor.longLegs->fired,actor.longLegs->targetReady);
                    if(actor.maw)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).maw=({frame:$0,fired:!!$1,deathPending:!!$2});},
                        actor.maw->cast.attackFrame,actor.maw->cast.fired,actor.maw->deathPending);
                    if(actor.brain)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).brain=({
                        ticks:$0,frame:$1,charging:!!$2,blocked:!!$3,charges:$4,stops:$5,creep:$6,pending:!!$7,
                        dx:$8,dz:$9,mx:$10,mz:$11,targetX:$12,targetZ:$13});},double(actor.brain->ticks),actor.brain->walkFrame,
                        actor.brain->charging,actor.brain->blocked,double(actor.brain->charges),double(actor.brain->stops),
                        double(actor.brain->creepPatches),bool(actor.brain->pendingCreep),actor.brain->chargeDirection.x,
                        actor.brain->chargeDirection.z,actor.brain->momentum.x,actor.brain->momentum.z,
                        actor.brain->predictedTarget.x,actor.brain->predictedTarget.z);
                    if(actor.linkedHead)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).linkedHead=({
                        ticks:$0,extended:!!$1,timer:$2,throws:$3,returns:$4,neckCount:$5,deathPending:!!$6,
                        mx:$7,mz:$8,targetX:$9,targetZ:$10});},double(actor.linkedHead->ticks),actor.linkedHead->extended,
                        actor.linkedHead->timer,double(actor.linkedHead->throws),double(actor.linkedHead->returns),
                        actor.linkedHead->neckCount,actor.linkedHead->deathPending,actor.linkedHead->momentum.x,
                        actor.linkedHead->momentum.z,actor.linkedHead->predictedTarget.x,actor.linkedHead->predictedTarget.z);
                    if(actor.vis)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).vis=({
                        ticks:$0,frame:$1,fired:!!$2,volleys:$3,dx:$4,dz:$5,walkFrame:$6});},
                        double(actor.vis->ticks),actor.vis->attackFrame,actor.vis->fired,double(actor.vis->volleys),
                        actor.vis->heading.x,actor.vis->heading.z,actor.vis->walkFrame);
                    if(actor.guts)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).guts=({
                        ticks:$0,direction:$1,windup:$2,recovery:$3,charging:!!$4,turns:$5,charges:$6,stops:$7,
                        patches:$8,pending:!!$9,multiplier:$10,frame:$11,dx:$12,dz:$13});},
                        double(actor.guts->ticks),actor.guts->direction,actor.guts->windup,actor.guts->recovery,
                        actor.guts->charging,double(actor.guts->turns),double(actor.guts->charges),double(actor.guts->stops),
                        double(actor.guts->creepPatches),bool(actor.guts->pendingCreep),actor.guts->multiplier,
                        actor.guts->rollFrame,actor.guts->chargeDirection.x,actor.guts->chargeDirection.z);
                    if(actor.returningBody)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).returningBody=({
                        frame:$0,clock:$1,initialX:$2,initialZ:$3});},actor.returningBody->frame,actor.returningBody->clock,
                        actor.returningBody->initialVelocity.x,actor.returningBody->initialVelocity.z);
                    if(actor.baby)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).baby=({
                        ticks:$0,phase:$1,frame:$2,attackFrame:$3,fired:!!$4,cooldown:$5,charge:$6,
                        intangible:!!$7,visibility:$8,volleys:$9,teleports:$10,dashes:$11,dx:$12,dz:$13});},
                        double(actor.baby->ticks),int(actor.baby->phase),actor.baby->frame,actor.baby->attackFrame,
                        actor.baby->fired,actor.baby->cooldown,actor.baby->teleportCharge,actor.baby->intangible,
                        actor.baby->visibility,double(actor.baby->volleys),double(actor.baby->teleports),double(actor.baby->dashes),
                        actor.baby->dashDirection.x,actor.baby->dashDirection.z);
                    if(actor.adultLeech)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).adultLeech=({
                        ticks:$0,phase:$1,frame:$2,intangible:!!$3,visibility:$4,charges:$5,impacts:$6,burrows:$7,
                        landings:$8,wallRings:$9,landingRings:$10,pending:$11,used:!!$12,recovery:$13});},
                        double(actor.adultLeech->ticks),int(actor.adultLeech->phase),actor.adultLeech->frame,
                        actor.adultLeech->intangible,actor.adultLeech->visibility,double(actor.adultLeech->charges),
                        double(actor.adultLeech->impacts),double(actor.adultLeech->burrows),double(actor.adultLeech->landings),
                        double(actor.adultLeech->wallRings),double(actor.adultLeech->landingRings),
                        int(actor.adultLeech->pendingShots.size()),actor.adultLeech->burrowUsed,actor.adultLeech->recovery);
                    if(actor.slide)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).slide=({
                        ticks:$0,phase:$1,frame:$2,slideFrames:$3,collisions:$4,dashes:$5,launches:$6,chains:$7,creep:$8,second:!!$9});},double(actor.slide->ticks),
                        actor.slide->phase,actor.slide->frame,actor.slide->slideFrames,actor.slide->collisions,double(actor.slide->dashes),
                        double(actor.slide->launches),double(actor.slide->chains),double(actor.slide->creepPatches),actor.slide->secondDash);
                    if(actor.memBrain)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).memBrain=({
                        ticks:$0,frame:$1,fired:!!$2,attacks:$3,volleys:$4,pending:$5,target:!!$6,dx:$7,dz:$8,births:$9,pushes:$10});},
                        double(actor.memBrain->ticks),actor.memBrain->attackFrame,actor.memBrain->fired,
                        double(actor.memBrain->attacks),double(actor.memBrain->volleys),int(actor.memBrain->pendingShots.size()),
                        actor.memBrain->targetReady,actor.memBrain->destination.x,actor.memBrain->destination.z,
                        double(actor.memBrain->births),double(actor.memBrain->pushes));
                    if(actor.guts)EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.actors.at(-1).guts,{
                        shots:$0,shotFrame:$1,shotTimer:$2,pendingShots:$3});},double(actor.guts->shots),actor.guts->shotFrame,
                        actor.guts->shotTimer,int(actor.guts->pendingShots.size()));
                    if(actor.lump)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).lump=({
                        ticks:$0,phase:$1,frame:$2,cooldown:$3,intangible:!!$4,visibility:$5,volleys:$6,
                        burrows:$7,relocations:$8,anchorX:$9,anchorZ:$10,pending:$11});},
                        double(actor.lump->ticks),int(actor.lump->phase),actor.lump->frame,actor.lump->cooldown,
                        actor.lump->intangible,actor.lump->visibility,double(actor.lump->volleys),double(actor.lump->burrows),
                        double(actor.lump->relocations),actor.lump->anchor.x,actor.lump->anchor.z,int(actor.lump->pendingShots.size()));
                    if(actor.leech)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).leech=({
                        ticks:$0,charging:!!$1,charges:$2,stops:$3,frame:$4,dx:$5,dz:$6,mx:$7,mz:$8});},
                        double(actor.leech->ticks),actor.leech->charging,double(actor.leech->charges),double(actor.leech->stops),
                        actor.leech->walkFrame,actor.leech->chargeDirection.x,actor.leech->chargeDirection.z,
                        actor.leech->momentum.x,actor.leech->momentum.z);
                    if(actor.mirror)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).mirror=({
                        ticks:$0,volleys:$1,cooldown:$2,delay:$3,corrections:$4,pending:!!$5,
                        desiredX:$6,desiredZ:$7,shotX:$8,shotZ:$9});},double(actor.mirror->ticks),double(actor.mirror->volleys),
                        actor.mirror->cooldown,actor.mirror->observedDelay,double(actor.mirror->terrainCorrections),
                        actor.mirror->pending,actor.mirror->desired.x,actor.mirror->desired.z,
                        actor.mirror->shotVelocity.x,actor.mirror->shotVelocity.z);
                    if(actor.knight)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).knight=({
                        ticks:$0,charging:!!$1,charges:$2,stops:$3,impacts:$4,bursts:$5,recovery:$6,
                        pending:!!$7,dx:$8,dz:$9,mx:$10,mz:$11});},double(actor.knight->ticks),actor.knight->charging,
                        double(actor.knight->charges),double(actor.knight->stops),double(actor.knight->impacts),double(actor.knight->impactBursts),
                        actor.knight->recovery,actor.knight->pendingImpact,actor.knight->chargeDirection.x,actor.knight->chargeDirection.z,
                        actor.knight->momentum.x,actor.knight->momentum.z);
                    if(actor.cardinalWalker)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).cardinalWalker=({
                        ticks:$0,frame:$1,axis:$2,hasDestination:!!$3,dx:$4,dz:$5,mx:$6,mz:$7});},
                        double(actor.cardinalWalker->ticks),actor.cardinalWalker->walkFrame,actor.cardinalWalker->walkAxis,
                        actor.cardinalWalker->hasDestination,actor.cardinalWalker->destination.x,actor.cardinalWalker->destination.z,
                        actor.cardinalWalker->momentum.x,actor.cardinalWalker->momentum.z);
                    if(actor.spitty)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).spitty=({
                        frame:$0,walkFrame:$1,walkAxis:$2,fired:!!$3,deathPending:!!$4,bursts:$5,volleys:$6,
                        pendingBurst:$7,dx:$8,dz:$9,aimX:$10,aimZ:$11,ticks:$12});},
                        actor.spitty->attackFrame,actor.spitty->walkFrame,actor.spitty->walkAxis,actor.spitty->fired,
                        actor.spitty->deathPending,double(actor.spitty->bursts),double(actor.spitty->volleys),
                        actor.spitty->pendingBurst,actor.spitty->destination.x,actor.spitty->destination.z,
                        actor.spitty->attackDirection.x,actor.spitty->attackDirection.z,double(actor.spitty->ticks));
                    if(actor.host)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).host=({frame:$0,fired:!!$1,exposed:!!$2,delay:$3,cooldown:$4});},
                        actor.host->frame,actor.host->fired,actor.host->exposed,actor.host->delay,actor.host->cooldown);
                    if(actor.targetHop)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).targetHop=({frame:$0,counter:$1,hops:$2,landings:$3,airborne:!!$4,ready:!!$5,pursuing:!!$6,bonus:$7,dx:$8,dz:$9,mx:$10,mz:$11,transformedFlight:!!$12});},
                        actor.targetHop->frame,actor.targetHop->counter,actor.targetHop->hops,actor.targetHop->landings,
                        actor.targetHop->airborne,actor.targetHop->targetReady,actor.targetHop->pursuing,actor.targetHop->bonus,
                        actor.targetHop->destination.x,actor.targetHop->destination.z,actor.targetHop->momentum.x,actor.targetHop->momentum.z,actor.targetHop->transformedFlight.has_value());
                    if(actor.maskArmor)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).maskArmor=({grace:$0,reflections:$1,dx:$2,dz:$3});},
                        actor.maskArmor->turnGrace,double(actor.maskArmor->reflections),actor.maskArmor->facing.x,actor.maskArmor->facing.z);
                    if(actor.linkedRemnant)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).linkedRemnant=({initialized:!!$0,waiting:!!$1});},
                        actor.linkedRemnant->initialized,actor.linkedRemnant->waiting);
                    if(actor.landingCreep)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).landingCreep=({patches:$0,pending:$1,releases:$2});},
                        double(actor.landingCreep->patches),int(actor.landingCreep->pending.size()),double(actor.landingCreep->releases));
                    if(actor.eggy)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).eggy=({dying:!!$0,frame:$1,released:$2,patches:$3,restarts:$4});},
                        actor.eggy->dying,actor.eggy->frame,actor.eggy->released,actor.eggy->creepPatches,actor.eggy->restarts);
                    if(actor.hopRings)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).hopRings=({stage:$0,animationStage:$1,volleys:$2,cycles:$3,pending:$4});},
                        actor.hopRings->stage,actor.hopRings->animationStage,actor.hopRings->volleys,actor.hopRings->cycles,int(actor.hopRings->pending.size()));
                    if(actor.leaper)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).leaper=({phase:$0,frame:$1,leaps:$2,landings:$3,volleys:$4,patches:$5,pending:!!$6,tx:$7,tz:$8,progress:$9});},
                        actor.leaper->phase,actor.leaper->frame,actor.leaper->leaps,actor.leaper->bigLandings,
                        actor.leaper->volleys,actor.leaper->creepPatches,bool(actor.leaper->pending),
                        actor.leaper->target.x,actor.leaper->target.z,actor.leaper->progress);
                    if(actor.adaptiveArmor)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).adaptiveArmor=({ticks:$0,batches:$1,samples:$2,pending:$3,dps:$4,multiplier:$5});},
                        double(actor.adaptiveArmor->ticks),double(actor.adaptiveArmor->batches),int(actor.adaptiveArmor->history.size()),
                        int(actor.adaptiveArmor->pending.size()),actor.adaptiveArmor->recentDps,actor.adaptiveArmor->multiplier);
                    if(actor.mushroom)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).mushroom=({phase:$0,frame:$1,timer:$2,opening:$3,blocking:!!$4,diagonal:!!$5,fired:!!$6});},
                        int(actor.mushroom->phase),actor.mushroom->frame,actor.mushroom->timer,actor.mushroom->opening,
                        actor.mushroom->blocking(),actor.mushroom->diagonal,actor.mushroom->fired);
                    if(actor.eternalFly)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).eternalFly=({ticks:$0,phase:$1,parent:$2});},
                        actor.eternalFly->orbitTicks,actor.eternalFly->phase,double(actor.partner));
                    if(actor.sack)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).sack=({frame:$0,
                        attacks:$1,growth:$2,shake:!!$3});},actor.sack->frame,actor.sack->attacks,actor.sack->growth,actor.sack->shake);
                    if(actor.danny)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).danny=({frame:$0,cooldown:$1,attacks:$2,children:$3,recentDamage:$4,pending:$5});},
                        actor.danny->frame,actor.danny->cooldown,actor.danny->attacks,actor.danny->children,actor.danny->recentDamage,int(actor.danny->pendingShots.size()));
                    if(actor.gaper)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).gaper=({ticks:$0,headFrame:$1,wakeStarted:!!$2,directPath:!!$3,force:$4,eyeOpenness:$5,walkFrame:$6});},
                        actor.gaper->ticks,actor.gaper->headFrame,actor.gaper->wakeStarted,actor.gaper->directPath,
                        actor.gaper->force,actor.gaper->eyeOpenness,actor.gaper->walkFrame);
                    if(actor.smallMaggot)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).smallMaggot=({ticks:$0,cooldown:$1,alert:!!$2,force:$3,curve:$4,walkFrame:$5,turns:$6,alerts:$7});},
                        actor.smallMaggot->ticks,actor.smallMaggot->cooldown,actor.smallMaggot->alert,actor.smallMaggot->force,
                        actor.smallMaggot->curve,actor.smallMaggot->walkFrame,double(actor.smallMaggot->turns),double(actor.smallMaggot->alerts));
                    if(actor.headless)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).headless=({ticks:$0,cooldown:$1,shots:$2,pending:!!$3});},
                        actor.headless->ticks,actor.headless->cooldown,actor.headless->shots,!actor.headless->pendingShots.empty());
                    if(actor.faceless)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).faceless=({frame:$0,attacks:$1,aggressive:!!$2,recentDamage:$3,pending:$4,spawner:$5});},
                        actor.faceless->frame,actor.faceless->attacks,actor.faceless->aggressive,actor.faceless->recentDamage,int(actor.faceless->pendingShots.size()),actor.spawnerType);
                    if(actor.hardy)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).hardy=({phase:$0,frame:$1,impacts:$2,launches:$3,collisions:$4,cooldown:$5,pending:$6});},
                        actor.hardy->phase,actor.hardy->frame,actor.hardy->impacts,actor.hardy->launches,actor.hardy->collisions,actor.hardy->cooldown,int(actor.hardy->pendingShots.size()));
                    if(actor.rockSpider)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).rockSpider=({phase:$0,
                        frame:$1,counter:$2,selections:$3,cycles:$4,height:$5,vertical:$6,pursuing:!!$7,ticks:$8});},
                        int(actor.rockSpider->phase),actor.rockSpider->frame,actor.rockSpider->counter,actor.rockSpider->selections,
                        actor.rockSpider->cycles,actor.rockSpider->height,actor.rockSpider->vertical,actor.rockSpider->pursuing,double(actor.rockSpider->ticks));
                    if(actor.spider)EM_ASM({if(Module.verify)Module.enemyProbe.actors.at(-1).spider=({ready:!!$0,
                        pursuing:!!$1,counter:$2,targetX:$3,targetZ:$4});},actor.spider->targetReady,actor.spider->pursuing,
                        actor.spider->counter,actor.spider->destination.x,actor.spider->destination.z);
                }
                EM_ASM({if(Module.verify)Module.enemyProbe.segmented=({groups:[],paid:!!$0,killed:!!$1,health:$2});},
                    game.run->rooms[size_t(game.run->room)].bossPaid,game.run->bossKilled,game.run->boss()?game.run->bossHealthFraction(*game.run->boss()):0);
                if(const auto &h=game.run->rooms[size_t(game.run->room)].hornfel;h) {
                    EM_ASM({if(Module.verify)Module.enemyProbe.hornfel=({state:$0,owner:$1,cart:$2,rider:$3,intact:!!$4,visible:!!$5,
                        route:$6,distance:$7,passes:$8,attacks:$9,completed:!!$10,escaped:!!$11,doors:[]});},
                        int(h->state),double(h->owner),double(h->cart.id),double(h->cart.rider),h->cart.intact,h->cart.visible,
                        h->cart.route,h->cart.distance,h->passes,h->attacks,h->completed,h->escaped);
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.hornfel,{charges:$0,chargePasses:$1,repeatsChosen:$2,repeatsLeft:$3,
                        chargeBombs:$4,drive:$5,nativeVelocity:$6,recoveryClock:$7,recoveryShot:!!$8,recoveryShots:$9,chargeCooldown:$10});},
                        h->charges,h->chargePasses,h->repeatsChosen,h->repeatsLeft,h->chargeBombs,h->drive,h->nativeVelocity,
                        h->recoveryClock,h->recoveryShot,h->recoveryShots,h->chargeCooldown);
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.hornfel,{decoys:[],decoyRuns:$0,decoysSpawned:$1,decoysRemoved:$2,decoysDestroyed:$3});},
                        h->decoyRuns,h->decoysSpawned,h->decoysRemoved,h->decoysDestroyed);
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.hornfel,{escortGroups:$0,escortsSpawned:$1,escortsReleased:$2,escortGroupsSkipped:$3});},
                        h->escortGroups,h->escortsSpawned,h->escortsReleased,h->escortGroupsSkipped);
                    const auto &traffic=h->traffic;
                    EM_ASM({if(Module.verify)Module.enemyProbe.hornfel.traffic=({initialized:!!$0,expired:!!$1,stopped:!!$2,timeout:$3,lifespan:$4,
                        ticks:$5,attempts:$6,unavailable:$7,blocked:$8,capacityRejected:$9,spawned:$10,removed:$11,destroyed:$12,passengers:[]});},
                        traffic.initialized,traffic.expired,traffic.stopped,traffic.timeout,traffic.lifespan,double(traffic.ticks),double(traffic.attempts),
                        double(traffic.unavailable),double(traffic.blocked),double(traffic.capacityRejected),double(traffic.spawned),double(traffic.removed),double(traffic.destroyed));
                    for(const auto &r:traffic.passengers) {
                        const auto &path=game.run->arena.rails->paths[size_t(r.cart.route)];
                        EM_ASM({if(Module.verify)Module.enemyProbe.hornfel.traffic.passengers.push({actor:$0,cart:$1,route:$2,distance:$3,visible:!!$4,
                            entry:$5,exit:$6,x:$7,z:$8});},double(r.actor),double(r.cart.id),r.cart.route,r.cart.distance,r.cart.visible,path.entry,path.exit,r.cart.position.x,r.cart.position.z);
                    }
                    for(const auto &d:h->decoys) {
                        const auto &path=game.run->arena.rails->paths[size_t(d.cart.route)];
                        EM_ASM({if(Module.verify)Module.enemyProbe.hornfel.decoys.push({actor:$0,cart:$1,route:$2,distance:$3,visible:!!$4,finished:!!$5,deathPending:!!$6,entry:$7,exit:$8,x:$9,z:$10});},
                            double(d.actor),double(d.cart.id),d.cart.route,d.cart.distance,d.cart.visible,d.finished,d.deathPending,path.entry,path.exit,d.cart.position.x,d.cart.position.z);
                    }
                    for(const auto &door:h->doors)EM_ASM({if(Module.verify)Module.enemyProbe.hornfel.doors.push({id:$0,type:967,x:$1,z:$2,open:$3});},double(door.id),door.position.x,door.position.z,door.openness);
                    if(game.run->arena.rails)EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.hornfel,{layout:UTF8ToString($0),pits:$1,cellX:$2,cellZ:$3});},
                        game.run->arena.rails->layout.c_str(),int(game.run->arena.rails->pits.size()),game.run->arena.rails->cellSize.x,game.run->arena.rails->cellSize.z);
                }
                EM_ASM({if(Module.verify)Module.enemyProbe.fireWaves=[];});
                for(const auto &burst:game.run->fireWaves)if(burst.room==game.run->room) {
                    EM_ASM({if(Module.verify)Module.enemyProbe.fireWaves.push({id:$0,source:$1,age:$2,x:$3,z:$4,speed:$5,range:$6,radius:$7,rays:[]});},
                        double(burst.id),double(burst.source),burst.age,burst.origin.x,burst.origin.z,burst.rules.speed,burst.rules.range,burst.rules.radius);
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.fireWaves.at(-1),{jetStep:$0,jetStepFrames:$1,jets:[]});},burst.jetStep,burst.rules.jetStepFrames);
                    for(const auto &jet:burst.jets)EM_ASM({if(Module.verify)Module.enemyProbe.fireWaves.at(-1).jets.push({x:$0,z:$1,age:$2,scale:$3,pulses:$4});},
                        jet.position.x,jet.position.z,burst.age-jet.born,jet.scale,jet.pulses);
                    for(int n=0;n<burst.rayCount;++n) {
                        Vector3 from{},to{};const bool active=burst.segment(n,from,to);
                        EM_ASM({if(Module.verify)Module.enemyProbe.fireWaves.at(-1).rays.push({length:$0,stopped:!!$1,active:!!$2,x:$3,z:$4,endX:$5,endZ:$6,dx:$7,dz:$8});},
                            burst.rays[size_t(n)].length,burst.rays[size_t(n)].stopped,active,from.x,from.z,to.x,to.z,
                            burst.directions[size_t(n)].x,burst.directions[size_t(n)].z);
                    }
                }
                for(const auto &group:game.run->rooms[size_t(game.run->room)].segmented) {
                    EM_ASM({if(Module.verify)Module.enemyProbe.segmented.groups.push({id:$0,completed:!!$1,chains:[]});},double(group.id),group.completed);
                    for(const auto &chain:group.chains) {
                        EM_ASM({if(Module.verify)Module.enemyProbe.segmented.groups.at(-1).chains.push({id:$0,members:[]});},double(chain.id));
                        for(auto id:chain.members)EM_ASM({if(Module.verify)Module.enemyProbe.segmented.groups.at(-1).chains.at(-1).members.push($0);},double(id));
                    }
                }
                EM_ASM({if(Module.verify){Module.enemyProbe.familiars=[];Module.enemyProbe.playerHp=$0;}},game.run->player.hp);
                EM_ASM({if(Module.verify){Module.enemyProbe.statue=({disabled:!!$0,volleys:$1,fx:$2,fz:$3,clear:!!$4,explosions:$5,pulling:!!$6,phase:$7,lift:$8});Module.enemyProbe.plates=[];}},
                    enemy&&enemy->statueDisabled,enemy?enemy->statueVolley:0,enemy?enemy->facing.x:0,enemy?enemy->facing.z:0,game.run->roomClear,double(game.run->stats.explosions),enemy&&enemy->statuePullActive,enemy?enemy->statuePhase:0,enemy?enemy->lift:0);
                for(const auto &p:game.run->rooms[size_t(game.run->room)].plates)
                    EM_ASM({if(Module.verify)Module.enemyProbe.plates.push({x:$0,z:$1,pressed:!!$2});},p.position.x,p.position.z,p.pressed);
                EM_ASM({if(Module.verify)Module.enemyProbe.supply=({inventory:$0,carried:$1,produced:$2,pending:$3,bombs:[]});},
                    game.run->dynamite,double(game.run->carriedBomb()?game.run->carriedBomb()->id:0),
                    enemy?enemy->supplyProduced:0,enemy?enemy->supplyDeathPending:0);
                for(const auto &bomb:game.run->suppliedBombs) {
                    const auto source=bomb.sourceIdentity();
                    EM_ASM({if(Module.verify)Module.enemyProbe.supply.bombs.push({entity:$0,supplier:$1,state:$2,source:[$3,$4,$5],
                        room:$6,deathDrop:!!$7,x:$8,y:$9,z:$10,age:$11,fuse:$12,vx:$13,vy:$14,vz:$15});},
                        double(bomb.id),double(bomb.supplier),int(bomb.state),source.type,source.variant,source.subtype,
                        bomb.room,bomb.deathDrop,bomb.charge.position.x,bomb.charge.position.y,bomb.charge.position.z,
                        bomb.charge.age,bomb.charge.delay,bomb.charge.velocity.x,bomb.charge.velocity.y,bomb.charge.velocity.z);
                }
                EM_ASM({if(Module.verify){Module.enemyProbe.enemyBombs=[];Module.enemyProbe.pendingEnemyBombs=$0;}},int(game.run->pendingEnemyBombs.size()));
                for(const auto &bomb:game.run->enemyBombs) {
                    EM_ASM({if(Module.verify)Module.enemyProbe.enemyBombs.push({entity:$0,source:$1,monster:[$2,$3,$4],ordnance:[$5,$6,$7],
                        room:$8,x:$9,y:$10,z:$11,age:$12,fuse:$13,damage:$14,playerDamage:$15});},double(bomb.id),double(bomb.source),
                        bomb.sourceMonster.type,bomb.sourceMonster.variant,bomb.sourceMonster.subtype,bomb.ordnance.type,bomb.ordnance.variant,bomb.ordnance.subtype,
                        bomb.room,bomb.charge.position.x,bomb.charge.position.y,bomb.charge.position.z,bomb.charge.age,bomb.charge.delay,bomb.charge.blastDamage,bomb.charge.damage);
                    EM_ASM({if(Module.verify)Module.enemyProbe.enemyBombs.at(-1).marker=!!$0;},bomb.blastMarker);
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.enemyBombs.at(-1),{payload:$0,detonated:!!$1,effectAge:$2,configured:!!$3,beams:[]});},
                        int(bomb.rules.payload),bomb.detonated,bomb.effectAge,bomb.configured);
                    if(bomb.detonated&&bomb.rules.payload==dw::EnemyBombPayload::Brimstone)
                        for(auto end:bomb.beamEnds)EM_ASM({if(Module.verify)Module.enemyProbe.enemyBombs.at(-1).beams.push({x:$0,y:$1,z:$2});},end.x,end.y,end.z);
                }
                for(const auto &f:game.run->familiars)
                    EM_ASM({if(Module.verify)Module.enemyProbe.familiars.push({entity:$0,x:$1,y:$2,z:$3,radius:$4,history:$5});},
                        double(f.id),f.position.x,f.position.y,f.position.z,f.radius,int(f.trail.size()));
                EM_ASM({if(Module.verify)Module.enemyProbe.groups=[];});
                for(const auto &group:game.run->rooms[size_t(game.run->room)].formations) {
                    EM_ASM({if(Module.verify)Module.enemyProbe.groups.push({id:$0,type:$1,variant:$2,subtype:$3,x:$4,z:$5,angle:$6,slots:[]});},
                        double(group.id),group.monster.type,group.monster.variant,group.monster.subtype,group.center.x,group.center.z,group.angle);
                    for(const auto &slot:group.slots)EM_ASM({if(Module.verify)Module.enemyProbe.groups.at(-1).slots.push({member:$0,angle:$1});},double(slot.member),slot.angle);
                }
                EM_ASM({if(Module.verify){Module.enemyProbe.bullets=[];Module.enemyProbe.hazards=[];}});
                EM_ASM({if(Module.verify){Module.enemyProbe.flooded=!!$0;Module.enemyProbe.sourceStage=$1;}},
                    game.run->arena.rooms[size_t(game.run->room)].flooded,game.run->arena.profile.sourceStage);
                if(enemy)EM_ASM({if(Module.verify)Module.enemyProbe.hop=({active:!!$0,pursuing:!!$1,
                    startX:$2,startZ:$3,endX:$4,endZ:$5,elapsed:$6,duration:$7,height:$8});},
                    enemy->hop.active,enemy->hop.pursuing,enemy->hop.start.x,enemy->hop.start.z,
                    enemy->hop.end.x,enemy->hop.end.z,enemy->hop.elapsed,enemy->hop.duration,enemy->hop.height);
                for(const auto &p:game.run->projectiles) {
                    EM_ASM({if(Module.verify)Module.enemyProbe.bullets.push({entity:$0,kind:$1,x:$2,y:$3,z:$4,
                        vx:$5,vy:$6,vz:$7,curve:$8,life:$9,owner:$10});},double(p.id),int(p.kind),p.position.x,p.position.y,p.position.z,
                        p.velocity.x,p.velocity.y,p.velocity.z,p.angularVelocity,p.life,double(p.context.sourceEntity));
                    EM_ASM({if(Module.verify)Module.enemyProbe.bullets.at(-1).sourceHoming=!!$0;},bool(p.sourceHoming));
                    if(p.sourcePlanarMotion) {
                        const auto &m=*p.sourcePlanarMotion;
                        EM_ASM({if(Module.verify)Module.enemyProbe.bullets.at(-1).sourcePlanarMotion=({
                            acceleration:$0,direction:$1,radius:$2,x:$3,z:$4,clock:$5});},
                            m.acceleration,m.orbitDirection,m.orbitRadius,m.orbitCenter.x,m.orbitCenter.z,p.planarClock);
                    }
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.bullets.at(-1),{gravity:$0,blastRadius:$1,
                        radius:$2,damage:$3,impactPending:!!$4});},p.gravity,p.blastRadius,p.radius,p.damage,p.impactPending);
                    EM_ASM({if(Module.verify)Object.assign(Module.enemyProbe.bullets.at(-1),{noWallCollision:!!$0,
                        flightRetention:$1});},p.noWallCollision,p.flightRetention);
                }
                for(const auto &h:game.run->hazards) {
                    EM_ASM({if(Module.verify)Module.enemyProbe.hazards.push({kind:$0,x:$1,z:$2,radius:$3,tintG:$4,owner:$5,
                        originX:$6,originZ:$7,delay:$8,duration:$9,ownerBound:!!$10});},int(h.kind),h.position.x,h.position.z,h.radius,int(h.tint.g),double(h.context.sourceEntity),
                        h.origin.x,h.origin.z,h.delay,h.duration,h.ownerBound);
                    if(h.ownedBeam)EM_ASM({if(Module.verify)Module.enemyProbe.hazards.at(-1).ownedBeam=({
                        frame:$0,pulses:$1,dx:$2,dz:$3,immuneType:$4,monsterDamage:$5});},
                        h.ownedBeam->frame,double(h.ownedBeam->pulses),h.ownedBeam->heading.x,h.ownedBeam->heading.z,
                        h.ownedBeam->immuneType,h.ownedBeam->monsterDamage);
                    if(h.rockWave)EM_ASM({if(Module.verify)Module.enemyProbe.hazards.at(-1).rockWave=({frame:$0,points:$1});},h.rockWave->frame,int(h.rockWave->trail.size()));
                    if(h.fadeDuration>0)EM_ASM({if(Module.verify)Module.enemyProbe.hazards.at(-1).fade=({
                        age:$0,duration:$1,scale:$2,clear:!!$3,life:$4,damage:$5});},h.fadeAge,h.fadeDuration,h.fadeScale,h.fadeOnRoomClear,h.age,h.damage);
                }
                EM_ASM({if(Module.verify)Module.enemyProbe.playerLaunch=({active:!!$0,height:$1,y:$2});},bool(game.run->player.launch),
                    game.run->player.launch?game.run->player.launch->height:0,game.run->player.position.y);
            }
            const bool renderedCinematicEditor = filming && cinematic.editorVisible();
#endif
            BeginDrawing();
            dw::Action action = dw::Action::None;
            if (filming)
                cinematic.draw();
            else if (editing)
                editor.draw();
            else
                action = renderer.draw(game);
            if ((canCompareStyle && (styleCompare || game.visualStyle != dw::VisualStyle::Original)) || canCompareArt) {
                const std::string label = canCompareStyle
                    ? std::string(dw::visualStyleName(game.visualStyle)) + "   /   F6: next style"
                    : (artPoc ? "ART POC   /   F6: original" : "ORIGINAL   /   F6: art POC");
                const int width = MeasureText(label.c_str(), 14) + 24;
                const int x = editing ? int(GetScreenWidth() * (1110.f / 1440)) - width - 10
                                      : (GetScreenWidth() - width) / 2;
                const int y = editing ? int(GetScreenHeight() * (94.f / 900)) : filming ? 52 : 4;
                DrawRectangle(x, y, width, 25, {25, 30, 30, 230});
                DrawText(label.c_str(), x + 12, y + 5, 14, {221, 214, 192, 255});
            }
            const auto drawn = std::chrono::steady_clock::now();
            EndDrawing();
#ifdef __EMSCRIPTEN__
            // Verification-only observer at the actual draw boundary. Browser
            // animation callbacks may resume asynchronously after their wrapper
            // returns, so a wrapper cannot pair canvas pixels with a probe.
            EM_ASM({if(Module.verify&&Module.captureEnemyFrame&&Module.enemyProbe)
                Module.captureEnemyFrame($0);},frame);
#endif
            game.perform(action);
            if(filming&&(cinematic.storyFinished||cinematic.storyCancelled)) {
                if(cinematic.runtimeIntro()) {
                    const auto destination=cinematic.document().destination;
                    const auto storm=cinematic.document().destinationStorm;
                    cinematic.unload();
                    game.perform(dw::Action::Hub);
                    const auto hub=destination=="frontier"?dw::HubKind::Frontier:destination=="town"?dw::HubKind::BlackCreek:dw::HubKind::Redstone;
                    game.selectHub(hub);game.sandstorm=storm>0;renderer.reloadTown();renderer.setSandstormStrength(storm);
                    intro=false;
                } else if(cinematic.storyFinished)cinematic.previewDestination();
                cinematic.storyFinished=cinematic.storyCancelled=false;
            }
            if (filming && !cinematic.active && !cinematic.quitRequested) {
                cinematic.unload();
                ++game.audioContext;
                SetWindowTitle(editor.active?"DeathWard | Town editor":"DeathWard | The consequences remain");
            }
            if (editing && !editor.active && !editor.quitRequested) {
                if (editor.saved) {
                    game.town.load(game.hubDirectory() / "town.nav");
                    game.reloadTownObjects();
                    renderer.reloadTown();
                }
                game.perform(dw::Action::Hub);
                SetWindowTitle("DeathWard | The consequences remain");
            }
            dw::AudioFrame audioFrame;
            audioFrame.camera = game.camera;
            audioFrame.dt = GetFrameTime();
            audioFrame.context = game.audioContext;
            audioFrame.music = editing || filming ? dw::MusicScene::Silent : game.musicScene();
            audioFrame.paused = editing || filming || game.paused || game.buildOpen || game.letterVisible() || game.journalVisible() ||
                                (game.screen != dw::Screen::Hub && game.screen != dw::Screen::Expedition);
            audioFrame.environment = game.activeHub == dw::HubKind::Redstone
                                         ? dw::AudioEnvironment::Canyon
                                     : game.activeHub == dw::HubKind::BlackCreek
                                         ? dw::AudioEnvironment::Town
                                         : dw::AudioEnvironment::Frontier;
            audioFrame.player = game.town.player.position;
            if (game.run) {
                audioFrame.environment = game.run->arena.theme == dw::MissionTheme::Canyon
                                             ? dw::AudioEnvironment::Canyon
                                             : dw::AudioEnvironment::Mine;
                audioFrame.player = game.run->player.position;
                audioFrame.room = game.run->audioEpoch;
                audioFrame.paused =
                    audioFrame.paused || game.run->rewardOpen || game.run->shopOpen || game.run->dead;
                audioFrame.footsteps = game.run->player.dodge <= 0 && game.run->player.pullTime <= 0;
            }
            auto gameAudioSettings=game.audioSettings;
            if(filming) gameAudioSettings.effects=gameAudioSettings.ambience=gameAudioSettings.music=0;
            audio.update(audioFrame, gameAudioSettings,
                         game.run ? game.run->audioCues.cues() : std::span<const dw::AudioCue>{},
                         game.audioCues.cues());
            game.audioCues.clear();
            if (game.run)
                game.run->audioCues.clear();
            if (!(savedAudioSettings == game.audioSettings)) {
                if (!dw::saveAudioSettings(audioPreferences, game.audioSettings))
                    TraceLog(LOG_WARNING, "AUDIO: Could not save volume preferences");
                savedAudioSettings = game.audioSettings;
            }
            if (!(savedVisualSettings == game.visualSettings)) {
                if (!dw::saveVisualSettings(visualPreferences, game.visualSettings))
                    TraceLog(LOG_WARNING, "SCENERY: Could not save vegetation preference");
                savedVisualSettings = game.visualSettings;
            }
#ifdef __EMSCRIPTEN__
            // Read-only state for browser integration checks; absent during ordinary play.
            const auto *probeProp = game.townObjects.firstPropPose();
            const auto &residents = game.animals.residents();
            const auto &characters = game.characters.residents();
            const auto &previewAnimals = editor.animalPreview().residents();
            const auto selectedAnimal = editor.animalSelection();
            const auto animalIndex = selectedAnimal.value_or(0);
            const auto *previewAnimal = animalIndex < previewAnimals.size() ? &previewAnimals[animalIndex] : nullptr;
            const auto *animalDefinition = selectedAnimal ? &editor.document().animals[*selectedAnimal] : nullptr;
            std::string animalClips;
            if (animalDefinition)
                for (const auto &clip : animalDefinition->activity.clips) {
                    if (!animalClips.empty()) animalClips += ',';
                    animalClips += clip;
                }
            EM_ASM({
                if (Module.verify) Module.animalEditor = ({count: $0, selected: $1, time: $2,
                    phase: $3, x: $4, z: $5, species: $6, radius: $7, seed: $8, homeX: $9, homeZ: $10,
                    stationary: !!$11, speed: $12, clips: UTF8ToString($13)});
                }, int(editor.document().animals.size()), selectedAnimal ? int(*selectedAnimal) : -1,
                editor.animalPreview().time(), previewAnimal ? previewAnimal->phase : 0.,
                previewAnimal ? previewAnimal->position.x : 0.f, previewAnimal ? previewAnimal->position.z : 0.f,
                animalDefinition ? int(animalDefinition->kind) : -1, animalDefinition ? animalDefinition->roam : 0.f,
                animalDefinition ? double(animalDefinition->seed) : 0., animalDefinition ? animalDefinition->home.x : 0.f,
                animalDefinition ? animalDefinition->home.z : 0.f,
                animalDefinition && animalDefinition->activity.stationary,
                animalDefinition ? animalDefinition->activity.speed : 1.f, animalClips.c_str());
            auto buildingPoint = [&](Vector3 p) {
                const float h=game.town.height(p);p.y=std::isfinite(h)?h:0;
                return GetWorldToScreen(p,game.camera);
            };
            const auto interiorProbe=buildingPoint({-13.5f,0,-11.5f});
            const auto exitProbe=buildingPoint({-3,0,-4});
            EM_ASM({
                if (Module.verify) Module.buildings = ({inside:!!$0, doors:$1, open:$2,
                    targetX:$3, targetY:$4, exitX:$5, exitY:$6});
            }, renderer.insideBuilding(),int(game.townObjects.doorCount()),int(game.townObjects.openDoorCount()),
                interiorProbe.x,interiorProbe.y,exitProbe.x,exitProbe.y);
            const auto &previewCharacters = editor.characterPreview().residents();
            const auto &particleEffects = editor.active ? editor.effects() : renderer.townEffects();
            EM_ASM({
                if (Module.verify) Module.particles = ({ready: !!$0, attachments: $1, count: $2, time: $3, steam: $4});
            }, particleEffects.loaded(), int(particleEffects.attachmentCount()),
               int(particleEffects.particleCount()), particleEffects.time(), int(particleEffects.count("steam")));
            const auto &missionEffects = renderer.missionEffects();
            EM_ASM({
                if (Module.verify) Module.combatParticles = ({ready: !!$0, count: $1,
                    dust: $2, explosion: $3, muzzle: $4, time: $5});
            }, missionEffects.loaded(), int(missionEffects.particleCount()), int(missionEffects.count("canyondust")),
               int(missionEffects.count("blastfire") + missionEffects.count("blastsmoke")),
               int(missionEffects.count("muzzle") + missionEffects.count("gunsmoke")), missionEffects.time());
            const auto selectedCharacter = editor.characterSelection();
            EM_ASM(
                {
                    if (Module.verify) {
                        Module.characters = ({count: $0, time: $1, phase: $2, x: $3, z: $4, visits: $5});
                        Module.characterEditor = ({count: $6, selected: $7, stops: $8, time: $9});
                    }
                },
                int(characters.size()), game.characters.time(), characters.empty() ? 0. : characters[0].phase,
                characters.empty() ? 0.f : characters[0].position.x, characters.empty() ? 0.f : characters[0].position.z,
                characters.empty() ? 0 : int(characters[0].visits), int(previewCharacters.size()),
                selectedCharacter ? int(*selectedCharacter) : -1,
                selectedCharacter ? int(editor.document().characters[*selectedCharacter].stops.size()) : 0,
                editor.characterPreview().time());
            EM_ASM(
                {
                    if (Module.verify)
                        Module.animals = ({count : $0, time : $1, phase : $2, x : $3, z : $4});
                },
                int(residents.size()), game.animals.time(), residents.empty() ? 0. : residents[0].phase,
                residents.empty() ? 0.f : residents[0].position.x,
                residents.empty() ? 0.f : residents[0].position.z);
            EM_ASM(
                {
                    if (Module.verify)
                        Module.motion = ({
                            count : $0,
                            time : $1,
                            x : $2,
                            z : $3,
                            rotation : $4,
                            preview : !!$5,
                            previewTime : $6,
                            vehicles : $7,
                            trainDistance : $8,
                            trainSpeed : $9
                        });
                },
                int(game.townObjects.activeCount()), game.townObjects.time(),
                probeProp ? probeProp->transform.m12 : 0, probeProp ? probeProp->transform.m14 : 0,
                probeProp ? probeProp->transform.m0 : 0, editor.previewPlaying(),
                editor.animationPreview().time(), int(game.townObjects.solids().size()),
                game.townObjects.solids().empty() ? 0. : game.townObjects.pathDistance(),
                game.townObjects.solids().empty() ? 0.f : game.townObjects.pathSpeed());
            const dw::MoneyPickup *probeCoin = nullptr;
            if (game.run)
                for (const auto &coin : game.run->moneyPickups)
                    if (game.run->arena.roomAt(coin.position) == game.run->room &&
                        (!probeCoin || dw::distance(coin.position, game.run->player.position) <
                                           dw::distance(probeCoin->position, game.run->player.position)))
                        probeCoin = &coin;
            Vector2 coinPixel{-1, -1};
            if (probeCoin) {
                auto point = probeCoin->position;
                point.y = .4f;
                coinPixel = GetWorldToScreen(point, game.camera);
                coinPixel.x *= 1280.f / float(GetScreenWidth());
                coinPixel.y *= 800.f / float(GetScreenHeight());
            }
            Vector2 shopPixel{-1, -1};
            if (game.run && game.run->arena.shopRoom >= 0) {
                auto point = game.run->arena.rooms[size_t(game.run->arena.shopRoom)].objective;
                point.y += .8f;
                shopPixel = GetWorldToScreen(point, game.camera);
                shopPixel.x *= 1280.f / float(GetScreenWidth());
                shopPixel.y *= 800.f / float(GetScreenHeight());
            }
            EM_ASM(
                {
                    if (Module.verify)
                        Module.state = ({
                            frame : $0,
                            screen : $1,
                            hub : $2,
                            paused : !!$3,
                            menu : !!$4,
                            x : $5,
                            z : $6,
                            zoom : $7,
                            room : $8,
                            enemies : $9,
                            shots : $10,
                            audio : $11,
                            music : $12,
                            theme : $13,
                            history : $14,
                            error : UTF8ToString($15)
                        });
                },
                frame, int(game.screen), int(game.activeHub), game.paused, game.missionMenu,
                audioFrame.player.x, audioFrame.player.z, game.cameraZoomPercent(),
                game.run ? game.run->room : -1, game.run ? int(game.run->livingEnemies()) : 0,
                game.run ? int(game.run->stats.shots) : 0, int(game.audioStatus), game.audioSettings.music,
                game.run ? int(game.run->arena.theme) : -1, int(game.campaign.data().history.size()),
                game.error.c_str());
            EM_ASM(
                {
                    if (Module.state) {
                        Module.state.editor = !!$0;
                        Module.state.score = $1;
                        Module.state.editorSaved = !!$2;
                        Module.state.editorStatus = UTF8ToString($3);
                        Module.state.money = $4;
                        Module.state.earned = $5;
                        Module.state.coinX = $6;
                        Module.state.coinY = $7;
                        Module.state.coinValue = $8;
                        Module.state.artPoc = !!$9;
                        Module.state.missionShadows = !!$10;
                        Module.state.decorations = $11;
                        Module.state.roomDecorations = $12;
                        Module.state.vegetationDensity = $13;
                        Module.state.vegetationCount = $14;
                        Module.state.groundDetail = !!$15;
                    }
                },
                editing, int(game.musicScene()), editor.saved, editor.status.c_str(),
                int(game.run ? game.run->money() : game.campaign.data().world.money),
                game.run ? int(game.run->moneyCollected) : 0, coinPixel.x, coinPixel.y,
                probeCoin ? probeCoin->value : 0, artPoc && canCompareArt,
                game.run && renderer.missionShadowsReady(), game.run ? renderer.missionDecorationCount() : 0,
                game.run ? renderer.missionDecorationCount(game.run->room) : 0,
                game.visualSettings.vegetation, game.run ? renderer.missionVegetationCount() : 0,
                game.visualSettings.groundDetail);
            EM_ASM({ if (Module.state) {
                Module.state.celShading = $0 == 1;
                Module.state.visualStyle = $0;
                Module.state.visualStyleName = UTF8ToString($1);
            } }, int(game.visualStyle), dw::visualStyleName(game.visualStyle));
            EM_ASM(
                {
                    if (Module.state) {
                        Module.state.shopRoom = $0;
                        Module.state.shopOpen = !!$1;
                        Module.state.shopX = $2;
                        Module.state.shopY = $3;
                        Module.state.spent = $4;
                        Module.state.dynamite = $5;
                        Module.state.dynamiteArmed = !!$6;
                        Module.state.litDynamite = $7;
                        Module.state.explosions = $8;
                        Module.state.dynamiteThrowMode = !!$9;
                        Module.state.placedDynamite = $10;
                        Module.state.canyonRiver = !!$11;
                        Module.state.riverActive = !!$12;
                        Module.state.riverRoom = $13;
                        Module.state.riverKind = $14;
                        Module.state.roadRoom = $15;
                    }
                },
                game.run ? game.run->arena.shopRoom : -1, game.run && game.run->shopOpen, shopPixel.x,
                shopPixel.y, game.run ? int(game.run->moneySpent) : 0, game.run ? game.run->dynamite : 0,
                game.dynamiteArmed,
                game.run ? int(std::count_if(game.run->hazards.begin(), game.run->hazards.end(),
                                             [](const auto &hazard) {
                                                 return hazard.kind == dw::HazardKind::PlayerDynamite;
                                             }))
                         : 0,
                game.run ? int(game.run->stats.explosions) : 0, game.dynamiteThrowMode,
                game.run ? int(std::count_if(game.run->hazards.begin(), game.run->hazards.end(),
                                             [](const auto &hazard) {
                                                 return hazard.kind == dw::HazardKind::PlayerDynamite &&
                                                        hazard.settled;
                                             }))
                         : 0,
                game.visualSettings.canyonRiver,
                game.run && game.run->arena.canyon && !game.run->arena.canyon->river.empty(),
                game.run && game.run->arena.canyon && !game.run->arena.canyon->riverRooms.empty()
                    ? game.run->arena.canyon->riverRooms.front()
                    : -1,
                game.run && game.run->arena.canyon ? int(game.run->arena.canyon->riverKind) : 0,
                game.run && game.run->arena.canyon && !game.run->arena.canyon->roadRooms.empty()
                    ? game.run->arena.canyon->roadRooms[1] : -1);
            EM_ASM({ if (Module.state) Module.state.sandstorm = !!$0; }, game.sandstorm);
            const auto exitMarker=game.floorExitMarker();
            EM_ASM({if(Module.verify)Module.navigation=({focus:$0,help:!!$1,floor:$2,exitReady:!!$3,exitX:$4,exitY:$5,build:!!$6});},
                int(game.keyboardFocus()),game.controlsOpen,game.run?game.run->floor:-1,
                game.run&&game.run->canUseFloorExit(),exitMarker?exitMarker->x:-1,exitMarker?exitMarker->y:-1,game.buildOpen);
            if(game.run) {
                const auto &trade=game.run->rooms[size_t(game.run->room)];
                EM_ASM({if(Module.verify)Module.economy=({service:$0,open:!!$1,coins:$2,keys:$3,dynamite:$4,maxHP:$5,hp:$6,sold0:!!$7,sold1:!!$8,reward:!!$9,itemCount:$10});},
                    int(game.run->arena.rooms[size_t(game.run->room)].service),game.run->shopOpen,double(game.run->money()),
                    game.run->keys,game.run->dynamite,game.run->player.maxHp,game.run->player.hp,
                    trade.serviceSold[0],trade.serviceSold[1],game.run->rewardOpen,int(game.run->items.size()));
                const auto *guardian=game.run->boss();
                EM_ASM({if(Module.verify)Module.guardian=({band:$0,kind:$1,state:$2,phase:$3,hp:$4,playerHp:$5,clear:!!$6,time:$7});},
                    game.run->arena.profile.band,guardian?int(guardian->bossKind):0,guardian?int(guardian->state):-1,
                    guardian?guardian->phase:-1,guardian?guardian->hp:0,game.run->player.hp,int(game.run->roomClear),game.run->stats.duration);
                int friendly=0,spikes=0,homing=0,returning=0,caps=0,children=0;
                for(const auto &p:game.run->projectiles)if(!p.hostile) {
                    ++friendly;spikes+=p.attack.rail;homing+=p.attack.homingTurn>0;
                    returning+=p.returning;caps+=p.attack.capDamage>0&&!p.capSpent;
                }
                for(const auto &h:game.run->hazards)children+=h.secondary;
                EM_ASM({if(Module.verify)Module.build=({items:$0,friendly:$1,spikes:$2,homing:$3,returning:$4,caps:$5,children:$6,splits:$7});},
                    int(game.run->items.size()),friendly,spikes,homing,returning,caps,children,int(game.run->stats.splits));
                int health=-1,destroyed=0;
                for(const auto &prop:game.run->arena.breakables) {
                    if(prop.kind==dw::BreakableKind::CacheGate)health=std::max(0,prop.health);
                    if(prop.destroyed)++destroyed;
                }
                const auto cache=game.run->arena.supplyCache;
                auto pixel=GetWorldToScreen(cache.reward,game.camera);
                pixel.x*=1280.f/GetScreenWidth();pixel.y*=800.f/GetScreenHeight();
                EM_ASM({if(Module.verify)Module.demolition=({props:$0,room:$1,health:$2,destroyed:$3,x:$4,y:$5,keys:$6});},
                    int(game.run->arena.breakables.size()),cache.room,health,destroyed,pixel.x,pixel.y,game.run->keys);
            }
            const auto questPixel=game.questMarkerScreen();
            EM_ASM({
                if(Module.verify)Module.quest=({active:!!$0,stage:$1,dialogue:!!$2,sleeping:!!$3,walking:!!$4,
                    x:$5,y:$6,last:!!$7,speaker:UTF8ToString($8),search:!!$9});
            },game.arrivalActive(),int(game.arrivalStage()),game.questDialogueOpen(),game.sleeping(),game.walkingToQuest(),
              questPixel.x,questPixel.y,game.questLastLine(),game.questLine()?game.questLine()->speaker.c_str():"",
              game.run&&game.run->surveyTutorial);
            Vector2 evidencePixel{},exitPixel{};
            if(game.run) {
                const int site=game.run->storyRoomIndex();
                const auto p=game.run->surveyTutorial?game.run->surveyPosition():
                    site>=0?game.run->arena.rooms[size_t(site)].objective:game.run->player.position;
                evidencePixel=GetWorldToScreen({p.x,.33f,p.z},game.camera);
                exitPixel=GetWorldToScreen(game.run->arena.exit,game.camera);
                evidencePixel.x*=1280.f/GetScreenWidth();evidencePixel.y*=800.f/GetScreenHeight();
                exitPixel.x*=1280.f/GetScreenWidth();exitPixel.y*=800.f/GetScreenHeight();
            }
            EM_ASM({
                if(Module.verify)Module.expedition=({floor:$0,floors:$1,rooms:$2,account:$3,site:$4,
                    evidence:$5,journal:!!$6,letter:!!$7,evidenceX:$8,evidenceY:$9,exitX:$10,exitY:$11,
                    pacing:$12,roomWidth:$13,roomDepth:$14});
            },game.run?game.run->floor:-1,game.run?game.run->expedition.floorCount:0,
              game.run?game.run->arena.roomCount():0,game.run?int(game.run->expedition.account):0,
              game.run?game.run->storyRoomIndex():-1,game.run?int(game.run->evidence.size()):0,
              game.journalVisible(),game.letterVisible(),evidencePixel.x,evidencePixel.y,exitPixel.x,exitPixel.y,
              game.run?int(game.run->expedition.pacing):-1,
              game.run?game.run->arena.rooms[size_t(game.run->room)].bounds.max.x-game.run->arena.rooms[size_t(game.run->room)].bounds.min.x:0,
              game.run?game.run->arena.rooms[size_t(game.run->room)].bounds.max.z-game.run->arena.rooms[size_t(game.run->room)].bounds.min.z:0);
            EM_ASM({
                if(Module.verify) Module.cinematic=({active:!!$0,time:$1,playing:!!$2,dirty:!!$3,storm:$4,voices:$5});
                if(Module.verify) Object.assign(Module.cinematic,({cast:$6,speaker:UTF8ToString($7),story:!!$8,ending:!!$9,track:$10,key:$11,trainSpeed:$12}));
            },cinematic.active,cinematic.preview().time(),cinematic.preview().playing(),cinematic.dirty(),
              cinematic.active?cinematic.preview().storm():0.f,int(cinematic.audioVoices()),
              int(cinematic.document().cast.size()),cinematic.document().line(cinematic.preview().time())?cinematic.document().line(cinematic.preview().time())->speaker.c_str():"",
              cinematic.screening(),cinematic.showingDestination(),cinematic.selectedTrack(),cinematic.selectedKey(),
              cinematic.previewTrainSpeed());
            EM_ASM({
                if(Module.verify) {
                    Module.cinematic.intro=!!$0;
                    Module.cinematic.editorVisible=!!$1;
                    if($1)Module.cinematicEditorFrames=(Module.cinematicEditorFrames||0)+1;
                }
            },cinematic.runtimeIntro(),renderedCinematicEditor);
#endif
            const auto end = std::chrono::steady_clock::now();
            if (benchmark) {
                timings.push_back(std::chrono::duration<double, std::milli>(end - start).count());
                simulationMs += std::chrono::duration<double, std::milli>(simulated - start).count();
                drawMs += std::chrono::duration<double, std::milli>(drawn - simulated).count();
                presentMs += std::chrono::duration<double, std::milli>(end - drawn).count();
            }
            ++frame;
            if ((smoke || benchmark) && frame >= frames) {
                if (!screenshot.empty()) {
                    auto parent = std::filesystem::path(screenshot).parent_path();
                    if (!parent.empty())
                        std::filesystem::create_directories(parent);
                    Image capture = LoadImageFromScreen();
                    bool saved = ExportImage(capture, screenshot.c_str());
                    UnloadImage(capture);
                    if (!saved)
                        throw std::runtime_error("Could not export screenshot: " + screenshot);
                }
                break;
            }
        }
        if (benchmark && !timings.empty()) {
            std::sort(timings.begin(), timings.end());
            double mean = std::accumulate(timings.begin(), timings.end(), 0.0) / double(timings.size());
            std::cout << "BENCHMARK seed=1866 version=" << dw::ContentVersion
                      << " resolution=1440x900 frames=" << frame << " mean_ms=" << mean
                      << " p95_ms=" << timings[size_t(double(timings.size() - 1) * 0.95)]
                      << " max_ms=" << timings.back() << " max_projectiles=" << maxProjectiles
                      << " min_active_enemies=" << minEnemies << " min_active_projectiles=" << minProjectiles
                      << " kills=" << totalKills << " max_chain_depth=" << maxChain
                      << " suppressed=" << totalSuppressed << " simulation_ms=" << simulationMs / frame
                      << " draw_ms=" << drawMs / frame << " present_ms=" << presentMs / frame << '\n';
        }
        if(enemyScene&&game.run) {
            const auto *enemy=game.run->findEnemy(probeEnemy);
            if(const auto &h=game.run->rooms[size_t(game.run->room)].hornfel;h)
                std::cout<<"HORNFEL_PROBE state="<<int(h->state)<<" cart="<<h->cart.id<<" rider="<<h->cart.rider
                    <<" passes="<<h->passes<<" attacks="<<h->attacks<<" intact="<<h->cart.intact<<" completed="<<h->completed<<" escaped="<<h->escaped
                    <<" charges="<<h->charges<<" chargePasses="<<h->chargePasses<<" repeats="<<h->repeatsChosen<<" chargeBombs="<<h->chargeBombs
                    <<" recoveryShots="<<h->recoveryShots<<" fireWaves="<<game.run->fireWaves.size()
                    <<" escortsSpawned="<<h->escortsSpawned<<" escortsReleased="<<h->escortsReleased<<'\n';
            std::cout<<"ENEMY_PROBE id="<<dw::monsterIdText(*enemyScene)<<" frames="<<frame
                <<" alive="<<(enemy&&enemy->alive)<<" hp="<<(enemy?enemy->hp:0)
                <<" shots="<<game.run->stats.projectiles<<" threats="<<game.run->roomThreats()<<'\n';
            for(const auto &actor:game.run->enemies)if(actor.alive)
                std::cout<<"ENEMY_ACTOR id="<<dw::monsterIdText(actor.monster)<<" hp="<<actor.hp
                    <<" max_hp="<<actor.maxHp<<" state="<<int(actor.state)<<" owner="<<actor.summoner
                    <<" x="<<actor.position.x<<" y="<<actor.position.y<<" z="<<actor.position.z<<" radius="<<actor.radius<<" speed="<<dw::length(actor.velocity)<<" formation="<<actor.formation
                    <<" component_owner="<<actor.componentOwner<<" slot="<<actor.componentSlot<<" boss_form="<<int(actor.bossForm)<<" parts="<<actor.bossParts<<" attack="<<actor.bossAttack
                    <<" follow_parent="<<(actor.flyFollow?actor.flyFollow->parent:0)
                    <<" fear_frames="<<(actor.statuses?actor.statuses->fear:0)
                    <<" confusion_frames="<<(actor.statuses?actor.statuses->confusion:0)
                    <<" freeze_frames="<<(actor.statuses?actor.statuses->freeze:0)
                    <<" slow_frames="<<(actor.statuses?actor.statuses->slow:0)
                    <<" poison_frames="<<(actor.statuses?actor.statuses->poison.frames:0)
                    <<" burn_frames="<<(actor.statuses?actor.statuses->burn.frames:0)
                    <<" shrink_frames="<<(actor.statuses?actor.statuses->shrink:0)
                    <<" charm_frames="<<(actor.statuses?actor.statuses->charm:0)
                    <<" charm_target="<<(actor.statuses?actor.statuses->charmTarget:0)
                    <<" visual_scale="<<(actor.statuses?actor.statuses->visualScale:1)<<'\n';
            for(const auto &group:game.run->rooms[size_t(game.run->room)].formations)
                std::cout<<"ENEMY_GROUP id="<<group.id<<" x="<<group.center.x<<" z="<<group.center.z<<" angle="<<group.angle<<" slots="<<group.slots.size()<<'\n';
            for(const auto &p:game.run->projectiles)
                std::cout<<"ENEMY_BULLET kind="<<int(p.kind)<<" x="<<p.position.x<<" z="<<p.position.z
                    <<" vx="<<p.velocity.x<<" vz="<<p.velocity.z<<" curve="<<p.angularVelocity<<" life="<<p.life
                    <<" y="<<p.position.y<<" vy="<<p.velocity.y<<" time_scale="<<p.sourceTimeScale<<'\n';
            for(const auto &bomb:game.run->enemyBombs)
                std::cout<<"ENEMY_BOMB id="<<dw::monsterIdText(bomb.ordnance)<<" source="<<dw::monsterIdText(bomb.sourceMonster)
                    <<" room="<<bomb.room<<" x="<<bomb.charge.position.x<<" y="<<bomb.charge.position.y<<" z="<<bomb.charge.position.z
                    <<" age="<<bomb.charge.age<<" fuse="<<bomb.charge.delay<<" damage="<<bomb.charge.blastDamage<<'\n';
        }
        cinematic.unload();
        editor.unload();
        game.close();
        renderer.unload();
        audio.unload();
        CloseWindow();
#ifdef __EMSCRIPTEN__
        EM_ASM({
            Module.gameFinished = true;
            if (Module.showEnd)
                Module.showEnd();
        });
#endif
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "DeathWard: " << e.what() << '\n';
#ifdef __EMSCRIPTEN__
        EM_ASM(
            {
                if (Module.showError)
                    Module.showError(UTF8ToString($0));
            },
            e.what());
#endif
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
