#pragma once
#include "core/Types.hpp"
#include <span>

namespace dw {
enum class AudioCueKind {
    Shot,
    StoneHit,
    FleshHit,
    Hurt,
    Dodge,
    EnemyDeath,
    PlayerDeath,
    Warning,
    Explosion,
    Pickup,
    RoomClear,
    Door,
    UI,
    Test,
    StepGravel,
    StepWood,
    StepMine,
    EnemyShot,
    MonsterAttack,
    Count
};
inline int audioPriority(AudioCueKind kind) {
    switch (kind) {
    case AudioCueKind::PlayerDeath:
        return 5;
    case AudioCueKind::Shot:
    case AudioCueKind::Hurt:
    case AudioCueKind::Warning:
    case AudioCueKind::Test:
        return 4;
    case AudioCueKind::Pickup:
    case AudioCueKind::RoomClear:
    case AudioCueKind::Dodge:
    case AudioCueKind::UI:
        return 3;
    case AudioCueKind::EnemyDeath:
    case AudioCueKind::Explosion:
    case AudioCueKind::Door:
    case AudioCueKind::EnemyShot:
    case AudioCueKind::MonsterAttack:
        return 2;
    default:
        return 1;
    }
}
struct AudioCue {
    AudioCueKind kind;
    Vector3 position{};
};
// Presentation only: bounded even when there is no audio device/consumer.
class AudioCueQueue {
  public:
    static constexpr size_t Capacity = 128;
    void push(AudioCueKind kind, Vector3 position = {}) {
        if (cues_.size() < Capacity) {
            cues_.push_back({kind, position});
            return;
        }
        auto quietest = std::min_element(cues_.begin(), cues_.end(), [](auto a, auto b) {
            return audioPriority(a.kind) < audioPriority(b.kind);
        });
        if (audioPriority(kind) > audioPriority(quietest->kind))
            *quietest = {kind, position};
    }
    std::span<const AudioCue> cues() const {
        return cues_;
    }
    void clear() {
        cues_.clear();
    }

  private:
    std::vector<AudioCue> cues_;
};
struct AudioSettings {
    float master = .65f, effects = .75f, ambience = .45f;
    bool muted = false;
    bool operator==(const AudioSettings &) const = default;
};
enum class AudioStatus { Disabled, Unavailable, Ready };
enum class AudioEnvironment { Town, Frontier, Canyon, Mine, Count };
} // namespace dw
