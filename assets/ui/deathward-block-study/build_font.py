#!/usr/bin/env python3
"""Six structural letter studies in the preferred Block style, as actual CFF.

Requirements: fonttools, shapely==2.1.2, pillow. The other glyphs are preserved.
The 1000-square guides below are hand-authored per letter; they are not traces
or a distortion field applied to the previous contours. Edge wear comes last.
"""
from pathlib import Path
import hashlib
import json
import math
import random

from fontTools.ttLib import TTFont
from fontTools.pens.basePen import BasePen
from fontTools.pens.t2CharStringPen import T2CharStringPen
from PIL import Image, ImageDraw, ImageFont
from shapely import make_valid
from shapely.affinity import scale, translate
from shapely.geometry import Polygon
from shapely.geometry.polygon import orient
from shapely.ops import unary_union

HERE = Path(__file__).resolve().parent
BASE = HERE.parent / 'deathward-block/DeathWardBlock-Regular.otf'
OUTPUT = HERE / 'DeathWardBlockStudy-Regular.otf'
FAMILY = 'DeathWard Block Study'
CHARS = 'AB DGRS'.replace(' ', '')

# Per-letter large-scale decisions. No repeated bevel recipe: preserve blunt,
# uneven shoulders, bracket feet, dense strokes and small irregular counters.
DESIGNS = {
    'A': {
        'outer': [(0, 0), (45, 360), (180, 985), (650, 1000),
                  (770, 815), (1000, 10), (655, 0), (610, 195),
                  (350, 205), (315, 5)],
        'holes': [[(385, 390), (555, 400), (465, 700), (425, 670)]],
        'change': 'Left-offset flat crown, kinked right shoulder, unequal feet and higher crossbar.',
    },
    'B': {
        'outer': [(0, 975), (675, 1000), (930, 915), (960, 700),
                  (815, 590), (985, 495), (1000, 130), (860, 0),
                  (0, 10), (10, 205), (145, 220), (105, 780), (0, 785)],
        'holes': [[(420, 650), (640, 665), (625, 830), (420, 820)],
                  [(435, 180), (680, 205), (665, 395), (420, 380)]],
        'change': 'Shorter upper bowl, raised waist, heavier lower bowl and unequal bracket feet.',
    },
    'D': {
        'outer': [(0, 1000), (680, 975), (950, 900), (1000, 710),
                  (940, 120), (670, 0), (0, 20), (10, 200),
                  (135, 215), (105, 800), (0, 805)],
        'holes': [[(470, 785), (615, 755), (640, 265), (490, 205)]],
        'change': 'Sloping upper shoulder, long tapered right flank and asymmetric lower shoulder.',
    },
    'G': {
        'outer': [(0, 975), (920, 1000), (900, 815), (325, 790),
                  (305, 230), (745, 220), (760, 390), (530, 405),
                  (515, 590), (1000, 560), (965, 20), (80, 0), (0, 90)],
        'holes': [],
        'change': 'Longer upper arm, recessed inner bar, shallow sloping jaw and clipped left heel.',
    },
    'R': {
        'outer': [(0, 990), (760, 1000), (965, 865), (1000, 630),
                  (760, 555), (650, 555), (1000, 0), (670, 15),
                  (425, 505), (375, 525), (380, 0), (30, 10)],
        'holes': [[(395, 725), (665, 745), (655, 825), (395, 835)]],
        'change': 'Cut upper shoulder and an inward leg attachment with wider diagonal splay.',
    },
    'S': {
        'outer': [(75, 1000), (920, 985), (895, 785), (445, 800),
                  (425, 630), (850, 615), (980, 505), (1000, 35),
                  (115, 0), (65, 215), (665, 235), (650, 405),
                  (75, 405), (0, 530), (30, 865)],
        'holes': [],
        'change': 'Narrower upper block, offset middle step, broader lower body and short bottom return.',
    },
}


