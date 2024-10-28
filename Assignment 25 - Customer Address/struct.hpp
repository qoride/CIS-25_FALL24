#ifndef STRUCT_HPP_
#define STRUCT_HPP_

#include <string>

struct Address{
    std::string street;
    std::string city;
    int zip;
};

struct Customer{
    int ID;
    std::string name;
    std::string email;
    Address address;
};

#endif /* STRUCT_HPP_ */
