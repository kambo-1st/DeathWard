#include "AssetInventory.hpp"
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <stdexcept>
namespace dw::assetBrowser {
std::string lower(std::string s) {
    for (char &c : s)
        c = char(std::tolower(static_cast<unsigned char>(c)));
    return s;
}
const char *kindName(Kind k) {
    switch (k) {
    case Kind::Model:
        return "Models";
    case Kind::Image:
        return "Images";
    case Kind::Audio:
        return "Audio";
    case Kind::Font:
        return "Fonts";
    case Kind::Text:
        return "Text";
    default:
        return "Other";
    }
}
Kind classify(const std::string &e) {
    auto in = [&](const char *list) { return std::string(list).find("|" + e + "|") != std::string::npos; };
    if (in("|.fbx|.glb|.gltf|.obj|.iqm|.m3d|.vox|"))
        return Kind::Model;
    if (in("|.png|.jpg|.jpeg|.bmp|.tga|.gif|.qoi|.hdr|.dds|.ktx|.pvr|.astc|.psd|.svg|"))
        return Kind::Image;
    if (in("|.wav|.ogg|.mp3|.flac|.xm|.mod|.aiff|"))
        return Kind::Audio;
    if (in("|.ttf|.otf|.fnt|"))
        return Kind::Font;
    if (in("|.txt|.md|.json|.cfg|.mechanics|.meta|.prefab|.asset|.mat|.anim|.unity|.labels|.scene|.particles|"
           ".attachments|.catalog|.animals|.cinematic|.identifier|.xml|.csv|.yaml|.yml|.glsl|.vs|.fs|"))
        return Kind::Text;
    return Kind::Other;
}
Inventory scan(const fs::path &path) {
    Inventory result;
    result.root = fs::absolute(path).lexically_normal();
    if (!fs::is_directory(result.root))
        throw std::runtime_error("Asset directory does not exist: " + result.root.string());
    std::error_code ec;
    fs::recursive_directory_iterator it(result.root, fs::directory_options::skip_permission_denied, ec), end;
    if (ec)
        result.errors.push_back(ec.message());
    for (; it != end; it.increment(ec)) {
        if (ec) {
            result.errors.push_back(ec.message());
            ec.clear();
            continue;
        }
        if (!it->is_regular_file(ec)) {
            ec.clear();
            continue;
        }
        Asset a;
        a.absolute = it->path();
        a.relative = a.absolute.lexically_relative(result.root).generic_string();
        a.folder = a.absolute.parent_path().lexically_relative(result.root).generic_string();
        if (a.folder == ".")
            a.folder.clear();
        a.extension = lower(a.absolute.extension().string());
        a.kind = classify(a.extension);
        a.bytes = it->file_size(ec);
        if (ec) {
            a.bytes = 0;
            result.errors.push_back(a.relative + ": " + ec.message());
            ec.clear();
        }
        a.search = lower(a.relative);
        result.assets.push_back(std::move(a));
    }
    std::sort(result.assets.begin(), result.assets.end(),
              [](const auto &a, const auto &b) { return a.relative < b.relative; });
    return result;
}
std::string jsonString(const std::string &s) {
    std::ostringstream out;
    out << '"';
    for (unsigned char c : s) {
        switch (c) {
        case '"':
            out << "\\\"";
            break;
        case '\\':
            out << "\\\\";
            break;
        case '\n':
            out << "\\n";
            break;
        case '\r':
            out << "\\r";
            break;
        case '\t':
            out << "\\t";
            break;
        default:
            if (c < 32)
                out << "\\u" << std::hex << std::setw(4) << std::setfill('0') << int(c) << std::dec;
            else
                out << c;
        }
    }
    out << '"';
    return out.str();
}
} // namespace dw::assetBrowser
