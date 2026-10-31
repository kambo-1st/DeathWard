# Shared regular-enemy adaptive armor

The reviewed target remains the installed Repentance1.7.9b executable, SHA256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
The [manifest](source-manifest.json) pins the previous bounded disassembly,
installed DamageFlag definitions, native bomb producer and exact XML records.
Earlier reports remain unchanged; this is a subsequent implementation slice.

## Verified native algorithm

NPC initialization sets `+b90` shieldStrength to zero and `+b94` history length
to120. Config fields `+e0/+e4` populate them at692a5e–692a7c. NPC Update at69b681
calls6adfd0. That function processes a complete pending damage list, appends the
raw current frame total (including zero frames), then averages over the actual
number of history entries and multiplies by30. It retains at most120 entries.

The soft cap is current body maximumHP divided by shieldStrength. When recentDPS
exceeds it, every ordinary hit in that batch receives the same multiplier:
`r + max(.09 - .18*r, 0)`, with `r=cap/recentDPS`; otherwise it receives1.
The current hit participates before reduction. This makes an isolated large hit
reduce itself even when history was previously quiet. No separate pre-clamp has
been inferred from that effect.

Native flag0x2000 (`DAMAGE_INVINCIBLE`) excludes damage from history and scaling.
Flag0x40000000 (`DAMAGE_IGNORE_ARMOR`) contributes to history but bypasses scaling.
Neither is projectile piercing. `DAMAGE_FAKE` is a separate flag,1<<21.
Explosion bit4 alone does not grant either bypass.

The native Bomb initializer at67acd3 clears byte+398. Its explosion call at67cd48
selects4 when that byte is nonzero and0x40000004 otherwise, then calls6d26e0.
This supports bypass for ordinary physical Bomb bodies. It does not establish
that arbitrary NPC explosion markers or secondary item explosions bypass armor.
DeathWard maps its real dynamite, supplied bombs and physical enemy bombs to the
ordinary Bomb path. Nonphysical markers sharing the scheduler remain separate.
The alternate source Bomb byte branch is not currently exposed as a game mechanic.

## Installed regular profiles

| ID | Name | Source HP | Local HP | Strength |
| --- | --- | ---: | ---: | ---: |
|14.2.0|Tainted Pooter|75|240|30|
|22.3.0|Tainted Mulligan|100|320|30|
|25.6.0|Tainted Boom Fly|20|64|10|
|29.3.0|Tainted Hopper|80|256|30|
|31.1.0|Tainted Spitty|60|192|30|
|61.7.0|Tainted Sucker|14|44.8|10|
|855.0.0|Level2 Charger|40|128|2.5|

All use120 history frames. Maximum HP uses the existing3.2 conversion;
player defaults are unchanged. Source HP corrects the previous
legacy22.3,31.1 and61.7 values. The latter two behavior implementations remain
**existing_unverified**; armor data is not evidence of their complete AI fidelity.
No encounter weights or floor routes change in this slice.

## Pipeline and declared local policies

The existing60Hz simulation accumulates accepted hits on each independent armored
body until its next30Hz armor tick. Hits retain their source and original chain
budget; replay does not consume a second generation admission. Item damage/kill
hooks run after actual resolution. Newly emitted item attacks clear inherited
armor bypass and the internal replay marker. Execution resolves immediately and
cancels deferred hits. Released projectiles retain their existing ownership rules.

Pending buffers are bounded per body by the configured ordinary queue capacity.
A full buffer leaves the next accepted hit in the ordinary queue until a source
tick frees space. A source batch resolves atomically; it can contain hits admitted
on both preceding60Hz frames. This is not a new global per-tick work limit.
The full-game workload/performance gate remains open.

Inactive rooms freeze history, pending hits and fractional clock. Re-entry restores
only chains referenced by pending damage, with their accepted budget and kill
counts, and recomputes their active pins. Stun continues armor history while its
behavior controller handles movement/attack interruption. Modal pause freezes the
whole simulation. These lifecycle choices are explicit DeathWard adaptations.

The native helper can select parent-owned history for linked components. This
slice deliberately validates independent ordinary bodies only; shared boss and
component ownership require another contract. No new boss implementation is added.

## Remaining source reconciliation

The previously archived wiki describes extra initial protection and a large-hit
adjustment. Those claims have not been tied to the installed path above; neither
has been invented. Native special statuses, every damage producer/flag combination,
champions, control effects and exact global update ordering remain unaccepted.
Later public EntityNPC offsets differ from this executable and are not substituted
for its measured layout. Dedicated Ascent routes, remaining regular AI gaps,
full build balance and rendered performance are separate unfinished requirements.
