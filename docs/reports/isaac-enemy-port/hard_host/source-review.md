# Hard Host source review — installed Repentance 1.7.9b

This extends the previous Host-family checkpoint. It is a partial port, not a
completed parity claim. The exact executable and six bounded instruction windows
are pinned in `source/manifest.json`; `analyze-hard-host.py --check` verifies them.
Identity, habitats and the 71-frame animation with Open10/Close54 are preserved in
the preceding Host report. No source artwork was imported.

Hard Host27.3 has15sourceHP and contact damage1, unlike the contact-free normal
Host. Local values are48HP and established hostile contact damage10. It shares
the normal Host acquisition, armor and hit-delay controller. Its only ordinary
attack event is Close54. It aims at the live target, spawns1000.72 subtype2 at
20source units forward, and assigns the original Host as parent. The old generic
bullet attack and112HP are replaced. Mines/Ashpit habitats map to the authored
band1 specialist pool, cap1 per room. This does not add it to the Mine roster.

The1000.72 generator starts with240-frame timeout. Every even source frame it
advances30source units. Subtype2 is straight through frame6; afterward each step
uses an independent angle offset `(random-.5)*150*min(1,(frame-6)/20)` degrees
relative to the original heading. It does not cumulatively turn its heading.
The local scale is3world units every2/30seconds; the launch offset is2. Source
RNG ordering and whether age0 can participate on the spawn update remain open.
The port uses ages2,4,... and a separate seeded stream preserved across retries.

At each accepted point, a rock poof62 is spawned and `6d1750` receives damage10,
radius20*SpriteScale, entityLineCheck=false, original spawner, and damage flag
0x1000000 (CRUSH). This is the damage/grid helper, not the bomb visual wrapper
6d26e0. The generator stops at nonzero grid collision but still applies its last
pulse; pits/grid type7 and grid type15 skip the pulse. Out-of-room positions
remove it. The local implementation uses32NPC damage,10base player damage and
a2world-unit radius. Crush is separate from Physical, Flame, Burning and the
explosionDamage flag. It must not accidentally trigger fire-specific reactions.
Hostile pulses can damage other NPCs and companions, but not their source.

The terrain helper scans nearby grid entries with cover checks and invokes their
destruction handlers. Local cracked rocks, dung and optional cache entrances can
be destroyed; powder barrels use their existing fuse. Ore/resource gates and
structural cache sides retain DeathWard's existing protection. This is an explicit
resource-rule adaptation, not a native restriction. Swept3D tracing prevents
tunnelling through narrow props; source stepping uses destination grid cells.
The local terminal pulse occurs just outside the hit surface. Entity damage
keeps the source's no-line-check behavior; terrain recipients use a pre-change
cover snapshot. Pits/room edges consume the generator without a remote pulse.

The slam also visits players within a strict120source-unit radius, without a
sight check. It passes a normalized outward vector times3 and scalar9 to virtual
slot0x50. The installed Player vtable resolves this to794280: it adds horizontal
velocity, clears height and sets vertical speed to-9. This is a **hop**, not just
a flat push. The grounded player update adds vertical speed to height then adds
1.1gravity per30Hz frame. Local conversion uses initial upward27world/sec and
gravity99world/sec2, matching heights. Horizontal impulse9world/sec uses a local
.8 per-source-frame retention alongside normal controls. Native locomotion
friction, control/flying-player exceptions and exact collision masks remain open.
Horizontal navigation stays grounded, so the hop cannot unlock routes over walls
or pits. Physical height changes and ground-pulse immunity last until landing.

The emitted generator survives owner death/room clear, and is removed on room
change. Unemitted slams are cancelled by death or stun. Hazard/event saturation
retains the whole pending slam/pulse; retries preserve RNG and target point.
Existing Quake waves keep their earlier continuous front implementation.

Remaining: native status/champion/control transformations, special grid/item and
NPC immunities, full knockback/mass physics from crush pulses, native RNG/grid
parity and shared update order; full combat readability, balance and controlled
Linux/WASM performance acceptance. The port's original stone cap/rock crests and
physical hop are visual adaptations.
