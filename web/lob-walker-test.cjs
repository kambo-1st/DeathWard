// Actual regular lobber trajectories and seeded encounters; no content overrides.
const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_LOB_OUTPUT||'artifacts/lob-walkers';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const test of [
   {name:'gurgle-physical-lob',id:87,hp:128},
   {name:'splasher-movement-lob',id:238,hp:38.4},
   {name:'natural-gurgle',id:87,seed:2,floor:3,room:3,hp:128},
   {name:'natural-splasher',id:238,seed:0,floor:5,room:3,hp:67.84}
  ]) {
   const natural=test.seed!==undefined;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${test.id}.0.0`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let rising=false,falling=false,capture=false;
   for(let frame=20;frame<=600;frame+=20) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert(s.frame<frame+15);assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe;assert.equal(p.type,test.id);assert.equal(p.variant,0);assert.equal(p.resident.natural,natural);
    if(frame===20){assert(Math.abs(p.hp-test.hp)<.01);if(natural){assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);assert(p.actors.length>1);}}
    const bullets=p.bullets.filter(b=>b.owner===p.entity);
    for(const b of bullets) {
     assert.equal(b.kind,12);assert(Math.abs(b.blastRadius-6)<.01);assert(Math.abs(b.gravity-(test.id===87?36.9:22.5))<.01);
     assert(Number.isFinite(b.y)&&b.y>=0);rising||=b.vy>0;falling||=b.vy<0;
     if(test.id===238)assert(Math.abs(Math.hypot(b.vx,b.vz)-15)<.01);
    }
    if(frame>=180&&!capture&&bullets.length){s.capture=`${out}/${test.name}.png`;await page.screenshot({path:s.capture});capture=true;}
    samples.push(s);
   }
   if(!natural){assert(rising&&falling,'both airborne ascent and descent observed');assert(samples.at(-1).probe.shots>=2);assert(samples.at(-1).probe.statue.explosions>=1);}
   assert(capture,'settled-camera real projectile capture');assert.deepEqual(errors,[]);
   checks.push({case:test.name,rising,falling,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Default-content Gurgle/Splasher physical lobs and actual seeded residents in Original style. No source-exact movement, comprehensive balance or controlled rendered-performance certification.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