class OutlinePen(BasePen):
    def __init__(self, glyphs):
        super().__init__(glyphs)
        self.contours = []
        self.current = []

    def _moveTo(self, p): self.current = [p]
    def _lineTo(self, p): self.current.append(p)
    def _closePath(self):
        if len(self.current) >= 3:
            self.contours.append(self.current)
        self.current = []
    def _endPath(self): self._closePath()


def signed_area(points):
    return sum(a[0]*b[1]-b[0]*a[1] for a, b in zip(points, points[1:]+points[:1]))/2


def read_shape(glyph, glyphs):
    pen = OutlinePen(glyphs)
    glyph.draw(pen)
    exterior = unary_union([Polygon(p) for p in pen.contours if signed_area(p) < 0])
    holes = unary_union([Polygon(p) for p in pen.contours if signed_area(p) > 0])
    return exterior.difference(holes)


def rough_ring(points, rng):
    # Slow irregularities, then tiny edge nicks; not a uniformly jagged sawtooth.
    phase = [rng.uniform(0, math.tau) for _ in range(4)]
    result = []
    for a, b in zip(points, points[1:]+points[:1]):
        count = max(1, math.ceil(math.dist(a, b)/28))
        for i in range(count):
            t = i/count
            x, y = a[0]*(1-t)+b[0]*t, a[1]*(1-t)+b[1]*t
            dx = 4.8*math.sin(y/101+phase[0])+2.5*math.sin(y/37+phase[1])
            dy = 4.5*math.sin(x/116+phase[2])+2.2*math.sin(x/39+phase[3])
            result.append((x+dx, y+dy))
    return result


def build_shape(ch, original):
    design = DESIGNS[ch]
    guide = Polygon(design['outer'], design['holes'])
    assert guide.is_valid and len(guide.interiors) == len(original.interiors)
    rng = random.Random('DeathWardBlockStudy-v1:'+ch)
    shape = Polygon(rough_ring(design['outer'], rng),
                    [rough_ring(h, rng) for h in design['holes']])
    assert shape.is_valid
    boundary = shape.exterior
    chips = []
    for _ in range(4):
        position = rng.uniform(0, boundary.length)
        p = boundary.interpolate(position)
        a = boundary.interpolate((position-1) % boundary.length)
        b = boundary.interpolate((position+1) % boundary.length)
        length = math.hypot(b.x-a.x, b.y-a.y)
        tx, ty = (b.x-a.x)/length, (b.y-a.y)/length
        nx, ny = -ty, tx
        size = rng.uniform(4, 10)
        def at(t, n): return p.x+t*tx+n*nx, p.y+t*ty+n*ny
        chips.append(Polygon([at(-size*.65, -size), at(size*.7, -size*.5),
                              at(size*.2, size), at(-size*.2, size*.2)]))
    shape = make_valid(shape.difference(unary_union(chips))).simplify(.4, preserve_topology=True)
    assert isinstance(shape, Polygon) and shape.is_valid
    assert len(shape.interiors) == len(original.interiors)
    left, bottom, right, top = original.bounds
    # Fit the existing advance envelope to make an honest equal-size comparison.
    x0, y0, x1, y1 = shape.bounds
    shape = scale(translate(shape, xoff=-x0, yoff=-y0),
                  xfact=(right-left)/(x1-x0), yfact=(top-bottom)/(y1-y0), origin=(0, 0))
    return translate(shape, xoff=left, yoff=bottom)


def write_shape(shape, pen):
    shape = orient(shape, sign=-1)
    for contour in [shape.exterior, *shape.interiors]:
        points = []
        for x, y in list(contour.coords)[:-1]:
            point = (round(x), round(y))
            if not points or point != points[-1]: points.append(point)
        pen.moveTo(points[0])
        for p in points[1:]: pen.lineTo(p)
        pen.closePath()


