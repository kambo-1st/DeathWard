# Incomplete whole-tear investigation

This is a diagnostic,not an accepted native capture. Run from repository root.
The supplied tear has collision damage3.5,visual scale1,friction1,zero flags and
grid collision class0. Room descriptor/config pointers are supplied using the
existing native boss-fixture layout. Complete native initialization is absent.

Whole Update642990 reaches native size/animation setup651770. Its uninitialized
animation cache requests `RegularTear6` through formatter411f70. The diagnostic
stops there explicitly rather than executing unresolved import data or skipping
initialization. No C++ gameplay result is accepted from this incomplete probe.

Next: establish native initialized tear size/cache/geometry and the actual
`RegularTear6` metadata/formatting boundary. Original collision-damage setter
6500d0 writes2e0 and3a4;visual scale370/374 is separate. Native XML base radius7
and the current DW resolved radius.14 require effective native initialization/
scale/collider verification before spatial acceptance. Do not infer an effective
radius from the XML alone. Full flags/character/item/child paths,grid and damage
collision ordering and live observations remain open.
