#include "content/Mechanics.hpp"
#include <iostream>
int main(int argc,char **argv) {
    try {
        const auto content=argc>1?dw::MechanicsLibrary::load(argv[1]):dw::defaultMechanics();
        std::cout<<"Valid mechanics: "<<content->items().size()<<" items, "<<content->monsters().size()
                 <<" monster definitions; fingerprint "<<content->fingerprint()<<'\n'
                 <<"Loaded from "<<content->directory()<<'\n';
        return 0;
    } catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}
}
