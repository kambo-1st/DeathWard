const {chromium}=require('playwright'),assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_MUSHROOM_OUTPUT;fs.mkdirSync(out,{recursive:true});
 const witness=JSON.parse(fs.readFileSync(process.env.DEATHWARD_MUSHROOM_WITNESS));
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),checks=[],errors=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const name of ['isolated','closed-hit','resident']) {
   const natural=name==='resident',params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-300.0.0`});
   if(natural){params.set('resident-seed',witness.seed);params.set('resident-floor',witness.floor);}
   if(name==='closed-hit')params.set('enemy-hit','10:8');
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${params}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   console.log('START',name,'browser',await browser.version());
   console.log('GL',await page.evaluate(()=>{const g=Module.ctx,e=g.getExtension('WEBGL_debug_renderer_info');return e?g.getParameter(e.UNMASKED_RENDERER_WEBGL):g.getParameter(g.RENDERER);}));
   const phases=new Set(),orientations=new Set(),shots=new Set(),captures={},samples=[];
   for(let frame=20;frame<=900;frame+=2) {
    await page.waitForFunction(f=>Module.state?.frame>=f,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError(),p:Module.enemyProbe}));samples.push(s);
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(s.p.type,300);assert.equal(s.p.variant,0);
    assert.equal(s.p.resident.natural,natural);if(!natural)assert(Math.abs(s.p.hp-(name==='closed-hit'?71.6:73.6))<.01);
    const actor=s.p.actors.find(a=>a.id===s.p.entity||a.entity===s.p.entity)||s.p.actors.find(a=>a.type===300);assert(actor?.mushroom);
    const m=actor.mushroom;phases.add(m.phase);assert.equal(m.blocking,m.phase===0||m.phase===1);
    if(m.phase===2&&m.fired){assert(m.frame>=3);orientations.add(m.diagonal?'diagonal':'cardinal');}
    const bullets=s.p.bullets.filter(b=>b.owner===s.p.entity);
    for(const b of bullets){shots.add(b.entity);assert.equal(b.damage,10);assert(Math.abs(Math.hypot(b.vx,b.vz)-21)<.01);assert(Math.abs(b.vy)<.001);
     const cardinal=Math.abs(b.vx)<.01||Math.abs(b.vz)<.01;
     assert(cardinal||Math.abs(Math.abs(b.vx)-Math.abs(b.vz))<.01);}
    const shot=natural?(frame>=100?'resident':null):frame>=60?(m.blocking?'closed':bullets.length&&m.phase===2?'burst':m.phase===3?'exposed':null):null;
    if(shot&&!captures[shot]){captures[shot]=`${out}/${name}-${shot}.png`;await page.screenshot({path:captures[shot]});}
   }
   if(!natural){for(const phase of [1,2,3,4])assert(phases.has(phase));assert(shots.size>=4);assert(captures.closed&&captures.burst&&captures.exposed);}
   else {assert.equal(samples[0].p.resident.room,witness.room);assert(captures.resident);}
   assert.deepEqual(errors,[]);checks.push({case:name,phases:[...phases],orientations:[...orientations],observedShots:shots.size,captures,samples});console.log('PASS',name);
  }
 } finally {fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Production WASM Mushroom normal cycle/cross projectiles, closed quarter-damage hit, actual seeded resident and Original appearance. Special statuses and full six-gate acceptance remain open.'},null,2)+'\n');await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
