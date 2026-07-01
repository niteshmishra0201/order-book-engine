#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include<algorithm>
#include<string>

int main(){

    std::vector<int> orderId;
    orderId.push_back(101);
    orderId.push_back(102);
    orderId.push_back(103);
    orderId.push_back(104);

    for(int i : orderId){
        std::cout<<"id is "<<i<<std::endl;
    }

    
    
    std::map<double , int> bidBook;
    bidBook[99.50] = 300;
    bidBook[100.00] = 500;
    bidBook[98.00] = 200;

for(auto& pair : bidBook){
    std::cout << "Price: " << pair.first << " Qty: " << pair.second << "\n";
}
std::cout << "Best bid: " << bidBook.rbegin()->first << "\n";

    std::unordered_map<int, std::string>  orderIndex;
    orderIndex[101] = "OPEN";
    orderIndex[102] = "OPEN";
    orderIndex[103] = "OPEN";

    orderIndex.erase(102);

std::cout << "Order 102 exists: " << orderIndex.count(102) << "\n";

    return 0;
}