#pragma once
#include "combat/PlayerHealth.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace dw {

// Ordinary Isaac's documented Repentance baseline. This is the attribute
// contract, not certification of the complete native cache/actor implementation.
// Health uses the existing typed half-heart model. Other values retain their
// source meanings, independently of rendering, room size and simulation clocks.
// Runtime health remains in its existing authority; the six scalar attributes
// can be stored without creating a second mutable health state.
struct SourcePlayerStats {
    float speed = 1;
    float tearsPerSecond = 30.f / 11.f;
    float damage = 3.5f;
    float rangeTiles = 6.5f;
    float shotSpeed = 1;
    float luck = 0;
};
struct SourcePlayerAttributes : SourcePlayerStats {
    SourcePlayerHealth health;
};

namespace attribute_detail {
inline float positive(float value) {
    if (!std::isfinite(value) || value <= 0)
        throw std::invalid_argument("Attribute conversion requires a finite positive value");
    return value;
}
inline float nonnegative(float value) {
    if (!std::isfinite(value) || value < 0)
        throw std::invalid_argument("Attribute conversion requires a finite nonnegative value");
    return value;
}
} // namespace attribute_detail

// Explicit accepted-feel calibration for responsive walking. This is a
// proportional adaptation, not a port of native acceleration/cache/cap rules.
class WalkingPace {
public:
    explicit WalkingPace(float worldSpeedAtSpeedOne)
        : baseline_(attribute_detail::positive(worldSpeedAtSpeedOne)) {}
    float worldSpeed(const SourcePlayerStats &attributes) const {
        return baseline_ * attribute_detail::nonnegative(attributes.speed);
    }
private:
    float baseline_;
};

// Nominal rate arithmetic only: native firing-counter gates, fractional carry
// and item exceptions remain separate work. Zero rate means no periodic shot.
inline float nominalFireIntervalSeconds(const SourcePlayerStats &attributes) {
    const auto rate = attribute_detail::nonnegative(attributes.tearsPerSecond);
    return rate == 0 ? std::numeric_limits<float>::infinity() : 1.f / rate;
}

enum class AttributeActorClock { Player, Tear };

// One spatial conversion shared by positions, tile distances and velocities.
// There is deliberately no default calibration. Callers must supply and audit
// the spatial and scheduler assumptions before enabling a gameplay consumer.
class AttributeSpace {
public:
    AttributeSpace(float worldUnitsPerSourceCoordinate, float sourceCoordinatesPerTile,
                   float playerInvocationsPerSecond, float tearInvocationsPerSecond)
        : scale_(attribute_detail::positive(worldUnitsPerSourceCoordinate)),
          tile_(attribute_detail::positive(sourceCoordinatesPerTile)),
          playerClock_(attribute_detail::positive(playerInvocationsPerSecond)),
          tearClock_(attribute_detail::positive(tearInvocationsPerSecond)) {}

    float worldDistance(float sourceCoordinates) const {
        if (!std::isfinite(sourceCoordinates))
            throw std::invalid_argument("Source coordinate must be finite");
        return sourceCoordinates * scale_;
    }
    float worldRange(const SourcePlayerStats &attributes) const {
        return attribute_detail::nonnegative(attributes.rangeTiles) * tile_ * scale_;
    }
    // Input is an already resolved native velocity, not Speed or Shot Speed.
    // Their distinct native producer formulas are not replaced by this adapter.
    float worldVelocity(float sourceCoordinatesPerInvocation, AttributeActorClock clock) const {
        const float rate = clock == AttributeActorClock::Player ? playerClock_ : tearClock_;
        return worldDistance(sourceCoordinatesPerInvocation) * rate;
    }

private:
    float scale_, tile_, playerClock_, tearClock_;
};

struct ResolvedPlayerShooting {
    float intervalSeconds, launchSpeed, reach;
    bool enabled() const {
        return std::isfinite(intervalSeconds) && intervalSeconds > 0 && launchSpeed > 0 && reach > 0;
    }
};

// Explicit shooting calibration: tiles use the shared spatial boundary; the
// launch reference preserves the human-selected projectile feel. That launch
// adaptation is not a claim of native velocity/clock equivalence.
class ShootingCalibration {
public:
    ShootingCalibration(AttributeSpace space, float launchAtShotSpeedOne)
        : space_(space), launch_(attribute_detail::positive(launchAtShotSpeedOne)) {}
    ResolvedPlayerShooting resolve(const SourcePlayerStats &attributes) const {
        return {nominalFireIntervalSeconds(attributes),
                launch_ * attribute_detail::nonnegative(attributes.shotSpeed),
                space_.worldRange(attributes)};
    }
private:
    AttributeSpace space_;
    float launch_;
};

// Useful for straight-flight calibration. Source trajectory/flags/obstacles may
// require a richer consumer; this helper never changes Tears or configured Range.
inline float nominalStraightFlightSeconds(const SourcePlayerAttributes &attributes,
                                         const AttributeSpace &space, float worldLaunchSpeed) {
    return space.worldRange(attributes) / attribute_detail::positive(worldLaunchSpeed);
}

} // namespace dw
