#pragma once
#include "audio/AudioState.hpp"
#include "combat/Monsters.hpp"
#include "content/Mechanics.hpp"
#include "core/Types.hpp"
#include "world/Campaign.hpp"
#include "world/Dungeon.hpp"
#include "world/Particles.hpp"
#include <deque>
#include <functional>
#include <optional>
#include <unordered_map>

namespace dw {
enum class MessageKind { Notice, Debug, ThrowAim };
enum class EnemyKind {
    Rusher,
    Gunman,
    Shotgun,
    Sharpshooter,
    Prospector,
    Ironhide,
    Railbreaker,
    Preacher,
    BellRinger,
    Hangman,
    Spitter,
    Marshal,
    Wraith,
    PowderHusk,
    Chainbound,
    Boss,
    Monster,
    Count
};
inline constexpr int OrdinaryEnemyCount = int(EnemyKind::Boss);
struct EnemyDefinition {
    const char *name;
    float hp, radius, speed, windup, cooldown;
};
const EnemyDefinition &enemyDefinition(EnemyKind kind);
enum class EnemyState {
    Ready,
    Windup,
    Charging,
    Stunned,
    Teleporting,
    Collapsed,
    Buried,
    Jumping,
    Exposed,
    Returning
};
const char *bossName(BossKind kind);
struct Enemy;
struct Event;
struct CreatureCycleRuntime {
    float clock=0,timer=0,phaseTime=0;
    int phase=0,frame=0;
    bool initialized=false,near=false,inflated=false,deathPending=false;
    Vector3 origin{},target{},momentum{};
    std::deque<Event> pending;
};
struct AdaptiveArmorRuntime {
    float clock=0,recentDps=0,multiplier=1;
    uint64_t ticks=0,batches=0;
    std::deque<float> history;
    std::vector<Event> pending;
};
const char *bossHint(const Enemy &enemy);
struct FlyBombFollowRuntime {
    EntityId parent=0;
    float clock=0;
    uint64_t tick=0;
    Vector3 momentum{},wander{},target{}; // Native planar units per 30 Hz tick.
};
struct EnvironmentActorRuntime {
    bool spent=false,destructionPending=false,explosiveHit=false;
    uint64_t hits=0,baseLoss=0;
    float accumulatedDamage=0;
};
struct LobWalkerRuntime {
    float clock=0;
    int attackFrame=-1;
    bool fired=false;
};
struct AxisWanderRuntime {
    float clock=0;
    Vector3 destination{},momentum{};
    bool hasDestination=false;
    int stuckTicks=0,walkFrame=0,walkAxis=-1;
    uint64_t ticks=0;
};
struct LeechRuntime : AxisWanderRuntime {
    bool initialized=false,charging=false,blocked=false;
    int chargeStuckTicks=0;
    Vector3 chargeDirection{},predictedTarget{},lastPosition{};
    uint64_t charges=0,stops=0;
};
struct MirrorRuntime {
    float clock=0;
    int cooldown=0,observedDelay=0,eye=1,shootFrame=0;
    bool initialized=false;
    uint64_t ticks=0,volleys=0,terrainCorrections=0;
    Vector3 desired{},shotVelocity{},shotOrigin{},inheritedVelocity{};
    bool pending=false;
};
struct SpittyRuntime : AxisWanderRuntime {
    Vector3 attackDirection{1,0,0};
    bool fired=false,deathPending=false;
    int attackFrame=-1,pendingBurst=0;
    uint64_t volleys=0,bursts=0;
};
struct VisRuntime : AxisWanderRuntime {
    Vector3 heading{0,0,1};
    int attackFrame=-1;
    bool initialized=false,fired=false;
    uint64_t volleys=0;
};
struct ReturningBodyMotion {
    Vector3 from{},to{};
    float begin=0,end=1; // Fraction of the current Simulation::step.
};
struct ReturningBodyRuntime {
    Vector3 initialVelocity{};
    float clock=0;
    int frame=0;
    std::vector<ReturningBodyMotion> motion;
};
struct GutsRuntime {
    Vector3 momentum{},destination{},chargeDirection{},predictedTarget{},gaze{0,0,1};
    float clock=0,multiplier=1,arrival=.1f,rollPhase=0;
    int direction=-1,windup=-1,recovery=60,rollFrame=0,hitFrame=-1;
    bool initialized=false,hasDestination=false,turned=false,charging=false,frameReady=false;
    std::optional<Vector3> pendingCreep;
    uint64_t ticks=0,turns=0,charges=0,stops=0,creepPatches=0;
    int shotTimer=0,shotFrame=-1;
    uint64_t shots=0;
    std::vector<Event> pendingShots;
};
enum class AdultLeechPhase { Wander, Charge, Burrow, Hidden, Fall };
struct AdultLeechRuntime {
    AdultLeechPhase phase=AdultLeechPhase::Wander;
    Vector3 momentum{},heading{},anchor{},impactVelocity{},impactNormal{};
    float clock=0,gain=.5f,chargeSign=1,visibility=1,walkPhase=0;
    int frame=0,recovery=0,hidden=0,pendingRing=-1;
    bool initialized=false,frameReady=false,blocked=false,burrowUsed=false,intangible=false,anchored=false;
    uint64_t ticks=0,charges=0,stops=0,impacts=0,burrows=0,landings=0,wallRings=0,landingRings=0;
    std::vector<Event> pendingShots;
};
struct SlideRuntime {
    Vector3 momentum{};
    float clock=0,animation=0;
    int phase=0,frame=0,slideFrames=0,collisions=0;
    bool initialized=false,frameReady=false,blocked=false;
    uint64_t ticks=0,dashes=0;
    bool secondDash=false;
    uint64_t launches=0,chains=0,creepPatches=0;
    std::optional<Vector3> pendingCreep;
    std::vector<Event> deathShot; // At most one; Event is forward-declared here.
};
struct MemBrainRuntime {
    Vector3 momentum{},destination{};
    float clock=0,walkPhase=0;
    float attackFrame=-1;
    int birthChoice=-1;
    uint64_t births=0,pushes=0;
    bool initialized=false,targetReady=false,blocked=false,fired=false,frameReady=false;
    uint64_t ticks=0,attacks=0,volleys=0;
    std::vector<Event> pendingShots;
};
struct MaskArmorRuntime {
    Vector3 facing{0,0,1};
    float turnGrace=0;
    bool initialized=false;
    uint64_t reflections=0;
};
struct KnightRuntime : AxisWanderRuntime {
    Vector3 chargeDirection{},predictedTarget{},impactNormal{},impactVelocity{},pendingOrigin{},pendingDirection{};
    bool initialized=false,charging=false,blocked=false,pendingImpact=false;
    int recovery=0;
    float liftVelocity=0;
    uint64_t charges=0,stops=0,impacts=0,impactBursts=0;
};
struct LinkedRemnantRuntime {
    bool initialized=false,waiting=false;
};
struct LandingCreepRuntime {
    std::vector<Vector3> pending;
    uint64_t patches=0,releases=0;
};
struct BrainRuntime : AxisWanderRuntime {
    bool initialized=false,charging=false,blocked=false;
    float walkPhase=0;
    Vector3 chargeDirection{},predictedTarget{};
    std::optional<Vector3> pendingCreep;
    uint64_t charges=0,stops=0,creepPatches=0;
};
struct LinkedHeadRuntime {
    float clock=0,walkPhase=0,neckRadius=.09f;
    uint64_t ticks=0,throws=0,returns=0;
    int timer=0,neckCount=0;
    bool initialized=false,extended=false,deathPending=false;
    Vector3 momentum{},predictedTarget{};
    std::array<Vector3,16> neckPoints{};
};
enum class LumpPhase { Ready, Spitting, Hiding, Hidden, Appearing };
struct LumpRuntime {
    LumpPhase phase=LumpPhase::Ready;
    float clock=0,visibility=1;
    uint64_t ticks=0,volleys=0,burrows=0,relocations=0;
    int frame=0,cooldown=0;
    bool initialized=false,intangible=false,fired=false;
    Vector3 anchor{};
    std::vector<Event> pendingShots;
};
enum class BabyPhase { Ready, Vanishing, Appearing, DashStart, Dashing };
struct BabyRuntime {
    BabyPhase phase=BabyPhase::Ready;
    float clock=0,teleportCharge=0,walkPhase=0,visibility=1;
    uint64_t ticks=0,volleys=0,teleports=0,dashes=0;
    int frame=0,attackFrame=-1,cooldown=0,recentDamageFrames=0;
    bool initialized=false,fired=false,intangible=false,blocked=false;
    Vector3 momentum{},dashTarget{},dashDirection{};
    std::optional<Vector3> destination;
};
struct HeadShooterRuntime {
    float clock=0;
    float timerFraction=0,animationFraction=0;
    uint64_t tick=0;
    int attackFrame=-1;
    bool fired=false,initialized=false;
    float angle=0,shotFrames=0;
    std::vector<Event> pendingShots;
};
struct MawRuntime {
    HeadShooterRuntime cast;
    Vector3 momentum{};
    bool deathPending=false;
};
struct EternalFlyRuntime {
    float clock=0;
    uint64_t tick=0;
    int orbitTicks=0,phase=0;
    bool initialized=false;
};
struct BuzzFlyRuntime {
    float clock=0;
    uint64_t tick=0;
    Vector3 momentum{},wander{},target{}; // Source planar units per 30 Hz update.
    int attackFrame=-1;
    bool fired=false,initialized=false;
    bool diesOnContact=false,targetReady=false;
    float contactRetention=1;
    int healingTicks=0,healingDivisor=60;
};
struct EvaderRuntime {
    float clock=0, cooldown=0;
    uint64_t tick=0,lifeTicks=0;
    int evadeChecks=0, attackFrame=-1,detonationFrame=-1;
    bool initialized=false, fired=false, targetReady=false,gridCollision=false;
    Vector3 momentum{}, destination{};
};
enum class EnemyStatus { Fear, Confusion, Freeze, Slow, Poison, Burn, Shrink, Charm };
struct StatusDamageTick {float damage=0;Vector3 position{};Context source;};
struct DamageStatusRuntime {
    int frames=0,elapsed=0;
    float damage=0;
    Context source;
    std::optional<StatusDamageTick> pending;
};
struct EnemyStatusRuntime {
    int fear=0,confusion=0,freeze=0,slow=0,shrink=0,charm=0;
    EntityId charmTarget=0;
    uint64_t charmFrame=0,charmLastPoll=~uint64_t(0);
    float visualScale=1,unshrunkRadius=0;
    bool squashed=false,squashQueued=false;
    DamageStatusRuntime poison,burn;
    float clock=0;
    float animationDelay=0,frozenPoseTime=0,frozenSpeed=0;
    uint64_t ticks=0;
    std::optional<Vector3> confusedTarget;
    EvaderRuntime flee;
};
struct CharmContactHit {EntityId target=0;float damage=0;Vector3 origin{},position{};};
struct CharmContactRuntime {
    uint64_t cycle=~uint64_t(0);
    Vector3 previous{};
    bool motionReady=false;
    std::vector<EntityId> touched;
    std::optional<CharmContactHit> pending;
};
struct LeperRuntime {
    struct FleshBirth { Vector3 position{},velocity{}; };
    EvaderRuntime evade;
    float clock=0,walkPhase=0,friction=1;
    int ticks=0,walkFrame=0,chase=0,transition=0,births=0,batches=0,creepPatches=0;
    bool initialized=false,frameReady=false,deathReleased=false;
    std::optional<Vector3> pendingCreep;
    float creepRadius=0,creepDamage=0,creepDuration=0,creepFadeDuration=0,creepFadeScale=1;
    std::vector<Event> pendingDamage;
    std::vector<Event> applyingDamage;
    std::vector<FleshBirth> frameFlesh;
};
struct SwimmerRuntime {
    float clock=0, acceleration=0;
    int hopFrame=-1;
    bool swimming=false;
    Vector3 momentum{};
};
struct HostRuntime {
    float clock=0,blockedDamage=0;
    uint64_t tick=0,lifeTicks=0;
    int frame=-1,delay=0,cooldown=0;
    bool initialized=false,fired=false,exposed=false,shake=false;
    Vector3 momentum{};
};
enum class MushroomPhase { InitialHide, Blocking, Reveal, Revealed, Hide };
struct MushroomRuntime {
    MushroomPhase phase=MushroomPhase::InitialHide;
    float clock=0,opening=0;
    int frame=0,timer=0;
    bool initialized=false,diagonal=false,fired=false;
    Vector3 anchor{};
    bool blocking() const {return phase==MushroomPhase::InitialHide||phase==MushroomPhase::Blocking;}
};
struct SpiderRuntime {
    float clock=0;
    int counter=0;
    bool initialized=false,targetReady=false,pursuing=false,diesOnContact=false;
    Vector3 destination{},momentum{};
};
struct GaperRuntime {
    float clock=0,eyeOpenness=0,walkPhase=0,force=0;
    float animationFraction=0,headFraction=0;
    int ticks=0,headFrame=0,walkFrame=0;
    bool initialized=false,frameReady=false,wakeStarted=false,directPath=false;
    Vector3 momentum{},destination{};
};
struct BlackGlobinRuntime {
    float clock=0,lastEmissionHP=0,walkPhase=0;
    int ticks=0,walkFrame=0,births=0;
    bool initialized=false,frameReady=false,deathReleased=false;
    Vector3 momentum{},destination{};
};
struct LeperFleshRuntime {
    float clock=0,animation=0;
    int ticks=0,shape=0;
    bool initialized=false,frameReady=false,flip=false,deathReleased=false;
    Vector3 momentum{};
    std::vector<Event> pendingShots;
};
struct RottenGaperRuntime {
    float clock=0,force=0,walkPhase=0;
    int ticks=0,walkFrame=0,spawnCounter=0,remember=0,evadeChecks=0;
    uint64_t spawnRolls=0,births=0;
    EntityId avoid=0;
    bool initialized=false,frameReady=false,orbitDirect=false,evading=false,targetReady=false;
    Vector3 momentum{},destination{};
};
struct SmallMaggotRuntime {
    float clock=0,force=0,curve=0;
    int ticks=0,cooldown=0,walkFrame=0,walkAxis=-1;
    bool initialized=false,frameReady=false,alert=false,blocked=false;
    uint64_t turns=0,alerts=0;
    Vector3 momentum{},heading{};
};
struct HeadlessRuntime {
    float clock=0;
    float timerFraction=0,animationFraction=0;
    int ticks=0,animationTicks=0,cooldown=0,shots=0,births=0;
    bool initialized=false,frameReady=false,targetReady=false,blocked=false;
    Vector3 momentum{},destination{};
    std::vector<Event> pendingShots;
    bool scarred=false;
};
struct FacelessRuntime {
    float clock=0,recentDamage=0,incomingDamage=0;
    int frame=-1,attacks=0;
    bool initialized=false,aggressive=false,fired=false,frameReady=false,targetReady=false,blocked=false;
    Vector3 momentum{},destination{};
    std::vector<Event> pendingShots;
};
struct DannyRuntime {
    float clock=0,recentDamage=0,incomingDamage=0;
    int frame=-1,cooldown=0,attacks=0,children=0;
    bool initialized=false,fired=false,frameReady=false,waitingBirths=false;
    Vector3 momentum{},destination{};
    std::vector<Event> pendingShots;
};
struct HardyRuntime {
    int phase=0,frame=0,cooldown=0,impacts=0,collisions=0,slideFrames=0,launches=0;
    uint64_t ticks=0;
    float clock=0;
    bool initialized=false,lethalImpact=false,blocked=false;
    Vector3 momentum{};
    std::vector<Event> pendingShots;
};
enum class RockSpiderPhase { Rock, Appearing, Skitter };
struct RockSpiderRuntime {
    RockSpiderPhase phase=RockSpiderPhase::Rock;
    float clock=0,height=0,vertical=0;
    int frame=0,counter=0,selections=0,cycles=0;
    uint64_t ticks=0;
    bool initialized=false,pursuing=false;
    Vector3 heading{},momentum{};
};
struct LongLegsRuntime {
    float clock=0;
    int frame=-1,evadeChecks=0,attacks=0;
    uint64_t tick=0;
    bool initialized=false,targetReady=false,fired=false;
    Vector3 destination{},momentum{};
};
struct SackRuntime {
    float clock=0,growth=0,previousHp=0;
    int frame=-1,attacks=0,shots=0;
    bool initialized=false,fired=false,shake=false,targetReady=false;
    Vector3 destination{},momentum{};
};
struct StriderRuntime {
    float clock=0,angle=Pi/2;
    int frame=-1,strokes=0;
    bool initialized=false,chasing=false;
    Vector3 direction{},momentum{};
};
struct SwarmSpiderRuntime {
    float clock=0;
    int frame=-1,kind=0,hops=0;
    bool initialized=false,airborne=false;
    Vector3 launch{},momentum{};
};
struct EggyRuntime {
    float clock=0;
    int frame=0,released=0,creepPatches=0,restarts=0;
    bool dying=false,finishing=false;
    Context deathContext;
    Vector3 anchor{};
};
struct WilloRuntime {
    float clock=0,angle=0,slot=0,attackSlot=0;
    uint64_t members=0;
    int attackFrame=-1;
    bool fired=false,warning=false;
};
struct ThrownOffspringRuntime {
    OffspringLaunch profile;
    Vector3 origin{}, step{};
    float clock=0, height=0, verticalVelocity=0;
    int frames=0, duration=0;
};
struct Enemy {
    EntityId id = 0;
    EnemyKind kind = EnemyKind::Rusher;
    BossKind bossKind = BossKind::None;
    BossForm bossForm=BossForm::Normal;
    unsigned bossParts=0; // Successful threshold components; destroyed eyes never respawn.
    EntityId bossGroup=0; // Independent boss bodies sharing one encounter payout.
    int bossHalf=0;
    EntityId componentOwner=0;
    int componentSlot=-1;
    EntityId segmentedEncounter=0;
    float segmentArmor=0;
    bool segmentHead=false;
    bool segmentSettling=false;
    int bossCombo = 0, bossCycles = 0;
    int bossAttack = 0, bossStep = 0, bossTargetCount = 0;
    std::array<Vector3,3> bossTargets{};
    Vector3 position{}, velocity{};
    float hp = 40, maxHp = 40, radius = 0.65f, cooldown = 1, flash = 0, age = 0;
    int phase = 0;
    bool alive = true;
    EnemyState state = EnemyState::Ready;
    Vector3 facing{0, 0, -1}, target{};
    float stateTime = 0, aura = 0, pathTime = 0;
    EntityId partner = 0;
    EntityId summoner = 0; // Population ownership, independent of paired parts / current attack target.
    int spawnerType=0; // Original creator type; survives detachment and removal of the creator.
    EntityId formation = 0; // Independent group identity; survives its founding member.
    std::vector<Vector3> path;
    MonsterId monster{};
    int generation = 0;
    float auxiliary = 0, trailTime = 0, lift = 0;
    float beamCooldown=0, chargeRecovery=0;
    Vector3 home{};
    uint64_t observedShots = 0;
    bool awakened = false, friendly = false;
    bool permanentCharmed = false;
    int chargeDeathShot=0;
    bool chargeDeathPending=false;
    std::optional<CreatureCycleRuntime> creature;
    int champion=-1,championDeathShot=0;
    float championSpeed=1,championVisual=1,championDamage=1,championTrail=0,championAbility=1.2f;
    Color championTint{};
    bool championDeathPending=false,championPile=false,championOrbiter=false,crowned=false;
    int championDeathStage=0;
    std::vector<EntityId> championTargets;
    bool championEffect(int id) const {
        return champion==id||(champion==25&&(id==2||id==5||id==10||id==11||id==13||id==17));
    }
    float championVisibility() const {
        if(flash>0)return 1;
        return champion==14?.12f:champion==9?.08f+.92f*(.5f+.5f*std::sin(age*2.5f)):1.f;
    }
    std::optional<EnemyStatusRuntime> statuses;
    std::optional<CharmContactRuntime> charmContact;
    bool affectedBy(EnemyStatus status) const {
        if(!statuses)return false;
        switch(status) {
        case EnemyStatus::Fear:return statuses->fear>0;
        case EnemyStatus::Confusion:return statuses->confusion>0;
        case EnemyStatus::Freeze:return statuses->freeze>0;
        case EnemyStatus::Slow:return statuses->slow>0;
        case EnemyStatus::Poison:return statuses->poison.frames>0;
        case EnemyStatus::Burn:return statuses->burn.frames>0;
        case EnemyStatus::Shrink:return statuses->shrink>0;
        case EnemyStatus::Charm:return permanentCharmed||statuses->charm>0;
        }
        return false;
    }
    bool selfDetonated = false;
    std::optional<FlyBombFollowRuntime> flyFollow;
    std::optional<EnvironmentActorRuntime> environment;
    std::optional<LobWalkerRuntime> lob;
    std::optional<HeadShooterRuntime> headShooter;
    std::optional<MawRuntime> maw;
    std::optional<SpittyRuntime> spitty;
    std::optional<AxisWanderRuntime> cardinalWalker;
    std::optional<BrainRuntime> brain;
    std::optional<VisRuntime> vis;
    std::optional<GutsRuntime> guts;
    std::optional<MirrorRuntime> mirror;
    std::optional<AdultLeechRuntime> adultLeech;
    std::optional<MemBrainRuntime> memBrain;
    std::optional<SlideRuntime> slide;
    std::optional<LumpRuntime> lump;
    std::optional<LeechRuntime> leech;
    std::optional<MaskArmorRuntime> maskArmor;
    std::optional<KnightRuntime> knight;
    std::optional<LinkedRemnantRuntime> linkedRemnant;
    std::optional<LandingCreepRuntime> landingCreep;
    std::optional<ReturningBodyRuntime> returningBody;
    std::optional<LinkedHeadRuntime> linkedHead;
    std::optional<BabyRuntime> baby;
    std::optional<EternalFlyRuntime> eternalFly;
    std::optional<HostRuntime> host;
    std::optional<MushroomRuntime> mushroom;
    std::optional<TargetHopRuntime> targetHop;
    std::optional<LeaperRuntime> leaper;
    std::optional<EggyRuntime> eggy;
    std::optional<AdaptiveArmorRuntime> adaptiveArmor;
    std::optional<HopRingRuntime> hopRings;
    std::optional<BuzzFlyRuntime> buzz;
    std::optional<EvaderRuntime> evader;
    std::optional<SwimmerRuntime> swimmer;
    std::optional<WilloRuntime> willo;
    std::optional<SpiderRuntime> spider;
    std::optional<RockSpiderRuntime> rockSpider;
    std::optional<HardyRuntime> hardy;
    std::optional<DannyRuntime> danny;
    std::optional<GaperRuntime> gaper;
    std::optional<BlackGlobinRuntime> blackGlobin;
    std::optional<LeperFleshRuntime> leperFlesh;
    std::optional<LeperRuntime> leper;
    std::optional<RottenGaperRuntime> rottenGaper;
    std::optional<SmallMaggotRuntime> smallMaggot;
    std::optional<HeadlessRuntime> headless;
    std::optional<FacelessRuntime> faceless;
    std::optional<StriderRuntime> strider;
    std::optional<LongLegsRuntime> longLegs;
    std::optional<SackRuntime> sack;
    std::optional<SwarmSpiderRuntime> swarmSpider;
    std::optional<ThrownOffspringRuntime> thrownOffspring;
    EntityId railCarrier=0; // Physical attachment; independent of summoner/Parent.
    int regrowthSplits = 0;
    BehaviorRuntime behavior;
    HopRuntime hop;
    float idleTime = 0;
    float fireContactCooldown = 0;
    float companionAttackCooldown=0, companionHurtCooldown=0;
    std::optional<ItemKey> companionItem;
    bool statueDisabled=false;
    bool statuePullActive=false;
    double statuePhase=0;
    Vector3 statueFacing{0,0,-1};
    unsigned statueVolley=0;
    float supplyCooldown=0;
    unsigned supplyProduced=0;
    int supplyDeathPending=0;
    bool deathBlastPending=false;
    bool dyingEggy() const {return eggy&&eggy->dying;}
    float animationTime() const {
        if(affectedBy(EnemyStatus::Freeze))return statuses->frozenPoseTime;
        return age + idleTime - (statuses?statuses->animationDelay:0);
    }
    float animationSpeed() const {return affectedBy(EnemyStatus::Freeze)?statuses->frozenSpeed:length(velocity);}
};
struct PlayerLaunch {
    float clock=0,height=0,up=0,gravity=0,retention=.8f,baseY=.85f;
    Vector3 impulse{};
};
struct Player {
    Vector3 position{0, 0.85f, 10}, aim{0, 0.85f, 0};
    Vector3 velocity{}, facing{0, 0, -1};
    float shootPose = 0;
    bool dodgeMoving = false;
    float baseHealth = StartingHealth, shotDamage = RevolverDamage;
    float hp = StartingHealth, maxHp = StartingHealth, fireCooldown = 0, dodge = 0, dodgeCooldown = 0,
          hurt = 0;
    Vector3 dodgeDirection{0, 0, -1};
    int nextRound = 1;
    Vector3 pullTarget{};
    float pullTime = 0;
    float slowTime = 0;
    std::optional<PlayerLaunch> launch;
};
enum class ProjectileKind { Bullet, Hook, Homing, SplitShot, BurstShot, Tar, Flame, ReturningHead, Rock, Ember, Brown, Yellow, Ipecac, Bone, Green, DarkBone };
// A projectile's birth specification survives hits and explosions. Secondary
// effects never reinterpret blast damage as weapon damage or reapply stat taxes.
struct AttackSpec {
    Vector3 heading{0,0,-1};
    float damage = RevolverDamage, speed = 26, life = 3.2f, radius = .14f;
    float homingTurn = 0, returnRange = 0, capDamage = 0, capRadius = 0, capSelfDamage = 0;
    int bounces = 0, pierce = 0;
    bool scatter = false, rail = false;
};
struct Projectile {
    EntityId id = 0;
    Vector3 position{}, previous{}, origin{}, velocity{};
    float damage = RevolverDamage, life = 3.2f, radius = 0.14f;
    bool hostile = false, lastRound = false, ghost = false, alive = true, cancelled = false;
    // NPC projectile policy is independent of player AttackSpec conversion.
    bool hitsEnemies=false,ignoresPlayer=false;
    float npcDamage=0;
    int bounces = 0, pierce = 0;
    ProjectileKind kind = ProjectileKind::Bullet;
    Context context;
    std::vector<EntityId> hitEntities;
    AttackSpec attack;
    bool returning = false, phaseSpent = false, capSpent = false;
    float traveled = 0, guidanceTime = 0;
    EntityId guidedTarget = 0;
    float angularVelocity = 0; // Radians/second about world up, independent of shooter lifetime.
    DamageKind damageKind = DamageKind::Physical;
    float gravity=0,blastRadius=0,blastDamage=0;
    float flightRetention=0,blastPlayerDamage=-1;
    float sourceTimeScale=1;
    std::optional<HostileHomingDefinition> sourceHoming;
    std::optional<SourcePlanarMotionDefinition> sourcePlanarMotion;
    float planarClock=0;
    uint32_t planarTicks=0;
    float homingClock=0;
    FireWaveDefinition fireWave;
    bool impactPending=false;
    std::optional<ProjectileSplitDefinition> impactSplit;
    std::optional<ProjectileBurstDefinition> sourceBurst;
    bool physicalImpact=false;
    bool championSpectral=false;
    bool noWallCollision=false;
    bool repeatWallBounce=false; // Reflect lateral terrain hits until landing/lifetime, without a bounce budget.
    Color tint{0,0,0,0}; // Optional visual tint; does not change impact mechanics.
};
enum class EventType {
    Shot,
    ProjectileHit,
    ProjectileBounce,
    Damage,
    EnemyDamaged,
    EnemyKilled,
    Explosion,
    PlayerDamaged,
    RoomCleared,
    Pickup,
    CompanionDamaged,
    CompanionKilled,
    RoomHazardDestroyed
};
enum class Demolition { Soft, SpentDynamite, RockWave, SuppliedBomb, EnemyBomb };
struct Event {
    EventType type = EventType::Shot;
    Context context;
    EntityId target = 0;
    Vector3 position{}, direction{0, 0, -1}, origin{};
    float damage = RevolverDamage, radius = 3.3f, speed = 26;
    bool hostile = false, lastRound = false, ghost = false;
    bool projectileHitsEnemies=false,projectileIgnoresPlayer=false;
    float projectileNpcDamage=0;
    bool projectileImpact=false;
    bool noWallCollision=false;
    bool repeatWallBounce=false; // Reflect lateral terrain hits until landing/lifetime, without a bounce budget.
    bool armorPiercing = false, areaDamage = false, weakPointHit = false;
    bool execution = false;
    bool debugExecution=false,explosionDamage=false;
    // Independent of piercing and explosion classification. IGNORE_ARMOR still
    // enters source damage history; INVINCIBLE bypasses both history and scaling.
    bool ignoreAdaptiveArmor=false,bypassAdaptiveHistory=false;
    bool adaptiveResolved=false; // Internal damage-batch replay; accept() clears it.
    bool leperResolved=false; // Internal source-frame replay; accept() clears it.
    bool harmsCompanions = false; // Explicit neutral/special damage, not ordinary player fire.
    DamageKind damageKind = DamageKind::Physical;
    int bounces = 0;
    ProjectileKind projectileKind = ProjectileKind::Bullet;
    Color projectileTint{0,0,0,0};
    float projectileLife = 0; // Explicit enemy shot lifetime; zero preserves the native attack default.
    float projectileCurve = 0;
    float projectileGravity=0,projectileBlastRadius=0,projectileBlastDamage=0;
    float projectileFlightRetention=0,projectileRadius=0,projectileBlastPlayerDamage=-1;
    float projectileTimeScale=1;
    std::optional<ProjectileSplitDefinition> projectileSplit;
    std::optional<ProjectileBurstDefinition> projectileBurst;
    std::optional<HostileHomingDefinition> projectileHoming;
    std::optional<SourcePlanarMotionDefinition> projectilePlanarMotion;
    FireWaveDefinition fireWave;
    Demolition demolition = Demolition::Soft;
    float playerDamage = 0;
    bool playerDamageHostile = false;
    std::optional<AttackSpec> attack;
    float remainingLife = 3.2f;
    int remainingBounces = 0, remainingPierce = 0;
    bool returning = false, explosiveHit = false, compactBlast = false;
    EntityId projectile = 0;
    bool explosionLineCheck=true; // Source blasts may explicitly bypass cover.
    EntityId explosionIgnore=0; // Explicit producer immunity, distinct from ordnance attribution.
};
enum class HazardKind {
    Dynamite,
    Fire,
    Ring,
    Powder,
    Creep,
    Tar,
    Beam,
    HolyLight,
    Gas,
    MonsterBomb,
    PlayerDynamite,
    BossCharge,
    RockWave,
    FireWave
};
struct RockWaveRuntime {
    RockWaveDefinition rules;
    float clock=0;
    int frame=0;
    Vector3 heading{};
    Random rng;
    std::vector<Vector3> trail;
};
struct OwnedBeamRuntime {
    Vector3 heading{},offset{};
    float clock=0,range=100,monsterDamage=35.2f;
    int immuneType=0,damageFrames=2,frame=0;
    uint64_t pulses=0;
};
struct Hazard {
    bool explosiveGas=false,gasIgnited=false;
    float gasBlastRadius=0,gasBlastDamage=0,gasPlayerDamage=0;
    HazardKind kind = HazardKind::Dynamite;
    Vector3 position{}, origin{};
    float age = 0, delay = 1, duration = 0, radius = 3, damage = 20;
    // Optional harmless disappearance after expiry/room clear. Existing hazards
    // keep their immediate removal policy when fadeDuration is zero.
    float fadeDuration=0,fadeAge=-1,fadeScale=1;
    bool fadeOnRoomClear=false;
    bool alive = true, hitPlayer = false;
    Context context;
    Color tint{0,0,0,0}; // Alpha zero uses the existing kind palette.
    bool ownerBound=false;
    std::optional<OwnedBeamRuntime> ownedBeam;
    Vector3 velocity{};
    Vector3 previous{}; // Swept ground-wave contact, distinct from its launch origin.
    float waveTrail=.5f;
    std::optional<RockWaveRuntime> rockWave;
    bool settled = false;
    bool playerContact = false;
    float blastDamage = DynamiteDamage;
    int braidCopies = 0;
    bool secondary = false, kicked = false;
    Vector3 braidDirection{1,0,0};
    // Existing hostile patches damage the player and expose reactive monsters
    // to flame contact. Player/neutral flames can opt into monster damage.
    bool harmsMonsters = false, harmsPlayer = true;
    float monsterDamageInterval = .5f;
};
struct EnemyBomb {
    EntityId id=0,source=0,blastIgnore=0;
    MonsterId sourceMonster,ordnance;
    int room=0;
    Hazard charge;
    bool blastMarker=false; // Stationary delayed blast, without physical dropped-bomb motion.
    EnemyBombDefinition rules;
    bool configured=false,detonated=false;
    float effectAge=0;
    std::array<Vector3,4> beamEnds{};
};
// Shared by live charges and the mouse aiming preview.
void advanceDynamite(Hazard &charge, const Arena &arena, float dt);
enum class SuppliedBombState { Pickup, Carried, Thrown };
struct SuppliedBomb {
    EntityId id=0,supplier=0;
    int room=0;
    bool deathDrop=false;
    SuppliedBombState state=SuppliedBombState::Pickup;
    SuppliedBombDefinition rules;
    Hazard charge;
    // These external components are not ordinary enemy registry entries.
    MonsterId sourceIdentity() const {return state==SuppliedBombState::Pickup?monsterId(5,41):monsterId(4,13);}
};
struct VisualEffect {
    Vector3 position{};
    float radius = 1, life = 0.4f, maxLife = 0.4f;
    int kind = 0;
};
struct Chain {
    uint64_t accepted = 0, queued = 0, active = 0, kills = 0;
    bool stopped = false;
};
struct Limits {
    int maxDepth = 16;
    size_t eventsPerChain = 8192, eventsPerTick = 2048, queuedEvents = 16384, projectiles = 4096,
           enemies = 256, hazards = 256, suppliedBombs = 128, enemyBombs=128, pendingEnemyBombs=256, fireWaves=32;
};
struct ChainLog {
    uint64_t id = 0;
    int generation = 0, effect = -1;
    std::string reason;
    uint64_t suppressed = 1;
};
struct Input {
    Vector3 movement{}, aim{0, 0.85f, 0};
    // Directional controls keep their world-space heading while the player moves.
    std::optional<Vector3> aimDirection;
    std::optional<Vector3> moveTarget;
    std::optional<std::pair<int, int>> doorTarget;
    std::optional<Vector3> dynamiteTarget;
    bool placeDynamite = false;
    bool fire = false, dodge = false, interact = false, standStill = false;
};
struct EncounterPlan {
    EncounterPattern pattern = EncounterPattern::Pursuit;
    int budget = 0, spent = 0, specialists = 0, specialistGroups = 0;
    std::vector<MonsterId> monsters;
    std::vector<MonsterId> originalMonsters; // Composition before one-shot conditional substitutions.
    std::optional<MonsterId> statue;
};
struct PressurePlate { Vector3 position{}; bool pressed=false; };
struct FormationSlot { EntityId member=0; float angle=0; };
struct FamiliarPose { double time=0; Vector3 position{},facing{}; };
struct ContactFamiliarRuntime {
    ItemKey item;
    EntityId id=0;
    Vector3 position{},facing{};
    float radius=.6f;
    std::deque<FamiliarPose> trail;
    std::vector<std::pair<EntityId,float>> contacts;
};
struct FormationRuntime {
    EntityId id=0;
    MonsterId monster{};
    bool friendly=false;
    Vector3 center{};
    float angle=0, pathTime=0;
    std::vector<FormationSlot> slots;
    std::vector<Vector3> path;
};
struct BossChainRuntime {
    EntityId id=0;
    std::vector<EntityId> members;
    std::deque<Vector3> trail; // Head path, newest first; bounded per chain.
    float turnTime=0;
};
struct SegmentedEncounterRuntime {
    EntityId id=0;
    MonsterId monster;
    std::vector<BossChainRuntime> chains;
    std::vector<EntityId> allMembers;
    float maximumHealth=0;
    bool completed=false;
};
struct FireWaveRay {
    float length=0;
    bool stopped=false;
};
struct FireWaveJet {
    Vector3 position{};
    float born=0,scale=1;
    unsigned pulses=0;
};
struct FireWaveBurst {
    EntityId id=0,source=0;
    int room=0;
    Vector3 origin{};
    float age=0;
    FireWaveDefinition rules;
    Context context;
    int jetStep=0;
    std::vector<FireWaveJet> jets;
    std::array<FireWaveRay,4> rays;
    // Default four cardinal rays; impact families may author a smaller fan.
    int rayCount=4;
    std::array<Vector3,4> directions{{{1,0,0},{0,0,1},{-1,0,0},{0,0,-1}}};
    bool segment(int ray,Vector3 &from,Vector3 &to) const;
};
enum class HornfelState { Outside, Opening, Riding, Sad, Fleeing, Finished, Charging, RecoveryEntry, Recovering, DecoyRun };
struct RailCartRuntime {
    EntityId id=0,rider=0;
    MonsterId identity=monsterId(965);
    int route=0;
    float distance=0;
    Vector3 position{},direction{1,0,0};
    bool visible=false,intact=true;
};
struct RailDoorRuntime {
    EntityId id=0;
    MonsterId identity=monsterId(967);
    Vector3 position{};
    float openness=0;
    bool requested=false;
};
struct HornfelDecoyRuntime {
    EntityId actor=0;
    RailCartRuntime cart;
    float opening=0;
    bool finished=false,deathPending=false,explosiveHit=false;
    uint64_t acceptedHits=0,baseLoss=0;
    std::vector<Vector3> bombVelocities;
};
struct RailPassengerRuntime {
    EntityId actor=0;
    RailCartRuntime cart;
    float opening=0,emptyTime=0;
    bool finished=false;
};
struct RailTrafficRuntime {
    bool initialized=false,expired=false,stopped=false;
    float clock=0;
    int timeout=0,lifespan=0;
    uint64_t ticks=0,attempts=0,unavailable=0,blocked=0,capacityRejected=0;
    uint64_t spawned=0,removed=0,destroyed=0;
    std::vector<RailPassengerRuntime> passengers;
};
struct HornfelRuntime {
    EntityId owner=0;
    HornfelState state=HornfelState::Outside;
    RailCartRuntime cart;
    std::vector<RailDoorRuntime> doors;
    std::vector<HornfelDecoyRuntime> decoys;
    RailTrafficRuntime traffic;
    bool decoySelected=false,mainReserved=false;
    float decoyCooldown=0,activeAge=0;
    int decoyRuns=0,decoysSpawned=0,decoysRemoved=0,decoysDestroyed=0;
    bool escortPending=false;
    Vector3 escortEntry{},escortDirection{};
    int escortGroups=0,escortsSpawned=0,escortsReleased=0,escortGroupsSkipped=0;
    float clock=0,attackClock=0,mineCooldown=0;
    int attack=-1,event=0,escapeDoor=-1,passes=0,attacks=0;
    std::vector<std::string> payloads;
    std::vector<Vector3> targets,path;
    bool escaped=false,completed=false;
    bool chargeSelected=false,recoveryShot=false;
    float chargeCooldown=0,drive=0,nativeVelocity=0,driveClock=0,bombClock=0,recoveryClock=0;
    int repeatsLeft=0,repeatsChosen=0,charges=0,chargePasses=0,chargeBombs=0,recoveryShots=0;
};
struct MonsterSpawn {
    MonsterId id;
    Vector3 position;
    EntityId partner = 0;
    int generation = 0;
    bool collapsed = false;
    float healthScale = 1;
    int regrowthSplits = 0;
    EntityId summoner = 0;
    EntityId componentOwner=0;
    int componentSlot=-1;
    std::optional<ItemKey> sourceItem;
    bool retained=false;
    float contactRetention=0; // Live-summon policy captured before its owner can disappear.
    std::optional<ThrownOffspringRuntime> thrown;
    Vector3 impulse{};
    std::optional<SwarmSpiderRuntime> swarmHop;
    std::optional<SlideRuntime> slide;
    std::optional<RockSpiderRuntime> rockSpider;
    EntityId producer=0; // Backpressure attribution, independent of source child ownership.
    int spawnerType=0;
    bool championFriendly=false,championPermanent=false;
    float championCharm=0;
    bool childContactDeath=false; // Captured live-birth policy, never inherited by death offspring.
};
struct RoomProgress {
    bool visited = false, cleared = false, rewardTaken = false, bossPaid = false;
    std::array<ItemKey, 2> offers{};
    std::array<bool,2> serviceSold{};
    // The active room uses Simulation::enemies; other rooms keep their actual group here.
    std::vector<Enemy> residents;
    std::vector<MonsterSpawn> pendingSpawns;
    std::unordered_map<uint64_t,Chain> adaptiveChains;
    std::vector<FormationRuntime> formations;
    std::vector<SegmentedEncounterRuntime> segmented;
    std::optional<HornfelRuntime> hornfel;
    std::vector<PressurePlate> plates;
    bool plateObjective=false,trapOnly=false;
};
struct MoneyPickup {
    Vector3 position{};
    int value = 1;
    float age = 0;
    bool dropped = false;
};
enum class ShopOfferKind { Power, Medicine, Dynamite };
struct ShopOffer {
    ItemKey item = ItemId::Ricochet;
    int price = 25;
    ShopOfferKind kind = ShopOfferKind::Power;
    bool sold = false;
};
struct ServiceOffer {
    std::string name, description, cost;
};

class Simulation {
  public:
    Simulation(uint64_t seed, uint64_t runId, const WorldState &world,
               MissionTheme theme = MissionTheme::Mine, bool canyonRiver = true, bool tutorial = false,
               WitnessAccount account = WitnessAccount::None, int floor = 0,
               ExpeditionPacing pacing = ExpeditionPacing::Compact,
               std::shared_ptr<const MechanicsLibrary> content = defaultMechanics());
    std::shared_ptr<const MechanicsLibrary> content;
    ExpeditionPlan expedition;
    int floor = 0;
    Player player;
    Arena arena;
    Stats stats;
    Limits limits;
    Random encounterRng, rewardRng, combatRng;
    std::vector<Enemy> enemies;
    std::vector<Projectile> projectiles;
    std::vector<VisualEffect> visuals;
    std::vector<ParticleBurst> particleBursts;
    std::vector<Hazard> hazards;
    std::vector<SuppliedBomb> suppliedBombs;
    std::vector<EnemyBomb> enemyBombs,pendingEnemyBombs;
    std::vector<FireWaveBurst> fireWaves;
    std::vector<ContactFamiliarRuntime> familiars;
    std::vector<MoneyPickup> moneyPickups;
    uint64_t moneyCollected = 0;
    uint64_t moneySpent = 0;
    std::array<ShopOffer, 4> shopOffers{};
    bool shopOpen = false;
    AudioCueQueue audioCues;
    uint64_t audioEpoch = 0;
    std::vector<ItemKey> items;
    std::array<ItemKey, 2> offers{};
    std::vector<RoomProgress> rooms;
    int keys = 0, powerUpsTaken = 0;
    int dynamite = StartingDynamite;
    const SuppliedBomb *carriedBomb() const;
    EntityId spawnBombFlyHost(MonsterId child,Vector3 position,EntityId producer=0);
    float dynamiteCooldown = 0;
    std::deque<ChainLog> logs;
    std::unordered_map<uint64_t, Chain> chains;
    bool godMode = false, rewardOpen = false, roomClear = false, finished = false, dead = false;
    bool rescued = false, altarDestroyed = false, bossKilled = false, checkpointNeeded = false;
    bool followup = false, debugScenario = false;
    bool surveyTutorial = false, surveyRecovered = false, letterOpen = false;
    bool floorExitRequested = false;
    StoryRoom storyOpen = StoryRoom::None;
    std::vector<StoryEvidence> evidence;
    bool testimony() const { return expedition.account!=WitnessAccount::None; }
    bool legacyObjectives() const { return !surveyTutorial&&!testimony(); }
    bool lastFloor() const { return floor+1==expedition.floorCount; }
    int storyRoomIndex() const;
    bool storySeen() const;
    bool canUseFloorExit() const;
    bool advanceFloor();
    int finalRoom() const { return arena.roomCount()-1; }
    Vector3 surveyPosition() const { return arena.rooms.back().objective; }
    bool canReturn() const { return lastFloor()&&canUseFloorExit(); }
    std::string tutorialHint() const;
    int room = 0;
    float messageTime = 0;
    double roomEnteredAt = 0, roomClearedAt = -10;
    MessageKind messageKind = MessageKind::Notice;
    std::string message;
    static constexpr int FinalRoom = RoomCount - 1;

