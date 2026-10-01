#include "render/GroundSurface.hpp"
#include "rlgl.h"

namespace dw {
std::string GroundSurface::withDetail(const char *fragment) {
    constexpr const char *functions = R"GLSL(
uniform int groundEnabled;
uniform int roadEnabled;
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
vec3 groundNatural(vec3 base, vec3 position) {
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
vec3 groundSurface(vec3 base, vec3 position) {
    vec3 color = groundNatural(base,position);
    if (roadEnabled == 0) return color;
    vec2 p = position.xz + groundSeed;
    vec4 marks = texture(groundSoil,(position.xz-groundRectangle.xy)/groundRectangle.zw);
    float patches = groundNoise(p*.38+17.);
    vec3 dirt = base*mix(vec3(.91,.85,.77),vec3(.81,.75,.68),patches);
    dirt *= .98+.04*groundNoise(p*3.3);
    color = mix(color,dirt,marks.g*.92);
    // Broad, imperfect wagon wear is baked along the actual curved route.
    // Texture filtering and world-space noise keep it soft at all zoom levels.
    color *= 1.-marks.b*(.09+.09*groundNoise(p*.7+51.));
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
    roads_ = false;
}
void GroundSurface::prepare(const Arena &arena, std::span<const Box> rocks) {
    unload();
    const float x = arena.bounds.min.x - 8, z = arena.bounds.min.z - 8;
    const float spanX = std::max(1.f, arena.bounds.max.x - x + 8);
    const float spanZ = std::max(1.f, arena.bounds.max.z - z + 8);
    roads_ = arena.canyon && !arena.canyon->road.empty();
    const float step =
        roads_ ? std::max(.25f, std::max(spanX, spanZ) / 2047) : std::max(.5f, std::max(spanX, spanZ) / 1023);
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
    // One shared atlas: soil accumulation (R), worn road (G), wagon ruts (B).
    std::vector<unsigned char> pixels(distances.size() * 4, 0);
    for (size_t i = 0; i < distances.size(); ++i) {
        pixels[i * 4] = static_cast<unsigned char>(255 * std::exp(-distances[i] / .8f));
        pixels[i * 4 + 3] = 255;
    }
    if (roads_) {
        std::fill(distances.begin(), distances.end(), 1000.f);
        const auto &road = arena.canyon->road;
        auto smooth = [](float lo, float hi, float v) {
            const float t = std::clamp((v - lo) / (hi - lo), 0.f, 1.f);
            return t * t * (3 - 2 * t);
        };
        // Rasterize only the small boxes touched by each segment, rather than
        // searching the whole polyline at every texel of a large dungeon.
        for (size_t i = 1; i < road.size(); ++i) {
            const auto &a = road[i - 1], &b = road[i];
            const auto edge = sub(b.position, a.position);
            const float span = std::max(.001f, dot(edge, edge));
            const float radius = std::max(a.width, b.width) + .4f;
            const int left =
                std::max(0, int(std::floor((std::min(a.position.x, b.position.x) - radius - x) / step)));
            const int right = std::min(
                width - 1, int(std::ceil((std::max(a.position.x, b.position.x) + radius - x) / step)));
            const int top =
                std::max(0, int(std::floor((std::min(a.position.z, b.position.z) - radius - z) / step)));
            const int bottom = std::min(
                depth - 1, int(std::ceil((std::max(a.position.z, b.position.z) + radius - z) / step)));
            for (int row = top; row <= bottom; ++row)
                for (int col = left; col <= right; ++col) {
                    const Vector3 p{x + col * step, 0, z + row * step};
                    const float t = std::clamp(dot(sub(p, a.position), edge) / span, 0.f, 1.f);
                    const auto offset = sub(p, add(a.position, mul(edge, t)));
                    const float side = length(offset), halfWidth = std::lerp(a.width, b.width, t);
                    const float along = std::lerp(a.along, b.along, t);
                    const float fade = smooth(0, 5, along) * smooth(0, 5, road.back().along - along);
                    const float ragged =
                        .12f * std::sin(p.x * .91f + p.z * .72f) + .06f * std::sin(p.z * 2.1f - p.x * 1.3f);
                    const float wear = (1 - smooth(halfWidth * .55f, halfWidth + .2f, side + ragged)) * fade;
                    const float wheel = .68f + .055f * std::sin(along * .31f);
                    const float ruts = (1 - smooth(.09f, .31f, std::abs(side - wheel))) * wear;
                    const auto index = size_t(row * width + col) * 4;
                    pixels[index + 1] = std::max(pixels[index + 1], static_cast<unsigned char>(wear * 255));
                    // The closest segment supplies rut coordinates. Taking the
                    // maximum over rounded end caps would fill the road centre.
                    if (side < distances[index / 4]) {
                        distances[index / 4] = side;
                        pixels[index + 2] = static_cast<unsigned char>(ruts * 255);
                    }
                }
        }
    }
    Image image{pixels.data(), width, depth, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
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
    const int roads = floor && roads_ && soil_.id;
    SetShaderValue(shader, GetShaderLocation(shader, "groundEnabled"), &active, SHADER_UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "roadEnabled"), &roads, SHADER_UNIFORM_INT);
    if (!active && !roads)
        return;
    SetShaderValue(shader, GetShaderLocation(shader, "groundRectangle"), &rectangle_, SHADER_UNIFORM_VEC4);
    SetShaderValue(shader, GetShaderLocation(shader, "groundSeed"), &seed_, SHADER_UNIFORM_VEC2);
}
} // namespace dw
