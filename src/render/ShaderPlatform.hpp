#pragma once
#include "raylib.h"
#include "rlgl.h"
#include <string>
#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <emscripten.h>
#endif

namespace dw {
inline Shader loadWorldShader(const char *vertex, const char *fragment) {
#ifdef __EMSCRIPTEN__
    auto convert = [](const char *source) {
        if (!source)
            return std::string{};
        std::string converted(source);
        if (converted.starts_with("#version 330"))
            converted.replace(0, converted.find('\n') + 1,
                              "#version 300 es\nprecision highp float;\nprecision highp int;\n");
        return converted;
    };
    const auto vs = convert(vertex), fs = convert(fragment);
    return LoadShaderFromMemory(vertex ? vs.c_str() : nullptr, fragment ? fs.c_str() : nullptr);
#else
    return LoadShaderFromMemory(vertex, fragment);
#endif
}
inline unsigned loadDepthTexture(int width, int height) {
#ifdef __EMSCRIPTEN__
    // WebGL 2 requires a sized depth format; raylib 5.5's helper uses the ES2 format.
    unsigned texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT,
                 GL_UNSIGNED_INT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
#else
    return rlLoadTextureDepth(width, height, false);
#endif
}
inline void depthOnlyFramebuffer(unsigned framebuffer) {
#ifdef __EMSCRIPTEN__
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    const GLenum none = GL_NONE;
    glDrawBuffers(1, &none);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
#else
    (void)framebuffer;
#endif
}
inline int worldColorFormat() {
#ifdef __EMSCRIPTEN__
    const bool hdr = EM_ASM_INT({ return !!Module.ctx.getExtension('EXT_color_buffer_float'); });
    if (!hdr)
        return PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
#endif
    return PIXELFORMAT_UNCOMPRESSED_R16G16B16A16;
}
} // namespace dw
