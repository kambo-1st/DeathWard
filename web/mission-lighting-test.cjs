// Verify real WebGL depth textures in generated missions, including 8-bit post fallback.
const {chromium} = require('playwright');
const assert = require('node:assert/strict');
const path = require('node:path');
const root = path.resolve(__dirname, '..');
(async () => {
  const browser = await chromium.launch({headless: true,
    executablePath: process.env.DEATHWARD_BROWSER || undefined,
    args: ['--no-sandbox', '--enable-gpu', '--use-gl=angle', '--use-angle=gl', '--ignore-gpu-blocklist']});
  try {
    for (const [theme, fallback] of [['canyon', false], ['mine', false], ['canyon', true]]) {
      const context = await browser.newContext({viewport: {width: 1280, height: 848}});
      const page = await context.newPage();
      const errors = [];
      page.on('pageerror', e => errors.push(String(e)));
      page.on('console', m => {
        if (/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed|shadow.*unavailable/i.test(m.text()))
          errors.push(m.text());
      });
      if (fallback) await page.addInitScript(() => {
        const original = WebGL2RenderingContext.prototype.getExtension;
        WebGL2RenderingContext.prototype.getExtension = function(name) {
          return name === 'EXT_color_buffer_float' ? null : original.call(this, name);
        };
      });
      const wait = (fn, arg) => page.waitForFunction(fn, arg, {timeout: 60000});
      const key = async code => {
        let frame = await page.evaluate(() => Module.state.frame);
        await page.keyboard.down(code);
        await wait(n => Module.state.frame >= n + 2, frame);
        frame = await page.evaluate(() => Module.state.frame);
        await page.keyboard.up(code);
        await wait(n => Module.state.frame >= n + 2, frame);
      };
      await page.goto((process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/') + `?verify&mute&theme=${theme}`);
      await wait(() => window.Module?.ready);
      await page.locator('#start').click({noWaitAfter: true});
      await wait(() => Module.state?.frame > 8);
      assert.equal(await page.evaluate(() => Module.state.artPoc), false);
      await key('Enter');
      await wait(() => Module.state.menu);
      for (let i = 0; i < 12; ++i) await key('Backspace');
      await page.keyboard.type('1866', {delay: 50});
      await key('Enter');
      await wait(() => Module.state.screen === 1 && Module.state.missionShadows);
      assert.equal(await page.evaluate(() => Module.state.theme), theme === 'canyon' ? 1 : 0);
      const decorations = await page.evaluate(() => Module.state.decorations);
      assert.ok(decorations >= 15 * 6 && decorations <= 15 * 80);
      assert.ok(await page.evaluate(() => Module.state.roomDecorations >= 6));
      if (theme === 'canyon' && !fallback) {
        assert.equal(await page.evaluate(() => Module.state.riverActive), true);
        await page.screenshot({path: path.join(root, 'artifacts/river-web-canyon.png')});
      }
      await key('F2');
      await key('F12');
      await key('F12');
      await wait(() => Module.state.room === 2 && Module.state.missionShadows);
      assert.ok(await page.evaluate(() => Module.state.roomDecorations >= 6));
      await page.screenshot({path: path.join(root, `artifacts/mission-shadow-web-${theme}${fallback ? '-fallback' : ''}.png`)});
      await page.mouse.move(600, 400);
      await page.mouse.down({button: 'middle'});
      await page.mouse.move(850, 440, {steps: 20});
      await page.mouse.up({button: 'middle'});
      await page.mouse.wheel(0, 500);
      await key('KeyW');
      await key('F12');
      await wait(() => Module.state.room === 3 && Module.state.missionShadows);
      assert.ok(await page.evaluate(() => Module.state.roomDecorations >= 6));
      assert.equal(await page.evaluate(() => Module.state.decorations), decorations);
      const state = await page.evaluate(() => ({error: Module.state.error, gl: Module.ctx.getError(),
        shadows: Module.state.missionShadows, art: Module.state.artPoc}));
      if (errors.length || state.gl) console.error({theme, fallback, errors});
      assert.deepEqual(state, {error: '', gl: 0, shadows: true, art: false});
      assert.deepEqual(errors, []);
      console.log(`PASS ${theme}${fallback ? ' / 8-bit fallback' : ''}: ${decorations} decorations, WebGL depth, room changes, orbit, zoom and movement`);
      await context.close();
    }
  } finally {await browser.close();}
})().catch(error => {console.error(error); process.exitCode = 1;});
