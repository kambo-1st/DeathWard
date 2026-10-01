const { chromium } = require('playwright');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');

(async () => {
  const browser = await chromium.launch({
    headless: true, executablePath: process.env.DEATHWARD_BROWSER,
    args: ['--no-sandbox', '--enable-gpu', '--use-gl=angle', '--use-angle=gl', '--ignore-gpu-blocklist']
  });
  const context = await browser.newContext({viewport: {width: 1440, height: 950}});
  const page = await context.newPage();
  const errors = [];
  page.on('pageerror', error => errors.push(String(error)));
  page.on('console', message => {
    if (/ERROR:|INVALID_OPERATION|INVALID_ENUM|shader failed|POST:.*unavailable/i.test(message.text()))
      errors.push(message.text());
  });
  const root = process.env.DEATHWARD_URL || 'http://127.0.0.1:8091/';
  const wait = (fn, argument) => page.waitForFunction(fn, argument, {timeout: 90000});
  const frames = async (count = 3) => {
    const frame = await page.evaluate(() => Module.state.frame);
    await wait(([frame, count]) => Module.state.frame > frame + count, [frame, count]);
  };
  const key = async name => {
    await page.keyboard.down(name); await frames();
    await page.keyboard.up(name); await frames();
  };
  const click = async (x, y) => {
    const box = await page.locator('#canvas').boundingBox();
    await page.mouse.move(box.x + x * box.width / 1440, box.y + y * box.height / 900);
    await page.mouse.down(); await frames(); await page.mouse.up(); await frames();
  };
  const launch = async suffix => {
    await page.goto(root + suffix);
    await wait(() => window.Module?.ready);
    await page.locator('#start').click({noWaitAfter: true});
    await wait(() => Module.state?.frame > 8);
  };
  const saved = name => page.evaluate(name => Module.FS.readFile('/persist/redstone/' + name, {encoding: 'utf8'}), name);
  try {
    await launch('?verify&hub=redstone');
    const original = await saved('town.scene');
    await key('F4'); await wait(() => Module.state.editor);
    await click(1300, 68); await wait(() => Module.cinematic.active);
    assert.equal(await page.evaluate(() => Module.cinematic.dirty), true);
    await click(830, 27); await wait(() => !Module.saving && !Module.cinematic.dirty);
    assert.match(await saved('arrival.cinematic'), /^DEATHWARD_CINEMATIC 1/);
    await click(155 + 6 / 20 * 1230, 705);
    assert.ok(Math.abs(await page.evaluate(() => Module.cinematic.time) - 6) < .05, JSON.stringify(await page.evaluate(() => Module.cinematic)));
    fs.mkdirSync(path.join(__dirname, '../artifacts'), {recursive: true});
    await page.screenshot({path: path.join(__dirname, '../artifacts/cinematic-web-interior.png')});
    await page.setViewportSize({width:1280,height:848});await frames();
    await click(155 + 6 / 20 * 1230,705);
    assert.ok(Math.abs(await page.evaluate(() => Module.cinematic.time) - 6) < .05);
    await page.setViewportSize({width:1440,height:950});await frames();
    await key('Space');
    await wait(() => Module.cinematic.time > 7.2);
    assert.equal(await page.evaluate(() => Module.cinematic.voices), 2);
    await key('Space');
    const paused = await page.evaluate(() => Module.cinematic.time);
    await frames(8); assert.equal(await page.evaluate(() => Module.cinematic.time), paused);
    await click(155 + 12 / 20 * 1230, 770);
    assert.equal(await page.evaluate(() => Module.cinematic.voices), 0);
    assert.ok(await page.evaluate(() => Module.cinematic.storm) > .99);
    await click(1360, 352); // Reduce this weather key from 1 to .9.
    assert.equal(await page.evaluate(() => Module.cinematic.dirty), true);
    await click(830, 27); await wait(() => !Module.saving && !Module.cinematic.dirty);
    const sequence = await saved('arrival.cinematic');
    assert.match(sequence, /weather 12 0\.899/);
    await page.screenshot({path: path.join(__dirname, '../artifacts/cinematic-web-storm.png')});
    await click(1320, 27); await wait(() => !Module.cinematic.active && Module.state.editor);
    assert.equal(await saved('town.scene'), original);
    await key('F4'); await wait(() => !Module.state.editor);
    await launch('?verify&hub=redstone&cinematic');
    await wait(() => Module.cinematic.active);
    assert.equal(await page.evaluate(() => Module.cinematic.dirty), false);
    assert.equal(await saved('arrival.cinematic'), sequence);
    assert.equal(await saved('town.scene'), original);
    assert.equal(await page.evaluate(() => Module.ctx.getError()), 0);
    assert.deepEqual(errors, []);
    console.log('PASS browser cinematic editor: separate screen, carriage camera, playback/audio, scrub, weather editing, IndexedDB reload and unchanged map.');
  } catch (error) {
    console.error(error);
    console.error(await page.evaluate(() => ({canvas: [Module.canvas.width,Module.canvas.height,Module.canvas.clientWidth,Module.canvas.clientHeight],box:Module.canvas.getBoundingClientRect().toJSON(),viewport:Module.ctx?Array.from(Module.ctx.getParameter(Module.ctx.VIEWPORT)):[],state:Module.cinematic})));
    await page.screenshot({path: path.join(__dirname, '../artifacts/cinematic-web-failure.png')}); console.error(errors);throw error;
  } finally { await browser.close(); }
})().catch(error => {console.error(error); process.exitCode = 1;});
