#pragma once
#include "audio/AudioState.hpp"
#include <filesystem>

namespace dw {
// Streams the supplied score independently of positional effects and ambience.
class MusicDirector {
  public:
    MusicDirector() = default;
    ~MusicDirector() {
        unload();
    }
    MusicDirector(const MusicDirector &) = delete;
    MusicDirector &operator=(const MusicDirector &) = delete;
    bool load(const std::filesystem::path &directory);
    void update(MusicScene scene, uint64_t context, float dt, bool paused, const AudioSettings &settings);
    void unload();
    bool ready() const {
        return ready_;
    }
    float level(MusicScene scene) const {
        return gains_[size_t(scene)];
    }
    float position(MusicScene scene) const;
    uint64_t stingersPlayed() const {
        return stingersPlayed_;
    }
    bool stingerPlaying() const;
    MusicScene selected() const {
        return selected_;
    }

  private:
    std::array<Music, size_t(MusicScene::Silent)> tracks_{};
    std::array<float, size_t(MusicScene::Count)> gains_{};
    std::array<Sound, size_t(MusicStinger::Count)> stingers_{};
    MusicScene requested_ = MusicScene::Silent, selected_ = MusicScene::Silent;
    MusicStinger stinger_ = MusicStinger::Count;
    uint64_t context_ = 0, stingersPlayed_ = 0;
    float release_ = 0, duck_ = 1;
    bool ready_ = false, haveFrame_ = false;
    void stopStinger();
};
} // namespace dw
