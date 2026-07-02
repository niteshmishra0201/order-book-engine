#include "OrderBook.h"
#include <iostream>

int main() {
    OrderBook book;

    // Create and add some orders
    Order o1 = {1, Side::BUY,  100.50, 500, 1000};
    Order o2 = {2, Side::BUY,  100.50, 300, 2000};
    Order o3 = {3, Side::BUY,   99.00, 200, 3000};
    Order o4 = {4, Side::SELL, 101.00, 400, 4000};
    Order o5 = {5, Side::SELL, 102.00, 600, 5000};

    book.addOrder(o1);
    book.addOrder(o2);
    book.addOrder(o3);
    book.addOrder(o4);
    book.addOrder(o5);

    book.printBook();

    return 0;
}