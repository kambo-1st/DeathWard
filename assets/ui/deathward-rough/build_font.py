#!/usr/bin/env python3
"""Build a vector-only, distressed Anton derivative. No game files are changed.

Dependencies: fonttools, shapely==2.1.2, pillow (specimen only).
Run from any directory: python3 build_font.py
"""
from __future__ import annotations

import copy
import hashlib
import json
import math
from pathlib import Path
import random
import unicodedata

from fontTools.fontBuilder import FontBuilder
from fontTools.pens.basePen import BasePen
from fontTools.pens.t2CharStringPen import T2CharStringPen
from fontTools.ttLib import TTFont
from PIL import Image, ImageDraw, ImageFont
from shapely import make_valid
from shapely.affinity import translate
from shapely.geometry import Polygon, MultiPolygon, GeometryCollection, box
from shapely.geometry.polygon import orient
from shapely.ops import unary_union

HERE = Path(__file__).resolve().parent
SOURCE = HERE.parents[1] / "Anton-Regular.ttf"
OUTPUT = HERE / "DeathWardRough-Regular.otf"
FAMILY = "DeathWard Rough"


class FacetPen(BasePen):
    """Keep Anton's structure but turn rounded corners into short, cut facets."""

    def __init__(self, glyphs):
        super().__init__(glyphs)
        self.contours = []
        self.points = []

    def _moveTo(self, p):
        self.points = [p]

    def _lineTo(self, p):
        self.points.append(p)

    def _qCurveToOne(self, control, end):
        start = self._getCurrentPoint()
        length = math.dist(start, control) + math.dist(control, end)
        # Coarse curve facets are intentional, distinct from the small edge wear.
        steps = max(1, min(5, math.ceil(length / 125)))
        for i in range(1, steps + 1):
            t = i / steps
            p = tuple((1-t)**2*start[k]+2*(1-t)*t*control[k]+t*t*end[k] for k in (0, 1))
            self.points.append(p)

    def _curveToOne(self, a, b, end):
        start = self._getCurrentPoint()
        steps = max(2, math.ceil((math.dist(start, a)+math.dist(a, b)+math.dist(b, end))/110))
        for i in range(1, steps + 1):
            t = i / steps
            self.points.append(tuple((1-t)**3*start[k]+3*(1-t)**2*t*a[k]+3*(1-t)*t*t*b[k]+t**3*end[k] for k in (0, 1)))

    def _closePath(self):
        if len(self.points) >= 3:
            self.contours.append(self.points)
        self.points = []

    def _endPath(self):
        self._closePath()


def polygons(geometry):
    if isinstance(geometry, Polygon):
        yield geometry
    elif isinstance(geometry, (MultiPolygon, GeometryCollection)):
        for item in geometry.geoms:
            yield from polygons(item)


def signed_area(points):
    return sum(a[0]*b[1]-b[0]*a[1] for a, b in zip(points, points[1:]+points[:1])) / 2


def source_geometry(contours):
    if not contours:
        return Polygon()
    # TrueType uses clockwise outer contours, counterclockwise counters.
    solid = [make_valid(Polygon(p)) for p in contours if signed_area(p) < 0]
    holes = [make_valid(Polygon(p)) for p in contours if signed_area(p) > 0]
    if not solid:
        return unary_union(holes)
    return make_valid(unary_union(solid).difference(unary_union(holes)))


def square_bowls(geometry):
    """Move round bowl corners toward a cut block, preserving each counter."""
    def squarify(coords):
        xs, ys = zip(*coords)
        cx, cy = (min(xs)+max(xs))/2, (min(ys)+max(ys))/2
        rx, ry = (max(xs)-min(xs))/2, (max(ys)-min(ys))/2
        if rx < 2 or ry < 2:
            return coords
        def axis(v, c, r, power):
            d = (v-c)/r
            return c + math.copysign(abs(d)**power*r, d)
        return [(axis(x, cx, rx, .67), axis(y, cy, ry, .52)) for x, y in coords]
    return make_valid(unary_union([
        Polygon(squarify(list(p.exterior.coords)),
                [squarify(list(h.coords)) for h in p.interiors])
        for p in polygons(geometry)
    ]))


