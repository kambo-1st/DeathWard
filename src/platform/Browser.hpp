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
        for (const hub of['town', 'frontier', 'redstone', 'train_opening']) {
            const destination = '/persist/' + hub;
            FS.mkdirTree(destination);
            if(hub === 'train_opening' && !FS.analyzePath(destination+'/arrival.cinematic').exists)
                FS.writeFile(destination+'/arrival.cinematic',FS.readFile('/assets/train_opening/arrival.cinematic'));
            if (hub === 'redstone') {
                const matches = (name, length, expected) => {
                    const path = destination + '/' + name;
                    if (!FS.analyzePath(path).exists) return false;
                    const bytes = FS.readFile(path);
                    if (bytes.length !== length) return false;
                    let hash = 2166136261;
                    for (const byte of bytes) hash = Math.imul(hash ^ byte, 16777619) >>> 0;
                    return hash === expected;
                };
                // Upgrade only known untouched shipped scene/nav pairs.
                // Edited maps retain their layout and train/character settings.
                if ((matches('town.scene', 164220, 1179254129) &&
                     matches('town.nav', 5760052, 342212985)) ||
                    (matches('town.scene', 239972, 21795443) &&
                     matches('town.nav', 5760052, 576788661)) ||
                    (matches('town.scene', 260594, 418788540) &&
                     matches('town.nav', 5760052, 1738682236)) ||
                    (matches('town.scene', 260906, 1259833876) &&
                     matches('town.nav', 5760052, 1036499475)) ||
                    (matches('town.scene', 273555, 1956042650) &&
                     matches('town.nav', 5760052, 631388059)) ||
                    (matches('town.scene', 274526, 3143384547) &&
                     matches('town.nav', 5760052, 3536157510)) ||
                    (matches('town.scene', 274646, 2447431695) &&
                     matches('town.nav', 5760052, 3827705978)) ||
                    (matches('town.scene', 271017, 1725496596) &&
                     matches('town.nav', 5760052, 24843763)) ||
                    (matches('town.scene', 271048, 847026121) &&
                     matches('town.nav', 5760052, 4092110643))) {
                    for (const name of ['town.scene', 'town.nav'])
                        FS.writeFile(destination + '/' + name, FS.readFile('/assets/redstone/' + name));
                }
            }
            for (const name of['town.scene', 'town.nav', 'town.labels']) {
                if (!FS.analyzePath(destination + '/' + name).exists)
                    FS.writeFile(destination + '/' + name, FS.readFile('/assets/' + hub + '/' + name));
            }
            if (hub === 'redstone') {
                // New props append to the original mesh catalog. Extend old
                // editor saves without touching any authored instances or paths.
                const path = destination + '/town.scene';
                let saved = FS.readFile(path, {encoding:'utf8'});
                const shipped = FS.readFile('/assets/redstone/town.scene', {encoding:'utf8'});
                const catalog = text => text.split('\n').filter(line => line.startsWith('asset '));
                const newAssets = catalog(shipped);
                // Corrected road geometry keeps its pivots and mesh indices.
                // Refresh only its derived bounds; authored instances, labels,
                // routes and navigation remain exactly as the user saved them.
                const roadAssets = new Map(newAssets.filter(line => line.startsWith('asset redstone_road_'))
                    .map(line => [line.trim().split(' ').filter(Boolean).slice(0,5).join(' '), line]));
                const correctedRoads = saved.split('\n').map(line => {
                    const fields = line.trim().split(' ').filter(Boolean);
                    const replacement = roadAssets.get(fields.slice(0,5).join(' '));
                    if (!replacement) return line;
                    const bounds = replacement.split(' ').slice(5).map(Number);
                    // Editor saves round float bounds; preserve that spelling
                    // when they already describe the corrected mesh.
                    return bounds.some((value,n) => Math.abs(value-Number(fields[n+5])) > .0001)
                        ? replacement : line;
                }).join('\n');
                if (correctedRoads !== saved) {
                    FS.writeFile(path, correctedRoads);
                    saved = correctedRoads;
                }
                const oldAssets = catalog(saved);
                if (oldAssets.length < newAssets.length && oldAssets.every((line, n) => {
                    const before = line.trim().split(' ').filter(Boolean);
                    const after = newAssets[n].trim().split(' ').filter(Boolean);
                    return before.slice(0,5).join(' ') === after.slice(0,5).join(' ');
                })) FS.writeFile(path, saved.trimEnd() + '\n' + newAssets.slice(oldAssets.length).join('\n') + '\n');
                // Add the missing soil once to existing road-era editor saves
                // when the surrounding terrain is still at its authored poses.
                // A later deliberate deletion of the fill must stay deleted.
                const repairMarker = destination + '/.badlands-ground-v1';
                if (!FS.analyzePath(repairMarker).exists) {
                    const instances = text => new Map(text.split('\n').filter(line => line.startsWith('instance '))
                        .map(line => [line.trim().split(' ').filter(Boolean)[2],line]));
                    const oldInstances = instances(saved);
                    const shippedInstances = instances(shipped);
                    const repairId = 'terrain-badlands-ground:1829520066912572';
                    const repair = shippedInstances.get(repairId);
                    const anchors = (['redstone-road-east',
                        'town-1017155373:1829520066912572', 'town-1959252270:1194512102497620',
                        'town-1055865170:1194512102497620', 'town-320569589:1194512102497620',
                        'town-884915718:1194512102497620']);
                    const samePose = id => {
                        const before = (oldInstances.get(id) || "").trim().split(' ').filter(Boolean);
                        const after = (shippedInstances.get(id) || "").trim().split(' ').filter(Boolean);
                        return before.length === 19 && after.length === 19 &&
                            before.slice(0,3).join(' ') === after.slice(0,3).join(' ') &&
                            after.slice(3).every((value,n) => Math.abs(Number(value)-Number(before[n+3])) < .0001);
                    };
                    if (repair && !oldInstances.has(repairId) && anchors.every(samePose)) {
                        FS.writeFile(path, FS.readFile(path,{encoding:'utf8'}).trimEnd() + '\n' + repair + '\n');
                        // Use the existing geometry rebake on startup, preserving
                        // this save's arrival/mission markers and custom scenery.
                        const navPath = destination + '/town.nav';
                        const navigation = FS.readFile(navPath);
                        navigation[7] = 50; // DWTNAV02 requests a current-format rebuild.
                        FS.writeFile(navPath,navigation);
                    }
                    FS.writeFile(repairMarker,'1');
                }
                const labelPath = destination + '/town.labels';
                const labels = FS.readFile(labelPath, {encoding:'utf8'});
                const known = new Set(labels.split('\n').map(line => line.split(' ')[0]));
                const added = FS.readFile('/assets/redstone/town.labels', {encoding:'utf8'})
                    .split('\n').filter(line => line && !known.has(line.split(' ')[0]));
                if (added.length) FS.writeFile(labelPath, labels.trimEnd() + '\n' + added.join('\n') + '\n');
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
