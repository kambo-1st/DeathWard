#include "RockFormations.hpp"
#include <algorithm>
#include <stdexcept>

namespace dw::rockFormations {
std::vector<FormationDescriptor> compose(float wallLength,uint64_t seed,bool authored) {
    std::vector<FormationDescriptor> forms{
        // yaw, lean, roof slope, secondary crown slope, crown position,
        // side taper, rim bevel width, footprint corners, beveled side mask.
        {"left_join", .035f, 4.0f, 4.1f, 2.25f, .06f,
         {-.18f, {-.08f,-.02f}, {-.24f,.08f}, {-.32f,.08f}, .10f, .14f, .08f, 7, 0x12}},
        {"left_mass", .235f, 5.6f, 4.7f, 3.10f, .12f,
         {.14f, {.09f,-.03f}, {.09f,-.04f}, {-.30f,.08f}, .13f, .11f, .10f, 7, 0x24}},
        {"dominant", .49f, 8.2f, 5.9f, 3.65f, .28f,
         {-.12f, {-.07f,.03f}, {-.045f,.04f}, {.28f,-.08f}, .08f, .09f, .11f, 8, 0x42}},
        {"right_mass", .745f, 5.3f, 4.7f, 2.85f, .32f,
         {.23f, {-.10f,-.04f}, {.12f,-.04f}, {-.25f,.20f}, .12f, .16f, .07f, 6, 0x11}},
        {"right_join", .97f, 4.8f, 4.1f, 2.25f, .03f,
         {-.16f, {.06f,-.02f}, {.23f,.06f}, {.28f,.14f}, .14f, .12f, .09f, 7, 0x21}},
        {"left_shoulder", .34f, 4.0f, 2.8f, 1.35f, .08f,
         {-.24f, {.06f,0}, {-.18f,.08f}, {.22f,.08f}, .18f, .14f, .06f, 6, 0x10}},
        {"middle_shoulder", .615f, 3.8f, 3.1f, 1.95f, .04f,
         {.12f, {-.08f,.02f}, {.10f,-.16f}, {-.32f,.12f}, .15f, .10f, .08f, 7, 0x22}},
        {"right_shoulder", .845f, 3.0f, 2.6f, 1.25f, .03f,
         {-.32f, {.02f,-.02f}, {.29f,.06f}, {-.18f,.18f}, .13f, .16f, .05f, 6, 0x08}},
        {"left_base", .17f, 2.4f, 1.9f, .65f, .02f,
         {.15f, {.03f,0}, {-.12f,.12f}, {.24f,.12f}, .12f, .20f, .05f, 6, 0x10}},
        {"middle_base", .415f, 2.5f, 1.9f, .75f, .02f,
         {-.28f, {-.02f,0}, {.22f,-.08f}, {-.24f,.10f}, .10f, .18f, .04f, 7, 0x20}},
        {"dominant_base", .57f, 1.9f, 1.7f, .55f, .02f,
         {.22f, {.05f,-.03f}, {-.20f,.10f}, {.30f,.10f}, .12f, .16f, .05f, 6, 0x08}},
        {"right_base", .79f, 2.0f, 1.7f, .45f, .02f,
         {-.14f, {-.04f,.02f}, {.16f,.06f}, {-.22f,.08f}, .14f, .17f, .04f, 7, 0x10}}};

    for(size_t i=0;i<forms.size();++i)
        forms[i].role=i>=8?FormationRole::Base:i>=5?FormationRole::Shoulder:
            i==2?FormationRole::Dominant:(i==0 || i==4)?FormationRole::Join:FormationRole::Supporting;
    if(authored)return forms;
    if(wallLength<14 || wallLength>30)throw std::runtime_error("Unsupported formation section length (14..30 metres)");
    Random rng(seed^0x434f4d504f5345ULL);
    Random roles(seed^0x524f4c45534c4159ULL);
    const auto shoulderCount=1+roles.bounded(3),baseCount=1+roles.bounded(4);
    const auto shoulderOffset=roles.bounded(3),baseOffset=roles.bounded(4);
    const float scale=wallLength/24.512871f;
    for(size_t i=0;i<forms.size();++i) {
        auto &f=forms[i];
        if(i>=8)f.enabled=(i-8+baseOffset)%4<baseCount;
        else if(i>=5)f.enabled=(i-5+shoulderOffset)%3<shoulderCount;
        if(i!=0 && i!=4)f.at+=rng.real(-.012f,.012f);
        f.width*=scale*rng.real(.92f,1.08f);
        f.depth*=rng.real(.95f,1.05f);
        f.height*=rng.real(.95f,1.05f);
        f.setback+=rng.real(0,.08f);
        f.profile.yaw+=rng.real(-.055f,.055f);
        f.profile.lean.x+=rng.real(-.018f,.018f);
        f.profile.roof.x+=rng.real(-.025f,.025f);
        f.profile.roof.y+=rng.real(-.02f,.02f);
        f.profile.crownAt*=rng.real(.85f,1.15f);
    }
    return forms;
}
} // namespace dw::rockFormations
