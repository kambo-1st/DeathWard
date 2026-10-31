#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool v,const char *why){if(!v)throw std::runtime_error(why);}
bool near(float a,float b,float tolerance=.01f){return std::abs(a-b)<tolerance;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,content);
    s.arena=Arena{};s.arena.bounds={{-50,-1,-50},{50,20,50}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-50,-.4f,-50},{50,0,50}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.moneyPickups.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={-40,.85f,-40};return s;
}
void tick(Simulation &s,int n=1,float dt=1.f/30){for(int i=0;i<n;++i)s.step({},dt);}
void hit(Simulation &s,EntityId id,float damage,Vector3 direction={0,0,-1},bool area=false,bool piercing=false,
         DamageKind kind=DamageKind::Physical,bool execute=false) {
    Event h;h.type=EventType::Damage;h.target=id;h.damage=damage;h.direction=direction;
    h.areaDamage=area;h.armorPiercing=piercing;h.damageKind=kind;h.execution=execute;h.speed=17;
    if(const auto *e=s.findEnemy(id))h.position=add(e->position,{0,0,.7f});
    s.queueRoot(h);s.drainEvents();
}
EntityId knight(Simulation &s,int variant=0,Vector3 at={0,.85f,0}) {
    const auto id=s.spawnMonster(monsterId(41,variant),at);auto &e=*s.findEnemy(id);
    e.facing={0,0,1};if(e.maskArmor){e.maskArmor->facing=e.facing;e.maskArmor->turnGrace=0;}
    return id;
}
void armor() {
    for(int v:{0,1,2,4}) {
        auto s=fixture();const auto id=knight(s,v);const float health=v==4?96.f:64.f;
        check(near(s.findEnemy(id)->hp,health),"source20/30HP uses configured3.2conversion");
        hit(s,id,1,{.99f,0,-.01f});check(near(s.findEnemy(id)->hp,health),"even grazing front component blocks");
        hit(s,id,1,{1,0,0});check(near(s.findEnemy(id)->hp,health-1),"exact side is vulnerable");
        hit(s,id,1,{.99f,0,.01f});check(near(s.findEnemy(id)->hp,health-2),"small positive rear component passes");
        hit(s,id,1,{0,0,-1},false,true);hit(s,id,1,{0,0,-1},true);
        hit(s,id,1,{0,0,-1},false,false,DamageKind::Burning);
        check(near(s.findEnemy(id)->hp,health-5),"piercing area and status damage bypass mask");
        s.findEnemy(id)->facing={-1,0,0};hit(s,id,1,{1,0,0});
        check(near(s.findEnemy(id)->hp,health-5),"horizontal mask protects its displayed axis");
        hit(s,id,1,{-1,0,0});check(near(s.findEnemy(id)->hp,health-6),"horizontal rear remains vulnerable");
    }
    auto s=fixture();const auto id=knight(s,4);hit(s,id,1,{-.8f,0,-.6f});
    check(s.projectiles.size()==1&&s.projectiles.front().hostile,"blocked Black mask creates hostile reflection");
    const auto reflected=s.projectiles.front().velocity;
    check(near(length(reflected),17)&&near(reflected.x,-13.6f)&&near(reflected.z,10.2f),"oblique reflection preserves tangent and incoming speed");
    s.projectiles.clear();auto &e=*s.findEnemy(id);e.facing={1,0,0};e.state=EnemyState::Stunned;e.stateTime=10;
    tick(s);check(e.maskArmor->turnGrace>.49f,"new mask direction starts15frame reflection grace");
    hit(s,id,1,{-1,0,0});check(s.projectiles.empty(),"turn grace suppresses reflection while armor still blocks");
    tick(s,16);hit(s,id,1,{-1,0,0});check(s.projectiles.size()==1,"reflection resumes after turn grace");
    std::cout<<"MASK cardinal_half_plane=1 loose_armored=1 bypasses=1 specular_speed=1 grace15=1\n";
}
void linkedLife() {
    auto s=fixture();const auto id=knight(s,2);s.findEnemy(id)->maxHp=128;s.findEnemy(id)->hp=128;
    hit(s,id,10000,{0,0,1});
    auto *body=s.findEnemy(id);check(body&&body->alive&&body->monster==monsterId(41,3),"lethal Loose hit morphs original ID");
    check(near(body->maxHp,128)&&s.stats.kills==0&&s.moneyPickups.empty(),"morph preserves health scale without kill or loot");
    check(body->linkedRemnant->waiting,"required child is retained until birth");
    hit(s,id,10000,{0,0,1},true);check(body->alive&&near(body->hp,128),"body is invulnerable even before child birth");
    tick(s);body=s.findEnemy(id);const auto child=body->partner;const auto *pon=s.findEnemy(child);
    check(pon&&pon->monster==monsterId(840)&&pon->partner==id&&near(pon->maxHp,128),"bidirectional child ownership and health scale");
    check(s.roomThreats()==1,"only Pon blocks room completion");
    hit(s,child,10000);check(!s.findEnemy(id)->alive&&!s.findEnemy(child)->alive&&s.stats.kills==1,"Pon death removes only its remnant and pays one kill");
    auto capacity=fixture();capacity.debugScenario=false;const auto cid=knight(capacity,2);capacity.limits.enemies=1;
    hit(capacity,cid,10000,{0,0,1});tick(capacity,12);
    check(capacity.findEnemy(cid)&&capacity.findEnemy(cid)->linkedRemnant->waiting&&capacity.enemies.size()==1,"full pool retains child and original remnant");
    check(!capacity.roomClear&&capacity.roomThreats()==0,"retained child prevents actual clear with no independent remnant threat");
    capacity.limits.enemies=4;tick(capacity);
    check(capacity.findEnemy(cid)->partner&&capacity.enemies.size()==2,"capacity release creates exactly one child");
    hit(capacity,capacity.findEnemy(cid)->partner,10000);tick(capacity);
    check(capacity.roomClear&&capacity.livingEnemies()==0,"actual room completion follows vulnerable partner death");
    auto removed=fixture();const auto rid=knight(removed,2);removed.limits.enemies=1;
    hit(removed,rid,10000,{0,0,1});hit(removed,rid,10000,{0,0,1},false,false,DamageKind::Physical,true);
    removed.limits.enemies=4;tick(removed,2);check(removed.enemies.empty(),"removed owner cancels deferred child");
    auto placed=fixture();const auto a=knight(placed,3,{-8,.85f,0}),b=knight(placed,3,{8,.85f,0});
    const auto x=placed.spawnMonster(monsterId(840),{-9,.85f,0}),y=placed.spawnMonster(monsterId(840),{9,.85f,0});
    tick(placed);check(placed.findEnemy(a)->partner==x&&placed.findEnemy(b)->partner==y,"placed remnants claim nearest unclaimed Pons");
    hit(placed,x,10000);check(!placed.findEnemy(a)->alive&&placed.findEnemy(b)->alive&&placed.findEnemy(y)->alive,"pair death cannot kill another pair");
    auto orphan=fixture();const auto oid=knight(orphan,3);tick(orphan);check(!orphan.findEnemy(oid)&&orphan.enemies.empty(),"unpaired placed body expires without inventing Pon");
    std::cout<<"PAIR same_id=1 scale=1 no_duplicate_rewards=1 invulnerability=1 capacity=1 orphan=1 nearest_unique=1\n";
}
void hoppingAndCreep() {
    auto s=fixture();s.player.position={6,.85f,0};const auto id=s.spawnMonster(monsterId(840),{0,.85f,0});
    for(int n=0;n<180&&s.findEnemy(id)->targetHop->landings==0;++n)tick(s);
    auto &e=*s.findEnemy(id);check(e.targetHop->hops>0&&e.targetHop->landings==1,"Pon performs destination-driven hop and Land event");
    check(e.landingCreep->patches==1&&s.hazards.size()==1,"Land emits exactly one red footprint");
    const auto patch=s.hazards.front();check(near(patch.duration,125.f/30)&&near(patch.radius,2.5f),"source creep scale and lifetime preserved");
    hit(s,id,10000);s.enemies.clear();s.hazards={patch};s.player.position=patch.position;s.player.hurt=0;s.godMode=false;
    tick(s);check(near(s.player.hp,87.5f),"red landing patch damages after owner death");
    s.hazards.front().age=s.hazards.front().duration;s.player.hurt=0;const float hp=s.player.hp;tick(s);
    check(near(s.player.hp,hp),"fading footprint is harmless");
    auto blocked=fixture();blocked.player.position={8,.85f,0};
    blocked.arena.obstacles.push_back({{6,0,-2},{10,8,2}});blocked.arena.rebuildWalls();
    const auto bid=blocked.spawnMonster(monsterId(840),{0,.85f,0});tick(blocked,120);
    check(blocked.findEnemy(bid)->targetHop->hops>0&&!blocked.arena.blocked(blocked.findEnemy(bid)->position,.6f),"blocked player destination retries wandering and lands legally");
    auto cap=fixture();cap.player.position={6,.85f,0};const auto cid=cap.spawnMonster(monsterId(840),{0,.85f,0});cap.limits.hazards=0;
    for(int n=0;n<180&&cap.findEnemy(cid)->landingCreep->pending.empty();++n)tick(cap);
    check(cap.findEnemy(cid)->landingCreep->pending.size()==1,"full hazard pool retains Land footprint");
    auto &waiting=*cap.findEnemy(cid);waiting.targetHop->momentum={2,0,0};waiting.velocity={};
    waiting.targetHop->destination=add(waiting.position,{9,0,0});
    cap.limits.hazards=8;tick(cap);check(cap.hazards.size()==1&&length(horizontal(waiting.velocity))>3,
        "capacity release restores committed airborne momentum");
    waiting.landingCreep->pending.push_back(waiting.position);cap.limits.hazards=1;
    hit(cap,cid,10000);tick(cap);check(cap.findEnemy(cid)&&!cap.findEnemy(cid)->alive,"pending footprint survives dead actor cleanup");
    cap.limits.hazards=8;tick(cap);check(cap.hazards.size()==2&&!cap.findEnemy(cid),"retained footprint flushes once after death");
    std::cout<<"PON source_hop=1 landing_patch=1 life125=1 red_damage=1 fade=1 blocked_target_retry=1 capacity_after_death=1\n";
}
void movement() {
    for(int v:{0,1,2,4}) {
        auto s=fixture();const auto id=knight(s,v);s.player.position={12,.85f,0};
        tick(s,5);auto &e=*s.findEnemy(id);check(e.knight&&e.knight->charging,"aligned target starts cardinal charge without windup");
        check(e.state==EnemyState::Charging&&e.knight->charges==1,"one committed charge begins");
        const auto heading=unit(e.knight->chargeDirection);check(heading.x>.99f&&near(heading.z,0),"charge follows cardinal alignment");
        s.player.position={-35,.85f,35};tick(s,12);
        check(e.knight->charging&&dot(heading,unit(e.knight->chargeDirection))>.99f,"moving player does not bend committed charge");
        check(s.projectiles.empty()&&s.hazards.empty(),"ordinary charge does not invent warning or ranged payload");
        if(v==4)check(length(e.knight->chargeDirection)>1.4f,"Black accelerates force during committed charge");
        else check(near(length(e.knight->chargeDirection),v==1?1.65f:1.f),"ordinary and Selfless charge forces remain distinct");
    }
    auto diagonal=fixture();const auto did=knight(diagonal);diagonal.player.position={14,.85f,14};tick(diagonal,5);
    check(!diagonal.findEnemy(did)->knight->charging,"diagonal target does not trigger cardinal acquisition");
    auto occluded=fixture();const auto oid=knight(occluded);occluded.player.position={12,.85f,0};
    occluded.arena.walls.push_back({{5,-1,-20},{6,5,20}});tick(occluded,5);
    check(!occluded.findEnemy(oid)->knight->charging,"solid occluder prevents charge acquisition");
    auto longRun=fixture();const auto lid=knight(longRun);auto &le=*longRun.findEnemy(lid);
    le.knight->initialized=true;le.knight->charging=true;le.knight->chargeDirection={1,0,0};le.state=EnemyState::Charging;
    tick(longRun,50);check(le.knight->charging&&le.position.x>20,"unobstructed charge has no old1.2second timeout");
    auto random=fixture();const auto pon=random.spawnMonster(monsterId(840),{-20,.85f,20});const auto rid=knight(random,3);
    tick(random,12);auto &re=*random.findEnemy(rid);
    check(re.partner==pon&&length(re.velocity)>0&&re.knight->hasDestination,"Brainless adopts Pon while moving independently");
    auto mass=fixture();const auto light=knight(mass,0),heavy=knight(mass,4,{1.4f,.85f,0});
    for(auto &body:mass.enemies){body.state=EnemyState::Stunned;body.stateTime=10;}
    tick(mass);const float lightMoved=-mass.findEnemy(light)->position.x,heavyMoved=mass.findEnemy(heavy)->position.x-1.4f;
    check(heavyMoved>0&&lightMoved>heavyMoved*8,"source100mass Black body yields much less than mass10 Knight");
    std::cout<<"MOVEMENT cardinal_commit=1 no_generic_windup=1 no_timeout=1 selfless_force=1 black_acceleration=1 occlusion=1 remnant_wander=1 mass_ratio=1\n";
}
void impacts() {
    auto setup=[](Simulation &s,int v,float speed) {
        const auto id=knight(s,v);auto &e=*s.findEnemy(id);e.knight->initialized=true;e.knight->charging=true;
        e.knight->chargeDirection={v==4?4.f:1.f,0,0};e.velocity={speed,0,0};e.state=EnemyState::Charging;
        s.arena.walls.push_back({{6,-1,-40},{7,5,40}});return id;
    };
    auto s=fixture();const auto id=setup(s,4,36);
    for(int n=0;n<30&&!s.findEnemy(id)->knight->impacts;++n)tick(s);
    auto &e=*s.findEnemy(id);check(e.knight->impacts==1&&!e.knight->charging,"strong Black wall collision ends charge once");
    check(e.knight->recovery==45&&e.knight->liftVelocity>0,"impact starts45frame ground recovery and vertical rebound");
    check(s.fireWaves.size()==1&&s.fireWaves.front().rayCount==3,"impact creates exactly three fire wave generators");
    auto &w=s.fireWaves.front();
    check(near(w.directions[0].x,0)&&w.directions[1].x<-.99f&&near(w.directions[2].x,0)&&
        dot(w.directions[0],w.directions[2])<-.99f,"impact directions are back and opposite sides");
    tick(s,3);check(e.lift>0&&e.knight->recovery==45,"airborne recoil does not consume grounded recovery");
    check(!s.fireWaves.empty()&&!s.fireWaves.front().jets.empty(),"impact generators produce discrete jets");
    for(const auto &jet:s.fireWaves.front().jets)check(jet.position.x<=s.fireWaves.front().origin.x+.01f,"no jet propagates into forward wall direction");
    tick(s,10);check(e.knight->recovery>0&&!e.knight->charging,"recovery suppresses immediate recharge");
    check(near(e.hp,e.maxHp),"Black Knight ignores its ordinary fire jets");
    hit(s,id,1,{0,0,1},false,false,DamageKind::Flame);
    check(near(e.hp,e.maxHp-1),"jet exception does not confer blanket flame immunity");
    auto playerJet=fixture();const auto jid=knight(playerJet,4);auto &je=*playerJet.findEnemy(jid);
    je.state=EnemyState::Stunned;je.stateTime=10;
    FireWaveBurst playerWave;playerWave.room=0;playerWave.origin={-3,.85f,0};playerWave.rayCount=1;
    playerWave.rules=playerJet.content->knight(je.monster)->impactWave;playerWave.context.damageSource=DamageSource::Player;
    playerJet.fireWaves.push_back(playerWave);tick(playerJet,5);
    check(je.hp<je.maxHp,"player-produced fire jet bypasses native SpawnerType exception");
    auto ordinary=fixture();const auto oid=setup(ordinary,0,20);tick(ordinary,20);
    check(ordinary.findEnemy(oid)->knight->stops==1&&ordinary.fireWaves.empty(),"ordinary collision stops without Black payload");
    auto open=fixture();const auto bid=knight(open,4);auto &be=*open.findEnemy(bid);
    open.arena.rooms[0].bounds={{-10,-1,-10},{10,20,10}};
    be.knight->initialized=true;be.knight->charging=true;be.knight->chargeDirection={4,0,0};be.velocity={36,0,0};be.state=EnemyState::Charging;
    bool jets=false;
    for(int n=0;n<40;++n){tick(open);check(be.position.x<=10-be.radius+.001f,"open passage cannot release charger into a different room");
        for(const auto &w:open.fireWaves)jets|=!w.jets.empty();}
    check(be.knight->impacts==1&&jets,"room boundary impact produces visible inward jets");
    auto cap=fixture();const auto cid=setup(cap,4,36);cap.limits.fireWaves=0;
    for(int n=0;n<30&&!cap.findEnemy(cid)->knight->pendingImpact;++n)tick(cap);
    check(cap.findEnemy(cid)->knight->pendingImpact&&cap.fireWaves.empty(),"capacity retains due impact wave");
    hit(cap,cid,10000,{0,0,1},false,false,DamageKind::Physical,true);tick(cap);
    check(cap.findEnemy(cid)&&!cap.findEnemy(cid)->alive,"pending impact survives owner death");
    cap.limits.fireWaves=4;tick(cap);
    check(!cap.findEnemy(cid)&&cap.fireWaves.size()==1&&cap.fireWaves.front().rayCount==3,"retained fan emits once after owner death");
    std::cout<<"IMPACT three_directions=1 discrete_jets=1 lift=1 recovery45=1 ordinary_no_payload=1 capacity_after_death=1 open_passage_boundary=1\n";
}
void configuration() {
    const auto root=std::filesystem::temp_directory_path()/("dw-knights-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path path;~Cleanup(){std::filesystem::remove_all(path);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"knights.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture exists");text.replace(at,from.size(),to);std::ofstream(root/"knights.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit("1 15 10 .3","1 9 12 .3");check(changed->maskArmor(monsterId(41,4))->turnGraceFrames==9,"external reflection timing reloads");
    check(defaultMechanics()->maskArmor(monsterId(41,4))->turnGraceFrames==15,"old snapshot stays immutable");
    for(const auto &[from,to]:std::vector<std::pair<std::string,std::string>>{
        {"41.3.0 840.0.0 1","9999.0.0 840.0.0 1"},{"41.3.0 840.0.0 1","41.2.0 840.0.0 1"},
        {"1 15 10 .3","1 -1 10 .3"},{".1 .66 .8 100 10", ".1 .66 .8 0 10"},
        {".7 .07 4 3 22", ".7 .07 .5 3 22"},{"knight_impact 41.4.0 8 .9 .01 .88 5 1.1 5 45 1", ""},{"840.0.0 10 3 125 40 2.5 10 .98","840.0.0 0 3 125 40 2.5 10 .98"}}) {
        bool rejected=false;try{edit(from,to);}catch(const std::exception &){rejected=true;}check(rejected,"invalid lifecycle/timing rejected");
    }
    std::cout<<"CONFIG immutable_reload=1 invalid_profiles=7\n";
}
void placement() {
    struct Witness{MonsterId type;uint64_t seed;int floor,room;};
    for(auto w:std::array<Witness,5>{{{monsterId(41),0,2,5},{monsterId(41,1),1,6,7},{monsterId(41,2),0,3,2},{monsterId(41,4),1,6,10},{monsterId(840),28,7,3}}}) {
        Simulation s(w.seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,w.floor);s.godMode=true;
        EntityId actor=0;
        for(const auto &e:s.roomEnemies(w.room))if(e.monster==w.type) {
            check(!s.arena.blocked(e.position,e.radius),"natural Knight/Pon footprint is legal");
            check(e.knight||(e.targetHop&&e.landingCreep),"natural resident owns dedicated controller");actor=e.id;break;
        }
        check(actor,"fixed witness contains natural family member");
        check(s.arena.profile.band>0,"family absent from opening band");
        if(w.type==monsterId(41,1)||w.type==monsterId(41,4))check(s.arena.profile.band==3,"late variants stay in Storm Cut");
        if(w.type==monsterId(41,2)||w.type==monsterId(840))check(s.arena.profile.band>=2,"Loose and Pon stay in later bands");
        s.enterRoom(w.room);tick(s,6);const auto *e=s.findEnemy(actor);
        check(e&&(e->knight?e->knight->ticks>0:e->targetHop->initialized),"natural controller activates");
        std::cout<<"NATURAL_KNIGHT id="<<monsterIdText(w.type)<<" seed="<<w.seed<<" floor="<<w.floor<<" room="<<w.room<<'\n';
    }
}
void findBrainRiver() {
    for(uint64_t seed=34;seed<256;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int floor=0;floor<plan.floorCount;++floor) {
            if(plan.profileOnFloor(floor).band<2)continue;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            if(!s.arena.canyon||s.arena.canyon->riverKind!=CanyonRiverKind::Interior)continue;
            for(int room=1;room<s.finalRoom();++room) {
                if(!std::any_of(s.roomEnemies(room).begin(),s.roomEnemies(room).end(),[](const auto &e){return e.monster==monsterId(32);}))continue;
                if(!std::any_of(s.arena.canyon->river.begin(),s.arena.canyon->river.end(),[&](const auto &v){return s.arena.roomAt({v.position.x,.85f,v.position.z})==room;}))continue;
                std::cout<<"BRAIN_RIVER seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<s.arena.profile.band<<'\n';return;
            }
        }
    }
    check(false,"no natural Brain river witness in searched range");
}

}
int main(int argc,char **argv){std::cout<<std::unitbuf;try{if(argc==2&&std::string(argv[1])=="--find-brain-river"){findBrainRiver();return 0;}armor();linkedLife();hoppingAndCreep();movement();impacts();configuration();placement();std::cout<<"PASS Knight armor/lifecycle and Pon contracts\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
