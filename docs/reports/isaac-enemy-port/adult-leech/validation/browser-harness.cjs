// Production WASM Adult Leech: ordinary wall impact, low-health fall, natural resident.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_ADULT_LEECH_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{
  window.__adultCaptures={};window.__adultTrace=[];window.__lastWall=0;window.__wallFrame=0;
  window.__captureAdult=frame=>{
   if(frame>720)return;const p=Module.enemyProbe;if(!p)return;
   const a=p.actors.find(a=>a.entity===p.entity),r=a?.adultLeech;if(!r)return;
   const snapshot=JSON.parse(JSON.stringify(p));window.__adultTrace.push({frame,probe:snapshot});
   if(r.wallRings>window.__lastWall){window.__lastWall=r.wallRings;window.__wallFrame=frame;}
   const kind=r.phase===1&&Math.abs(a.vx)>20?'charge':
    window.__wallFrame&&frame===window.__wallFrame+3?'wall-ring':r.phase===3?'hidden':
    r.phase===4&&r.frame>=8&&r.frame<=10?'fall':r.phase===4&&r.frame>=20&&r.frame<=22?'landing':null;
   if(!kind||window.__adultCaptures[kind])return;
   window.__adultCaptures[kind]={frame,probe:snapshot,png:(Module.canvas||document.querySelector('canvas')).toDataURL('image/png')};
  };
 });
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Scoped Original-style WASM behavior; full statuses, external charge paths, balance and controlled performance remain open.'},null,2)+'\n');
 try{
  const seed=Number(process.env.DEATHWARD_ADULT_SEED),floor=Number(process.env.DEATHWARD_ADULT_FLOOR),room=Number(process.env.DEATHWARD_ADULT_ROOM);
  for(const t of [{name:'wall-impact',natural:false,fall:false},{name:'burrow-fall',natural:false,fall:true},{name:'resident',natural:true,fall:false}]) {
   if(process.env.DEATHWARD_ADULT_CASES&&!process.env.DEATHWARD_ADULT_CASES.split(',').includes(t.name))continue;
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${t.natural?'resident':'enemy'}-854.0.0`,'enemy-camera-follow':''});
   if(t.natural){q.set('resident-seed',seed);q.set('resident-floor',floor);}else if(t.fall){q.set('enemy-hit','10:110');q.set('enemy-player-at','220:-4:8');}else q.set('enemy-player-side','right');
   const result={...t,pass:false};checks.push(result);persist();console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureAdult;});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   await page.waitForFunction(()=>Module.state?.error||Module.state?.frame>=720,null,{timeout:90000});
   const state=await page.evaluate(()=>({error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),trace:window.__adultTrace,captures:window.__adultCaptures,
    renderer:(()=>{const gl=Module.ctx,x=gl.getExtension('WEBGL_debug_renderer_info');return x?gl.getParameter(x.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);})()}));
   Object.assign(result,{renderer:state.renderer,trace:state.trace});
   for(const [kind,c] of Object.entries(state.captures)){const path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;c.path=path;}
   result.captures=state.captures;persist();
   assert.equal(state.error,'');assert.equal(state.style,'Original');assert.equal(state.gl,0);assert(state.trace.length>650);
   let charges=0,wallRings=0,burrows=0,landings=0,landingRings=0,hidden=0,fallFrames=0;const shots=new Set();
   for(const {probe:p} of state.trace) {
    const a=p.actors.find(a=>a.entity===p.entity),r=a.adultLeech;
    assert.equal(a.type,854);assert.equal(a.variant,0);assert.equal(a.subtype,0);assert(Math.abs(a.maxHp-288)<.01);
    assert(!p.flightBlocked,'actual body stays inside flight boundary');
    charges=Math.max(charges,r.charges);wallRings=Math.max(wallRings,r.wallRings);burrows=Math.max(burrows,r.burrows);
    landings=Math.max(landings,r.landings);landingRings=Math.max(landingRings,r.landingRings);
    assert(r.burrows<=1);assert(r.landings<=1);
    if(r.phase===3){assert(r.intangible);assert.equal(r.visibility,0);++hidden;}
    if(r.phase===4){assert.equal(r.intangible,r.frame<18);++fallFrames;}
    if(!t.natural)assert.equal(p.shots,r.wallRings*12+r.landingRings*10);
    for(const b of p.bullets.filter(b=>b.owner===p.entity)) {
     shots.add(b.entity);assert(Math.abs(b.flightRetention-.9)<.001);assert(Math.abs(b.radius-.22)<.001);
     assert(Math.abs(b.gravity-8.1)<.001||Math.abs(b.gravity-3.6)<.001);
    }
    if(t.natural){assert(p.resident.natural);assert.equal(p.resident.floor,floor);assert.equal(p.resident.room,room);}
   }
   if(t.fall){assert.equal(burrows,1);assert.equal(landings,1);assert.equal(landingRings,1);assert(hidden>40);assert(fallFrames>60);assert(state.captures.fall&&state.captures.landing&&state.captures.hidden);}
   else if(!t.natural){assert(charges>0);assert(wallRings>0);assert.equal(burrows,0);assert(state.captures['wall-ring']);}
   else assert(charges>0||burrows>0,'natural actor activates a real attack phase');
   if(!t.natural)assert(shots.size>0,'emitted projectiles exist');
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,charges,wallRings,burrows,landings,landingRings,hiddenFrames:hidden,fallFrames,observedProjectiles:shots.size});persist();console.log('PASS',t.name,JSON.stringify({charges,wallRings,burrows,landingRings}));
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
