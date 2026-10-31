// Ordinary Bony family gameplay probes; source parity and full balance remain separate gates.
const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_BONY_OUTPUT||'artifacts/bony';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const test of [
   {name:'ordinary-bone-throw',frames:[5,10,15,20,30,60,120,180,300]},
   {name:'death-interrupts-throw',hit:'6:1000',frames:[15,45,120]},
   {name:'natural-quarry-resident',seed:1,floor:2,room:2,hp:44.8,frames:[30,120,240,360]},
   {name:'black-three-throws',id:277,frames:[15,40,65,80,120,300]},
   {name:'black-death-explosion',id:277,hit:'6:1000',frames:[15,45,120]},
   {name:'natural-black-resident',id:277,seed:0,floor:3,room:3,hp:51.2,frames:[30,120,240,360]}
  ]) {
   const natural=test.seed!==undefined,id=test.id||227;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${id}.0.0`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.hit)params.append('enemy-hit',test.hit);
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let observedBone=false;
   for(const frame of test.frames) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert(s.frame<frame+10,`sample window: requested ${frame}, got ${s.frame}`);assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe;assert.equal(p.type,id);assert.equal(p.variant,0);assert.equal(p.resident.natural,natural);
    if(natural){assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);assert(Math.abs(p.hp-test.hp)<.01);assert(p.actors.length>1,'unaltered resident roster');}
    else if(test.hit&&frame>6){assert.equal(p.alive,false);assert.equal(p.shots,0);assert.equal(p.kills,1);assert.equal(p.threats,0);assert.equal(p.statue.explosions,id===277?1:0);}
    else {
     assert(p.alive&&p.threats===1);assert.equal(p.hp,32);
     for(const b of p.bullets.filter(b=>b.owner===p.entity)) {
      assert.equal(b.kind,id===277?15:13,'actual family bone projectile');assert(Math.abs(Math.hypot(b.vx,b.vy,b.vz)-30)<.01);observedBone=true;
     }
     if(id===277&&frame<=80)assert.equal(p.shots,frame===15?1:frame===40?2:3,'three completed-animation shots, then recovery');
    }
    if(frame===test.frames.at(-1)){
     s.capture=`${out}/${test.name}-${frame}.png`;await page.screenshot({path:s.capture});
    }
    samples.push(s);
   }
   if(!natural&&!test.hit){assert(observedBone,'fast bone observed after stopped windup');assert(samples.at(-1).probe.shots>1,'ordinary reacquisition fires again');}
   assert.deepEqual(errors,[]);checks.push({case:test.name,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Normal/Black Bony attacks, death interruption/explosion and unforced seeded residents. Not mounted behavior, comprehensive balance or performance acceptance.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
