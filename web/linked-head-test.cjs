// Production WASM linked-part lifecycle. Uses ordinary game damage and clocks.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_LINKED_HEAD_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const cases=[{name:'normal',variant:0},{name:'red',variant:2},
  {name:'body-death',variant:0,hit:'enemy-hit'},{name:'red-head-death',variant:2,hit:'enemy-partner-hit'},
  {name:'normal-cover',variant:0,terrain:'cover'},{name:'normal-river',variant:0,terrain:'river'}];
 try {
  for(const t of cases) {
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',
    'enemy-camera-follow':'',scene:`enemy-35.${t.variant}.0`});
   if(t.hit)q.set(t.hit,'30:10000');if(t.terrain)q.set('enemy-terrain',t.terrain);
   const result={name:t.name,pass:false,samples:[],captures:{}};checks.push(result);console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   let pair=false,extended=false,survivor=false,cross=false;
   for(let f=4;f<=180;f+=2) {
    await page.waitForFunction(n=>Module.state?.error||Module.state?.frame>=n,f,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,error:Module.state.error,style:Module.state.visualStyleName,
      gl:Module.ctx.getError(),p:Module.enemyProbe}));result.samples.push(s);
    assert.equal(s.error,'');assert.equal(s.style,'Original');assert.equal(s.gl,0);
    const b=s.p.actors.find(a=>a.type===35&&a.variant===t.variant),h=s.p.actors.find(a=>a.type===35&&a.variant===t.variant+1);
    if(b&&h) {
     pair=true;assert.equal(b.maxHp,80);assert.equal(h.maxHp,t.variant===2?32:80);
     assert(b.linkedHead&&h.linkedHead,'dedicated linked controller');
     assert.equal(s.p.actors.filter(a=>a.type===35&&a.variant===10).length,0,'cord has no independent damageable actors');
     if(b.linkedHead.extended){extended=true;assert.equal(h.linkedHead.neckCount,8);}
     else assert.equal(h.linkedHead.neckCount,0);
    }
    if(t.hit&&s.frame>30) {
     if(t.hit==='enemy-hit') {
      assert(!b);const released=s.p.actors.find(a=>a.type===26&&a.variant===0);
      assert(released&&released.maxHp===64&&released.hp===64,'surviving head becomes full-health Maw');
      assert(!s.p.actors.some(a=>a.type===11),'body death does not add Gusher');survivor=true;
     } else {
      const released=s.p.actors.find(a=>a.type===11&&a.entity===s.p.entity);
      assert(released&&released.maxHp===40&&released.hp===40,'existing body becomes Gusher');assert(!h);survivor=true;
      const shots=s.p.bullets.filter(a=>a.owner!==s.p.entity);
      if(shots.length===4)cross=true;
     }
    }
    const capture=t.hit&&survivor?'survivor':b?.linkedHead.extended?'extended':s.frame>=15?'attached':null;
    if(capture&&!result.captures[capture]){result.captures[capture]=`${out}/${t.name}-${capture}.png`;await page.screenshot({path:result.captures[capture]});}
    if(t.hit?survivor&&(t.hit!=='enemy-partner-hit'||cross):s.frame>=120)break;
   }
   assert(pair,'actual body and separately damageable head observed');
   if(t.hit){assert(survivor);if(t.hit==='enemy-partner-hit')assert(cross,'four real cardinal death projectiles observed');}
   else if(!t.terrain)assert(extended,'actual launched head and eight harmless neck pieces observed');
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,pair,extended,survivor,cross});console.log('PASS',t.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({browser:await browser.version(),checks,errors,
   scope:'Production WASM linked body/head health, throw, cord visibility and damage-driven survivor/death packet. Partial acceptance evidence.'},null,2)+'\n');
  await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
