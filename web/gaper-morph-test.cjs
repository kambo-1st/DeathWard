// Isolated death-transformation slice. Native tests exercise production
// probabilities; explicit browser-only overrides select each morph deterministically.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_GAPER_OUTPUT;
 assert(out,'DEATHWARD_GAPER_OUTPUT is required');fs.mkdirSync(out,{recursive:true});
 const checks=[],errors=[],browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 await page.addInitScript(()=>{window.__samples=[];window.__capture=frame=>{
  if(![10,30,90,140].includes(frame)||!Module.enemyProbe)return;
  window.__samples.push({frame,probe:JSON.parse(JSON.stringify(Module.enemyProbe)),style:Module.state.visualStyleName,
   error:Module.state.error,gl:Module.ctx.getError(),png:frame===90?Module.canvas.toDataURL('image/png'):null});
 };});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,
  scope:'Gaper mortality only. Browser-only probability/choice overrides explicitly recorded. No movement, source HP, balance, performance or complete-port acceptance.'},null,2)+'\n');
 try {
  const cases=[{name:'frowning-pacer',variant:0,child:1},{name:'gaper-gusher',variant:1,child:0},{name:'flaming-gusher',variant:2,child:0},
   ...[0,1,2].map(variant=>({name:`overkill-${variant}`,variant,overkill:true}))];
  for(const t of cases) {
   const result={...t,pass:false};checks.push(result);persist();console.log('START',t.name);
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',scene:`enemy-10.${t.variant}.0`,'enemy-camera-follow':''});
   q.append('enemy-hit',`20:${t.overkill?1000:100}`);
   if(!t.overkill)q.append('enemy-hit','120:100');
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8767/'}?${q}`);
   await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   if(!t.overkill) {
    // Only this page's disposable preloaded filesystem changes. Production
    // files/probabilities remain unchanged and are sampled in Linux tests.
    result.override=await page.evaluate(({variant,child})=>{
     const path='/assets/mechanics/deaths.mechanics',id=`10.${variant}.0`,target=`11.${child}.0`;
     const before=Module.FS.readFile(path,{encoding:'utf8'}),prefixes=['lethal_morph','lethal_morph_roll','lethal_morph_choice'];
     const kept=before.split('\n').filter(line=>!prefixes.some(p=>line.startsWith(`${p} ${id} `)));
     const rows=[`lethal_morph ${id} ${target} 10000 80 .666666667 1.3`,`lethal_morph_roll ${id} 1 1`,`lethal_morph_choice ${id} ${target} 3`];
     Module.FS.writeFile(path,kept.concat(rows,'').join('\n'));return rows;
    },t);
   }
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__capture;});await page.locator('#start').click({noWaitAfter:true});
   for(let n=0;;++n) {
    try{await page.waitForFunction(()=>Module.state?.error||Module.state?.frame>=145,null,{timeout:60000});break;}
    catch(e){if(e.name!=='TimeoutError')throw e;result.lastFrame=await page.evaluate(()=>Module.state?.frame);persist();console.log('PROGRESS',t.name,result.lastFrame);assert(n<5,'six minute observation limit');}
   }
   const state=await page.evaluate(()=>({error:Module.state.error,samples:window.__samples}));assert.equal(state.error,'');
   for(const s of state.samples)if(s.png){s.capture=`${out}/${t.name}.png`;fs.writeFileSync(s.capture,Buffer.from(s.png.split(',')[1],'base64'));delete s.png;}
   result.samples=state.samples;persist();assert.deepEqual(state.samples.map(s=>s.frame),[10,30,90,140]);
   const original=state.samples[0].probe,entity=original.entity;assert(original.alive);assert.equal(original.kills,0);
   for(const s of state.samples) {
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);const p=s.probe,a=p.actors.find(a=>a.entity===entity);
    if(s.frame===10){assert(a&&a.type===10&&a.variant===t.variant);continue;}
    if(t.overkill||s.frame>=120){assert(!p.alive);assert.equal(p.kills,1);assert.equal(p.threats,0);}
    else {
     assert(p.alive&&a&&a.headless);assert.equal(a.type,11);assert.equal(a.variant,t.child);assert.equal(a.hp,32);assert.equal(a.maxHp,32);
     assert.equal(p.kills,0);assert.equal(p.threats,1);assert(!p.groundBlocked);assert.equal(p.entity,entity);
    }
   }
   assert.deepEqual(errors,[]);result.pass=true;persist();console.log('PASS',t.name);
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