def preview():
    label_path = HERE.parents[1] / 'ui/body.ttf'
    label = ImageFont.truetype(str(label_path), 20)
    heading = ImageFont.truetype(str(label_path), 28)
    canvas = Image.new('RGB', (1800, 1260), 'white')
    draw = ImageDraw.Draw(canvas)
    draw.text((48, 25), 'SIX LETTERS / SILHOUETTE STUDY', font=heading, fill='#222222')
    draw.text((48, 68), 'Each pair: preferred Block on the left, new study on the right. Same font size.',
              font=label, fill='#555555')
    cap_size = round(230*2048/1760)
    for index, ch in enumerate(CHARS):
        col, row = index % 3, index // 3
        left, top = 40+col*590, 130+row*390
        draw.text((left+55, top), 'PREVIOUS', font=label, fill='#777777')
        draw.text((left+335, top), 'NEW', font=label, fill='#777777')
        for cx, font_path in [(left+135, BASE), (left+415, OUTPUT)]:
            font = ImageFont.truetype(str(font_path), cap_size)
            box = draw.textbbox((0, 0), ch, font=font, anchor='ls')
            draw.text((cx-(box[0]+box[2])/2, top+295), ch, font=font, fill='black', anchor='ls')
        draw.line((left+275, top+48, left+275, top+315), fill='#dddddd', width=1)
    draw.line((48, 916, 1752, 916), fill='#dddddd', width=1)
    draw.text((48, 942), 'READING SIZE / ONLY THE SIX STUDIED LETTERS', font=label, fill='#555555')
    for baseline, font_path, name in [(1060, BASE, 'PREVIOUS'), (1194, OUTPUT, 'NEW')]:
        draw.text((48, baseline-55), name, font=label, fill='#777777')
        font = ImageFont.truetype(str(font_path), 91)
        draw.text((240, baseline), 'BAD RAGS   GRASS   BARDS', font=font, fill='black', anchor='ls')
    canvas.save(HERE / 'comparison.png')

    canvas = Image.new('RGB', (1800, 620), 'white')
    draw = ImageDraw.Draw(canvas)
    draw.text((45, 24), 'NEW SIX-LETTER STUDY / ACTUAL OTF', font=heading, fill='#555555')
    font = ImageFont.truetype(str(OUTPUT), 258)
    text = 'ABDGRS'
    draw.text(((1800-draw.textlength(text, font=font))/2, 310), text, font=font, fill='black', anchor='ls')
    for baseline, text, size in [(440, 'BAD RAGS', 110), (555, 'BADLANDS', 92)]:
        font = ImageFont.truetype(str(OUTPUT), size)
        draw.text(((1800-draw.textlength(text, font=font))/2, baseline), text,
                  font=font, fill='black', anchor='ls')
    draw.text((45, 585), 'BADLANDS retains the previous L and N. Other letters and numerals await redesign.',
              font=label, fill='#555555')
    canvas.save(HERE / 'specimen.png')


