cmake_minimum_required(VERSION 3.20)
project(DeathWard VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(DEATHWARD_SANITIZERS "Enable address and undefined behavior sanitizers" OFF)
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
    src/world/TownDocument.cpp
    src/world/ObjectAnimation.cpp
    src/world/TownNavigation.cpp
    src/world/HubWorld.cpp
    src/world/Animals.cpp
    src/world/Campaign.cpp
    src/world/Dungeon.cpp
    src/world/CanyonTerrain.cpp
    src/world/RoomGraph.cpp
    src/combat/Simulation.cpp
    src/combat/Loot.cpp
    src/combat/Shop.cpp
    src/combat/Dynamite.cpp
    src/combat/Enemies.cpp
    src/combat/Encounters.cpp
    src/combat/Monsters.cpp
    src/combat/Navigation.cpp
    src/items/Items.cpp
)
target_include_directories(deathward_core PUBLIC src)
target_include_directories(deathward_core SYSTEM PUBLIC ${raylib_SOURCE_DIR}/src)
if(MSVC)
    target_compile_options(deathward_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(deathward_core PRIVATE -Wall -Wextra -Wpedantic)
endif()
if(DEATHWARD_SANITIZERS AND NOT MSVC)
    target_compile_options(deathward_core PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(deathward_core PUBLIC -fsanitize=address,undefined)
endif()

function(deathward_assets target)
    if(EMSCRIPTEN)
        target_compile_definitions(${target} PRIVATE DEATHWARD_ASSET_DIR="/assets")
        return()
    endif()
    file(GLOB_RECURSE audio_assets CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/audio/*.wav" "${CMAKE_CURRENT_SOURCE_DIR}/assets/audio/*.ogg")
    set_property(TARGET ${target} APPEND PROPERTY LINK_DEPENDS ${audio_assets})
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets/audio" "$<TARGET_FILE_DIR:${target}>/assets/audio"
        VERBATIM)
    foreach(animal_file horse.glb hen.glb cow.glb cat.glb town.animals)
        set(animal_asset "${CMAKE_CURRENT_SOURCE_DIR}/assets/animals/${animal_file}")
        set_property(TARGET ${target} APPEND PROPERTY LINK_DEPENDS "${animal_asset}")
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${target}>/assets/animals"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${animal_asset}" "$<TARGET_FILE_DIR:${target}>/assets/animals/${animal_file}"
            VERBATIM)
    endforeach()
    set(bandit_asset "${CMAKE_CURRENT_SOURCE_DIR}/assets/bandit/bandit.glb")
    target_compile_definitions(${target} PRIVATE DEATHWARD_ASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets")
    set_property(TARGET ${target} APPEND PROPERTY LINK_DEPENDS "${bandit_asset}")
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${target}>/assets/bandit"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${bandit_asset}" "$<TARGET_FILE_DIR:${target}>/assets/bandit/bandit.glb"
        VERBATIM)
    foreach(western_file western.glb western.catalog)
        set(western_asset "${CMAKE_CURRENT_SOURCE_DIR}/assets/western/${western_file}")
        set_property(TARGET ${target} APPEND PROPERTY LINK_DEPENDS "${western_asset}")
        add_custom_command(TARGET ${target} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${target}>/assets/western"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different "${western_asset}" "$<TARGET_FILE_DIR:${target}>/assets/western/${western_file}"
            VERBATIM)
    endforeach()
    foreach(hub_pack town frontier)
        foreach(town_file town.glb town.scene town.nav town.labels)
            set(town_asset "${CMAKE_CURRENT_SOURCE_DIR}/assets/${hub_pack}/${town_file}")
            set_property(TARGET ${target} APPEND PROPERTY LINK_DEPENDS "${town_asset}")
            add_custom_command(TARGET ${target} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:${target}>/assets/${hub_pack}"
                COMMAND ${CMAKE_COMMAND} -E copy_if_different "${town_asset}" "$<TARGET_FILE_DIR:${target}>/assets/${hub_pack}/${town_file}"
                VERBATIM)
        endforeach()
    endforeach()
endfunction()

add_executable(deathward src/main.cpp src/audio/AudioSystem.cpp src/audio/MusicDirector.cpp src/render/PostProcess.cpp src/editor/TownEditor.cpp src/render/Renderer.cpp src/render/PlayerModel.cpp src/render/AnimalModels.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp src/render/TownScene.cpp src/core/Game.cpp)
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
        assets/bandit/bandit.glb assets/western/western.glb assets/western/western.catalog)
    foreach(animal_file horse.glb hen.glb cow.glb cat.glb town.animals)
        list(APPEND web_assets assets/animals/${animal_file})
    endforeach()
    foreach(hub town frontier)
        foreach(name town.glb town.scene town.nav town.labels)
            list(APPEND web_assets assets/${hub}/${name})
        endforeach()
    endforeach()
    file(GLOB_RECURSE web_audio CONFIGURE_DEPENDS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "assets/audio/*.wav" "assets/audio/*.ogg")
    list(APPEND web_assets ${web_audio})
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
if(BUILD_TESTING)
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
    add_executable(deathward_occlusion_tests tests/occlusion_tests.cpp src/render/PostProcess.cpp src/render/PlayerModel.cpp src/render/AnimalModels.cpp src/render/TownScene.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp src/render/Renderer.cpp src/core/Game.cpp)
    target_link_libraries(deathward_occlusion_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_occlusion_tests)
    add_executable(deathward_post_process_tests tests/post_process_tests.cpp src/render/PostProcess.cpp)
    target_include_directories(deathward_post_process_tests PRIVATE src)
    target_link_libraries(deathward_post_process_tests PRIVATE raylib)
    add_executable(deathward_editor_tests tests/editor_tests.cpp src/render/PostProcess.cpp src/editor/TownEditor.cpp src/render/TownScene.cpp)
    target_link_libraries(deathward_editor_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_editor_tests)
    add_executable(deathward_input_tests tests/input_tests.cpp src/render/PostProcess.cpp src/core/Game.cpp src/render/Renderer.cpp src/render/PlayerModel.cpp src/render/AnimalModels.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp src/render/TownScene.cpp)
    target_link_libraries(deathward_input_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_input_tests)
    add_executable(deathward_player_model_tests tests/player_model_tests.cpp src/render/PlayerModel.cpp)
    target_link_libraries(deathward_player_model_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_player_model_tests)
    add_executable(deathward_town_assets_tests tests/town_assets_tests.cpp src/render/TownScene.cpp)
    target_link_libraries(deathward_town_assets_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_town_assets_tests)
    add_executable(deathward_western_assets_tests tests/western_assets_tests.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp)
    target_link_libraries(deathward_western_assets_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_western_assets_tests)
endif()
