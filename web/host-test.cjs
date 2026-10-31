const {chromium}=require('playwright');
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_HOST_OUTPUT||'artifacts/hosts';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const base=[{name:'host',type:27,variant:0,hp:44.8},{name:'red-host',type:27,variant:1,hp:48},
  {name:'mobile-host',type:204,variant:0,hp:44.8},{name:'flesh-mobile-host',type:247,variant:0,hp:86.4},{name:'floast',type:859,variant:0,hp:64}];
 const cases=[...base];if(process.env.DEATHWARD_HOST_WITNESSES)for(const w of JSON.parse(fs.readFileSync(process.env.DEATHWARD_HOST_WITNESSES))) {
  const b=base.find(b=>b.type===w.type&&b.variant===w.variant);cases.push({...b,...w,name:'natural-'+b.name});
 }
 try {
  for(const t of cases) {
   const natural=t.seed!==undefined,params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${t.type}.${t.variant}.0`});
   if(natural){params.set('resident-seed',t.seed);params.set('resident-floor',t.floor);}
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   console.log('START',t.name,'browser',await browser.version());
   console.log('GL',await page.evaluate(()=>{const gl=Module.ctx,e=gl.getExtension('WEBGL_debug_renderer_info');return e?gl.getParameter(e.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);}));
   const samples=[];let fired=false,exposed=false,closed=false,travel=0,previous,captured=false,closedCapture=false;
   for(let frame=10;frame<=360;frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,p:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));samples.push(s);
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);const p=s.p;
    assert.equal(p.type,t.type);assert.equal(p.variant,t.variant);assert.equal(p.resident.natural,natural);
    if(!natural)assert(Math.abs(p.hp-t.hp)<.01);else{assert(p.hp>0&&p.hp<=t.hp+.01);assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);}
    const actor=p.actors.find(a=>a.id===p.entity||a.entity===p.entity)||p.actors.find(a=>a.type===t.type&&a.variant===t.variant);
    assert(actor?.host,'dedicated Host runtime present');const h=actor.host;
    if(h.exposed){exposed=true;assert(h.frame>=(t.type===27?9:10)&&h.frame<(t.type===27?55:t.type===859?54:53));}else closed=true;
    if(previous)travel+=Math.hypot(p.x-previous.x,p.z-previous.z);previous=p;
    for(const b of p.bullets.filter(b=>b.owner===p.entity)){fired=true;assert.equal(b.damage,10);assert(!b.sourceHoming);}
    if(!closedCapture&&!natural&&!h.exposed&&frame>=150){await page.screenshot({path:`${out}/${t.name}-closed.png`});closedCapture=true;}
    if(!captured&&((!natural&&h.exposed&&frame>=60)||(natural&&frame>=95))){s.capture=`${out}/${t.name}.png`;await page.screenshot({path:s.capture});captured=true;}
   }
   if(!natural){assert(exposed&&closed&&fired,'isolated opening/closing and actual projectile');if(t.type===27)assert(travel<.01,'stationary Host');else assert(travel>.1,'mobile/floating Host moves');}
   assert(captured);assert.deepEqual(errors,[]);checks.push({case:t.name,fired,exposed,closed,travel,samples});console.log('PASS',t.name);
  }
 } finally {fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Production WASM five regular Host identities plus seeded residents, runtime armor windows, physical projectiles, movement, health and Original-style captures. Native tests cover incoming damage and saturation. Partial acceptance only.'},null,2)+'\n');await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
