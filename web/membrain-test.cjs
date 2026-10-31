// Production WASM: exact MemBrain variants, Cyst, required births and natural residents.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_MEMBRAIN_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{
  window.__memCaptures={};window.__memTrace=[];window.__captureMem=frame=>{
   if(frame>600)return;const p=Module.enemyProbe;if(!p)return;
   const a=p.actors.find(a=>a.entity===p.entity),snapshot=JSON.parse(JSON.stringify(p));
   window.__memTrace.push({frame,probe:snapshot});const r=a?.memBrain,g=a?.guts;
   const kind=!a&&frame>=545?'children':r&&a.lift>.7?'hop':
    r?.frame>=32&&r?.frame<=34?'ring':g?.shotFrame>=3&&g?.shotFrame<=5?'shot':null;
   if(!kind||window.__memCaptures[kind])return;
   window.__memCaptures[kind]={frame,probe:snapshot,png:(Module.canvas||document.querySelector('canvas')).toDataURL('image/png')};
  };
 });
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Scoped production WASM behavior and natural placement in Original style; full status, balance and performance gates remain open.'},null,2)+'\n');
 try{
  const entries=[{name:'membrain',id:'57.0.0',child:32,seed:0,floor:5,room:2},
   {name:'mama-guts',id:'57.1.0',child:40,seed:1,floor:5,room:7},
   {name:'dead-meat',id:'57.2.0',child:862,seed:16,floor:3,room:10},
   {name:'cyst',id:'862.0.0',seed:22,floor:7,room:1}];
  for(const natural of [false,true])for(const entry of entries) {
   const t={...entry,name:(natural?'resident-':'')+entry.name,natural};
   if(process.env.DEATHWARD_MEMBRAIN_CASES&&!process.env.DEATHWARD_MEMBRAIN_CASES.split(',').includes(t.name))continue;
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${natural?'resident':'enemy'}-${t.id}`,'enemy-camera-follow':''});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}else if(t.child)q.set('enemy-hit','540:10000');
   const result={...t,pass:false};checks.push(result);persist();console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureMem;});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   await page.waitForFunction(()=>Module.state?.error||Module.state?.frame>=600,null,{timeout:90000});
   const state=await page.evaluate(()=>({error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),trace:window.__memTrace,captures:window.__memCaptures,
    renderer:(()=>{const gl=Module.ctx,x=gl.getExtension('WEBGL_debug_renderer_info');return x?gl.getParameter(x.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);})()}));
   assert.equal(state.error,'');assert.equal(state.style,'Original');assert.equal(state.gl,0);assert(state.trace.length>550);
   let volleys=0,shots=0,actualShots=0,previousShots=0,lastShotTick=null,childFrames=0,bounces=0;const bullets=new Map();
   for(const {frame,probe:p} of state.trace) {
    const a=p.actors.find(a=>a.entity===p.entity);
    if(!natural&&t.child&&frame>=540) {
     assert(!a,'ordinary damage removes parent');assert.equal(p.kills,1);assert.equal(p.threats,2);
     assert.equal(p.actors.length,2);for(const c of p.actors){assert.equal(c.type,t.child);assert.equal(c.variant,0);assert(c.brain||c.guts,'real child controller');}
     ++childFrames;continue;
    }
    assert(a);assert.equal(`${a.type}.${a.variant}.${a.subtype}`,t.id);assert(!p.groundBlocked,'legal grounded body');
    assert(Math.abs(a.maxHp-(t.child?198.4:80))<.01);
    if(t.child){assert(a.memBrain);volleys=Math.max(volleys,a.memBrain.volleys);if(!natural)assert.equal(p.shots,a.memBrain.volleys*8);}
    else {
     assert(a.guts);shots=Math.max(shots,a.guts.shots);
     if(a.guts.shots>previousShots){if(lastShotTick!==null)assert.equal(a.guts.ticks-lastShotTick,31);lastShotTick=a.guts.ticks;previousShots=a.guts.shots;}
     if(!natural){assert.equal(p.shots,a.guts.shots);assert.equal(p.hazards.length,0);}
    }
    for(const b of p.bullets.filter(b=>b.owner===p.entity)) {
     if(!bullets.has(b.entity))++actualShots;
     const old=bullets.get(b.entity);if(old&&old.vx*b.vx+old.vz*b.vz<-.01)++bounces;
     bullets.set(b.entity,b);assert(Math.abs(b.gravity-(t.id==='57.2.0'?1.35:t.child?4.5:9))<.001);
     assert(Math.abs(b.flightRetention-.9)<.001);assert(Math.abs(b.radius-(t.child?.308:.22))<.001);
    }
    if(natural){assert(p.resident.natural);assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);}
   }
   assert(actualShots>0,'actual projectiles observed');assert(t.child?volleys>0:shots>0);
   if(!natural&&t.child){assert(childFrames>40);assert(state.captures.children&&state.captures.ring&&state.captures.hop);}
   if(!t.child)assert(state.captures.shot);
   for(const [kind,c] of Object.entries(state.captures)){const path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;c.path=path;}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,volleys,shots,actualShots,childFrames,observedVelocityReversals:bounces,renderer:state.renderer,trace:state.trace,captures:state.captures});persist();console.log('PASS',t.name,JSON.stringify({volleys,shots,actualShots,childFrames,bounces}));
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
