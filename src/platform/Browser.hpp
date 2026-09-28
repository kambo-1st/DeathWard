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
        }
    });
#endif
}
} // namespace dw
