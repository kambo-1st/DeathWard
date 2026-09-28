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
        for (const hub of['town', 'frontier']) {
            const destination = '/persist/' + hub;
            FS.mkdirTree(destination);
            for (const name of['town.scene', 'town.nav', 'town.labels']) {
                if (!FS.analyzePath(destination + '/' + name).exists)
                    FS.writeFile(destination + '/' + name, FS.readFile('/assets/' + hub + '/' + name));
            }
            // The original Frontier labels gave the cooking pot its parent fire's
            // name. Migrate only that known label; keep authored scenes and names.
            if (hub === 'frontier') {
                const path = destination + '/town.labels';
                const labels = FS.readFile(path, {encoding: 'utf8'});
                const corrected = labels.split('\n').map(line =>
                    line === 'part_0106 SM_Prop_Campfire_Small_01' ?
                        'part_0106 SM_Prop_Campfire_Pot_01' : line).join('\n');
                if (corrected !== labels) FS.writeFile(path, corrected);
            }
        }
    });
#endif
}
} // namespace dw
