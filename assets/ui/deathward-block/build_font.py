#!/usr/bin/env python3
"""Build an all-caps display candidate from the user's five-row specimen.

Anton-derived DeathWard Rough supplies the OpenType base and remaining glyphs.
Requirements: fonttools, pillow, numpy, shapely==2.1.2.
"""
from pathlib import Path
import hashlib
import json
import math
import statistics

import numpy as np
from PIL import Image, ImageDraw, ImageFont
from fontTools.ttLib import TTFont
from fontTools.pens.t2CharStringPen import T2CharStringPen
from shapely.affinity import affine_transform
from shapely.geometry import Polygon, MultiPolygon, GeometryCollection, box
from shapely.geometry.polygon import orient
from shapely.ops import unary_union

HERE = Path(__file__).resolve().parent
BASE = HERE.parent/'deathward-rough/DeathWardRough-Regular.otf'
REFERENCE = HERE/'reference.png'
OUTPUT = HERE/'DeathWardBlock-Regular.otf'
ROWS = ['ABCDEFGHIJKLMN', 'OPQRSTUVWXYZ', 'abcdefghijklmn', 'opqrstuvwxyz', '0123456789']
FAMILY = 'DeathWard Block'
CAP_HEIGHT = 1760


def spans(values):
    result = []
    for i in np.flatnonzero(values):
        if not result or i > result[-1][1]+1:
            result.append([int(i), int(i)])
        else:
            result[-1][1] = int(i)
    return result


def pieces(geometry):
    if isinstance(geometry, Polygon):
        yield geometry
    elif isinstance(geometry, (MultiPolygon, GeometryCollection)):
        for item in geometry.geoms:
            yield from pieces(item)


def trace(mask):
    # Exact union of occupied scanline runs avoids flood-fill ambiguity at the
    # touching corners of diagonal strokes. Counters remain real vector holes.
    runs = []
    for y, line in enumerate(mask):
        for left, right in spans(line):
            runs.append(box(left, y, right+1, y+1))
    raw = unary_union(runs)
    raw = unary_union([p for p in pieces(raw) if p.area >= 3])
    simplified = raw.simplify(.58, preserve_topology=True)
    assert simplified.is_valid and not simplified.is_empty
    # The small simplification removes pixel stair steps, preserving visible
    # cut corners and edge nicks. It must not create/remove letter counters.
    assert sum(len(p.interiors) for p in pieces(raw)) == sum(len(p.interiors) for p in pieces(simplified))
    return simplified, raw.symmetric_difference(simplified).area / raw.area


def draw_geometry(geometry, pen):
    count = 0
    for polygon in pieces(geometry):
        polygon = orient(polygon, sign=-1)
        for ring in [polygon.exterior, *polygon.interiors]:
            coords = [(round(x), round(y)) for x, y in list(ring.coords)[:-1]]
            compact = []
            for p in coords:
                if not compact or compact[-1] != p:
                    compact.append(p)
            assert len(set(compact)) >= 3
            pen.moveTo(compact[0])
            for p in compact[1:]:
                pen.lineTo(p)
            pen.closePath()
            count += len(compact)
    return count


def render_preview():
    image = Image.new('RGB', (2230, 1550), 'white')
    d = ImageDraw.Draw(image)
    font = ImageFont.truetype(str(OUTPUT), 257)
    for row, y in zip(ROWS, [40, 305, 570, 835, 1100]):
        # Draw real text from the finished font; this is not a collage of the
        # source image. Lowercase uses the second, subtly different cap set.
        size = 257
        f = font
        while d.textlength(row, font=f) > 2160:
            size -= 1
            f = ImageFont.truetype(str(OUTPUT), size)
        bounds = d.textbbox((0, 0), row, font=f)
        x = (2230-d.textlength(row, font=f))/2
        d.text((x, y-bounds[1]), row, font=f, fill='black')
    f = ImageFont.truetype(str(OUTPUT), 106)
    row = 'DEATHWARD  /  FORT MERCY  /  BADLANDS'
    x = (2230-d.textlength(row, font=f))/2
    bounds = d.textbbox((0, 0), row, font=f)
    d.text((x, 1400-bounds[1]), row, font=f, fill='black')
    image.save(HERE/'specimen.png')

    comparison = Image.new('RGB', (1900, 830), 'white')
    d = ImageDraw.Draw(comparison)
    label = ImageFont.truetype(str(HERE.parents[1]/'Anton-Regular.ttf'), 25)
    sample = 'BADLANDS  ABGRS  0289'
    size = 180
    while max(d.textlength(sample, font=ImageFont.truetype(str(p), size)) for p in [BASE, OUTPUT]) > 1810:
        size -= 1
    for y, path, text in [(35, BASE, 'COMMITTED: DEATHWARD ROUGH'),
                          (430, OUTPUT, 'NEW: DEATHWARD BLOCK — SUPPLIED SILHOUETTES')]:
        d.text((45, y), text, font=label, fill='#666666')
        f = ImageFont.truetype(str(path), size)
        d.text((45, y+65), sample, font=f, fill='black', anchor='lt')
    comparison.save(HERE/'comparison.png')


