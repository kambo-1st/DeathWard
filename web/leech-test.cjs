// Production WASM Leech movement/death, owned orbiters and real seeded residents.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_LEECH_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{
  window.__leechCaptures={};window.__captureLeech=frame=>{
   const p=Module.enemyProbe,a=p?.actors.find(a=>a.entity===p.entity);if(!p)return;
   const captures=window.__leechCaptures;
   const kind=!a&&frame>=190?'death':a?.leech?.charging&&frame>25&&!captures.charge?'charge':a&&frame>=20?'idle':null;
   if(!kind||captures[kind])return;
   captures[kind]={frame,probe:JSON.parse(JSON.stringify(p)),png:(Module.canvas||document.querySelector('canvas')).toDataURL('image/png')};
  };
 });
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Scoped Original-style production WASM movement, death and natural populations. Full status parity, all-camera visuals, balance and performance remain open.'},null,2)+'\n');
 try{
  const cases=[{name:'leech',variant:0},{name:'kamikaze',variant:1},{name:'holy',variant:2},
   {name:'resident-leech',variant:0,seed:0,floor:4,room:6},
   {name:'resident-kamikaze',variant:1,seed:0,floor:4,room:8},
   {name:'resident-holy',variant:2,seed:11,floor:4,room:5}];
  for(const t of cases) {
   if(process.env.DEATHWARD_LEECH_CASES&&!process.env.DEATHWARD_LEECH_CASES.split(',').includes(t.name))continue;
   const natural=t.seed!==undefined,q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${natural?'resident':'enemy'}-55.${t.variant}.0`,'enemy-camera-follow':''});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   else{q.append('enemy-player-at','24:5:0');q.append('enemy-hit','190:1000');}
   const result={...t,pass:false,samples:[],captures:{}};checks.push(result);persist();console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureLeech;});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   result.renderer=await page.evaluate(()=>{const gl=Module.ctx,x=gl.getExtension('WEBGL_debug_renderer_info');return x?gl.getParameter(x.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);});
   let charges=0,stops=0,child=false;
   for(let frame=4;frame<=220;frame+=4) {
    await page.waitForFunction(n=>Module.state?.error||Module.state?.frame>=n,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),p:Module.enemyProbe}));result.samples.push(s);
    assert.equal(s.error,'');assert.equal(s.style,'Original');assert.equal(s.gl,0);
    const a=s.p.actors.find(a=>a.entity===s.p.entity);
    if(natural||s.frame<190) {
     assert(a?.leech,'dedicated Leech controller alive');assert.equal(a.maxHp,80);assert(!s.p.flightBlocked);
     charges=Math.max(charges,a.leech.charges);stops=Math.max(stops,a.leech.stops);
     if(t.variant===2){const flies=s.p.actors.filter(b=>b.type===96&&b.eternalFly?.parent===a.entity);assert.equal(flies.length,1,'one living owned orbiter');child=true;}
    }else{assert(!a,'lethal hit removes parent');assert(!s.p.actors.some(a=>a.type===96),'no released or orphan orbiter');assert.equal(s.p.kills,1);assert.equal(s.p.threats,0);}
    if(natural){assert(s.p.resident.natural);assert.equal(s.p.resident.floor,t.floor);assert.equal(s.p.resident.room,t.room);}
    if(!natural)assert.equal(s.p.shots,0,'Leeches have no projectile attack');
   }
   const captures=await page.evaluate(()=>window.__leechCaptures);assert(captures.idle);
   if(!natural){assert(charges>0&&captures.charge);assert(captures.death);}
   if(t.variant===2)assert(child);
   for(const [kind,c] of Object.entries(captures)){const path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;result.captures[kind]={path,...c};}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,charges,stops,child});persist();console.log('PASS',t.name);
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
