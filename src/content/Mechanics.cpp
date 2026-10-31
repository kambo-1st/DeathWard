#include "content/Mechanics.hpp"
#include "platform/Assets.hpp"
#include <fstream>
#include <iomanip>
#include <set>
#include <sstream>
#include <stdexcept>

namespace dw {
namespace {
template<class T> T named(std::string_view name,std::initializer_list<std::pair<std::string_view,T>> values) {
    for(const auto &[key,value]:values)if(key==name)return value;
    throw std::runtime_error("Unknown value '"+std::string(name)+"'");
}
BuildStat stat(std::string_view s) {
    constexpr std::array<std::string_view,size_t(BuildStat::Count)> names{
        "damage","speed","life","radius","homing","return_range","cap_damage","cap_radius",
        "cap_self_damage","pierce","bounces","pellets","cadence","scatter","rail"};
    for(size_t i=0;i<names.size();++i)if(names[i]==s)return BuildStat(i);
    throw std::runtime_error("Unknown build stat '"+std::string(s)+"'");
}
void require(bool ok,const std::string &message) { if(!ok)throw std::runtime_error(message); }
std::string word(std::istream &in) { std::string s;if(!(in>>std::quoted(s)))throw std::runtime_error("Expected a value");return s; }
float real(std::istream &in) {
    const auto s=word(in);size_t end=0;float n=std::stof(s,&end);
    require(end==s.size()&&std::isfinite(n)&&std::abs(n)<=1000000,"Expected finite number in [-1000000,1000000]");return n;
}
int integer(std::istream &in,int minimum,int maximum) {
    const auto s=word(in);size_t end=0;const int n=std::stoi(s,&end);
    require(end==s.size()&&n>=minimum&&n<=maximum,"Integer outside allowed range");return n;
}
bool flag(std::istream &in) { return integer(in,0,1)!=0; }
GroundPursuitDefinition readGroundPursuit(std::istream &row) {
    GroundPursuitDefinition p;
    p.scale=real(row);p.force=real(row);p.retention=real(row);p.blockedRetention=real(row);p.arrivalRetention=real(row);
    p.distanceGain=real(row);p.maxGain=real(row);p.arrival=real(row);p.stopSpeed=real(row);p.contact=real(row);
    p.walkFrames=integer(row,2,300);
    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.retention>0&&p.retention<1&&
        p.blockedRetention>0&&p.blockedRetention<=1&&p.arrivalRetention>0&&p.arrivalRetention<=1&&
        p.distanceGain>0&&p.distanceGain<=10&&p.maxGain>0&&p.maxGain<=10&&p.arrival>0&&p.arrival<=100&&
        p.stopSpeed>0&&p.stopSpeed<=10&&p.contact>0&&p.contact<=100,"Invalid ground pursuit profile");
    return p;
}
SackDefinition readSackCycle(std::istream &row) {
    SackDefinition p;
    p.healthScale=real(row);p.initialHealth=real(row);p.growth=real(row);p.growthRetention=real(row);p.healing=real(row);
    p.chance=integer(row,1,10000);p.farChance=integer(row,1,10000);p.populationLimit=integer(row,1,256);
    p.attackFrames=integer(row,2,300);p.eventFrame=integer(row,1,p.attackFrames-1);p.shakeFrames=integer(row,1,300);
    p.nearRange=real(row);p.aimRange=real(row);p.aimJitter=real(row);p.nearScatter=real(row);p.farScatter=real(row);
    p.child=parseMonsterId(word(row));
    require(p.healthScale>0&&p.healthScale<=10&&p.initialHealth>0&&p.growth>0&&p.growth<=1&&
        p.growthRetention>0&&p.growthRetention<1&&p.healing>0&&p.healing<=10&&p.nearRange>0&&
        p.aimRange>p.aimJitter&&p.aimJitter>=0&&p.nearScatter>0&&p.farScatter>0&&p.farScatter<=30,
        "Invalid Sack/growing Boil cycle");
    return p;
}
BehaviorAction action(std::string_view s) {
    return named<BehaviorAction>(s,{{"lock_target",BehaviorAction::LockTarget},{"fire",BehaviorAction::Fire},
        {"reset_cooldown",BehaviorAction::ResetCooldown},{"warning",BehaviorAction::Warning},{"summon",BehaviorAction::Summon}});
}
size_t copies(std::span<const ItemKey> inventory,const ItemKey &key) { return size_t(std::count(inventory.begin(),inventory.end(),key)); }
}

