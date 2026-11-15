# DeathWard Rough

An Anton-derived font artifact requested on 2026-11-15. The supplied reference
guides its heavy, irregular block-letter appearance. The revised scope excludes
an outline and background.

- **Font:** `DeathWardRough-Regular.otf`, a genuine OpenType CFF font.
- **Preview:** `specimen.png`, rendered from the generated OTF.
- **Comparison:** `comparison.png`, original Anton and the derivative at equal size.
- **Source:** `../../Anton-Regular.ttf`, retained unchanged.

The modifications are actual vector glyph contours: individual width and lean
changes, more angular bowls, a barred capital I, uneven edges and small,
deterministic chips cut by an irregular vector distress mask. Interiors stay
mostly solid, following the reference. There is no bitmap mask, runtime effect,
black background or outline. Lowercase, punctuation, accents and digits remain
available; the original character map and glyph order are retained.

The derivative uses a distinct family name, **DeathWard Rough**, and retains
Anton's copyright and SIL Open Font License. `OFL.txt` comes from the
[Google Fonts Anton source](https://github.com/google/fonts/tree/main/ofl/anton).

To rebuild, install `fonttools`, `shapely==2.1.2` and `pillow` in a separate Python
environment, then run `python3 build_font.py`. The script records source/output
hashes and validation in `manifest.json`. It checks CFF round-trip loading,
preserved glyph IDs and Unicode mappings, valid outline geometry and no loss of
visible glyphs, then renders the specimens with FreeType through Pillow.

The source GDEF/GPOS/GSUB tables are retained. Their complete language-specific
shaping and mark positioning have not been visually reviewed after the outline
changes. The supplied alphabet and game-word specimens are the visual scope of
this delivery.

Verification passed: FreeType rasterized all 978 mapped characters, all font tables decompiled, and the actual bundled `stb_truetype` loaded the CFF OTF and rasterized all 94 non-space printable ASCII glyphs. Both previews were visually inspected. See `validation.json`.

The font file is complete. On 2026-11-15 the user requested committing this candidate, then trying a second version closer to the supplied reference. Final visual acceptance remains open. Game integration
was not requested in the revised scope; no renderer, existing UI fonts, presets,
build configuration or gameplay files were changed.
