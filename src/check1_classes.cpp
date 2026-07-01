#include<iostream>
#include<string>
using namespace std;

class priceLevel{
    private:
    double price;
    int  totalQuantity;

    public:
    priceLevel(double price , int totalQuantity){
        this->price = price;
        this->totalQuantity = totalQuantity;
    }

    ~priceLevel(){
        cout<<"code is destroy"<<endl;
    }

    void display(){
        cout<<"price is "<< price<<endl;
        cout<<"totalQuantity is "<< totalQuantity<<endl;
    }
};

int main(){
    //Creating objects

    priceLevel Level1(22.00 , 10);
    priceLevel level2(23.00, 100);

    Level1.display();
    level2.display();

    return 0;
}