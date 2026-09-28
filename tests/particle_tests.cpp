#include "world/Particles.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
void check(bool ok, const char *message) { if (!ok) throw std::runtime_error(message); }
int main() {
    try {
        ParticleLibrary library;
        library.load(std::filesystem::path(DEATHWARD_ASSET_DIR) / "particles");
        check(library.emitters.size() == 3, "Flame, ember and smoke emitters load");
        const auto &flame = library.emitters.front();
        check(flame.kind == ParticleKind::Mesh && flame.rate == 8, "Original Small_03 mesh emission rate");
        check(std::abs(ParticleLibrary::curve(flame.sizes,.5f) - 3.75f) < .0001f,
              "Unity Hermite size curve and multiplier preserved");
        for (const auto &emitter : library.emitters) {
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
        std::cout << "PASS imported particle curves, prewarm, deterministic clocks and bounded emission\n";
    } catch (const std::exception &e) { std::cerr << e.what() << '\n'; return 1; }
}
