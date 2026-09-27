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
    src/world/Campaign.cpp
    src/combat/Simulation.cpp
    src/combat/Navigation.cpp
    src/items/Items.cpp
)
target_include_directories(deathward_core PUBLIC src ${raylib_SOURCE_DIR}/src)
if(MSVC)
    target_compile_options(deathward_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(deathward_core PRIVATE -Wall -Wextra -Wpedantic)
endif()
if(DEATHWARD_SANITIZERS AND NOT MSVC)
    target_compile_options(deathward_core PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(deathward_core PUBLIC -fsanitize=address,undefined)
endif()

add_executable(deathward src/main.cpp src/render/Renderer.cpp src/core/Game.cpp)
target_link_libraries(deathward PRIVATE deathward_core raylib)
if(NOT MSVC)
    target_compile_options(deathward PRIVATE -Wall -Wextra -Wpedantic)
endif()
include(CTest)
if(BUILD_TESTING)
    add_executable(deathward_tests tests/tests.cpp)
    target_link_libraries(deathward_tests PRIVATE deathward_core)
    add_test(NAME core_contracts COMMAND deathward_tests)
    # Run explicitly when a graphics display is available; keep CTest headless.
    add_executable(deathward_input_tests tests/input_tests.cpp src/core/Game.cpp src/render/Renderer.cpp)
    target_link_libraries(deathward_input_tests PRIVATE deathward_core raylib)
endif()