    void step(const Input &input, float dt = Tick);
    void grant(const ItemKey &item);
    void chooseReward(int index);
    bool rewardAvailable(int index) const;
    Vector3 rewardPosition(int index) const;
    void enterRoom(int index);
    void clearRoom();
    void requestDoor(int passage, int side);
    bool useDoor(int passage, int side);
    EntityId spawn(EnemyKind kind, Vector3 position);
    EntityId spawnMonster(MonsterId id, Vector3 position, EntityId componentOwner=0, int componentSlot=-1,
                          BossForm form=BossForm::Normal);
    void spawnMonsterDebug(MonsterId id);
    bool makeChampion(EntityId id,int kind);
    bool championEligible(MonsterId id) const {
        return (id.type==10&&(id.variant==0||id.variant==1)&&id.subtype==0)||
            (id.type==11&&(id.variant==0||id.variant==1)&&id.subtype==0)||
            (id==monsterId(12)||id==monsterId(14)||id==monsterId(16)||id==monsterId(855)||id==monsterId(812))||
            (id.type==23&&id.subtype==0&&id.variant>=0&&id.variant<=3);
    }
    bool championTypeEligible(MonsterId id,int kind) const {
        if(!championEligible(id)||!content->champion(kind))return false;
        // Only reviewed body/modifier combinations enter natural champion pools.
        return id==monsterId(812)||content->charge(id)||kind==0||kind==1||kind==2||kind==5||kind==7||
            kind==13||kind==18||kind==19||(id==monsterId(11)&&kind==10);
    }
    void startPractice(int batch);
    void startBatch2Practice(){startPractice(2);}
    // Positive source-frame durations add up to the configured cap. Negative
    // durations ensure at least abs(frames), matching the native refresh path.
    bool applyEnemyStatus(EntityId id,EnemyStatus status,int frames,float damage=0,Context source={});
    void removeEnemyStatus(EntityId id,EnemyStatus status);
    void addFire(Vector3 position,float radius,float duration,float damage,bool harmsMonsters,
                 bool harmsPlayer=true,Context context={});
    size_t roomThreats() const;
    void spawnEnemies(int count);
    int roomEnemyCount(int index) const;
    EncounterPlan floorEncounter(int index) const;
    const std::vector<Enemy> &roomEnemies(int index) const;
    void spawnRoomEnemies();
    void startBoss(BossKind kind = BossKind::None);
    void killAll();
    void clearRoomDebug();
    void jumpDebug(int index, bool restart = false);
    void healDebug();
    void tunePlayer(float baseHealth, float shotDamage);
    void startStress();
    void interact();
    void openShop();
    void closeShop();
    bool buyShop(int index);
    bool throwDynamite(Vector3 target);
    bool placeDynamite();
    float dynamiteBlastRadius() const { return itemStacks(ItemId::Braid)?3.3f:DynamiteRadius; }
    std::vector<Vector3> dynamiteTrajectory(Vector3 target) const;
    std::string shopUnavailable(int index) const;
    ServiceOffer serviceOffer(int index) const;
    std::string serviceUnavailable(int index) const;
    float bargainMaxHealth(int index) const;
    std::string nearbyInteraction() const;
    std::string demolitionHint() const;
    std::string demolitionWarning() const;
    std::optional<Vector3> moveDestination() const {
        return movePath_.empty() ? std::nullopt : std::optional<Vector3>(movePath_.back());
    }
    void finishDebug(bool victory);
    RunSummary summary() const;
    uint64_t money() const {
        return startingWorld_.money + moneyCollected - moneySpent;
    }
    size_t livingEnemies() const;
    size_t queuedEvents() const {
        return queue_.size();
    }
    size_t itemStacks(const ItemKey &item) const;
    Enemy *findEnemy(EntityId id);
    const Enemy *boss() const;
    float bossHealthFraction(const Enemy &enemy) const;
    const Enemy *findEnemy(EntityId id) const;
    bool chainActive(const Enemy &enemy) const;
    std::string roomName() const;
    static std::string roomName(int index, MissionTheme theme = MissionTheme::Mine);
    void announce(std::string text, float seconds = 3, MessageKind kind = MessageKind::Notice);
    void debugNotice(std::string text, float seconds = 3) { announce(std::move(text),seconds,MessageKind::Debug); }
    bool queueRoot(Event event);
    EntityId throwEnemyBomb(std::string_view profile,EntityId source,Vector3 start,Vector3 target,bool place=false);
    void emit(Event event, const Context &parent, int effect = -1);
    void drainEvents();
    void suppress(const Context &context, const std::string &reason);
    void particleEffect(ParticleEffect kind, Vector3 position, Vector3 direction = {0,1,0}, float scale = 1);
    ParticleEffect impactMaterial(Vector3 position, Vector3 normal) const;
    void effectVisual(Vector3 position, float radius, int kind, float duration = 0.4f);

