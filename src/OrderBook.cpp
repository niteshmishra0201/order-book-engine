#include "OrderBook.h"
#include <iostream>

void OrderBook::addOrder(Order order)
{
    if (order.side == Side::BUY)
    {

        bids[order.price].price = order.price;

        bids[order.price].orders.push_back(order);
    }
    else
    {
        asks[order.price].price = order.price;

        asks[order.price].orders.push_back(order);
    }

    if (order.side == Side::BUY)
    {
        orderIndex[order.id] = &bids[order.price].orders.back();
    }
    else
    {
        orderIndex[order.id] = &asks[order.price].orders.back();
    }
}

void OrderBook::printBook()
{
    std::cout << "\n===== ORDER BOOK =====\n";

    std::cout << "--- ASKS ---\n";
    for (auto it = asks.rbegin(); it != asks.rend(); ++it)
    {
        std::cout << "  Price: " << it->second.price
                  << " | Orders: " << it->second.orders.size()
                  << " | Total Qty: ";
        int total = 0;
        for (auto &o : it->second.orders)
            total += o.quantity;
        std::cout << total << "\n";
    }

    std::cout << "--- BIDS ---\n";
    for (auto it = bids.rbegin(); it != bids.rend(); ++it)
    {
        std::cout << "  Price: " << it->second.price
                  << " | Orders: " << it->second.orders.size()
                  << " | Total Qty: ";
        int total = 0;
        for (auto &o : it->second.orders)
            total += o.quantity;
        std::cout << total << "\n";
    }

    std::cout << "======================\n";
}