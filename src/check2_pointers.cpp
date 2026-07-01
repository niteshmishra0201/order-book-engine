#include<iostream>

class order{
private:
    int id;
    int quantity;

public:
    order(int id, int quantity){
        this->id = id;
        this->quantity = quantity;
    }

    void display(){
        std::cout << "Your ID is " << id << std::endl;
        std::cout << "Number of Quantity is " << quantity << std::endl;
    }

    void reduceQuantity(int amount){
        quantity -= amount;
    }

    int getId(){
        return id;
    }
};

// Function outside the class
void fillorder(order &obj, int fillQty){
    obj.reduceQuantity(fillQty);
}

int main(){

    order order1(1, 500);
    order1.display();


    fillorder(order1, 200);

    std::cout << "\nAfter filling order:\n";
    order1.display();


    order *ptr = &order1;

    std::cout << "\nID using Pointer: " << ptr->getId() << std::endl;

    return 0;
}