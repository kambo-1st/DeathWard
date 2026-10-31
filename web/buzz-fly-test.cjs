const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_BUZZ_OUTPUT||'artifacts/buzz-flies';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const test of [
   {name:'fly-buzz',id:'13.0.0'},
   {name:'pooter-buzz-shot',id:'14.0.0'},
   {name:'fly-dung-morph',id:'13.0.0',morph:true},
   {name:'natural-fly-dung',id:'13.0.0',seed:1,floor:0,room:1},
   {name:'natural-pooter',id:'14.0.0',seed:0,floor:0,room:3}
  ]) {
   const natural=test.seed!==undefined;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${test.id}`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.morph){params.set('enemy-terrain','dung');params.set('enemy-hit','220:100');}
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
   if(test.morph) {
    const edited=await page.evaluate(()=>{
     const path='/assets/mechanics/buzz_flies.mechanics',before=Module.FS.readFile(path,{encoding:'utf8'});
     const after=before.replace('dung_morph 13.0.0 14.0.0 1000','dung_morph 13.0.0 14.0.0 1');
     Module.FS.writeFile(path,after);return before!==after;
    });assert(edited,'only morph chance forced in disposable browser content');
   }
   await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let bullet=false,capture=false,distance=0,previous;
   for(let frame=15;frame<=300;frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe,actor=p.actors.find(a=>a.entity===p.entity),shoots=test.id==='14.0.0'||test.morph;
    assert.equal(p.resident.natural,natural);
    if(frame===15&&natural){assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);assert(p.actors.length>1);}
    if(test.morph&&s.frame>=220){assert(!p.alive);assert.equal(p.kills,1);assert.equal(p.threats,0);}
    else {
     assert(actor);assert.equal(actor.type,shoots?14:13);assert(Math.abs(actor.hp-(shoots?25.6:9.6))<.01);
     assert.equal(p.flightBlocked,false);
     if(previous)distance+=Math.hypot(actor.x-previous.x,actor.z-previous.z);previous=actor;
     if(test.morph){assert.equal(p.kills,0);assert.equal(p.threats,1);assert(p.dung.some(d=>d.health>=1&&d.health<=3&&!d.destroyed));}
     if(test.name==='natural-fly-dung')assert(p.dung.length>0);
    }
    const owned=p.bullets.filter(b=>b.owner===p.entity);
    for(const b of owned){assert(shoots);assert.equal(b.kind,0);assert(Math.abs(Math.hypot(b.vx,b.vy,b.vz)-21)<.02);bullet=true;}
    if(!capture&&frame>=120&&(!shoots||owned.length)) {s.capture=`${out}/${test.name}.png`;await page.screenshot({path:s.capture});capture=true;}
    samples.push(s);
   }
   assert(distance>.2,'actor actually moves');if(test.id==='14.0.0')assert(bullet,'Pooter fires an owned physical shot');
   assert(capture);assert.deepEqual(errors,[]);
   checks.push({case:test.name,distance,bullet,content_override:test.morph?'test-only morph chance1; default1/1000 sampled natively':null,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Ordinary Fly/Pooter movement, health, physical shots, actual seeded residents/dung, and same-actor live morph followed by one death. Morph case forces chance only. Not full status/item/balance/performance acceptance.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
