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
    bool smoke = false, benchmark = false, startEditor = false, artPoc = false;
    bool startCinematic = false, intro = false, fullExperience = false, explicitSave = false;
    bool mute = false, explicitAudio = false, sandstorm = false;
    std::optional<bool> canyonRiver;
    dw::ThemeChoice themeChoice = dw::ThemeChoice::Canyon;
    dw::HubKind initialHub = dw::HubKind::BlackCreek;
    std::filesystem::path editorDirectory;
    std::filesystem::path sequenceFile;
    std::filesystem::path slotsDirectory;
    std::optional<float> cinematicTime;
    std::string screenshot, scene = "combat";
    int frames = 180;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--save" && i + 1 < argc) {
            save = argv[++i]; explicitSave = true;
        }
        else if (arg == "--full-experience")
            fullExperience = true;
        else if (arg == "--slots" && i + 1 < argc)
            slotsDirectory = argv[++i];
        else if (arg == "--art-poc")
            artPoc = true;
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
        else if (arg == "--frames" && i + 1 < argc) {
            const std::string value = argv[++i];
            auto parsed = std::from_chars(value.data(), value.data() + value.size(), frames);
            if (parsed.ec != std::errc{} || parsed.ptr != value.data() + value.size() || frames < 1) {
                std::cerr << "--frames needs a positive whole number\n";
                return 2;
            }
        } else if (arg == "--help") {
            std::cout << "DeathWard\n  --editor             Open the 3D town editor\n  --town DIRECTORY     "
                         "Town pack to edit (with --editor)\n  --save PATH          Separate campaign file\n "
                         " --theme NAME         seeded, mine or canyon (default)\n  --hub NAME           "
                         "black-creek"
                         ", frontier or redstone\n  --smoke              "
                         "Render a scripted scene, then exit\n  --scene NAME         combat, hub, key, "
                         "power, reward, empty, cheats, "
                         "boss or summary (with --smoke)\n  --benchmark          Render the 100-enemy / "
                         "600-shot stress scenario\n  --frames N           Scripted frame count (default "
                         "180)\n  --screenshot PATH    Save a PNG before scripted exit\n"
                         "  --art-poc           Redstone art experiment (F6 compares in hub/editor)\n"
                         "  --sandstorm         Start with the sandstorm on; K toggles in any map\n"
                         "  --intro             Play the Westbound opening (combine with --cinematic to edit)\n"
                         "  --full-experience   Logos, three save slots, settings and the story opening\n"
                         "  --slots DIRECTORY   Store full-experience slots in a separate folder\n"
                         "  --cinematic         Open the separate Cinematic Editor\n"
                         "  --sequence PATH     Cinematic file to edit (default: arrival.cinematic in hub)\n"
                         "  --cinematic-at SEC  Preview a specific timeline time\n"
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
    if (scene != "combat" && scene != "hub" && scene != "key" && scene != "power" && scene != "reward" &&
        scene != "boss" && scene != "summary" && scene != "empty" && scene != "cheats") {
        std::cerr << "Unknown smoke scene: " << scene << '\n';
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
        if (smoke || benchmark) game.seedText = "1866";
        game.audioSettings = audioSettings; game.visualSettings = visualSettings; game.audioStatus = audioStatus;
        auto savedAudioSettings = audioSettings;
        auto savedVisualSettings = visualSettings;
        for (const auto hub : dw::Hubs)
            if (upgradeTownNavigation(hub) && hub == game.activeHub) {
                if (!game.town.load(game.hubDirectory() / "town.nav") || !game.reloadTownObjects())
                    throw std::runtime_error("Could not reload the upgraded town navigation.");
                game.updateCamera(1);
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
            if (smoke && scene == "cheats")
                game.debug = true;
            if (smoke && scene == "empty") {
                for (int i = 0; i < dw::RoomCount; ++i)
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
                const int passage = game.run->arena.rooms[dw::RoomCount - 2].passages.front();
                game.run->arena.passages[size_t(passage)].locked = false;
                game.run->enterRoom(dw::RoomCount - 2);
                game.run->player.position = game.run->arena.rooms[size_t(game.run->room)].center;
            }
            if (smoke && scene == "reward") {
                game.run->enterRoom(dw::RoomCount - 2);
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
            const bool canCompareArt =
                cinematic.active ? false : editor.active ? dw::RedstoneArt::supports(editor.document())
                              : game.screen == dw::Screen::Hub && game.activeHub == dw::HubKind::Redstone;
            if (canCompareArt && IsKeyPressed(KEY_F6)) {
                artCompare = true;
                artPoc = !artPoc;
                TraceLog(LOG_INFO, "ART: %s (Redstone only)", artPoc ? "weathered POC" : "original look");
            }
            renderer.artPoc = editor.artPoc = artPoc;
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
                game.run->step(input);
                game.updateCamera(dw::Tick);
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
            if (artCompare && canCompareArt) {
                const char *label = artPoc ? "ART POC   /   F6: original" : "ORIGINAL   /   F6: art POC";
                const int width = MeasureText(label, 14) + 24;
                const int x = editing ? int(GetScreenWidth() * (1110.f / 1440)) - width - 10
                                      : (GetScreenWidth() - width) / 2;
                const int y = editing ? int(GetScreenHeight() * (94.f / 900)) : 4;
                DrawRectangle(x, y, width, 25, {25, 30, 30, 230});
                DrawText(label, x + 12, y + 5, 14, {221, 214, 192, 255});
            }
            const auto drawn = std::chrono::steady_clock::now();
            EndDrawing();
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
            audioFrame.paused = editing || filming || game.paused || game.letterVisible() || game.journalVisible() ||
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
                    evidence:$5,journal:!!$6,letter:!!$7,evidenceX:$8,evidenceY:$9,exitX:$10,exitY:$11});
            },game.run?game.run->floor:-1,game.run?game.run->expedition.floorCount:0,
              game.run?game.run->arena.roomCount():0,game.run?int(game.run->expedition.account):0,
              game.run?game.run->storyRoomIndex():-1,game.run?int(game.run->evidence.size()):0,
              game.journalVisible(),game.letterVisible(),evidencePixel.x,evidencePixel.y,exitPixel.x,exitPixel.y);
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
