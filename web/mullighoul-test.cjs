const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_WILLO_OUTPUT||'artifacts/mullighoul';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const near=(a,b,label)=>assert(Math.abs(a-b)<.01,`${label}: ${a} vs ${b}`);
 try {
  for(const test of [
   {name:'willo-orbit',id:808}, {name:'willo-cohort',id:808,count:4},
   {name:'willo-cover',id:808,terrain:'cover'},
   {name:'mullighoul-live',id:817}, {name:'mullighoul-river',id:817,terrain:'river'},
   {name:'mullighoul-death',id:817,hit:45},
   {name:'mullighoul-overkill',id:817,hit:109,overkill:true},
   {name:'natural-willo',id:808,seed:3,floor:1,room:6},
   {name:'natural-mullighoul',id:817,seed:80,floor:2,room:8}
  ].filter(t=>!process.env.DEATHWARD_WILLO_CASE||process.env.DEATHWARD_WILLO_CASE.split(',').includes(t.name))) {
   const natural=test.seed!==undefined,variant=test.id===817?1:0;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${test.id}.${variant}.0`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.count)params.set('enemy-count',test.count);
   if(test.terrain)params.set('enemy-terrain',test.terrain);
   if(test.hit)params.set('enemy-hit',`100:${test.hit}`);
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});
   const samples=[],newborns=new Map();let capture=false,warning=false,shot=false,birth=false,firstChildren,distance=0,previous,wet=false,pulled=false;
   for(let frame=10;frame<=(test.hit?200:480);frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe,actor=p.actors.find(a=>a.entity===p.entity);
    assert.equal(p.resident.natural,natural);
    if(natural){assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);}
    if(actor) {
     assert.equal(actor.type,test.id);assert.equal(actor.variant,variant);near(actor.maxHp,test.id===808?19.2:44.8,'source-scaled HP');
     if(!previous)previous={x:p.startX,z:p.startZ};distance+=Math.hypot(actor.x-previous.x,actor.z-previous.z);previous=actor;
     if(test.id===817)near(actor.y,1.45,'Mullighoul hover');
     wet||=p.waterBlocked;
    }
    const willos=p.actors.filter(a=>a.type===808);
    assert(willos.filter(a=>a.willo&&a.willo.attackFrame>=0).length<=1,'one Willo attack at a time');
    for(const a of willos){
     // Spawn events drain after the controller pass. A just-admitted child
     // receives its orbit runtime on the next simulation update.
     if(!a.willo){if(!newborns.has(a.entity))newborns.set(a.entity,s.frame);assert(s.frame-newborns.get(a.entity)<=1,'orbit initializes next update');}
     near(a.maxHp,19.2,'persistent Willo HP');warning||=!!a.willo?.warning;
    }
    for(const b of p.bullets.filter(b=>willos.some(a=>a.entity===b.owner))) {
     shot=true;assert(b.noWallCollision);near(b.gravity,9,'Willo gravity');near(b.flightRetention,.9,'Willo damping');
     const speed=Math.hypot(b.vx,b.vz);
     if(natural&&p.actors.some(a=>a.type===235||a.type===236)) {
      // This production room includes an existing attraction statue. Its
      // field accelerates all projectiles, including wall-passing ones.
      assert(speed>0&&speed<=40.01,'statue projectile speed cap');pulled||=Math.abs(speed-30)>.01;
     } else near(speed,30,'Willo planar shot speed');
    }
    if(test.count){assert.equal(willos.length,4);const slots=willos.map(a=>a.willo.slot).sort((a,b)=>a-b);for(let i=1;i<slots.length;++i)near(slots[i]-slots[i-1],Math.PI/2,'cohort spacing');}
    if(test.hit&&s.frame>=100) {
     assert(!p.alive);assert.equal(p.kills,1);
     if(firstChildren===undefined){firstChildren=p.actors.filter(a=>a.summoner===0).length;assert.equal(firstChildren,test.overkill?0:3);}
     for(const a of p.actors.filter(a=>a.summoner===0))assert.equal(a.type,808);
    } else if(test.id===817)birth||=willos.some(a=>a.summoner===p.entity);
    if(!capture&&(test.hit?s.frame>=115:test.id===817?birth&&frame>=80:warning&&frame>=80)) {
     await page.screenshot({path:`${out}/${test.name}.png`});capture=true;
    }
    samples.push(s);
   }
   assert(distance>.3,'actor moves');
   if(!natural&&!test.hit&&test.id===808){assert(warning,'warning visible');assert(shot,'native Willo projectile observed');}
   if(!natural&&!test.hit&&test.id===817)assert(birth,'live full-health Willo child observed');
   if(test.name==='natural-willo')assert(pulled,'actual seeded attraction-statue interaction');
   if(!capture){await page.screenshot({path:`${out}/${test.name}.png`});capture=true;}
   assert.deepEqual(errors,[]);
   fs.writeFileSync(`${out}/${test.name}-samples.json`,JSON.stringify(samples,null,2)+'\n');
   checks.push({case:test.name,distance,warning,shot,birth,firstChildren,wet,pulled,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Nine Original-style production WASM scenes: Willo single/cohort/cover orbits, attack warning and projectile metadata, Mullighoul live/death children, overkill, hover in a river room, and two actual wet-band residents. Native tests separately cover exact animation timing, water crossing, wall-passing projectile collision, completion and capacity. Full parity, broad balance and controlled performance remain open.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
