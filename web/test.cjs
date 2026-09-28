const {chromium} = require('playwright');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');
const root = path.resolve(__dirname, '..');
const artifacts = path.join(root, 'artifacts');
fs.mkdirSync(artifacts, {recursive: true});
const base = process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/';
const messages = [], failures = [];
const options = {
  headless: process.env.DEATHWARD_HEADFUL !== '1',
  args: ['--no-sandbox', '--enable-gpu', '--use-gl=angle', '--use-angle=gl', '--ignore-gpu-blocklist'],
};
if (process.env.DEATHWARD_BROWSER) options.executablePath = process.env.DEATHWARD_BROWSER;

(async () => {
  const browser = await chromium.launch(options);
  const context = await browser.newContext({viewport: {width: 1280, height: 848}});
  const page = await context.newPage();
  page.setDefaultTimeout(45000);
  page.on('console', message => {
    const text = message.text();
    if (messages.length < 10000) messages.push(`${message.type()}: ${text}`);
    if (/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed|using direct world rendering/i.test(text))
      failures.push(text);
  });
  page.on('pageerror', error => failures.push(error.stack || error.message));
  const state = () => page.evaluate(() => Module.state);
  const wait = (test, arg) => page.waitForFunction(test, arg, {timeout: 60000});
  const key = async code => {
    // Keep transitions across rendered frames, including expensive scene loads.
    let frame = (await state()).frame;
    await page.keyboard.down(code);
    await wait(start => Module.state.frame >= start + 2, frame);
    frame = (await state()).frame;
    await page.keyboard.up(code);
    await wait(start => Module.state.frame >= start + 2, frame);
  };
  const click = async (x, y) => {
    const box = await page.locator('#canvas').boundingBox();
    await page.mouse.click(box.x + x * box.width / 1280, box.y + y * box.height / 800, {delay: 100});
  };
  const start = async url => {
    await page.goto(url);
    await wait(() => window.Module && Module.ready);
    await page.locator('#start').click({noWaitAfter: true});
    await wait(() => Module.state?.frame > 3 || document.querySelector('#problem').textContent);
    assert.equal(await page.locator('#problem').textContent(), '');
    assert.equal((await state()).error, '');
  };
  try {
    await start(base + '?verify');
    assert.equal((await state()).hub, 0);
    assert.equal((await state()).audio, 2);
    assert.equal((await state()).zoom, 160);
    await page.evaluate(() => {
      Module.audioProbe = {frames: 0, peak: 0};
      const device = miniaudio.devices.find(Boolean);
      const original = device.scriptNode.onaudioprocess;
      device.scriptNode.onaudioprocess = event => {
        original(event);
        const samples = event.outputBuffer.getChannelData(0);
        for (const sample of samples) Module.audioProbe.peak = Math.max(Module.audioProbe.peak, Math.abs(sample));
        Module.audioProbe.frames += samples.length;
      };
    });
    await wait(() => Module.audioProbe.frames > 4096 && Module.audioProbe.peak > .0001);
    await page.screenshot({path: path.join(artifacts, 'web-town.png')});
    const before = await state();
    await page.keyboard.down('w'); await page.waitForTimeout(700); await page.keyboard.up('w');
    await wait(s => Math.hypot(Module.state.x - s.x, Module.state.z - s.z) > .5, before);
    await page.mouse.move(640, 450);
    await page.mouse.wheel(0, -200);
    await wait(() => Module.state.zoom > 160);
    await page.setViewportSize({width: 1100, height: 735});
    await wait(() => Module.canvas.width === Math.round(Module.canvas.clientWidth) &&
                         Module.canvas.height === Math.round(Module.canvas.clientHeight));
    await page.screenshot({path: path.join(artifacts, 'web-resized.png')});
    await page.setViewportSize({width: 1280, height: 848});
    // Dispatch the browser focus event directly so this also runs on headless
    // hosts where tab visibility is intentionally overridden by automation.
    await page.evaluate(() => window.dispatchEvent(new Event('blur')));
    await wait(() => Module.state.paused);
    await key('Escape');
    await wait(() => !Module.state.paused);
    console.log('PASS town rendering, WebAudio initialization, movement and wheel zoom');
    await key('Escape');
    assert.equal((await state()).paused, true);
    await click(230, 494);
    await wait(() => Math.abs(Module.state.music - .3) < .001 && !Module.saving);
    await page.screenshot({path: path.join(artifacts, 'web-audio-controls.png')});
    await key('Escape');
    await click(1050, 734);
    await wait(() => Module.state.hub === 1 && Module.state.frame > 10);
    await page.waitForTimeout(1200);
    await page.screenshot({path: path.join(artifacts, 'web-frontier.png')});
    console.log('PASS music controls and direct Frontier travel');
    await key('Enter');
    await wait(() => Module.state.menu);
    for (let i = 0; i < 12; ++i) await key('Backspace');
    await page.keyboard.type('1866', {delay: 100});
    await key('Enter');
    await wait(() => Module.state.screen === 1 && Module.state.room === 0);
    assert.equal((await state()).theme, 1);
    await key('F2'); // Invulnerability while checking pickups and combat.
    await page.mouse.move(640, 450);
    await page.mouse.wheel(0, 800);
    await wait(() => Module.state.zoom < 120 && Module.state.coinValue > 0);
    await page.waitForTimeout(700);
    const coin = await state();
    await page.screenshot({path: path.join(artifacts, 'web-money-before.png')});
    await click(coin.coinX, coin.coinY);
    await wait(value => Module.state.money >= value, coin.money + coin.coinValue);
    const collectedMoney = (await state()).money;
    assert.equal((await state()).shots, 0);
    await wait(() => !Module.saving);
    await page.screenshot({path: path.join(artifacts, 'web-money.png')});
    console.log('PASS seeded ground money, click pickup and immediate checkpoint');
    await key('F12');
    await wait(() => Module.state.room === 1);
    await page.mouse.move(650, 445);
    await page.mouse.down({button: 'right'}); await page.waitForTimeout(750);
    await page.mouse.up({button: 'right'});
    await wait(() => Module.state.shots > 0);
    await page.mouse.move(600, 400);
    await page.mouse.down({button: 'middle'});
    await page.mouse.move(740, 450, {steps: 12});
    await page.mouse.up({button: 'middle'});
    await page.screenshot({path: path.join(artifacts, 'web-canyon.png')});
    await key('F7');
    await wait(() => Module.state.room === 14 && Module.state.enemies > 0);
    await key('F8');
    await wait(() => Module.state.screen === 2 && Module.state.history === 1 && !Module.saving);
    console.log('PASS canyon launch, firing, camera orbit, final encounter and victory');
    await start(base + '?verify&theme=mine');
    assert.equal((await state()).history, 1);
    assert((await state()).money >= collectedMoney, 'collected money survives resolution and browser reload');
    assert(Math.abs((await state()).music - .3) < .001);
    console.log('PASS campaign and music volume survive a browser reload');
    await key('F4');
    await wait(() => Module.state.editor);
    const originalScene = await page.evaluate(() => Module.FS.readFile('/persist/town/town.scene', {encoding: 'utf8'}));
    const editorClick = (x, y) => click(x * 1280 / 1440, y * 800 / 900);
    await editorClick(110, 160);
    await page.keyboard.type('Barrel', {delay: 80});
    await editorClick(110, 231);
    await editorClick(1270, 285); // Set this prop's height through the position inspector.
    await page.keyboard.type('2', {delay: 80});
    await key('Enter');
    await page.keyboard.down('Control'); await key('s'); await page.keyboard.up('Control');
    await wait(() => Module.state.editorSaved && !Module.saving);
    const savedScene = await page.evaluate(() => Module.FS.readFile('/persist/town/town.scene', {encoding: 'utf8'}));
    assert(savedScene !== originalScene, 'editor input changes and saves the selected prop');
    await page.screenshot({path: path.join(artifacts, 'web-editor.png')});
    await key('Escape');
    await wait(() => !Module.state.editor);
    console.log('PASS browser town editor opens and returns to the hub');
    await key('Enter');
    await wait(() => Module.state.menu);
    await key('Enter');
    await wait(() => Module.state.screen === 1 && Module.state.theme === 0);
    await key('F2');
    await key('F12');
    await page.screenshot({path: path.join(artifacts, 'web-mine.png')});
    await wait(() => !Module.saving);
    await start(base + '?verify');
    assert.equal((await state()).screen, 2);
    assert.equal((await state()).history, 2);
    assert.equal(await page.evaluate(() => Module.FS.readFile('/persist/town/town.scene', {encoding: 'utf8'})), savedScene);
    console.log('PASS mine mission and interrupted-run recovery after reload');
    console.log('PASS editor scene changes persist after reloading');
    assert.deepEqual(failures, []);
    console.log('PASS no JavaScript exceptions, shader failures or WebGL errors');
  } finally {
    console.log('Last state:', await state().catch(() => null));
    await page.screenshot({path: path.join(artifacts, 'web-last-frame.png')}).catch(() => {});
    fs.writeFileSync(path.join(artifacts, 'web-browser-console.log'), messages.join('\n'));
    fs.writeFileSync(path.join(artifacts, 'web-browser-errors.log'), failures.join('\n'));
    await browser.close();
  }
})().catch(error => { console.error(error); process.exitCode = 1; });
