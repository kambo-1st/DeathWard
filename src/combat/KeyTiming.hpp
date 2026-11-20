#pragma once
#include "combat/RedHeartTiming.hpp"
namespace dw {
// Pinned 005.031_Key / 005.032_Golden Key / 005.033_KeyRing:
// Appear33, Drop25, Collect12.
// Same metadata and ordinary appearance gate as red hearts; shared active-room
// 30 Hz state machine. This does not certify native physical contact or pushing.
using KeyTiming = RedHeartTiming;
} // namespace dw