def roughen(geometry, rng, width, cap_height):
    if geometry.is_empty:
        return geometry
    lo_x, lo_y, hi_x, hi_y = geometry.bounds
    center = (lo_x + hi_x) / 2
    height = hi_y - lo_y
    # Short marks and accents receive proportionally less wear.
    strength = min(1, height / 550, max(.2, (hi_x-lo_x)/220))
    lean = rng.uniform(-.012, .012)
    slope = rng.uniform(-.016, .016)
    phase = [rng.uniform(0, 2*math.pi) for _ in range(6)]

    def warp(p):
        x, y = p
        wx = (8*math.sin(y/155+phase[0]) + 4*math.sin(y/47+phase[1]) +
              3*math.sin(x/140+phase[2])) * strength
        wy = (8*math.sin(x/170+phase[3]) + 3*math.sin(x/49+phase[4]) +
              3*math.sin(y/120+phase[5])) * strength
        return (center+(x-center)*width+lean*(y-cap_height/2)+wx,
                y+slope*(x-center)+wy)

    def ring(coords):
        result = []
        for a, b in zip(coords, coords[1:]):
            steps = max(1, math.ceil(math.dist(a, b)/46))
            for i in range(steps):
                t = i/steps
                result.append(warp((a[0]*(1-t)+b[0]*t, a[1]*(1-t)+b[1]*t)))
        return result

    deformed = []
    for poly in polygons(geometry):
        deformed.append(make_valid(Polygon(ring(list(poly.exterior.coords)),
                             [ring(list(h.coords)) for h in poly.interiors])))
    geometry = make_valid(unary_union(deformed))
    # Apply an irregular vector distress mask, mostly at the edge. Keep the
    # heavy, solid interiors seen in the reference, not a spray of white noise.
    pieces = list(polygons(geometry))
    if not pieces:
        return geometry
    boundary = max(pieces, key=lambda p: p.area).exterior
    chips = []
    count = rng.randint(2, 5) if height > 600 else rng.randint(0, 1)
    for _ in range(count):
        along = rng.random()*boundary.length
        at = boundary.interpolate(along)
        before = boundary.interpolate((along-2) % boundary.length)
        after = boundary.interpolate((along+2) % boundary.length)
        dx, dy = after.x-before.x, after.y-before.y
        length = math.hypot(dx, dy)
        if length < .001:
            continue
        tx, ty = dx/length, dy/length
        nx, ny = -ty, tx
        size = rng.uniform(6, 16)*strength
        def p(t, n):
            return at.x+t*tx+n*nx, at.y+t*ty+n*ny
        chips.append(Polygon([p(-size*.55, -size), p(size*.7, -size*.35),
                              p(size*.2, size*1.3), p(-size*.35, size*.65)]))
    if chips:
        geometry = make_valid(geometry.difference(unary_union(chips)))
    # Remove only sub-pixel slivers created by clipping, never real accents.
    return unary_union([p for p in polygons(geometry) if p.area > 3]).simplify(.7, preserve_topology=True)


def draw_geometry(geometry, pen):
    for polygon in polygons(geometry):
        polygon = orient(polygon, sign=-1)
        for ring in [polygon.exterior, *polygon.interiors]:
            points = [(round(x), round(y)) for x, y in list(ring.coords)[:-1]]
            compact = []
            for p in points:
                if not compact or compact[-1] != p:
                    compact.append(p)
            if len(set(compact)) < 3:
                continue
            pen.moveTo(compact[0])
            for p in compact[1:]:
                pen.lineTo(p)
            pen.closePath()


