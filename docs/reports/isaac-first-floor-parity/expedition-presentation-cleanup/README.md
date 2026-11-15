# Expedition presentation cleanup — 2026-11-15

Accepted D09c keys/model committed as `b466b5a3`; no push. The user then selected this cleanup. It is implemented, developer-verified and accepted by the user on 2026-11-15 ("ok, commit next steps?"). This report accompanies the requested cleanup commit.

- Removed corridor floor chevrons and paired doorway lantern posts, including their shadow geometry and colored glows.
- Removed optional supply-cache generation. New/regenerated floors have no cache walls, gate, reserved enclosure or cache payout producer.
- Physical corridors, locks/combat seals, entrance/exit markers, ordinary rocks/ore/powder and source pickup/chest arrangements remain. Accepted controls/balance and the user's preset are untouched. No new tuning option or schema change.

Cache types and isolated historical destruction fixtures remain for compatibility, but ordinary generation creates none. Removing the cache's placement draws changes placement of ordinary breakable props within their independent stream; it does not change source room selection or floor geometry. Existing running processes need the rebuilt executable; regenerating a floor with **Apply map changes** also uses the new generation. Demolition smoke scenes now demonstrate a retained ordinary rock instead of requiring a cache.

Verification passed:

- Main executable and affected test targets built. Existing unrelated compiler warnings remain.
- [Generation/destruction and fly/dung suites](tests.log): 256 Mine/Canyon first/final floors have no cache, retain the expected props, and preserve mandatory objective/door/key routes. Historical synthetic explosion fixtures still pass.
- [Actual Game/Renderer key check](keys-input.log): normal-health key access/dynamite, collection, live policy, Apply/export/load, revisit/retry and source214 model/shadows pass.
- [Keyboard/door check](keyboard-input.log): existing locks, key spending, controls and floor exits pass.
- [Updated demolition smoke](demolition-smoke.log) exits successfully; [capture inspected](demolition.png). The unchanged source214 key-room screenshot was also inspected after rebuilding.
- Original165% preset SHA256 remains `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.

The rebuilt interactive game was handed off in seed285, displayed room6 (source214), using the original165% preset, normal6-half-heart health and no god mode. [Launch record](interactive-handoff.json). Walk through a passage to check the removed floor arrows and posts; the key rock enclosures remain intentionally. Apply map changes or another generated floor also has no supply cache.

The scoped cleanup is accepted; no cleanup implementation remains. Next proposed: **D09d ordinary bomb/dynamite pickups** in natural clear rewards and one compatible complete room layout, with collection/inventory/timing, no revisit duplication, live tuning/export/load and a short main-game check. This requires separate selection. Fuse/blast/self-damage and keyed-door spending remain separate D10 deliveries. Broader native pickup/room coverage and gameplay save continuity remain open; bulk parity stays paused.
