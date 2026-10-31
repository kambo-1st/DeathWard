// Production WASM probes for source-derived ordinary and Flaming Hoppers.
const assert=require('node:assert/strict'),fs=require('node:fs');
const hopperCases=[
 {name:'hopper-pursuit',type:29},{name:'flaming-pursuit',type:54},
 {name:'hopper-cover',type:29,terrain:'hop-cover'},{name:'flaming-cover',type:54,terrain:'hop-cover'},
 {name:'hopper-cover-morph',type:29,terrain:'hop-cover',morph:true},
 {name:'hopper-river',type:29,terrain:'river'},
 {name:'resident-hopper',type:29,seed:0},{name:'resident-flaming-hopper',type:54,seed:5},
 {name:'hopper-death',type:29,death:true}
];
async function runHopperCases(page,base,out,selected,checks,errors) {
 fs.mkdirSync(out,{recursive:true});
 for(const test of hopperCases) {
  if(selected&&!selected.includes(test.name))continue;
  const natural=test.seed!==undefined,id=`${test.type}.0.0`;
  const params=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`${natural?'resident':'enemy'}-${id}`});
  if(natural){params.set('resident-seed',test.seed);params.set('resident-floor',0);}
  if(test.terrain)params.set('enemy-terrain',test.terrain);
  if(test.morph)params.set('enemy-flame-hit','20:1000');
  if(test.death)params.set('enemy-hit','30:10000');
  const result={name:test.name,id,pass:false,samples:[],captures:{}};checks.push(result);console.log('START',test.name);
  await page.goto(`${base}?${params}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
  await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
  let air=false,land=false,water=false,overCover=false,morph=false,dead=false,peak=.85;
  for(let frame=8;frame<=600;frame+=2) {
   await page.waitForFunction(f=>Module.state?.error||Module.state?.frame>=f,frame,{timeout:90000});
   const s=await page.evaluate(()=>({frame:Module.state.frame,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError(),p:Module.enemyProbe}));
   const p=s.p,a=p.actors.find(a=>a.entity===p.entity),h=a?.targetHop;
   result.samples.push({frame:s.frame,style:s.style,error:s.error,gl:s.gl,actor:a,shots:p.shots,kills:p.kills,ground:p.groundBlocked,water:p.waterBlocked,flight:p.flightBlocked,bullets:p.bullets,hazards:p.hazards});
   assert.equal(s.style,'Original');assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(p.resident.natural,natural);
   if(a) {
    assert(h,'actual actor uses source destination hopping');assert.equal(a.type,test.morph&&s.frame>=20?54:test.type);
    assert(Math.abs(a.maxHp-(a.type===29?32:64))<.01);assert.equal(p.flightBlocked,false);
    assert(!p.bullets.some(b=>b.owner===p.entity),'Hopper does not gain a ranged attack');
    if(!natural){assert.equal(p.shots,0);assert.equal(p.hazards.length,0);assert.equal(p.kills,0);}
    air||=h.airborne;land||=air&&!h.airborne&&h.landings>0;water||=p.waterBlocked;overCover||=h.airborne&&p.groundBlocked;
    morph||=a.type===54&&h.transformedFlight;peak=Math.max(peak,a.y);
   } else if(test.death&&s.frame>=30){assert.equal(p.kills,1);assert.equal(p.actors.length,0);dead=true;}
   const shot=dead?'death':test.morph&&h?.transformedFlight&&a.y>2?'morph':
    natural&&h?.airborne&&a.y>1.5?'resident':!natural&&h?.airborne&&a.y>(test.terrain==='hop-cover'?3:1.9)?'air':
    land&&!natural?'land':null;
   // Let the normal capture camera settle before certifying a readable view.
   // The first-flight transformation/death views are retained as diagnostics.
   if(shot&&(s.frame>=150||shot==='morph'||shot==='death')&&!result.captures[shot]){result.captures[shot]=`${out}/${test.name}-${shot}.png`;await page.screenshot({path:result.captures[shot]});}
   const ready=test.death?dead&&air:air&&land&&(!test.morph||morph)&&
    (test.terrain!=='river'||water)&&(test.terrain!=='hop-cover'||overCover)&&
    (natural?result.captures.resident:result.captures.land&&(test.morph?result.captures.morph:result.captures.air));
   if(ready)break;
  }
  assert(air,'observed real flight');if(test.death)assert(dead);else assert(land,'observed completed flight');
  if(test.morph)assert(morph,'fire morph retained committed in-flight controller');
  if(test.terrain==='river')assert(water,'crossed actual deep river');
  if(test.terrain==='hop-cover')assert(overCover,'crossed actual solid cover');
  assert.deepEqual(errors,[]);Object.assign(result,{pass:true,air,land,water,overCover,morph,dead,peak});console.log('PASS',test.name);
 }
}
module.exports={runHopperCases};
if(require.main===module)(async()=>{
 const {chromium}=require('playwright');
 const out=process.env.DEATHWARD_HOPPER_OUTPUT,checks=[],errors=[];fs.mkdirSync(out,{recursive:true});
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 page.on('pageerror',e=>errors.push(String(e)));page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 try {await runHopperCases(page,process.env.DEATHWARD_WEB_URL,out,process.env.DEATHWARD_HOPPER_CASES?.split(','),checks,errors);}
 finally {fs.writeFileSync(`${out}/results.json`,JSON.stringify({browser:await browser.version(),checks,errors,scope:'Actual production WASM flight, terrain, fire morph, natural early-floor residents and death. Native tests cover exact source timing/lead and status/reload invariants. Full six-gate acceptance remains open.'},null,2)+'\n');await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