def specimen():
    image = Image.new('RGB', (1900, 1260), 'white')
    draw = ImageDraw.Draw(image)
    def text_line(text, y, max_width=1810, size=210):
        font = ImageFont.truetype(str(OUTPUT), size)
        while draw.textlength(text, font=font) > max_width:
            size -= 1
            font = ImageFont.truetype(str(OUTPUT), size)
        box = draw.textbbox((0, 0), text, font=font)
        x = (1900-draw.textlength(text, font=font))/2
        draw.text((x, y-box[1]), text, fill='black', font=font)
    text_line('ABCDEFGHIJKLMN', 45)
    text_line('OPQRSTUVWXYZ', 265)
    text_line('0123456789', 485)
    text_line('DEATHWARD', 715, size=230)
    text_line('FORT MERCY  •  INTO THE BADLANDS', 970, size=90)
    text_line('Expedition  /  Health  /  Dynamite  /  165%', 1080, size=65)
    image.save(HERE/'specimen.png')
    comparison = Image.new('RGB', (1800, 690), 'white')
    d = ImageDraw.Draw(comparison)
    label = ImageFont.truetype(str(SOURCE), 26)
    sample = 'BADLANDS  ABGR  0289'
    size = 170
    while max(d.textlength(sample, font=ImageFont.truetype(str(p), size)) for p in (SOURCE, OUTPUT)) > 1710:
        size -= 1
    for y, path, caption in [(30, SOURCE, 'ORIGINAL ANTON'), (365, OUTPUT, 'DEATHWARD ROUGH — MODIFIED GLYPHS')]:
        d.text((45, y), caption, font=label, fill='#666666')
        font = ImageFont.truetype(str(path), size)
        d.text((45, y+48), sample, font=font, fill='black', anchor='lt')
    comparison.save(HERE/'comparison.png')


