// Dedicated Spitty controllers in the actual production WASM build.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright');
 const out=process.env.DEATHWARD_SPITTY_OUTPUT;fs.mkdirSync(out,{recursive:true});
 const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const cases=[{name:'spitty',type:31,variant:0},{name:'conjoined',type:243,variant:0},{name:'tainted-spitty',type:31,variant:1},
  {name:'spitty-cover',type:31,variant:0,terrain:'cover'},{name:'spitty-river',type:31,variant:0,terrain:'river'},
  {name:'tainted-death',type:31,variant:1,death:true},
  {name:'resident-spitty',type:31,variant:0,seed:0,floor:4,room:9},
  {name:'resident-conjoined',type:243,variant:0,seed:2,floor:4,room:4},
  {name:'resident-tainted',type:31,variant:1,seed:2,floor:5,room:1}];
 try {
  for(const t of cases) {
   if(process.env.DEATHWARD_SPITTY_CASES&&!process.env.DEATHWARD_SPITTY_CASES.split(',').includes(t.name))continue;
   const natural=t.seed!==undefined,id=`${t.type}.${t.variant}.0`;
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon','enemy-camera-follow':'',scene:`${natural?'resident':'enemy'}-${id}`});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   if(t.terrain)q.set('enemy-terrain',t.terrain);if(t.death)q.set('enemy-hit','240:10000');
   const result={name:t.name,id,pass:false,samples:[],captures:{},captureFrames:{}};checks.push(result);console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   let volley=false,burst=false,stream=false,orbit=false,dead=false,movement=0,previous;
   for(let frame=8;frame<=900;frame+=3) {
    await page.waitForFunction(f=>Module.state?.error||Module.state?.frame>=f,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError(),p:Module.enemyProbe}));
    const p=s.p,a=p.actors.find(a=>a.entity===p.entity),r=a?.spitty,bullets=p.bullets.filter(b=>b.owner===p.entity);
    result.samples.push({frame:s.frame,style:s.style,error:s.error,gl:s.gl,actor:a,resident:p.resident,shots:p.shots,kills:p.kills,ground:p.groundBlocked,water:p.waterBlocked,bullets});
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(p.resident.natural,natural);
    if(natural){assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);}
    if(a) {
     assert(r,'resident uses dedicated controller');assert.equal(a.type,t.type);assert.equal(a.variant,t.variant);
     assert(Math.abs(a.maxHp-(t.type===243?57.6:t.variant?192:32))<.01);
     assert(!p.waterBlocked,'ground walker stays out of deep water');
     assert(!p.groundBlocked,'ground walker starts and remains outside solid terrain');
     if(previous)movement+=Math.hypot(a.x-previous.x,a.z-previous.z);previous=a;
     volley||=r.volleys>0;burst||=r.bursts>0;
    }
    for(const b of bullets) {
     assert(Math.abs(b.flightRetention-.9)<.001);assert(b.gravity>0);
     if(b.sourcePlanarMotion?.direction) {
      orbit=true;assert(t.death,'orbit is a death payload');assert(b.noWallCollision);assert(Math.abs(b.gravity-1.35)<.001);assert(Math.abs(b.radius-.275)<.001);
     } else if(b.sourcePlanarMotion) {
      stream=true;assert.equal(t.variant,1);assert(b.sourcePlanarMotion.acceleration>=.7299&&b.sourcePlanarMotion.acceleration<=1);assert(!b.noWallCollision);
     } else if(!t.variant){assert(Math.min(Math.abs(b.vx),Math.abs(b.vz))<.001,'ordinary shot is cardinal');}
    }
    if(t.death&&s.frame>=240&&!a){dead=true;assert.equal(p.kills,1);}
    const liveOrbit=bullets.some(b=>b.sourcePlanarMotion?.direction);
    const liveStream=bullets.some(b=>b.sourcePlanarMotion&&b.sourcePlanarMotion.direction===0);
    const capture=t.death&&liveOrbit?'death':s.frame>=160&&t.variant&&liveStream?'stream':s.frame>=160&&r?.frame>=0?'attack':s.frame>=180?'scene':s.frame>=90&&a?'open':null;
    if(capture&&!result.captures[capture]){
     result.captures[capture]=`${out}/${t.name}-${capture}.png`;
     await page.screenshot({path:result.captures[capture]});
     result.captureFrames[capture]={before:s.frame,after:await page.evaluate(()=>Module.state.frame)};
    }
    const ready=t.death?dead&&orbit&&result.captures.death:
     volley&&movement>.3&&(t.variant?burst&&stream:true)&&s.frame>=240&&(result.captures.attack||result.captures.stream||result.captures.scene);
    if(ready)break;
   }
   assert(movement>.3,'actual locomotion');if(t.death){assert(dead);assert(orbit);}else {assert(volley,'actual primary volley');if(t.variant){assert(burst);assert(stream);}}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,movement,volley,burst,stream,orbit,dead});console.log('PASS',t.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({browser:await browser.version(),checks,errors,scope:'Production WASM three exact Spitty controllers, primary/moving/death attacks, terrain, source health and real seeded activation. These are smoke/behavior checks, not complete six-gate acceptance.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
