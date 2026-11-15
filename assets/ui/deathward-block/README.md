# DeathWard Block — second font candidate

Requested on 2026-11-15 after preserving the first Anton-derived candidate in
commit `6997ff36`. This second candidate is complete and developer-verified,
and is preserved in the requested checkpoint commit. The user judged it too similar to the reference and requested a distinct redesign retaining the silhouette style. This candidate is not the selected final font.

- `DeathWardBlock-Regular.otf`: genuine OpenType CFF font with vector outlines.
- `specimen.png`: text rendered from this OTF, following the supplied alphabet.
- `comparison.png`: committed DeathWard Rough above, new DeathWard Block below.
- `reference.png`: the user-supplied image used to create the new outlines.

The first two alphabet rows provide A–Z. The next two provide subtly different
capital shapes for a–z. The final row provides 0–9, including the slashed zero.
This is therefore an **all-caps display candidate**, including when ordinary
ASCII lowercase is typed. The square S/G, cut corners, narrow counters and edge
wear come directly from the supplied shapes, rather than a new random mask.

The 62 pictured glyphs were traced as vector contours, with sub-pixel contour
simplification to remove raster stair steps. Letter counters are preserved;
maximum mask-area difference after simplification is below 0.67%. Widths follow
the reference, with consistent sidebearings. No outline, background, bitmap
table or runtime texture effect is added.

The committed Anton-derived DeathWard Rough remains the font base. Its other
glyphs and all 978 Unicode mappings are retained, but those additional shapes
were **not** redrawn from this reference. Inherited substitution/positioning
tables are removed from this candidate so lowercase ligatures cannot substitute
the old lowercase shapes. Complete typography/language acceptance is not claimed.

Verification: the font reloads as `OTTO`/CFF, all tables decompile, all 978 mapped
characters rasterize through FreeType, and all 62 rebuilt glyphs rasterize at
16/24/48/96/220 pixels. DeathWard's actual bundled `stb_truetype` loads it and
rasterizes all 94 non-space printable ASCII characters. Both rendered previews
were visually inspected. `manifest.json` and `validation.json` record details.

To rebuild, use Python with `fonttools`, `pillow`, `numpy` and `shapely==2.1.2`,
then run `python3 build_font.py`. Anton's license is preserved in `OFL.txt`;
the supplied reference's provenance is the user's attachment.

Next: a distinct redesign of the letterforms. This traced candidate remains a comparison artifact; it is not visually accepted for production.
This work only creates the font artifact. Existing fonts, game code, gameplay,
presets and build configuration are unchanged.
