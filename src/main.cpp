#include "core/Game.hpp"
#include "render/Renderer.hpp"
#include <algorithm>
#include <charconv>
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>

int main(int argc, char **argv) {
    std::filesystem::path save = dw::CampaignStore::defaultPath();
    bool smoke = false, benchmark = false;
    std::string screenshot, scene = "combat";
    int frames = 180;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--save" && i + 1 < argc)
            save = argv[++i];
        else if (arg == "--smoke")
            smoke = true;
        else if (arg == "--benchmark")
            benchmark = true;
        else if (arg == "--screenshot" && i + 1 < argc)
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
            std::cout << "DeathWard\n  --save PATH          Separate campaign file\n  --smoke              "
                         "Render a scripted scene, then exit\n  --scene NAME         combat, hub, key, "
                         "power, reward, "
                         "boss or summary (with --smoke)\n  --benchmark          Render the 100-enemy / "
                         "600-shot stress scenario\n  --frames N           Scripted frame count (default "
                         "180)\n  --screenshot PATH    Save a PNG before scripted exit\n";
            return 0;
        } else {
            std::cerr << "Unknown or incomplete option: " << arg << '\n';
            return 2;
        }
    }
    if (scene != "combat" && scene != "hub" && scene != "key" && scene != "power" && scene != "reward" &&
        scene != "boss" && scene != "summary") {
        std::cerr << "Unknown smoke scene: " << scene << '\n';
        return 2;
    }
    // Scripted verification never modifies the player's campaign by default.
    if (smoke || benchmark) {
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
        dw::Game game(save);
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
        InitWindow(1440, 900, "DeathWard | The consequences remain");
        if (!IsWindowReady())
            throw std::runtime_error("Cannot create a graphics window");
        SetWindowMinSize(1024, 640);
        SetExitKey(KEY_NULL);
        SetTargetFPS(benchmark ? 0 : 60);
        dw::Renderer renderer;
        if ((smoke && scene != "hub") || benchmark) {
            game.launch();
            if (!game.run)
                throw std::runtime_error(game.error);
            game.run->godMode = true;
            game.run->debugScenario = true;
            if (benchmark)
                game.run->startStress();
            else {
                game.run->spawnWave(12);
                if (scene == "combat" || scene == "boss" || scene == "summary")
                    for (int i = 0; i < dw::ItemCount; ++i)
                        game.run->grant(dw::ItemId(i));
            }
            if (smoke && scene == "boss")
                game.run->startBoss();
            if (smoke && scene == "key") {
                game.run->enterRoom(game.run->arena.keys.front().room);
                game.run->player.position = game.run->arena.rooms[size_t(game.run->room)].center;
                game.run->clearRoom();
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
        while (!WindowShouldClose() && !game.quit) {
            const auto start = std::chrono::steady_clock::now();
            if ((smoke || benchmark) && game.run) {
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
                game.update(GetFrameTime());
            const auto simulated = std::chrono::steady_clock::now();
            BeginDrawing();
            dw::Action action = renderer.draw(game);
            const auto drawn = std::chrono::steady_clock::now();
            EndDrawing();
            game.perform(action);
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
        game.close();
        CloseWindow();
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "DeathWard: " << e.what() << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
