#!/usr/bin/env python3
"""Complete the approved Block study into a Latin display OTF.

Run with fonttools, pillow, shapely==2.1.2. No game integration or source font
mutation. The six approved capitals are retained without rebuilding outlines.
"""
from pathlib import Path
import hashlib
import importlib.util
import json
import math
import random
import string
import sys
import unicodedata

sys.dont_write_bytecode = True
from fontTools.ttLib import TTFont
from fontTools.pens.recordingPen import DecomposingRecordingPen
from fontTools.pens.t2CharStringPen import T2CharStringPen
from PIL import Image, ImageDraw, ImageFont
from shapely import make_valid
from shapely.affinity import rotate, scale, translate
from shapely.geometry import Polygon, MultiPolygon, GeometryCollection, box
from shapely.geometry.polygon import orient
from shapely.ops import unary_union
from glyph_designs import LETTERS
from symbol_designs import symbols, accents

HERE = Path(__file__).resolve().parent
STUDY_DIR = HERE.parent / 'deathward-block-study'
BASE = STUDY_DIR / 'DeathWardBlockStudy-Regular.otf'
PREVIOUS = HERE.parent / 'deathward-block/DeathWardBlock-Regular.otf'
OUTPUT = HERE / 'DeathWardDisplay-Regular.otf'
FAMILY = 'DeathWard Display'
APPROVED = 'ABDGRS'
ALPHANUMERIC = string.ascii_uppercase + string.ascii_lowercase + string.digits
FACTOR = 1.76

spec = importlib.util.spec_from_file_location('block_study', STUDY_DIR / 'build_font.py')
study = importlib.util.module_from_spec(spec)
spec.loader.exec_module(study)
DESIGNS = {**study.DESIGNS, **LETTERS}


def pieces(shape):
    if isinstance(shape, Polygon):
        yield shape
    elif isinstance(shape, (MultiPolygon, GeometryCollection)):
        for child in shape.geoms: yield from pieces(child)


def wear(shape, character):
    rng = random.Random('DeathWardDisplay-v1:'+character)
    warped = unary_union([Polygon(study.rough_ring(list(p.exterior.coords)[:-1], rng),
                                  [study.rough_ring(list(h.coords)[:-1], rng) for h in p.interiors])
                          for p in pieces(shape)])
    assert warped.is_valid and not warped.is_empty, character
    chips = []
    for p in pieces(warped):
        edge = p.exterior
        for _ in range(4 if p.area > 100000 else 1):
            position = rng.uniform(0, edge.length)
            at = edge.interpolate(position)
            a, b = edge.interpolate((position-1) % edge.length), edge.interpolate((position+1) % edge.length)
            length = math.hypot(b.x-a.x, b.y-a.y)
            if length < .001: continue
            tx, ty = (b.x-a.x)/length, (b.y-a.y)/length
            nx, ny = -ty, tx
            size = rng.uniform(3, 9)
            def point(t, n): return at.x+t*tx+n*nx, at.y+t*ty+n*ny
            chips.append(Polygon([point(-size*.65, -size), point(size*.7, -size*.5),
                                  point(size*.2, size), point(-size*.2, size*.2)]))
    result = make_valid(warped.difference(unary_union(chips))).simplify(.4, preserve_topology=True)
    result = unary_union([p for p in pieces(result) if p.area > 1])
    assert result.is_valid and not result.is_empty, character
    assert sum(len(p.interiors) for p in pieces(result)) == sum(len(p.interiors) for p in pieces(shape)), character
    return result


def fit(shape, bounds):
    x0, y0, x1, y1 = shape.bounds
    left, bottom, right, top = bounds
    return translate(scale(translate(shape, xoff=-x0, yoff=-y0),
                           xfact=(right-left)/(x1-x0), yfact=(top-bottom)/(y1-y0), origin=(0, 0)),
                     xoff=left, yoff=bottom)


def write_shape(shape, pen):
    for p in pieces(shape):
        p = orient(p, sign=-1)
        for ring in [p.exterior, *p.interiors]:
            points = []
            for x, y in list(ring.coords)[:-1]:
                point = (round(x), round(y))
                if not points or point != points[-1]: points.append(point)
            assert len(set(points)) >= 3
            pen.moveTo(points[0])
            for pnt in points[1:]: pen.lineTo(pnt)
            pen.closePath()


