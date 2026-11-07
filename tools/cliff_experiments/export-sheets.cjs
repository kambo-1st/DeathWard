// Native screenshot layout only; no synthesized images or painted geometry.
const { chromium } = require('../../web/node_modules/playwright');
const path = require('path');
(async () => {
  const browser = await chromium.launch({headless:true,executablePath:process.env.CHROME_BIN || '/home/kambo/.cache/ms-playwright/chromium-1248/chrome-linux64/chrome',args:['--no-sandbox']});
  const page=await browser.newPage({viewport:{width:3000,height:2100},deviceScaleFactor:1});
  await page.goto('file://'+path.resolve('docs/reports/cliff-alternatives/index.html'));
  await page.evaluate(async()=>{await document.fonts.ready;await Promise.all([...document.images].map(i=>i.decode()));});
  await page.addStyleTag({content:'.wide{overflow:visible!important}main{max-width:none!important;margin:0!important;padding:0!important}'});
  for(const [id,file] of [['full-sheet','comparison.png'],['wall-sheet','wall-comparison.png'],['wire-sheet','wireframes.png']]) {
    const el=page.locator('#'+id);
    await el.evaluate(e=>Object.assign(e.style,{position:'fixed',left:'0px',top:'0px',zIndex:'9999'}));
    await el.screenshot({path:path.resolve('docs/reports/cliff-alternatives',file)});
    await el.evaluate(e=>Object.assign(e.style,{position:'',left:'',top:'',zIndex:''}));
  }
  const broken=await page.evaluate(()=>[...document.images].filter(i=>!i.complete||!i.naturalWidth).length);
  if(broken)throw Error('Broken report images: '+broken);
  await browser.close();
})();
