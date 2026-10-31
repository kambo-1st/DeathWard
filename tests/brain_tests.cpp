#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float epsilon=.006f){return std::abs(a-b)<epsilon;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,content);
    s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,20,100}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={-90,.85f,-90};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({});}
EntityId spawn(Simulation &s,Vector3 at={0,.85f,0}){return s.spawnMonster(monsterId(32),at);}
void damage(Simulation &s,EntityId id){Event h;h.type=EventType::Damage;h.target=id;h.damage=10000;s.queueRoot(h);s.drainEvents();}
void charge(Enemy &e,Vector3 direction={1,0,0}){
    auto &r=*e.brain;r.initialized=true;r.charging=true;r.chargeDirection=direction;e.state=EnemyState::Charging;
}
void movementAndCharge() {
    auto s=fixture();const auto id=spawn(s);auto &e=*s.findEnemy(id);
    check(e.brain&&near(e.maxHp,64)&&!e.cardinalWalker&&!e.spitty,"dedicated Brain health and runtime");
    e.brain->hasDestination=true;e.brain->destination={60,.85f,0};tick(s,2);
    check(near(e.velocity.x,0)&&e.brain->initialized,"first source update only initializes state");tick(s,2);
    check(near(e.velocity.x,.75f*.85f*3),"X source force and damping endpoint");
    auto vertical=fixture();auto vid=spawn(vertical);auto &v=*vertical.findEnemy(vid);
    v.brain->hasDestination=true;v.brain->destination={0,.85f,60};tick(vertical,4);
    check(near(v.velocity.z,.75f*.8f*3),"vertical damping is .8, not Maggot's correction");
    auto other=fixture(),far=fixture();auto a=spawn(other),b=spawn(far);far.player.position={90,.85f,90};
    for(int n=0;n<120;++n){tick(other);tick(far);check(distance(other.findEnemy(a)->position,far.findEnemy(b)->position)<.001f,"unacquired wandering is player independent");}
    auto c=fixture();auto cid=spawn(c);auto &body=*c.findEnemy(cid);charge(body);tick(c,2);
    check(near(body.velocity.x,3),"charge first endpoint is direction*3");tick(c,2);
    check(near(body.velocity.x,5.4f),"charge second endpoint follows .8v+direction");
    c.player.position={0,.85f,-60};tick(c,8);check(body.brain->charging&&body.brain->chargeDirection.x==1,"charge does not retarget moving player");
    auto acquire=fixture();auto aid=spawn(acquire);auto &actor=*acquire.findEnemy(aid);
    actor.brain->hasDestination=true;actor.brain->destination={60,.85f,0};acquire.player.position={15,.85f,0};
    while(!actor.brain->charging&&actor.brain->ticks<20)tick(acquire);
    check(actor.brain->charges==1&&actor.brain->chargeDirection.x==1,"aligned target enters committed charge without windup");
    check((uint64_t(std::floor(acquire.stats.duration*30+1e-4))+aid)%7==0,"acquisition uses global interval and entity stagger");
    auto lead=fixture();auto lid=spawn(lead);lead.player.position={15,.85f,0};
    while(!lead.findEnemy(lid)->brain->charging&&lead.findEnemy(lid)->brain->ticks<20) {
        Input moving;moving.movement={1,0,0};lead.step(moving);
    }
    const auto &prediction=*lead.findEnemy(lid)->brain;
    check(prediction.charging&&prediction.predictedTarget.x>lead.player.position.x&&
          prediction.predictedTarget.x<=lead.player.position.x+6*16.f/30+.001f&&
          near(prediction.predictedTarget.z,lead.player.position.z),"charge predicts ahead along actual moving target velocity within source horizon");
    auto clamp=fixture();auto clid=spawn(clamp);clamp.player.position={99,.85f,60};
    for(int n=0;n<20;++n){Input moving;moving.movement={1,0,0};clamp.step(moving);}
    check(near(clamp.findEnemy(clid)->brain->predictedTarget.x,98),"predicted target respects source room inset");
    auto cover=fixture();cover.arena.obstacles.push_back({{4,0,-12},{5,6,12}});cover.arena.rebuildWalls();auto did=spawn(cover);
    auto &d=*cover.findEnemy(did);d.brain->hasDestination=true;d.brain->destination={3,.85f,0};cover.player.position={15,.85f,0};tick(cover,12);
    check(!d.brain->charges,"solid cover prevents aligned acquisition");charge(d);tick(cover,90);
    check(d.brain->stops>0&&!sphereBox(d.position,d.radius,cover.arena.obstacles[0]),"committed charge stops at physical cover");
    auto crowd=fixture();auto first=spawn(crowd);auto second=crowd.spawnMonster(monsterId(21),{4,.85f,0});
    crowd.findEnemy(second)->state=EnemyState::Stunned;crowd.findEnemy(second)->stateTime=10;charge(*crowd.findEnemy(first));tick(crowd,80);
    check(crowd.findEnemy(first)->brain->stops>0,"charge stops on another body");
    auto grid=fixture();auto gid=spawn(grid,{0,.85f,.75f});charge(*grid.findEnemy(gid));tick(grid,2);
    check(near(grid.findEnemy(gid)->position.z,.675f),"charge nudges perpendicular coordinate .9old+.1currentGrid");
    auto obstructed=fixture();obstructed.arena.obstacles.push_back({{-5,0,-.1f},{5,4,.1f}});obstructed.arena.rebuildWalls();
    const auto oid=spawn(obstructed,{0,.85f,.75f});charge(*obstructed.findEnemy(oid));tick(obstructed,2);
    check(near(obstructed.findEnemy(oid)->position.z,.75f)&&!obstructed.arena.blocked(obstructed.findEnemy(oid)->position,.6f),
          "blocked current grid center never pulls a charge through cover");
    check(s.projectiles.empty()&&c.projectiles.empty(),"Brain has no ranged projectile");
    std::cout<<"MOVEMENT hp64 X.85 Y.8 charge=.8v+direction global7 committed=1 prediction=1 cover=1 bodies=1 grid=1 safe_grid=1\n";
}
void creepAndLifecycle() {
    auto intervals=[](int extra,bool fast) {
        auto s=fixture();const auto id=spawn(s);
        for(int n=0;n<extra;++n){auto x=s.spawnMonster(monsterId(13),{-50.f+float(n)*3,.85f,-50});s.findEnemy(x)->state=EnemyState::Stunned;s.findEnemy(x)->stateTime=10;}
        const int period=extra<4?12:24;
        for(int n=0;n<96;++n) {
            auto *a=s.findEnemy(id);const auto before=a->brain->creepPatches;
            // Far from all edges/targets. A high threshold isolates base-period
            // drops in the slow case; a committed fast charge enables the half step.
            a->position={0,.85f,0};a->velocity={fast?12.f:0,0,0};
            a->brain->hasDestination=false;
            if(fast)charge(*a);
            tick(s,2);a=s.findEnemy(id);const auto phase=(a->brain->ticks+id)%uint64_t(period);
            const bool expected=(fast||a->brain->ticks>1)&&(phase==0||(fast&&phase==uint64_t(period/2)));
            check(a->brain->creepPatches-before==uint64_t(expected),"source creep phase/crowd/fast interval");
        }
        check(!s.hazards.empty(),"creep actually emitted");return s;
    };
    auto s=intervals(0,false);intervals(4,false);intervals(0,true);intervals(4,true);
    auto h=s.hazards.back();
    check(near(h.radius,2.46f)&&near(h.damage,10)&&near(h.duration,125.f/30)&&near(h.fadeDuration,40.f/30),"source-derived independent creep profile");
    s.hazards.clear();s.enemies.clear();s.godMode=false;s.player.hp=100;s.player.hurt=0;
    h.age=0;h.position={0,.85f,0};s.hazards.push_back(h);s.player.position={0,.85f,0};tick(s);
    check(near(s.player.hp,87.5f),"creep damage is half Brain body contact, after shared multiplier");
    s.player.hurt=0;s.hazards.front().age=s.hazards.front().duration;tick(s);
    check(near(s.player.hp,87.5f)&&s.hazards.front().fadeAge>=0,"expired creep becomes harmless while visible");
    tick(s,90);check(s.hazards.empty(),"fade removes expired patch");
    auto survival=fixture();survival.debugScenario=false;auto sid=spawn(survival);
    const auto remaining=survival.spawnMonster(monsterId(21),{50,.85f,50});
    survival.findEnemy(remaining)->state=EnemyState::Stunned;survival.findEnemy(remaining)->stateTime=10;
    tick(survival,80);auto count=survival.hazards.size();damage(survival,sid);tick(survival);
    check(count>0&&survival.hazards.size()>=count&&!survival.hazards.front().ownerBound&&!survival.roomClear,
          "already emitted creep survives owner death while another enemy remains");
    damage(survival,remaining);tick(survival);
    check(survival.roomClear&&!survival.hazards.empty()&&survival.hazards.front().fadeAge==0,
          "last enemy death automatically clears room and starts harmless fade");
    survival.godMode=false;survival.player.position=survival.hazards.front().position;tick(survival);check(near(survival.player.hp,100),"cleared-room fade cannot hurt player");
    tick(survival,90);check(survival.hazards.empty(),"cleared room finishes creep fade");
    auto cap=fixture();auto capid=spawn(cap);cap.limits.hazards=0;tick(cap,80);
    auto &r=*cap.findEnemy(capid)->brain;check(r.pendingCreep&&r.creepPatches==0,"full hazard capacity retains one due patch");
    auto paused=r.ticks;tick(cap,60);check(r.ticks==paused,"no runaway source time under capacity pressure");
    cap.limits.hazards=10;tick(cap);check(!r.pendingCreep&&r.creepPatches==1,"retained patch resumes once without duplicate");
    auto stun=fixture();auto stid=spawn(stun);auto &st=*stun.findEnemy(stid);charge(st);st.state=EnemyState::Stunned;st.stateTime=.5f;
    tick(stun,10);check(!st.brain->charging&&near(length(st.velocity),0),"stun cancels charge");tick(stun,40);check(st.brain->ticks>0,"stun recovery resumes source movement");
    auto rooms=fixture();auto rid=spawn(rooms);tick(rooms,60);const auto prior=*rooms.findEnemy(rid)->brain;
    rooms.enterRoom(1);tick(rooms,30);rooms.enterRoom(0);check(rooms.findEnemy(rid)->brain->ticks==prior.ticks,"inactive room freezes actor source clock");
    std::cout<<"CREEP crowd5 periods12/24 fast_half_step=1 radius2.46 lifetime125 fade40 damage12.5 owner_survival=1 clear=1 capacity=1 suspend=1\n";
}
void contactAndKit() {
    auto s=fixture();s.godMode=false;spawn(s);s.player.position={0,.85f,0};tick(s);
    check(near(s.player.hp,75),"source double contact converts to25");tick(s,5);check(near(s.player.hp,75),"contact respects player invulnerability");
    auto fight=fixture();fight.godMode=false;fight.player.position={0,.85f,8};const auto id=spawn(fight);int frames=0;
    while(fight.roomThreats()&&!fight.dead&&frames<1800) {
        Input input;input.fire=true;
        if(auto *e=fight.findEnemy(id)) {
            const auto delta=horizontal(sub(e->position,fight.player.position));const float range=length(delta);
            input.aim=add(e->position,mul(e->velocity,std::min(.5f,range/26)));
            input.movement=range>14?unit(delta):range<8?mul(unit(delta),-1):rotateY(unit(delta),Pi/2);
            // A charger is countered by leaving its lane, not running down the
            // trail behind it. Choose ordinary movement from visible threats;
            // no damage/HP changes, invulnerability or enemy-state mutation.
            if(e->brain->charging) {
                const auto dir=e->brain->chargeDirection;
                const Vector3 side{-dir.z,0,dir.x};
                const float lateral=dot(sub(fight.player.position,e->position),side);
                if(std::abs(lateral)<4)input.movement=mul(side,lateral<0?-1.f:1.f);
            }
            Vector3 avoid{};
            const auto ahead=add(fight.player.position,mul(unit(input.movement),1.5f));
            for(const auto &h:fight.hazards)if(h.kind==HazardKind::Creep&&h.fadeAge<0&&h.age<h.duration) {
                const auto away=horizontal(sub(ahead,h.position));const float gap=length(away);
                if(gap<h.radius+1)avoid=add(avoid,mul(unit(away),(h.radius+1-gap)*2));
            }
            input.movement=unit(add(input.movement,avoid));
        }
        fight.step(input);++frames;
    }
    if(fight.dead||fight.roomThreats()) {
        const auto *enemy=fight.findEnemy(id);
        std::cerr<<"KIT_FAILURE frames="<<frames<<" player_hp="<<fight.player.hp<<" player="<<fight.player.position.x<<','<<fight.player.position.z
                 <<" enemy_hp="<<(enemy?enemy->hp:-1)<<" enemy="<<(enemy?enemy->position.x:0)<<','<<(enemy?enemy->position.z:0)
                 <<" charges="<<(enemy?enemy->brain->charges:0)<<" stops="<<(enemy?enemy->brain->stops:0)<<'\n';
    }
    check(!fight.dead&&!fight.roomThreats(),"default kit defeats ordinary Brain");
    std::cout<<"STARTING_KIT seconds="<<frames*Tick<<" hp="<<fight.player.hp<<"\n";
}
void configuration() {
    const auto root=std::filesystem::temp_directory_path()/("dw-brain-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{root};std::filesystem::create_directories(root);
    for(const auto &f:std::filesystem::directory_iterator(defaultMechanics()->directory()))if(f.path().extension()==".mechanics")std::filesystem::copy_file(f.path(),root/f.path().filename());
    std::ifstream in(root/"brains.mechanics");const std::string original(std::istreambuf_iterator<char>(in),{});
    auto edit=[&](std::string from,std::string to){auto text=original;const auto at=text.find(from);check(at!=text.npos,"config fixture present");text.replace(at,from.size(),to);std::ofstream(root/"brains.mechanics")<<text;return MechanicsLibrary::load(root);};
    auto changed=edit("5 12 24 3 2.46 10","5 12 24 3 2.46 7");check(near(changed->brain(monsterId(32))->creepDamage,7)&&near(defaultMechanics()->brain(monsterId(32))->creepDamage,10),"immutable external configuration");
    auto animation=fixture(edit("20 30 40 5","20 60 40 5"));auto aid=spawn(animation);tick(animation,4);
    check(near(animation.findEnemy(aid)->brain->walkPhase,1.f/60,.0001f),"visual phase uses externally configured animation length");
    for(auto pair:std::vector<std::pair<std::string,std::string>>{{".1 .75 .85 .8",".1 -.75 .85 .8"},{"7 20 200 16 .8 .1","7 20 10 16 .8 .1"},{"5 12 24 3","5 11 24 3"},{"125 40 .98","125 0 .98"},{"Wander None Blob","Chase None Blob"},{"brain_charge 32.0.0 7 20 200 16 .8 .1",""}}) {
        bool rejected=false;try{edit(pair.first,pair.second);}catch(const std::exception&){rejected=true;}check(rejected,"invalid/incomplete Brain profile rejected");
    }
    std::cout<<"CONFIG immutable=1 invalid_profiles=6\n";
}
void placement() {
    std::array<bool,4> seen{};bool wet=false;
    // Discovered with the actual seeded generator, including a naturally
    // populated interior-river room. Keep regression bounded; offline search
    // evidence is preserved rather than scanning hundreds of floors each run.
    struct Witness {uint64_t seed;int floor,room,band;bool river;};
    for(const auto witness:std::array<Witness,2>{{{9,5,5,2,false},{326,4,4,3,true}}}) {
        const auto seed=witness.seed;const int floor=witness.floor;
            Simulation s(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);s.godMode=true;
            const int room=witness.room;
                std::vector<EntityId> ids;
                for(const auto &e:s.roomEnemies(room))if(e.monster==monsterId(32)) {
                    const int band=s.arena.profile.band;check(band==witness.band,"Brain ordinary source habitat bands");
                    check(e.brain&&!s.arena.blocked(e.position,e.radius),"generated resident has real controller and legal footprint");
                    if(!seen[size_t(band)])std::cout<<"NATURAL_BRAIN seed="<<seed<<" floor="<<floor<<" room="<<room<<" band="<<band<<'\n';
                    seen[size_t(band)]=true;ids.push_back(e.id);
                }
                check(!ids.empty(),"fixed seeded witness contains a real Brain without injection");
                const bool river=s.arena.canyon&&s.arena.canyon->riverKind==CanyonRiverKind::Interior&&std::any_of(s.arena.canyon->river.begin(),s.arena.canyon->river.end(),[&](const auto &v){return s.arena.roomAt({v.position.x,.85f,v.position.z})==room;});
                if(witness.river)check(river,"river witness retains actual interior water geometry");
                s.enterRoom(room);s.player.position=s.arena.rooms[size_t(room)].entry;
                for(int f=0;f<(river?240:8);++f){tick(s);for(auto id:ids)if(auto *e=s.findEnemy(id);e&&e->alive)check(!s.arena.blocked(e->position,e->radius),"generated Brain charge/wander remains physically legal");}
                for(auto id:ids)if(auto *e=s.findEnemy(id))check(e->brain->ticks>0,"generated Brain activates dedicated runtime");
                if(river){wet=true;std::cout<<"RIVER_BRAIN seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';}
    }
    check(seen[2]&&seen[3]&&wet,"both native-equivalent habitat bands and a real river room");
}
}
int main(){std::cout<<std::unitbuf;try{movementAndCharge();creepAndLifecycle();contactAndKit();configuration();placement();std::cout<<"PASS Brain\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
