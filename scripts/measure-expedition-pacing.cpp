// Deterministic headless pacing trial. This is an invulnerable scripted player,
// not a human playtest. It uses real navigation, weapons, enemies and item offers.
// Compile against deathward_core; optional argv[1] selects one seed.
#include "combat/Simulation.hpp"
#include <iomanip>
#include <iostream>
#include <queue>
#include <stdexcept>
using namespace dw;
namespace {
struct Trial {
    Simulation run;
    double walk=0,backtrack=0;
    bool retracing=false;
    std::set<int> traversed,visited,required;
    explicit Trial(uint64_t seed,ExpeditionPacing pacing)
        :run(seed,1,{},MissionTheme::Canyon,true,false,WitnessAccount::None,0,pacing) {
        run.godMode=true;visited.insert(0);
    }
    void tick(const Input &input={}) {
        const auto before=run.player.position;const bool clear=run.roomClear;
        run.step(input);run.audioCues.clear();
        if(clear&&distance(before,run.player.position)>.001f) {
            walk+=Tick;if(retracing)backtrack+=Tick;
        }
        if(run.stats.duration>3600)throw std::runtime_error("one-hour simulation limit");
    }
    void fight() {
        std::vector<Vector3> navigation;
        for(int frame=0;!run.roomClear;++frame) {
            if(frame>=36000)throw std::runtime_error("combat timeout in room "+std::to_string(run.room));
            const Enemy *target=nullptr;float best=1e9f;
            for(const auto &enemy:run.enemies) {
                const auto *definition=monsterDefinition(enemy.monster);
                if(!enemy.alive||enemy.friendly||(definition&&definition->roomHazard))continue;
                float score=distance(enemy.position,run.player.position);
                if(enemy.state==EnemyState::Buried||enemy.state==EnemyState::Teleporting)score+=100;
                if(score<best){best=score;target=&enemy;}
            }
            Input input;
            if(target) {
                input.fire=true;input.aim=target->position;
                if(frame%30==0) {
                    // Orbit the target to expose directional shields and move
                    // around cover; navigation keeps the player on walkable ground.
                    const float angle=float(frame)*.007f+float(target->id%7);
                    navigation=run.arena.path(run.player.position,
                        add(target->position,{5*std::cos(angle),0,5*std::sin(angle)}),.48f);
                }
                while(!navigation.empty()&&distance(run.player.position,navigation.front())<.45f)
                    navigation.erase(navigation.begin());
                if(!navigation.empty())input.movement=unit(sub(navigation.front(),run.player.position));
            }
            tick(input);
        }
        visited.insert(run.room);
    }
    void walkTo(Vector3 goal) {
        goal.y=.85f;
        auto path=run.arena.path(run.player.position,goal,.48f);
        size_t at=0;
        for(int frame=0;distance(run.player.position,goal)>.7f;++frame) {
            if(frame>=6000)throw std::runtime_error("navigation timeout in room "+std::to_string(run.room));
            if(!run.roomClear) {fight();path=run.arena.path(run.player.position,goal,.48f);at=0;}
            while(at<path.size()&&distance(run.player.position,path[at])<.06f)++at;
            if(at==path.size())throw std::runtime_error("walking path ended before its target");
            const auto delta=sub(path[at],run.player.position);
            Input input;input.movement=mul(unit(delta),std::min(1.f,length(delta)/(6*Tick)));
            tick(input);
        }
        Input stop;stop.standStill=true;tick(stop);
    }
    std::vector<int> route(int destination,bool locks=false) const {
        std::vector<int> parent(run.arena.roomCount(),-1),via(parent.size(),-1);
        std::queue<int> queue;queue.push(run.room);parent[size_t(run.room)]=run.room;
        while(!queue.empty()) {
            const int current=queue.front();queue.pop();
            for(int index:run.arena.rooms[size_t(current)].passages) {
                const auto &p=run.arena.passages[size_t(index)];
                if(p.locked&&!locks)continue;
                const int next=p.rooms[0]==current?p.rooms[1]:p.rooms[0];
                if(parent[size_t(next)]>=0)continue;
                parent[size_t(next)]=current;via[size_t(next)]=index;queue.push(next);
            }
        }
        if(parent[size_t(destination)]<0)return {};
        std::vector<int> result;
        for(int at=destination;at!=run.room;at=parent[size_t(at)])result.push_back(via[size_t(at)]);
        std::reverse(result.begin(),result.end());return result;
    }
    void go(int destination,bool finalFight=true) {
        const auto links=route(destination,true);
        if(destination!=run.room&&links.empty())throw std::runtime_error("no graph route");
        for(int index:links) {
            fight();
            const auto &p=run.arena.passages[size_t(index)];
            const int side=p.rooms[0]==run.room?0:1,next=p.rooms[size_t(1-side)];
            retracing=traversed.contains(index);
            walkTo(run.arena.doorApproach(index,side));
            if(!run.useDoor(index,side))throw std::runtime_error("door "+std::to_string(index)+" could not be used in room "+std::to_string(run.room)+" with "+std::to_string(run.keys)+" keys");
            for(int frame=0;run.room!=next;++frame) {
                if(frame>6000)throw std::runtime_error("passage traversal timeout: link "+std::to_string(index)+
                    " source "+std::to_string(p.rooms[size_t(side)])+" target "+std::to_string(next)+
                    " actual "+std::to_string(run.room)+" clear "+std::to_string(run.roomClear)+
                    " moving "+std::to_string(bool(run.moveDestination()))+
                    " shop "+std::to_string(run.shopOpen)+" reward "+std::to_string(run.rewardOpen)+
                    " exit "+std::to_string(run.floorExitRequested)+" finished "+std::to_string(run.finished)+
                    " distance "+std::to_string(distance(run.player.position,run.arena.doorApproach(index,1-side))));
                tick();
            }
            traversed.insert(index);visited.insert(run.room);
        }
        retracing=false;
        if(finalFight)fight();
    }
    void key() {
        int selected=-1;size_t length=SIZE_MAX;
        for(size_t i=0;i<run.arena.keys.size();++i) {
            const auto &key=run.arena.keys[i];if(key.collected)continue;
            const auto path=route(key.room);
            if((key.room==run.room||!path.empty())&&path.size()<length){selected=int(i);length=path.size();}
        }
        if(selected<0)throw std::runtime_error("no accessible key");
        auto &key=run.arena.keys[size_t(selected)];go(key.room);walkTo(key.position);
        for(int i=0;i<10&&!key.collected;++i)tick();
        if(!key.collected)throw std::runtime_error("key not collected");
    }
    void item() {
        if(!run.keys)key();
        int target=-1;size_t length=SIZE_MAX;
        for(int i=0;i<run.arena.roomCount();++i)
            if(run.arena.rooms[size_t(i)].kind==RoomKind::Power) {
                const auto path=route(i,true);if(path.size()<length){target=i;length=path.size();}
            }
        if(target<0)throw std::runtime_error("no power room");
        go(target);walkTo(run.arena.rooms[size_t(target)].objective);run.interact();
        if(!run.rewardOpen)throw std::runtime_error("power pedestal did not open");
        run.chooseReward(0);
    }
};
}
int main(int argc,char **argv) {
    std::vector<uint64_t> seeds{0,1,2,3,4,5,6,7,42,1866};
    if(argc>1)seeds={std::stoull(argv[1])};
    std::cout<<"seed,preset,rooms,ordinary_width,ordinary_depth,mean_corridor,min_corridor,max_corridor,residents,first_item_seconds,boss_arrival_seconds,full_clear_seconds,walking_seconds,backtracking_seconds,required_combat,optional_combat,result\n"<<std::fixed<<std::setprecision(3);
    for(uint64_t seed:seeds)
        for(auto pacing:{ExpeditionPacing::Classic,ExpeditionPacing::Growing,ExpeditionPacing::ShortCorridors,ExpeditionPacing::SmallRooms,ExpeditionPacing::Compact}) {
            Trial trial(seed,pacing);auto &run=trial.run;
            double width=0,depth=0,corridor=0,shortest=1e9,longest=0;int ordinary=0,residents=0,combats=0;
            for(int i=0;i<run.arena.roomCount();++i) {
                const auto &r=run.arena.rooms[size_t(i)];residents+=int(run.roomEnemies(i).size());
                if(r.kind==RoomKind::Combat||r.kind==RoomKind::Boss)++combats;
                if(r.kind!=RoomKind::Boss){++ordinary;width+=r.bounds.max.x-r.bounds.min.x;depth+=r.bounds.max.z-r.bounds.min.z;}
            }
            for(const auto &p:run.arena.passages){const double length=distance(p.from,p.to);corridor+=length;shortest=std::min(shortest,length);longest=std::max(longest,length);}
            double item=-1,boss=-1,complete=-1;int required=0;std::string result="ok";
            try {
                trial.item();item=run.stats.duration;
                if(!run.keys)trial.key();
                trial.go(run.finalRoom(),false);boss=run.stats.duration;trial.required=trial.visited;
                trial.fight();
                while(trial.visited.size()<run.arena.rooms.size()) {
                    int selected=-1;size_t length=SIZE_MAX;
                    for(int i=0;i<run.arena.roomCount();++i)if(!trial.visited.contains(i)) {
                        const auto path=trial.route(i,true);if(path.size()<length){selected=i;length=path.size();}
                    }
                    if(selected<0)throw std::runtime_error("unvisited room unreachable");
                    const auto &room=run.arena.rooms[size_t(selected)];
                    if(room.kind==RoomKind::Power&&!run.keys)trial.key();
                    trial.go(selected);
                }
                trial.go(run.finalRoom());trial.walkTo(run.arena.exit);run.interact();
                if(!run.floorExitRequested)throw std::runtime_error("floor exit not requested");
                complete=run.stats.duration;
            } catch(const std::exception &e) {result=e.what();std::cerr<<seed<<' '<<int(pacing)<<": "<<result<<'\n';}
            for(int i:trial.required)if(run.arena.rooms[size_t(i)].kind==RoomKind::Combat||run.arena.rooms[size_t(i)].kind==RoomKind::Boss)++required;
            std::cout<<seed<<','<<int(pacing)<<','<<run.arena.roomCount()<<','<<width/ordinary<<','<<depth/ordinary<<','<<corridor/run.arena.passages.size()<<','<<shortest<<','<<longest<<','<<residents<<','<<item<<','<<boss<<','<<complete<<','<<trial.walk<<','<<trial.backtrack<<','<<required<<','<<combats-required<<','<<result<<'\n'<<std::flush;
        }
}
