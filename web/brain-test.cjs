// Production WASM: Brain movement, charge, creep lifecycle and actual residents.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright');
 const out=process.env.DEATHWARD_BRAIN_OUTPUT;fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),checks=[],errors=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const witnesses=JSON.parse(fs.readFileSync(process.env.DEATHWARD_BRAIN_WITNESSES,'utf8'));
 const cases=[{name:'brain',charge:true},{name:'brain-cover',terrain:'cover'},
  {name:'brain-river',terrain:'river'},{name:'brain-death',death:true},
  ...witnesses.bands.map(t=>({...t,name:`resident-band-${t.band}`})),
  {...witnesses.river,name:'resident-river'}];
 try {
  for(const t of cases) {
   if(process.env.DEATHWARD_BRAIN_CASES&&!process.env.DEATHWARD_BRAIN_CASES.split(',').includes(t.name))continue;
   const natural=t.seed!==undefined;
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',
    'enemy-camera-follow':'',scene:`${natural?'resident':'enemy'}-32.0.0`});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   if(t.terrain)q.set('enemy-terrain',t.terrain);if(t.death)q.set('enemy-hit','180:10000');
   const result={name:t.name,pass:false,samples:[],captures:{}};checks.push(result);console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   let movement=0,previous,dead=false,creep=false,faded=false,survived=false,charges=0,stops=0;
   for(let f=8;f<=550;f+=4) {
    await page.waitForFunction(n=>Module.state?.error||Module.state?.frame>=n,f,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,error:Module.state.error,style:Module.state.visualStyleName,
     gl:Module.ctx.getError(),p:Module.enemyProbe}));
    const p=s.p,a=p.actors.find(a=>a.entity===p.entity),bullets=p.bullets.filter(b=>b.owner===p.entity),
     patches=p.hazards.filter(h=>h.owner===p.entity&&h.fade);
    result.samples.push({frame:s.frame,error:s.error,style:s.style,gl:s.gl,actor:a,resident:p.resident,
     ground:p.groundBlocked,water:p.waterBlocked,kills:p.kills,bullets,patches});
    assert.equal(s.error,'');assert.equal(s.style,'Original');assert.equal(s.gl,0);
    assert.equal(p.resident.natural,natural);assert.equal(bullets.length,0,'Brain never inherits a ranged attack');
    if(natural){assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);}
    if(a) {
     assert.equal(a.type,32);assert.equal(a.variant,0);assert(Math.abs(a.maxHp-64)<.01);
     assert(a.brain?.ticks>0&&!a.spitty&&!a.cardinalWalker,'dedicated Brain controller');
     assert(!p.groundBlocked&&!p.waterBlocked,'grounded movement respects actual terrain');
     if(previous) {
      movement+=Math.hypot(a.x-previous.x,a.z-previous.z);
      if(a.brain.charging&&previous.brain.charging&&a.brain.charges===previous.brain.charges)
       assert.deepEqual([a.brain.dx,a.brain.dz],[previous.brain.dx,previous.brain.dz],'committed charge never homes');
     }
     previous=a;charges=Math.max(charges,a.brain.charges);stops=Math.max(stops,a.brain.stops);
     if(a.brain.charging)assert.equal(Math.abs(a.brain.dx)+Math.abs(a.brain.dz),1);
    } else {assert(t.death&&s.frame>=180,'only scripted death removes this fixture actor');assert.equal(p.kills,1);dead=true;}
    for(const h of patches) {
     creep=true;assert(Math.abs(h.radius-2.46)<.001);assert.equal(h.ownerBound,false);
     assert(Math.abs(h.duration-125/30)<.001&&Math.abs(h.fade.duration-40/30)<.001);
     assert(Math.abs(h.fade.scale-.98)<.001);assert.equal(h.fade.damage,10);assert.equal(h.fade.clear,true);
     if(h.fade.age>=0)faded=true;
    }
    if(dead&&patches.length)survived=true;
    const capture=dead&&patches.length?'after-death':dead&&!patches.length?'expired':
     a?.brain.charging?'charge':s.frame>=90?'trail':null;
    if(capture&&!result.captures[capture]){result.captures[capture]=`${out}/${t.name}-${capture}.png`;await page.screenshot({path:result.captures[capture]});}
    if(t.death?dead&&survived&&faded&&!patches.length:s.frame>=300&&creep&&(!t.charge||charges>0))break;
   }
   assert(movement>.5&&creep,'real movement and independent ground trails');if(t.charge)assert(charges>0);
   if(t.death){assert(dead&&survived&&faded);assert.equal(result.samples.at(-1).patches.length,0,'owner-independent creep expires after its fade');}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,movement,dead,creep,faded,survived,charges,stops});console.log('PASS',t.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({browser:await browser.version(),checks,errors,
   scope:'Production WASM dedicated Brain controller, charge commitment, terrain legality, creep profile and owner-independent lifecycle, plus actual seeded habitat residents. Partial acceptance evidence.'},null,2)+'\n');
  await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
