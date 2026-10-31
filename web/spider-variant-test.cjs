const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_SPIDER_VARIANT_OUTPUT||'artifacts/spider-variants';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const near=(a,b,label)=>assert(Math.abs(a-b)<.02,`${label}: ${a} vs ${b}`);
 try {
  for(const test of [
   {name:'strider-stroke',id:814},{name:'strider-river',id:814,terrain:'river'},
   {name:'strider-cover',id:814,terrain:'cover'},{name:'swarm-hops',id:884},
   {name:'swarm-group',id:884,count:6},{name:'swarm-player-flame',id:884,flame:true},
   {name:'natural-strider',id:814,seed:2,floor:2,room:4},
   {name:'natural-swarm',id:884,seed:0,floor:0,room:2}
  ].filter(t=>!process.env.DEATHWARD_SPIDER_VARIANT_CASE||process.env.DEATHWARD_SPIDER_VARIANT_CASE.split(',').includes(t.name))) {
   const natural=test.seed!==undefined;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${test.id}.0.0`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.count)params.set('enemy-count',test.count);
   if(test.terrain)params.set('enemy-terrain',test.terrain);
   if(test.flame)params.set('enemy-flame-hit','100:3');
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let capture=false,water=false,air=false,ground=false,strokes=0,hops=0,distance=0,previous,peak=0;
   for(let frame=10;frame<=400;frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe,actor=p.actors.find(a=>a.entity===p.entity);assert(actor,'selected actor remains alive');
    assert.equal(p.resident.natural,natural);
    if(natural){assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);}
    near(actor.maxHp,test.id===814?20.8:15.04,'installed scaled HP');
    if(!previous)previous={x:p.startX,z:p.startZ};distance+=Math.hypot(actor.x-previous.x,actor.z-previous.z);previous=actor;
    peak=Math.max(peak,Math.hypot(actor.vx,actor.vz));water||=p.waterBlocked;
    if(test.id===814) {assert(actor.strider);strokes=Math.max(strokes,actor.strider.strokes);near(actor.lift,.8,'source height presentation');}
    else {assert(actor.swarmSpider);air||=actor.swarmSpider.airborne;ground||=!actor.swarmSpider.airborne;hops=Math.max(hops,actor.swarmSpider.hops);}
    if(!natural)assert.equal(p.shots,0,'contact-only variants do not shoot');
    if(test.count)assert.equal(p.actors.filter(a=>a.type===884).length,6);
    if(test.flame)near(actor.hp,s.frame<100?15.04:12.04,'player flame damages Swarm');
    if(test.terrain==='cover')assert(!p.flightBlocked,'Strider remains outside solid cover');
    if(!capture&&frame>=90){await page.screenshot({path:`${out}/${test.name}.png`});capture=true;}
    samples.push(s);
   }
   fs.writeFileSync(`${out}/${test.name}-samples.json`,JSON.stringify(samples,null,2)+'\n');
   assert(distance>.3,'actor moves');
   if(test.id===814)assert(strokes>1,'repeated strokes');else assert(air&&ground&&hops>2,'ground and airborne phases repeat');
   if(test.terrain==='river')assert(water,'Strider actually enters deep water');
   assert(capture);assert.deepEqual(errors,[]);
   checks.push({case:test.name,distance,peak,water,air,ground,strokes,hops,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Eight Original-style production WASM cases: Strider strokes/deep water/cover, Swarm single/group hops and player-flame vulnerability, plus both real seeded residents. Native fixtures additionally verify exact events/forces/weights, true fireplace-specific immunity, wet Big Spider children and capacity, configuration, collision and contact. Full item/status/readability/balance/performance acceptance remains open.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
