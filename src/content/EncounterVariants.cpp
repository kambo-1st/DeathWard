#include "content/Mechanics.hpp"

namespace dw {
const SlideDefinition *MechanicsLibrary::slide(MonsterId id) const {
    const auto it=slides_.find(id);return it==slides_.end()?nullptr:&it->second;
}
const AdultLeechDefinition *MechanicsLibrary::adultLeech(MonsterId id) const {
    const auto it=adultLeeches_.find(id);return it==adultLeeches_.end()?nullptr:&it->second;
}
const MemBrainDefinition *MechanicsLibrary::memBrain(MonsterId id) const {
    const auto it=memBrains_.find(id);return it==memBrains_.end()?nullptr:&it->second;
}
const LumpDefinition *MechanicsLibrary::lump(MonsterId id) const {
    const auto it=lumps_.find(id);return it==lumps_.end()?nullptr:&it->second;
}
const LeechDefinition *MechanicsLibrary::leech(MonsterId id) const {
    const auto it=leeches_.find(id);return it==leeches_.end()?nullptr:&it->second;
}
const MirrorDefinition *MechanicsLibrary::mirror(MonsterId id) const {
    const auto it=mirrors_.find(id);return it==mirrors_.end()?nullptr:&it->second;
}
const KnightDefinition *MechanicsLibrary::knight(MonsterId id) const {
    const auto it=knights_.find(id);return it==knights_.end()?nullptr:&it->second;
}
const MaskArmorDefinition *MechanicsLibrary::maskArmor(MonsterId id) const {
    const auto it=maskArmor_.find(id);return it==maskArmor_.end()?nullptr:&it->second;
}
const LinkedRemnantDefinition *MechanicsLibrary::linkedRemnant(MonsterId id) const {
    const auto it=linkedRemnants_.find(id);return it==linkedRemnants_.end()?nullptr:&it->second;
}
const LandingCreepDefinition *MechanicsLibrary::landingCreep(MonsterId id) const {
    const auto it=landingCreep_.find(id);return it==landingCreep_.end()?nullptr:&it->second;
}
const GutsDefinition *MechanicsLibrary::guts(MonsterId id) const {
    const auto it=guts_.find(id);return it==guts_.end()?nullptr:&it->second;
}
const ReturningBodyDefinition *MechanicsLibrary::returningBody(MonsterId id) const {
    const auto it=returningBodies_.find(id);return it==returningBodies_.end()?nullptr:&it->second;
}
const VisDefinition *MechanicsLibrary::vis(MonsterId id) const {
    const auto it=vis_.find(id);return it==vis_.end()?nullptr:&it->second;
}
const BabyDefinition *MechanicsLibrary::baby(MonsterId id) const {
    const auto it=babies_.find(id);return it==babies_.end()?nullptr:&it->second;
}
const LeaperDefinition *MechanicsLibrary::leaper(MonsterId id) const {
    const auto it=leapers_.find(id);return it==leapers_.end()?nullptr:&it->second;
}
const AdaptiveArmorDefinition *MechanicsLibrary::adaptiveArmor(MonsterId id) const {
    const auto it=adaptiveArmor_.find(id);return it==adaptiveArmor_.end()?nullptr:&it->second;
}
const HopRingDefinition *MechanicsLibrary::hopRings(MonsterId id) const {
    const auto it=hopRings_.find(id);return it==hopRings_.end()?nullptr:&it->second;
}
const EggyDefinition *MechanicsLibrary::eggy(MonsterId id) const {
    const auto it=eggies_.find(id);return it==eggies_.end()?nullptr:&it->second;
}
const TargetHopDefinition *MechanicsLibrary::targetHop(MonsterId id) const {
    const auto it=targetHops_.find(id);return it==targetHops_.end()?nullptr:&it->second;
}
const LongLegsDefinition *MechanicsLibrary::longLegs(MonsterId id) const {
    const auto it=longLegs_.find(id);return it==longLegs_.end()?nullptr:&it->second;
}
const SackDefinition *MechanicsLibrary::sack(MonsterId id) const {
    const auto it=sacks_.find(id);return it==sacks_.end()?nullptr:&it->second;
}
const BoilDefinition *MechanicsLibrary::boil(MonsterId id) const {
    const auto it=boils_.find(id);return it==boils_.end()?nullptr:&it->second;
}
const StriderDefinition *MechanicsLibrary::strider(MonsterId id) const {
    const auto it=striders_.find(id);return it==striders_.end()?nullptr:&it->second;
}
const SwarmSpiderDefinition *MechanicsLibrary::swarmSpider(MonsterId id) const {
    const auto it=swarmSpiders_.find(id);return it==swarmSpiders_.end()?nullptr:&it->second;
}
MonsterId MechanicsLibrary::spawnIdentity(MonsterId id,const FloorProfile &p) const {
    const auto *r=replacement(id,p,3);return r&&r->allSpawns?r->target:id;
}
const SpiderDefinition *MechanicsLibrary::spider(MonsterId id) const {
    const auto it=spiders_.find(id);return it==spiders_.end()?nullptr:&it->second;
}
const HardyDefinition *MechanicsLibrary::hardy(MonsterId id) const {
    const auto it=hardies_.find(id);return it==hardies_.end()?nullptr:&it->second;
}
const DannyDefinition *MechanicsLibrary::danny(MonsterId id) const {
    const auto it=dannies_.find(id);return it==dannies_.end()?nullptr:&it->second;
}
const GaperDefinition *MechanicsLibrary::gaper(MonsterId id) const {
    const auto it=gapers_.find(id);return it==gapers_.end()?nullptr:&it->second;
}
const BlackGlobinDefinition *MechanicsLibrary::blackGlobin(MonsterId id) const {
    const auto it=blackGlobins_.find(id);return it==blackGlobins_.end()?nullptr:&it->second;
}
const LeperFleshDefinition *MechanicsLibrary::leperFlesh(MonsterId id) const {
    const auto it=leperFlesh_.find(id);return it==leperFlesh_.end()?nullptr:&it->second;
}
const LeperDefinition *MechanicsLibrary::leper(MonsterId id) const {
    const auto it=lepers_.find(id);return it==lepers_.end()?nullptr:&it->second;
}
const RottenGaperDefinition *MechanicsLibrary::rottenGaper(MonsterId id) const {
    const auto it=rottenGapers_.find(id);return it==rottenGapers_.end()?nullptr:&it->second;
}
const SmallMaggotDefinition *MechanicsLibrary::smallMaggot(MonsterId id) const {
    const auto it=smallMaggots_.find(id);return it==smallMaggots_.end()?nullptr:&it->second;
}
const HeadlessDefinition *MechanicsLibrary::headless(MonsterId id) const {
    const auto it=headless_.find(id);return it==headless_.end()?nullptr:&it->second;
}
const FacelessDefinition *MechanicsLibrary::faceless(MonsterId id) const {
    const auto it=faceless_.find(id);return it==faceless_.end()?nullptr:&it->second;
}
const RockSpiderDefinition *MechanicsLibrary::rockSpider(MonsterId id) const {
    const auto it=rockSpiders_.find(id);return it==rockSpiders_.end()?nullptr:&it->second;
}
const WilloDefinition *MechanicsLibrary::willo(MonsterId id) const {
    const auto it=willos_.find(id);return it==willos_.end()?nullptr:&it->second;
}
const SwimmerDefinition *MechanicsLibrary::swimmer(MonsterId id) const {
    const auto it=swimmers_.find(id);return it==swimmers_.end()?nullptr:&it->second;
}
const EvaderDefinition *MechanicsLibrary::evader(MonsterId id) const {
    const auto it=evaders_.find(id);return it==evaders_.end()?nullptr:&it->second;
}
const BuzzFlyDefinition *MechanicsLibrary::buzzFly(MonsterId id) const {
    const auto it=buzzFlies_.find(id);return it==buzzFlies_.end()?nullptr:&it->second;
}
const MawDefinition *MechanicsLibrary::maw(MonsterId id) const {
    const auto it=maws_.find(id);return it==maws_.end()?nullptr:&it->second;
}
const SpittyDefinition *MechanicsLibrary::spitty(MonsterId id) const {
    const auto it=spitties_.find(id);return it==spitties_.end()?nullptr:&it->second;
}
const CardinalWalkerDefinition *MechanicsLibrary::cardinalWalker(MonsterId id) const {
    const auto it=cardinalWalkers_.find(id);return it==cardinalWalkers_.end()?nullptr:&it->second;
}
const BrainDefinition *MechanicsLibrary::brain(MonsterId id) const {
    const auto it=brains_.find(id);return it==brains_.end()?nullptr:&it->second;
}
const LinkedHeadDefinition *MechanicsLibrary::linkedHead(MonsterId id) const {
    for(const auto &[body,p]:linkedHeads_)if(id==body||id==p.head)return &p;
    return nullptr;
}
bool MechanicsLibrary::linkedNeck(MonsterId id) const {
    for(const auto &[body,p]:linkedHeads_)if(id==p.neck)return true;
    return false;
}
const HostDefinition *MechanicsLibrary::host(MonsterId id) const {
    const auto it=hosts_.find(id);return it==hosts_.end()?nullptr:&it->second;
}
const MushroomDefinition *MechanicsLibrary::mushroom(MonsterId id) const {
    const auto it=mushrooms_.find(id);return it==mushrooms_.end()?nullptr:&it->second;
}
const EternalFlyDefinition *MechanicsLibrary::eternalFly(MonsterId id) const {
    const auto it=eternalFlies_.find(id);return it==eternalFlies_.end()?nullptr:&it->second;
}
const EnemyStatusDefinition *MechanicsLibrary::enemyStatuses(MonsterId id) const {
    const auto it=enemyStatuses_.find(id);return it==enemyStatuses_.end()?nullptr:&it->second;
}
const HeadShooterDefinition *MechanicsLibrary::headShooter(MonsterId id) const {
    const auto it=headShooters_.find(id);return it==headShooters_.end()?nullptr:&it->second;
}
const LobWalkerDefinition *MechanicsLibrary::lobWalker(MonsterId id) const {
    const auto it=lobWalkers_.find(id);return it==lobWalkers_.end()?nullptr:&it->second;
}
const SourceImmunityDefinition *MechanicsLibrary::sourceImmunity(MonsterId id) const {
    const auto it=sourceImmunities_.find(id);return it==sourceImmunities_.end()?nullptr:&it->second;
}
const LethalMorphDefinition *MechanicsLibrary::lethalMorph(MonsterId id) const {
    const auto it=lethalMorphs_.find(id);return it==lethalMorphs_.end()?nullptr:&it->second;
}
const MonsterReplacement *MechanicsLibrary::replacement(MonsterId source,const FloorProfile &p,int phase) const {
    if(!p.active())return nullptr;
    for(const auto &r:replacements_)if(r.phase==phase&&r.source==source&&p.band>=r.firstBand&&p.band<=r.lastBand&&
        (!r.variant||*r.variant==p.variant))return &r;
    return nullptr;
}
int MechanicsLibrary::replacementCost(MonsterId source,const FloorProfile &p) const {
    std::map<MonsterId,int> paths{{source,0}};
    for(int phase=0;phase<4;++phase) {
        // Reserve all configured branches, including disabled ones: changing
        // probabilities alone must not reroll the underlying room population.
        auto next=paths;
        for(const auto &[id,cost]:paths)if(const auto *r=replacement(id,p,phase))
            next[r->target]=std::max(next[r->target],cost+r->extraCost);
        paths=std::move(next);
    }
    int maximum=0;for(const auto &[id,cost]:paths)maximum=std::max(maximum,cost);return maximum;
}
const StageHealthDefinition *MechanicsLibrary::stageHealth(MonsterId id) const {
    const auto it=stageHealth_.find(id);return it==stageHealth_.end()?nullptr:&it->second;
}
float MechanicsLibrary::monsterHealth(MonsterId id,int sourceStage) const {
    const auto *p=stageHealth(id);if(!p)return monster(id)->hp;
    const int stage=std::clamp(sourceStage,1,13);
    const float multiplier=float(std::min(stage,4))+.8f*float(std::clamp(stage-5,0,5));
    return (p->base+p->perStage*multiplier)*p->scale;
}
const BoomFlyDefinition *MechanicsLibrary::boomFly(MonsterId id) const {
    const auto it=boomFlies_.find(id);return it==boomFlies_.end()?nullptr:&it->second;
}
FloorProfile MechanicsLibrary::configureFloor(FloorProfile profile,uint64_t seed) const {
    if(!profile.active())return profile;
    profile.sourceStage=sourceStages_.at(size_t(profile.band)).at(size_t(std::clamp(profile.stageStep,0,1)));
    const auto &variants=floorVariants_.at(size_t(profile.band));
    int total=0;for(const auto &[variant,weight]:variants)total+=weight;
    Random rng(seed^0x464c4f4f52564152ULL);int roll=int(rng.bounded(uint32_t(total)));
    for(const auto &[variant,weight]:variants)if((roll-=weight)<0){profile.variant=variant;break;}
    if(profile.variant==FloorVariant::Scorched&&profile.band==0)profile.name="Scorched Washes";
    if(profile.variant==FloorVariant::Flooded&&profile.band==1)profile.name="Flooded Quarry";
    if(profile.variant==FloorVariant::Dank&&profile.band==2)profile.name="Seeping Works";
    if(profile.variant==FloorVariant::Scarred&&profile.band==3)profile.name="Scarred Storm Cut";
    const auto &bosses=bossPools_.at(size_t(profile.band));
    const auto eligible=[&](const auto &boss){return !boss.variant||*boss.variant==profile.variant;};
    int bossWeight=nativeBossWeights_[size_t(profile.band)];for(const auto &boss:bosses)if(eligible(boss))bossWeight+=boss.weight;
    Random bossRng(seed^0x424f5353504f4f4cULL);int choice=int(bossRng.bounded(uint32_t(bossWeight)))-nativeBossWeights_[size_t(profile.band)];
    if(choice>=0)for(const auto &boss:bosses)if(eligible(boss)&&(choice-=boss.weight)<0) {
        profile.boss=BossKind::Isaac;profile.bossMonster=boss.monster;profile.bossForm=boss.form;break;
    }
    profile.doubleBossRoom=shell(profile.bossMonster)!=nullptr;
    if(const auto *h=hornfel(profile.bossMonster)) {
        int weight=0;for(const auto &[key,w]:h->layouts)weight+=w;
        Random rails(seed^0x484f524e5241494cULL);int choice=int(rails.bounded(uint32_t(weight)));
        for(const auto &[key,w]:h->layouts)if((choice-=w)<0){profile.bossRails=std::make_shared<RailLayout>(*railLayout(key));break;}
    }
    return profile;
}
const PeepDefinition *MechanicsLibrary::peep(MonsterId id) const {
    const auto it=peeps_.find(id);return it==peeps_.end()?nullptr:&it->second;
}
const LokiDefinition *MechanicsLibrary::loki(MonsterId id) const {
    const auto it=lokis_.find(id);return it==lokis_.end()?nullptr:&it->second;
}
const HornfelDecoyDefinition *MechanicsLibrary::hornfelDecoy(MonsterId id) const {
    const auto it=hornfelDecoys_.find(id);return it==hornfelDecoys_.end()?nullptr:&it->second;
}
const HornfelDefinition *MechanicsLibrary::hornfel(MonsterId id) const {
    const auto it=hornfels_.find(id);return it==hornfels_.end()?nullptr:&it->second;
}
const EnvironmentActorDefinition *MechanicsLibrary::environmentActor(MonsterId id) const {
    const auto it=environmentActors_.find(id);return it==environmentActors_.end()?nullptr:&it->second;
}
const RailTrafficDefinition *MechanicsLibrary::railTraffic(MonsterId id) const {
    const auto it=railTraffic_.find(id);return it==railTraffic_.end()?nullptr:&it->second;
}
const BloatDefinition *MechanicsLibrary::bloat(MonsterId id) const {
    const auto it=bloats_.find(id);return it==bloats_.end()?nullptr:&it->second;
}
const SegmentedBossDefinition *MechanicsLibrary::segmentedBoss(MonsterId id) const {
    const auto it=segmentedBosses_.find(id);return it==segmentedBosses_.end()?nullptr:&it->second;
}
const ShellBossDefinition *MechanicsLibrary::shell(MonsterId id) const {
    const auto it=shells_.find(id);return it==shells_.end()?nullptr:&it->second;
}
const DeathCrossDefinition *MechanicsLibrary::deathCross(MonsterId id) const {
    const auto it=deathCrosses_.find(id);return it==deathCrosses_.end()?nullptr:&it->second;
}
const DeathBlastDefinition *MechanicsLibrary::deathBlast(MonsterId id) const {
    const auto it=deathBlasts_.find(id);return it==deathBlasts_.end()?nullptr:&it->second;
}
const FlyBombDefinition *MechanicsLibrary::flyBomb(MonsterId id) const {
    const auto it=flyBombs_.find(id);return it==flyBombs_.end()?nullptr:&it->second;
}
const EnemyBombDefinition *MechanicsLibrary::enemyBomb(std::string_view key) const {
    const auto it=enemyBombs_.find(key);return it==enemyBombs_.end()?nullptr:&it->second;
}
const RailLayout *MechanicsLibrary::railLayout(std::string_view key) const {
    const auto it=railLayouts_.find(key);return it==railLayouts_.end()?nullptr:&it->second;
}
const ChargeDefinition *MechanicsLibrary::charge(MonsterId id) const {
    const auto it=charges_.find(id);return it==charges_.end()?nullptr:&it->second;
}
const CompanionDefinition *MechanicsLibrary::companion(MonsterId id) const {
    const auto it=companions_.find(id);return it==companions_.end()?nullptr:&it->second;
}
const StatueDefinition *MechanicsLibrary::statue(MonsterId id) const {
    const auto it=statues_.find(id);return it==statues_.end()?nullptr:&it->second;
}
bool MechanicsLibrary::bossFormAllowed(MonsterId id,BossForm form) const {
    if(peep(id))return form==BossForm::Normal||form==BossForm::Cyan||form==BossForm::Yellow;
    if(bloat(id))return form==BossForm::Normal||form==BossForm::Green;
    if(segmentedBoss(id)||loki(id)||hornfel(id))return form==BossForm::Normal;
    return false;
}
const ComponentDefinition *MechanicsLibrary::component(MonsterId id) const {
    const auto it=components_.find(id);return it==components_.end()?nullptr:&it->second;
}
} // namespace dw
