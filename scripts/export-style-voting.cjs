#!/usr/bin/env node
// Export contact sheets from the actual captures. Canvas only lays out the
// existing images and captions; it never regenerates or grades screenshot pixels.
const fs = require('node:fs');
const path = require('node:path');
const crypto = require('node:crypto');
const { spawnSync } = require('node:child_process');
const { chromium } = require('../web/node_modules/playwright');

const root = path.resolve(__dirname, '..');
const options = process.argv.slice(2);
const scaleIndex = options.indexOf('--scale');
const outputScale = scaleIndex < 0 ? 1 : Number(options[scaleIndex + 1]);
const twoOverOne = options.includes('--two-over-one');
const directoryOnly = options.includes('--directory') || twoOverOne;
if (!Number.isInteger(outputScale) || outputScale < 1 || outputScale > 3)
    throw Error('--scale must be 1, 2 or 3');
const output = path.join(root, twoOverOne ? 'artifacts/style-voting-no-text' :
    directoryOnly ? 'artifacts/style-voting-large' : 'artifacts/style-voting');
const formatDirectory = (suite, format) => directoryOnly
    ? path.join(output, suite === 'rendering-styles' ? '' : 'asset-sample', format === 'jpg' ? '' : 'lossless-png')
    : path.join(output, suite, format);
const number = value => String(value).padStart(2, '0');
const uri = file => 'data:image/png;base64,' + fs.readFileSync(file).toString('base64');
const metadata = spawnSync('python3', ['-c', `
import importlib.util,json
from pathlib import Path
p=Path('scripts/visual-style-report.py')
s=importlib.util.spec_from_file_location('styles',p)
m=importlib.util.module_from_spec(s);s.loader.exec_module(m)
print(json.dumps({'styles':m.STYLES,'views':m.VIEWS}))
`], { cwd: root, encoding: 'utf8' });
if (metadata.status !== 0) throw Error(metadata.stderr);
const { styles, views } = JSON.parse(metadata.stdout);

