#pragma once
#include "core/Types.hpp"
#include <string>

namespace dw {
// Authored grid topology is independent of world scale, combatants and pathfinding.
// Centered crossings continue straight and end stops reverse the vehicle, as
// supported by the preserved native rail projection. Curve geometry and the
// exact turning point remain explicit world-space adaptations.
enum class RailSide { North, East, South, West };
struct RailCell { int x=0,z=0,variant=0; bool overPit=false; };
struct RailDoor { int cell=0; RailSide side=RailSide::North; };
struct RailStep { int cell=0; RailSide incoming=RailSide::North,outgoing=RailSide::South; };
struct RailRouteDefinition { int entry=0,exit=0; std::vector<RailStep> steps; };
struct RailLayout {
    std::string key;
    int width=0,height=0;
    unsigned closedEntrances=0;
    int halfTurns=0;
    std::vector<RailCell> cells;
    std::vector<std::pair<int,int>> pitCells,rockCells;
    std::vector<RailDoor> doors;
    std::vector<RailRouteDefinition> routes;
    // Reject disconnected ports, duplicates and door routes that never leave.
    // Derived routes are rebuilt, so repeated validation is idempotent.
    void compile();
    RailLayout reversed() const;
};
struct RailPose { Vector3 position{},direction{0,0,1}; bool finished=false; };
struct RailTravel {
    RailPose pose;
    float distance=0,remaining=0;
    // Contact must use these segments, not a chord that cuts across a curve.
    std::vector<std::array<Vector3,2>> swept;
};
struct RailPath {
    int entry=0,exit=0;
    std::vector<Vector3> points;
    std::vector<float> distances;
    float length() const { return distances.empty()?0:distances.back(); }
    RailPose sample(float travelled) const;
    RailTravel advance(float from,float amount) const;
};
struct RailNetwork {
    std::string layout;
    Box bounds{};
    Vector3 cellSize{};
    std::vector<Vector3> doors;
    std::vector<RailSide> doorSides;
    std::vector<RailPath> paths;
    std::vector<Box> pits;
    // Fits all cell centers and wall ports to a dedicated arena footprint.
    // Curves use shared physical vertices for rendering and vehicle motion.
    static RailNetwork fit(const RailLayout &layout,const Box &bounds,float elevation=.12f);
};
unsigned railPorts(int variant);
Vector3 railDirection(RailSide side);
} // namespace dw