def main():
    source_bytes = BASE.read_bytes()
    font = TTFont(BASE)
    cmap, order, glyphs = font.getBestCmap(), font.getGlyphOrder(), font.getGlyphSet()
    originals = {ch: read_shape(glyphs[cmap[ord(ch)]], glyphs) for ch in CHARS}
    cff = font['CFF '].cff
    top = cff.topDictIndex[0]
    details = []
    for ch in CHARS:
        original = originals[ch]
        shape = build_shape(ch, original)
        name = cmap[ord(ch)]
        advance = font['hmtx'][name][0]
        pen = T2CharStringPen(advance, None)
        write_shape(shape, pen)
        top.CharStrings[name] = pen.getCharString(private=top.Private, globalSubrs=cff.GlobalSubrs)
        font['hmtx'][name] = (advance, math.floor(shape.bounds[0]))
        details.append({'character': ch, 'glyph': name, 'structural_change': DESIGNS[ch]['change'],
                        'counters': len(shape.interiors), 'advance': advance,
                        'shape_overlap': original.intersection(shape).area/original.union(shape).area,
                        'outer_contour_overlap': Polygon(original.exterior).intersection(Polygon(shape.exterior)).area /
                                                 Polygon(original.exterior).union(Polygon(shape.exterior)).area})
    names = {1: FAMILY, 2: 'Regular', 3: 'DeathWardBlockStudy:Regular:1.000',
             4: FAMILY+' Regular', 5: 'Version 1.000', 6: 'DeathWardBlockStudy-Regular',
             16: FAMILY, 17: 'Regular',
             10: 'Six uppercase structural studies: A B D G R S. Other glyphs retain DeathWard Block shapes.'}
    for record in font['name'].names:
        if record.nameID in names: record.string = names[record.nameID].encode(record.getEncoding())
    cff.fontNames = ['DeathWardBlockStudy-Regular']
    top.FamilyName, top.FullName, top.version = FAMILY, FAMILY+' Regular', '1.000'
    font.recalcTimestamp = False
    font.save(OUTPUT)
    checked = TTFont(OUTPUT, checkChecksums=2)
    assert checked.sfntVersion == 'OTTO' and 'CFF ' in checked
    assert checked.getBestCmap() == cmap and checked.getGlyphOrder() == order
    for tag in checked.keys():
        if tag != 'GlyphOrder': checked[tag]
    baseline = TTFont(BASE)
    before, after = baseline.getGlyphSet(), checked.getGlyphSet()
    from fontTools.pens.recordingPen import DecomposingRecordingPen
    changed_names = []
    for name in order:
        old_pen, new_pen = DecomposingRecordingPen(before), DecomposingRecordingPen(after)
        before[name].draw(old_pen)
        after[name].draw(new_pen)
        if old_pen.value != new_pen.value: changed_names.append(name)
    assert set(changed_names) == {cmap[ord(ch)] for ch in CHARS}
    assert baseline['hmtx'].metrics == checked['hmtx'].metrics
    for size in [16, 24, 48, 96, 220]:
        raster_font = ImageFont.truetype(str(OUTPUT), size)
        for ch in CHARS: assert raster_font.getmask(ch).getbbox()
    raster_font = ImageFont.truetype(str(OUTPUT), 64)
    for cp in cmap: raster_font.getmask(chr(cp))
    assert BASE.read_bytes() == source_bytes
    preview()
    result = {'family': FAMILY, 'font': OUTPUT.name,
              'sha256': hashlib.sha256(OUTPUT.read_bytes()).hexdigest(),
              'base': '../deathward-block/DeathWardBlock-Regular.otf', 'base_commit': '149fea6b',
              'base_sha256': hashlib.sha256(source_bytes).hexdigest(), 'base_unchanged': True,
              'scope': 'Six uppercase structural studies only; hand-authored guides followed by light edge wear.',
              'edited_glyphs': len(changed_names), 'unedited_glyphs_unchanged': True,
              'all_metrics_preserved': True, 'unicode_mappings': len(cmap), 'glyph_count': len(order),
              'overlap_note': 'Diagnostic shape comparison only, not an originality or legal assessment.',
              'glyphs': details, 'freetype_all_mapped_characters_rendered': len(cmap),
              'sizes_checked': [16, 24, 48, 96, 220], 'human_visual_acceptance': True,
              'human_acceptance_quote': "Nice that's it!",
              'full_font_continuation': '../deathward-display/README.md',
              'game_integrated': False,
              'remaining': ['Human in-game visual review of DeathWard Display', 'Browser-specific visual verification']}
    (HERE / 'manifest.json').write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps({'edited': CHARS, 'sha256': result['sha256'],
                      'unchanged_glyphs': len(order)-len(changed_names),
                      'shape_overlap': {d['character']: round(d['shape_overlap'], 3) for d in details}}, indent=2))


if __name__ == '__main__': main()
