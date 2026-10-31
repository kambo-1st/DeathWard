#include "combat/Simulation.hpp"
#include <filesystem>
#include <fstream>
#include <chrono>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *message){if(!ok)throw std::runtime_error(message);}
struct Pack {
    std::filesystem::path path=std::filesystem::temp_directory_path()/("deathward-bloat-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    Pack(){std::filesystem::create_directories(path);for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))
        if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),path/f.path().filename());}
    ~Pack(){std::filesystem::remove_all(path);}
    void weights(int attack){const auto f=path/"bosses.mechanics";std::ifstream in(f);std::string text((std::istreambuf_iterator<char>(in)),{});
        const std::string from="3 6 1 8 10 20 1 1 1";auto at=text.find(from);check(at!=std::string::npos,"real Bloat config fixture");
        text.replace(at,from.size(),"3 6 1 8 10 20 "+std::string(attack==0?"1 0 0":attack==1?"0 1 0":"0 0 1"));std::ofstream(f)<<text;}
    auto load(){return MechanicsLibrary::load(path);}
};
Simulation fixture(std::shared_ptr<const MechanicsLibrary> lib=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,lib);
    s.arena=Arena{};s.enemies.clear();s.hazards.clear();s.projectiles.clear();s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;
    s.arena.bounds={{-25,-1,-25},{25,8,25}};
    s.arena.boundaryWalls={{{-26,-1,-26},{-25,12,26}},{{25,-1,-26},{26,12,26}},{{-26,-1,-26},{26,12,-25}},{{-26,-1,25},{26,12,26}}};
    s.arena.rebuildWalls();for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,0,0};r.floors={{{-25,-.4f,-25},{25,0,25}}};}
    s.rooms.resize(s.arena.roomCount());s.player.position={0,.85f,-8};return s;
}
void ticks(Simulation &s,int count){for(int i=0;i<count;++i)s.step({});}
void kill(Simulation &s,EntityId id){Event e;e.type=EventType::Damage;e.target=id;e.damage=10000;e.execution=true;s.queueRoot(e);s.drainEvents();}
EntityId bloat(Simulation &s,BossForm form=BossForm::Normal){const auto id=s.spawnMonster(monsterId(68,1),{0,.85f,0},0,-1,form);check(id!=0,"Bloat body spawns");return id;}
int owned(const Simulation &s,EntityId owner){return int(std::count_if(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.alive&&e.componentOwner==owner;}));}
void lasers() {
    for(auto player:std::array<Vector3,5>{{{0,.85f,8},{-8,.85f,.4f},{8,.85f,.4f},{0,.85f,-8},{8,.85f,8}}}) {
        auto s=fixture();const auto id=bloat(s);s.findEnemy(id)->cooldown=1000;s.player.position=player;s.godMode=false;
        ticks(s,1);const bool beam=player.z==8?player.x==0:player.z==.4f;
        check(s.hazards.size()==(beam?2u:0u),"two instantaneous beams below/along sides, none above or off-axis");
        check(s.player.hp==(beam?87.5f:100.f),"near-instant paired beam damages once, not once per socket");
        for(const auto &h:s.hazards) {
            check(h.kind==HazardKind::Beam&&h.delay==0&&h.ownerBound&&h.context.sourceEntity==id,"real owned beam has no hidden telegraph delay");
            check(h.position.z>=h.origin.z-.001f,"no beam ever points upward");
            if(player.z==8)check(std::abs(h.position.x-h.origin.x)<.001f,"downward beams remain parallel");
            else check(std::abs(h.position.z-h.origin.z)<.001f,"side pair is fixed horizontal");
        }
        check(owned(s,id)==2&&s.roomThreats()==1,"Bloat begins with two non-gating owned eyes");
        kill(s,id);ticks(s,1);check(s.hazards.empty()&&owned(s,id)==0&&s.chains.empty(),"owner death cancels eyes and live lasers without retaining chains");
    }
    auto s=fixture();const auto id=bloat(s);s.findEnemy(id)->cooldown=1000;s.player.position={0,.85f,2};
    s.arena.obstacles.push_back({{-3,0,4},{3,3,5}});s.arena.rebuildWalls();ticks(s,1);
    check(s.hazards.size()==2,"aligned visible player triggers laser before cover");
    for(const auto &h:s.hazards)check(h.position.z<4,"beam endpoint clips against actual cover volume");
    s.godMode=false;s.player.position={0,.85f,8};ticks(s,10);check(s.player.hp==100,"cover protects player from laser");
    std::cout<<"BLOAT_LASERS down_pair=1 side_pair=1 no_up=1 immediate=1 owner_cleanup=1 cover=1\n";
    auto pair=fixture();const auto first=bloat(pair);const auto second=pair.spawnMonster(monsterId(68),{12,.85f,0},0,-1,BossForm::Cyan);
    pair.findEnemy(first)->cooldown=pair.findEnemy(second)->cooldown=1000;ticks(pair,1);
    check(owned(pair,first)==2&&owned(pair,second)==2,"each boss owns its own two components");
    check(!pair.spawnMonster(monsterId(68,10),{4,.85f,0},first,0),"wrong eye family cannot attach to another boss");
    kill(pair,first);ticks(pair,1);check(owned(pair,first)==0&&owned(pair,second)==2,"one owner death leaves the other owner's eyes intact");
}
void attacks() {
    for(auto form:{BossForm::Normal,BossForm::Green})for(int attack=0;attack<3;++attack) {
        Pack p;p.weights(attack);auto s=fixture(p.load());const auto id=bloat(s,form);
        s.findEnemy(id)->cooldown=0;s.findEnemy(id)->beamCooldown=1000;
        ticks(s,1);check(s.findEnemy(id)->bossAttack==attack,"file-only weights select Bloat action");
        const auto start=s.findEnemy(id)->position;float peak=start.y;
        for(int i=0;i<180&&s.findEnemy(id)->bossCycles==0;++i){ticks(s,1);peak=std::max(peak,s.findEnemy(id)->position.y);}
        const auto *boss=s.findEnemy(id);check(boss->bossCycles==1,"selected attack finishes within bounded time");
        const int shots=attack==0?0:form==BossForm::Green?(attack==1?2:3):8;
        check(s.stats.projectiles==uint64_t(shots),"normal 8-shot versus green 2/3 explosive-shot counts");
        if(attack==1)check(planarDistance(start,boss->position)<.001f&&peak>1.9f,"small hop stays in place but has a real arc");
        if(attack==2)check(boss->position.z<-6.9f&&peak>5,"long jump travels toward the acquired player");
        const auto children=std::count_if(s.enemies.begin(),s.enemies.end(),[&](const auto &e){return e.summoner==id;});
        check(children==(form==BossForm::Green&&attack==0?2:0),"only green large-creep action summons exactly two Chargers");
        for(const auto &e:s.enemies)if(e.summoner==id)check(e.monster==monsterId(23)&&s.content->charge(e.monster),"summons use configured cardinal Charger controller");
        for(const auto &h:s.hazards)check(h.tint.g==(form==BossForm::Green?151:35),"Repentance green creep replaces red, not only the sprite");
        if(attack==0||attack==2)check(!s.hazards.empty(),"large creep/long-jump landing creates actual damage patch");
        for(const auto &shot:s.projectiles) {
            if(form==BossForm::Green)check(shot.kind==ProjectileKind::Ipecac&&shot.gravity==12&&shot.blastRadius==2.8f,"Ipecac has actual ballistic/explosion data");
            else check(std::abs(std::sin(std::atan2(shot.velocity.z,shot.velocity.x)*4))<.001f,"Bloat rings use fixed cardinal/diagonal orientation");
        }
        s.findEnemy(id)->cooldown=1000;s.findEnemy(id)->beamCooldown=1000;
        if(form==BossForm::Green&&attack==1) {
            s.godMode=false;float projectilePeak=0;
            for(int i=0;i<100;++i){for(const auto &shot:s.projectiles)projectilePeak=std::max(projectilePeak,shot.position.y);ticks(s,1);}
            check(projectilePeak>2.5f&&s.projectiles.empty()&&s.player.hp==75,"real arcing shots land/explode and apply one hostile damage multiplier");
            check(s.findEnemy(id)->hp==1440,"hostile blast preserves current no-friendly-fire policy");
        }
        if(form==BossForm::Green&&attack==0) {
            kill(s,id);ticks(s,1);check(owned(s,id)==0&&s.roomThreats()==2,"owned eyes disappear while ordinary summoned Chargers survive");
        }
        std::cout<<"BLOAT_ATTACK form="<<int(form)<<" action="<<attack<<" shots="<<shots<<" summons="<<children<<" peak="<<peak<<'\n';
    }
}
void charger() {
    for(int band=0;band<4;++band) {
        const auto &pool=defaultMechanics()->encounterPool(band,EncounterPattern::ChargeLane);
        const bool present=std::any_of(pool.specialists.begin(),pool.specialists.end(),[](const auto &e){return e.monster==monsterId(23)&&e.weight>0;});
        check(present==(band==1||band==3),"ordinary Charger source stages are bands 1/3; green Bloat can summon in band 2");
    }
    auto s=fixture();s.player.position={.5f,.85f,8};const auto id=s.spawnMonster(monsterId(23),{0,.85f,0});s.findEnemy(id)->cooldown=0;
    ticks(s,1);check(s.findEnemy(id)->state==EnemyState::Charging&&s.findEnemy(id)->facing.x==0&&s.findEnemy(id)->position.z>0,"slightly offset acquisition immediately commits to exact cardinal axis");
    s.player.position={8,.85f,-8};ticks(s,30);check(std::abs(s.findEnemy(id)->position.x)<.001f&&s.findEnemy(id)->position.z>5,"charge does not home when player changes direction");
    auto a=fixture(),b=fixture();a.player.position={100,.85f,100};b.player.position={100,.85f,-100};
    const auto x=a.spawnMonster(monsterId(23),{0,.85f,0}),y=b.spawnMonster(monsterId(23),{0,.85f,0});
    ticks(a,120);ticks(b,120);check(distance(a.findEnemy(x)->position,b.findEnemy(y)->position)<.001f,"unaligned wandering does not pursue player");
    auto wall=fixture();wall.player.position={0,.85f,8};wall.arena.obstacles.push_back({{-3,0,4},{3,3,5}});wall.arena.rebuildWalls();
    const auto w=wall.spawnMonster(monsterId(23),{0,.85f,0});wall.findEnemy(w)->cooldown=0;ticks(wall,1);
    check(wall.findEnemy(w)->state!=EnemyState::Charging,"blocked line of sight prevents acquisition");
    wall.findEnemy(w)->state=EnemyState::Charging;wall.findEnemy(w)->stateTime=2;wall.findEnemy(w)->facing={0,0,1};ticks(wall,20);
    check(wall.findEnemy(w)->state==EnemyState::Ready&&wall.findEnemy(w)->position.z<4&&wall.findEnemy(w)->cooldown>0,"wall ends dash with recovery, no wall penetration");
    std::cout<<"CHARGER immediate_cardinal=1 locked_heading=1 untargeted_wander=1 los=1 collision_recovery=1\n";
}
void stages() {
    std::set<std::pair<int,BossForm>> seen;
    for(uint64_t seed=0;seed<64&&seen.size()<4;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            auto profile=defaultMechanics()->configureFloor(plan.profileOnFloor(floor),plan.floorSeed(floor));
            if(profile.bossMonster!=monsterId(68,1)||seen.contains({profile.band,profile.bossForm}))continue;
            check(profile.band==2||profile.band==3,"Bloat is restricted to Necropolis/Utero-equivalent bands");
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);s.jumpDebug(s.finalRoom());s.godMode=true;
            const auto id=s.boss()->id;check(s.enemies.size()==3&&owned(s,id)==2,"real Bloat room begins with correct owned-eye population");
            const auto before=s.enemies;s.enterRoom(0);s.enterRoom(s.finalRoom());
            check(s.enemies.size()==3&&s.enemies[1].id==before[1].id&&s.enemies[2].id==before[2].id,"room re-entry preserves existing owned parts");
            auto dynamite=s.dynamite;kill(s,id);ticks(s,1);
            check(s.roomClear&&s.bossKilled&&s.rooms.back().bossPaid&&s.roomThreats()==0&&s.dynamite==dynamite+1,"real boss completion cleans parts and pays once");
            seen.insert({profile.band,profile.bossForm});std::cout<<"BLOAT_STAGE seed="<<seed<<" floor="<<floor<<" band="<<profile.band<<" form="<<int(profile.bossForm)<<" completion=1\n";
        }
    }
    check(seen.size()==4,"both Bloat forms reached in both reviewed stage bands");
}
void startingKit() {
    for(auto form:{BossForm::Normal,BossForm::Green}) {
        auto s=fixture();s.godMode=false;s.dynamite=0;const auto id=bloat(s,form);s.player.position={0,.85f,-10};
        for(int tick=0;tick<12000&&!s.dead&&s.findEnemy(id);++tick) {
            const auto *boss=s.findEnemy(id);Input in;in.fire=true;in.aim=boss->position;
            const auto desired=add(boss->position,{std::sin(float(tick)*.025f)*5,0,-10});
            in.movement=unit(horizontal(sub(desired,s.player.position)));
            if((boss->hop.active&&planarDistance(boss->hop.end,s.player.position)<3)||
                std::any_of(s.projectiles.begin(),s.projectiles.end(),[&](const auto &p){return p.hostile&&distance(p.position,s.player.position)<3;}))in.dodge=true;
            s.step(in);
        }
        std::cout<<"BLOAT_STARTING_KIT form="<<int(form)<<" hp="<<s.player.hp<<" seconds="<<s.stats.duration<<" kills="<<s.stats.kills<<'\n';
        check(!s.dead&&!s.findEnemy(id)&&s.player.hp>0,"starting 100HP/24-damage kit defeats boss without items/bombs/invulnerability");
    }
}
}
int main(){try{lasers();attacks();charger();stages();startingKit();std::cout<<"PASS Bloat forms, real lasers/ballistics, owned eyes and Chargers\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
