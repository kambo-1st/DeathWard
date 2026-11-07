const { chromium } = require('../../web/node_modules/playwright');
const path = require('path');
const directory = process.argv[2] || 'docs/reports/cliff-formations';
(async () => {
  const browser = await chromium.launch({
    headless: true,
    executablePath: process.env.CHROME_BIN || '/home/kambo/.cache/ms-playwright/chromium-1248/chrome-linux64/chrome',
    args: ['--no-sandbox'],
  });
  try {
    const page = await browser.newPage({ viewport: { width: 3000, height: 2000 }, deviceScaleFactor: 1 });
    await page.goto('file://' + path.resolve(directory, 'index.html'));
    await page.evaluate(async () => {
      await document.fonts.ready;
      await Promise.all([...document.images].map(image => image.decode()));
    });
    await page.addStyleTag({ content: '.wide{overflow:visible!important}main{max-width:none!important;margin:0!important;padding:0!important}' });
    for (const [id, file] of [
      ['wall-sheet', 'comparison.png'], ['full-sheet', 'full-comparison.png'],
      ['annotations', 'annotations.png'], ['massing-sheet', 'massing-comparison.png'],
      ['wire-sheet', 'wire-comparison.png'],
      ['left-join', 'left-join.png'], ['middle-join', 'middle-join.png'],
      ['right-join', 'right-join.png'], ['rear-join', 'rear-join.png'],
    ]) {
      const element = page.locator('#' + id);
      if (!await element.count()) continue;
      await element.evaluate(node => Object.assign(node.style, { position: 'fixed', top: '0px', left: '0px', zIndex: 9999 }));
      await element.screenshot({ path: path.join(directory, file) });
      await element.evaluate(node => Object.assign(node.style, { position: '', top: '', left: '', zIndex: '' }));
    }
    console.log('Exported comparison sheets:', directory);
  } finally {
    await browser.close();
  }
})().catch(error => { console.error(error); process.exitCode = 1; });
