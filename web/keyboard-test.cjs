const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const browser=await chromium.launch({headless:process.env.DEATHWARD_HEADFUL!=='1',executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1440,height:948}}),errors=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const wait=(fn,arg)=>page.waitForFunction(fn,arg,{timeout:90000});
 const frames=async(n=2)=>{const f=await page.evaluate(()=>Module.state.frame);await wait(start=>Module.state.frame>=start.frame+start.count,{frame:f,count:n});};
 const key=async(code)=>{await page.keyboard.down(code);await frames();await page.keyboard.up(code);await frames();};
 const state=()=>page.evaluate(()=>Module.state);
 try {
  await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8091/'}?verify&mute&theme=canyon`);
  await wait(()=>window.Module?.ready);
  await page.locator('#start').focus();await page.keyboard.press('Enter');
  await wait(()=>Module.state?.frame>3&&Module.navigation);
  assert.equal(await page.evaluate(()=>document.activeElement.id),'canvas');
  await key('Escape');assert.ok((await state()).paused);
  await key('Tab');await key('Enter');assert.ok(await page.evaluate(()=>Module.navigation.help));
  const pausedFrame=await state();await key('KeyB');await key('ArrowUp');
  assert.equal((await state()).x,pausedFrame.x);assert.equal((await state()).z,pausedFrame.z);
  await key('Escape');assert.ok(!await page.evaluate(()=>Module.navigation.help));
  await key('Escape');assert.ok(!(await state()).paused);
  await key('KeyE');await wait(()=>Module.state.menu);await key('Enter');await wait(()=>Module.state.screen===1);
  // A parked pointer over the HUD must never disable keyboard gameplay.
  const box=await page.locator('#canvas').boundingBox();await page.mouse.move(box.x+1100*box.width/1280,box.y+200*box.height/800);
  const ammo=(await state()).dynamite;await key('KeyB');assert.equal((await state()).dynamite,ammo-1);
  const shots=(await state()).shots;await key('ArrowRight');assert.ok((await state()).shots>shots);
  await frames(25);await key('KeyC');assert.ok((await state()).dynamiteThrowMode);
  await page.keyboard.down('ArrowUp');await page.keyboard.down('KeyB');await frames();
  await page.keyboard.up('ArrowUp');await page.keyboard.up('KeyB');await frames();
  assert.equal((await state()).dynamite,ammo-2);
  const zoom=(await state()).zoom,scroll=await page.evaluate(()=>window.scrollY);
  await page.keyboard.down('PageUp');await frames(15);await page.keyboard.up('PageUp');await frames(10);
  assert.ok((await state()).zoom>zoom);assert.equal(await page.evaluate(()=>window.scrollY),scroll);
  await key('Escape');const stopped=(await state()).shots;
  await page.keyboard.down('ArrowDown');await frames();await key('Escape');await frames();
  assert.equal((await state()).shots,stopped,'a held menu arrow must not become a shot after closing pause');
  await page.keyboard.up('ArrowDown');await frames();
  // Cheats establish a cleared boss room; all navigation above uses normal controls.
  await key('F7');await key('F3');await wait(()=>Module.navigation.exitReady&&Module.navigation.exitX>=0);
  assert.ok((await page.evaluate(()=>Module.navigation.exitX))<=850);
  fs.mkdirSync('artifacts',{recursive:true});await page.screenshot({path:'artifacts/exit-beacon-web.png'});
  await key('Escape');await key('KeyH');assert.ok(await page.evaluate(()=>Module.navigation.help));
  await page.screenshot({path:'artifacts/keyboard-controls-web.png'});
  assert.equal((await state()).error,'');assert.equal(await page.evaluate(()=>Module.ctx.getError()),0);assert.deepEqual(errors,[]);
  console.log('PASS browser keyboard launch, menus/help, bombs over HUD, throwing, arrows, zoom, menu guards and cleared-floor beacon');
 } finally {await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1;});
