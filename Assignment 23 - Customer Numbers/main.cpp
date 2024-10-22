#include <iostream>
#include <limits>

using namespace std;

bool validateCustomer(string s){
    if(s.size()!=6)return false;
    for(int i = 0; i < s.size(); i++){
        if(i<2&&isdigit(s[i]))return false;
        if(i>1&&!isdigit(s[i]))return false;
    }
    return true;
}

int main(){
    string input;

    cout << "Enter your customer number: ";
    getline(cin,input);

    cout << "\nValidating..." << endl;

    cout << "\nYour customer number is " << ((validateCustomer(input) == true)?"valid.":"not valid.") << endl;

    return 0;
}
