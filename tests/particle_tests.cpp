#include "world/Particles.hpp"
#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok, const char *message) { if (!ok) throw std::runtime_error(message); }
int main() {
    try {
        ParticleLibrary library;
        library.load(std::filesystem::path(DEATHWARD_ASSET_DIR) / "particles");
        check(library.emitters.size() == 20, "Fire, combat and environment emitters load");
        const auto &flame = library.emitters.front();
        check(flame.kind == ParticleKind::Mesh && flame.rate == 8, "Original Small_03 mesh emission rate");
        check(std::abs(ParticleLibrary::curve(flame.sizes,.5f) - 3.75f) < .0001f,
              "Unity Hermite size curve and multiplier preserved");
        for (const auto &emitter : library.emitters) {
            if (emitter.burstMax) {
                check(ParticleLibrary::burst(emitter,-.1f,17,{1,0,0}).empty(), "Bursts never prewarm");
                const auto a=ParticleLibrary::burst(emitter,.025f,17,{1,0,0});
                const auto b=ParticleLibrary::burst(emitter,.025f,17,{1,0,0});
                check(!a.empty() && a.size()<=size_t(emitter.burstMax) && a.size()==b.size(),
                      "Burst population follows its bounded source count");
                for(size_t n=0;n<a.size();++n)
                    check(distance(a[n].position,b[n].position)==0 && a[n].size==b[n].size,
                          "Burst rendering and pause cannot consume random state");
                check(ParticleLibrary::burst(emitter,emitter.lifetime.y,17,{1,0,0}).empty(),
                      "Burst particles expire without looping");
                continue;
            }
            check(!ParticleLibrary::sample(emitter,0,17).empty(), "Prewarmed fires are visible immediately");
            for (double time : {0.,.001,1.,43.61,360000.}) {
                auto a = ParticleLibrary::sample(emitter,time,17), b = ParticleLibrary::sample(emitter,time,17);
                check(a.size() == b.size() && a.size() <= size_t(std::ceil(emitter.rate * emitter.lifetime.y) + 1),
                      "Stable sampling and bounded particle population over long sessions");
                for (size_t n = 0; n < a.size(); ++n) {
                    check(distance(a[n].position,b[n].position) == 0 && a[n].size == b[n].size &&
                          a[n].alpha == b[n].alpha && a[n].rotation == b[n].rotation,
                          "Rendering/pausing/revisiting at the same time cannot change particles");
                    check(std::isfinite(a[n].size) && a[n].size > 0 && a[n].alpha > 0 && a[n].alpha <= 1,
                          "Live particles have finite size and opacity");
                }
            }
            auto a = ParticleLibrary::sample(emitter,2,17), b = ParticleLibrary::sample(emitter,2.05,17);
            check(a.size()!=b.size() || distance(a[0].position,b[0].position)>0 || a[0].size!=b[0].size,
                  "Flame, ember and smoke evolve over time");
            auto c = ParticleLibrary::sample(emitter,2,18);
            check(a.size()!=c.size() || distance(a[0].position,c[0].position)>0,
                  "Different placements do not flicker in sync");
        }
        Simulation run(1866,1,{});
        run.arena=Arena{}; run.debugScenario=true; run.roomClear=false;
        run.moneyPickups.clear(); run.player.position={0,.85f,8};
        run.arena.walls.push_back({{-8,0,2},{8,4,3}});
        const auto rng=run.combatRng.state, rewards=run.rewardRng.state, encounter=run.encounterRng.state;
        Input fire; fire.fire=true; fire.aim={0,.85f,-5};
        run.step(fire);
        check(run.particleBursts.size()==1 && run.particleBursts[0].kind==ParticleEffect::PlayerMuzzle,
              "An actual player shot emits one muzzle burst");
        run.audioCues.clear();
        for(int n=0;n<20;++n)run.step({});
        check(std::any_of(run.particleBursts.begin(),run.particleBursts.end(),[](const auto &b){
                return b.kind==ParticleEffect::Wood;
            }), "Swept collision against a mine obstacle creates a wood impact without audio");
        check(run.impactMaterial({0,1,0},{0,1,0})==ParticleEffect::Dirt,"Ground impacts use dirt");
        run.arena.theme=MissionTheme::Canyon;
        check(run.impactMaterial({0,1,0},{1,0,0})==ParticleEffect::Stone,"Canyon impacts use rock");
        Passage gate; gate.gates[0]={{-1,0,-1},{1,3,1}};gate.sealed[0]=true;
        run.arena.passages.push_back(gate);
        check(run.impactMaterial({0,1,0},{1,0,0})==ParticleEffect::Metal,"Closed gates spark");
        run.arena.passages.clear();
        run.particleBursts.clear();
        check(run.placeDynamite(),"Can place test charge");
        run.godMode=true;
        for(int n=0;n<123;++n)run.step({});
        check(std::count_if(run.particleBursts.begin(),run.particleBursts.end(),[](const auto &b){
                return b.kind==ParticleEffect::Explosion;
            })==1 && run.stats.explosions==1, "Dynamite emits one explosion after the fuse");
        auto age=run.particleBursts.back().age;
        run.shopOpen=true;run.step({});
        check(run.particleBursts.back().age==age,"Modal pause freezes burst aging");
        run.shopOpen=false;
        check(run.combatRng.state==rng && run.rewardRng.state==rewards && run.encounterRng.state==encounter,
              "Cosmetic effects never perturb combat, loot or encounter random streams");
        for(int n=0;n<1000;++n)run.particleEffect(ParticleEffect::Metal,{0,1,0});
        check(run.particleBursts.size()==128,"Chain reactions have a bounded cosmetic queue");
        for(int n=0;n<190;++n)run.step({});
        check(run.particleBursts.empty(),"Expired effects release the queue");
        run.particleEffect(ParticleEffect::Explosion,{0,1,0});run.enterRoom(0);
        check(run.particleBursts.empty(),"Room changes cannot leak effects into another encounter");
        std::cout << "PASS imported curves, burst timing, collision materials, dynamite triggers, pause, isolated RNG and budgets\n";
    } catch (const std::exception &e) { std::cerr << e.what() << '\n'; return 1; }
}
