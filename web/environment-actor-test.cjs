// Gameplay probes for normal fireplace/TNT; no claim of complete source parity.
const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_ENVIRONMENT_OUTPUT||'artifacts/environment-actors';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const test of [
   {name:'fire-extinguish',id:33,args:[['enemy-hit','60:1'],['enemy-blast','120:1']],frames:[45,90,150,240]},
   {name:'fire-flooded',id:33,args:[['enemy-flooded','']],frames:[45,90]},
   {name:'tnt-blast',id:292,args:[['enemy-hit','60:24'],['enemy-blast','120:1']],frames:[45,90,150,240]},
   {name:'tnt-ignition',id:292,args:[['enemy-fire','60']],frames:[45,90,150]},
   {name:'natural-fire-passenger',seed:10,floor:2,id:33,frames:[450,550,650,850]},
   {name:'natural-tnt-passenger',seed:58,floor:3,id:292,frames:[1000,1100,1200,1600]}
  ]) {
   const natural=test.seed!==undefined;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:natural?'resident-906.0.0':`enemy-${test.id}.0.0`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}else for(const [k,v] of test.args)params.append(k,v);
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let carried=false;
   for(const frame of test.frames) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert(s.frame<frame+10,'tight sample window');assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);const p=s.probe;
    if(natural) {
     assert.equal(p.resident.natural,true);const t=p.hornfel.traffic;assert(t.initialized&&!t.stopped);assert.equal(t.capacityRejected,0);
     const ends=new Set();for(const r of t.passengers){assert(!ends.has(r.entry)&&!ends.has(r.exit),'paired endpoints exclusive');ends.add(r.entry);ends.add(r.exit);
      const a=p.actors.find(a=>a.entity===r.actor);if(a){assert.equal(a.carrier,r.cart);assert(a.environment&&[33,292].includes(a.type));if(a.type===test.id&&r.visible)carried=true;}}
     assert.equal(p.actors.filter(a=>a.environment&&a.type!==33&&a.type!==292).length,0);
     if(frame===test.frames.at(-1)){assert(t.spawned>0&&t.removed>0,'quiet exit counted');assert.equal(t.destroyed,0);}
    } else {
     const a=p.actors.find(a=>a.entity===p.entity);assert(a&&a.environment);assert.equal(a.carrier,0);assert.equal(p.threats,0);assert.equal(p.kills,0);
     const spent=test.name==='fire-flooded'||(test.name==='tnt-ignition'?frame>60:frame>120);assert.equal(a.spent,spent);assert.equal(a.destructionPending,false);
     if(spent)assert.equal(a.hp,test.id===33?1:.5);else if(frame>60)assert(a.hp<(test.id===33?5:4));
    }
    s.capture=`${out}/${test.name}-${frame}.png`;await page.screenshot({path:s.capture});samples.push(s);
   }
   if(natural)assert(carried,'actual natural passenger was observed');assert.deepEqual(errors,[]);checks.push({case:test.name,samples});console.log('PASS',test.name);
  }
 } finally {fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Four isolated environmental lifecycle probes plus two unforced natural rail routes. Existing boss timing fixtures require a later update after shared RNG changes; full browser regression and balance are not claimed.'},null,2)+'\n');await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
