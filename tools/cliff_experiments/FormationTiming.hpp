#pragma once
#include <chrono>
#include <cstdlib>
#include <iostream>

namespace dw::rockFormations {
// Timings observe the ordinary checked path. No check is disabled for a benchmark.
inline thread_local double validationMilliseconds = 0;
inline thread_local unsigned validationDepth = 0;
inline thread_local unsigned constructionCheckDepth = 0;
inline thread_local double constructionCheckMilliseconds = 0;
struct ConstructionChecks {
    std::chrono::steady_clock::time_point start=std::chrono::steady_clock::now();
    ConstructionChecks(){++constructionCheckDepth;}
    ~ConstructionChecks(){if(--constructionCheckDepth==0)constructionCheckMilliseconds+=std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-start).count();}
};
struct ConstructionTiming {
    const char *name;
    bool enabled=std::getenv("DW_CLIFF_PROFILE")!=nullptr;
    std::chrono::steady_clock::time_point start{};
    double validationStart=validationMilliseconds;
    explicit ConstructionTiming(const char *stage):name(stage) {if(enabled)start=std::chrono::steady_clock::now();}
    ~ConstructionTiming() {
        if(enabled) {
            const auto elapsed=std::chrono::duration<double,std::milli>(std::chrono::steady_clock::now()-start).count();
            std::cout<<"FORMATION_STAGE name="<<name<<" checked_ms="<<elapsed<<" validation_ms="<<validationMilliseconds-validationStart
                     <<" construction_ms="<<elapsed-(validationMilliseconds-validationStart)<<'\n';
        }
    }
};
struct ValidationTiming {
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    const bool constructive=constructionCheckDepth>0;
    const double constructionStart=constructionCheckMilliseconds;
    ValidationTiming() { ++validationDepth; }
    ~ValidationTiming() {
        if (--validationDepth == 0 && !constructive)
            validationMilliseconds += std::chrono::duration<double, std::milli>(
                std::chrono::steady_clock::now() - start).count()-(constructionCheckMilliseconds-constructionStart);
    }
    ValidationTiming(const ValidationTiming &) = delete;
    ValidationTiming &operator=(const ValidationTiming &) = delete;
};
}
