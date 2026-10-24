#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const std::string &message){if(!ok)throw std::runtime_error(message);}
void plans() {
    std::set<int> lengths;
    for(uint64_t seed=0;seed<256;++seed) {
        ExpeditionPlan p(seed);lengths.insert(p.floorCount);std::set<int> bands;
        for(int floor=0;floor<p.floorCount;++floor){const auto profile=p.profileOnFloor(floor);bands.insert(profile.band);
            check(profile.band==std::min(3,floor*4/p.floorCount),"progress is tied to expedition floor, not graph depth");}
        check(bands.size()==4,"every standard run visits all four bands");
        check(!ExpeditionPlan(seed,true).profileOnFloor(0).active(),"tutorial stays unchanged");
        check(!ExpeditionPlan(seed,false,WitnessAccount::None,ExpeditionPacing::Classic).profileOnFloor(0).active(),"Classic remains available");
    }
    check(lengths.size()==5,"all five run lengths covered");
}
void floors() {
    int count=0;std::array<int,4> threats{},groups{};std::set<EncounterPattern> patterns;
    for(uint64_t seed=0;seed<16;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int band=0;band<4;++band) {
            int floor=0;while(plan.profileOnFloor(floor).band<band)++floor;
            Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            const auto &profile=run.arena.profile;
            check(profile.band==band,"simulation uses current floor profile");
            for(auto &p:run.arena.passages){p.locked=false;p.sealed={false,false};}run.arena.rebuildWalls();
            for(int room=0;room<run.arena.roomCount();++room) {
                const auto &r=run.arena.rooms[size_t(room)];const auto &residents=run.roomEnemies(room);
                if(r.kind==RoomKind::Combat) {
                    const auto grammar=run.floorEncounter(room);patterns.insert(grammar.pattern);
                    check(grammar.spent<=grammar.budget&&grammar.specialists<=profile.maxSpecialists,"threat and specialist limits");
                    check(int(residents.size())==run.roomEnemyCount(room),"safe placement realizes the budget");
                    threats[size_t(band)]+=grammar.spent;++groups[size_t(band)];
                    for(const auto &e:residents) {
                        check(e.kind==EnemyKind::Monster,"canyon uses Isaac-derived ordinary roster");
                        check(!run.arena.blocked(e.position,e.radius)&&run.arena.roomAt(e.position)==room,"resident on reachable floor");
                        check(distance(e.position,r.entry)>=6,"safe entrance landing");
                        for(int link:r.passages) {
                            const int side=run.arena.passages[size_t(link)].rooms[0]==room?0:1;
                            check(distance(e.position,run.arena.doorApproach(link,side))>=e.radius+2.5f,"every entry stays clear");
                        }
                        for(const auto &other:residents)if(e.id!=other.id)
                            check(distance(e.position,other.position)>=e.radius+other.radius,"bodies do not overlap");
                    }
                }
                check(!run.arena.path(r.center,r.objective,.48f).empty(),"objective reachable without bombs");
                for(int link:r.passages) {
                    const int side=run.arena.passages[size_t(link)].rooms[0]==room?0:1;
                    check(!run.arena.path(r.center,run.arena.doorApproach(link,side),.48f).empty(),"all mandatory door routes survive dressing");
                }
            }
            for(const auto &prop:run.arena.floorProps) {
                for(float x=prop.bounds.min.x;x<=prop.bounds.max.x;x+=.5f)
                    for(float z=prop.bounds.min.z;z<=prop.bounds.max.z;z+=.5f) {
                        const Vector3 p{x,.85f,z};const auto road=run.arena.canyon->roadSample(p);const auto river=run.arena.canyon->riverSample(p);
                        check(std::abs(run.arena.canyon->height(x,z))<=.02f,"floor dressing stays flat across its full footprint");
                        check(road.distance>road.width&&river.distance>river.width,"floor dressing keeps roads and water clear");
                    }
            }
            const auto &r=run.arena.rooms.back();
            check(run.roomEnemies(run.finalRoom()).size()==1&&run.roomEnemies(run.finalRoom())[0].bossKind==plan.bossOnFloor(floor),"dedicated single canyon boss");
            check(r.obstacles.empty(),"no baked outcrops in charge arena");
            for(int n=0;n<32;++n) {
                const auto a=add(r.center,{std::cos(n*2*Pi/32)*9.7f,0,std::sin(n*2*Pi/32)*9.7f});
                const auto b=add(r.center,{std::cos((n+1)*2*Pi/32)*9.7f,0,std::sin((n+1)*2*Pi/32)*9.7f});
                check(!run.arena.blocked(a,.8f)&&run.arena.clear(a,b,.8f),"continuous arena dodge loop seed="+std::to_string(seed)+" floor="+std::to_string(floor));
            }
            ++count;
        }
    }
    check(patterns.size()==4,"all encounter patterns occur");
    for(int band=0;band<4;++band)std::cout<<"band="<<band<<" meanThreat="<<double(threats[size_t(band)])/groups[size_t(band)]<<'\n';
    check(double(threats[3])/groups[3]>double(threats[0])/groups[0],"late floors increase combined threat");
    std::cout<<"Validated "<<count<<" canyon floors across four bands\n";
}
void determinism() {
    Simulation a(1866,1,{},MissionTheme::Canyon),b(1866,2,{},MissionTheme::Canyon);
    for(int room=0;room<a.arena.roomCount();++room) {
        const auto original=a.floorEncounter(room);a.arena.rooms[size_t(room)].depth=99;
        const auto deep=a.floorEncounter(room);
        check(original.monsters==deep.monsters&&original.pattern==deep.pattern,"graph depth cannot override a floor identity");
        const auto &left=a.roomEnemies(room),&right=b.roomEnemies(room);
        check(left.size()==right.size(),"seeded resident count");
        for(size_t i=0;i<left.size();++i)check(left[i].monster==right[i].monster&&left[i].bossKind==right[i].bossKind&&
            left[i].hp==right[i].hp&&distance(left[i].position,right[i].position)<.0001f,"seeded resident composition/placement");
    }
    for(auto pacing:{ExpeditionPacing::Growing,ExpeditionPacing::ShortCorridors,ExpeditionPacing::SmallRooms}) {
        Simulation comparison(0,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,pacing);
        const auto &room=comparison.arena.rooms.back();
        check(room.bounds.max.x-room.bounds.min.x>=32&&room.bounds.max.z-room.bounds.min.z>=32,"every modern preset reserves a full boss arena");
        for(int n=0;n<32;++n) {
            const auto a=add(room.center,{std::cos(n*2*Pi/32)*9.7f,0,std::sin(n*2*Pi/32)*9.7f});
            const auto b=add(room.center,{std::cos((n+1)*2*Pi/32)*9.7f,0,std::sin((n+1)*2*Pi/32)*9.7f});
            check(comparison.arena.clear(a,b,.8f),"comparison presets retain the continuous boss loop");
        }
    }
    WorldState world;world.flags.insert("canyon_cleared");
    Simulation repeat(1866,3,world,MissionTheme::Canyon);repeat.startBoss();
    check(!repeat.bossKilled&&repeat.boss(),"a previous expedition's victory does not defeat the new floor's guardian");
}
void bossRules() {
    Simulation run(1866,1,{},MissionTheme::Canyon);run.startBoss(BossKind::Ridgeback);run.godMode=true;
    auto *boss=run.findEnemy(run.boss()->id);const auto id=boss->id;
    const auto center=run.arena.rooms.back().center;
    run.player.position=add(center,{0,0,8});
    bool burrow=false,windup=false,charge=false,recovery=false;Vector3 target{};
    for(int i=0;i<600;++i) {
        run.step({});boss=run.findEnemy(id);
        if(boss->state==EnemyState::Buried){burrow=true;check(distance(boss->target,run.player.position)>=2.7f,"safe burrow landing");}
        if(boss->state==EnemyState::Windup) {
            if(!windup){target=boss->target;run.player.position=add(center,{7,0,0});}
            windup=true;
            if(!charge)check(distance(boss->target,target)<.01f,"charge aim locks during warning");
        }
        charge=charge||boss->state==EnemyState::Charging;recovery=recovery||boss->state==EnemyState::Stunned;
        if(burrow&&windup&&charge&&recovery)break;
    }
    check(burrow&&windup&&charge&&recovery,"complete windup/attack/recovery state machine");
    boss->hp=boss->maxHp*.49f;boss->state=EnemyState::Exposed;boss->stateTime=.01f;
    run.step({});check(boss->phase==1&&boss->bossCombo==1&&boss->state==EnemyState::Windup,"phase two schedules a second separately warned charge");
    const auto before=*boss;run.rewardOpen=true;for(int i=0;i<30;++i)run.step({});run.rewardOpen=false;
    check(boss->stateTime==before.stateTime&&boss->age==before.age,"modal pause freezes boss");
    boss->position=center;run.player.position=add(center,{0,0,5});boss->state=EnemyState::Exposed;boss->stateTime=.01f;
    int winds=0,charges=0;auto previous=boss->state;
    for(int i=0;i<700;++i) {
        run.step({});
        if(boss->state!=previous) {
            winds+=boss->state==EnemyState::Windup;charges+=boss->state==EnemyState::Charging;
            if(charges==2&&boss->state==EnemyState::Stunned)break;
        }
        previous=boss->state;
    }
    check(winds==2&&charges==2,"phase two executes two charges with separate readable windups");
    // Aim a real charge at one fragile rock; do not invoke destruction directly.
    auto rock=std::find_if(run.arena.breakables.begin(),run.arena.breakables.end(),[&](const auto &p){return p.room==run.finalRoom()&&p.kind==BreakableKind::CrackedRock;});
    check(rock!=run.arena.breakables.end(),"arena has fragile counterplay cover");
    const auto at=mul(add(rock->bounds.min,rock->bounds.max),.5f);
    boss->position={at.x-3,.85f,at.z};boss->target={at.x+3,.85f,at.z};boss->facing={1,0,0};boss->state=EnemyState::Charging;boss->stateTime=1;
    for(int i=0;i<30&&boss->state==EnemyState::Charging;++i)run.step({});
    check(rock->destroyed&&boss->state==EnemyState::Stunned&&boss->stateTime>1.5f&&boss->bossCombo==0,"fragile cover cancels combo and creates long recovery");
    boss->state=EnemyState::Buried;Event hit;hit.type=EventType::Damage;hit.target=id;hit.damage=24;
    const auto hp=boss->hp;run.queueRoot(hit);run.drainEvents();check(boss->hp==hp,"buried state has explicit immunity");
    boss->state=EnemyState::Stunned;run.queueRoot(hit);run.drainEvents();check(boss->hp==hp-30,"recovery rewards ordinary bullets");
    run.dynamite=0;hit.execution=true;hit.damage=10000;run.queueRoot(hit);run.drainEvents();run.step({});
    check(run.roomClear&&run.bossKilled&&run.dynamite==1&&run.rooms.back().bossPaid,"death cleans fight, pays supply and opens exit");
    const auto loot=run.moneyPickups.size();run.queueRoot(hit);run.drainEvents();check(run.moneyPickups.size()==loot&&run.dynamite==1,"boss payout once only");
}
void weakBuildWins() {
    for(uint64_t seed:{7ULL,1866ULL,42ULL})for(int late:{0,1}) {
        ExpeditionPlan plan(seed);const int floor=late?plan.floorCount-1:0;
        Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,floor);
        run.startBoss(BossKind::Ridgeback);run.godMode=false;run.dynamite=0;run.items.clear();
        const auto center=run.arena.rooms.back().center;
        for(int i=0;i<7200&&!run.roomClear&&!run.dead;++i) {
            const auto *boss=run.boss();check(boss,"living encounter retains boss");
            auto delta=sub(run.player.position,center);delta.y=0;const float d=length(delta);
            const auto radial=unit(delta);const Vector3 tangent{-radial.z,0,radial.x};
            Input in;in.fire=true;in.aim=boss->position;
            in.movement=unit(add(tangent,mul(radial,std::clamp((9.7f-d)*.7f,-2.f,2.f))));
            if(boss->state==EnemyState::Charging&&distance(boss->position,run.player.position)<5)in.dodge=true;
            run.step(in);
        }
        std::cout<<"Ridgeback seed="<<seed<<" floor="<<floor<<" time="<<run.stats.duration<<" hp="<<run.player.hp<<'\n';
        check(run.roomClear&&!run.dead&&run.player.hp>0,"starting revolver defeats boss without bombs/items/invulnerability");
        check(run.stats.duration<120&&run.stats.explosions==0,"bounded weak-build duration without explosives");
    }
}
}
int main(){try{plans();determinism();bossRules();weakBuildWins();floors();std::cout<<"PASS floor identities, threat grammar, safe geometry and complete canyon boss\n";}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
