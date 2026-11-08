#include "combat/PlayerHealth.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace dw;

namespace {
void require(bool valid, const std::string &message) { if (!valid) throw std::runtime_error(message); }
void apply(SourcePlayerHealth &health, const std::string &operation, int amount) {
    if (operation == "red") health.addRed(amount);
    else if (operation == "max_red") health.addMaxRed(amount);
    else if (operation == "soul") health.addSoul(amount);
    else if (operation == "black") health.addBlack(amount);
    else if (operation == "eternal") health.addEternal(amount);
    else if (operation == "golden") health.addGolden(amount);
    else if (operation == "bone") health.addBone(amount);
    else if (operation == "rotten") health.addRotten(amount);
    else if (operation == "broken") health.addBroken(amount);
    else if (operation == "damage") health.damage(amount);
    else if (operation == "red_first_damage") health.damage(amount, true);
    else if (operation == "floor") health.newFloor();
    else throw std::runtime_error("Unknown operation " + operation);
}
std::string effects(const SourcePlayerHealth &health) {
    std::string result;
    for (const auto &effect : health.effects) {
        if (!result.empty()) result += '|';
        switch (effect.kind) {
        case HealthEffectKind::BlackBurst: result += "black_burst"; break;
        case HealthEffectKind::BoneBreakVisuals: result += "bone_break_visuals"; break;
        case HealthEffectKind::GoldenBurst: result += "golden_burst:" + std::to_string(effect.count); break;
        case HealthEffectKind::ConversionAnimation: result += "health_animation:" + std::to_string(effect.count); break;
        }
    }
    return result;
}
}

int main() {
    try {
        std::ifstream input(std::string(DEATHWARD_TEST_ROOT) + "/docs/reports/isaac-first-floor-parity/player-health/native-health.csv");
        require(bool(input), "native health trace exists");
        SourcePlayerHealth health;
        std::string line, name;
        std::getline(input, line);
        int rows = 0, cases = 0;
        while (std::getline(input, line)) {
            std::vector<std::string> fields;
            std::istringstream stream(line);
            std::string field;
            while (std::getline(stream, field, ',')) fields.push_back(field);
            if (!line.empty() && line.back() == ',') fields.emplace_back();
            require(fields.size() == 15, "native health trace schema");
            if (name != fields[0]) { name = fields[0]; health = {}; ++cases; }
            const std::string context = name + " step " + fields[1] + " " + fields[2] + "(" + fields[3] + ")";
            health.effects.clear();
            apply(health, fields[2], std::stoi(fields[3]));
            const std::array<int, 10> actual = {health.maxRed, health.red, health.eternal, health.soul,
                int(health.blackMask), health.golden, health.bone, int(health.boneMask), health.broken, health.rotten};
            for (size_t i = 0; i < actual.size(); ++i) {
                const int expected = std::stoi(fields[i + 4]);
                require(actual[i] == expected, context + " field " + std::to_string(i) + ": expected "
                        + std::to_string(expected) + ", got " + std::to_string(actual[i]));
            }
            require(effects(health) == fields[14], context + ": expected effects [" + fields[14] + "] got [" + effects(health) + "]");
            ++rows;
        }
        require(rows == 293 && cases == 28, "complete independent native health matrix");
        std::cout << "PASS native health: " << rows << " transitions / " << cases
                  << " cases; full damage flags, world-effect fidelity and acceptance remain open\n";
        return 0;
    } catch (const std::exception &error) {
        std::cerr << "FAIL " << error.what() << '\n';
        return 1;
    }
}
