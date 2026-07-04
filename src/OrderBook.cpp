#include "OrderBook.h"
#include <iostream>

bool OrderBook::addOrder(Order order) {
    // ── Validation 1: reject non-positive quantity ───────
    // A quantity of 0 or less makes no logical sense as an order
    if (order.quantity <= 0) {
        std::cout << "Add rejected: order " << order.id
                  << " has invalid quantity (" << order.quantity << ")\n";
        return false;
    }

    // ── Validation 2: reject duplicate order ID ──────────
    // .count() returns 1 if the key exists, 0 if not — O(1) check
    // We check this BEFORE touching the book, so a rejected
    // order leaves absolutely no trace behind
    if (orderIndex.count(order.id) > 0) {
        std::cout << "Add rejected: order ID " << order.id
                  << " already exists\n";
        return false;
    }

    // ── Original logic — unchanged from Day 2/3 ──────────
    if (order.side == Side::BUY) {
        bids[order.price].price = order.price;
        bids[order.price].orders.push_back(order);
    } else {
        asks[order.price].price = order.price;
        asks[order.price].orders.push_back(order);
    }

    orderIndex[order.id] = {order.side, order.price};

    return true;   // success
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

std::optional<double> OrderBook::getBestBid() {
    // If bids side is empty, there's no best bid — return empty box
    if (bids.empty()) {
        return std::nullopt;
    }
    // rbegin() = last element in ascending sorted map = highest price
    // ->first gets the key (price) of that element
    return bids.rbegin()->first;
}

std::optional<double> OrderBook::getBestAsk() {
    // If asks side is empty, there's no best ask — return empty box
    if (asks.empty()) {
        return std::nullopt;
    }
    // begin() = first element in ascending sorted map = lowest price
    return asks.begin()->first;
}

std::vector<std::pair<double, int>> OrderBook::getBookDepth(Side side, int n) {
    // This will hold our result — list of (price, totalQty) pairs
    std::vector<std::pair<double, int>> depth;

    // Pick which side we're reading from
    // Note: we use const auto& here — we're only reading, never modifying
    // const means "promise not to change this", & means "no copy, just reference"
    if (side == Side::BUY) {
        // Bids: best (highest) first, so iterate rbegin -> rend
        int count = 0;
        for (auto it = bids.rbegin(); it != bids.rend(); ++it) {
            if (count >= n) break;   // stop once we have n levels

            // Sum all order quantities at this price level
            int totalQty = 0;
            for (const auto& o : it->second.orders) {
                totalQty += o.quantity;
            }

            depth.push_back({it->first, totalQty});
            count++;
        }
    } else {
        // Asks: best (lowest) first, so iterate begin -> end (normal order)
        int count = 0;
        for (auto it = asks.begin(); it != asks.end(); ++it) {
            if (count >= n) break;

            int totalQty = 0;
            for (const auto& o : it->second.orders) {
                totalQty += o.quantity;
            }

            depth.push_back({it->first, totalQty});
            count++;
        }
    }

    return depth;
}