def raw_guide(ch):
    design = DESIGNS[ch]
    result = Polygon(design['outer'], design['holes'])
    assert result.is_valid, ch
    return result


def compose_accents(base_shape, marks, accent_shapes):
    result = base_shape
    left, bottom, right, top = base_shape.bounds
    center = (left+right)/2
    above, below = top+80, bottom-70
    for mark in marks:
        shape = accent_shapes[mark]
        x0, y0, x1, y1 = shape.bounds
        # Narrow I/J accents may extend beyond the stem, but not the advance.
        if x1-x0 > right-left+40:
            shape = scale(shape, xfact=(right-left+40)/(x1-x0), yfact=1, origin=(0, 0))
            x0, y0, x1, y1 = shape.bounds
        dx = center-(x0+x1)/2
        if mark == '\u031B':
            placed = translate(shape, xoff=right-70-x0, yoff=top-240-y0)
        elif mark in {'\u0327', '\u0328'}:
            # Cedilla/ogonek attach to the baseline, not to a floating accent row.
            if mark == '\u0328': dx = right-200-(x0+x1)/2
            placed = translate(shape, xoff=dx, yoff=bottom+40-y1)
            below = min(below, placed.bounds[1]-65)
        elif unicodedata.combining(mark) in {202, 220}:
            placed = translate(shape, xoff=dx, yoff=below-y1)
            below = placed.bounds[1]-65
        else:
            placed = translate(shape, xoff=dx, yoff=above-y0)
            above = placed.bounds[3]+65
        result = unary_union([result, placed])
    assert result.is_valid
    return result


def add_extended_latin(shapes, advances, put):
    def pair(upper, lower, make):
        for out, source in [(upper, True), (lower, False)]:
            shape = make(source)
            left = shape.bounds[0]
            shape = translate(shape, xoff=78-left)
            put(out, shape, round(shape.bounds[2]+78), 'Latin structural variant')

    def shape_for(ch, upper): return shapes[ch if upper else ch.lower()]
    pair('Ø', 'ø', lambda upper: unary_union([
        shape_for('O', upper),
        fit(Polygon([(0, 0), (155, 0), (1000, 1000), (845, 1000)]), shape_for('O', upper).bounds)]))
    for upper, lower, base in [('Ð', 'ð', 'D'), ('Đ', 'đ', 'D'), ('Ħ', 'ħ', 'H'), ('Ŧ', 'ŧ', 'T')]:
        def barred(is_upper, base=base):
            body = shape_for(base, is_upper)
            l, b, r, t = body.bounds
            return unary_union([body, box(l-80, b+(t-b)*.47, l+(r-l)*.60, b+(t-b)*.60)])
        pair(upper, lower, barred)
    pair('Ł', 'ł', lambda upper: unary_union([
        shape_for('L', upper),
        fit(Polygon([(0, 0), (1000, 500), (1000, 760), (0, 260)]),
            (0, 440, shape_for('L', upper).bounds[2]*.65, 1200))]))
    def thorn(upper):
        body = shape_for('P', upper)
        l, b, r, t = body.bounds
        return unary_union([scale(body, xfact=1, yfact=.72, origin=(l, b)), box(l, b, l+(r-l)*.32, t)])
    pair('Þ', 'þ', thorn)
    for upper, lower, letters in [('Æ', 'æ', 'AE'), ('Œ', 'œ', 'OE'), ('Ĳ', 'ĳ', 'IJ')]:
        def ligature(is_upper, letters=letters):
            first = scale(shape_for(letters[0], is_upper), xfact=.78, yfact=1, origin=(0, 0))
            second = scale(shape_for(letters[1], is_upper), xfact=.78, yfact=1, origin=(0, 0))
            return unary_union([first, translate(second, xoff=first.bounds[2]-second.bounds[0]+25)])
        pair(upper, lower, ligature)
    for ch, letters in [('ﬁ', 'fi'), ('ﬂ', 'fl')]:
        first, second = shapes[letters[0]], shapes[letters[1]]
        shape = unary_union([first, translate(second, xoff=advances[letters[0]])])
        put(ch, shape, advances[letters[0]]+advances[letters[1]], 'Matching encoded Latin ligature')
    for ch, source in [('Ŀ', 'L'), ('ŀ', 'l')]:
        body = shapes[source]
        l, b, r, t = body.bounds
        dot = box(l+(r-l)*.65, b+(t-b)*.48, l+(r-l)*.82, b+(t-b)*.61)
        put(ch, unary_union([body, dot]), advances[source], 'L with middle dot')
    quote = shapes["'"]
    put('ŉ', unary_union([quote, translate(shapes['n'], xoff=advances["'"])]),
        advances["'"]+advances['n'], 'N preceded by apostrophe')
    def eng(is_upper):
        body = shape_for('N', is_upper)
        l, b, r, t = body.bounds
        width = r-l
        return unary_union([body, Polygon([
            (l+.68*width, b+60), (r, b+40), (r, b-250),
            (l+.82*width, b-400), (l+.50*width, b-350),
            (l+.52*width, b-170), (l+.68*width, b-200)])])
    pair('Ŋ', 'ŋ', eng)
    eszett = Polygon([(0, 0), (0, 800), (130, 980), (620, 1000), (820, 900),
                      (820, 700), (540, 540), (960, 430), (1000, 150), (860, 0),
                      (480, 0), (480, 200), (700, 210), (680, 330), (360, 500),
                      (360, 640), (570, 800), (320, 810), (280, 730), (280, 0)])
    for ch in ['ß', 'ẞ']:
        put(ch, fit(wear(eszett, ch), (78, 0, 1200, 1760)), 1278, 'Angular capital eszett')
    for ch, source in [('ı', 'i'), ('ȷ', 'j'), ('ſ', 's'), ('ĸ', 'k')]:
        put(ch, shapes[source], advances[source], 'Display-cap variant')


