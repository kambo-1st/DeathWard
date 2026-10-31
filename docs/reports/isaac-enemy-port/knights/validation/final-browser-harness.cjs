// Scoped production checks: masks, in-place Loose/Pon lifecycle, landing creep.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_KNIGHT_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:process.env.DEATHWARD_BROWSER_HEADFUL!=='1',executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{
  window.__knightCaptures={};
  window.__captureKnight=frame=>{
   const p=Module.enemyProbe,a=p?.actors.find(a=>a.entity===p.entity);if(!p)return;
   const captures=window.__knightCaptures;
   let kind=null;
   if(frame>=24&&a?.maskArmor)kind='mask';
   if(a?.knight?.charging&&frame>30&&!captures.charge)kind='charge';
   if(p.fireWaves.some(w=>w.rays.length===3&&w.jets.length>=3)&&!captures.impact)kind='impact';
   if(frame>=60&&a?.type===41&&a.variant===3&&p.actors.some(a=>a.type===840))kind='pair';
   if(p.actors.some(a=>a.landingCreep?.patches>0)&&frame>90)kind='creep';
   if(a?.type===840&&a.targetHop?.airborne&&frame>35&&!captures.hop)kind='hop';
   if(!kind||captures[kind])return;
   captures[kind]={frame,probe:JSON.parse(JSON.stringify(p)),png:(Module.canvas||document.querySelector('canvas')).toDataURL('image/png')};
  };
 });
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Scoped production WASM lifecycle, hopping, rendering and seeded Pon smoke checks. Source-driven Knight movement/impact and natural placement smoke; full balance/performance/parity remain open.'},null,2)+'\n');
 try {
  const cases=[{name:'loose-pair',id:'41.2.0',pair:true},{name:'black-mask',id:'41.4.0',impact:true},
   {name:'knight',id:'41.0.0'},{name:'selfless',id:'41.1.0'},
   {name:'resident-knight',id:'41.0.0',seed:0,floor:2,room:5},
   {name:'resident-selfless',id:'41.1.0',seed:0,floor:5,room:7},
   {name:'resident-loose',id:'41.2.0',seed:0,floor:3,room:2},
   {name:'resident-black',id:'41.4.0',seed:1,floor:6,room:7},
   {name:'pon',id:'840.0.0'},{name:'pon-river',id:'840.0.0',terrain:'river'},
   {name:'resident-pon',id:'840.0.0',seed:33,floor:4,room:7}];
  for(const t of cases) {
   if(process.env.DEATHWARD_KNIGHT_CASES&&!process.env.DEATHWARD_KNIGHT_CASES.split(',').includes(t.name))continue;
   const natural=t.seed!==undefined,q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${natural?'resident':'enemy'}-${t.id}`,'enemy-camera-follow':''});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   if(t.terrain)q.set('enemy-terrain',t.terrain);
   if(t.impact)q.append('enemy-player-at','24:5:0');
   if(t.pair){q.append('enemy-blast','40:1000');q.append('enemy-partner-hit','190:1000');}
   const result={name:t.name,pass:false,samples:[],captures:{}};checks.push(result);console.log('START',t.name);persist();
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureKnight;});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   result.renderer=await page.evaluate(()=>{const gl=Module.ctx,x=gl.getExtension('WEBGL_debug_renderer_info');return x?gl.getParameter(x.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);});
   let original,pair=false,child=0,hops=0,patches=0,gone=false,charges=0,impacts=0;
   for(let frame=4;frame<=260;frame+=4) {
    await page.waitForFunction(n=>Module.state?.error||Module.state?.frame>=n,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),p:Module.enemyProbe}));result.samples.push(s);
    assert.equal(s.error,'');assert.equal(s.style,'Original');assert.equal(s.gl,0);
    original??=s.p.entity;const a=s.p.actors.find(a=>a.entity===original);
    if(t.pair) {
     if(a?.variant===2)assert.equal(a.maxHp,64);
     if(a?.variant===3){pair=true;assert.equal(a.entity,original);assert.equal(a.maxHp,64);const c=s.p.actors.find(a=>a.type===840);if(c)child=c.entity;}
     if(s.frame>195){assert(!a,'remnant removed after linked Pon hit');assert(!s.p.actors.some(a=>a.entity===child));gone=true;}
    } else {
     assert(a,'isolated/natural actor alive');assert.equal(a.maxHp,t.id==='41.4.0'?96:64);
     if(t.id.startsWith('41.')){assert(a.maskArmor&&a.knight);if(t.impact)assert.equal(a.hp,a.maxHp,'Black is immune to ordinary fire jets');charges=Math.max(charges,a.knight.charges);impacts=Math.max(impacts,a.knight.impacts);}
     else assert(a.targetHop&&a.landingCreep);
    }
    for(const a of s.p.actors.filter(a=>a.type===840)){hops=Math.max(hops,a.targetHop.hops);patches=Math.max(patches,a.landingCreep.patches);}
    if(natural){assert(s.p.resident.natural);assert.equal(s.p.resident.floor,t.floor);assert.equal(s.p.resident.room,t.room);}
   }
   const captures=await page.evaluate(()=>window.__knightCaptures);
   for(const [kind,c] of Object.entries(captures)) {
    const path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;
    result.captures[kind]={path,...c};
   }
   if(t.pair){assert(pair&&child&&gone,'same-ID pair formation and linked cleanup');assert(captures.mask&&captures.pair);}
   else if(t.id.startsWith('41.')){assert(captures.mask);if(!natural)assert(charges>0&&captures.charge);if(t.impact)assert(impacts>0&&captures.impact);}else {assert(hops>0&&patches>0);assert(captures.hop&&captures.creep);}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,pair,child,gone,hops,patches,charges,impacts});console.log('PASS',t.name);persist();
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