  private:
    Vector3 playerStepStart_{};
    void updateFlyBomb(Enemy &enemy,float dt);
    bool updateFlyBombFollow(Enemy &enemy,float dt);
    void updateBuzzFly(Enemy &enemy,float dt);
    void prepareDung();
    void updateBoomFly(Enemy &enemy,float dt);
    void updateLobWalker(Enemy &enemy,float dt);
    void updateHeadShooter(Enemy &enemy,float dt);
    void updateSubHorf(Enemy &enemy,float dt);
    bool flushReactiveShot(Enemy &enemy);
    void subHorfDeath(Enemy &enemy);
    bool shootLobWalker(Enemy &enemy,Vector3 aim);
    void boomFlyDeath(const Enemy &enemy);
    bool queueEnemyBomb(EnemyBomb bomb);
    bool detonateEnemyBomb(EnemyBomb &bomb);
    void updateEnemyBombEffect(EnemyBomb &bomb,float dt);
    void flyBombDeath(const Enemy &enemy);
    void updateEnemyBombs(float dt);
    bool createFireWave(const Projectile &projectile);
    void updateFireWaves(float dt);
    void updateFireJets(FireWaveBurst &burst,float dt);
    bool pulseFireJet(const FireWaveBurst &burst,const FireWaveJet &jet);
    void updateStatue(Enemy &enemy,float dt);
    void syncStatueBodies();
    void refreshStatues();
    void refreshStatueAttraction(float dt=0);
    Vector3 statueAttraction(Vector3 position,bool projectile,float *speedLimit=nullptr,bool championFields=true) const;
    struct StatueAttractor { Vector3 position; const StatueDefinition *definition; };
    std::vector<StatueAttractor> statueAttractors_;
    void updatePressurePlates();
    bool platesComplete() const;
    void spawnFloorStatue(const EncounterPlan &plan);
    uint64_t seed_, runId_, nextEntity_ = 1, nextChain_ = 1;
    uint32_t nextParticle_ = 1; // Cosmetic stream: never consumes gameplay RNG.
    bool canyonRiver_ = true, debugVictory_ = false;
    WorldState startingWorld_;
    std::deque<Event> queue_;
    // 4-unit XZ cells are a broad phase only; narrow phase uses swept 3D volumes.
    std::array<std::vector<size_t>, 100> grid_;
    std::vector<Vector3> movePath_;
    size_t waypoint_ = 0;
    bool interactOnArrival_ = false;
    std::optional<std::pair<int, int>> doorOnArrival_;
    std::vector<MonsterSpawn> pendingMonsters_;
    void flushMonsterSpawns(Random *placement = nullptr, float playerClearance = 0);
    void queueMonster(MonsterId id, Vector3 position, EntityId partner = 0, int generation = 0,
                      bool collapsed = false, float healthScale = 1, int regrowthSplits = 0,
                      EntityId summoner = 0, EntityId componentOwner=0, int componentSlot=-1,
                      std::optional<ItemKey> sourceItem = {}, bool retained=false,
                      std::optional<ThrownOffspringRuntime> thrown = {}, Vector3 impulse = {});
    void summonMonsters(const Enemy &enemy, const BehaviorSummon &rule);
    void updateMonster(Enemy &enemy, float dt);
    void updateMonsterStatuses(Enemy &enemy,float dt);
    void updateFrozenMonster(Enemy &enemy,float dt);
    void contactMonsterPlayer(Enemy &enemy,float damage);
    void flushSquashedEnemy(Enemy &enemy);
    void invalidateStatusPath(Enemy &enemy,EnemyStatus status);
    bool flushStatusDamage(Enemy &enemy,DamageStatusRuntime &runtime);
    void tickDamageStatus(Enemy &enemy,DamageStatusRuntime &runtime,const DamageStatusDefinition &profile);
    void stepFearMotion(Enemy &enemy,Vector3 &momentum);
    float enemyTimeScale(const Enemy &enemy) const;
    float enemyShotTimeScale(const Enemy &enemy) const;
    Vector3 slowEnemyMotion(const Enemy &enemy,Vector3 before,Vector3 after,float retention) const;
    Vector3 confusedTarget(Enemy &enemy);
    Vector3 resolvedEnemyTarget(Enemy &enemy);
    void setEnemyShotAffiliation(const Enemy &enemy,Event &shot) const;
    std::vector<Enemy> charmFollowers_;
    void restoreCharmFollowers();
    void updateChampion(Enemy &e,float dt);
    void updateCreatureCycle(Enemy &e,float dt);
    bool collapseClack(Enemy &e);
    void creatureDeath(Enemy &e);
    bool flushCreatureShots(Enemy &e);
    bool reflectBouncer(Enemy &e,Projectile &p);
    void igniteGas(Vector3 position,float radius);

