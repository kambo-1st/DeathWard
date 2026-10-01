const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const path=require('node:path');
(async()=>{
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1440,height:950}});
 const errors=[];page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|Invalid model|shader failed/i.test(m.text()))errors.push(m.text());});
 const wait=(fn,arg)=>page.waitForFunction(fn,arg,{timeout:90000});
 const frames=async(n=3)=>{const f=await page.evaluate(()=>Module.state.frame);await wait(([f,n])=>Module.state.frame>f+n,[f,n]);};
 const click=async(x,y)=>{const b=await page.locator('#canvas').boundingBox();await page.mouse.move(b.x+x*b.width/1440,b.y+y*b.height/900);await page.mouse.down();await frames();await page.mouse.up();await frames();};
 const key=async(k)=>{await page.keyboard.down(k);await frames();await page.keyboard.up(k);await frames();};
 const launch=async(args)=>{await page.goto((process.env.DEATHWARD_URL||'http://127.0.0.1:8091/')+args);await wait(()=>window.Module?.ready);await page.locator('#start').click({noWaitAfter:true});await wait(()=>Module.state?.frame>8);};
 try{
  await launch('?intro&cinematic&verify');
  assert.equal(await page.evaluate(()=>Module.cinematic.cast),4);
  const original=await page.evaluate(()=>Module.FS.readFile('/persist/train_opening/town.scene',{encoding:'utf8'}));
  await click(155,831);assert.equal(await page.evaluate(()=>Module.cinematic.key),0);
  await click(155,831);assert.equal(await page.evaluate(()=>Module.cinematic.key),1);
  await click(155,831);assert.equal(await page.evaluate(()=>Module.cinematic.key),2);
  await click(155+5/82*1230,852);assert.equal(await page.evaluate(()=>Module.cinematic.track),5);
  await click(1260,438); // Edit the first dialogue line.
  await page.keyboard.down('Control');await key('KeyA');await page.keyboard.up('Control');
  await page.keyboard.type('First journey west, young man?',{delay:35});await key('Enter');
  assert.equal(await page.evaluate(()=>Module.cinematic.dirty),true);
  await page.keyboard.down('Control');await key('KeyZ');await page.keyboard.up('Control');
  assert.equal(await page.evaluate(()=>Module.cinematic.dirty),false);
  await click(155+69/82*1230,705);
  assert.equal(await page.evaluate(()=>Module.cinematic.speaker),'conductor');
  assert.equal(await page.evaluate(()=>Module.cinematic.trainSpeed),0);
  assert.ok(await page.evaluate(()=>Module.cinematic.storm)>.99);
  await page.screenshot({path:path.join(__dirname,'../artifacts/opening/browser-editor.png')});
  await click(155+5/82*1230,852);
  await click(1395,354); // First dialogue's duration.
  assert.equal(await page.evaluate(()=>Module.cinematic.dirty),true);
  await click(830,27);await wait(()=>!Module.saving&&!Module.cinematic.dirty);
  const saved=await page.evaluate(()=>Module.FS.readFile('/persist/train_opening/arrival.cinematic',{encoding:'utf8'}));
  assert.match(saved,/dialogue 5 3\.5 /);
  await launch('?intro&cinematic&verify');
  assert.equal(await page.evaluate(()=>Module.FS.readFile('/persist/train_opening/arrival.cinematic',{encoding:'utf8'})),saved);
  assert.equal(await page.evaluate(()=>Module.FS.readFile('/persist/train_opening/town.scene',{encoding:'utf8'})),original);
  // Runtime handoff uses the same sequence; start near its end to test the actual cut.
  await launch('?intro&cinematic-at=81&verify');
  await wait(()=>!Module.cinematic.active&&Module.state.hub===2);
  assert.equal(await page.evaluate(()=>Module.state.sandstorm),true);
  assert.equal(await page.evaluate(()=>Module.state.paused),false);
  await frames();await page.screenshot({path:path.join(__dirname,'../artifacts/opening/browser-arrival.png')});
  const before=await page.evaluate(()=>({x:Module.state.x,z:Module.state.z}));
  await page.keyboard.down('KeyW');await frames(12);await page.keyboard.up('KeyW');await frames();
  const after=await page.evaluate(()=>({x:Module.state.x,z:Module.state.z}));
  assert.notDeepEqual(after,before,'control returns to the player after arrival');
  assert.equal(await page.evaluate(()=>Module.ctx.getError()),0);assert.deepEqual(errors,[]);
  console.log('PASS opening browser: cast selection, dialogue editing/undo/save/reload, conductor timing, storm, Redstone cut and restored player control.');
 }catch(e){console.error(errors);await page.screenshot({path:path.join(__dirname,'../artifacts/opening/browser-failure.png')});throw e;}
 finally{await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1;});
