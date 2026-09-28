const {chromium} = require('playwright');
const assert = require('node:assert/strict');
const options = {
  headless: process.env.DEATHWARD_HEADFUL !== '1',
  args: ['--no-sandbox', '--enable-gpu', '--use-gl=angle', '--use-angle=gl', '--ignore-gpu-blocklist'],
};
if (process.env.DEATHWARD_BROWSER) options.executablePath = process.env.DEATHWARD_BROWSER;
(async () => {
  const browser = await chromium.launch(options);
  try {
    const page = await browser.newPage({viewport: {width: 1100, height: 735}});
    const errors = [];
    page.on('pageerror', error => errors.push(error.message));
    await page.addInitScript(() => {
      Object.defineProperty(window, 'indexedDB', {get() { throw new Error('Storage blocked for verification'); }});
      const original = WebGL2RenderingContext.prototype.getExtension;
      WebGL2RenderingContext.prototype.getExtension = function(name) {
        return name === 'EXT_color_buffer_float' ? null : original.call(this, name);
      };
    });
    await page.goto((process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/') + '?verify&mute');
    await page.waitForFunction(() => window.Module?.ready, null, {timeout: 60000});
    await page.locator('#start').click({noWaitAfter: true});
    await page.waitForFunction(() => Module.state?.frame > 8, null, {timeout: 60000});
    const result = await page.evaluate(() => ({
      storage: Module.storageReady, state: Module.state, glError: Module.ctx.getError(),
      audioDevice: typeof window.miniaudio !== 'undefined',
      message: document.getElementById('save-status').textContent,
    }));
    assert.equal(result.storage, false);
    assert.equal(result.state.audio, 0);
    assert.equal(result.audioDevice, false);
    assert.equal(result.glError, 0);
    assert.equal(result.state.error, '');
    assert.match(result.message, /unavailable/);
    assert.deepEqual(errors, []);
    console.log('PASS blocked browser storage, skipped audio initialization and 8-bit rendering fallback');
  } finally { await browser.close(); }
})().catch(error => { console.error(error); process.exitCode = 1; });
