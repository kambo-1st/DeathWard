const {chromium}=require('../../web/node_modules/playwright');
const path=require('path');
(async()=>{
 const browser=await chromium.launch({headless:true,executablePath:process.env.CHROME_BIN||'/home/kambo/.cache/ms-playwright/chromium-1248/chrome-linux64/chrome',args:['--no-sandbox']});
 const page=await browser.newPage({viewport:{width:2600,height:1100},deviceScaleFactor:1});
 await page.goto('file://'+path.resolve('docs/reports/cliff-a-refinement/index.html'));
 await page.evaluate(async()=>{await document.fonts.ready;await Promise.all([...document.images].map(i=>i.decode()));});
 await page.addStyleTag({content:'.wide{overflow:visible!important}main{max-width:none!important;margin:0!important;padding:0!important}'});
 const el=page.locator('#refinement-sheet');
 await el.evaluate(e=>Object.assign(e.style,{position:'fixed',left:'0px',top:'0px',zIndex:9999}));
 await el.screenshot({path:'docs/reports/cliff-a-refinement/comparison.png'});
 await browser.close();
})();
