#include "audio/AudioSystem.hpp"
#include <atomic>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <thread>
using namespace dw;
namespace {
std::atomic<float> peak{0};
std::atomic<uint64_t> framesSeen{0}, nonzeroFrames{0};
std::atomic<double> leftEnergy{0}, rightEnergy{0};
bool audible = false;
void meter(void *data, unsigned int frames) {
    auto *samples = static_cast<float *>(data);
    float maximum = 0;
    double left = 0, right = 0;
    for (size_t i = 0; i < size_t(frames) * 2; ++i) {
        maximum = std::max(maximum, std::abs(samples[i]));
        (i % 2 ? right : left) += std::abs(samples[i]);
        if (!audible)
            samples[i] = 0;
    }
    if (maximum > peak.load())
        peak.store(maximum);
    framesSeen += frames;
    leftEnergy += left;
    rightEnergy += right;
    if (maximum > .0001f)
        nonzeroFrames += frames;
}
void check(bool ok, const char *message) {
    if (!ok)
        throw std::runtime_error(message);
}
void wait() {
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}
void verifyMusic(AudioSystem &audio, AudioFrame frame) {
    check(audio.music().ready(), "all eight score streams and four stingers load");
    AudioSettings settings;
    settings.effects = settings.ambience = 0;
    settings.music = .6f;
    frame.footsteps = false;
    frame.dt = .02f;
    frame.music = MusicScene::Town;
    ++frame.context;
    auto pump = [&](int count) {
        for (int i = 0; i < count; ++i) {
            audio.update(frame, settings, {});
            wait();
        }
    };
    const auto samples = nonzeroFrames.load();
    pump(60);
    check(nonzeroFrames > samples && audio.music().level(MusicScene::Town) > .9f,
          "the imported town track produces PCM with effects and ambience at zero");
    auto before = audio.music().position(MusicScene::Town);
    pump(20);
    check(audio.music().position(MusicScene::Town) > before + .2f,
          "ordinary frames keep the score playing without restarting it");
    const auto noStinger = audio.music().stingersPlayed();
    frame.music = MusicScene::Frontier;
    ++frame.context;
    pump(1);
    check(audio.music().level(MusicScene::Town) > 0 && audio.music().level(MusicScene::Frontier) > 0 &&
              audio.music().stingersPlayed() == noStinger,
          "hub travel crossfades themes without a mission stinger");
    frame.music = MusicScene::Canyon;
    ++frame.context;
    pump(30);
    check(audio.music().stingersPlayed() == noStinger + 1 && audio.music().stingerPlaying(),
          "departure plays its original stereo stinger once");
    ++frame.room;
    pump(10);
    check(audio.music().stingersPlayed() == noStinger + 1,
          "room travel never repeats the mission departure stinger");
    frame.music = MusicScene::Combat;
    pump(1);
    check(audio.music().level(MusicScene::Canyon) > 0 && audio.music().level(MusicScene::Combat) > 0 &&
              std::abs(audio.music().position(MusicScene::Canyon) -
                       audio.music().position(MusicScene::Combat)) < .15f,
          "Hunt combat crossfades at the current exploration timeline position");
    frame.music = MusicScene::Boss;
    pump(15);
    check(audio.music().selected() == MusicScene::Boss && audio.music().stingersPlayed() == noStinger + 2,
          "boss entry replaces the departure cue with one rattle");
    frame.music = MusicScene::Canyon;
    pump(50);
    check(audio.music().selected() == MusicScene::Boss, "combat music retains a short release tail");
    pump(60);
    check(audio.music().selected() == MusicScene::Canyon, "cleared combat returns to exploration music");
    frame.music = MusicScene::Victory;
    frame.paused = true;
    ++frame.context;
    pump(20);
    check(audio.music().selected() == MusicScene::Victory &&
              audio.music().stingersPlayed() == noStinger + 3 && audio.music().stingerPlaying(),
          "victory summary plays its score and one shimmer even with gameplay stopped");
    frame.music = MusicScene::Town;
    pump(1);
    check(!audio.music().stingerPlaying(),
          "returning to the hub stops the old result stinger without needing a world reload");
    frame.music = MusicScene::Defeat;
    pump(1);
    const auto death = audio.music().stingersPlayed();
    ++frame.context;
    pump(10);
    check(death == noStinger + 4 && audio.music().stingersPlayed() == death && audio.music().stingerPlaying(),
          "death animation and summary share a single defeat stinger");
    settings.music = 0;
    pump(12);
    const auto silentFrames = nonzeroFrames.load();
    pump(12);
    check(nonzeroFrames == silentFrames && !audio.music().stingerPlaying(),
          "the music slider silences both the score and stingers independently");
    settings.music = .6f;
    pump(12);
    check(nonzeroFrames > silentFrames && audio.music().stingersPlayed() == death,
          "raising music resumes the ongoing timeline without replaying stingers");
    settings.muted = true;
    frame.music = MusicScene::Boss;
    ++frame.context;
    pump(12);
    check(audio.music().stingersPlayed() == death && !audio.music().stingerPlaying(),
          "muted transitions consume their cues without playing or deferring them");
    settings.muted = false;
    pump(10);
    check(audio.music().stingersPlayed() == death, "unmute cannot replay a stale boss cue");
    frame.music = MusicScene::Silent;
    pump(160);
    for (int i = 0; i < int(MusicScene::Silent); ++i)
        check(audio.music().level(MusicScene(i)) == 0, "editor silence releases every previous score stream");
}
void verify(bool noDevice) {
    AudioSystem audio;
    check(audio.initialize(false) == AudioStatus::Disabled && !IsAudioDeviceReady(),
          "muted launch skips device initialization");
    const auto result = audio.initialize(true);
    if (noDevice) {
        check(result == AudioStatus::Unavailable && !audio.ready(),
              "missing output falls back to silent gameplay");
        check(audio.initialize(true) == AudioStatus::Unavailable,
              "failed device is not repeatedly initialized");
        audio.update({}, {}, {});
        return;
    }
    check(result == AudioStatus::Ready, "real playback device and complete sound pack required");
    AttachAudioMixedProcessor(meter);
    AudioSettings settings;
    AudioFrame frame;
    frame.music = MusicScene::Silent;
    frame.camera = {{0, 20, 20}, {0, 0, 0}, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
    frame.dt = .02f;
    const auto right = spatialAudio({10, 0, 0}, {}, frame.camera);
    const auto left = spatialAudio({-10, 0, 0}, {}, frame.camera);
    check(right.pan < .5f && left.pan > .5f && std::abs(right.gain - left.gain) < .001f,
          "stereo follows pinned raylib channel direction");
    frame.camera.position.z = -20;
    check(spatialAudio({10, 0, 0}, {}, frame.camera).pan > .5f, "orbiting reverses stereo positioning");
    check(spatialAudio({100, 0, 0}, {}, frame.camera).gain == 0, "distant sounds are culled");
    std::array<AudioCue, 1> cue{{{AudioCueKind::Test}}};
    audio.update(frame, settings, {}, cue);
    check(audio.played() == 1, "UI test uses a nonpositional voice");
    for (int i = 0; i < 30; ++i) {
        audio.update(frame, settings, {});
        wait();
    }
    check(peak > .001f && peak <= .951f && nonzeroFrames > 0, "real mixer produces nonzero limited PCM");
    settings.ambience = 0;
    const std::array<AudioCue, 1> positional{{{AudioCueKind::Shot, {10, 0, 0}}}};
    for (float cameraZ : {20.f, -20.f}) {
        frame.camera.position.z = cameraZ;
        ++frame.context;
        leftEnergy = rightEnergy = 0;
        audio.update(frame, settings, positional);
        for (int i = 0; i < 18; ++i) {
            audio.update(frame, settings, {});
            wait();
        }
        check(cameraZ > 0 ? rightEnergy > leftEnergy * 2 : leftEnergy > rightEnergy * 2,
              "actual PCM channels follow source position and camera orbit");
    }
    settings.ambience = .45f;
    AudioCueQueue flood;
    for (int i = 0; i < 5000; ++i)
        flood.push(AudioCueKind::Explosion);
    flood.push(AudioCueKind::Hurt);
    const auto played = audio.played();
    audio.update(frame, settings, flood.cues());
    check(audio.played() - played == 2 && audio.activeVoices() <= AudioSystem::VoiceLimit &&
              audio.suppressed() > 0,
          "chain reactions rate-limit repeated sounds and preserve hurt feedback");
    const std::array<AudioCue, 1> impact{{{AudioCueKind::StoneHit}}};
    frame.dt = .1f;
    for (int i = 0; i < 50; ++i)
        audio.update(frame, settings, impact);
    check(audio.activeVoices() == AudioSystem::VoiceLimit,
          "simultaneous sounds fill but never exceed the voice budget");
    const auto beforeHurt = audio.played();
    const std::array<AudioCue, 1> hurt{{{AudioCueKind::Hurt}}};
    audio.update(frame, settings, hurt);
    check(audio.played() == beforeHurt + 1 && audio.activeVoices() == AudioSystem::VoiceLimit,
          "player damage replaces an incidental voice in a full sound pool");
    frame.dt = .02f;
    frame.paused = true;
    audio.update(frame, settings, flood.cues());
    check(audio.activeVoices() == 0, "pause stops combat voices and drops world cues");
    frame.paused = false;
    settings.muted = true;
    audio.update(frame, settings, {}, cue);
    check(audio.activeVoices() == 0 && GetMasterVolume() == 0, "mute stops effects and silences output");
    settings.muted = false;
    frame.context++;
    const auto footsteps = audio.played();
    audio.update(frame, settings, {});
    for (int i = 0; i < 20; ++i) {
        frame.player.x += .12f;
        audio.update(frame, settings, {});
    }
    check(audio.played() > footsteps, "actual travel produces footsteps");
    const auto stationary = audio.played();
    for (int i = 0; i < 20; ++i)
        audio.update(frame, settings, {});
    check(audio.played() == stationary, "stationary players produce no footsteps");
    frame.footsteps = false;
    for (int i = 0; i < 20; ++i) {
        frame.player.x += .12f;
        audio.update(frame, settings, {});
    }
    check(audio.played() == stationary, "dodge and pull movement produce no footsteps");
    frame.environment = AudioEnvironment::Canyon;
    frame.context++;
    audio.update(frame, settings, {});
    check(audio.activeVoices() == 0, "travel stops old one-shots");
    check(audio.ambienceLevel(AudioEnvironment::Town) > 0 &&
              audio.ambienceLevel(AudioEnvironment::Canyon) > 0,
          "old and new ambience overlap during a crossfade");
    // Run longer than the 16-second loop, checking that the actual callback continues producing audio.
    uint64_t lastFrames = nonzeroFrames;
    for (int i = 0; i < 850; ++i) {
        audio.update(frame, settings, {});
        wait();
        if (i % 100 == 99) {
            check(nonzeroFrames > lastFrames, "streamed ambience continues through the loop boundary");
            lastFrames = nonzeroFrames;
        }
    }
    check(audio.ambienceLevel(AudioEnvironment::Town) == 0 &&
              audio.ambienceLevel(AudioEnvironment::Canyon) > .99f,
          "travel finishes fading the previous location out");
    const auto bufferedFrames = nonzeroFrames.load();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    check(nonzeroFrames > bufferedFrames + 15000,
          "ambience continues through a brief main-thread loading stall");
    verifyMusic(audio, frame);
    DetachAudioMixedProcessor(meter);
    check(peak <= .951f, "stacked effects remain below the limiter ceiling");
    audio.unload();
    audio.unload();
    check(!IsAudioDeviceReady(), "cleanup releases the device");
    check(audio.initialize(true) == AudioStatus::Ready, "audio can reload after cleanup");
    MusicDirector missing;
    check(!missing.load(AudioSystem::assetDirectory() / "nonexistent-music") && audio.ready(),
          "missing music is optional and cannot disable the existing audio device");
    missing.unload();
    audio.unload();

    const auto file =
        std::filesystem::temp_directory_path() /
        ("deathward-audio-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    settings = {.2f, .3f, .4f, true, .7f};
    check(saveAudioSettings(file, settings) && loadAudioSettings(file) == settings,
          "volume preferences round-trip independently of campaign data");
    {
        std::ofstream legacy(file);
        legacy << "DW_AUDIO_1\n0.2 0.3 0.4 1\n";
    }
    check(loadAudioSettings(file) == AudioSettings{.2f, .3f, .4f, true, .4f},
          "old settings retain every preference and add the default music volume");
    {
        std::ofstream corrupt(file);
        corrupt << "invalid audio settings";
    }
    check(loadAudioSettings(file) == AudioSettings{}, "invalid preferences restore sensible defaults");
    std::filesystem::remove(file);
    std::cout << "Mixed peak=" << peak.load() << " callback frames=" << framesSeen.load() << '\n';
}
} // namespace
int main(int argc, char **argv) {
    bool noDevice = false;
    for (int i = 1; i < argc; ++i) {
        audible = audible || std::string(argv[i]) == "--audible";
        noDevice = noDevice || std::string(argv[i]) == "--no-device";
    }
    try {
        SetTraceLogLevel(LOG_INFO);
        verify(noDevice);
        std::cout << "PASS audio playback, mixing and lifecycle checks\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL " << e.what() << '\n';
        return 1;
    }
}
