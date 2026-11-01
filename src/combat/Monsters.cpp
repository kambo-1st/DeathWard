#include "combat/Simulation.hpp"
#include "content/Mechanics.hpp"
#include <stdexcept>

namespace dw {
namespace {
using M = MonsterMotion;
using A = MonsterAttack;

int type(const Enemy &e) {
    return e.monster.type;
}
int variant(const Enemy &e) {
    return e.monster.variant;
}
Vector3 flatDirection(Vector3 a, Vector3 b) {
    auto d = sub(b, a);
    d.y = 0;
    return unit(d);
}
} // namespace
std::span<const MonsterDefinition> monsterCatalog() {
    return defaultMechanics()->monsters();
}
const MonsterDefinition *monsterDefinition(MonsterId id) {
    return defaultMechanics()->monster(id);
}

EntityId Simulation::spawnMonster(MonsterId id, Vector3 position,EntityId owner,int slot,BossForm form) {
    id=content->spawnIdentity(id,arena.profile);
    // Source subtype zero selects one of three rock silhouettes from InitSeed.
    // Use the seeded encounter stream; explicit subtypes remain exact identities.
    if(content->rockSpider(id)&&id.subtype==0)id=monsterId(id.type,id.variant,1+int(encounterRng.bounded(3)));
    // Native default Rotten Gaper morphs uniformly into subtypes1..5 from
    // InitSeed. DeathWard uses its deterministic encounter stream at allocation.
    if(content->rottenGaper(id)&&id.subtype==0)id=monsterId(id.type,id.variant,1+int(encounterRng.bounded(5)));
    const auto *d = content->monster(id);
    if (!d)
        return 0;
    if(content->linkedNeck(id))return 0; // Owned visual pieces, never free-standing enemies.
    if(content->monsterBoss(id)&&!content->bossFormAllowed(id,form))return 0;
    if(content->loki(id))return owner?0:spawnLoki(id,position);
    if(content->hornfel(id))return owner?0:spawnHornfel(id,position);
    if(content->hornfelDecoy(id))return 0; // Only the rail controller can allocate this rider.
    if(content->segmentedBoss(id))return owner?0:spawnSegmentedBoss(id,position);
    const auto *flyBomb=content->flyBomb(id);
    const auto *returning=content->returningBody(id);
    if(returning) {
        const auto *parent=findEnemy(owner);
        if(!parent||!parent->alive||parent->monster!=returning->owner)return 0;
    } else if(flyBomb&&flyBomb->orbitOwner) {
        const auto *parent=findEnemy(owner);
        if(!parent||!parent->alive||parent->monster!=flyBomb->orbitOwner||slot<0||slot>=flyBomb->orbitCount||
            (parent->bossParts&(1u<<slot)))return 0;
    } else if(const auto *component=content->component(id)) {
        const auto *parent=findEnemy(owner);
        if(!parent||!parent->alive||parent->monster!=component->owner||slot<0||slot>=2||
            (parent->bossParts&(1u<<slot)))return 0;
    } else if(owner)return 0;
    const auto entity = spawn(EnemyKind::Monster, position);
    if (!entity)
        return 0;
    auto &e = enemies.back();
    e.monster = id;
    if(content->rockSpider(id))e.rockSpider=RockSpiderRuntime{};
    if(content->hardy(id))e.hardy=HardyRuntime{};
    if(content->danny(id))e.danny=DannyRuntime{};
    if(content->faceless(id))e.faceless=FacelessRuntime{};
    if(content->gaper(id))e.gaper=GaperRuntime{};
    if(content->blackGlobin(id))e.blackGlobin=BlackGlobinRuntime{};
    if(content->leper(id))e.leper=LeperRuntime{};
    if(content->leperFlesh(id)) {
        auto &f=e.leperFlesh.emplace();f.shape=int(encounterRng.bounded(6));f.flip=encounterRng.bounded(2)!=0;
    }
    if(content->rottenGaper(id))e.rottenGaper=RottenGaperRuntime{};
    if(content->smallMaggot(id))e.smallMaggot=SmallMaggotRuntime{};
    if(content->headless(id))e.headless=HeadlessRuntime{};
    if(content->environmentActor(id))e.environment=EnvironmentActorRuntime{};
    e.hp = e.maxHp = content->monsterHealth(id,arena.profile.sourceStage);
    if(const auto *s=content->sack(id))e.hp=std::min(e.maxHp,s->initialHealth*s->healthScale*content->regularHealthAdjustment(id));
    if(const auto *p=content->boil(id);p&&!p->walking)e.hp=std::min(e.maxHp,p->cycle.initialHealth*p->cycle.healthScale*content->regularHealthAdjustment(id));
    e.radius = d->radius;
    if(d->flying)e.position.y=arena.flightHeight(e.position,e.radius);
    e.home = e.position;
    e.facing = rotateY({1, 0, 0}, float(entity % 8) * Pi / 4 + Pi / 4);
    if(content->boomFly(id))e.facing=rotateY({1,0,0},float(entity%4)*Pi/2+Pi/4);
    e.observedShots = stats.shots;
    e.friendly = content->companion(id)!=nullptr;
    if(const auto *lob=content->lobWalker(id)) {
        e.lob=LobWalkerRuntime{};
        if(!lob->attackFrames)e.cooldown=float(lob->initialMin+int(encounterRng.bounded(unsigned(lob->initialMax-lob->initialMin+1))))/30;
    }
    if(const auto *s=content->statue(id)) {
        e.facing=e.statueFacing=rotateY({0,0,-1},float(entity%4)*Pi/2+s->angle);
        if(s->attack==StatueAttack::Quake) {
            const std::array<Vector3,4> axes{{{-1,0,0},{0,0,-1},{1,0,0},{0,0,1}}};
            e.facing=e.statueFacing=axes[size_t(s->quakeAxis)];
        }
        e.cooldown=s->interval*.5f;
        syncStatueBodies();
    }
    if(content->component(id)||(flyBomb&&flyBomb->orbitOwner)) {
        e.componentOwner=owner;e.componentSlot=slot;
        e.facing=rotateY({1,0,0},Pi/4+float(slot)*Pi);
        findEnemy(owner)->bossParts|=1u<<slot;
    }
    if(content->monsterBoss(id))initializeMonsterBoss(e,form);
    if(const auto *p=content->maw(id)) {
        e.maw=MawRuntime{};e.cooldown=0;
        if(p->child)queueMonster(p->child,e.position,entity,0,false,1,0,0,0,-1,{},true);
    }
    if(content->eternalFly(id))e.eternalFly=EternalFlyRuntime{};
    if(content->spitty(id)){e.spitty=SpittyRuntime{};e.cooldown=0;e.facing={0,0,1};}
    if(content->cardinalWalker(id)){e.cardinalWalker=AxisWanderRuntime{};e.cooldown=0;e.facing={0,0,1};}
    if(content->knight(id)){e.knight=KnightRuntime{};e.cooldown=0;e.facing={0,0,1};}
    if(content->mirror(id)){e.mirror=MirrorRuntime{};e.cooldown=0;}
    if(content->brain(id)){e.brain=BrainRuntime{};e.cooldown=0;e.facing={0,0,1};}
    if(content->adultLeech(id)){e.adultLeech=AdultLeechRuntime{};e.cooldown=0;e.facing={1,0,0};}
    if(content->slide(id)){e.slide=SlideRuntime{};e.cooldown=0;}
    if(content->memBrain(id)){e.memBrain=MemBrainRuntime{};e.cooldown=0;}
    if(content->lump(id)){e.lump=LumpRuntime{};e.lump->anchor=e.position;e.cooldown=0;}
    if(content->baby(id)){e.baby=BabyRuntime{};e.cooldown=0;}
    if(content->vis(id)){e.vis=VisRuntime{};e.cooldown=0;e.facing={0,0,1};}
    if(const auto *g=content->guts(id)){e.guts=GutsRuntime{};e.guts->recovery=g->recoveryFrames;e.cooldown=0;e.facing={0,0,1};}
    if(returning) {
        e.returningBody=ReturningBodyRuntime{};e.componentOwner=owner;
        e.hp=e.maxHp=0;e.velocity={};e.cooldown=0;
    }
    if(const auto *p=content->linkedHead(id)) {
        e.linkedHead=LinkedHeadRuntime{};e.cooldown=0;
        if(id==p->body)queueMonster(p->head,e.position,entity,0,false,1,0,0,0,-1,{},true);
        else e.lift=p->headLift; // Correct carried pose even in an inactive room.
    }
    if(content->host(id)){e.host=HostRuntime{};e.cooldown=0;}
    if(content->mushroom(id)){e.mushroom=MushroomRuntime{};e.cooldown=0;}
    if(content->targetHop(id)){e.targetHop=TargetHopRuntime{};e.cooldown=0;}
    if(content->leaper(id))e.leaper=LeaperRuntime{};
    if(content->hopRings(id))e.hopRings=HopRingRuntime{};
    if(content->eggy(id))e.eggy=EggyRuntime{};
    if(content->adaptiveArmor(id))e.adaptiveArmor=AdaptiveArmorRuntime{};
    if(const auto *p=content->leech(id)) {
        e.leech=LeechRuntime{};e.cooldown=0;e.facing={0,0,1};
        if(p->child)queueMonster(p->child,e.position,entity,0,false,1,0,0,0,-1,{},true);
    }
    if(content->maskArmor(id))updateMaskArmor(e,0);
    if(content->linkedRemnant(id))e.linkedRemnant=LinkedRemnantRuntime{};
    if(content->landingCreep(id))e.landingCreep=LandingCreepRuntime{};
    return entity;
}
void Simulation::queueMonster(MonsterId id, Vector3 at, EntityId partner, int generation, bool collapsed,
                              float healthScale, int regrowthSplits, EntityId summoner,EntityId componentOwner,int componentSlot,
                              std::optional<ItemKey> sourceItem,bool retained,std::optional<ThrownOffspringRuntime> thrown,Vector3 impulse) {
    if ((!retained&&pendingMonsters_.size() + livingEnemies() >= limits.enemies) || generation > 4) {
        suppress({}, "monster offspring capacity");
        return;
    }
    id=content->spawnIdentity(id,arena.profile);
    pendingMonsters_.push_back({id, at, partner, generation, collapsed, healthScale, regrowthSplits, summoner,componentOwner,componentSlot,sourceItem,retained,0,thrown,impulse,{},{},{}});
    if(const auto *parent=findEnemy(summoner))pendingMonsters_.back().spawnerType=parent->monster.type;
    if(const auto *buzz=content->buzzFly(id);buzz&&summoner)if(const auto *parent=findEnemy(summoner)) {
        const auto policy=buzz->contactSummoners.find(parent->monster);
        if(policy!=buzz->contactSummoners.end())pendingMonsters_.back().contactRetention=policy->second;
    }
}
void Simulation::summonMonsters(const Enemy &e, const BehaviorSummon &rule) {
    const auto alive=std::count_if(enemies.begin(),enemies.end(),[&](const auto &child){return child.alive&&child.summoner==e.id;});
    const auto pending=std::count_if(pendingMonsters_.begin(),pendingMonsters_.end(),[&](const auto &child){return child.summoner==e.id;});
    const int count=std::min(rule.count,std::max(0,rule.ownerLimit-int(alive+pending)));
    for(int n=0;n<count;++n) {
        const auto offset=rotateY(mul(e.facing,-rule.spacing),float(n)*2*Pi/float(count));
        queueMonster(rule.monster,add(e.position,offset),0,e.generation+1,false,rule.healthScale,0,e.id);
    }
}
void Simulation::flushMonsterSpawns(Random *placement, float playerClearance) {
    // Copy a request before spawning: spawn can append a paired child to this queue.
    size_t cursor = 0;
    std::vector<MonsterSpawn> retained;
    while (cursor < pendingMonsters_.size()) {
        const auto request = pendingMonsters_[cursor++];
        const auto *d = content->monster(request.id);
        if (!d)
            continue;
        if(request.componentOwner) {
            const auto *parent=findEnemy(request.componentOwner);
            if(!parent||!parent->alive)continue;
        }
        const auto *pair=content->linkedRemnant(request.id);
        const bool pairedChild=pair&&request.id==pair->child&&request.partner;
        if(pairedChild) {
            const auto *parent=findEnemy(request.partner);
            if(!parent||!parent->alive||parent->monster!=pair->body)continue;
        }
        const bool attachedFly=content->eternalFly(request.id)&&request.partner&&request.retained;
        if(attachedFly) {
            const auto *parent=findEnemy(request.partner);
            if(!parent||!parent->alive)continue;
        }
        if(livingEnemies()>=limits.enemies) {
            if(request.retained)retained.push_back(request);
            continue;
        }
        Vector3 at = request.position;
        auto thrown=request.thrown;
        at.y = .85f;
        bool placed = false;
        if(attachedFly){at=findEnemy(request.partner)->position;placed=true;}
        if(content->returningBody(request.id)) {
            // This attack starts inside its parent and passes grid geometry.
            // Ordinary offspring placement would invent a displaced launch.
            placed=true;
        }
        if(const auto *p=content->linkedHead(request.id);p&&request.id==p->head) {
            if(const auto *parent=findEnemy(request.partner);parent&&parent->alive&&parent->monster==p->body) {
                // The head is attached to its body at birth, including when the
                // player touches that body. Ordinary offspring clearance would
                // otherwise displace or permanently withhold this required part.
                at=parent->position;placed=true;
            }
        }
        if(const auto *parent=findEnemy(request.summoner);parent&&parent->alive)
            if(const auto *p=content->rottenGaper(parent->monster);p&&p->brood&&p->child==request.id&&
               !arena.blocked(at,d->radius)) {
                // Native brood births overlap the parent's body with zero
                // velocity. Body separation resolves overlap after birth.
                placed=true;
            }
        for (int attempt = 0; !placed&&attempt < 65; ++attempt) {
            if (attempt)
                at = add(request.position,
                         rotateY({.8f + float(attempt / 8) * .45f, 0, 0}, float(attempt % 8) * Pi / 4));
            if(thrown&&attempt==64)at=thrown->origin; // A vertical birth remains possible in narrow spaces.
            at.y = .85f;
            if ((placement && !roomSpawnClear(at, d->radius)) ||
                ((content->strider(request.id)||((content->swimmer(request.id)||(content->slide(request.id)&&content->slide(request.id)->floodedPits))&&arena.swimmingRoom(room)))?arena.swimBlocked(at,d->radius,room):
                 d->flying?arena.flightBlocked(at,d->radius,room):arena.blocked(at,d->radius)) ||
                arena.reservedSupplyCache(at,d->radius) ||
                (!pairedChild&&!content->companion(request.id)&&distance(at, player.position) < std::max(playerClearance, d->radius + .65f)))
                continue;
            if(d->flying)at.y=arena.flightHeight(at,d->radius);
            if(thrown&&!planThrownOffspring(*thrown,at,d->radius,
                content->strider(request.id)||((content->swimmer(request.id)||(content->slide(request.id)&&content->slide(request.id)->floodedPits))&&arena.swimmingRoom(room))))continue;
            bool occupied = false;
            for (const auto &other : enemies)
                if (other.alive && distance(at, other.position) < d->radius + other.radius + .05f) {
                    // Eggy's released Swarms already have player-object-only
                    // collision; the non-colliding husk and peers cannot cage them.
                    if(request.swarmHop&&content->swarmSpider(request.id))continue;
                    if(pairedChild&&other.id==request.partner)continue;
                    // Loki emits its fly at its body, as in the source. Other
                    // bodies still exclude the new child; flight separates it.
                    if(content->eternalFly(request.id)&&other.id==request.partner)continue;
                    if(other.bossGroup==request.summoner&&request.summoner&&content->loki(other.monster))continue;
                    occupied = true;
                    break;
                }
            if (!occupied) {
                placed = true;
                break;
            }
        }
        if (!placed) {
            if(request.retained)retained.push_back(request);
            else suppress({}, "monster offspring placement");
            continue;
        }
        auto entity = spawnMonster(request.id, at,request.componentOwner,request.componentSlot);
        if (!entity) {
            if(request.retained)retained.push_back(request);
            continue;
        }
        auto &e = *findEnemy(entity);
        if (placement) {
            if(const auto *lob=content->lobWalker(e.monster);lob&&!lob->attackFrames)
                e.cooldown=float(lob->initialMin+int(placement->bounded(unsigned(lob->initialMax-lob->initialMin+1))))/30;
            else e.cooldown = placement->real(.6f, 1.8f);
        }
        if(content->maw(e.monster))e.cooldown=0;
        if(length(request.impulse)>0)e.velocity=request.impulse;
        if(request.slide)e.slide=request.slide;
        if(request.rockSpider){e.rockSpider=request.rockSpider;e.lift=-e.rockSpider->height*content->rockSpider(e.monster)->scale;}
        if(e.returningBody) {
            e.returningBody->initialVelocity=e.velocity;e.facing=unit(horizontal(e.velocity));
            e.returningBody->motion.push_back({e.position,e.position,0,1});
        }
        if(request.swarmHop) {
            e.swarmSpider=request.swarmHop;
            e.velocity=mul(request.swarmHop->momentum,content->swarmSpider(e.monster)->scale*30);
            e.state=EnemyState::Jumping;
        }
        e.partner = request.partner;
        if(const auto *p=content->linkedHead(e.monster);p&&e.monster==p->head)
            if(auto *parent=findEnemy(request.partner);parent&&parent->alive&&parent->monster==p->body) {
                parent->partner=entity;
                // Free-flight elevation must not pull a newborn attached head
                // away from a body beside raised canyon scenery.
                e.position=parent->position;
            }
        if(request.championFriendly) {
            e.friendly=true;e.permanentCharmed=request.championPermanent;
            if(request.championCharm>0||(request.championPermanent&&content->enemyStatuses(e.monster))){if(!e.statuses)e.statuses.emplace();e.statuses->charm=request.championCharm;}
        }
        e.summoner = request.summoner;
        e.spawnerType=request.spawnerType;
        if(thrown) {
            e.thrownOffspring=thrown;
            e.position=thrown->origin;e.position.y=.85f-thrown->height*thrown->profile.heightScale;
            e.velocity={};e.lift=0;
        }
        if(request.contactRetention>0) {
            if(!e.buzz)e.buzz=BuzzFlyRuntime{};
            e.buzz->diesOnContact=true;e.buzz->contactRetention=request.contactRetention;
        }
        if(request.childContactDeath&&content->spider(e.monster)) {
            if(!e.spider)e.spider=SpiderRuntime{};
            e.spider->diesOnContact=true;
        }
        e.companionItem = request.sourceItem;
        e.generation = request.generation;
        e.hp *= request.healthScale;e.maxHp *= request.healthScale;
        e.regrowthSplits = request.regrowthSplits;
        if (request.collapsed) {
            e.state = EnemyState::Collapsed;
            const auto *regrowth = content->regrowth(e.monster);
            e.stateTime = regrowth ? regrowth->delay : 2.5f;
            e.hp = e.maxHp * (regrowth ? regrowth->gooFraction : .25f);
        }
        if(pairedChild) {
            auto *parent=findEnemy(request.partner);parent->partner=entity;
            parent->linkedRemnant=LinkedRemnantRuntime{true,false};
        }
    }
    pendingMonsters_=std::move(retained);
}
size_t Simulation::roomThreats() const {
    return size_t(std::count_if(enemies.begin(), enemies.end(), [this](const Enemy &e) {
        const auto *d = content->monster(e.monster);
        const auto *pair=content->linkedRemnant(e.monster);
        return e.alive && !e.friendly && (!d || !d->roomHazard)&&(!pair||e.monster!=pair->body);
    }));
}
void Simulation::spawnMonsterDebug(MonsterId id) {
    id=content->spawnIdentity(id,arena.profile);
    const auto *d = content->monster(id);
    if (!d)
        return;
    const auto &bounds = arena.rooms[size_t(room)].bounds;
    for (int attempt = 0; attempt < 240; ++attempt) {
        Vector3 p{encounterRng.real(bounds.min.x + 1, bounds.max.x - 1), .85f,
                  encounterRng.real(bounds.min.z + 1, bounds.max.z - 1)};
        if (arena.blocked(p, d->radius) || arena.reservedSupplyCache(p,d->radius) || distance(p, player.position) < 6)
            continue;
        bool occupied = false;
        for (const auto &other : enemies)
            if (other.alive && distance(p, other.position) < d->radius + other.radius + .2f)
                occupied = true;
        if (occupied)
            continue;
        if (spawnMonster(id, p)) {
            debugScenario = true;
            flushMonsterSpawns();
            debugNotice(monsterIdText(id) + " / " + d->name);
        }
        return;
    }
    debugNotice("No safe space for this enemy in the current room.");
}
void Simulation::monsterPattern(const Enemy &e, int count, float angle, float speed, ProjectileKind kind) {
    for (int n = 0; n < count; ++n)
        shootEnemy(e, rotateY({1, 0, 0}, angle + float(n) * 2 * Pi / float(count)), 10, speed,
                   kind == ProjectileKind::BurstShot ? 1 : 0, kind);
}
void Simulation::monsterPatch(const Enemy &e, HazardKind kind, Vector3 at, float radius, float delay,
                              float duration) {
    Hazard h;
    h.kind = kind;
    h.position = at;
    h.origin = e.position;
    h.radius = radius;
    h.delay = delay;
    h.duration = duration;
    h.damage = kind == HazardKind::Tar ? 0 : kind == HazardKind::MonsterBomb ? 20 : 8;
    h.context.sourceEntity = e.id;
    addHazard(h);
}
void Simulation::monsterBeam(const Enemy &e, Vector3 dir, float delay) {
    auto end = add(e.position, mul(dir, 32));
    const auto hit = arena.trace(e.position, end, .1f);
    if (hit.hit)
        end = add(e.position, mul(sub(end, e.position), std::max(0.0f, hit.t - .005f)));
    Hazard h;
    h.kind = HazardKind::Beam;
    h.origin = e.position;
    h.position = end;
    h.radius = type(e) == 60 && variant(e) == 0 ? .16f : .35f;
    h.delay = delay;
    h.duration = .65f;
    h.damage = 16;
    h.context.sourceEntity = e.id;
    addHazard(h);
}
void Simulation::monsterLines(const Enemy &e, HazardKind kind, bool diagonal) {
    for (int n = 0; n < 4; ++n) {
        const auto dir = rotateY({1, 0, 0}, float(n) * Pi / 2 + (diagonal ? Pi / 4 : 0));
        for (int step = 1; step <= 10; ++step) {
            const auto at = add(e.position, mul(dir, float(step) * 1.5f));
            if (!arena.contains(at) || !arena.sight(e.position, at))
                break;
            monsterPatch(e, kind, at, .8f, .45f + float(step) * .065f,
                         kind == HazardKind::MonsterBomb ? 0 : 2.5f);
        }
    }
}
void Simulation::attackMonster(Enemy &e) {
    const auto &d = *content->monster(e.monster);
    const int t = type(e), v = variant(e);
    auto aim = d.flying?unit(sub(e.target,e.position)):flatDirection(e.position, e.target);
    const auto projectile = (t == 26 && v == 2)   ? ProjectileKind::Homing
                            : (t == 14 && v == 2) ? ProjectileKind::SplitShot
                            : (t == 15 && v == 1) ? ProjectileKind::Tar
                            : (t == 15 && v == 3) ? ProjectileKind::Flame
                                                  : ProjectileKind::Bullet;
    switch (d.attack) {
    case A::Shot:
        if (t == 27 && v == 3) {
            for (int n = 0; n < 4; ++n)
                shootEnemy(e, aim, 14, 7 + float(n) * 2, 0, ProjectileKind::Rock);
        } else
            shootEnemy(e, aim, 10, 9, 0, projectile);
        break;
    case A::Spread: {
        const int count = (t == 14 || t == 86) ? (v == 2 ? 4 : 2) : (t == 27 && v == 1) ? 5 : 3;
        for (int n = 0; n < count; ++n)
            shootEnemy(e, rotateY(aim, (float(n) - float(count - 1) / 2) * .22f), 10, 9, 0, projectile);
        break;
    }
    case A::Cross:
        monsterPattern(e, 4, (t == 15 && v == 3) ? .12f : 0, 9, projectile);
        if (t == 59 && ++e.phase % 3 == 0)
            monsterPatch(e, HazardKind::MonsterBomb, e.target, 2.2f, 1, 0);
        break;
    case A::Diagonal:
        monsterPattern(e, 4, Pi / 4, 9, projectile);
        break;
    case A::Ring:
        if (t == 57 && v == 2)
            for (int n = 0; n < 8; ++n)
                shootEnemy(e, rotateY({1, 0, 0}, float(n) * Pi / 4), 10, 8, 1);
        else if (t == 29) {
            constexpr std::array<int, 4> rings{4, 6, 8, 12};
            monsterPattern(e, rings[size_t(e.phase++ % 4)], e.age * .15f, 8);
            e.auxiliary = .18f;
        } else
            monsterPattern(e, 8, e.age * .15f, 8);
        break;
    case A::Burst:
        for (int n = 0; n < 7; ++n)
            shootEnemy(e, rotateY(aim, combatRng.real(-Pi, Pi)), 8, combatRng.real(4, 8), 0,
                       t == 34 ? ProjectileKind::Tar : projectile);
        break;
    case A::Lob:
        monsterPatch(e, HazardKind::MonsterBomb, e.target, 2.2f, .95f, 0);
        if (t == 87 && v == 1) {
            Enemy at = e;
            at.position = e.target;
            monsterLines(at, HazardKind::Fire);
        }
        break;
    case A::Spawn: {
        MonsterId child = monsterId(85); int count = 1;
        if (t == 22) {
            child = v == 0   ? monsterId(18)
                    : v == 1 ? monsterId(23, 1)
                    : v == 2 ? monsterId(38, 1, 1)
                             : monsterId(222);
            count = v == 3 ? 6 : 1;
        }
        if (t == 61)
            child = monsterId(861);
        // Population ownership must not reuse the paired-body/attack-target link.
        summonMonsters(e,{child,count,6,t == 22 && v == 1 ? .5f : 1.f,1.6f});
        break;
    }
    case A::Beam:
        monsterBeam(e, aim);
        break;
    case A::DoubleBeam:
        monsterBeam(e, aim);
        monsterBeam(e, mul(aim, -1));
        break;
    case A::QuadBeam:
        for (int n = 0; n < 4; ++n)
            monsterBeam(e, rotateY(aim, float(n) * Pi / 2));
        break;
    case A::Head:
        if (t == 39)
            shootEnemy(e, aim, 16, 12, 0, ProjectileKind::ReturningHead);
        else
            for (auto &child : enemies)
                if (child.alive && child.partner == e.id && type(child) == 35) {
                    child.state = EnemyState::Charging;
                    child.stateTime = .7f;
                    child.facing = aim;
                }
        break;
    case A::Light:
        for (int n = 0; n < 4; ++n)
            monsterPatch(e, HazardKind::HolyLight,
                         add(e.target, rotateY({float(n) * .7f, 0, 0}, float(n) * Pi / 2)), .85f,
                         .65f + float(n) * .18f, .3f);
        break;
    case A::Spitty:
        shootEnemy(e, e.facing, 10, 8);
        if (v == 1) {
            monsterPattern(e, 7, e.age, 6);
            for (int n = 0; n < 4; ++n)
                shootEnemy(e, e.facing, 10, 9 + float(n) * 2);
        }
        break;
    default:
        break;
    }
}

void Simulation::updateMonster(Enemy &e, float dt) {
    if(e.championPile) {
        e.age+=dt;e.flash=std::max(0.f,e.flash-dt);e.velocity={};e.stateTime-=dt;
        if(e.stateTime<=0){e.championPile=false;e.state=EnemyState::Ready;e.hp=e.maxHp;}
        return;
    }
    if(content->creatureCycle(e.monster)){updateCreatureCycle(e,dt);return;}
    if(!updateLinkedRemnant(e))return;
    if(content->knight(e.monster)){updateKnight(e,dt);return;}
    if(content->mirror(e.monster)){updateMirror(e,dt);return;}
    if(content->adultLeech(e.monster)){updateAdultLeech(e,dt);return;}
    if(content->hardy(e.monster)){updateHardy(e,dt);return;}
    if(content->danny(e.monster)){updateDanny(e,dt);return;}
    if(content->gaper(e.monster)){updateGaper(e,dt);return;}
    if(content->blackGlobin(e.monster)){updateBlackGlobin(e,dt);return;}
    if(content->leper(e.monster)){updateLeper(e,dt);return;}
    if(content->leperFlesh(e.monster)){updateLeperFlesh(e,dt);return;}
    if(content->rottenGaper(e.monster)){updateRottenGaper(e,dt);return;}
    if(content->smallMaggot(e.monster)){updateSmallMaggot(e,dt);return;}
    if(content->headless(e.monster)){updateHeadless(e,dt);return;}
    if(content->faceless(e.monster)){updateFaceless(e,dt);return;}
    if(content->slide(e.monster)){updateSlide(e,dt);return;}
    if(content->memBrain(e.monster)){updateMemBrain(e,dt);return;}
    if(content->lump(e.monster)){updateLump(e,dt);return;}
    if(content->leech(e.monster)){updateLeech(e,dt);return;}
    if(e.returningBody){updateReturningBody(e,dt);return;}
    if(content->vis(e.monster)){updateVis(e,dt);return;}
    if(content->guts(e.monster)){updateGuts(e,dt);return;}
    if(content->baby(e.monster)){updateBaby(e,dt);return;}
    if(content->linkedHead(e.monster)){updateLinkedHead(e,dt);return;}
    if(content->brain(e.monster)){updateBrain(e,dt);return;}
    if(content->cardinalWalker(e.monster)){updateCardinalWalker(e,dt);return;}
    if(content->spitty(e.monster)){updateSpitty(e,dt);return;}
    if(content->rockSpider(e.monster)){updateRockSpider(e,dt);return;}
    if(e.environment){updateEnvironmentActor(e,dt);return;}
    if(content->maw(e.monster)){updateMaw(e,dt);return;}
    if(content->eternalFly(e.monster)){updateEternalFly(e,dt);return;}
    if(content->host(e.monster)){updateHost(e,dt);return;}
    if(content->mushroom(e.monster)){updateMushroom(e,dt);return;}
    if(e.dyingEggy()){updateEggyDeath(e,dt);return;}
    if(content->targetHop(e.monster)){updateTargetHop(e,dt);return;}
    if(content->hornfelDecoy(e.monster))return; // Independent component update, outside vector iteration.
    if(content->boomFly(e.monster)){updateBoomFly(e,dt);return;}
    if(content->strider(e.monster)){updateStrider(e,dt);return;}
    if(content->longLegs(e.monster)){updateLongLegs(e,dt);return;}
    if(content->sack(e.monster)||content->boil(e.monster)){updateSack(e,dt);return;}
    if(content->swarmSpider(e.monster)){updateSwarmSpider(e,dt);return;}
    if(content->spider(e.monster)){updateSpider(e,dt);return;}
    if(content->willo(e.monster)){updateWillo(e,dt);return;}
    if(content->swimmer(e.monster)){updateSwimmer(e,dt);return;}
    if(content->evader(e.monster)){updateEvader(e,dt);return;}
    if(content->headShooter(e.monster)){updateHeadShooter(e,dt);return;}
    if(content->buzzFly(e.monster)){updateBuzzFly(e,dt);return;}
    if(content->lobWalker(e.monster)){updateLobWalker(e,dt);return;}
    if(content->flyBomb(e.monster)){updateFlyBomb(e,dt);return;}
    if(content->statue(e.monster)){updateStatue(e,dt);return;}
    if(content->component(e.monster)){updateOwnedComponent(e,dt);return;}
    if(content->charge(e.monster)){updateCharge(e,dt);return;}
    const auto &d = *content->monster(e.monster);
    const int t = type(e), v = variant(e);
    e.cooldown -= dt / (e.friendly ? 1.0f : EnemyCooldownMultiplier*arena.profile.cooldownScale);
    e.auxiliary -= dt;
    e.trailTime -= dt;
    e.age += dt;
    e.pathTime -= dt;
    e.flash = std::max(0.0f, e.flash - dt);
    e.fireContactCooldown = std::max(0.f,e.fireContactCooldown-dt);
    e.velocity = {};
    e.lift = 0;
    if(const auto *hop=content->hop(e.monster)) {
        updateHop(e,d,*hop,dt);
        return;
    }
    if(const auto *graph=content->behavior(d.behavior)) {
        updateBehavior(e,d,*graph,dt);
        return;
    }
    if(const auto *formation=content->formation(e.monster)) {
        if(e.state==EnemyState::Stunned) {
            e.stateTime-=dt;if(e.stateTime<=0)e.state=EnemyState::Ready;
            return;
        }
        updateFormationMember(e,*formation,dt);
        return;
    }
    if (t == 29 && v == 3 && e.phase > 0 && e.phase < 4 && e.auxiliary <= 0)
        attackMonster(e);
    auto target = player.position;
    if (e.friendly) {
        float best = 100000;
        for (const auto &other : enemies)
            if (other.alive && !other.friendly && other.id != e.id) {
                const float range = distance(e.position, other.position);
                if (range < best) {
                    best = range;
                    target = other.position;
                    e.partner = other.id;
                }
            }
        if (best == 100000)
            return;
    }
    const auto direction = flatDirection(e.position, target);
    const float dist = distance(e.position, target);
    const bool sight = arena.sight(e.position, target);
    if (t == 96) {
        const auto *parent = findEnemy(e.partner);
        if (!parent || !parent->alive) {
            if (parent && parent->monster == monsterId(55, 2)) {
                e.alive = false;
                return;
            }
            e.monster = monsterId(18);
            e.partner = 0;
            e.hp = e.maxHp = 32*content->regularHealthAdjustment(e.monster);
            return;
        }
    }
    if (t == 35 && (v == 1 || v == 3)) {
        const auto *parent = findEnemy(e.partner);
        if (!parent || !parent->alive) {
            e.monster = monsterId(26, v == 3 ? 1 : 0);
            e.partner = 0;
            return;
        }
    }
    if (e.state == EnemyState::Stunned) {
        e.stateTime -= dt;
        if (e.stateTime <= 0)
            e.state = EnemyState::Ready;
        return;
    }
    if (e.state == EnemyState::Collapsed) {
        e.stateTime -= dt;
        if (t == 24 && v == 1)
            moveMonster(e, mul(direction, -1.3f), dt);
        if (e.stateTime <= 0) {
            e.state = EnemyState::Ready;
            e.hp = e.maxHp;
            e.cooldown = .7f;
        }
        return;
    }
    if (e.state == EnemyState::Buried || e.state == EnemyState::Teleporting) {
        e.stateTime -= dt;
        if (e.stateTime <= 0) {
            if (!arena.blocked(e.target, e.radius) && !arena.reservedSupplyCache(e.target,e.radius) && distance(e.target, player.position) > 2)
                e.position = e.target;
            e.state = EnemyState::Exposed;
            e.stateTime = .6f;
            e.cooldown = .8f;
            e.target = target;
        }
        return;
    }
    if (e.state == EnemyState::Returning) {
        const auto *parent = findEnemy(e.partner);
        const auto destination = t == 35 && parent ? parent->position : e.home;
        moveMonster(e, mul(flatDirection(e.position, destination), 3), dt);
        if (distance(e.position, destination) < 1.3f) {
            e.state = EnemyState::Ready;
            e.cooldown = 1;
        }
        return;
    }
    if (e.state == EnemyState::Exposed) {
        e.stateTime -= dt;
        if (e.stateTime <= 0)
            e.state = EnemyState::Ready;
        return;
    }
    if (e.state == EnemyState::Jumping) {
        e.stateTime -= dt;
        const float progress = 1 - std::clamp(e.stateTime / .65f, 0.0f, 1.0f);
        e.lift = std::sin(progress * Pi) * (t == 34 ? 3 : 1.2f);
        moveMonster(e,
                    mul(flatDirection(e.position, e.target),
                        std::min(t == 34 ? 20.0f : d.speed,
                                 distance(e.position, e.target) / std::max(dt, e.stateTime))),
                    dt);
        if (e.stateTime <= 0) {
            e.state = EnemyState::Ready;
            e.cooldown = d.cooldown;
            e.lift = 0;
            if (d.attack != A::None) {
                e.target = target;
                if (t == 29 && v == 3)
                    e.phase = 0;
                attackMonster(e);
            }
            if ((t == 34 && v == 1) || (t == 29 && v == 2))
                monsterPatch(e, HazardKind::Tar, e.position, 1.6f, 0, 3);
            if (t == 840)
                monsterPatch(e, HazardKind::Creep, e.position, 1, 0, 3);
        }
    } else if (e.state == EnemyState::Charging) {
        e.stateTime -= dt;
        const auto before = e.position;
        const float speed = t == 41 && v == 1 ? 16 : t == 35 ? 12 : 11;
        moveMonster(e, mul(e.facing, speed), dt);
        const bool impact = distance(before, e.position) < speed * dt * .65f;
        if (impact || e.stateTime <= 0) {
            if (t == 41 && v == 4)
                monsterLines(e, HazardKind::Fire);
            if (t == 38) {
                e.target = target;
                attackMonster(e);
            }
            e.state = (t == 44 || t == 35) ? EnemyState::Returning : EnemyState::Stunned;
            e.stateTime = .7f;
            e.cooldown = d.cooldown;
        }
    } else if (e.state == EnemyState::Windup) {
        e.stateTime -= dt;
        if (e.stateTime <= 0) {
            e.cooldown = d.cooldown;
            e.state = EnemyState::Ready;
            if (d.motion == M::Charge || (t == 40 && v == 2)) {
                e.state = EnemyState::Charging;
                e.stateTime = 1.2f;
                e.facing = flatDirection(e.position, e.target);
            } else if (d.motion == M::Hop) {
                e.state = EnemyState::Jumping;
                e.stateTime = .65f;
            } else {
                attackMonster(e);
                if (t == 27) {
                    e.state = EnemyState::Exposed;
                    e.stateTime = .8f;
                }
                if (d.motion == M::Burrow)
                    e.auxiliary = .75f;
            }
        }
    } else {
        if (t == 30)
            e.hp = std::min(e.maxHp, e.hp + dt * 12*content->regularHealthAdjustment(e.monster));
        if (t == 861) {
            e.hp = std::min(e.maxHp, e.hp + dt * 3*content->regularHealthAdjustment(e.monster));
            if (e.age > 7) {
                e.monster = monsterId(61, 6);
                e.hp = e.maxHp = 48*content->regularHealthAdjustment(e.monster);
                e.radius = .5f;
            }
        }
        if ((t == 32 || (t == 40 && v == 1)) &&
            e.trailTime <= 0) {
            monsterPatch(e,
                         HazardKind::Creep,
                         e.position, .7f, 0, 2.6f);
            e.trailTime = .5f;
        }
        if ((t == 16 && v == 2 && dist < 1.4f) || (t == 16 && v < 2 && e.age > 12 && dist < 4)) {
            e.selfDetonated = true;
            Event death;
            death.type = EventType::Damage;
            death.target = e.id;
            death.damage = 10000;
            queueRoot(death);
        }
        Vector3 movement{};
        switch (d.motion) {
        case M::Still:
            break;
        case M::Chase:
        case M::Teleport:
        case M::Burrow:
            if (d.speed > 0)
                movement = mul(direction, d.speed);
            if (d.attack != A::None && dist < 5 && t != 10 && t != 87)
                movement = {};
            break;
        case M::Flee:
            movement = mul(direction, dist < 10 ? -d.speed : d.speed * .3f);
            break;
        case M::Mirror:
            movement = {-player.velocity.x, 0, -player.velocity.z};
            if (stats.shots != e.observedShots) {
                e.target = add(e.position, mul(unit(sub(player.aim, player.position)), -10));
                attackMonster(e);
            }
            e.observedShots = stats.shots;
            break;
        case M::Orbit: {
            // Legacy orbiters still use their old anchor until their formation
            // controller is ported; the anchor is not their population owner.
            const auto *parent = findEnemy(e.partner ? e.partner : e.summoner);
            auto center = parent && parent->alive ? parent->position : target;
            const auto goal = add(center, rotateY({t == 35 ? 1.1f : 1.6f, 0, 0}, e.age * 2 + float(e.id)));
            movement = mul(flatDirection(e.position, goal), std::min(6.0f, distance(goal, e.position) / dt));
            break;
        }
        case M::Wall: {
            float best = 1e9f;
            Vector3 anchor = e.home;
            for (const auto &wall : arena.walls) {
                const Vector3 p{std::clamp(e.position.x, wall.min.x, wall.max.x), .85f,
                                std::clamp(e.position.z, wall.min.z, wall.max.z)};
                if (distance(p, e.position) < best) {
                    best = distance(p, e.position);
                    anchor = p;
                }
            }
            auto away = flatDirection(anchor, e.position);
            movement = add(mul(rotateY(away, Pi / 2), d.speed), mul(away, (e.radius + .3f - best) * 2));
            break;
        }
        case M::Chain: {
            const auto *leader = findEnemy(e.partner);
            if (leader && leader->alive) {
                movement =
                    mul(flatDirection(e.position, leader->position),
                        d.speed * std::clamp(distance(e.position, leader->position) - .8f, 0.0f, 1.4f));
                break;
            }
            [[fallthrough]];
        }
        case M::Wander:
        case M::Charge:
        case M::Hop:
        case M::Bounce:
            if (d.motion != M::Bounce && e.auxiliary <= 0) {
                // With no active-item charges in DeathWard, Bulbs remain harmless wanderers.
                e.facing = rotateY({1, 0, 0}, t == 61 && v == 5 ? float(combatRng.bounded(4)) * Pi / 2
                                                                : combatRng.real(-Pi, Pi));
                e.auxiliary = combatRng.real(.7f, 1.8f);
            }
            movement = mul(e.facing, d.speed);
            if (d.motion == M::Hop)
                movement = {};
            if (t == 85 && dist < 7 && sight)
                movement = mul(direction, d.speed);
            break;
        }
        if (length(movement) > .1f && (d.motion == M::Chase || d.motion == M::Charge) &&
            !(d.flying?arena.flightClear(e.position,target,e.radius,room):arena.clear(e.position,target,e.radius))) {
            if (e.pathTime <= 0) {
                e.path = d.flying?arena.flightPath(e.position,target,e.radius,room):arena.path(e.position,target,e.radius);
                e.pathTime = 1.1f;
            }
            while (!e.path.empty() && planarDistance(e.position, e.path.front()) < .08f)
                e.path.erase(e.path.begin());
            if (!e.path.empty())
                movement = mul(flatDirection(e.position, e.path.front()), d.speed);
        }
        // Preserve exact mirroring/orbit positioning and committed jump/charge trajectories.
        if (!e.friendly && d.motion != M::Mirror && d.motion != M::Orbit)
            movement = mul(movement, EnemyMovementMultiplier);
        if (d.motion == M::Chase)
            movement = steerMonsterBodies(e, movement);
        const auto before = e.position;
        moveMonster(e, movement, dt);
        if (length(movement) > .1f && distance(before, e.position) < length(movement) * dt * .5f) {
            if (d.motion == M::Bounce) {
                // Reflect only the blocked component; never drift through a boundary.
                const auto probe = d.flying?arena.fly(before,{movement.x*dt,0,0},e.radius,room):arena.move(before, {movement.x * dt, 0, 0}, e.radius);
                if (std::abs(probe.x - before.x) < std::abs(movement.x * dt) * .5f)
                    e.facing.x = -e.facing.x;
                else
                    e.facing.z = -e.facing.z;
            } else {
                e.facing = rotateY(e.facing, Pi / 2);
                e.auxiliary = .4f;
            }
        }
        if (t == 60) {
            const float angle = std::atan2(e.facing.z, e.facing.x);
            const float delta = std::remainder(std::atan2(direction.z, direction.x) - angle, 2 * Pi);
            const float next = angle + std::clamp(delta, -dt * .9f, dt * .9f);
            e.facing = {std::cos(next), 0, std::sin(next)};
        } else if (length(movement) > .1f && d.motion != M::Bounce)
            e.facing = unit(movement);
        const bool aligned = (t == 23 && v == 3)
                                 ? std::abs(std::abs(direction.x) - std::abs(direction.z)) < .16f
                                 : std::abs(direction.x) < .18f || std::abs(direction.z) < .18f;
        bool attack = d.attack != A::None && d.motion != M::Mirror && sight && dist < 24;
        if (t == 30 && e.hp < e.maxHp - .1f)
            attack = false;
        if (t == 60 && v < 2)
            attack = attack && dot(e.facing, direction) > .97f;
        if (d.motion == M::Charge || (t == 40 && v == 2))
            attack = sight && aligned && dist < 22;
        if (d.motion == M::Hop)
            attack = true;
        if (e.cooldown <= 0 && attack) {
            e.state = EnemyState::Windup;
            if (!e.friendly)
                audioCues.push(AudioCueKind::Warning, e.position);
            e.stateTime = d.windup;
            e.target = target;
            if (d.motion == M::Hop && t != 34) {
                const auto hop = ((t == 29 && v == 1) || t == 54 || t == 884 || dist < 6)
                                     ? direction
                                     : rotateY({1, 0, 0}, combatRng.real(-Pi, Pi));
                e.target = add(e.position, mul(hop, d.speed * .65f));
            }
            if (t == 34 && distance(e.position, e.target) > 12)
                e.target = add(e.position, mul(direction, 12));
        }
        if ((d.motion == M::Burrow || d.motion == M::Teleport) && e.auxiliary <= 0 &&
            e.state == EnemyState::Ready) {
            const auto &bounds = arena.rooms[size_t(room)].bounds;
            for (int n = 0; n < 48; ++n) {
                Vector3 p{combatRng.real(bounds.min.x + 1, bounds.max.x - 1), .85f,
                          combatRng.real(bounds.min.z + 1, bounds.max.z - 1)};
                if (arena.blocked(p, e.radius) || arena.reservedSupplyCache(p,e.radius) || distance(p, target) < 3 || distance(p, target) > 14)
                    continue;
                e.target = p;
                e.state = d.motion == M::Burrow ? EnemyState::Buried : EnemyState::Teleporting;
                e.stateTime = 1;
                e.auxiliary = 5;
                break;
            }
        }
    }
    if (d.contact && e.lift < .8f && distance(e.position, target) < e.radius + .48f && sight) {
        if (e.friendly) {
            if (e.cooldown <= 0) {
                Event hit;
                hit.type = EventType::Damage;
                hit.target = e.partner;
                hit.damage = 28;
                queueRoot(hit);
                e.cooldown = .7f;
            }
        } else
            hurtPlayer(t == 24 ? 20 : 10);
    }
}

bool Simulation::collapseMonster(Enemy &e) {
    const auto *regrowth = content->regrowth(e.monster);
    if (!regrowth || e.state == EnemyState::Collapsed)
        return false;
    e.state = EnemyState::Collapsed;
    e.stateTime = regrowth->delay;
    // A scaled summoned body may start below the floor; collapse must never heal
    // its maximum HP up to an unscaled definition's minimum.
    e.maxHp = std::min(e.maxHp, std::max(regrowth->minimumHealth*content->regularHealthAdjustment(e.monster), e.maxHp * regrowth->healthRetention));
    e.hp = e.maxHp * regrowth->gooFraction;
    e.lift = 0;
    if (e.monster == monsterId(24, 2)) {
        queueMonster(monsterId(85), e.position, 0, e.generation + 1);
        monsterPatch(e, HazardKind::Tar, e.position, 1.3f, 0, 4);
    }
    if (e.regrowthSplits < regrowth->splitLimit) {
        ++e.regrowthSplits;
        queueMonster(e.monster, e.position, 0, e.generation + 1, true,
                     e.maxHp / content->monster(e.monster)->hp, e.regrowthSplits);
    }
    return true;
}
void Simulation::monsterDeathOffspring(const Enemy &e, const MonsterDeathRule &rule) {
    // Overkill uses post-hit health. Voluntary detonation is a distinct death cause,
    // so its synthetic lethal damage must not incorrectly suppress the offspring.
    if (!e.selfDetonated && rule.overkill && e.hp <= *rule.overkill*content->regularHealthAdjustment(e.monster))
        return;
    uint32_t totalWeight = 0;
    for (const auto &outcome : rule.outcomes) totalWeight += uint32_t(outcome.weight);
    int draws=1;
    if(rule.population) {
        const auto &p=*rule.population;
        // Native count is room-wide, not this parent's living offspring. Include
        // already reserved births so simultaneous deaths cannot evade the budget.
        draws=int(std::ceil(p.budget/(1+float(roomThreats()+pendingMonsters_.size())*p.crowdScale)));
        draws=std::max(p.minimum,draws+p.adjustment);
        if(p.capMinimum)draws=std::min(draws,p.capMinimum+int(combatRng.bounded(unsigned(p.capMaximum-p.capMinimum+1))));
    }
    std::vector<std::pair<MonsterId, float>> children;
    for(int draw=0;draw<draws;++draw) {
        auto choice=combatRng.bounded(totalWeight);
        for(const auto &outcome:rule.outcomes) {
            if(choice>=uint32_t(outcome.weight)){choice-=uint32_t(outcome.weight);continue;}
            for(const auto &group:outcome.offspring) {
                const int count=group.minimum+int(combatRng.bounded(uint32_t(group.maximum-group.minimum+1)));
                for(int n=0;n<count;++n)children.emplace_back(group.monster,group.healthScale);
            }
            break;
        }
    }
    auto axis = rule.layout == OffspringLayout::Perpendicular
        ? rotateY(flatDirection(e.position, player.position), Pi / 2) : Vector3{1, 0, 0};
    if(rule.layout==OffspringLayout::Perpendicular&&planarDistance(e.position,player.position)<.001f)axis=rotateY({1,0,0},combatRng.real(0,2*Pi));
    for (size_t n = 0; n < children.size(); ++n) {
        const float angle=rule.population?combatRng.real(0,2*Pi):float(n)*2*Pi/float(children.size());
        const float spacing=rule.population?std::max(rule.population->radiusMinimum,combatRng.real(0,rule.population->radiusMaximum)):rule.spacing;
        auto at=add(e.position,mul(rotateY(axis,angle),spacing));
        std::optional<ThrownOffspringRuntime> thrown;
        if(rule.launch) {
            thrown=ThrownOffspringRuntime{};thrown->profile=*rule.launch;thrown->origin=e.position;thrown->origin.y=.85f;
            at=add(thrown->origin,add(mul(rotateY(axis,angle),combatRng.real(0,rule.launch->radius)),
                mul(rotateY(axis,combatRng.real(0,2*Pi)),rule.launch->scatter)));
        }
        queueMonster(children[n].first,at,0,e.generation+1,false,children[n].second,0,0,0,-1,{},bool(rule.population)||bool(thrown)||rule.impulse>0,thrown,mul(rotateY(axis,angle),rule.impulse));
    }
}
void Simulation::monsterDeath(Enemy &e, const Event &event) {
    if(content->hardy(e.monster))return; // Exact death child handled with damage.
    if(content->rockSpider(e.monster))return; // In-place death morph / retained hot coal handled with damage.
    if(content->slide(e.monster))return; // Exact non-debug offspring are processed with damage.
    if(content->memBrain(e.monster))return; // Required children also survive ordinary execution deaths.
    if(content->linkedHead(e.monster))return; // Linked transitions also run for non-debug executions.
    if(content->spitty(e.monster))return; // Death packet also covers non-debug execution.
    if(content->boomFly(e.monster))return; // Includes non-debug execution; handled by process(Damage).
    if(content->flyBomb(e.monster))return; // Distinct contact/death ordnance is handled even for execution deaths.
    const int t = type(e), v = variant(e);
    if(const auto *cross=content->deathCross(e.monster)) {
        for(int n=0;n<4;++n)shootEnemy(e,rotateY({1,0,0},cross->angle+float(n)*Pi/2),cross->damage,cross->speed);
        if(cross->creepRadius>0) {
            Hazard h;h.kind=cross->creepDamage>0?HazardKind::Creep:HazardKind::Tar;h.position={e.position.x,.85f,e.position.z};h.delay=0;
            h.radius=cross->creepRadius;h.duration=cross->creepDuration;h.damage=cross->creepDamage;
            h.context.sourceEntity=e.id;h.tint={36,32,43,220};addHazard(h);
        }
        return;
    }
    // Resolve orbiters before room completion can remove a defeated parent's last threat.
    for (auto &child : enemies) {
        if (!child.alive || child.partner != e.id || child.monster != monsterId(96))
            continue;
        if(content->eternalFly(child.monster)) {
            releaseEternalFly(child);continue;
        }
        if (t == 55 && v == 2)
            child.alive = false;
        else {
            child.monster = monsterId(18);
            child.partner = 0;
            child.hp = child.maxHp = 32*content->regularHealthAdjustment(child.monster);
        }
    }
    auto offspring = [&](MonsterId id, int count) {
        for (int n = 0; n < count; ++n)
            queueMonster(id, add(e.position, rotateY({1, 0, 0}, float(n) * 2 * Pi / float(count))), 0,
                         e.generation + 1);
    };
    auto bomb = [&] { monsterPatch(e, HazardKind::MonsterBomb, e.position, 2.8f, .7f, 0); };
    if (const auto *rule = content->deathRule(e.monster))
        monsterDeathOffspring(e, *rule);
    if (t == 16&&!content->evader(e.monster)) {
        if (v == 0 && e.selfDetonated)
            monsterPattern(e, 4);
        if (v == 1) {
            bomb();
            monsterPattern(e, e.selfDetonated ? 8 : 4, Pi / 4);
        }
        if (v == 2)
            monsterPatch(e, HazardKind::MonsterBomb, e.position, 2.8f, 0, 0);
    }
    if (const auto *c=content->charge(e.monster);c&&c->deathShots){e.chargeDeathPending=true;flushChargeDeath(e);}
    if (t == 24 && v == 2)
        monsterPatch(e, HazardKind::Tar, e.position, 1.6f, 0, 4);
    if(const auto *p=content->maw(e.monster);p&&p->deathShots) {
        if(!e.maw)e.maw=MawRuntime{};
        e.maw->deathPending=true;shootMawDeath(e);
    } else if (t == 26 && v == 1)monsterPattern(e,4);
    if (t == 29 && v == 2 && !content->eggy(e.monster))
        offspring(monsterId(884), 5);
    if (t == 31 && v == 1) {
        monsterPattern(e, 8);
        monsterPattern(e, 8, Pi / 8, 6);
    }
    if (t == 35) {
        if (v == 0 || v == 2)
            offspring(monsterId(11), 1);
        else if (auto *parent = findEnemy(e.partner); parent && parent->alive) {
            parent->monster = monsterId(11);
            parent->hp = parent->maxHp = 40*content->regularHealthAdjustment(parent->monster);
        }
    }

    if (t == 55 && v > 0 && !content->deathBlast(e.monster))
        bomb();
    if (t == 57)
        offspring(v == 0 ? monsterId(32) : v == 1 ? monsterId(40) : monsterId(862), 2);
    if (t == 61) {
        if (v == 0 || v == 6)
            monsterPattern(e, 4);
        if (v == 1)
            monsterPatch(e, HazardKind::MonsterBomb, player.position, 2.2f, 1, 0);
        if (v == 2)
            for (int n = 0; n < 4; ++n)
                monsterBeam(e, rotateY({1, 0, 0}, float(n) * Pi / 2), .9f);
        if (v == 3) {
            monsterPattern(e, 4, Pi / 4, 9, ProjectileKind::Tar);
            monsterPatch(e, HazardKind::Tar, e.position, 2, 0, 4);
        }
        if (v == 4)
            offspring(monsterId(853), 4);
        if (v == 7)
            monsterPattern(e, 6, 0, 7, ProjectileKind::BurstShot);
    }
    if (t == 861) {
        offspring(monsterId(853), 2);
        monsterPatch(e, HazardKind::Creep, e.position, 1.6f, 0, 4);
    }
    (void)event;
}
} // namespace dw
