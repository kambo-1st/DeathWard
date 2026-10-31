// Production WASM Vis beam controllers. Exact draw-boundary captures; no injected state.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_VIS_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[],renderers=[];
 const headless=process.env.DEATHWARD_BROWSER_HEADFUL!=='1';
 const browser=await chromium.launch({headless,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 await page.addInitScript(()=>{
  window.__visCaptures={};
  window.__captureVisFrame=frame=>{
   const m=window.Module,p=m?.enemyProbe,a=p?.actors.find(a=>a.entity===p.entity),r=a?.vis;if(!r)return;
   const beams=p.hazards.filter(h=>h.owner===p.entity&&h.ownedBeam);
   const kind=beams.some(h=>h.fade?.age>=0)?'fade':beams.length?'beam':r.frame>10&&!r.fired?'windup':'walk';
   if(window.__visCaptures[kind])return;
   const canvas=m.canvas||document.querySelector('canvas'),sample=document.createElement('canvas');
   sample.width=sample.height=16;const ctx=sample.getContext('2d');ctx.drawImage(canvas,0,0,16,16);
   const pixels=ctx.getImageData(0,0,16,16).data;let min=255,max=0;
   for(let i=0;i<pixels.length;i+=4){min=Math.min(min,pixels[i]);max=Math.max(max,pixels[i]);}
   window.__visCaptures[kind]={frame,probe:JSON.parse(JSON.stringify(p)),colorRange:max-min,png:canvas.toDataURL('image/png')};
  };
 });
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({headless,renderers,checks,errors,
  scope:'Production isolated controller and rendering smoke only; not full visual/balance/performance acceptance.'},null,2)+'\n');
 try {
  for(const t of [{name:'vis',variant:0,beams:1},{name:'double',variant:1,beams:2},{name:'scarred',variant:3,beams:4},
   {name:'vis-cover',variant:0,beams:1,terrain:'cover'},{name:'double-river',variant:1,beams:2,terrain:'river'}]) {
   if(process.env.DEATHWARD_VIS_CASES&&!process.env.DEATHWARD_VIS_CASES.split(',').includes(t.name))continue;
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',
    scene:`enemy-39.${t.variant}.0`,'enemy-camera-follow':''});if(t.terrain)q.set('enemy-terrain',t.terrain);
   const result={name:t.name,pass:false,samples:[],captures:{}};checks.push(result);console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureVisFrame;});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   const renderer=await page.evaluate(()=>{const gl=Module.ctx,e=gl.getExtension('WEBGL_debug_renderer_info');return e?gl.getParameter(e.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);});
   renderers.push({name:t.name,renderer});console.log('RENDERER',renderer);persist();let volleys=0;
   for(let f=4;f<=420;f+=6) {
    await page.waitForFunction(n=>Module.state?.error||Module.state?.frame>=n,f,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,error:Module.state.error,gl:Module.ctx.getError(),style:Module.state.visualStyleName,p:Module.enemyProbe}));
    result.samples.push(s);assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(s.style,'Original');
    const a=s.p.actors.find(a=>a.entity===s.p.entity);assert(a?.vis,'dedicated living controller');
    assert.equal(a.type,39);assert.equal(a.variant,t.variant);assert(Math.abs(a.maxHp-(t.variant===3?70.4:80))<.01);
    const beams=s.p.hazards.filter(h=>h.owner===a.entity&&h.ownedBeam);
    if(beams.length) {
     assert.equal(beams.length,t.beams,'complete beam packet');
     for(const h of beams){assert.equal(h.delay,0);assert.equal(h.ownedBeam.immuneType,39);assert(Math.abs(h.duration-32/30)<1e-5);}
    }
    volleys=Math.max(volleys,a.vis.volleys);
    if((f-4)%120===0){console.log('FRAME',t.name,s.frame,'volleys',volleys);persist();}
    if(s.frame>240&&volleys>0)break;
   }
   const captures=await page.evaluate(()=>window.__visCaptures);
   for(const [kind,c] of Object.entries(captures)) {
    assert(c.colorRange>40,'actual rendered scene');const path=`${out}/${t.name}-${kind}.png`;
    fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;result.captures[kind]={path,...c};
   }
   assert(volleys>0,'real laser attack');assert(captures.windup&&captures.beam&&captures.fade,'draw-boundary attack phases');
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,volleys});console.log('PASS',t.name);persist();
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
