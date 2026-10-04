#include "editor/TownEditor.hpp"
#include "raymath.h"
#include "rlgl.h"
#include <stdexcept>

namespace dw {
namespace {
constexpr Color Text{232,230,217,255}, Muted{152,165,164,255}, Accent{232,174,96,255};
constexpr Color Allowed{99,212,181,255}, Blocked{237,100,95,255};
float lineDistance(Vector2 p, Vector2 a, Vector2 b) {
    const auto d = Vector2Subtract(b, a);
    const float t = std::clamp(Vector2DotProduct(Vector2Subtract(p, a), d) /
                               std::max(1.f, Vector2LengthSqr(d)), 0.f, 1.f);
    return Vector2Distance(p, Vector2Add(a, Vector2Scale(d, t)));
}
} // namespace
void TownEditor::cancelWalkDrawing() {
    drawingWalkArea_ = movingWalkPoint_ = false;
    walkDraft_.clear();
}
void TownEditor::beginWalkArea(bool blocked) {
    commitField(); searchFocus_ = false;
    navigationTab_ = true;
    animalTab_ = characterTab_ = palette_ = false;
    select({}); resetPreview(); cancelWalkDrawing();
    selectedWalkArea_.reset(); selectedWalkPoint_.reset();
    drawingWalkArea_ = true; drawingBlocked_ = blocked; marker_ = 0;
    status = "Click boundary points, then Finish area or Enter. Escape cancels; Backspace removes the last point.";
}
bool TownEditor::addWalkArea(bool blocked, std::vector<Vector3> points) {
    try {
        if (document_.walkAreas.size() >= 64) throw std::runtime_error("The map already has 64 walk areas.");
        TownWalkArea area{document_.nextWalkAreaId(), blocked, std::move(points)};
        area.validate();
        remember();
        document_.walkAreas.push_back(std::move(area));
        selectedWalkArea_ = document_.walkAreas.size() - 1;
        selectedWalkPoint_.reset();
        cancelWalkDrawing(); resetPreview();
        status = "Area added. Rebuild preview to check the paths; Save applies it to gameplay.";
        return true;
    } catch (const std::exception &e) { status = e.what(); return false; }
}
void TownEditor::finishWalkArea() {
    if (drawingWalkArea_) addWalkArea(drawingBlocked_, walkDraft_);
}
bool TownEditor::moveWalkAreaPoint(size_t area, size_t point, Vector3 position) {
    try {
        auto changed = document_.walkAreas.at(area);
        changed.points.at(point) = position;
        changed.validate();
        remember();
        document_.walkAreas[area] = std::move(changed);
        movingWalkPoint_ = false;
        resetPreview();
        status = "Boundary point moved. Rebuild preview or Save to update paths.";
        return true;
    } catch (const std::exception &e) { status = e.what(); return false; }
}
void TownEditor::removeWalkArea() {
    if (!selectedWalkArea_ || drawingWalkArea_) return;
    remember();
    document_.walkAreas.erase(document_.walkAreas.begin() + std::ptrdiff_t(*selectedWalkArea_));
    selectedWalkArea_.reset(); selectedWalkPoint_.reset();
    cancelWalkDrawing(); resetPreview();
    status = "Area removed. Rebuild preview or Save to update paths.";
}
bool TownEditor::rebuildWalkPreview() {
    try {
        auto next = navigation_;
        next.bake(document_, scene_.model());
        previewNavigation_ = std::move(next);
        walkPreviewValid_ = showNavigation_ = true;
        status = "Paths rebuilt for preview. Save applies the boundaries to gameplay.";
        return true;
    } catch (const std::exception &e) {
        walkPreviewValid_ = false;
        status = std::string("Cannot build paths: ") + e.what();
        return false;
    }
}
std::optional<Vector3> TownEditor::walkAreaGroundPoint(Vector2 pixel) const {
    const auto ray = GetScreenToWorldRay(pixel, camera);
    // Pick geometry, not the restricted navigation grid: boundaries must remain
    // editable on both sides, including ground excluded by an earlier save.
    if (const auto selected = scene_.pick(ray)) {
        const auto &instance = document_.instances[*selected];
        const auto &asset = document_.assets[instance.asset];
        RayCollision closest{}; closest.distance = 1e9f;
        for (int m = asset.first; m < asset.first + asset.count; ++m) {
            const auto hit = GetRayCollisionMesh(ray, scene_.model().meshes[m], instance.transform);
            if (hit.hit && hit.distance < closest.distance) closest = hit;
        }
        if (closest.hit) return closest.point;
    }
    if (ray.direction.y < -.001f) {
        const float t = (navigation_.spawn.y - ray.position.y) / ray.direction.y;
        if (t > 0) return add(ray.position, mul(ray.direction, t));
    }
    return {};
}
void TownEditor::walkAreaClick(Vector2 pixel) {
    if (drawingWalkArea_) {
        if (walkDraft_.size() >= 3 && Vector2Distance(pixel, GetWorldToScreen(walkDraft_.front(), camera)) < 14) {
            finishWalkArea(); return;
        }
        if (walkDraft_.size() >= 128) { status = "Finish this area before adding more points."; return; }
        if (const auto point = walkAreaGroundPoint(pixel)) walkDraft_.push_back(*point);
        return;
    }
    if (movingWalkPoint_ && selectedWalkArea_ && selectedWalkPoint_) {
        if (const auto point = walkAreaGroundPoint(pixel)) moveWalkAreaPoint(*selectedWalkArea_, *selectedWalkPoint_, *point);
        return;
    }
    float nearest = 16;
    for (size_t a = 0; a < document_.walkAreas.size(); ++a) {
        const auto &points = document_.walkAreas[a].points;
        for (size_t p = 0; p < points.size(); ++p) {
            const float d = Vector2Distance(pixel, GetWorldToScreen(points[p], camera));
            if (d < nearest) { nearest = d; selectedWalkArea_ = a; selectedWalkPoint_ = p; }
        }
    }
    if (nearest < 16) return;
    for (size_t a = 0; a < document_.walkAreas.size(); ++a) {
        const auto &points = document_.walkAreas[a].points;
        for (size_t p = 0; p < points.size(); ++p) {
            const float d = lineDistance(pixel, GetWorldToScreen(points[p], camera),
                                         GetWorldToScreen(points[(p + 1) % points.size()], camera));
            if (d < nearest) { nearest = d; selectedWalkArea_ = a; selectedWalkPoint_.reset(); }
        }
    }
}
void TownEditor::drawWalkAreas() {
    BeginScissorMode(int(272 * scaleX_), int(86 * scaleY_), int(840 * scaleX_), int(762 * scaleY_));
    BeginMode3D(camera);
    rlDrawRenderBatchActive(); rlDisableDepthTest();
    auto outline = [&](const auto &points, Color color, bool closed) {
        for (size_t i = 0; i < points.size(); ++i) {
            if (i + 1 < points.size() || closed)
                DrawLine3D(points[i], points[(i + 1) % points.size()], color);
        }
    };
    for (const auto &area : document_.walkAreas) outline(area.points, area.blocked ? Blocked : Allowed, true);
    if (drawingWalkArea_) outline(walkDraft_, Accent, false);
    rlDrawRenderBatchActive(); rlEnableDepthTest(); EndMode3D();
    auto handles = [&](const auto &points, Color color) {
        for (size_t i = 0; i < points.size(); ++i) {
            if (Vector3DotProduct(sub(points[i], camera.position), sub(camera.target, camera.position)) <= 0) continue;
            const auto p = GetWorldToScreen(points[i], camera);
            DrawCircleV(p, 6 * std::min(scaleX_, scaleY_), color);
            DrawText(std::to_string(i + 1).c_str(), int(p.x + 9), int(p.y - 8), 15, Text);
        }
    };
    if (drawingWalkArea_) handles(walkDraft_, Accent);
    else if (selectedWalkArea_) {
        const auto &area = document_.walkAreas[*selectedWalkArea_];
        handles(area.points, area.blocked ? Blocked : Allowed);
    }
    EndScissorMode();
}
void TownEditor::drawWalkAreaUI() {
    label("WALKABLE AREAS", 1132, 108, 13, Accent);
    if (button("Draw allowed area", {1132, 137, 286, 31}, drawingWalkArea_ && !drawingBlocked_)) beginWalkArea(false);
    if (button("Draw blocked area", {1132, 176, 286, 31}, drawingWalkArea_ && drawingBlocked_)) beginWalkArea(true);
    label("Green: stay inside. Red: keep out.", 1132, 222, 13, Muted, 284);
    label("Existing walls and rocks still block.", 1132, 244, 13, Muted, 284);
    if (button("Finish area", {1132, 273, 137, 31}, false, drawingWalkArea_ && walkDraft_.size() >= 3)) finishWalkArea();
    if (button("Undo point", {1281, 273, 137, 31}, false, drawingWalkArea_ && !walkDraft_.empty())) walkDraft_.pop_back();
    if (button("Cancel drawing", {1132, 312, 137, 31}, false, drawingWalkArea_ || movingWalkPoint_)) cancelWalkDrawing();
    if (button(showNavigation_ ? "Paths: ON" : "Paths: OFF", {1281, 312, 137, 31}, showNavigation_)) showNavigation_ = !showNavigation_;
    label("AREAS / scroll to browse", 1132, 360, 12, Accent);
    if (!closePrompt_ && !reloadPrompt_ && CheckCollisionPointRec(uiMouse(), {1132, 383, 286, 140}))
        walkAreaScroll_ -= int(GetMouseWheelMoveV().y * 2);
    walkAreaScroll_ = std::clamp(walkAreaScroll_, 0, std::max(0, int(document_.walkAreas.size()) - 5));
    for (int row = 0; row < 5 && size_t(row + walkAreaScroll_) < document_.walkAreas.size(); ++row) {
        const auto i = size_t(row + walkAreaScroll_);
        const auto &area = document_.walkAreas[i];
        if (button(std::string(area.blocked ? "Block " : "Allow ") + area.id,
                   {1132, 383 + float(row) * 28, 286, 26}, selectedWalkArea_ == i)) {
            cancelWalkDrawing(); selectedWalkArea_ = i; selectedWalkPoint_.reset(); walkPointScroll_ = 0;
        }
    }
    if (document_.walkAreas.empty()) label("No limits; use the existing ground.", 1132, 395, 13, Muted, 284);
    label(drawingWalkArea_ ? std::to_string(walkDraft_.size()) + " points / Enter to finish" : "POINTS / click a handle or row", 1132, 537, 12, Accent);
    if (selectedWalkArea_ && !drawingWalkArea_) {
        const auto &points = document_.walkAreas[*selectedWalkArea_].points;
        if (!closePrompt_ && !reloadPrompt_ && CheckCollisionPointRec(uiMouse(), {1132, 560, 286, 112}))
            walkPointScroll_ -= int(GetMouseWheelMoveV().y * 2);
        walkPointScroll_ = std::clamp(walkPointScroll_, 0, std::max(0, int(points.size()) - 4));
        for (int row = 0; row < 4 && size_t(row + walkPointScroll_) < points.size(); ++row) {
            const auto p = size_t(row + walkPointScroll_);
            if (button("Point " + std::to_string(p + 1), {1132, 560 + float(row) * 28, 286, 26}, selectedWalkPoint_ == p))
                selectedWalkPoint_ = p;
        }
    }
    if (button("Move point", {1132, 690, 137, 31}, movingWalkPoint_, selectedWalkPoint_.has_value())) {
        movingWalkPoint_ = true; status = "Click the new boundary position. Escape cancels.";
    }
    const bool canRemovePoint = selectedWalkArea_ && selectedWalkPoint_ && document_.walkAreas[*selectedWalkArea_].points.size() > 3;
    if (button("Remove point", {1281, 690, 137, 31}, false, canRemovePoint)) {
        auto area = document_.walkAreas[*selectedWalkArea_];
        area.points.erase(area.points.begin() + std::ptrdiff_t(*selectedWalkPoint_));
        try {
            area.validate(); remember();
            document_.walkAreas[*selectedWalkArea_] = std::move(area);
            selectedWalkPoint_.reset(); movingWalkPoint_ = false; resetPreview();
            status = "Boundary point removed. Rebuild preview or Save to update paths.";
        } catch (const std::exception &e) { status = e.what(); }
    }
    if (button("Focus area", {1132, 729, 137, 31}, false, selectedWalkArea_.has_value())) focusSelection();
    if (button("Delete area", {1281, 729, 137, 31}, false, selectedWalkArea_.has_value())) removeWalkArea();
    if (button("Rebuild path preview", {1132, 782, 286, 31}, walkPreviewValid_, !drawingWalkArea_)) rebuildWalkPreview();
    label("Save applies these limits to the map.", 1132, 826, 12, Muted, 284);
}
} // namespace dw
