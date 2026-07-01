#include "Order.h"

Order::Order(int id , double price , int quantity , std::string side){
    this->id = id;
    this->price = price;
    this->quantity = quantity;
    this->side = side;
}

Order::~Order(){
    std::cout<<"destructor called"<<std::endl;

}

void Order::display(){
    std::cout << "id is " << id 
              << " Price is " << price 
              << " total quantity is " << quantity << "\n";
}

void Order::reduceQuantity(int amount){
    quantity -= amount;
}