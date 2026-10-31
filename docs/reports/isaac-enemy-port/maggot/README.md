# Ordinary Maggot implementation checkpoint

Maggot **21.0.0** now uses a dedicated contact-only cardinal walker instead of
the generic wanderer. It does not pursue the player, shoot, charge or produce
offspring. Small Maggot **853.0.0** remains a distinct enemy.

The [source review](source-review.md) records the installed Repentance 1.7.9b
controller and animation metadata. The external profile in
`assets/mechanics/maggots.mechanics` supplies its movement, contact damage,
animation lengths and ordinary floor pools. Health is corrected from 40 to
**48**, using source HP15 and DeathWard's existing 3.2 conversion. Contact is
**12.5** after the shared hostile multiplier. Player defaults remain 100HP and
24 base damage.

Maggots use the Quarry and Storm floor bands, adapting their source Caves-family
and Corpse habitats. Their former ordinary Works-band route is removed.
[Generated witnesses](natural-witnesses.json) establish actual residents and
activation in both approved bands, plus movement in an interior-river room.

The reusable cardinal movement helper is shared with Spitties. Maggot retains
its own controller and cannot inherit their ranged or death attacks.

## Validation

- [All 86 Linux suites pass](native-full.txt), including the new cardinal walker
  suite and existing expedition, floor progression, hub and editor regressions.
- [Focused checks](native-focused-1.txt) cover source force/friction endpoints,
  independence from player position, physical cover and stuck recovery, stun,
  room suspension, ordinary death/clear, contact invulnerability and validated
  immutable external profiles. The default-kit bot defeats an isolated Maggot
  in 2.92 seconds with 100HP; this is not a full-floor balance result.
- [Six production WASM cases pass](web/results.json): open, cover, river, death,
  and actual seeded Quarry/Storm residents. No browser or GL errors.
- Shared-helper compatibility passes both the [native Spitty suite](spitty-regression-1.txt)
  and [four production WASM cases](web-spitty-regression/results.json), including
  Conjoined and Tainted attacks and Tainted death rings.
- [Eleven screenshots were individually inspected](visual-review.json): seven
  accepted as smoke views and four limited by foreground cliff occlusion.
  Spitty regression screenshots are preserved but not included in that count.
- Installed source extraction was rechecked; all **7,131** preceding report
  artifacts are unchanged. Served gzip files match their production build files.

The [checkpoint](checkpoint.json) pins the builds, source evidence and reports.
Fingerprint `36419b360ab65602` contains **178 definitions**, **172 reviewed
records**, **130 in progress**, **50 existing-unverified**, **461 missing**,
**12 excluded**, and **zero complete ports**. Ordinary pools still contain
79 direct identities, or 83 including conditional replacements.

## Remaining acceptance work

This is a partial implementation checkpoint. Native grid ranking, global RNG
and physics ordering, appearance activation, status/control/champion paths,
full item interactions and producer dependencies remain open. The small pale
body can be obscured by foreground cliffs; the existing enemy outline helps
locate it but does not establish all-camera readability. Full-floor mixed-build
balance and controlled Linux/WASM rendering performance are also unverified.
FPS labels captured during other builds are not performance measurements.

Regular enemies and required offspring remain the priority. Brain is next:
its source controller includes aligned charging and damaging creep that its
existing generic wanderer does not implement. The full 653-record goal remains
active.
