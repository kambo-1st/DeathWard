// Dedicated Gaper movement/HP/awareness in actual production WASM.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_GAPER_OUTPUT;
 assert(out);fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|DeathWard:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{window.__trace=[];window.__captures={};window.__capture=frame=>{
  if(frame>1500||!Module.enemyProbe)return;const p=Module.enemyProbe;
  window.__trace.push({frame,probe:JSON.parse(JSON.stringify(p))});
  const a=p.actors.find(a=>a.entity===p.entity),r=a?.gaper;if(!r)return;
  const kinds=[];if(a.variant===0&&r.eyeOpenness===0)kinds.push('closed');
  if(a.variant===0&&r.eyeOpenness===1)kinds.push('open');
  if(a.variant!==0&&frame>=20)kinds.push('walking');
  for(const k of kinds)if(!window.__captures[k])window.__captures[k]={frame,png:Module.canvas.toDataURL('image/png')};
 };});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Production Original-style Gaper normal-clock movement/HP/activation; no full status, balance or performance acceptance.'},null,2)+'\n');
 try {
  const entries=JSON.parse(process.env.DEATHWARD_GAPER_ENTRIES||JSON.stringify([{name:'frowning',variant:0,frames:180},{name:'ordinary',variant:1,frames:180},{name:'flaming',variant:2,frames:180},{name:'frowning-cover',variant:0,cover:true,frames:480}]));
  for(const t of entries) {
   const result={...t,pass:false};checks.push(result);persist();console.log('START',t.name);
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`${t.natural?'resident':'enemy'}-10.${t.variant}.0`,'enemy-camera-follow':''});
   if(t.natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   if(t.cover){assert(!t.natural);q.set('enemy-terrain','cover');}
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8767/'}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__capture;});await page.locator('#start').click({noWaitAfter:true});
   let previous=-1,stalled=0;
   for(let n=0;;++n) {
    try{await page.waitForFunction(limit=>Module.state?.error||Module.state?.frame>=limit,t.frames,{timeout:60000});break;}
    catch(e){if(e.name!=='TimeoutError')throw e;const frame=await page.evaluate(()=>Module.state?.frame);(result.observations??=[]).push({frame});persist();console.log('PROGRESS',t.name,frame);stalled=frame>previous?0:stalled+1;previous=frame;assert(stalled<2&&n<11,'no progress or observation limit');}
   }
   const state=await page.evaluate(()=>({error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError(),trace:window.__trace,captures:window.__captures}));
   for(const [kind,c] of Object.entries(state.captures)){c.path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(c.path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;}
   Object.assign(result,state);persist();assert.equal(state.error,'');assert.equal(state.style,'Original');assert.equal(state.gl,0);assert(state.trace.length>t.frames-20);
   let movement=0,previousActor=null,head=0,closedCover=false,awake=false;
   for(const {probe:p} of state.trace) {
    const a=p.actors.find(a=>a.entity===p.entity);assert(a?.gaper);assert.equal(a.type,10);assert.equal(a.variant,t.variant);assert(!p.groundBlocked);
    assert(Math.abs(a.maxHp-(t.variant===2?28.8:32))<.001);assert(a.hp>0&&a.hp<=a.maxHp);assert(a.gaper.walkFrame>=0&&a.gaper.walkFrame<22);
    if(t.variant===0) {
     assert(a.gaper.headFrame>=head&&a.gaper.headFrame<=19);head=a.gaper.headFrame;
     assert(Math.abs(a.gaper.force-(head>0?.72:.6))<.00001);awake||=head>0;
     closedCover||=!a.gaper.directPath&&!a.gaper.wakeStarted&&a.gaper.eyeOpenness===0;
    }else assert(Math.abs(a.gaper.force-(t.variant===1?.498:.5478))<.00001);
    if(previousActor)movement+=Math.hypot(a.x-previousActor.x,a.z-previousActor.z);previousActor=a;
    assert(!p.bullets.some(b=>b.owner===p.entity));
    if(!t.natural){assert.equal(p.shots,0);assert.equal(p.kills,0);assert.equal(p.threats,1);}
    else {assert(p.resident.natural);assert.equal(p.resident.floor,t.floor);assert.equal(p.resident.room,t.room);if(t.variant===2){assert(p.resident.scorched);assert(p.resident.source[0]===10&&[0,1].includes(p.resident.source[1])&&p.resident.source[2]===0);}else assert.deepEqual(p.resident.source,[10,t.variant,0]);}
   }
   assert(movement>1);if(t.variant===0){assert(awake);assert(result.captures.open);if(!t.natural)assert(result.captures.closed);}
   if(t.cover)assert(closedCover);assert.deepEqual(errors,[]);Object.assign(result,{pass:true,movement,closedCover,awake});persist();console.log('PASS',t.name);
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
