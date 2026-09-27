#include "render/PlayerModel.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <cstring>
#include <set>

namespace dw {
namespace {
// The pinned raylib 5.5 glTF loader samples animation poses every 17 ms.
constexpr float SampleSeconds = 0.017f;
Transform localTransform(const Transform &parent, const Transform &world) {
    const auto inverse = QuaternionInvert(parent.rotation);
    return {Vector3Divide(
                Vector3RotateByQuaternion(Vector3Subtract(world.translation, parent.translation), inverse),
                parent.scale),
            QuaternionMultiply(inverse, world.rotation), Vector3Divide(world.scale, parent.scale)};
}
Transform worldTransform(const Transform &parent, const Transform &local) {
    return {Vector3Add(
                parent.translation,
                Vector3RotateByQuaternion(Vector3Multiply(local.translation, parent.scale), parent.rotation)),
            QuaternionMultiply(parent.rotation, local.rotation), Vector3Multiply(parent.scale, local.scale)};
}
Transform blend(const Transform &from, const Transform &to, float amount) {
    return {Vector3Lerp(from.translation, to.translation, amount),
            QuaternionSlerp(from.rotation, to.rotation, amount), Vector3Lerp(from.scale, to.scale, amount)};
}
} // namespace

const char *PlayerModel::animationName(PlayerAnimation animation) {
    static constexpr std::array<const char *, size_t(PlayerAnimation::Count)> names{
        "Idle", "Walk", "Run", "Fire", "DodgeSlide", "DodgeForward", "DodgeStanding", "Death", "DeathRifle"};
    return names.at(size_t(animation));
}
std::filesystem::path PlayerModel::assetPath() {
    const auto relative = std::filesystem::path("bandit") / "bandit.glb";
    const auto packaged = std::filesystem::path(GetApplicationDirectory()) / "assets" / relative;
    if (std::filesystem::is_regular_file(packaged))
        return packaged;
    return std::filesystem::path(DEATHWARD_ASSET_DIR) / relative;
}
PlayerModel::~PlayerModel() {
    unload();
}
void PlayerModel::unload() {
    // raylib's UnloadModel deliberately leaves textures owned by the caller.
    std::set<unsigned int> textures;
    for (int i = 0; i < model_.materialCount; ++i)
        for (int map = MATERIAL_MAP_ALBEDO; map <= MATERIAL_MAP_BRDF; ++map) {
            const auto texture = model_.materials[i].maps[map].texture;
            if (texture.id && texture.id != rlGetTextureIdDefault() && textures.insert(texture.id).second)
                UnloadTexture(texture);
        }
    if (model_.meshCount)
        UnloadModel(model_);
    model_ = {};
    clips_ = {};
    pose_.clear();
    worldPose_.clear();
    blendFrom_.clear();
    upperBody_.clear();
    lastRun_ = nullptr;
    lastTime_ = -1;
    attempted_ = false;
    hand_ = finger_ = -1;
}
bool PlayerModel::load(const std::filesystem::path &path) {
    unload();
    attempted_ = true;
    if (!std::filesystem::is_regular_file(path)) {
        TraceLog(LOG_WARNING, "BANDIT: Missing player asset: %s", path.string().c_str());
        return false;
    }
    model_ = LoadModel(path.string().c_str());
    int count = 0;
    ModelAnimation *animations = LoadModelAnimations(path.string().c_str(), &count);
    bool valid =
        model_.meshCount > 0 && model_.boneCount > 0 && model_.bones && model_.bindPose && animations;
    for (int i = 0; valid && i < model_.boneCount; ++i)
        valid = model_.bones[i].parent >= -1 && model_.bones[i].parent < i;
    for (int i = 0; valid && i < count; ++i) {
        const auto &animation = animations[i];
        valid = animation.frameCount >= 2 && IsModelAnimationValid(model_, animation);
        for (int bone = 0; valid && bone < model_.boneCount; ++bone)
            valid = std::strcmp(model_.bones[bone].name, animation.bones[bone].name) == 0;
        if (!valid)
            break;
        for (size_t clip = 0; clip < clips_.size(); ++clip) {
            if (std::strcmp(animation.name, animationName(PlayerAnimation(clip))) != 0)
                continue;
            auto &destination = clips_[clip];
            destination.duration = float(animation.frameCount - 1) * SampleSeconds;
            destination.frames.resize(size_t(animation.frameCount));
            for (int frame = 0; frame < animation.frameCount; ++frame) {
                auto &pose = destination.frames[size_t(frame)];
                pose.resize(size_t(model_.boneCount));
                for (int bone = 0; bone < model_.boneCount; ++bone) {
                    const int parent = model_.bones[bone].parent;
                    const auto &world = animation.framePoses[frame][bone];
                    pose[size_t(bone)] =
                        parent < 0 ? world : localTransform(animation.framePoses[frame][parent], world);
                }
            }
        }
    }
    if (animations)
        UnloadModelAnimations(animations, count);
    for (const auto &clip : clips_)
        valid = valid && !clip.frames.empty();
    for (int i = 0; valid && i < model_.meshCount; ++i)
        valid = model_.meshes[i].boneIds && model_.meshes[i].boneWeights && model_.meshes[i].animVertices;
    if (!valid) {
        TraceLog(LOG_WARNING, "BANDIT: Invalid mesh, skeleton or animation set: %s", path.string().c_str());
        unload();
        attempted_ = true;
        return false;
    }
    const auto bounds = GetModelBoundingBox(model_);
    scale_ = 2.05f / std::max(0.1f, bounds.max.y - bounds.min.y);
    floorOffset_ = 0.025f - bounds.min.y * scale_;
    pose_ = clips_[size_t(PlayerAnimation::Idle)].frames.front();
    worldPose_.resize(pose_.size());
    blendFrom_ = pose_;
    upperBody_.resize(pose_.size());
    for (int i = 0; i < model_.boneCount; ++i) {
        const int parent = model_.bones[i].parent;
        upperBody_[size_t(i)] =
            std::strcmp(model_.bones[i].name, "Spine_01") == 0 || (parent >= 0 && upperBody_[size_t(parent)]);
        if (std::strcmp(model_.bones[i].name, "Hand_R") == 0)
            hand_ = i;
        if (std::strcmp(model_.bones[i].name, "IndexFinger_01_1") == 0)
            finger_ = i;
    }
    for (int material = 0; material < model_.materialCount; ++material) {
        const auto texture = model_.materials[material].maps[MATERIAL_MAP_DIFFUSE].texture;
        if (texture.id && texture.id != rlGetTextureIdDefault())
            SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
    }
    TraceLog(LOG_INFO, "BANDIT: Ready, %d bones and %d animation clips", model_.boneCount,
             int(clips_.size()));
    return true;
}
float PlayerModel::duration(PlayerAnimation animation) const {
    return clips_.at(size_t(animation)).duration;
}
Transform PlayerModel::sample(PlayerAnimation animation, float seconds, int bone, bool loop) const {
    const auto &clip = clips_[size_t(animation)];
    const float time =
        loop ? std::fmod(std::max(0.0f, seconds), clip.duration) : std::clamp(seconds, 0.0f, clip.duration);
    const float frame = time / SampleSeconds;
    const size_t first = std::min(size_t(frame), clip.frames.size() - 1);
    const size_t next = std::min(first + 1, clip.frames.size() - 1);
    return blend(clip.frames[first][size_t(bone)], clip.frames[next][size_t(bone)], frame - float(first));
}
void PlayerModel::update(const Simulation &run, float deathTime) {
    update(run.player, run.stats.duration + deathTime, &run, run.dead, deathTime);
}
void PlayerModel::update(const Player &player, double time, const void *context, bool dead, float deathTime) {
    if (!attempted_)
        load();
    if (!loaded())
        return;
    const bool reset = lastRun_ != context || lastTime_ < 0 || time < lastTime_;
    const float dt = reset ? 0 : float(time - lastTime_);
    lastRun_ = context;
    lastTime_ = time;
    const float speed = length(player.velocity);
    const bool firing = player.shootPose > 0 && !dead;
    PlayerAnimation desired = speed > 3.5f   ? PlayerAnimation::Run
                              : speed > 0.1f ? PlayerAnimation::Walk
                                             : PlayerAnimation::Idle;
    if (firing && speed <= 0.1f)
        desired = PlayerAnimation::Fire;
    if (player.dodge > 0)
        desired = player.dodgeMoving ? PlayerAnimation::DodgeSlide : PlayerAnimation::DodgeStanding;
    if (dead)
        desired = player.shootPose > 0 ? PlayerAnimation::DeathRifle : PlayerAnimation::Death;
    const bool dodge = desired == PlayerAnimation::DodgeSlide || desired == PlayerAnimation::DodgeForward ||
                       desired == PlayerAnimation::DodgeStanding;
    if (reset) {
        current_ = desired;
        phase_ = firePhase_ = firingBlend_ = 0;
        transition_ = 1;
        yaw_ = std::atan2(player.facing.x, player.facing.z);
    } else if (current_ != desired) {
        blendFrom_ = pose_;
        current_ = desired;
        phase_ = 0;
        transition_ = 0;
    }
    const float playback = current_ == PlayerAnimation::Walk  ? std::clamp(speed / 2.2f, 0.5f, 1.8f)
                           : current_ == PlayerAnimation::Run ? std::clamp(speed / 6.0f, 0.5f, 1.8f)
                                                              : 1.0f;
    phase_ += dt * playback;
    if (dodge)
        phase_ = duration(current_) * std::clamp(1 - player.dodge / 0.22f, 0.0f, 1.0f);
    if (dead)
        phase_ = duration(current_) * std::clamp(deathTime / PlayerDeathSeconds, 0.0f, 1.0f);
    transition_ = std::min(1.0f, transition_ + dt / (dodge ? 0.035f : 0.12f));
    firePhase_ = firing ? firePhase_ + dt : 0;
    firingBlend_ = std::clamp(firingBlend_ + (firing ? 1 : -1) * dt / 0.10f, 0.0f, 1.0f);
    const bool movingShot = !dodge && !dead && current_ != PlayerAnimation::Fire && firingBlend_ > 0;
    for (int bone = 0; bone < model_.boneCount; ++bone) {
        Transform target = sample(current_, phase_, bone, !dodge && !dead);
        if (movingShot && upperBody_[size_t(bone)])
            target = blend(target, sample(PlayerAnimation::Fire, firePhase_, bone, true), firingBlend_);
        pose_[size_t(bone)] = reset ? target : blend(blendFrom_[size_t(bone)], target, transition_);
        const int parent = model_.bones[bone].parent;
        worldPose_[size_t(bone)] = parent < 0
                                       ? pose_[size_t(bone)]
                                       : worldTransform(worldPose_[size_t(parent)], pose_[size_t(bone)]);
    }
    Transform *frame = worldPose_.data();
    ModelAnimation mixed{};
    mixed.boneCount = model_.boneCount;
    mixed.frameCount = 1;
    mixed.bones = model_.bones;
    mixed.framePoses = &frame;
    UpdateModelAnimation(model_, mixed, 0);
    const float targetYaw = std::atan2(player.facing.x, player.facing.z);
    yaw_ += std::remainder(targetYaw - yaw_, 2 * Pi) * (firing || dodge ? 1.0f : 1 - std::exp(-18 * dt));
}
Vector3 PlayerModel::worldPoint(Vector3 point, const Player &player) const {
    return add({player.position.x, player.position.y - .85f + floorOffset_, player.position.z},
               rotateY(mul(point, scale_), yaw_));
}
void PlayerModel::draw(const Simulation &run) const {
    draw(run.player, run.dead);
}
void PlayerModel::draw(const Player &player, bool dead) const {
    if (!loaded())
        return;
    DrawModelEx(model_, {player.position.x, player.position.y - .85f + floorOffset_, player.position.z},
                {0, 1, 0}, yaw_ * RAD2DEG, {scale_, scale_, scale_},
                player.hurt > 0 ? Color{255, 155, 135, 255} : WHITE);
    if (hand_ < 0 || dead)
        return;
    const Vector3 hand = worldPoint(worldPose_[size_t(hand_)].translation, player);
    Vector3 forward = player.shootPose > 0 ? unit(sub(player.aim, player.position))
                      : finger_ >= 0
                          ? unit(sub(worldPoint(worldPose_[size_t(finger_)].translation, player), hand))
                          : Vector3{0, -1, 0};
    const Vector3 muzzle = add(hand, mul(forward, 0.48f));
    DrawCylinderEx(hand, muzzle, 0.055f, 0.045f, 6, Color{160, 167, 169, 255});
    DrawSphereEx(add(hand, mul(forward, 0.12f)), 0.09f, 4, 6, Color{75, 78, 80, 255});
    if (player.fireCooldown > 0.24f)
        DrawSphereEx(muzzle, 0.12f, 4, 6, Color{255, 205, 111, 255});
}
} // namespace dw
