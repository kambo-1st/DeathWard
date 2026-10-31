// Actual production WASM: ordinary Maggot locomotion and real seeded residents.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright');
 const out=process.env.DEATHWARD_WALKER_OUTPUT;fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),checks=[],errors=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const cases=[{name:'maggot'},{name:'maggot-cover',terrain:'cover'},{name:'maggot-river',terrain:'river'},
  {name:'maggot-death',death:true},{name:'resident-quarry',seed:0,floor:2,room:2},{name:'resident-storm',seed:0,floor:5,room:1}];
 try {
  for(const t of cases) {
   if(process.env.DEATHWARD_WALKER_CASES&&!process.env.DEATHWARD_WALKER_CASES.split(',').includes(t.name))continue;
   const natural=t.seed!==undefined;
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon','enemy-camera-follow':'',scene:`${natural?'resident':'enemy'}-21.0.0`});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   if(t.terrain)q.set('enemy-terrain',t.terrain);if(t.death)q.set('enemy-hit','180:10000');
   const result={name:t.name,pass:false,samples:[],captures:{}};checks.push(result);console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   let movement=0,previous,dead=false;
   for(let f=8;f<=300;f+=3) {
    await page.waitForFunction(n=>Module.state?.error||Module.state?.frame>=n,f,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),p:Module.enemyProbe}));
    const p=s.p,a=p.actors.find(a=>a.entity===p.entity),bullets=p.bullets.filter(b=>b.owner===p.entity);
    result.samples.push({frame:s.frame,error:s.error,style:s.style,gl:s.gl,actor:a,resident:p.resident,ground:p.groundBlocked,water:p.waterBlocked,kills:p.kills,bullets});
    assert.equal(s.error,'');assert.equal(s.style,'Original');assert.equal(s.gl,0);
    assert.equal(p.resident.natural,natural);assert.equal(bullets.length,0,'contact walker never inherits Spitty projectiles');
    if(natural){assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);}
    if(a) {
     assert.equal(a.type,21);assert.equal(a.variant,0);assert(Math.abs(a.maxHp-48)<.01);
     assert(a.cardinalWalker?.ticks>0&&!a.spitty,'dedicated contact-only controller');
     assert(!p.groundBlocked&&!p.waterBlocked,'grounded path remains physically legal');
     if(previous)movement+=Math.hypot(a.x-previous.x,a.z-previous.z);previous=a;
    } else {assert(t.death&&s.frame>=180,'only scripted death removes the actor');assert.equal(p.kills,1);dead=true;}
    const capture=dead?'death':s.frame>=90&&a?'walk':null;
    if(capture&&!result.captures[capture]){result.captures[capture]=`${out}/${t.name}-${capture}.png`;await page.screenshot({path:result.captures[capture]});}
    if(movement>.5&&(t.death?dead&&result.captures.death:s.frame>=240&&result.captures.walk))break;
   }
   assert(movement>.5,'actual locomotion');if(t.death)assert(dead);
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,movement,dead});console.log('PASS',t.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({browser:await browser.version(),checks,errors,
   scope:'Production WASM source health, dedicated non-shooting cardinal movement, physical cover/river legality, ordinary death and two actual seeded source-equivalent bands; partial acceptance evidence.'},null,2)+'\n');
  await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
