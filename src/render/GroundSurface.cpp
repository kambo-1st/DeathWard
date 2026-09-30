#include "render/GroundSurface.hpp"
#include "rlgl.h"

namespace dw {
std::string GroundSurface::withDetail(const char *fragment) {
    constexpr const char *functions = R"GLSL(
uniform int groundEnabled;
uniform sampler2D groundSoil;
uniform vec4 groundRectangle;
uniform vec2 groundSeed;
float groundHash(vec2 p) {
    vec3 q = fract(vec3(p.xyx)*.1031);
    q += dot(q,q.yzx+33.33);
    return fract((q.x+q.y)*q.z);
}
float groundNoise(vec2 p) {
    vec2 i = floor(p), f = fract(p);
    f = f*f*(3.-2.*f);
    return mix(mix(groundHash(i),groundHash(i+vec2(1,0)),f.x),
               mix(groundHash(i+vec2(0,1)),groundHash(i+vec2(1,1)),f.x),f.y);
}
vec3 groundSurface(vec3 base, vec3 position) {
    if (groundEnabled == 0) return base;
    vec2 p = position.xz + groundSeed;
    vec2 warp = vec2(groundNoise(p*.071),groundNoise(p*.071+37.))*3.2;
    float broad = groundNoise((p+warp)*.115);
    float middle = groundNoise(p*.51+23.);
    float dirt = smoothstep(.28,.76,broad*.8+middle*.2);
    vec3 color = mix(base*1.025,base*vec3(.86,.83,.81),dirt*.85);
    float shoulder = texture(groundSoil,(position.xz-groundRectangle.xy)/groundRectangle.zw).r;
    float deposit = shoulder*(.65+.35*groundNoise(p*.8+71.));
    color *= 1.-deposit*.17;
    color *= 1.+(middle-.5)*.045;

    // World-sized detail fades before it becomes smaller than a pixel. It stays
    // attached to the floor during camera motion instead of shimmering like grain.
    float pixel = max(length(dFdx(position.xz)),length(dFdy(position.xz)));
    float fine = 1.-smoothstep(.025,.085,pixel);
    color *= 1.+(groundNoise(p*27.)-.5)*.095*fine;
    vec2 cells = p*3.1;
    vec2 cell = floor(cells);
    vec2 center = .25+.5*vec2(groundHash(cell+17.),groundHash(cell+91.));
    float r = length((fract(cells)-center)*vec2(1.,1.35));
    float aa = clamp(pixel*3.1,.015,.18);
    float speck = 1.-smoothstep(.12-aa,.12+aa,r);
    speck *= smoothstep(.73,.9,groundHash(cell+57.))*(1.-smoothstep(.10,.23,pixel));
    color *= 1.-speck*.13;
    return color;
}
)GLSL";
    std::string result(fragment);
    result.insert(result.find("void main()"), functions);
    return result;
}
void GroundSurface::unload() {
    if (soil_.id)
        UnloadTexture(soil_);
    soil_ = {};
}
void GroundSurface::prepare(const Arena &arena, std::span<const Box> rocks) {
    unload();
    const float x = arena.bounds.min.x - 8, z = arena.bounds.min.z - 8;
    const float spanX = std::max(1.f, arena.bounds.max.x - x + 8);
    const float spanZ = std::max(1.f, arena.bounds.max.z - z + 8);
    const float step = std::max(.5f, std::max(spanX, spanZ) / 1023);
    const int width = int(std::ceil(spanX / step)) + 1, depth = int(std::ceil(spanZ / step)) + 1;
    // Texel centres correspond to field samples, avoiding a half-texel offset at contacts.
    rectangle_ = {x - step / 2, z - step / 2, width * step, depth * step};
    std::vector<float> distances(size_t(width) * depth, 1000.f);
    if (arena.canyon)
        for (int row = 0; row < depth; ++row)
            for (int col = 0; col < width; ++col)
                if (arena.canyon->height(x + col * step, z + row * step) > .18f)
                    distances[size_t(row) * width + col] = 0;
    auto mark = [&](Box box) {
        const int x0 = std::clamp(int(std::floor((box.min.x - x) / step)), 0, width - 1);
        const int x1 = std::clamp(int(std::ceil((box.max.x - x) / step)), 0, width - 1);
        const int z0 = std::clamp(int(std::floor((box.min.z - z) / step)), 0, depth - 1);
        const int z1 = std::clamp(int(std::ceil((box.max.z - z) / step)), 0, depth - 1);
        for (int row = z0; row <= z1; ++row)
            for (int col = x0; col <= x1; ++col)
                distances[size_t(row) * width + col] = 0;
    };
    if (!arena.canyon)
        for (auto box : arena.obstacles)
            mark(box);
    for (auto box : rocks)
        mark(box);
    // Eight-neighbour distance transform, baked once per mission. This is soil
    // buildup beside real geometry, not baked lighting or screen-space AO.
    auto relax = [&](int col, int row, int dx, int dz, float cost) {
        const int fromX = col + dx, fromZ = row + dz;
        if (fromX < 0 || fromX >= width || fromZ < 0 || fromZ >= depth)
            return;
        auto &d = distances[size_t(row) * width + col];
        d = std::min(d, distances[size_t(fromZ) * width + fromX] + cost * step);
    };
    for (int row = 0; row < depth; ++row)
        for (int col = 0; col < width; ++col) {
            relax(col, row, -1, 0, 1);
            relax(col, row, 0, -1, 1);
            relax(col, row, -1, -1, 1.414214f);
            relax(col, row, 1, -1, 1.414214f);
        }
    for (int row = depth - 1; row >= 0; --row)
        for (int col = width - 1; col >= 0; --col) {
            relax(col, row, 1, 0, 1);
            relax(col, row, 0, 1, 1);
            relax(col, row, 1, 1, 1.414214f);
            relax(col, row, -1, 1, 1.414214f);
        }
    std::vector<unsigned char> pixels(distances.size());
    for (size_t i = 0; i < pixels.size(); ++i)
        pixels[i] = static_cast<unsigned char>(255 * std::exp(-distances[i] / .8f));
    Image image{pixels.data(), width, depth, 1, PIXELFORMAT_UNCOMPRESSED_GRAYSCALE};
    soil_ = LoadTextureFromImage(image);
    SetTextureFilter(soil_, TEXTURE_FILTER_BILINEAR);
    SetTextureWrap(soil_, TEXTURE_WRAP_CLAMP);
    Random random(arena.visualSeed ^ 0x67726f756e647331ULL);
    seed_ = {random.real(32, 512), random.real(32, 512)};
}
void GroundSurface::bind(Shader shader, bool floor) const {
    if (!shader.id)
        return;
    const int active = enabled && floor && soil_.id;
    SetShaderValue(shader, GetShaderLocation(shader, "groundEnabled"), &active, SHADER_UNIFORM_INT);
    if (!active)
        return;
    SetShaderValue(shader, GetShaderLocation(shader, "groundRectangle"), &rectangle_, SHADER_UNIFORM_VEC4);
    SetShaderValue(shader, GetShaderLocation(shader, "groundSeed"), &seed_, SHADER_UNIFORM_VEC2);
}
} // namespace dw
