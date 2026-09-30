#pragma once
#include "world/TownDocument.hpp"

namespace dw {
// Imported architecture has separate door leaves/glass and hollow wall/floor
// meshes. These rules also apply to copies placed through the town editor.
inline bool buildingGeometry(const TownAsset &asset) {
    return asset.label.starts_with("SM_Bld_") || asset.label.starts_with("SM_Building_");
}
inline bool buildingDoor(const TownAsset &asset) {
    return buildingGeometry(asset) && asset.label.find("Door") != std::string::npos &&
           asset.label.find("Glass") == std::string::npos && asset.label.find("Window") == std::string::npos;
}
inline bool doorGlass(const TownAsset &asset) {
    return buildingGeometry(asset) && asset.label.find("Door") != std::string::npos &&
           (asset.label.find("Glass") != std::string::npos || asset.label.find("Window") != std::string::npos);
}
inline bool buildingShell(const TownAsset &asset) {
    for (const char *name : {"SM_Bld_Single_01", "SM_Bld_Double_02", "SM_Bld_Large_01", "SM_Bld_Jail_01",
         "SM_Bld_Saloon_01", "SM_Bld_Church_01", "SM_Bld_TrainStation_01", "SM_Bld_Cabin_01",
         "SM_Bld_Barn_01", "SM_Bld_Mexican_01", "SM_Bld_Mexican_02", "SM_Bld_Mexican_03", "SM_Bld_Mexican_04"})
        if (asset.label == name && asset.bounds.max.y-asset.bounds.min.y > 2.8f &&
            asset.bounds.max.x-asset.bounds.min.x > 2.5f && asset.bounds.max.z-asset.bounds.min.z > 2)
            return true;
    return false;
}
} // namespace dw
