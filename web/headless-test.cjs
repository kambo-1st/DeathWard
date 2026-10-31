// Scoped production WASM checks for actual Gusher/Pacer controllers and residents.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_HEADLESS_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed|Resident captures preserve|requires an isolated/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{window.__trace=[];window.__captures={};window.__capture=frame=>{
  if(frame>1500)return;const p=Module.enemyProbe;if(!p)return;
  window.__trace.push({frame,probe:JSON.parse(JSON.stringify(p))});
  const a=p.actors.find(a=>a.entity===p.entity),r=a?.headless,kinds=[];
  if(r&&frame>=90)kinds.push('walking');
  if(r&&p.bullets.some(b=>b.owner===p.entity&&Math.hypot(b.x-a.x,b.z-a.z)>1&&b.y>1.3))kinds.push('lob');
  if(r?.shots>=3)kinds.push('repeat');
  for(const k of kinds)if(!window.__captures[k])window.__captures[k]={frame,png:Module.canvas.toDataURL('image/png')};
 };});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Scoped Original-style production WASM Gusher/Pacer tests. Natural populations/terrain unmodified. No full acceptance claim.'},null,2)+'\n');
 try {
  for(const t of JSON.parse(process.env.DEATHWARD_HEADLESS_ENTRIES)) {
   const result={...t,pass:false};checks.push(result);persist();console.log('START',t.name);
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${t.natural?'resident':'enemy'}-11.${t.variant}.0`,'enemy-camera-follow':''});
   if(t.natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   if(t.cover){assert(!t.natural);q.set('enemy-terrain','cover');}
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__capture;});await page.locator('#start').click({noWaitAfter:true});
   let previousFrame=-1,stalled=0;
   for(let observation=0;;++observation) {
    try{await page.waitForFunction(limit=>Module.state?.error||Module.state?.frame>=limit,t.frames,{timeout:60000});break;}
    catch(error){if(error.name!=='TimeoutError')throw error;
     const progress=await page.evaluate(()=>({frame:Module.state?.frame,error:Module.state?.error,traceFrames:window.__trace.length,last:window.__trace.at(-1)}));
     (result.observations??=[]).push(progress);persist();console.log('PROGRESS',t.name,progress.frame);
     assert.deepEqual(errors,[]);stalled=progress.frame>previousFrame?0:stalled+1;previousFrame=progress.frame;
     assert(stalled<2,'simulation stopped advancing across two observation windows');assert(observation<11,'twelve minute limit reached; progress evidence preserved');
    }
   }
   const state=await page.evaluate(()=>({error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),trace:window.__trace,captures:window.__captures,
    renderer:(()=>{const gl=Module.ctx,x=gl.getExtension('WEBGL_debug_renderer_info');return x?gl.getParameter(x.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);})()}));
   for(const [kind,c] of Object.entries(state.captures)){c.path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(c.path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;}
   Object.assign(result,{renderer:state.renderer,trace:state.trace,captures:state.captures});persist();
   assert.equal(state.error,'');assert.equal(state.style,'Original');assert.equal(state.gl,0);assert(state.trace.length>t.frames-30);
   let shots=0,movement=0,old=null;const bullets=new Set();
   for(const {probe:p} of state.trace) {
    const a=p.actors.find(a=>a.entity===p.entity);assert(a?.headless);assert.equal(a.type,11);assert.equal(a.variant,t.variant);assert(!p.groundBlocked);
    assert.equal(a.maxHp,32);assert(a.hp>0&&a.hp<=a.maxHp);assert(a.headless.cooldown>=0&&a.headless.cooldown<=59);shots=Math.max(shots,a.headless.shots);
    if(old)movement+=Math.hypot(a.x-old.x,a.z-old.z);
    if(!t.natural)assert.equal(p.shots,a.headless.shots);
    for(const b of p.bullets.filter(b=>b.owner===p.entity)) {
     bullets.add(b.entity);assert(Math.abs(Math.hypot(b.vx,b.vz)-15)<.01);
     assert(Math.abs(b.gravity-18)<.001&&Math.abs(b.flightRetention-.9)<.001&&Math.abs(b.radius-.22)<.001&&Math.abs(b.damage-10)<.001);
    }
    if(t.natural){assert(p.resident.natural);assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);assert.deepEqual(p.resident.source,[11,t.variant,0]);}
    old=a;
   }
   assert(movement>1,'headless body actually wanders');
   if(t.variant){assert.equal(shots,0);assert.equal(bullets.size,0);}else{assert(shots>=3&&bullets.size>=3);assert(result.captures.lob,'visible moving lob capture');}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,shots,movement,observedProjectileIds:bullets.size});persist();
   console.log('PASS',t.name,JSON.stringify({shots,movement,observedProjectileIds:bullets.size}));
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