def main():
    image = Image.open(REFERENCE).convert('RGBA')
    rgb = np.asarray(Image.alpha_composite(Image.new('RGBA', image.size, 'white'), image).convert('RGB'))
    mask = np.max(rgb, axis=2) < 128
    bands = spans(mask.any(axis=1))
    assert len(bands) == len(ROWS), bands
    font = TTFont(BASE)
    cmap = font.getBestCmap()
    glyph_order = font.getGlyphOrder()
    cff = font['CFF '].cff
    top = cff.topDictIndex[0]
    changed = []
    for text, (y0, y1) in zip(ROWS, bands):
        row = mask[y0:y1+1]
        columns = spans(row.any(axis=0))
        assert len(columns) == len(text), (text, columns)
        tops, bottoms = [], []
        for ch, (x0, x1) in zip(text, columns):
            ys = np.flatnonzero(row[:, x0:x1+1].any(axis=1))
            tops.append(int(ys[0]))
            if ch.upper() not in ['Q', 'K', 'X', 'V']:
                bottoms.append(int(ys[-1])+1)
        baseline = statistics.median(bottoms)
        cap_top = statistics.median(tops)
        factor = CAP_HEIGHT/(baseline-cap_top)
        for ch, (x0, x1) in zip(text, columns):
            outline, difference = trace(row[:, x0:x1+1])
            sidebearing = 78
            outline = affine_transform(outline, [factor, 0, 0, -factor, sidebearing, baseline*factor])
            assert outline.is_valid
            advance = round((x1-x0+1)*factor+sidebearing*2)
            pen = T2CharStringPen(advance, None)
            points = draw_geometry(outline, pen)
            name = cmap[ord(ch)]
            top.CharStrings[name] = pen.getCharString(private=top.Private, globalSubrs=cff.GlobalSubrs)
            font['hmtx'][name] = (advance, math.floor(outline.bounds[0]))
            changed.append({'character': ch, 'glyph': name, 'reference_box': [x0, y0, x1+1, y1+1],
                            'points': points, 'mask_area_difference': difference,
                            'counters': sum(len(p.interiors) for p in pieces(outline))})
    # Existing lowercase ligatures would reintroduce unrelated lowercase shapes
    # into the new caps. Keep mapping direct in this display candidate.
    for tag in ['GSUB', 'GPOS', 'GDEF']:
        if tag in font:
            del font[tag]
    for record in font['name'].names:
        name = {1:FAMILY, 2:'Regular', 3:'DeathWardBlock:Regular:1.000',
                4:FAMILY+' Regular', 5:'Version 1.000', 6:'DeathWardBlock-Regular',
                16:FAMILY, 17:'Regular',
                10:'Anton-derived all-caps display candidate. A-Z, a-z cap alternates and 0-9 are vector outlines traced from the user-supplied specimen.'}.get(record.nameID)
        if name is not None:
            record.string = name.encode(record.getEncoding())
    cff.fontNames = ['DeathWardBlock-Regular']
    top.FamilyName = FAMILY
    top.FullName = FAMILY+' Regular'
    top.version = '1.000'
    font['hhea'].advanceWidthMax = max(w for w, _ in font['hmtx'].metrics.values())
    font['OS/2'].sCapHeight = CAP_HEIGHT
    font['OS/2'].sxHeight = CAP_HEIGHT
    font['OS/2'].xAvgCharWidth = round(sum(w for w, _ in font['hmtx'].metrics.values())/len(glyph_order))
    font.recalcTimestamp = False
    font.save(OUTPUT)
    check = TTFont(OUTPUT, checkChecksums=2)
    assert check.sfntVersion == 'OTTO' and 'CFF ' in check
    assert check.getBestCmap() == cmap and check.getGlyphOrder() == glyph_order
    for tag in check.keys():
        if tag != 'GlyphOrder':
            check[tag]
    ft = ImageFont.truetype(str(OUTPUT), 64)
    for code in cmap:
        ft.getmask(chr(code))
    render_preview()
    manifest = {'family': FAMILY, 'base': '../deathward-rough/DeathWardRough-Regular.otf',
                'base_commit': '6997ff36', 'base_sha256': hashlib.sha256(BASE.read_bytes()).hexdigest(),
                'reference': 'reference.png', 'reference_sha256': hashlib.sha256(REFERENCE.read_bytes()).hexdigest(),
                'output': OUTPUT.name, 'output_sha256': hashlib.sha256(OUTPUT.read_bytes()).hexdigest(),
                'traced_characters': len(changed), 'glyph_count': len(glyph_order), 'unicode_mappings': len(cmap),
                'format': 'OpenType CFF / OTTO; vector outlines, no bitmap or color layers',
                'lowercase': 'a-z use the second cap alphabet shown in the reference',
                'other_characters': 'Retained from the committed Anton-derived candidate; not traced from the reference',
                'spacing': '78-unit sidebearings; proportional widths derived from the reference; no inherited positioning or substitution tables',
                'validation': 'All tables decompiled; glyph order/cmap preserved; counters preserved through contour simplification; all 978 mapped characters rasterized with FreeType',
                'human_visual_acceptance': False, 'game_integrated': False, 'changed_glyphs': changed}
    (HERE/'manifest.json').write_text(json.dumps(manifest, indent=2)+'\n')
    print('Built', OUTPUT)
    print('Traced', len(changed), 'glyphs; max contour area difference', max(c['mask_area_difference'] for c in changed))
    print('All', len(cmap), 'Unicode characters loaded and rasterized.')


if __name__ == '__main__':
    main()
