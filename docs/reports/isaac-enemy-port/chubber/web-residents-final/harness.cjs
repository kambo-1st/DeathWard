// Actual seeded populations: no injected enemy or replacement content.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_VIS_RESIDENT_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const headless=process.env.DEATHWARD_BROWSER_HEADFUL!=='1';
 const browser=await chromium.launch({headless,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 await page.addInitScript(()=>{
  window.__residentCaptures={};
  window.__captureResident=frame=>{
   const m=window.Module,p=m?.enemyProbe,a=p?.actors.find(a=>a.entity===p.entity);if(!a?.vis)return;
   const child=p.actors.find(e=>e.returningBody&&e.componentOwner===a.entity);
   const attack=p.hazards.some(h=>h.owner===a.entity&&h.ownedBeam&&h.fade?.age<0)||child?.returningBody.frame>=5;
   const kind=attack?'attack':a.vis.frame>10&&!a.vis.fired?'windup':frame>120?'population':null;
   if(!kind||window.__residentCaptures[kind])return;
   const canvas=m.canvas||document.querySelector('canvas');
   window.__residentCaptures[kind]={frame,probe:JSON.parse(JSON.stringify(p)),png:canvas.toDataURL('image/png')};
  };
 });
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({headless,checks,errors,
  scope:'Production seeded population, controller activation and rendering checks; not final mixed-floor balance or performance acceptance.'},null,2)+'\n');
 try {
  for(const t of [{variant:0,seed:0,floor:4,room:1},{variant:2,seed:0,floor:5,room:7},
   {variant:3,seed:1,floor:6,room:2},{variant:1,seed:4,floor:5,room:3}]) {
   const name=`resident-${t.variant}`,q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',
    scene:`resident-39.${t.variant}.0`,'resident-seed':t.seed,'resident-floor':t.floor,'enemy-camera-follow':''});
   const result={name,...t,query:q.toString(),pass:false,samples:[],captures:{}};checks.push(result);console.log('START',name);persist();
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureResident;});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   result.renderer=await page.evaluate(()=>{const gl=Module.ctx,e=gl.getExtension('WEBGL_debug_renderer_info');return e?gl.getParameter(e.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);});
   let previous,movement=0,volleys=0;
   for(let f=4;f<=720;f+=8) {
    await page.waitForFunction(n=>Module.state?.error||Module.state?.frame>=n,f,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,error:Module.state.error,gl:Module.ctx.getError(),style:Module.state.visualStyleName,p:Module.enemyProbe}));
    result.samples.push(s);assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(s.style,'Original');
    assert.equal(s.p.resident.natural,true);assert.equal(s.p.resident.floor,t.floor);assert.equal(s.p.resident.room,t.room);
    const a=s.p.actors.find(a=>a.entity===s.p.entity);assert(a?.vis,'actual dedicated resident remains alive');
    assert.equal(a.type,39);assert.equal(a.variant,t.variant);assert(Math.abs(a.maxHp-(t.variant===3?70.4:80))<.01);
    assert(!s.p.groundBlocked,'resident body remains on walkable ground');assert(a.vis.ticks>0);
    if(previous)movement+=Math.hypot(a.x-previous.x,a.z-previous.z);previous=a;volleys=Math.max(volleys,a.vis.volleys);
    if(f>240&&volleys>0)break;
   }
   const captures=await page.evaluate(()=>window.__residentCaptures);
   for(const [kind,c] of Object.entries(captures)) {
    const path=`${out}/${name}-${kind}.png`;fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));
    delete c.png;result.captures[kind]={path,...c};
   }
   assert(movement>.1,'actual cardinal movement');assert(volleys>0,'real attack in generated room');
   assert(captures.attack,'draw-boundary attack capture');assert.deepEqual(errors,[]);
   Object.assign(result,{pass:true,movement,volleys});console.log('PASS',name);persist();
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
