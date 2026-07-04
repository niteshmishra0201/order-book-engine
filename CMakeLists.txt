cmake_minimum_required(VERSION 3.10)

project(OrderBookEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(order_book_engine
    src/Order.cpp
    src/OrderBook.cpp
    src/main_check4.cpp
)

add_executable(run_tests
    src/OrderBook.cpp
    tests/test_orderbook.cpp
)