#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
bool near(float a,float b){return std::abs(a-b)<.003f;}
struct Pack {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("dw-hornfel-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());
        // These fixtures isolate the boss/decoy/escort controllers. Passenger
        // integration uses a separate suite with its own seeded contracts.
        replace("rail_traffic 906.0.0 1 ","rail_traffic 906.0.0 0 ","rail_passengers.mechanics");}
    ~Pack(){std::filesystem::remove_all(path);}
    void replace(const std::string &from,const std::string &to,const char *name="hornfel.mechanics") {
        const auto p=path/name;std::ifstream in(p);std::string s((std::istreambuf_iterator<char>(in)),{});
        const auto at=s.find(from);check(at!=std::string::npos,"editable test row exists");s.replace(at,from.size(),to);std::ofstream(p)<<s;
    }
    void noEscorts(){replace("hornfel_escort 906.0.0 819.0.0 3","hornfel_escort 906.0.0 819.0.0 0");}
    auto escort(float clearance=0) {
        replace("hornfel_decoy 906.1.0 906.0.0 1250","hornfel_decoy 906.1.0 906.0.0 0");
        replace("hornfel_charge 906.0.0 1250","hornfel_charge 906.0.0 0");
        replace("hornfel_escort 906.0.0 819.0.0 3 2 4 24","hornfel_escort 906.0.0 819.0.0 1 2 4 "+std::to_string(clearance));
        return MechanicsLibrary::load(path);
    }
    auto action(int n) {
        noEscorts();
        auto p=path/"hornfel.mechanics";std::ifstream in(p);std::string s((std::istreambuf_iterator<char>(in)),{});
        const std::string old="3 1 1 6 3 1";const auto at=s.find(old);check(at!=std::string::npos,"action fixture exists");
        s.replace(at,old.size(),n==0?"1 0 0 1 0 0":n==1?"0 1 0 1 0 0":"0 0 1 1 0 0");
        const std::string decoy="hornfel_decoy 906.1.0 906.0.0 1250";s.replace(s.find(decoy),decoy.size(),"hornfel_decoy 906.1.0 906.0.0 0");
        const std::string charge="hornfel_charge 906.0.0 1250";s.replace(s.find(charge),charge.size(),"hornfel_charge 906.0.0 0");std::ofstream(p)<<s;
        return MechanicsLibrary::load(path);
    }
    auto decoy() {
        noEscorts();
        const auto p=path/"hornfel.mechanics";std::ifstream in(p);std::string s((std::istreambuf_iterator<char>(in)),{});
        const std::string old="hornfel_decoy 906.1.0 906.0.0 1250 2 3 3.33333333 5";
        s.replace(s.find(old),old.size(),"hornfel_decoy 906.1.0 906.0.0 10000 2 3 3.33333333 0");std::ofstream(p)<<s;
        return MechanicsLibrary::load(path);
    }
    auto charge(int chance=10000) {
        noEscorts();
        const auto p=path/"hornfel.mechanics";std::ifstream in(p);std::string s((std::istreambuf_iterator<char>(in)),{});
        const std::string decoy="hornfel_decoy 906.1.0 906.0.0 1250";s.replace(s.find(decoy),decoy.size(),"hornfel_decoy 906.1.0 906.0.0 0");
        const std::string old="hornfel_charge 906.0.0 1250";
        s.replace(s.find(old),old.size(),"hornfel_charge 906.0.0 "+std::to_string(chance));std::ofstream(p)<<s;
        return MechanicsLibrary::load(path);
    }
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics(),std::string layout="hornfel_special_5220") {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.arena.bounds={{-40,-1,-40},{180,6,80}};s.arena.rooms.resize(2);
    s.arena.profile.bossRails=std::make_shared<RailLayout>(*lib->railLayout(layout));
    const auto &r=*s.arena.profile.bossRails;
    for(int i=0;i<2;++i) {
        auto &room=s.arena.rooms[size_t(i)];room.bounds={{float(i)*120-r.width*2.f,0,-r.height*2.f},{float(i)*120+r.width*2.f,4,r.height*2.f}};
        room.center=room.entry=room.objective=room.reward=room.bossSpawn={float(i)*120,.85f,0};room.exit=add(room.center,{0,0,3});room.kind=RoomKind::Combat;
        room.floors={room.bounds};room.floors[0].min.y=-.4f;room.floors[0].max.y=0;
    }
    s.rooms.assign(2,{});s.room=0;s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.enemyBombs.clear();s.pendingEnemyBombs.clear();s.stats={};
    s.player.position={0,.85f,0};s.godMode=true;s.debugScenario=true;s.roomClear=false;s.bossKilled=false;
    s.arena.prepareRailArena(0);check(s.spawnMonster(monsterId(906),{0,.85f,0})!=0,"Hornfel root creates cart and doors");return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
void hit(Simulation &s,EntityId id,float damage,bool debug=false) {Event e;e.type=EventType::Damage;e.target=id;e.damage=damage;e.debugExecution=e.execution=debug;s.queueRoot(e);s.drainEvents();}
void riding(Simulation &s) {for(int i=0;i<180&&!s.rooms[0].hornfel->cart.visible;++i)tick(s);check(s.rooms[0].hornfel->cart.visible,"door admits live cart");}
EntityId liveDecoy(Simulation &s) {
    for(int n=0;n<6000;++n) {
        for(const auto &d:s.rooms[0].hornfel->decoys)if(d.actor&&!d.finished&&d.cart.visible)return d.actor;
        tick(s);
    }
    throw std::runtime_error("decoy action never produced a visible rider");
}
void decoys() {
    for(const auto layout:{"hornfel_special_5220","hornfel_special_5228"}) {
        Pack p;auto s=fixture(p.decoy(),layout);const auto id=liveDecoy(s);auto &h=*s.rooms[0].hornfel;
        check(!s.spawnMonster(monsterId(906,1),{}),"decoys cannot be independently spawned into ordinary rooms");
        check(h.state==HornfelState::DecoyRun&&h.decoysSpawned>=1&&h.decoysSpawned<=(layout==std::string("hornfel_special_5220")?2:3),"source small/large attempts use only available routes");
        std::set<int> reservations;
        const auto &main=s.arena.rails->paths[size_t(h.cart.route)];reservations.insert(main.entry);reservations.insert(main.exit);
        for(const auto &d:h.decoys) {
            const auto &route=s.arena.rails->paths[size_t(d.cart.route)];
            check(!reservations.contains(route.entry)&&!reservations.contains(route.exit),"riders reserve both paired door endpoints");
            reservations.insert(route.entry);reservations.insert(route.exit);
        }
        const auto pos=s.findEnemy(id)->position;const auto travel=h.decoys.front().cart.distance;
        s.enterRoom(1);s.player.position={120,.85f,0};tick(s,120);s.enterRoom(0);s.player.position={0,.85f,0};
        check(distance(pos,s.findEnemy(id)->position)<.001f&&near(travel,h.decoys.front().cart.distance),"inactive-room round trip preserves decoy position and route");
        const auto kills=s.stats.kills;
        // Exit-lifetime fixture deliberately stays away from all rail contacts.
        s.player.position={0,.85f,35};
        hit(s,h.owner,10000,true);check(h.completed,"owner can finish with independent decoys on rails");
        const auto money=s.moneyPickups.size();
        tick(s,1600);
        check(h.decoysRemoved==h.decoysSpawned&&h.decoysDestroyed==0&&h.decoys.empty(),"every surviving decoy exits once without blast or respawn");
        check(s.stats.kills==kills+1&&s.moneyPickups.size()==money,"decoys have no independent kills or loot");
    }
    {
        Pack p;auto s=fixture(p.decoy());const auto id=liveDecoy(s);auto &h=*s.rooms[0].hornfel;
        s.player.position=s.findEnemy(id)->position;s.godMode=false;
        const float before=s.player.hp;tick(s);
        check(!s.findEnemy(id),"walking into a decoy consumes its body");
        check(near(before-s.player.hp,25),"whole-heart contact uses existing hostile conversion once");
        tick(s);check(h.decoysDestroyed==1&&s.enemyBombs.size()==6,"contact death uses the same once-only blast and six-bomb aftermath");
    }
    {
        Pack p;auto low=fixture(p.decoy());const auto id=liveDecoy(low);auto high=low;
        hit(low,id,32);hit(high,id,32.01f);
        check(low.findEnemy(id)->hp>=2&&low.findEnemy(id)->hp<=3,"damage equal to ten source units consumes one or two points");
        check(near(low.findEnemy(id)->hp-high.findEnemy(id)->hp,1),"strictly greater than ten consumes one additional point with same RNG");
        auto projectile=low;Event shot;shot.damage=24;shot.position=shot.origin=projectile.findEnemy(id)->position;
        shot.direction=projectile.findEnemy(id)->facing;shot.speed=26;projectile.queueRoot(shot);projectile.drainEvents();tick(projectile);
        check(!projectile.findEnemy(id)||projectile.findEnemy(id)->hp<low.findEnemy(id)->hp,"ordinary projectile collision reaches decoy hit-count handler");
        const auto hp=low.findEnemy(id)->hp;hit(low,id,0);check(near(low.findEnemy(id)->hp,hp),"zero damage never consumes hit health");
        for(int n=0;n<3&&low.findEnemy(id)->alive;++n)hit(low,id,1);
        check(!low.findEnemy(id)->alive&&low.stats.kills==0,"small hits destroy decoy after hit-count health without boss reward");
    }
    {
        Pack p;auto s=fixture(p.decoy());const auto id=liveDecoy(s);auto &h=*s.rooms[0].hornfel;
        // Move this visible rail body away from entry cover for a controlled blast fixture.
        s.findEnemy(id)->position={0,1.1f,0};
        const auto owner=h.owner;const auto ownerHp=s.findEnemy(owner)->hp;
        Event weak;weak.type=EventType::Damage;weak.target=id;weak.damage=1;
        Event blast=weak;blast.explosionDamage=true;
        auto rng=s.combatRng;s.queueRoot(weak);s.queueRoot(blast);s.drainEvents();
        check(!s.findEnemy(id)->alive&&s.combatRng.bounded(9999)==rng.bounded(9999),"explosion flag kills before any weak-hit RNG in the complete batch");
        s.limits.enemyBombs=s.limits.pendingEnemyBombs=0;tick(s);
        const auto &pending=*std::find_if(h.decoys.begin(),h.decoys.end(),[&](const auto &d){return d.actor==id;});
        const auto velocities=pending.bombVelocities;tick(s,30);
        check(h.decoysDestroyed==0&&s.enemyBombs.empty()&&velocities.size()==6,"six-bomb ring and direct blast wait together under capacity pressure");
        const auto &still=*std::find_if(h.decoys.begin(),h.decoys.end(),[&](const auto &d){return d.actor==id;});
        for(size_t i=0;i<velocities.size();++i)check(distance(velocities[i],still.bombVelocities[i])<.001f,"capacity retry does not reroll velocities");
        const auto victim=s.spawnMonster(monsterId(10),{2,1.1f,0});s.findEnemy(victim)->hp=s.findEnemy(victim)->maxHp=1000;
        s.arena.walls.push_back({{.8f,0,-2},{1.2f,4,2}});
        s.limits.enemyBombs=128;s.limits.pendingEnemyBombs=256;tick(s);
        check(h.decoysDestroyed==1&&s.enemyBombs.size()==6,"single admission emits immediate blast plus six actual bombs");
        check(near(s.findEnemy(victim)->hp,648),"source lineCheck=false direct blast crosses intervening cover");
        check(near(s.findEnemy(owner)->hp,ownerHp),"direct blast does not damage real Hornfel");
        std::set<EntityId> ids;
        for(const auto &bomb:s.enemyBombs) {
            check(bomb.source==id&&bomb.sourceMonster==monsterId(906,1)&&bomb.ordnance==monsterId(4,3)&&bomb.blastIgnore==owner,"bomb identity and separate parent immunity survive erased producer");
            ids.insert(bomb.id);
        }
        check(ids.size()==6,"all six bombs have distinct ordnance identities");
        hit(s,owner,10000,true);tick(s,180);
        check(h.decoysDestroyed==1&&s.enemyBombs.empty()&&s.pendingEnemyBombs.empty(),"fused bombs resolve once after producer and boss are gone");
    }
    {
        Pack p;auto s=fixture(p.decoy());liveDecoy(s);auto &h=*s.rooms[0].hornfel;
        s.player.position={0,.85f,35};s.limits.enemies=3;s.limits.enemyBombs=s.limits.pendingEnemyBombs=0;
        for(int frame=0;frame<2400;++frame) {
            for(const auto &e:s.enemies)if(e.alive&&s.content->hornfelDecoy(e.monster)&&e.state!=EnemyState::Teleporting) {
                Event hit;hit.type=EventType::Damage;hit.target=e.id;hit.damage=1;hit.explosionDamage=true;s.queueRoot(hit);
            }
            s.drainEvents();tick(s);
            check(h.decoys.size()<=3,"blocked destruction cannot accumulate unbounded component records across passes");
        }
        check(h.decoys.size()==3&&h.decoysDestroyed==0,"component budget retains three unadmitted deaths without losing them");
        s.limits.enemyBombs=128;s.limits.pendingEnemyBombs=256;tick(s);
        const auto emitted=std::count_if(s.enemyBombs.begin(),s.enemyBombs.end(),[](const auto &bomb){return bomb.sourceMonster==monsterId(906,1);});
        check(h.decoysDestroyed==3&&emitted==18,"capacity release admits each preserved six-bomb salvo exactly once");
    }
    std::cout<<"HORNFEL_DECOYS reservations=2 lifecycle=2 hit_rules=4 projectile_hit=1 contact_death=1 atomic_payload=1 retained_death_cap=1 cover_bypass=1\n";
}
void configuration() {
    const std::string charge="hornfel_charge 906.0.0 1250 10 6 8 .1 1.3 .8 .1 .08 30 40 .5 .1 5";
    const std::string recovery="hornfel_recovery 906.0.0 6 .75 .8 .1 1.2 .033333334 1.1 12 .2 10 6 12 .45 2.5 10";
    auto replace=[](Pack &p,const std::string &from,const std::string &to) {
        const auto file=p.path/"hornfel.mechanics";std::ifstream in(file);std::string data((std::istreambuf_iterator<char>(in)),{});
        const auto at=data.find(from);check(at!=std::string::npos,"configuration fixture matches authored row");
        data.replace(at,from.size(),to);std::ofstream(file)<<data;
    };
    auto bad=[&](const std::string &from,const std::string &to) {
        Pack p;replace(p,from,to);bool rejected=false;
        try{MechanicsLibrary::load(p.path);}catch(const std::exception &){rejected=true;}
        check(rejected,"malformed charge/recovery data must be rejected before running");
    };
    bad(charge,"");bad(recovery,"");bad(charge,charge+'\n'+charge);bad(recovery,recovery+'\n'+recovery);
    bad("1250 10 6 8 .1","1250 10 8 6 .1");
    bad("6 8 .1 1.3 .8 .1","6 8 .1 1.3 1 .1");
    bad("10 6 12 .45 2.5 10","10 0 12 .45 2.5 10");
    bad("10 6 12 .45 2.5 10","10 nan 12 .45 2.5 10");
    bad("6 .75 .8 .1 1.2","6 .75 2 .1 1.2");
    const std::string escort="hornfel_escort 906.0.0 819.0.0 3 2 4 24 .6 20 11.2";
    bad(escort,"");bad(escort,escort+'\n'+escort);
    bad("819.0.0 3 2 4 24","819.1.0 3 2 4 24");
    bad("24 .6 20 11.2","24 .6 20 100");bad("24 .6 20 11.2","24 nan 20 11.2");
    Pack p;auto first=MechanicsLibrary::load(p.path);auto live=fixture(first);
    replace(p,"10 6 12 .45 2.5 10","10 3 9 .45 2.5 10");const auto next=MechanicsLibrary::load(p.path);
    check(first->fingerprint()!=next->fingerprint()&&near(live.content->hornfel(monsterId(906))->fireWave.speed,6)&&
        near(next->hornfel(monsterId(906))->fireWave.speed,3)&&near(next->hornfel(monsterId(906))->fireWave.range,9),
        "reload changes the next content snapshot without silently mutating the running encounter");
        bad("906.0.0 1250 2 3 3.33333333","906.0.0 1250 3 2 3.33333333");
    bad("20 6 15 60 normal","20 0 15 60 normal");
    bad("20 6 15 60 normal","20 6 15 60 hot");
    bad("12 20 3.2 352 7.5","12 20 0 352 7.5");
    replace(p,"20 6 15 60 normal","20 6 8 24 normal");auto decoyNext=MechanicsLibrary::load(p.path);
    check(near(live.content->hornfelDecoy(monsterId(906,1))->bombSpeedMax,60)&&
        near(decoyNext->hornfelDecoy(monsterId(906,1))->bombSpeedMax,24),"decoy configuration reload preserves live snapshot");
    std::cout<<"HORNFEL_CONFIG rejects=18 snapshots=2\n";
}
void escorts() {
    auto children=[](const Simulation &s) {
        std::vector<EntityId> ids;for(const auto &e:s.enemies)if(e.alive&&e.flyFollow)ids.push_back(e.id);return ids;
    };
    for(int population:{0,3,4}) {
        Pack p;auto s=fixture(p.escort());
        for(int i=0;i<population;++i) {
            EnemyBomb b;b.id=200+i;b.ordnance=monsterId(4,14);b.room=0;b.charge.delay=100;b.charge.position={15,.44f,8};
            s.enemyBombs.push_back(b);
        }
        riding(s);
        check(s.rooms[0].hornfel->escortsSpawned==(population<4?2:0),"combined small-bomb cap gates pair before spawning;3 permits total5");
        for(auto id:children(s)) {
            const auto *e=s.findEnemy(id);check(e->monster==monsterId(819)&&e->hp==22.4f&&e->generation==1&&!e->componentOwner&&e->summoner==s.rooms[0].hornfel->owner,
                "ordinary vulnerable fly has distinct parent attachment and population provenance");
            check(!s.arena.flightBlocked(e->position,e->radius,0),"entrance random offset stays inside physical flight bounds");
        }
    }
    {Pack p;auto s=fixture(p.escort(100));riding(s);check(children(s).empty(),"player clearance suppresses unsafe entrance pair");}
    {Pack p;const auto lib=p.escort();auto attached=fixture(lib),free=fixture(lib);riding(attached);riding(free);
        auto ids=children(attached);auto freeIds=children(free);
        for(auto *s:{&attached,&free}) {
            auto &h=*s->rooms[0].hornfel;h.state=HornfelState::Opening;h.clock=1000;
            s->findEnemy(h.owner)->position={0,1.1f,0};s->player.position={20,.85f,0};
            int side=1;for(auto &e:s->enemies)if(e.flyFollow){e.position={0,.85f,float(side)*3};e.flyFollow->momentum={};side=-1;}
        }
        for(auto id:freeIds)free.findEnemy(id)->flyFollow.reset();
        tick(attached,90);tick(free,90);
        check(attached.findEnemy(ids[0])&&free.findEnemy(freeIds[0])&&
            distance(attached.findEnemy(ids[0])->position,free.findEnemy(freeIds[0])->position)>2,
            "parent forces produce visibly different movement from ordinary player pursuit");
        const auto at=attached.findEnemy(ids[0])->position;check(std::abs(at.x)>.5f&&planarDistance(at,{0,0,0})>3.5f,"soft radial and tangential steering moves around parent instead of rigidly attaching");
    }
    {Pack p;auto s=fixture(p.escort());s.limits.enemies=2;riding(s);
        check(children(s).empty()&&s.rooms[0].hornfel->escortGroupsSkipped==1,"capacity rejects optional pair atomically");
        s.limits.enemies=100;tick(s,30);check(children(s).empty(),"capacity release cannot inject a late pair mid-pass");}
    {Pack p;auto s=fixture(p.escort());riding(s);auto ids=children(s);check(ids.size()==2,"pair exists for lifecycle");
        hit(s,ids[0],17.4f); //5HP survives exit cap without being healed.
        const auto owner=s.rooms[0].hornfel->owner;
        for(int n=0;n<1200&&!s.rooms[0].hornfel->passes;++n) {
            tick(s);
            for(auto id:ids)if(const auto *e=s.findEnemy(id))check(!s.arena.flightBlocked(e->position,e->radius,0),"moving escort obeys room edges and cover");
        }
        check(s.rooms[0].hornfel->passes==1&&s.rooms[0].hornfel->escortsReleased==2,"ordinary rail exit releases surviving pair");
        check(s.findEnemy(ids[0])&&near(s.findEnemy(ids[0])->hp,5)&&s.findEnemy(ids[1])&&near(s.findEnemy(ids[1])->hp,11.2f),"release caps HP without healing injured flies");
        for(auto id:ids)check(!s.findEnemy(id)->flyFollow&&s.findEnemy(id)->summoner==owner,"release clears attachment, retaining source attribution");
        const auto from=s.findEnemy(ids[1])->position;tick(s,20);
        check(!s.findEnemy(ids[1])||distance(from,s.findEnemy(ids[1])->position)>.1f,"released fly resumes independent pursuit");
    }
    {Pack p;auto s=fixture(p.escort());riding(s);auto ids=children(s);const auto owner=s.rooms[0].hornfel->owner;
        hit(s,owner,10000);tick(s);
        check(s.rooms[0].hornfel->state==HornfelState::Sad&&s.findEnemy(ids[0])->flyFollow,"cart loss keeps live rider as parent");
        const auto hp=s.findEnemy(ids[0])->hp;hit(s,owner,10000,true);tick(s);
        check(s.findEnemy(ids[0])&&!s.findEnemy(ids[0])->flyFollow&&near(s.findEnemy(ids[0])->hp,hp),"owner removal releases without ordinary-exit HP clamp or killing children");
        check(s.roomThreats()>=2,"surviving escorts remain ordinary room-clear threats");
        hit(s,ids[0],1000);check(std::any_of(s.enemyBombs.begin(),s.enemyBombs.end(),[&](const auto &b){return b.source==ids[0]&&b.ordnance==monsterId(4,14);}),"escort shot death creates real Fly Bomb ordnance");
    }
    {Pack p;auto s=fixture(p.escort());riding(s);auto ids=children(s);const auto at=s.findEnemy(ids[0])->position;
        const auto clock=s.findEnemy(ids[0])->flyFollow->tick;s.enterRoom(1);s.player.position={120,.85f,0};tick(s,120);s.enterRoom(0);
        check(s.findEnemy(ids[0])&&s.findEnemy(ids[0])->flyFollow->tick==clock&&distance(at,s.findEnemy(ids[0])->position)<.001f,"inactive room preserves attachment and movement clock");
        s.player.position={0,.85f,0};tick(s,12);check(s.findEnemy(ids[0])->flyFollow->tick>clock,"return resumes attached movement");
        s.clearRoomDebug();check(s.enemies.empty()&&s.enemyBombs.empty()&&!s.rooms[0].hornfel,"debug clear removes escort and controller state");
    }
    std::cout<<"HORNFEL_ESCORTS combined_cap=3 distance_gate=1 atomic_pair=1 physical_entry=1 exit_hp=1 owner_lifecycle=1 death_bomb=1 inactive_pause=1\n";
}
void chargeSequence() {
    for(const auto layout:{"hornfel_special_5220","hornfel_special_5228"}) {
        Pack p;auto s=fixture(p.charge(),layout);auto &h=*s.rooms[0].hornfel;
        for(int n=0;n<3600&&h.state!=HornfelState::Charging;++n)tick(s);
        check(h.state==HornfelState::Charging&&h.repeatsChosen>=6&&h.repeatsChosen<=8,"eligible paired rail selects charge with6-8 repeats");
        const int chosen=h.cart.route,repeats=h.repeatsChosen;
        const auto &route=s.arena.rails->paths[size_t(chosen)];check(route.entry!=route.exit,"self-returning endcaps cannot select a charge");
        tick(s,60);const auto paused=h;const auto pos=s.findEnemy(h.owner)->position;
        s.enterRoom(1);s.player.position={120,.85f,0};tick(s,120);s.enterRoom(0);s.player.position={0,.85f,0};
        check(near(h.drive,paused.drive)&&near(h.cart.distance,paused.cart.distance)&&near(h.driveClock,paused.driveClock)&&h.repeatsLeft==paused.repeatsLeft&&distance(pos,s.findEnemy(h.owner)->position)<.001f,"charge drive/repeats pause and survive room reentry");
        for(int n=0;n<7200&&h.state==HornfelState::Charging;++n) {
            tick(s);check(h.cart.route==chosen,"all repeated passes retain original route");
        }
        check(h.state==HornfelState::RecoveryEntry&&h.chargePasses==repeats+1&&h.chargeBombs>0,"initial pass plus6-8 repeats emits scattered bombs then recovery entry");
        for(int n=0;n<10&&h.state!=HornfelState::Recovering;++n)tick(s);
        check(h.state==HornfelState::Recovering&&h.cart.route==chosen&&h.cart.distance<1,"recovery reuses original door and track");
        const int before=h.recoveryShots;int shootFrame=0;bool sawFire=false,afterAnimation=false;
        for(int n=0;n<2400&&h.state==HornfelState::Recovering;++n) {
            tick(s);
            if(!shootFrame&&h.recoveryShots>before)shootFrame=int(std::lround(h.recoveryClock*30));
            sawFire|=!s.fireWaves.empty();afterAnimation|=h.state==HornfelState::Recovering&&h.recoveryClock>87.f/30;
        }
        check(shootFrame==46&&h.recoveryShots==before+1,"one recovery projectile at authored Shoot frame46");
        check(h.state==HornfelState::Outside&&near(h.cart.distance,route.length()),"recovery ends at rail exit, not animation end");
        for(int n=0;n<180&&!sawFire;++n){tick(s);sawFire=!s.fireWaves.empty();}
        if(!sawFire)std::cerr<<"NO_FIRE layout="<<layout<<" clock="<<h.recoveryClock<<" shots="<<h.recoveryShots<<" projectiles="<<s.projectiles.size()<<" room="<<s.room<<'\n';
        check(sawFire,"recovery projectile actually lands and creates cardinal fire waves, including after cart exit");
        std::cout<<"HORNFEL_CHARGE layout="<<layout<<" repeats="<<repeats<<" passes="<<h.chargePasses<<" bombs="<<h.chargeBombs<<" shoot_frame="<<shootFrame<<" fire_wave=1 exit_recovery=1 longer_than_animation="<<afterAnimation<<'\n';
    }
    Pack p;auto s=fixture(p.charge());auto &h=*s.rooms[0].hornfel;
    for(int n=0;n<3600&&h.state!=HornfelState::Charging;++n)tick(s);
    const auto &route=s.arena.rails->paths[size_t(h.cart.route)];
    h.cart.distance=route.length()-.001f;h.repeatsLeft=1;h.nativeVelocity=40;
    s.player.position=route.sample(route.length()*.5f).position;s.player.position.y=.85f;s.player.hp=100;s.player.hurt=0;s.godMode=false;
    s.enemyBombs.clear();s.pendingEnemyBombs.clear();tick(s);
    check(h.repeatsLeft==0&&h.cart.distance==0&&s.player.hp==100,"instant repeat does not damage along teleport chord");
    s.godMode=true;s.player.position={0,.85f,0};
    for(int n=0;n<3600&&h.state!=HornfelState::Recovering;++n)tick(s);
    s.limits.projectiles=0;tick(s,160);
    check(!h.recoveryShot&&h.targets.size()==1,"recovery shot retains one target while projectile capacity is full");
    s.limits.projectiles=64;tick(s);
    check(h.recoveryShot&&h.recoveryShots==1,"retained recovery shot is emitted once after capacity returns");
    hit(s,h.owner,10000);check(h.state==HornfelState::Sad,"cart loss interrupts charge recovery without phase leakage");
}
void fireWaves() {
    Pack p;auto s=fixture(p.charge(0));auto &h=*s.rooms[0].hornfel;h.clock=1000;
    auto shot=[&] {
        Event e;e.position=e.origin={0,2,0};e.direction={0,-1,0};e.speed=1;e.projectileGravity=12;
        e.hostile=true;e.damage=10;e.projectileKind=ProjectileKind::Ember;e.fireWave={6,12,.45f,2.5f,10};e.context.sourceEntity=h.owner;
        s.queueRoot(e);s.drainEvents();
    };
    s.player.position={10,.85f,10};s.limits.fireWaves=0;shot();tick(s,60);
    check(s.fireWaves.empty()&&s.projectiles.size()==1&&s.projectiles[0].impactPending,"full fire capacity retains one impact, not partial rays");
    s.limits.fireWaves=32;tick(s);check(s.projectiles.empty()&&s.fireWaves.size()==1,"capacity recovery emits exactly one four-ray burst");
    tick(s,15);check(s.fireWaves.size()==1,"real growing fire persists");
    const auto &b=s.fireWaves.front();for(int n=0;n<4;++n) {
        Vector3 a,z;check(b.segment(n,a,z)&&((std::abs(a.x-z.x)<.001f)!=(std::abs(a.z-z.z)<.001f)),"four cardinal fire rays, not diagonal volleys");
    }
    const auto age=b.age;s.enterRoom(1);s.player.position={120,.85f,0};tick(s,120);s.enterRoom(0);s.player.position={10,.85f,10};
    check(near(s.fireWaves.front().age,age),"inactive room pauses existing fire");
    hit(s,h.owner,10000,true);s.clearRoom();check(s.fireWaves.size()==1,"already emitted fire survives producer death and ordinary clear");
    s.godMode=false;s.player.position={2,.85f,0};s.player.hurt=0;tick(s);
    check(s.player.hp<100,"actual fire trail harms the player after owner loss");
    s.godMode=true;s.player.position={10,.85f,10};tick(s,360);check(s.fireWaves.empty(),"bounded fire waves expire");

    Pack wallPack;auto wall=fixture(wallPack.charge(0));wall.rooms[0].hornfel->clock=1000;
    wall.arena.boundaryWalls.push_back({{2,-1,-3},{2.1f,4,3}});wall.arena.rebuildWalls();wall.player.position={3,.85f,0};wall.godMode=false;
    Event e;e.position=e.origin={0,2,0};e.direction={0,-1,0};e.speed=1;e.projectileGravity=12;e.hostile=true;e.fireWave={6,12,.45f,2.5f,10};
    wall.queueRoot(e);wall.drainEvents();tick(wall,120);
    check(wall.player.hp==100&&wall.fireWaves.size()==1&&wall.fireWaves[0].rays[0].stopped&&wall.fireWaves[0].rays[0].length<2,"fire stops at thin cover without damage through it");

    Pack pitPack;auto pit=fixture(pitPack.charge(0));pit.rooms[0].hornfel->clock=1000;
    pit.arena.rails->pits.push_back({{2,-3,-3},{4,0,3}});pit.player.position={5,.85f,0};pit.godMode=false;
    pit.queueRoot(e);pit.drainEvents();tick(pit,120);
    check(pit.player.hp==100&&pit.fireWaves.size()==1&&pit.fireWaves[0].rays[0].stopped&&pit.fireWaves[0].rays[0].length<2,"ground fire stops at a pit instead of jumping to the far bank");

    Pack reactPack;auto reactive=fixture(reactPack.charge(0));reactive.rooms[0].hornfel->clock=1000;
    const auto clotty=reactive.spawnMonster(monsterId(15),{3,.85f,0});
    const auto ally=reactive.spawnMonster(monsterId(23,0,1),{-3,.85f,0});
    check(reactive.findEnemy(ally)->friendly,"fire test uses a real damageable companion");
    const auto ordinary=reactive.spawnMonster(monsterId(12),{0,.85f,3});
    for(auto id:{clotty,ally,ordinary}){auto *body=reactive.findEnemy(id);body->state=EnemyState::Stunned;body->stateTime=10;}
    const auto allyHp=reactive.findEnemy(ally)->hp,ordinaryHp=reactive.findEnemy(ordinary)->hp;
    reactive.player.position={10,.85f,10};reactive.queueRoot(e);reactive.drainEvents();tick(reactive,100);
    check(reactive.findEnemy(clotty)->monster==monsterId(15,3),"actual fire segment ignites a reactive body away from the ray endpoint");
    if(!(reactive.findEnemy(ally)->hp<allyHp&&near(reactive.findEnemy(ordinary)->hp,ordinaryHp)))
        std::cerr<<"FIRE_TEAMS ally="<<reactive.findEnemy(ally)->hp<<'/'<<allyHp<<" ordinary="<<reactive.findEnemy(ordinary)->hp<<'/'<<ordinaryHp<<'\n';
    check(reactive.findEnemy(ally)->hp<allyHp&&near(reactive.findEnemy(ordinary)->hp,ordinaryHp),"hostile fire hurts a player ally while preserving ordinary monster friendly-fire policy");
    std::cout<<"FIRE_WAVES cardinal=4 atomic_capacity=1 player_damage=1 wall_stop=1 pit_stop=1 reactions=1 ally_damage=1 clear_survival=1 inactive_pause=1 expiry=1\n";
}
void throws() {
    for(int action=0;action<3;++action)for(bool large:{false,true}) {
        Pack p;auto s=fixture(p.action(action),large?"hornfel_special_5227":"hornfel_special_5220");auto id=s.rooms[0].hornfel->owner;
        hit(s,id,100);check(near(s.findEnemy(id)->hp,768),"offscreen boss cannot be shot");riding(s);
        auto &h=*s.rooms[0].hornfel;
        check(h.cart.id&&h.cart.rider==id&&h.cart.identity==monsterId(965)&&h.doors.size()==s.arena.rails->doors.size(),"separate typed cart and door ownership");
        for(const auto &door:h.doors)check(door.id&&door.identity==monsterId(967),"door is967, never decoy906.1");
        std::set<EntityId> bombs;int first=0,second=0;
        for(int frame=0;frame<600&&h.attacks==0;++frame) {
            tick(s);
            for(const auto &b:s.enemyBombs)if(b.source==id&&bombs.insert(b.id).second) {
                if(!first)first=int(std::lround(h.attackClock*30));else if(!second)second=int(std::lround(h.attackClock*30));
                check(b.ordnance==monsterId(4,action==2?15:0),"exact native ordnance identity");
            }
        }
        const int expected=action==2?(large?4:3):action+1;
        check(int(bombs.size())==expected&&h.attacks==1,"complete attack emits authored number of bombs");
        check(first==(action==2?34:17),"first release follows30FPS source animation event");
        if(action==1)check(second==27,"second throw event frame27");
        const auto pos=s.findEnemy(id)->position;const auto state=h.state;const auto clock=h.attackClock;
        s.enterRoom(1);tick(s,60);s.enterRoom(0);
        check(distance(s.findEnemy(id)->position,pos)<.001f&&s.rooms[0].hornfel->state==state&&near(s.rooms[0].hornfel->attackClock,clock),"inactive rooms preserve boss/cart/action state");
    }
    std::cout<<"HORNFEL_THROWS single=1 double=2 small_mines=3 large_mines=4 frames=17,27,34 separate_cart_doors=1 inactive_pause=1\n";
}
void lifecycle() {
    for(bool killed:{false,true}) {
        auto s=fixture();riding(s);auto id=s.rooms[0].hornfel->owner;auto &h=*s.rooms[0].hornfel;
        // Put the tested cart on an interior part of its physical path.
        h.cart.distance=s.arena.rails->paths[size_t(h.cart.route)].length()*.4f;tick(s);
        auto bombs=s.dynamite;hit(s,id,10000);
        check(s.findEnemy(id)->alive&&near(s.findEnemy(id)->hp,320)&&h.state==HornfelState::Sad&&!h.cart.intact&&h.cart.rider==0,"cart death resets100*3.2HP and detaches rider without a kill");
        check(s.stats.kills==0&&!s.bossKilled&&!s.rooms[0].bossPaid&&!s.arena.blocked(s.findEnemy(id)->position,s.findEnemy(id)->radius),"phase change neither rewards nor strands rider");
        check(near(s.findEnemy(id)->position.y,s.findEnemy(id)->radius+.05f),"dismount places rider on the ground, including an already legal cart position");
        tick(s,64);check(h.state==HornfelState::Fleeing,"32 authored Sad frames then fleeing");
        if(killed)hit(s,id,10000);
        else for(int n=0;n<3600&&!h.completed;++n)tick(s);
        check(h.completed&&h.escaped==!killed&&s.bossKilled&&s.rooms[0].bossPaid,"kill and successful escape both resolve encounter");
        check(s.stats.kills==uint64_t(killed),"escape does not emit a kill");
        check(s.dynamite==std::min(MaxDynamite,bombs+(killed?3:0)),"only killing gives three dynamite bonus");
        const auto paid=s.dynamite;tick(s,60);check(s.dynamite==paid,"no duplicate completion payout");
    }
    {
        auto s=fixture();riding(s);auto &h=*s.rooms[0].hornfel;
        auto *e=s.findEnemy(h.owner);e->position={s.arena.rooms[0].bounds.max.x-1,.85f,0};
        s.player.position=sub(e->position,{2,0,0});hit(s,e->id,10000);
        for(int n=0;n<3600&&!h.completed;++n) {
            tick(s);if(!h.completed)check(s.arena.roomAt(s.findEnemy(h.owner)->position)==0,"flee retreat stays inside its navigation room before door escape");
        }
        check(h.completed&&h.escaped,"near-wall dismount escapes without stranding on the terrain shoulder");
    }
    Pack p;auto s=fixture(p.action(2));s.limits.enemyBombs=s.limits.pendingEnemyBombs=0;riding(s);
    auto &h=*s.rooms[0].hornfel;tick(s,180);check(h.attack==2&&h.event==0&&s.enemyBombs.empty()&&h.targets.size()==3,"full mine salvo waits under capacity pressure");
    const auto targets=h.targets;s.limits.enemyBombs=10;tick(s);
    check(h.event==3&&s.enemyBombs.size()==3,"capacity recovery releases whole retained salvo");
    for(size_t n=0;n<3;++n)check(s.enemyBombs[n].source==h.owner,"retained source ownership");
    std::cout<<"HORNFEL_LIFECYCLE cart_hp=768 flee_hp=320 killed_bonus=3 escaped_bonus=0 no_escape_kill=1 atomic_mines=1\n";
}
void routes() {
    std::map<std::string,std::pair<uint64_t,int>> seeds;
    const auto lib=defaultMechanics();
    for(uint64_t seed=0;seed<2048&&seeds.size()<10;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            auto p=lib->configureFloor(plan.profileOnFloor(floor),plan.floorSeed(floor));
            if(!p.bossRails)continue;
            check(p.band==1&&p.variant==FloorVariant::Standard&&p.bossMonster==monsterId(906),"reviewed stage only");
            seeds.try_emplace(p.bossRails->key,seed,floor);
        }
    }
    check(seeds.size()==10,"all ten normal rail layouts reachable; no Void/Double Trouble substitution");
    for(const auto &[key,where]:seeds) {
        Simulation s(where.first,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,where.second);
        const auto &room=s.arena.rooms.back();check(s.arena.rails&&s.arena.rails->layout==key,"generated source-selected arena");
        check(near(s.arena.rails->cellSize.x,4)&&near(s.arena.rails->cellSize.z,4),"source aspect ratio before graph spacing");
        s.jumpDebug(s.finalRoom());s.godMode=true;tick(s,600);
        check(s.boss()&&s.boss()->monster==monsterId(906)&&(s.rooms.back().hornfel->attacks>0||s.rooms.back().hornfel->chargeBombs>0),"natural resident executes actual attacks");
        if(s.arena.path(s.player.position,room.exit,.48f).empty())std::cerr<<"BLOCKED_EXIT "<<key<<" seed="<<where.first<<" floor="<<where.second<<" player="<<s.player.position.x<<','<<s.player.position.z<<" exit="<<room.exit.x<<','<<room.exit.z<<" entry="<<room.entry.x<<','<<room.entry.z<<" blocked_player="<<s.arena.blocked(s.player.position,.48f)<<" blocked_exit="<<s.arena.blocked(room.exit,.48f)<<'\n';
        check(!s.arena.path(s.player.position,room.exit,.48f).empty(),"floor exit remains reachable around authored pits/rocks");
        for(const auto &pit:s.arena.rails->pits) {
            auto at=mul(add(pit.min,pit.max),.5f);at.y=.85f;
            check(s.arena.blocked(at,.48f)&&s.arena.canyon->height(at.x,at.z)<-.5f,"pits are physical and visibly lowered");
        }
        auto &h=*s.rooms.back().hornfel;
        for(int n=0;n<240&&!h.cart.visible;++n)tick(s);
        hit(s,h.owner,10000);
        check(h.state==HornfelState::Sad,"natural cart can break on the physical rail");
        for(int n=0;n<6000&&!h.completed;++n)tick(s);
        if(!h.completed) {
            const auto *body=s.findEnemy(h.owner);
            std::cerr<<"ESCAPE_STUCK "<<key<<" state="<<int(h.state)<<" door="<<h.escapeDoor<<" path="<<h.path.size()<<" body="<<body->position.x<<','<<body->position.z<<" blocked="<<s.arena.blocked(body->position,body->radius)<<'\n';
            if(h.escapeDoor>=0)std::cerr<<"escapeDoor="<<h.doors[size_t(h.escapeDoor)].position.x<<','<<h.doors[size_t(h.escapeDoor)].position.z<<'\n';
            for(auto p:h.path)std::cerr<<"waypoint="<<p.x<<','<<p.z<<'\n';
            std::cerr<<"bounds="<<room.bounds.min.x<<','<<room.bounds.min.z<<'/'<<room.bounds.max.x<<','<<room.bounds.max.z<<'\n';
            for(size_t i=0;i<s.arena.rails->doors.size();++i) {
                auto target=sub(s.arena.rails->doors[i],mul(railDirection(s.arena.rails->doorSides[i]),body->radius+.2f));target.y=body->position.y;
                std::cerr<<"candidate="<<target.x<<','<<target.z<<" blocked="<<s.arena.blocked(target,body->radius)<<" path="<<s.arena.path(body->position,target,body->radius).size()<<'\n';
            }
        }
        check(h.completed&&h.escaped&&s.rooms.back().bossPaid&&s.stats.kills<=uint64_t(h.escortsSpawned),"all source arenas permit actual grounded escape and one payout without counting Hornfel as a kill");
        std::vector<EntityId> remaining;for(const auto &e:s.enemies)if(e.alive&&e.monster.type==819)remaining.push_back(e.id);
        if(!remaining.empty())check(!s.roomClear,"Hornfel escape cannot erase surviving escort threats");
        for(auto id:remaining)hit(s,id,24);
        tick(s);
        check(s.roomClear&&s.stats.kills==uint64_t(h.escortsSpawned),"only actual escort deaths count as kills; last threat permits clear");
        for(const auto &coin:s.moneyPickups)if(coin.dropped) {
            auto at=coin.position;at.y=.85f;
            if(s.arena.blocked(at,.48f)||s.arena.path(room.entry,at,.48f).empty())std::cerr<<"UNREACHABLE_REWARD "<<key<<" coin="<<at.x<<','<<at.z<<" intended="<<room.reward.x<<','<<room.reward.z<<" entry="<<room.entry.x<<','<<room.entry.z<<'\n';
            check(!s.arena.blocked(at,.48f)&&!s.arena.path(room.entry,at,.48f).empty(),"boss payout stays reachable instead of falling into a center pit");
        }
        if(!s.storySeen())check(!s.canUseFloorExit(),"Hornfel escape does not bypass required testimony evidence");
        std::cout<<"HORNFEL_ROUTE layout="<<key<<" seed="<<where.first<<" floor="<<where.second<<" pits="<<s.arena.rails->pits.size()<<'\n';
    }
    std::cout<<"HORNFEL_REACHABILITY layouts=10 stage=1 standard=1 tutorial_excluded=1\n";
}
void isolatedCanyon() {
    Simulation s(1866,1,{},MissionTheme::Canyon);
    s.jumpDebug(s.finalRoom());s.clearRoomDebug();s.debugScenario=true;s.godMode=true;
    s.roomClear=s.bossKilled=false;s.rooms.back().cleared=s.rooms.back().bossPaid=false;s.stats={};
    const auto center=s.arena.rooms.back().center;s.player.position=add(center,{0,0,8});
    const auto id=s.spawnMonster(monsterId(906),center);check(id!=0,"isolated canyon creates rail actor");
    tick(s,90);hit(s,id,10000);auto &h=*s.rooms.back().hornfel;
    for(int n=0;n<3000&&!h.completed;++n)tick(s);
    if(!h.completed) {
        const auto *e=s.findEnemy(id);std::cerr<<"ISOLATED_ESCAPE x="<<e->position.x<<" z="<<e->position.z<<" state="<<int(h.state)<<" door="<<h.escapeDoor<<" path="<<h.path.size()<<'\n';
        for(size_t i=0;i<s.arena.rails->doors.size();++i) {
            auto target=sub(s.arena.rails->doors[i],mul(railDirection(s.arena.rails->doorSides[i]),e->radius+.2f));target.y=e->position.y;
            std::cerr<<"candidate="<<target.x<<','<<target.z<<" blocked="<<s.arena.blocked(target,e->radius)<<" path="<<s.arena.path(e->position,target,e->radius).size()<<'\n';
        }
    }
    check(h.completed&&h.escaped,"isolated canyon escape uses refreshed navigation, too");
    std::cout<<"HORNFEL_ISOLATED_ESCAPE completed=1 seconds="<<s.stats.duration<<'\n';
}
}
int main(){try{configuration();escorts();decoys();throws();chargeSequence();fireWaves();lifecycle();isolatedCanyon();routes();return 0;}catch(const std::exception &e){std::cerr<<"Hornfel test failed: "<<e.what()<<'\n';return 1;}}