std::shared_ptr<const MechanicsLibrary> MechanicsLibrary::load(const std::filesystem::path &directory) {
    auto lib=std::shared_ptr<MechanicsLibrary>(new MechanicsLibrary);
    lib->directory_=directory;
    std::vector<std::filesystem::path> files;
    for(const auto &entry:std::filesystem::directory_iterator(directory))
        if(entry.is_regular_file()&&entry.path().extension()==".mechanics")files.push_back(entry.path());
    std::sort(files.begin(),files.end());require(!files.empty(),"No .mechanics files in "+directory.string());
    uint64_t hash=14695981039346656037ULL;
    for(const auto &path:files) {
        std::ifstream in(path);require(bool(in),"Cannot read "+path.string());
        std::string line;size_t lineNumber=0;bool header=false;
        ItemDefinition *item=nullptr;BuildRule *rule=nullptr;BehaviorDefinition *graph=nullptr;BehaviorState *state=nullptr;
        MonsterDeathRule *death=nullptr;DeathOutcome *outcome=nullptr;
        while(std::getline(in,line)) {
            ++lineNumber;for(unsigned char ch:line){hash^=ch;hash*=1099511628211ULL;}hash^='\n';hash*=1099511628211ULL;
            try {
                std::istringstream row(line);row>>std::ws;if(row.eof()||row.peek()=='#')continue;
                const auto command=word(row);
                if(!header){require(command=="DEATHWARD_MECHANICS"&&integer(row,1,1)==1,"Expected DEATHWARD_MECHANICS 1");header=true;}
                else if(command=="item") {
                    require(!item&&!rule&&!graph&&!death,"Unclosed definition");ItemDefinition next;next.id=parseItemKey(word(row));
                    next.name=word(row);next.rarity=word(row);next.description=word(row);
                    require(lib->items_.size()<8192&&!lib->itemIndex_.contains(next.id),"Duplicate item ID or item capacity exceeded");
                    lib->itemIndex_[next.id]=lib->items_.size();lib->items_.push_back(std::move(next));item=&lib->items_.back();
                } else if(command=="hook") {
                    require(item,"hook outside item");const auto name=word(row);const auto mode=word(row);
                    require(name=="split"||name=="powder"||name=="ghost"||name=="cap","Unknown native item hook '"+name+"'");
                    require(mode=="once"||mode=="per_copy","Expected once or per_copy");
                    require(item->effects.size()<32,"Too many item hooks");item->effects.push_back({name,mode=="per_copy"});
                } else if(command=="pickup_health") {
                    require(item,"pickup_health outside item");item->pickupHealthMultiplier=real(row);item->pickupHealthFloor=real(row);
                    require(item->pickupHealthMultiplier>0&&item->pickupHealthMultiplier<=10&&item->pickupHealthFloor>0,"Invalid pickup health rule");
                } else if(command=="rule") {
                    require(!item&&!rule&&!graph&&!death,"Unclosed definition");BuildRule next;next.key=word(row);next.priority=integer(row,-100000,100000);
                    next.owner=parseItemKey(word(row));next.stackCap=integer(row,0,256);const auto when=word(row);
                    require(when=="always"||when=="sixth","Unknown rule condition");next.sixthOnly=when=="sixth";
                    require(lib->rules_.size()<32768,"Too many rules");lib->rules_.push_back(std::move(next));rule=&lib->rules_.back();
                } else if(command=="requires") {
                    require(rule,"requires outside rule");ItemRequirement r;r.item=parseItemKey(word(row));r.minimum=integer(row,0,256);r.maximum=integer(row,-1,256);
                    require(r.maximum==-1||r.maximum>=r.minimum,"Invalid stack interval");rule->requirements.push_back(r);
                } else if(command=="modify") {
                    require(rule,"modify outside rule");BuildModifier m;m.stat=stat(word(row));m.operation=named<ModifierOp>(word(row),{{"set",ModifierOp::Set},{"add",ModifierOp::Add},
                        {"multiply",ModifierOp::Multiply},{"min",ModifierOp::Minimum},{"max",ModifierOp::Maximum},{"ratio",ModifierOp::Ratio}});
                    if(m.operation==ModifierOp::Ratio)m.denominator=stat(word(row));
                    m.first=real(row);m.extra=real(row);const auto mode=word(row);require(mode=="once"||mode=="per_copy","Expected once or per_copy");m.perCopy=mode=="per_copy";
                    require(rule->modifiers.size()<128,"Too many modifiers");rule->modifiers.push_back(m);
                } else if(command=="monster") {
                    require(!item&&!rule&&!graph&&!death,"monster inside another definition");MonsterDefinition d;d.id=parseMonsterId(word(row));d.name=word(row);
                    d.motion=named<MonsterMotion>(word(row),{{"Still",MonsterMotion::Still},{"Chase",MonsterMotion::Chase},{"Wander",MonsterMotion::Wander},{"Flee",MonsterMotion::Flee},{"Bounce",MonsterMotion::Bounce},{"Charge",MonsterMotion::Charge},{"Hop",MonsterMotion::Hop},{"Burrow",MonsterMotion::Burrow},{"Teleport",MonsterMotion::Teleport},{"Mirror",MonsterMotion::Mirror},{"Wall",MonsterMotion::Wall},{"Chain",MonsterMotion::Chain},{"Orbit",MonsterMotion::Orbit}});
                    d.attack=named<MonsterAttack>(word(row),{{"None",MonsterAttack::None},{"Shot",MonsterAttack::Shot},{"Spread",MonsterAttack::Spread},{"Cross",MonsterAttack::Cross},{"Diagonal",MonsterAttack::Diagonal},{"Ring",MonsterAttack::Ring},{"Burst",MonsterAttack::Burst},{"Lob",MonsterAttack::Lob},{"Spawn",MonsterAttack::Spawn},{"Beam",MonsterAttack::Beam},{"DoubleBeam",MonsterAttack::DoubleBeam},{"QuadBeam",MonsterAttack::QuadBeam},{"Head",MonsterAttack::Head},{"Light",MonsterAttack::Light},{"Spitty",MonsterAttack::Spitty}});
                    d.shape=named<MonsterShape>(word(row),{{"Walker",MonsterShape::Walker},{"Headless",MonsterShape::Headless},{"Fly",MonsterShape::Fly},{"Blob",MonsterShape::Blob},{"Worm",MonsterShape::Worm},{"Skull",MonsterShape::Skull},{"Spider",MonsterShape::Spider},{"Eye",MonsterShape::Eye},{"Stone",MonsterShape::Stone}});
                    d.hp=real(row);d.speed=real(row);d.radius=real(row);d.cooldown=real(row);d.windup=real(row);d.depth=integer(row,1,1000);
                    d.flying=flag(row);d.contact=flag(row);d.roomHazard=flag(row);d.natural=flag(row);d.behavior=word(row);
                    require(d.id.type>0&&d.hp>=0&&d.speed>=0&&d.speed<=200&&d.radius>0&&d.radius<=100&&d.cooldown>=Tick&&d.windup>=0,"Invalid monster stats");
                    require(lib->monsters_.size()<8192&&!lib->monsterIndex_.contains(d.id),"Duplicate monster ID or capacity exceeded");
                    lib->monsterIndex_[d.id]=lib->monsters_.size();lib->monsters_.push_back(std::move(d));
                } else if(command=="stage_health") {
                    require(!item&&!rule&&!graph&&!death,"stage_health inside definition");
                    const auto id=parseMonsterId(word(row));StageHealthDefinition p;
                    p.base=real(row);p.perStage=real(row);p.scale=real(row);
                    require(p.base>=0&&p.perStage>=0&&p.scale>0&&p.scale<=100&&
                        (p.base+p.perStage)*p.scale>0&&(p.base+8*p.perStage)*p.scale<=1000000,"Invalid stage health");
                    require(lib->stageHealth_.emplace(id,p).second,"Duplicate stage health");
                } else if(command=="source_stages") {
                    require(!item&&!rule&&!graph&&!death,"source_stages inside definition");
                    const int band=integer(row,0,3),first=integer(row,1,13),second=integer(row,first,13);
                    require(!lib->explicitSourceStages_[size_t(band)],"Duplicate source stage mapping");
                    lib->explicitSourceStages_[size_t(band)]=true;lib->sourceStages_[size_t(band)]={first,second};
                } else if(command=="boom_fly") {
                    require(!item&&!rule&&!graph&&!death,"boom_fly inside definition");
                    const auto id=parseMonsterId(word(row));BoomFlyDefinition p;
                    p.kind=named<BoomFlyKind>(word(row),{{"normal",BoomFlyKind::Normal},{"red",BoomFlyKind::Red},
                        {"drowned",BoomFlyKind::Drowned},{"dragon",BoomFlyKind::Dragon},{"bone",BoomFlyKind::Bone},
                        {"sick",BoomFlyKind::Sick},{"tainted",BoomFlyKind::Tainted}});
                    p.contact=real(row);p.blastDamage=real(row);p.playerDamage=real(row);p.blastRadius=real(row);p.blastDelay=real(row);p.diagonal=flag(row);
                    require(p.contact>0&&p.contact<=1000&&p.blastDamage>=0&&p.blastDamage<=1000&&p.playerDamage>=0&&p.playerDamage<=1000&&
                        p.blastRadius>0&&p.blastRadius<=10&&p.blastDelay>=0&&p.blastDelay<=10,"Invalid Boom Fly contact or blast");
                    require(p.kind!=BoomFlyKind::Tainted||p.blastDelay>=Tick,"Tainted blast requires a warning interval");
                    require(lib->boomFlies_.emplace(id,p).second,"Duplicate Boom Fly controller");
                } else if(command=="boom_shots"||command=="boom_field"||command=="boom_child") {
                    require(!item&&!rule&&!graph&&!death,"Boom Fly extension inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->boomFlies_.find(id);
                    require(it!=lib->boomFlies_.end(),"Boom Fly extension requires a preceding controller");auto &p=it->second;
                    if(command=="boom_shots") {
                        require(!p.shotsConfigured,"Duplicate Boom Fly shots");p.shots=integer(row,1,32);
                        p.shotSpeed=real(row);p.shotDamage=real(row);p.interval=real(row);p.alignment=real(row);p.range=real(row);
                        require(p.shotSpeed>0&&p.shotSpeed<=50&&p.shotDamage>0&&p.shotDamage<=1000&&p.interval>=Tick&&p.interval<=60&&
                            p.alignment>0&&p.alignment<=5&&p.range>0&&p.range<=100,"Invalid Boom Fly shots");p.shotsConfigured=true;
                    } else if(command=="boom_field") {
                        require(!p.fieldConfigured,"Duplicate Boom Fly field");
                        p.trailInterval=real(row);p.trailRadius=real(row);p.trailDuration=real(row);p.deathRadius=real(row);
                        p.deathDuration=real(row);p.cloudSpread=real(row);p.lineRange=real(row);p.lineStep=real(row);p.lineDelay=real(row);p.fieldDamage=real(row);
                        require(p.trailInterval>=.1f&&p.trailInterval<=30&&p.trailRadius>0&&p.trailRadius<=5&&p.trailDuration>0&&p.trailDuration<=60&&
                            p.deathRadius>0&&p.deathRadius<=5&&p.deathDuration>0&&p.deathDuration<=60&&p.cloudSpread>0&&p.cloudSpread<=8&&
                            p.lineRange>0&&p.lineRange<=100&&p.lineStep>=.5f&&p.lineStep<=5&&p.lineRange/p.lineStep<=64&&
                            p.lineDelay>=0&&p.lineDelay<=1&&p.fieldDamage>0&&p.fieldDamage<=1000,"Invalid Boom Fly field");p.fieldConfigured=true;
                    } else {
                        require(!p.child&&p.kind==BoomFlyKind::Drowned,"Child requires one Drowned controller");
                        p.child=parseMonsterId(word(row));p.childChance=integer(row,0,10000);
                    }
                } else if(command=="boss_chain") {
                    require(!item&&!rule&&!graph&&!death,"boss_chain inside definition");
                    const auto id=parseMonsterId(word(row));SegmentedBossDefinition p;
                    p.chains=integer(row,1,4);p.segments=integer(row,3,16);p.splitMinimum=integer(row,2,8);
                    p.supplier=parseMonsterId(word(row));p.suppliers=integer(row,1,4);
                    p.spacing=real(row);p.armor=real(row);p.blastNear=real(row);p.blastFar=real(row);
                    p.speed=real(row);p.exposedSpeed=real(row);p.turnMin=real(row);p.turnMax=real(row);p.contactDamage=real(row);
                    require(p.spacing>=.5f&&p.spacing<=4&&p.armor>0&&p.armor<=1000&&p.blastFar>0&&p.blastFar<=p.blastNear&&p.blastNear<=1&&
                        p.speed>0&&p.speed<=10&&p.exposedSpeed>=0&&p.exposedSpeed<=3&&p.turnMin>=.1f&&p.turnMax>=p.turnMin&&p.turnMax<=30&&
                        p.contactDamage>0&&p.contactDamage<=1000,"Invalid segmented boss dimensions or damage");
                    require(lib->segmentedBosses_.emplace(id,p).second,"Duplicate segmented boss");
                } else if(command=="boss_chain_attacks") {
                    require(!item&&!rule&&!graph&&!death,"boss_chain_attacks inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->segmentedBosses_.find(id);
                    require(it!=lib->segmentedBosses_.end()&&!it->second.attacksConfigured,"Chain attacks require one preceding controller");
                    auto &p=it->second;p.armoredChild=parseMonsterId(word(row));p.exposedChild=parseMonsterId(word(row));
                    p.headInterval=real(row);p.childLimit=integer(row,1,32);p.burstMaximum=integer(row,1,8);
                    p.bodyInterval=real(row);p.bodyShots=integer(row,1,32);p.shotSpeed=real(row);p.shotDamage=real(row);
                    require(p.headInterval>=.25f&&p.headInterval<=60&&p.bodyInterval>=.25f&&p.bodyInterval<=60&&
                        p.shotSpeed>0&&p.shotSpeed<=50&&p.shotDamage>0&&p.shotDamage<=1000,"Invalid chain attacks");p.attacksConfigured=true;
                } else if(command=="boss_shell") {
                    require(!item&&!rule&&!graph&&!death,"boss_shell inside definition");
                    const auto id=parseMonsterId(word(row));SegmentedBossDefinition p;ShellBossDefinition shell;
                    p.chains=integer(row,1,4);p.segments=integer(row,3,16);p.splitMinimum=integer(row,3,8);
                    p.supplier=parseMonsterId(word(row));p.suppliers=integer(row,1,2);
                    p.spacing=real(row);p.armor=real(row);p.speed=real(row);
                    shell.exposedSlowdown=real(row);shell.steerRange=real(row);shell.turnRate=real(row);
                    shell.fleshSpeed=real(row);shell.settleSpeed=real(row);p.contactDamage=real(row);
                    p.blastNear=p.blastFar=1;
                    require(p.spacing>=.5f&&p.spacing<=4&&p.armor>0&&p.armor<=1000&&p.speed>0&&p.speed<=10&&
                        shell.exposedSlowdown>=0&&shell.exposedSlowdown<1&&shell.steerRange>0&&shell.steerRange<=30&&
                        shell.turnRate>=0&&shell.turnRate<=2&&shell.fleshSpeed>0&&shell.fleshSpeed<=p.speed&&
                        shell.settleSpeed>0&&shell.settleSpeed<=20&&p.contactDamage>0&&p.contactDamage<=1000,
                        "Invalid Shell motion, armor or dimensions");
                    require(lib->segmentedBosses_.emplace(id,p).second&&lib->shells_.emplace(id,shell).second,"Duplicate segmented boss");
                } else if(command=="boss_shell_attacks") {
                    require(!item&&!rule&&!graph&&!death,"boss_shell_attacks inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->segmentedBosses_.find(id);auto shell=lib->shells_.find(id);
                    require(it!=lib->segmentedBosses_.end()&&shell!=lib->shells_.end()&&!it->second.attacksConfigured,"Shell attacks require one preceding Shell controller");
                    auto &p=it->second;p.exposedChild=parseMonsterId(word(row));p.headInterval=real(row);p.childLimit=integer(row,1,32);
                    p.bodyInterval=real(row);p.shotSpeed=real(row);shell->second.shotSpread=real(row);p.shotDamage=real(row);p.bodyShots=3;
                    require(p.headInterval>=.25f&&p.headInterval<=60&&p.bodyInterval>=.25f&&p.bodyInterval<=60&&
                        p.shotSpeed>0&&p.shotSpeed<=50&&shell->second.shotSpread>=0&&shell->second.shotSpread<=1&&p.shotDamage>0&&p.shotDamage<=1000,
                        "Invalid Shell attacks");p.attacksConfigured=true;
                } else if(command=="enemy_bomb") {
                    require(!item&&!rule&&!graph&&!death,"enemy_bomb inside definition");
                    const auto key=word(row);EnemyBombDefinition p;p.ordnance=parseMonsterId(word(row));
                    p.payload=named<EnemyBombPayload>(word(row),{{"blast",EnemyBombPayload::Blast},{"hot",EnemyBombPayload::Hot},
                        {"sad",EnemyBombPayload::Sad},{"brimstone",EnemyBombPayload::Brimstone}});
                    p.fuse=real(row);p.radius=real(row);p.damage=real(row);p.playerDamage=real(row);
                    p.flight=real(row);p.range=real(row);p.harmsSource=flag(row);
                    require(!key.empty()&&key.size()<=64&&lib->enemyBombs_.size()<128&&p.ordnance.type==4&&p.ordnance.subtype==0&&
                        (p.ordnance.variant==0||p.ordnance.variant==3||p.ordnance.variant==7||p.ordnance.variant==8||p.ordnance.variant==15||p.ordnance.variant==16)&&
                        p.fuse>=Tick&&p.fuse<=30&&p.radius>0&&p.radius<=12&&p.damage>0&&p.damage<=1000&&
                        p.playerDamage>0&&p.playerDamage<=1000&&p.flight>=Tick&&p.flight<=5&&p.range>0&&p.range<=40,
                        "Invalid enemy bomb profile");
                    require(lib->enemyBombs_.emplace(key,p).second,"Duplicate enemy bomb profile");
                } else if(command=="enemy_bomb_fuse_jitter") {
                    require(!item&&!rule&&!graph&&!death,"Bomb fuse jitter inside definition");
                    const auto key=word(row);auto it=lib->enemyBombs_.find(key);
                    require(it!=lib->enemyBombs_.end()&&!it->second.fuseJitterFrames,"Fuse jitter requires one preceding bomb profile");
                    it->second.fuseJitterFrames=integer(row,1,300);
                } else if(command=="enemy_bomb_hot"||command=="enemy_bomb_sad"||command=="enemy_bomb_brimstone") {
                    require(!item&&!rule&&!graph&&!death,"enemy bomb effect inside definition");
                    const auto key=word(row);auto it=lib->enemyBombs_.find(key);
                    require(it!=lib->enemyBombs_.end()&&!it->second.effectConfigured,"Bomb effect needs one preceding profile");
                    auto &p=it->second;
                    if(command=="enemy_bomb_hot") {
                        p.contactDamage=real(row);p.fieldRadius=real(row);p.fieldDuration=real(row);p.fieldDamage=real(row);
                        require(p.payload==EnemyBombPayload::Hot&&p.contactDamage>0&&p.contactDamage<=1000&&p.fieldRadius>0&&p.fieldRadius<=10&&
                            p.fieldDuration>=Tick&&p.fieldDuration<=60&&p.fieldDamage>0&&p.fieldDamage<=1000,"Invalid hot bomb effect");
                    } else if(command=="enemy_bomb_sad") {
                        p.shots=integer(row,1,64);p.shotSpeed=real(row);p.shotDamage=real(row);p.shotLife=real(row);
                        require(p.payload==EnemyBombPayload::Sad&&p.shotSpeed>0&&p.shotSpeed<=50&&p.shotDamage>0&&p.shotDamage<=1000&&
                            p.shotLife>=Tick&&p.shotLife<=30,"Invalid sad bomb effect");
                    } else {
                        p.beamRange=real(row);p.beamRadius=real(row);p.beamDuration=real(row);p.beamDamage=real(row);
                        require(p.payload==EnemyBombPayload::Brimstone&&p.beamRange>0&&p.beamRange<=100&&p.beamRadius>0&&p.beamRadius<=2&&
                            p.beamDuration>=Tick&&p.beamDuration<=10&&p.beamDamage>0&&p.beamDamage<=1000,"Invalid brimstone bomb effect");
                    }
                    p.effectConfigured=true;
                } else if(command=="fly_bomb") {
                    require(!item&&!rule&&!graph&&!death,"fly_bomb inside definition");
                    const auto id=parseMonsterId(word(row));FlyBombDefinition p;p.ordnance=parseMonsterId(word(row));
                    p.circleRange=real(row);p.circleStrength=real(row);p.turnRate=real(row);
                    p.fuse=real(row);p.radius=real(row);p.contactDamage=real(row);p.contactPlayerDamage=real(row);
                    p.deathDamage=real(row);p.deathPlayerDamage=real(row);
                    require(p.ordnance==monsterId(4,14)&&p.circleRange>0&&p.circleRange<=30&&p.circleStrength>=0&&p.circleStrength<=3&&
                        p.turnRate>0&&p.turnRate<=30&&p.fuse>=Tick&&p.fuse<=10&&p.radius>0&&p.radius<=10&&
                        p.contactDamage>0&&p.contactDamage<=1000&&p.contactPlayerDamage>0&&p.contactPlayerDamage<=1000&&
                        p.deathDamage>0&&p.deathDamage<=1000&&p.deathPlayerDamage>0&&p.deathPlayerDamage<=1000,"Invalid fly bomb values");
                    require(lib->flyBombs_.emplace(id,p).second,"Duplicate fly bomb controller");
                } else if(command=="fly_bomb_follow") {
                    require(!item&&!rule&&!graph&&!death,"fly_bomb_follow inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->flyBombs_.find(id);
                    require(it!=lib->flyBombs_.end()&&!it->second.followConfigured,"Fly bomb follow requires one preceding controller");
                    auto &p=it->second;p.followScale=real(row);p.followRange=real(row);p.followRadius=real(row);
                    p.followWobble=real(row);p.followFrequency=real(row);p.followClamp=real(row);
                    p.followRadial=real(row);p.followTangent=real(row);p.followPursuit=real(row);
                    p.followDeadzone=real(row);p.followGain=real(row);p.followForce=real(row);p.followRetention=real(row);
                    p.followJitter=real(row);p.followJitterRetention=real(row);p.followSpeedCap=real(row);
                    require(id==monsterId(819)&&!p.orbitOwner&&p.followScale>0&&p.followScale<=1&&
                        p.followRange>0&&p.followRange<=1000&&p.followRadius>0&&p.followRadius<p.followRange&&
                        p.followWobble>=0&&p.followWobble<p.followRadius&&p.followFrequency>0&&p.followFrequency<=1&&
                        p.followClamp>0&&p.followClamp<=50&&p.followRadial>0&&p.followRadial<=5&&
                        p.followTangent>=0&&p.followTangent<=2&&p.followPursuit>=0&&p.followPursuit<=1&&
                        p.followDeadzone>=0&&p.followDeadzone<=100&&p.followGain>0&&p.followGain<=1&&
                        p.followForce>0&&p.followForce<=10&&p.followRetention>0&&p.followRetention<1&&
                        p.followJitter>=0&&p.followJitter<=3&&p.followJitterRetention>=0&&p.followJitterRetention<1&&
                        p.followSpeedCap>0&&p.followSpeedCap<=50,"Invalid fly bomb follow values");
                    p.followConfigured=true;
                } else if(command=="fly_bomb_orbit") {
                    require(!item&&!rule&&!graph&&!death,"fly_bomb_orbit inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->flyBombs_.find(id);
                    require(it!=lib->flyBombs_.end()&&!it->second.orbitOwner,"Fly bomb orbit requires one preceding controller");
                    auto &p=it->second;p.orbitOwner=parseMonsterId(word(row));p.orbitCount=integer(row,1,16);
                    p.orbitRadius=real(row);p.orbitSpeed=real(row);
                    require(p.orbitRadius>0&&p.orbitRadius<=8&&std::abs(p.orbitSpeed)>0&&std::abs(p.orbitSpeed)<=8,"Invalid fly bomb orbit");
                } else if(command=="lob_walker") {
                    require(!item&&!rule&&!graph&&!death,"lob_walker inside definition");
                    const auto id=parseMonsterId(word(row));LobWalkerDefinition p;
                    p.chance=integer(row,1,10000);p.range=real(row);
                    p.attackFrames=integer(row,0,300);p.shootFrame=integer(row,0,300);
                    p.initialMin=integer(row,0,600);p.initialMax=integer(row,p.initialMin,600);
                    p.repeatMin=integer(row,1,600);p.repeatMax=integer(row,p.repeatMin,600);
                    p.movementRetention=real(row);p.wanderMin=real(row);p.wanderMax=real(row);
                    require(p.range>0&&p.range<=100&&p.movementRetention>0&&p.movementRetention<1&&
                        p.wanderMin>=Tick&&p.wanderMax>=p.wanderMin&&p.wanderMax<=30&&
                        (p.attackFrames? p.shootFrame>0&&p.shootFrame<p.attackFrames:p.shootFrame==0),"Invalid lob walker cadence");
                    require(lib->lobWalkers_.emplace(id,p).second,"Duplicate lob walker");
                } else if(command=="lob_projectile") {
                    require(!item&&!rule&&!graph&&!death,"lob_projectile inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->lobWalkers_.find(id);
                    require(it!=lib->lobWalkers_.end()&&!it->second.flightConfigured,"Lob flight requires one preceding controller");
                    auto &p=it->second;
                    p.speed=real(row);p.jitter=real(row);p.upMin=real(row);p.upMax=real(row);
                    p.gravity=real(row);p.flightRetention=real(row);p.height=real(row);p.radius=real(row);
                    p.blastDamage=real(row);p.playerDamage=real(row);p.blastRadius=real(row);
                    require(p.speed>0&&p.speed<=100&&p.jitter>=0&&p.jitter<=p.speed&&
                        p.upMin>0&&p.upMax>=p.upMin&&p.upMax<=100&&p.gravity>0&&p.gravity<=200&&
                        p.flightRetention>0&&p.flightRetention<1&&p.radius>0&&p.radius<=2&&p.height>p.radius&&p.height<=10&&
                        p.blastDamage>0&&p.blastDamage<=3200&&p.playerDamage>0&&p.playerDamage<=1000&&p.blastRadius>0&&p.blastRadius<=15,
                        "Invalid lob projectile values");p.flightConfigured=true;
                } else if(command=="lob_fire_wave") {
                    require(!item&&!rule&&!graph&&!death,"lob_fire_wave inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->lobWalkers_.find(id);
                    require(it!=lib->lobWalkers_.end()&&!it->second.fireWave.jetStepFrames,"Lob fire wave requires one preceding controller");
                    auto &w=it->second.fireWave;
                    w.jetStepFrames=integer(row,1,30);w.jetSpacing=real(row);w.jetCount=integer(row,1,64);
                    w.jetLifeFrames=integer(row,3,300);w.jetPulseA=integer(row,1,w.jetLifeFrames-2);w.jetPulseB=integer(row,w.jetPulseA+1,w.jetLifeFrames-1);
                    w.radius=real(row);w.jetMonsterDamage=real(row);w.damage=real(row);w.jetScaleLoss=real(row);
                    require(w.jetSpacing>0&&w.jetSpacing<=10&&w.radius>0&&w.radius<=5&&w.jetMonsterDamage>0&&w.jetMonsterDamage<=1000&&
                        w.damage>0&&w.damage<=1000&&w.jetScaleLoss>=0&&w.jetScaleLoss*float(w.jetCount)<1,"Invalid discrete fire wave values");
                    w.speed=w.jetSpacing*30/float(w.jetStepFrames);w.range=w.jetSpacing*float(w.jetCount);w.trailDuration=float(w.jetLifeFrames)/30;
                } else if(command=="buzz_fly") {
                    require(!item&&!rule&&!graph&&!death,"buzz_fly inside definition");
                    const auto id=parseMonsterId(word(row));BuzzFlyDefinition p;
                    p.scale=real(row);p.pursuitChance=integer(row,1,10000);p.pursuit=real(row);
                    p.jitter=real(row);p.jitterRetention=real(row);p.retention=real(row);
                    p.edge=real(row);p.edgeMargin=real(row);p.speedCap=real(row);
                    require(p.scale>0&&p.scale<=1&&p.pursuit>=0&&p.pursuit<=5&&p.jitter>=0&&p.jitter<=5&&
                        p.jitterRetention>=0&&p.jitterRetention<1&&p.retention>0&&p.retention<1&&
                        p.edge>=0&&p.edge<=1&&p.edgeMargin>=0&&p.edgeMargin<=10&&p.speedCap>0&&p.speedCap<=50,
                        "Invalid buzzing fly forces");
                    require(lib->buzzFlies_.emplace(id,p).second,"Duplicate buzzing fly");
                } else if(command=="swimmer") {
                    require(!item&&!rule&&!graph&&!death,"swimmer inside definition");
                    const auto id=parseMonsterId(word(row));SwimmerDefinition p;
                    p.scale=real(row);p.acceleration=real(row);p.maximumAcceleration=real(row);p.retention=real(row);p.speedCap=real(row);
                    p.groundRetention=real(row);p.hopChance=integer(row,1,300);p.hopMinimum=real(row);p.hopMaximum=real(row);
                    p.hopFrames=integer(row,2,300);p.landFrame=integer(row,1,p.hopFrames-1);p.hopHeight=real(row);p.contactDamage=real(row);
                    p.bounce=real(row);p.marginX=real(row);p.marginTop=real(row);p.marginBottom=real(row);
                    require(p.scale>0&&p.scale<=1&&p.acceleration>0&&p.maximumAcceleration>=p.acceleration&&p.maximumAcceleration<=5&&
                        p.retention>0&&p.retention<1&&p.speedCap>0&&p.speedCap<=30&&p.groundRetention>0&&p.groundRetention<1&&
                        p.hopMinimum>0&&p.hopMaximum>=p.hopMinimum&&p.hopMaximum<=20&&p.hopHeight>=0&&p.hopHeight<=2&&
                        p.contactDamage>0&&p.contactDamage<=1000&&p.bounce<0&&p.bounce>=-1&&p.marginX>=0&&p.marginX<=50&&
                        p.marginTop>=0&&p.marginTop<=50&&p.marginBottom>=0&&p.marginBottom<=50,"Invalid swimmer profile");
                    require(lib->swimmers_.emplace(id,p).second,"Duplicate swimmer");
                } else if(command=="long_legs") {
                    require(!item&&!rule&&!graph&&!death,"long_legs inside definition");
                    const auto id=parseMonsterId(word(row));LongLegsDefinition p;
                    p.flee=integer(row,0,1);p.scale=real(row);p.pathForce=real(row);p.retention=real(row);p.attackRetention=real(row);
                    p.chance=integer(row,1,10000);p.quietChance=integer(row,1,10000);p.populationLimit=integer(row,1,256);
                    p.attackFrames=integer(row,2,300);p.eventFrame=integer(row,1,p.attackFrames-1);
                    p.child=parseMonsterId(word(row));p.twinChance=integer(row,0,10000);p.shots=integer(row,0,8);
                    p.shotMinimum=real(row);p.shotMaximum=real(row);p.shotHeight=real(row);p.shotUp=real(row);p.shotJitter=real(row);p.shotGravity=real(row);
                    p.contactDamage=real(row);p.creepRadius=real(row);p.creepDuration=real(row);
                    require(p.scale>0&&p.scale<=1&&p.pathForce>0&&p.pathForce<=5&&p.retention>0&&p.retention<1&&
                        p.attackRetention>0&&p.attackRetention<1&&p.shotMinimum>0&&p.shotMaximum>=p.shotMinimum&&p.shotMaximum<=30&&
                        p.shotHeight>0&&p.shotHeight<=5&&p.shotJitter>=0&&p.shotJitter<=2&&p.shotUp>0&&p.shotUp<=40&&
                        p.shotGravity>0&&p.shotGravity<=200&&p.contactDamage>0&&p.contactDamage<=1000&&
                        p.creepRadius>0&&p.creepRadius<=8&&p.creepDuration>0&&p.creepDuration<=30,"Invalid Long Legs profile");
                    require((p.flee&&p.child&&p.shots==0)||(!p.flee&&!p.child&&(p.shots==4||p.shots==8)&&!p.twinChance),"Invalid Long Legs attack kind");
                    require(lib->longLegs_.emplace(id,p).second,"Duplicate Long Legs profile");
                } else if(command=="sack") {
                    require(!item&&!rule&&!graph&&!death,"sack inside definition");
                    const auto id=parseMonsterId(word(row));auto p=readSackCycle(row);
                    require(lib->sacks_.emplace(id,p).second,"Duplicate Sack profile");
                } else if(command=="boil") {
                    require(!item&&!rule&&!graph&&!death,"boil inside definition");
                    const auto id=parseMonsterId(word(row));BoilDefinition p;p.walking=flag(row);
                    p.payload=named<BoilPayload>(word(row),{{"blood",BoilPayload::Blood},{"ipecac",BoilPayload::Ipecac},{"spider",BoilPayload::Spider}});
                    p.cycle=readSackCycle(row);
                    p.scale=real(row);p.retention=real(row);p.force=real(row);p.wanderDistance=real(row);p.arrival=real(row);
                    p.contactDamage=real(row);p.throwHeight=real(row);
                    require(p.scale>0&&p.scale<=1&&p.retention>0&&p.retention<1&&p.force>=0&&p.force<=5&&
                        p.wanderDistance>p.arrival&&p.wanderDistance<=1000&&p.arrival>0&&
                        p.contactDamage>=0&&p.contactDamage<=1000&&p.throwHeight<0&&p.throwHeight>=-100,
                        "Invalid Boil motion");
                    require(lib->boils_.emplace(id,p).second,"Duplicate Boil profile");
                } else if(command=="boil_projectiles") {
                    const auto id=parseMonsterId(word(row));auto it=lib->boils_.find(id);
                    require(!item&&!rule&&!graph&&!death&&it!=lib->boils_.end(),"boil_projectiles needs preceding Boil profile");
                    auto &p=it->second;
                    require(p.payload!=BoilPayload::Spider&&!p.projectilesConfigured,"Duplicate or incompatible Boil projectile profile");
                    p.projectilesConfigured=true;
                    p.shotMinimum=integer(row,1,16);p.shotMaximum=integer(row,p.shotMinimum,16);
                    p.shotSpeed=real(row);p.shotScatter=real(row);p.shotHeight=real(row);p.upMin=real(row);p.upMax=real(row);p.gravity=real(row);
                    p.aimedMultiplierMin=real(row);p.aimedMultiplierMax=real(row);p.shotRadius=real(row);
                    p.blastRadius=real(row);p.blastDamage=real(row);p.playerDamage=real(row);
                    require(p.shotSpeed>0&&p.shotSpeed<=100&&p.shotScatter>=0&&p.shotScatter<p.shotSpeed&&
                        p.shotHeight>0&&p.shotHeight<=10&&p.upMin>0&&p.upMax>=p.upMin&&p.upMax<=100&&p.gravity>0&&p.gravity<=200&&
                        p.aimedMultiplierMin>0&&p.aimedMultiplierMax>=p.aimedMultiplierMin&&p.aimedMultiplierMax<=5&&
                        p.shotRadius>0&&p.shotRadius<=1&&p.blastRadius>=0&&p.blastRadius<=20&&p.blastDamage>=0&&p.blastDamage<=1000&&
                        p.playerDamage>0&&p.playerDamage<=1000,"Invalid Boil projectile values");
                } else if(command=="strider") {
                    require(!item&&!rule&&!graph&&!death,"strider inside definition");
                    const auto id=parseMonsterId(word(row));StriderDefinition p;
                    p.scale=real(row);p.retention=real(row);p.forceMinimum=real(row);p.forceMaximum=real(row);
                    p.checkChance=integer(row,1,10000);p.chaseChance=integer(row,1,10000);p.wanderChance=integer(row,1,10000);
                    p.strokeFrames=integer(row,2,300);p.rowFrame=integer(row,1,p.strokeFrames-1);
                    p.turn=real(row);p.hover=real(row);p.contactDamage=real(row);
                    require(p.scale>0&&p.scale<=1&&p.retention>0&&p.retention<1&&p.forceMinimum>0&&
                        p.forceMaximum>=p.forceMinimum&&p.forceMaximum<=30&&p.turn>0&&p.turn<=1&&
                        p.hover>=0&&p.hover<=2&&p.contactDamage>0&&p.contactDamage<=1000,"Invalid Strider profile");
                    require(lib->striders_.emplace(id,p).second,"Duplicate Strider profile");
                } else if(command=="swarm_spider") {
                    require(!item&&!rule&&!graph&&!death,"swarm_spider inside definition");
                    const auto id=parseMonsterId(word(row));SwarmSpiderDefinition p;
                    p.scale=real(row);p.retention=real(row);p.nearRange=real(row);p.farRange=real(row);
                    p.turnChance=integer(row,1,10000);p.farTurnChance=integer(row,1,10000);p.earlyChance=integer(row,1,10000);
                    p.height=real(row);p.contactDamage=real(row);p.playerObjectsOnly=integer(row,0,1);
                    for(auto &weights:p.weights) {
                        int total=0;for(auto &weight:weights){weight=integer(row,0,1000);total+=weight;}
                        require(total>0,"Swarm hop weights need a positive total");
                    }
                    for(auto &hop:p.hops) {
                        hop.frames=integer(row,3,300);hop.jump=integer(row,1,hop.frames-2);hop.land=integer(row,hop.jump+1,hop.frames-1);
                        hop.minimum=real(row);hop.maximum=real(row);hop.spread=real(row);
                        require(hop.minimum>0&&hop.maximum>=hop.minimum&&hop.maximum<=30&&hop.spread>=0&&hop.spread<=180,"Invalid swarm hop");
                    }
                    require(p.scale>0&&p.scale<=1&&p.retention>0&&p.retention<1&&p.nearRange>0&&
                        p.farRange>p.nearRange&&p.farRange<=1000&&p.height>=0&&p.height<=2&&
                        p.contactDamage>0&&p.contactDamage<=1000,"Invalid Swarm Spider profile");
                    require(lib->swarmSpiders_.emplace(id,p).second,"Duplicate Swarm Spider profile");
                } else if(command=="gaper") {
                    require(!item&&!rule&&!graph&&!death,"gaper inside definition");
                    const auto id=parseMonsterId(word(row));GaperDefinition p;
                    p.frowning=integer(row,0,1);p.scale=real(row);p.force=real(row);p.awakeForce=real(row);
                    p.retention=real(row);p.blockedRetention=real(row);p.arrivalRetention=real(row);
                    p.distanceGain=real(row);p.maxGain=real(row);p.arrival=real(row);p.stopSpeed=real(row);p.contact=real(row);
                    p.headFrames=integer(row,p.frowning?2:1,300);p.walkFrames=integer(row,2,300);
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.awakeForce>=p.force&&p.awakeForce<=10&&
                        (p.frowning||p.force==p.awakeForce)&&p.retention>0&&p.retention<1&&
                        p.blockedRetention>0&&p.blockedRetention<=1&&p.arrivalRetention>0&&p.arrivalRetention<=1&&
                        p.distanceGain>0&&p.distanceGain<=10&&p.maxGain>0&&p.maxGain<=10&&p.arrival>0&&p.arrival<=100&&
                        p.stopSpeed>0&&p.stopSpeed<=10&&p.contact>0&&p.contact<=100,"Invalid Gaper profile");
                    require(lib->gapers_.emplace(id,p).second,"Duplicate Gaper profile");
                } else if(command=="leper") {
                    require(!item&&!rule&&!graph&&!death,"leper inside definition");
                    const auto id=parseMonsterId(word(row));LeperDefinition p;
                    static_cast<GroundPursuitDefinition&>(p)=readGroundPursuit(row);
                    p.chaseRetention=real(row);p.transitionRetention=real(row);p.damageScale=real(row);p.damageTimerGain=real(row);p.knockback=real(row);
                    p.chaseFrames=integer(row,1,1000);p.chaseChance=integer(row,1,1000);p.restMin=integer(row,1,1000);p.restMax=integer(row,p.restMin,1000);p.transitionFrames=integer(row,1,300);
                    p.flesh=parseMonsterId(word(row));p.gusher=parseMonsterId(word(row));
                    p.childOffset=real(row);p.childMin=real(row);p.childMax=real(row);p.childSpread=real(row);
                    p.deathMin=real(row);p.deathMax=real(row);p.overkill=real(row);
                    p.morphChance=integer(row,1,1000);p.gusherDelayMin=integer(row,0,1000);p.gusherDelayMax=integer(row,p.gusherDelayMin,1000);
                    p.evade.scale=p.scale;p.evade.spawns=false;
                    require(id.subtype>=0&&id.subtype<=3&&p.chaseRetention>0&&p.chaseRetention<=1&&p.transitionRetention>0&&p.transitionRetention<=1&&
                        p.damageScale>0&&p.damageScale<=100&&p.damageTimerGain>=0&&p.damageTimerGain<=100&&p.knockback>=0&&p.knockback<=100&&
                        p.childOffset>=0&&p.childOffset<=10&&p.childMin>=0&&p.childMax>=p.childMin&&p.childMax<=200&&
                        p.childSpread>=0&&p.childSpread<=180&&p.deathMin>=0&&p.deathMax>=p.deathMin&&p.deathMax<=100&&p.overkill>0&&p.overkill<=10000,
                        "Invalid Leper profile");
                    require(lib->lepers_.emplace(id,p).second,"Duplicate Leper profile");
                } else if(command=="leper_evade") {
                    require(!item&&!rule&&!graph&&!death,"leper_evade inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->lepers_.find(id);
                    require(it!=lib->lepers_.end()&&!it->second.evadeConfigured,"Missing/duplicate Leper evasion");
                    auto &p=it->second.evade;
                    p.visibleRange=real(row);p.hiddenRange=real(row);p.proximityFrames=integer(row,1,300);p.evadeChecks=integer(row,1,100);
                    p.retention=real(row);p.wanderForce=real(row);p.wanderRetention=real(row);p.pathForce=real(row);
                    require(p.visibleRange>0&&p.visibleRange<=100&&p.hiddenRange>0&&p.hiddenRange<=100&&p.retention>0&&p.retention<=1&&
                        p.wanderForce>0&&p.wanderForce<=10&&p.wanderRetention>0&&p.wanderRetention<=1&&p.pathForce>0&&p.pathForce<=10,"Invalid Leper evasion");
                    it->second.evadeConfigured=true;
                } else if(command=="leper_creep") {
                    require(!item&&!rule&&!graph&&!death,"leper_creep inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->lepers_.find(id);
                    require(it!=lib->lepers_.end()&&!it->second.creepConfigured,"Missing/duplicate Leper creep");
                    auto &p=it->second;p.trailPeriod=integer(row,1,300);p.creepMin=real(row);p.creepMax=real(row);p.creepDamage=real(row);
                    p.creepFrames=integer(row,1,1000);p.fadeFrames=integer(row,1,300);p.fadeScale=real(row);
                    require(p.creepMin>0&&p.creepMax>=p.creepMin&&p.creepMax<=10&&p.creepDamage>0&&p.creepDamage<=100&&p.fadeScale>0&&p.fadeScale<=1,"Invalid Leper creep");
                    p.creepConfigured=true;
                } else if(command=="leper_flesh") {
                    require(!item&&!rule&&!graph&&!death,"leper_flesh inside definition");
                    const auto id=parseMonsterId(word(row));LeperFleshDefinition p;
                    p.scale=real(row);p.retention=real(row);p.force=real(row);p.randomWeight=real(row);p.contact=real(row);
                    p.idleFrames=integer(row,1,300);p.trailPeriod=integer(row,1,300);p.particlePeriod=integer(row,1,300);
                    p.trailMin=real(row);p.trailMax=real(row);p.trailLife=real(row);
                    p.prediction=real(row);p.shotSpeed=real(row);p.shotUp=real(row);p.gravity=real(row);
                    p.shotHeight=real(row);p.shotRadius=real(row);p.shotDamage=real(row);p.shotLife=real(row);p.shotRetention=real(row);
                    require(p.scale>0&&p.scale<=1&&p.retention>0&&p.retention<1&&p.force>0&&p.force<=10&&
                        p.randomWeight>=0&&p.randomWeight<=10&&p.contact>0&&p.contact<=100&&p.trailMin>0&&
                        p.trailMax>=p.trailMin&&p.trailMax<=5&&p.trailLife>0&&p.trailLife<=30&&
                        p.prediction>=0&&p.prediction<=1&&p.shotSpeed>0&&p.shotSpeed<=200&&p.shotUp>=0&&p.shotUp<=100&&
                        p.gravity>0&&p.gravity<=200&&p.shotHeight>0&&p.shotHeight<=10&&p.shotRadius>0&&p.shotRadius<=2&&
                        p.shotDamage>0&&p.shotDamage<=100&&p.shotLife>0&&p.shotLife<=30&&p.shotRetention>0&&p.shotRetention<=1,
                        "Invalid Leper Flesh profile");
                    require(lib->leperFlesh_.emplace(id,p).second,"Duplicate Leper Flesh profile");
                } else if(command=="black_globin") {
                    require(!item&&!rule&&!graph&&!death,"black_globin inside definition");
                    const auto id=parseMonsterId(word(row));BlackGlobinDefinition p;
                    static_cast<GroundPursuitDefinition&>(p)=readGroundPursuit(row);
                    p.damageThreshold=real(row);p.targetFraction=real(row);p.throwHeight=real(row);p.headRadius=real(row);
                    p.spider=parseMonsterId(word(row));p.head=parseMonsterId(word(row));p.body=parseMonsterId(word(row));
                    require(p.damageThreshold>0&&p.damageThreshold<=1000&&p.targetFraction>0&&p.targetFraction<=1&&
                        p.throwHeight<=0&&p.throwHeight>=-100&&p.headRadius>0&&p.headRadius<=10,"Invalid Black Globin brood");
                    require(lib->blackGlobins_.emplace(id,p).second,"Duplicate Black Globin profile");
                } else if(command=="rotten_gaper") {
                    require(!item&&!rule&&!graph&&!death,"rotten_gaper inside definition");
                    const auto id=parseMonsterId(word(row));RottenGaperDefinition p;
                    p.scale=real(row);p.force=real(row);p.retention=real(row);p.blockedRetention=real(row);p.arrivalRetention=real(row);
                    p.distanceGain=real(row);p.maxGain=real(row);p.arrival=real(row);p.stopSpeed=real(row);p.contact=real(row);
                    p.walkFrames=integer(row,2,300);
                    require(id.type==10&&id.variant==3&&id.subtype>=0&&id.subtype<=5&&
                        p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.retention>0&&p.retention<1&&
                        p.blockedRetention>0&&p.blockedRetention<=1&&p.arrivalRetention>0&&p.arrivalRetention<=1&&
                        p.distanceGain>0&&p.distanceGain<=10&&p.maxGain>0&&p.maxGain<=10&&p.arrival>0&&p.arrival<=100&&
                        p.stopSpeed>0&&p.stopSpeed<=10&&p.contact>0&&p.contact<=100,"Invalid Rotten Gaper profile");
                    require(lib->rottenGapers_.emplace(id,p).second,"Duplicate Rotten Gaper profile");
                } else if(command=="rotten_brood") {
                    require(!item&&!rule&&!graph&&!death,"rotten_brood inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->rottenGapers_.find(id);
                    require(it!=lib->rottenGapers_.end()&&id.subtype==3&&!it->second.brood,"Invalid or duplicate Rotten brood profile");
                    auto &p=it->second;p.brood=true;p.child=parseMonsterId(word(row));
                    p.spawnDelay=integer(row,1,3000);p.spawnChance=integer(row,1,10000);p.childLimit=integer(row,1,64);
                    p.playerRange=real(row);p.peerRange=real(row);p.rememberMin=integer(row,1,300);p.rememberMax=integer(row,p.rememberMin,300);
                    p.evadeRetention=real(row);p.evadeForce=real(row);
                    require(p.playerRange>0&&p.playerRange<=1000&&p.peerRange>0&&p.peerRange<=1000&&
                        p.evadeRetention>0&&p.evadeRetention<1&&p.evadeForce>0&&p.evadeForce<=10,"Invalid Rotten brood movement");
                } else if(command=="rotten_orbit") {
                    require(!item&&!rule&&!graph&&!death,"rotten_orbit inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->rottenGapers_.find(id);
                    require(it!=lib->rottenGapers_.end()&&id.subtype==5&&!it->second.orbit,"Invalid or duplicate Rotten orbit profile");
                    auto &p=it->second;p.orbit=true;
                    p.orbitRadius=real(row);p.orbitNear=real(row);p.orbitSpan=real(row);p.orbitMinimum=real(row);p.orbitGain=real(row);
                    p.orbitRetention=real(row);p.orbitTurn=real(row);
                    require(p.orbitRadius>0&&p.orbitRadius<=1000&&p.orbitNear>=0&&p.orbitNear<=1000&&p.orbitSpan>0&&p.orbitSpan<=1000&&
                        p.orbitMinimum>0&&p.orbitGain>=0&&p.orbitMinimum+p.orbitGain<=2&&p.orbitRetention>0&&p.orbitRetention<1&&
                        p.orbitTurn>=0&&p.orbitTurn<=180,"Invalid Rotten orbit movement");
                } else if(command=="small_maggot") {
                    require(!item&&!rule&&!graph&&!death,"small_maggot inside definition");
                    const auto id=parseMonsterId(word(row));SmallMaggotDefinition p;
                    p.scale=real(row);p.retention=real(row);p.forceMin=real(row);p.forceMax=real(row);p.targetMultiplier=real(row);
                    p.curveDegrees=real(row);p.lookahead=real(row);p.obstacleTurnDegrees=real(row);p.alertRange=real(row);p.contact=real(row);
                    p.initialMin=integer(row,1,300);p.initialMax=integer(row,p.initialMin,300);
                    p.turnMin=integer(row,1,300);p.turnMax=integer(row,p.turnMin,300);
                    p.alertInterval=integer(row,1,300);p.alertChance=integer(row,1,10000);p.forgetChance=integer(row,1,10000);
                    p.obstacleAttempts=integer(row,1,100);p.walkFrames=integer(row,2,300);
                    require(p.scale>0&&p.scale<=1&&p.retention>0&&p.retention<1&&p.forceMin>0&&p.forceMax>=p.forceMin&&p.forceMax<=10&&
                        p.targetMultiplier>=1&&p.targetMultiplier<=10&&p.curveDegrees>=0&&p.curveDegrees<=90&&
                        p.lookahead>0&&p.lookahead<=100&&p.obstacleTurnDegrees>0&&p.obstacleTurnDegrees<=180&&
                        p.alertRange>0&&p.alertRange<=1000&&p.contact>0&&p.contact<=100,"Invalid Small Maggot profile");
                    require(lib->smallMaggots_.emplace(id,p).second,"Duplicate Small Maggot profile");
                } else if(command=="headless") {
                    require(!item&&!rule&&!graph&&!death,"headless inside definition");
                    const auto id=parseMonsterId(word(row));HeadlessDefinition p;
                    p.shooter=integer(row,0,1);p.scale=real(row);p.force=real(row);p.retention=real(row);
                    p.wanderDistance=real(row);p.arrival=real(row);p.stuckSpeedSquared=real(row);p.stuckChance=integer(row,1,10000);p.contact=real(row);
                    p.initialMin=integer(row,0,3600);p.initialMax=integer(row,p.initialMin,3600);
                    p.reloadMin=integer(row,1,3600);p.reloadMax=integer(row,p.reloadMin,3600);p.trailPeriod=integer(row,1,3600);
                    p.trailMin=real(row);p.trailMax=real(row);p.trailLife=real(row);
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.retention>0&&p.retention<1&&
                        p.wanderDistance>0&&p.wanderDistance<=1000&&p.arrival>0&&p.arrival<p.wanderDistance&&p.stuckSpeedSquared>=0&&p.stuckSpeedSquared<=100&&
                        p.contact>0&&p.contact<=100&&p.trailMin>0&&p.trailMax>=p.trailMin&&p.trailMax<=2&&p.trailLife>0&&p.trailLife<=30,"Invalid headless profile");
                    require(lib->headless_.emplace(id,p).second,"Duplicate headless profile");
                } else if(command=="headless_brood") {
                    require(!item&&!rule&&!graph&&!death,"headless_brood inside definition");
                    const auto id=parseMonsterId(word(row));require(lib->headless_.contains(id),"Headless brood requires profile");
                    auto &p=lib->headless_.at(id);require(!p.shooter&&!p.broodChild,"Duplicate or shooter headless brood");
                    p.broodChild=parseMonsterId(word(row));p.broodLimit=integer(row,1,100);
                    p.broodShort=integer(row,1,3600);p.broodLong=integer(row,p.broodShort,3600);
                    p.broodRadius=real(row);p.broodHeight=real(row);
                    require(p.broodRadius>0&&p.broodRadius<=30&&p.broodHeight<=0&&p.broodHeight>=-100,"Invalid headless brood launch");
                } else if(command=="headless_shot") {
                    require(!item&&!rule&&!graph&&!death,"headless_shot inside definition");
                    const auto id=parseMonsterId(word(row));require(lib->headless_.contains(id),"Headless shot requires profile");auto &p=lib->headless_.at(id);
                    require(p.shooter&&!p.shotConfigured,"Duplicate or non-shooter headless shot");p.shotConfigured=true;
                    p.shotSpeed=real(row);p.shotHeight=real(row);p.shotUp=real(row);p.gravity=real(row);p.shotRetention=real(row);
                    p.shotRadius=real(row);p.shotDamage=real(row);p.shotLife=real(row);
                    require(p.shotSpeed>0&&p.shotSpeed<=300&&p.shotHeight>0&&p.shotHeight<=10&&p.shotUp>=0&&p.shotUp<=100&&p.gravity>0&&p.gravity<=100&&
                        p.shotRetention>0&&p.shotRetention<=1&&p.shotRadius>0&&p.shotRadius<=2&&p.shotDamage>0&&p.shotDamage<=1000&&p.shotLife>0&&p.shotLife<=30,"Invalid headless shot");
                } else if(command=="faceless") {
                    require(!item&&!rule&&!graph&&!death,"faceless inside definition");
                    const auto id=parseMonsterId(word(row));FacelessDefinition p;
                    p.tainted=integer(row,0,1);p.scale=real(row);p.wanderForce=real(row);p.wanderRetention=real(row);
                    p.wanderDistance=real(row);p.arrival=real(row);p.stuckSpeedSquared=real(row);p.stuckChance=integer(row,1,10000);
                    p.pathForce=real(row);p.pathRetention=real(row);p.alertRange=real(row);p.contact=real(row);
                    p.baseChance=real(row);p.damageChance=real(row);p.damageScale=real(row);p.hurtDecay=real(row);p.shotCost=real(row);
                    p.attackFrames=integer(row,2,300);p.shootFrame=integer(row,1,p.attackFrames-1);
                    p.overkill=real(row);p.morphChance=integer(row,1,10000);p.pacerChance=integer(row,1,10000);
                    p.gusher=parseMonsterId(word(row));p.pacer=parseMonsterId(word(row));
                    require(p.scale>0&&p.scale<=1&&p.wanderForce>0&&p.wanderForce<=10&&p.wanderRetention>0&&p.wanderRetention<1&&
                        p.wanderDistance>0&&p.wanderDistance<=1000&&p.arrival>0&&p.arrival<p.wanderDistance&&p.stuckSpeedSquared>=0&&p.stuckSpeedSquared<=100&&
                        p.pathForce>0&&p.pathForce<=10&&p.pathRetention>0&&p.pathRetention<1&&p.alertRange>0&&p.alertRange<=1000&&p.contact>0&&p.contact<=100&&
                        p.baseChance>=0&&p.baseChance<=1&&p.damageChance>=0&&p.damageChance<=1&&p.damageScale>0&&p.damageScale<=100&&
                        p.hurtDecay>0&&p.hurtDecay<=100&&p.shotCost>=0&&p.shotCost<=1000&&p.overkill>0&&p.overkill<=1000,"Invalid Faceless profile");
                    require(lib->faceless_.emplace(id,p).second,"Duplicate Faceless profile");
                } else if(command=="faceless_shot") {
                    require(!item&&!rule&&!graph&&!death,"faceless_shot inside definition");
                    const auto id=parseMonsterId(word(row));require(lib->faceless_.contains(id),"Faceless shot requires profile");auto &p=lib->faceless_.at(id);
                    require(!p.shotConfigured,"Duplicate Faceless shot");p.shotConfigured=true;
                    p.shots=integer(row,1,64);p.shotSpeed=real(row);p.shotHeight=real(row);p.shotUp=real(row);p.gravity=real(row);p.shotRetention=real(row);
                    p.shotRadius=real(row);p.shotDamage=real(row);p.shotLife=real(row);
                    p.trailChance=integer(row,1,1000);p.trailMin=real(row);p.trailMax=real(row);p.trailLife=real(row);
                    require(p.shotSpeed>0&&p.shotSpeed<=300&&p.shotHeight>0&&p.shotHeight<=10&&p.shotUp>=0&&p.shotUp<=100&&p.gravity>0&&p.gravity<=100&&
                        p.shotRetention>0&&p.shotRetention<=1&&p.shotRadius>0&&p.shotRadius<=2&&p.shotDamage>0&&p.shotDamage<=1000&&p.shotLife>0&&p.shotLife<=30&&
                        p.trailMin>0&&p.trailMax>=p.trailMin&&p.trailMax<=2&&p.trailLife>0&&p.trailLife<=30,"Invalid Faceless shot");
                } else if(command=="danny") {
                    require(!item&&!rule&&!graph&&!death,"danny inside definition");
                    const auto id=parseMonsterId(word(row));DannyDefinition p;
                    p.coal=integer(row,0,1);p.scale=real(row);p.pathForce=real(row);p.retention=real(row);p.attackRetention=real(row);p.contact=real(row);
                    p.initialMin=integer(row,0,3600);p.initialMax=integer(row,p.initialMin,3600);p.cooldown=integer(row,1,3600);
                    p.chance=integer(row,1,1000);p.hurtChance=integer(row,1,1000);p.farChance=integer(row,1,1000);
                    p.attackFrames=integer(row,2,300);p.shootFrame=integer(row,1,p.attackFrames-1);
                    p.roomLimit=integer(row,1,100);p.ownedLimit=integer(row,1,16);p.total=integer(row,p.ownedLimit,32);
                    p.nearRange=real(row);p.farRange=real(row);p.damageScale=real(row);p.hurtThreshold=real(row);p.hurtDecay=real(row);
                    p.child=parseMonsterId(word(row));p.coalBody=parseMonsterId(word(row));
                    require(p.scale>0&&p.scale<=1&&p.pathForce>0&&p.pathForce<=10&&p.retention>0&&p.retention<1&&
                        p.attackRetention>0&&p.attackRetention<1&&p.contact>0&&p.contact<=100&&p.nearRange>0&&p.farRange>=p.nearRange&&p.farRange<=1000&&
                        p.damageScale>0&&p.damageScale<=100&&p.hurtThreshold>0&&p.hurtThreshold<=1000&&p.hurtDecay>0&&p.hurtDecay<=100,"Invalid Danny profile");
                    require(lib->dannies_.emplace(id,p).second,"Duplicate Danny profile");
                } else if(command=="danny_payload") {
                    require(!item&&!rule&&!graph&&!death,"danny_payload inside definition");
                    const auto id=parseMonsterId(word(row));require(lib->dannies_.contains(id),"Danny payload requires profile");auto &p=lib->dannies_.at(id);
                    require(!p.payloadConfigured,"Duplicate Danny payload");p.payloadConfigured=true;
                    p.childOffset=real(row);p.childHeight=real(row);p.childSpread=real(row);p.childMin=real(row);p.childMax=real(row);p.childUpMin=real(row);p.childUpMax=real(row);
                    p.shotHeight=real(row);p.shotRadius=real(row);p.shotDamage=real(row);p.shotLife=real(row);
                    p.shotSpeed=real(row);p.scatter=real(row);p.fallMin=real(row);p.fallMax=real(row);p.gravity=real(row);p.shotRetention=real(row);
                    require(p.childOffset>=0&&p.childOffset<=100&&p.childHeight<0&&p.childHeight>=-1000&&p.childSpread>=0&&p.childSpread<=360&&
                        p.childMin>=0&&p.childMax>=p.childMin&&p.childMax<=100&&p.childUpMin<=p.childUpMax&&p.childUpMax<0&&p.childUpMin>=-100&&
                        p.shotHeight>0&&p.shotHeight<=10&&p.shotRadius>0&&p.shotRadius<=2&&p.shotDamage>0&&p.shotDamage<=1000&&p.shotLife>0&&p.shotLife<=30&&
                        p.shotSpeed>0&&p.shotSpeed<=100&&p.scatter>=0&&p.scatter<=100&&p.fallMin<=p.fallMax&&p.fallMin>=-100&&p.fallMax<=100&&p.gravity>0&&p.gravity<=100&&p.shotRetention>0&&p.shotRetention<=1,"Invalid Danny payload");
                } else if(command=="hardy") {
                    require(!item&&!rule&&!graph&&!death,"hardy inside definition");
                    const auto id=parseMonsterId(word(row));HardyDefinition p;
                    p.scale=real(row);p.retention=real(row);p.idleRetention=real(row);p.force=real(row);p.launch=real(row);
                    p.chance=integer(row,1,1000);p.checkFrames=integer(row,1,300);p.launchFrame=integer(row,1,300);
                    p.hitFrames=integer(row,1,300);p.cooldown=integer(row,0,3600);p.slowAfter=integer(row,1,300);
                    p.slowSpeed=real(row);p.stopSpeed=real(row);p.brake=real(row);p.collisionBrake=real(row);p.impactDot=real(row);
                    p.contact=real(row);p.blastMultiplier=real(row);p.child=parseMonsterId(word(row));p.childHealth=real(row);p.rock=parseMonsterId(word(row));
                    require(p.scale>0&&p.scale<=1&&p.retention>0&&p.retention<1&&p.idleRetention>0&&p.idleRetention<=1&&
                        p.force>0&&p.force<=10&&p.launch>0&&p.launch<=100&&p.slowSpeed>p.stopSpeed&&p.stopSpeed>0&&
                        p.brake>0&&p.brake<1&&p.collisionBrake>0&&p.collisionBrake<1&&p.impactDot>=0&&p.impactDot<1&&
                        p.contact>0&&p.contact<=100&&p.blastMultiplier>0&&p.blastMultiplier<=10&&p.childHealth>0&&p.childHealth<=10,"Invalid Hardy profile");
                    require(lib->hardies_.emplace(id,p).second,"Duplicate Hardy profile");
                } else if(command=="hardy_payload") {
                    require(!item&&!rule&&!graph&&!death,"hardy_payload inside definition");
                    const auto id=parseMonsterId(word(row));require(lib->hardies_.contains(id),"Hardy payload requires profile");auto &p=lib->hardies_.at(id);
                    require(!p.payloadConfigured,"Duplicate Hardy payload");p.payloadConfigured=true;
                    p.childOffset=real(row);p.childHeight=real(row);p.childSpread=real(row);p.childSpeedMin=real(row);p.childSpeedMax=real(row);p.childUpMin=real(row);p.childUpMax=real(row);
                    p.shotScale=real(row);p.shotHeight=real(row);p.shotRadius=real(row);p.shotDamage=real(row);p.shotLife=real(row);
                    p.ringSpeed=real(row);p.clusterSpeed=real(row);p.clusterScatter=real(row);p.clusterFallMin=real(row);p.clusterFallMax=real(row);p.clusterGravity=real(row);p.shotRetention=real(row);
                    require(p.childOffset>=0&&p.childOffset<=100&&p.childHeight<0&&p.childHeight>=-1000&&p.childSpread>=0&&p.childSpread<=360&&
                        p.childSpeedMin>=0&&p.childSpeedMax>=p.childSpeedMin&&p.childSpeedMax<=100&&p.childUpMin<=p.childUpMax&&p.childUpMax<0&&p.childUpMin>=-100&&
                        p.shotScale>0&&p.shotScale<=1&&p.shotHeight>0&&p.shotHeight<=10&&p.shotRadius>0&&p.shotRadius<=2&&p.shotDamage>0&&p.shotDamage<=1000&&p.shotLife>0&&p.shotLife<=30&&
                        p.ringSpeed>0&&p.ringSpeed<=100&&p.clusterSpeed>0&&p.clusterSpeed<=100&&p.clusterScatter>=0&&p.clusterScatter<=100&&p.clusterFallMin<=p.clusterFallMax&&p.clusterFallMin>=-100&&p.clusterFallMax<=100&&p.clusterGravity>0&&p.clusterGravity<=100&&p.shotRetention>0&&p.shotRetention<=1,"Invalid Hardy payload");
                } else if(command=="rock_spider") {
                    require(!item&&!rule&&!graph&&!death,"rock_spider inside definition");
                    const auto id=parseMonsterId(word(row));RockSpiderDefinition p;
                    p.scale=real(row);p.retention=real(row);p.force=real(row);
                    p.counterStep=integer(row,1,2);p.selectionStep=integer(row,1,120);p.cycle=integer(row,2,480);
                    p.chaseChance=integer(row,1,100);p.spread=real(row);p.wanderDistance=real(row);
                    p.wanderAttempts=integer(row,1,32);p.appearFrames=integer(row,1,300);p.wakeChance=integer(row,1,300);
                    p.wakeSpeed=real(row);p.gravity=real(row);p.bounce=real(row);p.landingRetention=real(row);
                    p.wakeVertical=real(row);p.gridHeight=real(row);p.entityHeight=real(row);p.contactDamage=real(row);
                    auto morph=word(row),child=word(row);if(morph!="none")p.deathMorph=parseMonsterId(morph);if(child!="none")p.deathChild=parseMonsterId(child);
                    p.decayFrames=integer(row,1,3600);p.decayChance=integer(row,2,100);p.wetDecayFrames=integer(row,1,3600);
                    require(p.scale>0&&p.scale<=1&&p.retention>=0&&p.retention<1&&p.force>=0&&p.force<=30&&
                        p.cycle%p.selectionStep==0&&p.cycle>p.selectionStep&&p.spread>=0&&p.spread<=180&&
                        p.wanderDistance>0&&p.wanderDistance<=200&&p.wakeSpeed>0&&p.wakeSpeed<=30&&
                        p.gravity>0&&p.gravity<=10&&p.bounce<=0&&p.bounce>=-1&&p.landingRetention>=0&&p.landingRetention<=1&&
                        p.wakeVertical>0&&p.wakeVertical<=10&&p.gridHeight<=0&&p.entityHeight<p.gridHeight&&p.entityHeight>=-1000&&
                        p.contactDamage>0&&p.contactDamage<=1000&&!(p.deathMorph&&p.deathChild),"Invalid Rock Spider profile");
                    require(lib->rockSpiders_.emplace(id,p).second,"Duplicate Rock Spider profile");
                } else if(command=="spider") {
                    require(!item&&!rule&&!graph&&!death,"spider inside definition");
                    const auto id=parseMonsterId(word(row));SpiderDefinition p;
                    p.scale=real(row);p.retention=real(row);p.force=real(row);
                    p.idleFrames=integer(row,1,120);p.wanderFrames=integer(row,1,120);
                    p.rangeMinimum=real(row);p.rangeMaximum=real(row);p.prediction=real(row);
                    p.wanderMinimum=real(row);p.wanderMaximum=real(row);p.arrival=real(row);p.stuckSpeed=real(row);
                    p.gapChance=integer(row,1,10000);p.contactDamage=real(row);
                    p.leftMargin=real(row);p.topMargin=real(row);p.rightMargin=real(row);p.bottomMargin=real(row);
                    require(p.scale>0&&p.scale<=1&&p.retention>0&&p.retention<1&&p.force>0&&p.force<=20&&
                        p.rangeMinimum>0&&p.rangeMaximum>=p.rangeMinimum&&p.rangeMaximum<=500&&p.prediction>=0&&p.prediction<=30&&
                        p.wanderMinimum>0&&p.wanderMaximum>=p.wanderMinimum&&p.wanderMaximum<=300&&p.arrival>0&&p.arrival<=50&&
                        p.stuckSpeed>0&&p.stuckSpeed<=20&&p.contactDamage>0&&p.contactDamage<=1000&&
                        p.leftMargin>=0&&p.leftMargin<=100&&p.topMargin>=0&&p.topMargin<=100&&
                        p.rightMargin>=0&&p.rightMargin<=100&&p.bottomMargin>=0&&p.bottomMargin<=100,"Invalid spider profile");
                    require(lib->spiders_.emplace(id,p).second,"Duplicate spider profile");
                } else if(command=="willo") {
                    require(!item&&!rule&&!graph&&!death,"willo inside definition");
                    const auto id=parseMonsterId(word(row));WilloDefinition p;
                    p.scale=real(row);p.radius=real(row);p.ellipse=real(row);p.angularStep=real(row);p.tracking=real(row);
                    p.trackingCap=real(row);p.carry=real(row);p.settleRange=real(row);p.chance=integer(row,1,10000);
                    p.attackFrames=integer(row,2,300);p.warnFrame=integer(row,1,p.attackFrames-1);p.shootFrame=integer(row,p.warnFrame+1,p.attackFrames-1);
                    p.prediction=real(row);p.speed=real(row);p.damage=real(row);p.height=real(row);p.up=real(row);p.gravity=real(row);
                    p.retention=real(row);p.projectileRadius=real(row);p.life=real(row);p.noWallCollision=integer(row,0,1);
                    require(p.scale>0&&p.scale<=1&&p.radius>0&&p.radius<=300&&p.ellipse>0&&p.ellipse<=1&&
                        p.angularStep>0&&p.angularStep<=1&&p.tracking>0&&p.tracking<=1&&p.trackingCap>0&&p.trackingCap<=30&&
                        p.carry>=0&&p.carry<=4&&p.settleRange>0&&p.settleRange<=100&&p.prediction>=0&&p.prediction<=30&&
                        p.speed>0&&p.speed<=100&&p.damage>0&&p.damage<=1000&&p.height>0&&p.height<=5&&p.up>=-30&&p.up<=30&&
                        p.gravity>0&&p.gravity<=100&&p.retention>0&&p.retention<1&&p.projectileRadius>0&&p.projectileRadius<=1&&
                        p.life>0&&p.life<=20,"Invalid Willo profile");
                    require(lib->willos_.emplace(id,p).second,"Duplicate Willo profile");
                } else if(command=="evader_hover") {
                    require(!item&&!rule&&!graph&&!death,"evader_hover inside definition");
                    const auto id=parseMonsterId(word(row));const auto it=lib->evaders_.find(id);
                    require(it!=lib->evaders_.end()&&it->second.hoverHeight==0,"Hover requires one preceding evader profile");
                    it->second.hoverHeight=real(row);require(it->second.hoverHeight>0&&it->second.hoverHeight<=2,"Invalid evader hover height");
                } else if(command=="evader"||command=="evader_body") {
                    require(!item&&!rule&&!graph&&!death,"evader inside definition");
                    const auto id=parseMonsterId(word(row));EvaderDefinition p;
                    p.scale=real(row);p.visibleRange=real(row);p.hiddenRange=real(row);
                    p.proximityFrames=integer(row,1,120);p.evadeChecks=integer(row,1,30);
                    p.retention=real(row);p.wanderForce=real(row);p.wanderRetention=real(row);p.pathForce=real(row);
                    p.spawns=command=="evader";
                    if(p.spawns) {
                    p.attackRange=real(row);p.attackFrames=integer(row,2,300);p.shootFrame=integer(row,1,p.attackFrames-1);
                    p.cooldownFrames=integer(row,p.attackFrames,600);p.populationMinimum=integer(row,1,64);
                    p.populationMaximum=integer(row,p.populationMinimum,64);p.crowdDelayMinimum=integer(row,1,600);
                    p.crowdDelayMaximum=integer(row,p.crowdDelayMinimum,600);p.child=parseMonsterId(word(row));p.childHealth=real(row);
                    }
                    require(p.scale>0&&p.scale<=1&&p.visibleRange>0&&p.visibleRange<=100&&p.hiddenRange>0&&p.hiddenRange<=p.visibleRange&&
                        p.retention>0&&p.retention<=1&&p.wanderForce>=0&&p.wanderForce<=5&&p.wanderRetention>0&&p.wanderRetention<=1&&
                        p.pathForce>=0&&p.pathForce<=5&&p.attackRange>0&&p.attackRange<=100&&p.childHealth>0&&p.childHealth<=1,
                        "Invalid evader profile");
                    require(lib->evaders_.emplace(id,p).second,"Duplicate evader");
                } else if(command=="evader_cooldown_bonus"||command=="evader_child_contact_death") {
                    require(!item&&!rule&&!graph&&!death,"Evader extension inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->evaders_.find(id);
                    require(it!=lib->evaders_.end()&&it->second.spawns,"Extension requires a preceding spawning evader");
                    auto &p=it->second;
                    if(command=="evader_cooldown_bonus") {
                        require(!p.cooldownBonusMaximum,"Duplicate evader cooldown bonus");
                        p.cooldownBonusMinimum=integer(row,1,600-p.cooldownFrames);
                        p.cooldownBonusMaximum=integer(row,p.cooldownBonusMinimum,600-p.cooldownFrames);
                    } else {
                        require(!p.childContactDeath,"Duplicate evader contact-death policy");
                        p.childContactDeath=true;
                    }
                } else if(command=="evader_detonation"||command=="evader_chase") {
                    require(!item&&!rule&&!graph&&!death,"Evader extension inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->evaders_.find(id);
                    require(it!=lib->evaders_.end()&&!it->second.spawns&&!it->second.chase&&!it->second.detonationChance,
                        "Detonation requires one preceding nonspawning evader body");
                    auto &p=it->second;
                    if(command=="evader_detonation") {p.detonationChance=integer(row,1,100000);p.detonationFrames=integer(row,1,300);}
                    else {p.chase=true;p.contactFrames=integer(row,1,120);p.contactRange=real(row);
                        require(p.contactRange>0&&p.contactRange<=30,"Invalid evader pursuit trigger range");}
                } else if(command=="buzz_shot") {
                    require(!item&&!rule&&!graph&&!death,"buzz_shot inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->buzzFlies_.find(id);
                    require(it!=lib->buzzFlies_.end()&&!it->second.shot,"Buzz shot requires one preceding controller");
                    HeadShooterDefinition p;
                    p.checkFrames=integer(row,1,120);p.cooldownFrames=integer(row,1,600);
                    p.attackFrames=integer(row,2,300);p.shootFrame=integer(row,1,p.attackFrames-1);
                    p.range=real(row);p.speed=real(row);p.damage=real(row);p.life=real(row);
                    auto &b=it->second;b.cooldownRetention=real(row);b.cooldownWander=real(row);
                    require(p.cooldownFrames>=p.attackFrames&&p.range>0&&p.range<=100&&p.speed>0&&p.speed<=100&&
                        p.damage>0&&p.damage<=1000&&p.life>0&&p.life<=30&&b.cooldownRetention>0&&b.cooldownRetention<=1&&
                        b.cooldownWander>=0&&b.cooldownWander<=1,"Invalid buzzing shot profile");
                    b.shot=p;
                } else if(command=="buzz_pair") {
                    require(!item&&!rule&&!graph&&!death,"buzz_pair inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->buzzFlies_.find(id);
                    require(it!=lib->buzzFlies_.end()&&it->second.shot&&!it->second.paired&&it->second.volley.empty(),"Buzz pair requires one preceding shooter");
                    auto &p=it->second;p.pairForward=real(row);p.pairSide=real(row);
                    require(p.pairForward>0&&p.pairForward<=1&&p.pairSide>0&&p.pairSide<=1,"Invalid buzzing pair coefficients");
                    p.paired=true;
                } else if(command=="buzz_volley") {
                    require(!item&&!rule&&!graph&&!death,"buzz_volley inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->buzzFlies_.find(id);
                    require(it!=lib->buzzFlies_.end()&&it->second.shot&&!it->second.paired&&it->second.volley.empty(),"Buzz volley requires one preceding shooter");
                    const int count=integer(row,2,16);
                    for(int n=0;n<count;++n) {
                        Vector2 v{real(row),real(row)};
                        require(v.x>0&&v.x<=2&&std::abs(v.y)<=2,"Invalid buzzing volley coefficient");
                        it->second.volley.push_back(v);
                    }
                } else if(command=="buzz_back_split") {
                    require(!item&&!rule&&!graph&&!death,"buzz_back_split inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->buzzFlies_.find(id);
                    require(it!=lib->buzzFlies_.end()&&it->second.shot&&!it->second.impactSplit,"Buzz split requires one preceding shooter");
                    auto &p=it->second;ProjectileSplitDefinition s;p.shotRadius=real(row);s.angle=real(row)*Pi/180;
                    s.speed=real(row);s.damage=real(row);s.radius=real(row);s.offset=real(row);s.life=real(row);
                    require(p.shotRadius>0&&p.shotRadius<=2&&s.angle>0&&s.angle<Pi/2&&s.speed>0&&s.speed<=100&&
                        s.damage>0&&s.damage<=1000&&s.radius>0&&s.radius<p.shotRadius&&s.offset>=0&&s.offset<=5&&s.life>0&&s.life<=30,
                        "Invalid buzzing backward split");
                    p.impactSplit=s;
                } else if(command=="buzz_suppress") {
                    require(!item&&!rule&&!graph&&!death,"buzz_suppress inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->buzzFlies_.find(id);
                    require(it!=lib->buzzFlies_.end()&&it->second.shot&&!it->second.suppressor,"Buzz suppression requires one preceding shooter");
                    it->second.suppressor=parseItemKey(word(row));
                } else if(command=="buzz_chase") {
                    require(!item&&!rule&&!graph&&!death,"buzz_chase inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->buzzFlies_.find(id);
                    require(it!=lib->buzzFlies_.end()&&!it->second.chase,"Buzz chase requires one preceding controller");
                    BuzzChaseDefinition p;p.targetFrames=integer(row,1,120);p.forceFrames=integer(row,1,120);
                    p.axisScale=real(row);p.deadzone=real(row);p.gain=real(row);p.force=real(row);p.contact=real(row);
                    require(p.axisScale>0&&p.axisScale<=1&&p.deadzone>=0&&p.deadzone<=200&&p.gain>0&&p.gain<=1&&
                        p.force>0&&p.force<=5&&p.contact>0&&p.contact<=1000,"Invalid buzzing chase profile");
                    it->second.chase=p;
                } else if(command=="buzz_item_morph") {
                    require(!item&&!rule&&!graph&&!death,"buzz_item_morph inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->buzzFlies_.find(id);
                    require(it!=lib->buzzFlies_.end()&&!it->second.morphItem,"Buzz item morph requires one preceding controller");
                    it->second.morphItem=parseItemKey(word(row));it->second.itemMorph=parseMonsterId(word(row));
                } else if(command=="buzz_contact_summon") {
                    require(!item&&!rule&&!graph&&!death,"buzz_contact_summon inside definition");
                    const auto id=parseMonsterId(word(row)),parent=parseMonsterId(word(row));auto it=lib->buzzFlies_.find(id);
                    const float retention=real(row);
                    require(it!=lib->buzzFlies_.end()&&retention>0&&retention<=1,"Invalid buzzing contact summon");
                    require(it->second.contactSummoners.emplace(parent,retention).second,"Duplicate buzzing contact summoner");
                } else if(command=="dung_morph") {
                    require(!item&&!rule&&!graph&&!death,"dung_morph inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->buzzFlies_.find(id);
                    require(it!=lib->buzzFlies_.end()&&!it->second.morphChance,"Dung morph requires one preceding controller");
                    it->second.morph=parseMonsterId(word(row));it->second.morphChance=integer(row,1,1000000);
                } else if(command=="dung_props") {
                    require(!item&&!rule&&!graph&&!death&&!lib->dung_,"Duplicate or nested dung profile");
                    DungDefinition p;p.firstBand=integer(row,0,3);p.lastBand=integer(row,p.firstBand,3);p.count=integer(row,0,20);
                    p.halfWidth=real(row);p.height=real(row);p.hits=integer(row,1,100);p.bonusChance=integer(row,1,10000);
                    require(p.halfWidth>=.3f&&p.halfWidth<=2&&p.height>=.9f&&p.height<=2,"Invalid dung geometry");lib->dung_=p;
                } else if(command=="adult_leech") {
                    require(!item&&!rule&&!graph&&!death,"adult_leech inside definition");
                    const auto id=parseMonsterId(word(row));AdultLeechDefinition p;
                    p.scale=real(row);p.contact=real(row);p.walkForce=real(row);p.walkRetention=real(row);
                    p.headingChance=integer(row,1,1000);p.recoveryRetention=real(row);p.chargeChance=integer(row,1,1000);
                    p.alignment=real(row);p.chargeRetention=real(row);p.initialGain=real(row);p.gainStep=real(row);p.maxGain=real(row);
                    p.gainRange=real(row);p.steerDeadzone=real(row);p.steer=real(row);p.steerCap=real(row);
                    p.impactSpeed=real(row);p.impactDot=real(row);p.recoil=real(row);
                    p.recoveryFrames=integer(row,1,300);p.walkFrames=integer(row,1,300);
                    require(p.scale>0&&p.scale<=1&&p.contact>0&&p.contact<=1000&&p.walkForce>0&&p.walkForce<=10&&
                        p.walkRetention>0&&p.walkRetention<1&&p.recoveryRetention>0&&p.recoveryRetention<1&&
                        p.alignment>0&&p.alignment<=100&&p.chargeRetention>0&&p.chargeRetention<1&&p.initialGain>0&&
                        p.gainStep>0&&p.gainStep<=5&&p.maxGain>=p.initialGain&&p.maxGain<=10&&p.gainRange>0&&p.gainRange<=2000&&
                        p.steerDeadzone>=0&&p.steerDeadzone<=100&&p.steer>=0&&p.steer<=1&&p.steerCap>0&&p.steerCap<=10&&
                        p.impactSpeed>0&&p.impactSpeed<=100&&p.impactDot>=0&&p.impactDot<=1&&p.recoil>=0&&p.recoil<=20,
                        "Invalid Adult Leech locomotion");
                    require(lib->adultLeeches_.emplace(id,p).second,"Duplicate Adult Leech controller");
                } else if(command=="adult_leech_burrow") {
                    require(!item&&!rule&&!graph&&!death,"adult_leech_burrow inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->adultLeeches_.find(id);
                    require(it!=lib->adultLeeches_.end()&&!it->second.burrowConfigured,"Adult Leech burrow needs preceding controller once");
                    auto &p=it->second;p.healthThreshold=real(row);p.burrowDistance=real(row);p.burrowChance=integer(row,1,1000);
                    p.grid=real(row);p.burrowPull=real(row);p.burrowRetention=real(row);
                    p.burrowFrames=integer(row,2,300);p.burrowSound=integer(row,0,p.burrowFrames-1);p.burrowHit=integer(row,1,p.burrowFrames-1);
                    p.hiddenFrames=integer(row,0,300);p.emergeChance=integer(row,1,1000);
                    p.fallFrames=integer(row,3,300);p.fallHit=integer(row,1,p.fallFrames-2);p.fallSound=integer(row,p.fallHit+1,p.fallFrames-1);
                    p.followForce=real(row);p.followRetention=real(row);p.settleRetention=real(row);p.freeRetention=real(row);
                    require(p.healthThreshold>0&&p.healthThreshold<1&&p.burrowDistance>0&&p.burrowDistance<=1000&&
                        p.grid>0&&p.grid<=100&&p.burrowPull>0&&p.burrowPull<=1&&p.burrowRetention>0&&p.burrowRetention<1&&
                        p.followForce>0&&p.followForce<=10&&p.followRetention>0&&p.followRetention<1&&
                        p.settleRetention>0&&p.settleRetention<1&&p.freeRetention>0&&p.freeRetention<1,"Invalid Adult Leech burrow");
                    p.burrowConfigured=true;
                } else if(command=="adult_leech_shot") {
                    require(!item&&!rule&&!graph&&!death,"adult_leech_shot inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->adultLeeches_.find(id);const auto ring=word(row);
                    require(it!=lib->adultLeeches_.end()&&(ring=="wall"||ring=="landing"),"Invalid Adult Leech ring owner/kind");
                    auto &p=it->second.shots[ring=="wall"?0:1];require(!p.count,"Duplicate Adult Leech ring");
                    p.count=integer(row,2,64);p.speed=real(row);p.gravity=real(row);p.height=real(row);p.upMin=real(row);p.upMax=real(row);
                    p.retention=real(row);p.radius=real(row);p.damage=real(row);p.life=real(row);p.offset=real(row);
                    require(p.speed>0&&p.speed<=200&&p.gravity>0&&p.gravity<=200&&p.height>0&&p.height<=10&&
                        p.upMin>=-100&&p.upMax>=p.upMin&&p.upMax<=100&&p.retention>0&&p.retention<=1&&
                        p.radius>0&&p.radius<=2&&p.damage>0&&p.damage<=1000&&p.life>0&&p.life<=30&&p.offset>=0&&p.offset<=5,
                        "Invalid Adult Leech ring");
                } else if(command=="dip"||command=="squirt") {
                    require(!item&&!rule&&!graph&&!death,"slide controller inside definition");
                    const auto id=parseMonsterId(word(row));SlideDefinition p;p.targeted=command=="squirt";
                    p.scale=real(row);p.contact=real(row);p.idleRetention=real(row);p.moveRetention=real(row);
                    p.impulseMin=real(row);p.impulseMax=real(row);p.stopSpeed=real(row);
                    p.chance=integer(row,1,10000);p.checkFrames=integer(row,1,300);p.idleFrames=integer(row,1,300);p.moveFrames=integer(row,1,300);
                    if(p.targeted) {
                        p.attackFrames=integer(row,2,300);p.launchFrame=integer(row,1,p.attackFrames-1);
                        p.sustainForce=real(row);p.sustainFrames=integer(row,1,300);p.slowSpeed=real(row);p.slowRetention=real(row);
                        p.collisionFrames=integer(row,0,300);p.collisionRetention=real(row);p.child=parseMonsterId(word(row));p.childOffset=real(row);
                    }
                    require(p.scale>0&&p.scale<=1&&p.contact>0&&p.contact<=1000&&p.idleRetention>0&&p.idleRetention<1&&
                        p.moveRetention>0&&p.moveRetention<1&&p.impulseMin>0&&p.impulseMax>=p.impulseMin&&p.impulseMax<=100&&
                        (p.targeted?p.impulseMin==p.impulseMax:p.checkFrames==1)&&
                        p.stopSpeed>0&&p.stopSpeed<=10&&p.sustainForce>=0&&p.sustainForce<=10&&p.slowSpeed>=p.stopSpeed&&
                        p.slowSpeed<=100&&p.slowRetention>0&&p.slowRetention<=1&&p.collisionRetention>0&&p.collisionRetention<=1&&
                        p.childOffset>0&&p.childOffset<=5,"Invalid slide profile");
                    require(lib->slides_.emplace(id,p).second,"Duplicate slide controller");
                } else if(command=="slide_swim"||command=="drip_chain"||command=="splurt"||command=="slide_creep"||command=="slide_death_shot") {
                    require(!item&&!rule&&!graph&&!death,"slide extension inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->slides_.find(id);
                    require(it!=lib->slides_.end(),"Slide extension requires preceding controller");auto &p=it->second;
                    if(command=="slide_swim") {require(!p.floodedPits,"Duplicate slide swim");p.floodedPits=true;}
                    else if(command=="drip_chain") {
                        require(!p.targeted&&!p.chainFrame,"Drip chain requires one untargeted controller");
                        p.chainFrame=integer(row,1,p.moveFrames-1);p.chainChance=integer(row,1,1000);p.aimChance=integer(row,1,1000);
                    } else if(command=="splurt") {
                        require(p.targeted&&!p.secondAttackFrames,"Splurt requires one targeted controller");
                        p.secondAttackFrames=integer(row,2,300);p.secondLaunchFrame=integer(row,1,p.secondAttackFrames-1);
                        p.firstBrake=integer(row,1,300);p.secondBrake=integer(row,p.firstBrake,300);
                        p.childImpulseMin=real(row);p.childImpulseMax=real(row);
                        require(p.childImpulseMin>0&&p.childImpulseMax>=p.childImpulseMin&&p.childImpulseMax<=100,"Invalid Splurt child impulse");
                    } else if(command=="slide_creep") {
                        require(p.targeted&&!p.creep,"Slide creep requires one targeted controller");SlideCreep c;
                        c.interval=integer(row,1,300);c.radius=real(row);c.frames=integer(row,1,3000);
                        c.fadeFrames=integer(row,1,300);c.fadeScale=real(row);
                        require(c.radius>0&&c.radius<=10&&c.fadeScale>0&&c.fadeScale<1,"Invalid slide creep");p.creep=c;
                    } else {
                        require(!p.targeted&&!p.deathShot,"Slide death shot requires one untargeted controller");SlideDeathShot s;
                        s.prediction=real(row);s.speed=real(row);s.height=real(row);s.up=real(row);s.gravity=real(row);s.retention=real(row);
                        s.radius=real(row);s.damage=real(row);s.life=real(row);
                        require(s.prediction>=0&&s.prediction<=10&&s.speed>0&&s.speed<=200&&s.height>0&&s.height<=10&&
                            s.up>=-100&&s.up<=100&&s.gravity>0&&s.gravity<=200&&s.retention>0&&s.retention<=1&&
                            s.radius>0&&s.radius<=2&&s.damage>0&&s.damage<=1000&&s.life>0&&s.life<=30,"Invalid slide death shot");p.deathShot=s;
                    }
                } else if(command=="dinga") {
                    require(!item&&!rule&&!graph&&!death,"dinga inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->memBrains_.find(id);
                    require(it!=lib->memBrains_.end()&&!it->second.dinga,"Dinga requires preceding MemBrain controller once");
                    DingaDefinition p;p.child=parseMonsterId(word(row));p.populationLimit=integer(row,1,100);p.shotChance=integer(row,1,1000);
                    p.childOffset=real(row);p.pushRange=real(row);p.pushForce=real(row);p.animationFps=real(row);
                    require(p.childOffset>0&&p.childOffset<=5&&p.pushRange>0&&p.pushRange<=1000&&p.pushForce>0&&p.pushForce<=1&&
                        p.animationFps>0&&p.animationFps<=120,"Invalid Dinga profile");it->second.dinga=p;
                } else if(command=="membrain") {
                    require(!item&&!rule&&!graph&&!death,"membrain inside definition");
                    const auto id=parseMonsterId(word(row));MemBrainDefinition p;
                    p.scale=real(row);p.force=real(row);p.retention=real(row);p.wanderDistance=real(row);p.arrival=real(row);p.stuckSpeed=real(row);
                    p.stuckChance=integer(row,1,1000);p.contact=real(row);p.chance=integer(row,1,10000);p.populationLimit=integer(row,1,100);
                    p.walkFrames=integer(row,1,300);p.attackFrames=integer(row,2,300);p.shootFrame=integer(row,1,p.attackFrames-1);
                    p.child=parseMonsterId(word(row));p.childOffset=real(row);
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.retention>0&&p.retention<1&&p.wanderDistance>0&&
                        p.wanderDistance<=500&&p.arrival>0&&p.arrival<p.wanderDistance&&p.stuckSpeed>=0&&p.stuckSpeed<=10&&
                        p.contact>0&&p.contact<=1000&&p.childOffset>0&&p.childOffset<=5,"Invalid MemBrain locomotion");
                    require(lib->memBrains_.emplace(id,p).second,"Duplicate MemBrain controller");
                } else if(command=="membrain_shot") {
                    require(!item&&!rule&&!graph&&!death,"membrain_shot inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->memBrains_.find(id);
                    require(it!=lib->memBrains_.end()&&!it->second.shotConfigured,"MemBrain shot needs preceding controller once");
                    auto &p=it->second;p.shotConfigured=true;
                    p.shotSpeed=real(row);p.shotAngle=real(row);p.shotHeight=real(row);p.shotUpMin=real(row);p.shotUpMax=real(row);
                    p.shotGravity=real(row);p.shotRetention=real(row);p.shotRadius=real(row);p.shotDamage=real(row);p.shotLife=real(row);p.wallBounce=flag(row);
                    require(p.shotSpeed>0&&p.shotSpeed<=100&&std::abs(p.shotAngle)<=7&&p.shotHeight>0&&p.shotHeight<=5&&
                        p.shotUpMin>=-30&&p.shotUpMax>=p.shotUpMin&&p.shotUpMax<=30&&p.shotGravity>0&&p.shotGravity<=100&&
                        p.shotRetention>0&&p.shotRetention<=1&&p.shotRadius>0&&p.shotRadius<=2&&p.shotDamage>0&&p.shotDamage<=1000&&
                        p.shotLife>0&&p.shotLife<=30,"Invalid MemBrain projectile");
                } else if(command=="lump") {
                    require(!item&&!rule&&!graph&&!death,"lump inside definition");
                    const auto id=parseMonsterId(word(row));LumpDefinition p;
                    p.scale=real(row);p.retention=real(row);p.contact=real(row);
                    p.hideChance=integer(row,1,10000);p.appearChance=integer(row,1,10000);
                    p.hideFrames=integer(row,2,300);p.appearFrames=integer(row,2,300);p.shakeFrames=integer(row,1,300);
                    p.margin=real(row);p.alignment=real(row);p.axisRange=real(row);p.targetMin=real(row);p.grid=real(row);
                    require(p.scale>0&&p.scale<=1&&p.retention>0&&p.retention<1&&p.contact>0&&p.contact<=1000&&
                        p.margin>0&&p.margin<=100&&p.alignment>0&&p.axisRange>p.alignment&&p.axisRange<=2000&&
                        p.targetMin>0&&p.targetMin<p.axisRange&&p.grid>0&&p.grid<=100,"Invalid Lump burrow profile");
                    require(lib->lumps_.emplace(id,p).second,"Duplicate Lump controller");
                } else if(command=="lump_shot") {
                    require(!item&&!rule&&!graph&&!death,"lump_shot inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->lumps_.find(id);
                    require(it!=lib->lumps_.end()&&!it->second.shotConfigured,"Lump shot requires preceding controller once");
                    auto &p=it->second;p.shotConfigured=true;
                    p.shot.checkFrames=integer(row,1,300);p.shot.cooldownFrames=integer(row,1,600);
                    p.shot.attackFrames=integer(row,2,300);p.shot.shootFrame=integer(row,1,p.shot.attackFrames-1);
                    p.shot.range=real(row);p.shot.speed=real(row);p.shot.damage=real(row);p.shot.life=real(row);
                    p.shotHeight=real(row);p.shotUp=real(row);p.shotGravity=real(row);p.shotRetention=real(row);p.shotRadius=real(row);
                    require(p.shot.range>0&&p.shot.range<=100&&p.shot.speed>0&&p.shot.speed<=100&&p.shot.damage>0&&p.shot.damage<=1000&&
                        p.shot.life>0&&p.shot.life<=30&&p.shotHeight>0&&p.shotHeight<=5&&p.shotUp>=0&&p.shotUp<=100&&
                        p.shotGravity>0&&p.shotGravity<=200&&p.shotRetention>0&&p.shotRetention<=1&&p.shotRadius>0&&p.shotRadius<=2,
                        "Invalid Lump projectile");
                } else if(command=="leech") {
                    require(!item&&!rule&&!graph&&!death,"leech inside definition");
                    const auto id=parseMonsterId(word(row));LeechDefinition p;
                    p.scale=real(row);p.force=real(row);p.retention=real(row);p.zRetention=real(row);p.contact=real(row);
                    p.chargeForce=real(row);p.chargeRetention=real(row);p.gridPull=real(row);
                    p.alignment=real(row);p.prediction=real(row);p.checkFrames=integer(row,1,120);
                    p.walkFrames=integer(row,1,300);p.dashFrames=integer(row,1,300);
                    p.grid=real(row);p.arrival=real(row);p.stuckSpeed=real(row);
                    p.attempts=integer(row,1,20);p.maxCells=integer(row,1,20);p.stuckFrames=integer(row,1,120);
                    p.chargeStuckDistance=real(row);p.chargeStuckFrames=integer(row,1,120);
                    const auto child=word(row);if(child!="none")p.child=parseMonsterId(child);
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.retention>0&&p.retention<1&&
                        p.zRetention>0&&p.zRetention<=1&&p.contact>0&&p.contact<=1000&&p.chargeForce>0&&p.chargeForce<=10&&
                        p.chargeRetention>0&&p.chargeRetention<1&&p.gridPull>=0&&p.gridPull<=1&&
                        p.alignment>0&&p.alignment<=100&&p.prediction>=0&&p.prediction<=120&&p.grid>0&&p.grid<=100&&
                        p.arrival>0&&p.arrival<=p.grid&&p.stuckSpeed>0&&p.stuckSpeed<=10&&
                        p.chargeStuckDistance>0&&p.chargeStuckDistance<=10,"Invalid Leech profile");
                    require(lib->leeches_.emplace(id,p).second,"Duplicate Leech controller");
                } else if(command=="mirror") {
                    require(!item&&!rule&&!graph&&!death,"mirror inside definition");
                    const auto id=parseMonsterId(word(row));MirrorDefinition p;
                    p.cooldownFrames=integer(row,0,300);p.shots=integer(row,1,3);
                    p.speed=real(row);p.inheritance=real(row);p.movementMultiplier=real(row);
                    p.eyeMin=real(row);p.eyeExtra=real(row);
                    p.sideForward=real(row);p.sideCross=real(row);p.sideMultiplier=real(row);
                    p.spreadVelocity=real(row);p.spreadInheritance=real(row);
                    p.height=real(row);p.up=real(row);p.gravity=real(row);p.retention=real(row);
                    p.radius=real(row);p.damage=real(row);p.life=real(row);
                    require((p.shots==1||p.shots==3)&&p.speed>0&&p.speed<=200&&p.inheritance>=0&&p.inheritance<=2&&
                        p.movementMultiplier>0&&p.movementMultiplier<=4&&p.eyeMin>=0&&p.eyeExtra>=0&&p.eyeMin+p.eyeExtra<=2&&
                        p.sideForward>0&&p.sideForward<=1&&p.sideCross>=0&&p.sideCross<=1&&p.sideMultiplier>0&&p.sideMultiplier<=2&&
                        p.spreadVelocity>0&&p.spreadVelocity<=3&&p.spreadInheritance>=0&&p.spreadInheritance<=2&&
                        p.height>0&&p.height<=10&&p.up>=0&&p.up<=100&&p.gravity>0&&p.gravity<=200&&p.retention>0&&p.retention<=1&&
                        p.radius>0&&p.radius<=2&&p.damage>0&&p.damage<=1000&&p.life>0&&p.life<=30,"Invalid mirror profile");
                    require(lib->mirrors_.emplace(id,p).second,"Duplicate mirror controller");
                } else if(command=="knight") {
                    require(!item&&!rule&&!graph&&!death,"knight inside definition");
                    const auto id=parseMonsterId(word(row));KnightDefinition p;
                    p.scale=real(row);p.force=real(row);p.retention=real(row);p.mass=real(row);p.contact=real(row);
                    p.chargeForce=real(row);p.chargeAcceleration=real(row);p.chargeMaximum=real(row);
                    p.checkFrames=integer(row,1,120);p.walkFrames=integer(row,1,300);
                    p.alignment=real(row);p.range=real(row);p.prediction=real(row);p.gridPull=real(row);
                    p.grid=real(row);p.arrival=real(row);p.stuckSpeed=real(row);
                    p.attempts=integer(row,1,20);p.maxCells=integer(row,1,20);p.stuckFrames=integer(row,1,120);
                    p.randomWalk=integer(row,0,1)!=0;
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.retention>0&&p.retention<1&&
                        p.mass>0&&p.mass<=1000&&p.contact>0&&p.contact<=1000&&p.chargeForce>0&&p.chargeMaximum>=p.chargeForce&&
                        p.chargeMaximum<=10&&p.chargeAcceleration>=0&&p.chargeAcceleration<=1&&
                        p.alignment>0&&p.alignment<=100&&p.range>p.alignment&&p.range<=1000&&p.prediction>=0&&p.prediction<=120&&
                        p.gridPull>=0&&p.gridPull<=1&&p.grid>0&&p.grid<=100&&p.arrival>0&&p.arrival<=p.grid&&
                        p.stuckSpeed>0&&p.stuckSpeed<=10,"Invalid Knight movement profile");
                    require(lib->knights_.emplace(id,p).second,"Duplicate Knight controller");
                } else if(command=="knight_random") {
                    require(!item&&!rule&&!graph&&!death,"knight_random inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->knights_.find(id);
                    require(it!=lib->knights_.end()&&it->second.randomWalk,"Knight random profile requires random walker");
                    auto &p=it->second;p.randomForce=real(row);p.randomDistance=real(row);p.randomArrival=real(row);
                    require(p.randomForce>0&&p.randomForce<=10&&p.randomDistance>0&&p.randomDistance<=200&&
                        p.randomArrival>0&&p.randomArrival<p.randomDistance,"Invalid Knight random walk");
                } else if(command=="knight_impact") {
                    require(!item&&!rule&&!graph&&!death,"knight_impact inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->knights_.find(id);
                    require(it!=lib->knights_.end()&&!it->second.recoveryFrames,"Knight impact requires one preceding controller");
                    auto &p=it->second;p.impactSpeed=real(row);p.impactAlignment=real(row);p.impactBrake=real(row);
                    p.recoveryRetention=real(row);p.impactLift=real(row);p.impactGravity=real(row);p.impactRebound=real(row);
                    p.recoveryFrames=integer(row,1,600);p.ignoreFireJets=integer(row,0,1)!=0;
                    require(p.impactSpeed>0&&p.impactSpeed<=100&&p.impactAlignment>0&&p.impactAlignment<=1&&
                        p.impactBrake>=0&&p.impactBrake<=1&&p.recoveryRetention>0&&p.recoveryRetention<1&&
                        p.impactLift>0&&p.impactLift<=30&&p.impactGravity>0&&p.impactGravity<=10&&
                        p.impactRebound>0&&p.impactRebound<=10,"Invalid Knight impact profile");
                } else if(command=="knight_fire_wave") {
                    require(!item&&!rule&&!graph&&!death,"knight_fire_wave inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->knights_.find(id);
                    require(it!=lib->knights_.end()&&it->second.recoveryFrames&&!it->second.impactWave.jetStepFrames,
                        "Knight wave requires one preceding impact profile");
                    auto &w=it->second.impactWave;
                    w.jetStepFrames=integer(row,1,30);w.jetSpacing=real(row);w.jetCount=integer(row,1,64);
                    w.jetLifeFrames=integer(row,3,300);w.jetPulseA=integer(row,1,w.jetLifeFrames-2);w.jetPulseB=integer(row,w.jetPulseA+1,w.jetLifeFrames-1);
                    w.radius=real(row);w.jetMonsterDamage=real(row);w.damage=real(row);w.jetScaleLoss=real(row);
                    require(w.jetSpacing>0&&w.jetSpacing<=10&&w.radius>0&&w.radius<=5&&w.jetMonsterDamage>0&&w.jetMonsterDamage<=1000&&
                        w.damage>0&&w.damage<=1000&&w.jetScaleLoss>=0&&w.jetScaleLoss*float(w.jetCount)<1,"Invalid Knight fire wave");
                    w.speed=w.jetSpacing*30/float(w.jetStepFrames);w.range=w.jetSpacing*float(w.jetCount);w.trailDuration=float(w.jetLifeFrames)/30;
                } else if(command=="mask_armor") {
                    require(!item&&!rule&&!graph&&!death,"mask_armor inside definition");
                    const auto id=parseMonsterId(word(row));MaskArmorDefinition p;
                    p.reflect=integer(row,0,1)!=0;p.turnGraceFrames=integer(row,0,300);
                    p.reflectionDamage=real(row);p.grazingThreshold=real(row);
                    require(p.reflectionDamage>0&&p.reflectionDamage<=100&&p.grazingThreshold>=0&&p.grazingThreshold<=1&&
                        (p.reflect||p.turnGraceFrames==0),"Invalid mask reflection profile");
                    require(lib->maskArmor_.emplace(id,p).second,"Duplicate mask armor");
                } else if(command=="linked_remnant") {
                    require(!item&&!rule&&!graph&&!death,"linked_remnant inside definition");
                    LinkedRemnantDefinition p;p.source=parseMonsterId(word(row));p.body=parseMonsterId(word(row));
                    p.child=parseMonsterId(word(row));p.offset=real(row);
                    require(p.source!=p.body&&p.body!=p.child&&p.child!=p.source&&p.offset>0&&p.offset<=8,
                        "Invalid linked remnant identities or offset");
                    for(auto id:{p.source,p.body,p.child})require(lib->linkedRemnants_.emplace(id,p).second,"Duplicate linked remnant identity");
                } else if(command=="landing_creep") {
                    require(!item&&!rule&&!graph&&!death,"landing_creep inside definition");
                    const auto id=parseMonsterId(word(row));LandingCreepDefinition p;
                    p.searchAttempts=integer(row,1,100);p.releaseChance=integer(row,1,100);
                    p.frames=integer(row,1,1800);p.fadeFrames=integer(row,1,600);
                    p.radius=real(row);p.damage=real(row);p.fadeScale=real(row);
                    require(p.radius>0&&p.radius<=8&&p.damage>0&&p.damage<=100&&p.fadeScale>0&&p.fadeScale<=1,
                        "Invalid landing creep footprint or damage");
                    require(lib->landingCreep_.emplace(id,p).second,"Duplicate landing creep");
                } else if(command=="guts") {
                    require(!item&&!rule&&!graph&&!death,"guts inside definition");
                    const auto id=parseMonsterId(word(row));GutsDefinition p;
                    p.scale=real(row);p.force=real(row);p.retention=real(row);p.grid=real(row);
                    p.arrival=real(row);p.crossPull=real(row);p.contact=real(row);p.rollFrames=integer(row,1,300);
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=20&&p.retention>0&&p.retention<1&&
                        p.grid>0&&p.grid<=100&&p.arrival>0&&p.arrival<p.grid/2&&p.crossPull>=0&&p.crossPull<=1&&
                        p.contact>0&&p.contact<=1000,"Invalid Guts locomotion");
                    require(lib->guts_.emplace(id,p).second,"Duplicate Guts controller");
                } else if(command=="guts_shot") {
                    require(!item&&!rule&&!graph&&!death,"guts_shot inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->guts_.find(id);
                    require(it!=lib->guts_.end()&&!it->second.shooting,"Guts shot needs preceding controller once");auto &p=it->second;p.shooting=true;
                    p.shotInterval=integer(row,1,600);p.shotFrames=integer(row,1,300);p.shotSpeed=real(row);p.shotDamage=real(row);
                    p.shotHeight=real(row);p.shotUp=real(row);p.shotGravity=real(row);p.shotRetention=real(row);p.shotRadius=real(row);p.shotLife=real(row);
                    require(p.shotSpeed>0&&p.shotSpeed<=100&&p.shotDamage>0&&p.shotDamage<=1000&&p.shotHeight>0&&p.shotHeight<=5&&
                        p.shotUp>=-30&&p.shotUp<=30&&p.shotGravity>0&&p.shotGravity<=100&&p.shotRetention>0&&p.shotRetention<=1&&
                        p.shotRadius>0&&p.shotRadius<=2&&p.shotLife>0&&p.shotLife<=30,"Invalid Guts shot");
                } else if(command=="guts_charge") {
                    require(!item&&!rule&&!graph&&!death,"guts_charge inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->guts_.find(id);
                    require(it!=lib->guts_.end()&&!it->second.charge,"Guts charge needs preceding controller");
                    auto &p=it->second;p.charge=true;p.windupFrames=integer(row,1,120);p.recoveryFrames=integer(row,1,600);
                    p.hitFrames=integer(row,1,p.recoveryFrames);p.prediction=real(row);p.chargeMultiplier=real(row);
                    p.brake=real(row);p.recoveryAcceleration=real(row);
                    require(p.prediction>=0&&p.prediction<=60&&p.chargeMultiplier>1&&p.chargeMultiplier<=5&&
                        p.brake>0&&p.brake<1&&p.recoveryAcceleration>0&&p.recoveryAcceleration<=1,"Invalid Guts charge");
                } else if(command=="guts_creep") {
                    require(!item&&!rule&&!graph&&!death,"guts_creep inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->guts_.find(id);
                    require(it!=lib->guts_.end()&&!it->second.creepInterval,"Guts creep needs preceding controller");
                    auto &p=it->second;const auto kind=word(row);require(kind=="red"||kind=="tar","Invalid Guts creep kind");p.tar=kind=="tar";
                    p.creepInterval=integer(row,1,300);p.chargingCreepInterval=integer(row,1,300);
                    p.creepFrames=integer(row,1,900);p.fadeFrames=integer(row,1,300);p.creepRadius=real(row);p.creepDamage=real(row);p.fadeScale=real(row);
                    require(p.creepRadius>0&&p.creepRadius<=5&&p.fadeScale>0&&p.fadeScale<1&&
                        (p.tar?p.creepDamage==0:p.creepDamage>0&&p.creepDamage<=1000),"Invalid Guts creep");
                } else if(command=="vis") {
                    require(!item&&!rule&&!graph&&!death,"vis inside definition");
                    const auto id=parseMonsterId(word(row));VisDefinition p;
                    p.scale=real(row);p.force=real(row);p.retention=real(row);p.zRetention=1;p.contact=real(row);
                    p.walkFrames=integer(row,1,300);p.checkFrames=integer(row,1,300);
                    p.alignment=real(row);p.range=real(row);p.attackFrames=integer(row,2,300);
                    p.shootFrame=integer(row,1,p.attackFrames-1);p.beams=integer(row,0,4);
                    p.grid=real(row);p.arrival=real(row);p.stuckSpeed=real(row);
                    p.attempts=integer(row,1,20);p.maxCells=integer(row,1,20);p.stuckFrames=integer(row,1,120);
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.retention>0&&p.retention<1&&
                        p.contact>0&&p.contact<=1000&&p.alignment>0&&p.range>p.alignment&&p.range<=2000&&p.beams!=3&&
                        p.grid>0&&p.grid<=100&&p.arrival>0&&p.arrival<=p.grid&&p.stuckSpeed>0&&p.stuckSpeed<=10,
                        "Invalid Vis movement/attack");
                    require(lib->vis_.emplace(id,p).second,"Duplicate Vis controller");
                } else if(command=="vis_returning_body") {
                    require(!item&&!rule&&!graph&&!death,"vis_returning_body inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->vis_.find(id);
                    require(it!=lib->vis_.end()&&!it->second.returningBody,"Returning body requires one preceding Vis controller");
                    it->second.returningBody=parseMonsterId(word(row));
                } else if(command=="returning_body") {
                    require(!item&&!rule&&!graph&&!death,"returning_body inside definition");
                    const auto id=parseMonsterId(word(row));ReturningBodyDefinition p;p.owner=parseMonsterId(word(row));
                    p.scale=real(row);p.launch=real(row);p.horizontalMultiplier=real(row);
                    p.reversalFrame=integer(row,1,300);p.removeAfter=integer(row,p.reversalFrame+1,600);
                    p.returnOffset=real(row);p.contact=real(row);p.spawnOffset=real(row);
                    require(p.scale>0&&p.scale<=1&&p.launch>0&&p.launch<=100&&p.horizontalMultiplier>0&&p.horizontalMultiplier<=4&&
                        p.returnOffset>=0&&p.returnOffset<=200&&p.contact>0&&p.contact<=1000&&std::abs(p.spawnOffset)<=10,
                        "Invalid returning body trajectory");
                    require(lib->returningBodies_.emplace(id,p).second,"Duplicate returning body");
                } else if(command=="vis_beam") {
                    require(!item&&!rule&&!graph&&!death,"vis_beam inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->vis_.find(id);
                    require(it!=lib->vis_.end()&&!it->second.beamConfigured,"Vis beam requires one preceding controller");
                    auto &p=it->second;p.beamConfigured=true;
                    p.beamFrames=integer(row,1,300);p.fadeFrames=integer(row,1,120);p.damageFrames=integer(row,1,120);
                    p.beamRange=real(row);p.beamRadius=real(row);p.playerDamage=real(row);p.monsterDamage=real(row);
                    p.originX=real(row);p.beamHeight=real(row);p.fadeScale=real(row);
                    require(p.beamRange>0&&p.beamRange<=500&&p.beamRadius>0&&p.beamRadius<=5&&
                        p.playerDamage>0&&p.playerDamage<=1000&&p.monsterDamage>0&&p.monsterDamage<=10000&&
                        p.originX>=0&&p.originX<=5&&p.beamHeight>0&&p.beamHeight<=5&&p.fadeScale>0&&p.fadeScale<1,
                        "Invalid Vis beam profile");
                } else if(command=="cardinal_walker") {
                    require(!item&&!rule&&!graph&&!death,"cardinal_walker inside definition");
                    const auto id=parseMonsterId(word(row));CardinalWalkerDefinition p;
                    p.scale=real(row);p.force=real(row);p.retention=real(row);p.zRetention=real(row);p.contact=real(row);
                    p.horizontalFrames=integer(row,2,300);p.verticalFrames=integer(row,2,300);
                    p.grid=real(row);p.arrival=real(row);p.stuckSpeed=real(row);
                    p.attempts=integer(row,1,20);p.maxCells=integer(row,1,20);p.stuckFrames=integer(row,1,120);
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.retention>0&&p.retention<1&&
                        p.zRetention>0&&p.zRetention<=1&&p.contact>0&&p.contact<=1000&&p.grid>0&&p.grid<=100&&
                        p.arrival>0&&p.arrival<=p.grid&&p.stuckSpeed>0&&p.stuckSpeed<=10,"Invalid cardinal walker movement");
                    require(lib->cardinalWalkers_.emplace(id,p).second,"Duplicate cardinal walker controller");
                } else if(command=="baby") {
                    require(!item&&!rule&&!graph&&!death,"baby inside definition");
                    const auto id=parseMonsterId(word(row));BabyDefinition p;
                    p.kind=named<BabyKind>(word(row),{{"normal",BabyKind::Normal},{"angelic",BabyKind::Angelic},
                        {"small",BabyKind::Small},{"wrinkly",BabyKind::Wrinkly}});
                    p.scale=real(row);p.force=real(row);p.retention=real(row);p.contact=real(row);p.walkFrames=integer(row,1,300);
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.retention>0&&p.retention<1&&
                        p.contact>0&&p.contact<=1000,"Invalid Baby movement");
                    require(lib->babies_.emplace(id,p).second,"Duplicate Baby controller");
                } else if(command=="baby_shot"||command=="baby_teleport"||command=="baby_dash") {
                    require(!item&&!rule&&!graph&&!death,"Baby profile inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->babies_.find(id);
                    require(it!=lib->babies_.end(),"Baby profile requires preceding controller");auto &p=it->second;
                    if(command=="baby_shot") {
                        require(!p.shotConfigured,"Duplicate Baby shot");p.shotConfigured=true;
                        p.shot.checkFrames=integer(row,1,300);p.shot.cooldownFrames=integer(row,1,600);
                        p.shot.attackFrames=integer(row,2,300);p.shot.shootFrame=integer(row,1,p.shot.attackFrames-1);
                        p.shot.range=real(row);p.shot.speed=real(row);p.shot.damage=real(row);p.shot.life=real(row);
                        p.shotHeight=real(row);p.shotUp=real(row);p.shotGravity=real(row);p.shotRetention=real(row);
                        p.shotRadius=real(row);p.velocityMultiplier=real(row);p.spread=real(row);p.originOffset=real(row);
                        require(p.shot.range>0&&p.shot.range<=100&&p.shot.speed>0&&p.shot.speed<=100&&
                            p.shot.damage>0&&p.shot.damage<=1000&&p.shot.life>0&&p.shot.life<=30&&
                            p.shotHeight>0&&p.shotHeight<=5&&p.shotUp>=0&&p.shotUp<=100&&p.shotGravity>0&&p.shotGravity<=200&&
                            p.shotRetention>0&&p.shotRetention<=1&&p.shotRadius>0&&p.shotRadius<=2&&
                            p.velocityMultiplier>0&&p.velocityMultiplier<=3&&p.spread>0&&p.spread<=3&&
                            p.originOffset>=0&&p.originOffset<=5,"Invalid Baby projectile");
                    } else if(command=="baby_teleport") {
                        require(!p.teleportConfigured&&p.kind!=BabyKind::Wrinkly,"Invalid or duplicate Baby teleport");p.teleportConfigured=true;
                        p.searchCharge=real(row);p.startCharge=real(row);p.randomCharge=real(row);
                        p.alignment=real(row);p.alignmentRange=real(row);p.radiusMin=real(row);p.radiusExtra=real(row);
                        p.targetMin=real(row);p.targetMax=real(row);p.grid=real(row);p.attempts=integer(row,1,20);
                        p.vanishFrames=integer(row,2,300);p.appearFrames=integer(row,2,300);
                        p.jumpFrame=integer(row,1,p.vanishFrames-1);p.landFrame=integer(row,1,p.appearFrames-1);
                        require(p.searchCharge>0&&p.startCharge>p.searchCharge&&p.startCharge<=1000&&
                            p.randomCharge>=0&&p.randomCharge<=10&&p.alignment>0&&p.alignmentRange>p.alignment&&p.alignmentRange<=2000&&
                            p.radiusMin>0&&p.radiusExtra>=0&&p.radiusMin+p.radiusExtra<=2000&&p.targetMin>0&&
                            p.targetMin<=2000&&(p.targetMax==0||p.targetMax>p.targetMin)&&p.targetMax<=2000&&p.grid>0&&p.grid<=100,
                            "Invalid Baby teleport geometry");
                    } else {
                        require(!p.dashConfigured&&p.kind==BabyKind::Wrinkly,"Invalid or duplicate Baby dash");p.dashConfigured=true;
                        p.initialMin=integer(row,0,600);p.initialMax=integer(row,p.initialMin,600);
                        p.recoveryMin=integer(row,1,600);p.recoveryMax=integer(row,p.recoveryMin,600);
                        p.chance=integer(row,1,10000);p.dashFrames=integer(row,1,300);p.closeAttackFrame=integer(row,0,299);
                        p.keepDistance=real(row);p.dashRange=real(row);p.dashForce=real(row);p.dashRetention=real(row);p.dashStop=real(row);
                        require(p.keepDistance>0&&p.dashRange>p.keepDistance&&p.dashRange<=2000&&p.dashForce>0&&p.dashForce<=30&&
                            p.dashRetention>0&&p.dashRetention<1&&p.dashStop>0&&p.dashStop<p.keepDistance,"Invalid Wrinkly dash");
                    }
                } else if(command=="linked_head") {
                    require(!item&&!rule&&!graph&&!death,"linked_head inside definition");
                    LinkedHeadDefinition p;p.body=parseMonsterId(word(row));p.head=parseMonsterId(word(row));
                    p.neck=parseMonsterId(word(row));p.bodyRelease=parseMonsterId(word(row));p.headRelease=parseMonsterId(word(row));
                    p.scale=real(row);p.force=real(row);p.walkRetention=real(row);p.throwRetention=real(row);p.contact=real(row);
                    p.walkFrames=integer(row,1,300);p.splitChance=integer(row,1,1000000);
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.walkRetention>0&&p.walkRetention<1&&
                        p.throwRetention>0&&p.throwRetention<1&&p.contact>0&&p.contact<=1000,"Invalid linked head movement");
                    require(lib->linkedHeads_.emplace(p.body,p).second,"Duplicate linked head body");
                } else if(command=="linked_head_throw"||command=="linked_head_neck") {
                    require(!item&&!rule&&!graph&&!death,"Linked head profile inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->linkedHeads_.find(id);
                    require(it!=lib->linkedHeads_.end(),"Linked head profile requires preceding body");auto &p=it->second;
                    if(command=="linked_head_throw") {
                        require(!p.throwConfigured,"Duplicate linked head throw");p.throwConfigured=true;
                        p.checkFrames=integer(row,1,300);p.range=real(row);p.prediction=real(row);p.launchSpeed=real(row);p.returnDistance=real(row);
                        p.timerStart=integer(row,1,300);p.timerMinimum=integer(row,-300,-1);p.attachTimer=integer(row,0,p.timerStart);
                        p.springBase=real(row);p.springSubtract=real(row);p.springDivisor=real(row);p.headRetention=real(row);p.timerRetention=real(row);
                        require(p.range>0&&p.range<=1000&&p.prediction>=0&&p.prediction<=120&&p.launchSpeed>0&&p.launchSpeed<=100&&
                            p.returnDistance>0&&p.returnDistance<p.range&&p.springBase>0&&p.springBase<=10&&
                            p.springSubtract>=0&&p.springSubtract<p.springBase&&p.springDivisor>0&&p.springDivisor<=600&&
                            p.timerRetention>=0&&p.headRetention+p.timerRetention*float(p.timerMinimum)>0&&
                            p.headRetention+p.timerRetention*float(p.timerStart)<=1,"Invalid linked head spring");
                    } else {
                        require(!p.neckConfigured,"Duplicate linked head neck");p.neckConfigured=true;
                        p.neckCount=integer(row,1,16);p.neckRadius=real(row);p.headLift=real(row);p.neckSag=real(row);
                        p.deathShots=integer(row,0,16);p.deathSpeed=real(row);p.deathDamage=real(row);
                        require(p.neckRadius>0&&p.neckRadius<=1&&p.headLift>=0&&p.headLift<=3&&p.neckSag>=0&&p.neckSag<=3&&
                            p.deathSpeed>0&&p.deathSpeed<=100&&p.deathDamage>0&&p.deathDamage<=1000,"Invalid linked head neck/death profile");
                    }
                } else if(command=="brain") {
                    require(!item&&!rule&&!graph&&!death,"brain inside definition");
                    const auto id=parseMonsterId(word(row));BrainDefinition p;
                    p.scale=real(row);p.force=real(row);p.retention=real(row);p.verticalRetention=real(row);p.contact=real(row);
                    p.walkFrames=integer(row,2,300);p.grid=real(row);p.arrival=real(row);p.stuckSpeed=real(row);
                    p.attempts=integer(row,1,20);p.maxCells=integer(row,1,20);p.stuckFrames=integer(row,1,120);
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.retention>0&&p.retention<1&&
                        p.verticalRetention>0&&p.verticalRetention<1&&p.contact>0&&p.contact<=1000&&p.grid>0&&p.grid<=100&&
                        p.arrival>0&&p.arrival<=p.grid&&p.stuckSpeed>0&&p.stuckSpeed<=10,"Invalid Brain movement");
                    require(lib->brains_.emplace(id,p).second,"Duplicate Brain controller");
                } else if(command=="brain_charge"||command=="brain_creep"||command=="brain_pursuit") {
                    require(!item&&!rule&&!graph&&!death,"Brain profile inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->brains_.find(id);
                    require(it!=lib->brains_.end(),"Brain profile requires preceding controller");auto &p=it->second;
                    if(command=="brain_pursuit") {
                        require(!p.pursuit&&!p.chargeConfigured,"Conflicting Brain pursuit/charge");
                        p.pursuit=readGroundPursuit(row);
                        require(p.pursuit->scale==p.scale&&p.pursuit->contact==p.contact&&p.pursuit->walkFrames==p.walkFrames,
                            "Brain pursuit and trail must use the same units/contact/animation");
                    } else if(command=="brain_charge") {
                        require(!p.chargeConfigured&&!p.pursuit,"Conflicting Brain charge/pursuit");p.chargeConfigured=true;
                        p.chargeInterval=integer(row,1,300);p.alignment=real(row);p.range=real(row);p.prediction=real(row);
                        p.chargeRetention=real(row);p.gridPull=real(row);
                        require(p.alignment>0&&p.alignment<=p.grid&&p.range>p.alignment&&p.range<=1000&&
                            p.prediction>=0&&p.prediction<=120&&p.chargeRetention>0&&p.chargeRetention<1&&
                            p.gridPull>=0&&p.gridPull<=1,"Invalid Brain charge");
                    } else {
                        require(!p.creepConfigured,"Duplicate Brain creep");p.creepConfigured=true;
                        p.crowdThreshold=integer(row,1,100);p.denseInterval=integer(row,2,300);p.sparseInterval=integer(row,2,600);
                        p.extraCreepSpeed=real(row);p.creepRadius=real(row);p.creepDamage=real(row);
                        p.creepFrames=integer(row,1,1800);p.fadeFrames=integer(row,1,300);p.fadeScale=real(row);
                        require(p.denseInterval%2==0&&p.sparseInterval%2==0&&p.sparseInterval>=p.denseInterval&&
                            p.extraCreepSpeed>0&&p.extraCreepSpeed<=30&&p.creepRadius>0&&p.creepRadius<=10&&
                            p.creepDamage>0&&p.creepDamage<=1000&&p.fadeScale>0&&p.fadeScale<=1,"Invalid Brain creep");
                    }
                } else if(command=="spitty") {
                    require(!item&&!rule&&!graph&&!death,"spitty inside definition");
                    const auto id=parseMonsterId(word(row));SpittyDefinition p;
                    p.kind=named<SpittyKind>(word(row),{{"normal",SpittyKind::Normal},{"conjoined",SpittyKind::Conjoined},{"tainted",SpittyKind::Tainted}});
                    p.scale=real(row);p.force=real(row);p.retention=real(row);p.zRetention=real(row);p.contact=real(row);
                    p.chance=integer(row,1,1000000);p.attackFrames=integer(row,2,300);p.shootFrame=integer(row,1,p.attackFrames-1);
                    p.horizontalFrames=integer(row,2,300);p.verticalFrames=integer(row,2,300);
                    p.walkShootFrame=integer(row,0,std::min(p.horizontalFrames,p.verticalFrames)-1);
                    p.grid=real(row);p.arrival=real(row);p.stuckSpeed=real(row);
                    p.attempts=integer(row,1,20);p.maxCells=integer(row,1,20);p.stuckFrames=integer(row,1,120);
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.retention>0&&p.retention<1&&
                        p.zRetention>0&&p.zRetention<=1&&p.contact>0&&p.contact<=1000&&p.grid>0&&p.grid<=100&&
                        p.arrival>0&&p.arrival<=p.grid&&p.stuckSpeed>0&&p.stuckSpeed<=10,"Invalid Spitty movement");
                    require((p.kind==SpittyKind::Tainted)==(p.walkShootFrame>0),"Only Tainted Spitty has walking Shoot events");
                    require(lib->spitties_.emplace(id,p).second,"Duplicate Spitty controller");
                } else if(command=="spitty_flight") {
                    require(!item&&!rule&&!graph&&!death,"spitty_flight inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->spitties_.find(id);
                    require(it!=lib->spitties_.end(),"Spitty flight needs preceding controller");
                    const auto name=word(row);require(name=="shot"||name=="burst"||name=="death","Unknown Spitty flight role");
                    auto &p=name=="shot"?it->second.shot:name=="burst"?it->second.burst:it->second.death;
                    require(!p.configured,"Duplicate Spitty flight");
                    p.speed=real(row);p.height=real(row);p.upMin=real(row);p.upMax=real(row);p.gravity=real(row);
                    p.retention=real(row);p.radius=real(row);p.damage=real(row);p.life=real(row);
                    require(p.speed>0&&p.speed<=100&&p.height>0&&p.height<=10&&p.upMin>=-100&&p.upMax>=p.upMin&&p.upMax<=100&&
                        p.gravity>0&&p.gravity<=200&&p.retention>0&&p.retention<1&&p.radius>0&&p.radius<=2&&
                        p.damage>0&&p.damage<=1000&&p.life>0&&p.life<=30,"Invalid Spitty flight");p.configured=true;
                } else if(command=="spitty_stream"||command=="spitty_burst"||command=="spitty_death") {
                    require(!item&&!rule&&!graph&&!death,"Spitty extension inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->spitties_.find(id);
                    require(it!=lib->spitties_.end()&&it->second.kind==SpittyKind::Tainted,"Tainted extension needs preceding Tainted controller");
                    auto &p=it->second;
                    if(command=="spitty_stream") {
                        require(!p.streamConfigured,"Duplicate Spitty stream");p.streamCount=integer(row,2,32);
                        p.streamSize=real(row);p.streamSizeStep=real(row);p.streamAccelerationStep=real(row);
                        p.streamJitter=real(row);p.streamGravityStep=real(row);
                        require(p.streamSize>0&&p.streamSize<=4&&p.streamSizeStep>=0&&p.streamSize-p.streamSizeStep*float(p.streamCount-1)>.1f&&
                            p.streamAccelerationStep>=0&&1-p.streamAccelerationStep*float(p.streamCount-1)>.1f&&
                            p.streamJitter>=0&&p.streamJitter<=Pi/4&&std::abs(p.streamGravityStep)<=100,"Invalid Spitty stream");p.streamConfigured=true;
                    } else if(command=="spitty_burst") {
                        require(!p.burstConfigured,"Duplicate Spitty burst");p.burstMin=integer(row,1,32);p.burstMax=integer(row,p.burstMin,32);
                        p.burstSize=real(row);p.burstSizeToggle=real(row);p.burstSizeJitter=real(row);
                        require(p.burstSize>0&&p.burstSizeToggle>=0&&p.burstSizeJitter>=0&&
                            p.burstSize+p.burstSizeToggle+p.burstSizeJitter<=4,"Invalid Spitty burst");p.burstConfigured=true;
                    } else {
                        require(!p.deathConfigured,"Duplicate Spitty death");p.ringCount=integer(row,2,32);
                        p.deathSize=real(row);p.deathOffset=real(row);
                        require(p.deathSize>0&&p.deathSize<=4&&std::abs(p.deathOffset)<=Pi,"Invalid Spitty death");p.deathConfigured=true;
                    }
                } else if(command=="maw") {
                    require(!item&&!rule&&!graph&&!death,"maw inside definition");
                    const auto id=parseMonsterId(word(row));MawDefinition p;
                    p.scale=real(row);p.force=real(row);p.retention=real(row);p.contact=real(row);p.shoots=integer(row,0,1);
                    p.shot.checkFrames=integer(row,1,120);p.shot.cooldownFrames=integer(row,1,600);
                    p.shot.attackFrames=integer(row,2,300);p.shot.shootFrame=integer(row,1,p.shot.attackFrames-1);
                    p.shot.range=real(row);p.shot.speed=real(row);p.shot.damage=real(row);p.shot.life=real(row);p.shotRadius=real(row);
                    p.deathShots=integer(row,0,32);p.deathSpeed=real(row);p.deathDamage=real(row);
                    require(p.scale>0&&p.scale<=1&&p.force>0&&p.force<=10&&p.retention>0&&p.retention<1&&p.contact>0&&p.contact<=1000&&
                        p.shot.cooldownFrames>=p.shot.attackFrames&&p.shot.range>0&&p.shot.range<=100&&p.shot.speed>0&&p.shot.speed<=100&&
                        p.shot.damage>0&&p.shot.damage<=1000&&p.shot.life>0&&p.shot.life<=30&&p.shotRadius>0&&p.shotRadius<=2&&
                        p.deathSpeed>0&&p.deathSpeed<=100&&p.deathDamage>0&&p.deathDamage<=1000,"Invalid Maw profile");
                    require(lib->maws_.emplace(id,p).second,"Duplicate Maw profile");
                } else if(command=="maw_psychic") {
                    require(!item&&!rule&&!graph&&!death,"maw_psychic inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->maws_.find(id);
                    require(it!=lib->maws_.end()&&!it->second.homing,"Psychic profile needs preceding unique Maw");
                    auto &p=it->second;p.child=parseMonsterId(word(row));HostileHomingDefinition h;
                    h.range=real(row);h.acceleration=real(row);h.retention=real(row);h.prediction=real(row);
                    require(p.shoots&&p.child&&h.range>0&&h.range<=100&&h.acceleration>0&&h.acceleration<=100&&
                        h.retention>0&&h.retention<1&&h.prediction>=0&&h.prediction<=1,"Invalid Maw homing profile");p.homing=h;
                } else if(command=="eternal_fly") {
                    require(!item&&!rule&&!graph&&!death,"eternal_fly inside definition");
                    const auto id=parseMonsterId(word(row));EternalFlyDefinition p;p.released=parseMonsterId(word(row));
                    p.radiusX=real(row);p.radiusZ=real(row);p.phase=real(row);p.follow=real(row);
                    p.growthFrames=integer(row,1,600);p.healingFrames=integer(row,1,600);p.contact=real(row);
                    require(p.released&&p.radiusX>0&&p.radiusX<=20&&p.radiusZ>0&&p.radiusZ<=20&&p.phase>0&&p.phase<=Pi&&
                        p.follow>0&&p.follow<=1&&p.contact>0&&p.contact<=1000,"Invalid Eternal Fly profile");
                    require(lib->eternalFlies_.emplace(id,p).second,"Duplicate Eternal Fly profile");
                } else if(command=="status_effects") {
                    require(!item&&!rule&&!graph&&!death,"status_effects inside definition");
                    const auto id=parseMonsterId(word(row));EnemyStatusDefinition p;
                    p.capFrames=integer(row,1,18000);p.confusionRefreshFrames=integer(row,1,600);p.confusionRadius=real(row);
                    require(p.confusionRadius>0&&p.confusionRadius<=100,"Invalid confusion radius");
                    require(lib->enemyStatuses_.emplace(id,p).second,"Duplicate enemy status profile");
                } else if(command=="damage_status") {
                    require(!item&&!rule&&!graph&&!death,"damage_status inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->enemyStatuses_.find(id);const auto kind=word(row);
                    require(it!=lib->enemyStatuses_.end()&&(kind=="poison"||kind=="burn"),"Missing or invalid damage status profile");
                    auto &profile=kind=="poison"?it->second.poison:it->second.burn;
                    require(!profile,"Duplicate damage status profile");
                    DamageStatusDefinition p;p.capFrames=integer(row,1,18000);p.periodFrames=integer(row,1,600);
                    p.firstTick=integer(row,1,p.periodFrames);p.minimumDamage=real(row);
                    require(p.minimumDamage>0&&p.minimumDamage<=1000000,"Invalid minimum status damage");profile=p;
                } else if(command=="charm_effect") {
                    require(!item&&!rule&&!graph&&!death,"charm_effect inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->enemyStatuses_.find(id);
                    require(it!=lib->enemyStatuses_.end()&&!it->second.charm,"Missing or duplicate charm profile");
                    CharmDefinition p;p.targetFrames=integer(row,1,600);p.range=real(row);p.targetPenalty=real(row);
                    p.contactFrames=integer(row,1,600);p.healthScale=real(row);p.contactOffset=real(row);
                    p.contactDivisor=real(row);p.contactGain=real(row);p.projectileDamage=real(row);
                    require(p.range>0&&p.range<=10000&&p.targetPenalty>=0&&p.targetPenalty<=1000000&&
                        p.healthScale>0&&p.healthScale<=100&&p.contactDivisor>0&&p.contactDivisor<=10000&&
                        p.contactOffset>=p.contactDivisor&&p.contactOffset<=10000&&p.contactGain>0&&p.contactGain<=1000&&
                        p.projectileDamage>0&&p.projectileDamage<=1000000,"Invalid charm targeting or damage profile");
                    it->second.charm=p;
                } else if(command=="shrink_effect") {
                    require(!item&&!rule&&!graph&&!death,"shrink_effect inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->enemyStatuses_.find(id);
                    require(it!=lib->enemyStatuses_.end()&&!it->second.shrink,"Missing or duplicate shrink profile");
                    ShrinkDefinition p;p.capFrames=integer(row,1,18000);p.scale=real(row);p.approach=real(row);
                    require(p.scale>=.05f&&p.scale<1&&p.approach>0&&p.approach<=1,"Invalid shrink scale or approach");
                    it->second.shrink=p;
                } else if(command=="slow_effect") {
                    require(!item&&!rule&&!graph&&!death,"slow_effect inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->enemyStatuses_.find(id);
                    require(it!=lib->enemyStatuses_.end()&&!it->second.slow,"Missing or duplicate slow profile");
                    SlowDefinition p;p.timeScale=real(row);p.projectileTimeScale=real(row);p.refreshFrames=integer(row,1,600);
                    require(p.timeScale>=.05f&&p.timeScale<1&&p.projectileTimeScale>=.05f&&p.projectileTimeScale<1,"Invalid slow time scale");
                    it->second.slow=p;
                } else if(command=="freeze_effect") {
                    require(!item&&!rule&&!graph&&!death,"freeze_effect inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->enemyStatuses_.find(id);
                    require(it!=lib->enemyStatuses_.end()&&!it->second.freeze,"Missing or duplicate freeze profile");
                    FreezeDefinition p;p.capFrames=integer(row,1,18000);p.retention=real(row);
                    require(p.retention>0&&p.retention<1,"Invalid freeze retention");
                    it->second.freeze=p;
                } else if(command=="fear_motion") {
                    require(!item&&!rule&&!graph&&!death,"fear_motion inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->enemyStatuses_.find(id);
                    require(it!=lib->enemyStatuses_.end()&&!it->second.fear,"Missing or duplicate fear motion profile");
                    EvaderDefinition p;p.spawns=false;p.scale=real(row);p.visibleRange=real(row);p.hiddenRange=real(row);
                    p.proximityFrames=integer(row,1,600);p.evadeChecks=integer(row,1,30);
                    p.retention=real(row);p.wanderForce=real(row);p.wanderRetention=real(row);p.pathForce=real(row);
                    const float alert=real(row);
                    require(p.scale>0&&p.scale<=1&&p.visibleRange>0&&p.visibleRange<=100&&p.hiddenRange>0&&p.hiddenRange<=100&&
                        p.retention>0&&p.retention<=1&&p.wanderForce>0&&p.wanderForce<=10&&p.wanderRetention>0&&p.wanderRetention<=1&&
                        p.pathForce>0&&p.pathForce<=10&&alert>0&&alert<=1,"Invalid fear motion");
                    it->second.fear=p;it->second.fearAlertRetention=alert;
                } else if(command=="head_shooter") {
                    require(!item&&!rule&&!graph&&!death,"head_shooter inside definition");
                    const auto id=parseMonsterId(word(row));HeadShooterDefinition p;
                    p.checkFrames=integer(row,1,120);p.cooldownFrames=integer(row,1,600);
                    p.attackFrames=integer(row,2,300);p.shootFrame=integer(row,1,p.attackFrames-1);
                    p.range=real(row);p.speed=real(row);p.damage=real(row);p.life=real(row);
                    require(p.cooldownFrames>=p.attackFrames&&p.range>0&&p.range<=100&&p.speed>0&&p.speed<=100&&
                        p.damage>0&&p.damage<=1000&&p.life>0&&p.life<=30,"Invalid stationary shooter profile");
                    require(lib->headShooters_.emplace(id,p).second,"Duplicate stationary shooter");
                } else if(command=="head_shooter_body") {
                    require(!item&&!rule&&!graph&&!death,"head_shooter_body inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->headShooters_.find(id);
                    require(it!=lib->headShooters_.end()&&it->second.bodyRetention==0,"Missing or duplicate stationary shooter body");
                    const float retention=real(row);
                    require(retention>0&&retention<1,"Invalid stationary shooter body retention");
                    it->second.bodyRetention=retention;
                } else if(command=="head_shooter_flight") {
                    require(!item&&!rule&&!graph&&!death,"head_shooter_flight inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->headShooters_.find(id);
                    require(it!=lib->headShooters_.end()&&it->second.shotRetention==0,"Missing or duplicate stationary shooter flight");
                    auto &p=it->second;p.shotHeight=real(row);p.shotUp=real(row);p.shotGravity=real(row);
                    p.shotRetention=real(row);p.shotRadius=real(row);
                    require(p.shotHeight>0&&p.shotHeight<=10&&std::abs(p.shotUp)<=100&&p.shotGravity>0&&p.shotGravity<=100&&
                        p.shotRetention>0&&p.shotRetention<=1&&p.shotRadius>0&&p.shotRadius<=1,"Invalid stationary shooter flight");
                } else if(command=="host") {
                    require(!item&&!rule&&!graph&&!death,"host inside definition");
                    const auto id=parseMonsterId(word(row));HostDefinition p;const auto motion=word(row);
                    require(motion=="still"||motion=="walk"||motion=="float","Invalid Host movement");
                    p.motion=motion=="walk"?HostMotion::Walk:motion=="float"?HostMotion::Float:HostMotion::Still;
                    p.armored=integer(row,0,1);p.frames=integer(row,3,300);p.openFrame=integer(row,1,p.frames-2);
                    p.shootFrame=integer(row,p.openFrame,p.frames-2);p.closeFrame=integer(row,p.shootFrame,p.frames-1);
                    p.checkFrames=integer(row,1,120);p.cooldown=integer(row,1,600);p.chance=integer(row,1,100);p.delayLimit=integer(row,1,100);
                    p.range=real(row);p.speed=real(row);p.inheritVelocity=real(row);p.damage=real(row);p.life=real(row);p.contact=real(row);p.healthScale=real(row);
                    p.scale=real(row);p.force=real(row);p.retention=real(row);p.attackRetention=real(row);
                    require(p.range>0&&p.range<=100&&p.speed>0&&p.speed<=100&&p.damage>0&&p.damage<=1000&&
                        p.inheritVelocity>=0&&p.inheritVelocity<=2&&p.life>0&&p.life<=30&&p.contact>=0&&p.contact<=1000&&p.healthScale>0&&p.healthScale<=100&&
                        p.scale>0&&p.scale<=1&&p.force>=0&&p.force<=10&&p.retention>0&&p.retention<1&&
                        p.attackRetention>0&&p.attackRetention<1,"Invalid Host profile");
                    const int count=integer(row,0,16);
                    for(int n=0;n<count;++n){Vector2 v{real(row),real(row)};require(v.x>0&&v.x<=2&&std::abs(v.y)<=2,"Invalid Host volley");p.volley.push_back(v);}
                    require(lib->hosts_.emplace(id,p).second,"Duplicate Host profile");
                } else if(command=="mushroom") {
                    require(!item&&!rule&&!graph&&!death,"mushroom inside definition");
                    const auto id=parseMonsterId(word(row));MushroomDefinition p;
                    p.hideFrames=integer(row,1,120);p.revealFrames=integer(row,2,120);p.shootFrame=integer(row,1,p.revealFrames-1);
                    p.timerQuantum=integer(row,1,300);p.blockingChoices=integer(row,1,20);p.revealedChoices=integer(row,1,20);
                    p.closedDamageScale=real(row);p.speed=real(row);p.diagonal=real(row);p.damage=real(row);p.life=real(row);p.contact=real(row);
                    require(p.closedDamageScale>0&&p.closedDamageScale<=1&&p.speed>0&&p.speed<=100&&
                        p.diagonal>0&&p.diagonal<=1&&p.damage>0&&p.damage<=1000&&p.life>0&&p.life<=30&&p.contact>=0&&p.contact<=1000,
                        "Invalid Mushroom profile");
                    require(lib->mushrooms_.emplace(id,p).second,"Duplicate Mushroom profile");
                } else if(command=="host_slam") {
                    require(!item&&!rule&&!graph&&!death,"host_slam inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->hosts_.find(id);
                    require(it!=lib->hosts_.end()&&!it->second.slam,"Slam needs preceding unique Host");
                    HostSlamDefinition p;auto &w=p.wave;
                    w.stepFrames=integer(row,1,60);w.lifeFrames=integer(row,w.stepFrames,1800);
                    w.jitterStart=integer(row,0,w.lifeFrames);w.jitterRamp=integer(row,1,600);
                    w.spacing=real(row);w.radius=real(row);w.monsterDamage=real(row);w.playerDamage=real(row);
                    w.jitterDegrees=real(row);w.visualRadius=real(row);
                    p.offset=real(row);p.range=real(row);p.push=real(row);p.hop=real(row);p.gravity=real(row);p.retention=real(row);
                    require(w.spacing>0&&w.spacing<=10&&w.radius>0&&w.radius<=10&&w.monsterDamage>0&&w.monsterDamage<=1000&&
                        w.playerDamage>0&&w.playerDamage<=1000&&w.jitterDegrees>=0&&w.jitterDegrees<=180&&w.visualRadius>0&&w.visualRadius<=w.radius&&
                        p.offset>=0&&p.offset<=10&&p.range>0&&p.range<=100&&p.push>=0&&p.push<=100&&p.hop>0&&p.hop<=100&&
                        p.gravity>0&&p.gravity<=500&&p.retention>0&&p.retention<1,"Invalid Host slam");it->second.slam=p;
                } else if(command=="source_immunity") {
                    require(!item&&!rule&&!graph&&!death,"source_immunity inside definition");
                    const auto id=parseMonsterId(word(row));SourceImmunityDefinition p;
                    p.flame=integer(row,0,1);p.explosion=integer(row,0,1);
                    require(p.flame||p.explosion,"Source immunity must specify a damage channel");
                    require(lib->sourceImmunities_.emplace(id,p).second,"Duplicate source immunity");
                } else if(command=="lethal_morph") {
                    require(!item&&!rule&&!graph&&!death,"lethal_morph inside definition");
                    const auto id=parseMonsterId(word(row));LethalMorphDefinition p;
                    p.target=parseMonsterId(word(row));p.chance=integer(row,0,10000);
                    p.overkill=real(row);p.delayMin=real(row);p.delayMax=real(row);
                    require(p.overkill>0&&p.overkill<=3200&&p.delayMin>=0&&p.delayMax>=p.delayMin&&p.delayMax<=10,"Invalid lethal morph values");
                    require(lib->lethalMorphs_.emplace(id,p).second,"Duplicate lethal morph");
                } else if(command=="lethal_morph_roll") {
                    require(!item&&!rule&&!graph&&!death,"lethal_morph_roll inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->lethalMorphs_.find(id);
                    require(it!=lib->lethalMorphs_.end()&&!it->second.explicitRoll,"Morph roll needs one preceding lethal morph");
                    auto &p=it->second;p.chance=integer(row,0,10000);p.chanceOutOf=integer(row,1,10000);
                    require(p.chance<=p.chanceOutOf,"Morph numerator exceeds denominator");p.explicitRoll=true;
                } else if(command=="lethal_morph_choice") {
                    require(!item&&!rule&&!graph&&!death,"lethal_morph_choice inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->lethalMorphs_.find(id);
                    require(it!=lib->lethalMorphs_.end()&&it->second.choices.size()<8,"Morph choice needs a preceding morph and bounded choices");
                    const auto target=parseMonsterId(word(row));const int weight=integer(row,1,8000);
                    auto &choices=it->second.choices;
                    require(std::none_of(choices.begin(),choices.end(),[&](const auto &x){return x.first==target;}),"Duplicate morph choice");
                    choices.emplace_back(target,weight);
                } else if(command=="death_blast"||command=="death_payload") {
                    require(!item&&!rule&&!graph&&!death,"death_blast inside definition");
                    const auto id=parseMonsterId(word(row));DeathBlastDefinition p;
                    p.damage=real(row);p.playerDamage=real(row);p.radius=real(row);
                    require(p.damage>0&&p.damage<=3200&&p.playerDamage>0&&p.playerDamage<=1000&&p.radius>0&&p.radius<=30,"Invalid death blast");
                    if(command=="death_payload") {
                        const auto trigger=word(row);require(trigger=="always"||trigger=="self","Invalid death blast trigger");p.onlySelf=trigger=="self";
                        p.shots=integer(row,0,32);p.selfShots=integer(row,0,32);p.angle=real(row);p.shotSpeed=real(row);p.shotDamage=real(row);p.bomb=word(row);
                        if(p.bomb=="-")p.bomb.clear();
                        require(std::abs(p.angle)<=2*Pi&&p.shotSpeed>0&&p.shotSpeed<=100&&p.shotDamage>0&&p.shotDamage<=1000,"Invalid death volley");
                    }
                    require(lib->deathBlasts_.emplace(id,p).second,"Duplicate death blast");
                } else if(command=="death_cross") {
                    require(!item&&!rule&&!graph&&!death,"death_cross inside definition");
                    const auto id=parseMonsterId(word(row));DeathCrossDefinition p;
                    p.angle=real(row);p.speed=real(row);p.damage=real(row);p.creepRadius=real(row);p.creepDuration=real(row);p.creepDamage=real(row);
                    require(std::abs(p.angle)<=2*Pi&&p.speed>0&&p.speed<=50&&p.damage>0&&p.damage<=1000&&
                        p.creepRadius>=0&&p.creepRadius<=10&&p.creepDuration>=0&&p.creepDuration<=60&&p.creepDamage>=0&&p.creepDamage<=1000&&
                        ((p.creepRadius==0)==(p.creepDuration==0)),"Invalid death cross");
                    require(lib->deathCrosses_.emplace(id,p).second,"Duplicate death cross");
                } else if(command=="rail_layout") {
                    require(!item&&!rule&&!graph&&!death,"rail_layout inside definition");
                    RailLayout layout;layout.key=word(row);layout.width=integer(row,2,52);layout.height=integer(row,2,52);
                    require(!layout.key.empty()&&layout.key.size()<=64&&lib->railLayouts_.size()<64,"Invalid rail layout key or capacity");
                    require(lib->railLayouts_.emplace(layout.key,layout).second,"Duplicate rail layout");
                } else if(command=="rail_cell") {
                    require(!item&&!rule&&!graph&&!death,"rail_cell inside definition");
                    const auto key=word(row);auto it=lib->railLayouts_.find(key);
                    require(it!=lib->railLayouts_.end()&&it->second.cells.size()<2704,"Rail cell needs a preceding bounded layout");
                    RailCell cell;cell.x=integer(row,0,51);cell.z=integer(row,0,51);cell.variant=integer(row,0,10);cell.overPit=flag(row);
                    it->second.cells.push_back(cell);
                } else if(command=="rail_closed_entrances") {
                    require(!item&&!rule&&!graph&&!death,"Rail entrance mask inside definition");
                    auto it=lib->railLayouts_.find(word(row));require(it!=lib->railLayouts_.end(),"Rail entrance mask needs layout");
                    it->second.closedEntrances=unsigned(integer(row,0,15));
                } else if(command=="rail_pit"||command=="rail_rock") {
                    require(!item&&!rule&&!graph&&!death,"Rail terrain inside definition");
                    const auto key=word(row);auto it=lib->railLayouts_.find(key);
                    require(it!=lib->railLayouts_.end(),"Rail terrain needs a preceding layout");
                    const int x=integer(row,0,51),z=integer(row,0,51);
                    auto &cells=command=="rail_pit"?it->second.pitCells:it->second.rockCells;
                    require(cells.size()<2704,"Too many rail terrain cells");cells.emplace_back(x,z);
                } else if(command=="environment_actor") {
                    require(!item&&!rule&&!graph&&!death,"environment_actor inside definition");
                    const auto id=parseMonsterId(word(row));EnvironmentActorDefinition p;
                    p.kind=named<EnvironmentActorKind>(word(row),{{"fireplace",EnvironmentActorKind::Fireplace},{"tnt",EnvironmentActorKind::Tnt},{"hot_coal",EnvironmentActorKind::HotCoal}});
                    p.damageScale=real(row);p.contact=real(row);p.contactInterval=real(row);
                    p.blastDamage=real(row);p.blastRadius=real(row);p.blastPlayerDamage=real(row);
                    p.pushSpeed=real(row);p.pushRetention=real(row);
                    require(p.damageScale>0&&p.damageScale<=100&&p.contact>=0&&p.contact<=1000&&p.contactInterval>=Tick&&p.contactInterval<=10&&
                        p.blastDamage>0&&p.blastDamage<=10000&&p.blastRadius>0&&p.blastRadius<=30&&p.blastPlayerDamage>=0&&p.blastPlayerDamage<=1000&&
                        p.pushSpeed>0&&p.pushSpeed<=30&&p.pushRetention>=0&&p.pushRetention<1,"Invalid environment actor values");
                    require(lib->environmentActors_.emplace(id,p).second,"Duplicate environment actor");
                } else if(command=="rail_traffic") {
                    require(!item&&!rule&&!graph&&!death,"rail_traffic inside definition");
                    const auto id=parseMonsterId(word(row));RailTrafficDefinition p;p.enabled=flag(row);
                    p.initialMin=integer(row,1,36000);p.initialMax=integer(row,p.initialMin,36000);
                    p.largeArea=integer(row,1,4096);p.largeDivisor=integer(row,1,p.initialMin);
                    p.tickRate=real(row);p.speed=real(row);p.doorTime=real(row);
                    require(p.tickRate>=1&&p.tickRate<=120&&p.speed>0&&p.speed<=60&&p.doorTime>=Tick&&p.doorTime<=5,"Invalid rail traffic values");
                    require(lib->railTraffic_.emplace(id,p).second,"Duplicate rail traffic controller");
                } else if(command=="rail_passenger") {
                    require(!item&&!rule&&!graph&&!death,"rail_passenger inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->railTraffic_.find(id);
                    require(it!=lib->railTraffic_.end(),"Passenger requires rail traffic controller");
                    const auto actor=parseMonsterId(word(row));const auto state=word(row);
                    require(state=="available"||state=="pending","Invalid passenger availability");
                    require(it->second.passengers.size()<32&&std::none_of(it->second.passengers.begin(),it->second.passengers.end(),[&](const auto &p){return p.actor==actor;}),"Duplicate/too many rail passengers");
                    it->second.passengers.push_back({actor,state=="available"});
                } else if(command=="boss_hornfel") {
                    require(!item&&!rule&&!graph&&!death,"boss_hornfel inside definition");
                    const auto id=parseMonsterId(word(row));HornfelDefinition p;
                    p.speed=real(row);p.fleeSpeed=real(row);p.fleeHealth=real(row);p.contact=real(row);p.fleeContact=real(row);
                    p.outside=real(row);p.doorTime=real(row);p.attackDelay=real(row);
                    for(auto &w:p.attacks)w=integer(row,0,10000);
                    for(auto &w:p.bombs)w=integer(row,0,10000);
                    require(p.speed>0&&p.speed<=100&&p.fleeSpeed>0&&p.fleeSpeed<=20&&p.fleeHealth>0&&p.fleeHealth<=10000&&
                        p.contact>0&&p.contact<=1000&&p.fleeContact>0&&p.fleeContact<=1000&&p.outside>=Tick&&p.outside<=10&&
                        p.doorTime>=Tick&&p.doorTime<=3&&p.attackDelay>=Tick&&p.attackDelay<=10&&
                        std::any_of(p.attacks.begin(),p.attacks.end(),[](int w){return w>0;})&&
                        std::any_of(p.bombs.begin(),p.bombs.end(),[](int w){return w>0;}),"Invalid Hornfel controller");
                    require(lib->hornfels_.emplace(id,p).second,"Duplicate Hornfel controller");
                } else if(command=="hornfel_charge") {
                    require(!item&&!rule&&!graph&&!death,"hornfel_charge inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->hornfels_.find(id);
                    require(it!=lib->hornfels_.end()&&!it->second.chargeConfigured,"Missing/duplicate Hornfel charge controller");
                    auto &p=it->second;p.chargeChance=integer(row,0,10000);p.chargeCooldown=real(row);
                    p.repeatMin=integer(row,0,16);p.repeatMax=integer(row,p.repeatMin,16);
                    p.nativeScale=real(row);p.driveForce=real(row);p.retention=real(row);
                    p.driveStart=real(row);p.driveIncrement=real(row);p.driveMax=real(row);p.nativeTravelCap=real(row);
                    p.bombInterval=real(row);p.bombScatter=real(row);p.mineCooldown=real(row);
                    require(p.chargeCooldown>0&&p.chargeCooldown<=120&&p.nativeScale>0&&p.nativeScale<=1&&
                        p.driveForce>0&&p.driveForce<=10&&p.retention>0&&p.retention<1&&p.driveStart>0&&
                        p.driveIncrement>0&&p.driveIncrement<=10&&p.driveMax>=p.driveStart&&p.driveMax<=100&&
                        p.nativeTravelCap>0&&p.nativeTravelCap<=100&&p.bombInterval>=Tick&&p.bombInterval<=10&&
                        p.bombScatter>=0&&p.bombScatter<=10&&p.mineCooldown>0&&p.mineCooldown<=120,"Invalid Hornfel charge values");
                    p.chargeConfigured=true;
                } else if(command=="hornfel_recovery") {
                    require(!item&&!rule&&!graph&&!death,"hornfel_recovery inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->hornfels_.find(id);
                    require(it!=lib->hornfels_.end()&&!it->second.recoveryConfigured,"Missing/duplicate Hornfel recovery controller");
                    auto &p=it->second;p.recoveryEntryDrive=real(row);p.recoveryDeceleration=real(row);p.recoveryFloor=real(row);
                    p.recoveryAcceleration=real(row);p.recoveryDrive=real(row);p.recoveryDelay=real(row);
                    p.recoveryFlight=real(row);p.recoveryGravity=real(row);p.recoveryPrediction=real(row);p.recoveryDamage=real(row);
                    auto &w=p.fireWave;w.speed=real(row);w.range=real(row);w.radius=real(row);w.trailDuration=real(row);w.damage=real(row);
                    require(p.recoveryFloor>0&&p.recoveryFloor<=p.recoveryDrive&&p.recoveryDrive<=p.recoveryEntryDrive&&p.recoveryEntryDrive<=100&&
                        p.recoveryDeceleration>0&&p.recoveryDeceleration<=10&&p.recoveryAcceleration>0&&p.recoveryAcceleration<=10&&
                        p.recoveryDelay>=Tick&&p.recoveryDelay<=3&&p.recoveryFlight>=Tick&&p.recoveryFlight<=5&&
                        p.recoveryGravity>0&&p.recoveryGravity<=100&&p.recoveryPrediction>=0&&p.recoveryPrediction<=2&&
                        p.recoveryDamage>0&&p.recoveryDamage<=1000&&w.speed>0&&w.speed<=50&&w.range>0&&w.range<=50&&
                        w.radius>0&&w.radius<=3&&w.trailDuration>=Tick&&w.trailDuration<=20&&w.damage>0&&w.damage<=1000,"Invalid Hornfel recovery values");
                    p.recoveryConfigured=true;
                } else if(command=="hornfel_escort") {
                    require(!item&&!rule&&!graph&&!death,"hornfel_escort inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->hornfels_.find(id);
                    require(it!=lib->hornfels_.end()&&!it->second.escort,"Missing/duplicate Hornfel escort controller");
                    auto &p=it->second;p.escort=parseMonsterId(word(row));p.escortChance=integer(row,0,10000);
                    p.escortCount=integer(row,1,8);p.escortLimit=integer(row,1,32);
                    p.escortClearance=real(row);p.escortRadius=real(row);p.escortSpread=real(row);p.escortReleaseHp=real(row);
                    require(p.escortClearance>=0&&p.escortClearance<=100&&p.escortRadius>0&&p.escortRadius<=5&&
                        p.escortSpread>=0&&p.escortSpread<=90&&p.escortReleaseHp>0&&p.escortReleaseHp<=1000,"Invalid Hornfel escort values");
                } else if(command=="hornfel_decoy") {
                    require(!item&&!rule&&!graph&&!death,"hornfel_decoy inside definition");
                    const auto id=parseMonsterId(word(row));HornfelDecoyDefinition p;p.owner=parseMonsterId(word(row));
                    p.chance=integer(row,0,10000);p.smallCount=integer(row,1,8);p.largeCount=integer(row,p.smallCount,8);
                    p.cooldown=real(row);p.startDelay=real(row);p.speed=real(row);p.contact=real(row);p.damageScale=real(row);
                    p.blastDamage=real(row);p.blastRadius=real(row);p.playerDamage=real(row);
                    p.bombCount=integer(row,1,16);p.bombSpeedMin=real(row);p.bombSpeedMax=real(row);p.bomb=word(row);
                    require(p.cooldown>=Tick&&p.cooldown<=120&&p.startDelay>=0&&p.startDelay<=60&&p.speed>0&&p.speed<=100&&
                        p.contact>0&&p.contact<=1000&&p.damageScale>0&&p.damageScale<=100&&p.blastDamage>0&&p.blastDamage<=10000&&
                        p.blastRadius>0&&p.blastRadius<=30&&p.playerDamage>0&&p.playerDamage<=1000&&
                        p.bombSpeedMin>=0&&p.bombSpeedMax>=p.bombSpeedMin&&p.bombSpeedMax<=100,"Invalid Hornfel decoy values");
                    require(lib->hornfelDecoys_.emplace(id,p).second,"Duplicate Hornfel decoy");
                } else if(command=="hornfel_layout") {
                    require(!item&&!rule&&!graph&&!death,"hornfel_layout inside definition");
                    const auto id=parseMonsterId(word(row));auto it=lib->hornfels_.find(id);
                    require(it!=lib->hornfels_.end(),"Hornfel layout requires controller");
                    auto key=word(row);int weight=integer(row,1,10000);
                    require(it->second.layouts.size()<32&&std::none_of(it->second.layouts.begin(),it->second.layouts.end(),[&](const auto &x){return x.first==key;}),"Duplicate/too many Hornfel layouts");
                    it->second.layouts.emplace_back(key,weight);
                } else if(command=="boss_loki") {
                    require(!item&&!rule&&!graph&&!death,"boss_loki inside definition");
                    const auto id=parseMonsterId(word(row));LokiDefinition p;
                    p.child=parseMonsterId(word(row));p.bodies=integer(row,1,2);p.childLimit=integer(row,1,16);
                    p.shotSpeed=real(row);p.shotDamage=real(row);p.contactDamage=real(row);p.volleyInterval=real(row);
                    p.vanish=real(row);p.reappear=real(row);p.teleportClearance=real(row);p.initialDelay=real(row);
                    for(auto &weight:p.weights)weight=integer(row,0,10000);
                    require(p.shotSpeed>0&&p.shotSpeed<=50&&p.shotDamage>0&&p.shotDamage<=1000&&p.contactDamage>0&&p.contactDamage<=1000&&
                        p.volleyInterval>=Tick&&p.volleyInterval<=5&&p.vanish>=Tick&&p.vanish<=5&&p.reappear>=Tick&&p.reappear<=5&&
                        p.teleportClearance>=2&&p.teleportClearance<=20&&p.initialDelay>=Tick&&p.initialDelay<=10&&
                        std::any_of(p.weights.begin(),p.weights.end(),[](int w){return w>0;}),"Invalid Loki controller values");
                    require(lib->lokis_.emplace(id,p).second,"Duplicate Loki controller");
                } else if(command=="boss_peep") {
                    require(!item&&!rule&&!graph&&!death,"boss_peep inside definition");
                    const auto id=parseMonsterId(word(row));PeepDefinition p;p.eye=parseMonsterId(word(row));
                    p.flight=real(row);p.distance=real(row);p.height=real(row);p.maximumHeight=real(row);
                    p.creepRadius=real(row);p.creepDuration=real(row);p.shotSpeed=real(row);p.shotDamage=real(row);p.contactDamage=real(row);
                    p.yellowScale=real(row);p.yellowSpeed=real(row);p.trailInterval=real(row);p.trailRadius=real(row);
                    for(auto &weight:p.weights)weight=integer(row,0,10000);
                    require(p.flight>=Tick&&p.flight<=5&&p.distance>0&&p.distance<=20&&p.height>0&&p.maximumHeight>=p.height&&p.maximumHeight<=20&&
                        p.creepRadius>0&&p.creepRadius<=10&&p.creepDuration>0&&p.creepDuration<=60&&p.shotSpeed>0&&p.shotSpeed<=50&&p.shotDamage>0&&p.contactDamage>0&&
                        p.yellowScale>=.25f&&p.yellowScale<=1&&p.yellowSpeed>=1&&p.yellowSpeed<=4&&p.trailInterval>=.1f&&p.trailRadius>0&&p.trailRadius<=5&&
                        std::any_of(p.weights.begin(),p.weights.end(),[](int w){return w>0;}),"Invalid Peep controller values");
                    require(lib->peeps_.emplace(id,p).second,"Duplicate boss controller");
                } else if(command=="boss_bloat") {
                    require(!item&&!rule&&!graph&&!death,"boss_bloat inside definition");
                    const auto id=parseMonsterId(word(row));BloatDefinition p;
                    p.eye=parseMonsterId(word(row));p.charger=parseMonsterId(word(row));
                    p.flight=real(row);p.distance=real(row);p.height=real(row);p.maximumHeight=real(row);
                    p.shortFlight=real(row);p.shortHeight=real(row);p.creepRadius=real(row);p.creepDuration=real(row);
                    p.landingRadius=real(row);p.shotSpeed=real(row);p.shotDamage=real(row);p.contactDamage=real(row);
                    for(auto &weight:p.weights)weight=integer(row,0,10000);
                    require(p.flight>=Tick&&p.flight<=5&&p.distance>0&&p.distance<=20&&p.height>0&&p.maximumHeight>=p.height&&p.maximumHeight<=20&&
                        p.shortFlight>=Tick&&p.shortFlight<=2&&p.shortHeight>0&&p.shortHeight<=p.height&&p.creepRadius>0&&p.creepRadius<=10&&
                        p.creepDuration>0&&p.creepDuration<=60&&p.landingRadius>0&&p.landingRadius<=5&&p.shotSpeed>0&&p.shotSpeed<=50&&
                        p.shotDamage>0&&p.shotDamage<=1000&&p.contactDamage>0&&p.contactDamage<=1000&&
                        std::any_of(p.weights.begin(),p.weights.end(),[](int w){return w>0;}),"Invalid Bloat controller values");
                    require(lib->bloats_.emplace(id,p).second,"Duplicate Bloat controller");
                } else if(command=="boss_lasers"||command=="boss_ipecac") {
                    require(!item&&!rule&&!graph&&!death,"boss attack inside definition");const auto id=parseMonsterId(word(row));
                    auto it=lib->bloats_.find(id);require(it!=lib->bloats_.end(),"Boss attack requires a preceding Bloat controller");auto &p=it->second;
                    if(command=="boss_lasers") {
                        require(lib->bloatLasers_.insert(id).second,"Duplicate boss laser configuration");
                        p.beamRange=real(row);p.beamRadius=real(row);p.beamDuration=real(row);p.beamCooldown=real(row);p.beamAlignment=real(row);p.beamDamage=real(row);
                        require(p.beamRange>0&&p.beamRange<=100&&p.beamRadius>0&&p.beamRadius<=2&&p.beamDuration>=Tick&&p.beamDuration<=5&&
                            p.beamCooldown>=p.beamDuration&&p.beamCooldown<=10&&p.beamAlignment>0&&p.beamAlignment<=3&&p.beamDamage>0&&p.beamDamage<=1000,"Invalid boss laser values");
                    } else {
                        require(lib->bloatIpecac_.insert(id).second,"Duplicate boss Ipecac configuration");
                        p.lobFlight=real(row);p.gravity=real(row);p.lobSpread=real(row);p.blastRadius=real(row);p.blastDamage=real(row);p.summonLimit=integer(row,2,64);
                        require(p.lobFlight>=.2f&&p.lobFlight<=4&&p.gravity>0&&p.gravity<=50&&p.lobSpread>=0&&p.lobSpread<=10&&p.blastRadius>0&&p.blastRadius<=10&&
                            p.blastDamage>0&&p.blastDamage<=1000,"Invalid boss Ipecac values");
                    }
                } else if(command=="charge") {
                    require(!item&&!rule&&!graph&&!death,"charge inside definition");const auto id=parseMonsterId(word(row));ChargeDefinition c;
                    c.speed=real(row);c.duration=real(row);c.alignment=real(row);c.recovery=real(row);c.wanderMin=real(row);c.wanderMax=real(row);
                    require(c.speed>0&&c.speed<=50&&c.duration>=Tick&&c.duration<=10&&c.alignment>0&&c.alignment<=3&&c.recovery>=Tick&&c.recovery<=10&&
                        c.wanderMin>=Tick&&c.wanderMax>=c.wanderMin&&c.wanderMax<=10,"Invalid charge controller values");
                    require(lib->charges_.emplace(id,c).second,"Duplicate charge controller");
                } else if(command=="charge_mode"||command=="charge_trail"||command=="charge_tail"||command=="charge_death") {
                    require(!item&&!rule&&!graph&&!death,"charge extension inside definition");const auto id=parseMonsterId(word(row));
                    auto it=lib->charges_.find(id);require(it!=lib->charges_.end(),"Charge extension requires a preceding charge controller");auto &c=it->second;
                    if(command=="charge_mode") {
                        require(!c.modeConfigured,"Duplicate charge mode");c.modeConfigured=true;
                        c.diagonal=named<bool>(word(row),{{"cardinal",false},{"diagonal",true}});
                        c.reflect=named<bool>(word(row),{{"stop",false},{"reflect",true}});
                        c.turnRate=real(row);c.pause=real(row);c.contactDamage=real(row);
                        require(c.turnRate>=0&&c.turnRate<=8&&c.pause>=0&&c.pause<=c.recovery&&c.contactDamage>=0&&c.contactDamage<=1000,"Invalid charge mode values");
                    } else if(command=="charge_trail") {
                        require(!c.trailConfigured,"Duplicate charge trail");c.trailConfigured=true;
                        c.trailInterval=real(row);c.trailRadius=real(row);c.trailDuration=real(row);
                        require(c.trailInterval>=Tick&&c.trailInterval<=5&&c.trailRadius>0&&c.trailRadius<=3&&c.trailDuration>=Tick&&c.trailDuration<=30,"Invalid charge trail values");
                    } else if(command=="charge_tail") {
                        require(!c.tailConfigured,"Duplicate charge tail");c.tailConfigured=true;
                        c.tailOffset=real(row);c.tailRadius=real(row);
                        require(c.tailOffset>=.4f&&c.tailRadius>0&&c.tailRadius<=.5f&&c.tailOffset+c.tailRadius<=1.001f,"Invalid tail navigation hull");
                    } else {
                        require(!c.deathConfigured,"Duplicate charge death volley");c.deathConfigured=true;
                        c.deathShots=integer(row,1,32);c.deathAngle=real(row)*Pi/180;c.deathSpeed=real(row);c.deathDamage=real(row);
                        require(c.deathSpeed>0&&c.deathSpeed<=50&&c.deathDamage>0&&c.deathDamage<=1000,"Invalid charge death volley values");
                    }
                } else if(command=="statue") {
                    require(!item&&!rule&&!graph&&!death,"statue inside definition");
                    const auto id=parseMonsterId(word(row));StatueDefinition s;
                    s.attack=named<StatueAttack>(word(row),{{"aimed",StatueAttack::Aimed},{"triple",StatueAttack::Triple},{"lob",StatueAttack::Lob},{"fixed",StatueAttack::Fixed},{"cross",StatueAttack::Cross},{"beam",StatueAttack::Beam},{"rotating_beam",StatueAttack::RotatingBeam},{"attraction",StatueAttack::Attraction},{"quake",StatueAttack::Quake},{"supply",StatueAttack::Supply}});
                    s.clear=named<StatueClear>(word(row),{{"combat",StatueClear::Combat},{"plates",StatueClear::Plates},{"never",StatueClear::Never}});
                    s.interval=real(row);s.windup=real(row);s.damage=real(row);s.speed=real(row);s.spread=real(row);
                    s.range=real(row);s.beamRadius=real(row);s.beamDuration=real(row);s.turnRate=real(row);s.angle=real(row);
                    s.removeOnReentry=integer(row,0,1)!=0;
                    require(s.interval>=Tick&&s.interval<=30&&s.windup>=0&&s.windup<=5&&s.damage>0&&s.damage<=1000&&s.speed>0&&s.speed<=50&&
                        s.spread>=0&&s.spread<=Pi/2&&s.range>=1&&s.range<=100&&s.beamRadius>0&&s.beamRadius<=3&&s.beamDuration>=Tick&&s.beamDuration<=5&&
                        std::abs(s.turnRate)<=8&&std::abs(s.angle)<=2*Pi,"Invalid statue values");
                    require(lib->statues_.emplace(id,s).second,"Duplicate statue controller");
                } else if(command=="statue_lob") {
                    require(!item&&!rule&&!graph&&!death,"statue_lob inside definition");const auto id=parseMonsterId(word(row));
                    auto it=lib->statues_.find(id);require(it!=lib->statues_.end()&&it->second.attack==StatueAttack::Lob,"Statue lob requires a preceding lob controller");
                    auto &s=it->second;require(!s.lobConfigured,"Duplicate statue lob");s.lobConfigured=true;
                    s.lobFlight=real(row);s.gravity=real(row);s.blastRadius=real(row);s.blastDamage=real(row);
                    require(s.lobFlight>=.1f&&s.lobFlight<=5&&s.gravity>0&&s.gravity<=100&&s.blastRadius>0&&s.blastRadius<=10&&s.blastDamage>0&&s.blastDamage<=1000,"Invalid statue lob values");
                } else if(command=="statue_attraction") {
                    require(!item&&!rule&&!graph&&!death,"statue_attraction inside definition");const auto id=parseMonsterId(word(row));
                    auto it=lib->statues_.find(id);require(it!=lib->statues_.end()&&it->second.attack==StatueAttack::Attraction,"Statue attraction requires a preceding attraction controller");
                    auto &s=it->second;require(!s.attractionConfigured,"Duplicate statue attraction");s.attractionConfigured=true;
                    s.playerPull=real(row);s.projectilePull=real(row);s.projectileLimit=real(row);s.pullHeight=real(row);
                    s.activeSeconds=real(row);s.inactiveSeconds=real(row);
                    require(s.playerPull>0&&s.playerPull<=5&&s.projectilePull>0&&s.projectilePull<=100&&s.projectileLimit>=1&&s.projectileLimit<=100&&s.pullHeight>0&&s.pullHeight<=20&&
                        ((s.activeSeconds==0&&s.inactiveSeconds==0)||(s.activeSeconds>=Tick&&s.activeSeconds<=60&&s.inactiveSeconds>=Tick&&s.inactiveSeconds<=60)),"Invalid statue attraction values");
                } else if(command=="statue_quake") {
                    require(!item&&!rule&&!graph&&!death,"statue_quake inside definition");const auto id=parseMonsterId(word(row));
                    auto it=lib->statues_.find(id);require(it!=lib->statues_.end()&&it->second.attack==StatueAttack::Quake,"Statue quake requires a preceding quake controller");
                    auto &s=it->second;require(!s.quakeConfigured,"Duplicate statue quake");s.quakeConfigured=true;
                    s.quakeAxis=integer(row,0,3);s.hopHeight=real(row);s.hopSeconds=real(row);s.waveRadius=real(row);s.waveTrail=real(row);
                    require(s.hopHeight>0&&s.hopHeight<=4&&s.hopSeconds>=Tick&&s.hopSeconds<s.interval&&
                        s.waveRadius>0&&s.waveRadius<=2&&s.waveTrail>=Tick&&s.waveTrail<=2,"Invalid statue quake values");
                } else if(command=="statue_supply") {
                    require(!item&&!rule&&!graph&&!death,"statue_supply inside definition");const auto id=parseMonsterId(word(row));
                    auto it=lib->statues_.find(id);require(it!=lib->statues_.end()&&it->second.attack==StatueAttack::Supply,"Statue supply requires a preceding supply controller");
                    auto &s=it->second;require(!s.supplyConfigured,"Duplicate statue supply");s.supplyConfigured=true;auto &b=s.supply;
                    b.replenish=real(row);b.fuse=real(row);b.radius=real(row);b.damage=real(row);b.selfDamage=real(row);
                    b.range=real(row);b.flight=real(row);b.pickupRadius=real(row);b.deathDrops=integer(row,0,32);
                    require(b.replenish>=Tick&&b.replenish<=60&&b.fuse>=.25f&&b.fuse<=30&&b.radius>0&&b.radius<=10&&
                        b.damage>0&&b.damage<=1000&&b.selfDamage>=0&&b.selfDamage<=100&&b.range>=1&&b.range<=30&&
                        b.flight>=.1f&&b.flight<=3&&b.pickupRadius>=.25f&&b.pickupRadius<=2,"Invalid statue supply values");
                } else if(command=="statue_rooms") {
                    require(!item&&!rule&&!graph&&!death,"statue_rooms inside definition");const int band=integer(row,0,3);
                    require(!lib->explicitStatueChances_[size_t(band)],"Duplicate statue room chance");lib->explicitStatueChances_[size_t(band)]=true;
                    lib->statueChances_[size_t(band)]=integer(row,0,10000);
                } else if(command=="statue_pool") {
                    require(!item&&!rule&&!graph&&!death,"statue_pool inside definition");const int first=integer(row,0,3),last=integer(row,first,3);
                    const auto pattern=word(row);StatuePoolEntry e;e.pattern=pattern=="any"?-1:named<int>(pattern,{{"pursuit",0},{"crossfire",1},{"charge_lane",2},{"supply_guard",3}});
                    e.monster=parseMonsterId(word(row));e.weight=integer(row,0,10000);
                    for(int band=first;band<=last;++band) {
                        auto &pool=lib->statuePools_[size_t(band)];
                        require(std::none_of(pool.begin(),pool.end(),[&](const auto &v){return v.monster==e.monster&&(v.pattern<0||e.pattern<0||v.pattern==e.pattern);}),"Duplicate statue pool entry");
                        require(pool.size()<256,"Too many statue pool entries");pool.push_back(e);
                    }
                } else if(command=="companion") {
                    require(!item&&!rule&&!graph&&!death,"companion inside definition");
                    const auto id=parseMonsterId(word(row));CompanionDefinition c;
                    c.contactDamage=real(row);c.attackInterval=real(row);c.hurtInterval=real(row);c.incomingScale=real(row);
                    require(word(row)=="room","Only room-limited companion lifetime is supported");
                    require(c.contactDamage>0&&c.contactDamage<=1000&&c.attackInterval>=Tick&&c.attackInterval<=10&&
                        c.hurtInterval>=0&&c.hurtInterval<=5&&c.incomingScale>0&&c.incomingScale<=10,"Invalid companion values");
                    require(lib->companions_.emplace(id,c).second,"Duplicate companion controller");
                } else if(command=="contact_familiar") {
                    require(!item&&!rule&&!graph&&!death,"contact_familiar inside definition");ContactFamiliarDefinition f;
                    f.item=parseItemKey(word(row));f.child=parseMonsterId(word(row));f.limit=integer(row,1,64);
                    f.lag=real(row);f.radius=real(row);f.contactInterval=real(row);
                    require(f.lag>=0&&f.lag<=2&&f.radius>0&&f.radius<=3&&f.contactInterval>=Tick&&f.contactInterval<=10,"Invalid contact familiar values");
                    require(lib->contactFamiliars_.size()<32&&std::none_of(lib->contactFamiliars_.begin(),lib->contactFamiliars_.end(),
                        [&](const auto &old){return old.item==f.item;}),"Duplicate contact familiar or capacity exceeded");
                    lib->contactFamiliars_.push_back(f);
                } else if(command=="component_bounce") {
                    require(!item&&!rule&&!graph&&!death,"component_bounce inside definition");
                    const auto id=parseMonsterId(word(row));ComponentDefinition c;c.owner=parseMonsterId(word(row));
                    c.contactDamage=real(row);c.bombDeflection=real(row);
                    require(c.contactDamage>0&&c.contactDamage<=1000&&c.bombDeflection>0&&c.bombDeflection<=10,"Invalid component values");
                    require(lib->components_.emplace(id,c).second,"Duplicate component controller");
                } else if(command=="boss_native") {
                    require(!item&&!rule&&!graph&&!death,"boss_native inside definition");const int band=integer(row,0,3);
                    require(!lib->explicitNativeBossWeights_[size_t(band)],"Duplicate native boss weight");
                    lib->explicitNativeBossWeights_[size_t(band)]=true;lib->nativeBossWeights_[size_t(band)]=integer(row,0,10000);
                } else if(command=="boss_pool") {
                    require(!item&&!rule&&!graph&&!death,"boss_pool inside definition");const int band=integer(row,0,3);
                    BossPoolEntry e;e.monster=parseMonsterId(word(row));
                    e.form=named<BossForm>(word(row),{{"normal",BossForm::Normal},{"cyan",BossForm::Cyan},{"yellow",BossForm::Yellow},{"green",BossForm::Green}});
                    e.weight=integer(row,0,10000);auto &pool=lib->bossPools_[size_t(band)];
                    row>>std::ws;if(!row.eof()&&row.peek()!='#')e.variant=named<FloorVariant>(word(row),{{"standard",FloorVariant::Standard},{"scorched",FloorVariant::Scorched},{"flooded",FloorVariant::Flooded},{"dank",FloorVariant::Dank},{"scarred",FloorVariant::Scarred}});
                    require(pool.size()<8192&&std::none_of(pool.begin(),pool.end(),[&](const auto &old){return old.monster==e.monster&&old.form==e.form&&old.variant==e.variant;}),"Duplicate boss pool entry or capacity exceeded");
                    pool.push_back(e);
                } else if(command=="pool") {
                    require(!item&&!rule&&!graph&&!death,"pool inside another definition");const auto name=word(row);
                    auto key=parseItemKey(word(row));int weight=integer(row,0,10000);
                    auto &pool=lib->pools_[name];require(pool.size()<8192,"Too many pool entries");
                    require(std::none_of(pool.begin(),pool.end(),[&](const auto &p){return p.item==key;}),"Duplicate pool item");
                    pool.push_back({key,weight});
                } else if(command=="encounter") {
                    require(!item&&!rule&&!graph&&!death,"encounter inside another definition");
                    const int first=integer(row,0,3),last=integer(row,first,3);
                    const auto pattern=word(row),role=word(row);
                    const int p=pattern=="any"?-1:named<int>(pattern,{{"pursuit",0},{"crossfire",1},{"charge_lane",2},{"supply_guard",3}});
                    require(role=="basic"||role=="specialist","Unknown encounter role");
                    EncounterEntry entry;entry.monster=parseMonsterId(word(row));
                    entry.weight=integer(row,0,10000);entry.cost=integer(row,1,1000);entry.maximum=integer(row,0,256);
                    row>>std::ws;if(!row.eof()&&row.peek()!='#')entry.members=integer(row,1,64);
                    row>>std::ws;if(!row.eof()&&row.peek()!='#')entry.variant=named<FloorVariant>(word(row),{{"standard",FloorVariant::Standard},{"scorched",FloorVariant::Scorched},{"flooded",FloorVariant::Flooded},{"dank",FloorVariant::Dank},{"scarred",FloorVariant::Scarred}});
                    require(!entry.maximum||entry.maximum>=entry.members,"Encounter group exceeds its actor cap");
                    for(int band=first;band<=last;++band)for(int which=0;which<4;++which)if(p<0||which==p) {
                        auto &pool=lib->encounters_[size_t(band)][size_t(which)];
                        auto &entries=role=="basic"?pool.basics:pool.specialists;
                        const auto absent=[&](const auto &v){return std::none_of(v.begin(),v.end(),[&](const auto &e){return e.monster==entry.monster;});};
                        require(absent(pool.basics)&&absent(pool.specialists),"Duplicate encounter monster in band/pattern");
                        require(entries.size()<8192,"Too many encounter entries");entries.push_back(entry);
                    }
                } else if(command=="floor_variant") {
                    require(!item&&!rule&&!graph&&!death,"floor_variant inside definition");
                    const int band=integer(row,0,3);
                    const auto variant=named<FloorVariant>(word(row),{{"standard",FloorVariant::Standard},{"scorched",FloorVariant::Scorched},{"flooded",FloorVariant::Flooded},{"dank",FloorVariant::Dank},{"scarred",FloorVariant::Scarred}});
                    const int weight=integer(row,0,10000);
                    require(lib->floorVariants_[size_t(band)].emplace(variant,weight).second,"Duplicate floor variant");
                } else if(command=="replace_monster"||command=="replace_spawn") {
                    require(!item&&!rule&&!graph&&!death,"replace_monster inside definition");
                    MonsterReplacement r;r.source=parseMonsterId(word(row));r.target=parseMonsterId(word(row));
                    r.firstBand=integer(row,0,3);r.lastBand=integer(row,r.firstBand,3);
                    const auto variant=word(row);
                    if(variant!="any")r.variant=named<FloorVariant>(variant,{{"standard",FloorVariant::Standard},{"scorched",FloorVariant::Scorched},{"flooded",FloorVariant::Flooded},{"dank",FloorVariant::Dank},{"scarred",FloorVariant::Scarred}});
                    if(command=="replace_spawn"){r.chance=10000;r.phase=3;r.allSpawns=true;}
                    else {
                        r.chance=integer(row,0,10000);r.extraCost=integer(row,0,100);
                        row>>std::ws;if(!row.eof()&&row.peek()!='#')r.phase=integer(row,0,3);
                    }
                    require(lib->replacements_.size()<8192,"Too many replacement rules");lib->replacements_.push_back(r);
                } else if(command=="death") {
                    require(!item&&!rule&&!graph&&!death,"Unclosed definition");MonsterDeathRule next;next.key=word(row);
                    require(lib->deaths_.size()<8192&&!lib->deaths_.contains(next.key),"Duplicate death rule or capacity exceeded");
                    death=&lib->deaths_.emplace(next.key,std::move(next)).first->second;
                } else if(command=="overkill") {
                    require(death&&!outcome,"overkill outside death header");death->overkill=real(row);
                    require(*death->overkill<=0,"Overkill threshold must be nonpositive");
                } else if(command=="population_offspring") {
                    require(death&&!outcome&&!death->population,"population_offspring requires one death header");
                    PopulationOffspring p;p.budget=real(row);p.crowdScale=real(row);
                    p.capMinimum=integer(row,0,16);p.capMaximum=integer(row,p.capMinimum,16);
                    p.radiusMinimum=real(row);p.radiusMaximum=real(row);
                    require(p.budget>0&&p.budget<=16&&p.crowdScale>=0&&p.crowdScale<=10&&
                        ((p.capMinimum==0)==(p.capMaximum==0))&&p.radiusMinimum>=0&&p.radiusMaximum>=p.radiusMinimum&&p.radiusMaximum<=10,
                        "Invalid population offspring profile");death->population=p;
                } else if(command=="population_adjustment") {
                    require(death&&!outcome&&death->population&&!death->population->adjusted,"Population adjustment requires one preceding population profile");
                    auto &p=*death->population;p.adjustment=integer(row,-16,16);p.minimum=integer(row,0,16);p.adjusted=true;
                } else if(command=="offspring_launch") {
                    require(death&&!outcome&&!death->launch,"offspring_launch requires one death header");
                    OffspringLaunch p;p.radius=real(row);p.scatter=real(row);p.heightScale=real(row);p.initialHeight=real(row);
                    p.initialVelocity=real(row);p.gravity=real(row);p.planar=real(row);
                    require(p.radius>=0&&p.radius<=20&&p.scatter>=0&&p.scatter<=5&&p.heightScale>0&&p.heightScale<=1&&
                        p.initialHeight<=0&&p.initialHeight>=-30&&p.initialVelocity<0&&p.initialVelocity>=-20&&
                        p.gravity>=.2f&&p.gravity<=5&&p.planar>0&&p.planar<=.1f,"Invalid offspring launch");
                    death->launch=p;
                } else if(command=="offspring_impulse") {
                    require(death&&!outcome&&death->impulse==0,"offspring_impulse requires one death header");
                    death->impulse=real(row);require(death->impulse>0&&death->impulse<=100,"Invalid offspring impulse");
                } else if(command=="offspring_layout") {
                    require(death&&!outcome,"offspring_layout outside death header");
                    death->layout=named<OffspringLayout>(word(row),{{"radial",OffspringLayout::Radial},{"perpendicular",OffspringLayout::Perpendicular}});
                    death->spacing=real(row);require(death->spacing>=0&&death->spacing<=20,"Invalid offspring spacing");
                } else if(command=="outcome") {
                    require(death&&!outcome,"outcome outside death rule or previous outcome unclosed");
                    require(death->outcomes.size()<64,"Too many death outcomes");
                    death->outcomes.push_back({integer(row,1,10000),{}});outcome=&death->outcomes.back();
                } else if(command=="offspring") {
                    require(outcome,"offspring outside death outcome");MonsterOffspring next;
                    next.monster=parseMonsterId(word(row));next.minimum=integer(row,0,64);next.maximum=integer(row,next.minimum,64);
                    next.healthScale=real(row);require(next.healthScale>0&&next.healthScale<=10,"Invalid offspring health scale");
                    require(outcome->offspring.size()<64,"Too many offspring groups");outcome->offspring.push_back(next);
                } else if(command=="endoutcome") {require(outcome,"endoutcome outside outcome");outcome=nullptr;
                } else if(command=="death_for") {
                    require(!item&&!rule&&!graph&&!death,"death_for inside definition");const auto id=parseMonsterId(word(row));
                    require(lib->deathBindings_.emplace(id,word(row)).second,"Duplicate death binding");
                } else if(command=="formation") {
                    require(!item&&!rule&&!graph&&!death,"formation inside definition");
                    const auto id=parseMonsterId(word(row));require(word(row)=="ring","Unknown formation shape");
                    FormationDefinition f;f.capacity=integer(row,2,64);
                    f.radius=real(row);f.angularSpeed=real(row);f.speed=real(row);f.gatherSpeed=real(row);
                    require(f.radius>0&&f.radius<=20&&f.angularSpeed>0&&f.angularSpeed<=20&&
                        f.speed>0&&f.speed<=20&&f.gatherSpeed>=f.radius*f.angularSpeed+f.speed*EnemyMovementMultiplier&&f.gatherSpeed<=200,
                        "Invalid formation geometry or movement speeds");
                    require(lib->formations_.emplace(id,f).second,"Duplicate formation binding");
                } else if(command=="eggy") {
                    require(!item&&!rule&&!graph&&!death,"eggy inside definition");
                    const auto id=parseMonsterId(word(row));EggyDefinition p;
                    p.restartChance=integer(row,1,1000);p.creepRadius=real(row);p.creepDuration=real(row);
                    p.deathFrames=integer(row,2,600);p.releaseFrame=integer(row,1,599);
                    p.child=parseMonsterId(word(row));p.scatter=real(row);p.childAdvance=integer(row,0,30);
                    for(auto &weight:p.weights)weight=integer(row,1,100);
                    const int count=integer(row,1,64);
                    for(int i=0;i<count;++i)p.releaseCounters.push_back(integer(row,1,600));
                    require(p.creepRadius>0&&p.creepRadius<=10&&p.creepDuration>0&&p.creepDuration<=30&&
                        p.scatter>=0&&p.scatter<=5&&p.releaseFrame<p.deathFrames&&
                        std::adjacent_find(p.releaseCounters.begin(),p.releaseCounters.end(),std::greater_equal<int>())==p.releaseCounters.end()&&
                        p.releaseCounters.back()+p.releaseFrame-1<p.deathFrames,"Invalid Eggy release sequence");
                    require(lib->eggies_.emplace(id,p).second,"Duplicate Eggy binding");
                } else if(command=="adaptive_armor") {
                    require(!item&&!rule&&!graph&&!death,"adaptive_armor inside definition");
                    const auto id=parseMonsterId(word(row));AdaptiveArmorDefinition p;
                    p.strength=real(row);p.historyFrames=integer(row,1,600);p.minimum=real(row);p.correction=real(row);
                    require(p.strength>0&&p.strength<=1000&&p.minimum>=0&&p.minimum<=1&&
                        p.correction>=p.minimum&&p.correction<=1,"Invalid adaptive armor");
                    require(lib->adaptiveArmor_.emplace(id,p).second,"Duplicate adaptive armor");
                } else if(command=="hop_rings") {
                    require(!item&&!rule&&!graph&&!death,"hop_rings inside definition");
                    const auto id=parseMonsterId(word(row));HopRingDefinition p;
                    p.damage=real(row);p.life=real(row);p.radius=real(row);
                    p.height=real(row);p.upMin=real(row);p.upMax=real(row);p.gravity=real(row);p.flightRetention=real(row);
                    require(p.height>p.radius&&p.height<=20&&p.upMin>=-100&&p.upMax<=100&&p.upMin<=p.upMax&&
                        p.gravity>0&&p.gravity<=200&&p.flightRetention>0&&p.flightRetention<1,"Invalid hop ring flight");
                    const int count=integer(row,1,8);
                    for(int i=0;i<count;++i) {
                        HopRingStage stage;stage.count=integer(row,2,64);stage.speed=real(row);
                        require(stage.speed>0&&stage.speed<=200,"Invalid hop ring speed");p.stages.push_back(stage);
                    }
                    require(p.damage>0&&p.damage<=100&&p.life>0&&p.life<=30&&p.radius>0&&p.radius<=1,
                        "Invalid hop ring projectile");
                    require(lib->hopRings_.emplace(id,p).second,"Duplicate hop ring sequence");
                } else if(command=="leaper") {
                    require(!item&&!rule&&!graph&&!death,"leaper inside definition");
                    const auto id=parseMonsterId(word(row));LeaperDefinition p;
                    p.chance=integer(row,1,1000);p.upFrames=integer(row,2,600);p.jumpFrame=integer(row,1,599);
                    p.downFrames=integer(row,2,600);p.landFrame=integer(row,1,599);
                    p.progressStep=real(row);p.height=real(row);p.searchRadius=real(row);p.sticky=integer(row,0,1)!=0;
                    p.shots=integer(row,1,64);p.speed=real(row);p.damage=real(row);p.life=real(row);
                    p.shotHeight=real(row);p.upMin=real(row);p.upMax=real(row);p.gravity=real(row);p.retention=real(row);
                    p.radius=real(row);p.sizeLow=real(row);p.sizeStep=real(row);p.sizeJitter=real(row);
                    p.smallCreep=real(row);p.bigCreep=real(row);p.creepDuration=real(row);
                    require(p.jumpFrame<p.upFrames&&p.landFrame<p.downFrames&&p.progressStep>0&&p.progressStep<=1&&
                        p.height>0&&p.height<=12&&p.searchRadius>=0&&p.searchRadius<=20&&
                        p.speed>0&&p.speed<=200&&p.damage>0&&p.damage<=100&&p.life>0&&p.life<=30&&
                        p.shotHeight>0&&p.shotHeight<=20&&p.upMin>=-100&&p.upMin<=p.upMax&&p.upMax<=100&&
                        p.gravity>0&&p.gravity<=200&&p.retention>0&&p.retention<1&&p.radius>0&&p.radius<=1&&
                        p.sizeLow>0&&p.sizeLow<=2&&p.sizeStep>=0&&p.sizeStep<=2&&p.sizeJitter>=0&&p.sizeJitter<=1&&
                        p.radius*(p.sizeLow+p.sizeStep+p.sizeJitter)<p.shotHeight&&
                        p.smallCreep>=0&&p.smallCreep<=8&&p.bigCreep>=0&&p.bigCreep<=8&&
                        p.creepDuration>0&&p.creepDuration<=30&&
                        (p.sticky||(p.smallCreep==0&&p.bigCreep==0)),"Invalid Leaper timing, flight or creep");
                    require(lib->leapers_.emplace(id,p).second,"Duplicate Leaper binding");
                } else if(command=="target_hop") {
                    require(!item&&!rule&&!graph&&!death,"target_hop inside definition");
                    const auto id=parseMonsterId(word(row));TargetHopDefinition p;
                    p.scale=real(row);p.idleFrames=integer(row,0,600);p.hopFrames=integer(row,2,600);
                    p.jumpFrame=integer(row,1,599);p.landFrame=integer(row,2,599);
                    p.bonusA=real(row);p.bonusB=real(row);p.rangeBase=real(row);p.rangeBonus=real(row);
                    p.overshoot=real(row);p.wander=real(row);p.margin=real(row);p.grid=real(row);
                    p.arrival=real(row);p.nearRange=real(row);p.farForce=real(row);p.groundFactor=real(row);
                    p.retention=real(row);p.stuckSpeed=real(row);p.stuckFrames=integer(row,1,600);
                    p.releaseChance=integer(row,1,1000);p.height=real(row);p.contactDamage=real(row);
                    row>>std::ws;if(!row.eof())p.leadFrames=integer(row,0,60);
                    require(p.scale>0&&p.scale<=1&&p.jumpFrame<p.landFrame&&p.landFrame<p.hopFrames&&
                        p.bonusA>=0&&p.bonusB>=0&&p.bonusA+p.bonusB<=1000&&p.rangeBase>0&&p.rangeBase<=1000&&
                        p.rangeBonus>=0&&p.rangeBonus<=10&&p.overshoot>0&&p.wander>0&&p.wander<=1000&&
                        p.margin>=0&&p.margin<=100&&p.grid>0&&p.grid<=100&&p.arrival>0&&p.nearRange>=p.arrival&&
                        p.farForce>0&&p.farForce<=1&&p.groundFactor>0&&p.groundFactor<=1&&
                        p.retention>0&&p.retention<1&&p.stuckSpeed>=0&&p.height>0&&p.height<=8&&
                        p.contactDamage>0&&p.contactDamage<=100,"Invalid destination hop timing or movement");
                    require(lib->targetHops_.emplace(id,p).second,"Duplicate destination hop binding");
                } else if(command=="hop") {
                    require(!item&&!rule&&!graph&&!death,"hop inside definition");
                    const auto id=parseMonsterId(word(row));HopDefinition h;
                    h.range=real(row);h.wanderDistance=real(row);h.chaseDistance=real(row);
                    h.duration=real(row);h.height=real(row);h.maximumHeight=real(row);h.retry=real(row);
                    require(h.range>0&&h.range<=100&&h.wanderDistance>0&&h.wanderDistance<=16&&
                        h.chaseDistance>=h.wanderDistance&&h.chaseDistance<=16&&h.duration>=.1f&&h.duration<=5&&
                        h.height>=.1f&&h.height<=h.maximumHeight&&h.maximumHeight<=8&&h.retry>=Tick&&h.retry<=10,
                        "Invalid hop geometry or timing");
                    require(lib->hops_.emplace(id,h).second,"Duplicate hop binding");
                } else if(command=="fire_reaction") {
                    require(!item&&!rule&&!graph&&!death,"fire_reaction inside definition");
                    const auto id=parseMonsterId(word(row));FireReaction reaction;
                    reaction.dryOnly=named<bool>(word(row),{{"any",false},{"dry",true}});
                    reaction.flameScale=real(row);reaction.burningScale=real(row);
                    require(reaction.flameScale>=0&&reaction.flameScale<=10&&reaction.burningScale>=0&&reaction.burningScale<=10,
                        "Invalid fire damage multiplier");
                    const auto target=word(row);if(target!="none")reaction.transform=parseMonsterId(target);
                    reaction.trigger=named<FireTrigger>(word(row),{{"flame",FireTrigger::Flame},{"burning",FireTrigger::Burning},{"both",FireTrigger::Both}});
                    reaction.health=named<TransformHealth>(word(row),{{"fraction",TransformHealth::Fraction},{"current",TransformHealth::Current}});
                    require(lib->fireReactions_.emplace(id,reaction).second,"Duplicate fire reaction");
                } else if(command=="regrowth") {
                    require(!item&&!rule&&!graph&&!death,"regrowth inside definition");const auto id=parseMonsterId(word(row));MonsterRegrowth r;
                    r.healthRetention=real(row);r.gooFraction=real(row);r.delay=real(row);r.minimumHealth=real(row);r.splitLimit=integer(row,0,4);
                    require(r.healthRetention>0&&r.healthRetention<=1&&r.gooFraction>0&&r.gooFraction<=1&&r.delay>=Tick&&r.delay<=120&&r.minimumHealth>0,"Invalid regrowth rule");
                    require(lib->regrowth_.emplace(id,r).second,"Duplicate regrowth binding");
                } else if(command=="behavior") {
                    require(!item&&!rule&&!graph&&!death,"Unclosed definition");BehaviorDefinition next;next.key=word(row);next.initial=word(row);next.range=real(row);
                    require(next.key!="legacy"&&next.range>0&&next.range<=1000&&!lib->behaviors_.contains(next.key),"Invalid or duplicate behavior");
                    graph=&lib->behaviors_.emplace(next.key,std::move(next)).first->second;
                } else if(command=="projectiles") {
                    require(graph&&!state,"projectiles outside behavior header");graph->projectileCount=integer(row,1,128);graph->spread=real(row);graph->projectileDamage=real(row);graph->projectileSpeed=real(row);
                    require(graph->spread>=0&&graph->spread<=2*Pi&&graph->projectileDamage>=0&&graph->projectileSpeed>0&&graph->projectileSpeed<=200,"Invalid projectile pattern");
                } else if(command=="summon") {
                    require(graph&&!state&&!graph->summon,"summon outside behavior header or already configured");BehaviorSummon next;
                    next.monster=parseMonsterId(word(row));next.count=integer(row,1,64);next.ownerLimit=integer(row,next.count,64);
                    next.healthScale=real(row);next.spacing=real(row);
                    require(next.healthScale>0&&next.healthScale<=10&&next.spacing>=0&&next.spacing<=20,"Invalid summon health or spacing");
                    graph->summon=next;
                } else if(command=="orbit") {
                    require(graph&&!state,"orbit outside behavior header");graph->orbitRadius=real(row);graph->acceleration=real(row);
                    require(graph->orbitRadius>0&&graph->orbitRadius<=100&&graph->acceleration>0&&graph->acceleration<=1000,"Invalid orbit radius or acceleration");
                } else if(command=="state") {
                    require(graph&&!state,"state outside graph or previous state unclosed");BehaviorState next;next.name=word(row);
                    next.pose=named<BehaviorPose>(word(row),{{"ready",BehaviorPose::Ready},{"windup",BehaviorPose::Windup},{"exposed",BehaviorPose::Exposed}});
                    next.motion=named<BehaviorMotion>(word(row),{{"still",BehaviorMotion::Still},{"chase",BehaviorMotion::Chase},{"flee",BehaviorMotion::Flee},{"wander",BehaviorMotion::Wander},{"orbit",BehaviorMotion::Orbit},{"axis_wander",BehaviorMotion::AxisWander}});
                    auto duration=word(row);next.useWindup=duration=="windup";
                    if(!next.useWindup){std::istringstream n(duration);next.duration=real(n);require(next.duration>=0&&next.duration<=3600,"Invalid state duration");}
                    next.damageScale=real(row);require(next.damageScale>=0&&next.damageScale<=10,"Invalid state damage scale");
                    require(graph->states.size()<128,"Too many behavior states");graph->states.push_back(next);state=&graph->states.back();
                } else if(command=="motion_speed") {
                    require(state,"motion_speed outside state");state->motionSpeed=real(row);
                    require(state->motionSpeed>=0&&state->motionSpeed<=10,"Invalid motion speed multiplier");
                } else if(command=="projectile_aim") {
                    require(graph&&!state,"projectile_aim outside behavior header");
                    graph->projectileAim=named<BehaviorAim>(word(row),{{"locked",BehaviorAim::Locked},{"facing",BehaviorAim::Facing},{"player",BehaviorAim::Player}});
                } else if(command=="projectile_pattern") {
                    require(graph&&!state,"projectile_pattern outside behavior header");
                    graph->projectilePattern=named<BehaviorPattern>(word(row),{{"fan",BehaviorPattern::Fan},{"radial",BehaviorPattern::Radial}});
                    graph->projectileAngle=real(row);
                    require(std::abs(graph->projectileAngle)<=2*Pi,"Invalid projectile pattern angle");
                } else if(command=="projectile_kind") {
                    require(graph&&!state,"projectile_kind outside behavior header");
                    graph->projectileKind=named<BehaviorShot>(word(row),{{"bullet",BehaviorShot::Bullet},{"tar",BehaviorShot::Tar},{"ember",BehaviorShot::Ember},{"brown",BehaviorShot::Brown},{"bone",BehaviorShot::Bone},{"dark_bone",BehaviorShot::DarkBone}});
                } else if(command=="projectile_curve") {
                    require(graph&&!state,"projectile_curve outside behavior header");
                    graph->projectileCurve=real(row);
                    require(std::abs(graph->projectileCurve)<=20,"Invalid projectile angular velocity");
                    graph->alternateCurve=named<bool>(word(row),{{"fixed",false},{"alternate",true}});
                } else if(command=="projectile_life") {
                    require(graph&&!state,"projectile_life outside behavior header");graph->projectileLife=real(row);
                    require(graph->projectileLife>=Tick&&graph->projectileLife<=120,"Invalid projectile lifetime");
                } else if(command=="aimed_alignment") {
                    require(graph&&!state&&!graph->alignmentConfigured,"aimed_alignment requires one behavior header");
                    graph->alignment=real(row);graph->alignmentInterval=real(row);graph->alignmentPrediction=real(row);
                    require(graph->alignment>0&&graph->alignment<=10&&graph->alignmentInterval>=Tick&&graph->alignmentInterval<=10&&
                        graph->alignmentPrediction>=0&&graph->alignmentPrediction<=2,"Invalid aimed alignment values");
                    graph->alignmentConfigured=true;
                } else if(command=="wander") {
                    require(graph&&!state,"wander outside behavior header");graph->wanderMin=real(row);graph->wanderMax=real(row);
                    require(graph->wanderMin>=Tick&&graph->wanderMax>=graph->wanderMin&&graph->wanderMax<=120,"Invalid wandering interval");
                } else if(command=="enter"||command=="exit") {
                    require(state,"action outside state");auto &actions=command=="enter"?state->enter:state->exit;
                    require(actions.size()<32,"Too many state actions");actions.push_back(action(word(row)));
                } else if(command=="transition") {
                    require(state,"transition outside state");BehaviorTransition t;t.to=word(row);
                    t.guard=named<BehaviorGuard>(word(row),{{"always",BehaviorGuard::Always},{"timer",BehaviorGuard::Timer},{"attack_ready",BehaviorGuard::AttackReady},{"cooldown_ready",BehaviorGuard::CooldownReady},{"health_below",BehaviorGuard::HealthBelow},{"aligned_attack_ready",BehaviorGuard::AlignedAttackReady}});
                    t.value=real(row);require(t.value>=0&&t.value<=1,"Transition value must be in [0,1]");
                    require(state->transitions.size()<32,"Too many transitions");state->transitions.push_back(t);
                } else if(command=="endstate") {require(state,"endstate outside state");state=nullptr;}
                else if(command=="end") {require(!state&&!outcome&&(item||rule||graph||death),"Unmatched end");item=nullptr;rule=nullptr;graph=nullptr;death=nullptr;}
                else throw std::runtime_error("Unknown command '"+command+"'");
                row>>std::ws;require(row.eof()||row.peek()=='#',"Unexpected trailing data");
            } catch(const std::exception &e) {throw std::runtime_error(path.string()+":"+std::to_string(lineNumber)+": "+e.what());}
        }
        require(header&&!item&&!rule&&!graph&&!death&&!state,path.string()+": incomplete definition or missing header");
    }
    require(!lib->items_.empty()&&!lib->monsters_.empty(),"Content requires item and monster definitions");
    for(const auto &m:lib->monsters_)require(m.hp>0||lib->returningBody(m.id),"Zero health requires an owned returning body");
    for(const auto &[id,c]:lib->components_) {
        const auto *d=lib->monster(id);const auto *owner=lib->monster(c.owner);
        require(d&&owner&&id!=c.owner&&d->roomHazard&&!d->natural&&d->flying&&d->motion==MonsterMotion::Bounce&&
            d->attack==MonsterAttack::None&&d->behavior=="legacy"&&!lib->components_.contains(c.owner)&&!lib->formation(id)&&!lib->hop(id),
            "Component requires independent flying hazard and a valid distinct owner");
    }
    std::set<std::string> ruleNames;
    for(const auto &r:lib->rules_) {
        require(ruleNames.insert(r.key).second,"Duplicate rule '"+r.key+"'");require(lib->item(r.owner),"Unknown rule owner in '"+r.key+"'");
        require(!r.modifiers.empty(),"Empty rule '"+r.key+"'");for(const auto &q:r.requirements)require(lib->item(q.item),"Unknown requirement in '"+r.key+"'");
    }
    std::sort(lib->rules_.begin(),lib->rules_.end(),[](const auto &a,const auto &b){return std::tie(a.priority,a.key)<std::tie(b.priority,b.key);});
    for(auto &[key,g]:lib->behaviors_) {
        std::map<std::string,size_t> states;
        for(size_t i=0;i<g.states.size();++i)require(states.emplace(g.states[i].name,i).second,"Duplicate state in "+key);
        require(states.contains(g.initial),"Missing initial state in "+key);g.initialIndex=states.at(g.initial);
        for(auto &s:g.states)for(auto &t:s.transitions){require(states.contains(t.to),"Unknown transition target in "+key);t.target=states.at(t.to);
            require(t.guard!=BehaviorGuard::AlignedAttackReady||g.alignmentConfigured,"Aligned attack requires aimed_alignment in "+key);}
        if(g.summon) {
            require(lib->monster(g.summon->monster),"Unknown graph summon child in "+key);
            require(!lib->component(g.summon->monster),"Graph summon cannot bypass component ownership in "+key);
            require(!lib->flyBomb(g.summon->monster)||!lib->flyBomb(g.summon->monster)->orbitOwner,"Graph summon cannot bypass fly bomb ownership in "+key);
            require(!lib->segmentedBoss(g.summon->monster),"Graph summon cannot create a dedicated segmented encounter in "+key);
        }
        for(const auto &s:g.states)for(const auto *list:{&s.enter,&s.exit})
            if(std::find(list->begin(),list->end(),BehaviorAction::Summon)!=list->end())
                require(bool(g.summon),"Summon action requires a child configuration in "+key);
    }
    for(const auto &[key,death]:lib->deaths_) {
        require(!death.outcomes.empty(),"Death rule needs at least one outcome: "+key);
        require(!death.launch||death.impulse==0,"Thrown and grounded offspring impulses cannot be combined: "+key);
        for(const auto &outcome:death.outcomes) {
            int total=0;
            for(const auto &child:outcome.offspring) {
                require(lib->monster(child.monster),"Unknown death offspring in "+key);
                require(!death.launch||lib->swimmer(child.monster),"Thrown offspring require a swimmer controller in "+key);
                require(!lib->component(child.monster),"Death offspring cannot bypass component ownership in "+key);total+=child.maximum;
                require(!lib->flyBomb(child.monster)||!lib->flyBomb(child.monster)->orbitOwner,"Death offspring cannot bypass fly bomb ownership in "+key);
                require(!lib->segmentedBoss(child.monster),"Death offspring cannot create a dedicated segmented encounter in "+key);
            }
            require(total<=64,"Death outcome exceeds offspring budget: "+key);
            if(death.population)require(outcome.offspring.size()==1&&outcome.offspring.front().minimum==1&&total==1,
                "Population death outcomes must each select exactly one child: "+key);
        }
    }
    for(const auto &[id,key]:lib->deathBindings_)
        require(lib->monster(id)&&lib->deaths_.contains(key),"Unknown monster or death rule in death_for "+monsterIdText(id));
    for(const auto &[id,r]:lib->regrowth_) {
        const auto *d=lib->monster(id);
        require(d&&r.minimumHealth<=d->hp,"Unknown monster or excessive minimum health in regrowth "+monsterIdText(id));
        require(d->behavior=="legacy","Graph regeneration requires explicit collapsed-state handling");
    }
    for(const auto &[id,f]:lib->formations_) {
        const auto *d=lib->monster(id);
        require(d&&d->flying&&d->behavior=="legacy"&&d->motion==MonsterMotion::Orbit&&d->attack==MonsterAttack::None,
                "Formation requires a flying legacy orbit actor without a ranged attack");
        require(2*f.radius*std::sin(Pi/float(2*(f.capacity-1)))>=2*d->radius+.05f,"Formation slots overlap at capacity");
    }
    for(const auto &[id,h]:lib->hops_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->motion==MonsterMotion::Hop&&
            d->attack==MonsterAttack::None&&d->behavior=="legacy"&&!lib->formation(id)&&!lib->targetHop(id),
            "Hop controller requires an independent ground hopper without a ranged attack");
    }
    for(const auto &[id,p]:lib->adaptiveArmor_) {
        const auto *d=lib->monster(id);
        require(d&&!d->roomHazard&&!lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id),
            "Adaptive armor currently requires an independent ordinary enemy");
    }
    for(const auto &[id,p]:lib->targetHops_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Hop&&
            d->attack==MonsterAttack::None&&d->behavior=="legacy"&&!lib->hop(id)&&!lib->formation(id)&&
            !lib->swarmSpider(id)&&!lib->spider(id)&&!lib->charge(id)&&!lib->evader(id)&&
            !lib->component(id)&&!lib->companion(id)&&!lib->monsterBoss(id)&&!lib->regrowth(id)&&
            !lib->longLegs(id)&&!lib->sack(id),
            "Destination hop requires an independent grounded contact body");
    }
    for(const auto &[id,p]:lib->eggies_) {
        const auto *child=lib->swarmSpider(p.child);
        require(lib->targetHop(id)&&child&&p.child!=id&&!lib->deathRule(id)&&!lib->lethalMorph(id),
            "Eggy requires destination hopping and a separate Swarm child without conflicting death rules");
        for(const auto &hop:child->hops)require(hop.jump+p.childAdvance<hop.land,
            "Eggy child must begin in its airborne interval");
    }
    for(const auto &[id,p]:lib->hopRings_)
        require(lib->targetHop(id)&&!lib->eggy(id),"Hop rings require independent destination hopping without Eggy death/creep");
    for(const auto &[id,p]:lib->leapers_)
        require(lib->targetHop(id)&&!lib->eggy(id)&&!lib->hopRings(id)&&!lib->deathRule(id)&&!lib->lethalMorph(id),
            "Leaper requires independent destination hopping without conflicting landing or death actions");
    for(const auto &[id,reaction]:lib->fireReactions_) {
        const auto *source=lib->monster(id);
        require(source&&!source->roomHazard,"Unknown or hazardous fire-reaction source");
        if(reaction.transform) {
            const auto *target=lib->monster(*reaction.transform);
            require(target&&target->id!=id&&!target->roomHazard,"Invalid fire transformation target");
            const auto linked=[](MonsterId m){return m.type==35||m.type==96||m==monsterId(26,2)||m==monsterId(55,2)||m==monsterId(41,3);};
            // These are in-place independent-body transformations. Larger bodies,
            // navigation-mode switches and multipart controllers need separate
            // clearance/ownership handling rather than silently clipping them.
            require(source->natural&&target->natural&&!linked(id)&&!linked(target->id)&&
                source->flying==target->flying&&std::abs(source->radius-target->radius)<.00001f&&
                source->motion!=MonsterMotion::Chain&&target->motion!=MonsterMotion::Chain&&
                !lib->formation(id)&&!lib->formation(target->id)&&bool(lib->hop(id))==bool(lib->hop(target->id))&&
                bool(lib->targetHop(id))==bool(lib->targetHop(target->id)),
                "Fire transformation requires compatible independent bodies");
            if(lib->targetHop(id))require(!lib->eggy(id)&&!lib->eggy(target->id)&&
                !lib->hopRings(id)&&!lib->hopRings(target->id)&&!lib->leaper(id)&&!lib->leaper(target->id)&&
                !lib->adaptiveArmor(id)&&!lib->adaptiveArmor(target->id),
                "Destination-hop fire morph requires plain bodies without landing/death/armor state");
        }
        std::set<MonsterId> visited;auto next=id;
        while(const auto *rule=lib->fireReaction(next)) {
            require(visited.insert(next).second,"Cyclic fire transformation");
            if(!rule->transform)break;
            next=*rule->transform;
        }
    }
    for(const auto &m:lib->monsters_)require(m.behavior=="legacy"||lib->behavior(m.behavior),"Unknown behavior for "+monsterIdText(m.id));
    for(auto &[name,pool]:lib->pools_) {
        int eligible=0;
        for(const auto &entry:pool){require(lib->item(entry.item),"Unknown item in pool "+name);eligible+=entry.weight>0;}
        require(eligible>=2,"Pool "+name+" needs at least two positive-weight items");
        std::sort(pool.begin(),pool.end(),[](const auto &a,const auto &b){return a.item<b.item;});
    }
    for(const auto name:{"armory","shop","boss","bargain"})require(lib->pools_.contains(name),std::string("Missing required pool ")+name);
    for(const auto &[id,p]:lib->environmentActors_) {
        const auto *d=lib->monster(id);
        const bool coal=p.kind==EnvironmentActorKind::HotCoal;
        require(d&&d->roomHazard&&!d->flying&&d->motion==MonsterMotion::Still&&d->attack==MonsterAttack::None&&!d->natural&&
            d->hp==(coal?15:p.kind==EnvironmentActorKind::Fireplace?5:4)&&
            (coal?id.type==33&&id.variant==11&&id.subtype<=3&&lib->rockSpider(id):
            id==(p.kind==EnvironmentActorKind::Fireplace?monsterId(33):monsterId(292))),"Invalid environment actor identity");
    }
    for(const auto &[id,p]:lib->railTraffic_) {
        require(lib->hornfel(id)&&!p.passengers.empty(),"Invalid rail traffic owner or empty passenger table");
        for(const auto &passenger:p.passengers)if(passenger.available)
            require(lib->environmentActor(passenger.actor),"Passenger behavior is not implemented: "+monsterIdText(passenger.actor));
    }
    for(const auto &[id,p]:lib->hornfelDecoys_) {
        const auto *d=lib->monster(id);const auto *b=lib->enemyBomb(p.bomb);
        require(id==monsterId(906,1)&&p.owner==monsterId(906)&&lib->hornfel(p.owner)&&d&&d->hp==4&&d->roomHazard&&
            !d->natural&&!d->flying&&d->motion==MonsterMotion::Still&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            !lib->deathRule(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->regrowth(id)&&
            b&&b->ordnance==monsterId(4,3)&&b->payload==EnemyBombPayload::Blast&&b->fuse>0,"Invalid Hornfel decoy identity or payload");
    }
    for(const auto &[id,p]:lib->hornfels_) {
        const auto *d=lib->monster(id);
        require(id==monsterId(906)&&d&&!d->natural&&!d->roomHazard&&!d->flying&&d->motion==MonsterMotion::Still&&
            d->attack==MonsterAttack::None&&d->behavior=="legacy"&&!lib->loki(id)&&!lib->peep(id)&&!lib->bloat(id)&&
            !lib->segmentedBoss(id)&&!lib->component(id)&&!lib->regrowth(id)&&!lib->deathRule(id)&&!p.layouts.empty()&&
            p.chargeConfigured&&p.recoveryConfigured&&lib->hornfelDecoy(monsterId(906,1)),"Invalid Hornfel root");
        const auto *escort=lib->flyBomb(p.escort);const auto *escortBody=lib->monster(p.escort);
        require(p.escort==monsterId(819)&&escort&&escort->followConfigured&&!escort->orbitOwner&&escortBody&&
            !escortBody->roomHazard&&escortBody->flying&&p.escortReleaseHp<=escortBody->hp,"Invalid Hornfel escort identity");
        for(const auto &[key,weight]:p.layouts)require(lib->railLayout(key),"Unknown Hornfel rail layout");
        for(const auto key:{"hornfel_normal","hot","sad","brimstone"})require(lib->enemyBomb(key),"Missing Hornfel payload");
    }
    for(const auto &[id,p]:lib->lokis_) {
        const auto *d=lib->monster(id);const auto *child=lib->monster(p.child);
        require(d&&!d->natural&&!d->roomHazard&&!d->flying&&d->behavior=="legacy"&&
            d->motion==MonsterMotion::Still&&d->attack==MonsterAttack::None&&!lib->peep(id)&&!lib->bloat(id)&&
            !lib->formation(id)&&!lib->hop(id)&&!lib->charge(id)&&!lib->component(id)&&!lib->regrowth(id)&&!lib->deathRule(id)&&
            child&&lib->boomFly(p.child)&&!child->roomHazard&&!lib->monsterBoss(p.child)&&!lib->component(p.child),
            "Loki requires an independent grounded boss and an ordinary Boom Fly child");
    }
    for(const auto &[id,p]:lib->peeps_) {
        const auto *d=lib->monster(id);const auto *eye=lib->component(p.eye);
        require(d&&eye&&eye->owner==id&&!d->natural&&!d->roomHazard&&!d->flying&&d->behavior=="legacy"&&
            d->motion==MonsterMotion::Still&&d->attack==MonsterAttack::None&&!lib->formation(id)&&!lib->hop(id)&&!lib->bloat(id)&&!lib->charge(id),
            "Peep requires a dedicated grounded boss and its owned eye controller");
    }
    for(const auto &[id,p]:lib->segmentedBosses_) {
        const auto *d=lib->monster(id);const auto *supplier=lib->statue(p.supplier);
        const bool shell=lib->shell(id)!=nullptr;
        require(d&&!d->natural&&!d->roomHazard&&d->flying==shell&&d->motion==MonsterMotion::Chain&&d->attack==MonsterAttack::None&&
            d->behavior=="legacy"&&!lib->peep(id)&&!lib->bloat(id)&&!lib->component(id)&&!lib->hop(id)&&!lib->formation(id)&&!lib->charge(id)&&
            p.spacing>2*d->radius&&p.attacksConfigured&&supplier&&supplier->attack==StatueAttack::Supply,
            "Segmented boss requires independent chain body, attacks and real bomb supplier");
        for(auto child:{shell?p.exposedChild:p.armoredChild,p.exposedChild})require(lib->monster(child)&&!lib->monster(child)->roomHazard&&
            !lib->monsterBoss(child)&&!lib->component(child)&&!lib->companion(child),"Unsupported segmented boss child");
        if(shell)require(lib->flyBomb(p.exposedChild)&&!lib->flyBomb(p.exposedChild)->orbitOwner,"Shell requires an independent Fly Bomb child");
    }
    for(const auto &[id,p]:lib->adultLeeches_) {
        const auto *d=lib->monster(id);
        require(d&&d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Wander&&
            d->attack==MonsterAttack::None&&d->behavior=="legacy"&&p.burrowConfigured&&p.shots[0].count&&p.shots[1].count&&
            !lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&!lib->hop(id)&&
            !lib->targetHop(id)&&!lib->charge(id)&&!lib->regrowth(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&
            !lib->linkedHead(id)&&!lib->spitty(id)&&!lib->brain(id)&&!lib->cardinalWalker(id)&&!lib->maw(id)&&
            !lib->host(id)&&!lib->mushroom(id)&&!lib->environmentActor(id)&&!lib->boil(id)&&!lib->sack(id)&&
            !lib->flyBomb(id)&&!lib->boomFly(id)&&!lib->evader(id)&&!lib->swimmer(id)&&!lib->statue(id)&&
            !lib->lump(id)&&!lib->baby(id)&&!lib->leech(id)&&!lib->mirror(id)&&!lib->knight(id)&&!lib->guts(id)&&!lib->memBrain(id)&&
            !lib->deathRule(id)&&!lib->deathBlast(id)&&!lib->deathCross(id)&&!lib->fireReaction(id),
            "Adult Leech requires independent flying wandering actor and complete nonconflicting profiles");
    }
    for(const auto &[id,p]:lib->slides_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Wander&&
            d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            !lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&!lib->hop(id)&&
            !lib->targetHop(id)&&!lib->charge(id)&&!lib->regrowth(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&
            !lib->linkedHead(id)&&!lib->spitty(id)&&!lib->brain(id)&&!lib->cardinalWalker(id)&&!lib->maw(id)&&
            !lib->host(id)&&!lib->mushroom(id)&&!lib->environmentActor(id)&&!lib->boil(id)&&!lib->sack(id)&&
            !lib->flyBomb(id)&&!lib->boomFly(id)&&!lib->evader(id)&&!lib->swimmer(id)&&!lib->statue(id)&&
            !lib->lump(id)&&!lib->baby(id)&&!lib->leech(id)&&!lib->mirror(id)&&!lib->knight(id)&&!lib->guts(id)&&!lib->memBrain(id)&&!lib->adultLeech(id)&&
            !lib->deathRule(id)&&!lib->deathBlast(id)&&!lib->deathCross(id)&&!lib->fireReaction(id),
            "Slide requires independent grounded actor and nonconflicting profiles");
        if(p.targeted) {
            const auto *child=lib->monster(p.child);const auto *slide=lib->slide(p.child);
            require(child&&p.child!=id&&((slide&&!slide->targeted)||
                (lib->behavior(child->behavior)&&child->attack!=MonsterAttack::None)),
                "Squirt requires a real slide or attacking behavior child");
            if(p.secondAttackFrames)require(slide&&slide->chainFrame&&slide->floodedPits&&p.floodedPits,
                "Splurt requires swimming parent and Drip child");
        }
    }
    for(const auto &[id,p]:lib->memBrains_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Wander&&
            d->attack==MonsterAttack::None&&d->behavior=="legacy"&&p.shotConfigured&&
            !lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&!lib->hop(id)&&
            !lib->targetHop(id)&&!lib->charge(id)&&!lib->regrowth(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&
            !lib->linkedHead(id)&&!lib->spitty(id)&&!lib->brain(id)&&!lib->cardinalWalker(id)&&!lib->maw(id)&&
            !lib->host(id)&&!lib->mushroom(id)&&!lib->environmentActor(id)&&!lib->boil(id)&&!lib->sack(id)&&
            !lib->flyBomb(id)&&!lib->boomFly(id)&&!lib->evader(id)&&!lib->swimmer(id)&&!lib->statue(id)&&
            !lib->lump(id)&&!lib->baby(id)&&!lib->leech(id)&&!lib->mirror(id)&&!lib->knight(id)&&!lib->guts(id)&&!lib->slide(id)&&!lib->adultLeech(id)&&
            !lib->deathRule(id)&&!lib->deathBlast(id)&&!lib->deathCross(id)&&!lib->fireReaction(id),
            "MemBrain requires independent grounded wandering actor and complete nonconflicting profiles");
        const auto *child=lib->monster(p.child);
        require(child&&!child->roomHazard&&!child->flying&&p.child!=id&&
            (lib->brain(p.child)||lib->guts(p.child)||(p.dinga&&lib->slide(p.child)&&lib->slide(p.child)->targeted)),"MemBrain requires a real Brain/Guts/Squirt child controller");
        if(p.dinga)require(lib->slide(p.dinga->child)&&!lib->slide(p.dinga->child)->targeted&&p.dinga->child!=id,
            "Dinga requires a real Dip living child controller");
    }
    for(const auto &[id,p]:lib->lumps_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Burrow&&
            d->attack==MonsterAttack::None&&d->behavior=="legacy"&&p.shotConfigured&&
            !lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&!lib->hop(id)&&
            !lib->targetHop(id)&&!lib->charge(id)&&!lib->regrowth(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&
            !lib->linkedHead(id)&&!lib->spitty(id)&&!lib->brain(id)&&!lib->cardinalWalker(id)&&!lib->maw(id)&&
            !lib->host(id)&&!lib->mushroom(id)&&!lib->environmentActor(id)&&!lib->boil(id)&&!lib->sack(id)&&
            !lib->flyBomb(id)&&!lib->boomFly(id)&&!lib->evader(id)&&!lib->swimmer(id)&&!lib->statue(id)&&
            !lib->baby(id)&&!lib->leech(id)&&!lib->mirror(id)&&!lib->knight(id)&&!lib->guts(id)&&
            !lib->deathRule(id)&&!lib->deathBlast(id)&&!lib->deathCross(id)&&!lib->fireReaction(id),
            "Lump requires independent grounded burrow actor and complete nonconflicting profiles");
    }
    for(const auto &[id,p]:lib->babies_) {
        const auto *d=lib->monster(id);
        require(d&&d->flying&&!d->roomHazard&&d->contact&&d->attack==MonsterAttack::None&&d->motion==MonsterMotion::Chase&&
            d->behavior=="legacy"&&p.shotConfigured&&(p.kind==BabyKind::Wrinkly?p.dashConfigured:p.teleportConfigured)&&
            (!p.dashConfigured||p.closeAttackFrame<p.shot.shootFrame)&&
            !lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&!lib->hop(id)&&
            !lib->targetHop(id)&&!lib->charge(id)&&!lib->regrowth(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&
            !lib->linkedHead(id)&&!lib->spitty(id)&&!lib->brain(id)&&!lib->cardinalWalker(id)&&!lib->maw(id)&&
            !lib->host(id)&&!lib->mushroom(id)&&!lib->environmentActor(id)&&!lib->boil(id)&&!lib->sack(id)&&
            !lib->flyBomb(id)&&!lib->boomFly(id)&&!lib->evader(id)&&!lib->swimmer(id)&&!lib->statue(id)&&
            !lib->deathRule(id)&&!lib->deathBlast(id)&&!lib->deathCross(id)&&!lib->fireReaction(id),
            "Baby requires independent flying actor and complete nonconflicting profiles");
        require(p.kind!=BabyKind::Small||!d->natural,"Small Angelic Baby is offspring, not an ordinary pool entry");
    }
    std::set<MonsterId> linkedParts;
    for(const auto &[id,p]:lib->linkedHeads_) {
        const auto *body=lib->monster(id),*head=lib->monster(p.head),*neck=lib->monster(p.neck);
        require(body&&head&&neck&&p.throwConfigured&&p.neckConfigured&&p.body==id&&id!=p.head&&
            p.neck!=id&&p.neck!=p.head&&linkedParts.insert(id).second&&linkedParts.insert(p.head).second,
            "Linked head requires unique body/head and complete profiles");
        require(!body->flying&&!body->roomHazard&&body->motion==MonsterMotion::Chase&&body->attack==MonsterAttack::None&&
            head->flying&&!head->roomHazard&&!head->natural&&head->attack==MonsterAttack::None&&
            neck->roomHazard&&!neck->natural&&!neck->contact&&neck->attack==MonsterAttack::None,
            "Invalid linked head body/head/neck roles");
        for(const auto part:{id,p.head})require(!lib->monsterBoss(part)&&!lib->component(part)&&!lib->companion(part)&&
            !lib->formation(part)&&!lib->hop(part)&&!lib->targetHop(part)&&!lib->charge(part)&&!lib->regrowth(part)&&
            !lib->deathRule(part)&&!lib->deathBlast(part)&&!lib->deathCross(part)&&!lib->fireReaction(part)&&
            !lib->boomFly(part)&&!lib->flyBomb(part)&&!lib->headShooter(part)&&!lib->lobWalker(part)&&!lib->statue(part)&&
            !lib->evader(part)&&!lib->swimmer(part)&&!lib->environmentActor(part)&&!lib->cardinalWalker(part)&&
            !lib->spitty(part)&&!lib->brain(part)&&!lib->maw(part)&&!lib->boil(part)&&!lib->sack(part)&&
            !lib->host(part)&&!lib->mushroom(part)&&lib->monster(part)->behavior=="legacy",
            "Linked head conflicts with another controller");
        for(const auto child:{p.bodyRelease,p.headRelease})require(lib->monster(child)&&!lib->monster(child)->roomHazard&&
            !lib->monsterBoss(child)&&!lib->component(child)&&!lib->companion(child)&&!lib->linkedHead(child)&&!lib->linkedNeck(child),
            "Invalid linked head release identity");
    }
    for(const auto &[id,p]:lib->brains_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==(p.pursuit?MonsterMotion::Chase:MonsterMotion::Wander)&&d->attack==MonsterAttack::None&&
            d->behavior=="legacy"&&(p.chargeConfigured!=bool(p.pursuit))&&p.creepConfigured&&!lib->monsterBoss(id)&&!lib->component(id)&&
            !lib->companion(id)&&!lib->formation(id)&&!lib->hop(id)&&!lib->targetHop(id)&&!lib->charge(id)&&!lib->regrowth(id)&&
            !lib->deathRule(id)&&!lib->deathBlast(id)&&!lib->deathCross(id)&&!lib->fireReaction(id)&&!lib->boomFly(id)&&
            !lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->evader(id)&&
            !lib->swimmer(id)&&!lib->environmentActor(id)&&!lib->cardinalWalker(id)&&!lib->spitty(id)&&!lib->maw(id)&&
            !lib->boil(id)&&!lib->sack(id)&&!lib->host(id)&&!lib->mushroom(id),"Brain requires independent grounded actor and exclusive charge/pursuit plus creep");
    }
    for(const auto &[id,p]:lib->leeches_) {
        const auto *d=lib->monster(id);
        require(d&&d->flying&&d->contact&&!d->roomHazard&&d->motion==MonsterMotion::Charge&&d->attack==MonsterAttack::None&&
            d->behavior=="legacy"&&!lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&
            !lib->charge(id)&&!lib->hop(id)&&!lib->targetHop(id)&&!lib->regrowth(id)&&!lib->deathRule(id)&&
            !lib->environmentActor(id)&&!lib->knight(id)&&!lib->mirror(id)&&!lib->guts(id)&&!lib->brain(id)&&!lib->baby(id)&&
            !lib->vis(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->evader(id)&&!lib->swimmer(id)&&
            !lib->maw(id)&&!lib->spitty(id)&&!lib->cardinalWalker(id)&&!lib->host(id)&&!lib->mushroom(id)&&
            !lib->linkedHead(id)&&!lib->buzzFly(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->boil(id)&&!lib->sack(id)&&
            !lib->spider(id)&&!lib->longLegs(id)&&!lib->swarmSpider(id)&&!lib->strider(id)&&!lib->willo(id)&&!lib->eternalFly(id),
            "Leech requires independent flying contact charger without conflicting controller");
        if(p.child)require(lib->eternalFly(p.child)&&lib->monster(p.child)&&!lib->monster(p.child)->natural&&
            lib->deathBlast(id),"Leech orbiter requires Eternal Fly dependency and parent death blast");
    }
    for(const auto &[id,p]:lib->mirrors_) {
        const auto *d=lib->monster(id);
        require(d&&!d->contact&&!d->roomHazard&&d->motion==MonsterMotion::Mirror&&d->attack==MonsterAttack::None&&
            d->behavior=="legacy"&&!lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&
            !lib->hop(id)&&!lib->targetHop(id)&&!lib->charge(id)&&!lib->regrowth(id)&&!lib->deathRule(id)&&
            !lib->environmentActor(id)&&!lib->knight(id)&&!lib->guts(id)&&!lib->baby(id)&&!lib->brain(id)&&
            !lib->vis(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->evader(id)&&!lib->swimmer(id)&&
            !lib->maw(id)&&!lib->spitty(id)&&!lib->cardinalWalker(id)&&!lib->host(id)&&!lib->mushroom(id)&&
            !lib->linkedHead(id)&&!lib->buzzFly(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->boil(id)&&!lib->sack(id),
            "Mirror requires independent non-contact actor without conflicting controller");
    }
    for(const auto &[id,p]:lib->knights_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Charge&&
            d->attack==MonsterAttack::None&&d->behavior=="legacy"&&!lib->monsterBoss(id)&&!lib->component(id)&&
            !lib->companion(id)&&!lib->charge(id)&&!lib->targetHop(id)&&!lib->cardinalWalker(id)&&!lib->brain(id)&&
            !lib->guts(id)&&!lib->vis(id)&&!lib->host(id)&&!lib->mushroom(id)&&!lib->maw(id)&&!lib->spitty(id)&&
            !lib->linkedHead(id)&&!lib->baby(id)&&!lib->evader(id)&&!lib->swimmer(id)&&!lib->environmentActor(id)&&
            !lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->buzzFly(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&
            !lib->statue(id)&&!lib->boil(id)&&!lib->sack(id)&&!lib->spider(id)&&!lib->longLegs(id)&&!lib->swarmSpider(id)&&
            !lib->strider(id)&&!lib->willo(id)&&!lib->hop(id)&&!lib->eternalFly(id)&&!lib->formation(id)&&
            bool(p.recoveryFrames)==bool(p.impactWave.jetStepFrames),"Knight requires independent grounded charger and complete impact wave");
    }
    for(const auto &[id,p]:lib->maskArmor_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&!lib->monsterBoss(id)&&!lib->component(id)&&
            !lib->companion(id)&&!lib->charge(id)&&!lib->host(id)&&!lib->mushroom(id)&&d->behavior=="legacy",
            "Mask armor requires independent grounded actor without conflicting armor");
    }
    for(const auto &[id,p]:lib->linkedRemnants_) {
        const auto *d=lib->monster(id);
        require(d&&!d->roomHazard&&!d->flying&&!lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&
            !lib->linkedHead(id)&&!lib->deathRule(id)&&!lib->lethalMorph(id)&&!lib->regrowth(id)&&
            d->behavior=="legacy","Linked remnant conflicts with actor lifecycle");
        if(id==p.source)require(lib->monster(p.body)&&lib->monster(p.child)&&lib->maskArmor(id)&&lib->targetHop(p.child)&&lib->landingCreep(p.child)&&
            !lib->maskArmor(p.body)&&!lib->monster(p.body)->natural&&
            std::abs(d->radius-lib->monster(p.body)->radius)<.001f,"Linked remnant needs compatible body and landing-creep child");
    }
    for(const auto &[id,p]:lib->landingCreep_)require(lib->targetHop(id)&&!lib->eggy(id)&&!lib->leaper(id)&&
        !lib->hopRings(id),"Landing creep requires destination hop without another landing payload");
    for(const auto &[id,p]:lib->guts_) {
        const auto *d=lib->monster(id);
        require(d&&d->hp>0&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Wall&&
            d->attack==MonsterAttack::None&&d->behavior=="legacy"&&!lib->monsterBoss(id)&&!lib->component(id)&&
            !lib->companion(id)&&!lib->formation(id)&&!lib->hop(id)&&!lib->targetHop(id)&&!lib->charge(id)&&
            !lib->regrowth(id)&&!lib->deathRule(id)&&!lib->deathBlast(id)&&!lib->deathCross(id)&&!lib->fireReaction(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&
            !lib->evader(id)&&!lib->swimmer(id)&&!lib->environmentActor(id)&&!lib->cardinalWalker(id)&&!lib->spitty(id)&&
            !lib->maw(id)&&!lib->brain(id)&&!lib->linkedHead(id)&&!lib->baby(id)&&!lib->boil(id)&&!lib->sack(id)&&
            !lib->host(id)&&!lib->mushroom(id)&&!lib->vis(id)&&!lib->returningBody(id),"Guts needs independent grounded wall follower");
        require(!p.charge||(p.tar&&p.creepInterval>0),"Slog charge needs slowing trail");
    }
    for(const auto &[id,p]:lib->vis_) {
        const auto *d=lib->monster(id);
        const auto *child=lib->returningBody(p.returningBody);
        require(p.returningBody?(child&&child->owner==id&&p.beams==0&&!p.beamConfigured):
            (p.beams>0&&p.beamConfigured),"Vis requires exactly one complete beam or returning-body payload");
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Wander&&d->attack==MonsterAttack::None&&
            d->behavior=="legacy"&&!lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&
            !lib->formation(id)&&!lib->hop(id)&&!lib->targetHop(id)&&!lib->charge(id)&&!lib->regrowth(id)&&!lib->deathRule(id)&&
            !lib->deathBlast(id)&&!lib->deathCross(id)&&!lib->fireReaction(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&
            !lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->evader(id)&&!lib->swimmer(id)&&
            !lib->environmentActor(id)&&!lib->cardinalWalker(id)&&!lib->spitty(id)&&!lib->maw(id)&&!lib->brain(id)&&
            !lib->linkedHead(id)&&!lib->baby(id)&&!lib->boil(id)&&!lib->sack(id)&&!lib->host(id)&&!lib->mushroom(id),
            "Vis requires an independent grounded wanderer");
    }
    for(const auto &[id,p]:lib->returningBodies_) {
        const auto *d=lib->monster(id);const auto *owner=lib->vis(p.owner);
        require(d&&id!=p.owner&&owner&&owner->returningBody==id&&d->hp==0&&d->roomHazard&&!d->natural&&!d->flying&&d->contact&&
            d->motion==MonsterMotion::Still&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            !lib->stageHealth(id)&&!lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->statue(id)&&
            !lib->environmentActor(id)&&!lib->flyBomb(id)&&!lib->vis(id)&&!lib->deathRule(id)&&!lib->deathBlast(id)&&
            !lib->deathCross(id)&&!lib->fireReaction(id)&&!lib->regrowth(id),"Returning body requires zero health and an exclusive reciprocal owner");
    }
    for(const auto &[id,p]:lib->cardinalWalkers_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Wander&&d->attack==MonsterAttack::None&&
            d->behavior=="legacy"&&!lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&
            !lib->hop(id)&&!lib->targetHop(id)&&!lib->charge(id)&&!lib->regrowth(id)&&!lib->deathRule(id)&&!lib->deathBlast(id)&&
            !lib->deathCross(id)&&!lib->fireReaction(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&
            !lib->lobWalker(id)&&!lib->statue(id)&&!lib->evader(id)&&!lib->swimmer(id)&&!lib->environmentActor(id)&&
            !lib->spitty(id)&&!lib->maw(id)&&!lib->boil(id)&&!lib->sack(id)&&!lib->host(id)&&!lib->mushroom(id),
            "Cardinal walker requires an independent grounded contact-only wanderer");
    }
    for(const auto &[id,p]:lib->spitties_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Wander&&d->attack==MonsterAttack::Spitty&&
            d->behavior=="legacy"&&!lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&
            !lib->hop(id)&&!lib->targetHop(id)&&!lib->charge(id)&&!lib->regrowth(id)&&!lib->deathRule(id)&&!lib->deathBlast(id)&&
            !lib->deathCross(id)&&!lib->fireReaction(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&
            !lib->lobWalker(id)&&!lib->statue(id)&&!lib->evader(id)&&!lib->swimmer(id)&&!lib->environmentActor(id),
            "Spitty requires an independent grounded wanderer");
        require(p.shot.configured,"Spitty requires primary flight");
        const bool tainted=p.kind==SpittyKind::Tainted;
        require(p.burst.configured==tainted&&p.death.configured==tainted&&p.streamConfigured==tainted&&
            p.burstConfigured==tainted&&p.deathConfigured==tainted,"Spitty family payload is incomplete");
        require(p.shot.gravity+p.streamGravityStep*float(p.streamCount-1)>0,"Spitty stream must eventually land");
    }
    for(const auto &[id,p]:lib->maws_) {
        const auto *d=lib->monster(id);
        require(d&&d->flying&&!d->roomHazard&&d->motion==MonsterMotion::Chase&&d->behavior=="legacy"&&
            d->attack==(p.shoots?MonsterAttack::Shot:MonsterAttack::None)&&!lib->monsterBoss(id)&&!lib->buzzFly(id)&&
            !lib->component(id)&&!lib->companion(id)&&!lib->hop(id)&&!lib->charge(id)&&!lib->formation(id),"Maw requires independent flying chaser");
        if(p.child)require(lib->eternalFly(p.child),"Maw requires an Eternal Fly dependency");
    }
    for(const auto &[id,p]:lib->eternalFlies_) {
        const auto *d=lib->monster(id);const auto *released=lib->monster(p.released);
        require(d&&d->flying&&d->roomHazard&&d->motion==MonsterMotion::Orbit&&d->attack==MonsterAttack::None&&
            d->behavior=="legacy"&&released&&released->flying&&!released->roomHazard&&lib->buzzFly(p.released)&&
            !lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id),"Eternal Fly requires orbit hazard and released buzzing actor");
    }
    for(const auto &[id,p]:lib->enemyStatuses_) {
        require(lib->monster(id)&&
            (lib->gapers_.contains(id)||lib->headless_.contains(id)||lib->headShooters_.contains(id)),
            "Status effects require a reviewed Gaper, headless or stationary shooter controller");
        require(bool(p.fear)==(lib->gapers_.contains(id)||lib->headless_.contains(id)),
            "Moving status recipients need fear motion; stationary recipients must not have it");
    }
    for(const auto &[id,p]:lib->headShooters_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->motion==MonsterMotion::Still&&d->speed==0&&
            d->attack==MonsterAttack::Shot&&d->behavior=="legacy"&&!lib->monsterBoss(id)&&!lib->component(id)&&
            !lib->companion(id)&&!lib->formation(id)&&!lib->hop(id)&&!lib->charge(id)&&!lib->regrowth(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->lobWalker(id)&&!lib->statue(id),
            "Stationary shooter requires an independent grounded stationary shot actor");
    }
    for(const auto &[id,p]:lib->hosts_) {
        require(p.slam?(p.volley.empty()&&p.motion==HostMotion::Still&&p.armored&&p.shootFrame==p.closeFrame):
            (!p.volley.empty()&&p.shootFrame<p.closeFrame),"Host needs a volley before closing or a stationary armored slam on closing");
        const auto *d=lib->monster(id);
        require(d&&!d->roomHazard&&d->behavior=="legacy"&&d->attack==MonsterAttack::Spread&&
            d->flying==(p.motion==HostMotion::Float)&&d->contact==(p.contact>0)&&
            d->motion==(p.motion==HostMotion::Still?MonsterMotion::Still:p.motion==HostMotion::Walk?MonsterMotion::Chase:MonsterMotion::Bounce)&&
            (p.motion==HostMotion::Still?(d->speed==0&&p.force==0):(d->speed>0&&p.force>0))&&
            !lib->maw(id)&&!lib->headShooter(id)&&!lib->buzzFly(id)&&!lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&
            !lib->hop(id)&&!lib->formation(id)&&!lib->charge(id)&&!lib->regrowth(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&
            !lib->lobWalker(id)&&!lib->statue(id)&&!lib->eternalFly(id),"Host requires an independent configured body");
    }
    for(const auto &[id,p]:lib->mushrooms_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->motion==MonsterMotion::Still&&d->speed==0&&
            d->attack==MonsterAttack::Spread&&d->behavior=="legacy"&&d->contact==(p.contact>0)&&
            !lib->host(id)&&!lib->maw(id)&&!lib->headShooter(id)&&!lib->buzzFly(id)&&!lib->monsterBoss(id)&&
            !lib->component(id)&&!lib->companion(id)&&!lib->hop(id)&&!lib->formation(id)&&!lib->charge(id)&&
            !lib->regrowth(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->lobWalker(id)&&!lib->statue(id),
            "Mushroom requires an independent grounded stationary spread actor");
    }
    for(const auto &[id,p]:lib->lobWalkers_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->attack==MonsterAttack::Lob&&d->behavior=="legacy"&&
            ((d->motion==MonsterMotion::Chase&&p.attackFrames>0)||(d->motion==MonsterMotion::Wander&&p.attackFrames==0))&&
            !lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&!lib->hop(id)&&
            !lib->charge(id)&&!lib->regrowth(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&p.flightConfigured,
            "Lob walker requires an independent ground actor and a complete flight profile");
    }
    for(const auto &[id,p]:lib->sourceImmunities_) {
        const auto *d=lib->monster(id);
        require(d&&!d->roomHazard&&!lib->monsterBoss(id)&&!lib->component(id),"Source immunity requires an independent ordinary actor");
    }
    for(const auto &[id,p]:lib->lethalMorphs_) {
        const auto *d=lib->monster(id);
        const auto ordinary=[&](MonsterId key,const MonsterDefinition *body) {
            return body&&!body->roomHazard&&!lib->monsterBoss(key)&&!lib->component(key)&&!lib->companion(key)&&
                !lib->formation(key)&&!lib->hop(key)&&!lib->charge(key)&&!lib->regrowth(key)&&!lib->boomFly(key)&&!lib->flyBomb(key);
        };
        const auto compatible=[&](MonsterId key) {
            const auto *target=lib->monster(key);
            return id!=key&&ordinary(key,target)&&!lib->lethalMorph(key)&&
                d->flying==target->flying&&std::abs(d->radius-target->radius)<.001f;
        };
        require(ordinary(id,d)&&compatible(p.target)&&
            !lib->deathRule(id)&&!lib->deathBlast(id)&&!lib->deathCross(id)&&!lib->fireReaction(id),
            "Lethal morph requires compatible independent bodies without another exclusive death controller or a morph cycle");
        for(const auto &[target,weight]:p.choices)require(compatible(target),"Incompatible weighted morph target");
        require(p.choices.empty()||std::any_of(p.choices.begin(),p.choices.end(),[&](const auto &x){return x.first==p.target;}),
            "Weighted morph choices must include the default target");
    }
    for(const auto &[id,p]:lib->deathBlasts_) {
        const auto *d=lib->monster(id);
        require(d&&!d->roomHazard&&!lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->deathCross(id)&&!lib->regrowth(id),
            "Death blast requires an independent ordinary actor without another exclusive death controller");
        require(p.bomb.empty()||(lib->enemyBomb(p.bomb)&&lib->enemyBomb(p.bomb)->fuse>0),"Death bomb requires a registered positive-fuse profile");
    }
    for(const auto &[id,p]:lib->deathCrosses_) {
        const auto *d=lib->monster(id);
        require(d&&d->flying&&d->motion==MonsterMotion::Chase&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            !lib->deathRule(id)&&!lib->regrowth(id)&&!lib->monsterBoss(id),"Death cross requires independent pursuing flyer");
    }
    for(auto &[key,layout]:lib->railLayouts_) {
        try{layout.compile();}catch(const std::exception &e){throw std::runtime_error("Rail layout "+key+": "+e.what());}
    }
    for(const auto &[key,p]:lib->enemyBombs_)
        require(p.payload==EnemyBombPayload::Blast||p.effectConfigured,"Enemy bomb payload requires its effect configuration: "+key);
    for(const auto &[id,p]:lib->flyBombs_) {
        const auto *d=lib->monster(id),*owner=lib->monster(p.orbitOwner);
        require(d&&d->flying&&d->contact&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&d->speed>0&&
            !lib->monsterBoss(id)&&!lib->component(id)&&!lib->formation(id)&&!lib->hop(id)&&!lib->charge(id)&&!lib->companion(id)&&
            !lib->deathCross(id)&&!lib->deathRule(id)&&!lib->regrowth(id),"Fly bomb needs an independent contact flyer and explicit death controller");
        require(p.orbitOwner?(owner&&owner->flying&&!owner->roomHazard&&!lib->flyBomb(p.orbitOwner)&&p.orbitOwner!=id&&
                d->motion==MonsterMotion::Orbit&&d->roomHazard&&!d->natural&&p.orbitRadius>owner->radius+d->radius):
                (d->motion==MonsterMotion::Chase&&!d->roomHazard),"Invalid fly bomb owner or pursuit body");
    }
    for(const auto &[id,p]:lib->stageHealth_) {
        const auto *d=lib->monster(id);
        require(d&&!lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->regrowth(id)&&
            std::abs(d->hp-lib->monsterHealth(id,1))<.001f,"Stage health needs an independent actor with matching stage-one fallback HP");
    }
    for(size_t i=1;i<lib->sourceStages_.size();++i)
        require(lib->sourceStages_[i][0]>=lib->sourceStages_[i-1][1],"Source stage mapping must progress across bands");
    for(const auto &[id,p]:lib->boomFlies_) {
        const auto *d=lib->monster(id);
        require(d&&d->flying&&d->contact&&!d->roomHazard&&d->speed>0&&d->motion==MonsterMotion::Bounce&&d->attack==MonsterAttack::None&&
            d->behavior=="legacy"&&!lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&!lib->hop(id)&&
            !lib->charge(id)&&!lib->flyBomb(id)&&!lib->statue(id)&&!lib->deathCross(id)&&!lib->deathRule(id)&&!lib->regrowth(id),
            "Boom Fly requires an independent diagonal contact flyer and explicit death controller");
        const bool shots=p.kind==BoomFlyKind::Red||p.kind==BoomFlyKind::Drowned||p.kind==BoomFlyKind::Bone||p.kind==BoomFlyKind::Sick;
        const bool field=p.kind==BoomFlyKind::Dragon||p.kind==BoomFlyKind::Sick||p.kind==BoomFlyKind::Tainted;
        require(p.shotsConfigured==shots&&p.fieldConfigured==field,"Boom Fly variant needs its matching shots/field configuration");
        require(p.kind!=BoomFlyKind::Tainted||!d->natural,"Tainted Boom Fly requires a dedicated encounter, not an ordinary pool");
        if(p.kind==BoomFlyKind::Drowned) {
            const auto *child=lib->monster(p.child);
            require(child&&!child->flying&&!child->roomHazard&&!lib->monsterBoss(p.child)&&!lib->component(p.child)&&!lib->companion(p.child),
                "Drowned Boom Fly requires an independent ground child");
        }
    }
    for(const auto &[id,s]:lib->statues_) {
        const auto *d=lib->monster(id);
        require(d&&d->roomHazard&&!d->flying&&!d->contact&&d->speed==0&&d->motion==MonsterMotion::Still&&d->behavior=="legacy"&&
            !lib->component(id)&&!lib->monsterBoss(id)&&!lib->formation(id)&&!lib->hop(id)&&!lib->charge(id)&&!lib->companion(id),"Statue requires an independent stationary non-contact hazard");
        require(!lib->deathRule(id)&&!lib->regrowth(id),"Statue requires explicit exceptional-death policy");
        require(s.attack!=StatueAttack::Attraction||s.attractionConfigured,"Attraction statue requires force parameters");
        require(s.attack!=StatueAttack::Quake||s.quakeConfigured,"Quake statue requires wave parameters");
        require(s.attack!=StatueAttack::Supply||s.supplyConfigured,"Supply statue requires bomb parameters");
    }
    for(size_t band=0;band<lib->statuePools_.size();++band) {
        auto &pool=lib->statuePools_[band];
        for(const auto &e:pool)require(lib->statue(e.monster),"Statue pool needs a configured hazard");
        std::sort(pool.begin(),pool.end(),[](const auto &a,const auto &b){return std::tie(a.monster,a.pattern)<std::tie(b.monster,b.pattern);});
        require(!lib->statueChances_[band]||std::any_of(pool.begin(),pool.end(),[](const auto &e){return e.weight>0;}),"Enabled statue rooms need a positive pool");
    }
    for(const auto &[id,c]:lib->companions_) {
        const auto *d=lib->monster(id);
        require(d&&lib->charge(id)&&!d->natural&&!d->roomHazard&&!lib->monsterBoss(id)&&!lib->component(id),
            "Companion requires a non-pool independent charge actor");
        require(!lib->deathRule(id)&&!lib->regrowth(id),"Companion death recipes require explicit allied offspring support");
    }
    for(const auto &f:lib->contactFamiliars_)
        require(lib->item(f.item)&&lib->companion(f.child),"Contact familiar needs an installed item and companion child");
    std::sort(lib->contactFamiliars_.begin(),lib->contactFamiliars_.end(),[](const auto &a,const auto &b){return a.item<b.item;});
    for(const auto &[id,c]:lib->charges_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->motion==MonsterMotion::Charge&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            !lib->monsterBoss(id)&&!lib->formation(id)&&!lib->hop(id)&&!lib->component(id),"Charge requires an independent grounded contact actor");
    }
    for(const auto &[id,p]:lib->bloats_) {
        const auto *d=lib->monster(id);const auto *eye=lib->component(p.eye);const auto *child=lib->monster(p.charger);
        require(d&&eye&&eye->owner==id&&child&&lib->charge(p.charger)&&!d->natural&&!d->roomHazard&&!d->flying&&d->behavior=="legacy"&&
            d->motion==MonsterMotion::Still&&d->attack==MonsterAttack::None&&!lib->peep(id)&&!lib->hop(id)&&!lib->formation(id),
            "Bloat requires a dedicated grounded boss, owned eye and configured Charger");
        require(lib->bloatLasers_.contains(id)&&lib->bloatIpecac_.contains(id),"Bloat requires laser and Ipecac configuration");
    }
    for(size_t band=0;band<lib->bossPools_.size();++band) {
        auto &pool=lib->bossPools_[band];
        for(const auto &e:pool){require(lib->monsterBoss(e.monster),"Boss pool references an unsupported controller");
            require(lib->bossFormAllowed(e.monster,e.form),"Boss pool form is incompatible with controller");}
        std::sort(pool.begin(),pool.end(),[](const auto &a,const auto &b){return std::tie(a.monster,a.form,a.variant)<std::tie(b.monster,b.form,b.variant);});
    }
    for(size_t band=0;band<lib->floorVariants_.size();++band) {
        auto &variants=lib->floorVariants_[band];
        if(variants.empty())variants[FloorVariant::Standard]=1;
        require(std::any_of(variants.begin(),variants.end(),[](const auto &v){return v.second>0;}),"Floor variants need positive total weight");
        for(const auto &[variant,weight]:variants)if(weight>0) {
            int total=lib->nativeBossWeights_[band];
            for(const auto &boss:lib->bossPools_[band])if(!boss.variant||*boss.variant==variant)total+=boss.weight;
            require(total>0,"Boss pool needs positive total weight for each enabled floor variant");
        }
    }
    for(size_t i=0;i<lib->replacements_.size();++i) {
        const auto &r=lib->replacements_[i];const auto *from=lib->monster(r.source),*to=lib->monster(r.target);
        const auto linked=[](MonsterId id){return id.type==35||id.type==96||id==monsterId(26,2)||id==monsterId(55,2)||id==monsterId(41,3);};
        require(from&&to&&r.source!=r.target&&from->natural&&to->natural&&!from->roomHazard&&!to->roomHazard&&
            !lib->formation(r.source)&&!lib->formation(r.target)&&!linked(r.source)&&!linked(r.target)&&
            from->motion!=MonsterMotion::Chain&&to->motion!=MonsterMotion::Chain,
            "Replacement requires distinct independent natural monsters");
        if(r.allSpawns)for(const auto &other:lib->replacements_)
            require(!other.allSpawns||r.target!=other.source,"Spawn replacements must not chain or cycle");
        for(size_t j=0;j<i;++j) {
            const auto &other=lib->replacements_[j];
            require(r.phase!=other.phase||r.source!=other.source||r.firstBand>other.lastBand||other.firstBand>r.lastBand||
                (r.variant&&other.variant&&r.variant!=other.variant),"Overlapping monster replacement conditions");
        }
    }
    for(size_t band=0;band<lib->encounters_.size();++band)for(auto &pool:lib->encounters_[band]) {
        for(auto *entries:{&pool.basics,&pool.specialists}) {
            for(const auto &entry:*entries) {
                const auto *d=lib->monster(entry.monster);
                require(d,"Unknown encounter monster "+monsterIdText(entry.monster));
                require(d->natural&&!d->roomHazard,"Encounter pool cannot independently spawn component/hazard "+monsterIdText(entry.monster));
                if(entry.members>1)for(const auto &rule:lib->replacements_)
                    require(rule.allSpawns||rule.source!=entry.monster||int(band)<rule.firstBand||int(band)>rule.lastBand,
                        "Replacement cannot split a grouped encounter");
            }
            std::sort(entries->begin(),entries->end(),[](const auto &a,const auto &b){return a.monster<b.monster;});
        }
        require(std::any_of(pool.basics.begin(),pool.basics.end(),[&](const auto &e){return e.weight>0&&e.cost==1&&e.maximum==0&&e.members==1&&!e.variant&&
            std::all_of(lib->floorVariants_[band].begin(),lib->floorVariants_[band].end(),[&](const auto &v){FloorProfile p;p.band=int(band);p.variant=v.first;return lib->replacementCost(e.monster,p)==0;});}),
                "Encounter pool needs an unlimited positive-weight cost-1 single-actor basic in band "+std::to_string(band));
        require(std::any_of(pool.specialists.begin(),pool.specialists.end(),[](const auto &e){return e.weight>0&&!e.variant;}),
                "Encounter pool needs a positive-weight specialist in band "+std::to_string(band));
    }
    for(const auto &[id,p]:lib->longLegs_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&d->contact&&!d->roomHazard&&d->behavior=="legacy"&&
            d->motion==(p.flee?MonsterMotion::Flee:MonsterMotion::Chase)&&d->attack==(p.flee?MonsterAttack::Spawn:MonsterAttack::Ring)&&
            !lib->spider(id)&&!lib->strider(id)&&!lib->swarmSpider(id)&&!lib->evader(id)&&!lib->swimmer(id)&&!lib->hop(id)&&
            !lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->monsterBoss(id)&&!lib->statue(id),"Long Legs needs independent ground body");
        require(!p.child||lib->monster(p.child),"Long Legs child missing");
        require(!p.child||lib->spider(p.child)||lib->sack(p.child),"Long Legs needs reviewed Spider or Sack child");
    }
    for(const auto &[id,p]:lib->sacks_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->contact&&!d->roomHazard&&d->behavior=="legacy"&&d->speed==0&&
            d->motion==MonsterMotion::Still&&d->attack==MonsterAttack::Spawn&&!lib->longLegs(id)&&!lib->boil(id)&&
            !lib->headShooter(id)&&!lib->statue(id)&&!lib->environmentActor(id)&&!lib->monsterBoss(id)&&
            p.initialHealth*p.healthScale<=d->hp&&lib->spider(p.child),"Sack needs stationary regenerating body and Spider child");
    }
    for(const auto &[id,p]:lib->boils_) {
        const auto *d=lib->monster(id);const bool spider=p.payload==BoilPayload::Spider,explosive=p.payload==BoilPayload::Ipecac;
        require(d&&!d->flying&&!d->roomHazard&&d->contact==p.walking&&d->behavior=="legacy"&&
            d->motion==(p.walking?MonsterMotion::Wander:MonsterMotion::Still)&&
            d->attack==(spider?MonsterAttack::Spawn:explosive?MonsterAttack::Lob:MonsterAttack::Burst)&&
            (p.walking?p.force>0&&p.contactDamage>0:d->speed==0&&p.contactDamage==0)&&
            p.cycle.initialHealth*p.cycle.healthScale<=d->hp&&!lib->sack(id)&&!lib->longLegs(id)&&
            !lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->monsterBoss(id)&&!lib->environmentActor(id),
            "Boil needs independent stationary/growing or walking body");
        require(spider?bool(lib->spider(p.cycle.child))&&!p.projectilesConfigured:!p.cycle.child&&p.projectilesConfigured,
            "Boil needs configured projectiles or a reviewed Spider child");
        require(!p.projectilesConfigured||(explosive?p.shotMinimum==1&&p.shotMaximum==1&&p.blastRadius>0&&p.blastDamage>0:
            p.blastRadius==0&&p.blastDamage==0),"Invalid Boil payload contract");
    }
    auto spiderBody=[&](MonsterId id,MonsterMotion motion) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==motion&&d->attack==MonsterAttack::None&&
            d->behavior=="legacy"&&!lib->spider(id)&&!lib->swimmer(id)&&!lib->willo(id)&&!lib->evader(id)&&!lib->hop(id)&&
            !lib->charge(id)&&!lib->formation(id)&&!lib->regrowth(id)&&!lib->component(id)&&!lib->companion(id)&&
            !lib->monsterBoss(id)&&!lib->segmentedBoss(id)&&!lib->shell(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&
            !lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->buzzFly(id),"Spider variant requires independent contact body");
    };
    for(const auto &[id,p]:lib->striders_){spiderBody(id,MonsterMotion::Wander);require(!lib->swarmSpider(id),"Conflicting spider variants");}
    for(const auto &[id,p]:lib->swarmSpiders_){spiderBody(id,MonsterMotion::Hop);require(!lib->strider(id),"Conflicting spider variants");}
    for(const auto &[id,p]:lib->gapers_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->shape==MonsterShape::Walker&&
            d->motion==MonsterMotion::Chase&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            !lib->headless(id)&&!lib->faceless(id)&&!lib->danny(id)&&!lib->hardy(id)&&!lib->spider(id)&&!lib->strider(id)&&!lib->swarmSpider(id)&&!lib->longLegs(id)&&!lib->sack(id)&&!lib->boil(id)&&!lib->rockSpider(id)&&
            !lib->slide(id)&&!lib->charge(id)&&!lib->monsterBoss(id)&&!lib->segmentedBoss(id)&&!lib->deathRule(id)&&
            !lib->evader(id)&&!lib->hop(id)&&!lib->formation(id)&&!lib->regrowth(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->shell(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->buzzFly(id)&&!lib->mirror(id)&&!lib->swimmer(id),
            "Gaper requires independent grounded contact chaser");
    }
    for(const auto &[id,p]:lib->lepers_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact==(id.subtype>0)&&d->shape==MonsterShape::Walker&&
            d->motion==MonsterMotion::Chase&&d->attack==MonsterAttack::Spawn&&d->behavior=="legacy"&&
            !lib->evader(id)&&!lib->gaper(id)&&!lib->blackGlobin(id)&&!lib->rottenGaper(id)&&!lib->headless(id)&&!lib->faceless(id)&&
            !lib->danny(id)&&!lib->hardy(id)&&!lib->hop(id)&&!lib->spider(id)&&!lib->strider(id)&&!lib->swarmSpider(id)&&
            !lib->lethalMorph(id)&&!lib->deathRule(id)&&!lib->deathBlast(id)&&!lib->deathCross(id)&&!lib->regrowth(id)&&
            !lib->fireReaction(id)&&!lib->adaptiveArmor(id)&&!lib->formation(id)&&!lib->component(id)&&!lib->companion(id)&&
            !lib->monsterBoss(id)&&!lib->segmentedBoss(id)&&!lib->shell(id)&&!lib->slide(id)&&!lib->charge(id)&&
            !lib->brain(id)&&!lib->guts(id)&&!lib->targetHop(id)&&!lib->smallMaggot(id)&&!lib->rockSpider(id)&&!lib->longLegs(id)&&!lib->boil(id)&&!lib->sack(id),
            "Leper requires independent grounded body with exclusive staged damage and mortality");
        require(p.evadeConfigured&&p.creepConfigured&&lib->leperFlesh(p.flesh)&&lib->headless(p.gusher)&&lib->headless(p.gusher)->shooter,
            "Leper requires evasion, creep, Flesh and shooting Gusher controllers");
        for(int stage=0;stage<4;++stage) {
            const auto *next=lib->leper(monsterId(id.type,id.variant,stage));
            require(next&&next->flesh==p.flesh&&next->gusher==p.gusher,"Leper requires all four compatible form profiles");
        }
    }
    for(const auto &[id,p]:lib->leperFlesh_) {
        const auto *d=lib->monster(id);
        require(d&&d->flying&&!d->roomHazard&&d->contact&&d->shape==MonsterShape::Blob&&
            d->motion==MonsterMotion::Chase&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            !lib->deathRule(id)&&!lib->lethalMorph(id)&&!lib->deathBlast(id)&&!lib->deathCross(id)&&
            !lib->regrowth(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&
            !lib->leech(id)&&!lib->adultLeech(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&
            !lib->buzzFly(id)&&!lib->evader(id)&&!lib->mirror(id)&&!lib->eternalFly(id)&&!lib->monsterBoss(id)&&
            !lib->segmentedBoss(id)&&!lib->shell(id),"Leper Flesh requires independent floating contact body with its own death shot");
    }
    for(const auto &[id,p]:lib->blackGlobins_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->shape==MonsterShape::Walker&&
            d->motion==MonsterMotion::Chase&&d->attack==MonsterAttack::Spawn&&d->behavior=="legacy"&&
            !lib->gaper(id)&&!lib->rottenGaper(id)&&!lib->smallMaggot(id)&&!lib->headless(id)&&!lib->faceless(id)&&!lib->danny(id)&&!lib->hardy(id)&&
            !lib->spider(id)&&!lib->strider(id)&&!lib->swarmSpider(id)&&!lib->longLegs(id)&&!lib->sack(id)&&!lib->boil(id)&&!lib->rockSpider(id)&&
            !lib->slide(id)&&!lib->charge(id)&&!lib->monsterBoss(id)&&!lib->segmentedBoss(id)&&!lib->deathRule(id)&&!lib->lethalMorph(id)&&
            !lib->evader(id)&&!lib->hop(id)&&!lib->formation(id)&&!lib->regrowth(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->shell(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->buzzFly(id)&&!lib->mirror(id)&&!lib->swimmer(id)&&
            !lib->cardinalWalker(id)&&!lib->leech(id)&&!lib->adultLeech(id)&&!lib->spitty(id)&&!lib->brain(id)&&!lib->guts(id)&&!lib->targetHop(id),
            "Black Globin requires independent grounded chaser with its own mortality");
        require(lib->spider(p.spider)&&lib->brain(p.head)&&lib->brain(p.head)->pursuit&&
            lib->headless(p.body)&&lib->headless(p.body)->broodChild==p.spider&&
            p.head!=id&&p.body!=id&&p.head!=p.body,"Black Globin needs Spider, pursuing head and brood body controllers");
    }
    for(const auto &[id,p]:lib->rottenGapers_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->shape==MonsterShape::Walker&&
            d->motion==MonsterMotion::Chase&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            !lib->gaper(id)&&!lib->smallMaggot(id)&&!lib->headless(id)&&!lib->faceless(id)&&!lib->danny(id)&&!lib->hardy(id)&&
            !lib->spider(id)&&!lib->strider(id)&&!lib->swarmSpider(id)&&!lib->longLegs(id)&&!lib->sack(id)&&!lib->boil(id)&&!lib->rockSpider(id)&&
            !lib->slide(id)&&!lib->charge(id)&&!lib->monsterBoss(id)&&!lib->segmentedBoss(id)&&!lib->deathRule(id)&&!lib->lethalMorph(id)&&
            !lib->evader(id)&&!lib->hop(id)&&!lib->formation(id)&&!lib->regrowth(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->shell(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->buzzFly(id)&&!lib->mirror(id)&&!lib->swimmer(id)&&
            !lib->cardinalWalker(id)&&!lib->leech(id)&&!lib->adultLeech(id)&&!lib->spitty(id)&&!lib->brain(id)&&!lib->guts(id)&&!lib->targetHop(id),
            "Rotten Gaper requires independent grounded contact chaser");
        require(p.brood==(id.subtype==3)&&p.orbit==(id.subtype==5),"Missing Rotten subtype behavior");
        if(p.brood)require(lib->smallMaggot(p.child)!=nullptr,"Rotten brood requires Small Maggot controller");
        if(id.subtype==0)for(int subtype=1;subtype<=5;++subtype)
            require(lib->rottenGaper(monsterId(id.type,id.variant,subtype)),"Rotten default requires all five subtype profiles");
    }
    for(const auto &[id,p]:lib->smallMaggots_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->shape==MonsterShape::Worm&&
            d->motion==MonsterMotion::Chase&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            !lib->gaper(id)&&!lib->headless(id)&&!lib->faceless(id)&&!lib->danny(id)&&!lib->hardy(id)&&!lib->spider(id)&&!lib->strider(id)&&!lib->swarmSpider(id)&&!lib->longLegs(id)&&!lib->sack(id)&&!lib->boil(id)&&!lib->rockSpider(id)&&
            !lib->slide(id)&&!lib->charge(id)&&!lib->monsterBoss(id)&&!lib->segmentedBoss(id)&&!lib->deathRule(id)&&!lib->lethalMorph(id)&&
            !lib->evader(id)&&!lib->hop(id)&&!lib->formation(id)&&!lib->regrowth(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->shell(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->buzzFly(id)&&!lib->mirror(id)&&!lib->swimmer(id)&&
            !lib->cardinalWalker(id)&&!lib->leech(id)&&!lib->adultLeech(id)&&!lib->spitty(id)&&!lib->brain(id)&&!lib->guts(id)&&!lib->targetHop(id),
            "Small Maggot requires independent grounded contact crawler");
    }
    for(const auto &[id,p]:lib->headless_) {
        const auto *d=lib->monster(id);
        require(d&&p.shooter==p.shotConfigured&&!d->flying&&!d->roomHazard&&d->contact&&d->shape==MonsterShape::Headless&&
            d->motion==MonsterMotion::Wander&&d->attack==(p.broodChild?MonsterAttack::Spawn:MonsterAttack::None)&&d->behavior=="legacy"&&
            !lib->faceless(id)&&!lib->danny(id)&&!lib->hardy(id)&&!lib->spider(id)&&!lib->strider(id)&&!lib->swarmSpider(id)&&!lib->longLegs(id)&&!lib->sack(id)&&!lib->boil(id)&&!lib->rockSpider(id)&&
            !lib->slide(id)&&!lib->charge(id)&&!lib->monsterBoss(id)&&!lib->segmentedBoss(id)&&!lib->deathRule(id)&&!lib->lethalMorph(id)&&
            !lib->evader(id)&&!lib->hop(id)&&!lib->formation(id)&&!lib->regrowth(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->shell(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->buzzFly(id)&&!lib->mirror(id),"Headless requires independent grounded contact wanderer");
        if(p.broodChild)require(!p.shooter&&lib->spider(p.broodChild),"Headless brood requires a Spider controller");
    }
    for(const auto &[id,p]:lib->faceless_) {
        const auto *d=lib->monster(id),*gusher=lib->monster(p.gusher),*pacer=lib->monster(p.pacer);
        require(p.shotConfigured&&d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Wander&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            !lib->spider(id)&&!lib->strider(id)&&!lib->swarmSpider(id)&&!lib->longLegs(id)&&!lib->sack(id)&&!lib->boil(id)&&!lib->danny(id)&&!lib->hardy(id)&&!lib->rockSpider(id)&&
            !lib->slide(id)&&!lib->charge(id)&&!lib->monsterBoss(id)&&!lib->segmentedBoss(id)&&!lib->deathRule(id)&&!lib->lethalMorph(id)&&
            !lib->evader(id)&&!lib->hop(id)&&!lib->formation(id)&&!lib->regrowth(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->shell(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->buzzFly(id)&&!lib->mirror(id),"Faceless requires independent grounded contact wanderer");
        require(gusher&&pacer&&p.gusher!=id&&p.pacer!=id&&p.gusher!=p.pacer&&
            !gusher->flying&&!pacer->flying&&!gusher->roomHazard&&!pacer->roomHazard&&
            gusher->shape==MonsterShape::Headless&&pacer->shape==MonsterShape::Headless&&
            gusher->radius<=d->radius&&pacer->radius<=d->radius,"Faceless needs compatible grounded headless replacements");
    }
    for(const auto &[id,p]:lib->dannies_) {
        const auto *d=lib->monster(id),*child=lib->monster(p.child);
        require(p.payloadConfigured&&d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Chase&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            !lib->slide(id)&&!lib->charge(id)&&!lib->hardy(id)&&!lib->rockSpider(id)&&!lib->monsterBoss(id)&&!lib->deathRule(id)&&!lib->lethalMorph(id)&&
            !lib->evader(id)&&!lib->hop(id)&&!lib->formation(id)&&!lib->regrowth(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->shell(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->buzzFly(id),"Danny requires independent grounded contact chaser");
        const auto *rock=lib->rockSpider(p.child),*coal=lib->rockSpider(p.coalBody);const auto *environment=lib->environmentActor(p.coalBody);
        require(child&&!child->roomHazard&&rock&&(p.coal?bool(rock->deathChild):bool(rock->deathMorph))&&
            coal&&environment&&environment->kind==EnvironmentActorKind::HotCoal,"Danny requires actual Rock/Coal Spider and Hot Coal dependencies");
    }
    for(const auto &[id,p]:lib->hardies_) {
        const auto *d=lib->monster(id);
        require(p.payloadConfigured&&d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Charge&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            !lib->slide(id)&&!lib->charge(id)&&!lib->rockSpider(id)&&!lib->monsterBoss(id)&&!lib->deathRule(id)&&!lib->lethalMorph(id),"Hardy requires independent impact charger");
        require(lib->slide(p.child)&&!lib->slide(p.child)->targeted&&lib->rockSpider(p.rock)&&lib->rockSpider(p.rock)->deathMorph,"Hardy requires actual Dip and normal Rock Spider children");
    }
    for(const auto &[id,p]:lib->rockSpiders_) {
        const auto *d=lib->monster(id);const auto *environment=lib->environmentActor(id);
        const bool coal=environment&&environment->kind==EnvironmentActorKind::HotCoal;
        require(d&&!d->flying&&d->contact&&d->attack==MonsterAttack::None&&d->behavior=="legacy"&&
            (coal?d->roomHazard&&d->motion==MonsterMotion::Still&&p.force==0:
                !d->roomHazard&&d->motion==MonsterMotion::Wander&&p.force>0)&&
            !lib->spider(id)&&!lib->strider(id)&&!lib->swarmSpider(id)&&!lib->evader(id)&&!lib->hop(id)&&
            !lib->charge(id)&&!lib->formation(id)&&!lib->regrowth(id)&&!lib->component(id)&&!lib->companion(id)&&
            !lib->monsterBoss(id)&&!lib->segmentedBoss(id)&&!lib->shell(id)&&!lib->deathRule(id)&&!lib->lethalMorph(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->buzzFly(id),
            "Rock Spider requires independent skitter body or Hot Coal hazard");
        require(!p.deathMorph||(lib->spider(p.deathMorph)&&lib->monster(p.deathMorph)->radius<=d->radius),"Rock Spider morph requires smaller ordinary Spider");
        require(!p.deathChild||(lib->environmentActor(p.deathChild)&&lib->environmentActor(p.deathChild)->kind==EnvironmentActorKind::HotCoal),"Coal Spider needs real Hot Coal child");
        if(id.subtype==0)for(int shape=1;shape<=3;++shape) {
            const auto target=monsterId(id.type,id.variant,shape);const auto *next=lib->monster(target);
            require(next&&lib->rockSpider(target)&&next->hp==d->hp&&next->radius==d->radius,"Rock subtype selector requires three compatible profiles");
        }
    }
    for(const auto &[id,p]:lib->spiders_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Wander&&d->attack==MonsterAttack::None&&
            d->behavior=="legacy"&&!lib->evader(id)&&!lib->hop(id)&&!lib->charge(id)&&!lib->formation(id)&&!lib->regrowth(id)&&
            !lib->component(id)&&!lib->companion(id)&&!lib->monsterBoss(id)&&!lib->segmentedBoss(id)&&!lib->shell(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->buzzFly(id),
            "Spider requires independent grounded contact wanderer");
    }
    for(const auto &[id,p]:lib->willos_) {
        const auto *d=lib->monster(id);
        require(d&&d->flying&&!d->roomHazard&&!d->contact&&d->motion==MonsterMotion::Orbit&&d->attack==MonsterAttack::Shot&&
            d->behavior=="legacy"&&!lib->evader(id)&&!lib->hop(id)&&!lib->charge(id)&&!lib->formation(id)&&!lib->regrowth(id)&&
            !lib->component(id)&&!lib->companion(id)&&!lib->monsterBoss(id)&&!lib->segmentedBoss(id)&&!lib->shell(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&!lib->buzzFly(id),
            "Willo requires independent harmless flying orbit shooter");
    }
    for(const auto &[id,p]:lib->swimmers_) {
        const auto *d=lib->monster(id);
        require(d&&!d->flying&&!d->roomHazard&&d->contact&&d->motion==MonsterMotion::Chase&&d->attack==MonsterAttack::None&&
            d->behavior=="legacy"&&!lib->evader(id)&&!lib->hop(id)&&!lib->charge(id)&&!lib->formation(id)&&!lib->regrowth(id)&&
            !lib->component(id)&&!lib->companion(id)&&!lib->monsterBoss(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&
            !lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id),"Swimmer requires independent contact-pursuit body");
    }
    for(const auto &[id,p]:lib->evaders_) {
        const auto *d=lib->monster(id),*child=lib->monster(p.child);
        require(d&&!d->flying&&!d->roomHazard&&!d->contact&&d->motion==(p.chase?MonsterMotion::Chase:MonsterMotion::Flee)&&
            d->attack==(p.spawns?MonsterAttack::Spawn:MonsterAttack::None)&&d->behavior=="legacy"&&
            !lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&!lib->monsterBoss(id)&&!lib->hop(id)&&!lib->charge(id)&&!lib->regrowth(id)&&
            !lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id)&&
            (!p.spawns||(child&&p.child!=id&&!child->roomHazard&&!lib->component(p.child)&&!lib->companion(p.child)&&!lib->monsterBoss(p.child)&&
            !lib->segmentedBoss(p.child)&&!lib->formation(p.child)&&!lib->flyBomb(p.child))),"Evader requires independent ground body and ordinary child");
        require((!p.chase&&!p.detonationChance)||lib->deathBlast(id),"Detonating evader requires death payload");
        require(!p.childContactDeath||lib->spider(p.child),"Evader contact-death child needs a Spider controller");
    }
    for(const auto &[id,p]:lib->buzzFlies_) {
        const auto *d=lib->monster(id);
        require(!p.suppressor||lib->item(*p.suppressor),"Buzz suppression requires a registered item");
        require(d&&d->flying&&!d->roomHazard&&d->contact==bool(p.chase)&&d->behavior=="legacy"&&
            d->motion==(p.chase?MonsterMotion::Chase:MonsterMotion::Wander)&&!(p.chase&&p.shot)&&
            (p.shot?d->attack==MonsterAttack::Shot:d->attack==MonsterAttack::None)&&
            !lib->monsterBoss(id)&&!lib->component(id)&&!lib->companion(id)&&!lib->formation(id)&&!lib->hop(id)&&
            !lib->charge(id)&&!lib->regrowth(id)&&!lib->boomFly(id)&&!lib->flyBomb(id)&&!lib->headShooter(id)&&!lib->lobWalker(id)&&!lib->statue(id),
            "Buzzing fly requires a compatible independent flying actor");
        if(p.morphItem) {
            const auto *target=lib->monster(p.itemMorph);const auto *next=lib->buzzFly(p.itemMorph);
            require(lib->item(*p.morphItem)&&p.chase&&p.itemMorph!=id&&target&&next&&!next->chase&&!next->morphItem&&
                !target->contact&&std::abs(d->radius-target->radius)<.001f,"Buzz item morph requires a compatible harmless target and registered item");
        }
        for(const auto &[parent,retention]:p.contactSummoners)
            require(p.chase&&lib->monster(parent)&&parent!=id,"Buzz contact summon requires a chaser and registered distinct source");
        if(p.morphChance) {
            const auto *target=lib->monster(p.morph);const auto *next=lib->buzzFly(p.morph);
            require(lib->dung_&&p.morph!=id&&!p.shot&&!p.chase&&target&&next&&next->shot&&!next->morphChance&&
                std::abs(d->radius-target->radius)<.001f,"Dung morph requires compatible buzzing shooter and dung profile");
        }
    }
    std::ostringstream hex;hex<<std::hex<<hash;lib->fingerprint_=hex.str();return lib;
}
const MonsterDeathRule *MechanicsLibrary::deathRule(MonsterId id) const {
    const auto found=deathBindings_.find(id);
    return found==deathBindings_.end()?nullptr:&deaths_.at(found->second);
}
const MonsterRegrowth *MechanicsLibrary::regrowth(MonsterId id) const {
    const auto found=regrowth_.find(id);return found==regrowth_.end()?nullptr:&found->second;
}
const FormationDefinition *MechanicsLibrary::formation(MonsterId id) const {
    const auto found=formations_.find(id);return found==formations_.end()?nullptr:&found->second;
}
const FireReaction *MechanicsLibrary::fireReaction(MonsterId id) const {
    const auto found=fireReactions_.find(id);return found==fireReactions_.end()?nullptr:&found->second;
}
const HopDefinition *MechanicsLibrary::hop(MonsterId id) const {
    const auto found=hops_.find(id);return found==hops_.end()?nullptr:&found->second;
}
const ItemDefinition *MechanicsLibrary::item(const ItemKey &key) const {
    auto it=itemIndex_.find(key);return it==itemIndex_.end()?nullptr:&items_[it->second];
}
const MonsterDefinition *MechanicsLibrary::monster(MonsterId id) const {
    auto it=monsterIndex_.find(id);return it==monsterIndex_.end()?nullptr:&monsters_[it->second];
}
const BehaviorDefinition *MechanicsLibrary::behavior(std::string_view key) const {
    auto it=behaviors_.find(key);return it==behaviors_.end()?nullptr:&it->second;
}
const std::vector<WeightedItem> &MechanicsLibrary::pool(std::string_view key) const {
    auto it=pools_.find(key);if(it==pools_.end())throw std::out_of_range("Unknown item pool "+std::string(key));return it->second;
}
const EncounterPool &MechanicsLibrary::encounterPool(int band,EncounterPattern pattern) const {
    return encounters_.at(size_t(band)).at(size_t(pattern));
}
ResolvedBuild MechanicsLibrary::resolve(std::span<const ItemKey> inventory,float damage,float speed,bool sixth) const {
    require(std::isfinite(damage)&&std::isfinite(speed),"Non-finite base attack stats");
    ResolvedBuild out;out.values={damage,speed,3.2f,.14f,0,0,0,0,0,0,0,1,.29f,0,0};
    for(const auto &r:rules_) {
        size_t count=copies(inventory,r.owner);if(r.stackCap)count=std::min(count,size_t(r.stackCap));
        if(!count||(r.sixthOnly&&!sixth))continue;
        bool match=true;for(const auto &q:r.requirements){auto n=copies(inventory,q.item);if(n<size_t(q.minimum)||(q.maximum>=0&&n>size_t(q.maximum)))match=false;}
        if(!match)continue;
        for(const auto &m:r.modifiers) {
            auto &target=out.values[size_t(m.stat)];const double value=m.first+double(m.extra)*double(count-1);
            for(size_t i=0;i<(m.perCopy?count:1);++i) {
                double result=target;
                switch(m.operation) {
                case ModifierOp::Set:result=value;break;
                case ModifierOp::Add:result+=value;break;
                case ModifierOp::Multiply:result*=value;break;
                case ModifierOp::Minimum:result=std::min(result,value);break;
                case ModifierOp::Maximum:result=std::max(result,value);break;
                case ModifierOp::Ratio:result=value/std::max(.0001,double(out[m.denominator]));break;
                }
                target=float(std::clamp(result,-1000000.0,1000000.0));
            }
        }
    }
    constexpr std::array<float,size_t(BuildStat::Count)> lo{0,.01f,Tick,.01f,0,0,0,0,0,0,0,1,Tick,0,0};
    constexpr std::array<float,size_t(BuildStat::Count)> hi{1e6f,200,120,10,100,1000,1e6f,100,1e6f,4096,4096,128,120,1,1};
    for(size_t i=0;i<out.values.size();++i)out.values[i]=std::clamp(out.values[i],lo[i],hi[i]);
    return out;
}
std::shared_ptr<const MechanicsLibrary> defaultMechanics() {
    static const auto library=MechanicsLibrary::load(sourceAssetDirectory()/"mechanics");return library;
}
} // namespace dw
