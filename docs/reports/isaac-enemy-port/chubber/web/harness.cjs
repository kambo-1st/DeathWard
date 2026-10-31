// Real production WASM, source-clock observations and draw-boundary captures.
const assert=require('node:assert/strict'),fs=require('node:fs');
(async()=>{
 const {chromium}=require('playwright'),out=process.env.DEATHWARD_CHUBBER_OUTPUT;
 fs.mkdirSync(out,{recursive:true});const checks=[],errors=[],renderers=[];
 const headless=process.env.DEATHWARD_BROWSER_HEADFUL!=='1';
 const browser=await chromium.launch({headless,executablePath:process.env.DEATHWARD_BROWSER,
  args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 const page=await browser.newPage({viewport:{width:1280,height:848}});
 await page.addInitScript(()=>{
  window.__chubberCaptures={};
  window.__captureChubber=frame=>{
   const m=window.Module,p=m?.enemyProbe,a=p?.actors.find(a=>a.entity===p.entity),r=a?.vis;
   const c=p?.actors.find(a=>a.returningBody);
   if(c&&(c.returningBody.frame<5||(c.returningBody.frame>20&&c.returningBody.frame<38)))return;
   const kind=c?(c.returningBody.frame>=38?'return':'outbound'):!a?'cleanup':r?.frame>5&&!r.fired?'windup':'walk';
   if(window.__chubberCaptures[kind])return;
   const canvas=m.canvas||document.querySelector('canvas'),sample=document.createElement('canvas');
   sample.width=sample.height=16;const ctx=sample.getContext('2d');ctx.drawImage(canvas,0,0,16,16);
   const pixels=ctx.getImageData(0,0,16,16).data;let min=255,max=0;
   for(let i=0;i<pixels.length;i+=4){min=Math.min(min,pixels[i]);max=Math.max(max,pixels[i]);}
   window.__chubberCaptures[kind]={frame,probe:JSON.parse(JSON.stringify(p)),colorRange:max-min,png:canvas.toDataURL('image/png')};
  };
 });
 page.on('pageerror',e=>errors.push(String(e)));
 page.on('console',m=>{if(/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());});
 const persist=()=>fs.writeFileSync(`${out}/results.json`,JSON.stringify({headless,renderers,checks,errors,
  scope:'Production isolated Chubber/controller rendering smoke; full visual, balance and performance gates remain open.'},null,2)+'\n');
 try {
  for(const t of [{name:'vertical'},{name:'horizontal',horizontal:true},{name:'cover',terrain:'cover'},
   {name:'river',terrain:'river'},{name:'owner-death',kill:true}]) {
   if(process.env.DEATHWARD_CHUBBER_CASES&&!process.env.DEATHWARD_CHUBBER_CASES.split(',').includes(t.name))continue;
   const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',style:'original',
    scene:'enemy-39.2.0','enemy-camera-follow':''});
   if(t.terrain)q.set('enemy-terrain',t.terrain);
   if(t.horizontal)q.set('enemy-player-at','1:10:0');
   if(t.terrain==='river')q.set('enemy-player-at','1:0:10');
   if(t.kill)q.set('enemy-hit','70:10000');
   const result={name:t.name,query:q.toString(),pass:false,samples:[],captures:{}};checks.push(result);console.log('START',t.name);persist();
   await page.goto(`${process.env.DEATHWARD_WEB_URL}?${q}`);await page.waitForFunction(()=>Module.ready,null,{timeout:90000});
   await page.evaluate(()=>{Module.captureEnemyFrame=window.__captureChubber;});
   await page.locator('#start').click({noWaitAfter:true});await page.waitForFunction(()=>Module.ctx&&Module.enemyProbe,null,{timeout:90000});
   const renderer=await page.evaluate(()=>{const gl=Module.ctx,e=gl.getExtension('WEBGL_debug_renderer_info');return e?gl.getParameter(e.UNMASKED_RENDERER_WEBGL):gl.getParameter(gl.RENDERER);});
   renderers.push({name:t.name,renderer});console.log('RENDERER',renderer);persist();let emitted=false,returned=false,cleaned=false;
   for(let f=4;f<=180;f+=4) {
    await page.waitForFunction(n=>Module.state?.error||Module.state?.frame>=n,f,{timeout:90000});
    const s=await page.evaluate(()=>({frame:Module.state.frame,error:Module.state.error,gl:Module.ctx.getError(),style:Module.state.visualStyleName,p:Module.enemyProbe}));
    result.samples.push(s);assert.equal(s.error,'');assert.equal(s.gl,0);assert.equal(s.style,'Original');
    const a=s.p.actors.find(a=>a.entity===s.p.entity),children=s.p.actors.filter(a=>a.returningBody);
    if(!t.kill||s.frame<70){assert(a?.vis);assert.equal(a.maxHp,80);}
    for(const c of children) {
     assert.equal(c.type,39);assert.equal(c.variant,22);assert.equal(c.hp,0);assert.equal(c.maxHp,0);
     assert.equal(c.componentOwner,s.p.entity);assert(a,'no orphan child');assert(c.returningBody.frame<=42);
     assert(Math.abs(Math.hypot(c.returningBody.initialX,c.returningBody.initialZ)-(t.horizontal?67.2:48))<.02);
     emitted=true;returned||=c.returningBody.frame>22;
    }
    if(t.kill&&s.frame>72){assert(!a&&children.length===0,'owner death removes component');cleaned=true;break;}
    if(!t.kill&&emitted&&returned&&children.length===0){cleaned=true;break;}
   }
   const captures=await page.evaluate(()=>window.__chubberCaptures);
   for(const [kind,c] of Object.entries(captures)) {
    assert(c.colorRange>40);const path=`${out}/${t.name}-${kind}.png`;
    fs.writeFileSync(path,Buffer.from(c.png.split(',')[1],'base64'));delete c.png;result.captures[kind]={path,...c};
   }
   assert(emitted&&cleaned,'actual attack and cleanup');if(!t.kill)assert(returned,'return phase observed');
   assert(captures.windup&&captures.outbound,'actual rendered warning and body');
   assert.deepEqual(errors,[]);Object.assign(result,{pass:true,emitted,returned,cleaned});console.log('PASS',t.name);persist();
  }
 }finally{persist();await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
