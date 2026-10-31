// Production WASM: actual player-triggered shots and seeded resident mirrors.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_MIRROR_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{
  window.__mirrorCaptures={};window.__captureMirror=frame=>{
   const p=Module.enemyProbe,a=p?.actors.find(a=>a.entity===p.entity);if(!a?.mirror)return;
   const kind=a.mirror.volleys>0&&frame>=63?'shot':frame>=35?'idle':null;
   if(!kind||window.__mirrorCaptures[kind])return;
   window.__mirrorCaptures[kind]={frame,probe:JSON.parse(JSON.stringify(p)),png:(Module.canvas||document.querySelector('canvas')).toDataURL('image/png')};
  };
 });
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Scoped Original-style production WASM mirror controllers, actual trigger input and natural seeded placement. Full parity, all-camera visuals, balance and performance remain open.'},null,2)+'\n');
 try{
  for(const t of [{name:'dople',variant:0},{name:'evil-twin',variant:1},
   {name:'resident-dople',variant:0,seed:14,floor:6,room:3},{name:'resident-evil-twin',variant:1,seed:13,floor:4,room:6}]) {
   const natural=t.seed!==undefined,q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${natural?'resident':'enemy'}-53.${t.variant}.0`,'enemy-camera-follow':''});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   else for(const f of [60,61,90,91,130,131])q.append('enemy-player-attack',`${f}:0:25`);
   const result={...t,pass:false,samples:[],captures:{}};checks.push(result);persist();console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureMirror;});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   result.renderer=await page.evaluate(()=>{const gl=Module.ctx,x=gl.getExtension('WEBGL_debug_renderer_info');return x?gl.getParameter(x.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);});
   let final;
   for(let frame=4;frame<=155;frame+=4) {
    await page.waitForFunction(n=>Module.state?.error||Module.state?.frame>=n,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),p:Module.enemyProbe}));result.samples.push(s);
    assert.equal(s.error,'');assert.equal(s.style,'Original');assert.equal(s.gl,0);
    const a=s.p.actors.find(a=>a.entity===s.p.entity);assert(a?.mirror,'dedicated mirror survives');assert.equal(a.maxHp,64);
    assert.equal(s.p.actors.filter(a=>a.mirror).length,1);assert(!s.p.flightBlocked);
    if(!t.variant)assert(!s.p.groundBlocked,'Dople must not be inside canyon terrain');
    if(s.frame>=10&&a.mirror.corrections===0){assert(Math.abs(a.x-a.mirror.desiredX)<.01);assert(Math.abs(a.z-a.mirror.desiredZ)<.01);}
    if(natural){assert(s.p.resident.natural);assert.equal(s.p.resident.floor,t.floor);assert.equal(s.p.resident.room,t.room);}
    if(s.frame<60||natural)assert.equal(a.mirror.volleys,0,'no autonomous firing');
    final=a;
   }
   if(!natural)assert.equal(final.mirror.volleys,t.variant?2:3,'three triggers, Twin rejects the middle trigger');
   const captures=await page.evaluate(()=>window.__mirrorCaptures);
   assert(captures.idle);if(!natural)assert(captures.shot);
   for(const [kind,c] of Object.entries(captures)){const path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;result.captures[kind]={path,...c};}
   assert.deepEqual(errors,[]);result.pass=true;persist();console.log('PASS',t.name);
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
