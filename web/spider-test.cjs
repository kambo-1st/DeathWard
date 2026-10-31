const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_SPIDER_OUTPUT||'artifacts/spiders';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const near=(a,b,label)=>assert(Math.abs(a-b)<.01,`${label}: ${a} vs ${b}`);
 try {
  for(const test of [
   {name:'spider-bursts',id:85},{name:'spider-group',id:85,count:4},{name:'spider-river',id:85,river:true},
   {name:'big-spider-bursts',id:94},{name:'big-spider-death',id:94,hit:65},
   {name:'big-spider-overkill',id:94,hit:128,overkill:true},
   {name:'natural-spider',id:85,seed:0,floor:0,room:3},
   {name:'natural-big-spider',id:94,seed:71,floor:0,room:1}
  ].filter(t=>!process.env.DEATHWARD_SPIDER_CASE||process.env.DEATHWARD_SPIDER_CASE.split(',').includes(t.name))) {
   const natural=test.seed!==undefined;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${test.id}.0.0`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.count)params.set('enemy-count',test.count);
   if(test.river)params.set('enemy-terrain','river');
   if(test.hit)params.set('enemy-hit',`100:${test.hit}`);
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let capture=false,burst=false,idle=false,pursuit=false,firstChildren,distance=0,previous,peak=0;
   for(let frame=10;frame<=(test.hit?200:360);frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe,actor=p.actors.find(a=>a.entity===p.entity);
    assert.equal(p.resident.natural,natural);
    if(natural){assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);}
    if(actor) {
     assert.equal(actor.type,test.id);near(actor.maxHp,test.id===85?20.8:64,'installed scaled HP');assert(actor.spider);
     if(!previous)previous={x:p.startX,z:p.startZ};distance+=Math.hypot(actor.x-previous.x,actor.z-previous.z);previous=actor;
     const speed=Math.hypot(actor.vx,actor.vz);peak=Math.max(peak,speed);
     idle||=!actor.spider.ready&&speed<1;burst||=actor.spider.ready&&speed>5;pursuit||=actor.spider.pursuing;
     if(test.river)assert(!p.waterBlocked,'ordinary spider stays out of water');
    }
    if(!natural)assert.equal(p.shots,0,'ordinary spiders do not shoot');
    if(test.count)assert.equal(p.actors.filter(a=>a.type===85).length,4);
    if(test.hit&&s.frame>=100) {
     assert(!p.alive);assert.equal(p.kills,1);
     if(firstChildren===undefined){firstChildren=p.actors.length;assert.equal(firstChildren,test.overkill?0:2);}
     for(const a of p.actors){assert.equal(a.type,85);near(a.hp,20.8,'independent full-health death child');assert.equal(a.summoner,0);}
    }
    if(!capture&&(test.hit?s.frame>=115:frame>=85)) {await page.screenshot({path:`${out}/${test.name}.png`});capture=true;}
    samples.push(s);
   }
   assert(distance>.3,'actor moves');
   if(!natural&&!test.hit){assert(burst&&idle,'both stopped and burst phases observed');if(!test.river)assert(pursuit,'player acquisition observed');}
   assert(capture);assert.deepEqual(errors,[]);
   fs.writeFileSync(`${out}/${test.name}-samples.json`,JSON.stringify(samples,null,2)+'\n');
   checks.push({case:test.name,distance,peak,burst,idle,pursuit,firstChildren,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Selected cases from eight Original-style production WASM scenes: Spider/Big Spider bursts, group and river navigation, two-child death, overkill, and two actual early-floor residents. Native fixtures verify exact timing/acceleration/lead, committed targeting, solid/water collision, contact/fire, split vectors, capacity/completion and configuration. Full status/item/visual/balance/performance acceptance remains open.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
