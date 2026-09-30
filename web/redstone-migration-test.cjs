// Run the actual browser migration against isolated files, including edited maps.
const fs = require('node:fs');
const path = require('node:path');
const vm = require('node:vm');
const assert = require('node:assert/strict');
const root = path.resolve(__dirname, '..');
const header = fs.readFileSync(path.join(root, 'src/platform/Browser.hpp'), 'utf8');
const code = header.split('inline void prepareBrowserFiles()')[1].match(/EM_ASM\(\{([\s\S]*?)\n    \}\);/)[1];
const shipped = new Map();
for (const hub of ['town', 'frontier', 'redstone'])
  for (const name of ['town.scene', 'town.nav', 'town.labels'])
    shipped.set('/assets/' + hub + '/' + name, fs.readFileSync(path.join(root, 'assets', hub, name)));
const scenePath = '/persist/redstone/town.scene';
const navPath = '/persist/redstone/town.nav';
const markerPath = '/persist/redstone/.badlands-ground-v1';
const scene = shipped.get('/assets/redstone/town.scene').toString();
const nav = shipped.get('/assets/redstone/town.nav');
const repairId = 'terrain-badlands-ground:1829520066912572';
const repair = scene.split('\n').find(line => line.split(' ')[2] === repairId);
assert(repair, 'The shipped scene contains the ground repair');
const removeRepair = text => text.split('\n').filter(line => line.split(' ')[2] !== repairId).join('\n');
const move = (text, id) => text.split('\n').map(line => {
  const fields = line.split(' ');
  if (fields[0] === 'instance' && fields[2] === id) fields[6] = String(Number(fields[6]) + .25);
  return fields.join(' ');
}).join('\n');
function run(files) {
  const FS = {
    mkdirTree() {},
    analyzePath: file => ({exists: files.has(file)}),
    readFile: (file, options) => {
      assert(files.has(file), file);
      return options?.encoding ? files.get(file).toString() : new Uint8Array(files.get(file));
    },
    writeFile: (file, value) => files.set(file, Buffer.from(value))
  };
  vm.runInNewContext(code, {FS});
}
function check(name, saved, navigation, expected, expectedNav, alreadyMigrated = false) {
  const files = new Map(shipped);
  if (saved !== null) files.set(scenePath, Buffer.from(saved));
  if (navigation) files.set(navPath, navigation);
  if (alreadyMigrated) files.set(markerPath, Buffer.from('1'));
  run(files);
  assert.equal(files.get(scenePath).toString(), expected, name);
  assert.deepEqual(files.get(navPath), expectedNav, name);
  const once = new Map(files);
  run(files);
  assert.deepEqual(files, once, name + ' is idempotent');
  console.log('PASS', name);
}
check('fresh scene includes solid ground', null, null, scene, nav);
check('current scene is unchanged', scene, nav, scene, nav);
// Pick the actual instance ID rather than depending on a source FBX child ID.
const propId = scene.split('\n').map(line => line.split(' ')[2]).find(id => id?.startsWith('story-arrival-trunk-a:'));
assert(propId);
const custom = move(removeRepair(scene), propId);
assert.notEqual(custom, removeRepair(scene));
const customNav = Buffer.from(nav);
customNav.writeFloatLE(customNav.readFloatLE(28) + .2, 28); // Preserve the authored arrival marker.
const needsBake = Buffer.from(customNav);
needsBake[7] = '2'.charCodeAt(0);
check('edited scenery receives only the fill and requests a navigation rebuild', custom, customNav,
      custom.trimEnd() + '\n' + repair + '\n', needsBake);
const changedTerrain = move(custom, 'town-1959252270:1194512102497620');
check('edited terrain is preserved', changedTerrain, customNav, changedTerrain, customNav);
check('later deliberate deletion stays deleted', custom, customNav, custom, customNav, true);
const noRoad = custom.split('\n').filter(line => line.split(' ')[2] !== 'redstone-road-east').join('\n');
check('older layouts without the new road are preserved', noRoad, customNav, noRoad, customNav);
