# Mr. Maw family — implementation checkpoint

The dedicated linked body/head controller replaces the old generic orbit/charge
behavior. Source and implementation details are in [the review](source-review.md).
[Progress](progress.json) records current validation and outstanding work.
The [checkpoint](checkpoint.json) freezes the implementation evidence. This is
partial acceptance, not a declaration that all six gates are complete.

- Independent body/head health; ordinary80/80, red80/32.
- Source-timed pursuit, predicted head throw and spring return.
- Correct surviving Maw or Gusher; spontaneous separation without kill rewards.
- Four cardinal red-head death shots, retained under capacity pressure.
- Eight harmless owned neck pieces with original low-poly rendering.
- External immutable profiles and appropriate ordinary seeded stage pools.

[Focused Linux checks](native-carried-pose.txt) pass, including capacity pressure
and room completion. [Seven generated residents](native-residents.txt) activate
and simulate240 ticks each across both forms' three floor bands, including two
interior-river rooms. These are actual generated residents, without injection.
[Discovery candidates](natural-witnesses-candidates.json) and
[verified witnesses](natural-witnesses.json) distinguish discovery from activation.

The [first full run](native-regression.txt) passed85/88. Follow-up tests now cover
required heads in room counts and the owned-only neck role. The stronger room
check found a real newborn-head elevation bug beside scenery; attachment was
corrected. The old Brain seeds were replaced with newly discovered natural
witnesses for both habitat bands and an interior river; those checks pass.
The corrected [floor-regression run](native-attachment-fix.txt) passes.
[Passing evidence covers all88 registered Linux suites](native-summary.json).

Four native and twenty-one browser images have been [individually inspected](visual-review.json):
seventeen accepted smoke views and eight limited views.
The earlier Linux survivor capture now shows the released head fully above the
HUD. Browser open-room and river views show the linked pair and cord, but some
views remain limited by cover, HUD overlap or simulation advancing between the
probe and screenshot. In particular, the initial browser filenames ending in `attached` do not
establish an exact attached pose; the later exact-frame set below corrects this.
More camera/readability review remains.
The FPS overlays are not controlled performance evidence.

Both native and production WASM builds containing the attachment and carried-pose
fixes succeeded. [All six focused production browser cases pass](browser-summary.json),
including both body forms, both survivor transitions, cover and a river.
The served build hashes were checked against the production artifacts.
[Four starting-equipment combat checks](native-kit-initial.txt) also pass using
real movement and firing input with the default player health and damage.
These are isolated encounters, not full-floor balance approval.

[Seven actual seeded populations also pass in WASM](web-residents-final/results.json),
including both forms in bands1–3 and two river rooms. The production build's
verification-only observer now captures pixels directly after drawing, with
the matching simulation probe. [Three exact-pose cases pass](web-exact/results.json).
The attached normal/red heads and released survivor have been visually inspected.
An earlier animation-callback wrapper produced blank images: those files remain
in `web-residents`, explicitly rejected as visual evidence. Its behavioral
assertions passed, independently of the capture failure.

Seven final generated-room images have also been inspected. Two retain foreground
cliff occlusion limitations. Remaining source status/control details, full visual
readability, broader balance and controlled performance are open. Preserve the
preceding frozen Brain checkpoint and earlier reports. Regular Baby/Angelic/
Wrinkly enemies are next; their [source review](../baby/source-review.md) is ready
for implementation. No complete six-gate port is claimed.
