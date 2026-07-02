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

    orderIndex[order.id] = {order.side, order.price};
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

void OrderBook::cancelOrder(int orderId) {
    // ── Step 1: Check order exists ───────────────────────
    if (orderIndex.count(orderId) == 0) {
        std::cout << "Cancel failed: order " << orderId << " not found\n";
        return;
    }

    // ── Step 2: Get location from index ──────────────────
    // O(1) hash map lookup — this is why orderIndex exists
    OrderLocation loc = orderIndex[orderId];

    // ── Step 3: Get reference to correct side of book ────
    // auto& means "reference, figure out type automatically"
    // We pick bids or asks based on side
    auto& side = (loc.side == Side::BUY) ? bids : asks;

    // ── Step 4: Get reference to the price level ─────────
    auto& level = side[loc.price];

    // ── Step 5: Find order in deque and erase it ─────────
    // We scan only this price level's deque — not the whole book
    auto& orders = level.orders;
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (it->id == orderId) {
            orders.erase(it);   // remove at iterator position
            break;              // stop scanning immediately
        }
    }

    // ── Step 6: Clean up empty price level ───────────────
    // If no orders remain at this price, remove the level entirely
    // This keeps the book clean — no ghost price levels
    if (level.orders.empty()) {
        side.erase(loc.price);
    }

    // ── Step 7: Remove from index ────────────────────────
    orderIndex.erase(orderId);

    std::cout << "Order " << orderId << " cancelled\n";
}

void OrderBook::modifyOrder(int orderId, int newQuantity) {
    // ── Step 1: Validate ─────────────────────────────────
    if (orderIndex.count(orderId) == 0) {
        std::cout << "Modify failed: order " << orderId << " not found\n";
        return;
    }

    if (newQuantity <= 0) {
        std::cout << "Modify failed: quantity must be positive\n";
        return;
    }

    // ── Step 2: Get location ──────────────────────────────
    OrderLocation loc = orderIndex[orderId];

    // ── Step 3: Get correct side ──────────────────────────
    auto& side = (loc.side == Side::BUY) ? bids : asks;

    // ── Step 4: Find order and update quantity in place ───
    // No re-queuing — time priority is preserved
    // This is correct behavior for quantity-only modifications
    auto& orders = side[loc.price].orders;
    for (auto& o : orders) {
        if (o.id == orderId) {
            o.quantity = newQuantity;
            std::cout << "Order " << orderId
                      << " modified: new qty = " << newQuantity << "\n";
            break;
        }
    }
}