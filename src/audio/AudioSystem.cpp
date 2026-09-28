#include "audio/AudioSystem.hpp"
#include "platform/Browser.hpp"
#include <fstream>

namespace dw {
namespace {
struct Clip {
    const char *name;
    int variants;
    float gain, cooldown;
};
constexpr std::array<Clip, size_t(AudioCueKind::Count)> Clips{{{"shot", 3, .8f, .045f},
                                                               {"stone", 3, .38f, .035f},
                                                               {"flesh", 3, .4f, .035f},
                                                               {"hurt", 1, .85f, .12f},
                                                               {"dodge", 1, .6f, .1f},
                                                               {"enemy_death", 1, .5f, .06f},
                                                               {"player_death", 1, .9f, .4f},
                                                               {"warning", 1, .45f, .09f},
                                                               {"explosion", 1, .65f, .08f},
                                                               {"pickup", 1, .7f, .08f},
                                                               {"clear", 1, .7f, .2f},
                                                               {"door", 1, .45f, .15f},
                                                               {"ui", 1, .55f, .055f},
                                                               {"test", 1, .7f, .25f},
                                                               {"step_gravel", 3, .5f, .16f},
                                                               {"step_wood", 3, .45f, .16f},
                                                               {"step_mine", 3, .5f, .16f},
                                                               {"shot", 3, .45f, .07f},
                                                               {"monster_attack", 1, .45f, .07f}}};
constexpr std::array<const char *, 4> AmbienceNames{"town", "frontier", "canyon", "mine"};
float volume(float value) {
    return std::isfinite(value) ? std::clamp(value, 0.f, 1.f) : 0.f;
}
void limitMix(void *buffer, unsigned int frames) {
    // raylib's mixer is interleaved float stereo. No allocation or game access on this thread.
    auto *samples = static_cast<float *>(buffer);
    for (size_t i = 0; i < size_t(frames) * 2; ++i)
        samples[i] = std::isfinite(samples[i]) ? .95f * std::tanh(samples[i] / .95f) : 0;
}
} // namespace
AudioSpatial spatialAudio(Vector3 source, Vector3 listener, const Camera3D &camera) {
    const auto delta = sub(source, listener);
    const float range = std::sqrt(delta.x * delta.x + delta.z * delta.z);
    const auto forward = unit({camera.target.x - camera.position.x, 0, camera.target.z - camera.position.z});
    const Vector3 right{-forward.z, 0, forward.x};
    const float side = dot(delta, right) / std::max(5.f, range);
    // In pinned raylib 5.5, pan=1 feeds the left channel, pan=0 the right.
    return {std::pow(std::clamp(1.f - range / 55.f, 0.f, 1.f), 1.5f),
            std::clamp(.5f - side * .42f, .08f, .92f)};
}
AudioSettings loadAudioSettings(const std::filesystem::path &file) {
    AudioSettings settings, parsed;
    std::ifstream input(file);
    std::string version;
    int muted = 0;
    if (!(input >> version >> parsed.master >> parsed.effects >> parsed.ambience >> muted))
        return settings;
    if (version == "DW_AUDIO_2") {
        if (!(input >> parsed.music))
            return settings;
    } else if (version != "DW_AUDIO_1")
        return settings;
    if (std::isfinite(parsed.master) && std::isfinite(parsed.effects) && std::isfinite(parsed.ambience) &&
        std::isfinite(parsed.music) && (muted == 0 || muted == 1))
        settings = {volume(parsed.master), volume(parsed.effects), volume(parsed.ambience), muted != 0,
                    volume(parsed.music)};
    return settings;
}
bool saveAudioSettings(const std::filesystem::path &file, const AudioSettings &settings) {
    if (file.empty())
        return true;
    std::error_code error;
    if (!file.parent_path().empty())
        std::filesystem::create_directories(file.parent_path(), error);
    if (error)
        return false;
    std::ofstream output(file);
    output << "DW_AUDIO_2\n"
           << volume(settings.master) << ' ' << volume(settings.effects) << ' ' << volume(settings.ambience)
           << ' ' << int(settings.muted) << ' ' << volume(settings.music) << '\n';
    output.close();
    if (output)
        persistBrowserFiles();
    return bool(output);
}
std::filesystem::path AudioSystem::assetDirectory() {
    const auto packaged = std::filesystem::path(GetApplicationDirectory()) / "assets/audio";
    if (std::filesystem::exists(packaged / "shot_0.wav"))
        return packaged;
#ifdef DEATHWARD_ASSET_DIR
    return std::filesystem::path(DEATHWARD_ASSET_DIR) / "audio";
#else
    return "assets/audio";
#endif
}
AudioSystem::~AudioSystem() {
    unload();
}
AudioStatus AudioSystem::initialize(bool enabled, const std::filesystem::path &directory) {
    if (!enabled)
        return AudioStatus::Disabled;
    if (attempted_)
        return ready_ ? AudioStatus::Ready : AudioStatus::Unavailable;
    attempted_ = true;
    InitAudioDevice();
    if (!IsAudioDeviceReady()) {
        TraceLog(LOG_WARNING, "AUDIO: No playback device; continuing silently");
        return AudioStatus::Unavailable;
    }
    ready_ = true;
    SetMasterVolume(0);
    AttachAudioMixedProcessor(limitMix);
    bool complete = true;
    for (size_t i = 0; i < Clips.size(); ++i) {
        const auto &clip = Clips[i];
        sounds_[i].reserve(size_t(clip.variants));
        for (int n = 0; n < clip.variants; ++n) {
            const auto name =
                std::string(clip.name) + (clip.variants > 1 ? "_" + std::to_string(n) : "") + ".wav";
            auto sound = LoadSound((directory / name).string().c_str());
            if (IsSoundValid(sound))
                sounds_[i].push_back(sound);
            else
                complete = false;
        }
    }
    // Two-second stream halves cover brief scene-loading stalls. This only prebuffers
    // ambient PCM; it does not change the playback device or one-shot sound latency.
    SetAudioStreamBufferSizeDefault(88200);
    for (size_t i = 0; i < ambience_.size(); ++i) {
        ambience_[i] =
            LoadMusicStream((directory / (std::string(AmbienceNames[i]) + ".ogg")).string().c_str());
        ambience_[i].looping = true;
        if (!IsMusicValid(ambience_[i]))
            complete = false;
    }
    if (!complete) {
        TraceLog(LOG_WARNING, "AUDIO: Incomplete sound pack; continuing silently");
        unload();
        attempted_ = true;
        return AudioStatus::Unavailable;
    }
    music_.load(directory / "music");
    return AudioStatus::Ready;
}
void AudioSystem::stopVoices() {
    for (auto &voice : voices_)
        if (voice.source)
            StopSound(voice.alias);
}
size_t AudioSystem::activeVoices() const {
    return size_t(std::count_if(voices_.begin(), voices_.end(),
                                [](const auto &v) { return v.source && IsSoundPlaying(v.alias); }));
}
void AudioSystem::play(AudioCue cue, bool positional, const AudioFrame &frame,
                       const AudioSettings &settings) {
    const size_t index = size_t(cue.kind);
    const auto &clip = Clips[index];
    const auto spatial =
        positional ? spatialAudio(cue.position, frame.player, frame.camera) : AudioSpatial{1, .5f};
    if (time_ < nextCue_[index] || spatial.gain < .01f || volume(settings.effects) <= 0) {
        ++suppressed_;
        return;
    }
    auto voice = std::find_if(voices_.begin(), voices_.end(),
                              [](const auto &v) { return !v.source || !IsSoundPlaying(v.alias); });
    if (voice == voices_.end()) {
        voice = std::min_element(voices_.begin(), voices_.end(), [](const auto &a, const auto &b) {
            const int ap = audioPriority(a.cue.kind), bp = audioPriority(b.cue.kind);
            return ap == bp ? a.started < b.started : ap < bp;
        });
        if (audioPriority(voice->cue.kind) >= audioPriority(cue.kind)) {
            ++suppressed_;
            return;
        }
    }
    const auto *source = &sounds_[index][random_.bounded(uint32_t(sounds_[index].size()))];
    if (voice->source)
        StopSound(voice->alias);
    if (voice->source != source) {
        if (voice->source)
            UnloadSoundAlias(voice->alias);
        voice->alias = LoadSoundAlias(*source);
        voice->source = source;
    }
    voice->cue = cue;
    voice->gain = clip.gain;
    voice->positional = positional;
    voice->started = time_;
    SetSoundVolume(voice->alias, clip.gain * spatial.gain * volume(settings.effects));
    SetSoundPan(voice->alias, spatial.pan);
    const bool tune = cue.kind == AudioCueKind::Pickup || cue.kind == AudioCueKind::RoomClear ||
                      cue.kind == AudioCueKind::Test;
    SetSoundPitch(voice->alias, tune ? 1.f : random_.real(.94f, 1.06f));
    PlaySound(voice->alias);
    nextCue_[index] = time_ + clip.cooldown;
    ++played_;
}
void AudioSystem::update(const AudioFrame &frame, const AudioSettings &settings,
                         std::span<const AudioCue> world, std::span<const AudioCue> ui) {
    if (!ready_)
        return;
    const float dt = std::clamp(frame.dt, 0.f, .1f);
    time_ += dt;
    const bool muted = settings.muted || volume(settings.master) <= 0;
    const bool changed = !haveFrame_ || frame.context != context_ || frame.room != room_;
    if (changed || (frame.paused && !paused_) || (muted && !muted_)) {
        stopVoices();
        nextCue_.fill(0);
        stepDistance_ = 0;
    }
    SetMasterVolume(muted ? 0 : volume(settings.master));
    music_.update(frame.music, frame.context, dt, frame.paused, settings);
    for (size_t i = 0; i < ambience_.size(); ++i) {
        const float target = i == size_t(frame.environment) && !muted ? 1.f : 0.f;
        ambienceGain_[i] += (target - ambienceGain_[i]) * (1 - std::exp(-dt * 2.5f));
        if (ambienceGain_[i] < .002f && target == 0) {
            ambienceGain_[i] = 0;
            if (IsMusicStreamPlaying(ambience_[i]))
                StopMusicStream(ambience_[i]);
        } else {
            SetMusicVolume(ambience_[i],
                           volume(settings.ambience) * ambienceGain_[i] * (frame.paused ? .2f : 1.f));
            if (!IsMusicStreamPlaying(ambience_[i]))
                PlayMusicStream(ambience_[i]);
            UpdateMusicStream(ambience_[i]);
        }
    }
    for (auto &voice : voices_) {
        if (!voice.source || !IsSoundPlaying(voice.alias))
            continue;
        const auto spatial = voice.positional ? spatialAudio(voice.cue.position, frame.player, frame.camera)
                                              : AudioSpatial{1, .5f};
        SetSoundPan(voice.alias, spatial.pan);
        SetSoundVolume(voice.alias, voice.gain * spatial.gain * volume(settings.effects));
    }
    if (!muted) {
        // Highest-priority cues enter the pool first during a chain reaction.
        for (int priority = 5; priority >= 1; --priority) {
            for (const auto &cue : world)
                if ((!frame.paused || cue.kind == AudioCueKind::PlayerDeath) &&
                    audioPriority(cue.kind) == priority)
                    play(cue, true, frame, settings);
            for (const auto &cue : ui)
                if (audioPriority(cue.kind) == priority)
                    play(cue, false, frame, settings);
        }
        const float travel = distance(frame.player, lastPosition_);
        if (!changed && !frame.paused && frame.footsteps && travel > .001f && travel < 3) {
            stepDistance_ += travel;
            if (stepDistance_ >= 1.6f) {
                stepDistance_ = std::fmod(stepDistance_, 1.6f);
                const auto kind = frame.environment == AudioEnvironment::Canyon ? AudioCueKind::StepGravel
                                  : frame.environment == AudioEnvironment::Mine ? AudioCueKind::StepMine
                                                                                : AudioCueKind::StepWood;
                play({kind, frame.player}, false, frame, settings);
            }
        } else
            stepDistance_ = 0;
    }
    lastPosition_ = frame.player;
    context_ = frame.context;
    room_ = frame.room;
    paused_ = frame.paused;
    muted_ = muted;
    haveFrame_ = true;
}
void AudioSystem::unload() {
    if (ready_) {
        music_.unload();
        stopVoices();
        for (auto &voice : voices_)
            if (voice.source)
                UnloadSoundAlias(voice.alias);
        for (auto &clips : sounds_)
            for (auto sound : clips)
                UnloadSound(sound);
        for (auto music : ambience_)
            if (IsMusicValid(music))
                UnloadMusicStream(music);
        DetachAudioMixedProcessor(limitMix);
        CloseAudioDevice();
    }
    for (auto &clips : sounds_)
        clips.clear();
    voices_ = {};
    ambience_ = {};
    ambienceGain_ = {};
    nextCue_ = {};
    ready_ = attempted_ = haveFrame_ = paused_ = muted_ = false;
    stepDistance_ = 0;
    time_ = 0;
}
} // namespace dw
