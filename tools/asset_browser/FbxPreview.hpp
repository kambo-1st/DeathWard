#pragma once
#include "raylib.h"
#include "third_party/ufbx.h"
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>
namespace dw::assetBrowser {
class FbxPreview {
    struct Part {
        Mesh mesh{};
        Material material{};
        uint32_t node = 0;
        std::vector<uint32_t> corners;
    };
    std::vector<Part> parts;
    std::vector<Texture2D> textures;
    ufbx_scene *scene = nullptr;
    void updatePart(Part &, const ufbx_scene *, bool upload);

  public:
    BoundingBox bounds{};
    size_t triangleCount = 0;
    std::vector<std::string> animations;
    std::string notes;
    ~FbxPreview() { clear(); }
    void clear();
    bool load(const std::filesystem::path &,
              const std::unordered_map<std::string, std::filesystem::path> &images);
    void animate(size_t clip, double time);
    int sections() const { return int(parts.size()); }
    BoundingBox sectionBounds(int section) const {
        return section >= 0 && section < int(parts.size()) ? GetMeshBoundingBox(parts[section].mesh) : bounds;
    }
    void draw(Shader shader, bool wire, int section = -1) const;
};
} // namespace dw::assetBrowser
