const {chromium} = require('playwright');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const path = require('node:path');
const root = path.resolve(__dirname, '..');
const artifacts = path.join(root, 'artifacts');
fs.mkdirSync(artifacts, {recursive: true});
const base = process.env.DEATHWARD_WEB_URL || 'http://127.0.0.1:8080/';
const messages = [], failures = [];
const options = {
  headless: process.env.DEATHWARD_HEADFUL !== '1',
  args: ['--no-sandbox', '--enable-gpu', '--use-gl=angle', '--use-angle=gl', '--ignore-gpu-blocklist'],
};
if (process.env.DEATHWARD_BROWSER) options.executablePath = process.env.DEATHWARD_BROWSER;

(async () => {
  const browser = await chromium.launch(options);
  const context = await browser.newContext({viewport: {width: 1280, height: 848}});
  const page = await context.newPage();
  page.setDefaultTimeout(45000);
  page.on('console', message => {
    const text = message.text();
    if (messages.length < 10000) messages.push(`${message.type()}: ${text}`);
    if (/ERROR:|INVALID_OPERATION|INVALID_ENUM|INVALID_VALUE|shader failed|using direct world rendering/i.test(text))
      failures.push(text);
  });
  page.on('pageerror', error => failures.push(error.stack || error.message));
  const state = () => page.evaluate(() => Module.state);
  const wait = (test, arg) => page.waitForFunction(test, arg, {timeout: 60000});
  const checkGateNavigation = async navPath => {
    const result = await page.evaluate(navPath => {
      const bytes = FS.readFile(navPath);
      const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
      const width = view.getUint32(8, true), minX = view.getFloat32(16, true),
            minZ = view.getFloat32(20, true), cell = view.getFloat32(24, true);
      const height = (x, z) => view.getFloat32(52 + 4 *
        (Math.floor((z - minZ) / cell) * width + Math.floor((x - minX) / cell)), true);
      return {opening: Number.isFinite(height(-34.32, .48)),
        posts: [Number.isFinite(height(-34.32, -3.7)), Number.isFinite(height(-34.32, 4.67))]};
    }, navPath);
    assert.deepEqual(result, {opening: true, posts: [false, false]});
  };
  const key = async code => {
    // Keep transitions across rendered frames, including expensive scene loads.
    let frame = (await state()).frame;
    await page.keyboard.down(code);
    await wait(start => Module.state.frame >= start + 2, frame);
    frame = (await state()).frame;
    await page.keyboard.up(code);
    await wait(start => Module.state.frame >= start + 2, frame);
  };
  const click = async (x, y) => {
    const box = await page.locator('#canvas').boundingBox();
    await page.mouse.click(box.x + x * box.width / 1280, box.y + y * box.height / 800, {delay: 100});
  };
  const start = async (url, beforeStart) => {
    await page.goto(url);
    await wait(() => window.Module && Module.ready);
    if (beforeStart) await beforeStart();
    await page.locator('#start').click({noWaitAfter: true});
    await wait(() => Module.state?.frame > 3 || document.querySelector('#problem').textContent);
    assert.equal(await page.locator('#problem').textContent(), '');
    assert.equal((await state()).error, '');
  };
  try {
    let legacyScene;
    await start(base + '?verify', async () => {
      legacyScene = await page.evaluate(() => {
        FS.mkdirTree('/persist/town');
        FS.mkdirTree('/persist/frontier');
        FS.writeFile('/persist/town/town.labels',
          FS.readFile('/assets/town/town.labels', {encoding: 'utf8'})
            .replace('part_0033 SM_Veh_Train_01_Alt_Smokestack', 'part_0033 SM_Veh_Train_01')
            .replace('part_0047 SM_Building_Single_FrontDoor_01','part_0047 SM_Bld_Single_Front_01'));
        FS.writeFile('/persist/frontier/town.labels',
          FS.readFile('/assets/frontier/town.labels', {encoding: 'utf8'})
            .replace('part_0106 SM_Prop_Campfire_Pot_01', 'part_0106 SM_Prop_Campfire_Small_01'));
        const scene = FS.readFile('/assets/town/town.scene', {encoding: 'utf8'}) + '\n';
        FS.writeFile('/persist/town/town.scene', scene);
        const bytes = FS.readFile('/assets/town/town.nav');
        bytes[7] = '1'.charCodeAt(0); // Simulate an old navigation bake with a blocked gate.
        const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
        const width = view.getUint32(8, true), minX = view.getFloat32(16, true),
              minZ = view.getFloat32(20, true), cell = view.getFloat32(24, true);
        view.setFloat32(52 + 4 * (Math.floor((.48 - minZ) / cell) * width + Math.floor((-34.32 - minX) / cell)), NaN, true);
        FS.writeFile('/persist/town/town.nav', bytes);
        return scene;
      });
    });
    assert.equal(await page.evaluate(() => FS.readFile('/persist/town/town.scene', {encoding: 'utf8'})), legacyScene);
    assert.equal(await page.evaluate(() => FS.readFile('/assets/town/town.scene', {encoding: 'utf8'})),
      fs.readFileSync(path.join(root, 'assets/town/town.scene'), 'utf8'));
    assert.ok(await page.evaluate(() => FS.readFile('/persist/frontier/town.labels', {encoding: 'utf8'})
      .includes('part_0106 SM_Prop_Campfire_Pot_01')));
    assert.equal(await page.evaluate(() => FS.readFile('/persist/town/town.nav')[7]), '3'.charCodeAt(0));
    assert.ok(await page.evaluate(() => FS.readFile('/persist/town/town.labels', {encoding: 'utf8'})
      .includes('part_0047 SM_Building_Single_FrontDoor_01')));
    console.log('PASS old browser navigation upgrades without replacing the saved town scene');
    const animalFiles = await page.evaluate(() => FS.readdir('/assets/animals'));
    const expectedAnimals = JSON.parse(fs.readFileSync(path.join(root, 'assets/animals/animals.source.json')))
      .animals.map(animal => animal.id + '.glb').sort();
    assert.deepEqual(animalFiles.filter(name => name.endsWith('.glb')).sort(), expectedAnimals);
    assert.equal(animalFiles.includes('source'), false);
    console.log(`PASS all ${expectedAnimals.length} converted animal models packaged without source FBXs`);
    assert.equal((await state()).hub, 0);
    await checkGateNavigation('/persist/town/town.nav');
    assert.equal((await state()).audio, 2);
    assert.equal((await state()).zoom, 160);
    assert.equal(await page.evaluate(() => Module.animals.count), 5);
    assert.equal(await page.evaluate(() => Module.characters.count), 1);
    assert.equal(await page.evaluate(() => Module.particles.ready), true);
    assert.equal(await page.evaluate(() => Module.particles.attachments), 12);
    assert.ok(await page.evaluate(() => Module.particles.count > 30));
    assert.ok(await page.evaluate(() => Module.particles.steam > 0));
    assert.ok(await page.evaluate(() => FS.readFile('/persist/town/town.labels', {encoding:'utf8'})
      .includes('part_0033 SM_Veh_Train_01_Alt_Smokestack')));
    const particleBefore = await page.evaluate(() => Module.particles.time);
    await wait(before => Module.particles.time > before + .2, particleBefore);
    const cowgirlBefore = await page.evaluate(() => Module.characters);
    await wait(before => Math.hypot(Module.characters.x - before.x, Module.characters.z - before.z) > .3, cowgirlBefore);
    const animalBefore = await page.evaluate(() => Module.animals);
    await wait(before => Module.animals.phase > before.phase + 2 &&
      Math.hypot(Module.animals.x - before.x, Module.animals.z - before.z) > .1, animalBefore);
    assert.equal(await page.evaluate(() => Module.motion.count), 64);
    assert.equal(await page.evaluate(() => Module.motion.vehicles), 8);
    await wait(() => Module.motion.trainDistance > .2);
    const movingProp = await page.evaluate(() => Module.motion);
    await wait(before => Math.hypot(Module.motion.x - before.x, Module.motion.z - before.z) > .2, movingProp);
    assert.notEqual(await page.evaluate(() => Module.motion.rotation), movingProp.rotation);
    await page.evaluate(() => {
      Module.audioProbe = {frames: 0, peak: 0};
      const device = miniaudio.devices.find(Boolean);
      const original = device.scriptNode.onaudioprocess;
      device.scriptNode.onaudioprocess = event => {
        original(event);
        const samples = event.outputBuffer.getChannelData(0);
        for (const sample of samples) Module.audioProbe.peak = Math.max(Module.audioProbe.peak, Math.abs(sample));
        Module.audioProbe.frames += samples.length;
      };
    });
    await wait(() => Module.audioProbe.frames > 4096 && Module.audioProbe.peak > .0001);
    await page.screenshot({path: path.join(artifacts, 'web-town.png')});
    const before = await state();
    await page.keyboard.down('w'); await page.waitForTimeout(700); await page.keyboard.up('w');
    await wait(s => Math.hypot(Module.state.x - s.x, Module.state.z - s.z) > .5, before);
    await page.mouse.move(640, 450);
    await page.mouse.wheel(0, -200);
    await wait(() => Module.state.zoom > 160);
    await page.setViewportSize({width: 1100, height: 735});
    await wait(() => Module.canvas.width === Math.round(Module.canvas.clientWidth) &&
                         Module.canvas.height === Math.round(Module.canvas.clientHeight));
    await page.screenshot({path: path.join(artifacts, 'web-resized.png')});
    await page.setViewportSize({width: 1280, height: 848});
    // Dispatch the browser focus event directly so this also runs on headless
    // hosts where tab visibility is intentionally overridden by automation.
    await page.evaluate(() => window.dispatchEvent(new Event('blur')));
    await wait(() => Module.state.paused);
    const frozenMotion = await page.evaluate(() => Module.motion);
    const frozenAnimals = await page.evaluate(() => Module.animals);
    const frozenCharacters = await page.evaluate(() => Module.characters);
    const frozenParticles = await page.evaluate(() => Module.particles);
    await page.waitForTimeout(250);
    assert.deepEqual(await page.evaluate(() => Module.motion), frozenMotion);
    assert.deepEqual(await page.evaluate(() => Module.animals), frozenAnimals);
    assert.deepEqual(await page.evaluate(() => Module.characters), frozenCharacters);
    assert.deepEqual(await page.evaluate(() => Module.particles), frozenParticles);
    await key('Escape');
    await wait(() => !Module.state.paused);
    console.log('PASS town rendering, WebAudio initialization, movement and wheel zoom');
    console.log('PASS two trains, independent tumbleweeds and exact pause behavior');
    console.log('PASS five animated animals, roaming and exact pause behavior');
    console.log('PASS imported fireplace particles, prewarm, animation and exact pause behavior');
    await key('Escape');
    assert.equal((await state()).paused, true);
    await click(230, 494);
    await wait(() => Math.abs(Module.state.music - .3) < .001 && !Module.saving);
    await page.screenshot({path: path.join(artifacts, 'web-audio-controls.png')});
    await key('Escape');
    await click(1050, 734);
    await wait(() => Module.state.hub === 1 && Module.state.frame > 10);
    assert.equal(await page.evaluate(() => Module.motion.count), 0);
    assert.equal(await page.evaluate(() => Module.animals.count), 0);
    assert.equal(await page.evaluate(() => Module.characters.count), 0);
    assert.ok(await page.evaluate(() => Module.particles.ready && Module.particles.attachments > 0));
    assert.equal(await page.evaluate(() => Module.particles.attachments), 22);
    const frontierFireTime = await page.evaluate(() => Module.particles.time);
    await wait(before => Module.particles.time > before + .2, frontierFireTime);
    await page.waitForTimeout(1200);
    await page.screenshot({path: path.join(artifacts, 'web-frontier.png')});
    console.log('PASS music controls and direct Frontier travel');
    await key('Enter');
    await wait(() => Module.state.menu);
    for (let i = 0; i < 12; ++i) await key('Backspace');
    await page.keyboard.type('1866', {delay: 100});
    await key('Enter');
    await wait(() => Module.state.screen === 1 && Module.state.room === 0);
    assert.equal((await state()).theme, 1);
    await key('F2'); // Invulnerability while checking pickups and combat.
    await page.mouse.move(640, 450);
    await page.mouse.wheel(0, 800);
    await wait(() => Module.state.zoom < 120 && Module.state.coinValue > 0);
    await page.waitForTimeout(700);
    const coin = await state();
    await page.screenshot({path: path.join(artifacts, 'web-money-before.png')});
    await click(coin.coinX, coin.coinY);
    await wait(value => Module.state.money >= value, coin.money + coin.coinValue);
    const collectedMoney = (await state()).money;
    assert.equal((await state()).shots, 0);
    await wait(() => !Module.saving);
    await page.screenshot({path: path.join(artifacts, 'web-money.png')});
    console.log('PASS seeded ground money, click pickup and immediate checkpoint');
    await page.mouse.move(650, 440);
    await key('b');
    await wait(() => Module.state.dynamite === 2 && Module.state.litDynamite === 1);
    assert.equal((await state()).dynamiteThrowMode, false);
    assert.equal((await state()).placedDynamite, 1);
    assert.equal((await state()).shots, 0);
    await page.screenshot({path: path.join(artifacts, 'web-dynamite-lit.png')});
    const beforeKick = await state();
    await key('e');
    assert.equal((await state()).placedDynamite, 1); // Interaction is no longer a kick.
    // Step back toward the route we just used to collect the coin, then walk into the bundle.
    const routes = [
      {out: 'w', back: 's', x: -1, z: -1}, {out: 's', back: 'w', x: 1, z: 1},
      {out: 'a', back: 'd', x: -1, z: 1}, {out: 'd', back: 'a', x: 1, z: -1},
    ];
    routes.sort((a, b) => (b.x - a.x) * (coin.x - beforeKick.x) + (b.z - a.z) * (coin.z - beforeKick.z));
    const route = routes[0];
    await page.keyboard.down(route.out);
    await wait(start => Math.hypot(Module.state.x - start.x, Module.state.z - start.z) > .95, beforeKick);
    await page.keyboard.up(route.out);
    assert.equal((await state()).placedDynamite, 1);
    await page.keyboard.down(route.back);
    await wait(() => Module.state.litDynamite === 1 && Module.state.placedDynamite === 0);
    await page.keyboard.up(route.back);
    assert.equal((await state()).dynamite, 2);
    assert.equal((await state()).shots, 0);
    await page.screenshot({path: path.join(artifacts, 'web-dynamite-kicked.png')});
    await wait(() => Module.state.explosions === 1 && Module.state.litDynamite === 0);
    await wait(() => Module.combatParticles.explosion > 0);
    await page.screenshot({path: path.join(artifacts, 'web-dynamite-blast.png')});
    await click(160, 640);
    await wait(() => Module.state.dynamite === 1 && Module.state.placedDynamite === 1);
    assert.equal((await state()).dynamiteArmed, false);
    await page.screenshot({path: path.join(artifacts, 'web-dynamite-placed.png')});
    // A freshly placed charge remains stationary without movement or contact.
    await key('e');
    assert.equal((await state()).placedDynamite, 1);
    assert.equal((await state()).dynamite, 1);
    assert.equal((await state()).shots, 0);
    await wait(() => Module.state.explosions === 2 && Module.state.litDynamite === 0);
    await click(160, 608);
    await wait(() => Module.state.dynamiteThrowMode);
    await click(160, 640);
    await wait(() => Module.state.dynamiteArmed);
    await page.mouse.move(680, 400);
    await page.screenshot({path: path.join(artifacts, 'web-dynamite-preview.png')});
    await key('Escape');
    await wait(() => !Module.state.dynamiteArmed && !Module.state.paused);
    assert.equal((await state()).dynamite, 1);
    await click(160, 640);
    await wait(() => Module.state.dynamiteArmed);
    await click(680, 400);
    await wait(() => Module.state.dynamite === 0 && Module.state.litDynamite === 1);
    assert.equal((await state()).shots, 0);
    console.log('PASS dynamite ground placement, automatic contact kicks, throws, fuse and targeting cancellation');
    while ((await state()).room !== (await state()).shopRoom) await key('F12');
    assert.equal((await state()).enemies, 0);
    await page.waitForTimeout(700);
    const merchant = await state();
    await click(merchant.shopX, merchant.shopY);
    await wait(() => Module.state.shopOpen);
    const shopper = await state();
    await page.keyboard.down('w'); await page.waitForTimeout(300); await page.keyboard.up('w');
    await click(630, 535); // The wallet is too small for this power.
    await key('Digit2');
    const unavailable = await state();
    assert.equal(unavailable.money, shopper.money);
    assert.equal(unavailable.spent, 0);
    assert.equal(unavailable.shots, 0);
    assert.equal(unavailable.x, shopper.x);
    assert.equal(unavailable.z, shopper.z);
    await page.screenshot({path: path.join(artifacts, 'web-shop.png')});
    await click(925, 610);
    await wait(() => !Module.state.shopOpen);
    await key('e');
    await wait(() => Module.state.shopOpen);
    await key('Escape');
    await wait(() => !Module.state.shopOpen && !Module.state.paused);
    console.log('PASS peaceful shopkeeper, mouse approach, modal controls and unaffordable purchases');
    while ((await state()).room !== 1) await key('F12');
    await wait(() => Module.state.room === 1);
    await page.mouse.move(650, 445);
    await page.mouse.down({button: 'right'});
    await wait(() => Module.combatParticles.ready && Module.combatParticles.muzzle > 0);
    await page.waitForTimeout(750);
    await page.mouse.up({button: 'right'});
    await wait(() => Module.state.shots > 0);
    await page.mouse.move(600, 400);
    await page.mouse.down({button: 'middle'});
    await page.mouse.move(740, 450, {steps: 12});
    await page.mouse.up({button: 'middle'});
    assert.ok(await page.evaluate(() => Module.combatParticles.dust > 0));
    await page.screenshot({path: path.join(artifacts, 'web-canyon.png')});
    await key('F7');
    await wait(() => Module.state.room === 14 && Module.state.enemies > 0);
    await key('F8');
    await wait(() => Module.state.screen === 2 && Module.state.history === 1 && !Module.saving);
    console.log('PASS canyon launch, firing, camera orbit, final encounter and victory');
    await start(base + '?verify&theme=mine');
    assert.equal(await page.evaluate(() => Module.animals.count), 5);
    assert.equal((await state()).history, 1);
    assert((await state()).money >= collectedMoney, 'collected money survives resolution and browser reload');
    assert(Math.abs((await state()).music - .3) < .001);
    console.log('PASS campaign and music volume survive a browser reload');
    await key('F4');
    await wait(() => Module.state.editor);
    const editorAnimals = await page.evaluate(() => Module.animals);
    const editorCharacters = await page.evaluate(() => Module.characters);
    const originalScene = await page.evaluate(() => Module.FS.readFile('/persist/town/town.scene', {encoding: 'utf8'}));
    const editorClick = (x, y) => click(x * 1280 / 1440, y * 800 / 900);
    await editorClick(110, 199);
    await page.keyboard.type('Barrel', {delay: 80});
    await editorClick(110, 270);
    await editorClick(1270, 285); // Set this prop's height through the position inspector.
    await page.keyboard.type('2', {delay: 80});
    await key('Enter');
    await editorClick(65, 157); // People tab selects the demo cowgirl.
    await wait(() => Module.characterEditor.selected === 0 && Module.characterEditor.stops === 3);
    await editorClick(130, 814); // Add another character, then undo the placement.
    await wait(() => Module.characterEditor.count === 2);
    await page.keyboard.down('Control'); await key('z'); await page.keyboard.up('Control');
    await wait(() => Module.characterEditor.count === 1);
    await editorClick(1190, 583); // Walking speed.
    await page.keyboard.type('1.1', {delay: 80});
    await key('Enter');
    await editorClick(1180, 767); // Focus the selected character.
    await editorClick(1180, 729); // Play route preview.
    await wait(() => Module.characterEditor.time > 3);
    assert.ok(await page.evaluate(() => Module.particles.time > 2.9));
    await editorClick(1180, 729); // Pause preview.
    const pausedCharacterEditor = await page.evaluate(() => Module.characterEditor);
    const pausedEditorParticles = await page.evaluate(() => Module.particles);
    await page.waitForTimeout(200);
    assert.deepEqual(await page.evaluate(() => Module.characterEditor), pausedCharacterEditor);
    assert.deepEqual(await page.evaluate(() => Module.particles), pausedEditorParticles);
    assert.deepEqual(await page.evaluate(() => Module.characters), editorCharacters);
    await page.screenshot({path: path.join(artifacts, 'web-cowgirl-editor.png')});
    await editorClick(196, 157); // Animals tab.
    await wait(() => Module.animalEditor.count === 5 && Module.animalEditor.selected === 0);
    await editorClick(196, 245); // Species catalog.
    await editorClick(110, 199);
    await page.keyboard.type('hen', {delay: 80});
    await editorClick(110, 303); // Select the first matching species.
    await editorClick(130, 814); // Add animal on clear ground near the view.
    await wait(() => Module.animalEditor.count === 6 && Module.animalEditor.species === 1);
    await key('Escape'); // Finish ground placement.
    await page.keyboard.down('Control'); await key('z'); await page.keyboard.up('Control');
    await wait(() => Module.animalEditor.count === 5);
    await page.keyboard.down('Control'); await key('y'); await page.keyboard.up('Control');
    await wait(() => Module.animalEditor.count === 6 && Module.animalEditor.selected === 5);
    await editorClick(1320, 345); // Roaming radius: keep this hen at its authored home.
    await page.keyboard.type('0', {delay: 80});
    await key('Enter');
    await editorClick(1320, 415); // Independent seed.
    await page.keyboard.type('4294967295', {delay: 40});
    await key('Enter');
    await wait(() => Module.animalEditor.radius === 0 && Module.animalEditor.seed === 4294967295);
    await editorClick(1180, 710); // Focus.
    const beforeAnimalPreview = await page.evaluate(() => Module.animalEditor);
    await editorClick(1180, 603); // Play preview.
    await wait(before => Module.animalEditor.phase > before.phase + 3, beforeAnimalPreview);
    await editorClick(1180, 603); // Pause preview.
    const pausedAnimalEditor = await page.evaluate(() => Module.animalEditor);
    assert.equal(pausedAnimalEditor.x, beforeAnimalPreview.x);
    assert.equal(pausedAnimalEditor.z, beforeAnimalPreview.z);
    await page.waitForTimeout(200);
    assert.deepEqual(await page.evaluate(() => Module.animalEditor), pausedAnimalEditor);
    assert.deepEqual(await page.evaluate(() => Module.animals), editorAnimals);
    await page.screenshot({path: path.join(artifacts, 'web-animal-editor.png')});
    await page.keyboard.down('Control'); await key('s'); await page.keyboard.up('Control');
    await wait(() => Module.state.editorSaved && !Module.saving);
    const savedScene = await page.evaluate(() => Module.FS.readFile('/persist/town/town.scene', {encoding: 'utf8'}));
    await checkGateNavigation('/persist/town/town.nav');
    console.log('PASS town gate opening and solid posts survive browser editor navigation rebake');
    assert(savedScene !== originalScene, 'editor input changes and saves the selected prop');
    assert(savedScene.includes('character cowgirl-street-walk cowgirl'), 'authored cowgirl route persists in town.scene');
    assert(savedScene.startsWith('DEATHWARD_TOWN 5\n'));
    const savedAnimals = savedScene.split('\n').filter(row => row.startsWith('animal '));
    assert.equal(savedAnimals.length, 6);
    assert(savedAnimals.some(row => / hen .* 0 4294967295$/.test(row)), 'animal settings persist in the scene');
    assert.deepEqual(await page.evaluate(() => Module.animals), editorAnimals);
    await page.screenshot({path: path.join(artifacts, 'web-editor.png')});
    await key('Escape');
    await wait(() => !Module.state.editor);
    await wait(() => Module.animals.count === 6);
    console.log('PASS animal catalog search, placement, undo/redo, seed, idle preview, pause, save and game reload');
    console.log('PASS browser town editor opens and returns to the hub');
    console.log('PASS cowgirl roaming, pause, hub population, editor placement, undo, route preview and saving');
    await key('Enter');
    await wait(() => Module.state.menu);
    await key('Enter');
    await wait(() => Module.state.screen === 1 && Module.state.theme === 0);
    await key('F2');
    await key('F12');
    await page.screenshot({path: path.join(artifacts, 'web-mine.png')});
    await wait(() => !Module.saving);
    await start(base + '?verify');
    assert.equal((await state()).screen, 2);
    assert.equal((await state()).history, 2);
    assert.equal(await page.evaluate(() => Module.FS.readFile('/persist/town/town.scene', {encoding: 'utf8'})), savedScene);
    console.log('PASS mine mission and interrupted-run recovery after reload');
    console.log('PASS editor scene changes persist after reloading');
    assert.deepEqual(failures, []);
    console.log('PASS no JavaScript exceptions, shader failures or WebGL errors');
  } finally {
    console.log('Last state:', await state().catch(() => null));
    await page.screenshot({path: path.join(artifacts, 'web-last-frame.png')}).catch(() => {});
    fs.writeFileSync(path.join(artifacts, 'web-browser-console.log'), messages.join('\n'));
    fs.writeFileSync(path.join(artifacts, 'web-browser-errors.log'), failures.join('\n'));
    await browser.close();
  }
})().catch(error => { console.error(error); process.exitCode = 1; });
