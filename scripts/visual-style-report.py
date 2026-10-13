#!/usr/bin/env python3
"""Build a portable, offline comparison or gallery from native visual-style captures."""
import argparse
import base64
import datetime
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
STYLES = [
    dict(id="original", name="Original", tag="The baseline",
         description="Soft lighting, bloom and the established warm Western palette.",
         lighting="Continuous daylight", finish="Soft bloom and atmospheric grade",
         character="Soft, warm and familiar."),
    dict(id="cel", name="Cel-shaded", tag="Crisp & graphic",
         description="Three lighting bands, thin dark contours and a crisp finish.",
         lighting="Three stepped light bands", finish="Thin depth outlines; no bloom",
         character="Clear silhouettes and strong low-poly shapes."),
    dict(id="comic", name="Western comic", tag="Ink & paper",
         description="Stronger ink, crosshatching in dark areas and restrained paper grain.",
         lighting="Stepped light, darker ambient fill", finish="Ink contours, hatching and paper",
         character="Illustrated Western panels; more visible surface pattern."),
    dict(id="painted", name="Painted frontier", tag="Color & atmosphere",
         description="Cooler shadows, creamy highlights and gentle patches of color.",
         lighting="Continuous light, lifted cool shadows", finish="Edge-aware softening; no ink",
         character="Quiet and atmospheric, with less distant contrast."),
    dict(id="poster", name="Wanted poster", tag="Six printing inks",
         description="Cream, charcoal, rust and ochre form a deliberately limited print palette.",
         lighting="Stepped light", finish="Six ink tones, contours and paper fibres",
         character="Bold poster shapes; deliberately discards natural surface colors."),
    dict(id="noir", name="Western noir", tag="Light & suspicion",
         description="High-contrast monochrome with selective warm and turquoise accents.",
         lighting="Reduced ambient fill, stronger contrast", finish="Monochrome grade, selective color and fine grain",
         character="Dramatic shadows; saturated accents are selected by color, not object identity."),
    dict(id="retro", name="Retro 3D", tag="Pixels & dither",
         description="Chunkier world pixels, a reduced color palette and ordered dithering.",
         lighting="Continuous daylight", finish="Pixel grid and 4-bit-per-channel quantization",
         character="An early-3D flavor. UI stays at the window's full resolution."),
    dict(id="woodcut", name="Woodcut / linocut", tag="Carved & printed",
         description="Three base inks, bold silhouettes and cream gouges cut through the shadows.",
         lighting="Stepped light, deep neutral fill", finish="Charcoal, ochre and cream; irregular carved strokes",
         character="A rough frontier print, with deliberate loss of natural color."),
    dict(id="watercolor", name="Watercolor", tag="Translucent pigment",
         description="Pale paper beneath translucent washes, with pigment collecting at boundaries.",
         lighting="Continuous light, lifted cool fill", finish="Edge-aware washes, pigment pooling and paper tooth",
         character="Lighter and airier than Painted frontier; distant shapes soften into paper."),
    dict(id="pencil", name="Colored pencil", tag="Strokes & paper tooth",
         description="Overlapping colored strokes leave paper visible between directional marks.",
         lighting="Continuous light, lifted cool fill", finish="Colored cross-strokes, narrow graphite edges and paper",
         character="A textured sketchbook treatment. Strokes are screen-anchored, not mesh brushwork."),
    dict(id="ink", name="Ink wash", tag="Brush & gray washes",
         description="Broad smoky grays, pale warm paper and gently uneven brush-like stains.",
         lighting="Continuous light, neutral fill", finish="Monochrome pigment washes and soft dark boundaries",
         character="A quieter, softer monochrome than Noir, with visible paper in the lights."),
    dict(id="diorama", name="Miniature diorama", tag="A painted miniature",
         description="Matte color, deeper contact shading and a restrained focus falloff around the camera target.",
         lighting="Soft continuous light, balanced cool fill", finish="Depth-based contact approximation and gentle depth focus",
         character="A tabletop rendering treatment using the existing meshes. Contact shading uses visible depth, not baked AO."),
    dict(id="cinema", name="Spaghetti Western", tag="Dust & celluloid",
         description="Sun-bleached highlights, deeper cool shadows and a restrained photographic finish.",
         lighting="Reduced ambient fill, continuous contrast", finish="Muted color, soft highlight shoulder and fine stable grain",
         character="A cinematic grade without letterboxing or a heavy sepia filter."),
    dict(id="crt", name="CRT arcade", tag="Scanlines & phosphors",
         description="Coarse world pixels, fixed scanlines, RGB phosphors and subtle horizontal light bleed.",
         lighting="Continuous daylight", finish="5-bit color, scanlines, phosphor mask and restrained vignette",
         character="An arcade-monitor treatment. No flicker or screen warp; HUD and aiming remain unchanged."),
    dict(id="spectral", name="Spectral frontier", tag="Cold light & warm embers",
         description="Desaturated blue-green scenery, luminous contour rims and selective warm accents.",
         lighting="Cool ambient light, subdued direct sun", finish="Cold grade, bright depth rims and gentle distant haze",
         character="An eerie Western. Warm accents are chosen by color, not a lantern-specific object mask."),
    dict(id="sumi", name="Sumi-e frontier", tag="Brush, ink & vivid color",
         description="An Okami-inspired treatment: bold brush contours, warm paper and vivid painted colors.",
         lighting="Three painted light bands, cool violet shadow fill", finish="Irregular ink contours, soft bleed and vermilion/jade accents",
         character="Bold brushwork over the existing frontier scenery, with creamy highlights and violet-tinted shadows."),
]
VIEWS = [
    dict(id="fort", name="Fort Mercy", note="Architecture, ground, foliage and broad shadows."),
    dict(id="player", name="Character & train", note="A closer look at the protagonist, materials and silhouette."),
    dict(id="canyon", name="Generated canyon", note="Seed 1866, dry variant: cliffs, paths and terrain transitions."),
]

