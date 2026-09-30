// Actual animal inspector input, stationary animation and browser persistence.
const {chromium} = require('playwright');
const assert = require('node:assert/strict');
const path = require('node:path');
const root = path.resolve(__dirname, '..');
(async () => {
  const browser = await chromium.launch({headless: true,
    executablePath: process.env.DEATHWARD_BROWSER || undefined,
    args: ['--no-sandbox', '--enable-gpu', '--use-gl=angle', '--use-angle=gl', '--ignore-gpu-blocklist']});
  const page = await browser.newPage({viewport: {width: 1280, height: 848}});
  const errors = [];
  page.on('pageerror', e => errors.push(String(e)));
  page.on('console', m => {if (/ERROR:|INVALID_OPERATION|shader failed/i.test(m.text())) errors.push(m.text());});
  const wait = (fn, arg) => page.waitForFunction(fn, arg, {timeout: 60000});
  const animal = () => page.evaluate(() => Module.animalEditor);
  const key = async code => {
    await page.keyboard.down(code);
    await page.waitForTimeout(120);
    await page.keyboard.up(code);
    await page.waitForTimeout(120);
  };
  const click = async (x, y) => {
    const box = await page.locator('#canvas').boundingBox();
    await page.mouse.click(box.x + x * box.width / 1440, box.y + y * box.height / 900, {delay: 130});
  };
  const start = async () => {
    await page.goto((process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/') + '?verify&hub=town');
    await wait(() => window.Module?.ready);
    await page.locator('#start').click({noWaitAfter: true});
    await wait(() => Module.state?.frame > 8);
    assert.equal(await page.evaluate(() => Module.state.error), '');
    await key('F4'); await wait(() => Module.state.editor);
    await click(196, 157); await wait(() => Module.animalEditor.selected === 0);
  };
  try {
    await start();
    const before = await animal();
    // Precise movement, with terrain supplying height.
    await click(1180, 499);
    await page.keyboard.type(String(before.homeX + .5), {delay: 80}); await key('Enter');
    await wait(x => Math.abs(Module.animalEditor.homeX - x) < .001, before.homeX + .5);
    await page.keyboard.down('Control'); await key('z'); await page.keyboard.up('Control');
    await wait(x => Module.animalEditor.homeX === x, before.homeX);
    await page.keyboard.down('Control'); await key('y'); await page.keyboard.up('Control');
    await wait(x => Math.abs(Module.animalEditor.homeX - x) < .001, before.homeX + .5);
    await click(1180, 710); // Focus.
    await page.screenshot({path: path.join(root, 'artifacts/animal-activity-browser-transform.png')});
    await click(1340, 215); // Animation tab.
    await click(1220, 257); // Stay in place.
    await wait(() => Module.animalEditor.stationary);
    // The actual imported GLB order drives the same clip chooser as the editor.
    const clips = await page.evaluate(() => {
      const bytes = FS.readFile('/assets/animals/horse.glb');
      const length = new DataView(bytes.buffer, bytes.byteOffset).getUint32(12, true);
      return JSON.parse(new TextDecoder().decode(bytes.slice(20, 20 + length))).animations.map(a => a.name);
    });
    let chosen = 0;
    for (const desired of ['Idle', 'Eat']) {
      const target = clips.indexOf(desired); assert(target >= 0);
      while (chosen !== target) {await click(1400, 333); chosen = (chosen + 1) % clips.length;}
      await click(1180, 374);
    }
    await wait(() => Module.animalEditor.clips === 'Idle,Eat');
    await click(1320, 568); await page.keyboard.type('0.75', {delay: 80}); await key('Enter');
    await wait(() => Module.animalEditor.speed === .75);
    const home = await animal();
    await click(1180, 603);
    await wait(() => Module.animalEditor.phase > 6);
    await click(1180, 603);
    const paused = await animal();
    assert.equal(paused.x, home.x); assert.equal(paused.z, home.z);
    await page.waitForTimeout(250); assert.deepEqual(await animal(), paused);
    await page.screenshot({path: path.join(root, 'artifacts/animal-activity-browser-animation.png')});
    await page.keyboard.down('Control'); await key('s'); await page.keyboard.up('Control');
    await wait(() => Module.state.editorSaved && !Module.saving);
    const saved = await page.evaluate(() => FS.readFile('/persist/town/town.scene', {encoding:'utf8'}));
    assert(saved.startsWith('DEATHWARD_TOWN 7 1\n'));
    assert(saved.includes('animal_activity stable-horse 1 0.75 2 Idle Eat\n'));
    await start();
    const reloaded = await animal();
    assert.equal(reloaded.stationary, true); assert.equal(reloaded.clips, 'Idle,Eat');
    assert.equal(reloaded.speed, .75); assert.equal(reloaded.homeX, home.homeX);
    assert.equal(reloaded.homeZ, home.homeZ);
    assert.deepEqual(errors, []);
    console.log('PASS animal position input, undo/redo, stationary sequence, preview pause and browser save/reload');
  } finally {await browser.close();}
})().catch(error => {console.error(error); process.exitCode = 1;});
