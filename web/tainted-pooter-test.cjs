const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_TAINTED_POOTER_OUTPUT||'artifacts/tainted-pooter';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const near=(a,b,message)=>assert(Math.abs(a-b)<.004,`${message}: ${a} vs ${b}`);
 try {
  for(const test of [
   {name:'tainted-volley'},
   {name:'tainted-cover',terrain:'cover'},
   {name:'tainted-river',terrain:'river',frames:1800},
   {name:'tainted-skatole',suppressed:true},
   {name:'tainted-death',kill:180}
  ]) {
   if(process.env.DEATHWARD_TAINTED_POOTER_CASES&&!process.env.DEATHWARD_TAINTED_POOTER_CASES.split(',').includes(test.name))continue;
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:'enemy-14.2.0'});
   if(test.terrain)params.set('enemy-terrain',test.terrain);
   if(test.suppressed)params.set('enemy-item','isaac:collectible:9');
   if(test.kill)params.set('enemy-hit',`${test.kill}:10000`);
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});
   const samples=[];let capture=false,quad=false,backPair=false,distance=0,previous,elevated=false,overWater=false,returned=false;
   const roots=new Map(),children=new Map();
   for(let frame=10;frame<=(test.frames||420);frame+=2) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe,actor=p.actors.find(a=>a.entity===p.entity);assert.equal(p.resident.natural,false);
    if(test.kill&&s.frame>=test.kill){
     if(s.frame>=test.kill+2||!p.alive){assert(!p.alive);assert.equal(p.kills,1);assert.equal(p.threats,0);}
     else assert(actor?.adaptiveArmor?.pending>0,'lethal damage waits for next30Hz batch');
    }
    else {
     assert(actor);assert.equal(actor.type,14);assert.equal(actor.variant,2);near(actor.hp,240,'source-scaled HP');
     assert.equal(p.flightBlocked,false);
     if(previous)distance+=Math.hypot(actor.x-previous.x,actor.z-previous.z);previous=actor;
     if(actor.y>2)elevated=true;
     if(p.waterBlocked)overWater=true;else if(overWater)returned=true;
     assert.equal(p.kills,0);assert.equal(p.threats,1);
    }
    const shots=p.bullets.filter(b=>b.owner===p.entity),large=shots.filter(b=>b.kind!==0),small=shots.filter(b=>b.kind===0);
    if(test.suppressed)assert.equal(shots.length,0);
    for(const b of large){near(b.radius,.308,'large root radius');near(b.damage,10,'root damage');roots.set(b.entity,b);}
    for(const b of small){near(b.radius,.22,'default child radius');near(b.damage,10,'child damage');near(Math.hypot(b.vx,b.vy,b.vz),30,'child speed');near(b.vy,0,'child physical impact elevation');}
    if(large.length===4&&!quad) {
     const group=[...large].sort((a,b)=>a.entity-b.entity),[a,b]=group;
     const norm=Math.hypot(a.vx+b.vx,a.vz+b.vz),fx=(a.vx+b.vx)/norm,fz=(a.vz+b.vz)/norm;
     const horizontal=Math.sqrt(21*21-a.vy*a.vy),coeffs=[[.99,.1668],[.99,-.1668],[.8226,.43956],[.8226,-.43956]];
     group.forEach((shot,i)=>{near(shot.vy,a.vy,'shared physical pitch');near((shot.vx*fx+shot.vz*fz)/horizontal,coeffs[i][0],'forward coefficient');near((-shot.vx*fz+shot.vz*fx)/horizontal,coeffs[i][1],'side coefficient');});quad=true;
    }
    const born=small.filter(b=>!children.has(b.entity));
    if(born.length===2&&!backPair) {
     const [a,b]=born,expected=Math.cos(48*Math.PI/180);
     const pairDot=(a.vx*b.vx+a.vz*b.vz)/900;
     const bx=a.vx+b.vx,bz=a.vz+b.vz,bn=Math.hypot(bx,bz);
     const match=[...roots.values()].find(r=>{
      const rn=Math.hypot(r.vx,r.vz),cosine=(r.vx*bx+r.vz*bz)/(rn*bn);
      return cosine<-.999&&Math.hypot((a.x+b.x)/2-r.x,(a.z+b.z)/2-r.z)<4;
     });
     if(match&&Math.abs(pairDot-expected)<.004)backPair=true;
    }
    for(const b of small)children.set(b.entity,b);
    if(!capture&&frame>=24&&(test.suppressed||large.length===4)) {s.capture=`${out}/${test.name}.png`;await page.screenshot({path:s.capture});capture=true;}
    samples.push(s);
    if(test.terrain==='river'&&overWater&&returned&&quad&&backPair&&capture)break;
   }
   assert(distance>.2,'buzzing actor moves');assert(capture,'scene captured');
   if(!test.suppressed){assert(quad,'owned four-shot coefficients observed');assert(backPair,'two nonrecursive children split backward at +/-24 degrees');}
   if(test.terrain==='cover')assert(elevated,'physical body flies above cover');
   if(test.terrain==='river')assert(overWater&&returned,'physical body crosses deep river and returns to land');
   assert.deepEqual(errors,[]);
   checks.push({case:test.name,distance,quad,backPair,elevated,overWater,returned,roots:roots.size,children:children.size,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Five isolated scenes using production mechanics and Original visuals: source-scaled HP, buzzing, four-shot source coefficients and physical pitch, child size/speed/backward angles, cover/river, Skatole and one death. No natural Ascent route exists yet; no reachability, full balance or controlled performance acceptance is claimed.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
