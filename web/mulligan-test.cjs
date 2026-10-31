const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_MULLIGAN_OUTPUT||'artifacts/mulligans';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const near=(a,b,label)=>assert(Math.abs(a-b)<.01,`${label}: ${a} vs ${b}`);
 try {
  for(const test of [
   {name:'mulligan-live',variant:0}, {name:'mulligoon-live',variant:1},
   {name:'mulliboom-proximity',variant:2,proximity:true},
   {name:'mulligan-death',variant:0,hit:42},
   {name:'mulligan-overkill',variant:0,hit:74,overkill:true},
   {name:'mulligoon-death',variant:1,hit:42},
   {name:'mulliboom-death',variant:2,hit:42},
   {name:'natural-mulligan',variant:0,seed:2,floor:0,room:3},
   {name:'natural-mulligoon',variant:1,seed:105,floor:0,room:4},
   {name:'natural-mulliboom',variant:2,seed:54,floor:2,room:5}
  ].filter(t=>!process.env.DEATHWARD_MULLIGAN_CASE||t.name===process.env.DEATHWARD_MULLIGAN_CASE)) {
   const natural=test.seed!==undefined,dead=!!test.hit||test.proximity;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-16.${test.variant}.0`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.hit)params.set('enemy-hit',`1:${test.hit}`);
   if(test.proximity)params.set('enemy-player-at','1:0:3.5');
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let capture=false,distance=0,previous,firstChildren,bombSeen=false,boomSeen=false,aliveSeen=false;
   for(let frame=5;frame<=(dead?210:natural?240:150);frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe,actor=p.actors.find(a=>a.entity===p.entity);
    assert.equal(p.resident.natural,natural);
    if(natural){assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);}
    if(actor) {
     aliveSeen=true;assert.equal(actor.type,16);assert.equal(actor.variant,test.variant);near(actor.maxHp,41.6,'source-scaled health');
     if(!previous)previous={x:p.startX,z:p.startZ};
     distance+=Math.hypot(actor.x-previous.x,actor.z-previous.z);previous=actor;
    }
    if(test.hit) {
     assert(!p.alive);assert.equal(p.kills,1);
     if(firstChildren===undefined) {
      firstChildren=p.actors.length;
      assert.equal(firstChildren,test.variant===0&&!test.overkill?4:0);
      for(const child of p.actors)assert([13,14,18].includes(child.type),'source offspring identities');
     }
     assert.equal(p.shots,test.variant===1?4:0);
    }
    if(test.variant===1&&test.hit) {
     for(const bomb of p.enemyBombs) {
      bombSeen=true;assert.equal(bomb.source,p.entity);assert.deepEqual(bomb.ordnance,[4,3,0]);
      near(bomb.damage,320,'Troll Bomb damage');near(bomb.playerDamage,20,'full-heart conversion');
      assert(bomb.fuse>=1.5&&bomb.fuse<=74/30+.001);assert(bomb.configured);
     }
     for(const b of p.bullets.filter(b=>b.owner===p.entity)) {
      near(Math.hypot(b.vx,b.vz),21,'death shot speed');near(Math.abs(b.vx),Math.abs(b.vz),'diagonal death pattern');
     }
    }
    if(p.statue.explosions>0)boomSeen=true;
    if(!capture&&(test.hit||test.proximity&&!p.alive||!dead&&actor&&frame>=(natural&&test.variant===2?5:60))) {
     s.capture=`${out}/${test.name}.png`;await page.screenshot({path:s.capture});capture=true;
    }
    samples.push(s);
   }
   fs.writeFileSync(`${out}/${test.name}-samples.json`,JSON.stringify(samples,null,2)+"\n");
   const last=samples.at(-1).probe;
   if(!dead){assert(aliveSeen);assert(distance>.3,'physical movement');}
   if(test.proximity){assert(!last.alive);assert.equal(last.kills,1);assert.equal(last.shots,0);}
   if(test.variant===1&&test.hit){assert(bombSeen);assert.equal(last.enemyBombs.length,0);assert(last.statue.explosions>=1,'world includes bomb and possible scenery chain blasts');}
   if(dead&&test.variant===2){assert(boomSeen);assert.equal(samples.find(s=>s.probe.statue.explosions>0).probe.statue.explosions,1,'first immediate blast');assert.equal(last.enemyBombs.length,0);}
   if(test.hit&&test.variant===0)assert.equal(last.statue.explosions,0);
   if(dead&&test.variant>0)await page.screenshot({path:`${out}/${test.name}-after.png`});
   assert(capture);assert.deepEqual(errors,[]);
   checks.push({case:test.name,distance,firstChildren,bombSeen,boomSeen,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Ten production-mechanics Original-style scenes: regular Mulligan family movement, source-scaled health, offspring/overkill, real Troll Bomb and diagonal shots, immediate Mulliboom proximity/death blasts, and three actual seeded residents. Native tests cover exact update timing, random collision trigger, retained death payloads and destruction. World explosion totals may include secondary powder-barrel blasts; native isolated tests verify one producer blast. Full parity, broad balance and controlled performance remain open.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
