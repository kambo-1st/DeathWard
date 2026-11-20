#include "combat/Simulation.hpp"
namespace dw {
bool Simulation::spawnBagBomb(Vector3 at,int subtype,uint32_t seed) {
    if((subtype!=3&&subtype!=5)||!seed||dead||finished||arena.roomAt(at)!=room||arena.blocked(at,.48f)||
       (enemyBombs.size()>=limits.enemyBombs&&pendingEnemyBombs.size()>=limits.pendingEnemyBombs))return false;
    EnemyBomb bomb;bomb.id=nextEntity_++;bomb.room=room;bomb.ordnance=monsterId(4,subtype==3?3:4);
    bomb.bagBomb.emplace();auto &r=*bomb.bagBomb;r.seed=seed;r.motion.variant=subtype==3?3:4;
    // Explicit DW seed adapter: retain this content request's seed. Native
    // conversion draws a new global MT word; shared global ordering is unported.
    r.motion.countdown=int(std::lround(float(BagBombMotion::fuse(seed)+1)*grabBagTuning.bombFuse))-1;
    r.movement=grabBagTuning.bombMovement;
    auto &c=bomb.charge;c.kind=HazardKind::MonsterBomb;c.position=c.origin=at;
    c.position.y=(arena.canyon?arena.canyon->height(at.x,at.z):0)+.3f;c.origin=c.position;c.settled=true;
    c.delay=float(r.motion.countdown+1)/30;c.radius=InventoryBombTuning::sourceRadius(100)*InventoryBombTuning::WorldPerSourceCoordinate;
    c.blastDamage=100*CombatHealthUnitsPerSource;c.damage=20;
    return queueEnemyBomb(bomb);
}
void Simulation::updateBagBomb(EnemyBomb &bomb,float dt) {
    auto &r=*bomb.bagBomb;auto &c=bomb.charge;
    if(r.blastPending){if(detonateEnemyBomb(bomb))r.blastPending=false;return;}
    r.elapsed+=dt;
    while(r.elapsed+1e-9>=1.0/30&&c.alive) {
        r.elapsed-=1.0/30;
        auto &m=r.motion;const auto before=m.position;
        m.move();
        const float scale=BagBombRuntime::MotionScale;
        m.position=add(before,mul(sub(m.position,before),r.movement));
        auto desired=add(c.origin,mul(m.position,scale));desired.y=c.position.y;
        // Canyon body/terrain admission is an adaptation, not native grid bounce.
        if(arena.roomAt(desired)==room&&arena.clear(c.position,desired,.35f)&&!arena.blocked(desired,.35f))c.position=desired;
        else {m.position=before;m.velocity={};}
        c.position.y=(arena.canyon?arena.canyon->height(c.position.x,c.position.z):0)+.3f;
        c.age+=1.f/30;
        if(m.countdown<=0){r.blastPending=true;r.elapsed=0;if(detonateEnemyBomb(bomb))r.blastPending=false;break;}
        --m.countdown;
        const auto target=mul(horizontal(sub(player.position,c.origin)),1/scale);
        // Native player velocity is per 60 Hz player step, even though bombs
        // advance at 30 Hz. Do not double the five-player-step prediction.
        const auto targetVelocity=mul(horizontal(player.velocity),1/(60*scale));
        m.steer(target,targetVelocity);
        // Existing responsive player controls stay intact. Grounded contact
        // uses a bounded push adapter; full native mass/grid response is open.
        const bool contact=planarDistance(player.position,c.position)<.83f&&std::abs(player.position.y-c.position.y)<1;
        if(contact&&r.grace>0)r.grace=4;
        else if(contact&&arena.clear(player.position,c.position,.1f)) {
            m.velocity=add(m.velocity,mul(targetVelocity,.4f));
            const auto away=unit(horizontal(sub(c.position,player.position)));
            m.velocity=add(m.velocity,mul(away,.5f));
        }
        if(r.grace>0)--r.grace;
        c.velocity=mul(m.velocity,30*scale*r.movement);
    }
}
bool Simulation::spawnShopGrabBag(Vector3 at,int slot) {
    if(slot<0||size_t(slot)>=upgradedShop.size()||upgradedShop[size_t(slot)].category!=7||grabBags.size()>=128||dead||finished||arena.blocked(at,.48f))return false;
    const int owner=arena.roomAt(at);if(!hasSourceShop(owner))return false;
    GrabBagPickup p;p.position=at;p.room=owner;p.shopSlot=slot;p.seed=upgradedShop[size_t(slot)].seed;
    p.contents=sourceGrabBagContents(p.seed);
    // Resolve once; unsupported rare subtypes retain identity without reroll.
    // Cards use the existing bounded Temperance producer, not the full source pool.
    for(auto &d:p.contents) {
        if(d.variant==300)d.subtype=TemperanceCard;
        else if(d.variant==90)d.subtype=1;
        else d.subtype=sourceOrdinaryPickup(d.seed,d.variant).subtype;
    }
    grabBags.push_back(std::move(p));checkpointNeeded=true;return true;
}
void Simulation::updateGrabBags(float dt) {
    for(auto &bag:grabBags)if(bag.room==room) {
        if(!bag.opened){
            if(!grabBagTuning.enabled||!canBuyUpgradedShop(bag.shopSlot)||planarDistance(player.position,bag.position)>=1||!arena.clear(player.position,bag.position,.1f))continue;
            if(!payUpgradedShop(bag.shopSlot))continue;
            bag.opened=true;bag.timing.collect();checkpointNeeded=true;
            audioCues.push(AudioCueKind::Pickup,bag.position);announce("GRAB BAG / SUPPLIES UNPACKED",3);
        } else bag.timing.advance(dt);
        for(size_t i=0;i<bag.contents.size();++i){
            auto &d=bag.contents[i];if(d.delivered)continue;
            // Golden keys and Troll/Megatroll keep their resolved identities.
            const bool troll=d.variant==40&&(d.subtype==3||d.subtype==5);
            if((d.variant==30&&!sourceOrdinaryKeyValue(d.subtype)&&d.subtype!=2)||(d.variant==40&&!sourceOrdinaryBombValue(d.subtype)&&!troll))continue;
            for(int attempt=0;attempt<144;++attempt){
                const float angle=float(i)*2.399963f+float(attempt%24)*2*Pi/24;
                const float radius=1.6f+float(attempt/24)*.6f;
                Vector3 at{bag.position.x+std::cos(angle)*radius,.85f,bag.position.z+std::sin(angle)*radius};
                if(arena.roomAt(at)!=room||arena.blocked(at,.48f)||arena.reservedSupplyCache(at,.5f)||!arena.clear(bag.position,at,.25f)||arena.path(player.position,at,.48f).empty())continue;
                bool conflict=false;
                for(const auto &o:upgradedShop)if(!o.sold&&planarDistance(o.position,at)<1.3f)conflict=true;
                for(int p:arena.rooms[size_t(room)].passages)for(const auto &gate:arena.passages[size_t(p)].gates)if(sphereBox(at,.5f,gate))conflict=true;
                const auto near=[&](const auto &p){return p.room==room&&planarDistance(p.position,at)<.8f;};
                if(conflict||std::any_of(moneyPickups.begin(),moneyPickups.end(),near)||std::any_of(keyPickups.begin(),keyPickups.end(),near)||std::any_of(bombPickups.begin(),bombPickups.end(),near)||std::any_of(batteryPickups.begin(),batteryPickups.end(),near)||std::any_of(pillPickups.begin(),pillPickups.end(),near))continue;
                bool born=false;
                if(d.variant==20&&moneyPickups.size()<1024){MoneyPickup coin{at,sourceOrdinaryCoinValue(d.subtype),0,true};coin.sourceSubtype=d.subtype;coin.room=room;coin.timing.appear(1);moneyPickups.push_back(coin);born=true;}
                else if(d.variant==30)born=d.subtype==2?spawnGoldenKey(at,d.seed):spawnOrdinaryKey(at,d.subtype,d.seed);
                else if(troll)born=spawnBagBomb(at,d.subtype,d.seed);
                else if(d.variant==40)born=spawnOrdinaryBomb(at,d.subtype,d.seed);
                else if(d.variant==90)born=spawnBattery(at);
                else if(d.variant==300)born=spawnPill(at,d.subtype,d.seed);
                if(born){d.delivered=true;checkpointNeeded=true;}break;
            }
        }
    }
}
}
