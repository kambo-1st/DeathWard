# Maw family: installed behavior review

Baseline: the locally installed Repentance 1.7.9b executable, SHA256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
`source/manifest.json` pins two dispatch targets, eleven bounded assembly windows,
and checked constants. `animations/manifest.json` pins four extracted animation
metadata files. No source sprite artwork is imported into the game.
`records.json` preserves exact XML identities, attributes and room habitats.
`maw-wiki-source.json` and `fly-wiki-source.json` preserve the archived articles
with revision attribution. The live Maw page returned403 during this review;
the live response is not treated as supporting evidence.

| Record | Installed normal behavior | DeathWard mapping |
| --- | --- | --- |
|26.0.0 Maw|20HP; pursuit impulse.13 and friction.93; acquire below200 units every7 frames; cooldown28 from acquisition; Shoot20, event4; shot speed7|64HP; source30Hz; distance x.1, velocity x3; physical flying navigation; speed21 shot|
|26.1.0 Red Maw|Same20HP; pursuit impulse tripled; no live shooting; four cardinal death shots at8|64HP; impulse.39; four speed24 projectiles; whole burst retained under capacity pressure|
|26.2.0 Psychic Maw|Same20HP and pursuit/cast; shot HOMING bit, Scale1.5; spawns96 with Parent=self at own position|64HP, corrected from88; larger.33-radius homing projectile; required retained child; whole-heart20 damage before existing hostile1.25 conversion|
|96.0.0 Eternal Fly|300HP; player-object collision; no status effects/hiddenHP; orbit linked parent; release as18.0 after parent's death|960HP invulnerable orbit hazard; parent-linked ellipse, growing90 frames; same entity becomes damageable Attack Fly and blocks room completion|

The projectile parameter written as1.5 in the Psychic controller is **Scale**,
not HomingStrength. Accounting for five intervening pushes places the write at
parameter offset+14; HomingStrength stays1 at+1c. FireProjectiles copies the
latter into projectile+374; named binding/getter evidence is preserved.
Native homing steers only within100 units of the target position plus half its
native frame velocity. It adds1.4 times the normalized **unpredicted** target
direction, then multiplies velocity by.92. It does not normalize to its initial
speed. Our external profile exposes equivalent world range10, impulse4.2,
retention.92 and gate prediction1/60second. Generic existing homing remains
separate. The native three-frame target reacquisition, friendly targeting and
status-altered strength are not implemented by this normal-player profile.

For Maw's parent-linked fly, ellipse radii are25x20, angular step.04π, phase
index0–9 timesπ/10 with direction reversed for even indices, and position follows
the target by.5 per native frame. Radius ramps with min(orbitTicks,90)/90.
The source Hanger branch uses60x50, half angular step and30-frame ramp; the
Isaac-parent follow factor is1. Those branches are represented but not accepted
as complete encounters here. The source grid-parent path requires a live
corn-poop grid entity and has no corresponding validated DeathWard prop yet.

A released fly retains the accumulated orbit counter; shared Fly code heals
maxHP/60 each native update while decrementing that counter. The local released
fly carries that finite duration. It is not a new kill/reward entity. A child
whose parent dies before it has orbited is removed, consistent with the source
positive-counter condition. Required children waiting for capacity are retained.

## Explicit gaps and adaptations

- All four records remain **in progress**, not certified ports.
- Source appearance/teleport overlays, parent visibility transitions, exact grid
  and outer-margin constraints, hard/champion/status/control branches and RNG
  parity remain open. The native random helper at68d7b0 is not yet decoded; no
  movement claim is inferred from it.
- Archived Fly prose says released Eternal Flies die on player contact; this
  controller did not establish the necessary contact-death flag. The port does
  not invent that flag. Further collision/death-controller review is required.
- Holy Leech's existing child cleanup is deliberately retained pending that
  parent's own review. This is not claimed as verified source behavior.
- Corn-poop ownership, the unported Hanger/boss parents, and full linked-body
  transitions remain incomplete. Only the Psychic Maw encounter is exercised.
- 3D terrain clearance, elevated flight, swept projectile collision, local damage
  conversion and finite-capacity retry are DeathWard adaptations. Flat shots
  use the established local five-second lifetime. Exact native projectile
  height/lifetime and controlled-target behavior remain unverified.
- The three Maw variants enter authored specialist pools in bands1–3 (Caves
  onward), maximum one per identity per room. No opening-floor placement. Costs
  and weights are authored; wiki replacement percentages are not certified
  native placement rules. Eternal Fly is dependency-only.
- Original-style procedural heads use pale, red and muted purple palettes;
  stitched mouths and a Psychic forehead eye distinguish variants. This remains
  a local visual adaptation, pending actual captures and readability review.
- Full balance, controlled performance and all six acceptance gates remain open.

## Integration findings during validation

The initial isolated Psychic capture exposed a pre-existing shader edge case:
normalizing the zero surface derivative of its halo line produced undefined
lighting, spread into a black rectangle by bloom. A guarded normal with an up
fallback removes the rectangle in the same100-frame scene; before/after PNGs
are retained. Psychic homing bullets now use a purple tint.

The initial resident capture also exposed discarded offspring in
`prepareRoomEnemies`: the generated-floor path queued a Psychic child, then
restored the active room's old queue without preserving the new one. Preparation
now flushes births and stores any still-pending requests with their room.
Room entry/departure restores these requests; a capacity-delayed child's
room round trip is explicitly tested. This fixes required offspring in real
seeded rooms, not only debug-spawn scenes.
