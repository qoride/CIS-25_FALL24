#include <iostream>
#include <limits>
#include "struct.hpp"

using namespace std;

const char delimeter[2] = {'@','.'};
const string domains[6] = {"com","org","gov","net","edu","mil"};

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

    cout << "\nEnter your name: ";

    getline(cin,input);
    user.name = input;

    cout << "\nEnter your e-mail: ";
    user.email = "null";

    while(user.email == "null"){
        while(cin >> input){
            if(cin.good()){
                accepted = false;
                if(input.size()>=7){
                    for(int i = 0; i < input.size(); i++){
                        if(input[i] == delimeter[1]){
                            break;
                        }
                        if(input[i] == delimeter[0]){
                            for(int j = i+1; j < input.size(); j++){
                                if(input[j] == delimeter[0]){
                                    break;
                                }
                                if(input[j] == delimeter[1]){
                                    for(int d = 0; d < 6; d++){
                                        if(input.substr(j+1,input.size())==domains[d]){
                                            accepted = true;
                                            user.email = input;
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                }
                if(accepted == false){
                    cout << "\nERROR: E-mail was not accepted, try again: ";
                }else{
                    break;
                }
            }
        }
        if(cin.fail()){
            cin.clear();
            cout << "\nERROR: E-mail was not accepted, try again: ";
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cin.clear();
        }
        if(accepted == true)break;
    }

    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cin.clear();

    cout << "\nEnter your address's street: ";

    getline(cin,input);
    user.address.street = input;

    cout << "\nEnter your address's city: ";

    getline(cin,input);
    user.address.city = input;

    cout << "\nEnter your address's ZIP code: ";
    user.address.zip = -1;

    while(user.address.zip == -1){
        while(cin >> val){
            if(cin.good()){
                if(val >= 100000 || val < 10000){
                    cout << "\nERROR: ZIP code was not accepted, try again: ";
                }else{
                    user.address.zip = val;
                }
                break;
            }
        }
        if(cin.fail()){
            cin.clear();
            cout << "\nERROR: ZIP code was not accepted, try again: ";
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cin.clear();
        }
        if(user.address.zip != -1)break;
    }

    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cin.clear();

    cout << "\n=CUSTOMER="
    << "\nID: " << user.ID
    << "\nName: " << user.name
    << "\nE-mail: " << user.email
    << "\n\n=ADDRESS="
    << "\nStreet: " << user.address.street
    << "\nCity: " << user.address.city
    << "\nZIP code: " << user.address.zip << endl;

    return 0;
}
