// Focused browser coverage for variable-size special-room indices and CLI presets.
const {chromium} = require('playwright');
const assert = require('node:assert/strict');
(async () => {
  const browser = await chromium.launch({
    headless: process.env.DEATHWARD_HEADFUL !== '1',
    executablePath: process.env.DEATHWARD_BROWSER,
    args: ['--no-sandbox', '--enable-gpu', '--use-gl=angle', '--use-angle=gl', '--ignore-gpu-blocklist'],
  });
  const page = await browser.newPage();
  const errors = [];
  page.on('pageerror', error => errors.push(String(error)));
  page.on('console', message => {
    if (/ERROR:|INVALID_OPERATION|INVALID_ENUM|shader failed/i.test(message.text())) errors.push(message.text());
  });
  const base = process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/';
  try {
    for (const [pacing, rooms] of [['growing', 9], ['classic', 15]]) {
      for (const scene of ['power', 'boss']) {
        await page.goto(`${base}?verify&mute&smoke&frames=100000&theme=canyon&scene=${scene}&pacing=${pacing}`);
        await page.waitForFunction(() => window.Module?.ready, null, {timeout: 90000});
        await page.locator('#start').click({noWaitAfter: true});
        await page.waitForFunction(() => Module.state?.frame > 5, null, {timeout: 90000});
        const result = await page.evaluate(() => ({
          state: Module.state, expedition: Module.expedition, gl: Module.ctx.getError(),
        }));
        assert.equal(result.expedition.rooms, rooms);
        assert.ok(result.expedition.floors >= 4 && result.expedition.floors <= 8);
        assert.equal(result.state.room, rooms - (scene === 'power' ? 2 : 1));
        assert.equal(result.state.error, '');
        assert.equal(result.gl, 0);
        assert.deepEqual(errors, []);
        console.log(`PASS browser ${pacing}: ${rooms} rooms, ${scene} index ${result.state.room}, rendered without GL errors`);
      }
    }
  } finally { await browser.close(); }
})().catch(error => { console.error(error); process.exitCode = 1; });
