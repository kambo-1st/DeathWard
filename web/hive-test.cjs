const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_HIVE_OUTPUT||'artifacts/hive';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const near=(a,b,label)=>assert(Math.abs(a-b)<.01,`${label}: ${a} vs ${b}`);
 try {
  for(const test of [
   {name:'hive-live',id:'22.0.0'},
   {name:'drowned-live',id:'22.1.0'},
   {name:'hive-death',id:'22.0.0',hit:64},
   {name:'drowned-death',id:'22.1.0',hit:58},
   {name:'hive-overkill',id:'22.0.0',hit:128,overkill:true},
   {name:'drowned-overkill',id:'22.1.0',hit:122,overkill:true},
   {name:'natural-hive',id:'22.0.0',seed:9,floor:0,room:1},
   {name:'natural-drowned',id:'22.1.0',seed:66,floor:2,room:1}
  ]) {
   const natural=test.seed!==undefined,drowned=test.id==='22.1.0';
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${test.id}`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.hit)params.set('enemy-hit',`1:${test.hit}`);
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let capture=false,distance=0,previous,birth=false,firstChildren;
   const liveChildren=new Set();
   for(let frame=10;frame<=(test.hit?100:natural?540:360);frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe,actor=p.actors.find(a=>a.entity===p.entity);
    assert.equal(p.resident.natural,natural);
    if(natural){assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);}
    if(test.hit) {
     assert(!p.alive);assert.equal(p.kills,1);
     if(firstChildren===undefined) {
      firstChildren=p.actors.length;
      if(test.overkill){assert.equal(firstChildren,0);assert.equal(p.threats,0);}
      else {
       assert(drowned?firstChildren>=1&&firstChildren<=2:firstChildren===4);
       for(const child of p.actors) {
        assert.equal(child.summoner,0,'death children have no live-spit contact policy');
        if(drowned){assert.equal(child.type,23);assert.equal(child.variant,1);near(child.hp,35.2,'half-health Drowned Charger');}
        else {assert([13,14,18].includes(child.type));near(child.hp,({13:9.6,14:25.6,18:16})[child.type],'death child health');}
       }
      }
     }
    } else {
     assert(actor);assert.equal(actor.type,22);assert.equal(actor.variant,drowned?1:0);
     near(actor.hp,drowned?57.6:64,'source-scaled parent health');
     if(previous)distance+=Math.hypot(actor.x-previous.x,actor.z-previous.z);previous=actor;
     for(const child of p.actors.filter(a=>a.summoner===p.entity)) {
      birth=true;liveChildren.add(child.entity);
      assert.equal(child.type,drowned?23:18);assert.equal(child.variant,drowned?1:0);
      near(child.hp,drowned?35.2:16,'live child health');
     }
     assert.equal(p.bullets.filter(b=>b.owner===p.entity).length,0,'Hive spawns bodies, not projectiles');
    }
    if(!capture&&(test.hit||birth||natural&&frame>=360)) {
     s.capture=`${out}/${test.name}.png`;await page.screenshot({path:s.capture});capture=true;
    }
    samples.push(s);
   }
   if(!test.hit){assert(distance>.3,'physical evade/wander movement');if(!natural)assert(birth,'source Shoot event creates live child');}
   assert(capture);assert.deepEqual(errors,[]);
   checks.push({case:test.name,distance,liveChildren:[...liveChildren],firstChildren,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Eight production-mechanics Original-style browser scenes: Hive/Drowned movement and live children, independent death children, half-health Drowned offspring, overkill suppression and two real seeded residents. Native suite covers exact source timing, global population, retained births, contact policy and reload isolation. No complete status/item, balance or controlled performance acceptance.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
