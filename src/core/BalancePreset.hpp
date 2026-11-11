#pragma once
#include <filesystem>
#include <string>

namespace dw {
// Versioned player/shooting/view configuration and staged map settings.
// This is not player inventory, a gameplay save or certification of native parity.
struct BalancePreset {
    static constexpr float ReferenceSpeed = 1, MinSpeed = .1f, MaxSpeed = 2;
    static constexpr float ReferenceZoom = 160, MinZoom = 67, MaxZoom = 285;
    static constexpr float ReferenceTears = 30.f/11.f, MinTears = .1f, MaxTears = 10;
    static constexpr float ReferenceShotSpeed = 1, MinShotSpeed = .1f, MaxShotSpeed = 3;
    static constexpr float ReferenceRange = 6.5f, MinRange = .5f, MaxRange = 20;
    float playerSpeed = ReferenceSpeed;
    std::string mechanicsFingerprint;
    float roomSizeScale = 1;
    int roomMinHalfTiles = 0, roomMaxHalfTiles = 0; // 0/0 uses the selected pacing profile.
    float routeLengthScale = 1;
    float defaultZoomPercent = ReferenceZoom;
    float tearsPerSecond = ReferenceTears, shotSpeed = ReferenceShotSpeed, rangeTiles = ReferenceRange;
    bool custom() const { return playerSpeed != ReferenceSpeed || roomSizeScale != 1 || roomMinHalfTiles != 0 || routeLengthScale != 1 || defaultZoomPercent != ReferenceZoom || tearsPerSecond != ReferenceTears || shotSpeed != ReferenceShotSpeed || rangeTiles != ReferenceRange; }
    void validate() const;
    std::string json() const;
    std::string revision() const;
    void save(const std::filesystem::path &path) const;
    static BalancePreset load(const std::filesystem::path &path, const std::string &mechanicsFingerprint);
};
} // namespace dw