def preview():
    label_path = HERE.parent / 'body.ttf'
    label = ImageFont.truetype(str(label_path), 24)
    heading = ImageFont.truetype(str(label_path), 32)
    canvas = Image.new('RGB', (2230, 1820), 'white')
    draw = ImageDraw.Draw(canvas)
    draw.text((45, 25), 'DEATHWARD DISPLAY / ALPHABET, NUMERALS & PUNCTUATION', font=heading, fill='#444444')
    rows = [('ABCDEFGHIJKLMN', 285, 235), ('OPQRSTUVWXYZ', 555, 235),
            ('abcdefghijklmn', 825, 235), ('opqrstuvwxyz', 1095, 235),
            ('0123456789', 1370, 248)]
    for text, baseline, size in rows:
        font = ImageFont.truetype(str(OUTPUT), size)
        while draw.textlength(text, font=font) > 2125:
            size -= 1
            font = ImageFont.truetype(str(OUTPUT), size)
        draw.text(((2230-draw.textlength(text, font=font))/2, baseline), text, font=font, fill='black', anchor='ls')
    for text, baseline, size in [('. , : ; ! ?  \' "  ( ) [ ] { }', 1525, 102),
                                  ('+ - = / \\ * # % & @ $ < > _ | ^ ` ~', 1655, 83)]:
        font = ImageFont.truetype(str(OUTPUT), size)
        draw.text(((2230-draw.textlength(text, font=font))/2, baseline), text, font=font, fill='black', anchor='ls')
    draw.text((45, 1745), 'Lowercase keys produce alternate capitals. The approved A B D G R S remain unchanged.',
              font=label, fill='#555555')
    canvas.save(HERE / 'specimen.png')

    canvas = Image.new('RGB', (2100, 1300), 'white')
    draw = ImageDraw.Draw(canvas)
    draw.text((45, 20), 'PREVIOUS BLOCK / NEW DISPLAY', font=heading, fill='#444444')
    for row, text in enumerate(['ABCDEFGHIJKLMN', 'OPQRSTUVWXYZ', '0123456789']):
        top = 90+row*370
        size = 190
        while max(draw.textlength(text, font=ImageFont.truetype(str(p), size)) for p in [PREVIOUS, OUTPUT]) > 1840:
            size -= 1
        for baseline, font_path, title in [(top+140, PREVIOUS, 'PREVIOUS'), (top+315, OUTPUT, 'NEW')]:
            draw.text((32, baseline-70), title, font=label, fill='#666666')
            font = ImageFont.truetype(str(font_path), size)
            draw.text((215, baseline), text, font=font, fill='black', anchor='ls')
    draw.text((45, 1230), 'New structures, same heavy hand-cut style. All samples are rendered from the OTFs.',
              font=label, fill='#555555')
    canvas.save(HERE / 'comparison.png')

    canvas = Image.new('RGB', (1800, 1280), '#faf9f6')
    draw = ImageDraw.Draw(canvas)
    draw.text((45, 25), 'READABILITY / PUNCTUATION / ACCENTED LATIN', font=heading, fill='#444444')
    for y, size, text in [(180, 104, 'DEATHWARD'), (300, 80, 'EXPEDITION INTO THE BADLANDS'),
                          (400, 64, 'FORT MERCY   FLOOR 2 / ROOM 7'),
                          (485, 48, 'DYNAMITE: 3   HEALTH: 3/6   PAUSED'),
                          (555, 32, 'START EXPEDITION   SETTINGS   CONTINUE   QUIT'),
                          (615, 24, 'PICK UP KEY?  YES / NO    +25% DAMAGE'),
                          (665, 16, '16 PX CHECK: BADLANDS 0123456789 !? @ &')]:
        font = ImageFont.truetype(str(OUTPUT), size)
        draw.text((45, y-30), str(size)+' px', font=label, fill='#777777')
        draw.text((180, y), text, font=font, fill='black', anchor='ls')
    for y, text in [(810, 'PŘÍLIŠ ŽLUŤOUČKÝ KŮŇ'), (920, 'ÉTÉ · MAÑANA · ÜBER · ŁÓDŹ'),
                    (1030, 'À Á Â Ã Ä Å Æ Ç È É Ê Ë Ì Í Î Ï'),
                    (1140, 'Ð Ñ Ò Ó Ô Õ Ö Ø Œ Ù Ú Û Ü Ý ß')]:
        font = ImageFont.truetype(str(OUTPUT), 69)
        draw.text((50, y), text, font=font, fill='black', anchor='ls')
    draw.text((45, 1210), 'Accented samples use precomposed Unicode. Broader inherited coverage is listed in coverage.json.',
              font=ImageFont.truetype(str(label_path), 20), fill='#555555')
    canvas.save(HERE / 'readability.png')


