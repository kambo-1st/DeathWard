const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_CRACKLE_OUTPUT||'artifacts/crackle';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const test of [
   {name:'crackle-physical-fire-jets'},
   {name:'crackle-jets-survive-owner',force:true,kill:20},
   {name:'natural-crackle',seed:20,floor:2,room:5}
  ]) {
   const natural=test.seed!==undefined;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-87.1.0`});
   if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
   if(test.kill)params.append('enemy-hit',`${test.kill}:129`);
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
   if(test.force)assert(await page.evaluate(()=>{
    const p='/assets/mechanics/gurgle.mechanics',s=Module.FS.readFile(p,{encoding:'utf8'});
    const t=s.replace('lob_walker 87.1.0 60 ','lob_walker 87.1.0 1 ');Module.FS.writeFile(p,t);return s!==t;
   }),'test-only certain acquisition applied before loading');
   await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let bullet=false,jets=false,deadJets=false,capture=false;
   const end=test.kill?180:660;
   for(let frame=15;frame<=end;frame+=5) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    // Screenshots can span multiple rendered frames; sample actual frame below.
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe;assert.equal(p.type,87);assert.equal(p.variant,1);assert.equal(p.resident.natural,natural);
    if(frame===15){assert(Math.abs(p.hp-128)<.01);if(natural){assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);assert(p.actors.length>1);}}
    for(const b of p.bullets.filter(b=>b.owner===p.entity)){assert.equal(b.kind,9);assert.equal(b.blastRadius,0);assert(Math.abs(b.gravity-36.9)<.01);bullet=true;}
    const waves=p.fireWaves.filter(w=>w.source===p.entity);
    for(const w of waves) {
     assert.equal(w.jetStepFrames,2);assert.equal(w.speed,45);assert.equal(w.range,42);assert.equal(w.radius,2);
     assert(w.jetStep>=0&&w.jetStep<=14&&w.jets.length<=56);
     for(const j of w.jets){assert(j.scale>=.159&&j.scale<=.941);assert(j.pulses>=0&&j.pulses<=3);jets=true;deadJets||=!p.alive;}
    }
    if(test.kill&&s.frame>test.kill){assert.equal(p.alive,false);assert.equal(p.kills,1);assert.equal(p.threats,0);}
    if(!natural)assert.equal(p.statue.explosions,0,'fire jets are not explosive blasts');
    const visible=waves.some(w=>w.jets.some(j=>j.age<.14));
    if(!capture&&visible&&(s.frame>=180||test.kill)) {
     s.capture=`${out}/${test.name}.png`;await page.screenshot({path:s.capture});capture=true;
    }
    samples.push(s);
   }
   assert(bullet&&jets,'physical payload and separate jets observed');assert(capture,'visible fire-jet capture');
   if(test.kill)assert(deadJets,'source-free jets retain producer identity after death');
   assert.deepEqual(errors,[]);checks.push({case:test.name,override:test.force?'test-only chance divisor1; production60 unchanged':null,bullet,jets,deadJets,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Crackle physical lob, discrete fire jets, producer loss, and actual unforced dry-quarry resident. Death fixture forces only acquisition probability. Full source movement/status, balance and rendered performance remain open.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
