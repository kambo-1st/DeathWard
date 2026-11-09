# Private Frowning Gaper activation phase correction

The private corrected source-room review now advances Frowning Head state **after its AI force/wake checks**, matching the scoped native ordinary base-animation phase. The first activation update ends at Head frame1 while retaining force.6; the next AI update selects.72. Production defaults remain unchanged. Full native enemy acceptance is still open.

## Reproduced difference and correction

Before the correction, an actual Simulation probe with the private flag enabled ended its first activation update at frame0/awakened=false/force.6. The native initialization/AI/base-animation sequence ends at frame1/playing=true with the same force.6. The previous port advanced Head before the following AI tick; its force progression was already correct but its reported/visible Head state lagged by one NPC update.

The private branch now reads the old Head frame to select force, performs the direct-path wake/restart gate, then advances the overlay state. Rendering consumes the resulting post-base integer frame. A separate `headPlaying` runtime flag distinguishes a permanently awakened actor from an animation that has finished. The20-frame nonlooping Head stops at integer frame19; a fractional final frame is retained when native arithmetic retains it. Normal gameplay keeps the previous branch because the review opt-in flag defaults false.

The repeated frame-zero wake gate also resets fractional progress. Under a supplied.5 entity timeScale and a clear path every update, native Head repeatedly advances to.5 then restarts at0 on the following AI evaluation. A single clear-path pulse instead lets it continue and finish. The private branch now reproduces both controlled cases. These comparisons use the existing DeathWard Slow adapter solely to supply.5 timeScale; **they do not verify the full native Slow/status scheduler or authorize a production status change**.

## Evidence and verification scope

`capture-frowning-phases.py` executes original pinned Head initialization/AI gate code and the actual ordinary base-animation interval6860e7..68618c, with real mapped UCRT helpers. It records six cases of48 evaluations: never clear, immediately clear, delayed clear, a single clear pulse and the two fractional-time cases. Inputs include supplied direct-path results, healthy state and entity timeScale; visual layers and intervening NPC-wrapper logic are excluded. The ordinary AI-before-late-base order comes from the preceding scheduler checkpoint, not from executing the entire wrapper here.

Actual Simulation comparisons check the pre-AI frame and post-base frame/fraction, selected force, playing state and derived awakening/openness for every evaluation. Motion fixtures retain friendly-without-Charm isolation to exclude player-contact displacement; interactive enemies remain hostile. Native source force values, player pace, HP, damage, eight-direction firing and universal dodge are unchanged.

All288 phase states pass, as do all five focused suites. Actual Game native-player checks at30/60/144 render FPS and click arrival pass, and a240-frame Frowning cover launch/capture succeeds. The before/after probe preserves force.6 while correcting frame0/awakened=false to frame1/awakened=true. See `validation.json` and captured logs for results. The ten earlier supplied-route native trajectories and six continuous cover scenarios remain regression gates. The120Hz partition check remains a bounded numerical stress result rather than strict native equivalence.

## Review and remaining work

```sh
build/deathward_damage_health_review --source-room-review --cover-review --body 1
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-frowning-phases.py --check
ctest --test-dir build -R '^(gaper_family|gaper_trajectories|gaper_trajectories_substeps|source_room_review|first_floor_status_effects)$' --output-on-failure
```

Use1/2 to compare previous/corrected behavior and F8 to restart. The adapted3D face consumes `eyeOpenness`; this is not an Isaac sprite-art port or a claim of complete visual identity.

Next: verify Spider burst/idle movement, then Pooter wandering and enemy projectile timing. Gaper human visual acceptance, native prop-mask generation/cache behavior, complete NPC-wrapper/live cadence, contact/collision, status/champion/lifecycle branches and production rollout remain unfinished. HP encounter acceptance stays on hold; full first-floor parity is not complete.

Subsequent checkpoint: [Spider burst/idle and Pooter wandering](../spider-pooter-movement/README.md) now enables the scoped private movement corrections and compares192 native movement states at three physics partitions, plus16 Spider idle gates. Source RNG/acquisition/collision/full AI remain open; enemy projectile work is next.
