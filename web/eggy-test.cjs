const {chromium}=require('playwright'),assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_EGGY_OUTPUT;fs.mkdirSync(out,{recursive:true});
 const witness=JSON.parse(fs.readFileSync(process.env.DEATHWARD_EGGY_WITNESS));
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),checks=[],errors=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const name of (process.env.DEATHWARD_EGGY_CASES||'isolated,cover,death,blast,resident').split(',')) {
   const natural=name==='resident',dying=name==='death'||name==='blast';
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-29.2.0`});
   if(natural){params.set('resident-seed',witness.seed);params.set('resident-floor',witness.floor);}
   if(name==='cover')params.set('enemy-terrain','hop-cover');
   if(dying){params.set(name==='blast'?'enemy-blast':'enemy-hit','100:1000');params.append('enemy-hit','120:1000');}
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${params}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   console.log('START',name,'browser',await browser.version());
   const captures={},samples=[];let air=false,patches=0,peak=.85,released=0,maxChildren=0,finished=false;
   const result={case:name,pass:false,captures,samples};checks.push(result);
   for(let frame=10;frame<=(dying?330:500);frame+=2) {
    await page.waitForFunction(f=>Module.state?.frame>=f,frame,{timeout:90000});
    const s=await page.evaluate(()=>{
     const p=Module.enemyProbe;
     return {frame:Module.state.frame,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError(),
      p:{type:p.type,variant:p.variant,entity:p.entity,alive:p.alive,kills:p.kills,threats:p.threats,shots:p.shots,
       flightBlocked:p.flightBlocked,resident:p.resident,hazards:p.hazards,sourceStage:p.sourceStage,
       actors:p.actors.map(a=>({entity:a.entity,type:a.type,variant:a.variant,hp:a.hp,maxHp:a.maxHp,summoner:a.summoner,
        x:a.x,y:a.y,z:a.z,eggy:a.eggy,targetHop:a.targetHop,swarmSpider:a.swarmSpider}))}};
    });samples.push(s);
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(s.p.type,29);assert.equal(s.p.variant,2);
    assert.equal(s.p.resident.natural,natural);const a=s.p.actors.find(a=>a.entity===s.p.entity);
    if(!natural)assert.equal(s.p.shots,0,'Eggy invents no ranged attack');
    if(a) {
     assert(a.eggy&&a.targetHop);assert(!s.p.flightBlocked);
     const stage=s.p.sourceStage,m=Math.min(stage,4)+.8*Math.max(0,Math.min(5,stage-5));
     assert(Math.abs(a.maxHp-(20+2*m)*3.2)<.01);
     air||=a.targetHop.airborne;patches=Math.max(patches,a.eggy.patches);peak=Math.max(peak,a.y);released=Math.max(released,a.eggy.released);
     if(a.eggy.dying){assert.equal(s.p.kills,0);assert(a.hp>0&&a.hp<1);}
    }
    const children=s.p.actors.filter(a=>a.summoner===s.p.entity);maxChildren=Math.max(maxChildren,children.length);
    for(const child of children)assert(child.type===884&&child.swarmSpider,'offspring use dedicated Swarm controller');
    if(dying&&!a&&s.frame>240){assert.equal(s.p.kills,1);assert.equal(children.length,14);assert.equal(s.p.threats,14);finished=true;}
    let shot;
    if(name==='isolated')shot=a&&a.targetHop.airborne&&s.frame>=90?'air':a&&patches>0&&s.frame>=100?'creep':null;
    else if(name==='cover')shot=a&&a.targetHop.airborne&&a.y>3?'cover':null;
    else if(dying)shot=a?.eggy.dying&&released>=8?'release':finished?'children':null;
    else if(natural&&s.frame>=100)shot='resident';
    if(shot&&!captures[shot]){captures[shot]=`${out}/${name}-${shot}.png`;await page.screenshot({path:captures[shot]});}
   }
   if(dying)assert(finished&&released===14&&maxChildren===14&&captures.release&&captures.children);
   else assert(air&&patches>=1,'source hopping and landing patch observed');
   if(name==='isolated')assert(captures.air&&captures.creep);
   if(name==='cover')assert(captures.cover&&peak>3);
   if(natural){assert.equal(samples[0].p.resident.room,witness.room);assert(captures.resident);}
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,patches,peak,released,maxChildren,finished});console.log('PASS',name);
  }
 } finally {fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Production WASM Eggy ordinary hops/white creep, physical cover, timed14-Swarm release after gun/blast damage and natural resident. Native fixtures verify exact timing, pending birth phase and completion. Full six-gate acceptance remains open.'},null,2)+'\n');await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
