# Ordinary tear firing counter — Repentance1.7.9b

This captures original x86 code from the installed executable, SHA256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
It does not establish complete weapon or live-game acceptance.

`analyze-player-fire.py` executes the complete ordinary WeaponTears counter updater
at `0x95c790` and the supplied ordinary uncharged firing gate at
`0x959dee..0x959e39`. The latter receives the counter pointer, held input,
interpolation flag and cached MaxFireDelay that its surrounding branch prepares.
No executed instructions, native calls or imports are replaced. Source listings
also preserve the player weapon-update call site and cached delay copy.

The counter decreases on the main30Hz phase when greater than−1. The alternate
player phase leaves it unchanged. Firing requires a strictly negative counter;
each emission adds `MaxFireDelay+1` to the existing counter, retaining fractional
carry. The ordinary gate limits one main phase to eight emissions. Idle counter
values can remain below−1. The CSVs contain200 supplied update cases,360 gate
cases and4,800 sequential states across integer/fractional delay, odd-phase input,
release/repress, high-rate, reduced time-scale and the enabled Scatter item's
fractional cadence cases. Owner-null update cases
exercise the native fallback time scale1.

The baseline adapter uses these rules in `PlayerFire.hpp`. Legacy firing remains
on its existing timer. Universal dodge retains its boost and immunity. Each
emitted root advances the cylinder once; pellet count does not multiply that
advance. `fireCooldown` remains a derived compatibility timer; `nativeFire` is
authoritative for baseline emission timing. Explicit encounter/player resets also
reset the native counter. The desktop input queue retains short taps until a
main firing phase can consume them; bomb actions still consume their input
immediately. This preserves DeathWard's existing short-tap promise; native input
collection/debounce is not established by the bounded weapon fixtures. Floor transfer retains copied firing state, matching
the prior cooldown carry policy; native transfer behavior remains unaccepted.

Remaining: full caller branch reachability, charge/special/item weapons, native
shot-birth overshoot/interpolation, global phase alignment across room/floor
transitions, actor ordering, persistence and matched live-game observation. Large
simulation steps combine emissions at the caller's current position. Existing
room/collider scale and projectile acceptance gaps remain open.

Regenerate or verify (Python pefile/capstone and Unicorn2.1.4 required):

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-player-fire.py
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-player-fire.py --check
ctest --test-dir build -R '^(native_player_fire|isaac_baseline)$' --output-on-failure
```

Next birth-order investigation (disassembly leads, not executed acceptance):
`959e02..959e0e` stores `-1-counter` in the local passed into the emission
helper `9453d0`; the player branch calls `757690` at `945412`. The emission loop
subtracts `MaxFireDelay+1` from that local at `95c1e5..95c20b` between emissions.
The parameter's spawn/first-update effects still require execution and comparison;
these call sites do not establish complete birth timing by themselves.
