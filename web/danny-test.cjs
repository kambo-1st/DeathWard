// Actual production-WASM controller/offspring and seeded-population evidence.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_DANNY_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{window.__trace=[];window.__captures={};window.__capture=frame=>{
  if(frame>1200)return;const p=Module.enemyProbe;if(!p)return;
  window.__trace.push({frame,probe:JSON.parse(JSON.stringify(p))});
  const a=p.actors.find(a=>a.entity===p.entity),r=a?.danny,kinds=[];
  if(r?.frame===-1&&r.attacks===0)kinds.push('walking');
  if(r?.frame>=6&&r.frame<12)kinds.push('windup');
  if(r?.attacks===1&&p.actors.some(a=>a.rockSpider?.height<0))kinds.push('first-volley');
  if(r?.attacks>=2)kinds.push('repeat-volley');
  if(frame>=600&&p.actors.some(a=>a.summoner===p.entity&&a.rockSpider?.phase===2))kinds.push('living-offspring');
  for(const k of kinds)if(!window.__captures[k])window.__captures[k]={frame,png:Module.canvas.toDataURL('image/png')};
 };});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Scoped Original-style production WASM Danny/Coal Boy behavior and actual offspring; not full acceptance.'},null,2)+'\n');
 try {
  for(const t of JSON.parse(process.env.DEATHWARD_DANNY_ENTRIES)) {
   const result={...t,pass:false};checks.push(result);persist();console.log('START',t.name);
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${t.natural?'resident':'enemy'}-820.${t.variant}.0`,'enemy-camera-follow':''});
   if(t.natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__capture;});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(limit=>Module.state?.error||Module.state?.frame>=limit,t.frames,{timeout:180000});
   const state=await page.evaluate(()=>({error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),trace:window.__trace,captures:window.__captures,
    renderer:(()=>{const gl=Module.ctx,x=gl.getExtension('WEBGL_debug_renderer_info');return x?gl.getParameter(x.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);})()}));
   for(const [kind,c] of Object.entries(state.captures)){c.path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(c.path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;}
   Object.assign(result,{renderer:state.renderer,trace:state.trace,captures:state.captures});persist();
   assert.equal(state.error,'');assert.equal(state.style,'Original');assert.equal(state.gl,0);assert(state.trace.length>t.frames-30);
   let attacks=0,maxOwned=0,thrown=0,coals=0,peakProjectiles=0,firstVolley=null;
   for(const {frame,probe:p} of state.trace) {
    const a=p.actors.find(a=>a.entity===p.entity),owned=p.actors.filter(a=>a.summoner===p.entity);
    if(a){assert.equal(a.type,820);assert.equal(a.variant,t.variant);assert(a.danny);attacks=Math.max(attacks,a.danny.attacks);assert(!p.groundBlocked);}
    maxOwned=Math.max(maxOwned,owned.length);assert(owned.length<=(t.variant===0?2:1));
    thrown=Math.max(thrown,p.actors.filter(a=>a.rockSpider?.height<0).length);
    coals=Math.max(coals,p.actors.filter(a=>a.type===33&&a.variant===11).length);peakProjectiles=Math.max(peakProjectiles,p.bullets.length);
    if(!firstVolley&&a?.danny.attacks===1){firstVolley={frame,owned:owned.map(a=>[a.type,a.variant,a.subtype]),coals:p.actors.filter(a=>a.type===33&&a.variant===11).length};}
    if(t.natural){assert(p.resident.natural);assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);assert.deepEqual(p.resident.source,[820,t.variant,0]);}
   }
   assert(attacks>=1&&thrown>0&&firstVolley);
   if(!t.natural){assert(attacks>=2);assert.equal(firstVolley.owned.length,t.variant===0?2:1);assert(firstVolley.owned.every(x=>x[0]===818&&x[1]===(t.variant===0?0:2)));if(t.variant===1){assert.equal(firstVolley.coals,3);assert(coals>=4);}else assert(peakProjectiles>=4);}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,attacks,maxOwned,thrown,coals,peakProjectiles,firstVolley});persist();console.log('PASS',t.name);
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
