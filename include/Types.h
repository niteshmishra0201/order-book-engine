#pragma once

#include <cstdint>   
#include <deque>     
#include <string>    


enum class Side {
    BUY,
    SELL
};




struct Order {
    int      id;          
    Side     side;        
    double   price;       
    int      quantity;    
    uint64_t timestamp;   
};


struct PriceLevel {
    double             price;   
    std::deque<Order>  orders;  
};