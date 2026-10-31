// Production WASM: Dinga, Squirt, Dip, exact offspring and seeded residents.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_DINGA_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{
  window.__dingaCaptures={};window.__dingaTrace=[];window.__captureDinga=frame=>{
   if(frame>720)return;const p=Module.enemyProbe;if(!p)return;
   const a=p.actors.find(a=>a.entity===p.entity),snapshot=JSON.parse(JSON.stringify(p));
   window.__dingaTrace.push({frame,probe:snapshot});const r=a?.memBrain,s=a?.slide;
   const kinds=[];
   if(!a&&frame>=665)kinds.push('children');
   if(r&&a.lift>.7)kinds.push('hop');
   if(r&&p.bullets.some(b=>b.owner===p.entity)&&r.frame>=32&&r.frame<=35)kinds.push('ring');
   if(r?.births&&p.actors.some(a=>a.type===217))kinds.push('dips');
   if(s?.phase===1&&s.frame>=30&&s.frame<=34)kinds.push('windup');
   if(s?.phase===2&&Math.hypot(a.vx,a.vz)>6)kinds.push('slide');
   for(const kind of kinds)if(!window.__dingaCaptures[kind])window.__dingaCaptures[kind]={frame,probe:snapshot,
    png:(Module.canvas||document.querySelector('canvas')).toDataURL('image/png')};
  };
 });
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,
  scope:'Scoped production WASM behavior/placement and Original-style captures; full acceptance remains open.'},null,2)+'\n');
 try{
  const entries=JSON.parse(process.env.DEATHWARD_DINGA_ENTRIES||'[{"name":"dip","id":"217.0.0"},{"name":"squirt","id":"220.0.0"},{"name":"dinga","id":"223.0.0"}]');
  for(const t of entries) {
   const natural=!!t.natural,q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${natural?'resident':'enemy'}-${t.id}`,'enemy-camera-follow':''});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}else if(t.id!=='217.0.0')q.set('enemy-hit','660:10000');
   const result={...t,pass:false};checks.push(result);persist();console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureDinga;});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   await page.waitForFunction(()=>Module.state?.error||Module.state?.frame>=720,null,{timeout:90000});
   const state=await page.evaluate(()=>({error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),trace:window.__dingaTrace,captures:window.__dingaCaptures,
    renderer:(()=>{const gl=Module.ctx,x=gl.getExtension('WEBGL_debug_renderer_info');return x?gl.getParameter(x.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);})()}));
   assert.equal(state.error,'');assert.equal(state.style,'Original');assert.equal(state.gl,0);assert(state.trace.length>650);
   let volleys=0,births=0,dashes=0,childFrames=0,launchFrameSamples=0,previous=null;const bullets=new Set();
   for(const {frame,probe:p} of state.trace) {
    const a=p.actors.find(a=>a.entity===p.entity);
    if(!natural&&t.id!=='217.0.0'&&frame>=660) {
     assert(!a,'ordinary damage removes parent');assert.equal(p.kills,1);
     const expected=t.id==='223.0.0'?220:217;
     assert.equal(p.actors.filter(c=>c.type===expected&&c.variant===0&&c.slide).length,2,'two real death children');
     assert(p.threats>=2);++childFrames;continue;
    }
    assert(a);assert.equal(`${a.type}.${a.variant}.${a.subtype}`,t.id);assert(!p.groundBlocked,'grounded body remains legal');
    const stage=Math.min(p.sourceStage,4)+.8*Math.max(0,Math.min(p.sourceStage-5,5));
    const hp=a.type===217?(3+stage)*3.2:a.type===220?(15+6*stage)*3.2:198.4;assert(Math.abs(a.maxHp-hp)<.02);
    if(a.memBrain) {
     const r=a.memBrain;volleys=Math.max(volleys,r.volleys);births=Math.max(births,r.births);
     if(!natural)assert.equal(p.shots,r.volleys*8);
     if(previous?.memBrain&&previous.memBrain.frame>=0&&r.frame>=0&&r.frame>previous.memBrain.frame)
      assert(Math.abs(r.frame-previous.memBrain.frame-1.5)<.001,'Dinga45FPS animation advance');
    } else {
     assert(a.slide);dashes=Math.max(dashes,a.slide.dashes);
     if(a.type===220&&a.slide.phase===1&&a.slide.frame===36)++launchFrameSamples;
     if(!natural){assert.equal(p.shots,0);assert.equal(p.hazards.length,0);}
    }
    for(const b of p.bullets.filter(b=>b.owner===p.entity)){bullets.add(b.entity);assert(Math.abs(b.gravity-4.5)<.001);assert(Math.abs(b.radius-.308)<.001);}
    if(natural){assert(p.resident.natural);assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);}
    previous=a;
   }
   if(t.id==='223.0.0'){assert(volleys+births>0);if(!natural){assert(births>0);assert(volleys>0);assert(bullets.size>0);}}
   else {assert(dashes>0);if(t.id==='220.0.0')assert(launchFrameSamples>0);}
   if(!natural&&t.id!=='217.0.0'){assert(childFrames>40);assert(state.captures.children);}
   for(const [kind,c] of Object.entries(state.captures)){const path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;c.path=path;}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,volleys,births,dashes,launchFrameSamples,childFrames,actualShots:bullets.size,
    renderer:state.renderer,trace:state.trace,captures:state.captures});persist();console.log('PASS',t.name,JSON.stringify({volleys,births,dashes,launchFrameSamples,childFrames}));
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
