// Run against scripts/serve-web.py. Each browser context owns isolated IndexedDB.
const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
const path=require('node:path');
(async()=>{
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const context=await browser.newContext({viewport:{width:1440,height:950}});
 const page=await context.newPage();
 const errors=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|Invalid model|shader failed/i.test(m.text()))errors.push(m.text());});
 const wait=(fn,arg)=>page.waitForFunction(fn,arg,{timeout:90000});
 const tick=()=>page.evaluate(()=>new Promise(resolve=>requestAnimationFrame(()=>requestAnimationFrame(()=>requestAnimationFrame(resolve)))));
 const click=async(x,y)=>{
  const b=await page.locator('#canvas').boundingBox(),s=Math.min(b.width/1280,b.height/800);
  await page.mouse.move(b.x+(b.width-1280*s)/2+x*s,b.y+(b.height-800*s)/2+y*s);
  await page.mouse.down();await tick();await page.mouse.up();await tick();
 };
 const key=async(k)=>{await page.keyboard.down(k);await tick();await page.keyboard.up(k);await tick();};
 const output=path.join(__dirname,'../artifacts/full-experience');fs.mkdirSync(output,{recursive:true});
 const capture=name=>page.screenshot({path:path.join(output,name+'.png')});
 const url=process.env.DEATHWARD_URL||'http://127.0.0.1:8091/';
 const enter=async()=>{
  await page.goto(url+'?full-experience&verify');await wait(()=>window.Module?.ready);
  assert.equal(await page.locator('#start').textContent(),'Start DeathWard');
  await page.locator('#start').click({noWaitAfter:true});await wait(()=>Module.frontend?.active);
 };
 const menu=()=>wait(()=>Module.frontend?.page===2);
 const read=file=>page.evaluate(file=>Module.FS.readFile(file,{encoding:'utf8'}),file);
 const exists=file=>page.evaluate(file=>Module.FS.analyzePath(file).exists,file);
 const flush=()=>wait(()=>!Module.saving);
 try {
  await enter();await wait(()=>Module.frontend.page===0);await tick();await capture('studio');
  await wait(()=>Module.frontend.page===1);await tick();await capture('title');
  await menu();await capture('empty-slots');
  assert.deepEqual(await page.evaluate(()=>Module.frontend.slots.map(s=>s.state)),[0,0,0]);
  assert.equal(await exists('/persist/campaign.save'),false);
  assert.equal(await exists('/persist/slots'),false);

  // Mouse settings, keyboard adjustment, cancel and apply; no campaign writes.
  await click(540,720);await wait(()=>Module.frontend.page===3);
  const master=await page.evaluate(()=>Module.frontend.master);
  await key('ArrowLeft');assert.ok((await page.evaluate(()=>Module.frontend.master))<master);
  await key('Escape');await menu();
  assert.equal(await page.evaluate(()=>Module.frontend.master),master);
  await click(540,720);await wait(()=>Module.frontend.page===3);
  await key('ArrowLeft');await click(800,503); // vegetation slider
  await click(800,599); // rivers off
  await capture('settings');await click(810,700);await menu();await flush();
  const preferences=await read('/persist/audio.cfg');
  assert.equal(await exists('/persist/slots'),false);
  await page.setViewportSize({width:1100,height:820});await tick();await capture('smaller-window');

  // Start slot two. A saved opening exists immediately; other slots stay empty.
  await click(640,410);await click(640,638);
  await wait(()=>Module.cinematic?.story&&Module.cinematic.active);
  assert.equal(await exists('/persist/slots/slot-1.save'),false);
  assert.match(await read('/persist/slots/slot-2.save'),/journey.started/);
  assert.equal(await exists('/persist/slots/slot-3.save'),false);
  assert.equal(await exists('/persist/campaign.save'),false);
  await capture('train');await key('Escape');
  await wait(()=>Module.quest?.stage===1&&!Module.cinematic.active);await flush();
  assert.match(await read('/persist/slots/slot-2.save'),/redstone.arrived/);
  // Commit the first conversation through the real quest card.
  const objective=await page.evaluate(()=>({x:Module.quest.x,y:Module.quest.y}));
  // In-game HUD uses the whole canvas, unlike the letterboxed front end.
  const gameClick=async(x,y)=>{const b=await page.locator('#canvas').boundingBox();await page.mouse.move(b.x+x*b.width/1280,b.y+y*b.height/800);await page.mouse.down();await tick();await page.mouse.up();await tick();};
  await gameClick(objective.x,objective.y);await wait(()=>Module.quest.dialogue);
  for(let n=0;n<8&&await page.evaluate(()=>Module.quest.dialogue);++n)await gameClick(790,708);
  await wait(()=>Module.quest.stage===2);await flush();
  const second=await read('/persist/slots/slot-2.save');

  // Reload from IndexedDB; use keyboard only to continue the selected slot.
  await enter();await key('Enter');await key('Enter');await menu();
  assert.equal(await page.evaluate(()=>Module.frontend.slots[1].chapter),'Shelter for the night');
  assert.equal(await read('/persist/audio.cfg'),preferences);
  await capture('saved-slot');await key('ArrowRight');await key('Enter');await key('Enter');
  await wait(()=>Module.quest?.stage===2&&Module.state?.frame>8);
  assert.equal(await page.evaluate(()=>Module.cinematic.active),false);
  assert.equal(await read('/persist/slots/slot-2.save'),second);

  // New slot one starts the opening, independently of slot two's quest.
  await enter();await menu();await click(300,410);await click(640,638);
  await wait(()=>Module.cinematic?.story&&Module.cinematic.active);await flush();
  assert.equal(await read('/persist/slots/slot-2.save'),second);
  assert.doesNotMatch(await read('/persist/slots/slot-1.save'),/redstone.arrived/);

  // Corrupt-slot fixture: it is visibly blocked and its exact bytes survive.
  await page.evaluate(()=>{Module.FS.writeFile('/persist/slots/slot-3.save','damaged fixture');Module.flushSaves();});await flush();
  await enter();await menu();await click(970,410);await click(640,638);
  assert.equal(await page.evaluate(()=>Module.frontend.active),true);
  assert.equal(await page.evaluate(()=>Module.frontend.slots[2].state),2);
  assert.equal(await read('/persist/slots/slot-3.save'),'damaged fixture');await capture('unavailable-slot');
  assert.equal(await page.evaluate(()=>Module.ctx.getError()),0);assert.deepEqual(errors,[]);
  await click(740,720);await wait(()=>Module.gameFinished);
  assert.equal(await page.locator('#start').textContent(),'Play again');
  console.log('PASS full experience: logos, settings/cancel, resize, three isolated slots, train/quest handoff, persisted resume, corruption and exit.');
 } catch(e) {console.error(e,errors);await capture('failure');throw e;}
 finally{await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1;});
