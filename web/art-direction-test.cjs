// Exercise the opt-in look and actual F6 input in WebGL, without writing scene files.
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
  const key = async code => {
    let frame = await page.evaluate(() => Module.state.frame);
    await page.keyboard.down(code);
    await wait(start => Module.state.frame >= start + 2, frame);
    frame = await page.evaluate(() => Module.state.frame);
    await page.keyboard.up(code);
    await wait(start => Module.state.frame >= start + 2, frame);
  };
  const start = async suffix => {
    await page.goto((process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/') + '?verify&hub=redstone' + suffix);
    await wait(() => window.Module?.ready);
    await page.locator('#start').click({noWaitAfter: true});
    await wait(() => Module.state?.frame > 8);
    assert.equal(await page.evaluate(() => Module.state.error), '');
  };
  const scene = () => page.evaluate(() => FS.readFile('/persist/redstone/town.scene', {encoding: 'utf8'}));
  try {
    await start('&art=poc');
    assert.equal(await page.evaluate(() => Module.state.artPoc), true);
    const original = await scene();
    await page.screenshot({path: path.join(root, 'artifacts/art-poc-browser-on.png')});
    await key('F6'); await wait(() => !Module.state.artPoc);
    await page.screenshot({path: path.join(root, 'artifacts/art-poc-browser-off.png')});
    await key('F6'); await wait(() => Module.state.artPoc);
    await key('F4'); await wait(() => Module.state.editor);
    assert.equal(await page.evaluate(() => Module.state.artPoc), true);
    const time = await page.evaluate(() => Module.motion.previewTime);
    await key('F6'); await wait(() => !Module.state.artPoc);
    await key('F6'); await wait(() => Module.state.artPoc);
    assert.equal(await page.evaluate(() => Module.motion.previewTime), time);
    await page.screenshot({path: path.join(root, 'artifacts/art-poc-browser-editor.png')});
    // No unsaved-scene prompt: visual comparison must not dirty the editor.
    await key('Escape'); await wait(() => !Module.state.editor);
    assert.equal(await scene(), original);
    // Reload without the option restores the original look; comparison is not persisted.
    await start('');
    assert.equal(await page.evaluate(() => Module.state.artPoc), false);
    assert.equal(await scene(), original);
    assert.deepEqual(errors, []);
    console.log('PASS WebGL shaders, URL opt-in, F6 in hub/editor, unchanged scene and default-off reload');
  } catch (error) {
    console.error(errors);
    await page.screenshot({path: path.join(root, 'artifacts/art-poc-browser-failure.png')}).catch(() => {});
    throw error;
  } finally {await browser.close();}
})().catch(error => {console.error(error); process.exitCode = 1;});
