# Western Music score

Imported from the user's `Assets/Western Music` pack in the local Unity project.
These are the supplied recordings, separate from DeathWard's synthesized effects
and ambience. The original pack's rights apply to these imported assets.

| Situation | Original track |
| --- | --- |
| Black Creek hub | 12. In This Town |
| Frontier hub | Update v1_5 / Rebuilding |
| Canyon exploration | 07. The Hunt - The Journey |
| Mine exploration | 04. Mystery at Sundown |
| Ordinary combat, either mission | 08. The Hunt - The Thrill |
| Sheriff or canyon final encounter | 09. The Hunt - The Terror |
| Successful expedition summary | 10. Chasing Victory |
| Death animation and defeat summary | Update v1_5 / Sad Emotions |

| Event | Original stinger |
| --- | --- |
| Leave a hub for a mission | 01 - Whistle & Guitar |
| Enter the final encounter | 05 - Rattle |
| Complete a mission successfully | 07 - Guitar Shimmer |
| Player death | 02 - Snare & Bell - B |

Ordinary kills, room clears, pickups and hub travel do not play musical stingers.
One stinger plays at a time, in stereo at its original pitch. It briefly lowers
the background score. Death and its summary share a single cue. Returning to a
hub stops the previous event's stinger; retreat uses that hub's theme.

Tracks loop and crossfade; ordinary room transitions do not restart them. Combat
has a two-second release before returning to exploration. The three Hunt mixes
share their duration and are aligned to the current playback position when
crossfading. Other compositions begin at their own beginning. Pause lowers the
score and keeps streams running. The editor fades the score out. Music and
stingers share the separate **Music** volume control, initially 40%.

Eight stereo 44.1 kHz Ogg/Vorbis streams and four PCM16 stereo WAV stingers are
packaged. No stems or unused alternate tracks are included. Conversion retains
the full duration and stereo arrangement, applies a constant gain to balance the
mix (up to +6 dB, with peak headroom), and adds 10 ms fades at file boundaries to
avoid clicks. This does not remove pauses or rewrite the source compositions.

`manifest.json` records source names, source/output SHA-256 hashes, duration,
channels, rate and gain. To regenerate with `numpy` and `soundfile` installed:

```sh
python3 scripts/import_music.py '/mnt/c/Users/bohus/My project (1)/Assets/Western Music'
```

The normal game build uses these packaged files and does not need the Unity
project, Python or a connection to the Windows filesystem. A missing music pack
leaves existing effects and ambience available.
