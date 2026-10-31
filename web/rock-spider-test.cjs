// Scoped production WASM checks; exact source mechanics are also tested natively.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_ROCK_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{window.__trace=[];window.__captures={};window.__capture=frame=>{
  if(frame>720)return;const p=Module.enemyProbe;if(!p)return;
  const copy=()=>JSON.parse(JSON.stringify(p));window.__trace.push({frame,probe:copy()});
  const a=p.actors.find(a=>a.entity===p.entity),r=a?.rockSpider,kinds=[];
  if(r?.phase===0)kinds.push('rock');
  if(r?.phase===1&&r.frame>=10)kinds.push('reveal');
  if(r?.phase===2&&r.selections>0)kinds.push('skitter');
  if(a?.type===85)kinds.push('inner-spider');
  if(p.actors.some(a=>a.type===33&&a.variant===11))kinds.push('hot-coal');
  for(const kind of kinds)if(!window.__captures[kind])window.__captures[kind]={frame,probe:copy(),png:Module.canvas.toDataURL('image/png')};
 };});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Scoped Original-style production WASM movement, reveal, death morph, hot-coal birth, fire morph and actual seeded subtype placement. Full acceptance remains open.'},null,2)+'\n');
 try {
  const entries=JSON.parse(process.env.DEATHWARD_ROCK_ENTRIES);assert(entries.length);
  for(const t of entries) {
   const result={...t,pass:false};checks.push(result);persist();console.log('START',t.name);
   const natural=!!t.natural,coal=t.id.startsWith('818.2.');
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${natural?'resident':'enemy'}-${t.id}`,'enemy-camera-follow':''});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   if(t.death){q.set('enemy-hit','660:10000');if(!coal)q.append('enemy-hit','710:10000');if(coal)q.set('enemy-count','2');}
   if(t.flame){q.set('enemy-flame-hit','120:1000');q.set('enemy-burn-hit','140:1');}
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__capture;});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(()=>Module.state?.error||Module.state?.frame>=720,null,{timeout:90000});
   const state=await page.evaluate(()=>({error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),trace:window.__trace,captures:window.__captures,
    renderer:(()=>{const gl=Module.ctx,x=gl.getExtension('WEBGL_debug_renderer_info');return x?gl.getParameter(x.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);})()}));
   assert.equal(state.error,'');assert.equal(state.style,'Original');assert.equal(state.gl,0);assert(state.trace.length>650);
   let selections=0,cycles=0,inner=0,embers=0,fire=0;const phases=new Set();
   for(const {frame,probe:p} of state.trace) {
    const a=p.actors.find(a=>a.entity===p.entity);
    if(t.death&&frame>=660) {
     if(coal){assert(!a);assert.equal(p.kills,1);const child=p.actors.find(c=>c.type===33&&c.variant===11);assert(child);assert.equal(child.subtype,Number(t.id.split('.')[2]));assert(child.environment&&child.rockSpider);assert(child.hp>1&&child.hp<=15);++embers;}
     else if(frame<710){assert(a&&a.type===85&&a.spider);assert(Math.abs(a.maxHp-20.8)<.02);assert.equal(p.kills,0);assert(p.threats>=1);++inner;}
     else {assert(!a);assert.equal(p.kills,1);}
     continue;
    }
    assert(a&&a.rockSpider&&a.type===818);assert(a.subtype>=1&&a.subtype<=3);assert(!p.groundBlocked);
    if(t.id.endsWith('.0'))assert.equal(a.variant,0);else assert.equal(a.subtype,Number(t.id.split('.')[2]));
    if(t.flame&&frame>=120){assert.equal(a.variant,2);assert(Math.abs(a.hp-(frame>=140?47:48))<.02);++fire;}
    else {assert.equal(a.variant,coal?2:0);assert(Math.abs(a.maxHp-(coal?48:38.4))<.02);}
    phases.add(a.rockSpider.phase);selections=Math.max(selections,a.rockSpider.selections);cycles=Math.max(cycles,a.rockSpider.cycles);
    assert(Number.isFinite(a.x)&&Number.isFinite(a.z));
    if(!natural)assert.equal(p.shots,0);
    else {assert(p.resident.natural);assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);assert.deepEqual(p.resident.source,[818,coal?2:0,0]);}
   }
   assert(phases.has(0)&&phases.has(1)&&phases.has(2));assert(selections>0&&cycles>0);
   if(t.death)assert(coal?embers>=50:inner>=40);if(t.flame)assert(fire>500);
   for(const [kind,c] of Object.entries(state.captures)){c.path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(c.path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,selections,cycles,inner,embers,fire,renderer:state.renderer,trace:state.trace,captures:state.captures});persist();console.log('PASS',t.name);
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
