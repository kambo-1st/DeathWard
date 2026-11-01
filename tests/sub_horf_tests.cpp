#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <set>
using namespace dw;
namespace {
void check(bool b,const char *m){if(!b)throw std::runtime_error(m);}
bool near(float a,float b,float eps=.003f){return std::abs(a-b)<eps;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-80,-1,-80},{80,20,80}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.entry={0,.85f,-70};r.kind=RoomKind::Combat;r.floors={{{-80,-.4f,-80},{80,0,80}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();
    s.rooms.assign(s.arena.roomCount(),{});s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.player.position={60,.85f,60};return s;
}
void tick(Simulation &s,int n=1,int hz=30){for(int i=0;i<n;++i)s.step({},1.f/hz);}
EntityId spawn(Simulation &s){return s.spawnMonster(monsterId(812),{0,.85f,0});}
void hit(Simulation &s,EntityId id,float damage,bool impulse=false){Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;e.projectileImpact=impulse;e.harmsCompanions=true;e.direction={1,0,0};s.queueRoot(e);s.drainEvents();}
void motionAndFire() {
    auto s=fixture();auto id=spawn(s);tick(s,120);
    check(near(s.findEnemy(id)->hp,44.8f)&&s.stats.projectiles==0&&near(length(s.findEnemy(id)->velocity),0),"source14HP x3.2; idle does not acquire player or shoot");
    s.player.position={0,.85f,5};tick(s,60);check(s.stats.projectiles==0,"nearby player alone does not trigger Sub Horf");
    hit(s,id,1,true);check(near(s.findEnemy(id)->velocity.x,12),"real projectile impact applies source mass3 recoil policy");
    tick(s,60);check(s.findEnemy(id)->position.x>1&&s.stats.projectiles>0&&std::abs(s.findEnemy(id)->facing.z)>.01f,"hit causes physical movement, rotation and shots");
    auto push=fixture();auto p=spawn(push);push.findEnemy(p)->velocity={12,0,0};tick(push,60);
    check(push.stats.projectiles>0&&near(push.findEnemy(p)->hp,44.8f),"external impulse without damage also activates firing");
    Vector3 position{};float angle=0;uint64_t shots=0;
    for(int hz:{30,60,120}) {
        auto q=fixture();auto a=spawn(q);q.findEnemy(a)->velocity={12,0,0};tick(q,hz,hz);
        const auto *e=q.findEnemy(a);
        if(hz==30){position=e->position;angle=e->headShooter->angle;shots=q.stats.projectiles;}
        else check(distance(position,e->position)<.003f&&near(angle,e->headShooter->angle)&&shots==q.stats.projectiles,"30/60/120Hz preserve source spin, movement and shot count");
    }
    auto cover=fixture();auto c=spawn(cover);cover.arena.floorProps.push_back({StoryPropKind::Crate,{{1,-.1f,-4},{2,3,4}}});cover.arena.rebuildWalls();cover.findEnemy(c)->velocity={24,0,0};tick(cover,30);
    check(!cover.arena.blocked(cover.findEnemy(c)->position,cover.findEnemy(c)->radius)&&cover.findEnemy(c)->position.x<1,"grounded reactive movement respects cover");
    std::cout<<"SUB_HORF idle=1 hit_recoil=1 external_push=1 spin=1 shots=1 partitions=3 cover=1\n";
}
void deathAndCombinedEffects() {
    for(bool friendly:{false,true}) {
        auto s=fixture();auto id=spawn(s);
        if(friendly)check(s.applyEnemyStatus(id,EnemyStatus::Charm,-1),"permanent Charm applies");
        s.limits.projectiles=0;hit(s,id,100);
        check(!s.findEnemy(id)->alive&&s.findEnemy(id)->headShooter->pendingShots.size()==1,"one death shot retained at capacity");
        check(s.stats.kills==unsigned(!friendly),"friendly death does not pay hostile kill reward");
        s.debugScenario=false;tick(s,3);check(!s.roomClear&&s.findEnemy(id),"pending death shot prevents cleanup and early room clear");
        s.limits.projectiles=64;tick(s);
        check(s.stats.projectiles==1,"capacity recovery emits exactly one final shot");
        check(!s.projectiles.empty()&&s.projectiles.front().context.sourceEntity==id&&s.projectiles.front().ignoresPlayer==friendly,"death-shot attribution and Charm ownership survive corpse removal");
        tick(s,240);check(s.stats.projectiles==1&&s.roomClear,"one death shot resolves without duplicate and room can finish");
    }
    auto s=fixture();auto id=spawn(s);s.findEnemy(id)->velocity={12,0,0};tick(s,10);
    check(s.applyEnemyStatus(id,EnemyStatus::Freeze,30)&&s.applyEnemyStatus(id,EnemyStatus::Slow,90),"Freeze and Slow combine");
    const auto angle=s.findEnemy(id)->headShooter->angle;const auto shots=s.stats.projectiles;tick(s,10);
    check(near(s.findEnemy(id)->headShooter->angle,angle)&&s.stats.projectiles==shots,"Freeze holds spin and new shots despite Slow");
    s.removeEnemyStatus(id,EnemyStatus::Freeze);s.findEnemy(id)->velocity={12,0,0};tick(s,5);
    check(!near(s.findEnemy(id)->headShooter->angle,angle),"reactive controller resumes after thaw");
    auto damage=fixture();auto d=spawn(damage);damage.applyEnemyStatus(d,EnemyStatus::Charm,-1);damage.applyEnemyStatus(d,EnemyStatus::Freeze,90);Context hostile;hostile.damageSource=DamageSource::Enemy;damage.applyEnemyStatus(d,EnemyStatus::Poison,90,100,hostile);damage.limits.projectiles=0;tick(damage,5);
    check(!damage.findEnemy(d)->alive&&damage.findEnemy(d)->headShooter->pendingShots.size()==1,"poison continues through Freeze and creates one owned final shot");
    check(damage.findEnemy(d)->headShooter->pendingShots.front().projectileIgnoresPlayer&&damage.stats.kills==0,"status lethal damage preserves permanent Charm and no hostile reward");
    std::cout<<"SUB_HORF_COMBINED death_retry=1 no_early_clear=1 charm_affiliation=1 freeze_slow=1 poison_frozen_death=1\n";
}
void replacement() {
    const auto lib=defaultMechanics();FloorProfile p;p.band=0;
    const auto *r=lib->replacement(monsterId(12),p);
    check(r&&r->target==monsterId(812)&&r->chance==1&&r->chanceOutOf==60,"exact rational replacement config");
    for(int band=0;band<4;++band){p.band=band;check(lib->replacement(monsterId(12),p),"no invented floor gate");}
    auto s=fixture();s.arena.profile.band=0;s.arena.rooms.resize(4000,s.arena.rooms.front());
    int originals=0,replacements=0,witness=-1;
    for(int room=0;room<4000;++room) {
        auto a=s.floorEncounter(room),b=s.floorEncounter(room);check(a.monsters==b.monsters,"replacement is seeded and repeatable");
        for(size_t i=0;i<a.monsters.size();++i)if(a.originalMonsters[i]==monsterId(12)) {
            ++originals;Random rng(1866^0x5245504c414345ULL^(uint64_t(room+1)*0x9e3779b97f4a7c15ULL)^((i+1)*0xbf58476d1ce4e5b9ULL));
            const auto expected=rng.bounded(60)==0?monsterId(812):monsterId(12);
            check(a.monsters[i]==expected,"production encounter uses denominator60, not rounded basis points");
            if(expected==monsterId(812)){++replacements;witness=room;}
        }
    }
    check(originals>60&&replacements>0&&replacements<originals/10,"rare natural replacement witnesses exist");
    for(size_t n=0;n<s.arena.rooms.size();++n)if(int(n)!=witness)s.arena.rooms[n].bounds={{1000,-1,1000},{1010,20,1010}};
    s.room=witness;s.rooms.resize(s.arena.rooms.size());s.spawnRoomEnemies();
    check(std::any_of(s.enemies.begin(),s.enemies.end(),[](const Enemy &e){return e.monster==monsterId(812)&&near(e.hp,44.8f);}),"selected encounter spawns real Sub Horf actor with source HP");
    std::cout<<"SUB_HORF_REPLACEMENT originals="<<originals<<" replacements="<<replacements<<" witness_room="<<witness<<" exact_denominator=60 actual_spawn=1\n";
}

void championStats() {
    for(int kind=0;kind<26;++kind)for(bool friendly:{false,true}) {
        auto s=fixture();auto id=spawn(s);const auto &p=*s.content->champion(kind);
        check(s.championTypeEligible(monsterId(812),kind)&&s.makeChampion(id,kind),"all26ordinary SubHorf combat types accepted");
        auto *e=s.findEnemy(id);check(near(e->hp,44.8f*p.hp)&&near(e->radius,.65f*p.collision)&&near(e->championVisual,p.visual/p.collision),"champion source HP conversion and footprints");
        if(friendly)check(s.applyEnemyStatus(id,EnemyStatus::Charm,-1),"permanent Charm applies to every champion");
        s.godMode=false;s.player.position=e->position;tick(s);
        check(near(s.player.hp,friendly?100.f:100.f-10*p.damage*EnemyDamageMultiplier),"champion contact damage and friendly player immunity");
        e=s.findEnemy(id);check(near(length(e->velocity),0),"speed modifiers never create autonomous SubHorf walking");
    }
    check(!defaultMechanics()->monster(monsterId(812,1)),"separate Tainted SubHorf not silently enabled");
    auto s=fixture();check(!s.championTypeEligible(monsterId(812),26)&&!s.championEligible(monsterId(812,1)),"invalid kind and Tainted body excluded");
    for(int kind:{9,14}) {
        auto q=fixture();auto id=spawn(q);q.makeChampion(id,kind);auto *e=q.findEnemy(id);e->age=0;auto a=e->championVisibility();e->age=1.5f;
        check(kind==9?std::abs(a-e->championVisibility())>.1f:near(a,.12f),"black/camouflage visibility");e->flash=.1f;check(near(e->championVisibility(),1),"hit flash reveals champion");
    }
    std::cout<<"SUB_HORF_CHAMPION_STATS types=26 charm_combinations=52 size_damage=1 idle_physics=1 visibility=1\n";
}
void championTrailsAndFields() {
    for(int kind:{2,24}) {
        auto s=fixture();auto id=spawn(s);s.makeChampion(id,kind);tick(s,60);
        check(s.hazards.empty()&&s.arena.breakables.empty(),"idle reactive Green/Brown produces no trail");
        s.findEnemy(id)->velocity={12,0,0};tick(s);
        check(kind==2?!s.hazards.empty():!s.arena.breakables.empty(),"pushed Green/Brown leaves actual trail");
        check(!s.arena.blocked(s.findEnemy(id)->position,s.findEnemy(id)->radius),"trail never traps its producer");
        if(kind==24) {
            const auto at=s.arena.breakables.back().rewardPosition;Event blast;blast.type=EventType::Explosion;blast.position=blast.origin=at;blast.damage=10;blast.radius=2;blast.playerDamage=0;blast.demolition=Demolition::SpentDynamite;s.queueRoot(blast);s.drainEvents();
            check(s.arena.breakables.back().destroyed&&s.arena.breakables.back().paid&&s.moneyPickups.empty(),"Brown droppings are destructible but pay no loot");
        }

    }
    auto s=fixture();auto id=spawn(s);s.makeChampion(id,10);tick(s,75);
    check(s.stats.projectiles==2&&s.findEnemy(id)->headShooter->shotFrames==0,"Magenta extra shots work at rest independently of reactive firing");
    auto retry=fixture();id=spawn(retry);retry.makeChampion(id,10);retry.limits.projectiles=1;
    Event occupied;occupied.hostile=true;occupied.position={-50,1,-50};occupied.direction={1,0,0};occupied.speed=1;occupied.projectileLife=5;
    retry.queueRoot(occupied);retry.findEnemy(id)->championAbility=0;tick(retry);
    check(retry.stats.projectiles==1&&retry.findEnemy(id)->championAbility<=0,"Magenta accounts for already queued shots and retains due shot");
    retry.projectiles.clear();tick(retry);check(retry.stats.projectiles==2&&retry.findEnemy(id)->championAbility>1,"Magenta retries after capacity returns");
    auto spectral=fixture();id=spawn(spectral);spectral.makeChampion(id,8);spectral.arena.obstacles.push_back({{2,-1,-4},{4,5,4}});spectral.arena.rebuildWalls();spectral.findEnemy(id)->velocity={24,0,0};tick(spectral,12);
    check(spectral.findEnemy(id)->position.x>4,"translucent reactive body crosses cover when pushed");
    spectral.findEnemy(id)->position={79,.85f,0};spectral.findEnemy(id)->velocity={24,0,0};tick(spectral,30);
    check(spectral.findEnemy(id)->position.x<=80-spectral.findEnemy(id)->radius+.001f,"translucent body remains inside sealed room");
    hit(spectral,id,10000);check(spectral.projectiles.size()==1&&spectral.projectiles.front().championSpectral,"own final shot inherits spectral modifier");
    spectral.enemies.clear();tick(spectral,120);check(spectral.projectiles.empty(),"spectral shot cannot escape room after owner removal");
    for(int kind:{11,16}) {
        auto q=fixture();auto actor=spawn(q);q.makeChampion(actor,kind);q.player.position={0,.85f,8};q.findEnemy(actor)->age=kind==16?1.f:0.f;
        Event shot;shot.position=shot.origin={0,.85f,8};shot.direction={1,0,0};shot.speed=10;shot.projectileLife=5;q.queueRoot(shot);q.drainEvents();const auto player=q.player.position;
        tick(q,kind==16?35:5);
        check(!q.projectiles.empty()&&(kind==11?q.projectiles.front().velocity.z<0:q.projectiles.front().velocity.z>0),"Violet/Gray fields bend real player bullets");
        check(kind==11?q.player.position.z<player.z:near(q.player.position.z,player.z),"Violet pulls player; Gray affects bullets only");
    }
    auto heal=fixture();auto actor=spawn(heal);heal.makeChampion(actor,20);auto other=spawn(heal);heal.findEnemy(other)->position={8,.85f,0};heal.findEnemy(other)->hp=1;const auto own=heal.findEnemy(actor)->hp;tick(heal);
    check(heal.findEnemy(other)->hp>1&&near(heal.findEnemy(actor)->hp,own),"PulsingRed heals others only");
    auto whites=fixture();auto a=spawn(whites),b=spawn(whites),normal=spawn(whites);whites.makeChampion(a,6);whites.makeChampion(b,6);const auto hp=whites.findEnemy(a)->hp;
    hit(whites,a,1);check(near(whites.findEnemy(a)->hp,hp),"White protects while ordinary threat lives");hit(whites,normal,10000);hit(whites,a,1);hit(whites,b,1);
    check(near(whites.findEnemy(a)->hp,hp-1)&&near(whites.findEnemy(b)->hp,hp-1),"White pair releases protection without softlock");
    std::cout<<"SUB_HORF_CHAMPION_FIELDS moving_trails=2 magenta_retry=1 spectral=1 attraction_repulsion=2 healing=1 white_release=1\n";
}
void championDeaths() {
    for(int kind=0;kind<26;++kind)for(bool friendly:{false,true}) {
        auto s=fixture();auto id=spawn(s);s.makeChampion(id,kind);if(friendly)s.applyEnemyStatus(id,EnemyStatus::Charm,-1);s.limits.projectiles=0;hit(s,id,10000);
        if(kind==12) {
            check(s.findEnemy(id)->alive&&s.findEnemy(id)->championPile&&s.stats.kills==0&&s.stats.projectiles==0,"DarkRed collapse emits neither reward nor own death shot");
            tick(s,80);check(s.findEnemy(id)->alive&&!s.findEnemy(id)->championPile&&near(s.findEnemy(id)->hp,s.findEnemy(id)->maxHp),"DarkRed revives");
            hit(s,id,10000);hit(s,id,10000);
        }
        check(!s.findEnemy(id)->alive&&s.stats.kills==unsigned(!friendly)&&s.findEnemy(id)->headShooter->pendingShots.size()==1,"every champion retains one own final shot and pays one kill");
        s.limits.projectiles=64;tick(s);
        const auto expected=(kind==13||kind==25)?9u:1u;
        check(s.stats.projectiles==expected,"champion volley adds to rather than replaces SubHorf own final shot");
        for(const auto &shot:s.projectiles)check(shot.ignoresPlayer==friendly&&shot.hitsEnemies==friendly,"every death projectile preserves parent affiliation after cleanup");
        if(kind==5||kind==25)check(s.stats.explosions==1,"cyan/rainbow death blast occurs once");
        if(kind==15) {
            int count=0;for(const auto &e:s.enemies)if(e.alive&&e.monster==monsterId(812)){++count;check(e.champion<0&&near(e.maxHp,44.8f),"split copies are ordinary source-HP actors");}
            check(count==2,"PulsingGreen produces two SubHorfs");
        }
    }
    auto orbit=fixture();auto id=spawn(orbit);orbit.makeChampion(id,17);tick(orbit,3);int orbiters=0;for(const auto &e:orbit.enemies)orbiters+=e.alive&&e.monster==monsterId(96)&&e.partner==id;check(orbiters==1,"LightWhite has owned orbiter");
    hit(orbit,id,10000);tick(orbit);int flies=0;for(const auto &e:orbit.enemies)flies+=e.alive&&e.monster==monsterId(18);check(flies==2&&orbit.stats.projectiles==1,"LightWhite releases orbiter plus fly while preserving own shot");
    auto split=fixture();id=spawn(split);split.makeChampion(id,15);split.applyEnemyStatus(id,EnemyStatus::Charm,-1);hit(split,id,10000);tick(split);
    EntityId child=0;for(const auto &e:split.enemies)if(e.alive&&e.monster==monsterId(812)){check(e.friendly&&e.permanentCharmed&&e.affectedBy(EnemyStatus::Charm),"split copies retain functional permanent Charm");child=e.id;}
    check(child!=0,"friendly split child exists");split.limits.projectiles=0;hit(split,child,10000);check(split.findEnemy(child)->headShooter->pendingShots.front().projectileIgnoresPlayer&&split.stats.kills==0,"friendly descendant death shot preserves player immunity and no hostile reward");
    auto skull=fixture();id=spawn(skull);skull.makeChampion(id,23);auto other=spawn(skull);skull.findEnemy(other)->position={8,.85f,0};hit(skull,id,10000);check(skull.stats.kills==2&&skull.stats.projectiles==2,"Skull chain kills preserve one shot and reward per body");
    auto orange=fixture();id=spawn(orange);orange.makeChampion(id,3);orange.godMode=false;orange.moneyCollected=10;orange.player.position={0,.85f,5};orange.findEnemy(id)->facing={0,0,1};hit(orange,id,10000);
    check(orange.projectiles.front().context.championCoinLoss,"own death shot snapshots Orange coin-loss trait");orange.enemies.clear();tick(orange,15);check(orange.player.hp<100&&orange.moneySpent>=2&&orange.moneySpent<=4,"Orange death shot removes coins after owner cleanup");
    auto pulse=fixture();id=spawn(pulse);pulse.makeChampion(id,21);for(int n=0;n<8;++n){hit(pulse,id,.01f);tick(pulse,10);}int count=0;for(const auto &e:pulse.enemies)count+=e.alive&&e.summoner==id&&e.monster==monsterId(18);check(count==5,"Pulsating fly population is capped");
    auto crown=fixture();id=spawn(crown);crown.makeChampion(id,22);other=spawn(crown);crown.findEnemy(other)->position={8,.85f,0};tick(crown);check(crown.findEnemy(other)->crowned&&crown.findEnemy(other)->champion<0,"Crown colors ordinary neighbor without champion stats");hit(crown,id,10000);tick(crown);check(!crown.findEnemy(other)->crowned,"Crown effect ends with parent");
    std::cout<<"SUB_HORF_CHAMPION_DEATHS types=26 affiliation_scenarios=52 revival=1 own_plus_volley=9 split=2 permanent_charm_children=1 orbit_release=1 skull_chain=1 fly_cap=5 crown=1\n";
}

void championNatural() {
    const auto dir=std::filesystem::temp_directory_path()/("dw-sub-horf-champions-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::filesystem::create_directories(dir);
    for(const auto &p:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(p.path().extension()==".mechanics")std::filesystem::copy_file(p.path(),dir/p.path().filename());
    auto edit=[&](const char *file,const char *from,const char *to){const auto path=dir/file;std::ifstream in(path);std::string data((std::istreambuf_iterator<char>(in)),{});const auto at=data.find(from);check(at!=data.npos,"natural champion fixture line exists");data.replace(at,std::string(from).size(),to);std::ofstream(path)<<data;};
    edit("champions.mechanics","champion_spawn 500","champion_spawn 10000");
    edit("replacements.mechanics","replace_fraction 12.0.0 812.0.0 0 3 any 1 60 1","replace_fraction 12.0.0 812.0.0 0 3 any 1 1 1");
    auto content=MechanicsLibrary::load(dir);int seen=0;std::set<int> kinds;
    for(int seed=0;seed<12;++seed) {
        Simulation a(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Growing,content);
        Simulation b(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,ExpeditionPacing::Growing,content);
        for(int room=1;room<a.finalRoom();++room){const auto &left=a.roomEnemies(room),&right=b.roomEnemies(room);check(left.size()==right.size(),"natural seeded resident count repeats");
            for(size_t n=0;n<left.size();++n)if(left[n].monster==monsterId(812)) {
                ++seen;check(left[n].champion>=0&&left[n].champion==right[n].champion,"real resident preparation selects repeatable SubHorf champions");
                check(content->champion(left[n].champion)->firstStage<=a.arena.profile.sourceStage,"natural selection respects source-stage gates");kinds.insert(left[n].champion);
            }
        }
    }
    std::filesystem::remove_all(dir);check(seen>0&&kinds.size()>1&&defaultMechanics()->championChance()==500,"natural fixtures preserve production5percent tuning");
    std::cout<<"SUB_HORF_CHAMPION_NATURAL seeds=12 residents="<<seen<<" distinct_types="<<kinds.size()<<" stage_gates=1 deterministic=1 production_chance_unchanged=1\n";
}
}
int main(){try{motionAndFire();deathAndCombinedEffects();replacement();championStats();championTrailsAndFields();championDeaths();championNatural();std::cout<<"PASS Sub Horf\n";return 0;}catch(const std::exception&e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
