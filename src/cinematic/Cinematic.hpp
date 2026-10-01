#pragma once
#include "world/ObjectAnimation.hpp"

namespace dw {
enum class CameraBlend { Smooth, Linear, Cut };
struct CameraKey {
    float time = 0;
    Vector3 position{12, 12, 12}, target{};
    float fov = 45;
    std::string anchor; // Empty = world; otherwise a TownMotionGroup id.
    CameraBlend blend = CameraBlend::Smooth; // Transition to the next key.
};
struct WeatherKey { float time = 0, amount = 0; };
struct TrainCue {
    float time = 0, speed = 6, acceleration = 2;
    std::string path = "*";
};
struct SoundCue {
    float time = 0;
    std::string file = "warning.wav"; // Relative to assets/audio.
    float volume = 1;
    float duration = 0; // Zero plays the whole file; positive durations loop/trim the clip.
};
struct Cinematic {
    std::string title = "Untitled sequence";
    float duration = 20;
    std::vector<CameraKey> cameras;
    std::vector<WeatherKey> weather;
    std::vector<TrainCue> trains;
    std::vector<SoundCue> sounds;
    void sort();
    void validate(const TownDocument *scene = nullptr) const;
    bool load(const std::filesystem::path &file, std::string &error);
    bool save(const std::filesystem::path &file, std::string &error) const;
    float storm(float time) const;
    static Cinematic demo(const TownDocument &scene, Camera3D view);
};

// A private simulation driven by the sequence clock. Seeking is silent and
// deterministic; only forward playback delivers sound cues to the audio layer.
class CinematicPlayer {
  public:
    void reset(const TownDocument &scene, const Cinematic &sequence,
               ObjectAnimationSystem::Ground ground = {});
    void seek(float seconds);
    void play();
    void pause() { playing_ = false; }
    void advance(float seconds);
    bool playing() const { return playing_; }
    float time() const { return float(time_); }
    Camera3D camera() const;
    float storm() const { return sequence_.storm(float(time_)); }
    const ObjectAnimationSystem &animation() const { return animation_; }
    std::optional<Matrix> anchor(const std::string &id) const;
    std::vector<SoundCue> takeSounds();

  private:
    TownDocument scene_;
    Cinematic sequence_;
    ObjectAnimationSystem animation_;
    ObjectAnimationSystem::Ground ground_;
    std::vector<SoundCue> pending_;
    double time_ = 0, simulated_ = 0;
    size_t nextTrain_ = 0;
    bool playing_ = false, started_ = false;
    void simulate(double seconds);
    void trainCues(double through);
};
} // namespace dw
