#ifndef STRUCT_HPP_
#define STRUCT_HPP_

#include <string>
#include <vector>
#include <algorithm>

const std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

struct Date{
    int year;
    int month;
    int day;
    std::string Print(){
        return months[month-1] + " " + std::to_string(day) + ", " + std::to_string(year);
    }

    friend std::ostream& operator <<(std::ostream& out, const Date &d){
        out << months[d.month-1] << " " << d.day << ", " << d.year;
        return out;
    }

    bool LeapYear(){
        return ((year%4==0&&year%100!=100)||(year%400==0));
    }

    int DaysInMonth(){
        return 30 + ((month==2)?((LeapYear())?-1:-2):(month%2));
    }

    int Decode(){
        Date numDays;
        numDays.day = day;
        numDays.month = month;
        numDays.year = year;

        while(numDays.year > 1582){
            while(numDays.month > 0){
                numDays.day += numDays.DaysInMonth();
                numDays.month--;
            }
            numDays.year--;
            numDays.month = 12;
        }

        return numDays.day;
    }

    int DaysDifference(Date otherDate){
        return Decode()-otherDate.Decode();
    }

    Date Encode(int days){
        Date newDate;
        newDate.year = 1582;
        newDate.month = 12;
        newDate.day = days-1;

        while(newDate.day > newDate.DaysInMonth()+1){
            newDate.day -= newDate.DaysInMonth();
            newDate.month++;
            if(newDate.month > 12){
                newDate.year++;
                newDate.month -= 12;
            }
        }

        return newDate;
    }

    Date operator +(int days){
        Date newDate;
        newDate.day = day + days;
        newDate.month = month;
        newDate.year = year;

        while(newDate.day > newDate.DaysInMonth()+1){
            newDate.day -= newDate.DaysInMonth();
            newDate.month++;
            if(newDate.month > 12){
                newDate.year++;
                newDate.month -= 12;
            }
        }

        return newDate;
    }

    Date operator -(int days){
        Date newDate;
        newDate.day = day + days;
        newDate.month = month;
        newDate.year = year;

        int monthDays = newDate.DaysInMonth();

        while(newDate.day > monthDays){
            newDate.day -= monthDays;
            newDate.month++;
            monthDays = newDate.DaysInMonth();
            if(newDate.month > 12){
                newDate.year++;
                newDate.month -= 12;
            }
        }

        return newDate;
    }

    bool operator <(Date otherDate){
        return Decode()<otherDate.Decode();
    }

    bool operator >(Date otherDate){
        return Decode()>otherDate.Decode();
    }
};

struct Policy{
    int rentDays;
    double feeDaily;
};

struct Person{
    std::string name;
    Date borrowDate;

    friend std::ostream& operator <<(std::ostream& out, const Person &p){
        out << "Full name: " << p.name << std::endl;
        if(p.borrowDate.year != 0)out << "Borrow date: " << p.borrowDate << std::endl;
        return out;
    }
};

struct Book{
    int ISBN;
    std::string title;
    Person author;
    std::vector<Person> borrowers;
    int pages;
    int copies;
    Date publishDate;

    std::string CheckOut(Person &customer, Date date, Policy policy){
        borrowers.push_back(customer);
        customer.borrowDate = date;
        return "\n" + customer.name + " has borrowed " + title + " on " + date.Print() + ".\nPlease return it by " + (date+policy.rentDays).Print() + "\n";
    }

    std::string Return(Person customer, Date date, Policy policy){
        auto it = std::find_if(borrowers.begin(), borrowers.end(),[&customer](const Person& obj){
            return &obj == &customer;
        });
        if(it != borrowers.end()){
            it = borrowers.erase(it);
        }else{
            return "Could not find borrower.";
        }
        if(date<customer.borrowDate){
            return "We don't accept returns from time travelers.";
        }else{
            int borrowTime = customer.borrowDate.DaysDifference(date);
            if(borrowTime > policy.rentDays){
                return customer.name + " owes $" + std::to_string(policy.feeDaily*(borrowTime-policy.rentDays));
            }
            return title + " has been returned by " + customer.name + " with " + std::to_string(policy.rentDays - borrowTime) + " days remaining.";
        }
    }

    bool operator ==(Book other){
        return ISBN == other.ISBN;
    }

    friend std::ostream& operator <<(std::ostream& out, const Book &b){
        out << "Title: " << b.title << std::endl
        << "Author: " << b.author.name << std::endl
        << "Published: " << b.publishDate << std::endl;

        return out;
    }

    std::string fullInfo(){
        return "Title: " + title
        + "\nISBN: " + std::to_string(ISBN)
        + "\nAuthor: " + author.name
        + "\nPublished: " + publishDate.Print()
        + "\nPages: " + std::to_string(pages)
        + "\nCopies: " + std::to_string(copies-borrowers.size()) + " available out of " + std::to_string(copies) + " copies\n";
    }
};

#endif /* STRUCT_HPP_ */
