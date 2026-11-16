#include "world/SourceShopStock.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace dw;
int main(){try{
    const auto root=std::filesystem::path(__FILE__).parent_path().parent_path()/"docs/reports/isaac-first-floor-parity/d12c-shop-stock/source";
    std::ifstream stock(root/"native-stock.csv");std::string line;std::getline(stock,line);int count=0;
    while(std::getline(stock,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);uint32_t seed,after;int level,sale;
        in>>seed>>level;const auto result=sourceShopStock(seed,level);
        for(int expected:result.categories){int actual;in>>actual;if(expected!=actual)throw std::runtime_error("stock category mismatch");}
        in>>sale>>after;if(!in||sale!=result.discountSlot||after!=result.rngAfter)throw std::runtime_error("stock RNG/discount mismatch");++count;
    }
    if(count!=1551)throw std::runtime_error("missing stock reference cases");
    std::ifstream prices(root/"native-discounts.csv");std::getline(prices,line);int discounts=0;
    while(std::getline(prices,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);int base,copies,price;in>>base>>copies>>price;
        if(!in||sourceShopDiscountPrice(base,copies)!=price)throw std::runtime_error("discount arithmetic mismatch");++discounts;
    }
    if(discounts!=155)throw std::runtime_error("missing price reference cases");
    std::ifstream items(root/"native-item-prices.csv");std::getline(items,line);int itemPrices=0;
    while(std::getline(items,line)) {
        std::replace(line.begin(),line.end(),',',' ');std::istringstream in(line);uint32_t seed;int slot,price;
        in>>seed>>slot>>price;
        if(!in||price!=15)throw std::runtime_error("ordinary Steam Sale price mismatch");++itemPrices;
    }
    if(itemPrices!=30)throw std::runtime_error("missing item price cases");
    std::cout<<"PASS "<<count<<" native stock schedules, "<<discounts<<" native/CRT discount cases, "<<itemPrices<<" native collectible base prices\n";
}catch(const std::exception &e){std::cerr<<e.what()<<'\n';return 1;}}
