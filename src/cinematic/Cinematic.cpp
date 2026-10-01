#include "cinematic/Cinematic.hpp"
#include "platform/Browser.hpp"
#include "raymath.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace dw {
namespace {
void require(bool ok, const char *message) { if (!ok) throw std::runtime_error(message); }
bool finite(Vector3 p) { return std::isfinite(p.x) && std::isfinite(p.y) && std::isfinite(p.z); }
bool safeAudio(const std::string &file) {
    const std::filesystem::path path(file);
    if (file.empty() || path.is_absolute() || file.find('\\') != std::string::npos ||
        file.find(':') != std::string::npos)
        return false;
    for (const auto &part : path) if (part == "..") return false;
    return path.extension() == ".wav" || path.extension() == ".ogg";
}
template<class T> void order(std::vector<T> &items) {
    std::stable_sort(items.begin(), items.end(), [](const auto &a, const auto &b) { return a.time < b.time; });
}
} // namespace
void Cinematic::sort() { order(cameras); order(weather); order(trains); order(sounds); }
void Cinematic::validate(const TownDocument *scene) const {
    require(std::isfinite(duration) && duration >= 1 && duration <= 600, "Duration must be 1 to 600 seconds.");
    require(!title.empty() && title.size() <= 120, "Sequence title must be 1 to 120 characters.");
    require(!cameras.empty(), "Add at least one camera key.");
    auto track = [&](const auto &keys, bool unique) {
        require(keys.size() <= 512, "A track supports at most 512 keys.");
        float previous = -1;
        for (const auto &key : keys) {
            require(std::isfinite(key.time) && key.time >= 0 && key.time <= duration,
                    "Key times must be within the sequence.");
            require(unique ? key.time > previous : key.time >= previous, "Track times must be ordered.");
            previous = key.time;
        }
    };
    track(cameras, true); track(weather, true); track(trains, false); track(sounds, false);
    for (const auto &key : cameras) {
        require(finite(key.position) && finite(key.target) && distance(key.position, key.target) > .01f,
                "Camera position and target must be finite and different.");
        require(std::isfinite(key.fov) && key.fov >= 10 && key.fov <= 110, "Camera FOV must be 10 to 110 degrees.");
        require(int(key.blend) >= 0 && int(key.blend) <= 2, "Unknown camera transition.");
        if (scene && !key.anchor.empty())
            require(std::any_of(scene->groups.begin(), scene->groups.end(), [&](const auto &g) { return g.id == key.anchor; }),
                    "A camera's vehicle anchor is missing from this scene.");
    }
    for (const auto &key : weather)
        require(std::isfinite(key.amount) && key.amount >= 0 && key.amount <= 1, "Storm strength must be 0 to 1.");
    for (const auto &cue : trains) {
        require(std::isfinite(cue.speed) && cue.speed >= 0 && cue.speed <= 40 &&
                std::isfinite(cue.acceleration) && cue.acceleration > 0 && cue.acceleration <= 40,
                "Train speed or acceleration is out of range.");
        if (scene && cue.path != "*")
            require(std::any_of(scene->paths.begin(), scene->paths.end(), [&](const auto &p) { return p.id == cue.path; }),
                    "A train cue's route is missing from this scene.");
    }
    for (const auto &cue : sounds)
        require(safeAudio(cue.file) && std::isfinite(cue.volume) && cue.volume >= 0 && cue.volume <= 1 &&
                std::isfinite(cue.duration) && cue.duration >= 0 && cue.duration <= 600,
                "Sound must be a relative WAV/OGG file with volume from 0 to 1.");
}
bool Cinematic::load(const std::filesystem::path &file, std::string &error) {
    try {
        std::ifstream in(file);
        std::string magic, line; int version = 0;
        require(bool(in >> magic >> version) && magic == "DEATHWARD_CINEMATIC" && version == 1,
                "Cannot read this cinematic file.");
        Cinematic next;
        while (std::getline(in, line)) {
            if (line.empty() || line[0] == '#') continue;
            std::istringstream row(line); std::string kind, extra;
            row >> kind;
            if (kind == "title") row >> std::quoted(next.title);
            else if (kind == "duration") row >> next.duration;
            else if (kind == "camera") {
                CameraKey k; int blend = 0;
                row >> k.time >> k.position.x >> k.position.y >> k.position.z >> k.target.x >> k.target.y >> k.target.z
                    >> k.fov >> blend >> std::quoted(k.anchor);
                k.blend = CameraBlend(blend); next.cameras.push_back(k);
            } else if (kind == "weather") {
                WeatherKey k; row >> k.time >> k.amount; next.weather.push_back(k);
            } else if (kind == "train") {
                TrainCue k; row >> k.time >> k.speed >> k.acceleration >> std::quoted(k.path); next.trains.push_back(k);
            } else if (kind == "sound") {
                SoundCue k; row >> k.time >> k.volume >> k.duration >> std::quoted(k.file); next.sounds.push_back(k);
            } else throw std::runtime_error("Unknown cinematic record: " + kind);
            require(bool(row) && !(row >> extra), "Malformed cinematic record.");
        }
        next.sort(); next.validate(); *this = std::move(next); error.clear(); return true;
    } catch (const std::exception &e) { error = e.what(); return false; }
}
bool Cinematic::save(const std::filesystem::path &file, std::string &error) const {
    try {
        validate();
        if (!file.parent_path().empty()) std::filesystem::create_directories(file.parent_path());
        auto temporary = file; temporary += ".tmp";
        std::ofstream out(temporary);
        out << std::setprecision(9) << "DEATHWARD_CINEMATIC 1\ntitle " << std::quoted(title) << "\nduration " << duration << '\n';
        for (const auto &k : cameras)
            out << "camera " << k.time << ' ' << k.position.x << ' ' << k.position.y << ' ' << k.position.z << ' '
                << k.target.x << ' ' << k.target.y << ' ' << k.target.z << ' ' << k.fov << ' ' << int(k.blend) << ' '
                << std::quoted(k.anchor) << '\n';
        for (const auto &k : weather) out << "weather " << k.time << ' ' << k.amount << '\n';
        for (const auto &k : trains) out << "train " << k.time << ' ' << k.speed << ' ' << k.acceleration << ' ' << std::quoted(k.path) << '\n';
        for (const auto &k : sounds) out << "sound " << k.time << ' ' << k.volume << ' ' << k.duration << ' ' << std::quoted(k.file) << '\n';
        out.close(); require(bool(out), "Could not write cinematic file.");
        std::filesystem::rename(temporary, file); persistBrowserFiles(); error.clear(); return true;
    } catch (const std::exception &e) { error = e.what(); return false; }
}
float Cinematic::storm(float time) const {
    if (weather.empty()) return 0;
    if (time <= weather.front().time) return weather.front().amount;
    for (size_t i = 1; i < weather.size(); ++i)
        if (time < weather[i].time) {
            const auto &a = weather[i-1], &b = weather[i];
            float t = (time-a.time)/(b.time-a.time); t = t*t*(3-2*t);
            return std::lerp(a.amount,b.amount,t);
        }
    return weather.back().amount;
}
Cinematic Cinematic::demo(const TownDocument &scene, Camera3D view) {
    Cinematic result;
    result.title = "The storm stops the train";
    result.duration = 20;
    result.cameras = {{0, view.position, view.target, view.fovy,{}}, {20, view.position, view.target, 35,{}}};
    if (!scene.groups.empty()) {
        std::string carriage = scene.groups.front().id;
        for (const auto &instance : scene.instances)
            if (!instance.group.empty() && scene.assets[instance.asset].label.find("Carriage") != std::string::npos) {
                carriage = instance.group; break;
            }
        result.cameras = {
            {0, {10,7,14}, {0,2,0}, 45, carriage},
            {5, {7,4,9}, {0,2,0}, 38, carriage, CameraBlend::Cut},
            {5.1f, {-3,2.6f,0}, {3,2.4f,0}, 70, carriage},
            {9, {-2.7f,2.6f,0}, {3,2.4f,0}, 58, carriage, CameraBlend::Cut},
            {9.1f, {10,5,13}, {0,2,0}, 43, carriage},
            {15, {15,10,21}, {0,2,0}, 45, carriage},
            {20, {18,13,26}, {0,2,0}, 48, carriage}};
        result.trains = {{0,6,4,"*"}, {11,0,12,"*"}};
        result.sounds = {{0,"cinematic/train_roll.wav",.6f,11}, {7,"cinematic/storm_wind.wav",.7f,13},
                         {11,"cinematic/train_brake.wav",.9f}};
    } else
        result.sounds = {{7,"cinematic/storm_wind.wav",.7f}};
    result.weather = {{0,0},{4,.1f},{9,.85f},{12,1},{20,.8f}};
    result.validate(&scene); return result;
}
void CinematicPlayer::reset(const TownDocument &scene, const Cinematic &sequence, ObjectAnimationSystem::Ground ground) {
    sequence.validate(&scene); scene_ = scene; sequence_ = sequence; ground_ = std::move(ground); seek(0);
}
void CinematicPlayer::trainCues(double through) {
    while (nextTrain_ < sequence_.trains.size() && sequence_.trains[nextTrain_].time <= through + 1e-7) {
        const auto &cue = sequence_.trains[nextTrain_++];
        animation_.setPathMotion(cue.path, cue.speed, cue.acceleration);
    }
}
void CinematicPlayer::simulate(double seconds) {
    constexpr double tick = 1.0 / 60.0;
    while (simulated_ + tick <= double(seconds) + 1e-6) {
        trainCues(simulated_);
        animation_.update(float(tick), ground_);
        simulated_ += tick;
    }
    time_ = seconds;
}
void CinematicPlayer::seek(float seconds) {
    playing_ = started_ = false; pending_.clear(); nextTrain_ = 0; simulated_ = 0; time_ = 0;
    animation_.reset(scene_); trainCues(0);
    simulate(std::clamp(seconds, 0.f, sequence_.duration));
}
void CinematicPlayer::play() {
    if (time_ >= sequence_.duration) seek(0);
    if (!started_)
        for (const auto &cue : sequence_.sounds)
            if (cue.time == time_ || (cue.duration > 0 && cue.time < time_ && time_ < cue.time + cue.duration))
                pending_.push_back(cue);
    started_ = playing_ = true;
}
void CinematicPlayer::advance(float seconds) {
    if (!playing_ || !std::isfinite(seconds) || seconds <= 0) return;
    const double target = std::min(double(sequence_.duration), time_ + seconds);
    for (const auto &cue : sequence_.sounds)
        if (cue.time > time_ && cue.time <= target) pending_.push_back(cue);
    simulate(target);
    if (time_ >= sequence_.duration) playing_ = false;
}
std::optional<Matrix> CinematicPlayer::anchor(const std::string &id) const {
    for (size_t i = 0; i < scene_.groups.size(); ++i)
        if (scene_.groups[i].id == id) return animation_.groupTransform(i);
    return std::nullopt;
}
Camera3D CinematicPlayer::camera() const {
    auto resolve = [&](const CameraKey &key) {
        Camera3D result{key.position,key.target,{0,1,0},key.fov,CAMERA_PERSPECTIVE};
        if (auto transform = anchor(key.anchor)) {
            result.position = Vector3Transform(result.position,*transform);
            result.target = Vector3Transform(result.target,*transform);
        }
        return result;
    };
    if (time_ <= sequence_.cameras.front().time) return resolve(sequence_.cameras.front());
    for (size_t i = 1; i < sequence_.cameras.size(); ++i)
        if (time_ < sequence_.cameras[i].time) {
            const auto &a = sequence_.cameras[i-1], &b = sequence_.cameras[i];
            auto left = resolve(a), right = resolve(b);
            float t = (time_-a.time)/(b.time-a.time);
            if (a.blend == CameraBlend::Cut) t = 0;
            else if (a.blend == CameraBlend::Smooth) t = t*t*(3-2*t);
            left.position = Vector3Lerp(left.position,right.position,t);
            left.target = Vector3Lerp(left.target,right.target,t);
            left.fovy = std::lerp(left.fovy,right.fovy,t);
            if (distance(left.position,left.target) < .01f) left.target = add(left.position,{0,0,1});
            return left;
        }
    return resolve(sequence_.cameras.back());
}
std::vector<SoundCue> CinematicPlayer::takeSounds() { auto result = std::move(pending_); pending_.clear(); return result; }
} // namespace dw
