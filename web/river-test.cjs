// Actual mission-board clicks, saved comparison choice and animated WebGL water.
const {chromium} = require('playwright');
const assert = require('node:assert/strict');
const path = require('node:path');
(async () => {
  const browser = await chromium.launch({headless: true,
    executablePath: process.env.DEATHWARD_BROWSER || undefined,
    args: ['--no-sandbox', '--enable-gpu', '--use-gl=angle', '--use-angle=gl', '--ignore-gpu-blocklist']});
  try {
    const context = await browser.newContext({viewport: {width: 1280, height: 848}});
    const page = await context.newPage();
    const errors = [];
    page.on('pageerror', error => errors.push(String(error)));
    page.on('console', message => {
      if (/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed|shadow.*unavailable/i.test(message.text()))
        errors.push(message.text());
    });
    const wait = (fn, arg) => page.waitForFunction(fn, arg, {timeout: 60000});
    const frames = async (count = 3) => {
      const n = await page.evaluate(() => Module.state.frame);
      await wait(([before, count]) => Module.state.frame > before + count, [n, count]);
    };
    const key = async code => {
      await page.keyboard.down(code); await frames();
      await page.keyboard.up(code); await frames();
    };
    const riverClick = async () => {
      const box = await page.locator('#canvas').boundingBox();
      await page.mouse.move(box.x + 875 * box.width / 1280, box.y + 497 * box.height / 800);
      await page.mouse.down(); await frames();
      await page.mouse.up(); await frames();
    };
    const start = async () => {
      await wait(() => window.Module?.ready);
      await page.locator('#start').click({noWaitAfter: true});
      await wait(() => Module.state?.frame > 8);
      if (await page.evaluate(() => Module.state.screen === 2)) {
        await key('Enter');
        await wait(() => Module.state.screen === 0);
      }
    };
    const board = async (seed = '1866') => {
      await key('Enter'); await wait(() => Module.state.menu);
      for (let i = 0; i < 12; ++i) await key('Backspace');
      await page.keyboard.type(seed, {delay: 30});
    };
    await page.goto((process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/') + '?verify&mute&theme=canyon');
    await start(); await board();
    assert.equal(await page.evaluate(() => Module.state.canyonRiver), true);
    await riverClick();
    assert.equal(await page.evaluate(() => Module.state.canyonRiver), false);
    await key('Enter');
    await wait(() => Module.state.screen === 1 && Module.state.missionShadows);
    assert.equal(await page.evaluate(() => Module.state.riverActive), false);
    await wait(() => !Module.saving);
    await page.reload(); await start(); await board();
    assert.equal(await page.evaluate(() => Module.state.canyonRiver), false);
    await riverClick(); await key('Enter');
    await wait(() => Module.state.screen === 1 && Module.state.missionShadows && Module.state.riverActive);
    assert.equal(await page.evaluate(() => Module.state.riverKind), 1, 'seed 1866 selects a boundary river');
    assert.equal(await page.evaluate(() => Module.state.roadRoom), 0, 'seed 1866 has a road through the entrance');
    const riverRoom = await page.evaluate(() => Module.state.riverRoom);
    assert.ok(riverRoom >= 0 && riverRoom < 15);
    for (let i = 0; i < riverRoom; ++i) await key('F12');
    await wait(room => Module.state.room === room && Module.state.missionShadows, riverRoom);
    await page.mouse.move(550, 350);
    await page.mouse.down({button: 'right'}); await frames(15);
    await page.mouse.up({button: 'right'}); await frames();
    assert.ok(await page.evaluate(() => Module.state.shots > 0));
    await page.screenshot({path: path.resolve(__dirname, '../artifacts/river-web-canyon.png')});
    await page.mouse.down({button: 'middle'});
    await page.mouse.move(800, 390, {steps: 15});
    await page.mouse.up({button: 'middle'});
    await page.mouse.wheel(0, 250);
    await key('KeyW'); await key('KeyD');
    await key('F12'); await wait(room => Module.state.room === room && Module.state.missionShadows, (riverRoom + 1) % 15);
    assert.equal(await page.evaluate(() => Module.ctx.getError()), 0);
    // A fresh expedition uses the seed to select the other river style with the
    // same saved River On setting; no manual type selector is involved.
    await wait(() => !Module.saving);
    await page.reload(); await start(); await board('42');
    assert.equal(await page.evaluate(() => Module.state.canyonRiver), true);
    await key('Enter');
    await wait(() => Module.state.screen === 1 && Module.state.missionShadows && Module.state.riverActive);
    assert.equal(await page.evaluate(() => Module.state.riverKind), 2, 'seed 42 selects an interior river');
    await page.mouse.move(550, 350);
    await page.mouse.down({button: 'right'}); await frames(15);
    await page.mouse.up({button: 'right'}); await frames();
    assert.ok(await page.evaluate(() => Module.state.shots > 0));
    await page.screenshot({path: path.resolve(__dirname, '../artifacts/river-web-interior.png')});
    await key('KeyW'); await key('KeyD');
    await key('F12'); await wait(() => Module.state.room === 1 && Module.state.missionShadows);
    assert.equal(await page.evaluate(() => Module.ctx.getError()), 0);
    const roadRoom = await page.evaluate(() => Module.state.roadRoom);
    assert.equal(roadRoom, 12, 'seed 42 places its road away from the interior river');
    while (await page.evaluate(() => Module.state.room) !== roadRoom) await key('F12');
    await wait(room => Module.state.room === room && Module.state.missionShadows, roadRoom);
    await page.screenshot({path: path.resolve(__dirname, '../artifacts/road-web-interior.png')});
    await key('KeyW'); await key('KeyD');
    assert.equal(await page.evaluate(() => Module.ctx.getError()), 0);
    assert.deepEqual(errors, []);
    console.log('PASS WebGL rivers and interior roads: seeded boundary/interior selection, mission-board toggle, dry comparison, persistence, shadows, firing, orbit and room changes');
    await context.close();
  } finally {await browser.close();}
})().catch(error => {console.error(error); process.exitCode = 1;});
