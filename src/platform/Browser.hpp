#pragma once
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace dw {
inline void persistBrowserFiles() {
#ifdef __EMSCRIPTEN__
    EM_ASM({
        if (Module.flushSaves)
            Module.flushSaves();
    });
#endif
}
inline void prepareBrowserFiles() {
#ifdef __EMSCRIPTEN__
    EM_ASM({
        // Only editable scene/navigation files belong in IndexedDB. Models are
        // loaded directly from /assets; IDBFS does not preserve symlinks.
        for (const hub of['town', 'frontier', 'redstone']) {
            const destination = '/persist/' + hub;
            FS.mkdirTree(destination);
            for (const name of['town.scene', 'town.nav', 'town.labels']) {
                if (!FS.analyzePath(destination + '/' + name).exists)
                    FS.writeFile(destination + '/' + name, FS.readFile('/assets/' + hub + '/' + name));
            }
            // The original Frontier labels gave the cooking pot its parent fire's
            // name. Migrate only that known label; keep authored scenes and names.
            if (hub === 'frontier' || hub === 'town') {
                const path = destination + '/town.labels';
                const labels = FS.readFile(path, {encoding: 'utf8'});
                const corrected = labels.split('\n').map(line =>
                    hub === 'frontier' && line === 'part_0106 SM_Prop_Campfire_Small_01' ?
                        'part_0106 SM_Prop_Campfire_Pot_01' :
                    hub === 'town' && line === 'part_0033 SM_Veh_Train_01' ?
                        'part_0033 SM_Veh_Train_01_Alt_Smokestack' : line).join('\n');
                if (corrected !== labels) FS.writeFile(path, corrected);
                // Old prefab labels concealed the identity of doors and glass.
                // Replace only known original prefab names, preserving custom labels.
                const legacy = new Set(['SM_Bld_Single_Front_01', 'SM_Bld_Single_Front_02',
                    'SM_Bld_Double_02', 'SM_Bld_Double_Front_02', 'SM_Bld_Double_Front_01',
                    'SM_Bld_Outhouse_01', 'SM_Bld_Large_01', 'SM_Bld_Jail_01',
                    'SM_Bld_TrainStation_01', 'SM_Bld_Church_01', 'SM_Bld_Saloon_01',
                    'SM_Bld_Mexican_01', 'SM_Bld_Mexican_02', 'SM_Bld_Mexican_03', 'SM_Bld_Mexican_04',
                    'SM_Bld_Cabin_01', 'SM_Bld_Barn_01', 'SM_Bld_Fort_Entrance_01', 'SM_Bld_Fort_Entrance_02',
                    'SM_Bld_Fort_Wall_01', 'SM_Bld_Fort_Wall_02', 'SM_Bld_Mexican_Wall_01',
                    'SM_Bld_Mexican_Wall_Corner_01', 'SM_Bld_Fort_TowerCorner_01',
                    'SM_Bld_Quarry_01', 'SM_Bld_Quarry_02', 'SM_Bld_Quarry_05', 'SM_Bld_Mexican_Entrance_01']);
                const shipped = new Map(FS.readFile('/assets/' + hub + '/town.labels', {encoding:'utf8'})
                    .split('\n').map(line => line.split(' ')));
                const buildings = corrected.split('\n').map(line => {
                    const parts = line.split(' '), name = shipped.get(parts[0]);
                    return legacy.has(parts[1]) && name ? parts[0] + ' ' + name : line;
                }).join('\n');
                if (buildings !== corrected) FS.writeFile(path, buildings);
            }
        }
    });
#endif
}
} // namespace dw
