#pragma once
#include "cinematic/Cinematic.hpp"
#include "render/TownActorModels.hpp"
#include "rlgl.h"
#include <map>
#include <memory>

namespace dw {
class CinematicCast {
  public:
    void unload() { models_.clear(); }
    void draw(const CinematicPlayer &player, Shader shader = {}, Texture2D shadow = {}) {
        for(const auto &actor:player.actors()) {
            const auto &name=actor.member.model;
            auto &model=models_[name];
            if(!model) {
                model=std::make_unique<SkinnedModel>();
                auto path=TownActorModels::modelPath(name);
                if(name!="bandit"&&name!="cowgirl") {
                    path=std::filesystem::path(DEATHWARD_ASSET_DIR)/"cinematic_cast"/(name+".glb");
                    if(!std::filesystem::exists(path))path=std::filesystem::path(GetApplicationDirectory())/"assets/cinematic_cast"/(name+".glb");
                }
                model->load(path,true);
            }
            if(!model->loaded())continue;
            const auto bounds=GetModelBoundingBox(model->model());
            const float scale=actor.member.scale*1.9f/std::max(.1f,bounds.max.y-bounds.min.y);
            if(model->poseCinematic(player.time(),actor.pose==ActorPose::Seated,
                                    actor.pose==ActorPose::Walking,actor.talking))
            {
                rlDisableBackfaceCulling();
                model->draw(actor.position,actor.facing,scale,shader,shadow);
                rlEnableBackfaceCulling();
            }
        }
    }
  private:
    std::map<std::string,std::unique_ptr<SkinnedModel>> models_;
};
}
