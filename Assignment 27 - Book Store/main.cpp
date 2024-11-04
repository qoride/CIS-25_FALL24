#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include "struct.hpp"

using namespace std;

enum Option{
    addBook,
    removeBook,
    borrowBook,
    returnBook,
    infoBook,
    checkBorrowers,
    listCatalogue,
    exitProgram,
    invalidOption,
};

string OptionToString(Option option){
    switch(option){
        case addBook:           return "add";
        case removeBook:        return "remove";
        case borrowBook:        return "borrow";
        case returnBook:        return "return";
        case infoBook:          return "info";
        case checkBorrowers:    return "check";
        case listCatalogue:     return "list";
        case exitProgram:       return "exit";
        case invalidOption:     return "invalid";
    }
}

map<string, Option> menuMap = {
    {"add"      ,   addBook},
    {"remove"   ,   removeBook},
    {"borrow"   ,   borrowBook},
    {"return"   ,   returnBook},
    {"info"     ,   infoBook},
    {"check"    ,   checkBorrowers},
    {"list"     ,   listCatalogue},
    {"exit"     ,   exitProgram},
    {"invalid"  ,   invalidOption},
};

Option parseIn(string s){
    auto it = menuMap.find(s);
    return (it == menuMap.end())?invalidOption:it->second;
}

int main(){
    string input;
    vector<Book> catalogue;

    do{
        cout << endl << "┌─────────────────────────────────────────────────┐" << endl
        <<              "│ Welcome to the C++ Library!     //version 1.0.1 │" << endl
        <<              "├─────────────────────────────────────────────────┤" << endl
        <<              "│ Options:                                        │" << endl
        <<              "│ \"add\" - Add a book to the catalogue.            │" << endl
        <<              "│ \"remove\" - Remove a book from the catalogue.    │" << endl
        <<              "│ \"borrow\" - Let a customer checkout a book.      │" << endl
        <<              "│ \"return\" - Let a customer return a book.        │" << endl
        <<              "│ \"info\" - Check a book's information.            │" << endl
        <<              "│ \"list\" - Open the catalogue.                    │" << endl
        <<              "│ \"check\" - Check who is borrowing a book.        │" << endl
        <<              "├─────────────────────────────────────────────────┤" << endl
        <<              "│ \"exit\" - Exit the program.                      │" << endl
        <<              "└─────────────────────────────────────────────────┘" << endl
        <<              "Please select an option: ";
        cin >> input;
        switch(parseIn(input)){
            case addBook:

                break;

            case removeBook:

                break;

            case borrowBook:

                break;

            case returnBook:

                break;

            case infoBook:

                break;

            case listCatalogue:

                break;

            case checkBorrowers:

                break;
            
            case exitProgram:
                cout << "\nThank you, have a good day!" << endl;
                break;

            case invalidOption:
                cout << "\nERROR: Option not recognized, please try again." << endl;
                break;
        }
    }while(parseIn(input) != exitProgram);

    return 0;
}
