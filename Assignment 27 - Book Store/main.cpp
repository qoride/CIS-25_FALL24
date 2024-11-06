#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include "struct.hpp"

using namespace std;

enum Option{
    addBook = 0,
    removeBook,
    borrowBook,
    returnBook,
    infoBook,
    checkBorrowers,
    listCatalogue,
    exitProgram,
    cancelOption,
    yesOption,
    noOption,
    invalidOption,
};

const string OptionToString(Option option){
    switch(option){
        case addBook:           return "add";
        case removeBook:        return "remove";
        case borrowBook:        return "borrow";
        case returnBook:        return "return";
        case infoBook:          return "info";
        case checkBorrowers:    return "check";
        case listCatalogue:     return "list";
        case exitProgram:       return "exit";
        case cancelOption:      return "cancel";
        case yesOption:         return "Y";
        case noOption:          return "N";
        case invalidOption:     return "invalid";
    }
}

const map<string, Option> menuMap = {
    {"add"      ,   addBook},
    {"remove"   ,   removeBook},
    {"borrow"   ,   borrowBook},
    {"return"   ,   returnBook},
    {"info"     ,   infoBook},
    {"check"    ,   checkBorrowers},
    {"list"     ,   listCatalogue},
    {"exit"     ,   exitProgram},
    {"cancel"   ,   cancelOption},
    {"Y"        ,   yesOption},
    {"N"        ,   noOption},
    {"invalid"  ,   invalidOption},
};

//PROTOTYPES

int validNum(string msg, vector<int> data, bool (*condition)(vector<int>), string errormsg);
string validStr(string msg, string data, vector<string> accepted, string errormsg);
Book validBook(string &data, vector<Book> list);
void clearStream(string msg = "");
void bufferStream();
Option parseIn(string s);
bool isNum(string s);
int findBook(Book book, vector<Book> list, bool byISBN = false);
struct Book newBook();
bool greaterThan(vector<int> args);
bool lessThan(vector<int> args);
bool clampVal(vector<int> args);
bool noCondition(vector<int> args);
bool valEquals(vector<int> args);

//MAIN

int main(){
    string input;
    int val, temp;
    bool valid = false;
    vector<Book> catalogue;
    Policy policy = {30,1.00};

    Book sample = newBook();
    catalogue.push_back(sample);

    do{
        cout << endl << "┌─────────────────────────────────────────────────┐" << endl
        <<              "│ Welcome to the C++ Library!     //version 1.0.3 │" << endl
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
            case addBook:{
                Book* bookPtr = new Book;
                Book newBook = *bookPtr;

                newBook.ISBN = validNum("\nPlease enter the book's 9-digit ISBN number: ",
                {val,99999999,1000000000}, clampVal, "\nError: ISBN is invalid, please try again: ");

                if(findBook(newBook, catalogue, true) != -1){
                    input = validStr("\nThis book is already in the catalogue, add copies? [Y/N] ",
                    input, {"Y","N"}, "\nERROR: Invalid option, please try again: ");

                    if(input == "N"){
                        cout << "\nReturning to main menu...";
                        delete bookPtr;
                        bookPtr = nullptr;
                        break;
                    }else{
                        temp = validNum("\nEnter the number of copies you're adding: ",
                        {val, 0}, greaterThan, "\nERROR: Number is invalid, please try again: ");

                        catalogue.at(findBook(newBook, catalogue, true)).copies += temp;
                        cout << "\nAdded " << temp << " copies to " << catalogue.at(findBook(newBook, catalogue, true)).title << endl << endl;
                        delete bookPtr;
                        bookPtr = nullptr;
                        bufferStream();
                        break;
                    }
                }

                clearStream();
                cout << "\nPlease enter the title for the book: ";
                getline(cin, input);
                newBook.title = input;

                cout << "\nPlease enter the name of the book's author: ";
                getline(cin, input);
                newBook.author.name = input;

                newBook.publishDate.year = validNum("\nEnter the year the book was published: ",
                {val, 0}, greaterThan, "\nERROR: Year is invalid, please try again: ");

                newBook.publishDate.month = validNum("\nEnter the month the book was published: ",
                {val, 0, 13}, clampVal, "\nERROR: Month is invalid, please try again: ");

                newBook.publishDate.day = validNum("\nEnter the day the book was published: ",
                {val, 0, newBook.publishDate.DaysInMonth()+1}, clampVal, "\nERROR: Day is invalid, please try again: ");

                newBook.pages = validNum("\nEnter the number of pages in the book: ",
                {val, 0}, greaterThan, "\nERROR: Number is invalid, please try again: ");

                newBook.copies = validNum("\nEnter the number of copies of the book: ",
                {val, 0}, greaterThan, "\nERROR: Number is invalid, please try again: ");

                cout << endl << newBook.fullInfo() << "\nDoes this look good? [Y/N] ";
                do{
                    cin >> input;
                    switch(parseIn(input)){
                        case yesOption:
                            cout << "\nAdded " << newBook.copies << " copies of " << newBook.title << " to the catalogue.\n" << endl;
                            catalogue.push_back(newBook);
                            break;
                        case noOption:
                            cout << "\nReturning to main menu...";
                            break;
                        default:
                            cout << "\nERROR: Invalid input, try again: ";
                            break;
                    }
                }while(parseIn(input) != noOption && parseIn(input) != yesOption);
                delete bookPtr;
                bookPtr = nullptr;
                if(parseIn(input) == yesOption)bufferStream();
                break;}
            
            case removeBook:{

                break;}

            case borrowBook:{

                break;}

            case returnBook:{

                break;}

            case infoBook:{
                Book temp = validBook(input,catalogue);
                if(temp.ISBN != -1)cout << endl << temp.fullInfo();
                bufferStream();
                break;}

            case listCatalogue:{
                cout << "\nNumber of books: " << catalogue.size() << endl << endl;
                for(Book b:catalogue){
                    cout << b << endl;
                }
                bufferStream();
                break;}

            case checkBorrowers:{
                
                break;}
            
            case exitProgram:{
                cout << "\nThank you, have a good day!" << endl;
                break;}

            case invalidOption:{
                cout << "\nERROR: Option not recognized, please try again." << endl;
                break;}
        }
    }while(parseIn(input) != exitProgram);

    return 0;
}

