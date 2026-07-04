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

// ── Test 6: Zero quantity order is rejected ──────────────
void test_addOrder_zeroQuantity_rejected() {
    OrderBook book;

    bool result = book.addOrder({1, Side::BUY, 100.0, 0, 1000});

    REQUIRE(result == false);              // add should fail
    REQUIRE(!book.getBestBid().has_value()); // book should remain empty
}

// ── Test 7: Negative quantity order is rejected ──────────
void test_addOrder_negativeQuantity_rejected() {
    OrderBook book;

    bool result = book.addOrder({1, Side::BUY, 100.0, -50, 1000});

    REQUIRE(result == false);
    REQUIRE(!book.getBestBid().has_value());
}

// ── Test 8: Duplicate order ID is rejected ───────────────
void test_addOrder_duplicateId_rejected() {
    OrderBook book;

    bool first  = book.addOrder({1, Side::BUY, 100.0, 500, 1000});
    bool second = book.addOrder({1, Side::SELL, 105.0, 300, 2000}); // same ID!

    REQUIRE(first == true);    // first one succeeds
    REQUIRE(second == false);  // second one rejected

    // The ORIGINAL order should be untouched — still a BUY at 100.0
    auto bid = book.getBestBid();
    REQUIRE(bid.has_value());
    REQUIRE(bid.value() == 100.0);

    // And the ask side should remain completely empty —
    // proving the rejected order left NO trace at all
    REQUIRE(!book.getBestAsk().has_value());
}

// ── Test 9: Cancelling the last order at a price level ───
// removes the level ENTIRELY, not just empties it
void test_cancelOrder_removesEmptyLevel() {
    OrderBook book;

    book.addOrder({1, Side::BUY, 100.0, 500, 1000});
    book.cancelOrder(1);  // this was the ONLY order at this price

    auto depth = book.getBookDepth(Side::BUY, 5);

    // The level itself should be gone — size 0, not size 1 with qty 0
    REQUIRE(depth.size() == 0);
    REQUIRE(!book.getBestBid().has_value());
}

int main() {
    std::cout << "Running OrderBook tests...\n\n";

    test_addOrder_newPriceLevel();
    test_addOrder_existingPriceLevel();
    test_cancelOrder_middleOfQueue();
    test_modifyOrder_reducingQuantity();
    test_cancelOrder_nonExistent();

    test_addOrder_zeroQuantity_rejected();
    test_addOrder_negativeQuantity_rejected();
    test_addOrder_duplicateId_rejected();
    test_cancelOrder_removesEmptyLevel();

    printTestSummary();

    return (g_testsFailed == 0) ? 0 : 1;
}