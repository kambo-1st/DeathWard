#pragma once
#include "world/RailNetwork.hpp"
#include "combat/Monsters.hpp"
#include "world/Expedition.hpp"
#include <filesystem>
#include <map>
#include <memory>
#include <span>
#include <set>

namespace dw {
enum class BuildStat { Damage, Speed, Life, Radius, Homing, ReturnRange, CapDamage, CapRadius,
    CapSelfDamage, Pierce, Bounces, Pellets, Cadence, Scatter, Rail, Count };
enum class ModifierOp { Set, Add, Multiply, Minimum, Maximum, Ratio };
struct BuildModifier {
    BuildStat stat{}, denominator{};
    ModifierOp operation{};
    float first = 0, extra = 0;
    bool perCopy = false;
};
struct ItemRequirement { ItemKey item; int minimum=1, maximum=-1; };
struct BuildRule {
    std::string key;
    int priority = 0, stackCap = 0;
    ItemKey owner;
    bool sixthOnly = false;
    std::vector<ItemRequirement> requirements;
    std::vector<BuildModifier> modifiers;
};
struct ItemEffect { std::string action; bool perCopy=true; };
struct WeightedItem {
    ItemKey item;
    int weight=0;
    auto operator<=>(const WeightedItem &) const = default;
};
struct ItemDefinition {
    ItemKey id;
    std::string name,rarity,description;
    std::vector<ItemEffect> effects;
    float pickupHealthMultiplier=1, pickupHealthFloor=10;
};
struct ResolvedBuild {
    std::array<float,size_t(BuildStat::Count)> values{};
    float operator[](BuildStat stat) const { return values[size_t(stat)]; }
};
enum class StatueAttack { Aimed, Triple, Lob, Fixed, Cross, Beam, RotatingBeam, Attraction, Quake, Supply };
enum class StatueClear { Combat, Plates, Never };
struct SuppliedBombDefinition {
    float replenish=2.5f, fuse=3, radius=4.5f, damage=100, selfDamage=25;
    float range=12, flight=.7f, pickupRadius=.75f;
    int deathDrops=10;
};
struct StatueDefinition {
    StatueAttack attack=StatueAttack::Aimed;
    StatueClear clear=StatueClear::Combat;
    float interval=2.8f, windup=.3f, damage=10, speed=8, spread=.22f;
    float range=32, beamRadius=.25f, beamDuration=.08f, turnRate=0, angle=0;
    float lobFlight=1.1f, gravity=12, blastRadius=2.5f, blastDamage=20;
    float playerPull=0, projectilePull=0, projectileLimit=40, pullHeight=4;
    float activeSeconds=0, inactiveSeconds=0;
    int quakeAxis=0; // Source animation convention: left, up, right, down.
    float hopHeight=1, hopSeconds=.45f, waveRadius=.5f, waveTrail=.5f;
    SuppliedBombDefinition supply;
    bool removeOnReentry=false,lobConfigured=false,attractionConfigured=false,quakeConfigured=false,supplyConfigured=false;
};
struct StatuePoolEntry { MonsterId monster; int weight=1; int pattern=-1; };
struct EncounterEntry {
    MonsterId monster;
    int weight=1, cost=1, maximum=0; // Zero maximum means limited only by the encounter budget.
    int members=1; // Threat cost buys this many actors; maximum still caps actors per room.
    std::optional<FloorVariant> variant;
};
struct EncounterPool {
    std::vector<EncounterEntry> basics, specialists;
};
struct MonsterReplacement {
    MonsterId source, target;
    int firstBand=0, lastBand=3, chance=0, extraCost=0; // Chance in basis points, 0..10000.
    std::optional<FloorVariant> variant;
    int chanceOutOf=10000; // Exact rational odds; legacy rules use basis points.
    int phase=0; // Explicit ordered passes; old rules remain single-pass phase zero.
    bool allSpawns=false; // Deterministic final identity, including offspring.
};
struct StageHealthDefinition {float base=0,perStage=0,scale=1;};
enum class BoomFlyKind { Normal, Red, Drowned, Dragon, Bone, Sick, Tainted };
struct BoomFlyDefinition {
    BoomFlyKind kind=BoomFlyKind::Normal;
    float contact=10,blastDamage=100,playerDamage=20,blastRadius=3,blastDelay=0;
    int shots=0,childChance=0;
    float shotSpeed=8,shotDamage=10,interval=2,alignment=.8f,range=24;
    MonsterId child;
    float trailInterval=.6f,trailRadius=.7f,trailDuration=2.5f,deathRadius=1.3f,deathDuration=12,cloudSpread=2.25f;
    float lineRange=30,lineStep=1.5f,lineDelay=.065f,fieldDamage=8;
    bool diagonal=false,shotsConfigured=false,fieldConfigured=false;
};
// Family controllers share dedicated selection and owned-component lifetime.
// More controllers can be added without putting bosses into ordinary pools.
struct PeepDefinition {
    MonsterId eye;
    float flight=.85f, distance=6, height=3.5f, maximumHeight=6;
    float creepRadius=2.8f, creepDuration=6, shotSpeed=7.5f, shotDamage=10, contactDamage=20;
    float yellowScale=.85f, yellowSpeed=1.25f, trailInterval=.3f, trailRadius=.7f;
    std::array<int,3> weights{1,1,1}; // creep, eight-shot ring, jump + twelve-shot landing ring
};
struct LokiDefinition {
    MonsterId child;
    int bodies=1,childLimit=4;
    float shotSpeed=8,shotDamage=10,contactDamage=20,volleyInterval=.25f;
    float vanish=.35f,reappear=.3f,teleportClearance=6,initialDelay=1.2f;
    std::array<int,4> weights{3,2,1,2}; // cardinal/diagonal/cardinal, ring, summon, teleport
};
struct FireWaveDefinition {
    float speed=0,range=0,radius=.4f,trailDuration=2,damage=10;
    // Zero step frames keeps the existing continuous trail mode. Discrete jets
    // are a separate source effect: two damage pulses, then visual recovery.
    int jetStepFrames=0,jetCount=0,jetLifeFrames=20,jetPulseA=2,jetPulseB=4;
    float jetSpacing=3,jetScaleLoss=.06f,jetMonsterDamage=32;
};
enum class EnvironmentActorKind { Fireplace, Tnt, HotCoal };
struct EnvironmentActorDefinition {
    EnvironmentActorKind kind=EnvironmentActorKind::Fireplace;
    float damageScale=3.2f,contact=10,contactInterval=.5f;
    float blastDamage=320,blastRadius=7.5f,blastPlayerDamage=20;
    float pushSpeed=8,pushRetention=.8f;
};
struct RailPassengerDefinition {
    MonsterId actor;
    bool available=false; // Pending identities keep their original table slots.
};
struct RailTrafficDefinition {
    bool enabled=false;
    int initialMin=150,initialMax=359,largeArea=135,largeDivisor=2;
    float tickRate=30,speed=12,doorTime=.3f;
    std::vector<RailPassengerDefinition> passengers;
};
struct HornfelDefinition {
    float speed=12, fleeSpeed=4, fleeHealth=320, contact=20, fleeContact=10;
    float outside=1.5f, doorTime=.3f, attackDelay=.5f;
    std::array<int,3> attacks{3,1,1};
    std::array<int,3> bombs{6,3,1};
    std::vector<std::pair<std::string,int>> layouts;
    bool chargeConfigured=false,recoveryConfigured=false;
    int chargeChance=1250,repeatMin=6,repeatMax=8;
    float chargeCooldown=10,mineCooldown=5,bombInterval=.5f,bombScatter=.1f;
    float driveStart=.1f,driveIncrement=.08f,driveMax=30,driveForce=1.3f,retention=.8f;
    float nativeScale=.1f,nativeTravelCap=40;
    float recoveryEntryDrive=6,recoveryDeceleration=.75f,recoveryFloor=.8f,recoveryAcceleration=.1f;
    float recoveryDrive=1.2f,recoveryDelay=1.f/30;
    float recoveryFlight=1.1f,recoveryGravity=12,recoveryPrediction=.2f,recoveryDamage=10;
    FireWaveDefinition fireWave;
    MonsterId escort;
    int escortChance=0,escortCount=2,escortLimit=4; // One in N; zero disables optional escorts.
    float escortClearance=24,escortRadius=.6f,escortSpread=20,escortReleaseHp=11.2f;
};
struct HornfelDecoyDefinition {
    MonsterId owner;
    int chance=1250,smallCount=2,largeCount=3;
    float cooldown=100.f/30,startDelay=5,speed=12,contact=20,damageScale=3.2f;
    float blastDamage=352,blastRadius=7.5f,playerDamage=20;
    int bombCount=6;
    float bombSpeedMin=15,bombSpeedMax=60;
    std::string bomb="normal";
};
struct ComponentDefinition {
    MonsterId owner;
    float contactDamage=10, bombDeflection=1.5f;
};
struct BloatDefinition {
    MonsterId eye, charger;
    float flight=.9f,distance=7,height=3.8f,maximumHeight=6,shortFlight=.35f,shortHeight=.7f;
    float creepRadius=3,creepDuration=6,landingRadius=1,shotSpeed=8,shotDamage=10,contactDamage=20;
    std::array<int,3> weights{1,1,1}; // large creep, short hop, long jump
    float beamRange=32,beamRadius=.32f,beamDuration=.7f,beamCooldown=1.5f,beamAlignment=.8f,beamDamage=10;
    float lobFlight=1.1f,gravity=12,lobSpread=2,blastRadius=2.8f,blastDamage=20;
    int summonLimit=12;
};
struct SegmentedBossDefinition {
    int chains=2,segments=6,splitMinimum=3,suppliers=2;
    MonsterId supplier,armoredChild,exposedChild;
    float spacing=1.55f,armor=15,blastNear=.25f,blastFar=.14f;
    float speed=1.8f,exposedSpeed=.8f,turnMin=1.2f,turnMax=3.4f,contactDamage=10;
    float headInterval=5,bodyInterval=3,shotSpeed=7.5f,shotDamage=10;
    int childLimit=4,burstMaximum=2,bodyShots=7;
    bool attacksConfigured=false;
};
struct ShellBossDefinition {
    float exposedSlowdown=.6f,steerRange=6,turnRate=.35f,fleshSpeed=.8f,settleSpeed=5,shotSpread=.22f;
};
struct DeathCrossDefinition {
    float angle=0,speed=8,damage=10,creepRadius=0,creepDuration=0,creepDamage=10;
};
struct DeathBlastDefinition {
    float damage=128, playerDamage=20, radius=6;
    bool onlySelf=false;
    int shots=0,selfShots=0;
    float angle=0,shotSpeed=21,shotDamage=10;
    std::string bomb;
};
struct SourceImmunityDefinition { bool flame=false, explosion=false; };
// Stationary aimed shooters: cooldown starts at acquisition, with independent
// firing and recovery events on the source 30 Hz clock.
struct HeadShooterDefinition {
    int checkFrames=7,cooldownFrames=28,attackFrames=20,shootFrame=4;
    float range=20,speed=21,damage=10,life=5;
    bool reactive=false;
    float spinPerSpeed=2,intervalNumerator=20,velocityScale=3;
    float bodyRetention=0;
    float shotHeight=0,shotUp=0,shotGravity=0,shotRetention=0,shotRadius=.22f;
};
// Room-centered mirrors. Times use source 30 Hz frames; projectile distances
// and velocities are already converted to DeathWard units.
struct MirrorDefinition {
    int cooldownFrames=0,shots=1;
    float speed=30,inheritance=.6f,movementMultiplier=2,eyeMin=.3f,eyeExtra=.2f;
    float sideForward=.961f,sideCross=.276f,sideMultiplier=.9f;
    float spreadVelocity=1.2f,spreadInheritance=.4f;
    float height=1.15f,up=3,gravity=4.455f,retention=.9f,radius=.308f,damage=10,life=8;
};
// Source homing accelerates within a radius; it does not normalize speed.
struct HostileHomingDefinition {
    float range=10,acceleration=4.2f,retention=.92f,prediction=1.f/60;
};
// Native projectile motion after each 30 Hz movement step. Orbit uses a fixed
// center, a tangential component, and radial drift; it is not constant curvature.
// direction: +1 ORBIT_CW, -1 ORBIT_CCW, 0 no orbit. Radius zero spirals outward.
struct SourcePlanarMotionDefinition {
    float acceleration=1,orbitRadius=0;
    int orbitDirection=0;
    Vector3 orbitCenter{};
    // ACCELERATE_EX blends from1 to acceleration over this many source frames.
    // Zero retains the constant multiplier used by existing projectile families.
    float accelerationRampFrames=0;
};
enum class SpittyKind { Normal, Conjoined, Tainted };
// Shared native cardinal-path steering. Attack families own their own clocks,
// animation events and payloads; this profile describes only locomotion.
struct AxisWanderDefinition {
    float scale=.1f,force=.72f,retention=.85f,zRetention=.964705825f;
    float grid=40,arrival=5,stuckSpeed=.6f;
    int attempts=10,maxCells=11,stuckFrames=10;
};
struct LeechDefinition : AxisWanderDefinition {
    float contact=20,chargeForce=1.55f,chargeRetention=.9f,gridPull=.3f;
    float alignment=20,prediction=16,chargeStuckDistance=1.414213562f;
    int checkFrames=4,walkFrames=8,dashFrames=6,chargeStuckFrames=5;
    MonsterId child{};
};
struct CardinalWalkerDefinition : AxisWanderDefinition {
    float contact=10;
    int horizontalFrames=12,verticalFrames=24;
};
// Vis uses the shared cardinal wander, but commits a heading before its
// animation-driven beam packet. Values in source frames run at 30 Hz.
struct VisDefinition : AxisWanderDefinition {
    MonsterId returningBody{};
    float contact=10,alignment=20,range=400;
    int walkFrames=22,checkFrames=3,attackFrames=79,shootFrame=28,beams=1;
    int beamFrames=32,fadeFrames=19,damageFrames=2;
    float beamRange=100,beamRadius=1.6f,playerDamage=10,monsterDamage=35.2f;
    float originX=.6f,beamHeight=.85f,fadeScale=.895f;
    bool beamConfigured=false;
};
// Owned, invulnerable attack body. Source distances/velocities use scale;
// reversal and removal counters use the source's 30 Hz clock.
struct ReturningBodyDefinition {
    MonsterId owner{};
    float scale=.1f,launch=16,horizontalMultiplier=1.4f,returnOffset=20,contact=20,spawnOffset=.1f;
    int reversalFrame=21,removeAfter=42;
};
struct GutsDefinition {
    float scale=.1f,force=3,retention=.6f,grid=40,arrival=10,crossPull=.4f,contact=10;
    int rollFrames=24;
    bool charge=false;
    int windupFrames=6,recoveryFrames=60,hitFrames=11;
    float prediction=5,chargeMultiplier=1.8f,brake=.1f,recoveryAcceleration=.05f;
    int creepInterval=0,chargingCreepInterval=0,creepFrames=0,fadeFrames=40;
    float creepRadius=.75f,creepDamage=0,fadeScale=.98f;
    bool tar=false;
    bool shooting=false;
    int shotInterval=30,shotFrames=10;
    float shotSpeed=30,shotDamage=10,shotHeight=1.15f,shotUp=4.5f,shotGravity=9,shotRetention=.9f,shotRadius=.22f,shotLife=8;
};
struct AdultLeechShotDefinition {
    int count=0;
    float speed=30,gravity=8.1f,height=1.15f,upMin=-.15f,upMax=.15f,retention=.9f,radius=.22f,damage=10,life=8,offset=0;
};
struct AdultLeechDefinition {
    float scale=.1f,contact=20,walkForce=.7f,walkRetention=.8f,recoveryRetention=.9f;
    int headingChance=30,chargeChance=3,walkFrames=16,recoveryFrames=12;
    float alignment=30,chargeRetention=.86f,initialGain=.5f,gainStep=.2f,maxGain=5,gainRange=500;
    float steerDeadzone=10,steer=.12f,steerCap=2,impactSpeed=10,impactDot=.6f,recoil=2.5f;
    float healthThreshold=.66f,burrowDistance=80,grid=40,burrowPull=.3f,burrowRetention=.8f;
    int burrowChance=3,burrowFrames=25,burrowSound=8,burrowHit=22,hiddenFrames=30,emergeChance=15;
    int fallFrames=43,fallHit=18,fallSound=31;
    float followForce=.8f,followRetention=.7f,settleRetention=.7f,freeRetention=.8f;
    bool burrowConfigured=false;
    std::array<AdultLeechShotDefinition,2> shots; // wall impact, landing
};
struct SlideDeathShot {
    float prediction=.1f,speed=30,height=1.15f,up=0,gravity=4.5f,retention=.9f,radius=.308f,damage=20,life=8;
};
struct SlideCreep {
    int interval=3,frames=60,fadeFrames=30;
    float radius=1,fadeScale=.97f;
};
struct SlideDefinition {
    bool targeted=false;
    float scale=.1f,contact=10,idleRetention=.8f,moveRetention=.95f,impulseMin=5,impulseMax=10,stopSpeed=1;
    int chance=10,checkFrames=1,idleFrames=10,moveFrames=25,attackFrames=0,launchFrame=0;
    float sustainForce=0,slowSpeed=3,slowRetention=.8f,collisionRetention=.85f;
    int sustainFrames=10,collisionFrames=4;
    MonsterId child{};
    float childOffset=1;
    bool floodedPits=false;
    int chainFrame=0,chainChance=3,aimChance=3;
    int secondAttackFrames=0,secondLaunchFrame=0,firstBrake=8,secondBrake=40;
    float childImpulseMin=0,childImpulseMax=0;
    std::optional<SlideDeathShot> deathShot;
    std::optional<SlideCreep> creep;
};
struct DingaDefinition {
    MonsterId child{};
    int populationLimit=6,shotChance=7;
    float childOffset=3,pushRange=150,pushForce=.1f,animationFps=45;
};
struct MemBrainDefinition {
    float scale=.1f,force=.5f,retention=.8f,wanderDistance=40,arrival=3,stuckSpeed=.316227766f,contact=20;
    int stuckChance=10,chance=30,populationLimit=8,walkFrames=30,attackFrames=70,shootFrame=29;
    float shotSpeed=30,shotAngle=0,shotHeight=1.15f,shotUpMin=-.15f,shotUpMax=.15f;
    float shotGravity=4.5f,shotRetention=.9f,shotRadius=.308f,shotDamage=20,shotLife=8;
    bool wallBounce=false,shotConfigured=false;
    MonsterId child{};
    float childOffset=1;
    std::optional<DingaDefinition> dinga;
};
// Mask protection is directional in the installed controller; it is not a
// separate invisible actor. Reflection keeps incoming planar speed/angle.
struct MaskArmorDefinition {
    bool reflect=false;
    int turnGraceFrames=0;
    float reflectionDamage=10,grazingThreshold=.3f;
};
struct KnightDefinition : AxisWanderDefinition {
    float contact=10,mass=10,chargeForce=1,chargeAcceleration=0,chargeMaximum=1;
    float alignment=20,range=200,prediction=16,gridPull=.1f;
    int checkFrames=3,walkFrames=22;
    bool randomWalk=false;
    float randomForce=.5f,randomDistance=40,randomArrival=3;
    float impactSpeed=8,impactAlignment=.9f,impactBrake=.01f,recoveryRetention=.88f;
    float impactLift=5,impactGravity=1.1f,impactRebound=5;
    int recoveryFrames=0;
    bool ignoreFireJets=false;
    FireWaveDefinition impactWave;
};
// Lethal damage leaves the original body alive and releases one vulnerable
// partner. Independently placed remnants adopt an unclaimed partner nearby.
struct LinkedRemnantDefinition {
    MonsterId source{},body{},child{};
    float offset=1;
};
struct LandingCreepDefinition {
    int searchAttempts=10,releaseChance=3,frames=125,fadeFrames=40;
    float radius=2.5f,damage=10,fadeScale=.98f;
};
// Common installed ground path impulse. Navigation uses the actual canyon
// footprint, while force and retention retain their native 30Hz units.
struct GroundPursuitDefinition {
    float scale=.1f,force=.5f,retention=.7f,blockedRetention=.85f,arrivalRetention=.5f;
    float distanceGain=.1f,maxGain=2,arrival=1,stopSpeed=.1f,contact=20;
    int walkFrames=22;
};
struct BlackGlobinDefinition : GroundPursuitDefinition {
    float damageThreshold=16,targetFraction=.75f,throwHeight=-30,headRadius=4;
    MonsterId spider{},head{},body{};
};
struct LeperFleshDefinition {
    float scale=.1f,retention=.95f,force=.15f,randomWeight=2,contact=10;
    int idleFrames=24,trailPeriod=10,particlePeriod=6;
    float trailMin=.1f,trailMax=.2f,trailLife=8;
    float prediction=.1f,shotSpeed=30,shotUp=4.5f,gravity=4.5f;
    float shotHeight=1.15f,shotRadius=.22f,shotDamage=10,shotLife=8,shotRetention=.9f;
};
struct BrainDefinition : AxisWanderDefinition {
    float verticalRetention=.8f,contact=20;
    int walkFrames=30,chargeInterval=7;
    float alignment=20,range=200,prediction=16,chargeRetention=.8f,gridPull=.1f;
    int crowdThreshold=5,denseInterval=12,sparseInterval=24;
    float extraCreepSpeed=3,creepRadius=2.46f,creepDamage=10;
    int creepFrames=125,fadeFrames=40;
    float fadeScale=.98f;
    bool chargeConfigured=false,creepConfigured=false;
    std::optional<GroundPursuitDefinition> pursuit;
};
// A separately damageable head belongs to a grounded body. Neck pieces are
// harmless visual components, never independent encounter entries.
struct LinkedHeadDefinition {
    MonsterId body,head,neck,bodyRelease,headRelease;
    float scale=.1f,force=.6f,walkRetention=.7f,throwRetention=.7f,contact=10;
    int walkFrames=22,splitChance=1000,checkFrames=4;
    float range=130,prediction=3,launchSpeed=14,returnDistance=5;
    int timerStart=30,timerMinimum=-30,attachTimer=15;
    float springBase=1.4f,springSubtract=.7f,springDivisor=45,headRetention=.9f,timerRetention=.0028f;
    int neckCount=8,deathShots=0;
    float neckRadius=.09f,headLift=.65f,neckSag=.35f,deathSpeed=24,deathDamage=10;
    bool throwConfigured=false,neckConfigured=false;
};
struct LumpDefinition {
    float scale=.1f,retention=.7f,contact=10;
    int hideChance=50,appearChance=20,hideFrames=16,appearFrames=22,shakeFrames=2;
    float margin=20,alignment=20,axisRange=400,targetMin=200,grid=40;
    HeadShooterDefinition shot;
    float shotHeight=1.15f,shotUp=6,shotGravity=9,shotRetention=.9f,shotRadius=.22f;
    bool shotConfigured=false;
};
enum class BabyKind { Normal, Angelic, Small, Wrinkly };
struct BabyDefinition {
    BabyKind kind=BabyKind::Normal;
    float scale=.1f,force=.33f,retention=.7f,contact=10;
    int walkFrames=12;
    HeadShooterDefinition shot;
    float shotHeight=1.15f,shotUp=4.5f,shotGravity=6.75f,shotRetention=.9f,shotRadius=.22f;
    float velocityMultiplier=1.07f,spread=1,originOffset=0;
    float searchCharge=20,startCharge=40,randomCharge=.1f,alignment=20,alignmentRange=400;
    float radiusMin=60,radiusExtra=250,targetMin=200,targetMax=0,grid=40;
    int attempts=2,vanishFrames=25,appearFrames=19,jumpFrame=5,landFrame=5;
    int initialMin=5,initialMax=14,recoveryMin=15,recoveryMax=44,chance=4,dashFrames=7,closeAttackFrame=3;
    float keepDistance=120,dashRange=280,dashForce=3.75f,dashRetention=.85f,dashStop=20;
    bool shotConfigured=false,teleportConfigured=false,dashConfigured=false;
};
struct SpittyFlightDefinition {
    float speed=24,height=.45f,upMin=4.65f,upMax=4.65f,gravity=4.41f,retention=.9f;
    float radius=.22f,damage=10,life=8;
    bool configured=false;
};
struct SpittyDefinition : AxisWanderDefinition {
    SpittyKind kind=SpittyKind::Normal;
    float contact=10;
    int chance=35,attackFrames=16,shootFrame=6,horizontalFrames=12,verticalFrames=24,walkShootFrame=0;
    SpittyFlightDefinition shot,burst,death;
    int streamCount=1,burstMin=3,burstMax=4,ringCount=8;
    float streamSize=1,streamSizeStep=0,streamAccelerationStep=0,streamJitter=0,streamGravityStep=0;
    float burstSize=.9f,burstSizeToggle=.4f,burstSizeJitter=.05f,deathSize=1.25f,deathOffset=Pi/8;
    bool streamConfigured=false,burstConfigured=false,deathConfigured=false;
};
struct MawDefinition {
    float scale=.1f,force=.13f,retention=.93f,contact=10,shotRadius=.22f;
    bool shoots=true;
    HeadShooterDefinition shot;
    std::optional<HostileHomingDefinition> homing;
    MonsterId child;
    int deathShots=0;
    float deathSpeed=24,deathDamage=10;
};
struct EternalFlyDefinition {
    MonsterId released;
    float radiusX=2.5f,radiusZ=2,phase=.04f*Pi,follow=.5f,contact=10;
    int growthFrames=90,healingFrames=60;
};
enum class HostMotion { Still, Walk, Float };
struct RockWaveDefinition {
    int stepFrames=2,lifeFrames=240,jitterStart=6,jitterRamp=20;
    float spacing=3,radius=2,monsterDamage=32,playerDamage=10,jitterDegrees=75,visualRadius=.5f;
};
struct HostSlamDefinition {
    RockWaveDefinition wave;
    float offset=2,range=12,push=9,hop=27,gravity=99,retention=.8f;
};
struct HostDefinition {
    HostMotion motion=HostMotion::Still;
    bool armored=true;
    int frames=61,openFrame=9,shootFrame=24,closeFrame=55,checkFrames=7,cooldown=7,chance=1,delayLimit=10;
    float range=24,speed=21,inheritVelocity=0,damage=10,life=5,contact=0,healthScale=3.2f;
    float scale=.1f,force=0,retention=.7f,attackRetention=.7f;
    std::vector<Vector2> volley; // Native forward/side coefficients; preserve unequal shot speeds.
    std::optional<HostSlamDefinition> slam;
};
struct MushroomDefinition {
    int hideFrames=6,revealFrames=6,shootFrame=3,timerQuantum=30,blockingChoices=5,revealedChoices=3;
    float closedDamageScale=.25f,speed=21,diagonal=.70710677f,damage=10,life=5,contact=10;
};
struct BuzzChaseDefinition {
    int targetFrames=3,forceFrames=2;
    float axisScale=.5f,deadzone=25,gain=.08f,force=1.2f,contact=10;
};
struct ProjectileBurstDefinition {
    // Installed BURST flag: four perpendicular children, random cross rotation,
    // parent planar speed, .6 size, inherited acceleration, no recursive burst.
    float childScale=.6f,height=.59375f,upMin=-.21f,upMax=.09f;
};
struct ProjectileSplitDefinition {
    float angle=24*Pi/180,speed=30,damage=10,radius=.22f,offset=1,life=5;
};
struct BuzzFlyDefinition {
    float scale=.1f,pursuit=.7f,jitter=.6f,jitterRetention=.4f,retention=.6f,edge=.06f,edgeMargin=3,speedCap=24;
    int pursuitChance=5,morphChance=0;
    MonsterId morph;
    std::optional<HeadShooterDefinition> shot;
    float cooldownRetention=.8f,cooldownWander=.7f;
    // Source mode1 uses approximate rotation coefficients, without normalizing.
    bool paired=false;
    float pairForward=1,pairSide=0;
    std::vector<Vector2> volley; // Forward/side velocity coefficients, never renormalized.
    std::optional<ProjectileSplitDefinition> impactSplit;
    float shotRadius=.22f;
    std::optional<ItemKey> suppressor;
    std::optional<BuzzChaseDefinition> chase;
    std::optional<ItemKey> morphItem;
    MonsterId itemMorph;
    // Only live summons from these sources expire on player contact. Death
    // offspring have no summoner link and retain ordinary persistent contact.
    std::map<MonsterId,float> contactSummoners;
};
struct DungDefinition {
    int firstBand=0,lastBand=1,count=2,hits=4,bonusChance=3;
    float halfWidth=.7f,height=1.1f;
};
// Shared ground lobber: Chase acquires stochastically and holds an attack pose;
// Wander fires along actual travel with an integral source-frame delay.
struct LobWalkerDefinition {
    int chance=60, attackFrames=30, shootFrame=5, initialMin=20, initialMax=39, repeatMin=60, repeatMax=89;
    float range=13, movementRetention=.7f, wanderMin=.7f, wanderMax=1.8f;
    float speed=11.55f, jitter=5.775f, upMin=9.75f, upMax=34.95f;
    float gravity=36.9f, flightRetention=.9f, height=1.15f, radius=.352f;
    float blastDamage=160, playerDamage=20, blastRadius=6;
    FireWaveDefinition fireWave;
    bool flightConfigured=false;
};
struct LethalMorphDefinition {
    MonsterId target;
    int chance=0, chanceOutOf=10000; // Eligible-hit roll; basis points unless overridden.
    bool explicitRoll=false;
    // Ordered weighted choices override target. A single weighted choice still
    // consumes the selection draw (e.g. Flaming Gaper's modulo-three roll).
    std::vector<std::pair<MonsterId,int>> choices;
    float overkill=0, delayMin=0, delayMax=0;
};
struct FlyBombDefinition {
    float circleRange=6,circleStrength=.7f,turnRate=4;
    float fuse=1,radius=3,contactDamage=40,contactPlayerDamage=10,deathDamage=100,deathPlayerDamage=20;
    MonsterId ordnance,orbitOwner;
    int orbitCount=0;
    float orbitRadius=2,orbitSpeed=1.8f;
    bool followConfigured=false;
    float followScale=.1f,followRange=260,followRadius=65,followWobble=5,followFrequency=.02f;
    float followClamp=5,followRadial=.5f,followTangent=.2f,followPursuit=.2f;
    float followDeadzone=25,followGain=.08f,followForce=1.2f,followRetention=.6f;
    float followJitter=.6f,followJitterRetention=.4f,followSpeedCap=24;
};
enum class EnemyBombPayload { Blast, Hot, Sad, Brimstone };
struct EnemyBombDefinition {
    MonsterId ordnance;
    EnemyBombPayload payload=EnemyBombPayload::Blast;
    float fuse=1.5f,radius=3,damage=100,playerDamage=20,flight=.7f,range=14;
    bool harmsSource=false;
    float contactDamage=0,fieldRadius=1,fieldDuration=10,fieldDamage=10;
    int shots=10;
    float shotSpeed=8,shotDamage=10,shotLife=5;
    float beamRange=40,beamRadius=.25f,beamDuration=1,beamDamage=10;
    bool effectConfigured=false;
    int fuseJitterFrames=0;
};
struct ChargeDefinition {
    float speed=11,duration=1.5f,alignment=.8f,recovery=.7f,wanderMin=.7f,wanderMax=1.8f;
    bool diagonal=false, reflect=false;
    float turnRate=0, pause=0, contactDamage=10;
    float trailInterval=0, trailRadius=0, trailDuration=0;
    float tailOffset=0, tailRadius=0; // Fractions of body radius; stays inside navigation hull.
    int deathShots=0;
    float deathAngle=0, deathSpeed=7, deathDamage=10;
    bool modeConfigured=false,trailConfigured=false,tailConfigured=false,deathConfigured=false;
};
struct BossPoolEntry { MonsterId monster; BossForm form=BossForm::Normal; int weight=1; std::optional<FloorVariant> variant; };
struct CompanionDefinition {
    float contactDamage=27.84f, attackInterval=.7f, hurtInterval=.45f, incomingScale=.32f;
};
struct ContactFamiliarDefinition {
    ItemKey item;
    MonsterId child;
    int limit=16;
    float lag=.15f, radius=.6f, contactInterval=.25f;
};
struct MonsterOffspring {
    MonsterId monster;
    int minimum=1, maximum=1;
    float healthScale=1;
};
struct EvaderDefinition {
    float hoverHeight=0; // Ground/cover collision retained; pits may be crossed.
    float scale=.1f, visibleRange=25, hiddenRange=17, attackRange=30;
    float retention=.8f, wanderForce=.5f, wanderRetention=.9f, pathForce=1.079f;
    int proximityFrames=14, evadeChecks=3, attackFrames=18, shootFrame=4, cooldownFrames=75;
    int populationMinimum=4, populationMaximum=8, crowdDelayMinimum=20, crowdDelayMaximum=69;
    int cooldownBonusMinimum=0, cooldownBonusMaximum=0;
    MonsterId child;
    float childHealth=1;
    bool spawns=true,chase=false,childContactDeath=false;
    int detonationChance=0,detonationFrames=0,contactFrames=0;
    float contactRange=0;
};
// Timed status support is opt-in until each controller is reviewed.
struct FreezeDefinition {int capFrames=120;float retention=.01f;};
struct SlowDefinition {float timeScale=.5f,projectileTimeScale=.5f;int refreshFrames=2;};
struct ShrinkDefinition {int capFrames=150;float scale=.333f,approach=1.f/6;};
struct CharmDefinition {
    int targetFrames=15,contactFrames=3;
    float range=500,targetPenalty=1600,healthScale=3.2f;
    float contactOffset=110,contactDivisor=100,contactGain=33,projectileDamage=19.2f;
};
struct DamageStatusDefinition {int capFrames=120,periodFrames=20,firstTick=2;float minimumDamage=6.4f;};
// Native Bouncer phase constants and explicitly tuned 3D locomotion.
struct BouncerDefinition {
    float timerMin=6,timerRange=4,damageDivisor=3.5f,proximity=12,fleeSpeed=3.5f,chaseSpeed=2.7f,contact=10;
    int inflateFrames=21,inflateEvent=7;
};
struct QuakeyDefinition {float interval=4,windup=.45f,flight=.7f,height=3,range=12,shotSpeed=8,damage=10;int rocks=3;};
struct GasDwarfDefinition {float interval=.65f,radius=1.4f,duration=5,blastRadius=2.8f,blastDamage=40,playerDamage=20,shotSpeed=6;};
struct ClackDefinition {float chase=2.5f,wander=1.2f,regrow=3,contact=10;};
struct CreatureCycleDefinition {
    std::optional<BouncerDefinition> bouncer;
    std::optional<QuakeyDefinition> quakey;
    std::optional<GasDwarfDefinition> gasDwarf;
    std::optional<ClackDefinition> clack;
};
struct ChampionDefinition {std::string name;float hp=2,speed=1,visual=1.15f,collision=1,damage=2;int firstStage=1;Color tint{};};
struct HitResponseDefinition {float mass=5,projectile=15,explosion=30,maximum=20;};
struct EnemyStatusDefinition {
    int capFrames=120,confusionRefreshFrames=15;
    float confusionRadius=24,fearAlertRetention=1;
    std::optional<EvaderDefinition> fear;
    std::optional<FreezeDefinition> freeze;
    std::optional<SlowDefinition> slow;
    std::optional<ShrinkDefinition> shrink;
    std::optional<CharmDefinition> charm;
    std::optional<DamageStatusDefinition> poison,burn;
};
struct LeperDefinition : GroundPursuitDefinition {
    EvaderDefinition evade;
    bool evadeConfigured=false,creepConfigured=false;
    int chaseFrames=90,chaseChance=10,restMin=30,restMax=89,transitionFrames=9;
    float chaseRetention=.9f,transitionRetention=.8f,damageScale=3.2f,damageTimerGain=2,knockback=10;
    MonsterId flesh{},gusher{};
    float childOffset=2,childMin=15,childMax=30,childSpread=45,deathMin=6,deathMax=12,overkill=80;
    int morphChance=2,gusherDelayMin=20,gusherDelayMax=39;
    int trailPeriod=10,creepFrames=30,fadeFrames=40;
    float creepMin=.4f,creepMax=1,creepDamage=10,fadeScale=.98f;
};
struct PopulationOffspring {
    float budget=4, crowdScale=.2f, radiusMinimum=.2f, radiusMaximum=.6f;
    int capMinimum=0, capMaximum=0;
    int adjustment=0, minimum=0;
    bool adjusted=false;
};
struct SwimmerDefinition {
    float scale=.1f, acceleration=.016f, maximumAcceleration=.35f, retention=.96f, speedCap=10;
    float groundRetention=.7f, hopMinimum=2, hopMaximum=4, hopHeight=.35f, contactDamage=10;
    int hopChance=2, hopFrames=10, landFrame=6;
    float bounce=-.6f, marginX=10, marginTop=20, marginBottom=4;
};
struct SpiderDefinition {
    float scale=.1f,retention=.6f,force=6,rangeMinimum=100,rangeMaximum=200,prediction=10;
    float wanderMinimum=70,wanderMaximum=110,arrival=14,stuckSpeed=3,contactDamage=10;
    float leftMargin=60,topMargin=70,rightMargin=40,bottomMargin=60;
    int idleFrames=14,wanderFrames=15,gapChance=20;
};
// Installed Rock Spider controller: a falling/disguised rock, a reveal, then
// three heading selections in a 48-count skitter cycle. Distances are native.
// Installed type10 path force/retention. All distances are native pixels;
// scale converts them to this world's units, source updates run at30Hz.
struct GaperDefinition : GroundPursuitDefinition {
    bool frowning=false;
    float awakeForce=.498f;
    int headFrames=1;
};
struct RottenGaperDefinition {
    float scale=.1f,force=.6f,retention=.7f,blockedRetention=.85f,arrivalRetention=.5f;
    float distanceGain=.1f,maxGain=2,arrival=1,stopSpeed=.1f,contact=10;
    int walkFrames=22;
    bool brood=false,orbit=false;
    MonsterId child{};
    int spawnDelay=60,spawnChance=8,childLimit=6,rememberMin=30,rememberMax=44;
    float playerRange=80,peerRange=60,evadeRetention=.8f,evadeForce=1.079f;
    float orbitRadius=60,orbitNear=80,orbitSpan=100,orbitMinimum=.75f,orbitGain=.25f,orbitRetention=.9f,orbitTurn=20;
};
struct SmallMaggotDefinition {
    float scale=.1f,retention=.8f,forceMin=.15f,forceMax=.45f,targetMultiplier=2;
    float curveDegrees=2,lookahead=6,obstacleTurnDegrees=90,alertRange=80,contact=10;
    int initialMin=10,initialMax=39,turnMin=10,turnMax=39;
    int alertInterval=4,alertChance=4,forgetChance=25,obstacleAttempts=10,walkFrames=13;
};
struct HeadlessDefinition {
    bool shooter=false,shotConfigured=false;
    float scale=.1f,force=.5f,retention=.75f,wanderDistance=40,arrival=3,stuckSpeedSquared=.1f,contact=10;
    int stuckChance=10,initialMin=20,initialMax=39,reloadMin=40,reloadMax=59,trailPeriod=10;
    float trailMin=.1f,trailMax=.25f,trailLife=8;
    float shotSpeed=15,shotHeight=1.15f,shotUp=12,gravity=18,shotRetention=.9f,shotRadius=.22f,shotDamage=10,shotLife=8;
    MonsterId broodChild{};
    int broodLimit=5,broodShort=90,broodLong=180;
    float broodRadius=10,broodHeight=-30;
};
struct FacelessDefinition {
    bool tainted=false,shotConfigured=false;
    float scale=.1f,wanderForce=.5f,wanderRetention=.8f,wanderDistance=40,arrival=3,stuckSpeedSquared=.1f;
    int stuckChance=10;
    float pathForce=.6f,pathRetention=.7f,alertRange=80,contact=10;
    float baseChance=.008f,damageChance=.08f,damageScale=3.2f,hurtDecay=.11f,shotCost=7;
    int attackFrames=19,shootFrame=9;
    float overkill=25;
    int morphChance=2,pacerChance=3;
    MonsterId gusher=monsterId(11),pacer=monsterId(11,1);
    int shots=6,trailChance=6;
    float shotSpeed=21,shotHeight=1.15f,shotUp=4.5f,gravity=4.5f,shotRetention=.9f;
    float shotRadius=.22f,shotDamage=10,shotLife=8,trailMin=.1f,trailMax=.35f,trailLife=8;
};
struct DannyDefinition {
    bool coal=false,payloadConfigured=false;
    float scale=.1f,pathForce=.6f,retention=.7f,attackRetention=.7f,contact=10;
    int initialMin=10,initialMax=19,cooldown=150,chance=60,hurtChance=20;
    int farChance=10,attackFrames=38,shootFrame=12,roomLimit=9,ownedLimit=2,total=6;
    float nearRange=200,farRange=400,damageScale=3.2f,hurtThreshold=6,hurtDecay=.11f;
    MonsterId child=monsterId(818),coalBody=monsterId(33,11);
    float childOffset=4,childHeight=-15,childSpread=30,childMin=1,childMax=4;
    float childUpMin=-5,childUpMax=-3;
    float shotHeight=1.15f,shotRadius=.22f,shotDamage=10,shotLife=8;
    float shotSpeed=7,scatter=3.5f,fallMin=-20,fallMax=4,gravity=23.4f,shotRetention=.9f;
};
struct HardyDefinition {
    bool payloadConfigured=false;
    float scale=.1f,retention=.95f,idleRetention=.5f,force=.7f,launch=20;
    float slowSpeed=9,stopSpeed=1,brake=.8f,collisionBrake=.6f,impactDot=.5f;
    int chance=5,checkFrames=5,launchFrame=36,hitFrames=26,cooldown=60,slowAfter=30;
    float contact=10,blastMultiplier=2.5f;
    MonsterId child=monsterId(217),rock=monsterId(818);
    float childHealth=2,childOffset=20,childHeight=-10,childSpread=120;
    float childSpeedMin=1,childSpeedMax=3,childUpMin=-5,childUpMax=-3;
    float shotScale=.1f,shotHeight=1.15f,shotRadius=.22f,shotDamage=10,shotLife=8;
    float ringSpeed=10,clusterSpeed=7,clusterScatter=3.5f,clusterFallMin=-19,clusterFallMax=5;
    float clusterGravity=18.9f,shotRetention=.9f;
};
struct RockSpiderDefinition {
    float scale=.1f,retention=.6f,force=3,spread=30,wanderDistance=20,contactDamage=10;
    int counterStep=1,selectionStep=12,cycle=48,chaseChance=6,wanderAttempts=10;
    int appearFrames=20,wakeChance=4;
    float wakeSpeed=2,gravity=.5f,bounce=-.3f,landingRetention=.8f;
    float wakeVertical=.6f,gridHeight=-4,entityHeight=-50;
    MonsterId deathMorph,deathChild;
    int decayFrames=30,decayChance=3,wetDecayFrames=5;
};
struct LongLegsDefinition {
    bool flee=false;
    float scale=.1f,pathForce=.65f,retention=.8f,attackRetention=.5f,contactDamage=10;
    int chance=50,quietChance=50,populationLimit=6,attackFrames=45,eventFrame=22;
    MonsterId child{};
    int twinChance=0,shots=8;
    float shotMinimum=8,shotMaximum=10,shotHeight=.65f,shotUp=15,shotJitter=.15f,shotGravity=27;
    float creepRadius=1,creepDuration=6;
};
struct SackDefinition {
    float healthScale=3.2f,initialHealth=7,growth=.02f,growthRetention=.64f,healing=1.2f;
    int chance=50,farChance=4,populationLimit=8,attackFrames=24,eventFrame=12,shakeFrames=26;
    float nearRange=23,aimRange=25,aimJitter=2,nearScatter=7,farScatter=10;
    MonsterId child=monsterId(85);
};
enum class BoilPayload { Blood, Ipecac, Spider };
struct BoilDefinition {
    SackDefinition cycle;
    BoilPayload payload=BoilPayload::Blood;
    bool walking=false,projectilesConfigured=false;
    float scale=.1f,retention=.75f,force=.5f,wanderDistance=40,arrival=3;
    float shotSpeed=21,shotScatter=10.5f,shotHeight=1.15f,upMin=7.5f,upMax=43.5f,gravity=63.9f;
    float aimedMultiplierMin=1,aimedMultiplierMax=1,shotRadius=.15f;
    float blastRadius=0,blastDamage=0,playerDamage=20,contactDamage=10,throwHeight=-30;
    int shotMinimum=3,shotMaximum=4;
};
struct StriderDefinition {
    float scale=.1f,retention=.95f,forceMinimum=6,forceMaximum=9,turn=.2f,hover=.8f,contactDamage=10;
    int checkChance=4,chaseChance=2,wanderChance=3,strokeFrames=20,rowFrame=6;
};
struct SwarmHopDefinition {
    int frames=10,jump=2,land=8;
    float minimum=5,maximum=6,spread=45;
};
struct SwarmSpiderDefinition {
    float scale=.1f,retention=.7f,nearRange=100,farRange=200,height=.35f,contactDamage=10;
    int turnChance=4,farTurnChance=20,earlyChance=4;
    bool playerObjectsOnly=true;
    std::array<std::array<int,3>,3> weights{{{5,3,0},{2,3,2},{2,3,9}}};
    std::array<SwarmHopDefinition,3> hops{{{10,2,8,5,6,45},{12,3,9,8,10,20},{18,4,14,10,13,10}}};
};
struct WilloDefinition {
    float scale=.1f,radius=120,ellipse=.84f,angularStep=.054977871f,tracking=.5f,trackingCap=10,carry=2,settleRange=20;
    int chance=9,attackFrames=36,warnFrame=6,shootFrame=24;
    float prediction=1,speed=30,damage=10,height=1.15f,up=-1.5f,gravity=9,retention=.9f,projectileRadius=.25f,life=4;
    bool noWallCollision=true;
};
struct OffspringLaunch {
    float radius=8, scatter=1, heightScale=.1f, initialHeight=-10, initialVelocity=-8, gravity=.7f, planar=.04f;
};
struct DeathOutcome {
    int weight=1;
    std::vector<MonsterOffspring> offspring;
};
enum class OffspringLayout { Radial, Perpendicular };
struct MonsterDeathRule {
    std::string key;
    std::optional<float> overkill;
    float spacing=1,impulse=0;
    OffspringLayout layout=OffspringLayout::Radial;
    std::vector<DeathOutcome> outcomes;
    std::optional<PopulationOffspring> population;
    std::optional<OffspringLaunch> launch;
};
struct MonsterRegrowth {
    float healthRetention=.8f, gooFraction=.25f, delay=2.5f, minimumHealth=12;
    int splitLimit=0;
};
struct FormationDefinition {
    int capacity=10;
    float radius=2.4f, angularSpeed=2.6f, speed=1.4f, gatherSpeed=8;
};
struct HopDefinition {
    float range=6, wanderDistance=2, chaseDistance=4;
    float duration=.7f, height=1.4f, maximumHeight=5, retry=.3f;
};
struct HopRuntime {
    Vector3 start{}, end{};
    float elapsed=0, duration=0, height=0;
    bool active=false, pursuing=false;
};
// Destination-driven source hops: animation controls collision, while inertia
// and the remaining target delta control horizontal travel independently.
struct TargetHopDefinition {
    float scale=.1f;
    int idleFrames=15,hopFrames=26,jumpFrame=4,landFrame=18;
    float bonusA=50,bonusB=70,rangeBase=130,rangeBonus=1.3f,overshoot=200,wander=95;
    float margin=5,grid=40,arrival=10,nearRange=30,farForce=.05f,groundFactor=.1f,retention=.7f;
    float stuckSpeed=.75f;
    int stuckFrames=30,releaseChance=10;
    float height=1.6f,contactDamage=10;
    int leadFrames=0; // Optional source30Hz target-velocity prediction.
};
struct TargetHopRuntime {
    Vector3 destination{},momentum{},lastGround{};
    float clock=0,bonus=0,arc=0;
    int counter=0,frame=-1,hops=0,landings=0;
    bool initialized=false,targetReady=false,pursuing=false,airborne=false,restartAtJump=false;
    // An in-flight fire morph keeps the committed source trajectory until ground.
    std::optional<TargetHopDefinition> transformedFlight;
};
struct LeaperDefinition {
    int chance=7,upFrames=12,jumpFrame=5,downFrames=40,landFrame=22;
    float progressStep=.02f,height=6,searchRadius=12;
    bool sticky=false;
    int shots=4;
    float speed=27,damage=10,life=6,shotHeight=1.15f,upMin=-.15f,upMax=.15f;
    float gravity=4.5f,retention=.9f,radius=.22f,sizeLow=1,sizeStep=0,sizeJitter=0;
    float smallCreep=0,bigCreep=0,creepDuration=10;
};
struct LeaperLanding {Vector3 position{};bool big=false;};
struct LeaperRuntime {
    // 0 ordinary hopping, 1 BigJumpUp, 2 BigJumpDown.
    int phase=0,frame=0,leaps=0,bigLandings=0,volleys=0,creepPatches=0;
    float progress=0;
    Vector3 target{},start{};
    std::optional<LeaperLanding> pending;
};
struct EggyDefinition {
    int restartChance=3,deathFrames=70,releaseFrame=7,childAdvance=2;
    float creepRadius=1.28f,creepDuration=5,scatter=.1f;
    MonsterId child=monsterId(884);
    std::array<int,3> weights{3,2,1};
    std::vector<int> releaseCounters;
};
struct HopRingStage {int count=4;float speed=24;};
struct HopRingDefinition {
    float damage=10,life=6,radius=.18f;
    float height=1.15f,upMin=-.15f,upMax=.15f,gravity=1.35f,flightRetention=.9f;
    std::vector<HopRingStage> stages;
};
struct HopRingVolley {Vector3 position{};int stage=0;};
struct HopRingRuntime {
    int stage=0,animationStage=0,volleys=0,cycles=0;
    bool chainPending=false;
    std::vector<HopRingVolley> pending;
};
enum class DamageKind { Physical, Flame, Burning, Crush };
struct AdaptiveArmorDefinition {
    float strength=30,minimum=.09f,correction=.18f;
    int historyFrames=120;
};
enum class FireTrigger { Flame, Burning, Both };
enum class TransformHealth { Fraction, Current };
struct FireReaction {
    bool dryOnly=false;
    float flameScale=1, burningScale=1;
    std::optional<MonsterId> transform;
    FireTrigger trigger=FireTrigger::Both;
    TransformHealth health=TransformHealth::Fraction;
};

// State graphs use named engine primitives. New native actions can be added without
// replacing the graph interpreter; unsupported actions are rejected at load time.
enum class BehaviorGuard { Always, Timer, AttackReady, CooldownReady, HealthBelow, AlignedAttackReady };
enum class BehaviorAction { None, LockTarget, Fire, ResetCooldown, Warning, Summon };
enum class BehaviorPose { Ready, Windup, Exposed };
enum class BehaviorMotion { Still, Chase, Flee, Wander, Orbit, AxisWander };
enum class BehaviorAim { Locked, Facing, Player };
enum class BehaviorPattern { Fan, Radial };
// Presentation is independent of ground effects: ember-looking shots do not
// imply a fire patch. Tar retains the existing slowing-patch impact primitive.
enum class BehaviorShot { Bullet, Tar, Ember, Brown, Bone, DarkBone };
struct BehaviorTransition {
    std::string to;
    BehaviorGuard guard = BehaviorGuard::Timer;
    float value = 0;
    size_t target = 0;
};
struct BehaviorState {
    std::string name;
    BehaviorPose pose=BehaviorPose::Ready;
    BehaviorMotion motion=BehaviorMotion::Still;
    float duration=0, damageScale=1, motionSpeed=1;
    bool useWindup=false;
    std::vector<BehaviorAction> enter,exit;
    std::vector<BehaviorTransition> transitions;
};
struct BehaviorSummon {
    MonsterId monster;
    int count=1, ownerLimit=6;
    float healthScale=1, spacing=1.6f;
};
struct BehaviorDefinition {
    std::string key,initial;
    float range=24;
    int projectileCount=1;
    float spread=0, projectileDamage=10, projectileSpeed=9;
    BehaviorAim projectileAim=BehaviorAim::Locked;
    BehaviorPattern projectilePattern=BehaviorPattern::Fan;
    BehaviorShot projectileKind=BehaviorShot::Bullet;
    float projectileAngle=0, projectileCurve=0;
    bool alternateCurve=false;
    float projectileLife=5, wanderMin=.7f, wanderMax=1.8f;
    float orbitRadius=3.5f, acceleration=6;
    float alignment=0, alignmentInterval=.1f, alignmentPrediction=0;
    bool alignmentConfigured=false;
    std::optional<BehaviorSummon> summon;
    size_t initialIndex=0;
    std::vector<BehaviorState> states;
};
struct BehaviorRuntime {
    std::string graph;
    size_t state=0;
    float elapsed=0;
    bool initialized=false;
    int64_t alignmentTick=-1;
    Vector3 momentum{};
    float orbitSign=0;
    uint64_t volleys=0;
};

class MechanicsLibrary {
  public:
    // Build a new immutable snapshot. Failure never mutates a running library.
    static std::shared_ptr<const MechanicsLibrary> load(const std::filesystem::path &directory);
    std::span<const ItemDefinition> items() const { return items_; }
    std::span<const MonsterDefinition> monsters() const { return monsters_; }
    const ItemDefinition *item(const ItemKey &key) const;
    const MonsterDefinition *monster(MonsterId id) const;
    const BehaviorDefinition *behavior(std::string_view key) const;
    const MonsterDeathRule *deathRule(MonsterId id) const;
    const MonsterRegrowth *regrowth(MonsterId id) const;
    const FormationDefinition *formation(MonsterId id) const;
    const FireReaction *fireReaction(MonsterId id) const;
    const HopDefinition *hop(MonsterId id) const;
    const TargetHopDefinition *targetHop(MonsterId id) const;
    const LeaperDefinition *leaper(MonsterId id) const;
    const EggyDefinition *eggy(MonsterId id) const;
    const HopRingDefinition *hopRings(MonsterId id) const;
    const AdaptiveArmorDefinition *adaptiveArmor(MonsterId id) const;
    const PeepDefinition *peep(MonsterId id) const;
    const LokiDefinition *loki(MonsterId id) const;
    const HornfelDefinition *hornfel(MonsterId id) const;
    const HornfelDecoyDefinition *hornfelDecoy(MonsterId id) const;
    const EnvironmentActorDefinition *environmentActor(MonsterId id) const;
    const RailTrafficDefinition *railTraffic(MonsterId owner) const;
    const BloatDefinition *bloat(MonsterId id) const;
    const SegmentedBossDefinition *segmentedBoss(MonsterId id) const;
    const ShellBossDefinition *shell(MonsterId id) const;
    const DeathCrossDefinition *deathCross(MonsterId id) const;
    const DeathBlastDefinition *deathBlast(MonsterId id) const;
    const SourceImmunityDefinition *sourceImmunity(MonsterId id) const;
    const MawDefinition *maw(MonsterId id) const;
    const SpittyDefinition *spitty(MonsterId id) const;
    const CardinalWalkerDefinition *cardinalWalker(MonsterId id) const;
    const VisDefinition *vis(MonsterId id) const;
    const GutsDefinition *guts(MonsterId id) const;
    const MaskArmorDefinition *maskArmor(MonsterId id) const;
    const KnightDefinition *knight(MonsterId id) const;
    const MirrorDefinition *mirror(MonsterId id) const;
    const AdultLeechDefinition *adultLeech(MonsterId id) const;
    const SlideDefinition *slide(MonsterId id) const;
    const MemBrainDefinition *memBrain(MonsterId id) const;
    const LumpDefinition *lump(MonsterId id) const;
    const LeechDefinition *leech(MonsterId id) const;
    const LinkedRemnantDefinition *linkedRemnant(MonsterId id) const;
    const LandingCreepDefinition *landingCreep(MonsterId id) const;
    const ReturningBodyDefinition *returningBody(MonsterId id) const;
    const BrainDefinition *brain(MonsterId id) const;
    const LinkedHeadDefinition *linkedHead(MonsterId id) const;
    const BabyDefinition *baby(MonsterId id) const;
    bool linkedNeck(MonsterId id) const;
    const HostDefinition *host(MonsterId id) const;
    const MushroomDefinition *mushroom(MonsterId id) const;
    const EternalFlyDefinition *eternalFly(MonsterId id) const;
    const HeadShooterDefinition *headShooter(MonsterId id) const;
    const BuzzFlyDefinition *buzzFly(MonsterId id) const;
    const EvaderDefinition *evader(MonsterId id) const;
    const CreatureCycleDefinition *creatureCycle(MonsterId id) const {auto i=creatureCycles_.find(id);return i==creatureCycles_.end()?nullptr:&i->second;}
    const ChampionDefinition *champion(int id) const {auto i=champions_.find(id);return i==champions_.end()?nullptr:&i->second;}
    int championChance() const {return championChance_;}
    const HitResponseDefinition *hitResponse(MonsterId id) const {auto i=hitResponses_.find(id);return i==hitResponses_.end()?nullptr:&i->second;}
    const EnemyStatusDefinition *enemyStatuses(MonsterId id) const;
    const SwimmerDefinition *swimmer(MonsterId id) const;
    const SpiderDefinition *spider(MonsterId id) const;
    const HardyDefinition *hardy(MonsterId id) const;
    const DannyDefinition *danny(MonsterId id) const;
    const GaperDefinition *gaper(MonsterId id) const;
    const BlackGlobinDefinition *blackGlobin(MonsterId id) const;
    const LeperFleshDefinition *leperFlesh(MonsterId id) const;
    const LeperDefinition *leper(MonsterId id) const;
    const RottenGaperDefinition *rottenGaper(MonsterId id) const;
    const SmallMaggotDefinition *smallMaggot(MonsterId id) const;
    const HeadlessDefinition *headless(MonsterId id) const;
    const FacelessDefinition *faceless(MonsterId id) const;
    const RockSpiderDefinition *rockSpider(MonsterId id) const;
    const StriderDefinition *strider(MonsterId id) const;
    const LongLegsDefinition *longLegs(MonsterId id) const;
    const SackDefinition *sack(MonsterId id) const;
    const BoilDefinition *boil(MonsterId id) const;
    const SwarmSpiderDefinition *swarmSpider(MonsterId id) const;
    MonsterId spawnIdentity(MonsterId id,const FloorProfile &profile) const;
    const WilloDefinition *willo(MonsterId id) const;
    const std::optional<DungDefinition> &dung() const { return dung_; }
    const LobWalkerDefinition *lobWalker(MonsterId id) const;
    const LethalMorphDefinition *lethalMorph(MonsterId id) const;
    const ChargeDefinition *charge(MonsterId id) const;
    const CompanionDefinition *companion(MonsterId id) const;
    const StatueDefinition *statue(MonsterId id) const;
    const std::vector<StatuePoolEntry> &statuePool(int band) const { return statuePools_.at(size_t(band)); }
    int statueChance(int band) const { return statueChances_.at(size_t(band)); }
    std::span<const ContactFamiliarDefinition> contactFamiliars() const { return contactFamiliars_; }
    bool monsterBoss(MonsterId id) const { return peep(id)||bloat(id)||segmentedBoss(id)||loki(id)||hornfel(id); }
    bool bossFormAllowed(MonsterId id,BossForm form) const;
    const ComponentDefinition *component(MonsterId id) const;
    const FlyBombDefinition *flyBomb(MonsterId id) const;
    const EnemyBombDefinition *enemyBomb(std::string_view key) const;
    const RailLayout *railLayout(std::string_view key) const;
    const auto &railLayouts() const { return railLayouts_; }
    const BoomFlyDefinition *boomFly(MonsterId id) const;
    float monsterHealth(MonsterId id,int sourceStage) const;
    const StageHealthDefinition *stageHealth(MonsterId id) const;
    float regularHealthMultiplier() const {return regularHealthMultiplier_;}
    float regularHealthAdjustment(MonsterId id) const {return regularHealthIds_.contains(id)?regularHealthMultiplier_:1.f;}
    bool regularHealthMember(MonsterId id) const {return regularHealthIds_.contains(id);}
    const std::vector<WeightedItem> &pool(std::string_view key) const;
    const EncounterPool &encounterPool(int band, EncounterPattern pattern) const;
    const MonsterReplacement *replacement(MonsterId source,const FloorProfile &profile,int phase=0) const;
    int replacementCost(MonsterId source,const FloorProfile &profile) const;
    FloorProfile configureFloor(FloorProfile profile,uint64_t seed) const;
    ResolvedBuild resolve(std::span<const ItemKey> inventory,float damage,float speed,bool sixth) const;
    const std::string &fingerprint() const { return fingerprint_; }
    const std::filesystem::path &directory() const { return directory_; }
  private:
    std::filesystem::path directory_;
    std::string fingerprint_;
    std::vector<ItemDefinition> items_;
    std::vector<MonsterDefinition> monsters_;
    std::vector<BuildRule> rules_;
    std::map<std::string,BehaviorDefinition,std::less<>> behaviors_;
    std::map<std::string,MonsterDeathRule,std::less<>> deaths_;
    std::map<MonsterId,std::string> deathBindings_;
    std::map<MonsterId,MonsterRegrowth> regrowth_;
    std::map<MonsterId,FormationDefinition> formations_;
    std::map<MonsterId,FireReaction> fireReactions_;
    std::map<MonsterId,HopDefinition> hops_;
    std::map<MonsterId,TargetHopDefinition> targetHops_;
    std::map<MonsterId,LeaperDefinition> leapers_;
    std::map<MonsterId,EggyDefinition> eggies_;
    std::map<MonsterId,HopRingDefinition> hopRings_;
    std::map<MonsterId,AdaptiveArmorDefinition> adaptiveArmor_;
    std::map<MonsterId,PeepDefinition> peeps_;
    std::map<MonsterId,LokiDefinition> lokis_;
    std::map<MonsterId,HornfelDefinition> hornfels_;
    std::map<MonsterId,HornfelDecoyDefinition> hornfelDecoys_;
    std::map<MonsterId,EnvironmentActorDefinition> environmentActors_;
    std::map<MonsterId,RailTrafficDefinition> railTraffic_;
    std::map<MonsterId,BloatDefinition> bloats_;
    std::map<MonsterId,SegmentedBossDefinition> segmentedBosses_;
    std::map<MonsterId,ShellBossDefinition> shells_;
    std::map<MonsterId,DeathCrossDefinition> deathCrosses_;
    std::map<MonsterId,DeathBlastDefinition> deathBlasts_;
    std::map<MonsterId,SourceImmunityDefinition> sourceImmunities_;
    std::map<MonsterId,LobWalkerDefinition> lobWalkers_;
    std::map<MonsterId,MawDefinition> maws_;
    std::map<MonsterId,SpittyDefinition> spitties_;
    std::map<MonsterId,CardinalWalkerDefinition> cardinalWalkers_;
    std::map<MonsterId,VisDefinition> vis_;
    std::map<MonsterId,GutsDefinition> guts_;
    std::map<MonsterId,MaskArmorDefinition> maskArmor_;
    std::map<MonsterId,KnightDefinition> knights_;
    std::map<MonsterId,MirrorDefinition> mirrors_;
    std::map<MonsterId,AdultLeechDefinition> adultLeeches_;
    std::map<MonsterId,MemBrainDefinition> memBrains_;
    std::map<MonsterId,SlideDefinition> slides_;
    std::map<MonsterId,LumpDefinition> lumps_;
    std::map<MonsterId,LeechDefinition> leeches_;
    std::map<MonsterId,LinkedRemnantDefinition> linkedRemnants_;
    std::map<MonsterId,LandingCreepDefinition> landingCreep_;
    std::map<MonsterId,ReturningBodyDefinition> returningBodies_;
    std::map<MonsterId,BrainDefinition> brains_;
    std::map<MonsterId,LinkedHeadDefinition> linkedHeads_;
    std::map<MonsterId,BabyDefinition> babies_;
    std::map<MonsterId,HostDefinition> hosts_;
    std::map<MonsterId,MushroomDefinition> mushrooms_;
    std::map<MonsterId,EternalFlyDefinition> eternalFlies_;
    std::map<MonsterId,HeadShooterDefinition> headShooters_;
    std::map<MonsterId,BuzzFlyDefinition> buzzFlies_;
    std::map<MonsterId,EvaderDefinition> evaders_;
    std::map<int,ChampionDefinition> champions_;
    std::map<MonsterId,CreatureCycleDefinition> creatureCycles_;
    int championChance_=0;
    std::map<MonsterId,HitResponseDefinition> hitResponses_;
    std::map<MonsterId,EnemyStatusDefinition> enemyStatuses_;
    std::map<MonsterId,SwimmerDefinition> swimmers_;
    std::map<MonsterId,SpiderDefinition> spiders_;
    std::map<MonsterId,HardyDefinition> hardies_;
    std::map<MonsterId,DannyDefinition> dannies_;
    std::map<MonsterId,GaperDefinition> gapers_;
    std::map<MonsterId,BlackGlobinDefinition> blackGlobins_;
    std::map<MonsterId,LeperFleshDefinition> leperFlesh_;
    std::map<MonsterId,LeperDefinition> lepers_;
    std::map<MonsterId,RottenGaperDefinition> rottenGapers_;
    std::map<MonsterId,SmallMaggotDefinition> smallMaggots_;
    std::map<MonsterId,HeadlessDefinition> headless_;
    std::map<MonsterId,FacelessDefinition> faceless_;
    std::map<MonsterId,RockSpiderDefinition> rockSpiders_;
    std::map<MonsterId,StriderDefinition> striders_;
    std::map<MonsterId,LongLegsDefinition> longLegs_;
    std::map<MonsterId,SackDefinition> sacks_;
    std::map<MonsterId,BoilDefinition> boils_;
    std::map<MonsterId,SwarmSpiderDefinition> swarmSpiders_;
    std::map<MonsterId,WilloDefinition> willos_;
    std::optional<DungDefinition> dung_;
    std::map<MonsterId,LethalMorphDefinition> lethalMorphs_;
    std::map<MonsterId,FlyBombDefinition> flyBombs_;
    std::map<std::string,EnemyBombDefinition,std::less<>> enemyBombs_;
    std::map<std::string,RailLayout,std::less<>> railLayouts_;
    std::map<MonsterId,BoomFlyDefinition> boomFlies_;
    std::map<MonsterId,StageHealthDefinition> stageHealth_;
    std::set<MonsterId> regularHealthIds_;
    float regularHealthMultiplier_=1;
    bool explicitRegularHealthMultiplier_=false;
    std::array<std::array<int,2>,4> sourceStages_{{{1,2},{3,4},{5,6},{7,8}}};
    std::array<bool,4> explicitSourceStages_{};
    std::map<MonsterId,ChargeDefinition> charges_;
    std::map<MonsterId,CompanionDefinition> companions_;
    std::map<MonsterId,StatueDefinition> statues_;
    std::array<std::vector<StatuePoolEntry>,4> statuePools_;
    std::array<int,4> statueChances_{};
    std::array<bool,4> explicitStatueChances_{};
    std::vector<ContactFamiliarDefinition> contactFamiliars_;
    std::set<MonsterId> bloatLasers_,bloatIpecac_;
    std::map<MonsterId,ComponentDefinition> components_;
    std::array<std::vector<BossPoolEntry>,4> bossPools_;
    std::array<int,4> nativeBossWeights_{1,1,1,1};
    std::array<bool,4> explicitNativeBossWeights_{};
    std::map<ItemKey,size_t> itemIndex_;
    std::map<MonsterId,size_t> monsterIndex_;
    std::map<std::string,std::vector<WeightedItem>,std::less<>> pools_;
    std::array<std::array<EncounterPool,4>,4> encounters_;
    std::vector<MonsterReplacement> replacements_;
    std::array<std::map<FloorVariant,int>,4> floorVariants_;
};
std::shared_ptr<const MechanicsLibrary> defaultMechanics();
} // namespace dw
