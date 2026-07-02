#pragma once

#include "Types.h"
#include <map>
#include <unordered_map>

class OrderBook {
private:
    std::map<double, PriceLevel>       bids;
    std::map<double, PriceLevel>       asks;
    std::unordered_map<int, OrderLocation> orderIndex;

public:
    void addOrder(Order order);
    void cancelOrder(int orderId);
    void modifyOrder(int orderId, int newQuantity);
    void printBook();
};