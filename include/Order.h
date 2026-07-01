#pragma once
#include<iostream>
#include<string>

class Order{
    private:
    int id;
    double price;
    int quantity;
    std::string side;

    public:
    Order(int id , double price , int quantity , std::string side);
    ~Order();

    void display();

    int getId(){
        return id;
    };

    int getQuantity(){
        return quantity;
    }

    void reduceQuantity(int amount);

};