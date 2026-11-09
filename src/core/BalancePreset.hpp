#pragma once
#include <filesystem>
#include <string>

namespace dw {
// Versioned configuration, not player inventory or a gameplay save. D01 exposes
// Speed, camera defaults and staged map settings; native geometry is not claimed.
struct BalancePreset {
    static constexpr float ReferenceSpeed = 1, MinSpeed = .1f, MaxSpeed = 2;
    static constexpr float ReferenceZoom = 160, MinZoom = 67, MaxZoom = 285;
    float playerSpeed = ReferenceSpeed;
    std::string mechanicsFingerprint;
    float roomSizeScale = 1;
    int roomMinHalfTiles = 0, roomMaxHalfTiles = 0; // 0/0 uses the selected pacing profile.
    float routeLengthScale = 1;
    float defaultZoomPercent = ReferenceZoom;
    bool custom() const { return playerSpeed != ReferenceSpeed || roomSizeScale != 1 || roomMinHalfTiles != 0 || routeLengthScale != 1 || defaultZoomPercent != ReferenceZoom; }
    void validate() const;
    std::string json() const;
    std::string revision() const;
    void save(const std::filesystem::path &path) const;
    static BalancePreset load(const std::filesystem::path &path, const std::string &mechanicsFingerprint);
};
} // namespace dw
