#pragma once
#include "combat/Simulation.hpp"
#include "render/ArtWardrobe.hpp"
#include <filesystem>

namespace dw {
enum class PlayerAnimation {
    Idle,
    Walk,
    Run,
    Fire,
    DodgeSlide,
    DodgeForward,
    DodgeStanding,
    Death,
    DeathRifle,
    Count
};
inline constexpr float PlayerDeathSeconds = 2.0f;

// Owns the bandit's GPU resources and a local-space animation mixer. Gameplay
// remains authoritative for position, facing, hit volumes and action timing.
class PlayerModel {
  public:
    PlayerModel() = default;
    bool artPoc = false;
    ~PlayerModel();
    PlayerModel(const PlayerModel &) = delete;
    PlayerModel &operator=(const PlayerModel &) = delete;
    bool load(const std::filesystem::path &path = assetPath());
    void unload();
    void update(const Simulation &run, float deathTime = 0);
    void draw(const Simulation &run) const;
    Vector3 muzzlePosition(const Player &player) const;
    void update(const Player &player, double time, const void *context, bool dead = false,
                float deathTime = 0);
    void draw(const Player &player, bool dead = false, Shader shader = {}, Texture2D shadowMap = {}) const;
    bool loaded() const {
        return model_.meshCount > 0;
    }
    PlayerAnimation animation() const {
        return current_;
    }
    float animationTime() const {
        return phase_;
    }
    float firingBlend() const {
        return firingBlend_;
    }
    const Model &model() const {
        return model_;
    }
    const std::vector<Transform> &pose() const {
        return worldPose_;
    }
    static std::filesystem::path assetPath();
    static const char *animationName(PlayerAnimation animation);
    float duration(PlayerAnimation animation) const;

  private:
    struct Clip {
        std::vector<std::vector<Transform>> frames;
        float duration = 0;
    };
    Model model_{};
    mutable ArtWardrobe wardrobe_;
    std::array<Clip, size_t(PlayerAnimation::Count)> clips_;
    std::vector<Transform> pose_, worldPose_, blendFrom_;
    std::vector<bool> upperBody_;
    const void *lastRun_ = nullptr;
    double lastTime_ = -1;
    PlayerAnimation current_ = PlayerAnimation::Idle;
    float phase_ = 0, transition_ = 1, firePhase_ = 0, firingBlend_ = 0;
    float scale_ = 1, floorOffset_ = 0, yaw_ = 0;
    int hand_ = -1, finger_ = -1;
    bool attempted_ = false;
    Transform sample(PlayerAnimation animation, float seconds, int bone, bool loop) const;
    Vector3 worldPoint(Vector3 point, const Player &player) const;
};
} // namespace dw
