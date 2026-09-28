#pragma once
#include "audio/AudioState.hpp"
#include "audio/MusicDirector.hpp"
#include <filesystem>

namespace dw {
struct AudioFrame {
    Camera3D camera{};
    Vector3 player{};
    AudioEnvironment environment = AudioEnvironment::Town;
    MusicScene music = MusicScene::Town;
    uint64_t context = 0, room = 0;
    bool paused = false, footsteps = true;
    float dt = 0;
};
struct AudioSpatial {
    float gain = 0, pan = .5f;
};
AudioSpatial spatialAudio(Vector3 source, Vector3 listener, const Camera3D &camera);
AudioSettings loadAudioSettings(const std::filesystem::path &file);
bool saveAudioSettings(const std::filesystem::path &file, const AudioSettings &settings);

class AudioSystem {
  public:
    static constexpr size_t VoiceLimit = 32;
    AudioSystem() = default;
    ~AudioSystem();
    AudioSystem(const AudioSystem &) = delete;
    AudioSystem &operator=(const AudioSystem &) = delete;
    AudioStatus initialize(bool enabled, const std::filesystem::path &directory = assetDirectory());
    void update(const AudioFrame &frame, const AudioSettings &settings, std::span<const AudioCue> world,
                std::span<const AudioCue> ui = {});
    void unload();
    bool ready() const {
        return ready_;
    }
    size_t activeVoices() const;
    uint64_t played() const {
        return played_;
    }
    uint64_t suppressed() const {
        return suppressed_;
    }
    float ambienceLevel(AudioEnvironment env) const {
        return ambienceGain_[size_t(env)];
    }
    static std::filesystem::path assetDirectory();
    const MusicDirector &music() const {
        return music_;
    }

  private:
    struct Voice {
        Sound alias{};
        const Sound *source = nullptr;
        AudioCue cue{AudioCueKind::UI};
        float gain = 0;
        double started = 0;
        bool positional = true;
    };
    std::array<std::vector<Sound>, size_t(AudioCueKind::Count)> sounds_;
    std::array<Voice, VoiceLimit> voices_{};
    std::array<Music, size_t(AudioEnvironment::Count)> ambience_{};
    std::array<float, size_t(AudioEnvironment::Count)> ambienceGain_{};
    std::array<double, size_t(AudioCueKind::Count)> nextCue_{};
    MusicDirector music_;
    Random random_{0x415544494fULL};
    double time_ = 0;
    float stepDistance_ = 0;
    Vector3 lastPosition_{};
    uint64_t context_ = 0, room_ = 0, played_ = 0, suppressed_ = 0;
    bool ready_ = false, attempted_ = false, haveFrame_ = false, paused_ = false, muted_ = false;
    void play(AudioCue cue, bool positional, const AudioFrame &frame, const AudioSettings &settings);
    void stopVoices();
};
} // namespace dw
