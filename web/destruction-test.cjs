// Real WASM simulation: placed charges, fuse timing, persistent cache state and path-to-loot.
const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
  const browser=await chromium.launch({headless:process.env.DEATHWARD_HEADFUL!=='1',
    executablePath:process.env.DEATHWARD_BROWSER,
    args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
  const page=await browser.newPage({viewport:{width:1280,height:848}});
  const errors=[];
  page.on('pageerror',e=>errors.push(String(e)));
  page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
  const base=process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8091/';
  fs.mkdirSync('artifacts',{recursive:true});
  try {
    for(const theme of ['canyon','mine']) {
      await page.goto(`${base}?verify&mute&smoke&frames=100000&scene=demolition-run&theme=${theme}`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      await page.waitForFunction(()=>Module.state?.frame>3,null,{timeout:90000});
      const initial=await page.evaluate(()=>({state:Module.state,prop:Module.demolition}));
      assert.equal(initial.prop.props,8);assert.equal(initial.prop.health,2);
      assert.equal(initial.state.dynamite,3);
      await page.screenshot({path:`artifacts/demolition-${theme}-closed.png`});
      await page.waitForFunction(()=>Module.demolition?.health===1,null,{timeout:90000});
      assert.equal(await page.evaluate(()=>Module.state.dynamite),2);
      await page.screenshot({path:`artifacts/demolition-${theme}-cracked.png`});
      await page.waitForFunction(()=>Module.demolition?.health===0,null,{timeout:90000});
      assert.equal(await page.evaluate(()=>Module.state.dynamite),1);
      await page.waitForFunction(()=>Module.state.frame>=420,null,{timeout:90000});
      const final=await page.evaluate(()=>({state:Module.state,prop:Module.demolition,gl:Module.ctx.getError()}));
      assert.equal(final.prop.keys,initial.prop.keys+1);
      assert.ok(final.state.money>=initial.state.money+8);
      assert.equal(final.prop.health,0);assert.equal(final.state.error,'');assert.equal(final.gl,0);
      assert.deepEqual(errors,[]);
      await page.screenshot({path:`artifacts/demolition-${theme}-open.png`});
      console.log(`PASS ${theme}: two placed sticks open cache; path collects key and coins; no GL/JS errors`);
    }
  } finally {await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1;});
