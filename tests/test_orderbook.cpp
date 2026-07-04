#include "test_framework.h"
#include "OrderBook.h"

// ── Test 1: Adding an order creates a new price level ──────
void test_addOrder_newPriceLevel()
{
    OrderBook book; // fresh book, no leftover state from other tests

    book.addOrder({1, Side::BUY, 100.0, 500, 1000});

    auto bid = book.getBestBid();
    REQUIRE(bid.has_value());      // a bid should exist now
    REQUIRE(bid.value() == 100.0); // and it should be exactly 100.0
}

// ── Test 2: Adding a second order at the SAME price ─────────
// should add to the existing level's total quantity, not create a new one
void test_addOrder_existingPriceLevel()
{
    OrderBook book;

    book.addOrder({1, Side::BUY, 100.0, 500, 1000});
    book.addOrder({2, Side::BUY, 100.0, 300, 2000});

    auto depth = book.getBookDepth(Side::BUY, 5);

    REQUIRE(depth.size() == 1);      // still just ONE price level
    REQUIRE(depth[0].second == 800); // but combined quantity 500+300
}

// ── Test 3: Cancelling an order from the middle of a queue ──
void test_cancelOrder_middleOfQueue()
{
    OrderBook book;

    book.addOrder({1, Side::BUY, 100.0, 500, 1000});
    book.addOrder({2, Side::BUY, 100.0, 300, 2000}); // this one gets cancelled
    book.addOrder({3, Side::BUY, 100.0, 200, 3000});

    book.cancelOrder(2);

    auto depth = book.getBookDepth(Side::BUY, 5);
    REQUIRE(depth[0].second == 700); // 500 + 200, order 2's 300 is gone
}

// ── Test 4: Modifying an order's quantity ────────────────────
void test_modifyOrder_reducingQuantity()
{
    OrderBook book;

    book.addOrder({1, Side::BUY, 100.0, 500, 1000});
    book.modifyOrder(1, 200);

    auto depth = book.getBookDepth(Side::BUY, 5);
    REQUIRE(depth[0].second == 200); // quantity should now be 200
}

// ── Test 5: Cancelling a non-existent order should not crash ─
void test_cancelOrder_nonExistent()
{
    OrderBook book;

    book.addOrder({1, Side::BUY, 100.0, 500, 1000});
    book.cancelOrder(999); // does not exist — should just print a message, not crash

    // Confirm order 1 is untouched
    auto depth = book.getBookDepth(Side::BUY, 5);
    REQUIRE(depth.size() == 1);
    REQUIRE(depth[0].second == 500);
}

int main()
{
    std::cout << "Running OrderBook tests...\n\n";

    test_addOrder_newPriceLevel();
    test_addOrder_existingPriceLevel();
    test_cancelOrder_middleOfQueue();
    test_modifyOrder_reducingQuantity();
    test_cancelOrder_nonExistent();

    printTestSummary();

    // Return non-zero exit code if any test failed
    // This matters later for CI/CD pipelines — a failed test should
    // make the build itself report failure, not just print text
    return (g_testsFailed == 0) ? 0 : 1;
}