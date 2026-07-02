#pragma once

#include "Types.h"
#include <map>
#include <unordered_map>

class OrderBook {
private:

    std::map<double, PriceLevel> bids;


    std::map<double, PriceLevel> asks;

    std::unordered_map<int, Order*> orderIndex;

public:
    // Add a new order to the book
    void addOrder(Order order);

    void printBook();
};