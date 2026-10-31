cmake_minimum_required(VERSION 3.20)
project(DeathWard VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(DEATHWARD_SANITIZERS "Enable address and undefined behavior sanitizers" OFF)
option(DEATHWARD_PACKAGED_ASSETS "Load native assets beside the executable, never from the checkout" OFF)
if(DEATHWARD_PACKAGED_ASSETS)
    add_compile_definitions(DEATHWARD_PACKAGED_ASSETS)
endif()
if(MSVC)
    # Preserve the game's UTF-8 text regardless of the Windows system code page.
    add_compile_options(/utf-8)
endif()
if(EMSCRIPTEN)
    set(PLATFORM Web CACHE STRING "raylib platform" FORCE)
    set(GRAPHICS GRAPHICS_API_OPENGL_ES3 CACHE STRING "WebGL 2" FORCE)
    set(BUILD_TESTING OFF CACHE BOOL "Native test executables" FORCE)
    add_compile_options(-fexceptions)
endif()
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE)
set(SUPPORT_MODULE_RAUDIO ON CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
FetchContent_Declare(raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
    URL_HASH SHA256=aea98ecf5bc5c5e0b789a76de0083a21a70457050ea4cc2aec7566935f5e258e
)
FetchContent_MakeAvailable(raylib)
# A missing output must fail initialization instead of succeeding with a silent null device.
target_compile_definitions(raylib PRIVATE MA_NO_NULL)

add_library(deathward_core
    src/content/ContentId.cpp
    src/content/Mechanics.cpp
    src/content/EncounterVariants.cpp
    src/combat/MonsterBoss.cpp
    src/combat/LokiBoss.cpp
    src/combat/HornfelBoss.cpp
    src/combat/HornfelDecoys.cpp
    src/combat/HornfelEscorts.cpp
    src/combat/RailTraffic.cpp
    src/combat/EnvironmentActors.cpp
    src/combat/SegmentedBoss.cpp
    src/combat/ShellBoss.cpp
    src/combat/BoomFlies.cpp
    src/combat/BloatBoss.cpp
    src/combat/Charging.cpp
    src/combat/Companions.cpp
    src/combat/Statues.cpp
    src/combat/OwnedComponents.cpp
    src/combat/Behavior.cpp
    src/combat/FireReactions.cpp
    src/combat/Mortality.cpp
    src/combat/LobWalkers.cpp
    src/combat/HeadShooters.cpp
    src/combat/MawFamily.cpp
    src/combat/Spitties.cpp
    src/combat/CardinalWalkers.cpp
    src/combat/Brains.cpp
    src/combat/LinkedHeads.cpp
    src/combat/Babies.cpp
    src/combat/Vis.cpp
    src/combat/Guts.cpp
    src/combat/Mirrors.cpp
    src/combat/Leeches.cpp
    src/combat/Lumps.cpp
    src/combat/AdultLeeches.cpp
    src/combat/Dips.cpp
    src/combat/MemBrains.cpp
    src/combat/MasksAndRemnants.cpp
    src/combat/ReturningBodies.cpp
    src/combat/Hosts.cpp
    src/combat/Mushrooms.cpp
    src/combat/TargetHops.cpp
    src/combat/Leapers.cpp
    src/combat/AdaptiveArmor.cpp
    src/combat/Eggies.cpp
    src/combat/BuzzFlies.cpp
    src/combat/Evaders.cpp
    src/combat/Swimmers.cpp
    src/combat/Spiders.cpp
    src/combat/Hardies.cpp
    src/combat/Dannies.cpp
    src/combat/RockSpiders.cpp
    src/combat/SpiderVariants.cpp
    src/combat/LongLegs.cpp
    src/combat/Boils.cpp
    src/combat/Willos.cpp
    src/combat/FireWaves.cpp
    src/combat/Hopping.cpp
    src/cinematic/Cinematic.cpp
    src/world/TownDocument.cpp
    src/world/TownWalkArea.cpp
    src/world/Particles.cpp
    src/world/ObjectAnimation.cpp
    src/world/TownNavigation.cpp
    src/world/HubWorld.cpp
    src/world/Animals.cpp
    src/world/TownCharacters.cpp
    src/world/ArrivalQuest.cpp
    src/world/SaveSlots.cpp
    src/world/FlagCloth.cpp
    src/world/Campaign.cpp
    src/world/Expedition.cpp
    src/world/Dungeon.cpp
    src/world/RailNetwork.cpp
    src/world/RailArena.cpp
    src/world/FlightNavigation.cpp
    src/world/Breakables.cpp
    src/world/FloorDressing.cpp
    src/combat/FloorEncounters.cpp
    src/combat/CanyonBoss.cpp
    src/combat/FrontierBoss.cpp
    src/world/CanyonTerrain.cpp
    src/world/CanyonRiver.cpp
    src/world/CanyonRoad.cpp
    src/world/RoomGraph.cpp
    src/combat/Simulation.cpp
    src/combat/Loot.cpp
    src/combat/Shop.cpp
    src/combat/Services.cpp
    src/combat/Dynamite.cpp
    src/combat/SuppliedBombs.cpp
    src/combat/FlyBombs.cpp
    src/combat/EnemyBombs.cpp
    src/combat/Destruction.cpp
    src/combat/ProjectileMotion.cpp
    src/combat/Enemies.cpp
    src/combat/Encounters.cpp
    src/combat/Monsters.cpp
    src/combat/MonsterMovement.cpp
    src/combat/Formations.cpp
    src/combat/Navigation.cpp
    src/items/Items.cpp
    src/items/ItemPools.cpp
)
target_include_directories(deathward_core PUBLIC src)
target_include_directories(deathward_core SYSTEM PUBLIC ${raylib_SOURCE_DIR}/src)
if(DEATHWARD_PACKAGED_ASSETS)
    # sourceAssetDirectory uses raylib's executable-directory lookup in portable builds.
    target_link_libraries(deathward_core PRIVATE raylib)
endif()
if(EMSCRIPTEN)
    target_compile_definitions(deathward_core PRIVATE DEATHWARD_ASSET_DIR="/assets")
else()
    target_compile_definitions(deathward_core PRIVATE DEATHWARD_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
endif()
if(MSVC)
    target_compile_options(deathward_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(deathward_core PRIVATE -Wall -Wextra -Wpedantic)
endif()
if(DEATHWARD_SANITIZERS AND NOT MSVC)
    target_compile_options(deathward_core PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(deathward_core PUBLIC -fsanitize=address,undefined)
endif()

file(GLOB animal_models CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/assets/animals"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/animals/*.glb")
add_library(deathward_skinning src/render/SkinnedModel.cpp src/render/ArtWardrobe.cpp)
target_link_libraries(deathward_skinning PUBLIC deathward_core raylib)
add_library(deathward_cloth src/render/FlagCloth.cpp)
target_link_libraries(deathward_cloth PUBLIC deathward_core raylib)
add_library(deathward_particles src/render/ParticleEffects.cpp src/render/RedstoneArt.cpp)
target_link_libraries(deathward_particles PUBLIC deathward_core raylib)
if(EMSCRIPTEN)
    target_compile_definitions(deathward_particles PRIVATE DEATHWARD_ASSET_DIR="/assets")
else()
    target_compile_definitions(deathward_particles PRIVATE DEATHWARD_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
endif()
add_library(deathward_mission_lighting src/render/MissionLighting.cpp src/render/GroundSurface.cpp src/render/CanyonWater.cpp)
target_link_libraries(deathward_mission_lighting PUBLIC deathward_core raylib)
function(deathward_assets target)
    target_link_libraries(${target} PRIVATE deathward_skinning deathward_particles deathward_mission_lighting deathward_cloth)
    if(EMSCRIPTEN)
        target_compile_definitions(${target} PRIVATE DEATHWARD_ASSET_DIR="/assets")
        return()
    endif()
    target_compile_definitions(${target} PRIVATE DEATHWARD_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
    if(TARGET deathward_runtime_assets)
        add_dependencies(${target} deathward_runtime_assets)
        return()
    endif()
    # Game and graphics checks share a runtime directory. Stage it once: parallel
    # per-executable copies race on Windows file locks (especially streamed audio).
    add_custom_target(deathward_runtime_assets)
    add_dependencies(${target} deathward_runtime_assets)
    add_custom_command(TARGET deathward_runtime_assets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets/mechanics" "$<TARGET_FILE_DIR:deathward>/assets/mechanics"
        VERBATIM)
    foreach(ui_file title.ttf body.ttf LICENSE.txt)
        set(ui_asset "${CMAKE_CURRENT_SOURCE_DIR}/assets/ui/${ui_file}")
        add_custom_command(TARGET deathward_runtime_assets POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:deathward>/assets/ui"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${ui_asset}" "$<TARGET_FILE_DIR:deathward>/assets/ui/${ui_file}"
            VERBATIM)
    endforeach()
    file(GLOB particle_assets CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/assets/particles/*.glb"
        "${CMAKE_CURRENT_SOURCE_DIR}/assets/particles/*.png"
        "${CMAKE_CURRENT_SOURCE_DIR}/assets/particles/*.particles"
        "${CMAKE_CURRENT_SOURCE_DIR}/assets/particles/*.attachments")
    foreach(particle_asset ${particle_assets})
        get_filename_component(particle_file "${particle_asset}" NAME)
        add_custom_command(TARGET deathward_runtime_assets POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:deathward>/assets/particles"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${particle_asset}" "$<TARGET_FILE_DIR:deathward>/assets/particles/${particle_file}"
            VERBATIM)
    endforeach()
    file(GLOB_RECURSE audio_assets CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/audio/*.wav" "${CMAKE_CURRENT_SOURCE_DIR}/assets/audio/*.ogg")
    add_custom_command(TARGET deathward_runtime_assets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets/audio" "$<TARGET_FILE_DIR:deathward>/assets/audio"
        VERBATIM)
    foreach(animal_file ${animal_models} town.animals)
        set(animal_asset "${CMAKE_CURRENT_SOURCE_DIR}/assets/animals/${animal_file}")
        add_custom_command(TARGET deathward_runtime_assets POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:deathward>/assets/animals"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${animal_asset}" "$<TARGET_FILE_DIR:deathward>/assets/animals/${animal_file}"
            VERBATIM)
    endforeach()
    set(bandit_asset "${CMAKE_CURRENT_SOURCE_DIR}/assets/bandit/bandit.glb")
    set(cowgirl_asset "${CMAKE_CURRENT_SOURCE_DIR}/assets/cowgirl/cowgirl.glb")
    add_custom_command(TARGET deathward_runtime_assets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:deathward>/assets/cowgirl"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${cowgirl_asset}" "$<TARGET_FILE_DIR:deathward>/assets/cowgirl/cowgirl.glb"
        VERBATIM)
    add_custom_command(TARGET deathward_runtime_assets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:deathward>/assets/bandit"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${bandit_asset}" "$<TARGET_FILE_DIR:deathward>/assets/bandit/bandit.glb"
        VERBATIM)
    foreach(western_file western.glb western.catalog)
        set(western_asset "${CMAKE_CURRENT_SOURCE_DIR}/assets/western/${western_file}")
        add_custom_command(TARGET deathward_runtime_assets POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:deathward>/assets/western"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${western_asset}" "$<TARGET_FILE_DIR:deathward>/assets/western/${western_file}"
            VERBATIM)
    endforeach()
    file(GLOB cast_assets CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/cinematic_cast/*.glb")
    add_custom_command(TARGET deathward_runtime_assets POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets/cinematic_cast" "$<TARGET_FILE_DIR:deathward>/assets/cinematic_cast"
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:deathward>/assets/train_opening"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_CURRENT_SOURCE_DIR}/assets/train_opening/arrival.cinematic" "$<TARGET_FILE_DIR:deathward>/assets/train_opening/arrival.cinematic" VERBATIM)
    foreach(hub_pack town frontier redstone train_opening)
        foreach(town_file town.glb town.scene town.nav town.labels)
            set(town_asset "${CMAKE_CURRENT_SOURCE_DIR}/assets/${hub_pack}/${town_file}")
            add_custom_command(TARGET deathward_runtime_assets POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:deathward>/assets/${hub_pack}"
                COMMAND ${CMAKE_COMMAND} -E copy_if_different "${town_asset}" "$<TARGET_FILE_DIR:deathward>/assets/${hub_pack}/${town_file}"
                VERBATIM)
        endforeach()
    endforeach()
endfunction()

add_executable(deathward src/main.cpp src/core/FrontEnd.cpp src/audio/AudioSystem.cpp src/audio/MusicDirector.cpp src/cinematic/CinematicAudio.cpp src/editor/CinematicEditor.cpp src/render/PostProcess.cpp src/editor/TownEditor.cpp src/editor/TownEditorAnimals.cpp src/editor/TownEditorNavigation.cpp src/render/Renderer.cpp src/render/PlayerModel.cpp src/render/AnimalModels.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp src/render/TownScene.cpp src/core/Game.cpp src/core/GameQuest.cpp)
target_link_libraries(deathward PRIVATE deathward_core raylib)
deathward_assets(deathward)
if(EMSCRIPTEN)
    set_target_properties(deathward PROPERTIES OUTPUT_NAME index SUFFIX ".html")
    target_link_options(deathward PRIVATE
        -sASYNCIFY=1 -sASYNCIFY_STACK_SIZE=262144
        -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=268435456 -sMAXIMUM_MEMORY=2147483648
        -sSTACK_SIZE=8388608 -sDISABLE_EXCEPTION_CATCHING=0 -sFORCE_FILESYSTEM=1
        -sGL_ENABLE_GET_PROC_ADDRESS=1 -sENVIRONMENT=web -sEXIT_RUNTIME=0
        "-sEXPORTED_RUNTIME_METHODS=['callMain','FS','HEAPF32']"
        -lidbfs.js "SHELL:--shell-file '${CMAKE_CURRENT_SOURCE_DIR}/web/shell.html'")
    set(web_assets
        assets/ui/title.ttf assets/ui/body.ttf assets/ui/LICENSE.txt
        assets/bandit/bandit.glb assets/cowgirl/cowgirl.glb assets/western/western.glb assets/western/western.catalog)
    file(GLOB mechanics_assets CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "assets/mechanics/*.mechanics")
    list(APPEND web_assets ${mechanics_assets})
    file(GLOB web_particles CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "assets/particles/*.glb" "assets/particles/*.png"
        "assets/particles/*.particles" "assets/particles/*.attachments")
    list(APPEND web_assets ${web_particles})
    foreach(animal_file ${animal_models} town.animals)
        list(APPEND web_assets assets/animals/${animal_file})
    endforeach()
    foreach(hub town frontier redstone train_opening)
        foreach(name town.glb town.scene town.nav town.labels)
            list(APPEND web_assets assets/${hub}/${name})
        endforeach()
    endforeach()
    file(GLOB_RECURSE web_audio CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "assets/audio/*.wav" "assets/audio/*.ogg")
    list(APPEND web_assets ${web_audio})
    file(GLOB web_cast CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "assets/cinematic_cast/*.glb")
    list(APPEND web_assets ${web_cast} assets/train_opening/arrival.cinematic)
    foreach(asset IN LISTS web_assets)
        target_link_options(deathward PRIVATE "SHELL:--preload-file '${CMAKE_CURRENT_SOURCE_DIR}/${asset}@/${asset}'")
        set_property(TARGET deathward APPEND PROPERTY LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${asset}")
    endforeach()
    set_property(TARGET deathward APPEND PROPERTY LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/web/shell.html")
endif()
if(NOT MSVC)
    target_compile_options(deathward PRIVATE -Wall -Wextra -Wpedantic)
    if(EMSCRIPTEN)
        target_compile_options(deathward PRIVATE -Wno-dollar-in-identifier-extension)
    endif()
endif()
include(CTest)
option(DEATHWARD_ART_SAMPLE "Build the isolated, reversible asset art-direction viewer" OFF)
if(DEATHWARD_ART_SAMPLE AND NOT EMSCRIPTEN)
    add_executable(deathward_art_sample EXCLUDE_FROM_ALL tools/art_sample.cpp src/render/PlayerModel.cpp src/render/PostProcess.cpp)
    target_link_libraries(deathward_art_sample PRIVATE deathward_core raylib deathward_skinning deathward_mission_lighting)
    target_compile_definitions(deathward_art_sample PRIVATE DEATHWARD_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
endif()
if(NOT EMSCRIPTEN)
    add_executable(deathward_check_mechanics tools/check_mechanics.cpp)
    target_link_libraries(deathward_check_mechanics PRIVATE deathward_core raylib)
    add_executable(deathward_bake_navigation tools/bake_navigation.cpp)
    target_link_libraries(deathward_bake_navigation PRIVATE deathward_core raylib)
endif()

if(BUILD_TESTING)
    find_package(Python3 COMPONENTS Interpreter QUIET)
    if(Python3_Interpreter_FOUND)
        add_test(NAME enemy_port_coverage COMMAND ${Python3_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/scripts/isaac-reference/track-enemies.py --check)
    endif()
    add_executable(deathward_mechanics_tests tests/mechanics_tests.cpp)
    target_link_libraries(deathward_mechanics_tests PRIVATE deathward_core raylib)
    add_test(NAME mechanics_content COMMAND deathward_mechanics_tests)
    add_executable(deathward_expedition_economy_tests tests/expedition_economy_tests.cpp)
    target_link_libraries(deathward_expedition_economy_tests PRIVATE deathward_core)
    add_test(NAME expedition_economy COMMAND deathward_expedition_economy_tests)
    add_executable(deathward_canyon_boss_tests tests/canyon_boss_tests.cpp)
    target_link_libraries(deathward_canyon_boss_tests PRIVATE deathward_core)
    add_test(NAME canyon_bosses COMMAND deathward_canyon_boss_tests)
    add_executable(deathward_floor_progression_tests tests/floor_progression_tests.cpp)
    target_link_libraries(deathward_floor_progression_tests PRIVATE deathward_core)
    add_test(NAME floor_progression COMMAND deathward_floor_progression_tests)
    # A narrow river edge passed padded placement but blocked a Gaper's body.
    add_test(NAME floor_resident_placement COMMAND deathward_floor_progression_tests --scan-placement 404 404)
    add_executable(deathward_item_build_tests tests/item_build_tests.cpp)
    target_link_libraries(deathward_item_build_tests PRIVATE deathward_core)
    add_test(NAME item_builds COMMAND deathward_item_build_tests)
    add_executable(deathward_destruction_tests tests/destruction_tests.cpp)
    target_link_libraries(deathward_destruction_tests PRIVATE deathward_core)
    add_test(NAME expedition_destruction COMMAND deathward_destruction_tests)
    add_executable(deathward_walk_area_tests tests/walk_area_tests.cpp)
    target_link_libraries(deathward_walk_area_tests PRIVATE deathward_core raylib)
    add_test(NAME walkable_areas COMMAND deathward_walk_area_tests)
    add_executable(deathward_expedition_tests tests/expedition_tests.cpp)
    target_link_libraries(deathward_expedition_tests PRIVATE deathward_core)
    target_compile_definitions(deathward_expedition_tests PRIVATE DEATHWARD_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_test(NAME expedition COMMAND deathward_expedition_tests)
    add_executable(deathward_pacing_tests tests/pacing_tests.cpp)
    target_link_libraries(deathward_pacing_tests PRIVATE deathward_core)
    add_test(NAME expedition_pacing COMMAND deathward_pacing_tests)
    add_executable(deathward_flag_cloth_tests tests/flag_cloth_tests.cpp)
    target_link_libraries(deathward_flag_cloth_tests PRIVATE deathward_core)
    target_include_directories(deathward_flag_cloth_tests SYSTEM PRIVATE ${raylib_SOURCE_DIR}/src/external)
    target_compile_definitions(deathward_flag_cloth_tests PRIVATE DEATHWARD_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_test(NAME flag_cloth COMMAND deathward_flag_cloth_tests)
    # Explicit visual check; ordinary CTest remains independent of a display.
    add_executable(deathward_flag_render_tests tests/flag_render_tests.cpp src/render/TownScene.cpp src/render/PostProcess.cpp)
    target_link_libraries(deathward_flag_render_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_flag_render_tests)
    add_executable(deathward_save_slot_tests tests/save_slot_tests.cpp)
    target_link_libraries(deathward_save_slot_tests PRIVATE deathward_core)
    add_test(NAME save_slots COMMAND deathward_save_slot_tests)
    add_executable(deathward_arrival_input_tests tests/arrival_input_tests.cpp src/render/PostProcess.cpp src/core/Game.cpp src/core/GameQuest.cpp src/render/Renderer.cpp src/render/PlayerModel.cpp src/render/AnimalModels.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp src/render/TownScene.cpp)
    target_link_libraries(deathward_arrival_input_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_arrival_input_tests)
    add_executable(deathward_arrival_quest_tests tests/arrival_quest_tests.cpp)
    target_link_libraries(deathward_arrival_quest_tests PRIVATE deathward_core)
    target_compile_definitions(deathward_arrival_quest_tests PRIVATE DEATHWARD_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_test(NAME arrival_quest COMMAND deathward_arrival_quest_tests)
    add_executable(deathward_cinematic_cast_tests tests/cinematic_cast_tests.cpp)
    target_link_libraries(deathward_cinematic_cast_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_cinematic_cast_tests)
    add_executable(deathward_cinematic_tests tests/cinematic_tests.cpp)
    target_link_libraries(deathward_cinematic_tests PRIVATE deathward_core)
    add_test(NAME cinematic_timeline COMMAND deathward_cinematic_tests)
    # Explicit display/audio test; keep ordinary CTest independent of WSLg devices.
    add_executable(deathward_cinematic_editor_tests tests/cinematic_editor_tests.cpp
        src/editor/CinematicEditor.cpp src/cinematic/CinematicAudio.cpp
        src/render/TownScene.cpp src/render/PostProcess.cpp src/render/AnimalModels.cpp)
    target_link_libraries(deathward_cinematic_editor_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_cinematic_editor_tests)
    add_executable(deathward_road_tests tests/road_tests.cpp)
    target_link_libraries(deathward_road_tests PRIVATE deathward_core)
    add_test(NAME canyon_roads COMMAND deathward_road_tests)
    add_executable(deathward_river_tests tests/river_tests.cpp)
    target_link_libraries(deathward_river_tests PRIVATE deathward_core)
    add_test(NAME canyon_rivers COMMAND deathward_river_tests)
    add_executable(deathward_redstone_tests tests/redstone_tests.cpp)
    target_link_libraries(deathward_redstone_tests PRIVATE deathward_core)
    target_compile_definitions(deathward_redstone_tests PRIVATE DEATHWARD_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_test(NAME redstone_hub COMMAND deathward_redstone_tests)
    add_executable(deathward_art_direction_tests tests/art_direction_tests.cpp src/render/TownScene.cpp src/render/PlayerModel.cpp src/render/PostProcess.cpp)
    target_link_libraries(deathward_art_direction_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_art_direction_tests)
    add_executable(deathward_cel_shading_tests tests/cel_shading_tests.cpp src/render/TownScene.cpp src/render/PlayerModel.cpp src/render/PostProcess.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp)
    target_link_libraries(deathward_cel_shading_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_cel_shading_tests)
    add_executable(deathward_redstone_render_tests tests/redstone_render_tests.cpp src/render/TownScene.cpp src/render/PlayerModel.cpp src/render/PostProcess.cpp)
    target_link_libraries(deathward_redstone_render_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_redstone_render_tests)
    add_executable(deathward_building_navigation_tests tests/building_navigation_tests.cpp)
    target_link_libraries(deathward_building_navigation_tests PRIVATE deathward_core)
    add_test(NAME building_navigation COMMAND deathward_building_navigation_tests)
    add_executable(deathward_building_tests tests/building_tests.cpp src/render/TownScene.cpp src/render/PlayerModel.cpp src/render/PostProcess.cpp)
    target_link_libraries(deathward_building_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_building_tests)
    add_executable(deathward_particle_tests tests/particle_tests.cpp)
    target_link_libraries(deathward_particle_tests PRIVATE deathward_core)
    target_compile_definitions(deathward_particle_tests PRIVATE DEATHWARD_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_test(NAME particle_emission COMMAND deathward_particle_tests)
    add_executable(deathward_particle_render_tests tests/particle_render_tests.cpp src/render/TownScene.cpp src/render/PostProcess.cpp)
    target_link_libraries(deathward_particle_render_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_particle_render_tests)
    add_executable(deathward_character_tests tests/character_tests.cpp)
    target_link_libraries(deathward_character_tests PRIVATE deathward_core)
    target_compile_definitions(deathward_character_tests PRIVATE DEATHWARD_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_test(NAME town_characters COMMAND deathward_character_tests)
    add_executable(deathward_character_model_tests tests/character_model_tests.cpp)
    target_link_libraries(deathward_character_model_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_character_model_tests)
    add_executable(deathward_animal_tests tests/animal_tests.cpp)
    target_link_libraries(deathward_animal_tests PRIVATE deathward_core)
    add_test(NAME ambient_animals COMMAND deathward_animal_tests)
    add_executable(deathward_animal_model_tests tests/animal_model_tests.cpp src/render/AnimalModels.cpp)
    target_link_libraries(deathward_animal_model_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_animal_model_tests)
    add_executable(deathward_train_tests tests/train_tests.cpp)
    target_link_libraries(deathward_train_tests PRIVATE deathward_core)
    add_test(NAME train_motion COMMAND deathward_train_tests)
    add_executable(deathward_object_animation_tests tests/object_animation_tests.cpp)
    target_link_libraries(deathward_object_animation_tests PRIVATE deathward_core)
    add_test(NAME object_animation COMMAND deathward_object_animation_tests)
    add_executable(deathward_dynamite_tests tests/dynamite_tests.cpp)
    target_link_libraries(deathward_dynamite_tests PRIVATE deathward_core)
    add_test(NAME player_dynamite COMMAND deathward_dynamite_tests)
    add_executable(deathward_shop_tests tests/shop_tests.cpp)
    target_link_libraries(deathward_shop_tests PRIVATE deathward_core)
    add_test(NAME mission_shop COMMAND deathward_shop_tests)
    add_executable(deathward_money_tests tests/money_tests.cpp)
    target_link_libraries(deathward_money_tests PRIVATE deathward_core)
    add_test(NAME money_pickups COMMAND deathward_money_tests)
    add_executable(deathward_resident_enemies_tests tests/resident_enemies_tests.cpp)
    target_link_libraries(deathward_resident_enemies_tests PRIVATE deathward_core)
    add_test(NAME resident_enemies COMMAND deathward_resident_enemies_tests)
    add_executable(deathward_audio_cue_tests tests/audio_cue_tests.cpp)
    target_link_libraries(deathward_audio_cue_tests PRIVATE deathward_core)
    add_test(NAME audio_presentation COMMAND deathward_audio_cue_tests)
    # Explicit device check; regular CTest remains independent of audio hardware/WSLg.
    add_executable(deathward_audio_tests tests/audio_tests.cpp src/audio/AudioSystem.cpp src/audio/MusicDirector.cpp)
    target_link_libraries(deathward_audio_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_audio_tests)
    add_executable(deathward_monster_tests tests/monster_tests.cpp)
    target_link_libraries(deathward_monster_tests PRIVATE deathward_core)
    add_test(NAME monster_behaviors COMMAND deathward_monster_tests)
    add_executable(deathward_flight_tests tests/flight_tests.cpp)
    target_link_libraries(deathward_flight_tests PRIVATE deathward_core)
    add_test(NAME monster_flight COMMAND deathward_flight_tests)
    add_executable(deathward_formation_tests tests/formation_tests.cpp)
    target_link_libraries(deathward_formation_tests PRIVATE deathward_core)
    add_test(NAME monster_formations COMMAND deathward_formation_tests)
    add_executable(deathward_pattern_tests tests/pattern_tests.cpp)
    target_link_libraries(deathward_pattern_tests PRIVATE deathward_core)
    add_test(NAME monster_patterns COMMAND deathward_pattern_tests)
    add_executable(deathward_source_projectile_tests tests/source_projectile_tests.cpp)
    target_link_libraries(deathward_source_projectile_tests PRIVATE deathward_core)
    add_test(NAME source_projectile_motion COMMAND deathward_source_projectile_tests)
    add_executable(deathward_spitty_tests tests/spitty_tests.cpp)
    target_link_libraries(deathward_spitty_tests PRIVATE deathward_core)
    add_test(NAME spitty_family COMMAND deathward_spitty_tests)
    add_executable(deathward_cardinal_walker_tests tests/cardinal_walker_tests.cpp)
    target_link_libraries(deathward_cardinal_walker_tests PRIVATE deathward_core)
    add_test(NAME cardinal_walkers COMMAND deathward_cardinal_walker_tests)
    add_executable(deathward_brain_tests tests/brain_tests.cpp)
    target_link_libraries(deathward_brain_tests PRIVATE deathward_core)
    add_test(NAME brain COMMAND deathward_brain_tests)
    add_executable(deathward_baby_tests tests/baby_tests.cpp)
    target_link_libraries(deathward_baby_tests PRIVATE deathward_core)
    add_test(NAME baby_family COMMAND deathward_baby_tests)
    add_executable(deathward_vis_tests tests/vis_tests.cpp)
    target_link_libraries(deathward_vis_tests PRIVATE deathward_core)
    add_test(NAME vis_family COMMAND deathward_vis_tests)
    add_executable(deathward_chubber_tests tests/chubber_tests.cpp)
    target_link_libraries(deathward_chubber_tests PRIVATE deathward_core)
    add_test(NAME chubber_family COMMAND deathward_chubber_tests)
    add_executable(deathward_guts_tests tests/guts_tests.cpp)
    target_link_libraries(deathward_guts_tests PRIVATE deathward_core)
    add_test(NAME guts_family COMMAND deathward_guts_tests)
    add_executable(deathward_knight_tests tests/knight_tests.cpp)
    target_link_libraries(deathward_knight_tests PRIVATE deathward_core)
    add_test(NAME knight_lifecycle COMMAND deathward_knight_tests)
    add_executable(deathward_leech_tests tests/leech_tests.cpp)
    target_link_libraries(deathward_leech_tests PRIVATE deathward_core)
    add_test(NAME leech_behavior COMMAND deathward_leech_tests)
    add_executable(deathward_lump_tests tests/lump_tests.cpp)
    target_link_libraries(deathward_lump_tests PRIVATE deathward_core)
    add_test(NAME lump_behavior COMMAND deathward_lump_tests)
    add_executable(deathward_adult_leech_tests tests/adult_leech_tests.cpp)
    target_link_libraries(deathward_adult_leech_tests PRIVATE deathward_core)
    add_test(NAME adult_leech COMMAND deathward_adult_leech_tests)
    add_executable(deathward_dip_variant_tests tests/dip_variant_tests.cpp)
    target_link_libraries(deathward_dip_variant_tests PRIVATE deathward_core)
    add_test(NAME dip_variants COMMAND deathward_dip_variant_tests)
    add_executable(deathward_dinga_tests tests/dinga_tests.cpp)
    target_link_libraries(deathward_dinga_tests PRIVATE deathward_core)
    add_test(NAME dinga_family COMMAND deathward_dinga_tests)
    add_executable(deathward_membrain_tests tests/membrain_tests.cpp)
    target_link_libraries(deathward_membrain_tests PRIVATE deathward_core)
    add_test(NAME membrain_family COMMAND deathward_membrain_tests)

    add_executable(deathward_mirror_tests tests/mirror_tests.cpp)
    target_link_libraries(deathward_mirror_tests PRIVATE deathward_core)
    add_test(NAME mirror_behavior COMMAND deathward_mirror_tests)
    add_executable(deathward_linked_head_tests tests/linked_head_tests.cpp)
    target_link_libraries(deathward_linked_head_tests PRIVATE deathward_core)
    add_test(NAME linked_head COMMAND deathward_linked_head_tests)
    add_executable(deathward_fire_reaction_tests tests/fire_reaction_tests.cpp)
    target_link_libraries(deathward_fire_reaction_tests PRIVATE deathward_core)
    add_test(NAME monster_fire_reactions COMMAND deathward_fire_reaction_tests)
    add_executable(deathward_hop_tests tests/hop_tests.cpp)
    target_link_libraries(deathward_hop_tests PRIVATE deathward_core)
    add_test(NAME monster_hopping COMMAND deathward_hop_tests)
    add_executable(deathward_replacement_tests tests/replacement_tests.cpp)
    target_link_libraries(deathward_replacement_tests PRIVATE deathward_core)
    add_test(NAME monster_replacements COMMAND deathward_replacement_tests)
    add_executable(deathward_monster_boss_tests tests/monster_boss_tests.cpp)
    target_link_libraries(deathward_monster_boss_tests PRIVATE deathward_core)
    add_test(NAME monster_boss_components COMMAND deathward_monster_boss_tests)
    add_executable(deathward_bloat_tests tests/bloat_tests.cpp)
    target_link_libraries(deathward_bloat_tests PRIVATE deathward_core)
    add_test(NAME bloat_boss_and_chargers COMMAND deathward_bloat_tests)
    add_executable(deathward_charger_tests tests/charger_variant_tests.cpp)
    target_link_libraries(deathward_charger_tests PRIVATE deathward_core)
    add_test(NAME charger_variants COMMAND deathward_charger_tests)
    add_executable(deathward_companion_tests tests/companion_tests.cpp)
    target_link_libraries(deathward_companion_tests PRIVATE deathward_core)
    add_test(NAME companion_familiars COMMAND deathward_companion_tests)
    add_executable(deathward_statue_tests tests/statue_tests.cpp)
    target_link_libraries(deathward_statue_tests PRIVATE deathward_core)
    add_test(NAME room_statues COMMAND deathward_statue_tests)
    add_executable(deathward_maw_tests tests/maw_tests.cpp)
    target_link_libraries(deathward_maw_tests PRIVATE deathward_core)
    add_test(NAME maw_attraction COMMAND deathward_maw_tests)
    add_executable(deathward_quake_tests tests/quake_tests.cpp)
    target_link_libraries(deathward_quake_tests PRIVATE deathward_core)
    add_test(NAME quake_waves COMMAND deathward_quake_tests)
    add_executable(deathward_supplied_bomb_tests tests/supplied_bomb_tests.cpp)
    target_link_libraries(deathward_supplied_bomb_tests PRIVATE deathward_core)
    add_test(NAME supplied_bombs COMMAND deathward_supplied_bomb_tests)
    add_executable(deathward_fly_bomb_tests tests/fly_bomb_tests.cpp)
    target_link_libraries(deathward_fly_bomb_tests PRIVATE deathward_core)
    add_test(NAME fly_bombs COMMAND deathward_fly_bomb_tests)
    add_executable(deathward_enemy_bomb_tests tests/enemy_bomb_tests.cpp)
    target_link_libraries(deathward_enemy_bomb_tests PRIVATE deathward_core)
    add_test(NAME enemy_bomb_payloads COMMAND deathward_enemy_bomb_tests)
    add_executable(deathward_rail_tests tests/rail_tests.cpp)
    target_link_libraries(deathward_rail_tests PRIVATE deathward_core)
    add_test(NAME authored_rails COMMAND deathward_rail_tests)
    add_executable(deathward_boom_fly_tests tests/boom_fly_tests.cpp)
    target_link_libraries(deathward_boom_fly_tests PRIVATE deathward_core)
    add_test(NAME boom_flies COMMAND deathward_boom_fly_tests)
    add_executable(deathward_loki_tests tests/loki_tests.cpp)
    target_link_libraries(deathward_loki_tests PRIVATE deathward_core)
    add_test(NAME loki_bosses COMMAND deathward_loki_tests)
    add_executable(deathward_hornfel_tests tests/hornfel_tests.cpp)
    target_link_libraries(deathward_hornfel_tests PRIVATE deathward_core)
    add_test(NAME hornfel_boss COMMAND deathward_hornfel_tests)
    add_executable(deathward_rail_passenger_tests tests/rail_passenger_tests.cpp)
    target_link_libraries(deathward_rail_passenger_tests PRIVATE deathward_core)
    add_test(NAME rail_passengers COMMAND deathward_rail_passenger_tests)
    add_executable(deathward_bony_tests tests/bony_tests.cpp)
    target_link_libraries(deathward_bony_tests PRIVATE deathward_core)
    add_test(NAME bony_regular_enemy COMMAND deathward_bony_tests)
    add_executable(deathward_black_bony_tests tests/black_bony_tests.cpp)
    target_link_libraries(deathward_black_bony_tests PRIVATE deathward_core)
    add_test(NAME black_bony_regular_enemy COMMAND deathward_black_bony_tests)
    add_executable(deathward_mortality_tests tests/mortality_tests.cpp)
    target_link_libraries(deathward_mortality_tests PRIVATE deathward_core)
    add_test(NAME source_immunity_and_lethal_morph COMMAND deathward_mortality_tests)
    add_executable(deathward_lob_walker_tests tests/lob_walker_tests.cpp)
    target_link_libraries(deathward_lob_walker_tests PRIVATE deathward_core)
    add_test(NAME gurgle_splasher_physical_lobs COMMAND deathward_lob_walker_tests)
    add_executable(deathward_crackle_tests tests/crackle_tests.cpp)
    target_link_libraries(deathward_crackle_tests PRIVATE deathward_core)
    add_test(NAME crackle_discrete_fire_jets COMMAND deathward_crackle_tests)
    add_executable(deathward_horf_tests tests/horf_tests.cpp)
    target_link_libraries(deathward_horf_tests PRIVATE deathward_core)
    add_test(NAME horf_stationary_shooting COMMAND deathward_horf_tests)
    add_executable(deathward_buzz_fly_tests tests/buzz_fly_tests.cpp)
    target_link_libraries(deathward_buzz_fly_tests PRIVATE deathward_core)
    add_test(NAME buzzing_flies COMMAND deathward_buzz_fly_tests)
    add_executable(deathward_tainted_pooter_tests tests/tainted_pooter_tests.cpp)
    target_link_libraries(deathward_tainted_pooter_tests PRIVATE deathward_core)
    add_test(NAME tainted_pooter_impacts COMMAND deathward_tainted_pooter_tests)
    add_executable(deathward_evader_tests tests/evader_tests.cpp)
    target_link_libraries(deathward_evader_tests PRIVATE deathward_core)
    add_test(NAME hive_evaders COMMAND deathward_evader_tests)
    add_executable(deathward_mulligan_tests tests/mulligan_tests.cpp)
    target_link_libraries(deathward_mulligan_tests PRIVATE deathward_core)
    add_test(NAME mulligan_family COMMAND deathward_mulligan_tests)
    add_executable(deathward_spider_tests tests/spider_tests.cpp)
    target_link_libraries(deathward_spider_tests PRIVATE deathward_core)
    add_test(NAME spider_family COMMAND deathward_spider_tests)
    add_executable(deathward_danny_tests tests/danny_tests.cpp)
    target_link_libraries(deathward_danny_tests PRIVATE deathward_core)
    add_test(NAME danny_family COMMAND deathward_danny_tests)
    add_executable(deathward_hardy_tests tests/hardy_tests.cpp)
    target_link_libraries(deathward_hardy_tests PRIVATE deathward_core)
    add_test(NAME hardy_family COMMAND deathward_hardy_tests)
    add_executable(deathward_rock_spider_tests tests/rock_spider_tests.cpp)
    target_link_libraries(deathward_rock_spider_tests PRIVATE deathward_core)
    add_test(NAME rock_spider_family COMMAND deathward_rock_spider_tests)
    add_executable(deathward_spider_variant_tests tests/spider_variant_tests.cpp)
    target_link_libraries(deathward_spider_variant_tests PRIVATE deathward_core)
    add_test(NAME spider_variants COMMAND deathward_spider_variant_tests)
    add_executable(deathward_long_legs_tests tests/long_legs_tests.cpp)
    target_link_libraries(deathward_long_legs_tests PRIVATE deathward_core)
    add_test(NAME long_legs_and_sack COMMAND deathward_long_legs_tests)
    add_executable(deathward_maw_family_tests tests/maw_family_tests.cpp)
    target_link_libraries(deathward_maw_family_tests PRIVATE deathward_core)
    add_test(NAME maw_family COMMAND deathward_maw_family_tests)
    add_executable(deathward_host_tests tests/host_tests.cpp)
    target_link_libraries(deathward_host_tests PRIVATE deathward_core)
    add_test(NAME hosts COMMAND deathward_host_tests)
    add_executable(deathward_hard_host_tests tests/hard_host_tests.cpp)
    target_link_libraries(deathward_hard_host_tests PRIVATE deathward_core)
    add_test(NAME hard_host COMMAND deathward_hard_host_tests)
    add_executable(deathward_mushroom_tests tests/mushroom_tests.cpp)
    target_link_libraries(deathward_mushroom_tests PRIVATE deathward_core)
    add_test(NAME mushroom COMMAND deathward_mushroom_tests)
    add_executable(deathward_trite_tests tests/trite_tests.cpp)
    target_link_libraries(deathward_trite_tests PRIVATE deathward_core)
    add_test(NAME trite COMMAND deathward_trite_tests)
    add_executable(deathward_eggy_tests tests/eggy_tests.cpp)
    target_link_libraries(deathward_eggy_tests PRIVATE deathward_core)
    add_test(NAME eggy COMMAND deathward_eggy_tests)
    add_executable(deathward_tainted_hopper_tests tests/tainted_hopper_tests.cpp)
    target_link_libraries(deathward_tainted_hopper_tests PRIVATE deathward_core)
    add_test(NAME tainted_hopper COMMAND deathward_tainted_hopper_tests)
    add_executable(deathward_adaptive_armor_tests tests/adaptive_armor_tests.cpp)
    target_link_libraries(deathward_adaptive_armor_tests PRIVATE deathward_core)
    add_test(NAME adaptive_armor COMMAND deathward_adaptive_armor_tests)
    add_executable(deathward_leaper_tests tests/leaper_tests.cpp)
    target_link_libraries(deathward_leaper_tests PRIVATE deathward_core)
    add_test(NAME leapers COMMAND deathward_leaper_tests)
    add_executable(deathward_boil_tests tests/boil_tests.cpp)
    target_link_libraries(deathward_boil_tests PRIVATE deathward_core)
    add_test(NAME boil_family COMMAND deathward_boil_tests)
    add_executable(deathward_mullighoul_tests tests/mullighoul_tests.cpp)
    target_link_libraries(deathward_mullighoul_tests PRIVATE deathward_core)
    add_test(NAME willo_and_mullighoul COMMAND deathward_mullighoul_tests)
    add_executable(deathward_prey_tests tests/prey_tests.cpp)
    target_link_libraries(deathward_prey_tests PRIVATE deathward_core)
    add_test(NAME prey_and_small_leech COMMAND deathward_prey_tests)
    add_executable(deathward_segmented_boss_tests tests/segmented_boss_tests.cpp)
    target_link_libraries(deathward_segmented_boss_tests PRIVATE deathward_core raylib)
    add_test(NAME segmented_bosses COMMAND deathward_segmented_boss_tests)
    add_executable(deathward_shell_tests tests/shell_tests.cpp)
    target_link_libraries(deathward_shell_tests PRIVATE deathward_core)
    add_test(NAME shell_boss COMMAND deathward_shell_tests)
    add_executable(deathward_theme_tests tests/theme_tests.cpp)
    target_link_libraries(deathward_theme_tests PRIVATE deathward_core)
    add_test(NAME mission_themes COMMAND deathward_theme_tests)
    add_executable(deathward_hub_tests tests/hub_tests.cpp)
    target_link_libraries(deathward_hub_tests PRIVATE deathward_core)
    target_compile_definitions(deathward_hub_tests PRIVATE DEATHWARD_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
    add_test(NAME imported_town_navigation COMMAND deathward_hub_tests)
    add_executable(deathward_tests tests/tests.cpp)
    target_link_libraries(deathward_tests PRIVATE deathward_core)
    add_test(NAME core_contracts COMMAND deathward_tests)
    add_executable(deathward_enemy_tests tests/enemy_tests.cpp)
    target_link_libraries(deathward_enemy_tests PRIVATE deathward_core)
    add_test(NAME enemy_behaviors COMMAND deathward_enemy_tests)
    add_executable(deathward_dungeon_tests tests/dungeon_tests.cpp)
    target_link_libraries(deathward_dungeon_tests PRIVATE deathward_core)
    add_test(NAME generated_dungeons COMMAND deathward_dungeon_tests)
    add_executable(deathward_room_graph_tests tests/room_graph_tests.cpp)
    target_link_libraries(deathward_room_graph_tests PRIVATE deathward_core)
    add_test(NAME generated_room_graphs COMMAND deathward_room_graph_tests)
    # Run explicitly when a graphics display is available; keep CTest headless.
    add_executable(deathward_occlusion_tests tests/occlusion_tests.cpp src/render/PostProcess.cpp src/render/PlayerModel.cpp src/render/AnimalModels.cpp src/render/TownScene.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp src/render/Renderer.cpp src/core/Game.cpp src/core/GameQuest.cpp)
    target_link_libraries(deathward_occlusion_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_occlusion_tests)
    add_executable(deathward_post_process_tests tests/post_process_tests.cpp src/render/PostProcess.cpp)
    target_include_directories(deathward_post_process_tests PRIVATE src)
    target_link_libraries(deathward_post_process_tests PRIVATE raylib)
    add_executable(deathward_editor_tests tests/editor_tests.cpp src/render/AnimalModels.cpp src/render/PostProcess.cpp src/editor/TownEditor.cpp src/editor/TownEditorAnimals.cpp src/editor/TownEditorNavigation.cpp src/render/TownScene.cpp)
    target_link_libraries(deathward_editor_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_editor_tests)
    add_executable(deathward_input_tests tests/input_tests.cpp src/render/PostProcess.cpp src/core/Game.cpp src/core/GameQuest.cpp src/render/Renderer.cpp src/render/PlayerModel.cpp src/render/AnimalModels.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp src/render/TownScene.cpp)
    target_link_libraries(deathward_input_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_input_tests)
    add_executable(deathward_player_model_tests tests/player_model_tests.cpp src/render/PlayerModel.cpp)
    target_link_libraries(deathward_player_model_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_player_model_tests)
    add_executable(deathward_town_assets_tests tests/town_assets_tests.cpp src/render/TownScene.cpp)
    target_link_libraries(deathward_town_assets_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_town_assets_tests)
    add_executable(deathward_mission_lighting_tests tests/mission_lighting_tests.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp)
    target_link_libraries(deathward_mission_lighting_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_mission_lighting_tests)
    add_executable(deathward_western_assets_tests tests/western_assets_tests.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp)
    target_link_libraries(deathward_western_assets_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_western_assets_tests)
endif()