    bool collapseChampion(Enemy &e);
    void championHurt(Enemy &e);
    void championChild(const Enemy &e,MonsterId kind,Vector3 at,EntityId partner=0);
    bool flushChampionDeath(Enemy &e);
    bool flushChargeDeath(Enemy &e);
    uint64_t charmContactFrame_=0;
    void prepareCharmContacts();
    void updateCharmContacts();
    void updateEvader(Enemy &enemy, float dt);
    float stepEvaderMotion(Enemy &enemy,const EvaderDefinition &profile,EvaderRuntime &runtime,const Vector3 *target=nullptr);
    void updateSwimmer(Enemy &enemy, float dt);
    void syncWilloOrbits();
    void updateWillo(Enemy &enemy,float dt);
    void updateSpider(Enemy &enemy,float dt);
    void updateHardy(Enemy &enemy,float dt);
    void updateDanny(Enemy &enemy,float dt);
    void updateGaper(Enemy &enemy,float dt);
    bool stepGroundPursuit(Enemy &enemy,const GroundPursuitDefinition &profile,Vector3 &momentum,Vector3 &destination,float force,float *appliedRetention=nullptr,const Vector3 *target=nullptr);
    void updateBlackGlobin(Enemy &enemy,float dt);
    void blackGlobinDamageBrood(Enemy &enemy);
    void blackGlobinDeath(Enemy &enemy);
    void updateLeperFlesh(Enemy &enemy,float dt);
    void leperFleshDeath(Enemy &enemy);
    bool flushLeperFleshShot(Enemy &enemy);
    void updateLeper(Enemy &enemy,float dt);
    void resolveLeperDamage(Enemy &enemy);
    void applyLeperDamage(Enemy &enemy);
    bool delaysLeperDamage(const Event &event) const;
    bool leperDamageFull(const Event &event) const;
    void cancelLeperDamage(Enemy &enemy);
    void emitLeperFlesh(Enemy &enemy,bool final);
    void flushLeperBirths(Enemy &enemy);
    bool leperDeath(Enemy &enemy,const Event &event);
    bool flushLeperCreep(Enemy &enemy);
    bool queueThrownSpider(Enemy &enemy,MonsterId child,Vector3 target,float height);
    void updateRottenGaper(Enemy &enemy,float dt);
    void updateSmallMaggot(Enemy &enemy,float dt);
    void updateHeadless(Enemy &enemy,float dt);
    bool flushHeadlessShot(Enemy &enemy);
    void updateFaceless(Enemy &enemy,float dt);
    void shootFaceless(Enemy &enemy);
    bool flushFacelessShots(Enemy &enemy);
    bool tryFacelessMorph(Enemy &enemy,const Event &event);
    void dannyAttack(Enemy &enemy);
    bool flushDannyShots(Enemy &enemy);
    bool flushHardyShots(Enemy &enemy);
    void hardyImpact(Enemy &enemy,Vector3 normal);
    void hardyDeath(Enemy &enemy);
    void updateRockSpider(Enemy &enemy,float dt);
    bool rockSpiderDeath(Enemy &enemy,const Event &event);
    void updateStrider(Enemy &enemy,float dt);
    void updateLongLegs(Enemy &enemy,float dt);
    void updateSack(Enemy &enemy,float dt);
    void updateMaw(Enemy &enemy,float dt);
    bool shootMawDeath(Enemy &enemy);
    void updateEternalFly(Enemy &enemy,float dt);
    void releaseEternalFly(Enemy &enemy);
    bool shootBoil(Enemy &enemy,const BoilDefinition &profile,bool aimed);
    void updateSwarmSpider(Enemy &enemy,float dt);
    bool planThrownOffspring(ThrownOffspringRuntime &thrown,Vector3 target,float radius,bool overPits) const;
    void updateThrownOffspring(Enemy &enemy,float dt);
    void updateHop(Enemy &enemy,const MonsterDefinition &definition,const HopDefinition &hop,float dt);
    void updateTargetHop(Enemy &enemy,float dt);
    void tryLeaperJump(Enemy &enemy,Vector3 target);
    void advanceLeaper(Enemy &enemy);
    void leaperLanded(Enemy &enemy,bool big);
    void flushLeaperLanding(Enemy &enemy);
    bool beginEggyDeath(Enemy &enemy,const Event &event);
    void updateEggyDeath(Enemy &enemy,float dt);
    bool eggyLanded(Enemy &enemy);
    bool hopRingLanded(Enemy &enemy);
    void flushHopRings(Enemy &enemy);
    bool planHopArc(Enemy &enemy,Vector3 direction,float reach,float height,float maximumHeight,float duration);
    bool revalidateHopArc(Enemy &enemy);
    bool advanceHopArc(Enemy &enemy,float dt);
    void initializeMonsterBoss(Enemy &enemy,BossForm form);
    EntityId spawnSegmentedBoss(MonsterId id,Vector3 center);
    void updateSegmentedBosses(float dt);
    void reconcileSegmentedBosses();
    void updateShell(SegmentedEncounterRuntime &group,float dt);
    void reconcileShell(SegmentedEncounterRuntime &group);
    bool settleShellSegment(Enemy &enemy,float dt);
    float segmentDamage(Enemy &enemy,const Event &event);
    void updateMonsterBoss(Enemy &enemy,float dt);
    EntityId spawnLoki(MonsterId id,Vector3 center);
    bool lokiPositionClear(const Enemy &enemy,Vector3 point,float playerClearance) const;
    void updateLoki(Enemy &enemy,float dt);
    EntityId spawnHornfel(MonsterId id,Vector3 center);
    void updateHornfel(Enemy &enemy,float dt);
    bool hornfelCartLoss(Enemy &enemy,const Event &event);
    void finishHornfel(Enemy &enemy,bool escaped);
    int selectHornfelRoute(bool reserveMain);
    void selectHornfelDecoys();
    void updateHornfelDecoys(float dt);
    void damageHornfelDecoy(Enemy &enemy,const Event &event);
    void reconcileHornfelDecoys();
    void selectHornfelEscorts();
    void spawnHornfelEscorts();
    void releaseHornfelEscorts(EntityId owner);
    void updateRailTraffic(float dt);
    void clearRailTraffic();
    void damageEnvironmentActor(Enemy &enemy,const Event &event);
    void reconcileEnvironmentActors();
    void queueDeathBlast(Enemy &enemy);
    void reconcileDeathBlasts();
    void updateEnvironmentActor(Enemy &enemy,float dt);
    bool environmentActionsPending() const;
    void updateBloat(Enemy &enemy,float dt);
    void updateCharge(Enemy &enemy,float dt);
    void updateContactFamiliars(float dt);
    void updateCompanionContacts(float dt);
    void exposeCompanionsToHazard(const Hazard &hazard,float previousAge);
    bool companionTarget(const Enemy &enemy) const;
    float contactDamage(const Enemy &enemy) const;
    Vector3 chargeTailPosition(const Enemy &enemy) const;
    float enemyProjectileHit(const Enemy &enemy,Vector3 from,Vector3 to,float radius,bool &weakPoint) const;
    void bloatLasers(Enemy &enemy,const BloatDefinition &definition,bool down);
    void bloatLobs(const Enemy &enemy,const BloatDefinition &definition,int count);
    void requestBossComponents(Enemy &enemy);
    void updateOwnedComponent(Enemy &enemy,float dt);
    void removeOwnedComponents(EntityId owner,bool deathEffects=true);
    void bossCreep(const Enemy &enemy,float radius,float duration,Color tint={196,160,45,200},float damage=10);
    float reactToFire(Enemy &enemy,const Event &event);
    bool transformMonster(Enemy &enemy,MonsterId target,TransformHealth health);
    void exposeMonstersToFire(const Hazard &hazard);
    void updateFormations(float dt);
    void updateFormationMember(Enemy &enemy, const FormationDefinition &definition, float dt);
    void updateBehavior(Enemy &enemy,const MonsterDefinition &definition,const BehaviorDefinition &graph,float dt);
    void attackMonster(Enemy &enemy);
    bool collapseMonster(Enemy &enemy);
    bool tryLethalMorph(Enemy &enemy,const Event &event);
    void identifyDamageSource(Event &event) const;
    bool sourceImmune(const Enemy &enemy,const Event &event) const;
    bool delaysAdaptiveDamage(const Event &event) const;
    bool adaptiveDamageFull(const Event &event) const;
    void updateAdaptiveArmor(float dt);
    void cancelAdaptiveDamage(Enemy &enemy);
    void saveAdaptiveChains();
    void monsterDeath(Enemy &enemy, const Event &event);
    void updateMaskArmor(Enemy &enemy,float dt);
    void updateKnight(Enemy &enemy,float dt);
    bool flushKnightImpact(Enemy &enemy);
    bool maskBlocks(const Enemy &enemy,const Event &event) const;
    void reflectMaskHit(Enemy &enemy,const Event &event);
    bool tryLinkedRemnant(Enemy &enemy,const Event &event);
    bool updateLinkedRemnant(Enemy &enemy);
    void finishLinkedRemnant(Enemy &enemy);
    bool flushLandingCreep(Enemy &enemy);
    void monsterDeathOffspring(const Enemy &enemy, const MonsterDeathRule &rule);
    void monsterPattern(const Enemy &enemy, int count, float angle = 0, float speed = 9,
                        ProjectileKind kind = ProjectileKind::Bullet);
    void monsterPatch(const Enemy &enemy, HazardKind kind, Vector3 position, float radius, float delay = .5f,
                      float duration = 3);
    void monsterBeam(const Enemy &enemy, Vector3 direction, float delay = .4f);
    void monsterLines(const Enemy &enemy, HazardKind kind, bool diagonal = false);
    void moveMonster(Enemy &enemy, Vector3 velocity, float dt);
    Vector3 steerMonsterBodies(const Enemy &enemy, Vector3 velocity,bool alignRoute=false) const;
    void resolveMonsterBodies(float dt);
    void requestMove(Vector3 target, bool interactAtDestination = true);
    void cancelMove();
    bool accept(Event event);
    void process(const Event &event);
    void createProjectile(const Event &event);
    void updateGuidance(Projectile &projectile,float dt);
    void updateSourcePlanarMotion(Projectile &projectile,float elapsed);
    void updateSpitty(Enemy &enemy,float dt);
    void updateCardinalWalker(Enemy &enemy,float dt);
    int faceAxisWander(Enemy &enemy,AxisWanderRuntime &runtime);
    void stepAxisWander(Enemy &enemy,const AxisWanderDefinition &profile,AxisWanderRuntime &runtime);
    void updateBrain(Enemy &enemy,float dt);
    void updateGuts(Enemy &enemy,float dt);
    void updateMirror(Enemy &enemy,float dt);
    void updateAdultLeech(Enemy &enemy,float dt);
    bool shootAdultLeech(Enemy &enemy,int ring);
    void updateSlide(Enemy &enemy,float dt);
    void slideDeath(Enemy &enemy);
    bool flushSlideDeath(Enemy &enemy);
    bool dingaAttack(Enemy &enemy);
    void updateMemBrain(Enemy &enemy,float dt);
    bool shootMemBrain(Enemy &enemy);
    void memBrainDeath(const Enemy &enemy);
    bool shootCyst(Enemy &enemy);
    void updateLump(Enemy &enemy,float dt);
    bool lumpDestinationClear(const Enemy &enemy,Vector3 point,bool occupancy) const;
    void chooseLumpDestination(Enemy &enemy);
    bool shootLump(Enemy &enemy);
    void updateLeech(Enemy &enemy,float dt);
    void updateVis(Enemy &enemy,float dt);
    bool shootVis(Enemy &enemy);
    void updateReturningBody(Enemy &enemy,float dt);
    float returningBodyHit(const Enemy &enemy,Vector3 from,Vector3 to,float radius,float begin,float end) const;
    void followOwnedBeam(Hazard &beam);
    void damageOwnedBeam(Hazard &beam,float dt);
    void updateLinkedHead(Enemy &enemy,float dt);
    void releaseLinkedPart(Enemy &enemy,MonsterId replacement);
    void linkedHeadDeath(Enemy &enemy);
    bool shootLinkedHeadDeath(Enemy &enemy);
    void updateBaby(Enemy &enemy,float dt);
    bool shootBaby(Enemy &enemy);
    bool babyDestinationClear(const Enemy &enemy,Vector3 point) const;
    void chooseBabyDestination(Enemy &enemy);
    void moveAxisWander(Enemy &enemy,const AxisWanderDefinition &profile,AxisWanderRuntime &runtime,float dt);
    bool shootSpitty(Enemy &enemy,bool burst=false,bool death=false);
    void beginReturn(Projectile &projectile);
    void updatePlayer(const Input &input, float dt);
    void kickDynamiteOnContact(Vector3 previousPosition);
    void beginBossEncounter();
    void spawnFloorEnemies();
    void spawnCanyonBoss();
    void updateCanyonBoss(Enemy &enemy,float dt);
    void updateFrontierBoss(Enemy &enemy,float dt);
    void throwBossCharge(const Enemy &enemy,Vector3 target);
    void rewardCanyonBoss(const Enemy &enemy);
    void prepareRoomEnemies(int index);
    bool roomSpawnClear(Vector3 position, float radius) const;
    void updateEnemies(float dt);
    void performEnemyAttack(Enemy &enemy);
    void updateHazards(float dt);
    void resolveExplosion(const Event &event);
    void hitBreakable(Breakable &prop, float damage, bool hard);
    void advanceRockWave(Hazard &wave, float dt);
    void advanceSteppedRockWave(Hazard &wave, float dt);
    bool pulseRockWave(const Hazard &wave, Vector3 at);
    void launchPlayer(Vector3 origin,const HostSlamDefinition &rules);
    void resetPlayerLaunch();
    bool createSuppliedBomb(Enemy &supplier, bool deathDrop);
    bool takeNearbySuppliedBomb();
    bool useSuppliedBomb(Vector3 target, bool place=false);
    void updateSuppliedBombs(float dt);
    void updateBreakables(float dt);
    void payBreakables();
    void addHazard(Hazard hazard);
    void clearHazards(bool preservePlayer = false);
    bool hurtPlayer(float damage, const Context &context = {}, bool hostile = true);
    float enemyDamage(const Enemy &enemy, const Event &event) const;
    void updateHost(Enemy &enemy,float dt);
    void updateMushroom(Enemy &enemy,float dt);
    void hostBlockedHit(Enemy &enemy,const Event &event);
    void shootEnemy(const Enemy &enemy, Vector3 direction, float damage, float speed, int bounces = 0,
                    ProjectileKind kind = ProjectileKind::Bullet, float life = 0, float curve = 0);
    bool placeEnemy(EnemyKind kind, Random &rng, bool spaced, MonsterId monster = {});
    void updateProjectiles(float dt);
    bool burstOnDeath(const Projectile &projectile);
    bool splitOnImpact(const Projectile &projectile);
    void rebuildGrid();
    std::vector<size_t> candidates(Vector3 from, Vector3 to, float radius) const;
    void collectChains();
    void offerReward();
    void collectKeys();
    void prepareMoney();
    void dropMoney(const Enemy &enemy);
    void updateMoney(float dt);
    void prepareShop();
    bool buyService(int index);
    Hazard makeDynamite(Vector3 target) const;
    bool deployDynamite(Hazard charge);
};
} // namespace dw
