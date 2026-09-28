#pragma once
#include "render/PlayerOcclusion.hpp"
#include "world/Dungeon.hpp"
#include <filesystem>

namespace dw {
enum class WesternAsset {
    Crate,
    Barrel,
    Sacks,
    Woodpile,
    Lantern,
    Coffin,
    Cart,
    Fence,
    Saloon,
    Jail,
    Church,
    Station,
    WaterTower,
    Well,
    Rail,
    Ground,
    RockA,
    RockB,
    CactusA,
    CactusB,
    Floor,
    CliffWall,
    CliffPillar,
    CliffCap,
    Sandstone,
    Count
};
struct WesternPlacement {
    WesternAsset asset;
    Box bounds;
    float yaw = 0;
    bool exterior = false;
};

// Static, instanced scenery; generated gameplay geometry remains authoritative.
class WesternScene {
  public:
    WesternScene() = default;
    ~WesternScene();
    WesternScene(const WesternScene &) = delete;
    WesternScene &operator=(const WesternScene &) = delete;
    bool load(const std::filesystem::path &directory = assetDirectory());
    void unload();
    void prepare(const Arena &arena);
    void draw(Vector3 focus);
    void drawGlass();
    void setPlayerOcclusion(const Camera3D &camera, Vector3 player, bool enabled = true) {
        occlusion_.set(camera, player);
        occlusion_.enabled = enabled;
    }
    void drawOccluders();
    bool loaded() const {
        return model_.meshCount > 0;
    }
    bool terrainReady() const {
        return !terrain_.empty();
    }
    const auto &terrainChunks() const {
        return terrain_;
    }
    const std::vector<WesternPlacement> &placements() const {
        return placements_;
    }
    const Model &model() const {
        return model_;
    }
    Box assetBounds(WesternAsset asset) const {
        return assets_[size_t(asset)].bounds;
    }
    static std::filesystem::path assetDirectory();
    static Matrix placementTransform(Box source, const WesternPlacement &placement);

  private:
    struct Asset {
        int firstMesh = 0, meshCount = 0;
        Box bounds{};
    };
    Model model_{};
    Shader shader_{};
    std::array<Asset, size_t(WesternAsset::Count)> assets_{};
    std::array<std::vector<Matrix>, size_t(WesternAsset::Count)> batches_;
    std::vector<WesternPlacement> placements_;
    std::vector<const WesternPlacement *> occluders_;
    const Arena *lastArena_ = nullptr;
    uint64_t lastSeed_ = 0;
    MissionTheme lastTheme_ = MissionTheme::Mine;
    bool attempted_ = false;
    PlayerOcclusion occlusion_;
    struct TerrainChunk {
        Mesh mesh{};
        Box bounds{};
        std::vector<std::array<Vector3, 2>> floorOutline;
        bool rock = false, faded = false;
    };
    std::vector<TerrainChunk> terrain_;
    Mesh terrainBase_{};
    std::shared_ptr<const CanyonTerrain> terrainField_;
    std::vector<int> terrainSections_;
    Shader terrainShader_{};
    Material terrainMaterial_{};
    Texture2D heightTexture_{};
    void clearTerrain();
    void generateCanyon(const Arena &arena);
    void drawTerrain(Vector3 focus);
    void drawTerrainOutlines();
    void generate(const Arena &arena);
    void drawBatches(bool transparent);
};
} // namespace dw
