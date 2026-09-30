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
                     matches('town.nav', 5760052, 631388059))) {
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
                const saved = FS.readFile(path, {encoding:'utf8'});
                const shipped = FS.readFile('/assets/redstone/town.scene', {encoding:'utf8'});
                const catalog = text => text.split('\n').filter(line => line.startsWith('asset '));
                const oldAssets = catalog(saved);
                const newAssets = catalog(shipped);
                if (oldAssets.length < newAssets.length && oldAssets.every((line, n) => {
                    const before = line.trim().split(' ').filter(Boolean);
                    const after = newAssets[n].trim().split(' ').filter(Boolean);
                    return before.slice(0,5).join(' ') === after.slice(0,5).join(' ');
                })) FS.writeFile(path, saved.trimEnd() + '\n' + newAssets.slice(oldAssets.length).join('\n') + '\n');
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
