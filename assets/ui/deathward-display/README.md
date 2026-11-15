# DeathWard Display

The approved six-letter Block study is now extended to a usable Latin display
font. The uppercase **A B D G R S** retain the approved CFF drawing programs and
horizontal metrics exactly. The other capitals, alternate-cap lowercase, digits
and punctuation have their own structural drawings in the same heavy, uneven,
hand-cut style, with sparse deterministic edge wear applied afterward.

**Status:** the user accepted the complete font ("Nice commit and use it as a
main font"). The accepted artifact and six-letter study are committed as
`32991e0d`. Main-game integration is committed as `53c10729`, developer-verified
and accepted by the user after the native interactive launch; see
`../../../docs/reports/main-font-integration/README.md` for the scope and screenshots.

## Files

- `DeathWardDisplay-Regular.otf`: actual OpenType CFF font, family **DeathWard
  Display**, style **Regular**. It can be used directly without the generator.
- `specimen.png`: full alphabet, alternate capitals, digits and ASCII punctuation.
- `comparison.png`: previous Block and new Display at the same font sizes.
- `readability.png`: words at 16–104 px, punctuation and accented Latin samples.
- `coverage.json`: exhaustive styled/inherited character inventory.
- `manifest.json`, `validation.json`: hashes, checked scope and remaining work.
- `build_font.py`, `glyph_designs.py`, `symbol_designs.py`: reproducible construction.
- `requirements.txt`, `OFL.txt`: build dependencies and retained font license.

## Coverage

All 94 non-space printable ASCII characters use the new style: A–Z, a–z,
0–9 and all 32 punctuation/symbol characters. Lowercase keys produce alternate
capital drawings, matching the reference's two capital alphabets; this is an
all-caps display design, not conventional small lowercase.

The new style also covers the Latin-1 and Latin Extended-A **letters**, matching
precomposed Latin accents, common typographic punctuation and currency signs.
There are **648 styled Unicode characters**, including the six approved capitals.
The font retains all **978 Unicode mappings and 1,326 glyph slots** from its
Anton-derived base. The remaining **330 mapped characters** retain inherited
coverage; this includes spacing/control characters, combining marks, uncommon
Latin/phonetic letters, some other-script forms and less-used symbols. Their exact
inventory is in `coverage.json`. This delivery does not claim that all Unicode
or every inherited character has been redesigned.

Precomposed accented letters are assembled from the new base drawings and
matching chunky marks. Accents sit above the capital height; horns reserve their
extra horizontal extent, and ascent/descent metadata accommodates stacked marks.
Standalone combining-mark layout and complex text shaping have not been rebuilt
or accepted. Use precomposed (NFC) Latin text for this delivery. No new ligature
substitution or pair-kerning feature is added; encoded Latin ligatures have
matching drawings. Spaces retain their existing advance.

## Verification

- Genuine `OTTO` / CFF reload; all font tables decompile and the family is
  recognized as DeathWard Display Regular.
- All six approved CFF programs and metrics compare exactly with the study.
  Other modified outlines are limited to the documented 642 glyphs.
- All 978 mapped characters rasterize with FreeType. Styled visible characters
  are checked at 16, 24, 32, 48, 96 and 220 px. Soft hyphen is intentionally
  suppressed by text layout; its actual outline is checked separately.
- The game's bundled `stb_truetype` loads this OTF and rasterizes all **648 styled
  Unicode characters**, including the soft-hyphen outline.
- All alphanumeric pairs have positive vector ink spacing. At 24/32/48/96 px,
  the smallest gap measured at 50% raster coverage is 1.5/1.75/3.36/7.20 px.
  Antialiasing fringes are not treated as solid ink.
- The full alphabet, comparison and reading-size sheets were visually inspected.
  The heavy display forms retain more detail at 24–32 px and larger; 16 px is a
  rendering check, not acceptance of this face for small body text.
- The preferred Block and approved study OTFs remain byte-identical. The selected
  integration now uses this OTF through the shared main-font loader; its scope
  and runtime checks are recorded in the integration report. Gameplay and presets
  are outside the font change.

## Rebuild

From the repository root, using an isolated Python environment with the versions
in `requirements.txt`:

```sh
python3 assets/ui/deathward-display/build_font.py
```

The generator reads the preserved `deathward-block-study` OTF and its drawing
helpers, the previous `deathward-block` OTF for comparison, and `assets/ui/body.ttf`
for specimen labels. It writes only this artifact directory. The original Anton
attribution/license is retained; the font uses its own family/PostScript names.

Remaining: browser-specific visual verification. Broader inherited Unicode
redesign and combining-mark layout remain
outside this Latin display delivery. Native title, settings, HUD, tuning and
runtime dialogue have been checked with the integrated font.
