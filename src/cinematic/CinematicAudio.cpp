#include "cinematic/CinematicAudio.hpp"

namespace dw {
void CinematicAudio::stop() {
    for (auto &voice : voices_) {
        StopMusicStream(voice.stream);
        UnloadMusicStream(voice.stream);
    }
    voices_.clear();
}
void CinematicAudio::update(float time, bool playing, const AudioSettings &settings,
                            const std::vector<SoundCue> &cues, const std::filesystem::path &directory) {
    if (!IsAudioDeviceReady()) return;
    for (const auto &cue : cues) {
        if (voices_.size() >= 8) { error = "Eight simultaneous sound clips are already playing."; break; }
        const auto file = directory / cue.file;
        if (!std::filesystem::is_regular_file(file)) { error = "Missing sound: " + cue.file; continue; }
        auto stream = LoadMusicStream(file.string().c_str());
        if (!IsMusicValid(stream)) { error = "Cannot load sound: " + cue.file; continue; }
        stream.looping = cue.duration > 0;
        const float duration = cue.duration > 0 ? cue.duration : GetMusicTimeLength(stream);
        SetMusicVolume(stream, settings.muted ? 0 : cue.volume * settings.effects);
        PlayMusicStream(stream);
        if (time > cue.time + .02f && GetMusicTimeLength(stream) > 0)
            SeekMusicStream(stream, std::fmod(time - cue.time, GetMusicTimeLength(stream)));
        voices_.push_back({stream,cue.time + duration,cue.volume,false});
    }
    for (auto i = voices_.begin(); i != voices_.end();) {
        if (time >= i->end) {
            StopMusicStream(i->stream); UnloadMusicStream(i->stream); i = voices_.erase(i); continue;
        }
        SetMusicVolume(i->stream, settings.muted ? 0 : i->gain * settings.effects);
        if (!playing && !i->paused) PauseMusicStream(i->stream);
        if (playing && i->paused) ResumeMusicStream(i->stream);
        i->paused = !playing;
        UpdateMusicStream(i->stream);
        ++i;
    }
}
} // namespace dw
