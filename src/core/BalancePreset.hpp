#pragma once
#include <filesystem>
#include <string>

namespace dw {
// Versioned configuration, not player inventory or a gameplay save. D01 exposes
// only the already enabled Speed consumer; later deliveries extend this schema.
struct BalancePreset {
    static constexpr float ReferenceSpeed = 1, MinSpeed = .1f, MaxSpeed = 2;
    float playerSpeed = ReferenceSpeed;
    std::string mechanicsFingerprint;
    bool custom() const { return playerSpeed != ReferenceSpeed; }
    void validate() const;
    std::string json() const;
    std::string revision() const;
    void save(const std::filesystem::path &path) const;
    static BalancePreset load(const std::filesystem::path &path, const std::string &mechanicsFingerprint);
};
} // namespace dw
