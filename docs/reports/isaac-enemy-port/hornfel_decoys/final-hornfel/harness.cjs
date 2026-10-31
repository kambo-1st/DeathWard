// Real WASM behavior/capture probes, not a claim of complete Isaac parity.
const {chromium}=require('playwright');
const assert=require('node:assert/strict');
const fs=require('node:fs');
(async()=>{
  const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
    args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
  const page=await browser.newPage({viewport:{width:1280,height:848}});
  const errors=[],checks=[];
  const selected=process.env.DEATHWARD_ENEMY_CASES?.split(',').filter(Boolean);
  page.on('pageerror',e=>errors.push(String(e)));
  page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
  fs.mkdirSync('artifacts/enemy-port',{recursive:true});
  const base=process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/';
  try {
    for(const test of [
      {name:'hornfel',frames:[45,120,240,500]},
      {name:'hornfel-decoy-destruction',decoyBlast:2910,frames:[2890,2940,3060,3240]},
      {name:'hornfel-decoy-contact',decoyContact:2910,frames:[2890,2940,3060,3240]},
      {name:'resident-hornfel-decoys',seed:57,floor:2,decoys:true,frames:[500,650,745,810]},
      {name:'hornfel-escape',hit:true,frames:[45,110,180,900]},
      {name:'hornfel-killed',hit:true,killed:true,frames:[45,110,220]},
      {name:'resident-hornfel-pits',seed:953,floor:2,frames:[45,120,240,500]},
      {name:'resident-hornfel-restricted-door',seed:58,floor:3,frames:[45,120,240,500]},
      {name:'resident-hornfel-charge',seed:10,floor:2,frames:[90,300,430,500,580],charge:[390,483,545,556]},
      {name:'resident-hornfel-charge-pits',seed:953,floor:2,frames:[1350,1580,1660,1740,1795,1850],charge:[1617,1710,1773,1819]},
      {name:'resident-hornfel-charge-curves',seed:749,floor:2,frames:[90,300,430,510,570,640],charge:[390,483,543,608]}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const natural=test.seed!==undefined;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-906.0.0`});
      if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
      if(test.hit)params.append('enemy-hit','90:10000');
      if(test.decoyBlast)params.append('enemy-decoy-blast',`${test.decoyBlast}:1`);
      if(test.decoyContact)params.append('enemy-player-at',`${test.decoyContact}:-16.6154:-7.74167`);
      if(test.killed)params.append('enemy-hit','200:10000');
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of test.frames) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe?.hornfel,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        const p=sample.probe,h=p.hornfel;
        assert(sample.frame<frame+10,'Hornfel timing window');assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);
        assert.equal(p.resident.natural,natural);assert(h.cart>0&&h.owner===p.entity&&h.doors.length>=8);
        assert(h.doors.every(d=>d.id>0&&d.type===967&&d.open>=0&&d.open<=1));
        if(natural){assert.equal(h.cellX,4);assert.equal(h.cellZ,4);if(!test.charge&&!test.decoys)assert(h.pits>0);}
        if(test.decoyBlast||test.decoyContact) {
          const trigger=test.decoyBlast||test.decoyContact;
          assert.equal(h.decoysSpawned,2);assert.equal(p.kills,0);assert.equal(p.threats,1);
          if(frame<trigger) {
            assert.equal(h.decoysDestroyed,0);assert.equal(h.decoys.length,2);
            assert(h.decoys.every(d=>d.visible));
          } else {
            assert(h.decoysDestroyed>=1);assert(h.decoys.every(d=>!d.deathPending));
            const bombs=p.enemyBombs.filter(b=>b.ordnance[0]===4&&b.ordnance[1]===3);
            if(frame<trigger+90)assert.equal(bombs.length,h.decoysDestroyed*6,'Six physical fused bombs per destroyed decoy');
            else assert.equal(bombs.length,0,'Decoy bombs finish their actual fuses');
            if(frame===3240)assert.equal(h.decoysRemoved+h.decoysDestroyed,h.decoysSpawned,'Remaining decoy exits without respawn');
          }
        }
        if(test.decoys) {
          assert.equal(h.decoyRuns,1);assert.equal(h.decoysSpawned,2);assert.equal(h.decoysDestroyed,0);
          const expected=frame<719?2:frame<776?1:0;
          assert.equal(h.decoysRemoved,2-expected);assert.equal(h.decoys.length,expected);
          assert.equal(p.actors.filter(a=>a.type===906&&a.variant===1).length,expected);
          const doors=new Set();
          for(const d of h.decoys) {
            assert(d.actor>0&&d.cart>0&&d.visible&&!d.finished);
            assert(!doors.has(d.entry)&&!doors.has(d.exit));doors.add(d.entry);doors.add(d.exit);
            assert.equal(p.actors.find(a=>a.entity===d.actor).hp,4);
          }
          assert.equal(p.kills,0);assert.equal(p.threats,1,'Decoys are not additional room-clear bosses');
        }
        if(test.charge) {
          const [lastCharge,shotAt,fireAt,exitAt]=test.charge;
          assert(h.charges>=1&&h.repeatsChosen>=6&&h.repeatsChosen<=8);
          if(frame<lastCharge)assert.equal(h.state,6,'Repeated charge stays on rail');
          else {
            assert.equal(h.chargePasses,h.repeatsChosen+1,'Initial pass is additional to repeat counter');
            assert.equal(h.recoveryShots,frame<shotAt?0:1,'One animation-driven recovery projectile');
            if(frame<exitAt)assert.equal(h.state,8,'Recovery continues until exit');
          }
          if(frame>=fireAt) {
            assert(p.fireWaves.length>0,'Actual landed recovery creates persistent fire');
            for(const burst of p.fireWaves) {
              assert.equal(burst.source,p.entity);assert.equal(burst.rays.length,4);
              for(const ray of burst.rays)if(ray.active)assert((Math.abs(ray.x-ray.endX)<.001)!==(Math.abs(ray.z-ray.endZ)<.001),'Fire follows cardinal axes');
            }
          }
        }
        if(!test.hit||frame<90){assert(p.alive&&p.hp===768&&h.intact&&h.rider===p.entity);if(frame>=240)assert(h.attacks>0||h.chargeBombs>0);}
        else if(frame<200){assert(p.alive&&p.hp===320&&!h.intact&&h.rider===0&&!h.completed);assert.equal(p.kills,0);}
        else {assert(h.completed);assert.equal(h.escaped,!test.killed);assert.equal(p.kills,test.killed?1:0);assert(p.segmented.paid);}
        sample.capture=`artifacts/enemy-port/wasm-${test.name}-${frame}.png`;await page.screenshot({path:sample.capture});samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id:'906.0.0',case:test.name,samples,scope:'Partial Hornfel rail controller, real authored arena, cart loss and distinct killed/escaped completion. Decoys have separate rail lifetime and source hit health; passenger and broad item interactions remain unfinished.'});
      console.log(`PASS WASM ${test.name}: rails, cart/door lifetime and phase completion`);
    }
    for(const [profile,payload,variant] of [['normal',0,3],['hornfel_normal',0,0],['hot',1,8],['sad',2,16],['brimstone',3,15]]) {
      const name=`ordnance-${profile}`;if(selected&&!selected.includes(name))continue;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:'enemy-69.0.0',
        'enemy-bomb':profile,'enemy-player-side':'above'});
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];let bombId=0;
      for(const frame of [45,100,200]) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        const p=sample.probe;assert(sample.frame<frame+10);assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);
        assert.equal(p.resident.natural,false,'Component probe is not a natural boss producer');
        const live=frame===45||profile==='hot'||(profile==='brimstone'&&frame===100);
        assert.equal(p.enemyBombs.length,live?1:0);
        if(live) {
          const b=p.enemyBombs[0];assert(b.configured);assert.equal(b.payload,payload);assert.equal(b.source,p.entity);
          assert.deepEqual(b.ordnance,[4,variant,0],'Verified source payload identity, distinct from NPC owner');
          assert.equal(b.detonated,frame>45);if(frame===45)bombId=b.entity;else assert.equal(b.entity,bombId);
          if(frame===100&&profile==='brimstone') {
            assert.equal(b.beams.length,4);
            for(const end of b.beams)assert(Math.min(Math.abs(end.x-b.x),Math.abs(end.z-b.z))<.003,'Four fixed cardinal beams');
          }
        }
        if(frame>45){assert(p.statue.explosions>=1);assert.equal(p.shots,profile==='sad'?10:0);}
        if(profile==='sad')for(const shot of p.bullets)assert.equal(shot.owner,bombId,'Payload retains bomb attribution');
        sample.capture=`artifacts/enemy-port/wasm-${name}-${frame}.png`;await page.screenshot({path:sample.capture});samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({case:name,samples,scope:'Isolated external hostile bomb payload, actual trajectory/fuse/aftermath in Original WASM. Dedicated producer acceptance is tracked separately.'});
      console.log(`PASS WASM ${name}: typed component, fuse and aftermath`);
    }
    for(const test of [
      {name:'loki',id:'69.0.0',frames:[45,180,360,650]},
      {name:'lokii',id:'69.1.0',frames:[45,180,360,650]},
      {name:'lokii-half-death',id:'69.1.0',frames:[45,310,450],halfDeath:true},
      {name:'resident-loki',id:'69.0.0',seed:2,floor:3,frames:[45,180,360]},
      {name:'resident-lokii',id:'69.1.0',seed:3,floor:3,frames:[45,180,360]}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const natural=test.seed!==undefined,split=test.id==='69.1.0';
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${test.id}`});
      if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
      else params.set('enemy-player-side','above');
      if(test.halfDeath)params.set('enemy-execute','300:10000');
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of test.frames) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        const p=sample.probe,dead=test.halfDeath&&frame>300;
        assert(sample.frame<frame+10,'Loki timing window');assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);
        assert.equal(p.resident.natural,natural);
        const bodies=p.actors.filter(a=>a.type===69);assert.equal(bodies.length,split?(dead?1:2):1);
        assert(bodies.every(a=>a.hp===1120&&a.maxHp===1120&&a.bossGroup>0),'350 source HP per body');
        assert.equal(new Set(bodies.map(a=>a.bossGroup)).size,1);
        const flies=p.actors.filter(a=>a.type===25);assert(flies.length<=(split?1:4));
        assert(flies.every(a=>a.variant===(split?1:0)&&a.summoner===bodies[0].bossGroup));
        if(dead){assert.equal(p.kills,1);assert.equal(p.segmented.paid,false);assert.equal(p.segmented.killed,false);assert(Math.abs(p.segmented.health-.5)<.001);}
        else {assert.equal(p.kills,0);assert.equal(p.segmented.health,1);}
        if(frame>=360)assert(bodies.some(a=>a.cycles>0),'Actual controller completed actions');
        sample.capture=`artifacts/enemy-port/wasm-${test.name}-${frame}.png`;await page.screenshot({path:sample.capture});samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id:test.id,case:test.name,samples,scope:'Actual Loki/Lokii controllers, grouped health and first-half death; native suite checks complete payout, ordered patterns and story gates. Special items/support variants remain unfinished.'});
      console.log(`PASS WASM ${test.name}: independent bodies, health, actions and group completion rules`);
    }
    for(const test of [
      {name:'boom-normal',id:'25.0.0',frames:[45,65],blast:true},
      {name:'boom-red',id:'25.1.0',frames:[45,65],shots:6},
      {name:'boom-drowned',id:'25.2.0',frames:[45,65],shots:4,blast:true},
      {name:'dragon-cardinal',id:'25.3.0',frames:[45,65],fire:true},
      {name:'dragon-diagonal',id:'25.3.1',frames:[45,65],fire:true,diagonal:true},
      {name:'bone-fly',id:'25.4.0',frames:[45,65],shots:3,bone:true},
      {name:'sick-boom',id:'25.5.0',frames:[45,65],shots:6,gas:true},
      {name:'tainted-boom',id:'25.6.0',frames:[45,65,110,240],tainted:true},
      {name:'resident-boom',id:'25.0.0',frames:[45,80],seed:0,floor:2},
      {name:'resident-red-boom',id:'25.1.0',frames:[45,80],seed:0,floor:3},
      {name:'resident-drowned-boom',id:'25.2.0',frames:[45,80],seed:0,floor:4},
      {name:'resident-dragon',id:'25.3.0',frames:[45,80],seed:16,floor:1},
      {name:'resident-dragon-x',id:'25.3.1',frames:[45,80],seed:4,floor:3},
      {name:'resident-bone-fly',id:'25.4.0',frames:[45,80],seed:19,floor:2},
      {name:'resident-sick-boom',id:'25.5.0',frames:[45,80],seed:4,floor:6}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const natural=test.seed!==undefined;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${test.id}`});
      if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
      else {params.set('enemy-hit','60:1000');params.set('enemy-player-side','above');}
      if(test.tainted)params.set('enemy-clear','70');
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of test.frames) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        const p=sample.probe;assert(sample.frame<frame+10,'Boom Fly sample missed timing window');
        assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);assert.equal(p.resident.natural,natural);
        if(natural||frame===45) {
          assert(p.alive);const stage=p.sourceStage;
          const hp=test.tainted?64:(8+3*(Math.min(stage,4)+.8*Math.max(0,Math.min(stage-5,5))))*3.2;
          assert(Math.abs(p.hp-hp)<.001,'Actual resident/fixture stage health');
          assert(Math.abs(Math.abs(p.charge.fx)-Math.SQRT1_2)<.001&&Math.abs(Math.abs(p.charge.fz)-Math.SQRT1_2)<.001,'Diagonal bearing preserved');
          if(test.gas)assert(p.hazards.some(h=>h.owner===p.entity&&h.duration===2.5),'Actual gas trail');
        } else {
          assert.equal(p.alive,false);
          if(test.shots)assert.equal(p.shots,samples[0].probe.shots+test.shots,'Variant-specific death volley count');
          if(test.blast)assert(p.statue.explosions>=1); // Real dressing may create collateral barrel blasts.
          if(test.fire) {
            const patches=p.hazards.filter(h=>h.owner===p.entity);assert(patches.length>4);
            for(const h of patches) {
              const x=Math.abs(h.x-h.originX),z=Math.abs(h.z-h.originZ);
              assert(test.diagonal?Math.abs(x-z)<.002:Math.min(x,z)<.002,'Fire matches cross/X face marker');
            }
          }
          if(test.gas){assert(p.hazards.filter(h=>h.owner===p.entity&&h.duration===12).length===8);assert(p.bullets.filter(b=>b.owner===p.entity).every(b=>b.kind===14&&b.blastRadius===0));}
          if(test.bone)assert(p.bullets.filter(b=>b.owner===p.entity).every(b=>b.kind===13));
          if(test.tainted) {
            if(frame===65){assert.equal(p.statue.explosions,0);assert(p.enemyBombs.length>4);assert(p.enemyBombs.every(b=>b.marker));}
            if(frame>=110){assert(p.statue.clear);assert(p.statue.explosions>0);}
            if(frame===240)assert.equal(p.enemyBombs.length,0);
          }
        }
        sample.capture=`artifacts/enemy-port/wasm-${test.name}-${frame}.png`;await page.screenshot({path:sample.capture});samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id:test.id,case:test.name,samples,scope:'Actual Boom Fly WASM behavior and stage HP. Tainted is an isolated partial controller, not Ascent reachability; item/faction and adaptive armor gaps remain.'});
      console.log(`PASS WASM ${test.name}: family behavior, presentation and source-stage health`);
    }
    for(const test of [
      {name:'fly-bomb-pursuit',id:'819.0.0',frames:[15,80,280]},
      {name:'fly-bomb-death',id:'819.0.0',frames:[15,65,125],death:true},
      {name:'eternal-fly-bombs',id:'819.1.0',frames:[15,65,95,155],owned:true},
      {name:'resident-fly-bomb',id:'819.0.0',frames:[15,80],natural:true}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${test.natural?'resident':'enemy'}-${test.id}`});
      if(test.natural){params.set('resident-seed','19');params.set('resident-floor','2');}
      if(test.death){params.set('enemy-hit','60:24');params.set('enemy-clear','70');}
      if(test.owned){params.set('enemy-hit','60:1000');params.set('enemy-blast','90:100');}
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of test.frames) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        const p=sample.probe;assert(sample.frame<frame+10,'Fly Bomb sample missed timing window');
        assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);
        assert.equal(p.resident.natural,!!test.natural);
        if(test.owned) {
          if(frame<90) {
            assert(p.alive);assert(Math.abs(p.hp-22.4)<.001);assert.equal(p.actors.filter(a=>a.type===819&&a.variant===1).length,3);
            const owner=p.actors.find(a=>a.type===25&&a.variant===0);assert(owner);
            for(const child of p.actors.filter(a=>a.type===819)) {
              assert.equal(child.componentOwner,owner.entity);assert(Math.abs(Math.hypot(child.x-owner.x,child.z-owner.z)-2)<.05);
            }
          } else {
            assert.equal(p.alive,false);assert.equal(p.actors.filter(a=>a.type===819).length,0);
            if(frame===95){assert.equal(p.enemyBombs.length,3);assert(p.enemyBombs.every(b=>b.monster[1]===1&&b.damage===100));}
            else {assert.equal(p.enemyBombs.length,0);assert.equal(p.statue.explosions,5);}
          }
        } else if(test.death) {
          if(frame===15){assert(p.alive);assert(Math.abs(p.hp-22.4)<.001);}
          else {
            assert.equal(p.alive,false);
            if(frame===65){assert.equal(p.enemyBombs.length,1);assert.equal(p.statue.explosions,0);assert.equal(p.enemyBombs[0].damage,100);assert.deepEqual(p.enemyBombs[0].ordnance,[4,14,0]);}
            else {assert.equal(p.enemyBombs.length,0);assert.equal(p.statue.explosions,1);assert(p.statue.clear);}
          }
        } else if(!test.natural) {
          if(frame<280){assert(p.alive);assert.equal(p.enemyBombs.length,0);}
          else {assert.equal(p.alive,false);assert.equal(p.statue.explosions,1);assert.equal(p.enemyBombs.length,0);}
        }
        sample.capture=`artifacts/enemy-port/wasm-${test.name}-${frame}.png`;await page.screenshot({path:sample.capture});samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id:test.id,case:test.name,samples,scope:'Actual WASM Fly Bomb lifecycle and flight; Eternal owner group is a dependency fixture, not a claimed Horny Boys route.'});
      console.log(`PASS WASM ${test.name}: contact/death ordnance and owner lifecycle`);
    }
    for(const test of [
      {name:'shell-head',frames:[15,25,65,100],head:true},
      {name:'shell-middle',frames:[15,65,90,110,415],part:2},
      {name:'shell-tail',frames:[15,65,110],part:4},
      {name:'resident-shell',frames:[15,190,350],natural:true}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${test.natural?'resident':'enemy'}-19.3.0`});
      if(test.natural){params.set('resident-seed','33');params.set('resident-floor','2');}
      else {
        if(test.part!==undefined)params.set('enemy-segment',test.part);
        params.append('enemy-hit','20:10000');params.append('enemy-blast','60:100');
        if(!test.head)params.append('enemy-hit','100:24');
        if(test.part===2)params.append('enemy-execute','400:10000');
      }
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of test.frames) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        const p=sample.probe,parts=p.actors.filter(a=>a.segmented),heads=parts.filter(a=>a.head);
        assert(sample.frame<frame+10,'Shell sample missed timing window');assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);
        assert.equal(p.resident.natural,!!test.natural);assert.equal(p.segmented.groups.length,1);
        assert.equal(heads.length,2);assert(heads.every(a=>a.hp===112&&a.armor===15),'Invulnerable head state');
        assert.equal(p.segmented.paid,false);assert.equal(p.segmented.killed,false);assert.equal(p.actors.filter(a=>a.type===809).length,2);
        if(test.natural||test.head) {assert(p.alive);assert.equal(p.hp,112);}
        if(test.natural||frame<60){assert.equal(parts.length,10);assert.equal(p.segmented.health,1);assert(parts.every(a=>a.armor===15));}
        if(test.part!==undefined&&frame>=60&&frame<400) {
          const body=parts.find(a=>a.entity===p.entity);assert(body);assert.equal(body.armor,0);
          if(frame===65&&body.settling)assert(body.y>.85,'Exposed body is still landing from real cover');
          else assert.equal(body.settling,false);
          // This capture retains real arena dressing. Its delayed barrel blast
          // deals 80 after the scripted stripping blast; record both events.
          assert(p.statue.explosions===1||p.statue.explosions===2);
          assert.equal(p.hp,(frame<100?112:88)-80*(p.statue.explosions-1));
          if(test.part===2&&frame===90)assert(p.shots>=3,'Landed middle fired a real triple');
          if(test.part===4&&frame===65)assert(p.actors.some(a=>a.type===819&&a.variant===0),'Tail produced actual Fly Bomb');
        }
        if(frame>400){assert.equal(p.alive,false);assert(p.segmented.health<1);assert.equal(p.segmented.groups[0].completed,false);}
        sample.capture=`artifacts/enemy-port/wasm-${test.name}-${frame}.png`;await page.screenshot({path:sample.capture});samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id:'19.3.0',case:test.name,samples,scope:'Actual Shell controller, segment-specific armor probe, offspring and generated double arena. Scripted damage is not player-control balance evidence.'});
      console.log(`PASS WASM ${test.name}: invulnerable head, flesh attacks and arena`);
    }
    for(const test of [
      {name:'tuff-pair',frames:[15,190,350]},
      {name:'tuff-armor',frames:[25,65,120,350,415,530],armor:true},
      {name:'resident-tuff',frames:[15,190,350],seed:1,floor:2},
      {name:'sucker-death',id:'61.0.0',frames:[15,125]},
      {name:'ink-death',id:'61.3.0',frames:[15,125]}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const id=test.id||'19.2.0',natural=test.seed!==undefined,flyer=!!test.id;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${id}`});
      if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
      if(test.armor) {
        params.append('enemy-hit','20:9999');params.append('enemy-blast','60:100');params.append('enemy-hit','100:24');
        params.append('enemy-execute','400:10000');params.append('enemy-reenter','500');
      }
      if(flyer)params.set('enemy-hit','120:100');
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of test.frames) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        const p=sample.probe;assert(sample.frame<frame+10,'Segmented sample missed timing window');
        assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);
        if(flyer) {
          if(frame===15)assert.equal(p.hp,32);
          else {
            assert.equal(p.shots,4);assert.equal(p.bullets.length,4);assert.equal(p.alive,false);
            for(const b of p.bullets) {
              assert.equal(b.kind,0);
              if(id==='61.0.0')assert(Math.abs(b.vx)<.001||Math.abs(b.vz)<.001);
              else assert(Math.abs(Math.abs(b.vx)-Math.abs(b.vz))<.001);
            }
            if(id==='61.0.0')assert.equal(p.hazards.length,0);
            else {assert.equal(p.hazards.length,1);assert.equal(p.hazards[0].kind,5);}
          }
        } else {
          const deadHead=!!test.armor&&frame>400,parts=p.actors.filter(a=>a.segmented),heads=parts.filter(a=>a.head);
          assert.equal(parts.length,deadHead?11:12);assert.equal(heads.length,2);
          assert.equal(p.segmented.groups.length,1);assert.equal(p.segmented.groups[0].chains.length,2);
          assert.equal(p.segmented.groups[0].completed,false);assert.equal(p.segmented.paid,false);assert.equal(p.segmented.killed,false);
          assert.equal(p.actors.filter(a=>a.type===809).length,2);
          assert(p.supply.bombs.length>=2,'Two actual suppliers stock the arena');
          assert.equal(p.resident.natural,natural);assert(parts.every(a=>a.hp>0&&a.maxHp===112));
          if(test.armor) {
            if(frame===25){assert.equal(p.hp,112);assert(parts.every(a=>a.armor===15));}
            else if(!deadHead){
              if(frame===65)assert.equal(p.hp,112);
              else {assert(p.hp>0&&p.hp<=88);if(p.hp<88)assert(p.statue.explosions>1,'Additional damage needs a real collateral barrel explosion');}
              assert.equal(parts.find(a=>a.entity===p.entity).armor,0);
            }
            if(frame===350)assert(p.actors.some(a=>a.type===61&&a.variant===0),'Exposed head emits real Suckers');
            if(deadHead){assert.equal(p.alive,false);assert(p.segmented.health<11/12+.001);}
          } else {assert.equal(p.segmented.health,1);assert(parts.every(a=>a.armor===15));}
          if(frame===350)assert(p.actors.some(a=>a.type===61&&a.variant===3),'Armored head emits real Ink');
        }
        sample.capture=`artifacts/enemy-port/wasm-${test.name}-${frame}.png`;await page.screenshot({path:sample.capture});samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id,case:test.name,samples,scope:'Real multipart/controller or flyer-death WASM probe; scripted blast is a real explosion, not a player-control test. Native starting-kit balance remains a separate gate.'});
      console.log(`PASS WASM ${test.name}: segmented armor/ownership or flyer death`);
    }
    for(const test of [
      {name:'supply-stock',frames:[15,400],clear:60,reenter:200},
      {name:'supply-carry',frames:[40,185,220],take:30,reenter:80,move:205},
      {name:'supply-throw',frames:[40,65,130,220],take:30,attack:60,move:80},
      {name:'supply-death',frames:[15,45,150],kill:30,reenter:90}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:'enemy-809.0.0','enemy-player-side':'below'});
      if(test.clear)params.set('enemy-clear',test.clear);
      if(test.reenter)params.set('enemy-reenter',test.reenter);
      if(test.take)params.append('enemy-player-at',`${test.take}:0:2`);
      if(test.move)params.append('enemy-player-at',`${test.move}:0:8`);
      if(test.attack)params.set('enemy-player-attack',`${test.attack}:10:2`);
      if(test.kill)params.set('enemy-execute',`${test.kill}:10000`);
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of test.frames) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        assert(sample.frame<frame+10,'Supply sample missed timing window');const p=sample.probe,b=p.supply.bombs;
        assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);
        assert.equal(p.playerHp,100);assert.equal(p.threats,0);assert.equal(p.kills,0);assert.equal(p.shots,0);
        if(samples.length)assert.equal(p.supply.inventory,samples[0].probe.supply.inventory,'Supply must not consume ordinary inventory');
        for(const bomb of b)assert.deepEqual(bomb.source,bomb.state===0?[5,41,0]:[4,13,0]);
        if(test.name==='supply-stock'||test.name==='supply-death') {
          const death=test.kill&&frame>test.kill;
          assert.equal(b.length,death?11:1);assert.equal(p.supply.produced,death?11:1);assert.equal(p.supply.pending,0);
          assert.equal(b.filter(bomb=>bomb.deathDrop).length,death?10:0);
          assert(b.every(bomb=>bomb.state===0&&bomb.age===0),'Stock stays unlit on the floor');
          assert.equal(p.supply.carried,0);assert.equal(p.statue.explosions,0);
          assert.equal(p.alive,!(death&&frame<test.reenter));
        } else {
          assert.equal(p.alive,true);assert.equal(p.hp,64);
          if(frame===40) {
            assert.equal(b.length,1);assert.equal(b[0].state,1);assert.equal(p.supply.carried,b[0].entity);
            assert(b[0].age>.14&&b[0].age<.35);
          } else if(frame===185) {
            assert.equal(b.length,2);assert.equal(b.filter(bomb=>bomb.state===0).length,1);
            assert.equal(p.supply.carried,b[0].entity);assert(b[0].age>2.5&&b[0].age<2.8);
          } else if(frame===65||frame===130) {
            assert.equal(p.supply.carried,0);assert.equal(b[0].state,2);assert(b[0].x>p.startX+.5,'Actual attack input propels the bomb');
            assert(b[0].age>.5,'Throw did not reset fuse');
            if(frame===65)assert(b[0].vx>10);
          } else if(frame===220) {
            assert.equal(p.supply.carried,0);assert.equal(b.length,1);assert.equal(b[0].state,0);
            assert.equal(p.statue.explosions,1);assert.equal(p.supply.produced,2);
          }
        }
        sample.capture=`artifacts/enemy-port/wasm-${test.name}-${frame}.png`;await page.screenshot({path:sample.capture});samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id:'809.0.0',case:test.name,samples,scope:'Real unlit stock, pickup identity transition, held fuse, actual attack-input throw, replenishment, exceptional ten-drop burst and re-entry. Dedicated encounter routing remains pending; god-mode captures do not establish self-damage.'});
      console.log(`PASS WASM ${test.name}: actual supplied-bomb lifecycle`);
    }
    for(const test of [
      {name:'quake-left',axis:0,dx:-1,dz:0},
      {name:'quake-up',axis:1,dx:0,dz:-1},
      {name:'quake-right',axis:2,dx:1,dz:0},
      {name:'quake-down-plate',axis:3,dx:0,dz:1,plate:240}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const id=`804.0.${test.axis}`;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`enemy-${id}`,'enemy-clear':'210'});
      if(test.plate)params.set('enemy-player-at',`${test.plate}:-5:5`);
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of [165,195,225,375]) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        assert(sample.frame<frame+10,'Quake sample missed timing window');const p=sample.probe;
        assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);
        assert.equal(p.alive,true);assert.equal(p.hp,64);assert.equal(p.playerHp,100);assert.equal(p.threats,0);assert.equal(p.kills,0);assert.equal(p.shots,0);
        assert.equal(p.statue.fx,test.dx);assert.equal(p.statue.fz,test.dz);assert.equal(p.statue.explosions,0);
        assert.equal(p.statue.volleys,frame===165?0:frame===375&&!test.plate?2:1);
        if(frame===165){assert(p.statue.lift>.5,'Anchored hop is visible before landing');assert.equal(p.hazards.length,0);}
        if(frame===195) {
          assert(p.hazards.some(h=>h.kind===12),'Landing produces an actual travelling rock wave');
          for(const h of p.hazards) {assert.equal(h.kind,12);assert((h.x-p.startX)*test.dx+(h.z-p.startZ)*test.dz>2,'Wave advances on fixed axis');}
        }
        if(frame===225)assert.equal(p.statue.clear,true);
        if(frame===375&&test.plate){assert(p.statue.disabled&&p.plates[0].pressed);assert.equal(p.hazards.length,0);}
        sample.capture=`artifacts/enemy-port/wasm-${test.name}-${frame}.png`;await page.screenshot({path:sample.capture});samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id,case:test.name,samples,scope:'All four fixed axes, anchored hop, three-second landing, moving rock front, combat-clear persistence and plate shutdown. Dimensions and cache-wall behavior are explicit local adaptations.'});
      console.log(`PASS WASM ${test.name}: landing, wave direction and lifecycle`);
    }
    for(const test of [
      {name:'maw-normal',id:'235.0.0',frames:[30,90],clear:60},
      {name:'maw-broken-cycle',id:'236.0.0',frames:[60,245,400,490],reset:250},
      {name:'maw-plate',id:'235.0.0',frames:[30,120,300],clear:45,plate:100},
      {name:'maw-projectiles',id:'235.0.0',frames:[30,60],shots:true}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`enemy-${test.id}`,'enemy-player-side':'below'});
      if(test.clear)params.set('enemy-clear',test.clear);
      if(test.plate)params.set('enemy-player-at',`${test.plate}:-5:5`);
      if(test.reset)params.set('enemy-player-at',`${test.reset}:0:8`);
      if(test.shots)for(const team of ['player','hostile'])params.append('enemy-shot',`5:${team}:-6:-6:6:0`);
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of test.frames) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        assert(sample.frame<frame+10,'Maw sample missed timing window');const p=sample.probe;
        assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);assert.equal(p.playerHp,100);
        assert.equal(p.alive,true);assert.equal(p.hp,320);assert.equal(p.threats,0);assert.equal(p.kills,0);assert.equal(p.statue.volleys,0);
        assert.equal(p.shots,test.shots?2:0);
        if(test.name==='maw-broken-cycle') {
          assert.equal(p.statue.pulling,frame===60||frame===490);
          if(frame===400)assert(Math.abs(p.playerZ-p.startZ-8)<.001,'No player force in inactive phase');
          if(frame===490)assert(p.playerZ-p.startZ<7.8,'Force resumes in next active phase');
        } else if(test.plate&&frame>test.plate) {
          assert.equal(p.statue.pulling,false);assert.equal(p.statue.disabled,true);assert(p.plates[0].pressed);
          if(samples.at(-1)?.frame>test.plate)assert.equal(p.playerZ,samples.at(-1).probe.playerZ);
        } else {
          assert.equal(p.statue.pulling,true);assert(p.playerZ-p.startZ<7.6,'Player moves inward from the capture scene’s initial eight-unit separation');
          if(test.clear&&frame>test.clear)assert.equal(p.statue.clear,true);
        }
        if(test.shots) {
          assert.equal(p.bullets.length,2,'Both actual projectile factions remain in flight');
          for(const bullet of p.bullets)assert(bullet.vz>.3,'Both shot paths bend toward the Maw');
        }
        sample.capture=`artifacts/enemy-port/wasm-${test.name}-${frame}.png`;await page.screenshot({path:sample.capture});samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id:test.id,case:test.name,samples,scope:'Actual player attraction, source four-second Broken cycle, plate/clear lifecycle or projectile force in both factions; strengths and geometry are declared 3D tuning.'});
      console.log(`PASS WASM ${test.name}: actual suction and Original presentation`);
    }
    for(const test of [
      {name:'statue-stone',id:'42.0.0',frames:[30,90],clear:60,shots:1},
      {name:'statue-vomit',id:'42.1.0',frames:[30,90],clear:60,shots:1},
      {name:'statue-triple',id:'42.2.0',frames:[30,90],clear:60,shots:3},
      {name:'statue-eye',id:'201.0.0',frames:[5,45,70,90],clear:60,reenter:80},
      {name:'statue-fixed',id:'202.0.0',frames:[30,90,120,160],clear:45,plate:100},
      {name:'statue-cross',id:'202.10.0',frames:[5,45,90],clear:60,cross:true},
      {name:'statue-cross-alt',id:'202.10.1',frames:[5,45,90],clear:60,cross:true,diagonal:true},
      {name:'statue-always',id:'202.11.0',frames:[5,45,90,120],clear:60,cross:true,plate:100,always:true},
      {name:'statue-always-alt',id:'202.11.1',frames:[5,45,90,120],clear:60,cross:true,diagonal:true,plate:100,always:true},
      {name:'statue-brimstone',id:'203.0.0',frames:[32,60,120,200],clear:45,plate:100}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`enemy-${test.id}`,'enemy-player-side':'below'});
      if(test.clear)params.set('enemy-clear',test.clear);
      if(test.reenter)params.set('enemy-reenter',test.reenter);
      if(test.plate)params.set('enemy-player-at',`${test.plate}:-5:5`);
      if(test.name==='statue-stone')params.set('enemy-hit','10:10000');
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of test.frames) {
        // Eye clear/re-entry samples are only20frames apart. A full-canvas
        // screenshot can take longer than that on WSL. Replay the same seeded
        // timeline for each capture instead of relaxing the timing assertion or
        // accidentally sampling the state after a later scheduled transition.
        if(test.name==='statue-eye'&&samples.length) {
          await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
          await page.locator('#start').click({noWaitAfter:true});
        }
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        assert(sample.frame<frame+10,'Statue sample missed timing window');const p=sample.probe;
        assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);assert.equal(p.playerHp,100);assert.equal(p.threats,0);assert.equal(p.kills,0);
        assert.equal(p.alive,!(test.reenter&&frame>test.reenter));
        if(p.alive)assert.equal(p.statue.disabled,!!(!test.always&&((test.plate&&frame>test.plate)||(!test.plate&&frame>test.clear))));
        if(test.shots) {
          assert.equal(p.shots,test.shots);assert.equal(p.hp,64);
          if(test.name==='statue-vomit'&&frame===30){assert.equal(p.bullets.length,1);assert.equal(p.bullets[0].kind,12);assert.equal(p.bullets[0].gravity,12);}
          if(test.name==='statue-vomit'&&frame===90)assert.equal(p.statue.explosions,1);
        }
        if(test.cross&&frame<=45) {
          assert.equal(p.shots,frame===5?4:8);const diagonal=frame===5?!!test.diagonal:!test.diagonal;
          const bullets=p.bullets.slice(-4);assert.equal(bullets.length,4);
          for(const b of bullets)assert(diagonal?Math.abs(Math.abs(b.vx)-Math.abs(b.vz))<.001:Math.abs(b.vx)<.001||Math.abs(b.vz)<.001);
        }
        if(test.name==='statue-eye') {
          if(frame===5)assert(p.statue.volleys>0,'Laser emitted before a full rotation; a sample may fall in its flicker-off interval');
          if(frame===45)assert(p.statue.fx<-.3,'Eye rotates in configured clockwise direction');
          if(frame>=70)assert.equal(p.hazards.length,0);
        }
        if(test.name==='statue-brimstone'&&frame===32)assert(p.hazards.some(h=>h.kind===6&&h.z>h.originZ));
        if(test.plate&&frame>test.plate) {
          assert.equal(p.plates.length,1);assert.equal(p.plates[0].pressed,true);
          if(!test.always&&samples.length&&samples.at(-1).frame>test.plate)assert.equal(p.statue.volleys,samples.at(-1).probe.statue.volleys);
        }
        if(test.name==='statue-fixed'&&frame===90)assert(p.statue.volleys>samples[0].probe.statue.volleys,'Fixed turret keeps firing after ordinary clear');
        sample.capture=`artifacts/enemy-port/wasm-${test.name}-${frame}.png`;await page.screenshot({path:sample.capture});samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id:test.id,case:test.name,samples,scope:'Real configured hazard controller, clear/re-entry calls or player-pressed floor plate. Always-on/subtype phase are explicit local interpretations pending remaining source acceptance.'});
      console.log(`PASS WASM ${test.name}: attacks, lifecycle and Original rendering`);
    }
    for(const test of [
      {name:'resident-quake-left',id:'804.0.0',seed:9,floor:2,room:2,frame:210},
      {name:'resident-quake-up',id:'804.0.1',seed:31,floor:2,room:3,frame:210},
      {name:'resident-quake-right',id:'804.0.2',seed:10,floor:2,room:7,frame:210},
      {name:'resident-quake-down',id:'804.0.3',seed:23,floor:2,room:6,frame:210},
      {name:'resident-statue-fixed',id:'202.0.0',seed:2,floor:5,room:10},
      {name:'resident-statue-brimstone',id:'203.0.0',seed:0,floor:5,room:2},
      {name:'resident-maw',id:'235.0.0',seed:0,floor:5,room:5,pull:true},
      {name:'resident-broken-maw',id:'236.0.0',seed:1,floor:2,room:4,pull:true}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',
        scene:`resident-${test.id}`,'resident-seed':String(test.seed),'resident-floor':String(test.floor)});
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,test.frame||120,{timeout:90000});
      const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
      assert(sample.frame<(test.frame||120)+10,'Resident statue sample missed timing window');const p=sample.probe;
      assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);assert.equal(p.playerHp,100);
      assert.equal(p.resident.natural,true);assert.equal(p.resident.floor,test.floor);assert.equal(p.resident.room,test.room);
      assert.equal(p.alive,true);assert.equal(p.statue.disabled,false);
      if(test.pull){assert.equal(p.statue.pulling,true);assert.equal(p.statue.volleys,0);}
      else assert(p.statue.volleys>0,'Actual seeded statue attacks');
      assert.equal(p.plates.length,1);assert.equal(p.plates[0].pressed,false);
      assert(p.threats>0&&p.actors.length>1,'Ordinary companions remain in their generated encounter');
      assert.deepEqual(errors,[]);
      sample.capture=`artifacts/enemy-port/wasm-${test.name}.png`;await page.screenshot({path:sample.capture});
      checks.push({id:test.id,case:test.name,samples:[sample],scope:'Actual seeded hazard and plate with ordinary residents preserved; no forced hazard spawn or lifecycle mutation.'});
      console.log(`PASS WASM ${test.name}: actual seeded stage, active controller and floor plate`);
    }
    for(const test of [
      {name:'shadow-contact',id:'11.0.0',copies:1,move:'1:1.1:0',frames:[12,90,300]},
      {name:'shadow-copies',id:'11.0.0',copies:2,move:'1:1.1:0',frames:[12,90]},
      {name:'shadow-path',id:'11.0.0',copies:1,move:'30:8:8',frames:[32,45]},
      {name:'shadow-fire',id:'23.0.1',copies:0,fire:true,frames:[15,45]}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`enemy-${test.id}`,'enemy-player-side':'below'});
      for(let n=0;n<test.copies;++n)params.append('enemy-item','isaac:collectible:433');
      if(test.move)params.append('enemy-player-at',test.move);
      if(test.fire)params.append('enemy-fire','1');
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of test.frames) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        assert(sample.frame<frame+10,'Shadow sample missed timing window');const p=sample.probe;
        assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);
        const allies=p.actors.filter(a=>a.friendly);assert(allies.length<=16);assert.equal(p.playerHp,100);
        assert.equal(p.familiars.length,test.copies?1:0);
        for(const ally of allies){assert.deepEqual([ally.type,ally.variant,ally.subtype],[23,0,1]);assert.equal(ally.maxHp,64);}
        if(test.name==='shadow-contact'||test.name==='shadow-copies') {
          assert(allies.length>0,'Enemy contact must produce real allies');
          for(const ally of allies)assert.equal(ally.summoner,p.familiars[0].entity);
          assert.equal(p.threats,p.alive?1:0,'Allies never count as hostile room threats');
          if(frame===300)assert(!p.alive||p.hp<40,'Produced allies must really attack the hostile');
        }
        if(test.name==='shadow-path') {
          assert.equal(allies.length,0,'No enemy contact means no allies');
          assert(p.familiars[0].history<=256);
          if(frame===32)assert(Math.abs(p.familiars[0].x-p.startX)<.01,'Shadow follows delayed movement');
          else assert(Math.abs(p.familiars[0].x-p.startX-8)<.01,'Shadow catches up after its delay');
        }
        if(test.fire){assert.equal(p.threats,0);assert(Math.abs(p.hp-(frame===15?60.8:57.6))<.002);}
        sample.capture=`artifacts/enemy-port/wasm-${test.name}-${frame}.png`;await page.screenshot({path:sample.capture});samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id:'23.0.1',case:test.name,samples,scope:'Actual item/contact producer, delayed shadow, allied target behavior or repeated hazard damage; partial parity evidence.'});
      console.log(`PASS WASM ${test.name}: actual companion system and Original presentation`);
    }
    for(const test of [
      {name:'drowned-death-volley',id:'23.1.0',side:'below',frames:[15,48]},
      {name:'dank-reflection',id:'23.2.0',side:'above',move:'15:8:-8',frames:[30,70,110]},
      {name:'princess-diagonal',id:'23.3.0',side:'diagonal',move:'1:-8:-8',frames:[12,45]},
      {name:'level2-steering',id:'855.0.0',side:'below',move:'15:8:8',frames:[10,40]},
      {name:'drowned-repeat-fire',id:'23.1.0',side:'diagonal',fire:'1',hp:70.4,frames:[15,45]},
      {name:'princess-repeat-fire',id:'23.3.0',side:'below',fire:'1',hp:83.2,frames:[15,45]},
      {name:'resident-drowned-charger',id:'23.1.0',seed:3,floor:1,from:'23.0.0',frames:[60]},
      {name:'resident-level2-charger',id:'855.0.0',seed:0,floor:5,frames:[60]}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const natural=test.seed!==undefined;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${test.id}`});
      if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);if(test.from)params.set('resident-from',test.from);}
      else params.set('enemy-player-side',test.side);
      if(test.move)params.append('enemy-player-at',test.move);
      if(test.fire)params.append('enemy-fire',test.fire);
      if(test.name==='drowned-death-volley')params.append('enemy-hit','30:100');
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of test.frames) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        assert(sample.frame<frame+10,'Charger sample missed its timing window');const p=sample.probe;
        assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);assert.equal(p.resident.natural,natural);
        if(test.name==='drowned-death-volley') {
          if(frame===15){assert(p.alive&&p.state===2&&Math.abs(p.hp-70.4)<.001);assert(p.actors[0].vz>12);}
          else {assert.equal(p.alive,false);assert.equal(p.shots,4);assert.equal(p.kills,1);assert.equal(p.threats,0);
            assert.equal(p.bullets.length,4);for(const b of p.bullets)assert(Math.abs(Math.abs(b.vx)-Math.abs(b.vz))<.001);}
        }
        if(test.name==='dank-reflection') {
          assert(p.alive&&Math.abs(p.hp-83.2)<.001);
          if(frame===30){assert.equal(p.state,2);assert(p.charge.fz<-.9);assert(p.hazards.some(h=>h.kind===5));}
          if(frame===70){assert.equal(p.state,2);assert(p.charge.fz>.9);}
          if(frame===110){assert(p.charge.recovery>0);assert(Math.abs(p.actors[0].vx)+Math.abs(p.actors[0].vz)<.001);}
        }
        if(test.name==='princess-diagonal'){assert.equal(p.state,2);assert(Math.abs(p.charge.fx-p.charge.fz)<.001&&p.charge.fx<-.7);assert(Math.abs(p.hp-83.2)<.001);}
        if(test.name==='level2-steering') {
          assert.equal(p.hp,128);assert.equal(p.state,2);
          if(frame===10){assert(Math.abs(p.charge.fx)<.001&&p.actors[0].vz>10&&p.actors[0].vz<12);}
          else assert(p.charge.fx>.3&&p.x>p.startX+.5);
        }
        if(test.fire){assert(p.alive);assert(Math.abs(p.hp-(test.hp-(frame===15?10:20)))<.001,'Fire contact must resume after its shared cooldown');}
        if(natural){assert.equal(p.resident.floor,test.floor);assert(p.alive);if(test.from){assert.deepEqual(p.resident.source,[23,0,0]);assert.equal(p.resident.variant,2);assert(p.resident.dampPatches>0&&p.flooded);}}
        const capture=`artifacts/enemy-port/wasm-${test.name}-${frame}.png`;await page.screenshot({path:capture});sample.capture=capture;samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id:test.id,case:test.name,samples,scope:'Real variant controller/source stage route in Original WASM; partial fidelity evidence.'});
      console.log(`PASS WASM ${test.name}: variant behavior and presentation`);
    }

    for(const test of [
      {name:'bloat-down',side:'below',form:'normal',frames:[32]},
      {name:'bloat-sides',side:'left',form:'normal',frames:[32]},
      {name:'bloat-above',side:'above',form:'normal',frames:[65]},
      {name:'bloat-green',side:'above',form:'green',frames:[65,240,560,615]},
      {name:'resident-bloat',seed:4,floor:4,form:'green',frames:[32,130,360]},
      {name:'charger-cardinal',side:'below',id:'23.0.0',frames:[10,25]}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const natural=test.seed!==undefined,id=test.id||'68.1.0';
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${id}`});
      if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
      else {params.set('enemy-player-side',test.side);if(test.form)params.set('enemy-boss-form',test.form);}
      if(test.name==='bloat-green')params.set('enemy-execute','600:10000');
      await page.goto(`${base}?${params}`);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});const samples=[];
      for(const frame of test.frames) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        assert(sample.frame<frame+10,'Bloat/Charger sample missed timing window');const p=sample.probe;
        assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);assert.equal(p.resident.natural,natural);
        if(test.id) {
          assert.equal(p.threats,1);assert.equal(p.shots,0);assert.equal(p.hp,64);assert.equal(p.state,2);
          assert(Math.abs(p.x-p.startX)<.001&&p.z>p.startZ+1);assert(Math.abs(p.actors[0].vx)<.001&&p.actors[0].vz>11);
        } else {
          const dead=frame===615,eyes=p.actors.filter(a=>a.componentOwner===p.entity);
          const children=p.actors.filter(a=>a.summoner===p.entity);
          assert.equal(p.alive,!dead);assert.equal(eyes.length,dead?0:2);assert.equal(p.threats,children.length+(dead?0:1));
          assert.equal(p.kills,dead?1:0);if(!dead){assert.equal(p.hp,1440);assert.equal(p.boss.form,test.form==='green'?3:0);assert.equal(p.boss.parts,3);}
          for(const eye of eyes)assert.deepEqual([eye.type,eye.variant,eye.subtype],[68,11,0]);
          for(const child of children)assert.deepEqual([child.type,child.variant,child.subtype],[23,0,0]);
          if(test.name==='bloat-down'||test.name==='bloat-sides') {
            const beams=p.hazards.filter(h=>h.kind===6);assert.equal(beams.length,2);
            for(const h of beams){assert.equal(h.delay,0);assert.equal(h.ownerBound,true);assert.equal(h.owner,p.entity);
              if(test.name==='bloat-down')assert(h.z>h.originZ&&Math.abs(h.x-h.originX)<.001);
              else assert(Math.abs(h.z-h.originZ)<.001&&Math.abs(h.x-h.originX)>5);}
          }
          if(test.name==='bloat-above'){assert.equal(p.shots,8);assert(!p.hazards.some(h=>h.kind===6));}
          if(test.name==='bloat-green'&&frame===65) {
            assert.equal(p.shots,2);assert.equal(p.bullets.length,2);
            for(const shot of p.bullets){assert.equal(shot.kind,12);assert.equal(shot.gravity,12);assert(Math.abs(shot.blastRadius-2.8)<.001&&shot.y>2);}
          }
          if(test.name==='bloat-green'&&frame===560) {
            assert.equal(children.length,2);assert(p.hazards.some(h=>h.kind===4&&h.tintG===151&&h.owner===p.entity));
            sample.capture='artifacts/enemy-port/wasm-bloat-green-creep.png';await page.screenshot({path:sample.capture});
          }
          if(dead)assert(!p.hazards.some(h=>h.ownerBound));
          if(natural){assert.equal(p.resident.floor,test.floor);assert.deepEqual(p.resident.source,[68,1,0]);}
        }
        if(frame===test.frames[0]){sample.capture=`artifacts/enemy-port/wasm-${test.name}.png`;await page.screenshot({path:sample.capture});}
        samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id,case:test.name,samples,capture:samples[0].capture,
        scope:'Real Bloat/Charger WASM controller: cardinal laser geometry, fixed ring, ballistic green shots, source-owned eyes, explicit cleanup or actual seeded encounter; partial parity evidence.'});
      console.log(`PASS WASM ${test.name}: real controller and Original presentation`);
    }
    for(const test of [
      {name:'peep-thresholds',form:'normal',hits:true},
      {name:'peep-cyan',form:'cyan'},
      {name:'peep-yellow',form:'yellow'},
      {name:'resident-peep',seed:21,floor:2,form:'cyan'}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const natural=test.seed!==undefined;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',
        scene:`${natural?'resident':'enemy'}-68.0.0`});
      if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',test.floor);}
      else {
        params.set('enemy-boss-form',test.form);params.set('enemy-execute','600:10000');
        if(test.hits){params.append('enemy-hit','20:480');params.append('enemy-hit','30:480');}
      }
      await page.goto(`${base}?${params}`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      const samples=[];
      for(const frame of [80,130,210,360,...(natural?[]:[615])]) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,
          style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        assert(sample.frame<frame+12,'Peep sample missed timing window');
        const p=sample.probe;const dead=frame===615;
        assert.equal(p.alive,!dead);assert.equal(p.threats,dead?0:1);assert.equal(p.kills,dead?1:0);
        assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);
        assert.equal(p.resident.natural,natural);
        if(dead)assert.equal(p.actors.length,0);
        else {
          assert.equal(p.hp,test.hits?480:1440);
          assert.equal(p.boss.form,['normal','cyan','yellow'].indexOf(test.form));
          const children=p.actors.filter(a=>a.componentOwner===p.entity),expected=test.hits||test.form==='cyan'?2:0;
          assert.equal(children.length,expected);assert.equal(p.actors.length,expected+1);assert.equal(p.boss.parts,expected?3:0);
          assert.deepEqual(children.map(a=>a.componentSlot).sort(),expected?[0,1]:[]);
          for(const eye of children)assert.deepEqual([eye.type,eye.variant,eye.subtype],[68,10,0]);
          const body=p.actors.find(a=>a.entity===p.entity);assert(Math.abs(body.radius-(test.form==='yellow'?1.0625:1.25))<.001);
          for(const shot of p.bullets.filter(b=>b.owner===p.entity))assert.equal(shot.kind,11);
          if(test.form==='yellow')assert(p.hazards.some(h=>h.owner===p.entity&&h.tintG===160));
          if(natural){assert.equal(p.resident.floor,test.floor);assert.deepEqual(p.resident.source,[68,0,0]);}
        }
        if(frame===130){sample.capture=`artifacts/enemy-port/wasm-${test.name}.png`;await page.screenshot({path:sample.capture});}
        samples.push(sample);
      }
      assert(samples.some(s=>s.probe.boss.cycles>0),'Boss must complete a real attack');
      assert.deepEqual(errors,[]);checks.push({id:'68.0.0',case:test.name,samples,capture:samples[1].capture,
        scope:natural?'Actual seeded dedicated Peep encounter and owned eyes, Original rendering.':
          'Boss form, detached-eye thresholds/ownership, attacks, yellow creep, execution cleanup and one kill; native special-item exceptions remain open.'});
      console.log(`PASS WASM ${test.name}: boss form, owned eyes, attacks${natural?' in generated stage':', cleanup'}`);
    }
    for(const test of [
      {name:'resident-iblob',id:'15.2.0',from:'15.0.0',seed:92,floor:2,scorched:false,hp:96},
      {name:'resident-grilled',id:'15.3.0',from:'15.3.0',seed:1,floor:0,scorched:true,hp:96},
      {name:'resident-flaming',id:'54.0.0',from:'29.0.0',seed:98,floor:0,scorched:true,hp:64}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',
        scene:`resident-${test.id}`,'resident-seed':String(test.seed),'resident-floor':String(test.floor),'resident-from':test.from});
      await page.goto(`${base}?${params}`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      const samples=[];
      for(const frame of [110,130,160,200]) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,
          style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        assert(sample.frame<frame+10,'Natural resident sample missed timing window');
        const p=sample.probe,r=p.resident;
        assert.equal(r.natural,true);assert.deepEqual(r.source,test.from.split('.').map(Number));
        assert.equal(r.floor,test.floor);assert.equal(r.scorched,test.scorched);
        assert.equal(p.alive,true);assert.equal(p.hp,test.hp);assert(p.threats>1,'Preserve complete natural room population');
        const actor=p.actors.find(a=>a.entity===p.entity);assert(actor);
        assert.deepEqual([actor.type,actor.variant,actor.subtype],test.id.split('.').map(Number));
        assert.equal(p.kills,0);assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);
        if(test.scorched)assert(r.patches>0);else assert.equal(r.patches,0);
        if(frame===130){sample.capture=`artifacts/enemy-port/wasm-${test.name}.png`;await page.screenshot({path:sample.capture});}
        samples.push(sample);
      }
      if(test.id==='54.0.0')assert(samples.some(s=>s.probe.hop.active&&s.probe.y>1.2),'Natural substituted Hopper must actually jump');
      else assert(samples.some(s=>s.probe.bullets.some(p=>p.owner===s.probe.entity)),'Natural resident must emit its own volley');
      assert.deepEqual(errors,[]);checks.push({id:test.id,case:test.name,samples,capture:samples[1].capture,
        scope:'Actual seeded Rourke-account resident, source-slot provenance, untouched room population/cooldowns, active attacks/jump and Original floor-variant rendering.'});
      console.log(`PASS WASM ${test.name}: actual seed ${test.seed}, floor ${test.floor}, source ${test.from}`);
    }
    for(const [id,shots,hp] of [['11.0.0',1,40],['11.1.0',0,32],['12.0.0',1,64],['14.0.0',1,48],['14.1.0',2,72],['10.3.1',0,88],['10.3.2',0,88],['10.3.3',0,88],['10.3.4',0,88],['10.3.5',0,88],['853.0.0',0,24],['15.0.0',4,80],['15.1.0',4,80],['15.2.0',8,96],['15.3.0',4,96],['872.0.0',4,80]]) {
      if(selected&&!selected.includes(id))continue;
      await page.goto(`${base}?verify&mute&smoke&frames=100000&theme=canyon&scene=enemy-${id}`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      await page.waitForFunction(()=>Module.state?.frame>=44&&Module.enemyProbe,null,{timeout:90000});
      const result=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,error:Module.state.error,
        style:Module.state.visualStyleName,gl:Module.ctx.getError()}));
      assert(result.frame<120,'First-cycle sample missed its window');
      assert.equal(result.probe.alive,true);assert.equal(result.probe.shots,shots);assert.equal(result.probe.hp,hp);
      assert.equal(result.probe.threats,1);assert.equal(result.error,'');assert.equal(result.gl,0);
      assert.deepEqual([result.probe.type,result.probe.variant,result.probe.subtype],id.split('.').map(Number));
      assert.equal(result.style,'Original');assert.deepEqual(errors,[]);
      const capture=`artifacts/enemy-port/wasm-${id}.png`;
      await page.screenshot({path:capture});checks.push({id,scope:'First-cycle configured movement/shot-count smoke; not full parity.',...result,capture});
      console.log(`PASS WASM enemy ${id}: ${shots} shots, ${hp} HP, one threat, Original rendering`);
    }
    if(!selected||selected.includes('cloggy-curves')) {
      await page.goto(`${base}?verify&mute&smoke&frames=100000&theme=canyon&scene=enemy-872.0.0`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      const samples=[];
      for(const frame of [48,80,210]) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe}));
        assert(sample.frame<frame+12,'Curved-volley sample missed its window');
        assert.equal(sample.probe.threats,1);
        const curve=frame===210?-.9:.9;
        const shots=sample.probe.bullets.filter(p=>Math.abs(p.curve-curve)<.001);
        assert(shots.length>=2,'Missing live volley with expected handedness');
        for(const p of shots) {
          assert.equal(p.kind,10);assert(Math.abs(Math.hypot(p.vx,p.vy,p.vz)-9)<.002);
          const initialAngle=Math.atan2(p.vz,p.vx)+curve*(5-p.life);
          assert(Math.abs(Math.sin(initialAngle*2))<.005,'Projectile deviated from curved cardinal trajectory');
        }
        assert.equal(sample.probe.hazards.length,0);samples.push(sample);
      }
      const capture='artifacts/enemy-port/wasm-cloggy-curves.png';await page.screenshot({path:capture});
      assert.deepEqual(errors,[]);checks.push({id:'872.0.0',case:'cloggy-curves',samples,capture,
        scope:'Two live volleys alternate curvature, keep speed, follow cardinal launch axes and do not create ground hazards.'});
      console.log('PASS WASM Cloggy: opposite curve directions on successive actual volleys');
    }
    const fireCases=[
      {name:'clotty-flame',id:'15.0.0',flame:['20:1000'],frame:45,body:[15,3,0],hp:96},
      {name:'clotty-burning',id:'15.0.0',burn:['20:1000'],frame:45,body:[15,3,0],hp:96},
      {name:'clotty-live-fire',id:'15.0.0',fire:['20'],frame:45,body:[15,3,0],hp:96,hazards:1},
      {name:'fire-above-cover',id:'14.0.0',fire:['20'],terrain:'cover',frame:75,body:[14,0,0],hp:28,hazards:1},
      {name:'clotty-flooded',id:'15.0.0',flame:['20:10'],burn:['30:20'],flooded:true,frame:45,body:[15,0,0],hp:50},
      {name:'clotty-flooded-death',id:'15.0.0',flame:['20:1000'],flooded:true,frame:45,dead:true},
      {name:'hopper-fire-burn',id:'29.0.0',burn:['20:12','60:12'],flame:['40:1000'],frame:75,body:[54,0,0],hp:36}
    ];
    for(const test of fireCases) {
      if(selected&&!selected.includes(test.name))continue;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`enemy-${test.id}`});
      for(const value of test.flame||[])params.append('enemy-flame-hit',value);
      for(const value of test.burn||[])params.append('enemy-burn-hit',value);
      for(const value of test.fire||[])params.append('enemy-fire',value);
      if(test.flooded)params.set('enemy-flooded','');
      if(test.terrain)params.set('enemy-terrain',test.terrain);
      await page.goto(`${base}?${params}`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,test.frame,{timeout:90000});
      const result=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,error:Module.state.error,
        style:Module.state.visualStyleName,gl:Module.ctx.getError()}));
      assert(result.frame<test.frame+15,'Fire sample missed timing window');
      assert.equal(result.probe.flooded,!!test.flooded);
      assert.equal(result.probe.threats,test.dead?0:1);assert.equal(result.probe.kills,test.dead?1:0);
      assert.equal(result.probe.actors.length,test.dead?0:1);
      if(!test.dead) {
        const actor=result.probe.actors[0];
        assert.deepEqual([actor.type,actor.variant,actor.subtype],test.body);
        assert.equal(actor.entity,result.probe.entity);assert(Math.abs(actor.hp-test.hp)<.002);
        if(test.terrain)assert(actor.y>2.8,'Flying body must stay above cover during elevated fire contact');
      }
      if(test.hazards!==undefined)assert.equal(result.probe.hazards.length,test.hazards);
      assert.equal(result.style,'Original');assert.equal(result.error,'');assert.equal(result.gl,0);assert.deepEqual(errors,[]);
      const capture=`artifacts/enemy-port/wasm-${test.name}.png`;await page.screenshot({path:capture});
      checks.push({id:test.id,case:test.name,...result,capture,scope:'Actual typed flame/burning damage or real flame contact; in-place identity/HP, flooded gameplay exception and kill counts. Flooded map art is not represented by the test condition.'});
      console.log(`PASS WASM ${test.name}: ${result.probe.threats} threats, ${result.probe.kills} kills`);
    }
    for(const test of [
      {name:'hopper-wander',id:'29.0.0',pursuing:false,span:2,peak:53},
      {name:'flaming-pursuit',id:'54.0.0',pursuing:true,span:6,peak:43},
      {name:'hopper-cover',id:'29.0.0',pursuing:true,span:4,peak:53,cover:true},
      {name:'flaming-cover',id:'54.0.0',pursuing:true,span:5,peak:43,cover:true},
      {name:'hopper-cover-morph',id:'29.0.0',pursuing:true,span:4,peak:53,cover:true,morph:true}
    ]) {
      if(selected&&!selected.includes(test.name))continue;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`enemy-${test.id}`});
      if(test.cover)params.set('enemy-terrain','hop-cover');
      if(test.morph)params.set('enemy-flame-hit','48:1000');
      await page.goto(`${base}?${params}`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      const samples=[];
      for(const frame of [test.peak,95]) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe?.hop,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,
          style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
        assert(sample.frame<frame+8,'Hop sample missed arc window');
        const p=sample.probe,h=p.hop;assert.equal(p.threats,1);assert.equal(p.kills,0);assert.equal(p.shots,0);
        assert.equal(h.pursuing,test.pursuing);assert(Math.abs(Math.hypot(h.endX-h.startX,h.endZ-h.startZ)-test.span)<.01);
        assert.equal(p.flightBlocked,false);assert.equal(sample.style,'Original');assert.equal(sample.error,'');assert.equal(sample.gl,0);
        assert.equal(p.actors[0].type,test.morph?54:Number(test.id.split('.')[0]));
        if(frame===test.peak) {
          assert(h.active);assert(p.y>(test.cover?2.8:2));
          const capture=`artifacts/enemy-port/wasm-${test.name}.png`;await page.screenshot({path:capture});sample.capture=capture;
        } else {
          assert.equal(h.active,false);assert(Math.abs(p.y-.85)<.002);assert.equal(p.groundBlocked,false);
          assert(Math.hypot(p.x-h.endX,p.z-h.endZ)<1.1,'Landing differs beyond normal player/body separation');
        }
        if(test.morph)assert(Math.abs(h.duration-.7/1.1)<.001,'Morph changed committed flight timing');
        samples.push(sample);
      }
      assert.deepEqual(errors,[]);checks.push({id:test.id,case:test.name,samples,capture:samples[0].capture,
        scope:'Configured range/wander/pursuit, committed actual-height arc, clear landing and optional in-flight fire morph in Original rendering.'});
      console.log(`PASS WASM ${test.name}: airborne arc and grounded landing`);
    }
    const deathCases=[
      {name:'moter-split',id:'80.0.0',hits:['30:72'],frame:44,count:2,child:[18,0,0],hp:32},
      {name:'moter-overkill',id:'80.0.0',hits:['30:92'],frame:44,count:0},
      {name:'drowned-hive-split',id:'22.1.0',hits:['30:112'],frame:44,count:[1,2],child:[23,1,0],hp:35.2},
      {name:'drowned-hive-overkill',id:'22.1.0',hits:['30:132'],frame:44,count:0},
      {name:'globin-goo',id:'24.0.0',hits:['30:96'],frame:44,count:1,child:[24,0,0],hp:19.2,maxHp:76.8,state:5,kills:0},
      {name:'globin-regrown',id:'24.0.0',hits:['30:96'],frame:200,count:1,child:[24,0,0],hp:76.8,maxHp:76.8,state:0,kills:0},
      {name:'globin-finished',id:'24.0.0',hits:['30:96','190:96','220:50'],frame:235,count:0,kills:1},
      {name:'cursed-goo',id:'24.3.0',hits:['30:112'],frame:44,count:2,child:[24,3,0],hp:23.52,maxHp:78.4,state:5,kills:0},
      {name:'cursed-regrown',id:'24.3.0',hits:['30:112'],frame:150,count:2,child:[24,3,0],hp:78.4,maxHp:78.4,state:0,kills:0}
    ];
    for(const test of deathCases) {
      if(selected&&!selected.includes(test.name))continue;
      const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`enemy-${test.id}`});
      for(const hit of test.hits)params.append('enemy-hit',hit);
      await page.goto(`${base}?${params}`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      await page.waitForFunction(frame=>Module.state?.frame>=frame&&Module.enemyProbe,test.frame,{timeout:90000});
      const result=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,error:Module.state.error,
        style:Module.state.visualStyleName,gl:Module.ctx.getError()}));
      assert(result.frame<test.frame+35,'Death-state sample missed its window');
      const allowed=Array.isArray(test.count)?test.count:[test.count];
      assert(allowed.includes(result.probe.threats));assert.equal(result.probe.actors.length,result.probe.threats);
      for(const actor of result.probe.actors) {
        assert.deepEqual([actor.type,actor.variant,actor.subtype],test.child);
        assert(Math.abs(actor.hp-test.hp)<.002);
        if(test.maxHp!==undefined)assert(Math.abs(actor.maxHp-test.maxHp)<.002);
        if(test.state!==undefined)assert.equal(actor.state,test.state);
      }
      if(test.kills!==undefined)assert.equal(result.probe.kills,test.kills);
      assert.equal(result.error,'');assert.equal(result.gl,0);assert.equal(result.style,'Original');assert.deepEqual(errors,[]);
      const capture=`artifacts/enemy-port/wasm-${test.name}.png`;
      await page.screenshot({path:capture});checks.push({id:test.id,case:test.name,scope:'Scripted death/regrowth transition; partial parity evidence.',...result,capture});
      console.log(`PASS WASM ${test.name}: ${result.probe.threats} threats, ${result.probe.kills} kills`);
    }
    if(!selected||selected.includes('rotten-brood-cycle')) {
      await page.goto(`${base}?verify&mute&smoke&frames=100000&theme=canyon&scene=enemy-10.3.3&enemy-hit=930:1000`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      const samples=[];
      for(const [frame,expected,parentAlive] of [[110,0,true],[130,1,true],[250,2,true],[735,6,true],[910,6,true],[950,6,false]]) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe}));
        assert(sample.frame<frame+8,'Brood sample missed its timing window');
        const children=sample.probe.actors.filter(a=>a.summoner===sample.probe.entity);
        assert.equal(children.length,expected);assert.equal(sample.probe.alive,parentAlive);
        assert.equal(sample.probe.threats,expected+(parentAlive?1:0));assert.equal(sample.probe.shots,0);
        for(const child of children){assert.deepEqual([child.type,child.variant,child.subtype],[853,0,0]);assert.equal(child.maxHp,24);}
        const actors=sample.probe.actors;
        let playerGap=Infinity,bodyGap=Infinity;
        for(let i=0;i<actors.length;++i) {
          const a=actors[i];assert(a.radius>0);
          playerGap=Math.min(playerGap,Math.hypot(a.x-sample.probe.playerX,a.z-sample.probe.playerZ)-a.radius);
          for(let j=i+1;j<actors.length;++j) {
            const b=actors[j];bodyGap=Math.min(bodyGap,Math.hypot(a.x-b.x,a.z-b.z)-a.radius-b.radius);
          }
        }
        assert(playerGap>=.47,'Grounded brood overlaps player');
        assert(bodyGap>=-.025,'Grounded brood bodies overlap one another');
        sample.spacing={playerGap,bodyGap:Number.isFinite(bodyGap)?bodyGap:null};
        if(frame===910)await page.screenshot({path:'artifacts/enemy-port/wasm-rotten-brood-spaced.png'});
        samples.push(sample);
      }
      const capture='artifacts/enemy-port/wasm-rotten-brood-cycle.png';await page.screenshot({path:capture});
      assert.deepEqual(errors,[]);checks.push({id:'10.3.3',case:'rotten-brood-cycle',samples,capture,
        scope:'Two-second summon intervals, six-child ownership cap, body/player spacing, surviving brood after parent death.'});
      console.log('PASS WASM Rotten brood: timed children, six-child cap, physical spacing, survive parent death');
    }
    if(!selected||selected.includes('rotten-orbit-cycle')) {
      await page.goto(`${base}?verify&mute&smoke&frames=100000&theme=canyon&scene=enemy-10.3.5`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      const samples=[];
      for(const frame of [44,120,240,360,480,600]) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe}));
        assert(sample.frame<frame+10);assert.equal(sample.probe.threats,1);assert.equal(sample.probe.shots,0);
        samples.push(sample);
      }
      const speeds=samples.map(s=>Math.hypot(s.probe.actors[0].vx,s.probe.actors[0].vz));
      assert(speeds[0]>2&&speeds[0]<6,'Initial orbit accelerates gradually');
      assert(Math.max(...speeds)>6&&Math.max(...speeds)<8.1,'Orbit reaches bounded high speed');
      const points=samples.map(s=>({x:s.probe.x-s.probe.playerX,z:s.probe.z-s.probe.playerZ}));
      const span=Math.max(...points.map(p=>p.x))-Math.min(...points.map(p=>p.x));
      assert(span>3,'Orbit moves sideways around player, not straight into contact');
      const capture='artifacts/enemy-port/wasm-rotten-orbit-cycle.png';await page.screenshot({path:capture});
      assert.deepEqual(errors,[]);checks.push({id:'10.3.5',case:'rotten-orbit-cycle',samples,speeds,capture,
        scope:'Observed acceleration, bounded speed and circling movement in the actual canyon arena.'});
      console.log('PASS WASM Rotten orbit: acceleration, bounded speed and lateral travel');
    }
    for(const test of [
      {name:'flight-cover-shooter',id:'14.0.0',terrain:'cover',frame:44,shots:1},
      {name:'flight-cover-pursuit',id:'18.0.0',terrain:'cover',frame:90,shots:0},
      {name:'flight-river',id:'18.0.0',terrain:'river',shots:0}]) {
      if(selected&&!selected.includes(test.name))continue;
      await page.goto(`${base}?verify&mute&smoke&frames=100000&theme=canyon&scene=enemy-${test.id}&enemy-terrain=${test.terrain}`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      await page.waitForFunction(()=>Module.state?.frame>=1&&Module.enemyProbe,null,{timeout:90000});
      const start=await page.evaluate(()=>Module.enemyProbe);
      const span=Math.hypot(start.playerX-start.startX,start.playerZ-start.startZ);
      const frame=test.frame||Math.round(span*.5/(3.2*1.1)*60);
      await page.waitForFunction(f=>Module.state?.frame>=f,frame,{timeout:90000});
      const result=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,
        error:Module.state.error,style:Module.state.visualStyleName,gl:Module.ctx.getError()}));
      assert(result.frame<frame+8);assert.equal(result.probe.alive,true);assert.equal(result.probe.flightBlocked,false);
      assert.equal(result.probe.shots,test.shots);assert.equal(result.error,'');assert.equal(result.gl,0);assert.equal(result.style,'Original');
      if(test.terrain==='cover')assert(result.probe.y>=2.84,'Airborne body/hitbox clears the two-metre crate');
      else {assert.equal(result.probe.waterBlocked,true,'Fly actually crosses deep river, not a ford');assert(Math.abs(result.probe.y-.85)<.01);}
      const capture=`artifacts/enemy-port/wasm-${test.name}.png`;await page.screenshot({path:capture});
      let final;
      if(test.id==='18.0.0') {
        const finish=Math.ceil(span/(3.2*1.1)*60)+40;
        await page.waitForFunction(f=>Module.state?.frame>=f,finish,{timeout:90000});
        final=await page.evaluate(()=>Module.enemyProbe);
        assert(Math.hypot(final.x-final.playerX,final.z-final.playerZ)<1,'Fly reaches player across the obstacle');
        assert.equal(final.flightBlocked,false);assert(Math.abs(final.y-.85)<.01,'Fly returns to normal height');
      }
      assert.deepEqual(errors,[]);checks.push({id:test.id,case:test.name,...result,final,capture,
        scope:'Real airborne position over crate/deep river; active-room bounds and unobstructed pursuit, with aimed shooter emission.'});
      console.log(`PASS WASM ${test.name}: visible flight elevation and reachable player`);
    }
    if(!selected||selected.includes('ring-formation')) {
      await page.goto(`${base}?verify&mute&smoke&frames=100000&theme=canyon&scene=enemy-222.0.0&enemy-count=10&enemy-hit=200:1000`);
      await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
      await page.locator('#start').click({noWaitAfter:true});
      const samples=[];
      for(const frame of [160,240]) {
        await page.waitForFunction(f=>Module.state?.frame>=f&&Module.enemyProbe,frame,{timeout:90000});
        const sample=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,gl:Module.ctx.getError(),error:Module.state.error}));
        assert(sample.frame<frame+10);assert.equal(sample.probe.groups.length,1);
        const group=sample.probe.groups[0];assert.equal(group.slots.length,10);
        assert.equal(sample.probe.threats,frame===160?10:9);assert.equal(sample.probe.alive,frame===160);
        assert.equal(sample.probe.shots,0);assert.equal(sample.gl,0);assert.equal(sample.error,'');assert.equal(sample.style,'Original');
        assert(group.z-sample.probe.startZ>3,'Group centre translates toward the player');
        for(const actor of sample.probe.actors){assert.equal(actor.formation,group.id);assert(Math.abs(Math.hypot(actor.x-group.x,actor.z-group.z)-2.4)<.03);}
        samples.push(sample);
      }
      const [before,after]=samples.map(s=>s.probe.groups[0]);assert.equal(before.id,after.id);
      assert.deepEqual(before.slots.map(s=>s.angle),after.slots.map(s=>s.angle),'Deaths do not redistribute angular slots');
      assert.equal(after.slots.filter(s=>!s.member).length,1);assert.deepEqual(errors,[]);
      const capture='artifacts/enemy-port/wasm-ring-formation.png';await page.screenshot({path:capture});
      checks.push({id:'222.0.0',case:'ring-formation',samples,capture,scope:'Ten-member moving circle, preserved slots and nine surviving threats after founder death; partial behavior/visual acceptance.'});
      console.log('PASS WASM Ring Fly formation: translating circle, preserved slots and founder-independent lifetime');
    }
    assert(checks.length>0,'No requested cases matched');
    if(selected)for(const name of selected)assert(checks.some(c=>(c.case||c.id)===name),`Missing requested case: ${name}`);
    fs.writeFileSync(process.env.DEATHWARD_ENEMY_CHECK_OUTPUT||'/tmp/deathward-enemy-port-browser-checks.json',
      JSON.stringify({platform:'WASM/Chromium',browser:await browser.version(),checks,errors},null,2)+'\n');
  } catch(error) {
    console.error('Browser errors:',JSON.stringify(errors));
    const failureState=await page.evaluate(()=>({state:window.Module?.state,
      probe:window.Module?.enemyProbe,problem:document.querySelector('#problem')?.textContent})).catch(()=>null);
    console.error('Failure state:',JSON.stringify(failureState));
    fs.writeFileSync(process.env.DEATHWARD_ENEMY_CHECK_OUTPUT||'/tmp/deathward-enemy-port-browser-checks.json',
      JSON.stringify({platform:'WASM/Chromium',partial:true,checks,errors,failure:String(error),failureState},null,2)+'\n');
    throw error;
  } finally {await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1;});
