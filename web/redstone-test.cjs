// Real browser travel, mission return and independent editing for the third hub.
const {chromium} = require('playwright');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');
const root = path.resolve(__dirname, '..');
(async () => {
  const browser = await chromium.launch({headless: true,
    executablePath: process.env.DEATHWARD_BROWSER || undefined,
    args: ['--no-sandbox', '--enable-gpu', '--use-gl=angle', '--use-angle=gl', '--ignore-gpu-blocklist']});
  const page = await browser.newPage({viewport: {width: 1280, height: 848}});
  const errors = [];
  page.on('pageerror', e => errors.push(String(e)));
  page.on('console', m => {if (/ERROR:|INVALID_OPERATION|shader failed/i.test(m.text())) errors.push(m.text());});
  const wait = (fn, arg) => page.waitForFunction(fn, arg, {timeout: 60000});
  const state = () => page.evaluate(() => Module.state);
  const key = async code => {
    let frame = (await state()).frame;
    await page.keyboard.down(code);
    await wait(start => Module.state.frame >= start + 2, frame);
    frame = (await state()).frame;
    await page.keyboard.up(code);
    await wait(start => Module.state.frame >= start + 2, frame);
  };
  const click = async (x, y) => {
    const box = await page.locator('#canvas').boundingBox();
    await page.mouse.click(box.x + x * box.width / 1280, box.y + y * box.height / 800, {delay: 130});
  };
  const start = async () => {
    await page.goto((process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/') + '?verify&hub=redstone');
    await wait(() => window.Module?.ready);
    assert.equal(await page.locator('#start').textContent(), 'Enter Redstone Canyon');
    await page.locator('#start').click({noWaitAfter: true});
    await wait(() => Module.state?.frame > 8);
    assert.equal((await state()).hub, 2);
    assert.equal((await state()).error, '');
  };
  try {
    await start();
    assert.equal(await page.evaluate(() => Module.motion.vehicles), 4);
    await wait(() => Module.particles.steam > 0 && Module.characters.count === 15);
    assert.equal(await page.evaluate(() => Module.motion.trainDistance), 0);
    const otherScenes = await page.evaluate(() => ['town', 'frontier'].map(hub =>
      FS.readFile('/persist/' + hub + '/town.scene', {encoding: 'utf8'})));
    await key('Escape');
    const frozen = await page.evaluate(() => Module.motion.trainDistance);
    await page.waitForTimeout(250);
    assert.equal(await page.evaluate(() => Module.motion.trainDistance), frozen);
    await key('Escape');
    await click(1050, 680); await wait(() => Module.state.hub === 1);
    await click(1050, 680); await wait(() => Module.state.hub === 2);
    await click(1050, 734); await wait(() => Module.state.hub === 0);
    await click(1050, 680); await wait(() => Module.state.hub === 2);
    await page.screenshot({path: path.join(root, 'artifacts/web-redstone.png')});
    console.log('PASS canyon URL, steam, train pause and direct travel between all three hubs');
    await key('Enter'); await wait(() => Module.state.menu);
    await key('Enter'); await wait(() => Module.state.screen === 1);
    await key('Escape'); await wait(() => Module.state.paused);
    await key('t'); await wait(() => Module.state.screen === 2);
    await key('Enter'); await wait(() => Module.state.screen === 0 && Module.state.hub === 2);
    console.log('PASS canyon mission-board approach, launch, retreat and return to Redstone');
    await key('F4'); await wait(() => Module.state.editor);
    const editorClick = (x, y) => click(x * 1280 / 1440, y * 800 / 900);
    await editorClick(110, 270); // First placed object, in the original catalog.
    await editorClick(1260, 499); // Cast shadows: OFF.
    await page.screenshot({path: path.join(root, 'artifacts/web-object-shadows-off.png')});
    await page.keyboard.down('Control'); await key('s'); await page.keyboard.up('Control');
    await wait(() => Module.state.editorSaved && !Module.saving);
    let saved = await page.evaluate(() => FS.readFile('/persist/redstone/town.scene', {encoding: 'utf8'}));
    const shadowId = saved.split('\n').find(line => line.startsWith('instance ')).split(' ')[2];
    assert(saved.startsWith('DEATHWARD_TOWN 6 1\n'));
    assert.deepEqual(saved.split('\n').filter(line => line.startsWith('shadow ')), [`shadow ${shadowId} 0`]);
    const rail = saved.split('\n').find(line => line.startsWith('path redstone-rail ')).split(' ');
    assert.equal(Number(rail[2]), 0);
    assert(Math.abs(Number(rail[3]) - .8) < .0001);
    assert.equal(Number(rail[4]), 0);
    assert.equal(await page.evaluate(() => FS.readFile('/persist/redstone/town.nav')[7]), '3'.charCodeAt(0));
    assert.deepEqual(await page.evaluate(() => ['town', 'frontier'].map(hub =>
      FS.readFile('/persist/' + hub + '/town.scene', {encoding: 'utf8'}))), otherScenes);
    await key('Escape'); await wait(() => !Module.state.editor);
    await start();
    assert.equal(await page.evaluate(() => FS.readFile('/persist/redstone/town.scene', {encoding: 'utf8'})), saved);
    assert.equal(await page.evaluate(() => Module.motion.vehicles), 4);
    await key('F4'); await wait(() => Module.state.editor);
    await editorClick(110, 270);
    await editorClick(1260, 499); // Reloaded OFF setting switches back ON.
    await page.keyboard.down('Control'); await key('s'); await page.keyboard.up('Control');
    await wait(() => Module.state.editorSaved && !Module.saving);
    saved = await page.evaluate(() => FS.readFile('/persist/redstone/town.scene', {encoding: 'utf8'}));
    assert(!saved.split('\n').some(line => line.startsWith('shadow ')));
    await key('Escape'); await wait(() => !Module.state.editor);
    console.log('PASS per-object shadow toggle, browser save/reload and restoring shadows');
    // Simulate an edited save from the smaller, original mesh library. Loading
    // the new GLB must append catalog entries without replacing authored data.
    const legacy = await page.evaluate(() => {
      const file = '/persist/redstone/town.scene';
      let assets = 0;
      const text = FS.readFile(file, {encoding:'utf8'}).split('\n').filter(line => {
        if (line.startsWith('asset ')) return assets++ < 192;
        if (line.startsWith('instance ')) return Number(line.split(' ')[1]) < 192;
        return true;
      }).join('\n');
      FS.writeFile(file, text);
      const labelPath = '/persist/redstone/town.labels';
      const labels = FS.readFile(labelPath, {encoding:'utf8'}).split('\n').slice(0,192);
      labels[0] = labels[0].split(' ')[0] + ' My_custom_ground';
      FS.writeFile(labelPath, labels.join('\n') + '\n');
      Module.flushSaves();
      return text;
    });
    await wait(() => !Module.saving);
    await start();
    const upgraded = await page.evaluate(() => FS.readFile('/persist/redstone/town.scene', {encoding:'utf8'}));
    const shippedAssets = fs.readFileSync(path.join(root, 'assets/redstone/town.scene'), 'utf8')
      .split('\n').filter(line => line.startsWith('asset '));
    const upgradedAssets = upgraded.split('\n').filter(line => line.startsWith('asset '));
    assert.equal(upgradedAssets.length, shippedAssets.length);
    for (let n = 0; n < shippedAssets.length; ++n) {
      const before = shippedAssets[n].split(' '), after = upgradedAssets[n].split(' ');
      assert.deepEqual(after.slice(0,5), before.slice(0,5));
      // Editor saves serialize float bounds, while the composer writes doubles.
      for (let axis = 5; axis < before.length; ++axis)
        assert(Math.abs(Number(after[axis]) - Number(before[axis])) < .0001);
    }
    const authored = text => text.split('\n').filter(line => line && !line.startsWith('asset ')).join('\n');
    assert.equal(authored(upgraded), authored(legacy));
    assert((await page.evaluate(() => FS.readFile('/persist/redstone/town.labels', {encoding:'utf8'}))).includes('My_custom_ground'));
    console.log('PASS old edited maps keep placements, routes and custom labels with the expanded mesh library');
    // An existing edited road-era save receives the missing soil without
    // losing its placements. Startup rebakes its own navigation afterward.
    const repairId = 'terrain-badlands-ground:1829520066912572';
    const custom = await page.evaluate(({saved, repairId}) => {
      const rows = saved.split('\n').filter(line => line.split(' ')[2] !== repairId);
      const prop = rows.findIndex(line => line.split(' ')[2]?.startsWith('story-arrival-trunk-a:'));
      const fields = rows[prop].split(' ');
      fields[6] = String(Number(fields[6]) + .25);
      rows[prop] = fields.join(' ');
      const text = rows.join('\n');
      FS.writeFile('/persist/redstone/town.scene', text);
      FS.unlink('/persist/redstone/.badlands-ground-v1');
      Module.flushSaves();
      return {text, prop: rows[prop]};
    }, {saved, repairId});
    await wait(() => !Module.saving);
    await start();
    const repaired = await page.evaluate(() => FS.readFile('/persist/redstone/town.scene', {encoding:'utf8'}));
    assert.equal(repaired.split('\n').filter(line => line.split(' ')[2] === repairId).length, 1);
    assert(repaired.includes(custom.prop));
    assert.equal(repaired.split('\n').filter(line => line.split(' ')[2] !== repairId).join('\n'), custom.text);
    assert.equal(await page.evaluate(() => FS.readFile('/persist/redstone/town.nav')[7]), '3'.charCodeAt(0));
    console.log('PASS edited road-era save receives solid Badlands ground, keeps custom props and rebuilds navigation');
    assert.deepEqual(errors, []);
    console.log('PASS independent canyon editor save, navigation rebuild, reload and clean WebGL rendering');
  } finally {
    fs.writeFileSync(path.join(root, 'artifacts/redstone-browser-errors.log'), errors.join('\n'));
    await page.screenshot({path: path.join(root, 'artifacts/web-redstone-last.png')}).catch(() => {});
    await browser.close();
  }
})().catch(e => {console.error(e); process.exitCode = 1;});
