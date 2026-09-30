// Exercise real mouse entry/exit, automatic doors and the building cutaway in WebGL.
const {chromium} = require('playwright');
const assert = require('node:assert/strict');
const path = require('node:path');
const fs = require('node:fs');
const root=path.resolve(__dirname,'..');
(async()=>{
  const browser=await chromium.launch({headless:true,
    executablePath:process.env.DEATHWARD_BROWSER || undefined,
    args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
  try {
    const page=await browser.newPage({viewport:{width:1280,height:848}});
    const errors=[];
    page.on('pageerror',e=>errors.push(String(e)));
    page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|shader failed/i.test(m.text()))errors.push(m.text());});
    const wait=(fn,arg)=>page.waitForFunction(fn,arg,{timeout:60000});
    await page.goto((process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/')+'?verify');
    await wait(()=>Module.ready);await page.locator('#start').click({noWaitAfter:true});
    await wait(()=>Module.state?.frame>8);
    assert.equal(await page.evaluate(()=>Module.state.error),'');
    assert.ok(await page.evaluate(()=>Module.buildings.doors>20));
    assert.equal(await page.evaluate(()=>Module.buildings.inside),false);
    await page.mouse.move(640,420);await page.mouse.wheel(0,700);
    await wait(()=>Module.state.zoom<100);
    const clickPoint=async(which)=>{
      const point=await page.evaluate(which=>({x:Module.buildings[which+'X'],y:Module.buildings[which+'Y'],
          width:Module.canvas.width,height:Module.canvas.height}),which);
      const box=await page.locator('#canvas').boundingBox();
      assert.ok(point.x>0 && point.x<point.width && point.y>130 && point.y<700,'Destination is visible outside HUD panels');
      await page.mouse.click(box.x+point.x*box.width/point.width,box.y+point.y*box.height/point.height,{delay:120});
    };
    await clickPoint('target');
    await wait(()=>Module.buildings.open>0);
    await wait(()=>Math.hypot(Module.state.x+13.5,Module.state.z+11.5)<.3);
    assert.equal(await page.evaluate(()=>Module.buildings.inside),true);
    fs.mkdirSync(path.join(root,'artifacts'),{recursive:true});
    await page.screenshot({path:path.join(root,'artifacts/web-building-interior.png')});
    await page.keyboard.press('Escape',{delay:100});await wait(()=>Module.state.paused);
    const frozen=await page.evaluate(()=>({building:Module.buildings,time:Module.motion.time}));
    await page.waitForTimeout(250);
    assert.deepEqual(await page.evaluate(()=>({building:Module.buildings,time:Module.motion.time})),frozen);
    await page.keyboard.press('Escape',{delay:100});await wait(()=>!Module.state.paused);
    await page.mouse.move(620,390);await page.mouse.down({button:'middle'});
    await page.mouse.move(680,390,{steps:8});await page.mouse.up({button:'middle'});
    assert.equal(await page.evaluate(()=>Module.buildings.inside),true);
    await clickPoint('exit');
    await wait(()=>Math.hypot(Module.state.x+3,Module.state.z+4)<.3);
    assert.equal(await page.evaluate(()=>Module.buildings.inside),false);
    assert.deepEqual(errors,[]);
    console.log('PASS browser mouse entry/exit, door opening, original interior, pause, camera orbit and exterior restoration');
  } finally {await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1;});
