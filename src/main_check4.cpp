#include "OrderBook.h"
#include <iostream>

int main() {
    OrderBook book;

    bool ok1 = book.addOrder({1, Side::BUY,  100.50, 500, 1000});
    std::cout << "Order 1 added: " << (ok1 ? "yes" : "no") << "\n";

    book.addOrder({2, Side::BUY,  100.50, 300, 2000});
    book.addOrder({3, Side::BUY,   99.00, 200, 3000});
    book.addOrder({4, Side::SELL, 101.00, 400, 4000});
    book.addOrder({5, Side::SELL, 102.00, 600, 5000});
    book.addOrder({6, Side::SELL, 103.00, 100, 6000});

    book.printBook();

    // Try adding invalid orders
    bool badQty = book.addOrder({7, Side::BUY, 100.0, 0, 7000});
    std::cout << "\nOrder 7 (qty=0) added: " << (badQty ? "yes" : "no") << "\n";

    bool dupId = book.addOrder({1, Side::SELL, 105.0, 100, 8000});
    std::cout << "Order with duplicate ID 1 added: " << (dupId ? "yes" : "no") << "\n";

    return 0;
}