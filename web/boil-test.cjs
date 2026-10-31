const {chromium}=require('playwright');
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_BOIL_OUTPUT||'artifacts/boils';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const cases=[{name:'boil',id:'30.0.0',frames:1400},{name:'gut',id:'30.1.0',frames:1400},
  {name:'sack',id:'30.2.0',frames:1600},{name:'walking-boil',id:'88.0.0',frames:1000},
  {name:'walking-gut',id:'88.1.0',frames:1000},{name:'walking-sack',id:'88.2.0',frames:1600},
  {name:'walking-boil-cover',id:'88.0.0',frames:1000,terrain:'cover'},
  {name:'natural-boil',id:'30.0.0',seed:0,floor:4,room:2,frames:500},
  {name:'natural-gut',id:'30.1.0',seed:0,floor:3,room:8,frames:500},
  {name:'natural-sack',id:'30.2.0',seed:8,floor:3,room:6,frames:500},
  {name:'natural-walking-boil',id:'88.0.0',seed:2,floor:5,room:3,frames:500},
  {name:'natural-walking-gut',id:'88.1.0',seed:0,floor:4,room:1,frames:500},
  {name:'natural-walking-sack',id:'88.2.0',seed:0,floor:2,room:1,frames:500}];
 try {
  for(const test of cases.filter(t=>!process.env.DEATHWARD_BOIL_CASE||process.env.DEATHWARD_BOIL_CASE.split(',').includes(t.name))) {
   const natural=test.seed!==undefined,walking=test.id.startsWith('88'),variant=Number(test.id.split('.')[1]);
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${test.id}`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.terrain)params.set('enemy-terrain',test.terrain);
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let attacks=0,child=false,thrown=false,maxHealth=0,travel=0,previous,captured=false;
   for(let frame=10;frame<=test.frames;frame+=10) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,p:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    samples.push(s);assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.p,e=p.actors.find(a=>a.entity===p.entity);assert(e,'selected actor alive');assert(Math.abs(e.maxHp-64)<.02);
    assert.equal(p.resident.natural,natural);if(natural){assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);}
    assert(e.sack,'dedicated family controller exists');attacks=Math.max(attacks,e.sack.attacks);maxHealth=Math.max(maxHealth,e.hp);
    if(previous)travel+=Math.hypot(e.x-previous.x,e.z-previous.z);previous=e;
    if(!natural&&frame===10)assert(walking?e.hp===64:e.hp<30,'correct initial full/partly grown health');
    if(!natural&&variant===2) {
     child||=p.actors.some(a=>a.entity!==e.entity&&[85,814].includes(a.type));
     thrown||=p.actors.some(a=>a.entity!==e.entity&&a.thrown);
     assert.equal(p.shots,0,'Sacks spawn children, not blood projectiles');
    }
    if(!captured&&frame>=140){await page.screenshot({path:`${out}/${test.name}.png`});captured=true;}
   }
   fs.writeFileSync(`${out}/${test.name}-samples.json`,JSON.stringify(samples,null,2)+'\n');
   if(!natural) {
    assert(attacks>0,'attack event executed');assert(maxHealth>63.9,'stationary fully grows/walker remains full');
    assert(walking?travel>1:travel<.01,'correct stationary/wandering behavior');
    if(variant===2){assert(child,'independent child in live simulation');assert(thrown,'thrown birth observed');}
    else assert(samples.at(-1).p.shots>=(variant===1?1:3),'actual projectile payload emitted');
    await page.screenshot({path:`${out}/${test.name}-late.png`});
   }
   assert.deepEqual(errors,[]);checks.push({case:test.name,attacks,child,thrown,maxHealth,travel,sampleCount:samples.length});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'13 Original-style production WASM cases: six isolated family members, walking cover navigation and six actual seeded residents. Exact growth/events/ballistics/immunity/retained impacts and stun during thrown flight have native fixtures. Broader acceptance gates remain open.'},null,2)+'\n');
  await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
