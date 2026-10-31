# Mushroom 300.0.0 — installed Repentance 1.7.9b

This is a new regular enemy, previously absent from the runtime. Identity and
habitats are preserved in [record.json](record.json): 23 base HP, no stage HP,
contact damage 1, and positive-weight Caves/Catacombs/Flooded Caves room templates.
Greed templates are separate evidence, not standard spawn probabilities. The
archived Host article, revision 270008, and its attribution remain in the
[previous source archive](../hosts/host-wiki-source.json). It describes 25%
closed damage, four cardinal/diagonal shots, contact damage and a 20% replacement
of Host/Red Host in Chapter 2, subject to an unlock.

The [native manifest](source/manifest.json) pins executable SHA-256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
The NPC dispatcher maps type 300 through entry 121 / case `699d97` to controller
`52fcb0`. `analyze-mushroom.py --check` rechecks dispatch, constants and the four
preserved instruction windows. [Animation metadata](animations/manifest.json)
comes from the installed Afterbirth+ archive after searching DLC overrides first;
only ANM2 metadata is extracted, not artwork.

## Normal controller

Initialization sets source state 3 and chooses `30 * (1 + RNG % 5)` blocked ticks.
It stores its starting position. State 3 first plays the six-frame Hide animation
once, then the looping Blocking animation. Pending incoming damage is multiplied
by `.25` while in state 3. It is resistance, not immunity, and the controller does
not single out bullets or exempt burning/explosion damage.

The normal hostile branch decrements the timer every source frame; it does not
require target range or line of sight. At expiry it chooses state 8 or 9 with
`8 | (RNG & 1)`. Both states play Reveal, which lasts six frames and triggers
Shoot at frame 3. It supplies velocity `(7,0)` to FireProjectiles mode 6 or 7.
Mode 6 emits `(7,0),(-7,0),(0,7),(0,-7)`. Mode 7 uses four sign combinations of
`7 * .7071067690849304`. These are world-axis patterns, not target-aimed fans.
The common postpass skips both the special falling-speed rewrite and the
1.2-speed/.4-parent-velocity boost for these modes. Normal shot speed is therefore
21 local units/second after the existing 30 Hz, distance × .1 conversion.

When Reveal ends, state 16 chooses `30 * (1 + RNG % 3)` exposed ticks and plays
Revealed. After this timer, it plays Hide. It remains in state 16, taking full
damage, during the entire six-frame retraction. Only when Hide finishes does it
return to state 3 and choose its next blocked timer. Subsequent cycles do not
repeat the extra initial Hide. No normal offspring or special death spawn exists
in this controller. The source restores horizontal velocity toward its saved
position each update; it does not pursue or drift toward the player.

## Local implementation and explicit adaptations

- Source HP × 3.2 gives 73.6 local HP. Contact and projectile damage use the
  established base 10 hostile damage path. The body's collision radius .7 is an
  authored 3D size, not a claim that source radius 13 was directly converted.
- Dedicated external `mushroom` configuration controls animation frames, timer
  quantum/choices, resistance, cross speed/coefficient, damage, lifetime and
  contact. Timer choices are discrete multiples of the quantum, not a continuous
  uniform delay. The chosen orientation survives event/projectile pressure.
- The body is anchored to its original local position. Whole four-shot bursts
  wait for capacity; local limits do not split a native attack into partial fans.
- Shots are physical combat-plane projectiles using the existing five-second
  local lifetime. Exact native projectile height/fall/lifetime is not claimed.
  Physical wall collision is retained, including when firing without sight.
- Local stun pauses the actor's timer/animation; it does not implement Isaac's
  petrification status or its loss of closed damage resistance. Death cancels an
  unemitted burst, and room suspension preserves phase/timer/orientation.
- Original-style procedural cap, pale stem/spots and facial features use no
  imported Isaac artwork. The cap raises/retracts with animation progress. Its reveal supplies the
  telegraph; the inherited single aimed warning ray is suppressed because it
  misrepresented the actual fixed-axis cross.
- Band 1 gets a direct ordinary specialist entry, weight 2 / cost 3 / cap 1,
  supported by its standard room-template habitat. Source Host/Red Host
  replacement probability and unlock route are not implemented by this entry.
  Mine, opening band, tutorial, hubs and expedition length are unchanged.

## Remaining acceptance

Native petrification/champion/control branches, source RNG ordering, exact
damage-queue/update ordering, projectile vertical physics and Host replacement
unlock/probability parity remain open. Full combat readability, balance and
controlled Linux/WASM performance acceptance are also open. Passing normal-state
tests and appearance captures is partial evidence, not a completed port claim.
