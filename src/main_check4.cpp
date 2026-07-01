#include "Order.h"
#include<iostream>

int main(){
    Order order1(001 , 110.00, 500, "Unknown");
    Order order2(002 , 120.00, 400, "Unknown2");

    order1.display();
    order2.display();

    order1.reduceQuantity(100);
    order1.display();

    std::cout << "ID of order2: " << order2.getId() << "\n";

    return 0;
}