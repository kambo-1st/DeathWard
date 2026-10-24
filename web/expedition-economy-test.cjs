const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const browser=await chromium.launch({headless:process.env.DEATHWARD_HEADFUL!=='1',executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1440,height:948}}),errors=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const click=async(x,y)=>{
  const box=await page.locator('#canvas').boundingBox();
  await page.mouse.move(box.x+x*box.width/1280,box.y+y*box.height/800);
  let frame=await page.evaluate(()=>Module.state.frame);await page.mouse.down();
  await page.waitForFunction(start=>Module.state.frame>=start+2,frame);
  frame=await page.evaluate(()=>Module.state.frame);await page.mouse.up();
  await page.waitForFunction(start=>Module.state.frame>=start+2,frame);
 };
 fs.mkdirSync('artifacts',{recursive:true});
 try {
  for(const scene of (process.env.DEATHWARD_ECONOMY_ONLY?['service-exchange','service-surgeon','service-bargain','boss-reward']:['foreman','foreman-late','foreman-fight','marshal','marshal-late','marshal-fight','service-exchange','service-surgeon','service-bargain','boss-reward'])) {
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8091/'}?verify&mute&smoke&frames=100000&theme=canyon&scene=${scene}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(()=>Module.economy&&Module.state.frame>3,null,{timeout:90000});
   if(scene.endsWith('-fight')) {
    await page.waitForFunction(()=>Module.guardian.clear,null,{timeout:180000});
    const g=await page.evaluate(()=>Module.guardian),e=await page.evaluate(()=>Module.economy);
    assert.ok(g.playerHp>0&&g.time<120);assert.equal(e.dynamite,1);assert.equal(e.itemCount,0);
    console.log(`PASS browser ${scene}: starting revolver, no player bombs/items/god mode`,g);
   } else if(scene.startsWith('foreman')||scene.startsWith('marshal')) {
    await page.waitForFunction(()=>Module.guardian.state===1,null,{timeout:90000});
    const g=await page.evaluate(()=>Module.guardian);
    assert.equal(g.kind,scene.startsWith('foreman')?3:4);assert.equal(g.phase,scene.endsWith('-late')?1:0);assert.ok(g.hp>0);
   } else if(scene.startsWith('service-')) {
    await page.waitForFunction(()=>Module.economy.open,null,{timeout:90000});
    await page.screenshot({path:`artifacts/m6-${scene}-before-web.png`});
    await click(425,572);
    await page.waitForFunction(()=>Module.economy.sold0,null,{timeout:10000});
    const e=await page.evaluate(()=>Module.economy);
    if(scene==='service-exchange'){assert.equal(e.keys,0);assert.equal(e.dynamite,6);assert.equal(e.coins,100);}
    if(scene==='service-surgeon'){assert.equal(e.hp,100);assert.equal(e.maxHP,100);assert.equal(e.coins,80);}
    if(scene==='service-bargain'){assert.equal(e.hp,50);assert.equal(e.maxHP,64);assert.equal(e.itemCount,1);assert.ok(e.sold1);}
    await click(425,572);assert.deepEqual(await page.evaluate(()=>Module.economy),e);
    await click(640,655);await page.waitForFunction(()=>!Module.economy.open);
    console.log(`PASS browser ${scene}: visible offer, purchase, exact resource change, duplicate rejected, leave`);
   } else {
    await page.waitForFunction(()=>Module.economy.reward);
    await click(470,556);await page.waitForFunction(()=>!Module.economy.reward);
    assert.equal(await page.evaluate(()=>Module.economy.itemCount),1);
    console.log('PASS browser mutually exclusive boss reward');
   }
   await page.screenshot({path:`artifacts/m6-${scene}-web.png`});
   assert.equal(await page.evaluate(()=>Module.state.error),'');assert.equal(await page.evaluate(()=>Module.ctx.getError()),0);assert.deepEqual(errors,[]);
  }
 } finally {await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1;});
