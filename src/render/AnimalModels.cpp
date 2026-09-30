#include "render/AnimalModels.hpp"
namespace dw {
std::filesystem::path AnimalModels::assetDirectory() {
#ifdef __EMSCRIPTEN__
    return "/assets/animals";
#else
    const auto source = std::filesystem::path(DEATHWARD_ASSET_DIR) / "animals";
    if (std::filesystem::is_directory(source))
        return source;
    return std::filesystem::path(GetApplicationDirectory()) / "assets/animals";
#endif
}
void AnimalModels::unload() { for (auto &model : models_) model.unload(); }
bool AnimalModels::loaded(AnimalKind kind) const { return models_.at(size_t(kind)).loaded(); }
bool AnimalModels::load(AnimalKind kind, const std::filesystem::path &path) { return models_.at(size_t(kind)).load(path); }
const Model &AnimalModels::model(AnimalKind kind) const { return models_.at(size_t(kind)).model(); }
const std::vector<Transform> &AnimalModels::bonePose(AnimalKind kind) const { return models_.at(size_t(kind)).bonePose(); }
const std::vector<std::string> &AnimalModels::clipNames(AnimalKind kind) {
    auto &model = models_.at(size_t(kind));
    if (!model.attempted()) load(kind, assetDirectory() / (std::string(animalName(kind)) + ".glb"));
    return model.clipNames();
}
float AnimalModels::clipDuration(AnimalKind kind, const std::string &name) {
    clipNames(kind);
    return models_.at(size_t(kind)).clipDuration(name);
}
void AnimalModels::prepare(const Animals &animals) {
    for (const auto &animal : animals.residents())
        if (!models_[size_t(animal.kind)].attempted())
            load(animal.kind, assetDirectory() / (std::string(animalName(animal.kind)) + ".glb"));
}
bool AnimalModels::pose(const Animal &animal) {
    auto &model = models_[size_t(animal.kind)];
    if (!model.attempted()) load(animal.kind, assetDirectory() / (std::string(animalName(animal.kind)) + ".glb"));
    return animal.activity.stationary
        ? model.poseSequence(animal.phase, animal.activity.clips, animal.activity.speed)
        : model.pose(animal.phase, animal.walking, animal.eating);
}
Box AnimalModels::bounds(const Animal &animal) {
    if (pose(animal)) return models_[size_t(animal.kind)].bounds(animal.position, animal.facing, animal.scale);
    const float r = animalRadius(animal.kind) * animal.scale;
    return {add(animal.position, {-r, 0, -r}), add(animal.position, {r, r * 2, r})};
}
void AnimalModels::draw(const Animals &animals, Shader shader, Texture2D shadowMap) {
    for (const auto &animal : animals.residents()) draw(animal, shader, shadowMap);
}
void AnimalModels::draw(const Animal &animal, Shader shader, Texture2D shadowMap) {
    if (pose(animal)) models_[size_t(animal.kind)].draw(animal.position, animal.facing, animal.scale, shader, shadowMap);
}
}
