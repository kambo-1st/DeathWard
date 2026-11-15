# DeathWard Block — six-letter silhouette study

This is the next visual checkpoint after the user rejected **Cut** for changing
the style too much and **Block Refined** for looking the same. The user approved
the proposed six-letter study before another full-alphabet pass.

**Status:** the user accepted this direction ("Nice that's it!") and selected
completion of the remainder. The extended font is now available in
`../deathward-display/README.md`. This preserved study still changes only
uppercase **A B D G R S**; its OTF remains unchanged and is not an enabled game font.

- `comparison.png`: previous Block on the left of each pair, new study on the
  right, at identical font sizes. The bottom compares words using these six
  letters at a smaller reading size.
- `specimen.png`: the new letters and sample words rendered from the actual OTF.
- `DeathWardBlockStudy-Regular.otf`: genuine OpenType CFF, with a separate family
  name so the preferred Block remains independently usable.
- `build_font.py`: explicit per-letter polygon guides followed by deterministic
  light edge wear; the study is reproducible from the preferred Block artifact.
- `manifest.json` and `validation.json`: scope, hashes, checks and remaining work.

The design retains heavy compact strokes, blunt irregular corners, bracketed
B/D stems, stepped G/S forms, small counters and sparse edge distress. Changes
are made to each letter's structure before distress is applied:

| Letter | Structural change |
| --- | --- |
| A | Left-offset flat crown, kinked right shoulder, unequal feet, higher crossbar |
| B | Shorter upper bowl, raised waist, heavier lower bowl, unequal bracket feet |
| D | Sloping upper shoulder, tapered right flank, asymmetric lower shoulder |
| G | Longer upper arm, recessed inner bar, shallow sloping jaw, clipped left heel |
| R | Cut upper shoulder, inward leg attachment, wider diagonal splay |
| S | Narrower upper block, offset middle step, broader lower body, short bottom return |

The font inherits the Anton-derived font container and untouched glyphs from
DeathWard Block (`149fea6b`). These six new guides are hand-authored, using the
preferred Block design language; they are not presented as Anton's original
letterforms. All 1,320 other glyph outlines, 978 Unicode mappings and horizontal
metrics are preserved. Lowercase retains the previous alternate capital shapes
and is not yet matched to the six new uppercase forms. The base OTF is unchanged.
Shape-overlap numbers in the manifest describe geometry differences only; they
are not an originality or legal assessment. Attribution and OFL are retained.

Validation: complete CFF/table reload; exact unchanged-glyph and metrics checks;
FreeType rasterization of all mapped characters and the edited six at
16/24/48/96/220 px; the game's bundled `stb_truetype` loads the OTF and rasterizes
all 94 non-space printable ASCII characters. Both preview images were inspected.
These checks do not establish human visual acceptance or small-UI readability.

Rebuild with Python, `fonttools`, `shapely==2.1.2` and `pillow`:

```sh
python3 assets/ui/deathward-block-study/build_font.py
```

The remaining alphabet, alternate-cap lowercase, numerals, punctuation and
precomposed Latin accents have been completed in **DeathWard Display**, with
spacing/readability checks. The user accepted that full font, committed with this
study as `32991e0d`, and selected main-game integration, which is now enabled.
In-game human visual acceptance and browser verification remain; see
`../../../docs/reports/main-font-integration/README.md`. This study OTF remains a
preserved comparison artifact; the game uses the completed Display OTF.
