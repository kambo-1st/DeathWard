// Real pause-menu input, live instanced vegetation and IndexedDB persistence.
const {chromium} = require('playwright');
const assert = require('node:assert/strict');
const path = require('node:path');
(async () => {
  const browser = await chromium.launch({headless: true,
    executablePath: process.env.DEATHWARD_BROWSER || undefined,
    args: ['--no-sandbox', '--enable-gpu', '--use-gl=angle', '--use-angle=gl', '--ignore-gpu-blocklist']});
  try {
    for (const theme of ['canyon', 'mine']) {
      const context = await browser.newContext({viewport: {width: 1280, height: 848}});
      const page = await context.newPage();
      const errors = [];
      page.on('pageerror', error => errors.push(String(error)));
      page.on('console', message => {
        if (/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed|shadow.*unavailable/i.test(message.text()))
          errors.push(message.text());
      });
      const wait = (fn, arg) => page.waitForFunction(fn, arg, {timeout: 60000});
      const frames = async () => {
        const n = await page.evaluate(() => Module.state.frame);
        await wait(previous => Module.state.frame > previous + 2, n);
      };
      const key = async code => {
        await page.keyboard.down(code); await frames();
        await page.keyboard.up(code); await frames();
      };
      const densityClick = async more => {
        const box = await page.locator('#canvas').boundingBox();
        await page.mouse.move(box.x + (more ? 265 : 178) * box.width / 1280,
          box.y + 719 * box.height / 800);
        await page.mouse.down(); await frames();
        await page.mouse.up(); await frames();
      };
      const groundClick = async () => {
        const box = await page.locator('#canvas').boundingBox();
        await page.mouse.move(box.x + 1075 * box.width / 1280, box.y + 650 * box.height / 800);
        await page.mouse.down(); await frames();
        await page.mouse.up(); await frames();
      };
      await page.goto((process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/') + `?verify&mute&theme=${theme}`);
      await wait(() => window.Module?.ready);
      await page.locator('#start').click({noWaitAfter: true});
      await wait(() => Module.state?.frame > 8);
      assert.equal(await page.evaluate(() => Module.state.vegetationDensity), 100);
      await key('Enter');
      await wait(() => Module.state.menu);
      for (let i = 0; i < 12; ++i) await key('Backspace');
      await page.keyboard.type('1866');
      await key('Enter');
      await wait(() => Module.state.screen === 1 && Module.state.missionShadows);
      const baseline = await page.evaluate(() => Module.state.vegetationCount);
      await key('Escape');
      await wait(() => Module.state.paused);
      assert.equal(await page.evaluate(() => Module.state.groundDetail), true);
      await groundClick();
      assert.equal(await page.evaluate(() => Module.state.groundDetail), false);
      await groundClick();
      assert.equal(await page.evaluate(() => Module.state.groundDetail), true);
      for (let i = 0; i < 5; ++i) await densityClick(false);
      assert.equal(await page.evaluate(() => Module.state.vegetationDensity), 0);
      assert.equal(await page.evaluate(() => Module.state.vegetationCount), 0);
      for (let i = 0; i < 4; ++i) await densityClick(true);
      assert.equal(await page.evaluate(() => Module.state.vegetationCount), baseline);
      for (let i = 0; i < 5; ++i) await densityClick(true);
      assert.equal(await page.evaluate(() => Module.state.vegetationDensity), 200);
      assert.ok(await page.evaluate(n => Module.state.vegetationCount > n, baseline));
      assert.equal(await page.evaluate(() => Module.state.shots), 0);
      assert.equal(await page.evaluate(() => Module.state.paused), true);
      await page.screenshot({path: path.resolve(__dirname, `../artifacts/vegetation-web-${theme}.png`)});
      await densityClick(false);
      await groundClick();
      assert.equal(await page.evaluate(() => Module.state.groundDetail), false);
      await wait(() => !Module.saving && FS.readFile('/persist/visual.cfg', {encoding: 'utf8'}).includes('175'));
      assert.equal(await page.evaluate(() => Module.ctx.getError()), 0);
      await page.reload();
      await wait(() => window.Module?.ready);
      await page.locator('#start').click({noWaitAfter: true});
      await wait(() => Module.state?.frame > 8);
      assert.equal(await page.evaluate(() => Module.state.vegetationDensity), 175);
      assert.equal(await page.evaluate(() => Module.state.groundDetail), false);
      assert.deepEqual(errors, []);
      console.log(`PASS ${theme}: vegetation density, ground detail toggle, live shadows and saved preferences`);
      await context.close();
    }
  } finally {await browser.close();}
})().catch(error => {console.error(error); process.exitCode = 1;});
