const {chromium}=require('playwright'),assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_HARD_HOST_OUTPUT;fs.mkdirSync(out,{recursive:true});
 const witness=JSON.parse(fs.readFileSync(process.env.DEATHWARD_HARD_HOST_WITNESS));
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),checks=[],errors=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const name of ['near','far','resident']) {
   const natural=name==='resident',params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-27.3.0`});
   if(natural){params.set('resident-seed',witness.seed);params.set('resident-floor',witness.floor);}
   if(name==='far')params.set('enemy-player-at','1:0:14');
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${params}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   console.log('START',name,'browser',await browser.version());let open=false,closed=false,waved=false,hop=false,landed=false;const captures={},samples=[];
   for(let frame=10;frame<=380;frame+=2) {
    await page.waitForFunction(f=>Module.state?.frame>=f,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError(),p:Module.enemyProbe}));samples.push(s);
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(s.p.type,27);assert.equal(s.p.variant,3);
    assert.equal(s.p.resident.natural,natural);if(!natural)assert.equal(s.p.hp,48);
    const actor=s.p.actors.find(a=>a.id===s.p.entity||a.entity===s.p.entity)||s.p.actors.find(a=>a.type===27&&a.variant===3);assert(actor?.host);
    const h=actor.host;if(h.exposed){open=true;assert(h.frame>=10&&h.frame<54);}else closed=true;
    const wave=s.p.hazards.find(w=>w.owner===s.p.entity&&w.rockWave);
    if(wave){waved=true;assert(wave.rockWave.frame%2===0);assert.equal(wave.radius,2);assert(h.fired||h.frame<0);}
    assert(!s.p.bullets.some(b=>b.owner===s.p.entity),'Hard Host emits no generic bullets');
    if(s.p.playerLaunch.active&&s.p.playerLaunch.height>0)hop=true;
    if(hop&&!s.p.playerLaunch.active)landed=true;
    const shot=natural?(frame>=100?'resident':null):h.exposed&&frame>=60?'open':wave&&wave.rockWave.frame>=2?'wave':!h.exposed&&frame>=180?'closed':null;
    if(shot&&!captures[shot]){captures[shot]=`${out}/${name}-${shot}.png`;await page.screenshot({path:captures[shot]});}
   }
   assert(open&&closed);if(!natural){assert(waved);assert.equal(hop,name==='near');if(name==='near')assert(landed);assert(captures.open&&captures.wave&&captures.closed);}
   else {assert.equal(samples[0].p.resident.room,witness.room);assert(captures.resident);}
   assert.deepEqual(errors,[]);checks.push({case:name,open,closed,waved,hop,landed,captures,samples});console.log('PASS',name);
  }
 } finally {fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Production WASM Hard Host isolated near/far and actual seeded resident: armor events, physical crush generator, absent bullets, hop/landing and Original appearance. Partial acceptance.'},null,2)+'\n');await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
