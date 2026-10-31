// Current production controller in isolated, obstructed, natural and owned cases.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_MAGGOT_OUTPUT;
 assert(out);fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{window.__trace=[];window.__captures={};window.__capture=frame=>{
  if(frame>1000||!Module.enemyProbe)return;const p=Module.enemyProbe;
  window.__trace.push({frame,probe:JSON.parse(JSON.stringify(p))});
  if([0,140,280,350].includes(frame))window.__captures[frame]=Module.canvas.toDataURL('image/png');
 };});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Production normal-clock Small Maggot controller; Original style, no page-local content overrides. Rotten parent remains provisional.'},null,2)+'\n');
 try {
  const entries=[{name:'isolated',frames:360,death:330},{name:'cover',frames:480,cover:true},
   {name:'natural',frames:300,natural:true,seed:0,floor:5,room:1},{name:'brood',frames:420,brood:true}]
   .filter(t=>!process.env.DEATHWARD_MAGGOT_CASES||process.env.DEATHWARD_MAGGOT_CASES.split(',').includes(t.name));
  assert(entries.length>0,'at least one known scenario required');
  for(const t of entries) {
   const result={...t,pass:false};checks.push(result);persist();console.log('START',t.name);
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',
    scene:`${t.natural?'resident':'enemy'}-${t.brood?'10.3.3':'853.0.0'}`,'enemy-camera-follow':''});
   if(t.natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   if(t.cover)q.set('enemy-terrain','cover');
   if(t.name==='isolated'){q.set('enemy-player-at','1:0:4');q.set('enemy-hit',`${t.death}:1000`);}
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8767/'}?${q}`);
   await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__capture;});await page.locator('#start').click({noWaitAfter:true});
   let previous=-1,stalled=0;
   for(let n=0;;++n){try{await page.waitForFunction(limit=>Module.state?.error||Module.state?.frame>=limit,t.frames,{timeout:60000});break;}
    catch(e){if(e.name!=='TimeoutError')throw e;const frame=await page.evaluate(()=>Module.state?.frame);(result.observations??=[]).push({frame});persist();console.log('PROGRESS',t.name,frame);stalled=frame>previous?0:stalled+1;previous=frame;assert(stalled<2&&n<11,'stalled frame counter');}}
   const state=await page.evaluate(()=>({error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),trace:window.__trace,captures:window.__captures}));
   for(const [frame,png] of Object.entries(state.captures)){const path=`${out}/${t.name}-${frame}.png`;fs.writeFileSync(path,Buffer.from(png.split(',')[1],'base64'));state.captures[frame]=path;}
   Object.assign(result,state);persist();assert.equal(state.error,'');assert.equal(state.style,'Original');assert.equal(state.gl,0);assert(state.trace.length>t.frames-20);
   let movement=0,previousActor=null,previousProbe=null,alerted=false,turns=0,children=0,naturalDeath=null;
   for(const {frame,probe:p} of state.trace) {
    if(frame>t.frames)break;
    const bodies=t.brood?p.actors.filter(a=>a.type===853):p.actors.filter(a=>a.entity===p.entity);
    if(t.natural&&bodies.length===0) {
     // This real seeded room contains a Black Knight whose fire jets can kill
     // other monsters. Require the observed pulse/owner and a real threat/kill
     // transition; do not accept an unexplained disappearance or change the room.
     if(!naturalDeath) {
      assert(previousActor&&previousProbe);assert.equal(p.kills,previousProbe.kills+1);assert.equal(p.threats,previousProbe.threats-1);
      const wave=p.fireWaves.find(w=>p.actors.some(a=>a.entity===w.source&&a.type===41&&a.variant===4)&&
       w.jets.some(j=>Math.hypot(j.x-previousActor.x,j.z-previousActor.z)<=w.radius+previousActor.radius+.25&&
        j.pulses>(previousProbe.fireWaves.find(old=>old.id===w.id)?.jets.find(old=>old.x===j.x&&old.z===j.z)?.pulses??0)));
      assert(wave,'natural death requires an actual overlapping Black Knight fire pulse');assert(previousActor.hp<=32);
      naturalDeath={frame,source:wave.source,cause:'Black Knight fire jet,32Flame damage; reproduced in native diagnostic'};
     }
    } else if(!t.brood&&(!t.death||frame<t.death))assert.equal(bodies.length,1);
    for(const a of bodies) {
     assert.equal(a.type,853);assert.equal(a.variant,0);assert.equal(a.subtype,0);assert(a.smallMaggot);
     assert(Math.abs(a.maxHp-32)<.001);assert(a.hp>0&&a.hp<=a.maxHp);
     assert(a.smallMaggot.walkFrame>=0&&a.smallMaggot.walkFrame<13);
     if(a.smallMaggot.ticks===0) {
      assert(t.brood,'only a newly flushed offspring can await its first source update');
      assert.equal(a.smallMaggot.cooldown,0);assert.equal(a.smallMaggot.force,0);assert.equal(a.smallMaggot.turns,0);
     } else assert(a.smallMaggot.cooldown>=1&&a.smallMaggot.cooldown<=39);
     assert(a.smallMaggot.force>=0&&a.smallMaggot.force<=.90001);assert(Math.abs(a.smallMaggot.curve)<=2*Math.PI/180+.00001);
     if(a.smallMaggot.turns>0)assert(a.smallMaggot.force>=.14999);
     alerted||=a.smallMaggot.alert;turns=Math.max(turns,a.smallMaggot.turns);
     assert(!p.bullets.some(b=>b.owner===a.entity));
     if(t.brood){assert.equal(a.summoner,p.entity);children=Math.max(children,bodies.length);}
     else {if(previousActor)movement+=Math.hypot(a.x-previousActor.x,a.z-previousActor.z);previousActor=a;assert(!p.groundBlocked);}
    }
    if(t.natural){assert(p.resident.natural);assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);assert.deepEqual(p.resident.source,[853,0,0]);}
    else {assert.equal(p.shots,0);if(t.death&&frame>=t.death){assert.equal(p.threats,0);assert.equal(p.kills,1);}else assert.equal(p.kills,0);}
    previousProbe=p;
   }
   assert(turns>0);if(t.brood)assert(children>=2&&children<=6);else assert(movement>.2);
   if(t.name==='isolated')assert(alerted);
   if(t.natural)assert(naturalDeath,'retain the discovered fire-jet interaction as a regression');
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,movement,alerted,turns,children,naturalDeath});persist();console.log('PASS',t.name);
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
