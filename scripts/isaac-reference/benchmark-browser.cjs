// Same seed/stress scenario as the native --benchmark; no player save/settings.
const {chromium}=require('playwright');
const fs=require('node:fs');
const path=require('node:path');
(async()=>{
  const browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
    args:['--no-sandbox','--enable-gpu','--use-gl=angle','--use-angle=gl','--ignore-gpu-blocklist']});
  const page=await browser.newPage({viewport:{width:1440,height:900}});
  const errors=[],lines=[];
  page.on('pageerror',e=>errors.push(String(e)));
  page.on('console',m=>{
    lines.push(m.text());
    if(/INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed/i.test(m.text()))errors.push(m.text());
  });
  try {
    await page.goto((process.env.DEATHWARD_WEB_URL||'http://127.0.0.1:8098/')+'?verify&mute');
    await page.waitForFunction(()=>window.Module?.ready,null,{timeout:90000});
    await page.evaluate(()=>Module.callMain(['--benchmark','--theme','canyon','--style','original','--frames','360','--mute']));
    await page.waitForFunction(()=>Module.gameFinished,null,{timeout:300000});
    if(errors.length)throw new Error(errors.join('\n'));
    const line=lines.find(s=>s.startsWith('BENCHMARK '));
    if(!line)throw new Error('No completed benchmark measurements');
    const fields=Object.fromEntries([...line.matchAll(/(\w+)=([^ ]+)/g)].map(m=>[m[1],Number.isFinite(Number(m[2]))?Number(m[2]):m[2]]));
    const result={platform:'WASM/Chromium',date:new Date().toISOString(),
      browser:await browser.version(),device:lines.filter(s=>/Vendor:|Renderer:|Version:/.test(s)),
      scenario:'Existing 100-enemy/600-shot stress; saturation test, not normal-play FPS or full enemy-port coverage.',
      measurements:fields,errors};
    const output=process.env.DEATHWARD_BENCHMARK_OUTPUT||'/tmp/deathward-enemy-port-browser-benchmark.json';
    fs.mkdirSync(path.dirname(output),{recursive:true});fs.writeFileSync(output,JSON.stringify(result,null,2)+'\n');
    console.log(JSON.stringify(result,null,2));
  } finally {await browser.close();}
})().catch(e=>{console.error(e);process.exitCode=1;});
