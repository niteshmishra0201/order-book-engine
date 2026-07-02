#include "OrderBook.h"
#include <iostream>

int main() {
    OrderBook book;

    // Add 5 orders
    book.addOrder({1, Side::BUY,  100.50, 500, 1000});
    book.addOrder({2, Side::BUY,  100.50, 300, 2000});
    book.addOrder({3, Side::BUY,   99.00, 200, 3000});
    book.addOrder({4, Side::SELL, 101.00, 400, 4000});
    book.addOrder({5, Side::SELL, 102.00, 600, 5000});

    std::cout << "=== Initial Book ===";
    book.printBook();

    // Cancel order 2 (BUY at 100.50)
    book.cancelOrder(2);
    std::cout << "\n=== After cancelling order 2 ===";
    book.printBook();

    // Modify order 1 quantity
    book.modifyOrder(1, 250);
    std::cout << "\n=== After modifying order 1 qty to 250 ===";
    book.printBook();

    // Cancel order 3 (only order at 99.00 — level should disappear)
    book.cancelOrder(3);
    std::cout << "\n=== After cancelling order 3 (empty level removed) ===";
    book.printBook();

    // Try cancelling non-existent order
    book.cancelOrder(999);

    return 0;
}