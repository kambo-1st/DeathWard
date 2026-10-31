const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_PREY_OUTPUT||'artifacts/prey';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const near=(a,b,label)=>assert(Math.abs(a-b)<.01,`${label}: ${a} vs ${b}`);
 try {
  for(const test of [
   {name:'small-leech-dry',id:810}, {name:'small-leech-wet',id:810,wet:true},
   {name:'small-leech-river',id:810,river:true},
   {name:'prey-live',id:817},
   {name:'prey-death',id:817,hit:45},
   {name:'prey-overkill',id:817,hit:109,overkill:true},
   {name:'natural-small-leech',id:810,seed:41,floor:2,room:7},
   {name:'natural-prey',id:817,seed:119,floor:2,room:3}
  ].filter(t=>!process.env.DEATHWARD_PREY_CASE||t.name===process.env.DEATHWARD_PREY_CASE)) {
   const natural=test.seed!==undefined;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${test.id}.0.0`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.wet)params.set('enemy-flooded','');
   if(test.river)params.set('enemy-terrain','river');
   // Delay death for camera settling. Existing live-spit children keep their
   // summoner identity; death children are independent bodies with summoner0.
   if(test.hit)params.set('enemy-hit',`100:${test.hit}`);
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let capture=false,distance=0,previous,birth=false,thrown=false,landed=false,hop=false,swam=false,peak=0;
   let firstChildren;const liveChildren=new Set();
   for(let frame=10;frame<=(test.hit?200:test.id===817?360:240);frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe,actor=p.actors.find(a=>a.entity===p.entity);
    assert.equal(p.resident.natural,natural);
    if(natural){assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);}
    if(actor) {
     assert.equal(actor.type,test.id);near(actor.maxHp,test.id===810?16:44.8,'source-scaled HP');
     if(!previous)previous={x:p.startX,z:p.startZ};distance+=Math.hypot(actor.x-previous.x,actor.z-previous.z);previous=actor;
     if(test.id===810){hop||=actor.hopFrame>=0;swam||=actor.swimming;assert(!actor.thrown);}
    }
    if(test.hit&&s.frame>=100) {
     assert(!p.alive);assert.equal(p.kills,1);
     if(firstChildren===undefined){firstChildren=p.actors.filter(a=>a.summoner===0).length;assert.equal(firstChildren,test.overkill?0:3);}
     for(const child of p.actors.filter(a=>a.summoner===0)) {
      assert.equal(child.type,810);near(child.hp,16,'death child full health');assert.equal(child.summoner,0);
      if(child.thrown){thrown=true;assert.equal(child.throwDuration,23);peak=Math.max(peak,child.y);}
      else landed=true;
     }
    } else if(test.id===817) {
     for(const child of p.actors.filter(a=>a.summoner===p.entity)) {
      birth=true;liveChildren.add(child.entity);assert.equal(child.type,810);near(child.maxHp,16,'live child full health');assert(!child.thrown);
     }
    }
    if(!capture&&(test.hit?s.frame>=115&&!test.overkill: test.id===817?(birth||natural&&frame>=180):frame>=80)) {
     await page.screenshot({path:`${out}/${test.name}.png`});capture=true;
    }
    samples.push(s);
   }
   if(test.overkill){assert.equal(firstChildren,0);await page.screenshot({path:`${out}/${test.name}.png`});capture=true;}
   if(test.hit&&!test.overkill){assert(thrown&&landed&&peak>5,'thrown arc and restoration on landing');await page.screenshot({path:`${out}/${test.name}-landed.png`});}
   if(test.id===810) {assert(distance>.3);if(test.wet||test.river||natural)assert(swam&&!hop);else assert(hop&&!swam);}
   if(test.id===817&&!test.hit){assert(distance>.3);if(!natural)assert(birth,'live Shoot child');}
   assert(capture);assert.deepEqual(errors,[]);
   fs.writeFileSync(`${out}/${test.name}-samples.json`,JSON.stringify(samples,null,2)+'\n');
   checks.push({case:test.name,distance,liveChildren:[...liveChildren],firstChildren,thrown,landed,peak,hop,swam,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Eight Original-style production WASM scenes: dry/wet/river Small Leech movement, Prey live children, thrown death children and landing, overkill, and two actual seeded wet-floor residents. Native tests cover exact source timing, contact/projectile collision, solid obstacles, population/capacity, and configuration validation. Full parity, balance and controlled performance remain open.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
