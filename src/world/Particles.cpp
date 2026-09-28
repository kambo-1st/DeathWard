#include "world/Particles.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace dw {
namespace {
float random(uint32_t &state) {
    state += 0x9e3779b9u;
    uint32_t x = state;
    x = (x ^ (x >> 16)) * 0x21f0aaadu;
    x = (x ^ (x >> 15)) * 0x735a2d97u;
    return float((x ^ (x >> 15)) >> 8) / 16777216.f;
}
float between(Vector2 range, uint32_t &state) {
    return std::lerp(range.x, range.y, random(state));
}
bool finite(float v) { return std::isfinite(v); }
} // namespace
void ParticleLibrary::load(const std::filesystem::path &directory) {
    ParticleLibrary next;
    std::ifstream file(directory / "fire.particles");
    std::string header;
    int version = 0;
    if (!(file >> header >> version) || header != "DEATHWARD_PARTICLES" || version != 1)
        throw std::runtime_error("Invalid particle library header");
    std::string line;
    ParticleEmitter *e = nullptr;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream in(line);
        std::string key;
        in >> key;
        if (key == "emitter") {
            if (e) throw std::runtime_error("Unclosed particle emitter");
            std::string mode;
            next.emitters.emplace_back();
            e = &next.emitters.back();
            in >> e->name >> mode >> e->resource;
            if (mode == "mesh") e->kind = ParticleKind::Mesh;
            else if (mode == "billboard") e->kind = ParticleKind::Billboard;
            else if (mode == "additive") e->kind = ParticleKind::Additive;
            else throw std::runtime_error("Unknown particle renderer");
        } else if (!e) throw std::runtime_error("Particle parameter outside emitter");
        else if (key == "end") e = nullptr;
        else if (key == "rate") in >> e->rate;
        else if (key == "lifetime") in >> e->lifetime.x >> e->lifetime.y;
        else if (key == "size") in >> e->size.x >> e->size.y;
        else if (key == "speed") in >> e->speed.x >> e->speed.y;
        else if (key == "spin") in >> e->spin.x >> e->spin.y;
        else if (key == "gravity") in >> e->gravity;
        else if (key == "radius") in >> e->radius;
        else if (key == "noise") in >> e->noise >> e->frequency;
        else if (key == "emission") in >> e->emission;
        else if (key == "sizekey") {
            ParticleKey k;
            in >> k.time >> k.value >> k.inSlope >> k.outSlope;
            e->sizes.push_back(k);
        } else if (key == "alpha") {
            ParticleKey k;
            in >> k.time >> k.value;
            e->alphas.push_back(k);
        } else if (key == "color") {
            ParticleColorKey k;
            in >> k.time >> k.value.x >> k.value.y >> k.value.z;
            e->colors.push_back(k);
        } else throw std::runtime_error("Unknown particle parameter: " + key);
        std::string extra;
        if (!in || (in >> extra)) throw std::runtime_error("Malformed particle line: " + line);
    }
    if (e || next.emitters.empty() || next.emitters.size() > 32)
        throw std::runtime_error("Incomplete particle library");
    for (const auto &emitter : next.emitters) {
        for (float v : {emitter.rate, emitter.gravity, emitter.radius, emitter.noise, emitter.frequency,
                        emitter.emission, emitter.lifetime.x, emitter.lifetime.y, emitter.size.x,
                        emitter.size.y, emitter.speed.x, emitter.speed.y, emitter.spin.x, emitter.spin.y})
            if (!finite(v)) throw std::runtime_error("Non-finite particle parameter");
        if (emitter.rate <= 0 || emitter.rate > 200 || emitter.lifetime.x <= 0 ||
            emitter.lifetime.y < emitter.lifetime.x || emitter.lifetime.y > 20 ||
            emitter.rate * emitter.lifetime.y > 512 || emitter.size.x < 0 || emitter.size.y < emitter.size.x ||
            emitter.radius < 0 || emitter.noise < 0 || emitter.emission < 0 || emitter.emission > 8 ||
            emitter.resource.find_first_of("/\\") != std::string::npos || emitter.resource == "..")
            throw std::runtime_error("Particle parameters outside budget");
        auto checkKeys = [](const auto &keys) {
            if (keys.empty() || keys.size() > 32) throw std::runtime_error("Missing or excessive particle curve");
            float previous = -1;
            for (const auto &k : keys) {
                if (!finite(k.time) || k.time < 0 || k.time > 1 || k.time <= previous)
                    throw std::runtime_error("Invalid particle curve times");
                previous = k.time;
            }
        };
        checkKeys(emitter.sizes); checkKeys(emitter.alphas); checkKeys(emitter.colors);
        for (const auto &keys : {emitter.sizes, emitter.alphas})
            for (const auto &k : keys)
                if (!finite(k.value) || !finite(k.inSlope) || !finite(k.outSlope))
                    throw std::runtime_error("Invalid particle curve values");
        for (const auto &k : emitter.colors)
            if (!finite(k.value.x) || !finite(k.value.y) || !finite(k.value.z))
                throw std::runtime_error("Invalid particle color");
    }
    std::ifstream bindings(directory / "town.attachments");
    if (!bindings) throw std::runtime_error("Missing town particle attachments");
    while (std::getline(bindings, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream in(line);
        ParticleAttachment a;
        std::string emitter, extra;
        if (!(in >> a.label >> emitter >> a.offset.x >> a.offset.y >> a.offset.z >> a.scale >> a.lightRange) ||
            (in >> extra) || !finite(a.offset.x) || !finite(a.offset.y) || !finite(a.offset.z) ||
            !finite(a.scale) || a.scale <= 0 || a.scale > 100 || !finite(a.lightRange) ||
            a.lightRange < 0 || a.lightRange > 30)
            throw std::runtime_error("Invalid particle attachment: " + line);
        auto it = std::find_if(next.emitters.begin(), next.emitters.end(),
                               [&](const auto &em) { return em.name == emitter; });
        if (it == next.emitters.end()) throw std::runtime_error("Unknown attachment emitter");
        a.emitter = size_t(it - next.emitters.begin());
        next.attachments.push_back(a);
        if (next.attachments.size() > 256) throw std::runtime_error("Too many particle attachments");
    }
    *this = std::move(next);
}
float ParticleLibrary::curve(const std::vector<ParticleKey> &keys, float time, bool hermite) {
    if (keys.empty()) return 1;
    if (time <= keys.front().time) return keys.front().value;
    for (size_t n = 1; n < keys.size(); ++n) {
        if (time > keys[n].time) continue;
        const auto &a = keys[n - 1], &b = keys[n];
        float span = b.time - a.time, t = (time - a.time) / span;
        if (!hermite) return std::lerp(a.value, b.value, t);
        return (2*t*t*t - 3*t*t + 1)*a.value + (t*t*t - 2*t*t + t)*span*a.outSlope +
               (-2*t*t*t + 3*t*t)*b.value + (t*t*t - t*t)*span*b.inSlope;
    }
    return keys.back().value;
}
std::vector<ParticleSample> ParticleLibrary::sample(const ParticleEmitter &e, double time, uint32_t seed) {
    std::vector<ParticleSample> result;
    if (!std::isfinite(time) || time < 0 || time > 1e10 || e.rate <= 0) return result;
    // Include negative spawn times, so a fireplace is already burning at time zero.
    uint32_t phaseSeed = seed;
    const double phase = random(phaseSeed);
    const auto last = int64_t(std::floor(time * e.rate + phase));
    const auto first = int64_t(std::floor((time - e.lifetime.y) * e.rate + phase));
    result.reserve(size_t(last - first + 1));
    for (auto index = first; index <= last; ++index) {
        uint32_t state = seed ^ (uint32_t(index) * 0x85ebca6bu);
        const float age = float(time - (double(index) - phase) / e.rate);
        const float lifetime = between(e.lifetime, state);
        if (age < 0 || age >= lifetime) continue;
        const float t = age / lifetime, size = between(e.size, state), speed = between(e.speed, state);
        const float spin = between(e.spin, state), angle = random(state) * 2 * PI;
        const float radius = std::sqrt(random(state)) * e.radius, noisePhase = random(state) * 2 * PI;
        ParticleSample p;
        p.position = {std::cos(angle) * radius, speed * age + .5f * e.gravity * age * age,
                      std::sin(angle) * radius};
        // Bounded turbulence; never accumulates drift or depends on frame rate.
        p.position.x += e.noise * t * std::sin(age * e.frequency * 6 + noisePhase);
        p.position.z += e.noise * t * std::cos(age * e.frequency * 5 + noisePhase);
        p.size = std::max(0.f, size * curve(e.sizes, t));
        p.alpha = std::clamp(curve(e.alphas, t, false), 0.f, 1.f);
        p.rotation = angle + spin * age;
        p.color = e.colors.back().value;
        if (t <= e.colors.front().time) p.color = e.colors.front().value;
        else for (size_t n = 1; n < e.colors.size(); ++n) {
            const auto &a = e.colors[n - 1], &b = e.colors[n];
            if (t > b.time) continue;
            const float f = (t - a.time) / (b.time - a.time);
            p.color = add(mul(a.value, 1-f), mul(b.value, f));
            break;
        }
        if (p.alpha > .001f && p.size > .0001f) result.push_back(p);
    }
    return result;
}
} // namespace dw
