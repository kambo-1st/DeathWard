#pragma once
#include "RockFormations.hpp"
namespace dw::rockFormations {
struct Section {
    std::vector<cliffDetail::Quad> wall;
    float length=0, turn=0;
    uint64_t key=0;
    Vector3 midpoint{};
    std::string shape, curvature, fallback;
};
// World-space contour selection. No camera, screen rectangle or Works seed.
Section selectSection(const CanyonAppearance &,const Box &room);
std::vector<Section> selectSections(const CanyonAppearance &,const Box &room);
}
