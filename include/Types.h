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

// ── OrderLocation ────────────────────────────────────────
// Stores WHERE an order lives in the book
// Used by orderIndex for O(1) cancel/modify lookup
// Safer than storing Order* which can become dangling
struct OrderLocation {
    Side   side;   // which side of the book (BUY/SELL)
    double price;  // which price level it sits at
};