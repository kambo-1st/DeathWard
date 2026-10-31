// Scoped production-WASM behavior and natural population evidence.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_HARDY_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{window.__trace=[];window.__captures={};window.__capture=frame=>{
  if(frame>1800)return;const p=Module.enemyProbe;if(!p)return;
  window.__trace.push({frame,probe:JSON.parse(JSON.stringify(p))});
  const a=p.actors.find(a=>a.entity===p.entity),r=a?.hardy,kinds=[];
  if(r?.phase===0&&r.impacts===0)kinds.push('intact');
  if(r?.phase===1&&r.frame>=24)kinds.push('windup');
  if(r?.phase===2)kinds.push('charge');
  if(r?.impacts===1)kinds.push('first-impact');
  if(r?.impacts===2)kinds.push('second-impact');
  if(p.actors.some(a=>a.type===818&&a.rockSpider?.height<0))kinds.push('thrown-spiders');
  if(!a&&p.actors.some(a=>a.type===217))kinds.push('death-dip');
  for(const k of kinds)if(!window.__captures[k])window.__captures[k]={frame,png:Module.canvas.toDataURL('image/png')};
 };});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Scoped Original-style production WASM Hardy controller, impacts and offspring. Not full acceptance.'},null,2)+'\n');
 try {
  for(const t of JSON.parse(process.env.DEATHWARD_HARDY_ENTRIES)) {
   const result={...t,pass:false};checks.push(result);persist();console.log('START',t.name);
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${t.natural?'resident':'enemy'}-826.0.0`,'enemy-camera-follow':''});
   if(t.natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   if(t.death)q.set('enemy-hit','80:10000');
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__capture;});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(limit=>Module.state?.error||Module.state?.frame>=limit,t.frames,{timeout:180000});
   const state=await page.evaluate(()=>({error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),trace:window.__trace,captures:window.__captures,
    renderer:(()=>{const gl=Module.ctx,x=gl.getExtension('WEBGL_debug_renderer_info');return x?gl.getParameter(x.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);})()}));
   for(const [kind,c] of Object.entries(state.captures)){c.path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(c.path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;}
   Object.assign(result,{renderer:state.renderer,trace:state.trace,captures:state.captures});persist();
   assert.equal(state.error,'');assert.equal(state.style,'Original');assert.equal(state.gl,0);assert(state.trace.length>t.frames-30);
   let impacts=0,launches=0,thrown=0,dips=0,shots=0;const phases=new Set();
   for(const {frame,probe:p} of state.trace) {
    const a=p.actors.find(a=>a.entity===p.entity);
    if(a){assert.equal(a.type,826);assert(a.hardy);phases.add(a.hardy.phase);impacts=Math.max(impacts,a.hardy.impacts);launches=Math.max(launches,a.hardy.launches);assert(!p.groundBlocked);}
    thrown=Math.max(thrown,p.actors.filter(a=>a.type===818&&a.rockSpider?.height<0).length);
    const children=p.actors.filter(a=>a.type===217);dips=Math.max(dips,children.length);shots=Math.max(shots,p.bullets.length);
    if(t.death&&frame>=80){assert(!a);assert.equal(p.kills,1);assert.equal(children.length,1);assert(Math.abs(children[0].maxHp-25.6)<.02);assert.equal(thrown,0);}
    if(t.natural){assert(p.resident.natural);assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);assert.deepEqual(p.resident.source,[826,0,0]);}
   }
   if(!t.death){assert(launches>0&&phases.has(1)&&phases.has(2));if(!t.natural){assert(impacts>=2);assert(thrown>=2&&thrown<=3);assert.equal(dips,1);assert(shots>=8);}}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,impacts,launches,thrown,dips,shots,phases:[...phases],renderer:state.renderer,trace:state.trace,captures:state.captures});persist();console.log('PASS',t.name);
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
