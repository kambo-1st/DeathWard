// Real seeded populations and frame-synchronous captures on the production build.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_LINKED_HEAD_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[];
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 // Read the canvas at the real C++ EndDrawing boundary, including async builds.
 // No simulation state changes and no labels from an older tick.
 await page.addInitScript(()=>{
  window.__linkedCaptures={};
  window.__captureLinkedFrame=frame=>{
   const m=window.Module,p=m?.enemyProbe;
   if(!p)return;
   const body=p.actors.find(a=>a.entity===p.entity),head=p.actors.find(a=>a.type===35&&(a.variant===1||a.variant===3));
   const kind=body?.type===35&&head?(body.linkedHead?.extended?'extended':'attached'):
    p.actors.some(a=>a.type===26)?'survivor':null;
   if(!kind||window.__linkedCaptures[kind])return;
   const canvas=m.canvas||document.querySelector('canvas');
   const sample=document.createElement('canvas');sample.width=sample.height=16;
   const ctx=sample.getContext('2d');ctx.drawImage(canvas,0,0,16,16);
   const pixels=ctx.getImageData(0,0,16,16).data;
   let min=255,max=0;for(let i=0;i<pixels.length;i+=4){min=Math.min(min,pixels[i]);max=Math.max(max,pixels[i]);}
   window.__linkedCaptures[kind]={frame,probe:JSON.parse(JSON.stringify(p)),colorRange:max-min,png:canvas.toDataURL('image/png')};
  };
 });
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const w=JSON.parse(fs.readFileSync(process.env.DEATHWARD_LINKED_HEAD_WITNESSES,'utf8'));
 const unique=[...new Map([...w.bands,...w.rivers].map(t=>[`${t.seed}:${t.floor}:${t.room}`,t])).values()];
 const cases=[...unique.map(t=>({...t,name:`resident-${t.variant}-band-${t.band}-seed-${t.seed}`})),
  {name:'exact-normal',variant:0},{name:'exact-red',variant:2},{name:'exact-body-death',variant:0,death:true}];
 try {
  for(const t of cases){
   if(process.env.DEATHWARD_LINKED_HEAD_CASES&&!process.env.DEATHWARD_LINKED_HEAD_CASES.split(',').includes(t.name))continue;
   const natural=t.seed!==undefined,q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',
    'enemy-camera-follow':'',scene:`${natural?'resident':'enemy'}-35.${t.variant}.0`});
   if(natural){q.set('resident-seed',t.seed);q.set('resident-floor',t.floor);}
   if(t.death)q.set('enemy-hit','8:10000');
   const result={name:t.name,witness:t,pass:false,samples:[],captures:{}};checks.push(result);console.log('START',t.name);
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureLinkedFrame;});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   let pair=false,thrown=false,movement=0,previous;
   for(let f=4;f<=(t.death?20:240);f+=4){
    await page.waitForFunction(n=>Module.state?.error||Module.state?.frame>=n,f,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,error:Module.state.error,gl:Module.ctx.getError(),style:Module.state.visualStyleName,p:Module.enemyProbe}));
    result.samples.push(s);assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(s.style,'Original');
    assert.equal(s.p.resident.natural,natural);
    if(natural){assert.equal(s.p.resident.floor,t.floor);assert.equal(s.p.resident.room,t.room);}
    const b=s.p.actors.find(a=>a.entity===s.p.entity),h=s.p.actors.find(a=>a.type===35&&a.variant===t.variant+1);
    if(b?.type===35){
     assert.equal(b.variant,t.variant);assert.equal(b.maxHp,80);assert(b.linkedHead?.ticks>0);
     assert(!s.p.groundBlocked&&!s.p.waterBlocked,'generated grounded body remains on legal terrain');
     if(previous)movement+=Math.hypot(b.x-previous.x,b.z-previous.z);previous=b;
     if(h){pair=true;assert.equal(h.maxHp,t.variant===2?32:80);assert(h.linkedHead);
      if(b.linkedHead.extended){thrown=true;assert.equal(h.linkedHead.neckCount,8);}}
    }
    if(!natural&&!t.death)assert(b?.type===35,'isolated pair retained through capture');
    if(t.death&&s.frame>8){assert(!b);assert(s.p.actors.some(a=>a.type===26&&a.hp===64));}
   }
   // Persist the image and its exact matching probe, never a later Playwright frame.
   const captures=await page.evaluate(()=>window.__linkedCaptures);
   for(const [kind,c] of Object.entries(captures)){
    assert(c.colorRange>40,'capture contains actual scene colors, not a cleared canvas');
    const path=`${out}/${t.name}-${kind}.png`;fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));
    delete c.png;result.captures[kind]={path,...c};
   }
   assert(pair||t.death,'actual separately damageable linked head observed');
   if(!natural&&!t.death){assert(thrown);assert(captures.attached&&captures.extended);}
   if(t.death)assert(captures.survivor);
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,pair,thrown,movement});console.log('PASS',t.name);
  }
 }finally{
  fs.writeFileSync(`${out}/results.json`,JSON.stringify({browser:await browser.version(),checks,errors,
   scope:'Seven unmodified seeded populations plus exact-frame rendered attached, thrown and survivor captures. Partial acceptance evidence.'},null,2)+'\n');
  await browser.close();
 }
})().catch(e=>{console.error(e);process.exit(1)});
