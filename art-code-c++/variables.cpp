#include <iostream>
#include <vector>

using namespace std;

int main(){
   
    vector <string> names;
    string name;
    name = "jeff";
    names.push_back(name);
    
    name = "mahir";
    names.push_back(name);
    cout << "the first name is " << names[0] << endl;
    cout << "the second name is " << names[1] << endl;;
    
}

