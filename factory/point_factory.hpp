#ifndef POINT_FACTORY_HPP
#define POINT_FACTORY_HPP

#include <iostream>
#include <ostream>
#include <math.h>

namespace factory::point_factory {

enum class Point_types {Cartisian, Polar};

class Point {
    double x, y;
    Point(double x, double y) : x{x}, y{y} {}
    Point(double x, double y, Point_types type) {
        if (type == Point_types::Cartisian) {
            x = x; y = y;
        }else if(type == Point_types::Polar) {
            x = x*std::cos(y); y = x*std::sin(y);
        }
        //what if...
    }
public:
    struct Point_factory {
        static Point create_cartisian(double x, double y) { return Point {x,y}; }
        static Point create_polar(double x, double y) { return Point {x*std::cos(y),x*std::sin(y)}; }
    };

    friend std::ostream& operator<<(std::ostream &os, const Point &p) {
        return os << "Point: (" << p.x << ',' << p.y << ')';
    }
};

void main() {
    auto cartisian = Point::Point_factory::create_cartisian(2,M_PI);
    auto polar = Point::Point_factory::create_polar(2,M_PI);

    std::cout << cartisian << '\n' << polar << std::endl;
}
}

#endif // POINT_FACTORY_HPP
