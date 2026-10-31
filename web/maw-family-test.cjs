const {chromium}=require('playwright');
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_MAW_OUTPUT||'artifacts/maw-family';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const cases=[{name:'maw',variant:0},{name:'red-maw',variant:1},{name:'psychic-maw',variant:2}];
 if(process.env.DEATHWARD_MAW_WITNESSES)for(const w of JSON.parse(fs.readFileSync(process.env.DEATHWARD_MAW_WITNESSES)))cases.push({...w,name:'natural-'+cases[w.variant].name});
 try {
  for(const t of cases) {
   const natural=t.seed!==undefined;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-26.${t.variant}.0`});
   if(natural){params.set('resident-seed',t.seed);params.set('resident-floor',t.floor);}
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
   console.log('START',t.name,'browser',await browser.version());
   console.log('GL',await page.evaluate(()=>{const gl=Module.ctx,ext=gl.getExtension('WEBGL_debug_renderer_info');return ext?gl.getParameter(ext.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);}));
   const samples=[];let fired=false,child=false,travel=0,previous,captured=false;
   for(let frame=10;frame<=360;frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,p:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));samples.push(s);
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);const p=s.p;
    assert.equal(p.type,26);assert.equal(p.variant,t.variant);assert.equal(p.resident.natural,natural);assert(Math.abs(p.hp-64)<.01);
    if(natural){assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);}
    if(previous)travel+=Math.hypot(p.x-previous.x,p.z-previous.z);previous=p;
    for(const b of p.bullets.filter(b=>b.owner===p.entity)) {
     assert.notEqual(t.variant,1,'Red Maw has no live projectiles');fired=true;
     assert.equal(b.sourceHoming,t.variant===2);assert(Math.abs(b.radius-(t.variant===2?.33:.22))<.001);assert.equal(b.damage,t.variant===2?20:10);
     if(t.variant===0) {
      const speed=Math.hypot(b.vx,b.vz);
      if(natural&&p.actors.some(a=>a.type===235||a.type===236))assert(Number.isFinite(speed),'room suction may physically redirect and slow the bullet');
      else assert(Math.abs(speed-21)<.01,'unaffected source shot speed');
     }
    }
    if(t.variant===2)for(const a of p.actors)if(a.eternalFly?.parent===p.entity){child=true;assert.equal(a.type,96);assert(a.eternalFly.ticks>=0);}
    if(!captured&&frame>=95){s.capture=`${out}/${t.name}.png`;await page.screenshot({path:s.capture});captured=true;}
   }
   assert(travel>.1,'flying chase moves');if(!natural&&t.variant!==1)assert(fired,'isolated Maw fires');if(t.variant===2)assert(child,'linked Eternal Fly present');
   assert.deepEqual(errors,[]);checks.push({case:t.name,travel,fired,child,samples});console.log('PASS',t.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Production WASM normal Maw family health, live pursuit/casts/projectile sizes/homing profile and required child, Original visuals. Native tests cover death and saturation. Not complete enemy parity/balance/performance certification.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
