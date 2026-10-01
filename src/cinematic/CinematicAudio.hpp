#pragma once
#include "cinematic/Cinematic.hpp"
#include "audio/AudioState.hpp"

namespace dw {
// Shares the existing audio device and master volume; never initializes a second device in WSL/Web.
class CinematicAudio {
  public:
    ~CinematicAudio() { stop(); }
    void update(float time, bool playing, const AudioSettings &settings,
                const std::vector<SoundCue> &cues, const std::filesystem::path &directory);
    void stop();
    size_t voices() const { return voices_.size(); }
    std::string error;
  private:
    struct Voice { Music stream{}; float end = 0, gain = 1; bool paused = false; };
    std::vector<Voice> voices_;
};
} // namespace dw
