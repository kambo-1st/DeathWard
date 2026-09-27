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
        std::cout << "PASS color grading, bloom locality, image orientation, unchanged UI, resize and "
                     "resource reload\n";
        return 0;
    } catch (const std::exception &error) {
        std::cerr << "FAIL " << error.what() << '\n';
        if (IsWindowReady())
            CloseWindow();
        return 1;
    }
}
