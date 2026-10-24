const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const browser=await chromium.launch({headless:process.env.DEATHWARD_HEADFUL!=='1',executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1440,height:948}}),errors=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 fs.mkdirSync('artifacts',{recursive:true});
 try {
  for(const scene of ['ridgeback','ridgeback-late','ridgeback-fight','profile-quarry','profile-works','profile-storm']) {
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8091/'}?verify&mute&smoke&frames=100000&theme=canyon&scene=${scene}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(()=>Module.guardian&&Module.state.frame>3,null,{timeout:90000});
   if(scene==='ridgeback-fight') {
    await page.waitForFunction(()=>Module.guardian.clear,null,{timeout:180000});
    const state=await page.evaluate(()=>({g:Module.guardian,s:Module.state}));
    assert.ok(state.g.playerHp>0);assert.equal(state.s.explosions,0);assert.equal(state.s.dynamite,1);
    assert.ok(state.g.time<120);console.log('PASS browser Ridgeback defeated with starting revolver, no bombs or invulnerability',state.g);
   } else if(scene.startsWith('ridgeback')) {
    await page.waitForFunction(()=>Module.guardian.state===1,null,{timeout:90000});
    const g=await page.evaluate(()=>Module.guardian);assert.equal(g.kind,2);assert.equal(g.phase,scene==='ridgeback-late'?1:0);
    assert.equal(g.band,scene==='ridgeback-late'?3:0);
    console.log(`PASS browser ${scene}: live committed windup and correct floor/phase`);
   } else {
    await page.waitForFunction(()=>Module.state.frame>=100,null,{timeout:90000});
    const band=scene==='profile-quarry'?1:scene==='profile-works'?2:3;
    assert.equal(await page.evaluate(()=>Module.guardian.band),band);
    console.log(`PASS browser ${scene}: band ${band}`);
   }
   await page.screenshot({path:`artifacts/m5-${scene}-web.png`});
   assert.equal(await page.evaluate(()=>Module.state.error),'');assert.equal(await page.evaluate(()=>Module.ctx.getError()),0);assert.deepEqual(errors,[]);
  }
 } finally {await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1;});
