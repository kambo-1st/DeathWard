#include "world/TownNavigation.hpp"
#include "world/HubWorld.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
int main(int argc, char **argv) {
    if (argc != 2) { std::cerr << "Usage: deathward_bake_navigation <town directory>\n"; return 1; }
    Model model{};
    try {
        const std::filesystem::path directory = argv[1];
        TownDocument document;
        std::string error;
        if (!document.load(directory / "town.scene", error)) throw std::runtime_error(error);
        TownNavigation navigation;
        navigation.load(directory / "town.nav");
        SetTraceLogLevel(LOG_ERROR);
        SetConfigFlags(FLAG_WINDOW_HIDDEN);
        InitWindow(32, 32, "Bake town navigation");
        if (!IsWindowReady()) throw std::runtime_error("A graphics display is required to load the town model.");
        model = LoadModel((directory / "town.glb").string().c_str());
        navigation.bake(document, model);
        saveTownNavigation(directory, navigation);
        HubWorld verify;
        if (!verify.load(directory / "town.nav")) throw std::runtime_error(verify.error);
        std::cout << "PASS baked " << directory.string() << ": " << verify.walkableCells() << " connected cells\n";
        UnloadModel(model);
        CloseWindow();
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        if (model.meshCount) UnloadModel(model);
        if (IsWindowReady()) CloseWindow();
        return 1;
    }
}
