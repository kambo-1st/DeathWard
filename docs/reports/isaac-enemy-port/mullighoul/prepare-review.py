"""Write this slice's review; never alter any earlier checkpoint."""
import json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4]
BASE='docs/reports/isaac-enemy-port/mullighoul/'
OUT=ROOT/BASE
assert not (OUT/'checkpoint.json').exists()
manifest=json.loads((OUT/'source/manifest.json').read_text())
review={
 'scope':['808.0.0 Willo','817.1.0 Mullighoul'],
 'baseline':manifest['baseline'],'executable_sha256':manifest['executable_sha256'],
 'findings':manifest['findings'],
 'source_manifest':BASE+'source/manifest.json','animation_manifest':BASE+'animations/manifest.json',
 'wiki':{'articles':[{'title':'Fly','revision':268920,'url':'https://bindingofisaacrebirth.wiki.gg/index.php?oldid=268920'},
 {'title':'Mulligan','revision':271647,'url':'https://bindingofisaacrebirth.wiki.gg/index.php?oldid=271647'}],
 'preserved':BASE+'wiki-source.json','license':'CC BY-SA 4.0','attribution':'The Binding of Isaac: Rebirth Wiki contributors',
 'access':'Current fetches failed; pinned previously preserved full articles retained. Installed code and metadata resolve contradictory/abbreviated wiki descriptions.'},
 'adaptations':[
 'Source HP x3.2, XZ distance x0.1 and source velocity x3. Existing player defaults and global enemy damage multiplier remain unchanged. Willo has 19.2 HP; Mullighoul has 44.8 HP; both have harmless body contact.',
 'Willo uses one ownerless, single-player cohort per configured identity, ordered by stable local entity ID. Source regrouping is filtered by Parent pointer. Ordinary Mullighoul children have no Parent and use the ownerless cohort; summoner provenance does not make an orbit owner.',
 'Orbit targets use the global simulation clock at 60 Hz and source angular rate. Tracking is integrated by the existing 60 Hz simulation; attack/random/event clocks use 30 Hz. This is not a bit-identical native frame/interpolation implementation.',
 'Willo bodies ignore grid scenery, including outer cliffs, to preserve the source player-centred orbit. Shooting requires the actor centre inside the current room rectangle and within the source settled range. Rectangular room validity is a local approximation on irregular canyon borders.',
 'A Willo projectile uses source speed 10, one-update player prediction and NO_WALL_COLLIDE. Local vertical scale 0.05 converts source height -23, falling speed +1, damping 0.9 and acceleration +0.2/update into height 1.15, upward speed -1.5, gravity 9 and retention 0.9. Local radius 0.25 represents native ground termination at height -5. Four-second lifetime is a safety limit beyond ordinary landing, not a recovered native constant.',
 'Mullighoul hover height 0.6 is added to the standard body centre. Reusable swim navigation ignores water but respects solid obstacles, gates, raised terrain and room boundaries. Native grid collision 6 does not imply rock/wall-free flight.',
 'Existing capacity and retained-event rules preserve pending Willo shots and death births. Pending births keep rooms sealed. Stun cancels the attack and releases the cohort lock. These are integration policies, not full native status/item parity.',
 'Willo uses the existing Original procedural flying-body silhouette with a pale yellow-green tint and flashing Warn phase; Mullighoul retains the existing walker silhouette at elevated height. No source sprite artwork is imported.',
 'Downpour/Flooded Caves source habitats map to sparse wet Broken Quarry band-1 pools. Willo crossfire entries spawn pairs at cost 2 with max 3; Mullighoul pursuit entries cost 3 with max 1. These local weights/costs are not source room probabilities.'
 ],
 'remaining':[
 'Willo Parent-owned orbit, multiple-player averaging, friendly/item-control paths, fear/confusion/shrink attack suppression and complete status/time-scale interactions remain unfinished. Native initial 40-counter and appear lifecycle are not reproduced.',
 'Min-Min underwater spawn/dive and special states 6/7/9/10/13 are preserved in source evidence but not implemented by this ordinary-enemy slice. Additional boss work remains deferred by user priority.',
 'Mullighoul native nonzero NPC+bc6 death-count counter, champions and complete friendly/status/item interactions remain unresolved. The normal zero-counter death path is implemented.',
 'Shared Hive grid-path/cache/initial-impulse equivalence and exact Willo native half-frame tracking are not certified. Local physical navigation and room-boundary approximations are explicit.',
 'Generic silhouettes, all-angle readability, broad balance, controlled native/WASM performance acceptance and the full six-gate checklist remain open. Both exact IDs remain in_progress, not complete.'
 ],
 'natural_witnesses':[{'id':'808.0.0','seed':3,'floor':1,'room':6},{'id':'817.1.0','seed':80,'floor':2,'room':8}],
 'evidence_corrections':[
 'The initial source finding labelled flag mask 0x1000a00 as fear/confusion/freeze. Installed enums.lua establishes bits 9 CONFUSION, 11 FEAR and 24 SHRINK. Corrected before freezing; disassembly bytes are unchanged.',
 'Native init upper flag 0x2000 at +0x164 corresponds to bit 45 NO_PLAYER_CONTROL, not a knockback flag.',
 'Initial compile used nonexistent MonsterAttack::Aimed; corrected to existing Shot. Initial config used unsupported pool pattern artillery; corrected to crossfire. Both failed logs are retained.'
 ]
}
(OUT/'source-review.json').write_text(json.dumps(review,indent=2)+'\n')
