// Real browser travel, mission return and independent editing for the third hub.
const {chromium} = require('playwright');
const assert = require('node:assert/strict');
const fs = require('node:fs');
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
  const state = () => page.evaluate(() => Module.state);
  const key = async code => {
    let frame = (await state()).frame;
    await page.keyboard.down(code);
    await wait(start => Module.state.frame >= start + 2, frame);
    frame = (await state()).frame;
    await page.keyboard.up(code);
    await wait(start => Module.state.frame >= start + 2, frame);
  };
  const click = async (x, y) => {
    const box = await page.locator('#canvas').boundingBox();
    await page.mouse.click(box.x + x * box.width / 1280, box.y + y * box.height / 800, {delay: 130});
  };
  const start = async () => {
    await page.goto((process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/') + '?verify&hub=redstone');
    await wait(() => window.Module?.ready);
    assert.equal(await page.locator('#start').textContent(), 'Enter Redstone Canyon');
    await page.locator('#start').click({noWaitAfter: true});
    await wait(() => Module.state?.frame > 8);
    assert.equal((await state()).hub, 2);
    assert.equal((await state()).error, '');
  };
  try {
    await start();
    assert.equal(await page.evaluate(() => Module.motion.vehicles), 4);
    await wait(() => Module.motion.trainDistance > 1 && Module.particles.steam > 0);
    const otherScenes = await page.evaluate(() => ['town', 'frontier'].map(hub =>
      FS.readFile('/persist/' + hub + '/town.scene', {encoding: 'utf8'})));
    await key('Escape');
    const frozen = await page.evaluate(() => Module.motion.trainDistance);
    await page.waitForTimeout(250);
    assert.equal(await page.evaluate(() => Module.motion.trainDistance), frozen);
    await key('Escape');
    await click(1050, 680); await wait(() => Module.state.hub === 1);
    await click(1050, 680); await wait(() => Module.state.hub === 2);
    await click(1050, 734); await wait(() => Module.state.hub === 0);
    await click(1050, 680); await wait(() => Module.state.hub === 2);
    await page.screenshot({path: path.join(root, 'artifacts/web-redstone.png')});
    console.log('PASS canyon URL, steam, train pause and direct travel between all three hubs');
    await key('Enter'); await wait(() => Module.state.menu);
    await key('Enter'); await wait(() => Module.state.screen === 1);
    await key('Escape'); await wait(() => Module.state.paused);
    await key('t'); await wait(() => Module.state.screen === 2);
    await key('Enter'); await wait(() => Module.state.screen === 0 && Module.state.hub === 2);
    console.log('PASS canyon mission-board approach, launch, retreat and return to Redstone');
    await key('F4'); await wait(() => Module.state.editor);
    await page.keyboard.down('Control'); await key('s'); await page.keyboard.up('Control');
    await wait(() => Module.state.editorSaved && !Module.saving);
    const saved = await page.evaluate(() => FS.readFile('/persist/redstone/town.scene', {encoding: 'utf8'}));
    const rail = saved.split('\n').find(line => line.startsWith('path redstone-rail ')).split(' ');
    assert.equal(Number(rail[2]), 3);
    assert(Math.abs(Number(rail[3]) - .8) < .0001);
    assert.equal(Number(rail[4]), 0);
    assert.equal(await page.evaluate(() => FS.readFile('/persist/redstone/town.nav')[7]), '3'.charCodeAt(0));
    assert.deepEqual(await page.evaluate(() => ['town', 'frontier'].map(hub =>
      FS.readFile('/persist/' + hub + '/town.scene', {encoding: 'utf8'}))), otherScenes);
    await key('Escape'); await wait(() => !Module.state.editor);
    await start();
    assert.equal(await page.evaluate(() => FS.readFile('/persist/redstone/town.scene', {encoding: 'utf8'})), saved);
    assert.equal(await page.evaluate(() => Module.motion.vehicles), 4);
    assert.deepEqual(errors, []);
    console.log('PASS independent canyon editor save, navigation rebuild, reload and clean WebGL rendering');
  } finally {
    fs.writeFileSync(path.join(root, 'artifacts/redstone-browser-errors.log'), errors.join('\n'));
    await page.screenshot({path: path.join(root, 'artifacts/web-redstone-last.png')}).catch(() => {});
    await browser.close();
  }
})().catch(e => {console.error(e); process.exitCode = 1;});
