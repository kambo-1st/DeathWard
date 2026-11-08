#pragma once
#include "combat/PlayerAttributes.hpp"

namespace dw {
// Human-accepted ordinary shooting calibration. The tile conversion and launch
// adaptation remain explicit; complete live native equivalence is unverified.
inline const ShootingCalibration AcceptedPlayerShooting{AttributeSpace(11.f/260.f,40,60,30),8};
}
