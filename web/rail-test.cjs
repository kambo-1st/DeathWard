// Run the same authored-rail/content tests in an actual browser WebAssembly VM.
// The input directory contains an Emscripten build of tests/rail_tests.cpp.
// This is behavior/content evidence, not a rendered boss encounter.
const fs = require('node:fs');
const path = require('node:path');
const http = require('node:http');
const { chromium } = require('playwright');
const root = path.resolve(process.argv[2] || '/tmp/deathward-rail-wasm');
const output = process.argv[3] || 'artifacts/enemy-port/rail-wasm.json';
const html = `<!doctype html><html><body><pre id="log"></pre><script>
window.railResult={lines:[],errors:[],status:null};
var Module={print(t){railResult.lines.push(t);document.getElementById('log').textContent+=t+'\\n';},
printErr(t){railResult.errors.push(t);},onExit(code){railResult.status=code;},
onAbort(reason){railResult.errors.push(String(reason));railResult.status=-1;}};
</script><script src="index.js"></script></body></html>`;
const server = http.createServer((req,res)=>{
  let relative;
  try { relative=decodeURIComponent(new URL(req.url,'http://localhost').pathname); }
  catch {res.writeHead(400);res.end();return;}
  if(relative==='/'){res.setHeader('Content-Type','text/html');res.end(html);return;}
  const file=path.resolve(root,'.'+relative);
  if(!file.startsWith(root+path.sep)){res.writeHead(403);res.end();return;}
  const mime=file.endsWith('.wasm')?'application/wasm':file.endsWith('.js')?'text/javascript':'application/octet-stream';
  fs.readFile(file,(error,bytes)=>{res.writeHead(error?404:200,{'Content-Type':mime});res.end(error?'not found':bytes);});
});
(async()=>{
  let browser;
  try {
    await new Promise(resolve=>server.listen(0,'127.0.0.1',resolve));
    browser=await chromium.launch({headless:true,executablePath:process.env.DEATHWARD_BROWSER,
      args:['--no-sandbox','--disable-gpu']});
    const page=await browser.newPage();const errors=[];page.on('pageerror',error=>errors.push(String(error)));
    await page.goto(`http://127.0.0.1:${server.address().port}/`);
    await page.waitForFunction(()=>window.railResult?.status!==null,{},{timeout:60000});
    const result=await page.evaluate(()=>window.railResult);
    const prefixes=['RAIL_GEOMETRY','RAIL_INSTALLED','RAIL_VALIDATION','RAIL_CONTENT'];
    const passed=result.status===0&&result.errors.length===0&&errors.length===0&&prefixes.every(p=>result.lines.some(s=>s.startsWith(p)));
    const report={platform:'WASM/Chromium',browser:browser.version(),passed,...result,pageErrors:errors,
      scope:'Same C++ authored-rail behavior, topology and immutable content tests as native. No boss AI or game-rendering acceptance.'};
    fs.mkdirSync(path.dirname(output),{recursive:true});fs.writeFileSync(output,JSON.stringify(report,null,2)+'\n');
    for(const line of result.lines)console.log(line);
    console.log(`WASM rail tests: ${passed?'PASS':'FAIL'}`);
    if(!passed)process.exitCode=1;
  } catch(error) { console.error(error);process.exitCode=1; }
  finally {if(browser)await browser.close();await new Promise(resolve=>server.close(resolve));}
})();
