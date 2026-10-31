const {chromium}=require('playwright');const fs=require('fs');const assert=require('node:assert/strict');
(async()=>{const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
const page=await browser.newPage({viewport:{width:1280,height:848}}),errors=[],views=[];page.on('pageerror',e=>errors.push(String(e)));
try{for(const variant of [0,1]){
 const q=new URLSearchParams({verify:'',mute:'',smoke:'',frames:'100000',theme:'canyon',scene:`enemy-16.${variant}.0`,'enemy-hit':'100:42'});
 await page.goto('http://127.0.0.1:8098/?'+q);await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
 await page.waitForFunction(()=>Module.state?.frame>=105,null,{timeout:90000});
 const view=await page.evaluate(()=>({frame:Module.state.frame,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError(),probe:Module.enemyProbe}));
 assert.equal(view.style,'Original');assert.equal(view.error,'');assert.equal(view.gl,0);assert(!view.probe.alive);assert.equal(view.probe.kills,1);
 if(variant===0)assert.equal(view.probe.actors.length,4);else{assert.equal(view.probe.enemyBombs.length,1);assert.equal(view.probe.shots,4);}
 view.path=`docs/reports/isaac-enemy-port/mulligans/web/${variant?'mulligoon':'mulligan'}-death-visible.png`;await page.screenshot({path:view.path});views.push(view);
 }}finally{fs.writeFileSync('docs/reports/isaac-enemy-port/mulligans/browser-visuals.json',JSON.stringify({views,errors},null,2)+'\n');await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
