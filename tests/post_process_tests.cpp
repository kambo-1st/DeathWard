#include "render/PostProcess.hpp"
#include "rlgl.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace {
void check(bool condition, const char *message) {
    if (!condition)
        throw std::runtime_error(message);
}
void verifyOutlines(dw::PostProcess &post) {
    const int w = GetScreenWidth(), h = GetScreenHeight();
    const Camera3D camera{{0, 0, 8}, {0, 0, 0}, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
    auto body = [] { DrawSphereEx({0, 0, 0}, 1, 12, 16, {70, 140, 190, 255}); };
    for (int cover : {0, 1, 2, 3}) {
        auto render = [&](bool outline) {
            BeginDrawing();
            post.begin({40, 45, 50, 255});
            BeginMode3D(camera);
            if (cover == 1 || cover == 3)
                DrawCube({0, 0, 2}, 4, 4, .2f, {85, 90, 95, 255});
            if (cover == 2)
                DrawCube({-1.5f, 0, 2}, 3, 4, .2f, {85, 90, 95, 255});
            body();
            EndMode3D();
            post.end();
            if (outline)
                post.outlineOccluded(camera, [&] {
                    if (cover != 3)
                        body();
                });
            DrawRectangle(2, 2, 25, 20, GREEN);
            rlDrawRenderBatchActive();
            auto frame = LoadImageFromScreen();
            EndDrawing();
            return frame;
        };
        auto before = render(false), after = render(true);
        int left = 0, right = 0, interior = 0;
        for (int y = 0; y < h; ++y)
            for (int x = 0; x < w; ++x) {
                const auto a = GetImageColor(before, x, y), b = GetImageColor(after, x, y);
                if (std::abs(int(a.r) - b.r) + std::abs(int(a.g) - b.g) + std::abs(int(a.b) - b.b) <= 3)
                    continue;
                (x < w / 2 ? left : right)++;
                interior += std::abs(x - w / 2) < 12 && std::abs(y - h / 2) < 12;
            }
        if (cover == 0 || cover == 3)
            check(left + right == 0, "visible enemies and an empty next frame have no outline");
        if (cover == 1)
            check(left > 100 && right > 100, "fully hidden enemies get a complete silhouette outline");
        if (cover == 2)
            check(left > 100 && right < 10, "only the occluded silhouette edge receives an outline");
        check(interior == 0, "the silhouette remains hollow instead of filling the enemy body");
        const auto ui = GetImageColor(after, 10, 10);
        check(ui.r == GREEN.r && ui.g == GREEN.g && ui.b == GREEN.b,
              "UI remains above the enemy outline composite");
        UnloadImage(before);
        UnloadImage(after);
    }
}
void verify(dw::PostProcess &post) {
    const int w = GetScreenWidth(), h = GetScreenHeight();
    BeginDrawing();
    post.begin(BLACK);
    check(post.ready(), "HDR targets and shaders must load");
    DrawRectangle(0, 0, w / 2, h / 2, {40, 40, 40, 255});
    DrawRectangle(w / 2, 0, w - w / 2, h / 2, {205, 205, 205, 255});
    DrawRectangle(0, h / 2, w / 2, h - h / 2, {25, 40, 190, 255});
    DrawRectangle(w / 2, h / 2, w - w / 2, h - h / 2, {20, 150, 30, 255});
    post.end();
    const Color ui{20, 210, 95, 255};
    DrawRectangle(2, 2, 25, 20, ui);
    rlDrawRenderBatchActive();
    auto frame = LoadImageFromScreen();
    EndDrawing();
    auto shadow = GetImageColor(frame, w / 4, h / 4), highlight = GetImageColor(frame, w * 3 / 4, h / 4);
    auto blue = GetImageColor(frame, w / 4, h * 3 / 4), green = GetImageColor(frame, w * 3 / 4, h * 3 / 4);
    const auto overlay = GetImageColor(frame, 10, 10);
    check(shadow.b > shadow.g + 8 && shadow.r > shadow.g + 3, "neutral shadows receive the plum palette");
    check(highlight.r > highlight.b + 5 && highlight.g > highlight.b, "highlights receive a warm tint");
    check(blue.b > blue.r + 40 && green.g > green.r + 40,
          "framebuffer orientation and material colors survive compositing");
    check(overlay.r == ui.r && overlay.g == ui.g && overlay.b == ui.b,
          "UI drawn afterward keeps its exact color and coordinates");
    UnloadImage(frame);

    BeginDrawing();
    post.begin({16, 16, 16, 255});
    const int cx = w / 4, cy = h / 4;
    DrawRectangle(cx - 8, cy - 8, 16, 16, WHITE);
    post.end();
    frame = LoadImageFromScreen();
    EndDrawing();
    const auto near = GetImageColor(frame, cx + 12, cy), far = GetImageColor(frame, w - (cx + 12), cy);
    check(int(near.r) + near.g + near.b > int(far.r) + far.g + far.b + 3,
          "bright geometry produces a local bloom halo without lighting the whole frame");
    UnloadImage(frame);

    BeginDrawing();
    post.begin({40, 40, 40, 255});
    DrawRectangle(w / 2, 0, w - w / 2, h, {100, 100, 100, 255});
    post.end();
    frame = LoadImageFromScreen();
    EndDrawing();
    const auto edge = GetImageColor(frame, w / 2 - 1, h / 2), flat = GetImageColor(frame, w / 2 - 10, h / 2);
    const auto lightSide = GetImageColor(frame, w / 2 + 10, h / 2);
    check(edge.g > flat.g && edge.g < lightSide.g,
          "gentle blur softens an edge without flattening its contrast");
    UnloadImage(frame);

    const Camera3D camera{{0, 0, 0}, {0, 0, -1}, {0, 1, 0}, 45, CAMERA_PERSPECTIVE};
    const Vector3 nearPosition{-5, 0, -20}, farPosition{25, 0, -100};
    BeginDrawing();
    post.begin(BLACK, 20);
    BeginMode3D(camera);
    // Equal screen-size/color surfaces at different distances isolate depth-based haze.
    DrawCube(nearPosition, 8, 8, .1f, {50, 60, 70, 255});
    DrawCube(farPosition, 40, 40, .1f, {50, 60, 70, 255});
    EndMode3D();
    post.end();
    DrawRectangle(2, 2, 25, 20, ui);
    rlDrawRenderBatchActive();
    frame = LoadImageFromScreen();
    EndDrawing();
    const auto a = GetWorldToScreen(nearPosition, camera), b = GetWorldToScreen(farPosition, camera);
    const auto closeColor = GetImageColor(frame, int(a.x), int(a.y));
    const auto distantColor = GetImageColor(frame, int(b.x), int(b.y));
    check(int(distantColor.r) + distantColor.g + distantColor.b >
              int(closeColor.r) + closeColor.g + closeColor.b + 20,
          "fog lifts distant geometry more than the near focal area");
    const auto fogUI = GetImageColor(frame, 10, 10);
    check(fogUI.r == ui.r && fogUI.g == ui.g && fogUI.b == ui.b,
          "depth fog and blur leave UI pixels unchanged");
    UnloadImage(frame);
    verifyOutlines(post);
}
} // namespace
int main() {
    try {
        SetTraceLogLevel(LOG_WARNING);
        SetConfigFlags(FLAG_WINDOW_HIDDEN | FLAG_WINDOW_RESIZABLE);
        InitWindow(800, 600, "Post processing verification");
        check(IsWindowReady(), "a graphics display is required");
        {
            dw::PostProcess post;
            verify(post);
            SetWindowSize(997, 653);
            for (int i = 0; i < 3; ++i) {
                BeginDrawing();
                EndDrawing();
            }
            check(GetScreenWidth() == 997 && GetScreenHeight() == 653, "resize event reaches the renderer");
            verify(post);
            post.unload();
            post.unload();
            verify(post);
            post.unload();
        }
        CloseWindow();
        std::cout << "PASS enemy occlusion outlines, color grading, bloom locality, gentle blur, depth fog, "
                     "image orientation, "
                     "unchanged UI, resize and "
                     "resource reload\n";
        return 0;
    } catch (const std::exception &error) {
        std::cerr << "FAIL " << error.what() << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
