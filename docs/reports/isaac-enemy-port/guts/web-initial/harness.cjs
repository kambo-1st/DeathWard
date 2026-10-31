// Production WASM: isolated controllers and actual seeded floor residents.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_GUTS_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const headless=process.env.DEATHWARD_BROWSER_HEADFUL!=='1';
 const browser=await chromium.launch({headless,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 await page.addInitScript(()=>{
  window.__gutsCaptures={};
  window.__captureGuts=frame=>{
   const m=window.Module,p=m?.enemyProbe,a=p?.actors.find(a=>a.entity===p.entity),r=a?.guts;if(!r)return;
   const kind=r.charging?'charge':r.windup>=2?'windup':r.stops>0&&r.recovery>48?'impact':r.patches>8?'trail':r.ticks>30?'roll':null;
   if(!kind||window.__gutsCaptures[kind])return;
   const canvas=m.canvas||document.querySelector('canvas');
   window.__gutsCaptures[kind]={frame,probe:JSON.parse(JSON.stringify(p)),png:canvas.toDataURL('image/png')};
  };
 });
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({headless,checks,errors,
  scope:'Production isolated/seeded Guts controller and rendering checks; not full parity, balance or performance acceptance.'},null,2)+'\n');
 try {
  const cases=[{name:'guts',variant:0},{name:'scarred',variant:1},{name:'slog',variant:2},
   {name:'slog-river',variant:2,terrain:'river'},
   {name:'resident-guts',variant:0,seed:7,floor:3,room:3,context:3},
   {name:'resident-scarred',variant:1,seed:9,floor:6,room:5,context:0},
   {name:'resident-slog',variant:2,seed:19,floor:3,room:3,context:3}];
  for(const t of cases) {
   if(process.env.DEATHWARD_GUTS_CASES&&!process.env.DEATHWARD_GUTS_CASES.split(',').includes(t.name))continue;
   const natural=t.seed!==undefined;
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',
    scene:`${natural?'resident':'enemy'}-40.${t.variant}.0`,'enemy-camera-follow':''});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   else q.set('enemy-player-at','1:10:0');
   if(t.terrain)q.set('enemy-terrain',t.terrain);
   const result={...t,query:q.toString(),pass:false,samples:[],captures:{}};checks.push(result);console.log('START',t.name);persist();
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureGuts;});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   result.renderer=await page.evaluate(()=>{const gl=Module.ctx,e=gl.getExtension('WEBGL_debug_renderer_info');return e?gl.getParameter(e.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);});
   let previous,movement=0,charges=0,stops=0,patches=0,turns=0;
   for(let frame=4;frame<=(natural?240:t.variant===2?960:360);frame+=8) {
    await page.waitForFunction(n=>Module.state?.error||Module.state?.frame>=n,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,error:Module.state.error,gl:Module.ctx.getError(),style:Module.state.visualStyleName,p:Module.enemyProbe}));
    result.samples.push(s);assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(s.style,'Original');
    const a=s.p.actors.find(a=>a.entity===s.p.entity);assert(a?.guts,'dedicated actor is alive');
    assert.equal(a.type,40);assert.equal(a.variant,t.variant);assert(Math.abs(a.maxHp-(t.variant?89.6:80))<.01);
    assert(!s.p.groundBlocked,'body remains on walkable ground');assert(a.guts.ticks>0);
    if(natural){assert(s.p.resident.natural);assert.equal(s.p.resident.floor,t.floor);assert.equal(s.p.resident.room,t.room);assert.equal(s.p.resident.variant,t.context);}
    if(previous)movement+=Math.hypot(a.x-previous.x,a.z-previous.z);previous=a;
    charges=Math.max(charges,a.guts.charges);stops=Math.max(stops,a.guts.stops);patches=Math.max(patches,a.guts.patches);turns=Math.max(turns,a.guts.turns);
    if(frame>=180&&(natural||t.variant!==2||charges&&stops))break;
   }
   const captures=await page.evaluate(()=>window.__gutsCaptures);
   for(const [kind,c] of Object.entries(captures)) {
    const path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;
    result.captures[kind]={path,...c};
   }
   assert(movement>1,'actual contour travel');assert(Object.keys(captures).length>0,'draw-boundary capture');
   if(t.variant)assert(patches>0,'variant emits trail');else assert.equal(patches,0);
   if(t.variant===2&&!natural&&!t.terrain){assert(charges>0&&stops>0,'Slog acquires and ends charge');assert(captures.windup&&captures.charge&&captures.impact,'charge phases captured');}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,movement,charges,stops,patches,turns});console.log('PASS',t.name);persist();
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
