#include "combat/PlayerAttributes.hpp"
#include <iostream>
#include <stdexcept>
#include <type_traits>

namespace {
void check(bool ok, const char *message) {
    if (!ok) throw std::runtime_error(message);
}
void near(float actual, float expected, const char *message) {
    check(std::abs(actual - expected) < .00001f, message);
}
template<class F> void rejects(F action) {
    bool rejected = false;
    try { action(); } catch (const std::invalid_argument &) { rejected = true; }
    check(rejected, "invalid calibration/input must be rejected rather than silently clamped");
}
}

int main() {
    try {
        using namespace dw;
        static_assert(!std::is_default_constructible_v<AttributeSpace>);
        SourcePlayerAttributes base;
        check(base.health.red == 6 && base.health.maxRed == 6 && base.health.soul == 0,
              "ordinary baseline contains three filled red hearts in typed half-heart units");
        near(base.speed, 1, "baseline Speed"); near(base.shotSpeed, 1, "baseline Shot Speed");
        near(base.tearsPerSecond, 2.7272727f, "Repentance Tears is a rate, not a HUD band or delay");
        near(base.damage, 3.5f, "baseline source Damage"); near(base.rangeTiles, 6.5f, "baseline tile Range");
        near(base.luck, 0, "baseline Luck");

        // Synthetic calibration fixtures, not an accepted DeathWard calibration.
        const AttributeSpace space(.05f, 40, 60, 30);
        near(space.worldRange(base), 13, "tile distance uses the same spatial scale as coordinates");
        near(space.worldDistance(260), 13, "source coordinate conversion agrees with tile conversion");
        near(space.worldVelocity(2, AttributeActorClock::Player), 6, "player velocity uses its explicit clock");
        near(space.worldVelocity(2, AttributeActorClock::Tear), 3, "tear velocity uses its explicit clock");
        near(space.worldVelocity(-2, AttributeActorClock::Tear), -3, "signed velocity is preserved");

        const float interval = nominalFireIntervalSeconds(base);
        near(interval, .36666667f, "nominal interval is derived from rate without a scheduler port");
        auto fasterShot = base; fasterShot.shotSpeed *= 2;
        near(space.worldRange(fasterShot), 13, "Shot Speed cannot change configured reach");
        near(nominalFireIntervalSeconds(fasterShot), interval, "Shot Speed cannot change firing cadence");
        near(nominalStraightFlightSeconds(base, space, 5), 2.6f, "slower flight can reach full configured distance");
        near(nominalStraightFlightSeconds(fasterShot, space, 10), 1.3f, "faster travel changes duration, not reach or cadence");

        auto rapid = base; rapid.tearsPerSecond *= 2;
        near(nominalFireIntervalSeconds(rapid), interval / 2, "higher Tears means faster firing");
        near(space.worldRange(rapid), 13, "Tears cannot change Range");
        near(rapid.shotSpeed, base.shotSpeed, "Tears cannot change Shot Speed");
        auto longRange = base; longRange.rangeTiles *= 2;
        near(space.worldRange(longRange), 26, "Range upgrades are not capped at half a review room");
        near(nominalFireIntervalSeconds(longRange), interval, "Range cannot change Tears");

        auto modified = base; modified.speed = 1.5f; modified.damage = 7; modified.luck = -2;
        modified.health.addSoul(2);
        near(space.worldRange(modified), 13, "movement, damage, Luck and health do not rewrite projectile reach");
        near(nominalFireIntervalSeconds(modified), interval, "other attributes do not rewrite firing cadence");
        check(base.health.soul == 0 && modified.health.soul == 2, "typed health snapshots remain independent");

        auto stopped = base; stopped.tearsPerSecond = 0;
        check(std::isinf(nominalFireIntervalSeconds(stopped)), "zero Tears disables periodic firing");
        for(float bad : {0.f, -1.f, std::numeric_limits<float>::infinity(),
                         std::numeric_limits<float>::quiet_NaN()}) {
            rejects([&] { AttributeSpace invalid(bad, 40, 60, 30); });
            rejects([&] { AttributeSpace invalid(.05f, bad, 60, 30); });
            rejects([&] { AttributeSpace invalid(.05f, 40, bad, 30); });
            rejects([&] { AttributeSpace invalid(.05f, 40, 60, bad); });
            rejects([&] { nominalStraightFlightSeconds(base, space, bad); });
        }
        auto invalid = base; invalid.rangeTiles = -1;
        rejects([&] { space.worldRange(invalid); });
        invalid = base; invalid.tearsPerSecond = -1;
        rejects([&] { nominalFireIntervalSeconds(invalid); });
        std::cout << "PASS canonical seven attributes, typed health, independent rate/range/flight, explicit spatial/clock conversions and invalid-input handling; no gameplay wiring\n";
        return 0;
    } catch (const std::exception &e) { std::cerr << e.what() << '\n'; return 1; }
}
