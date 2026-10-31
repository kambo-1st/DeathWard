#include "combat/Simulation.hpp"
#include "items/Items.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
#include <chrono>
#include <filesystem>
#include <fstream>
using namespace dw;
namespace {
void check(bool ok, const char *message) {
    if (!ok)
        throw std::runtime_error(message);
}
Simulation fixture() {
    Simulation s(1866, 1, {});
    s.arena = Arena{};
    s.rooms.resize(s.arena.rooms.size());
    s.arena.bounds = {{-25, -1, -25}, {25, 4, 25}};
    s.arena.walls = {{{-26, -1, -26}, {-25, 5, 26}},
                     {{25, -1, -26}, {26, 5, 26}},
                     {{-26, -1, -26}, {26, 5, -25}},
                     {{-26, -1, 25}, {26, 5, 26}}};
    for (auto &r : s.arena.rooms) {
        r.bounds = s.arena.bounds;
        r.center = {0, 0, 0};
        r.floors = {{{-25, -.4f, -25}, {25, 0, 25}}};
    }
    s.player.position = {0, .85f, 8};
    s.debugScenario = true;
    s.roomClear = false;
    return s;
}
void tick(Simulation &s, int count) {
    for (int n = 0; n < count; ++n)
        s.step({});
}
void damage(Simulation &s, EntityId id, float amount, Vector3 direction = {0, 0, -1}, bool area = false,
            bool ignoreAdaptiveArmor = false) {
    Event e;
    e.type = EventType::Damage;
    e.target = id;
    e.damage = amount;
    e.direction = direction;
    e.areaDamage = area;
    e.ignoreAdaptiveArmor = ignoreAdaptiveArmor;
    s.queueRoot(e);
    s.drainEvents();
}
EntityId ready(Simulation &s, MonsterId id) {
    if(const auto *decoy=s.content->hornfelDecoy(id)) {
        const auto owner=decoy->owner;
        // Catalog smoke isolates component availability. Dedicated Hornfel and
        // passenger suites cover competition with live escorts and rail traffic.
        const auto path=std::filesystem::temp_directory_path()/("dw-decoy-smoke-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
        std::filesystem::create_directories(path);
        for(const auto &f:std::filesystem::directory_iterator(s.content->directory()))if(f.path().extension()==".mechanics") {
            std::ifstream in(f.path());std::string text((std::istreambuf_iterator<char>(in)),{});
            for(const auto &[from,to]:std::array<std::pair<std::string,std::string>,2>{{
                {"hornfel_escort 906.0.0 819.0.0 3 ","hornfel_escort 906.0.0 819.0.0 0 "},
                {"rail_traffic 906.0.0 1 ","rail_traffic 906.0.0 0 "}}})
                if(const auto at=text.find(from);at!=std::string::npos)text.replace(at,from.size(),to);
            std::ofstream(path/f.path().filename())<<text;
        }
        s.content=MechanicsLibrary::load(path);std::filesystem::remove_all(path);
        check(!s.spawnMonster(id,{0,.85f,0}),"decoy requires a live rail encounter");
        ready(s,owner);
        for(int frame=0;frame<12000;++frame) {
            s.step({});
            for(const auto &e:s.enemies)if(e.alive&&e.monster==id&&e.state!=EnemyState::Teleporting)return e.id;
        }
        throw std::runtime_error("native decoy action did not produce a component");
    }
    EntityId owner=0;
    if(const auto *component=s.content->component(id))owner=ready(s,component->owner);
    if(const auto *component=s.content->returningBody(id))owner=ready(s,component->owner);
    if(const auto *fly=s.content->flyBomb(id);fly&&fly->orbitOwner)owner=ready(s,fly->orbitOwner);
    auto entity = s.spawnMonster(id, {owner?4.f:0, .85f, 0},owner,owner?0:-1);
    check(entity!=0,"test actor must have a valid owning encounter when required");
    s.findEnemy(entity)->cooldown = 0;
    return entity;
}
void catalogAndSmoke() {
    std::set<MonsterId> ids;
    for (const auto &d : monsterCatalog()) {
        check(ids.insert(d.id).second, "monster IDs must be unique");
        auto s = fixture();
        s.godMode = true;
        if(s.content->linkedNeck(d.id)) {
            check(!s.spawnMonster(d.id,{0,.85f,0}),"visual neck cannot become an independent enemy");
            const auto owner=ready(s,monsterId(35));tick(s,120);
            check(s.findEnemy(owner)!=nullptr,"neck lifecycle is owned by a real body/head encounter");
            continue; // Dedicated linked_head suite validates the eight harmless pieces.
        }
        ready(s, d.id);
        tick(s, 420);
        for (const auto &e : s.enemies)
            check(std::isfinite(e.position.x) && std::isfinite(e.hp),
                  "every family simulates finite positions and health");
        check(s.enemies.size() <= s.limits.enemies && s.hazards.size() <= s.limits.hazards &&
                  s.projectiles.size() <= s.limits.projectiles,
              "all families respect effect budgets");
        s.clearRoomDebug();
        check(s.livingEnemies() == 0 && s.hazards.empty() && s.chains.empty(),
              "clear-room cheat cleans every monster family");
    }
    for (auto id : {monsterId(10), monsterId(10, 3), monsterId(25, 3, 1), monsterId(38, 1, 1),
                   monsterId(42, 2), monsterId(68, 10), monsterId(68, 11), monsterId(89)})
        check(ids.contains(id), "requested endpoints and multi-part variants are present");
    const auto *bloat = monsterDefinition(monsterId(68, 1));
    check(!bloat || bloat->name == "The Bloat", "68.1 is The Bloat, never the Peep Eye component");
    for (auto eye : {monsterId(68, 10), monsterId(68, 11)}) {
        const auto *d = monsterDefinition(eye);
        check(d && d->roomHazard && !d->natural,
              "boss eyes keep their installed IDs and require their owning encounter");
    }
    check(monsterIdText(monsterId(25, 3, 1)) == "25.3.1" && monsterIdText(monsterId(68, 11)) == "68.11",
          "variant IDs preserve decimal components");
    std::cout << "CATALOG " << ids.size() << " entries including offspring\n";
}
void gunsAndArmor() {
    auto s = fixture();
    auto id = ready(s, monsterId(12));
    for(int n=0;n<14&&s.findEnemy(id)->state!=EnemyState::Windup;++n)s.step({});
    check(s.findEnemy(id)->state == EnemyState::Windup && s.projectiles.empty(), "Horf warns before firing");
    tick(s, 8);
    check(s.stats.projectiles == 1, "Horf fires one actual projectile");
    int frames = 0;
    while (s.stats.projectiles < 2 && frames < 180) {
        tick(s, 1);
        ++frames;
    }
    check(frames == 56 && s.stats.projectiles == 2,
          "Horf repeats after28source frames including windup and recovery");
    check(s.player.hp == StartingHealth - 12.5f && s.stats.damageTaken == 12.5f,
          "Horf shots deal 25% more damage exactly once");
    auto c = fixture();
    ready(c, monsterId(15));
    tick(c, 36);
    check(c.stats.projectiles == 4, "Clotty fires four cardinal shots");
    auto host = fixture();
    id = host.spawnMonster(monsterId(27), {0, .85f, 0});
    damage(host, id, 20);
    check(std::abs(host.findEnemy(id)->hp-44.8f)<.001f, "closed Host shell blocks damage");
    for(int n=0;n<600&&!host.findEnemy(id)->host->exposed;++n)host.step({});
    check(host.findEnemy(id)->host->exposed,"Host reaches its source opening event after blocked-hit delay");
    damage(host, id, 20);
    check(std::abs(host.findEnemy(id)->hp-24.8f)<.001f, "raised Host exposes its body");
    auto knight = fixture();
    id = knight.spawnMonster(monsterId(41), {0, .85f, 0});
    knight.findEnemy(id)->facing = {0, 0, 1};
    damage(knight, id, 30, {0, 0, -1});
    check(knight.findEnemy(id)->hp == 64, "Knight blocks frontal shots");
    damage(knight, id, 30, {0, 0, 1});
    check(knight.findEnemy(id)->hp == 34, "Knight rear remains vulnerable");
    damage(knight, id, 30, {0, 0, -1}, true);
    check(knight.findEnemy(id)->hp == 4, "explosions bypass directional armor");
    auto reflect = fixture();
    id = reflect.spawnMonster(monsterId(41, 4), {0, .85f, 0});
    reflect.findEnemy(id)->facing = {0, 0, 1};
    damage(reflect, id, 20);
    check(reflect.projectiles.size() == 1 && reflect.projectiles[0].hostile,
          "Black Knight reflects a frontal shot");
}
void regenerationAndOffspring() {
    auto s = fixture();
    auto id = s.spawnMonster(monsterId(24), {0, .85f, 0});
    damage(s, id, 200);
    check(s.findEnemy(id)->alive && s.findEnemy(id)->state == EnemyState::Collapsed && s.stats.kills == 0,
          "Globin collapses before a true kill");
    tick(s, 160);
    check(s.findEnemy(id)->state != EnemyState::Collapsed && std::abs(s.findEnemy(id)->hp - 76.8f) < .001f,
          "ignored goo regenerates with reduced maximum health");
    damage(s, id, 200);
    damage(s, id, 200);
    check(!s.findEnemy(id)->alive && s.stats.kills == 1, "finishing the goo prevents regeneration");
    auto moter = fixture();
    id = moter.spawnMonster(monsterId(80), {0, .85f, 0});
    damage(moter, id, 72);
    moter.step({});
    check(moter.livingEnemies() == 2, "Moter produces two living Attack Flies");
    for (const auto &e : moter.enemies)
        check(e.monster == monsterId(18), "Moter children use the correct ID");
    auto limited = fixture();
    limited.limits.enemies = 2;
    id = limited.spawnMonster(monsterId(22, 3), {0, .85f, 0});
    // Isolate bounded offspring from armor reduction and use the source HP.
    damage(limited, id, limited.findEnemy(id)->maxHp, {0,0,-1}, false, true);
    tick(limited,2);
    check(limited.livingEnemies() <= 2 && limited.stats.suppressed > 0,
          "death summons are bounded and report suppression");
    auto room = fixture();
    room.debugScenario = false;
    room.rooms[0].cleared = false;
    id = room.spawnMonster(monsterId(80), {0, .85f, 0});
    damage(room, id, 72);
    room.step({});
    check(!room.roomClear && room.roomThreats() == 2, "offspring are present before the room-clear check");
    room.killAll();
    room.step({});
    check(room.roomClear && room.livingEnemies() == 0,
          "kill cheat also clears offspring without new summons");
    auto linked = fixture();
    id = linked.spawnMonster(monsterId(41, 3), {0, .85f, 0});
    const auto placedPon=linked.spawnMonster(monsterId(840),{2,.85f,0});
    linked.step({});
    check(linked.findEnemy(id),"Brainless Knight survives with an available Pon");
    auto pon = linked.findEnemy(id)->partner;
    check(pon==placedPon && linked.findEnemy(pon), "Brainless Knight adopts the nearest unclaimed Pon");
    damage(linked, pon, 200);
    linked.step({});
    check(!linked.findEnemy(id), "killing Pon removes its corresponding Knight");
}
void deathRulesAndRegrowth() {
    for (auto id : {monsterId(16),
                    monsterId(22), monsterId(22,1), monsterId(22,2), monsterId(22,3), monsterId(80)}) {
        const auto *rule=defaultMechanics()->deathRule(id);
        check(rule&&rule->overkill,"reviewed offspring families have explicit overkill policies");
        auto s=fixture();const auto entity=s.spawnMonster(id,{0,.85f,0});
        const auto maximum=s.findEnemy(entity)->hp;
        // Test the exact mortality boundary independently of adaptive scaling.
        damage(s,entity,maximum+*rule->overkill-1,{0,0,-1},false,true);
        damage(s,entity,1-2* *rule->overkill,{0,0,-1},false,true);
        tick(s,2);
        check(s.livingEnemies()==0,"inclusive overkill threshold suppresses offspring after accumulated damage");
    }
    auto gaper=fixture();int empty=0,pacer=0,gusher=0;
    for(int n=0;n<600;++n) {
        gaper.enemies.clear();
        const auto id=gaper.spawnMonster(monsterId(10,1),{0,.85f,0});
        damage(gaper,id,64);gaper.step({});
        check(gaper.livingEnemies()<=1,"Gaper produces at most one replacement");
        if(gaper.enemies.empty())++empty;
        for(const auto &e:gaper.enemies) {
            check(e.monster==monsterId(11)||e.monster==monsterId(11,1),"Gaper child identity");
            if(e.monster==monsterId(11,1))++pacer;else ++gusher;
        }
    }
    check(empty>240&&empty<360&&pacer>60&&pacer<140&&gusher>150&&gusher<250,
          "seeded sample exercises source 50% death / one-sixth Pacer / one-third Gusher weights");
    auto moter=fixture();auto id=moter.spawnMonster(monsterId(80),{0,.85f,0});
    damage(moter,id,72);moter.step({});
    check(moter.enemies.size()==2&&moter.enemies[0].position.x*moter.enemies[1].position.x<0&&
          std::abs(moter.enemies[0].position.z)<.01f&&std::abs(moter.enemies[1].position.z)<.01f,
          "Moter children split to either side of the player approach");
    for(int variant:{0,1}) {
        auto s=fixture();id=s.spawnMonster(monsterId(16,variant),s.player.position);
        tick(s,1);check(s.player.hp==StartingHealth,"Mulligan and Mulligoon cannot hurt by touching");
    }
    auto voluntary=fixture();id=voluntary.spawnMonster(monsterId(16),{0,.85f,5});
    voluntary.findEnemy(id)->evader=EvaderRuntime{};
    // Inject a late animation frame only after the native initialization state.
    voluntary.findEnemy(id)->evader->initialized=true;voluntary.findEnemy(id)->evader->lifeTicks=29;
    voluntary.findEnemy(id)->evader->detonationFrame=28;tick(voluntary,2);
    check(voluntary.livingEnemies()>=2&&voluntary.stats.projectiles==4,
          "voluntary detonation bypasses overkill suppression and adds a cardinal burst");
    auto shot=fixture();id=shot.spawnMonster(monsterId(16),{0,.85f,0});
    shot.findEnemy(id)->age=13;damage(shot,id,72);shot.step({});
    check(shot.stats.projectiles==0&&shot.livingEnemies()>=2,
          "ordinary late-life kill is not mistaken for self-detonation");
    auto drowned=fixture();id=drowned.spawnMonster(monsterId(22,1),{0,.85f,0});
    for(int frame=0;frame<120&&std::none_of(drowned.enemies.begin(),drowned.enemies.end(),[&](const auto &e){return e.summoner==id;});++frame)drowned.step({});
    auto offspring=std::find_if(drowned.enemies.begin(),drowned.enemies.end(),[&](const auto &e){return e.summoner==id;});
    check(offspring!=drowned.enemies.end()&&offspring->monster==monsterId(23,1)&&std::abs(offspring->hp-35.2f)<.001f&&std::abs(offspring->maxHp-35.2f)<.001f,
          "Drowned Hive attack summons have half normal Drowned Charger health");
    drowned.enemies.erase(std::remove_if(drowned.enemies.begin(),drowned.enemies.end(),[&](const auto &e){return e.id!=id;}),drowned.enemies.end());
    damage(drowned,id,112);drowned.step({});
    check(drowned.livingEnemies()>=1&&drowned.livingEnemies()<=2,"Drowned Hive death creates one or two children");
    for(const auto &e:drowned.enemies)check(std::abs(e.hp-35.2f)<.001f&&std::abs(e.maxHp-35.2f)<.001f,"death and attack offspring share half-health policy");
    auto cursed=fixture();cursed.godMode=true;id=cursed.spawnMonster(monsterId(24,3),{0,.85f,0});
    damage(cursed,id,112);cursed.step({});
    check(cursed.livingEnemies()==2&&cursed.stats.kills==0,"Cursed Globin splits into two threats without a kill reward");
    for(const auto &e:cursed.enemies)
        check(e.state==EnemyState::Collapsed&&std::abs(e.maxHp-78.4f)<.001f&&std::abs(e.hp-23.52f)<.001f,
              "both goo children receive the same reduction exactly once");
    tick(cursed,100);
    for(const auto &e:cursed.enemies)check(e.state!=EnemyState::Collapsed&&std::abs(e.hp-78.4f)<.001f,"both Cursed bodies regrow at reduced health");
    for(int cycle=0;cycle<4;++cycle) {
        std::vector<EntityId> ids;for(const auto &e:cursed.enemies)ids.push_back(e.id);
        for(auto other:ids)damage(cursed,other,200);
        cursed.step({});tick(cursed,100);
    }
    check(cursed.livingEnemies()==8,"external split limit bounds Cursed Globin multiplication across repeated regeneration");
    auto finish=fixture();finish.debugScenario=false;finish.rooms[0].cleared=false;
    id=finish.spawnMonster(monsterId(24),{0,.85f,0});damage(finish,id,96);finish.step({});
    check(!finish.roomClear&&finish.roomThreats()==1,"collapsed goo keeps the room sealed");
    damage(finish,id,50);finish.step({});check(finish.roomClear,"destroying final goo permits room completion");
}
void reviewedOpeningBehavior() {
    auto gusher=fixture();gusher.player.position={0,.85f,40};gusher.godMode=true;
    auto id=ready(gusher,monsterId(11));
    auto *body=gusher.findEnemy(id);body->velocity={-3,0,0};
    body->headless->initialized=true;body->headless->cooldown=0;
    tick(gusher,1);
    check(gusher.projectiles.size()==1,"Gusher can fire without acquiring a distant player");
    const auto &shot=gusher.projectiles.front();
    check(std::abs(shot.velocity.x+15)<.001f&&std::abs(shot.velocity.z)<.001f&&
          std::abs(shot.velocity.y-12)<.001f&&std::abs(shot.gravity-(.1f+.1f+.3f)*.05f*30*30)<.001f&&std::abs(shot.flightRetention-.9f)<.001f,
          "Gusher uses native speed5, falling modifiers and common base along movement, not player aim");
    for(int variant=0;variant<=1;++variant) {
        auto pooter=fixture();pooter.godMode=true;id=ready(pooter,monsterId(14,variant));
        pooter.findEnemy(id)->facing={1,0,0};pooter.findEnemy(id)->auxiliary=10;
        tick(pooter,42);
        check(pooter.stats.projectiles==uint64_t(variant+1),"Pooter fires one shot; Super Pooter fires two");
        const auto at=pooter.findEnemy(id)->position;
        check(planarDistance(at,{0,.85f,0})>.01f&&pooter.findEnemy(id)->buzz.has_value(),"Pooter variants use shared buzzing movement");
        if(variant)check(pooter.projectiles[0].velocity.x*pooter.projectiles[1].velocity.x<0,
                         "Super Pooter's pair forms a V around the acquired direction");
    }
    auto pacer=fixture();pacer.godMode=true;id=ready(pacer,monsterId(11,1));
    body=pacer.findEnemy(id);body->velocity={-3,0,0};body->headless->initialized=true;
    body->headless->targetReady=true;body->headless->destination={-20,.85f,0};
    tick(pacer,120);
    check(pacer.findEnemy(id)->position.x< -3&&pacer.projectiles.empty(),"Pacer wanders without firing");
    auto flaming=fixture();flaming.godMode=true;ready(flaming,monsterId(10,2));tick(flaming,120);
    check(flaming.hazards.empty(),"Flaming Gaper does not invent a damaging fire trail");
}
void rottenGapers() {
    // Exact force/timing/ownership contracts live in rotten_gaper_family.
    // This general suite checks public spawn/update integration for every subtype.
    for(int sub=0;sub<=5;++sub) {
        auto s=fixture();s.godMode=true;
        const auto id=ready(s,monsterId(10,3,sub));tick(s,60);
        const auto *e=s.findEnemy(id);
        check(e&&e->rottenGaper&&e->rottenGaper->initialized,"Rotten uses dedicated source-timed controller");
        check(sub?e->monster.subtype==sub:(e->monster.subtype>=1&&e->monster.subtype<=5),"Rotten subtype dispatch preserves explicit identities");
        check(s.stats.projectiles==0&&s.hazards.empty(),"Rotten has no invented ranged attack or damaging trail");
    }
}
void rottenStartingKit() {
    for(int subtype=1;subtype<=5;++subtype) {
        auto s=fixture();s.debugScenario=false;s.rooms[0].cleared=false;
        s.spawnMonster(monsterId(10,3,subtype),{0,.85f,0});
        if(subtype==3)s.player.position={0,.85f,20};
        int frames=0;size_t peak=0;bool firing=subtype!=3;
        for(;frames<1200&&!s.dead&&!s.roomClear;++frames) {
            const Enemy *target=nullptr;
            for(const auto &e:s.enemies)if(e.alive&&(!target||distance(e.position,s.player.position)<distance(target->position,s.player.position)))target=&e;
            check(target,"uncleared test encounter retains a target");
            // Engage active pursuers immediately. For brood, allow two actual
            // births before attacking, while using the starting kit's dodge.
            firing|=s.roomThreats()>=3||frames>=300;
            Input in;in.fire=firing;
            in.dodge=distance(target->position,s.player.position)<2.2f;
            // Solve the actual starting projectile's intercept time. The old
            // distance/30 estimate trails a fast tangential target indefinitely.
            const auto delta=horizontal(sub(target->position,s.player.position)),v=horizontal(target->velocity);
            const float speed=playerAttack(s,s.player.shotDamage,false).speed;
            const float a=dot(v,v)-speed*speed,b=2*dot(delta,v),c=dot(delta,delta),disc=b*b-4*a*c;
            float flight=length(delta)/speed;
            if(disc>=0&&std::abs(a)>.0001f) {
                const float t1=(-b-std::sqrt(disc))/(2*a),t2=(-b+std::sqrt(disc))/(2*a);
                if(t1>0)flight=t1;
                if(t2>0)flight=std::min(flight,t2);
            }
            in.aim=add(target->position,mul(v,flight));
            const auto away=unit(sub(s.player.position,target->position));
            in.movement=distance(target->position,s.player.position)<5?away:Vector3{};
            s.step(in);peak=std::max(peak,s.roomThreats());
        }
        std::cout<<"ROTTEN_STARTING_KIT subtype="<<subtype<<" seconds="<<frames*Tick<<" hp="<<s.player.hp<<" peak="<<peak<<'\n';
        check(s.roomClear&&!s.dead&&s.player.hp>0&&frames<1200,"starting revolver clears activated Rotten encounter and children without items/bombs/god mode");
        if(subtype==3)check(peak>=3,"brood balance check includes live summons before player firing begins");
    }
}
void groundBodySpacing() {
    auto brood=fixture();brood.godMode=true;
    const auto parent=ready(brood,monsterId(10,3,3));
    float playerGap=100,bodyGap=100;
    for(int frame=0;frame<1200;++frame) {
        brood.step({});
        for(size_t i=0;i<brood.enemies.size();++i) {
            const auto &a=brood.enemies[i];
            const bool newborn=a.smallMaggot&&a.smallMaggot->ticks==0;
            if(!newborn)playerGap=std::min(playerGap,distance(a.position,brood.player.position)-a.radius);
            check(!brood.arena.blocked(a.position,a.radius),"ground contact resolution stays on navigable floor");
            for(size_t j=i+1;j<brood.enemies.size();++j) {
                const auto &b=brood.enemies[j];
                // Native brood birth overlaps its parent. Check spacing once
                // each child has received a source update and body resolution.
                if(!newborn&&!(b.smallMaggot&&b.smallMaggot->ticks==0))
                    bodyGap=std::min(bodyGap,distance(a.position,b.position)-a.radius-b.radius);
            }
        }
    }
    std::cout<<"GROUND_BROOD player_gap="<<playerGap<<" body_gap="<<bodyGap<<" threats="<<brood.roomThreats()<<'\n';
    check(brood.roomThreats()==7&&brood.findEnemy(parent),"spacing preserves the complete brood and its ownership cap");
    check(playerGap>=.47f&&bodyGap>=-.025f,"pursuers and all six children keep distinct physical bodies around player");
    check(std::any_of(brood.enemies.begin(),brood.enemies.end(),[](const auto &e){return e.monster==monsterId(853)&&std::abs(e.position.x)>.4f;}),
          "children steer around the parent rather than queue on the same centre line");

    auto repeated=fixture();repeated.godMode=true;ready(repeated,monsterId(10,3,3));tick(repeated,1200);
    check(repeated.enemies.size()==brood.enemies.size(),"same seed retains identical brood size");
    for(size_t i=0;i<brood.enemies.size();++i)
        check(distance(repeated.enemies[i].position,brood.enemies[i].position)<.00001f,
              "ground steering and resolution are deterministic without consuming combat RNG");

    for(bool dodge:{false,true}) {
        auto s=fixture();s.player.position={-4,.85f,0};
        for(int n=-1;n<=1;++n) {
            const auto id=s.spawnMonster(monsterId(10,1),{0,.85f,float(n)*1.3f});
            s.findEnemy(id)->state=EnemyState::Stunned;s.findEnemy(id)->stateTime=10;
        }
        Input in;in.movement={1,0,0};in.aim={8,.85f,0};
        for(int n=0;n<60;++n){in.dodge=dodge&&n==24;s.step(in);}
        check(s.player.position.x>1.9f,"walking and dodging through a crowd remain under player control");
        if(dodge)check(s.player.hp==StartingHealth,"dodge still protects against grounded contact");
    }
    auto touch=fixture();ready(touch,monsterId(10,1));tick(touch,200);
    check(touch.player.hp<StartingHealth&&touch.player.hp>0,"contact skin does not make pursuing enemies harmless");

    for(const auto kind:{monsterId(10,1),monsterId(10,3,4)}) {
    auto wall=fixture();wall.godMode=true;wall.player.position={0,.85f,8};
    // A narrow passage forces bodies to queue, then separate after the opening.
    wall.arena.walls.push_back({{-25,-1,2},{-1,5,3}});
    wall.arena.walls.push_back({{1,-1,2},{25,5,3}});
    for(int n=0;n<5;++n)wall.spawnMonster(kind,{float(n-2)*1.3f,.85f,-2});
    for(int frame=0;frame<800;++frame) {
        wall.step({});
        for(const auto &e:wall.enemies)
            check(!wall.arena.blocked(e.position,e.radius),"crowd corrections never push bodies through walls or sealed passages");
    }
    for(const auto &e:wall.enemies)std::cout<<"GROUND_PASSAGE type="<<monsterIdText(kind)<<" entity="<<e.id<<" x="<<e.position.x<<" z="<<e.position.z<<" waypoints="<<e.path.size()<<" waypoint="<<(e.path.empty()?0:e.path.front().x)<<','<<(e.path.empty()?0:e.path.front().z)<<'\n';
    check(std::count_if(wall.enemies.begin(),wall.enemies.end(),[](const auto &e){return e.position.z>3.6f;})==5,
          "ground steering allows every pursuer through a narrow opening");
    }

    auto stationary=fixture();stationary.godMode=true;
    const auto horf=ready(stationary,monsterId(12));
    stationary.spawnMonster(monsterId(10,1),{0,.85f,-1.25f});tick(stationary,240);
    check(distance(stationary.findEnemy(horf)->position,{0,.85f,0})<.00001f,"stationary shooters are not shoved around by pursuit steering");
}
void hazardsAndCover() {
    auto s = fixture();
    s.debugScenario = false;
    s.rooms[0].cleared = false;
    const auto grimace = ready(s, monsterId(42));
    const auto victim = s.spawn(EnemyKind::Rusher, {5, .85f, 0});
    damage(s, grimace, 1000);
    check(s.findEnemy(grimace)->alive && s.roomThreats() == 1,
          "Grimace is invulnerable but not a room objective");
    damage(s, victim, 1000);
    s.step({});
    check(s.roomClear && s.roomThreats() == 0 && s.hazards.empty(),
          "room opens with only an invulnerable hazard left");
    for (bool wall : {false, true}) {
        auto beam = fixture();
        auto id = ready(beam, monsterId(39));
        // Isolate cover from cardinal wandering: commit the lane through the
        // stationary target. Source Vis can otherwise drift sideways and miss.
        auto &caster=*beam.findEnemy(id);
        caster.vis->initialized=true;caster.vis->heading={0,0,1};
        caster.vis->attackFrame=beam.content->vis(caster.monster)->shootFrame-1;
        caster.velocity={};
        beam.step({});
        if (wall)
            beam.arena.walls.push_back({{-3, 0, 4}, {3, 4, 5}});
        tick(beam, 100);
        check((beam.player.hp < StartingHealth) == !wall, "laser damage is clipped by solid cover");
        beam.findEnemy(id)->state = EnemyState::Stunned;
        beam.findEnemy(id)->stateTime = 100;
        tick(beam, 180);
        check(beam.chains.empty(), "laser effects release their chain ownership");
    }
    auto dodge = fixture();
    ready(dodge, monsterId(39));
    // Wait for the real Shoot event; Vis no longer has the old extra .4s
    // laser warning. Arming dodge after a hard-coded70 frames starts too late.
    dodge.godMode=true;
    for(int frame=0;frame<200&&dodge.hazards.empty();++frame)tick(dodge,1);
    check(!dodge.hazards.empty(),"dodge fixture reaches an actual Vis beam");
    dodge.godMode=false;
    dodge.player.dodge = 2;
    dodge.player.dodgeDirection = {};
    tick(dodge, 40);
    check(dodge.player.hp == StartingHealth, "dodge protects against an active beam");
    auto bomb = fixture();
    bomb.godMode=true;
    auto id = ready(bomb, monsterId(87));
    for(int frame=0;frame<1200&&bomb.projectiles.empty();++frame)bomb.step({});
    check(!bomb.projectiles.empty()&&bomb.hazards.empty(),"Gurgle creates a physical explosive lob");
    const Vector3 zone{0,.85f,0};
    bomb.projectiles.front().position={0,.36f,0};bomb.projectiles.front().velocity={0,-1,0};
    bomb.findEnemy(id)->position = zone;
    bomb.findEnemy(id)->state = EnemyState::Stunned;
    bomb.findEnemy(id)->stateTime = 10;
    auto other = bomb.spawn(EnemyKind::Ironhide, add(zone, {1, 0, 0}));
    bomb.findEnemy(other)->state = EnemyState::Stunned;
    bomb.findEnemy(other)->stateTime = 10;
    tick(bomb, 10);
    check(bomb.findEnemy(id)->hp == bomb.findEnemy(id)->maxHp && (!bomb.findEnemy(other)||bomb.findEnemy(other)->hp < 144),
          "Gurgle blast spares its source and damages other enemies");
}
void movementAndProjectiles() {
    auto chase = fixture();
    const auto gaper = chase.spawnMonster(monsterId(10, 1), {0, .85f, 0});
    chase.player.position={0,.85f,24};
    tick(chase,2);
    check(std::abs(chase.findEnemy(gaper)->velocity.z-2.988f)<.001f,
          "Gaper begins with source force .498 times gain2 and world speed scale3");
    chase.player.position = add(chase.findEnemy(gaper)->position, {0, 0, .75f});
    tick(chase, 1);
    check(chase.player.hp == StartingHealth - 10*EnemyDamageMultiplier, "Gaper uses its source-adapted contact damage");
    tick(chase, 10);
    check(chase.player.hp == StartingHealth - 10*EnemyDamageMultiplier, "contact damage still respects hurt invulnerability");
    auto mirror = fixture();
    auto id = mirror.spawnMonster(monsterId(53), {0, .85f, 0});
    tick(mirror,4); // Source initialization consumes one native frame.
    Input input;
    input.movement = {1, 0, 0};
    input.fire = true;
    input.aim = {0, .85f, -8};
    mirror.step(input);
    mirror.step(input); // Mirror attack decisions sample the source30Hz clock.
    check(mirror.findEnemy(id)->position.x < 0 && mirror.stats.projectiles == 2,
          "Dople mirrors actual movement and fired shots");
    auto split = fixture();
    ready(split, monsterId(14, 2));
    tick(split, 32);
    check(split.projectiles.size() == 4, "Tainted Pooter starts with four splitting shots");
    for (auto &p : split.projectiles)
        p.life = 0;
    split.step({});
    check(split.stats.projectiles == 4 && split.projectiles.empty(), "safety timeout does not imitate a physical split impact");
    auto terrain = fixture();
    terrain.godMode = true;
    terrain.arena.walls.push_back({{-2, 0, 3}, {2, 4, 4}});
    id = ready(terrain, monsterId(23));
    tick(terrain, 180);
    check(!terrain.arena.blocked(terrain.findEnemy(id)->position, .6f),
          "charging monsters respect obstacle collision");
    auto burrow = fixture();
    id = ready(burrow, monsterId(58));
    tick(burrow, 2);
    check(burrow.findEnemy(id)->state == EnemyState::Buried, "Para-Bite burrows");
    auto hp = burrow.findEnemy(id)->hp;
    damage(burrow, id, 1000);
    check(burrow.findEnemy(id)->hp == hp, "buried enemies cannot be shot");
    tick(burrow, 70);
    check(!burrow.arena.blocked(burrow.findEnemy(id)->position, .6f), "burrowing returns to valid terrain");
}
void referenceCorrections() {
    auto bulb = fixture();
    const auto bulbId = bulb.spawnMonster(monsterId(61, 5), bulb.player.position);
    tick(bulb, 12);
    check(bulb.player.hp == StartingHealth && bulb.player.dodgeCooldown == 0,
          "Bulb has no health or dodge-drain effect when no active item exists");
    const auto facing = bulb.findEnemy(bulbId)->facing;
    check(std::abs(facing.x) < .001f || std::abs(facing.z) < .001f,
          "harmless Bulbs wander along right-angled directions");

    auto sucker = fixture();
    const auto id = sucker.spawnMonster(monsterId(61, 7), sucker.player.position);
    tick(sucker, 12);
    check(sucker.player.hp == StartingHealth, "Tainted Sucker never deals contact damage");
    sucker.findEnemy(id)->position = {0, .85f, 0};
    damage(sucker, id, 1000);
    tick(sucker,2); // Source armor batches damage before ordinary death effects.
    check(sucker.projectiles.size() == 6, "Tainted Sucker death creates six parent projectiles");
    for (const auto &p : sucker.projectiles)
        check(p.bounces == 1 && p.kind == ProjectileKind::BurstShot,
              "Tainted Sucker parents can bounce before splitting");
    sucker.projectiles.front().position = {24, .85f, 0};
    tick(sucker, 12);
    check(sucker.stats.bounces > 0 && sucker.projectiles.front().velocity.x < 0,
          "Tainted Sucker's projectile actually reflects off cover");
    for (auto &p : sucker.projectiles)
        p.life = 0;
    sucker.step({});
    check(sucker.stats.projectiles == 42, "six parent projectiles each split into six children");

    auto eggy = fixture();
    auto egg = eggy.spawnMonster(monsterId(29, 2), {0, .85f, 0});
    damage(eggy, egg, 1000);
    check(eggy.findEnemy(egg)->dyingEggy() && eggy.livingEnemies() == 1,
          "Eggy's lethal hit begins a timed husk rather than instant legacy children");
    tick(eggy, 139);
    check(eggy.findEnemy(egg) && eggy.findEnemy(egg)->eggy->released == 14,
          "Eggy releases all fourteen children before Die70 removes its body");
    eggy.step({});
    check(!eggy.findEnemy(egg) && eggy.livingEnemies() == 14,
          "Eggy's completed death leaves fourteen configured Swarm Spiders");
    for (const auto &e : eggy.enemies)
        check(e.monster == monsterId(884) && eggy.content->swarmSpider(e.monster) &&
                  std::abs(e.radius-monsterDefinition(monsterId(85))->radius)<.001f,
              "Eggy spawns dedicated Swarm Spiders; both source spiders have radius 13 despite smaller Swarm art");
    bool hopped = false;
    for (int frame = 0; frame < 180; ++frame) {
        eggy.step({});
        hopped |=
            std::any_of(eggy.enemies.begin(), eggy.enemies.end(), [](const Enemy &e) { return e.lift > 0; });
    }
    check(hopped, "Swarm Spiders hop while approaching the player");

    auto spawner = fixture();
    spawner.godMode = true;
    const auto hive = spawner.spawnMonster(monsterId(22, 3), {0, .85f, 0});
    for (int n = 0; n < 5; ++n) {
        const auto child = spawner.spawnMonster(monsterId(222), {float(n) * 2 - 4, .85f, -3});
        spawner.findEnemy(child)->summoner = hive;
    }
    spawner.findEnemy(hive)->state = EnemyState::Windup;
    spawner.findEnemy(hive)->stateTime = 0;
    spawner.step({});
    check(std::count_if(spawner.enemies.begin(), spawner.enemies.end(),
                        [hive](const Enemy &e) { return e.alive && e.summoner == hive; }) == 6,
          "a partly occupied summon group never exceeds its six-child limit");
}
} // namespace
int main() {
    try {
        catalogAndSmoke();
        gunsAndArmor();
        regenerationAndOffspring();
        deathRulesAndRegrowth();
        reviewedOpeningBehavior();
        rottenGapers();
        rottenStartingKit();
        groundBodySpacing();
        hazardsAndCover();
        movementAndProjectiles();
        referenceCorrections();
        std::cout << "PASS monster roster, armor, regeneration, summons, linked deaths, room hazards, beams, "
                     "collision and projectiles\n";
    } catch (const std::exception &e) {
        std::cerr << "FAIL: " << e.what() << '\n';
        return 1;
    }
}
