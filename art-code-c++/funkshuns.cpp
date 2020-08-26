#include <iostream>
#include <vector>
using namespace std;

float calculateTotalWeight(int numPeeps, float weight); // this is the function prototype

vector <string> names;

int main(){
   int numOfPeople;
   float weightOfStuff;

   weightOfStuff = 3.7;

   cout << "how many people are coming to the BBQ?" << endl;
   cin >> numOfPeople;
   for (int i=0; i < numOfPeople; i++){
       string newName;
       cin >> newName;
       names.push_back(newName);
    }

   for (int i =0; i < numOfPeople; i++){
       cout << "person " << i << " is coming to the BBQ" << endl;
       cout << "their name is " << names[i] << endl;
    }   
 cout << "total weight is " <<  calculateTotalWeight(numOfPeople, weightOfStuff) << "kg" << endl;
}

float calculateTotalWeight(int numPeeps, float weight){
        float totalWeight;
        totalWeight = numPeeps * weight;
        return totalWeight;
}