def main():
    source = TTFont(SOURCE)
    order = source.getGlyphOrder()
    glyphs = source.getGlyphSet()
    reverse = {}
    for code, name in source.getBestCmap().items():
        reverse.setdefault(name, chr(code))
    charstrings, metrics = {}, {}
    empty_before, empty_after = [], []
    bbox = [0, 0, 0, 0]
    for name in order:
        rng = random.Random(int.from_bytes(hashlib.sha256(('DeathWardRough-v1:'+name).encode()).digest()[:8], 'big'))
        pen = FacetPen(glyphs)
        glyphs[name].draw(pen)
        geometry = source_geometry(pen.contours)
        was_empty = geometry.is_empty
        if was_empty:
            empty_before.append(name)
        ch = reverse.get(name, '')
        base = unicodedata.normalize('NFD', ch)[:1]
        source_advance = source['hmtx'][name][0]
        if base and base in 'BCDGOPQRSU0235689':
            geometry = square_bowls(geometry)
        if base == 'I':
            # The reference's capital I has compact horizontal end bars.
            stem = max(polygons(geometry), key=lambda p: p.area)
            left, bottom, right, top = stem.bounds
            middle = (left+right)/2+105
            geometry = unary_union([translate(geometry, xoff=105),
                                    box(middle-275, bottom, middle+275, bottom+230),
                                    box(middle-275, top-230, middle+275, top)])
            source_advance += 210
        # Anton is slightly narrower than the reference; keep broad M/W from
        # overwhelming their neighbours while individually varying other widths.
        width = (1.005 if base and base in 'MWmw' else 1.10) + rng.uniform(-.017, .017)
        geometry = roughen(geometry, rng, width, source['OS/2'].sCapHeight)
        advance = round(source_advance * width)
        if geometry.is_empty:
            empty_after.append(name)
            lsb = round(source['hmtx'][name][1]*width)
        else:
            assert geometry.is_valid, name
            bounds = geometry.bounds
            lsb = math.floor(bounds[0])
            bbox = [min(bbox[0], math.floor(bounds[0])), min(bbox[1], math.floor(bounds[1])),
                    max(bbox[2], math.ceil(bounds[2])), max(bbox[3], math.ceil(bounds[3]))]
        metrics[name] = advance, lsb
        cff_pen = T2CharStringPen(advance, glyphs)
        draw_geometry(geometry, cff_pen)
        charstrings[name] = cff_pen.getCharString()
    assert empty_before == empty_after, 'A visible glyph was lost'
    fb = FontBuilder(source['head'].unitsPerEm, isTTF=False)
    fb.setupGlyphOrder(order)
    fb.setupCharacterMap(source.getBestCmap())
    fb.setupCFF('DeathWardRough-Regular', {
        'FullName': FAMILY+' Regular', 'FamilyName': FAMILY, 'Weight': 'Regular',
        'version': '1.000', 'FontBBox': bbox,
        'Notice': 'Derived from Anton. Copyright 2020 The Anton Project Authors. Licensed under SIL OFL 1.1.',
    }, charstrings, {})
    fb.setupHorizontalMetrics(metrics)
    fb.setupHorizontalHeader(ascent=source['hhea'].ascent, descent=source['hhea'].descent,
                             lineGap=source['hhea'].lineGap)
    fb.font['OS/2'] = copy.deepcopy(source['OS/2'])
    fb.font['OS/2'].xAvgCharWidth = round(sum(w for w, _ in metrics.values())/len(metrics))
    fb.font['OS/2'].usWinAscent = max(source['OS/2'].usWinAscent, bbox[3])
    fb.font['OS/2'].usWinDescent = max(source['OS/2'].usWinDescent, -bbox[1])
    fb.setupNameTable({
        'familyName': FAMILY, 'styleName': 'Regular', 'fullName': FAMILY+' Regular',
        'psName': 'DeathWardRough-Regular', 'uniqueFontIdentifier': 'DeathWardRough:Regular:1.000',
        'version': 'Version 1.000',
        'copyright': 'Copyright 2020 The Anton Project Authors (https://github.com/googlefonts/AntonFont.git). Modified for DeathWard, 2026.',
        'description': 'An Anton-derived display face with individually altered, faceted contours and subtle irregular vector edge distress. No outline, background or bitmap mask.',
        'licenseDescription': source['name'].getDebugName(13),
        'licenseInfoURL': 'https://openfontlicense.org',
    })
    fb.setupPost(underlinePosition=source['post'].underlinePosition,
                 underlineThickness=source['post'].underlineThickness)
    # Preserve all glyph IDs, character coverage and original substitutions,
    # kerning and mark attachment. No output subset or fake uppercase mapping.
    for table in ['GDEF', 'GPOS', 'GSUB']:
        if table in source:
            fb.font[table] = copy.deepcopy(source[table])
    fb.font['head'].created = source['head'].created
    fb.font['head'].modified = source['head'].modified
    fb.font.recalcTimestamp = False
    fb.save(OUTPUT)
    result = TTFont(OUTPUT)
    assert result.sfntVersion == 'OTTO' and 'CFF ' in result and 'glyf' not in result
    assert result.getBestCmap() == source.getBestCmap()
    assert result.getGlyphOrder() == order
    specimen()
    manifest = {
        'family': FAMILY, 'version': '1.000', 'source': '../../Anton-Regular.ttf',
        'source_sha256': hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
        'output': OUTPUT.name, 'output_sha256': hashlib.sha256(OUTPUT.read_bytes()).hexdigest(),
        'format': 'OpenType CFF (OTTO); vector contours, no bitmap/color layers',
        'glyphs': len(order), 'mapped_characters': len(source.getBestCmap()),
        'preserved_layout_tables': [t for t in ['GDEF', 'GPOS', 'GSUB'] if t in result],
        'empty_glyphs_preserved': len(empty_after),
        'scope': 'Modified font artifact only. No game font wiring, source overwrite, outline or background.',
        'validation': 'CFF roundtrip, complete glyph order and cmap, valid polygons, no lost visible glyphs; Pillow/FreeType specimen render.',
    }
    (HERE/'manifest.json').write_text(json.dumps(manifest, indent=2)+'\n')
    print(json.dumps(manifest, indent=2))


if __name__ == '__main__':
    main()
