const {chromium}=require('playwright'),assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const out=process.env.DEATHWARD_LEAPER_OUTPUT;fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}}),checks=[],errors=[];
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {
  const cases=[['normal',0],['sticky',1],['cover',0],['river',0],['resident-normal',0],['resident-sticky',1],['death',1]];
  for(const [name,variant] of cases) {
   if(process.env.DEATHWARD_LEAPER_CASES&&!process.env.DEATHWARD_LEAPER_CASES.split(',').includes(name))continue;
   const natural=name.startsWith('resident'),dying=name==='death',id=`34.${variant}.0`;
   const query=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${id}`});
   if(natural){query.set('resident-seed',variant?8:2);query.set('resident-floor',4);}
   else if(name==='cover')query.set('enemy-terrain','hop-cover');
   else if(name==='river')query.set('enemy-terrain','river');
   if(!natural&&name!=='river')for(let frame=60;frame<=2100;frame+=60) {
    const x=name==='cover'?2:6,z=name==='cover'?4:8;
    query.append('enemy-player-at',`${frame}:${frame%120?x:-x}:${z}`);
   }
   if(dying)query.set('enemy-hit','900:10000');
   const result={name,id,pass:false,samples:[],captures:{}};checks.push(result);console.log('START',name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${query}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   let high=false,ordinary=false,water=false,peak=.85,volleys=0,finished=false;
   for(let frame=10;frame<=2400;frame+=4) {
    await page.waitForFunction(f=>Module.state?.error||Module.state?.frame>=f,frame,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError(),p:Module.enemyProbe}));
    const a=s.p.actors.find(a=>a.entity===s.p.entity);
    result.samples.push({frame:s.frame,style:s.style,error:s.error,gl:s.gl,actor:a,shots:s.p.shots,kills:s.p.kills,water:s.p.waterBlocked,flight:s.p.flightBlocked,bullets:s.p.bullets,hazards:s.p.hazards});
    if(frame%100===10)console.log('PROGRESS',name,s.frame,'leaps',a?.leaper?.leaps,'volleys',a?.leaper?.volleys);
    assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(s.p.resident.natural,natural);
    if(a) {
     assert(a.leaper&&a.targetHop);assert(Math.abs(a.maxHp-(variant?89.6:80))<.01);assert(!s.p.flightBlocked);
     high||=a.leaper.phase>0&&a.targetHop.airborne;ordinary||=a.targetHop.hops>0;water||=s.p.waterBlocked;peak=Math.max(peak,a.y);volleys=Math.max(volleys,a.leaper.volleys);
     if(!natural)assert.equal(s.p.shots,a.leaper.volleys*(variant?6:4),'no shots on ordinary hops or generic burst');
     for(const bullet of s.p.bullets.filter(b=>b.owner===s.p.entity)) {
      assert.equal(bullet.kind,0);assert(Math.abs(bullet.gravity-(variant?63.9:4.5))<.01);
      assert(Math.abs(Math.hypot(bullet.vx,bullet.vz)-(variant?21:27))<.02);
      if(!variant)assert(Math.abs(bullet.vx)<.01||Math.abs(bullet.vz)<.01);
     }
    }
    if(dying&&!a&&s.frame>910){assert.equal(s.p.kills,1);assert.equal(s.p.actors.length,0);finished=true;}
    const shot=finished?'death':natural&&a?.leaper.volleys?'resident':
      a?.leaper.phase===1&&!a.targetHop.airborne?'warning':
      a?.leaper.phase>0&&a.targetHop.airborne&&a.y>3?'high':
      a?.leaper.volleys&&s.p.bullets.some(b=>b.owner===s.p.entity)?'volley':null;
    if(shot&&!result.captures[shot]){result.captures[shot]=`${out}/${name}-${shot}.png`;await page.screenshot({path:result.captures[shot]});}
    if(dying?finished:(high&&ordinary&&volleys>=1&&(natural?result.captures.resident:result.captures.high&&(name==='river'||result.captures.volley))&&(name!=='river'||water)))break;
   }
   assert(high&&ordinary&&volleys>0,'ordinary and high hops both occur naturally');
   if(dying)assert(finished&&result.captures.death);
   else if(natural)assert(result.captures.resident);
   else assert(result.captures.high&&(name==='river'||result.captures.volley));
   if(name==='river')assert(water);
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,high,ordinary,water,peak,volleys,finished});console.log('PASS',name,'volleys',volleys);
  }
 } finally {
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({browser:await browser.version(),checks,errors,scope:'Production WASM ordinary/high hopping, source landing volleys, cover/water, natural middle-floor encounters and death in Original style. Native tests establish exact source timing and retained capacity. Full six-gate acceptance remains open.'},null,2)+'\n');await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
