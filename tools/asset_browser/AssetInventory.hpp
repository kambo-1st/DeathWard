#pragma once
#include <filesystem>
#include <string>
#include <vector>
namespace dw::assetBrowser {
namespace fs = std::filesystem;
enum class Kind { Model, Image, Audio, Font, Text, Other };
struct Asset {
    fs::path absolute;
    std::string relative, folder, extension, search;
    Kind kind;
    uintmax_t bytes = 0;
};
struct Inventory {
    fs::path root;
    std::vector<Asset> assets;
    std::vector<std::string> errors;
};
std::string lower(std::string text);
const char *kindName(Kind kind);
Kind classify(const std::string &extension);
Inventory scan(const fs::path &root);
std::string jsonString(const std::string &text);
} // namespace dw::assetBrowser
