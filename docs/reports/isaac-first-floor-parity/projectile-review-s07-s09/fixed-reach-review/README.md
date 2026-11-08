# Slow firing with fixed half-room reach

**Current demo ready; checks pass; human verdict pending.** The user requested slow firing with a half-room maximum distance and no speed metrics. Earlier fixed-lifetime comparisons shortened reach when slowing the shots; that behavior is superseded.

```sh
./build/deathward_projectile_review
```

**1 Slow / 2 Steady / 3 Faster.** Steady is selected initially. These are feel choices; the demo displays no numerical projectile speed or flight-time metrics. Every choice reaches the same gold boundary when shooting from the starting position. **T** cycles close, middle, near-limit and beyond-limit targets. **F8** resets. Existing firing, movement, camera, dodge and **F11** shot-follow controls remain.

Shots now end at the explicit traveled-distance limit, just inside half the room. Their safety lifetime allows the full trip at each pace. The falling presentation follows the native-shaped curve stretched over that trip; it does not prematurely expire slower shots. Firing pauses grow with the chosen travel time so at most three ordinary shots naturally coexist. No renderer-only hiding is used. This intentionally changes review cadence, rather than claiming a native firing-counter port.

Larger bullet visuals, the collision radius, two-hit target health, accepted walking and universal dodge are retained. Normal expedition projectiles and cadence are unchanged; this remains an isolated preview with a temporary campaign.

The target fixture was also corrected: the earlier freeze duration was invalid and the legacy target kind bypassed native status updates. Targets now use the status-aware static source monster kind with a valid freeze request, whose success is required. Unhit witnesses are checked to remain stationary. The earlier logs do not establish frozen-target acceptance; current evidence supersedes that claim. Normal enemy behavior was not changed to fix the fixture.

[Current evidence](fixed-reach-review/validation.json) records same-boundary checks at each visible pace in cardinal and diagonal directions, sustained-fire checks at multiple input partitions with peak three, independent native arithmetic, eight-direction Game firing, inheritance, range/cover, stationary unhit targets, two-hit deaths and dodge. Terminal distance observations allow one simulation tick because cleanup may remove the projectile within the update. Exact range clipping is separate from that observation boundary. The [inspection image](fixed-reach-review/review.png) checks the room and plain-language UI, not human acceptance.

Still unfinished: your verdict on firing rhythm and flight feel, live Isaac calibration and normal-expedition integration; full native actor/birth/flags/item/RNG/hit-geometry acceptance, later combat stages and earlier health/enemy gaps. These are requested adaptation choices; source instruction matches alone do not certify the resulting balance.
