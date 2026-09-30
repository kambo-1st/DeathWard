#include "world/TownCharacters.hpp"
#include "world/TownNavigation.hpp"
#include "raymath.h"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok, const char *message) { if (!ok) throw std::runtime_error(message); }
TownDocument fixture() {
    TownDocument d;
    d.assets = {{"ground", "Ground", 0, 1, 0, {{-10, 0, -10}, {10, 0, 10}}}};
    d.instances = {{0, MatrixIdentity(), "ground"}};
    TownCharacter c;
    c.id = "test-walker"; c.position = {-4, 0, 0}; c.dwell = .5f;
    c.stops = {{4, 0, 0}, {4, 0, -6}, {-4, 0, -6}};
    d.characters.push_back(c);
    return d;
}
int main() {
    try {
        TownNavigation nav;
        nav.width = nav.depth = 50; nav.cell = .4f; nav.minX = nav.minZ = -10;
        nav.spawn = {-4, 0, 0}; nav.mission = {4, 0, 0}; nav.heights.assign(2500, 0);
        for (int z = 15; z < 35; ++z) nav.heights[size_t(z) * 50 + 25] = NAN;
        HubWorld ground; ground.setNavigation(nav);
        auto document = fixture();
        TownCharacters a, b, c;
        a.reset(document, ground); b.reset(document, ground); c.reset(document, ground);
        const auto start = a.residents()[0].position;
        a.update(.1f, ground);
        check(distance(start, a.residents()[0].position) == 0, "Initial dwell holds the authored starting point");
        a.reset(document, ground);
        for (int i = 0; i < 60 * 90; ++i) {
            const auto previous = a.residents()[0].position;
            a.update(1.f/60, ground);
            const auto &state = a.residents()[0];
            check(ground.walkable(state.position) && ground.canTraverse(previous, state.position), "NPC never crosses the wall");
            check(distance(previous, state.position) <= document.characters[0].speed * Tick + .001f, "Speed bounds actual travel");
        }
        for (int i = 0; i < 30 * 90; ++i) b.update(1.f/30, ground);
        for (int i = 0; i < 120 * 90; ++i) c.update(1.f/120, ground);
        check(a.residents()[0].visits >= 4, "Loop returns home and continues across multiple stops");
        check(distance(a.residents()[0].position,b.residents()[0].position) < .00001f &&
              distance(a.residents()[0].position,c.residents()[0].position) < .00001f, "30/60/120 FPS produces matching routes");
        auto position = a.residents()[0].position; auto time = a.time(); a.update(0, ground);
        check(distance(position,a.residents()[0].position)==0 && time==a.time(), "Zero update freezes pose and position");
        document.characters[0].loop = false; document.characters[0].stops = {{-2,0,0}};
        a.reset(document,ground);
        for (int i=0;i<900;++i) a.update(Tick,ground);
        check(a.residents()[0].visits >= 4, "Back-and-forth repeatedly visits both endpoints");
        ground.setMovingSolids({{{-2, .8f, 0}, {1,0,0}, {1,.8f,1}}});
        a.reset(document,ground);
        for (int i=0;i<150;++i) a.update(Tick,ground);
        check(a.residents()[0].blocked && distance(a.residents()[0].position,document.characters[0].position)<.01f,
              "A blocked destination waits rather than teleporting");
        ground.setMovingSolids({});
        for (int i=0;i<300;++i) a.update(Tick,ground);
        check(a.residents()[0].visits>0, "Route resumes after a moving obstacle clears");
        auto path=std::filesystem::temp_directory_path()/"deathward-character-roundtrip.scene";
        document.write(path); TownDocument restored; std::string error;
        check(restored.load(path,error) && restored.characters.size()==1 && restored.characters[0].stops.size()==1 &&
              !restored.characters[0].loop, "Character route and settings survive scene round trip");
        std::filesystem::remove(path);
        document.characters[0].model = "bandit";
        document.write(path);
        check(restored.load(path,error) && restored.characters[0].model == "bandit",
              "Bandit residents retain their model and routes through editor scene saves");
        std::filesystem::remove(path);
        document.characters[0].model = "unknown";
        bool badModel = false;
        try { document.validate(); } catch (...) { badModel = true; }
        check(badModel, "Unknown resident models are rejected");
        document.characters[0].model = "cowgirl";
        document.characters[0].speed=NAN; bool rejected=false;
        try {document.validate();} catch (...) {rejected=true;}
        check(rejected,"Invalid character settings rejected");
        const auto town=std::filesystem::path(DEATHWARD_ASSET_DIR)/"town";
        check(restored.load(town/"town.scene",error) && ground.load(town/"town.nav"), "Demo town loads");
        check(restored.characters.size()==1 && restored.characters[0].stops.size()==3,"Town contains the four-stop cowgirl demo");
        a.reset(restored,ground);
        for (int i=0;i<7200;++i) a.update(Tick,ground);
        std::cout << "Demo visits=" << a.residents()[0].visits << " blocked=" << a.residents()[0].blocked << " at=" << a.residents()[0].position.x << "," << a.residents()[0].position.z << " target=" << a.residents()[0].destination << "\n";
        check(a.residents()[0].visits>=8 && !a.residents()[0].blocked,"Demo walks multiple complete town laps");
        std::cout<<"PASS character routes, obstacle navigation, pauses, deterministic timing, persistence and town demo\n";
    } catch (const std::exception &e) {std::cerr<<e.what()<<'\n';return 1;}
}
