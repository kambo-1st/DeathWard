// Exercise the actual upload ZIP on a plain server, with no path rewrites or compression.
const {chromium} = require('playwright');
const assert = require('node:assert/strict');
const crypto = require('node:crypto');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const {execFileSync, spawn} = require('node:child_process');

const root = path.resolve(__dirname, '..');
const archive = path.resolve(process.argv[2] || path.join(root, 'dist/deathward-web.zip'));
const artifacts = path.join(root, 'artifacts');
const temporary = fs.mkdtempSync(path.join(os.tmpdir(), 'deathward-upload-'));
const options = {
  headless: process.env.DEATHWARD_HEADFUL !== '1',
  args: ['--no-sandbox', '--enable-gpu', '--use-gl=angle', '--use-angle=gl', '--ignore-gpu-blocklist'],
};
if (process.env.DEATHWARD_BROWSER) options.executablePath = process.env.DEATHWARD_BROWSER;

(async () => {
  let server, browser;
  const errors = [], network = [];
  try {
    execFileSync('python3', ['-c', `
import pathlib, sys, zipfile
with zipfile.ZipFile(sys.argv[1]) as bundle:
    assert bundle.testzip() is None
    for destination in [pathlib.Path(sys.argv[2]), pathlib.Path(sys.argv[2]) / 'deathward']:
        bundle.extractall(destination)
`, archive, temporary]);
    const manifest = JSON.parse(fs.readFileSync(path.join(temporary, 'manifest.json')));
    for (const [name, metadata] of Object.entries(manifest.files)) {
      const data = fs.readFileSync(path.join(temporary, name));
      assert.equal(data.length, metadata.bytes);
      assert.equal(crypto.createHash('sha256').update(data).digest('hex'), metadata.sha256);
    }
    console.log('PASS upload ZIP integrity and runtime file hashes');
    server = spawn('python3', ['-u', '-c', `
from functools import partial
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
import sys
server = ThreadingHTTPServer(('127.0.0.1', 0), partial(SimpleHTTPRequestHandler, directory=sys.argv[1]))
print('READY', server.server_port, flush=True)
server.serve_forever()
`, temporary], {stdio: ['ignore', 'pipe', 'pipe']});
    server.stderr.on('data', () => {});
    const port = await new Promise((resolve, reject) => {
      const timer = setTimeout(() => reject(new Error('Static test server did not start')), 10000);
      server.once('error', error => { clearTimeout(timer); reject(error); });
      server.once('exit', code => { clearTimeout(timer); reject(new Error(`Server exited: ${code}`)); });
      let output = '';
      server.stdout.on('data', chunk => {
        output += chunk;
        const match = output.match(/READY (\d+)/);
        if (match) { clearTimeout(timer); resolve(Number(match[1])); }
      });
    });
    const base = `http://127.0.0.1:${port}`;
    const redirect = await fetch(`${base}/deathward?verify&mute`, {redirect: 'manual'});
    assert.equal(redirect.status, 301);
    assert.equal(redirect.headers.get('location'), '/deathward/?verify&mute');
    browser = await chromium.launch(options);
    fs.mkdirSync(artifacts, {recursive: true});
    for (const [mount, hub] of [['/', 0], ['/deathward/', 1], ['/deathward/', 2]]) {
      const context = await browser.newContext({viewport: {width: 1280, height: 848}});
      const page = await context.newPage();
      const requests = [], runtimeResponses = new Map();
      page.on('pageerror', error => errors.push(error.message));
      page.on('request', request => requests.push(request.url()));
      page.on('requestfailed', request => errors.push(`${request.url()}: ${request.failure()?.errorText}`));
      page.on('console', message => {
        if (/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed|using direct world rendering/i.test(message.text()))
          errors.push(message.text());
      });
      page.on('response', response => {
        const name = new URL(response.url()).pathname.split('/').pop();
        if (name.startsWith('deathward.')) runtimeResponses.set(name, response);
        if (response.status() >= 400) errors.push(`${response.status()}: ${response.url()}`);
      });
      // The nested request deliberately omits the slash; the server supplies it.
      const url = hub ? `${base}/deathward?verify&mute&hub=${hub === 2 ? 'redstone' : 'frontier'}` : `${base}/?verify&mute`;
      await page.goto(url);
      await page.waitForFunction(() => window.Module?.ready, null, {timeout: 60000});
      await page.locator('#start').click({noWaitAfter: true});
      await page.waitForFunction(() => Module.state?.frame > 8, null, {timeout: 60000});
      const state = await page.evaluate(() => Module.state);
      assert.equal(state.hub, hub);
      assert.equal(state.screen, 0);
      assert.equal(state.error, '');
      assert.equal(await page.locator('#problem').textContent(), '');
      assert.equal(new URL(page.url()).pathname, mount);
      for (const name of Object.keys(manifest.files).filter(name => name !== 'index.html')) {
        assert(runtimeResponses.has(name), `Browser must download ${name}`);
        const response = runtimeResponses.get(name);
        assert.equal(response.status(), 200);
        assert.equal(new URL(response.url()).pathname, mount + name);
        if (name.endsWith('.wasm')) assert.match(response.headers()['content-type'], /application\/wasm/);
      }
      for (const request of requests) {
        const url = new URL(request);
        assert.equal(url.origin, base, 'No runtime dependency on another host');
        if (hub) assert(url.pathname === '/deathward' || url.pathname.startsWith(mount),
                        `Request escaped the deployment directory: ${url.pathname}`);
      }
      await page.screenshot({path: path.join(artifacts, hub === 2 ? 'web-upload-redstone.png' : hub ? 'web-upload-subdirectory.png' : 'web-upload-root.png')});
      network.push(...requests);
      assert.deepEqual(errors, []);
      console.log(`PASS packaged ${['Black Creek', 'Frontier', 'Redstone Canyon'][hub]} at ${mount}, relative assets and clean WebGL startup`);
      await context.close();
    }
    const explicitIndex = await fetch(`${base}/deathward/index.html`);
    assert.equal(explicitIndex.status, 200);
    assert.equal(await explicitIndex.text(), fs.readFileSync(path.join(temporary, 'index.html'), 'utf8'));
    console.log('PASS directory redirect preserves query parameters; explicit index.html is available');
  } finally {
    fs.mkdirSync(artifacts, {recursive: true});
    fs.writeFileSync(path.join(artifacts, 'web-upload-errors.log'), errors.join('\n'));
    fs.writeFileSync(path.join(artifacts, 'web-upload-requests.log'), network.join('\n'));
    if (browser) await browser.close();
    if (server) server.kill();
    fs.rmSync(temporary, {recursive: true, force: true});
  }
})().catch(error => { console.error(error); process.exitCode = 1; });
