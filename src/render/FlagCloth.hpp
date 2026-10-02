#pragma once
#include "world/FlagCloth.hpp"

namespace dw {
class FlagCloth {
  public:
    FlagCloth(const Mesh &source,uint32_t seed);
    ~FlagCloth();
    FlagCloth(const FlagCloth &)=delete;
    FlagCloth &operator=(const FlagCloth &)=delete;
    void update(Matrix placement,double time,float storm);
    const Mesh &mesh() const {return mesh_;}
    Box bounds() const {return surface_.bounds;}
  private:
    FlagSurface surface_;
    Mesh mesh_{};
    uint32_t seed_;
    double time_=-1;
    float storm_=-1;
    Matrix placement_{};
};
}
