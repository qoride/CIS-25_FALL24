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

    bool LeapYear(){
        return ((year%4==0&&year%100!=100)||(year%400==0));
    }

    int DaysInMonth(){
        return 30 + (month==2)?((LeapYear())?-1:-2):(month%2);
    }

    int Decode(){
        Date days;
        days.day = day;
        days.month = month;
        days.year = year;

        while(days.month > 2){
            days.day += days.DaysInMonth();
            days.month--;
        }

        while(days.year > 1582){
            days.day += (days.LeapYear())?366:365;
            days.year--;
        }

        return days.day;
    }

    int DaysDifference(Date otherDate){
        return Decode()-otherDate.Decode();
    }

    Date Encode(int days){
        Date newDate;
        newDate.year = 1582;
        newDate.month = 1;
        newDate.day = 1;
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
    float feeDaily;
};

struct Person{
    std::string name;
    Date borrowDate;
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
        if(borrowers.size() == copies)return "No more copies left.";
        borrowers.push_back(customer);
        customer.borrowDate = date;
        return customer.name + " has borrowed " + title + " on " + date.Print() + ".\nPlease return it by " + std::to_string(policy.rentDays) + " days.";
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

    std::string ListBorrowers(){
        std::string list = "";
        for(Person p : borrowers){
            list += "\n" + p.name + ", " + p.borrowDate.Print();
        }
    }
};

#endif /* STRUCT_HPP_ */
