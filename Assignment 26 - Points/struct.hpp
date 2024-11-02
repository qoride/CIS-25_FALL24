#ifndef STRUCT_HPP_
#define STRUCT_HPP_

#include <ostream>

struct Point{
    int x;
    int y;

    bool operator ==(Point other){
        return x == other.x && y == other.y;
    }

    friend std::ostream& operator <<(std::ostream& out, const Point &p){
        out << "(" << std::to_string(p.x) << ", " << std::to_string(p.y) << ")";
        return out;
    }
};

#endif /* STRUCT_HPP_ */