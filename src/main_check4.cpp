#include "OrderBook.h"
#include <iostream>

int main() {
    OrderBook book;

    book.addOrder({1, Side::BUY,  100.50, 500, 1000});
    book.addOrder({2, Side::BUY,  100.50, 300, 2000});
    book.addOrder({3, Side::BUY,   99.00, 200, 3000});
    book.addOrder({4, Side::SELL, 101.00, 400, 4000});
    book.addOrder({5, Side::SELL, 102.00, 600, 5000});
    book.addOrder({6, Side::SELL, 103.00, 100, 6000});

    book.printBook();

    // --- Test getBestBid / getBestAsk ---
    std::optional<double> bestBid = book.getBestBid();
    std::optional<double> bestAsk = book.getBestAsk();

    if (bestBid.has_value()) {
        std::cout << "\nBest Bid: " << bestBid.value() << "\n";
    }
    if (bestAsk.has_value()) {
        std::cout << "Best Ask: " << bestAsk.value() << "\n";
    }

    // --- Test getBookDepth ---
    std::cout << "\nTop 2 BID levels:\n";
    auto bidDepth = book.getBookDepth(Side::BUY, 2);
    for (const auto& level : bidDepth) {
        std::cout << "  Price: " << level.first
                  << " | Qty: " << level.second << "\n";
    }

    std::cout << "\nTop 2 ASK levels:\n";
    auto askDepth = book.getBookDepth(Side::SELL, 2);
    for (const auto& level : askDepth) {
        std::cout << "  Price: " << level.first
                  << " | Qty: " << level.second << "\n";
    }

    // --- Test empty side behavior ---
    OrderBook emptyBook;
    std::optional<double> emptyBid = emptyBook.getBestBid();
    if (!emptyBid.has_value()) {
        std::cout << "\nEmpty book correctly returns no best bid\n";
    }

    return 0;
}