const {chromium}=require('playwright'),assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_TAINTED_HOPPER_OUTPUT;fs.mkdirSync(out,{recursive:true});
 const witness=JSON.parse(fs.readFileSync(process.env.DEATHWARD_TAINTED_HOPPER_WITNESS));
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),checks=[],errors=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const name of (process.env.DEATHWARD_TAINTED_HOPPER_CASES||'isolated,cover,river,death,resident').split(',')) {
   const natural=name==='resident',dying=name==='death';
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-29.3.0`});
   if(natural){params.set('resident-seed',witness.seed);params.set('resident-floor',witness.floor);}
   if(name==='cover')params.set('enemy-terrain','hop-cover');
   if(name==='river')params.set('enemy-terrain','river');
   if(dying)params.set('enemy-hit','200:10000');
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${params}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   console.log('START',name,'browser',await browser.version());
   const captures={},samples=[],phases=new Set();let air=false,water=false,peak=.85,volleys=0,finished=false;
   const result={case:name,pass:false,captures,samples};checks.push(result);
   for(let frame=10;frame<=600;frame+=2) {
    await page.waitForFunction(f=>Module.state?.frame>=f,frame,{timeout:90000});
    const s=await page.evaluate(()=>{
     const p=Module.enemyProbe;
     return {frame:Module.state.frame,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError(),
      p:{type:p.type,variant:p.variant,entity:p.entity,alive:p.alive,kills:p.kills,threats:p.threats,shots:p.shots,
       flightBlocked:p.flightBlocked,waterBlocked:p.waterBlocked,resident:p.resident,hazards:p.hazards,
       actors:p.actors.map(a=>({entity:a.entity,type:a.type,variant:a.variant,hp:a.hp,maxHp:a.maxHp,
        x:a.x,y:a.y,z:a.z,hopRings:a.hopRings,targetHop:a.targetHop}))}};
    });samples.push(s);
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(s.p.type,29);assert.equal(s.p.variant,3);
    assert.equal(s.p.resident.natural,natural);const a=s.p.actors.find(a=>a.entity===s.p.entity);
    if(a) {
     assert(a.hopRings&&a.targetHop);assert(!s.p.flightBlocked);assert(Math.abs(a.maxHp-256)<.01);
     air||=a.targetHop.airborne;water||=s.p.waterBlocked;peak=Math.max(peak,a.y);volleys=Math.max(volleys,a.hopRings.volleys);
     phases.add(a.hopRings.animationStage);
     if(!natural) {
      const n=a.hopRings.volleys,expected=30*Math.floor(n/4)+[0,4,10,18][n%4];
      assert.equal(s.p.shots,expected,'source4/6/8/12 repeated ring sequence without generic extra shots');
      assert.equal(a.hopRings.pending,0,'normal capacity does not stall rings');
     }
    }
    if(dying&&!a&&s.frame>210){assert.equal(s.p.kills,1);assert.equal(s.p.actors.length,0);finished=true;}
    let shot;
    if(name==='isolated')shot=a?.hopRings.volleys===1?'first':a?.hopRings.volleys===4?'fourth':a?.targetHop.airborne&&a.y>2?'air':null;
    else if(name==='cover')shot=a?.targetHop.airborne&&a.y>3?'cover':null;
    else if(name==='river')shot=a?.targetHop.airborne&&s.p.waterBlocked?'river':null;
    else if(dying)shot=finished?'death':null;
    else if(natural&&a?.hopRings.volleys>0)shot='resident';
    if(shot&&!captures[shot]){captures[shot]=`${out}/${name}-${shot}.png`;await page.screenshot({path:captures[shot]});}
   }
   assert(air&&volleys>=4,'full physical four-hop cycle observed');
   if(dying)assert(finished&&captures.death);
   if(name==='isolated')assert(captures.air&&captures.first&&captures.fourth&&phases.size===4);
   if(name==='cover')assert(captures.cover&&peak>3);
   if(name==='river')assert(captures.river&&water);
   if(natural){assert.equal(samples[0].p.resident.room,witness.room);assert(captures.resident);}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,peak,volleys,phases:[...phases],water,finished});console.log('PASS',name);
  }
 } finally {fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Production WASM Tainted Hopper four-stage rings, actual cover/water hopping, ordinary death and natural late-floor encounter in Original style. Native tests verify exact timings, flight recurrence and capacity handling. Adaptive armor and full six-gate acceptance remain open.'},null,2)+'\n');await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
