const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_ATTACK_FLY_OUTPUT||'artifacts/attack-fly';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const test of [
   {name:'attack-pursuit'},
   {name:'attack-cover',terrain:'cover'},
   {name:'attack-river',terrain:'river'},
   {name:'attack-skatole',morph:true},
   {name:'attack-damaged-morph',morph:true,hit:'1:15',hp:1},
   {name:'attack-death',hit:'180:100',kill:180},
   {name:'natural-attack',seed:0,floor:0}
  ]) {
   const resident=test.seed!==undefined;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${resident?'resident':'enemy'}-18.0.0`});
   if(resident){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.terrain)params.set('enemy-terrain',test.terrain);
   if(test.morph)params.set('enemy-item','isaac:collectible:9');
   if(test.hit)params.set('enemy-hit',test.hit);
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let capture=false,distance=0,previous,elevated=false,overWater=false,returnedToLand=false;
   for(let frame=10;frame<=360;frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe,actor=p.actors.find(a=>a.entity===p.entity);assert.equal(p.resident.natural,resident);
    if(test.kill&&s.frame>=test.kill){assert(!p.alive);assert.equal(p.kills,1);assert.equal(p.threats,0);}
    else {
     assert(actor);assert.equal(actor.type,test.morph?13:18);assert.equal(actor.variant,0);
     assert(Math.abs(actor.hp-(test.hp||(test.morph?9.6:16)))<.01);assert.equal(p.flightBlocked,false);
     if(previous)distance+=Math.hypot(actor.x-previous.x,actor.z-previous.z);previous=actor;
     if(actor.y>2)elevated=true;
     if(p.waterBlocked)overWater=true;else if(overWater)returnedToLand=true;
     if(!resident){assert.equal(p.kills,0);assert.equal(p.threats,1);}
    }
    assert.equal(p.bullets.filter(b=>b.owner===p.entity).length,0,'Attack Fly and morphed Fly do not shoot');
    if(!capture&&frame>=40&&(test.terrain==='cover'?p.y>2:test.terrain==='river'?p.waterBlocked:true)) {
     s.capture=`${out}/${test.name}.png`;await page.screenshot({path:s.capture});capture=true;
    }
    samples.push(s);
   }
   assert(distance>.3,'physical buzzing pursuit moves');assert(capture);
   if(test.terrain==='cover')assert(elevated,'body crosses above solid cover');
   if(test.terrain==='river')assert(overWater&&returnedToLand,'body crosses deep river and returns to land');
   assert.deepEqual(errors,[]);checks.push({case:test.name,distance,elevated,overWater,returnedToLand,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Original visuals, physical pursuit/cover/river crossing, source health, same-entity Skatole transformation with current HP clamp, one final death and a real seeded resident. Native suite additionally covers live/death Hive children and contact expiry. No full balance/performance certification.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
