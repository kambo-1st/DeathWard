#include "combat/Simulation.hpp"
#include <iostream>
#include <stdexcept>
using namespace dw;
namespace {
void check(bool ok,const std::string &message){if(!ok)throw std::runtime_error(message);}
void residentFloor(const Simulation &run,const Enemy &e,uint64_t seed,int floor,int room) {
    const bool blocked=run.arena.blocked(e.position,e.radius);
    const int actualRoom=run.arena.roomAt(e.position);
    if(blocked) {
        for(size_t n=0;n<run.arena.walls.size();++n)if(sphereBox(e.position,e.radius,run.arena.walls[n]))std::cerr<<"COLLISION wall="<<n<<'\n';
        for(size_t n=0;n<run.arena.movementBodies.size();++n)if(sphereBox(e.position,e.radius,run.arena.movementBodies[n]))std::cerr<<"COLLISION actor="<<n<<'\n';
        if(run.arena.canyon) {
            std::cerr<<"COLLISION terrain="<<run.arena.canyon->blocked(e.position,e.radius)<<" padded="<<run.arena.blocked(e.position,std::max(.8f,e.radius))<<'\n';
            for(int n=-1;n<8;++n) {
                auto p=e.position;if(n>=0)p=add(p,rotateY({e.radius,0,0},float(n)*Pi/4));
                std::cerr<<"SAMPLE "<<n<<" height="<<run.arena.canyon->height(p.x,p.z)<<" water="<<run.arena.canyon->waterBlocked(p)<<'\n';
            }
        }
    }
    check(!blocked&&actualRoom==room,"resident on reachable floor: seed="+std::to_string(seed)+
        " floor="+std::to_string(floor)+" room="+std::to_string(room)+" id="+monsterIdText(e.monster)+
        " entity="+std::to_string(e.id)+" position="+std::to_string(e.position.x)+","+
        std::to_string(e.position.y)+","+std::to_string(e.position.z)+" radius="+std::to_string(e.radius)+
        " blocked="+std::to_string(blocked)+" actualRoom="+std::to_string(actualRoom));
}
void scanPlacement(uint64_t first,uint64_t last) {
    for(uint64_t seed=first;seed<=last;++seed) {
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int band=0;band<4;++band) {
            int floor=0;while(plan.profileOnFloor(floor).band<band)++floor;
            Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            for(auto &p:run.arena.passages){p.locked=false;p.sealed={false,false};}run.arena.rebuildWalls();
            for(int room=0;room<run.arena.roomCount();++room)if(run.arena.rooms[size_t(room)].kind==RoomKind::Combat)
                for(const auto &e:run.roomEnemies(room)) {
                    const auto *linked=run.content->linkedHead(e.monster);
                    if(run.content->statue(e.monster)||run.content->eternalFly(e.monster)||(linked&&e.monster==linked->head))continue;
                    residentFloor(run,e,seed,floor,room);
                }
        }
    }
    std::cout<<"PASS placement scan seeds "<<first<<".."<<last<<'\n';
}
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
    std::set<MonsterId> seen;
    std::set<MonsterId> statueSeen;
    std::array<int,3> activatedRings{};
    std::array<std::set<MonsterId>,3> activatedHoppers;
    int scorchedFloors=0, substitutedHoppers=0, substitutedChargers=0;
    auto needsReplacementCoverage=[&](int band) {
        // I.Blob is a1% substitution in every band. Scorched Hopper/Grilled
        // and Flooded Charger coverage only need their eligible contexts.
        return !seen.contains(monsterId(15,2))||
            (band==0&&(!seen.contains(monsterId(15,3))||substitutedHoppers==0))||
            (band==1&&substitutedChargers==0);
    };
    auto replacementCoverage=[&] {return !needsReplacementCoverage(0)&&!needsReplacementCoverage(1);};
    auto needsPoolCoverage=[&](int band) {
        for(int pattern=0;pattern<4;++pattern) {
            const auto &pool=defaultMechanics()->encounterPool(band,EncounterPattern(pattern));
            for(const auto *entries:{&pool.basics,&pool.specialists})for(const auto &entry:*entries)
                if(entry.weight>0&&!seen.contains(entry.monster))return true;
        }
        return false;
    };
    auto needsStatueCoverage=[&](int band) {
        for(const auto &entry:defaultMechanics()->statuePool(band))
            if(entry.weight>0&&!statueSeen.contains(entry.monster))return true;
        return false;
    };
    for(uint64_t seed=0;seed<512;++seed) {
        // Keep the broad 32-seed/four-band regression, then supplement only
        // missing pool residents and rare-family activation. Pool changes legitimately
        // change which seeds contain a group; never weaken the assertions.
        // Leave enough fallback seeds for rare source selection plus a floor
        // variant plus substitution, as the regular-enemy pool expands.
        if(seed>=32&&std::all_of(activatedRings.begin(),activatedRings.end(),[](int n){return n>=2;})&&
           std::all_of(activatedHoppers.begin(),activatedHoppers.end(),[](const auto &ids){return ids.size()==2;})&&replacementCoverage()&&
           !needsPoolCoverage(0)&&!needsPoolCoverage(1)&&!needsPoolCoverage(2)&&!needsPoolCoverage(3)&&
           !needsStatueCoverage(0)&&!needsStatueCoverage(1)&&!needsStatueCoverage(2)&&!needsStatueCoverage(3))break;
        ExpeditionPlan plan(seed,false,WitnessAccount::Rourke);
        for(int band=0;band<4;++band) {
            const bool needsActivation=band<3&&(activatedRings[size_t(band)]<2||activatedHoppers[size_t(band)].size()<2);
            if(seed>=32&&!needsReplacementCoverage(band)&&!needsActivation&&!needsPoolCoverage(band)&&!needsStatueCoverage(band))continue;
            int floor=0;while(plan.profileOnFloor(floor).band<band)++floor;
            Simulation run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::Rourke,floor);
            const auto &profile=run.arena.profile;
            scorchedFloors+=profile.variant==FloorVariant::Scorched;
            check(profile.band==band,"simulation uses current floor profile");
            for(auto &p:run.arena.passages){p.locked=false;p.sealed={false,false};}run.arena.rebuildWalls();
            for(int room=0;room<run.arena.roomCount();++room) {
                const auto &r=run.arena.rooms[size_t(room)];const auto &residents=run.roomEnemies(room);
                if(r.kind==RoomKind::Combat) {
                    const auto grammar=run.floorEncounter(room);patterns.insert(grammar.pattern);
                    check(grammar.spent<=grammar.budget&&grammar.specialistGroups<=profile.maxSpecialists,"threat and specialist-group limits");
                    check(grammar.monsters.size()<=14&&grammar.specialists+2<=int(grammar.monsters.size()),"formation members consume actor slots and retain ordinary support");
                    const auto statueCount=std::count_if(residents.begin(),residents.end(),[&](const auto &e){return run.content->statue(e.monster)!=nullptr;});
                    const auto childCount=std::count_if(residents.begin(),residents.end(),[&](const auto &e){
                        const auto *linked=run.content->linkedHead(e.monster);
                        return run.content->eternalFly(e.monster)||(linked&&e.monster==linked->head);
                    });
                    const auto requiredChildren=std::count_if(grammar.monsters.begin(),grammar.monsters.end(),[&](auto id){
                        const auto *p=run.content->maw(id);const auto *linked=run.content->linkedHead(id);const auto *leech=run.content->leech(id);
                        return (p&&p->child)||(leech&&leech->child)||(linked&&id==linked->body);
                    });
                    check(int(residents.size())-int(statueCount+childCount)==run.roomEnemyCount(room),"safe placement realizes ordinary budget separately from required orbiters");
                    check(childCount==requiredChildren&&statueCount<=1&&residents.size()==grammar.monsters.size()+size_t(childCount+statueCount),"all ordinary actors and required children realized, at most one optional statue");
                    if(statueCount)check(grammar.statue&&residents[grammar.monsters.size()].monster==*grammar.statue,"extra statue matches seeded hazard plan before queued offspring");
                    for(size_t slot=0;slot<grammar.monsters.size();++slot) {
                        const auto planned=grammar.monsters[slot],actual=residents[slot].monster;
                        const bool rockDefault=run.content->rockSpider(planned)&&planned.subtype==0;
                        const bool rottenDefault=run.content->rottenGaper(planned)&&planned.subtype==0;
                        check((rockDefault||rottenDefault)?actual.type==planned.type&&actual.variant==planned.variant&&actual.subtype>=1&&actual.subtype<=(rockDefault?3:5):
                            actual==planned,"resident identity matches seeded substitution and native default-subtype initialization");
                        // Record the selector only when a planned default slot
                        // actually produced one of its permitted live subtypes.
                        if(rottenDefault)seen.insert(planned);
                        if(grammar.originalMonsters[slot]!=grammar.monsters[slot]) {
                            const bool firstHopper=grammar.monsters[slot]==monsterId(54)&&substitutedHoppers++==0;
                            const bool firstCharger=grammar.monsters[slot]==monsterId(23,1)&&substitutedChargers++==0;
                            if(firstCharger)check(profile.variant==FloorVariant::Flooded&&band==1,"Drowned replacement needs actual Flooded Quarry");
                            if(firstHopper||firstCharger||!seen.contains(grammar.monsters[slot]))std::cout<<"NATURAL_REPLACEMENT seed="<<seed<<" floor="<<floor<<" room="<<room
                                <<" source="<<monsterIdText(grammar.originalMonsters[slot])<<" target="<<monsterIdText(grammar.monsters[slot])<<'\n';
                        }
                    }
                    threats[size_t(band)]+=grammar.spent;++groups[size_t(band)];
                    for(const auto &e:residents) {
                        if(const auto *linked=run.content->linkedHead(e.monster);linked&&e.monster==linked->head) {
                            const auto parent=std::find_if(residents.begin(),residents.end(),[&](const auto &body){return body.id==e.partner;});
                            check(parent!=residents.end()&&parent->monster==linked->body&&parent->partner==e.id,
                                  "linked head has the correct reciprocal body owner");
                            check(std::count_if(residents.begin(),residents.end(),[&](const auto &other){return other.partner==e.partner&&other.monster==e.monster;})==1,
                                  "exactly one required head per body");
                            check(distance(e.position,parent->position)<.001f,"required head begins attached to body");
                            continue;
                        }
                        if(run.content->eternalFly(e.monster)) {
                            const auto parent=std::find_if(residents.begin(),residents.end(),[&](const auto &body){return body.id==e.partner;});
                            check(parent!=residents.end(),"required orbiter has parent in this resident room");
                            const auto *maw=run.content->maw(parent->monster);const auto *leech=run.content->leech(parent->monster);
                            check(parent->alive&&((maw&&maw->child==e.monster)||(leech&&leech->child==e.monster)),"required orbiter has correct live parent in this resident room");
                            check(std::count_if(residents.begin(),residents.end(),[&](const auto &other){return other.partner==e.partner&&other.monster==e.monster;})==1,"exactly one required fly per parent");
                            continue;
                        }
                        if(run.content->statue(e.monster)) {
                            const auto &pool=run.content->statuePool(band);
                            check(band>0&&std::any_of(pool.begin(),pool.end(),[&](const auto &p){return p.weight>0&&p.monster==e.monster&&(p.pattern<0||p.pattern==int(grammar.pattern));}),"actual statue obeys its separate source-stage pool");
                            check(run.arena.blocked(e.position,e.radius)&&run.arena.flightBlocked(e.position,e.radius,room),"statue footprint is solid for walking and flight");
                            if(statueSeen.insert(e.monster).second)std::cout<<"NATURAL_STATUE id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
                            if(e.monster.type==804) {
                                const std::array<Vector3,4> axes{{{-1,0,0},{0,0,-1},{1,0,0},{0,0,1}}};
                                check(band==1&&distance(e.facing,axes[size_t(e.monster.subtype)])<.001f,"Quake obeys source stage and fixed subtype axis");
                                const auto start=add(e.position,mul(e.facing,e.radius+.05f));
                                check(!run.arena.trace(start,add(start,mul(e.facing,6)),.5f).hit,"Actual Quake placement has a usable attack lane, excluding its own actor footprint");
                            }
                            if(run.content->statue(e.monster)->clear==StatueClear::Plates) {
                                check(!run.rooms[size_t(room)].plates.empty(),"persistent generated turret has a reachable optional plate");
                                for(const auto &plate:run.rooms[size_t(room)].plates)
                                    check(!run.arena.path(r.entry,plate.position,.48f).empty(),"plate reachable from room entry");
                            }
                            continue;
                        }
                        const bool first=seen.insert(e.monster).second;
                        if(run.content->rockSpider(e.monster)) {
                            check(e.monster.subtype>=1&&e.monster.subtype<=3,"default rock selects a concrete native silhouette");
                            seen.insert(monsterId(e.monster.type,e.monster.variant,0));
                        }
                        if(first&&e.monster==monsterId(15,3))std::cout<<"NATURAL_GRILLED seed="<<seed<<" floor="<<floor<<" room="<<room<<'\n';
                        if((e.monster.type==23&&e.monster.variant>0)||e.monster==monsterId(855)) {
                            if(first)std::cout<<"NATURAL_CHARGER id="<<monsterIdText(e.monster)<<" seed="<<seed<<" floor="<<floor<<" room="<<room<<" variant="<<int(profile.variant)<<'\n';
                            check(e.monster==monsterId(23,1)?(band==1||band==2):e.monster==monsterId(23,2)?band==2:e.monster==monsterId(23,3)?band==1:band==3,
                                  "Charger variants obey reviewed source stage bands");
                        }
                        if(e.monster==monsterId(872))check(band==1&&grammar.pattern==EncounterPattern::Crossfire,
                            "Cloggy is restricted to Dross-equivalent Broken Quarry crossfire rooms");
                        if(e.monster==monsterId(819))check(band==1&&profile.variant==FloorVariant::Standard,
                            "Fly Bomb stays in the reviewed standard Mines/Ashpit analogue");
                        if(e.monster==monsterId(15))check(band==1||band==3,"ordinary Clotty does not acquire an unsupported Depths route");
                        if(e.monster==monsterId(15,3))check(band==0&&profile.variant==FloorVariant::Scorched,"Grilled belongs to Scorched Washes ordinary rooms");
                        if(e.monster==monsterId(29)||e.monster==monsterId(54)) {
                            check(band<=2&&grammar.pattern==EncounterPattern::Pursuit,"Hoppers occur in approved early/middle pursuit rooms");
                            const int cap=e.monster==monsterId(29)?2:1;
                            check(std::count_if(residents.begin(),residents.end(),[&](const auto &other){return other.monster==e.monster;})<=cap,
                                "Hopper family room cap is respected");
                        }
                        if(e.monster.type==10&&e.monster.variant==3)
                            check(band==3&&e.monster.subtype>=1&&e.monster.subtype<=5,
                                  "only reviewed exact Rotten subtypes enter late Storm Cut pools");
                        if(band==0)check(e.monster!=monsterId(21)&&e.monster!=monsterId(23),
                            "Caves-family Maggot/Charger cannot enter the opening Washes band");
                        const auto &pool=run.content->encounterPool(band,grammar.pattern);
                        const auto eligible=[&](const auto &entries){return std::any_of(entries.begin(),entries.end(),
                            [&](const auto &entry){
                                if(entry.weight<=0||(entry.variant&&*entry.variant!=profile.variant))return false;
                                std::set<MonsterId> reachable{entry.monster};
                                for(int phase=0;phase<4;++phase) {
                                    std::set<MonsterId> next;
                                    for(const auto id:reachable) {
                                        const auto *replacement=run.content->replacement(id,profile,phase);
                                        if(!replacement||replacement->chance<10000)next.insert(id);
                                        if(replacement&&replacement->chance>0)next.insert(replacement->target);
                                    }
                                    reachable=std::move(next);
                                }
                                const int defaultSubtypes=run.content->rockSpider(e.monster)?3:run.content->rottenGaper(e.monster)?5:0;
                                if(defaultSubtypes&&e.monster.subtype>=1&&e.monster.subtype<=defaultSubtypes)
                                    return reachable.contains(monsterId(e.monster.type,e.monster.variant,0))||reachable.contains(e.monster);
                                return reachable.contains(e.monster);});};
                        check(eligible(pool.basics)||eligible(pool.specialists),"actual residents obey the external stage/pattern pool");
                        check(e.kind==EnemyKind::Monster,"canyon uses Isaac-derived ordinary roster");
                        residentFloor(run,e,seed,floor,room);
                        check(distance(e.position,r.entry)>=6,"safe entrance landing");
                        for(int link:r.passages) {
                            const int side=run.arena.passages[size_t(link)].rooms[0]==room?0:1;
                            check(distance(e.position,run.arena.doorApproach(link,side))>=e.radius+2.5f,"every entry stays clear");
                        }
                        for(const auto &other:residents)if(e.id!=other.id) {
                            // The source Eternal Fly starts at its parent and expands its orbit.
                            if(other.partner==e.id&&(run.content->eternalFly(other.monster)||run.content->linkedHead(other.monster)))continue;
                            check(distance(e.position,other.position)>=e.radius+other.radius,"independent bodies do not overlap");
                        }
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
            const auto &bossResidents=run.roomEnemies(run.finalRoom());
            check(!bossResidents.empty()&&bossResidents[0].bossKind==profile.boss,"dedicated seeded canyon boss follows configured pool");
            if(const auto *parts=run.content->segmentedBoss(profile.bossMonster)) {
                check(band==1&&profile.variant==FloorVariant::Standard,"Tuff/Shell stay in standard Broken Quarry, the reviewed Mines/Ashpit analogue");
                const size_t bodyCount=size_t(parts->chains*parts->segments);
                check(bossResidents.size()==bodyCount+size_t(parts->suppliers)&&run.rooms.back().segmented.size()==1&&run.rooms.back().segmented[0].chains.size()==size_t(parts->chains),
                      "Generated multipart arena contains complete configured chains and suppliers");
                for(size_t i=0;i<bossResidents.size();++i) {
                    const auto &e=bossResidents[i];
                    check(i<bodyCount?e.segmentedEncounter!=0:e.monster==parts->supplier,"Real generated multipart boss and suppliers");
                    if(i<bodyCount)check(!run.arena.blocked(e.position,e.radius),"Generated body has legal footprint");
                    else check(!run.arena.path(r.center,add(e.position,mul(e.facing,2)),.48f).empty(),"Generated supplier has a reachable approach");
                }
            } else if(run.content->hornfel(profile.bossMonster)) {
                check(band==1&&profile.variant==FloorVariant::Standard,"Hornfel stays in reviewed Mines analogue");
                const auto &h=run.rooms.back().hornfel;
                check(run.arena.rails&&h&&bossResidents.size()==1&&h->owner==bossResidents[0].id&&h->cart.rider==h->owner&&
                    h->doors.size()==run.arena.rails->doors.size(),"generated rail encounter binds complete cart and door set");
                check(!run.arena.path(r.entry,r.exit,.48f).empty()&&!run.arena.path(r.entry,r.reward,.48f).empty(),"rail arena has reachable progression and reward");
            } else if(const auto *loki=run.content->loki(profile.bossMonster)) {
                check(band==(profile.bossMonster.variant==1?3:2),"Loki/Lokii stay in reviewed Chapter3/4 analogue bands");
                check(bossResidents.size()==size_t(loki->bodies),"generated Loki encounter has every independent body");
                for(const auto &body:bossResidents)check(body.bossGroup==bossResidents[0].id&&body.kind==EnemyKind::Boss&&
                    body.monster==profile.bossMonster&&body.hp==1120&&!run.arena.blocked(body.position,body.radius),
                    "generated Lokii halves share payout identity, full health and legal independent footprints");
            } else {
                for(size_t i=1;i<bossResidents.size();++i)check(bossResidents[i].componentOwner==bossResidents[0].id&&
                    run.content->monster(bossResidents[i].monster)->roomHazard,"additional boss residents are non-gating owned components");
            }
            if(profile.boss==BossKind::Isaac&&!run.content->segmentedBoss(profile.bossMonster)&&!run.content->loki(profile.bossMonster)&&!run.content->hornfel(profile.bossMonster)) {
                const bool peep=bossResidents[0].monster==monsterId(68);
                check(peep?band==1:((band==2||band==3)&&bossResidents[0].monster==monsterId(68,1)),"source bosses stay in their reviewed stage bands");
                check(bossResidents.size()==(!peep||profile.bossForm==BossForm::Cyan?3u:1u),"dedicated boss forms have correct initial owned eyes");
            }
            check(r.obstacles.empty(),"no baked outcrops in charge arena");
            for(int n=0;!profile.bossRails&&n<32;++n) {
                const auto a=add(r.center,{std::cos(n*2*Pi/32)*9.7f,0,std::sin(n*2*Pi/32)*9.7f});
                const auto b=add(r.center,{std::cos((n+1)*2*Pi/32)*9.7f,0,std::sin((n+1)*2*Pi/32)*9.7f});
                check(!run.arena.blocked(a,.8f)&&run.arena.clear(a,b,.8f),"continuous arena dodge loop seed="+std::to_string(seed)+" floor="+std::to_string(floor));
            }
            if(band<3&&activatedRings[size_t(band)]<2)for(int room=1;room<run.finalRoom();++room) {
                const auto &residents=run.roomEnemies(room);
                if(std::count_if(residents.begin(),residents.end(),[](const auto &e){return e.monster==monsterId(222);})!=4)continue;
                run.jumpDebug(room);run.godMode=true;
                for(int tick=0;tick<180;++tick)run.step({});
                check(run.rooms[size_t(room)].formations.size()==1,"real seeded encounter assembles one Ring Fly group");
                int live=0;for(const auto &e:run.enemies)if(e.monster==monsterId(222)) {
                    ++live;check(e.formation!=0&&!run.arena.flightBlocked(e.position,e.radius,room),"activated formation retains all members within canyon collision");
                }
                check(live==4,"real formation retains four living members");++activatedRings[size_t(band)];break;
            }
            if(band<3&&activatedHoppers[size_t(band)].size()<2)for(int room=1;room<run.finalRoom();++room) {
                std::vector<EntityId> targets;
                for(const auto &e:run.roomEnemies(room))if((e.monster==monsterId(29)||e.monster==monsterId(54))&&
                    !activatedHoppers[size_t(band)].contains(e.monster))targets.push_back(e.id);
                if(targets.empty())continue;
                run.jumpDebug(room);run.godMode=true;std::set<EntityId> airborne,landed;
                for(int tick=0;tick<420;++tick) {
                    run.step({});
                    for(auto id:targets) {
                        const auto *e=run.findEnemy(id);check(e&&e->alive,"seeded Hopper survives activation check");
                        check(!run.arena.flightBlocked(e->position,e->radius,room),"active seeded Hopper remains inside room");
                        check(e->targetHop.has_value(),"seeded Hopper uses source destination hopping");
                        if(e->targetHop->airborne&&e->position.y>1.4f)airborne.insert(id);
                        if(!e->targetHop->airborne) {
                            check(!run.arena.blocked(e->position,e->radius),"seeded Hopper lands on legal ground");
                            if(airborne.contains(id))landed.insert(id);
                        }
                    }
                }
                for(auto id:targets) {
                    check(landed.contains(id),"real seeded Hopper completes a jump");
                    activatedHoppers[size_t(band)].insert(run.findEnemy(id)->monster);
                }
            }
            ++count;
        }
    }
    check(patterns.size()==4,"all encounter patterns occur");
    std::cout<<"Replacement coverage: I.Blob="<<seen.contains(monsterId(15,2))
        <<" Grilled="<<seen.contains(monsterId(15,3))<<" Hopper substitutions="<<substitutedHoppers
        <<" Drowned substitutions="<<substitutedChargers<<'\n';
    check(replacementCoverage(),"natural default-chance I.Blob, Grilled and Hopper substitutions are reachable");
    check(substitutedChargers>0,"natural 50 percent Drowned substitution is reached in seeded floors");
    std::cout<<"Scorched floors="<<scorchedFloors<<" Hopper substitutions="<<substitutedHoppers<<" Drowned substitutions="<<substitutedChargers<<'\n';
    for(int band=0;band<3;++band){check(activatedRings[size_t(band)]==2,"Ring Fly encounters activate in every approved band");std::cout<<"Activated Ring Fly groups band="<<band<<" count="<<activatedRings[size_t(band)]<<'\n';}
    for(int band=0;band<3;++band){check(activatedHoppers[size_t(band)].size()==2,"both Hopper forms activate in each approved band");std::cout<<"Activated Hopper forms band="<<band<<" count="<<activatedHoppers[size_t(band)].size()<<'\n';}
    for(int band=0;band<4;++band)for(int pattern=0;pattern<4;++pattern) {
        const auto &pool=defaultMechanics()->encounterPool(band,EncounterPattern(pattern));
        for(const auto *entries:{&pool.basics,&pool.specialists})for(const auto &entry:*entries)
            if(entry.weight>0)check(seen.contains(entry.monster),"enabled pool actor unreachable in seeded regression sample: "+monsterIdText(entry.monster));
    }
    std::cout<<"Reachable pool identities="<<seen.size()<<'\n';
    for(int band=0;band<4;++band)std::cout<<"band="<<band<<" meanThreat="<<double(threats[size_t(band)])/groups[size_t(band)]<<'\n';
    check(double(threats[3])/groups[3]>double(threats[0])/groups[0],"late floors increase combined threat");
    const std::set<MonsterId> expectedStatues{monsterId(42),monsterId(42,1),monsterId(42,2),monsterId(201),monsterId(202),monsterId(202,10),monsterId(202,10,1),monsterId(203),monsterId(235),monsterId(236),monsterId(804),monsterId(804,0,1),monsterId(804,0,2),monsterId(804,0,3)};
    check(statueSeen==expectedStatues,"all fourteen enabled hazard identities have actual legal seeded placement");
    std::cout<<"Reachable statue identities="<<statueSeen.size()<<'\n';
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
int main(int argc,char **argv){try{
    if(argc==4&&std::string(argv[1])=="--scan-placement") {scanPlacement(std::stoull(argv[2]),std::stoull(argv[3]));return 0;}
    plans();determinism();bossRules();weakBuildWins();floors();std::cout<<"PASS floor identities, threat grammar, safe geometry and complete canyon boss\n";
}catch(const std::exception &e){std::cerr<<"FAIL "<<e.what()<<'\n';return 1;}}
