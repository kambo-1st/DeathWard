#include "audio/MusicDirector.hpp"

namespace dw {
namespace {
constexpr std::array<const char *, size_t(MusicScene::Silent)> TrackNames{
    "town", "frontier", "canyon", "mine", "combat", "boss", "victory", "defeat"};
constexpr std::array<const char *, size_t(MusicStinger::Count)> StingerNames{
    "departure", "boss_entry", "victory_stinger", "defeat_stinger"};
bool expedition(MusicScene scene) {
    return scene == MusicScene::Canyon || scene == MusicScene::Mine || scene == MusicScene::Combat ||
           scene == MusicScene::Boss;
}
bool hunt(MusicScene scene) {
    return scene == MusicScene::Canyon || scene == MusicScene::Combat || scene == MusicScene::Boss;
}
float volume(float value) {
    return std::isfinite(value) ? std::clamp(value, 0.f, 1.f) : 0.f;
}
} // namespace
bool MusicDirector::load(const std::filesystem::path &directory) {
    unload();
    // Music is optional: a missing pack must not disable the core sound effects.
    for (const auto *name : TrackNames)
        if (!std::filesystem::exists(directory / (std::string(name) + ".ogg"))) {
            TraceLog(LOG_WARNING, "AUDIO: Western Music pack missing; effects and ambience remain available");
            return false;
        }
    for (const auto *name : StingerNames)
        if (!std::filesystem::exists(directory / (std::string(name) + ".wav"))) {
            TraceLog(LOG_WARNING,
                     "AUDIO: Western Music stingers missing; effects and ambience remain available");
            return false;
        }
    bool complete = true;
    for (size_t i = 0; i < tracks_.size(); ++i) {
        tracks_[i] = LoadMusicStream((directory / (std::string(TrackNames[i]) + ".ogg")).string().c_str());
        tracks_[i].looping = true;
        complete = complete && IsMusicValid(tracks_[i]);
    }
    for (size_t i = 0; i < stingers_.size(); ++i) {
        stingers_[i] = LoadSound((directory / (std::string(StingerNames[i]) + ".wav")).string().c_str());
        complete = complete && IsSoundValid(stingers_[i]);
    }
    if (!complete) {
        unload();
        TraceLog(LOG_WARNING, "AUDIO: Western Music pack could not load; continuing without score");
        return false;
    }
    ready_ = true;
    return true;
}
float MusicDirector::position(MusicScene scene) const {
    return ready_ && size_t(scene) < tracks_.size() ? GetMusicTimePlayed(tracks_[size_t(scene)]) : 0;
}
bool MusicDirector::stingerPlaying() const {
    return ready_ && stinger_ != MusicStinger::Count && IsSoundPlaying(stingers_[size_t(stinger_)]);
}
void MusicDirector::stopStinger() {
    if (stinger_ != MusicStinger::Count)
        StopSound(stingers_[size_t(stinger_)]);
    stinger_ = MusicStinger::Count;
}
void MusicDirector::update(MusicScene scene, uint64_t context, float dt, bool paused,
                           const AudioSettings &settings) {
    if (!ready_)
        return;
    dt = std::clamp(dt, 0.f, .1f);
    const bool changed = !haveFrame_ || scene != requested_;
    const bool travel = haveFrame_ && context != context_;
    const bool silent = settings.muted || volume(settings.master) == 0 || volume(settings.music) == 0;
    if (changed || travel) {
        // Death's animation and its summary share one cue even though the run is released.
        const bool deathContinues = scene == MusicScene::Defeat && requested_ == scene;
        if ((travel && !deathContinues) ||
            (changed && (scene == MusicScene::Town || scene == MusicScene::Frontier)))
            stopStinger();
        MusicStinger cue = MusicStinger::Count;
        if (haveFrame_ && changed && scene == MusicScene::Defeat)
            cue = MusicStinger::Defeat;
        else if (haveFrame_ && changed && scene == MusicScene::Victory)
            cue = MusicStinger::Victory;
        else if (haveFrame_ && scene == MusicScene::Boss && (changed || travel))
            cue = MusicStinger::Boss;
        else if (haveFrame_ && expedition(scene) && (travel || !expedition(requested_)))
            cue = MusicStinger::Departure;
        if (cue != MusicStinger::Count && !silent) {
            stopStinger();
            stinger_ = cue;
            SetSoundVolume(stingers_[size_t(cue)], volume(settings.music) * .85f);
            PlaySound(stingers_[size_t(cue)]);
            ++stingersPlayed_;
        }
        // Keep a short musical tail after the last enemy instead of switching abruptly.
        release_ = !travel && (selected_ == MusicScene::Combat || selected_ == MusicScene::Boss) &&
                           (scene == MusicScene::Canyon || scene == MusicScene::Mine)
                       ? 2.f
                       : 0.f;
        requested_ = scene;
    }
    release_ = std::max(0.f, release_ - dt);
    if (release_ == 0 && selected_ != requested_) {
        // The three Hunt arrangements share their length and musical timeline.
        // Enter the next arrangement at the same point, then crossfade its mix.
        if (hunt(selected_) && hunt(requested_) &&
            std::abs(GetMusicTimeLength(tracks_[size_t(selected_)]) -
                     GetMusicTimeLength(tracks_[size_t(requested_)])) < .1f) {
            const float at = position(selected_);
            StopMusicStream(tracks_[size_t(requested_)]);
            SeekMusicStream(tracks_[size_t(requested_)], at);
        }
        selected_ = requested_;
    }
    if (silent || scene == MusicScene::Silent)
        stopStinger();
    if (stingerPlaying())
        SetSoundVolume(stingers_[size_t(stinger_)], volume(settings.music) * .85f * (paused ? .65f : 1.f));
    const float duckTarget = stingerPlaying() ? .3f : 1.f;
    duck_ += (duckTarget - duck_) * (1 - std::exp(-dt * (duckTarget < duck_ ? 12.f : 3.f)));
    for (size_t i = 0; i < tracks_.size(); ++i) {
        const float target = i == size_t(selected_) ? 1.f : 0.f;
        gains_[i] += (target - gains_[i]) * (1 - std::exp(-dt * 2.f));
        if (gains_[i] < .002f && target == 0) {
            gains_[i] = 0;
            if (IsMusicStreamPlaying(tracks_[i]))
                StopMusicStream(tracks_[i]);
            continue;
        }
        SetMusicVolume(tracks_[i],
                       (silent ? 0.f : volume(settings.music)) * gains_[i] * duck_ * (paused ? .35f : 1.f));
        if (!IsMusicStreamPlaying(tracks_[i]))
            PlayMusicStream(tracks_[i]);
        UpdateMusicStream(tracks_[i]);
    }
    haveFrame_ = true;
    context_ = context;
}
void MusicDirector::unload() {
    stopStinger();
    for (auto sound : stingers_)
        if (IsSoundValid(sound))
            UnloadSound(sound);
    for (auto track : tracks_)
        if (IsMusicValid(track))
            UnloadMusicStream(track);
    tracks_ = {};
    stingers_ = {};
    gains_ = {};
    requested_ = selected_ = MusicScene::Silent;
    release_ = 0;
    duck_ = 1;
    haveFrame_ = ready_ = false;
}
} // namespace dw
