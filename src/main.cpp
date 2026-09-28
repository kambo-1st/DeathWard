#include "audio/AudioSystem.hpp"
#include "core/Game.hpp"
#include "editor/TownEditor.hpp"
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

int main(int argc, char **argv) {
    std::filesystem::path save = dw::CampaignStore::defaultPath();
    bool smoke = false, benchmark = false, startEditor = false;
    bool mute = false, explicitAudio = false;
    dw::ThemeChoice themeChoice = dw::ThemeChoice::Canyon;
    dw::HubKind initialHub = dw::HubKind::BlackCreek;
    std::filesystem::path editorDirectory;
    std::string screenshot, scene = "combat";
    int frames = 180;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--save" && i + 1 < argc)
            save = argv[++i];
        else if (arg == "--editor")
            startEditor = true;
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
        else if (arg == "--theme" && i + 1 < argc) {
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
            else {
                std::cerr << "--hub must be black-creek or frontier\n";
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
                         "black-creek "
                         "or frontier\n  --smoke              "
                         "Render a scripted scene, then exit\n  --scene NAME         combat, hub, key, "
                         "power, reward, empty, cheats, "
                         "boss or summary (with --smoke)\n  --benchmark          Render the 100-enemy / "
                         "600-shot stress scenario\n  --frames N           Scripted frame count (default "
                         "180)\n  --screenshot PATH    Save a PNG before scripted exit\n"
                         "  --mute              Skip audio initialization\n"
                         "  --audio             Enable audio in scripted checks (silent by default)\n";
            return 0;
        } else {
            std::cerr << "Unknown or incomplete option: " << arg << '\n';
            return 2;
        }
    }
    if (scene != "combat" && scene != "hub" && scene != "key" && scene != "power" && scene != "reward" &&
        scene != "boss" && scene != "summary" && scene != "empty" && scene != "cheats") {
        std::cerr << "Unknown smoke scene: " << scene << '\n';
        return 2;
    }
    // Scripted verification never modifies the player's campaign by default.
    if (smoke || benchmark || startEditor) {
        bool explicitSave = false;
        for (int i = 1; i < argc; ++i)
            if (std::string(argv[i]) == "--save")
                explicitSave = true;
        if (!explicitSave)
            save = std::filesystem::temp_directory_path() /
                   ("deathward-check-" +
                    std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()) + ".save");
    }
    try {
        dw::prepareBrowserFiles();
        dw::Game game(save, initialHub);
        game.themeChoice = themeChoice;
        if (smoke || benchmark)
            game.seedText = "1866";
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
        InitWindow(1440, 900, "DeathWard | The consequences remain");
        if (!IsWindowReady())
            throw std::runtime_error("Cannot create a graphics window");
        SetWindowMinSize(1024, 640);
        SetExitKey(KEY_NULL);
#ifdef __EMSCRIPTEN__
        // The browser schedules frames. Never busy-wait or nanosleep on its UI thread.
        SetTargetFPS(0);
#else
        SetTargetFPS(benchmark ? 0 : 60);
#endif
        dw::AudioSystem audio;
        const auto audioPreferences =
            smoke || benchmark || startEditor ? std::filesystem::path{} : save.parent_path() / "audio.cfg";
        if (!audioPreferences.empty())
            game.audioSettings = dw::loadAudioSettings(audioPreferences);
        auto savedAudioSettings = game.audioSettings;
        game.audioStatus = audio.initialize(!mute && (!(smoke || benchmark) || explicitAudio));
        dw::Renderer renderer;
        const dw::Game::SceneryPicker pickScenery = [&](const auto &run, const auto &camera, Ray ray) {
            return renderer.pickScenery(run, camera, ray);
        };
        dw::TownEditor editor;
        if (startEditor) {
            const auto directory = editorDirectory.empty() ? game.hubDirectory() : editorDirectory;
            if (!editor.open(directory, game.camera))
                throw std::runtime_error(editor.status);
            SetWindowTitle("DeathWard | Town editor");
        }
        if ((smoke && scene != "hub") || benchmark) {
            game.launch();
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
                (browserWidth != GetScreenWidth() || browserHeight != GetScreenHeight()))
                SetWindowSize(browserWidth, browserHeight);
#else
            if (WindowShouldClose()) {
                if (editor.active)
                    editor.requestClose(true);
                else
                    break;
            }
#endif
            if (editor.quitRequested)
                break;
#ifdef __EMSCRIPTEN__
            if (EM_ASM_INT({
                    const pause = Module.pauseRequested || document.hidden || !document.hasFocus();
                    Module.pauseRequested = false;
                    return pause;
                })) {
                game.paused = true;
            }
#endif
            if (game.editorRequested) {
                game.editorRequested = false;
                if (!editor.open(game.hubDirectory(), game.camera))
                    game.error = editor.status;
                else
                    SetWindowTitle("DeathWard | Town editor");
            }
            const bool editing = editor.active;
            const auto start = std::chrono::steady_clock::now();
            if (editing) {
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
            BeginDrawing();
            dw::Action action = dw::Action::None;
            if (editing)
                editor.draw();
            else
                action = renderer.draw(game);
            const auto drawn = std::chrono::steady_clock::now();
            EndDrawing();
            game.perform(action);
            if (editing && !editor.active && !editor.quitRequested) {
                if (editor.saved) {
                    game.town.load(game.hubDirectory() / "town.nav");
                    renderer.reloadTown();
                }
                game.perform(dw::Action::Hub);
                SetWindowTitle("DeathWard | The consequences remain");
            }
            dw::AudioFrame audioFrame;
            audioFrame.camera = game.camera;
            audioFrame.dt = GetFrameTime();
            audioFrame.context = game.audioContext;
            audioFrame.music = editing ? dw::MusicScene::Silent : game.musicScene();
            audioFrame.paused = editing || game.paused ||
                                (game.screen != dw::Screen::Hub && game.screen != dw::Screen::Expedition);
            audioFrame.environment = game.activeHub == dw::HubKind::BlackCreek
                                         ? dw::AudioEnvironment::Town
                                         : dw::AudioEnvironment::Frontier;
            audioFrame.player = game.town.player.position;
            if (game.run) {
                audioFrame.environment = game.run->arena.theme == dw::MissionTheme::Canyon
                                             ? dw::AudioEnvironment::Canyon
                                             : dw::AudioEnvironment::Mine;
                audioFrame.player = game.run->player.position;
                audioFrame.room = game.run->audioEpoch;
                audioFrame.paused = audioFrame.paused || game.run->rewardOpen || game.run->dead;
                audioFrame.footsteps = game.run->player.dodge <= 0 && game.run->player.pullTime <= 0;
            }
            audio.update(audioFrame, game.audioSettings,
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
#ifdef __EMSCRIPTEN__
            // Read-only state for browser integration checks; absent during ordinary play.
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
                    }
                },
                editing, int(game.musicScene()), editor.saved, editor.status.c_str(),
                int(game.run ? game.run->money() : game.campaign.data().world.money),
                game.run ? int(game.run->moneyCollected) : 0, coinPixel.x, coinPixel.y,
                probeCoin ? probeCoin->value : 0);
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
