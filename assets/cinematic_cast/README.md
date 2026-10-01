# Westbound passengers

`elder_man.glb` and `elder_woman.glb` reuse the user's POLYGON Western business-man
and woman meshes. `conductor.glb` adapts the business-man outfit with a shorter cap
and navy uniform material. Silver hair accents distinguish the older travellers.
The protagonist continues to use the existing Bandit model.

The three new GLBs retain the original embedded Western atlas and are retargeted
to the retained 48-bone Bandit rig with its Idle and Walk clips. Sitting and small
speaking gestures are applied to this rig by the cinematic renderer. These are
provisional cast treatments rather than bespoke facial acting or voice recordings.
Original Synty asset licensing still applies.

Regenerate with Blender 3.6:

```sh
blender --background --python scripts/create_cinematic_cast.py
```

The script expects the original FBX at the user's existing Unity project path;
runtime builds use the checked-in GLBs. It remaps the source finger-group suffixes,
removes Unity-only vertex masks, and preserves the runtime's texture/skin format.
