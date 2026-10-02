const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
const path=require('node:path');
(async()=>{
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1440,height:950}});
 const errors=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|Invalid model|shader failed/i.test(m.text()))errors.push(m.text());});
 const wait=(fn,arg)=>page.waitForFunction(fn,arg,{timeout:90000});
 const frames=async(n=3)=>{const f=await page.evaluate(()=>Module.state.frame);await wait(([f,n])=>Module.state.frame>f+n,[f,n]);};
 const click=async(x,y)=>{const b=await page.locator('#canvas').boundingBox();await page.mouse.move(b.x+x*b.width/1280,b.y+y*b.height/800);await page.mouse.down();await frames();await page.mouse.up();await frames();};
 const key=async(k)=>{await page.keyboard.down(k);await frames();await page.keyboard.up(k);await frames();};
 const launch=async(args)=>{await page.goto((process.env.DEATHWARD_URL||'http://127.0.0.1:8091/')+args);await wait(()=>window.Module?.ready);await page.locator('#start').click({noWaitAfter:true});await wait(()=>Module.state?.frame>8);};
 const walk=async()=>{const p=await page.evaluate(()=>Module.quest);await click(p.x,p.y);await wait(()=>Module.quest.dialogue);};
 const talk=async()=>{for(let n=0;n<8&&await page.evaluate(()=>Module.quest.dialogue);++n)await click(790,708);};
 const saved=()=>page.evaluate(()=>Module.FS.readFile('/persist/campaign.save',{encoding:'utf8'}));
 const capture=async(name)=>page.screenshot({path:path.join(__dirname,'../artifacts/quest/browser-'+name+'.png')});
 fs.mkdirSync(path.join(__dirname,'../artifacts/quest'),{recursive:true});
 try {
  await launch('?intro&cinematic-at=81&verify');await wait(()=>Module.quest.stage===1&&!Module.cinematic.active);
  assert.equal(await page.evaluate(()=>Module.state.hub),2);await capture('arrival');
  const map=await page.evaluate(()=>Module.FS.readFile('/persist/redstone/town.scene',{encoding:'utf8'}));
  await walk();assert.equal(await page.evaluate(()=>Module.quest.speaker),'YOU');await talk();
  assert.equal(await page.evaluate(()=>Module.quest.stage),2);await wait(()=>!Module.saving);
  assert.match(await saved(),/redstone.evening_conductor/);
  await launch('?hub=redstone&verify');assert.equal(await page.evaluate(()=>Module.quest.stage),2);
  await walk();await capture('tent');await talk();await wait(()=>Module.quest.stage===3&&!Module.quest.sleeping);
  await capture('morning');await wait(()=>!Module.saving);assert.match(await saved(),/redstone.slept/);
  await walk();await talk();assert.equal(await page.evaluate(()=>Module.quest.stage),4);
  await walk();await capture('commander');await talk();assert.equal(await page.evaluate(()=>Module.quest.stage),5);
  await walk();await capture('trail');await talk();await wait(()=>Module.quest.stage===6&&Module.quest.search);
  assert.equal(await page.evaluate(()=>Module.state.screen),1);await capture('search');
  await key('Escape');await wait(()=>Module.state.paused);await key('KeyT');await wait(()=>Module.state.screen===2);
  await key('Enter');await wait(()=>Module.state.screen===0&&Module.state.hub===2);
  assert.equal(await page.evaluate(()=>Module.quest.stage),6);await wait(()=>!Module.saving);
  await launch('?hub=redstone&verify');assert.equal(await page.evaluate(()=>Module.quest.stage),6);
  assert.equal(await page.evaluate(()=>Module.FS.readFile('/persist/redstone/town.scene',{encoding:'utf8'})),map);
  assert.equal(await page.evaluate(()=>Module.ctx.getError()),0);assert.deepEqual(errors,[]);
  console.log('PASS browser arrival: cinematic handoff, clickable quest markers, dialogue, save/reload, sleep, morning conductor, commander, generated search and return.');
 } catch(e) {console.error(e,errors);console.error(await page.evaluate(()=>({state:Module.state,quest:Module.quest})));await capture('failure');throw e;}
 finally{await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1;});