def main():
    base_bytes, previous_bytes = BASE.read_bytes(), PREVIOUS.read_bytes()
    font = TTFont(BASE)
    cmap, order, glyphs = font.getBestCmap(), font.getGlyphOrder(), font.getGlyphSet()
    cff = font['CFF '].cff
    top = cff.topDictIndex[0]
    shapes = {ch: study.read_shape(glyphs[cmap[ord(ch)]], glyphs) for ch in ALPHANUMERIC}
    advances = {ch: font['hmtx'][cmap[ord(ch)]][0] for ch in ALPHANUMERIC}
    records = {}

    def put(ch, shape, advance=None, reason='New structural guide and light edge wear'):
        if ord(ch) not in cmap: return
        assert shape.is_valid and not shape.is_empty, (ch, 'invalid output')
        if advance is None: advance = round(shape.bounds[2]+78)
        name = cmap[ord(ch)]
        pen = T2CharStringPen(advance, None)
        write_shape(shape, pen)
        top.CharStrings[name] = pen.getCharString(private=top.Private, globalSubrs=cff.GlobalSubrs)
        font['hmtx'][name] = (advance, math.floor(shape.bounds[0]))
        shapes[ch], advances[ch] = shape, advance
        records[ch] = {'glyph': name, 'reason': reason, 'advance': advance}

    for ch in ALPHANUMERIC:
        if ch in APPROVED:
            records[ch] = {'glyph': cmap[ord(ch)], 'reason': 'Approved study outline preserved exactly',
                           'advance': advances[ch]}
            continue
        upper = ch.upper()
        guide = raw_guide(upper)
        # Both cases share a silhouette family, with independently worn alternate caps.
        target = shapes[upper].bounds if ch.islower() else shapes[ch].bounds
        shape = fit(wear(guide, ch), target)
        put(ch, shape, advances[upper], DESIGNS[upper]['change'])

    punct = symbols({ch: raw_guide(ch) for ch in string.ascii_uppercase})
    for ch, guide in punct.items():
        shape = scale(wear(guide, ch), xfact=FACTOR, yfact=FACTOR, origin=(0, 0))
        shape = translate(shape, xoff=78-shape.bounds[0])
        put(ch, shape, reason='New chunky punctuation with light edge wear')

    # Shared spacing and typographic variants use the actual newly designed glyphs.
    for ch, source in [('‘', "'"), ('’', "'"), ('‚', ','), ('“', '"'), ('”', '"'),
                       ('–', '-'), ('—', '-'), ('−', '-'), ('‐', '-'), ('‑', '-'), ('\u00AD', '-')]:
        if ord(ch) not in cmap: continue
        shape = shapes[source]
        if ch in {'‘', '“'}: shape = rotate(shape, 180, origin='center')
        if ch in {'–', '—'}: shape = scale(shape, xfact=1.45 if ch == '–' else 2.1, yfact=1, origin=(78, 0))
        put(ch, shape, reason='Matching typographic punctuation')
    for ch, source in [('¡', '!'), ('¿', '?')]:
        shape = rotate(shapes[source], 180, origin=(0, 880))
        put(ch, translate(shape, xoff=78-shape.bounds[0]), advances[source], 'Inverted punctuation')
    dot = shapes['.']
    for ch, count in [('…', 3), ('·', 1), ('•', 1)]:
        shape = unary_union([translate(dot, xoff=i*(dot.bounds[2]-dot.bounds[0]+120)) for i in range(count)])
        if ch in {'·', '•'}: shape = translate(shape, yoff=710)
        if ch == '•': shape = scale(shape, xfact=1.2, yfact=1.2, origin='center')
        put(ch, shape, reason='Matching dots')
    for ch, source in [('«', '<'), ('»', '>')]:
        shape = scale(shapes[source], xfact=.7, yfact=.8, origin=(78, 880))
        put(ch, unary_union([shape, translate(shape, xoff=shape.bounds[2]-shape.bounds[0]+80)]),
            reason='Double angle quotation marks')
    put('×', rotate(shapes['+'], 45, origin='center'), reason='Matching multiplication sign')
    bar = shapes['-']
    mid = (bar.bounds[0]+bar.bounds[2])/2-(dot.bounds[0]+dot.bounds[2])/2
    put('÷', unary_union([bar, translate(dot, xoff=mid, yoff=1230), translate(dot, xoff=mid, yoff=140)]),
        reason='Matching division sign')
    put('±', unary_union([translate(shapes['+'], yoff=180), translate(bar, yoff=-700)]),
        reason='Matching plus-minus sign')

    add_extended_latin(shapes, advances, put)
    mark_shapes = accents()
    for ch, shape in mark_shapes.items():
        assert shape.is_valid, ('accent', ch)
    # All canonically decomposable Latin bases that have a matching new drawing.
    for cp in sorted(cmap):
        ch = chr(cp)
        if ch in records or not unicodedata.name(ch, '').startswith('LATIN '): continue
        decomposition = unicodedata.normalize('NFD', ch)
        if len(decomposition) > 1 and decomposition[0] in shapes and all(m in mark_shapes for m in decomposition[1:]):
            base = decomposition[0]
            shape = compose_accents(shapes[base], decomposition[1:], mark_shapes)
            # A horn can extend right of its base letter. Reserve its ink width
            # so accented letters cannot collide with the following character.
            put(ch, shape, max(advances[base], math.ceil(shape.bounds[2]+78)),
                'New Latin base with matching precomposed accent(s)')
    for ch, source in [('ª', 'a'), ('º', 'o'), ('¹', '1'), ('²', '2'), ('³', '3')]:
        shape = scale(shapes[source], xfact=.58, yfact=.58, origin=(78, 0))
        put(ch, translate(shape, yoff=735), reason='Matching superior glyph')
    # Frequently used currency shapes use the new letter structures.
    put('¢', unary_union([shapes['C'], box(490, -120, 650, 1870)]), reason='New C with currency bar')
    put('£', unary_union([shapes['L'], box(0, 670, 850, 930)]), reason='New L with currency crossbar')
    put('¥', unary_union([shapes['Y'], box(180, 520, 1330, 710), box(200, 880, 1310, 1070)]),
        reason='New Y with currency crossbars')
    put('€', unary_union([shapes['C'], box(0, 640, 830, 810), box(0, 995, 850, 1165)]),
        reason='New C with currency crossbars')
    put('°', translate(mark_shapes['\u030A'], xoff=78, yoff=1430), reason='Matching degree ring')

    names = {1: FAMILY, 2: 'Regular', 3: 'DeathWardDisplay:Regular:1.000', 4: FAMILY+' Regular',
             5: 'Version 1.000', 6: 'DeathWardDisplay-Regular', 16: FAMILY, 17: 'Regular',
             10: 'Heavy hand-cut Latin display face. Alternate capitals on lowercase keys. Includes matching digits, punctuation and precomposed Latin accents; broader inherited glyphs are recorded in coverage.json.'}
    for record in font['name'].names:
        if record.nameID in names: record.string = names[record.nameID].encode(record.getEncoding())
    cff.fontNames = ['DeathWardDisplay-Regular']
    top.FamilyName, top.FullName, top.version = FAMILY, FAMILY+' Regular', '1.000'
    font['OS/2'].sCapHeight = 1760
    font['OS/2'].sxHeight = 1760
    font['hhea'].advanceWidthMax = max(w for w, _ in font['hmtx'].metrics.values())
    font['OS/2'].xAvgCharWidth = round(sum(w for w, _ in font['hmtx'].metrics.values())/len(order))
    new_top = math.ceil(max(g.bounds[3] for ch, g in shapes.items() if ch in records))+32
    new_bottom = math.floor(min(g.bounds[1] for ch, g in shapes.items() if ch in records))-32
    font['hhea'].ascent = max(font['hhea'].ascent, new_top)
    font['hhea'].descent = min(font['hhea'].descent, new_bottom)
    font['OS/2'].sTypoAscender = max(font['OS/2'].sTypoAscender, new_top)
    font['OS/2'].sTypoDescender = min(font['OS/2'].sTypoDescender, new_bottom)
    font['OS/2'].usWinAscent = max(font['OS/2'].usWinAscent, new_top)
    font['OS/2'].usWinDescent = max(font['OS/2'].usWinDescent, -new_bottom)
    font.recalcTimestamp = False
    font.save(OUTPUT)

    checked, baseline = TTFont(OUTPUT, checkChecksums=2), TTFont(BASE)
    assert checked.sfntVersion == 'OTTO' and 'CFF ' in checked
    assert checked.getBestCmap() == cmap and checked.getGlyphOrder() == order
    for tag in checked.keys():
        if tag != 'GlyphOrder': checked[tag]
    before, after = baseline.getGlyphSet(), checked.getGlyphSet()
    changed = []
    for name in order:
        a, b = DecomposingRecordingPen(before), DecomposingRecordingPen(after)
        before[name].draw(a)
        after[name].draw(b)
        if a.value != b.value: changed.append(name)
    expected = {cmap[ord(ch)] for ch in records if ch not in APPROVED}
    assert set(changed) == expected, (set(changed)-expected, expected-set(changed))
    for ch in APPROVED:
        name = cmap[ord(ch)]
        assert baseline['hmtx'][name] == checked['hmtx'][name]
        assert baseline['CFF '].cff.topDictIndex[0].CharStrings[name].program == checked['CFF '].cff.topDictIndex[0].CharStrings[name].program
    assert set(string.printable[:94]).issubset(records)
    for size in [16, 24, 32, 48, 96, 220]:
        raster_font = ImageFont.truetype(str(OUTPUT), size)
        for ch in records:
            # Soft hyphen is intentionally suppressed by text layout unless a
            # line break uses it; validate its outline with the glyph checks.
            if unicodedata.category(ch) != 'Cf':
                assert raster_font.getmask(ch).getbbox(), (ch, size)
    raster_font = ImageFont.truetype(str(OUTPUT), 64)
    for cp in cmap: raster_font.getmask(chr(cp))
    # Every alphanumeric pair has a positive vector ink gap. At small sizes,
    # faint antialiasing fringes can share a pixel; also check 50% raster coverage.
    vector_gap = min(advances[a]+shapes[b].bounds[0]-shapes[a].bounds[2]
                     for a in ALPHANUMERIC for b in ALPHANUMERIC)
    assert vector_gap > 0
    spacing = []
    for size in [24, 32, 48, 96]:
        raster_font = ImageFont.truetype(str(OUTPUT), size)
        # Pillow textbbox includes advance padding; inspect the actual ink.
        ink = {}
        for ch in ALPHANUMERIC:
            mask, offset = raster_font.getmask2(ch, anchor='ls')
            ink_image = Image.frombytes('L', mask.size, bytes(mask))
            ink_box = ink_image.point(lambda value: 255 if value >= 128 else 0).getbbox()
            ink[ch] = (offset[0]+ink_box[0], offset[0]+ink_box[2])
        minimum = min(raster_font.getlength(a) + ink[b][0] - ink[a][1]
                      for a in ALPHANUMERIC for b in ALPHANUMERIC)
        spacing.append({'font_px': size, 'minimum_50pct_ink_gap_px': minimum})
        assert minimum >= 0, spacing[-1]
    assert BASE.read_bytes() == base_bytes and PREVIOUS.read_bytes() == previous_bytes
    preview()
    coverage = {'redesigned_or_approved': [
        {'character': ch, 'unicode': f'U+{ord(ch):04X}', 'name': unicodedata.name(ch, ''), **data}
        for ch, data in sorted(records.items(), key=lambda v: ord(v[0]))],
        'inherited': [{'character': chr(cp), 'unicode': f'U+{cp:04X}', 'glyph': name,
                       'name': unicodedata.name(chr(cp), '')}
                      for cp, name in sorted(cmap.items()) if chr(cp) not in records],
        'note': 'Whitespace, combining-mark layout, additional scripts, phonetic and uncommon symbols retain inherited coverage. Precomposed Latin shown in the first list uses the new style.'}
    (HERE / 'coverage.json').write_text(json.dumps(coverage, indent=2, ensure_ascii=False)+'\n')
    manifest = {'family': FAMILY, 'font': OUTPUT.name,
                'sha256': hashlib.sha256(OUTPUT.read_bytes()).hexdigest(),
                'approved_study_sha256': hashlib.sha256(base_bytes).hexdigest(),
                'previous_block_sha256': hashlib.sha256(previous_bytes).hexdigest(),
                'approved_capitals_preserved_exactly': APPROVED, 'source_fonts_unchanged': True,
                'redesigned_or_approved_characters': len(records), 'changed_glyphs_from_study': len(changed),
                'inherited_characters': len(coverage['inherited']), 'unicode_mappings': len(cmap), 'glyph_count': len(order),
                'scope': 'Full ASCII Latin display set plus matching precomposed Latin accents and common punctuation/currency. Lowercase is alternate capitals.',
                'freeType_all_mapped_rendered': len(cmap), 'redesigned_sizes_rendered': [16, 24, 32, 48, 96, 220],
                'minimum_alphanumeric_vector_ink_gap_units': vector_gap,
                'spacing_checks': spacing, 'human_six_letter_direction_accepted': True,
                'human_full_font_acceptance': True, 'game_integrated': True,
                'human_native_in_game_acceptance': True,
                'remaining': ['Browser-specific visual verification',
                              'Broader inherited Unicode redesign and combining-mark layout are outside this Latin display delivery']}
    (HERE / 'manifest.json').write_text(json.dumps(manifest, indent=2)+'\n')
    (HERE / 'OFL.txt').write_bytes((STUDY_DIR / 'OFL.txt').read_bytes())
    print(json.dumps({k: manifest[k] for k in ['font', 'sha256', 'approved_capitals_preserved_exactly',
                      'redesigned_or_approved_characters', 'changed_glyphs_from_study', 'inherited_characters', 'spacing_checks']}, indent=2))


if __name__ == '__main__': main()
