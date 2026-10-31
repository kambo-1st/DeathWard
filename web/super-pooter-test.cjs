const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_SUPER_OUTPUT||'artifacts/super-pooter';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  const natural=JSON.parse(process.env.DEATHWARD_SUPER_RESIDENT||'{"seed":0,"floor":0}');
  for(const test of [
   {name:'super-pair',id:'14.1.0'},
   {name:'super-cover',id:'14.1.0',terrain:'cover'},
   {name:'super-skatole',id:'14.1.0',suppressed:true},
   {name:'pooter-skatole',id:'14.0.0',suppressed:true},
   {name:'super-death',id:'14.1.0',kill:180},
   {name:'natural-super',id:'14.1.0',...natural}
  ]) {
   const resident=test.seed!==undefined;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${resident?'resident':'enemy'}-${test.id}`});
   if(resident){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.terrain)params.set('enemy-terrain',test.terrain);
   if(test.suppressed)params.set('enemy-item','isaac:collectible:9');
   if(test.kill)params.set('enemy-hit',`${test.kill}:100`);
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let capture=false,pair=false,distance=0,previous,elevated=false;
   for(let frame=15;frame<=300;frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe,actor=p.actors.find(a=>a.entity===p.entity);
    assert.equal(p.resident.natural,resident);
    if(test.kill&&s.frame>=test.kill){assert(!p.alive);assert.equal(p.kills,1);assert.equal(p.threats,0);}
    else {
     assert(actor);assert.equal(actor.type,14);assert.equal(actor.variant,test.id==='14.0.0'?0:1);assert(Math.abs(actor.hp-25.6)<.01);
     assert.equal(p.flightBlocked,false);
     if(previous)distance+=Math.hypot(actor.x-previous.x,actor.z-previous.z);previous=actor;
     if(actor.y>2)elevated=true;
     if(test.suppressed){assert.equal(p.kills,0);assert.equal(p.threats,1);}
    }
    const shots=p.bullets.filter(b=>b.owner===p.entity);
    if(test.suppressed)assert.equal(shots.length,0);
    for(const b of shots){assert.equal(b.kind,0);const speed=Math.hypot(b.vx,b.vy,b.vz);assert(speed>20.99&&speed<21.01);}
    if(shots.length===2&&!pair) {
     const [a,b]=shots,la=Math.hypot(a.vx,a.vz),lb=Math.hypot(b.vx,b.vz);
     const dot=(a.vx*b.vx+a.vz*b.vz)/(la*lb),expected=Math.cos(2*Math.atan2(.276,.961));
     assert(Math.abs(dot-expected)<.002,'source pair angle');assert(Math.abs(a.vy-b.vy)<.002,'shared physical pitch');pair=true;
    }
    if(!capture&&frame>=40&&(test.suppressed||shots.length===2)) {s.capture=`${out}/${test.name}.png`;await page.screenshot({path:s.capture});capture=true;}
    samples.push(s);
   }
   assert(distance>.2,'buzzing body moves');assert(capture);if(!test.suppressed)assert(pair,'owned physical pair observed');
   if(test.terrain)assert(elevated,'cover raises physical flight body');assert.deepEqual(errors,[]);
   checks.push({case:test.name,distance,pair,elevated,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Original visuals, buzzing, source health, mode1 pair angles/speeds, elevated flight/pitch, partial Skatole dependency, one death and seeded placement. No full balance/performance or item certification.'},null,2)+'\n');
  await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
