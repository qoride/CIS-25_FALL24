#include <iostream>
#include <limits>
#include <vector>
#include "struct.hpp"

using namespace std;

void clearStream(string msg = "");

int main(){
    int val;
    bool pass = false;
    Point p1, p2;
    vector<int*> comps = {&p1.x,&p1.y,&p2.x,&p2.y};

    for(int i = 0; i < 4; i++){
        cout << "\nEnter the " <<((i%2==0)?"x":"y")<<"-coordinate for the " <<((i<2)?"first":"second")<<" point: ";

        while(!pass){
            while(cin >> val){
                *comps[i] = val;
                pass = true;
                break;
            }
            if(cin.fail()){
                clearStream("\nERROR: number was not accepted, try again: ");
            }
        }

        clearStream();
        pass = false;
    }

    cout << "\nPoint 1: " << p1 << endl
    <<"Point 2: " << p2 << endl
    <<"\nEqual?: " <<((p1==p2)?"true":"false")<< endl;

    return 0;
}

void clearStream(string msg){
    cin.clear();
    cout << msg;
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}