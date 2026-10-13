// Compare visual presets through actual URL, keyboard and pause-menu input.
const {chromium} = require('playwright');
const assert = require('node:assert/strict');
const path = require('node:path');
const root = path.resolve(__dirname, '..');
const styles = ['original', 'cel', 'comic', 'painted', 'poster', 'noir', 'retro',
  'woodcut', 'watercolor', 'pencil', 'ink', 'diorama', 'cinema', 'crt', 'spectral', 'sumi'];
const cycle = start => Array.from({length: styles.length}, (_, i) => (start + i + 1) % styles.length);
(async () => {
  const browser = await chromium.launch({headless: true,
    executablePath: process.env.DEATHWARD_BROWSER || undefined,
    args: ['--no-sandbox', '--enable-gpu', '--use-gl=angle', '--use-angle=gl', '--ignore-gpu-blocklist']});
  const page = await browser.newPage({viewport: {width: 1440, height: 950}});
  const errors = [];
  try {
    page.on('pageerror', e => errors.push(String(e)));
    page.on('console', m => {if (/ERROR:|INVALID_OPERATION|shader failed/i.test(m.text())) errors.push(m.text());});
    const wait = (fn, arg) => page.waitForFunction(fn, arg, {timeout: 60000});
    const frames = async () => {
      const start = await page.evaluate(() => Module.state.frame);
      await wait(start => Module.state.frame >= start + 3, start);
    };
    const key = async code => {
      await page.keyboard.down(code); await frames();
      await page.keyboard.up(code); await frames();
    };
    const launch = async (suffix, hub = 'redstone') => {
      await page.goto((process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/') + '?verify&mute&hub=' + hub + suffix);
      await wait(() => window.Module?.ready);
      await page.locator('#start').click({noWaitAfter: true});
      await wait(() => Module.state?.frame > 8 || document.querySelector('#problem')?.textContent);
      assert.equal(await page.locator('#problem').textContent(), '');
      assert.equal(await page.evaluate(() => Module.state.error), '');
    };
    const styleClick = async () => {
      const box = await page.locator('#canvas').boundingBox();
      await page.mouse.move(box.x + 720 * box.width / 1280, box.y + 56 * box.height / 800);
      await page.mouse.down(); await frames();
      await page.mouse.up(); await frames();
    };
    const scene = () => page.evaluate(() => FS.readFile('/persist/redstone/town.scene', {encoding: 'utf8'}));
    await launch('&cel-shading');
    assert.equal(await page.evaluate(() => Module.state.celShading), true);
    assert.equal(await page.evaluate(() => Module.state.artPoc), false);
    const original = await scene();
    await page.screenshot({path: path.join(root, 'artifacts/cel-browser-on.png')});
    for (const style of cycle(1)) {
      await key('F6'); await wait(style => Module.state.visualStyle === style, style);
      if (style >= 2)
        await page.screenshot({path: path.join(root, `artifacts/style-browser-${styles[style]}.png`)});
    }
    await key('F4'); await wait(() => Module.state.editor);
    for (const style of cycle(1)) {
      await key('F6'); await wait(style => Module.state.visualStyle === style, style);
    }
    await page.screenshot({path: path.join(root, 'artifacts/cel-browser-editor.png')});
    await key('Escape'); await wait(() => !Module.state.editor);
    await key('Escape'); await wait(() => Module.state.paused);
    await styleClick(); await wait(() => Module.state.visualStyle === 2);
    await styleClick(); await wait(() => Module.state.visualStyle === 3);
    assert.equal(await page.evaluate(() => Module.state.paused), true);
    await page.screenshot({path: path.join(root, 'artifacts/style-browser-pause.png')});
    assert.equal(await scene(), original);
    assert.equal(await page.evaluate(() => Module.ctx.getError()), 0);
    await launch('');
    assert.equal(await page.evaluate(() => Module.state.visualStyle), 0);
    assert.equal(await scene(), original);
    // Check a direct style launch before starting a mission: reloading an
    // active expedition intentionally opens its interrupted-run summary.
    await launch('&style=okami');
    assert.equal(await page.evaluate(() => Module.state.visualStyle), 15);
    await key('F6');
    await wait(() => Module.state.visualStyle === 0);
    await launch('&style=painted', 'town');
    assert.equal(await page.evaluate(() => Module.state.visualStyle), 3);
    await key('Enter'); await wait(() => Module.state.menu);
    for (let i = 0; i < 12; ++i) await key('Backspace');
    await page.keyboard.type('1866');
    await key('Enter'); await wait(() => Module.state.screen === 1 && Module.state.missionShadows);
    await key('Escape'); await wait(() => Module.state.paused);
    const shots = await page.evaluate(() => Module.state.shots);
    for (const style of cycle(3)) {
      await styleClick(); await wait(style => Module.state.visualStyle === style, style);
    }
    assert.equal(await page.evaluate(() => Module.state.paused), true);
    assert.equal(await page.evaluate(() => Module.state.shots), shots);
    await key('Escape'); await wait(() => !Module.state.paused);
    await key('F6');
    assert.equal(await page.evaluate(() => Module.state.visualStyle), 3, 'Mission F6 remains a cheat');
    assert.equal(await page.evaluate(() => Module.ctx.getError()), 0);
    assert.deepEqual(errors, []);
    console.log('PASS all 16 WebGL styles, CLI aliases, hub/editor F6, hub/mission Pause selector, unchanged map and default-off reload');
  } catch (error) {
    console.error(errors);
    console.error(await page.evaluate(() => ({state: window.Module?.state,
      status: document.querySelector('#status')?.textContent})).catch(() => ({})));
    await page.screenshot({path: path.join(root, 'artifacts/cel-browser-failure.png')}).catch(() => {});
    throw error;
  } finally { await browser.close(); }
})().catch(error => {console.error(error); process.exitCode = 1;});
