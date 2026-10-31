// Production WASM Lump phases, visibility and actual seeded late-floor placement.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_LUMP_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{
  window.__lumpCaptures={};window.__lumpTrace=[];window.__captureLump=frame=>{
   if(frame>420)return;
   const p=Module.enemyProbe,a=p?.actors.find(a=>a.entity===p.entity);if(!p)return;
   const snapshot=JSON.parse(JSON.stringify(p));window.__lumpTrace.push({frame,probe:snapshot});
   const r=a?.lump,captures=window.__lumpCaptures;
   const kind=!a&&frame>=400?'death':r?.phase===1&&r.frame>=4?'spit':r?.phase===2&&r.frame>=6?'hide':
    r?.phase===3?'hidden':r?.phase===4&&r.frame>=6?'appear':null;
   if(!kind||captures[kind])return;
   captures[kind]={frame,probe:snapshot,png:(Module.canvas||document.querySelector('canvas')).toDataURL('image/png')};
  };
 });
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Scoped Original-style production WASM phases, collision visibility, death and one natural resident. Full status, balance and performance gates remain open.'},null,2)+'\n');
 try{
  for(const t of [{name:'lump'},{name:'resident-lump',seed:0,floor:5,room:2}]) {
   if(process.env.DEATHWARD_LUMP_CASES&&!process.env.DEATHWARD_LUMP_CASES.split(',').includes(t.name))continue;
   const natural=t.seed!==undefined,q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${natural?'resident':'enemy'}-56.0.0`,'enemy-camera-follow':''});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}else q.set('enemy-execute','400:1000');
   const result={...t,pass:false};checks.push(result);persist();console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureLump;});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   await page.waitForFunction(()=>Module.state?.error||Module.state?.frame>=420,null,{timeout:90000});
   const state=await page.evaluate(()=>({error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),trace:window.__lumpTrace,captures:window.__lumpCaptures,
    renderer:(()=>{const gl=Module.ctx,x=gl.getExtension('WEBGL_debug_renderer_info');return x?gl.getParameter(x.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);})()}));
   assert.equal(state.error,'');assert.equal(state.style,'Original');assert.equal(state.gl,0);assert(state.trace.length>350);
   const phases=new Set();let volleys=0,burrows=0,relocations=0;
   for(const {frame,probe:p} of state.trace) {
    const a=p.actors.find(a=>a.entity===p.entity);
    if(!natural&&frame>=400){assert(!a,'execution removes even buried enemy');assert.equal(p.threats,0);assert.equal(p.kills,1);continue;}
    assert(a?.lump,'dedicated controller');assert.equal(a.maxHp,96);const r=a.lump;phases.add(r.phase);
    if(!r.intangible)assert(!p.groundBlocked,'visible body has legal terrain footprint');
    if(r.phase===3){assert(r.intangible);assert.equal(r.visibility,0);assert(p.threats>0);}
    if(r.phase===2)assert(!r.intangible,'Hide animation remains collidable');
    if(r.phase===4&&r.frame>0)assert(!r.intangible,'Appear collision returns after transition update');
    volleys=Math.max(volleys,r.volleys);burrows=Math.max(burrows,r.burrows);relocations=Math.max(relocations,r.relocations);
    if(!natural)assert.equal(p.shots,r.volleys*3,'real projectile count matches complete three-shot packets');
    else{assert(p.resident.natural);assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);}
   }
   assert(volleys>0&&burrows>0,'real attacks and hidden phases occur');
   assert(state.captures.spit&&state.captures.hide&&state.captures.hidden);
   if(!natural)assert(state.captures.death);
   for(const [kind,c] of Object.entries(state.captures)){const path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;c.path=path;}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,phases:[...phases],volleys,burrows,relocations,renderer:state.renderer,trace:state.trace,captures:state.captures});persist();console.log('PASS',t.name,JSON.stringify({volleys,burrows,relocations}));
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
