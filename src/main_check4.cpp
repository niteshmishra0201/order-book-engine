#include "Types.h"
#include <iostream>

int main() {
    // Create one Order
    Order o1;
    o1.id        = 1;
    o1.side      = Side::BUY;
    o1.price     = 100.50;
    o1.quantity  = 500;
    o1.timestamp = 1000000;

    std::cout << "Order ID: "    << o1.id       << "\n";
    std::cout << "Price: "       << o1.price    << "\n";
    std::cout << "Quantity: "    << o1.quantity << "\n";
    std::cout << "Side: "        << (o1.side == Side::BUY ? "BUY" : "SELL") << "\n";

    // Create one PriceLevel and push order into it
    PriceLevel level;
    level.price = 100.50;
    level.orders.push_back(o1);

    std::cout << "\nPriceLevel price: " << level.price << "\n";
    std::cout << "Orders at level: "   << level.orders.size() << "\n";

    return 0;
}