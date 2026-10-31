const {chromium}=require('playwright');
const fs=require('node:fs');
(async()=>{
 const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
 try {
  const page=await browser.newPage({viewport:{width:1280,height:848}});
  await page.goto('http://127.0.0.1:8098/?verify&mute&smoke&frames=100000&theme=canyon&scene=enemy-14.2.0&enemy-terrain=river');
  await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});await page.locator('#start').click({noWaitAfter:true});
  await page.waitForFunction(()=>Module.state?.frame>280&&Module.enemyProbe?.waterBlocked,null,{timeout:90000});
  const data=await page.evaluate(()=>({frame:Module.state.frame,probe:Module.enemyProbe,style:Module.state.visualStyleName,error:Module.state.error,gl:Module.ctx.getError()}));
  if(data.style!=='Original'||data.error||data.gl||!data.probe.waterBlocked)throw Error('Unexpected visual capture state');
  await page.screenshot({path:'docs/reports/isaac-enemy-port/tainted_pooter/browser-river.png'});
  fs.writeFileSync('docs/reports/isaac-enemy-port/tainted_pooter/browser-river.json',JSON.stringify(data,null,2)+'\n');
 }finally{await browser.close();}
})().catch(e=>{console.error(e);process.exit(1)});
