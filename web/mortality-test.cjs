// Damage/death slice only. These fixtures do not certify legacy movement/attacks.
const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_MORTALITY_OUTPUT||'artifacts/mortality';fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],checks=[];
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  for(const test of [
   {name:'gurgle-player-bomb',id:'87.0.0',args:[['enemy-blast','20:10']],afterHp:118},
   {name:'gurgle-environment-fire',id:'87.0.0',args:[['enemy-fire','20']],afterHp:128},
   {name:'crackle-environment-fire',id:'87.1.0',args:[['enemy-fire','20']],afterHp:128},
   {name:'splasher-environment-fire',id:'238.0.0',args:[['enemy-fire','20']],afterHp:28.4},
   {name:'gurgle-overkill',id:'87.0.0',args:[['enemy-hit','20:208']],dead:true},
   {name:'crackle-no-morph',id:'87.1.0',args:[['enemy-hit','20:129']],dead:true},
   {name:'gurgle-in-place-morph',id:'87.0.0',args:[['enemy-hit','20:129'],['enemy-hit','120:100']],certain:true}
  ]) {
   const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`enemy-${test.id}`});
   for(const [key,value] of test.args)params.append(key,value);
   await page.goto(`${process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/'}?${params}`);
   await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
   if(test.certain) {
    // Force just the chance in the browser's disposable preloaded filesystem.
    // Production1500 remains unchanged; native tests exercise the seeded15% roll.
    const edited=await page.evaluate(()=>{
     const path='/assets/mechanics/gurgle.mechanics',before=Module.FS.readFile(path,{encoding:'utf8'});
     const after=before.replace('1500 80','10000 80');Module.FS.writeFile(path,after);return after!==before;
    });assert(edited,'external test-only probability fixture applied before library load');
   }
   await page.locator('#start').click({noWaitAfter:true});const samples=[];
   for(const frame of [10,30,90,140]) {
    await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
    assert(s.frame<frame+10);assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);
    const p=s.probe,actor=p.actors.find(a=>a.entity===p.entity||a.id===p.entity);
    if(frame===10){assert(p.alive);assert(Math.abs(p.hp-(test.id.startsWith('238')?38.4:128))<.01);}
    else if(test.certain) {
     if(frame<120){assert(p.alive);assert.equal(p.kills,0);assert.equal(p.threats,1);assert(actor&&actor.type===238,'same entity became Splasher');assert(Math.abs(p.hp-38.4)<.01);}
     else {assert.equal(p.alive,false);assert.equal(p.kills,1);assert.equal(p.threats,0);}
    } else if(test.dead){assert.equal(p.alive,false);assert.equal(p.kills,1);assert.equal(p.threats,0);}
    else if(frame===30)assert(Math.abs(p.hp-test.afterHp)<.01,`${test.name}: ${p.hp}`);
    if(frame===90){s.capture=`${out}/${test.name}.png`;await page.screenshot({path:s.capture});}
    samples.push(s);
   }
   assert.deepEqual(errors,[]);checks.push({case:test.name,content_override:test.certain?'test-only100% morph chance; default15% tested natively':null,samples});console.log('PASS',test.name);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({checks,errors,scope:'Mortality only: source fire/player-bomb exceptions, overkill, Crackle exclusion and forced-probability in-place morph. No attack/movement/ordinary placement/balance/performance acceptance.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
