const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_HORF_OUTPUT||'artifacts/horf';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const test of [{name:'horf-current-shot'},{name:'horf-solid-cover',cover:true},{name:'natural-horf',seed:1,floor:0,room:2}]) {
   const natural=test.seed!==undefined;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-12.0.0`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.cover)params.set('enemy-terrain','cover');
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let bullet=false,capture=false,position;
   for(let frame=15;frame<=360;frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe;assert.equal(p.type,12);assert.equal(p.variant,0);assert.equal(p.resident.natural,natural);
    if(frame===15){assert(Math.abs(p.hp-32)<.01);position={x:p.x,z:p.z};if(natural){assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);assert(p.actors.length>1);}}
    assert(Math.hypot(p.x-position.x,p.z-position.z)<.001,'Horf remains stationary');
    const shots=p.bullets.filter(b=>b.owner===p.entity);
    for(const b of shots){assert.equal(b.kind,0);assert(Math.abs(Math.hypot(b.vx,b.vz)-21)<.01);bullet=true;}
    if(test.cover){assert.equal(p.shots,0);assert.equal(shots.length,0);}
    if(!capture&&frame>=180&&(shots.length||test.cover)) {s.capture=`${out}/${test.name}.png`;await page.screenshot({path:s.capture});capture=true;}
    samples.push(s);
   }
   if(!test.cover){assert(bullet);assert(samples.at(-1).probe.shots>=3);}
   assert(capture);assert.deepEqual(errors,[]);checks.push({case:test.name,bullet,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Default-content Horf health, stationary behavior, actual21-unit/s shots, solid cover and seeded opening-stage resident in Original style. No controlled-target/status/full balance/performance certification.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
