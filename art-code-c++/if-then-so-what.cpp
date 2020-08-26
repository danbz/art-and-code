#include <iostream>

using namespace std;

int main(){
   int numOfPeople;

   cout << "how many people are coming to the BBQ?" << endl;
   cin >> numOfPeople;
    
    if (numOfPeople == 0){
        cout << "watch tv instead!" << endl;
    } else {
        cout << "prepare for an awesome BBQ" << endl;
    }
    
}