PAGE = r"""<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>DeathWard · Visual style comparison</title>
<style>
:root{color-scheme:dark;--bg:#141b1d;--panel:#1e282b;--line:#3b4645;--paper:#f0e6cf;--muted:#abb5ad;--gold:#dfae62;--mint:#82c6b6}
*{box-sizing:border-box}body{margin:0;background:var(--bg);color:var(--paper);font:16px/1.6 system-ui,sans-serif}
main{max-width:1440px;margin:auto;padding:36px 40px 56px}header{border-top:3px solid var(--gold);padding:22px 0 26px}
.eyebrow{font:12px/1.5 ui-monospace,monospace;text-transform:uppercase;letter-spacing:.15em;color:var(--gold)}
h1{font:clamp(32px,4.5vw,62px)/1.05 Georgia,serif;font-weight:400;margin:18px 0}h2{font:30px/1.2 Georgia,serif;font-weight:400;margin:0 0 10px}p{margin:0 0 12px}
.lead{max-width:810px;color:var(--muted);font-size:18px}.meta{display:flex;gap:24px;flex-wrap:wrap;margin-top:20px;font-size:13px;color:var(--mint)}
.toolbar{display:grid;grid-template-columns:1fr 1fr 1fr auto;gap:18px;align-items:end;padding:20px;background:var(--panel);border:1px solid var(--line);border-bottom:0}
label{display:block;font:11px/1.5 ui-monospace,monospace;letter-spacing:.08em;text-transform:uppercase;color:var(--muted);margin-bottom:7px}
select,button,input{font:inherit}select{width:100%;background:var(--bg);border:1px solid #5c6863;color:var(--paper);padding:10px 12px;min-height:46px;border-radius:0}
button{cursor:pointer;border:1px solid var(--line);color:var(--paper);background:var(--panel);padding:10px 16px}
button:hover{border-color:var(--gold)}:focus-visible{outline:2px solid var(--mint);outline-offset:4px}
#stage{position:relative;width:100%;aspect-ratio:1.44;overflow:hidden;cursor:ew-resize;background:#0c1112;--split:50%;touch-action:pan-y}
#stage img{position:absolute;inset:0;width:100%;height:100%;object-fit:contain;pointer-events:none;user-select:none}
#candidateImage{clip-path:inset(0 0 0 var(--split))}#divider{position:absolute;left:var(--split);top:0;bottom:0;width:2px;background:var(--paper);pointer-events:none}
#divider span{position:absolute;top:50%;left:1px;transform:translate(-50%,-50%);border:1px solid var(--paper);background:#152023e8;padding:4px 9px;font-size:23px}
.badge{position:absolute;top:18px;background:#121b1fe8;padding:6px 12px;font:12px/1.4 ui-monospace,monospace;pointer-events:none;border:1px solid #69736a}
#referenceLabel{left:18px}#candidateLabel{right:18px}
.sliderRow{display:flex;gap:20px;align-items:center;padding:14px 20px;border:1px solid var(--line);background:var(--panel)}
.sliderRow label{margin:0;white-space:nowrap}input[type=range]{width:100%;accent-color:var(--gold);cursor:ew-resize}#splitValue{font:13px ui-monospace,monospace;min-width:35px;color:var(--gold)}
#viewNote{color:var(--muted);font-size:13px;padding:12px 1px}
.detail{display:grid;grid-template-columns:1fr 1fr;gap:30px;border-bottom:1px solid var(--line);padding:20px 0 32px}
.detail h3{font:26px Georgia,serif;font-weight:400;margin:0 0 12px}.detail p{color:var(--muted)}.detail .eyebrow{margin-bottom:10px}
.run{display:flex;gap:8px;margin-top:14px}.run input{font:12px ui-monospace,monospace;min-width:0;flex:1;color:var(--mint);background:#101719;border:1px solid var(--line);padding:10px}
.run button{font-size:13px}#copyStatus{min-height:22px;font-size:12px;color:var(--mint)}
section{margin-top:32px}.sectionIntro{color:var(--muted);margin-bottom:22px}
#gallery{display:grid;grid-template-columns:repeat(auto-fit,minmax(255px,1fr));gap:18px}
.card{padding:0;text-align:left;overflow:hidden;background:#182225;border:1px solid var(--line)}
.card[aria-pressed=true]{border-color:var(--gold);box-shadow:inset 0 -3px var(--gold)}.card img{display:block;width:100%;aspect-ratio:1.44;object-fit:contain}
.cardBody{padding:16px 18px 20px}.card h3{font:23px Georgia,serif;margin:8px 0}.card p{font-size:14px;color:var(--muted);margin:0}.card .eyebrow{font-size:10px}
.tableWrap{overflow-x:auto}table{border-collapse:collapse;width:100%;font-size:14px}th,td{text-align:left;padding:16px 18px 16px 0;border-bottom:1px solid var(--line);vertical-align:top}
th{font:11px ui-monospace,monospace;text-transform:uppercase;letter-spacing:.08em;color:var(--gold)}td:first-child{white-space:nowrap;color:var(--paper)}td{color:var(--muted)}
.notes{display:grid;grid-template-columns:1fr 1fr;gap:38px;background:var(--panel);padding:26px 30px;border-left:3px solid var(--gold);font-size:14px}
.notes h3{font:22px Georgia,serif;margin:0 0 12px}.notes p{color:var(--muted)}kbd{font:12px ui-monospace,monospace;padding:2px 6px;border:1px solid #66746a;color:var(--paper)}
footer{margin-top:28px;color:var(--muted);font:12px ui-monospace,monospace}noscript{display:block;padding:24px;color:var(--gold)}
@media(max-width:780px){main{padding:20px 16px 32px}.toolbar{grid-template-columns:1fr 1fr;gap:12px;padding:14px}.detail,.notes{grid-template-columns:1fr;gap:18px}.badge{top:8px;font-size:10px;max-width:43%}#referenceLabel{left:8px}#candidateLabel{right:8px}.sliderRow{gap:12px}.sliderRow label{font-size:10px}.meta{gap:14px}.run{flex-wrap:wrap}.run input{flex-basis:80%;font-size:10px}}
@media print{body{background:white;color:#222}main{max-width:none;padding:0}.toolbar,#stage,.sliderRow,#viewNote,.detail,.run,.notes,footer{display:none}.meta,.lead,.sectionIntro,.card p,td{color:#444!important}.card{break-inside:avoid;color:#222;background:white;border:1px solid #bbb}#gallery{grid-template-columns:repeat(2,1fr)}table{font-size:10px}h1{font-size:32px}.eyebrow,th{color:#765126}}
</style>
</head>
<body>
<main>
<header>
<div class="eyebrow">DeathWard / Art direction study</div>
<h1>One frontier. <span id="styleTotal"></span> visual styles.</h1>
<p class="lead">Compare the same fort, protagonist and generated canyon. Geometry, cameras and poses match; each preset changes the lighting and rendering treatment.</p>
<div class="meta"><span id="presetCount"></span><span id="viewCount"></span><span id="captureCount"></span><span>Works entirely offline</span></div>
</header>
<noscript>This interactive comparison needs JavaScript enabled. It makes no network requests.</noscript>
<div class="toolbar">
<div><label for="view">Viewpoint</label><select id="view"></select></div>
<div><label for="reference">Left / Reference</label><select id="reference"></select></div>
<div><label for="candidate">Right / Compare with</label><select id="candidate"></select></div>
<button id="swap" type="button" title="Swap reference and comparison styles">Swap sides ⇄</button>
</div>
<div id="stage" aria-label="Matching renders with an adjustable comparison divider">
<img id="referenceImage" alt="">
<img id="candidateImage" alt="">
<div id="divider" aria-hidden="true"><span>↔</span></div>
<span id="referenceLabel" class="badge"></span><span id="candidateLabel" class="badge"></span>
</div>
<div class="sliderRow"><label for="split">Drag to compare</label><input id="split" type="range" min="0" max="100" value="50" aria-label="Comparison divider position"><output id="splitValue" for="split">50%</output></div>
<p id="viewNote"></p>
<div class="detail">
<div><div class="eyebrow">Current comparison</div><h3 id="detailTitle"></h3><p id="detailDescription"></p><p id="detailCharacter"></p></div>
<div><div class="eyebrow">Try this style in the game</div><p>Start at Fort Mercy, or use the live selector in your current session.</p><div class="run"><input id="command" readonly aria-label="Launch command"><button id="copy" type="button">Copy</button></div><p id="copyStatus" aria-live="polite"></p></div>
</div>
<section aria-labelledby="galleryTitle">
<h2 id="galleryTitle">The full lineup</h2><p class="sectionIntro">Choose a card to compare it on the right. Changing the viewpoint updates every card.</p>
<div id="gallery"></div>
</section>
<section aria-labelledby="treatmentTitle">
<h2 id="treatmentTitle">What changes</h2>
<div class="tableWrap"><table><thead><tr><th>Preset</th><th>Light</th><th>Surface &amp; finish</th><th>Visual character</th></tr></thead><tbody id="treatments"></tbody></table></div>
</section>
<section class="notes">
<div><h3>Switch while playing</h3><p>Use <kbd>F6</kbd> in a hub, town editor or cinematic editor to cycle through the presets. In generated missions, use <strong>Pause → Visual Style</strong>; F6 retains its mission cheat.</p><p>The choice lasts for the session. A normal launch starts in Original. The earlier <code>--cel-shading</code> flag still selects Cel-shaded.</p></div>
<div><h3>How to read this comparison</h3><p>These are rendered game captures, not concept art. Assets and scene placement are shared. The character view uses a fixed pose; the canyon uses seed 1866 with water disabled for a repeatable frame.</p><p>Paper, ink and dithering affect the world image. HUD text stays at full resolution. The style switch does not edit maps, collision or campaign data.</p></div>
</section>
<footer id="generated"></footer>
</main>
<script>
const data = __DATA__;
const get = id => document.getElementById(id);
const styles = data.styles;
get('styleTotal').textContent = styles.length;
get('presetCount').textContent = styles.length + ' presets';
get('viewCount').textContent = data.views.length + ' matching viewpoints';
get('captureCount').textContent = styles.length * data.views.length + ' native captures';
const byId = Object.fromEntries(styles.map(style => [style.id, style]));
function options(element, items) {
  for (const item of items) element.add(new Option(item.name, item.id));
}
options(get('view'), data.views);
options(get('reference'), styles);
options(get('candidate'), styles);
get('reference').value = 'cel';
get('candidate').value = 'sumi';
function setSplit(value) {
  get('split').value = Math.max(0, Math.min(100, value));
  get('stage').style.setProperty('--split', get('split').value + '%');
  get('splitValue').value = get('split').value + '%';
}
function redraw() {
  const view = get('view').value;
  const left = byId[get('reference').value];
  const right = byId[get('candidate').value];
  get('referenceImage').src = data.images[left.id][view];
  get('candidateImage').src = data.images[right.id][view];
  get('referenceImage').alt = left.name + ' — ' + view;
  get('candidateImage').alt = right.name + ' — ' + view;
  get('referenceLabel').textContent = left.name;
  get('candidateLabel').textContent = right.name;
  get('viewNote').textContent = data.views.find(item => item.id === view).note;
  get('detailTitle').textContent = right.name;
  get('detailDescription').textContent = right.description;
  get('detailCharacter').textContent = right.character;
  get('command').value = './scripts/run.sh --hub redstone --style ' + right.id;
  get('copyStatus').textContent = '';
  for (const card of get('gallery').children) {
    card.querySelector('img').src = data.images[card.dataset.style][view];
    card.setAttribute('aria-pressed', String(card.dataset.style === right.id));
  }
}
for (const [index, style] of styles.entries()) {
  const card = document.createElement('button');
  card.type = 'button'; card.className = 'card'; card.dataset.style = style.id;
  card.setAttribute('aria-label', 'Compare ' + style.name);
  const img = new Image(); img.alt = style.name + ' preview'; img.loading = 'lazy'; card.append(img);
  const body = document.createElement('div'); body.className = 'cardBody';
  const tag = document.createElement('div'); tag.className = 'eyebrow'; tag.textContent = String(index + 1).padStart(2, '0') + ' / ' + style.tag;
  const title = document.createElement('h3'); title.textContent = style.name;
  const description = document.createElement('p'); description.textContent = style.description;
  body.append(tag, title, description); card.append(body);
  card.addEventListener('click', () => { get('candidate').value = style.id; redraw(); });
  get('gallery').append(card);
  const row = document.createElement('tr');
  for (const text of [style.name, style.lighting, style.finish, style.character]) {
    const cell = document.createElement('td'); cell.textContent = text; row.append(cell);
  }
  get('treatments').append(row);
}
for (const id of ['view', 'reference', 'candidate']) get(id).addEventListener('change', redraw);
get('split').addEventListener('input', event => setSplit(event.target.value));
get('swap').addEventListener('click', () => {
  const old = get('reference').value; get('reference').value = get('candidate').value; get('candidate').value = old; redraw();
});
function moveDivider(event) {
  const bounds = get('stage').getBoundingClientRect();
  setSplit(Math.round((event.clientX - bounds.left) / bounds.width * 100));
}
get('stage').addEventListener('pointerdown', event => {
  if (event.button !== 0) return;
  get('stage').setPointerCapture(event.pointerId); moveDivider(event);
});
get('stage').addEventListener('pointermove', event => {
  if (get('stage').hasPointerCapture(event.pointerId)) moveDivider(event);
});
get('stage').addEventListener('pointerup', event => {
  if (get('stage').hasPointerCapture(event.pointerId)) get('stage').releasePointerCapture(event.pointerId);
});
get('copy').addEventListener('click', async () => {
  try { await navigator.clipboard.writeText(get('command').value); get('copyStatus').textContent = 'Launch command copied.'; }
  catch (_) { get('command').focus(); get('command').select(); get('copyStatus').textContent = 'Command selected — press Ctrl+C to copy.'; }
});
get('generated').textContent = 'DeathWard · Native comparison captures · Generated ' + data.generated + ' · All images embedded';
redraw();
</script>
</body>
</html>
"""

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--captures", type=Path, default=ROOT / "artifacts")
    parser.add_argument("--layout", choices=("comparison", "gallery"), default="comparison")
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    if args.output is None:
        args.output = ROOT / f"artifacts/visual-style-{args.layout}.html"
    images = {}
    for style in STYLES:
        prefix = {"original": "before", "cel": "after"}.get(style["id"], style["id"])
        images[style["id"]] = {}
        for view in VIEWS:
            path = args.captures / f"cel-{prefix}-{view['id']}.png"
            if not path.is_file():
                parser.error(f"Missing {path}. Run ./build/deathward_cel_shading_tests first.")
            images[style["id"]][view["id"]] = "data:image/png;base64," + base64.b64encode(path.read_bytes()).decode("ascii")
    payload = dict(styles=STYLES, views=VIEWS, images=images,
                   generated=datetime.datetime.now().astimezone().strftime("%Y-%m-%d %H:%M %Z"))
    template = (Path(__file__).with_name("visual-style-gallery.html").read_text(encoding="utf-8")
                if args.layout == "gallery" else PAGE)
    page = template.replace("__DATA__", json.dumps(payload, separators=(",", ":")).replace("</", "<\\/"))
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(page, encoding="utf-8")
    print(f"Offline {args.layout}: {args.output} ({args.output.stat().st_size / 1048576:.1f} MiB, {len(STYLES) * len(VIEWS)} embedded images)")

if __name__ == "__main__":
    main()
