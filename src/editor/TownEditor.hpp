#pragma once
#include "render/PostProcess.hpp"
#include "render/TownScene.hpp"
#include "world/TownNavigation.hpp"
#include <deque>

namespace dw {
class TownEditor {
  public:
    bool active = false, quitRequested = false, saved = false;
    std::string status;
    Camera3D camera{};
    bool open(const std::filesystem::path &directory, Camera3D view);
    void update(float dt);
    void draw();
    void requestClose(bool quit = false);
    void unload() {
        scene_.unload();
        postProcess_.unload();
    }
    bool dirty() const {
        return revision_ != savedRevision_;
    }
    const TownDocument &document() const {
        return document_;
    }
    const TownNavigation &navigation() const {
        return navigation_;
    }
    std::optional<size_t> selection() const {
        return selected_;
    }
    void select(std::optional<size_t> index);
    void translate(Vector3 delta);
    void rotate(Vector3 axis, float degrees);
    void scale(Vector3 factors);
    void duplicate();
    void remove();
    void addAsset(size_t asset);
    void undo();
    void redo();
    bool save();
    bool reload();
    void focusSelection();
    void setMotion(ObjectMotion motion);
    void setPreviewPlaying(bool playing);
    void resetPreview();
    bool previewPlaying() const {
        return previewPlaying_;
    }
    const ObjectAnimationSystem &animationPreview() const {
        return preview_;
    }

  private:
    struct Snapshot {
        TownDocument document;
        Vector3 spawn, mission;
        std::optional<size_t> selected;
        uint64_t revision;
    };
    enum class Tool { Move, Rotate, Scale };
    TownScene scene_;
    PostProcess postProcess_;
    TownDocument document_;
    TownNavigation navigation_;
    TownNavigation previewNavigation_;
    ObjectAnimationSystem preview_;
    bool animationTab_ = false, previewPlaying_ = false;
    uint64_t navigationRevision_ = 0;
    std::filesystem::path directory_;
    std::optional<size_t> selected_, paletteSelection_;
    std::deque<Snapshot> undo_, redo_;
    uint64_t revision_ = 0, savedRevision_ = 0, nextRevision_ = 0;
    Tool tool_ = Tool::Move;
    bool palette_ = false, searchFocus_ = false, selectText_ = false, snap_ = true, showGrid_ = true,
         showNavigation_ = false;
    bool closePrompt_ = false, reloadPrompt_ = false, closingWindow_ = false;
    bool orbiting_ = false, panning_ = false, dragChanged_ = false;
    int scroll_ = 0, field_ = -1, dragAxis_ = -1, marker_ = 0;
    std::string search_, fieldText_;
    Matrix dragTransform_{};
    Vector2 previousMouse_{}, dragMouse_{};
    float yaw_ = 0, pitch_ = 0, radius_ = 40, scaleX_ = 1, scaleY_ = 1;
    Snapshot snapshot() const;
    void restore(Snapshot state);
    void remember();
    void sync();
    void updateView();
    bool overUI(Vector2 pixel) const;
    Vector2 uiMouse() const;
    Vector3 pivot() const;
    Vector3 values(int group) const;
    void commitField();
    void closeNow();
    void label(const std::string &text, float x, float y, int size, Color color, float width = 1000) const;
    bool button(const std::string &text, Rectangle r, bool selected = false, bool enabled = true) const;
    void panel(Rectangle r, Color color) const;
    void drawUI();
    void drawAnimationUI();
};
} // namespace dw
