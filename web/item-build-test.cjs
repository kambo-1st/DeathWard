const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
  const browser=await chromium.launch({headless:process.env.DEATHWARD_HEADFUL!=='1',executablePath:process.env.DEATHWARD_BROWSER,
    args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
  const page=await browser.newPage({viewport:{width:1280,height:848}});
  const errors=[];page.on('pageerror',e=>errors.push(String(e)));
  page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
  fs.mkdirSync('artifacts',{recursive:true});
  const base=process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8091/';
  try {
    for(const build of ['bank','shrapnel','return','braid']) {
      await page.goto(`${base}?verify&mute&smoke&frames=100000&theme=canyon&scene=build-${build}`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      await page.waitForFunction(()=>Module.state?.frame>3,null,{timeout:90000});
      await page.waitForFunction(build=>{
        const b=Module.build;
        return build==='bank'?b.spikes>0&&b.homing>0:build==='shrapnel'?b.caps>0&&b.friendly>=5:
          build==='return'?b.returning>0:b.children===2;
      },build,{timeout:90000});
      await page.screenshot({path:`artifacts/item-build-${build}.png`});
      if(build==='braid') {
        await page.waitForFunction(()=>Module.state.explosions===3&&Module.build.children===0,null,{timeout:90000});
        assert.equal(await page.evaluate(()=>Module.state.dynamite),2);
      }
      const out=await page.evaluate(()=>({state:Module.state,build:Module.build,gl:Module.ctx.getError()}));
      assert.equal(out.build.items,build==='braid'?1:3);assert.equal(out.state.error,'');assert.equal(out.gl,0);assert.deepEqual(errors,[]);
      console.log(`PASS browser ${build}: live weapon behavior and Original-style rendering`);
    }
  } finally {await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1;});
