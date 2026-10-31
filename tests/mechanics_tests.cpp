#include "items/Items.hpp"
#include "items/ItemPools.hpp"
#include <filesystem>
#include <fstream>
#include <chrono>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const std::string &message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.001f;}
struct Pack {
    std::filesystem::path root=std::filesystem::temp_directory_path()/
        ("deathward-mechanics-contracts-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(root);
        for(const auto &p:std::filesystem::directory_iterator(defaultMechanics()->directory()))
            if(p.path().extension()==".mechanics")std::filesystem::copy_file(p.path(),root/p.path().filename());}
    ~Pack(){std::filesystem::remove_all(root);}
    void extra(const std::string &text){std::ofstream(root/"z-test.mechanics")<<"DEATHWARD_MECHANICS 1\n"<<text;}
    void clearEncounterPools(){
        // Packages can append pools outside encounters.mechanics. A fixture
        // replacing the whole roster must clear all authored ordinary entries.
        for(const auto &file:std::filesystem::directory_iterator(root))if(file.path().extension()==".mechanics") {
            std::ifstream in(file.path());std::string line,data;
            while(std::getline(in,line)){std::istringstream row(line);std::string command;row>>command;if(command!="encounter")data+=line+'\n';}
            in.close();std::ofstream(file.path())<<data;
        }
    }
};
void rejects(Pack &pack,const std::string &text,const std::string &expected) {
    pack.extra(text);bool rejected=false;
    try{MechanicsLibrary::load(pack.root);}catch(const std::exception &e){rejected=std::string(e.what()).find(expected)!=std::string::npos;}
    check(rejected,"invalid definition not diagnosed: "+expected);
}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation run(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Classic,std::move(content));
    run.arena=Arena{};run.arena.bounds={{-25,-1,-25},{25,5,25}};
    for(auto &r:run.arena.rooms){r.bounds=run.arena.bounds;r.center={0,.85f,0};}
    run.rooms.resize(run.arena.rooms.size());for(auto &r:run.rooms){r.residents.clear();r.cleared=false;}
    run.enemies.clear();run.player.position={0,.85f,8};run.debugScenario=true;run.godMode=true;run.roomClear=false;
    return run;
}
void identities() {
    check(monsterId(912,100)!=monsterId(913),"high variant IDs must not collide");
    check(parseMonsterId("912.100.7")==monsterId(912,100,7),"full tuple text roundtrip");
    const auto item=parseItemKey("isaac:collectible:118"),trinket=parseItemKey("isaac:trinket:118");
    check(item!=trinket&&parseItemKey(itemKeyText(item))==item,"item kinds have independent namespaces");
    for(auto bad:{"10.1.0.2","10.-1","10.1x","10.","999999999999"}) {
        bool rejected=false;try{parseMonsterId(bad);}catch(...){rejected=true;}check(rejected,"invalid tuple accepted");
    }
    for(auto bad:{"bad namespace:collectible:2","dw:unknown:2","dw:pill:-1","dw:pill:2x","dw:pill:4294967296"}) {
        bool rejected=false;try{parseItemKey(bad);}catch(...){rejected=true;}check(rejected,"invalid item key accepted");
    }
}
void validation() {
    Pack p;
    const auto before=defaultMechanics()->fingerprint();
    rejects(p,"item dw:collectible:0 \"duplicate\" \"COMMON\" \"bad\"\nend\n","z-test.mechanics:2:");
    rejects(p,"rule bad 0 dw:collectible:0 1 always\nmodify unknown set 1 0 once\nend\n","Unknown build stat");
    rejects(p,"rule bad 0 dw:collectible:0 1 always\nmodify damage multiply nan 0 once\nend\n","finite number");
    rejects(p,"rule bad 0 missing:collectible:8 1 always\nmodify damage set 1 0 once\nend\n","Unknown rule owner");
    rejects(p,"item extra:collectible:1 \"x\" \"COMMON\" \"x\"\nhook typo once\nend\n","Unknown native item hook");
    rejects(p,"behavior broken start 24\nstate start ready still 0 1\ntransition absent always 0\nendstate\nend\n","Unknown transition target");
    rejects(p,"rule bad 0 dw:collectible:0 1 always\nmodify damage set 1 0 once\n","incomplete definition");
    rejects(p,"pool shop missing:collectible:2 1\n","Unknown item in pool");
    rejects(p,"encounter 0 3 any basic 9000.0.0 1 1 0\n","Unknown encounter monster");
    rejects(p,"encounter 0 3 any specialist 68.10.0 1 3 1\n","component/hazard");
    rejects(p,"encounter 0 3 any basic 10.1.0 1 1 0\n","Duplicate encounter monster");
    rejects(p,"encounter 0 4 any basic 10.1.0 1 1 0\n","Integer outside allowed range");
    rejects(p,"encounter 0 3 any basic 10.1.0 1 0 0\n","Integer outside allowed range");
    rejects(p,"floor_variant 0 standard 1\n","Duplicate floor variant");
    rejects(p,"floor_variant 1 lava 1\n","Unknown value");
    rejects(p,"boss_pool 1 68.0.0 normal 1\n","Duplicate boss pool entry");
    rejects(p,"boss_native 1 5\n","Duplicate native boss weight");
    rejects(p,"boss_pool 0 68.10.0 normal 1\n","unsupported controller");
    rejects(p,"boss_pool 0 68.0.0 crimson 1\n","Unknown value");
    rejects(p,"boss_pool 0 68.0.0 green 1\n","incompatible with controller");
    rejects(p,"boss_pool 0 68.1.0 cyan 1\n","incompatible with controller");
    rejects(p,"boss_pool 1 19.2.0 normal 1 standard\n","Duplicate boss pool entry");
    rejects(p,"boss_pool 1 19.2.0 normal 1 lava\n","Unknown value");
    rejects(p,"boss_pool 0 19.2.0 cyan 1\n","incompatible with controller");
    rejects(p,"boss_chain 19.2.0 2 6 3 809.0.0 2 1.55 15 .25 .14 1.8 .8 1.2 3.4 10\n","Duplicate segmented boss");
    rejects(p,"boss_chain 19.3.0 2 6 3 809.0.0 2 1.55 15 .1 .25 1.8 .8 1.2 3.4 10\n","Invalid segmented boss");
    rejects(p,"boss_chain_attacks 19.3.0 61.3.0 61.0.0 5 4 2 3 7 7.5 10\n","preceding controller");
    rejects(p,"death_cross 61.0.0 0 8 10 0 0 10\n","Duplicate death cross");
    rejects(p,"death_cross 11.0.0 0 8 10 0 0 10\n","independent pursuing flyer");
    rejects(p,"boss_lasers 68.1.0 32 .32 .7 1.5 .8 10\n","Duplicate boss laser");
    rejects(p,"boss_ipecac 68.1.0 1.1 12 2 2.8 20 12\n","Duplicate boss Ipecac");
    rejects(p,"boss_lasers 9999.0.0 32 .32 .7 1.5 .8 10\n","preceding Bloat controller");
    rejects(p,"charge 23.0.0 11 1.5 .8 .7 .7 1.8\n","Duplicate charge controller");
    rejects(p,"statue 42.0.0 aimed combat 2.8 .3 10 8 0 32 .25 .08 0 0 0\n","Duplicate statue controller");
    rejects(p,"statue 11.0.0 aimed combat 2.8 .3 10 8 0 32 .25 .08 0 0 0\n","stationary non-contact hazard");
    rejects(p,"statue 11.0.0 aimed combat 0 .3 10 8 0 32 .25 .08 0 0 0\n","Invalid statue values");
    rejects(p,"statue_lob 42.1.0 1.1 12 2.5 20\n","Duplicate statue lob");
    rejects(p,"statue_lob 42.0.0 1.1 12 2.5 20\n","preceding lob controller");
    rejects(p,"statue_rooms 1 3000\n","Duplicate statue room chance");
    rejects(p,"statue_pool 1 3 any 42.0.0 1\n","Duplicate statue pool entry");
    rejects(p,"statue_pool 1 3 any 11.0.0 1\n","configured hazard");
    rejects(p,"statue_supply 809.0.0 2.5 3 4.5 100 25 12 .7 .75 10\n","Duplicate statue supply");
    rejects(p,"statue_supply 42.0.0 2.5 3 4.5 100 25 12 .7 .75 10\n","preceding supply controller");
    rejects(p,"statue 11.0.0 supply never 1 0 1 1 0 24 .25 .08 0 0 0\nstatue_supply 11.0.0 2.5 0 4.5 100 25 12 .7 .75 10\n","Invalid statue supply values");
    rejects(p,"statue_quake 804.0.0 0 1 .45 .5 .5\n","Duplicate statue quake");
    rejects(p,"statue_quake 42.0.0 0 1 .45 .5 .5\n","preceding quake controller");
    rejects(p,"statue 11.0.0 quake plates 3 0 10 10 0 32 .25 .08 0 0 0\nstatue_quake 11.0.0 0 1 3 .5 .5\n","Invalid statue quake values");
    rejects(p,"statue_attraction 235.0.0 2 12 40 4 0 0\n","Duplicate statue attraction");
    rejects(p,"statue_attraction 42.0.0 2 12 40 4 0 0\n","preceding attraction controller");
    rejects(p,"statue 11.0.0 attraction plates 1 0 1 1 0 24 .25 .08 0 0 0\nstatue_attraction 11.0.0 6 12 40 4 0 0\n","Invalid statue attraction values");
    rejects(p,"statue 11.0.0 attraction plates 1 0 1 1 0 24 .25 .08 0 0 0\nstatue_attraction 11.0.0 2 12 40 4 4 0\n","Invalid statue attraction values");
    rejects(p,"companion 23.0.1 20 .7 .45 .32 room\n","Duplicate companion controller");
    rejects(p,"companion 23.0.0 20 .7 .45 .32 room\n","non-pool independent charge actor");
    rejects(p,"companion 11.0.0 20 .7 .45 .32 room\n","Invalid linked head release identity");
    rejects(p,"companion 23.0.0 20 .7 .45 0 room\n","Invalid companion values");
    rejects(p,"contact_familiar isaac:collectible:433 23.0.1 16 .15 .6 .25\n","Duplicate contact familiar");
    rejects(p,"contact_familiar missing:collectible:1 23.0.1 16 .15 .6 .25\n","installed item and companion child");
    rejects(p,"contact_familiar dw:collectible:0 23.0.0 16 .15 .6 .25\n","installed item and companion child");
    rejects(p,"contact_familiar dw:collectible:0 23.0.1 65 .15 .6 .25\n","Integer outside allowed range");
    rejects(p,"charge 18.0.0 11 1.5 .8 .7 .7 1.8\n","independent grounded contact actor");
    rejects(p,"charge_mode 23.2.0 cardinal reflect 0 .65 10\n","Duplicate charge mode");
    rejects(p,"charge_trail 23.2.0 .12 .7 2.5\n","Duplicate charge trail");
    rejects(p,"charge_tail 23.3.0 .65 .35\n","Duplicate charge tail");
    rejects(p,"charge_death 23.1.0 4 45 7 10\n","Duplicate charge death volley");
    rejects(p,"charge_mode 23.0.0 cardinal stop -1 0 10\n","Invalid charge mode");
    rejects(p,"charge_tail 23.0.0 2 .4\n","Invalid tail navigation hull");
    rejects(p,"charge_trail 23.0.0 0 .7 2.5\n","Invalid charge trail");
    rejects(p,"charge_mode 9999.0.0 cardinal stop 0 0 10\n","preceding charge controller");
    rejects(p,"boss_native 0 0\n","positive total weight");
    rejects(p,"component_bounce 68.10.0 68.0.0 10 1.5\n","Duplicate component controller");
    rejects(p,"component_bounce 18.0.0 68.0.0 10 1.5\n","independent flying hazard");
    rejects(p,"boss_peep 9999.0.0 68.10.0 .85 6 3.5 6 2.8 6 7.5 10 20 .85 1.25 .3 .7 1 1 1\n","dedicated grounded boss");
    rejects(p,"replace_monster 15.0.0 15.2.0 1 2 any 100 1\n","Overlapping monster replacement conditions");
    rejects(p,"replace_monster 11.0.0 9999.0.0 0 3 any 100 1\n","distinct independent natural monsters");
    rejects(p,"replace_monster 11.0.0 11.0.0 0 3 any 100 1\n","distinct independent natural monsters");
    rejects(p,"replace_monster 222.0.0 18.0.0 0 3 any 100 1\n","distinct independent natural monsters");
    rejects(p,"replace_monster 11.0.0 11.1.0 0 3 any 10001 1\n","Integer outside allowed range");
    rejects(p,"behavior broken ready 24\nprojectile_life 0\nend\n","Invalid projectile lifetime");
    rejects(p,"behavior broken ready 24\nprojectile_pattern radial 8\nend\n","Invalid projectile pattern angle");
    rejects(p,"behavior broken ready 24\nprojectile_curve nan alternate\nend\n","finite number");
    rejects(p,"behavior broken ready 24\nprojectile_curve 21 fixed\nend\n","Invalid projectile angular velocity");
    rejects(p,"behavior broken ready 24\nprojectile_kind lava\nend\n","Unknown value");
    rejects(p,"behavior broken ready 24\nwander 2 1\nend\n","Invalid wandering interval");
    rejects(p,"behavior broken ready 24\nstate ready ready wander 0 1\nmotion_speed -1\nendstate\nend\n","Invalid motion speed multiplier");
    rejects(p,"death bad\noverkill 1\nend\n","Overkill threshold");
    rejects(p,"death bad\nend\n","at least one outcome");
    rejects(p,"death bad\noutcome 1\noffspring 9000.0.0 1 1 1\nendoutcome\nend\n","Unknown death offspring");
    rejects(p,"death bad\noutcome 1\noffspring 19.2.0 1 1 1\nendoutcome\nend\n","dedicated segmented encounter");
    rejects(p,"death bad\noutcome 1\noffspring 18.0.0 64 64 1\noffspring 18.0.0 1 1 1\nendoutcome\nend\n","offspring budget");
    rejects(p,"death bad\noutcome 1\noffspring 18.0.0 2 1 1\nendoutcome\nend\n","Integer outside allowed range");
    rejects(p,"death bad\noutcome 1\noffspring 18.0.0 1 1 0\nendoutcome\nend\n","Invalid offspring health");
    rejects(p,"death bad\noutcome 1\nend\n","Unmatched end");
    rejects(p,"death_for 13.0.0 missing\n","Unknown monster or death rule");
    rejects(p,"death_for 16.0.0 mulligan\n","Duplicate death binding");
    rejects(p,"death_for 10.1.0 mulligan\n","another exclusive death controller");
    rejects(p,"regrowth 13.0.0 0.8 0.25 1 1000 2\n","excessive minimum health");
    rejects(p,"regrowth 13.0.0 2 0.25 1 12 2\n","Invalid regrowth");
    rejects(p,"regrowth 24.0.0 0.8 0.25 1 12 2\n","Duplicate regrowth");
    rejects(p,"behavior bad ready 24\nstate ready ready still 1 1\nenter summon\nendstate\nend\n","requires a child configuration");
    rejects(p,"behavior bad ready 24\nsummon 9999.0.0 1 6 1 1.6\nstate ready ready still 1 1\nendstate\nend\n","Unknown graph summon child");
    rejects(p,"behavior bad ready 24\nsummon 19.2.0 1 6 1 1.6\nstate ready ready still 1 1\nendstate\nend\n","dedicated segmented encounter");
    rejects(p,"behavior bad ready 24\nsummon 853.0.0 7 6 1 1.6\nend\n","Integer outside allowed range");
    rejects(p,"behavior bad ready 24\nsummon 853.0.0 1 6 0 1.6\nend\n","Invalid summon health");
    rejects(p,"behavior bad ready 24\norbit 3.5 0\nend\n","Invalid orbit");
    rejects(p,"formation 222.0.0 ring 10 2.4 2.6 1.4 8\n","Duplicate formation");
    rejects(p,"fire_reaction 15.0.0 dry 0 0 none both fraction\n","Duplicate fire reaction");
    rejects(p,"target_hop 29.0.0 .1 0 26 4 17 0 0 130 1.3 200 95 5 40 10 30 .05 .1 .7 .75 30 10 1.4 10\n","Duplicate destination hop binding");
    rejects(p,"hop 9999.0.0 6 2 4 .7 1.4 5 .3\n","independent ground hopper");
    rejects(p,"hop 14.0.0 6 2 4 .7 1.4 5 .3\n","independent ground hopper");
    rejects(p,"hop 29.1.0 6 2 4 0 1.4 5 .3\n","Invalid hop geometry");
    rejects(p,"hop 29.1.0 6 2 4 .7 6 5 .3\n","Invalid hop geometry");
    rejects(p,"hop 29.1.0 nan 2 4 .7 1.4 5 .3\n","finite number");
    rejects(p,"fire_reaction 11.1.0 any -1 1 none both fraction\n","Invalid fire damage multiplier");
    rejects(p,"fire_reaction 11.1.0 any 1 nan none both fraction\n","finite number");
    rejects(p,"fire_reaction 11.1.0 any 1 1 9000.0.0 both fraction\n","Invalid fire transformation target");
    rejects(p,"fire_reaction 11.1.0 any 1 1 11.1.0 both fraction\n","Invalid fire transformation target");
    rejects(p,"fire_reaction 11.1.0 any 1 1 13.0.0 both fraction\n","compatible independent bodies");
    rejects(p,"fire_reaction 10.0.0 any 1 1 10.1.0 both fraction\nfire_reaction 10.1.0 any 1 1 10.0.0 both fraction\n","Cyclic fire transformation");
    rejects(p,"formation 18.0.0 ring 10 2.4 2.6 1.4 8\n","flying legacy orbit actor");
    rejects(p,"formation 222.0.0 ring 1 2.4 2.6 1.4 8\n","Integer outside allowed range");
    rejects(p,"formation 222.0.0 ring 10 2.4 2.6 1.4 1\n","Invalid formation");
    rejects(p,"encounter 0 0 pursuit specialist 18.0.0 1 3 2 4\n","exceeds its actor cap");
    check(defaultMechanics()->fingerprint()==before,"invalid loads never change live registry");
}
void externalEncounters() {
    Pack p;p.clearEncounterPools();
    const std::string rows=
        "encounter 0 3 any basic 11.1.0 1 1 0\n"
        "encounter 0 3 any basic 10.1.0 0 1 0\n"
        "encounter 0 3 any specialist 12.0.0 1 2 1\n"
        "encounter 0 3 any specialist 15.0.0 100 3 1\n";
    std::ofstream(p.root/"encounters.mechanics")<<"DEATHWARD_MECHANICS 1\n"<<rows;
    auto library=MechanicsLibrary::load(p.root);auto run=fixture(library);
    for(int band=0;band<4;++band)for(int pattern=0;pattern<4;++pattern) {
        run.arena.profile.band=band;run.arena.profile.patterns={0,0,0,0};run.arena.profile.patterns[size_t(pattern)]=1;
        run.arena.profile.maxThreat=14;run.arena.profile.maxSpecialists=4;
        for(int room=0;room<run.arena.roomCount();++room) {
            auto &r=run.arena.rooms[size_t(room)];r.kind=RoomKind::Combat;r.floors={{{-25,-.4f,-25},{25,0,25}}};
            const auto plan=run.floorEncounter(room);
            int cost=0;std::map<MonsterId,int> counts;
            for(auto id:plan.originalMonsters){++counts[id];cost+=id==monsterId(12)?2:id==monsterId(15)?4:1;}
            check(!plan.monsters.empty()&&cost==plan.spent&&cost<=plan.budget,"file-defined costs reach actual floor plans");
            check(counts[monsterId(12)]<=1&&counts[monsterId(15)]<=1,"file-defined room caps survive repeated weighted choices");
            check(!counts[monsterId(10,1)]&&counts.size()<=4,"disabled basics never selected");
            check(plan.specialists==(pattern==0?1:2),"exhausted specialist caps fall back to basic budget filling");
            run.combatRng.next();r.depth+=20;
            check(run.floorEncounter(room).monsters==plan.monsters,"combat RNG and room depth do not alter external pools");
        }
    }
    // A second content load can change the pools without changing a running expedition.
    std::ofstream(p.root/"encounters.mechanics")<<"DEATHWARD_MECHANICS 1\n"
        "encounter 0 3 any basic 11.0.0 1 1 0\nencounter 0 3 any specialist 14.0.0 1 2 1\n";
    auto changed=fixture(MechanicsLibrary::load(p.root));changed.arena=run.arena;
    check(run.floorEncounter(0).monsters!=changed.floorEncounter(0).monsters,"new pools load independently of live content snapshot");
    std::ofstream(p.root/"encounters.mechanics")<<"DEATHWARD_MECHANICS 1\n";
    rejects(p,"","Encounter pool needs an unlimited positive-weight cost-1 single-actor basic");
}
void externalDeathRules() {
    Pack p;
    p.extra(R"(
death custom
overkill -5
outcome 1
offspring 18.0.0 2 2 0.25
endoutcome
end
death_for 13.0.0 custom
)" );
    auto a=MechanicsLibrary::load(p.root);auto live=fixture(a);
    p.extra(R"(
death custom
outcome 1
endoutcome
end
death_for 13.0.0 custom
)" );
    auto b=MechanicsLibrary::load(p.root);auto changed=fixture(b);
    for(auto *run:{&live,&changed}) {
        const auto id=run->spawnMonster(monsterId(13),{0,.85f,0});
        Event e;e.type=EventType::Damage;e.target=id;e.damage=run->findEnemy(id)->hp;
        run->queueRoot(e);run->drainEvents();run->step({});
    }
    check(live.livingEnemies()==2&&changed.livingEnemies()==0,"external death edits apply only to the new snapshot");
    for(const auto &e:live.enemies)check(e.hp==4&&e.maxHp==4,"quarter-health offspring use source-scaled Attack Fly16HP");
    check(a->fingerprint()!=b->fingerprint(),"death rules participate in content fingerprint");
    p.extra(R"(
death tiny_globin
outcome 1
offspring 24.0.0 1 1 0.05
endoutcome
end
death_for 13.0.0 tiny_globin
)" );
    auto tiny=fixture(MechanicsLibrary::load(p.root));
    const auto source=tiny.spawnMonster(monsterId(13),{0,.85f,0});
    Event hit;hit.type=EventType::Damage;hit.target=source;hit.damage=1000;
    tiny.queueRoot(hit);tiny.drainEvents();tiny.step({});
    check(tiny.enemies.size()==1&&near(tiny.enemies.front().maxHp,4.8f),"offspring may legitimately start below the regrowth health floor");
    hit.target=tiny.enemies.front().id;tiny.queueRoot(hit);tiny.drainEvents();
    check(near(tiny.enemies.front().maxHp,4.8f)&&near(tiny.enemies.front().hp,1.2f),
          "regrowth floor cannot raise a scaled child's maximum health");
}
const std::string powers=R"(
item test:collectible:9001 "Test power" "COMMON" "Adds ten damage."
end
item test:trinket:9001 "Test charm" "COMMON" "Same local number, separate category."
hook ghost once
end
rule test_add 5 test:collectible:9001 4 always
modify damage add 10 0 per_copy
end
rule test_pair 6 test:trinket:9001 1 always
requires test:collectible:9001 1 -1
modify damage multiply 2 0 once
end
pool shop test:collectible:9001 10000
pool shop test:trinket:9001 10000
)";
void externalItemsAndSnapshots() {
    Pack p;p.extra(powers);const auto a=MechanicsLibrary::load(p.root);
    const auto power=parseItemKey("test:collectible:9001"),charm=parseItemKey("test:trinket:9001");
    auto left=fixture(a),right=fixture(a);left.grant(power);left.grant(charm);right.grant(charm);right.grant(power);
    check(near(playerAttack(left,24,false).damage,68)&&near(playerAttack(right,24,false).damage,68),"new file-only items and conditional interaction execute in both pickup orders");
    Event shot;shot.position=shot.origin=left.player.position;shot.direction={1,0,0};left.queueRoot(shot);left.drainEvents();
    check(!left.projectiles.empty()&&near(left.projectiles.back().damage,68),"external rule reaches actual projectile emission");
    const auto target=left.spawn(EnemyKind::Gunman,{8,.85f,0});
    Event kill;kill.type=EventType::Damage;kill.target=target;kill.damage=10000;kill.direction={1,0,0};kill.origin=left.player.position;
    left.queueRoot(kill);left.drainEvents();
    check(left.projectiles.back().context.sourceItem==charm,"native event hook retains the namespaced source item");
    const auto offers=drawItemOffers(ItemPool::Shop,4,*a);
    check(offers[0]!=offers[1]&&(offers[0]==power||offers[1]==power),"external items enter real weighted reward pools");
    auto modified=powers;modified.replace(modified.find("damage add 10"),13,"damage add 20");p.extra(modified);
    const auto b=MechanicsLibrary::load(p.root);auto newer=fixture(b);newer.grant(power);
    check(a->fingerprint()!=b->fingerprint()&&near(playerAttack(newer,24,false).damage,44)&&near(playerAttack(left,24,false).damage,68),"new load sees edits while existing expedition retains its snapshot");
    const auto path=p.root/"campaign.save";CampaignStore store(path);const auto runId=store.begin(1866,"mechanics test");
    auto summary=left.summary();summary.id=runId;summary.mechanicsFingerprint=a->fingerprint();store.checkpoint(summary);
    CampaignStore reloaded(path);check(reloaded.data().pending->items==left.items&&reloaded.data().pending->mechanicsFingerprint==a->fingerprint(),"namespaced IDs and rules fingerprint survive save v7 even without package registration in global library");
    auto bargain=fixture(a);bargain.rooms[0].offers[0]=ItemId::Judas;
    check(near(bargain.bargainMaxHealth(0),64),"bargain includes external pickup-health rule");
    auto changedHealth=std::ifstream(p.root/"items.mechanics");
    std::string items((std::istreambuf_iterator<char>(changedHealth)),{});changedHealth.close();
    items.replace(items.find("pickup_health 0.8"),17,"pickup_health 0.5");
    std::ofstream(p.root/"items.mechanics")<<items;
    auto editedBargain=fixture(MechanicsLibrary::load(p.root));editedBargain.rooms[0].offers[0]=ItemId::Judas;
    check(near(editedBargain.bargainMaxHealth(0),40),"bargain preview follows an edited data value");
}
void legacyInventory() {
    Pack p;const auto path=p.root/"legacy.save";
    const std::string payload="2 42 50 50 0 0 0 0 0 0 100\n0\n"
        "\"Sheriff Cole\" \"alive\" 0\n\"Mary Bell\" \"alive\" 0\n"
        "\"Father Gabriel\" \"alive\" 0\n\"Silas Reed\" \"alive\" 0\n\"Dr. Whitmore\" \"alive\" 0\n1\n"
        "1 42 \"deathward-m1-53\" \"The Lost Survey\" \"\" 2 0 0 0 0 5 0 1 0 1 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n3 0 2 10\n0\n0\n0\n";
    uint64_t hash=14695981039346656037ULL;for(unsigned char c:payload)hash=(hash^c)*1099511628211ULL;
    std::ofstream(path,std::ios::binary)<<"DEATHWARD 6 "<<hash<<'\n'<<payload;
    CampaignStore old(path);const std::vector<ItemKey> expected{ItemId::Ricochet,ItemId::Judas,ItemId::Braid};
    check(old.data().pending->items==expected&&old.data().pending->mechanicsFingerprint.empty(),"format-6 numeric inventory migrates to stable keys");
    old.recover();check(CampaignStore(path).data().history.back().items==expected,"legacy inventory survives writing and reading format 7");
}
void graphs() {
    Pack p;p.extra(R"(
behavior guard_cycle guard 24
projectiles 3 0.2 7 8
state guard windup still 0.1 0
enter lock_target
exit fire
transition open timer 0
endstate
state open exposed still 1 1
transition desperate health_below 0.5
transition guard timer 0
endstate
state desperate ready chase 0 0.5
enter lock_target
enter fire
endstate
end
monster 912.100.0 "Graph test" Still Spread Skull 80 2 0.6 2 0.1 1 0 0 0 0 guard_cycle
monster 913.0.0 "Distinct tuple" Still Shot Skull 80 0 0.6 2 0.1 1 0 0 0 0 aimed_shooter
)" );
    auto content=MechanicsLibrary::load(p.root);auto run=fixture(content);
    const auto id=run.spawnMonster(monsterId(912,100),{0,.85f,0});check(id!=0,"external high-variant enemy spawns");
    auto hurt=[&](float damage){Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;run.queueRoot(e);run.drainEvents();};
    hurt(10);check(run.findEnemy(id)->hp==80,"initial-state immunity works before first update");
    for(int i=0;i<5;++i)run.step({});check(run.projectiles.empty(),"graph telegraph does not emit early");
    for(int i=0;i<3;++i)run.step({});check(run.projectiles.size()==3&&run.findEnemy(id)->state==EnemyState::Exposed,"one exit action emits configured three-shot spread");
    hurt(45);check(run.findEnemy(id)->hp==35,"exposed state takes normal damage");
    const auto before=run.findEnemy(id)->position;run.step({});check(run.findEnemy(id)->behavior.state==2,"health threshold selects authored next phase");
    hurt(10);check(run.findEnemy(id)->hp==30,"phase damage multiplier is applied by real damage pipeline");
    run.step({});check(distance(before,run.findEnemy(id)->position)>0,"authored phase enables chase movement");
    check(content->monster(monsterId(913))->name=="Distinct tuple","both formerly colliding definitions coexist");
    const auto saved=run.findEnemy(id)->behavior;
    run.enterRoom(1);run.enterRoom(0);
    check(run.findEnemy(id)&&run.findEnemy(id)->behavior.state==saved.state,"resident enemy preserves state graph across room re-entry");
}
void ownedGraphSummons() {
    Pack p;p.extra(R"(
behavior test_brood ready 24
summon 853.0.0 4 6 0.5 1.6
state ready ready still 0 1
enter summon
exit summon
transition ready timer 0
endstate
end
monster 912.100.0 "Summon test" Still None Walker 80 0 0.6 2 0.1 1 0 0 0 0 test_brood
)" );
    auto run=fixture(MechanicsLibrary::load(p.root));
    const auto owner=run.spawnMonster(monsterId(912,100),{0,.85f,0});
    const auto other=run.spawnMonster(monsterId(912,100),{8,.85f,0});
    run.step({});
    for(auto parent:{owner,other}) {
        int count=0;
        for(const auto &e:run.enemies)if(e.summoner==parent) {
            ++count;check(e.monster==monsterId(853)&&near(e.hp,16)&&e.partner==0,"graph summon preserves child/health and independent ownership");
        }
        check(count==6,"enter+exit+enter summons in one tick count pending children, separately for each owner");
    }
    run.enterRoom(1);for(int i=0;i<120;++i)run.step({});run.enterRoom(0);
    run.step({});check(run.enemies.size()==14,"owned summon cap survives room departure and return");
    run.limits.enemies=15;const auto last=run.spawnMonster(monsterId(912,100),{-8,.85f,0});
    run.step({});check(last&&run.enemies.size()==15&&run.stats.suppressed>0,"global capacity still bounds graph summons");
}
void externalProjectilePatterns() {
    Pack p;
    const auto graph=[](float curve){return std::string(R"(
monster 912.100.0 "Pattern fixture" Still Cross Blob 80 0 .6 1 .1 1 0 1 0 0 external_pattern
behavior external_pattern fire 24
projectiles 3 0 7 6
projectile_pattern radial 0.3
projectile_kind brown
projectile_curve )")+std::to_string(curve)+R"( alternate
projectile_life 2
state fire ready still 1 1
enter fire
transition fire timer 0
endstate
end
)";};
    p.extra(graph(.4f));auto a=MechanicsLibrary::load(p.root);auto live=fixture(a);
    p.extra(graph(-.7f));auto b=MechanicsLibrary::load(p.root);auto next=fixture(b);
    for(auto *s:{&live,&next}) {
        s->spawnMonster(monsterId(912,100),{0,.85f,0});s->step({});
        check(s->projectiles.size()==3,"external radial pattern executes actual three-shot volley");
        for(size_t n=0;n<3;++n) {
            const auto &shot=s->projectiles[n];
            check(distance(shot.velocity,rotateY({6,0,0},.3f+float(n)*2*Pi/3))<.001f,
                  "external radial launch angle reaches real projectile velocity");
            check(shot.kind==ProjectileKind::Brown&&near(shot.life,2)&&near(shot.damage,7),
                  "external kind, lifetime and damage reach actual shot");
        }
    }
    check(near(live.projectiles[0].angularVelocity,.4f)&&near(next.projectiles[0].angularVelocity,-.7f),
          "new snapshot accepts edited curve without changing existing expedition");
    check(a->fingerprint()!=b->fingerprint(),"projectile primitive values participate in fingerprint");
}
void externalHops() {
    Pack p;const auto before=MechanicsLibrary::load(p.root);
    auto oldRun=fixture(before);oldRun.player.position.z=-8;
    const auto old=oldRun.spawnMonster(monsterId(29),{0,.85f,0});
    std::ifstream input(p.root/"hops.mechanics");std::string config((std::istreambuf_iterator<char>(input)),{});
    const auto at=config.find("0 0 130 1.3");check(at!=config.npos,"ordinary source range fixture exists");
    config.replace(at,11,"0 0 60 1.3");std::ofstream(p.root/"hops.mechanics")<<config;
    const auto after=MechanicsLibrary::load(p.root);auto fresh=fixture(after);fresh.player.position.z=-8;
    const auto next=fresh.spawnMonster(monsterId(29),{0,.85f,0});
    for(int n=0;n<4;++n){oldRun.step({});fresh.step({});}
    const auto &a=*oldRun.findEnemy(old)->targetHop,&b=*fresh.findEnemy(next)->targetHop;
    check(a.pursuing&&!b.pursuing,"source-range edit affects real acquisition while old run retains its snapshot");
    std::cout<<"HOP_RELOAD old_ready="<<a.targetReady<<" new_ready="<<b.targetReady
        <<" old="<<a.destination.x<<','<<a.destination.z<<" new="<<b.destination.x<<','<<b.destination.z<<'\n';
    check(a.targetReady&&b.targetReady&&distance(a.destination,b.destination)>1,"range edit changes committed target versus wander destination");
    check(before->fingerprint()!=after->fingerprint(),"destination hop configuration participates in snapshot fingerprint");
}
void externalFireReactions() {
    Pack p;auto old=MechanicsLibrary::load(p.root);auto live=fixture(old);
    std::ifstream in(p.root/"fire.mechanics");std::string config((std::istreambuf_iterator<char>(in)),{});in.close();
    const std::string before="fire_reaction 15.0.0 dry 0 0 15.3.0 both fraction";
    config.replace(config.find(before),before.size(),"fire_reaction 15.0.0 any 1 1 15.1.0 flame current");
    std::ofstream(p.root/"fire.mechanics")<<config;
    auto newer=MechanicsLibrary::load(p.root);auto next=fixture(newer);
    for(auto *s:{&live,&next}) {
        const auto id=s->spawnMonster(monsterId(15),{0,.85f,0});s->findEnemy(id)->hp=60;
        Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=10;hit.damageKind=DamageKind::Flame;
        s->queueRoot(hit);s->drainEvents();
    }
    check(live.enemies[0].monster==monsterId(15,3)&&near(live.enemies[0].hp,72),"live snapshot retains original fractional fire transform");
    check(next.enemies[0].monster==monsterId(15,1)&&near(next.enemies[0].hp,50),"edited target/current-health policy/damage scale executes in new snapshot");
    check(old->fingerprint()!=newer->fingerprint(),"fire rules participate in content fingerprint");
}
void externalFormations() {
    Pack p;std::ofstream(p.root/"formations.mechanics")<<"DEATHWARD_MECHANICS 1\nformation 222.0.0 ring 6 3 1.5 2 8\n";
    auto content=MechanicsLibrary::load(p.root);auto run=fixture(content);
    for(int i=0;i<7;++i)run.spawnMonster(monsterId(222),{float(i)-3,.85f,0});
    run.step({});check(run.rooms[0].formations.size()==2,"external six-member cap creates two formations for seven actors");
    check(run.rooms[0].formations[0].slots.size()==6&&near(run.rooms[0].formations[0].angle,1.5f*Tick),"external cap and angular speed reach actual simulation");
    check(near(run.rooms[0].formations[0].center.z,2*EnemyMovementMultiplier*Tick),"external translation speed reaches actual simulation");
    std::ofstream(p.root/"formations.mechanics")<<"DEATHWARD_MECHANICS 1\nformation 222.0.0 ring 6 3 2 2 9\n";
    auto next=MechanicsLibrary::load(p.root);check(next->fingerprint()!=content->fingerprint(),"formation edits change snapshot fingerprint");
    check(near(run.content->formation(monsterId(222))->angularSpeed,1.5f)&&near(next->formation(monsterId(222))->angularSpeed,2),"existing expedition keeps original formation rules while next snapshot loads edits");
    p.clearEncounterPools();
    std::ofstream(p.root/"encounters.mechanics")<<"DEATHWARD_MECHANICS 1\nencounter 0 3 any basic 11.1.0 1 1 0 4\nencounter 0 3 any specialist 12.0.0 1 2 1\n";
    rejects(p,"","single-actor basic");
}
}
int main(){try{identities();validation();externalEncounters();externalDeathRules();externalItemsAndSnapshots();legacyInventory();graphs();ownedGraphSummons();externalFormations();externalProjectilePatterns();externalFireReactions();externalHops();std::cout<<"Mechanics contracts passed\n";return 0;}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
