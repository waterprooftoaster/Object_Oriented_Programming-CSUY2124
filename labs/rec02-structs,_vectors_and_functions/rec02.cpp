/*
  rec02.cpp
  fall 2024
 Andy Wu
 cw4483
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct Hydrocarbon{
    Hydrocarbon(int num_of_carbon, int num_of_hydrogen)
    : C(num_of_carbon), H(num_of_hydrogen){}
    
    void add_name(const string& new_name){
        
    }
}

int main(){

    vector<string> molecules;
    
    ifstream ifs;
    ifs.open("text.txt");

    if (!ifs){
        cout << "unable to open file" << endl;
    }

    string token;
    while (ifs >> token){
#add
    }

}
