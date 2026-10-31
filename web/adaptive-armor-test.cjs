const {chromium}=require('playwright');
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_ARMOR_OUTPUT;fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),checks=[],errors=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const [id,hp,strength] of [['14.2.0',240,30],['22.3.0',320,30],['25.6.0',64,10],
    ['29.3.0',256,30],['31.1.0',192,30],['61.7.0',44.8,10],['855.0.0',128,2.5]]) {
   const query=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`enemy-${id}`});
   query.append('enemy-hit','60:50');query.append('enemy-hit','60:50');query.append('enemy-hit','320:10');
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${query}`);
   await page.waitForFunction(()=>Module.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
   await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   const result={id,hp,strength,pass:false,samples:[]};checks.push(result);console.log('START',id);
   // The frame60 burst resolves on source tick31; tick151 expires it.
   // Observe after that boundary and before the next scripted hit.
   for(const frame of [30,80,310,340]) {
    await page.waitForFunction(f=>Module.state?.frame>=f,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,style:Module.state.visualStyleName,error:Module.state.error,
     gl:Module.ctx.getError(),actor:Module.enemyProbe.actors.find(a=>a.entity===Module.enemyProbe.entity)}));
    result.samples.push(s);assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    assert(s.actor?.adaptiveArmor,'live production actor owns armor state');assert(Math.abs(s.actor.maxHp-hp)<.015);
   }
   const [start,burst,quiet,last]=result.samples.map(s=>s.actor),a=burst.adaptiveArmor;
   assert(Math.abs(start.hp-hp)<.015);assert.equal(a.batches,1,'two simultaneous hits use one source batch');
   assert(burst.hp<hp-8&&burst.hp>hp-100,'high burst receives adaptive reduction');
   assert.equal(quiet.adaptiveArmor.samples,120);assert.equal(quiet.adaptiveArmor.dps,0,'rolling history expires');
   assert.equal(quiet.hp,burst.hp);assert.equal(last.adaptiveArmor.batches,2);
   assert(Math.abs(last.hp-(quiet.hp-10))<.015,'isolated low hit after quiet window receives full damage');
   result.capture=`${out}/${id}.png`;await page.screenshot({path:result.capture});
   assert.deepEqual(errors,[]);result.pass=true;console.log('PASS',id,'burst damage',hp-burst.hp);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({browser:await browser.version(),checks,errors,
   scope:'Production WASM seven ordinary armor profiles: batched burst reduction, rolling expiry, quiet low damage and Original rendering. Native tests verify exact formula, bomb flags, chain budgets and room suspension. This does not certify complete enemy behavior or six acceptance gates.'},null,2)+'\n');
  await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
