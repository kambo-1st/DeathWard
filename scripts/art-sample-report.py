#!/usr/bin/env python3
"""Package the sample viewer's actual renders into a portable offline comparison."""
import base64
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'artifacts/art-sample'


def uri(path):
    return 'data:image/png;base64,' + base64.b64encode(path.read_bytes()).decode()


images = {mode: [uri(OUT / f'{mode}-{view}.png') for view in range(3)]
          for mode in ('original', 'shapes', 'paint', 'combined')}
html = '''<!doctype html>
<html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>DeathWard — The Waystation / Asset Study</title>
<style>
:root{color-scheme:dark;--paper:#eee6d6;--ink:#171f23;--line:#3b4549;--rust:#c28c60}
*{box-sizing:border-box}body{margin:0;background:var(--ink);color:var(--paper);font:16px/1.6 system-ui,sans-serif}
main{max-width:1500px;margin:auto;padding:40px 32px 80px}header{display:flex;justify-content:space-between;gap:30px;align-items:center}
.eyebrow{font-size:12px;letter-spacing:.2em;text-transform:uppercase;color:var(--rust)}h1{font:clamp(40px,5vw,76px)/1.05 Georgia,serif;margin:16px 0}
.intro{max-width:780px;color:#b6c0c0}.badge{border:1px solid #697b70;border-radius:40px;padding:8px 18px;font-size:13px;white-space:nowrap;color:#bad4c1}
.toolbar{margin:32px 0 16px;display:flex;gap:18px;flex-wrap:wrap;align-items:center}.group{display:flex;gap:6px;flex-wrap:wrap}
button{font:inherit;font-size:14px;background:#263136;border:1px solid var(--line);color:var(--paper);padding:9px 16px;border-radius:6px;cursor:pointer}
button[aria-pressed=true]{background:var(--rust);color:#1b2020;border-color:var(--rust)}button:focus-visible,input:focus-visible{outline:3px solid #99b3c2;outline-offset:4px}
.frame{position:relative;aspect-ratio:8/5;overflow:hidden;background:#d6bc81;border:1px solid #55615e;border-radius:8px}
.frame img{width:100%;height:100%;object-fit:contain;position:absolute;inset:0}.frame .after{clip-path:inset(0 0 0 var(--split,50%))}
.divider{position:absolute;left:var(--split,50%);top:0;bottom:0;border-left:2px solid #fff8dc;pointer-events:none}
.label{position:absolute;top:18px;background:#171f23e6;padding:6px 14px;border-radius:4px;font-size:12px;letter-spacing:.08em;text-transform:uppercase}
.left{left:18px}.right{right:18px}label{display:block;margin:18px 0 0;color:#bac5c3;font-size:14px}input{width:100%;accent-color:var(--rust)}
.caption{color:#bcc6c5;max-width:960px}.cards{display:grid;grid-template-columns:repeat(4,1fr);gap:18px;margin:36px 0}.card{padding:22px;background:#222d31;border-top:2px solid #977553;border-radius:4px}
h2{font:27px Georgia,serif;margin:0 0 12px}.card p{font-size:14px;color:#b6c0c0;margin:0}.swatches{display:flex;gap:14px;flex-wrap:wrap}.swatch{display:flex;align-items:center;gap:10px;font-size:13px;color:#b6c0c0}.swatch i{display:block;width:22px;height:22px;border-radius:50%;background:var(--c)}
.notes{display:grid;grid-template-columns:1fr 1fr;gap:40px;padding-top:34px;border-top:1px solid var(--line)}.notes p,.notes li{color:#b6c0c0;font-size:14px}code{color:#e6c6a9}footer{margin-top:40px;color:#879692;font-size:12px}
@media(max-width:850px){main{padding:24px 16px}header{display:block}.badge{display:inline-block}.cards{grid-template-columns:1fr 1fr}.notes{grid-template-columns:1fr}.label{font-size:9px;top:8px;padding:4px 7px}.left{left:8px}.right{right:8px}}
@media(max-width:450px){.cards{grid-template-columns:1fr}button{padding:8px 10px;font-size:12px}}
</style>
<main>
<header><div><div class="eyebrow">DeathWard / Reversible art-direction experiment</div><h1>The Waystation.</h1></div><span class="badge">Separate viewer · Game unchanged</span></header>
<p class="intro">One protagonist. One tent. One wagon. One short fence. A controlled comparison of the current game assets and locally altered shapes and materials, under identical lighting and camera settings.</p>
<div class="toolbar"><div class="group" id="views" aria-label="Camera view"><button data-view="0" aria-pressed="true">Whole sample</button><button data-view="1" aria-pressed="false">Protagonist</button><button data-view="2" aria-pressed="false">Canvas &amp; timber</button></div>
<div class="group" id="modes" aria-label="Sample treatment"><button data-mode="shapes" aria-pressed="false">Silhouettes only</button><button data-mode="paint" aria-pressed="false">Paint only</button><button data-mode="combined" aria-pressed="true">Combined</button></div></div>
<div class="frame" id="frame"><img id="before" alt="Current game assets in the sample arrangement"><img class="after" id="after" alt="Art-direction sample with custom assets"><div class="divider"></div><span class="label left">Current assets</span><span class="label right" id="treatment">Silhouettes + paint</span></div>
<label for="split">Drag to compare. Move fully left for the sample; fully right for the current assets.</label><input id="split" type="range" min="0" max="100" value="50">
<p class="caption" id="caption"></p>
<div class="swatches"><span class="swatch"><i style="--c:#e9dfc9"></i>Ivory canvas</span><span class="swatch"><i style="--c:#6e839a"></i>Dusty indigo</span><span class="swatch"><i style="--c:#a99c85"></i>Sun-worn timber</span><span class="swatch"><i style="--c:#897363"></i>Taupe leather</span></div>
<div class="cards"><article class="card"><h2>The traveler</h2><p>Asymmetric hat and shoulder wrap with a pale hem. Painted cloth and leather. Original face, skeleton and all nine animation streams retained.</p></article>
<article class="card"><h2>The shelter</h2><p>A sagged, uneven ridge and a loose entrance valance. Pale painted canvas replaces the palette-flat fabric. Original structure retained.</p></article>
<article class="card"><h2>The wagon</h2><p>A partial canvas cover, a listing hoop profile and repair boards. Wood and iron remain distinct. Original wheels, chassis and cargo retained.</p></article>
<article class="card"><h2>The fence</h2><p>Leaning timber, uneven rails, an end post and a diagonal repair brace. Painted wood grain replaces the clean palette finish.</p></article></div>
<section class="notes"><div><h2>A fair comparison</h2><p>These are actual native game-renderer captures, not generated mockups. Both sides use the existing Original lighting and post-processing. There is no extra full-screen filter. The unchanged assets are arranged in an isolated study rather than inserted into a live map.</p><p>The source geometry is still visible in the faces, wheels and construction. This is a direction sample, not a finished character redesign.</p></div>
<div><h2>Immediate reversal</h2><p>In the viewer, press <code>1</code> for the original assets, or <code>Tab</code> to alternate before and after. Close the viewer to return to normal work. The game does not load the sample.</p><p>Run <code>scripts/run-art-sample.sh</code>. Orbit by dragging; zoom with the wheel; <code>H</code> focuses the protagonist, <code>Space</code> animates and <code>W</code> previews walking.</p><p>Checked: source character and map hashes unchanged; all nine animation clips load; returning to Original restores identical captured pixels in all three views.</p></div></section>
<footer>All images embedded. Works offline. Painted texture atlas generated with the built-in imagegen tool; prompt and source manifest are in assets/art_sample/.</footer>
</main>
<script id="images" type="application/json">__IMAGES__</script>
<script>
const images=JSON.parse(document.querySelector('#images').textContent);
let mode='combined',view=0;
const names={shapes:'Custom silhouettes',paint:'Painted materials',combined:'Silhouettes + paint'};
const descriptions={shapes:'Shape changes isolated: the original surfaces remain, with neutral materials on added pieces.',paint:'Material changes isolated: original geometry, new painted surfaces. The face and hardware retain their source materials.',combined:'The combined sample: custom silhouettes plus painted materials. Camera, light, ground and post-processing match the original.'};
function update(){document.querySelector('#before').src=images.original[view];document.querySelector('#after').src=images[mode][view];document.querySelector('#treatment').textContent=names[mode];document.querySelector('#caption').textContent=descriptions[mode];document.querySelectorAll('[data-mode]').forEach(b=>b.setAttribute('aria-pressed',b.dataset.mode===mode));document.querySelectorAll('[data-view]').forEach(b=>b.setAttribute('aria-pressed',Number(b.dataset.view)===view));}
document.querySelectorAll('[data-mode]').forEach(b=>b.addEventListener('click',()=>{mode=b.dataset.mode;update();}));
document.querySelectorAll('[data-view]').forEach(b=>b.addEventListener('click',()=>{view=Number(b.dataset.view);update();}));
document.querySelector('#split').addEventListener('input',e=>document.querySelector('#frame').style.setProperty('--split',e.target.value+'%'));
update();
</script></html>'''
destination = ROOT / 'artifacts/art-sample-comparison.html'
destination.write_text(html.replace('__IMAGES__', json.dumps(images, separators=(',', ':'))))
print(destination)