async function main() {
    const suites = [{
        id: 'rendering-styles', title: 'VISUAL STYLE VOTE', vote: `Vote by number: 01–${number(styles.length)}`,
        footer: `Same cameras, geometry and poses across all ${styles.length} options.`,
        cards: styles.map((style, index) => ({
            code: number(index + 1), slug: style.id, name: style.name,
            images: views.map(view => ({
                label: view.name,
                file: path.join(root, 'artifacts', `cel-${({ original: 'before', cel: 'after' })[style.id] || style.id}-${view.id}.png`)
            }))
        }))
    }];
    const sample = path.join(root, 'artifacts/art-sample');
    if (fs.existsSync(sample)) suites.push({
        id: 'asset-sample', title: 'ASSET DIRECTION VOTE', vote: 'Vote by letter: A–D',
        footer: 'Same cameras and lighting. Separate experiment from rendering-style voting.',
        cards: [['original', 'Original assets'], ['shapes', 'Custom silhouettes'],
                ['paint', 'Painted materials'], ['combined', 'Silhouettes + painted materials']].map(([slug, name], index) => ({
            code: String.fromCharCode(65 + index), slug, name,
            images: ['Whole sample', 'Protagonist', 'Canvas & timber'].map((label, view) => ({
                label, file: path.join(sample, `${slug}-${view}.png`)
            }))
        }))
    });
    // Fail before exporting if any of the matched views is missing.
    for (const suite of suites) for (const card of suite.cards) for (const image of card.images)
        if (!fs.existsSync(image.file)) throw Error(`Missing source capture: ${image.file}`);

    const browser = await chromium.launch({
        executablePath: process.env.DEATHWARD_BROWSER || undefined,
        headless: true, args: ['--no-sandbox']
    });
    try {
        const page = await browser.newPage();
        const manifest = { format: 2, scale: outputScale, directory_only: directoryOnly,
            layout: twoOverOne ? 'two-over-one-no-text' : 'vertical-labeled',
            description: 'Uncropped captures. Enlarged cards repeat source pixels without inventing detail.', suites: [] };
        for (const suite of suites) {
            for (const format of ['png', 'jpg']) fs.mkdirSync(formatDirectory(suite.id, format), { recursive: true });
            const record = { id: suite.id, title: suite.title, cards: [],
                directories: Object.fromEntries(['png', 'jpg'].map(format => [format, path.relative(output, formatDirectory(suite.id, format))])) };
            for (const card of suite.cards) {
                const result = await page.evaluate(async ({ suite, card, outputScale, twoOverOne }) => {
                    const loaded = await Promise.all(card.images.map(async image => {
                        const img = new Image(); img.src = image.data; await img.decode(); return img;
                    }));
                    if (twoOverOne) {
                        const [first, second, third] = loaded;
                        const width = Math.max(first.width + second.width, third.width);
                        const topHeight = Math.max(first.height, second.height);
                        const canvas = document.createElement('canvas');
                        canvas.width = width * outputScale;
                        canvas.height = (topHeight + third.height) * outputScale;
                        const ctx = canvas.getContext('2d');
                        ctx.scale(outputScale, outputScale);
                        ctx.imageSmoothingEnabled = false;
                        ctx.fillStyle = '#182125';
                        ctx.fillRect(0, 0, width, topHeight + third.height);
                        const topX = (width - first.width - second.width) / 2;
                        const positions = [[topX, 0], [topX + first.width, 0],
                            [(width - third.width) / 2, topHeight]];
                        const panels = loaded.map((img, index) => {
                            const [x, y] = positions[index];
                            ctx.drawImage(img, x, y);
                            return { x: x * outputScale, y: y * outputScale,
                                width: img.width * outputScale, height: img.height * outputScale };
                        });
                        return { png: canvas.toDataURL('image/png').split(',')[1],
                            jpg: canvas.toDataURL('image/jpeg', .96).split(',')[1],
                            width: canvas.width, height: canvas.height, panels };
                    }
                    const width = Math.max(...loaded.map(img => img.width));
                    const pad = 32, top = 166, label = 46, gap = 24, foot = 78;
                    const canvas = document.createElement('canvas');
                    const logicalWidth = width + pad * 2;
                    const logicalHeight = top + loaded.reduce((sum, img) => sum + img.height + label + gap, 0) + foot;
                    canvas.width = logicalWidth * outputScale;
                    canvas.height = logicalHeight * outputScale;
                    const ctx = canvas.getContext('2d', { willReadFrequently: true });
                    ctx.scale(outputScale, outputScale);
                    ctx.imageSmoothingEnabled = false;
                    ctx.fillStyle = '#182125'; ctx.fillRect(0, 0, logicalWidth, logicalHeight);
                    ctx.textBaseline = 'top';
                    ctx.fillStyle = '#b4c0c0'; ctx.font = '20px Arial, sans-serif';
                    ctx.fillText('DEATHWARD / ' + suite.title, pad, 23);
                    ctx.textAlign = 'right'; ctx.fillText(suite.vote, logicalWidth - pad, 23); ctx.textAlign = 'left';
                    ctx.fillStyle = '#eee8db'; ctx.fillRect(pad, 67, 88, 70);
                    ctx.fillStyle = '#182125'; ctx.font = 'bold 40px Arial, sans-serif';
                    ctx.textAlign = 'center'; ctx.fillText(card.code, pad + 44, 81); ctx.textAlign = 'left';
                    ctx.fillStyle = '#f0eade';
                    let size = 48;
                    do { ctx.font = `bold ${size}px Arial, sans-serif`; --size; }
                    while (ctx.measureText(card.name).width > logicalWidth - 190);
                    ctx.fillText(card.name, pad + 112, 82);
                    const panels = [];
                    let y = top;
                    loaded.forEach((img, index) => {
                        ctx.fillStyle = '#2a363b'; ctx.fillRect(pad, y, width, label);
                        ctx.fillStyle = '#e7e8e2'; ctx.font = '22px Arial, sans-serif';
                        ctx.fillText(`${index + 1} / ${card.images[index].label}`, pad + 16, y + 12);
                        const x = pad + (width - img.width) / 2;
                        // Integer enlargement preserves every source pixel as an exact block.
                        ctx.drawImage(img, x, y + label);
                        panels.push({ x: x * outputScale, y: (y + label) * outputScale,
                            width: img.width * outputScale, height: img.height * outputScale });
                        y += label + img.height + gap;
                    });
                    ctx.fillStyle = '#b4c0c0'; ctx.font = '20px Arial, sans-serif';
                    ctx.fillText(suite.footer, pad, y + 10);
                    ctx.fillText('Full screenshots • Original capture colors • No cropping', pad, y + 40);
                    return { png: canvas.toDataURL('image/png').split(',')[1],
                        jpg: canvas.toDataURL('image/jpeg', .96).split(',')[1],
                        width: canvas.width, height: canvas.height, panels };
                }, { outputScale, twoOverOne, suite: { title: suite.title, vote: suite.vote, footer: suite.footer },
                    card: { ...card, images: card.images.map(image => ({ label: image.label, data: uri(image.file) })) } });
                const stem = `${card.code}-${card.slug}`;
                for (const format of ['png', 'jpg'])
                    fs.writeFileSync(path.join(formatDirectory(suite.id, format), `${stem}.${format}`), Buffer.from(result[format], 'base64'));
                record.cards.push({ code: card.code, name: card.name, slug: card.slug,
                    width: result.width, height: result.height,
                    images: card.images.map((image, index) => ({
                        label: image.label, source: path.relative(root, image.file),
                        sha256: crypto.createHash('sha256').update(fs.readFileSync(image.file)).digest('hex'),
                        ...result.panels[index]
                    })) });
                console.log(`${suite.id}/${stem}: ${result.width} × ${result.height}`);
            }

            // An optional one-image index helps people locate the number to vote for.
            if (!twoOverOne) {
            const overview = await page.evaluate(async ({ cards, title, vote, outputScale }) => {
                const columns = 4, cellWidth = 720, pad = 24, header = 144, caption = 84;
                const cellHeight = 500 + caption;
                const canvas = document.createElement('canvas');
                const logicalWidth = pad + columns * (cellWidth + pad);
                const logicalHeight = header + Math.ceil(cards.length / columns) * (cellHeight + pad) + pad;
                canvas.width = logicalWidth * outputScale;
                canvas.height = logicalHeight * outputScale;
                const ctx = canvas.getContext('2d');
                ctx.scale(outputScale, outputScale);
                ctx.fillStyle = '#182125'; ctx.fillRect(0, 0, logicalWidth, logicalHeight);
                ctx.textBaseline = 'top'; ctx.fillStyle = '#eee8db'; ctx.font = 'bold 46px Arial, sans-serif';
                ctx.fillText('DEATHWARD / ' + title, pad, 28);
                ctx.fillStyle = '#b4c0c0'; ctx.font = '25px Arial, sans-serif';
                ctx.fillText(vote + ' • Open the individual cards for all three views.', pad, 89);
                for (let i = 0; i < cards.length; ++i) {
                    const card = cards[i], img = new Image(); img.src = card.data; await img.decode();
                    const x = pad + (i % columns) * (cellWidth + pad);
                    const y = header + Math.floor(i / columns) * (cellHeight + pad);
                    ctx.fillStyle = '#2a363b'; ctx.fillRect(x, y, cellWidth, cellHeight);
                    const scale = Math.min(cellWidth / img.width, 500 / img.height);
                    const w = img.width * scale, h = img.height * scale;
                    ctx.drawImage(img, x + (cellWidth - w) / 2, y + (500 - h) / 2, w, h);
                    ctx.fillStyle = '#eee8db'; ctx.font = 'bold 28px Arial, sans-serif';
                    ctx.fillText(card.code + ' / ' + card.name, x + 18, y + 523);
                }
                return { png: canvas.toDataURL('image/png').split(',')[1],
                    jpg: canvas.toDataURL('image/jpeg', .96).split(',')[1] };
            }, { outputScale, title: suite.title, vote: suite.vote,
                cards: suite.cards.map(card => ({ code: card.code, name: card.name, data: uri(card.images[0].file) })) });
            for (const format of ['png', 'jpg'])
                fs.writeFileSync(path.join(formatDirectory(suite.id, format), `00-overview.${format}`), Buffer.from(overview[format], 'base64'));
            }
            manifest.suites.push(record);
        }
        fs.writeFileSync(path.join(output, 'manifest.json'), JSON.stringify(manifest, null, 2) + '\n');
        // Pillow only checks exact retained screenshot pixels; it does not edit images.
        const validation = spawnSync('python3', ['-c', `
from pathlib import Path
import hashlib,json,zipfile,sys
import numpy as np
from PIL import Image
root=Path.cwd(); output=Path(sys.argv[1])
manifest=json.loads((output/'manifest.json').read_text())
scale=manifest['scale']; panel_count=0
for suite in manifest['suites']:
    key=[]
    for card in suite['cards']:
        key.append(card['code']+' / '+card['name'])
        sheet=Image.open(output/suite['directories']['png']/(card['code']+'-'+card['slug']+'.png')).convert('RGB')
        assert sheet.size==(card['width'],card['height'])
        for panel in card['images']:
            source=root/panel['source']
            assert hashlib.sha256(source.read_bytes()).hexdigest()==panel['sha256']
            original=Image.open(source).convert('RGB')
            x,y=panel['x'],panel['y']
            actual=sheet.crop((x,y,x+panel['width'],y+panel['height']))
            original=np.asarray(original); actual=np.asarray(actual)
            for dy in range(scale):
                for dx in range(scale):
                    assert np.array_equal(original,actual[dy::scale,dx::scale]),(card['name'],panel['label'])
            panel_count+=1
    readme=('DEATHWARD / '+suite['title']+'\\n\\n'
        'Upload the numbered individual images. Each contains all three matched screenshots.\\n'
        + ('Two screenshots side by side, third centered below. No text added to images; identify styles by filename.\\n'
           if manifest['layout']=='two-over-one-no-text' else
           '00-overview is an optional thumbnail index. Vote using the number/letter in the header.\\n') +
        'JPG files are smaller for uploads. PNG files preserve source pixels as exact blocks.\\n'
        f'Cards are enlarged {scale}x; this does not add new scene detail.\\n'
        'Rendering styles and the recent asset-direction sample are separate ballots.\\n\\n'
        +'\\n'.join(key)+'\\n')
    (output/suite['directories']['jpg']/'README.txt').write_text(readme)
    if manifest['directory_only']:
        print('Loose images: '+str(output/suite['directories']['jpg']))
        continue
    for fmt in ['jpg','png']:
        target=output/(suite['id']+('-upload.zip' if fmt=='jpg' else '-lossless.zip'))
        with zipfile.ZipFile(target,'w',compression=zipfile.ZIP_DEFLATED,compresslevel=6) as z:
            z.writestr('README.txt',readme)
            for p in sorted((output/suite['directories'][fmt]).glob('*.'+fmt)):z.write(p,p.name)
        print(str(target.relative_to(root))+': '+str(round(target.stat().st_size/1048576,1))+' MiB')
print(f'PASS: all {panel_count} source panels preserved in PNG cards at {scale}x; source files unchanged')
`, output], { cwd: root, encoding: 'utf8' });
        if (validation.status !== 0) throw Error(validation.stderr || validation.stdout);
        console.log(validation.stdout.trim());
    } finally {
        await browser.close();
    }
}
main().catch(error => { console.error(error); process.exitCode = 1; });
