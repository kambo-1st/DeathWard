const {chromium}=require('playwright'),assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_TRITE_OUTPUT;fs.mkdirSync(out,{recursive:true});
 const witness=JSON.parse(fs.readFileSync(process.env.DEATHWARD_TRITE_WITNESS));
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),checks=[],errors=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const name of ['isolated','cover','river','resident']) {
   const natural=name==='resident',params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-29.1.0`});
   if(natural){params.set('resident-seed',witness.seed);params.set('resident-floor',witness.floor);}
   if(name==='cover')params.set('enemy-terrain','hop-cover');if(name==='river')params.set('enemy-terrain','river');
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${params}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   console.log('START',name,'browser',await browser.version());
   console.log('GL',await page.evaluate(()=>{const g=Module.ctx,e=g.getExtension('WEBGL_debug_renderer_info');return e?g.getParameter(e.UNMASKED_RENDERER_WEBGL):g.getParameter(g.RENDERER);}));
   const captures={},samples=[];let air=false,ground=false,water=false,hops=0,landings=0,peak=.85,distance=0,previous;
   for(let frame=10;frame<=700;frame+=2) {
    await page.waitForFunction(f=>Module.state?.frame>=f,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError(),p:Module.enemyProbe}));samples.push(s);
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(s.p.type,29);assert.equal(s.p.variant,1);
    assert.equal(s.p.resident.natural,natural);const a=s.p.actors.find(a=>a.entity===s.p.entity);assert(a?.targetHop);assert(Math.abs(a.maxHp-32)<.01);
    if(!natural)assert.equal(s.p.shots,0,'Trite invents no ranged attack');assert(!s.p.flightBlocked,'body stays inside wall boundary');
    const r=a.targetHop;assert(r.bonus>=0&&r.bonus<120);air||=r.airborne;ground||=!r.airborne;water||=s.p.waterBlocked;
    hops=Math.max(hops,r.hops);landings=Math.max(landings,r.landings);peak=Math.max(peak,a.y);
    if(previous)distance+=Math.hypot(a.x-previous.x,a.z-previous.z);previous=a;
    const shot=name==='isolated'?(frame>=90&&!r.airborne&&r.frame<0?'ground':r.airborne&&r.frame>=8&&r.frame<=12?'air':hops>0&&r.frame>=0&&r.frame<4?'prepare':null):
     name==='cover'?(r.airborne&&a.y>3?'cover':null):name==='river'?(r.airborne&&s.p.waterBlocked?'river':null):frame>=100?'resident':null;
    if(shot&&!captures[shot]){captures[shot]=`${out}/${name}-${shot}.png`;await page.screenshot({path:captures[shot]});}
   }
   assert(air&&ground&&hops>=1&&landings>=1&&distance>.5,'physical hop cycle actually runs');
   if(name==='isolated')assert(captures.ground&&captures.air&&captures.prepare);
   if(name==='cover')assert(captures.cover&&peak>3,'actual body rises above cover');
   if(name==='river')assert(captures.river&&water,'actually crosses deep-water cells');
   if(natural){assert.equal(samples[0].p.resident.room,witness.room);assert(captures.resident);}
   assert.deepEqual(errors,[]);checks.push({case:name,hops,landings,peak,distance,water,captures,samples});console.log('PASS',name);
  }
 } finally {fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Production WASM Trite source-frame destination hopping: isolated lifecycle, real cover and river traversal, natural resident and Original appearance. Native tests separately verify numeric recurrence and lifecycle. Full six-gate acceptance remains open.'},null,2)+'\n');await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
