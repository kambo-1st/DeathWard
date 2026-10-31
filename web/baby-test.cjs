// Production WASM Baby controllers, actual residents, and draw-boundary captures.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_BABY_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const headless=process.env.DEATHWARD_BROWSER_HEADFUL!=='1',renderers=[];
 const browser=await chromium.launch({headless,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 await page.addInitScript(()=>{
  window.__babyCaptures={};
  window.__captureBabyFrame=frame=>{
   const m=window.Module,p=m?.enemyProbe,a=p?.actors.find(a=>a.entity===p.entity),r=a?.baby;
   if(!r)return;
   const kind=r.phase===1&&r.visibility===0?'vanish':r.phase===2&&r.visibility===1?'appear':
    r.phase===3?'dash-windup':r.phase===4?'dash':r.fired&&r.attackFrame>=(a.variant===3?19:13)?'flight':
    r.fired?'shot':r.attackFrame>=0?'attack':'ready';
   if(window.__babyCaptures[kind])return;
   const canvas=m.canvas||document.querySelector('canvas'),sample=document.createElement('canvas');
   sample.width=sample.height=16;const ctx=sample.getContext('2d');ctx.drawImage(canvas,0,0,16,16);
   const pixels=ctx.getImageData(0,0,16,16).data;let min=255,max=0;
   for(let i=0;i<pixels.length;i+=4){min=Math.min(min,pixels[i]);max=Math.max(max,pixels[i]);}
   window.__babyCaptures[kind]={frame,probe:JSON.parse(JSON.stringify(p)),colorRange:max-min,png:canvas.toDataURL('image/png')};
  };
 });
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({headless,renderers,checks,errors,
  scope:'Production build behavior and draw-boundary captures; generated cases preserve entire seeded population. Partial acceptance only.'},null,2)+'\n');
 const witnesses=process.env.DEATHWARD_BABY_WITNESSES?JSON.parse(fs.readFileSync(process.env.DEATHWARD_BABY_WITNESSES,'utf8')):[];
 const cases=[{name:'normal',variant:0,teleport:true},{name:'angelic',variant:1,teleport:true},
  {name:'small',variant:1,subtype:1,teleport:true},{name:'wrinkly',variant:3,side:'diagonal',dash:true},
  {name:'normal-cover',variant:0,terrain:'cover'},{name:'angelic-river',variant:1,terrain:'river'},
  ...witnesses.map(w=>({...w,name:`resident-${w.variant}-seed-${w.seed}-floor-${w.floor}`}))];
 try {
  for(const t of cases) {
   if(process.env.DEATHWARD_BABY_CASES&&!process.env.DEATHWARD_BABY_CASES.split(',').includes(t.name))continue;
   const natural=t.seed!==undefined,q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',
    'enemy-camera-follow':'',scene:`${natural?'resident':'enemy'}-38.${t.variant}.${t.subtype||0}`});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   if(t.terrain)q.set('enemy-terrain',t.terrain);if(t.side)q.set('enemy-player-side',t.side);
   const result={name:t.name,witness:t,pass:false,samples:[],captures:{}};checks.push(result);console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureBabyFrame;});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   const renderer=await page.evaluate(()=>{const gl=Module.ctx,e=gl.getExtension('WEBGL_debug_renderer_info');return e?gl.getParameter(e.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);});
   renderers.push({name:t.name,renderer});console.log('RENDERER',renderer);persist();
   let previous,movement=0,shots=0,teleports=0,dashes=0;
   for(let f=4;f<=720;f+=6) {
    await page.waitForFunction(n=>Module.state?.error||Module.state?.frame>=n,f,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,error:Module.state.error,gl:Module.ctx.getError(),style:Module.state.visualStyleName,p:Module.enemyProbe}));
    result.samples.push(s);assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(s.style,'Original');assert.equal(s.p.resident.natural,natural);
    if(natural){assert.equal(s.p.resident.floor,t.floor);assert.equal(s.p.resident.room,t.room);}
    const a=s.p.actors.find(a=>a.entity===s.p.entity);assert(a?.baby,'dedicated living actor');
    assert.equal(a.type,38);assert.equal(a.variant,t.variant);assert(Math.abs(a.maxHp-(t.subtype?51.2:80))<.01);
    if(a.baby.phase!==1)assert(!s.p.flightBlocked,'physical flight legality outside Vanish');
    if(previous) {
     movement+=Math.hypot(a.x-previous.x,a.z-previous.z);
     if(a.baby.phase===4&&previous.baby.phase===4&&a.baby.dashes===previous.baby.dashes)
      assert.deepEqual([a.baby.dx,a.baby.dz],[previous.baby.dx,previous.baby.dz],'committed dash direction');
    }
    previous=a;shots=Math.max(shots,a.baby.volleys);teleports=Math.max(teleports,a.baby.teleports);dashes=Math.max(dashes,a.baby.dashes);
    if((f-4)%120===0){console.log('FRAME',t.name,s.frame,'volleys',shots,'teleports',teleports,'dashes',dashes);persist();}
    if(s.frame>=360&&(!t.teleport||teleports>0)&&(!t.dash||dashes>0))break;
   }
   const captures=await page.evaluate(()=>window.__babyCaptures);
   for(const [kind,c] of Object.entries(captures)) {
    assert(c.colorRange>40,'real drawn scene');const path=`${out}/${t.name}-${kind}.png`;
    fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;result.captures[kind]={path,...c};
   }
   assert(movement>.1,'actual movement');if(!t.terrain||t.terrain==='river')assert(shots>0,'real attack');
   if(t.teleport){assert(teleports>0,'actual teleport');assert(captures.vanish&&captures.appear,'exact visible phase captures');}
   if(t.dash){assert(dashes>0);assert(captures.dash);}
   if(t.variant===3)assert.equal(teleports,0,'Wrinkly never teleports');
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,movement,shots,teleports,dashes});console.log('PASS',t.name);persist();
  }
 }finally {
  persist();
  await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
