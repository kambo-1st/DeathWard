// Production WASM checks for exact Dip/Squirt variants and seeded residents.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_DIP_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{window.__captures={};window.__trace=[];window.__capture=frame=>{
  if(frame>720)return;const p=Module.enemyProbe;if(!p)return;window.__trace.push({frame,probe:JSON.parse(JSON.stringify(p))});
  const a=p.actors.find(a=>a.entity===p.entity),r=a?.slide,kinds=[];
  if(r?.phase===2&&r.dashes>0)kinds.push('slide');
  if(r?.phase===1&&r.frame>=4)kinds.push(r.second?'second-windup':'windup');
  if(r?.creep>2)kinds.push('creep');
  if(r?.chains>0)kinds.push('chain');
  if(!a&&frame>=660&&p.actors.length)kinds.push('children');
  if(!a&&p.bullets.some(b=>b.owner===p.entity))kinds.push('death-shot');
  for(const k of kinds)if(!window.__captures[k])window.__captures[k]={frame,probe:JSON.parse(JSON.stringify(p)),png:Module.canvas.toDataURL('image/png')};
 };});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Scoped production WASM behavior and placement, Original style. Full acceptance remains open.'},null,2)+'\n');
 try{
 const entries=JSON.parse(process.env.DEATHWARD_DIP_ENTRIES||'[]');assert(entries.length>0);
 for(const t of entries){const result={...t,pass:false};checks.push(result);persist();console.log('START',t.name);
  const natural=!!t.natural,death=!natural&&['217.3.0','220.1.0','871.0.0'].includes(t.id);
  const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${natural?'resident':'enemy'}-${t.id}`,'enemy-camera-follow':''});
  if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}if(death)q.set('enemy-hit','660:10000');
  await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
  await page.evaluate(()=>{Module.captureEnemyFrame=window.__capture;});await page.locator('#start').click({noWaitAfter:true});
  await page.waitForFunction(()=>Module.state?.error||Module.state?.frame>=720,null,{timeout:90000});
  const state=await page.evaluate(()=>({error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),trace:window.__trace,captures:window.__captures,
   renderer:(()=>{const gl=Module.ctx,x=gl.getExtension('WEBGL_debug_renderer_info');return x?gl.getParameter(x.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);})()}));
  assert.equal(state.error,'');assert.equal(state.style,'Original');assert.equal(state.gl,0);assert(state.trace.length>650);
  let dashes=0,launches=0,chains=0,creep=0,childFrames=0;const shots=new Set();
  for(const {frame,probe:p} of state.trace){const a=p.actors.find(a=>a.entity===p.entity);
   for(const b of p.bullets.filter(b=>b.owner===p.entity)){shots.add(b.entity);assert(Number.isFinite(b.x)&&Number.isFinite(b.z));if(t.id==='217.3.0'){assert(Math.abs(b.radius-.22)<.001);assert(Math.abs(b.gravity-4.5)<.001);}}
   if(death&&frame>=660){assert(!a);assert.equal(p.kills,1);
    if(t.id!=='217.3.0'){const expected=t.id==='871.0.0'?[870,0]:[15,1];assert.equal(p.actors.filter(c=>c.type===expected[0]&&c.variant===expected[1]).length,2);assert(p.threats>=2);++childFrames;}
    continue;
   }
   assert(a&&a.slide);assert.equal(`${a.type}.${a.variant}.${a.subtype}`,t.id);
   assert(Number.isFinite(a.x)&&Number.isFinite(a.z));
   // Wet variants may occupy the ground-blocked river but may never cross solids.
   if(['217.3.0','870.0.0','871.0.0'].includes(t.id))assert(!p.swimBlocked);else assert(!p.groundBlocked);
   const stage=Math.min(p.sourceStage,4)+.8*Math.max(0,Math.min(p.sourceStage-5,5));
   const hp=t.id==='217.1.0'||t.id==='217.2.0'?9.6:t.id==='217.3.0'?(6+2*stage)*3.2:t.id==='870.0.0'?(3+stage)*3.2:(15+6*stage)*3.2;
   assert(Math.abs(a.maxHp-hp)<.02);
   dashes=Math.max(dashes,a.slide.dashes);launches=Math.max(launches,a.slide.launches);chains=Math.max(chains,a.slide.chains);creep=Math.max(creep,a.slide.creep);
   if(!natural){assert.equal(p.shots,0);if(t.id!=='220.1.0')assert.equal(p.hazards.length,0);}
   if(natural){assert(p.resident.natural);assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);}
  }
  assert(dashes>0);if(t.id==='870.0.0')assert(chains>0);if(t.id==='871.0.0')assert(launches>=2);if(t.id==='220.1.0')assert(creep>0);
  if(death&&t.id==='217.3.0'){assert.equal(shots.size,1);assert(state.captures['death-shot']);}if(childFrames)assert(childFrames>40);
  for(const [kind,c] of Object.entries(state.captures)){c.path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(c.path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;}
  assert.deepEqual(errors,[]);Object.assign(result,{pass:true,dashes,launches,chains,creep,childFrames,shots:shots.size,renderer:state.renderer,trace:state.trace,captures:state.captures});persist();console.log('PASS',t.name,JSON.stringify({dashes,launches,chains,creep,childFrames,shots:shots.size}));
 }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
