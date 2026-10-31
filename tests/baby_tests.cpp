#include "combat/Simulation.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const char *why){if(!ok)throw std::runtime_error(why);}
bool near(float a,float b,float epsilon=.008f){return std::abs(a-b)<epsilon;}
Simulation fixture(std::shared_ptr<const MechanicsLibrary> content=defaultMechanics()) {
    Simulation s(1866,1,{},MissionTheme::Mine,true,false,WitnessAccount::None,0,ExpeditionPacing::Compact,content);
    s.arena=Arena{};s.arena.bounds={{-100,-1,-100},{100,20,100}};
    for(auto &r:s.arena.rooms){r.bounds=s.arena.bounds;r.center={0,.85f,0};r.kind=RoomKind::Combat;r.floors={{{-100,-.4f,-100},{100,0,100}}};}
    s.arena.rebuildWalls();s.enemies.clear();s.projectiles.clear();s.hazards.clear();s.rooms.assign(s.arena.roomCount(),{});
    s.room=0;s.stats={};s.debugScenario=true;s.godMode=true;s.roomClear=false;s.player.position={50,.85f,50};return s;
}
void tick(Simulation &s,int n=1){for(int i=0;i<n;++i)s.step({},1.f/30);}
EntityId spawn(Simulation &s,int variant=0,int subtype=0,Vector3 at={0,.85f,0}){return s.spawnMonster(monsterId(38,variant,subtype),at);}
void damage(Simulation &s,EntityId id,float amount=7,bool execution=false) {
    Event h;h.type=EventType::Damage;h.target=id;h.damage=amount;h.execution=execution;s.queueRoot(h);s.drainEvents();
}
void statsAndMovement() {
    for(const auto [variant,subtype,hp]:{std::tuple{0,0,80.f},std::tuple{1,0,80.f},std::tuple{1,1,51.2f},std::tuple{3,0,80.f}}) {
        auto s=fixture();const auto id=spawn(s,variant,subtype);auto &e=*s.findEnemy(id);
        check(e.baby&&near(e.hp,hp)&&near(e.maxHp,hp),"source HP and dedicated runtime");
        check(near(s.content->monsterHealth(e.monster,13),hp),"no source stage HP growth");
        check(s.content->monster(e.monster)->flying,"wall-only source grid collision maps to canyon flight");
        tick(s);check(e.baby->initialized,"first source update initializes");
        tick(s);check(near(length(horizontal(e.velocity)),.33f*3),"first force endpoint .33 native units");
        tick(s);check(near(length(horizontal(e.velocity)),(.33f*.7f+.33f)*3),"second endpoint .7v+.33dir");
    }
    auto s=fixture();const auto id=spawn(s);auto &e=*s.findEnemy(id);tick(s);
    e.baby->cooldown=20;e.velocity={3,0,0};tick(s);
    check(near(e.velocity.x,2.1f)&&near(e.velocity.z,0),"cooldown coasts without pursuit force");
    auto close=fixture();const auto wid=spawn(close,3);close.player.position={6,.85f,0};tick(close,2);
    check(close.findEnemy(wid)->velocity.x<0,"Wrinkly retreats inside preferred distance");
    std::cout<<"STATS normal80 angel80 small51.2 wrinkly80 movement=.7v+.33dir retreat=1\n";
}
void shooting() {
    for(const auto [variant,subtype,count]:{std::tuple{0,0,1},std::tuple{1,0,3},std::tuple{1,1,1}}) {
        auto s=fixture();s.player.position={8,.85f,8};const auto id=spawn(s,variant,subtype);auto &e=*s.findEnemy(id);
        for(int n=0;n<20&&e.baby->attackFrame<0;++n)tick(s);
        check(e.baby->attackFrame==0&&e.baby->cooldown==34,"acquire then decrement native cooldown35");
        check((e.baby->ticks+id)%7==0,"global/entity seven-frame attack check");
        const auto acquire=e.baby->ticks;tick(s,4);check(s.projectiles.empty(),"no projectile before Shoot5");
        s.player.position={-8,.85f,8};const auto aim=unit(horizontal(sub(s.player.position,e.position)));
        const auto inherited=mul(horizontal(e.velocity),count==3?.4f*1.07f:0);tick(s);
        check(e.baby->ticks-acquire==5&&int(s.projectiles.size())==count&&e.baby->volleys==1,"Shoot event and exact packet size");
        const auto &center=s.projectiles.front();
        check(dot(unit(horizontal(center.velocity)),aim)>.999f,"aim sampled at Shoot, not acquisition");
        const float speed=24*1.07f*(count==3?1.2f:1);
        check(near(length(horizontal(center.velocity)),speed,.02f),"source mode and multiplier set planar speed");
        check(near(center.velocity.y,count==3?6.f:4.5f)&&near(center.gravity,6.75f)&&near(center.flightRetention,.9f),"physical vertical projectile parameters");
        if(count==3) {
            const Vector3 side{-aim.z,0,aim.x};
            const auto expected=add(add(mul(aim,speed*.9f*.961f),mul(side,speed*.9f*.276f)),inherited);
            check(distance(horizontal(s.projectiles[1].velocity),expected)<.01f,"spread is unnormalized native side vector plus inherited momentum");
        }
        tick(s,27);check(e.baby->attackFrame==-1,"Attack32 finishes independently of shot event");
    }
    auto s=fixture();s.player.position={12,.85f,12};const auto id=spawn(s,1);auto &e=*s.findEnemy(id);
    e.baby->initialized=true;e.baby->attackFrame=4;e.baby->cooldown=30;e.velocity={3,0,0};
    const auto aim=unit(horizontal(sub(s.player.position,e.position)));tick(s);
    const auto expected=mul(add(mul(aim,24*1.2f),Vector3{1.2f,0,0}),1.07f);
    check(distance(horizontal(s.projectiles.front().velocity),expected)<.01f,"mode2 inherits .4 actual parent velocity before final multiplier");
    auto capacity=fixture();capacity.player.position={8,.85f,8};const auto cid=spawn(capacity,1);auto &c=*capacity.findEnemy(cid);
    c.baby->initialized=true;c.baby->attackFrame=4;c.baby->cooldown=30;capacity.limits.projectiles=2;tick(capacity,3);
    check(c.baby->attackFrame==5&&!c.baby->fired&&capacity.projectiles.empty(),"triple volley retained atomically under capacity");
    capacity.limits.projectiles=3;tick(capacity);check(capacity.projectiles.size()==3&&c.baby->volleys==1,"retained packet fires once capacity returns");
    auto cover=fixture();cover.player.position={12,.85f,0};cover.arena.obstacles.push_back({{4,0,-6},{5,8,6}});cover.arena.rebuildWalls();
    const auto coverId=spawn(cover);tick(cover,20);check(!cover.findEnemy(coverId)->baby->volleys,"solid cover blocks acquisition");
    std::cout<<"SHOTS global7 cooldown35 Shoot5 counts1/3/1 current_target=1 native_spread=1 inherited_velocity=1 atomic=1\n";
}
void teleport() {
    auto s=fixture();s.player.position={8,.85f,8};const auto id=spawn(s);auto &e=*s.findEnemy(id);
    e.baby->initialized=true;e.baby->cooldown=100;e.baby->teleportCharge=41;e.baby->destination=Vector3{-30,.85f,-30};tick(s);
    check(e.baby->phase==BabyPhase::Vanishing&&!e.baby->intangible,"Vanish begins before collision changes on next native update");
    tick(s);const float hp=e.hp;damage(s,id);check(near(e.hp,hp)&&e.baby->intangible,"absent actor ignores ordinary damage");
    tick(s,4);check(near(e.baby->visibility,0),"Jump5 hides body");
    tick(s,19);check(e.baby->teleports==0,"no relocation at frame24");tick(s);
    check(e.baby->teleports==1&&e.baby->phase==BabyPhase::Appearing&&near(e.position.x,-30)&&near(e.position.z,-30),"relocation after counter24 to stored cell");
    tick(s,5);check(near(e.baby->visibility,1)&&e.baby->intangible,"Land5 visible while source collision remains disabled");
    tick(s,14);check(e.baby->phase==BabyPhase::Ready&&e.baby->intangible,"Appear19 finishes before next ready collision update");
    tick(s);damage(s,id);check(near(e.hp,hp-7),"ready actor vulnerable again");
    check(e.baby->recentDamageFrames==4,"damage starts recent-hit teleport pressure");tick(s);
    check(e.baby->teleportCharge>=20&&e.baby->teleportCharge<22,"recent damage sets charge20");
    for(int variant:{0,1}) {
        auto natural=fixture();natural.player.position={0,.85f,0};const auto nid=spawn(natural,variant,0,{8,.85f,8});auto &n=*natural.findEnemy(nid);
        n.baby->initialized=true;n.baby->cooldown=1000;n.baby->teleportCharge=21;
        for(int i=0;i<500&&!n.baby->destination;++i)tick(natural);
        check(bool(n.baby->destination),"native random search finds destination");
        const auto dest=*n.baby->destination;const float range=planarDistance(dest,natural.player.position);
        check(!natural.arena.blocked(dest,n.radius),"destination uses clear grounded cell");
        // Constraints precede snapping in the source; one half-cell diagonal is permitted.
        check(variant?range>5-2.83f&&range<12+2.83f:range>20-2.83f,"normal escapes, Angelic relocates close, with source grid snapping");
        check(near(std::fmod(dest.x+102,4),0)&&near(std::fmod(dest.z+102,4),0),"room-relative40 source grid centers");
    }
    auto blocked=fixture();blocked.player.position={8,.85f,8};const auto bid=spawn(blocked);auto &b=*blocked.findEnemy(bid);
    b.baby->initialized=true;b.baby->cooldown=100;b.baby->phase=BabyPhase::Vanishing;b.baby->frame=24;b.baby->destination=Vector3{-30,.85f,-30};
    blocked.arena.obstacles.push_back({{-32,0,-32},{-28,6,-28}});blocked.arena.rebuildWalls();tick(blocked);
    check(!b.baby->teleports||!blocked.arena.blocked(b.position,b.radius),"dynamic obstruction never embeds teleport destination");
    auto interrupt=fixture();interrupt.player.position={8,.85f,8};const auto iid=spawn(interrupt);auto &i=*interrupt.findEnemy(iid);
    i.baby->initialized=true;i.baby->attackFrame=3;i.baby->cooldown=20;i.baby->teleportCharge=41;i.baby->destination=Vector3{-30,.85f,-30};
    tick(interrupt,50);check(i.baby->volleys==0,"teleport replacing Attack before Shoot does not invent a later shot");
    std::cout<<"TELEPORT search=1 safe_cells=1 counter25 appear19 damage_window=1 animation_events=1 interrupted_attack=1\n";
}
void wrinklyDash() {
    auto s=fixture();s.player.position={20,.85f,0};const auto id=spawn(s,3);auto &e=*s.findEnemy(id);tick(s);
    check(e.baby->cooldown>=5&&e.baby->cooldown<=14,"Wrinkly initial native delay");
    for(int n=0;n<100&&e.baby->phase!=BabyPhase::DashStart;++n)tick(s);
    check(e.baby->phase==BabyPhase::DashStart&&e.baby->dashes==0,"mid-range target starts dash windup");
    s.player.position={18,.85f,4};tick(s,6);check(e.baby->dashes==0,"seven-frame windup not early");tick(s);
    check(e.baby->phase==BabyPhase::Dashing&&e.baby->dashes==1,"dash locks at windup completion");
    const auto direction=e.baby->dashDirection,target=e.baby->dashTarget;
    s.player.position={-20,.85f,-20};tick(s);
    check(distance(e.baby->dashDirection,direction)<.001f&&distance(e.baby->dashTarget,target)<.001f,"dash does not home after commitment");
    for(int n=0;n<100&&e.baby->attackFrame<0;++n)tick(s);
    check(e.baby->attackFrame==0&&e.baby->teleports==0,"dash ends in Attack without teleport");
    tick(s,10);check(s.projectiles.empty(),"Wrinkly waits for Shoot11");tick(s);
    check(e.baby->volleys==1&&s.projectiles.size()==3,"Wrinkly emits one triple burst");
    check(near(s.projectiles.front().gravity,9)&&near(s.projectiles.front().velocity.y,6),"Wrinkly default mode2 vertical flight");
    tick(s,27);check(e.baby->attackFrame==-1&&e.baby->cooldown>=14&&e.baby->cooldown<=43,"source recovery15..44 decremented by epilogue");
    auto wall=fixture();wall.player.position={20,.85f,0};wall.arena.obstacles.push_back({{5,0,-6},{6,8,6}});wall.arena.rebuildWalls();
    const auto wid=spawn(wall,3);auto &w=*wall.findEnemy(wid);
    check(!wall.arena.sight(w.position,wall.player.position),"solid cover obstructs the target");
    for(int n=0;n<100&&w.baby->phase!=BabyPhase::Dashing;++n)tick(wall);
    check(w.baby->phase==BabyPhase::Dashing,"hostile Wrinkly acquires through cover without an invented sight gate");
    for(int n=0;n<60&&w.baby->attackFrame<0;++n)tick(wall);
    check(w.baby->attackFrame>=0&&!wall.arena.flightBlocked(w.position,w.radius,0),"canyon wall stops committed dash without embedding");
    auto contact=fixture();contact.player.position={.8f,.85f,0};const auto pid=spawn(contact,3);auto &p=*contact.findEnemy(pid);
    p.baby->initialized=true;p.baby->phase=BabyPhase::Dashing;p.baby->dashDirection={1,0,0};p.baby->dashTarget={20,.85f,0};
    tick(contact,2);check(p.baby->attackFrame==0,"intercepting player ends dash before its original committed target");
    std::cout<<"WRINKLY retreat120 windup7 locked_direction=1 Shoot11 triple=1 recovery=1 wall_stop=1\n";
}
void configuration() {
    const auto content=defaultMechanics();
    for(int band=0;band<4;++band)for(auto pattern:{EncounterPattern::Pursuit,EncounterPattern::Crossfire})
        for(const auto &entry:content->encounterPool(band,pattern).specialists)if(entry.monster.type==38) {
            check(entry.monster.subtype==0&&entry.monster.variant!=2,"no small offspring or boss component in ordinary pool");
            check(band>=(entry.monster.variant==0?2:3),"source habitat bands");
        }
    const auto root=std::filesystem::temp_directory_path()/("dw-baby-"+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    struct Cleanup{std::filesystem::path p;~Cleanup(){std::filesystem::remove_all(p);}}cleanup{root};
    std::filesystem::copy(content->directory(),root,std::filesystem::copy_options::recursive);
    const auto file=root/"babies.mechanics";std::ifstream in(file);std::string original((std::istreambuf_iterator<char>(in)),{});
    auto modified=original;const auto pos=modified.find("normal .1 .33 .7");check(pos!=std::string::npos,"external movement profile present");
    modified.replace(pos,std::string("normal .1 .33 .7").size(),"normal .1 .66 .7");{std::ofstream out(file);out<<modified;}
    auto changed=MechanicsLibrary::load(root);check(changed->fingerprint()!=content->fingerprint()&&near(changed->baby(monsterId(38))->force,.66f),"external reload changes immutable profile");
    check(near(content->baby(monsterId(38))->force,.33f),"old snapshot remains unchanged");
    {std::ofstream out(file);out<<original<<"\nbaby_dash 38.0.0 5 14 15 44 4 7 3 120 280 3.75 .85 20\n";}
    bool rejected=false;try{MechanicsLibrary::load(root);}catch(const std::exception&){rejected=true;}check(rejected,"teleport controller rejects incompatible dash profile");
    std::cout<<"CONFIG external=1 snapshots=1 invalid_profile=1 stage_pools=1\n";
}
void lifecycleAndKit() {
    auto rooms=fixture();rooms.player.position={8,.85f,8};const auto rid=spawn(rooms);
    auto *stored=rooms.findEnemy(rid);stored->baby->initialized=true;stored->baby->attackFrame=2;stored->baby->cooldown=30;
    rooms.enterRoom(1);tick(rooms,31);rooms.enterRoom(0);stored=rooms.findEnemy(rid);
    check(stored&&stored->baby->attackFrame==2,"inactive room suspends attack animation clock");
    rooms.player.position={8,.85f,8};tick(rooms,3);check(stored->baby->volleys==1,"resumed attack emits once at retained event");
    stored->baby->attackFrame=-1;stored->baby->cooldown=0;stored->baby->teleportCharge=0;
    for(int n=0;n<10&&stored->baby->attackFrame<0;++n)tick(rooms);
    check(stored->baby->attackFrame==0&&(uint64_t(std::llround(rooms.stats.duration*30))+rid)%7==0,
        "reentry acquisition uses current global frame, not frozen actor clock");
    auto child=fixture();child.player.position={12,.85f,0};
    const auto parent=child.spawnMonster(monsterId(22,2),{0,.85f,0});
    auto *holy=child.findEnemy(parent);holy->state=EnemyState::Windup;holy->stateTime=0;holy->target=child.player.position;
    tick(child);
    auto offspring=std::find_if(child.enemies.begin(),child.enemies.end(),[](const auto &e){return e.monster==monsterId(38,1,1);});
    check(offspring!=child.enemies.end()&&offspring->baby&&near(offspring->maxHp,51.2f)&&offspring->summoner==parent,
        "actual Holy Mulligan route creates correct independent small Angelic child");
    const auto childId=offspring->id;damage(child,parent,10000,true);tick(child);
    check(child.findEnemy(childId)&&child.findEnemy(childId)->alive&&child.roomThreats()==1,"child survives parent and remains room threat");
    damage(child,childId,10000,true);tick(child);check(child.roomThreats()==0,"last offspring death releases room threat");
    for(const auto [variant,subtype]:{std::pair{0,0},std::pair{1,0},std::pair{1,1},std::pair{3,0}}) {
        auto fight=fixture();fight.godMode=false;fight.player.position={10,.85f,6};
        check(near(fight.player.hp,100)&&near(fight.player.shotDamage,24),"unchanged starting equipment");
        const auto id=spawn(fight,variant,subtype);int frames=0;
        while(frames<2400&&!fight.dead&&fight.roomThreats()) {
            Input input;const auto *e=fight.findEnemy(id);
            if(e&&e->alive) {
                input.fire=true;input.aim=e->position;
                auto away=unit(horizontal(sub(fight.player.position,e->position)));
                const auto side=Vector3{-away.z,0,away.x};
                input.movement=planarDistance(fight.player.position,e->position)<5?away:side;
            }
            fight.step(input);++frames;
        }
        check(!fight.dead&&fight.roomThreats()==0,"starting-kit actual-input fight clears Baby variant");
        std::cout<<"STARTING_KIT id=38."<<variant<<'.'<<subtype<<" seconds="<<frames*Tick<<" hp="<<fight.player.hp<<" shots="<<fight.stats.shots<<'\n';
    }
    std::cout<<"LIFECYCLE actual_parent_route=1 child_survives_parent=1 room_clear=1\n";
}
}
int main(){std::cout<<std::unitbuf;try{statsAndMovement();shooting();teleport();wrinklyDash();configuration();lifecycleAndKit();std::cout<<"PASS Baby family\n";return 0;}
catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
