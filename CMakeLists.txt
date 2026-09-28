cmake_minimum_required(VERSION 3.20)
project(DeathWard VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(DEATHWARD_SANITIZERS "Enable address and undefined behavior sanitizers" OFF)
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE)
set(SUPPORT_MODULE_RAUDIO OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
FetchContent_Declare(raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
    URL_HASH SHA256=aea98ecf5bc5c5e0b789a76de0083a21a70457050ea4cc2aec7566935f5e258e
)
FetchContent_MakeAvailable(raylib)

add_library(deathward_core
    src/world/TownDocument.cpp
    src/world/TownNavigation.cpp
    src/world/HubWorld.cpp
    src/world/Campaign.cpp
    src/world/Dungeon.cpp
    src/world/CanyonTerrain.cpp
    src/world/RoomGraph.cpp
    src/combat/Simulation.cpp
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

add_executable(deathward src/main.cpp src/render/PostProcess.cpp src/editor/TownEditor.cpp src/render/Renderer.cpp src/render/PlayerModel.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp src/render/TownScene.cpp src/core/Game.cpp)
target_link_libraries(deathward PRIVATE deathward_core raylib)
deathward_assets(deathward)
if(NOT MSVC)
    target_compile_options(deathward PRIVATE -Wall -Wextra -Wpedantic)
endif()
include(CTest)
if(BUILD_TESTING)
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
    add_executable(deathward_occlusion_tests tests/occlusion_tests.cpp src/render/PostProcess.cpp src/render/PlayerModel.cpp src/render/TownScene.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp src/render/Renderer.cpp src/core/Game.cpp)
    target_link_libraries(deathward_occlusion_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_occlusion_tests)
    add_executable(deathward_post_process_tests tests/post_process_tests.cpp src/render/PostProcess.cpp)
    target_include_directories(deathward_post_process_tests PRIVATE src)
    target_link_libraries(deathward_post_process_tests PRIVATE raylib)
    add_executable(deathward_editor_tests tests/editor_tests.cpp src/render/PostProcess.cpp src/editor/TownEditor.cpp src/render/TownScene.cpp)
    target_link_libraries(deathward_editor_tests PRIVATE deathward_core raylib)
    deathward_assets(deathward_editor_tests)
    add_executable(deathward_input_tests tests/input_tests.cpp src/render/PostProcess.cpp src/core/Game.cpp src/render/Renderer.cpp src/render/PlayerModel.cpp src/render/WesternScene.cpp src/render/CanyonScene.cpp src/render/TownScene.cpp)
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
