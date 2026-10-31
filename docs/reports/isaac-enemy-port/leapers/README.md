# Regular enemy port: Leaper and Sticky Leaper

Both exact tuples now have source-derived ordinary hopping and an occasional
high leap onto a committed target. Normal Leapers fire four cardinal shots only
on a high landing. Sticky Leapers leave non-damaging slowing creep and fire six
scattered physical shots on a high landing. Colored shots no longer inherit
unintended Tar impact patches. Sticky's source health corrects96 to89.6.

[Source review](source-review.md) separates installed1.7.9b evidence from local
3D adaptations. [External configuration](../../../../assets/mechanics/leapers.mechanics)
controls source30Hz phases, selection, interpolation, projectile flight and creep.
New bindings reuse the target_hop controller and immutable validated reloads.
Whole landing packets wait for capacity; stun, inactive rooms and death preserve
or cancel them deliberately. A ground marker shows the committed landing point.
The Original style, protagonist100HP/default damage,4–8-floor structure,
tutorial, Mine roster and hubs remain unchanged.

Normal Leapers use sparse band1–2 ordinary pools; Sticky Leapers use band2.
[Natural witnesses](natural-witnesses.json) are Rourke seed2/floor4/room4 and
seed8/floor4/room3 respectively. Source room templates support these middle
habitats. Weights and room caps remain authored DeathWard pacing.

## Validation and limitations

- [Native full run](native-full.txt): all83 suites pass. The
  [focused run](native-focused-final.txt) checks ordinary/high timing, snapshot
  targeting, exact cardinal/scattered shots, source flight, creep, capacity,
  stun, room suspension, death, physical collision windows, actual cover/river
  traversal, legal target correction, immutable reloads and seeded placement.
- The default100HP/24damage starting kit kills both isolated variants. This
  is an initial viability check, not mixed-build balance acceptance.
- The native executable and production WASM were rebuilt.
  [Seven accepted browser cases](browser-summary.json) cover both isolated
  variants, cover, river, both natural encounters and owner death. Results span
  three preserved runs; superseded failed cases are not counted as passes.
  [Twelve inspected images](visual-review.json) include ten accepted smoke views
  and two limited views. Neither this nor FPS labels certify full visual or
  controlled-performance gates.
- Earlier fixture failures are retained. A stationary player consumed landing
  shots and displaced the enemy, so projectile-lifetime/landing-accuracy tests
  now move the player after the target snapshot. A browser cover fixture also
  used an illegal scripted floor position; its failure and corrected route are
  retained. These corrections did not relax production collision rules.
  The river test now verifies traversal/high landing directly: a stationary
  player can immediately consume all landing bullets, so that case does not
  require a surviving-volley screenshot. Isolated moving-player cases verify
  the rendered volleys separately.
- The browser harness initially requested a missing default Playwright binary.
  Chrome156 then progressed unusually slowly; its partial run and diagnostic
  were preserved. Validation uses the previously validated Chrome149 instead.
  This is not evidence of a game-code performance regression or a completed
  browser-performance gate.
- [Historical integrity](historical-check.json): all6,810 preceding enemy-port
  report artifacts remain byte-for-byte unchanged.

The full roster remains unfinished:177definitions,168reviewed,126in progress,
53existing-unverified,462missing,12excluded and **zero complete six-gate ports**.
There are76 direct ordinary pool identities,80including replacements.
Special status/control branches, all damage classes and item interactions,
native hard-mode integration, exact creep footprint/slow strength, all-camera
readability, mixed-build balance and controlled rendered performance remain open.
Regular enemies and required offspring remain ahead of further boss work;
ordinary Hopper and Flaming Hopper are next.
