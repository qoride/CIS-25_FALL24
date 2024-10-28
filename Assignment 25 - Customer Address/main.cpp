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

    cout << "\nID: " << user.ID
    << "\nName: " << user.name
    << "\nE-mail: " << user.email << endl;

    return 0;
}