//DEFINITIONS

struct Book newBook(){
    Book book;
    book.ISBN = 0;
    book.title = "none";
    Person auth;
    auth.name = "N/A";
    Date d;
    d.year = 0;
    d.month = 1;
    d.day = 0;
    auth.borrowDate;
    book.author = auth;
    book.borrowers = {};
    book.pages = 0;
    book.copies = 0;
    Date pd;
    pd.year = 0;
    pd.month = 0;
    pd.day = 0;
    book.publishDate = pd;

    return book;
}

int validNum(string msg, vector<int> data, bool (*condition)(vector<int>), string errormsg){
    cout << msg;
    do{
        while(cin >> data.at(0)){
            if(condition(data)){
                return data.at(0);
            }else{
                clearStream(errormsg);
            }
        }
        if(cin.fail())clearStream(errormsg);
    }while(true);
}

string validStr(string msg, string data, vector<string> accepted, string errormsg){
    cout << msg;
    do{
        while(cin >> data){
            for(int i = 0; i < accepted.size(); i++){
                if(data == accepted.at(i)){
                    return data;
                }
            }
            clearStream(errormsg);
        }
        if(cin.fail())clearStream(errormsg);
    }while(true);
}

Book validBook(string &data, vector<Book> list){
    clearStream();
    int duplicates = -1;
    Book* bookPtr = new Book;
    Book bookFinder = *bookPtr;
    cout << "\nEnter the title or ISBN of the book: ";
    getline(cin,data);
    bookFinder.title = data;
    try{
        bookFinder.ISBN = stoi(data);
    }catch (const invalid_argument& e) {
        bookFinder.ISBN = -1;
    } catch (const out_of_range& e) {
        bookFinder.ISBN = -1;
    }
    
    if(!isNum(data)){
        for(Book b:list){
            if(b.title == data)duplicates++;
        }
        if(duplicates > 0){
            cout << "\nERROR: Multiple books with the same title, try entering the ISBN: ";
        }else{
            if(findBook(bookFinder,list) != -1){
                delete bookPtr;
                bookPtr = nullptr;
                return list.at(findBook(bookFinder,list));
            }else{
                cout << "\nERROR: Could not find book by title, try entering the ISBN: ";
            }
        }

        getline(cin,data);
        try{
            bookFinder.ISBN = stoi(data);
        }catch (const invalid_argument& e) {
            bookFinder.ISBN = -1;
        } catch (const out_of_range& e) {
            bookFinder.ISBN = -1;
        }
    }

    if(isNum(data)){
        if(findBook(bookFinder,list,true) != -1){
            delete bookPtr;
            bookPtr = nullptr;
            return list.at(findBook(bookFinder,list,true));
        }else{
            cout << "\nERROR: Book not found.";
        }
    }
    bookFinder.ISBN = -1;
    delete bookPtr;
    bookPtr = nullptr;
    return bookFinder;
}

void clearStream(string msg){
    cin.clear();
    cout << msg;
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

void bufferStream(){
    string s;
    clearStream();
    cout << "Press ENTER to return to main menu.";
    getline(cin,s);
}

Option parseIn(string s){
    auto it = menuMap.find(s);
    return (it == menuMap.end())?invalidOption:it->second;
}

bool isNum(string s){
    for(char c : s){
        if(!isdigit(c))return false;
    }
    return true;
}

bool greaterThan(vector<int> args){
    return args.at(0) > args.at(1);
}

bool lessThan(vector<int> args){
    return args.at(0) < args.at(1);
}

bool clampVal(vector<int> args){
    return args.at(0) > args.at(1) && args.at(0) < args.at(2);
}

bool noCondition(vector<int> args){
    return true;
}

bool valEquals(vector<int> args){
    return args.at(0) == args.at(1);
}

int findBook(Book book, vector<Book> list, bool byISBN){
    if(list.size() == 0)return -1;
    if(byISBN == false){
        for(int i = 0; i < list.size(); i++){
            if(book.title == list.at(i).title)return i;
        }
    }else{
        for(int i = 0; i < list.size(); i++){
            if(book == list.at(i))return i;
        }
    }
    return -1;
}