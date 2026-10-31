const {chromium}=require('playwright');
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_LONG_LEGS_OUTPUT||'artifacts/long-legs';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  const cases=[{name:'baby',id:'206.0.0',frames:1400},{name:'small-baby',id:'206.1.0',frames:1600},
   {name:'crazy',id:'207.0.0',frames:800},{name:'small-crazy',id:'207.1.0',frames:800},
   {name:'sack',id:'30.2.0',frames:1600},{name:'crazy-cover',id:'207.0.0',frames:1000,terrain:'cover'},
   {name:'natural-baby',id:'206.0.0',frames:500,seed:9,floor:0,room:1},
   {name:'natural-small-baby',id:'206.1.0',frames:500,seed:1,floor:0,room:4},
   {name:'natural-crazy',id:'207.0.0',frames:500,seed:3,floor:0,room:5},
   {name:'natural-small-crazy',id:'207.1.0',frames:500,seed:4,floor:0,room:3}];
  for(const test of cases.filter(t=>!process.env.DEATHWARD_LONG_LEGS_CASE||process.env.DEATHWARD_LONG_LEGS_CASE.split(',').includes(t.name))) {
   const natural=test.seed!==undefined,sack=test.id==='30.2.0',baby=test.id.startsWith('206'),small=test.id.split('.')[1]==='1';
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
    const p=s.p,e=p.actors.find(a=>a.entity===p.entity);assert(e,'selected actor alive');
    assert.equal(p.resident.natural,natural);if(natural){assert.equal(p.resident.room,test.room);assert.equal(p.resident.floor,test.floor);}
    assert(Math.abs(e.maxHp-(small?51.2:64))<.02,'source-scaled maximum health');
    maxHealth=Math.max(maxHealth,e.hp);if(previous)travel+=Math.hypot(e.x-previous.x,e.z-previous.z);previous=e;
    const ai=sack?e.sack:e.longLegs;assert(ai,'dedicated controller running');attacks=Math.max(attacks,ai.attacks);
    if(!natural&&(baby||sack)) {
     const expected=small?30:85;child||=p.actors.some(a=>a.entity!==e.entity&&a.type===expected);
     thrown||=p.actors.some(a=>a.entity!==e.entity&&a.thrown);
     assert.equal(p.shots,0,'spawners do not emit a projectile volley');
    }
    if(!captured&&frame>=140){await page.screenshot({path:`${out}/${test.name}.png`});captured=true;}
   }
   fs.writeFileSync(`${out}/${test.name}-samples.json`,JSON.stringify(samples,null,2)+'\n');
   if(!sack)assert(travel>.5,'ordinary parent moves');
   if(!natural) {
    assert(attacks>0,'source attack event emitted');
    if(baby||sack)assert(child,'expected child reaches live simulation');
    if(sack){assert(maxHealth>63.9,'Sack fully regenerates');assert(thrown,'Sack uses thrown child');}
    else if(!baby)assert(samples.at(-1).p.shots>=(small?4:8),'Crazy volley emitted');
    await page.screenshot({path:`${out}/${test.name}-late.png`});
   }
   assert.deepEqual(errors,[]);checks.push({case:test.name,attacks,child,thrown,maxHealth,travel,sampleCount:samples.length});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Ten Original-style production WASM cases: four Long Legs parents, regenerating/throwing Sack, Crazy cover navigation and all four actual seeded parent rooms. Exact frame events, volleys, birth impulses/capacity and regen are checked in native fixtures. Full native special branches and all six acceptance gates are not certified.'},null,2)+'\n');
  await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
