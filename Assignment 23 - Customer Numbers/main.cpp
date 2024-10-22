#include <iostream>
#include <limits>

using namespace std;

int main(){
    bool accepted;
    int val;
    string input;
    Customer user;

    cout << "Enter your ID: ";
    user.ID = -1;

    while(user.ID == -1){
        while(cin >> val){
            if(cin.good()){
                user.ID = val;
                break;
            }
        }
        if(cin.fail()){
            cin.clear();
            cout << "\nERROR: ID was not accepted, try again: ";
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cin.clear();
        }
    }

    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cin.clear();
    return 0;
}
