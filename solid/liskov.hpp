#ifndef LISKOV_HPP
#define LISKOV_HPP

#include <iostream>

// Objects in a program should be replaceable with instances of their subtypes
// w/o altering the correctness of the program

namespace solid::liskov {
class Rectangle {
protected:
    int width, height;
public:
    Rectangle(const int width, const int height)
        : width{width}, height{height} { }

    int get_width() const { return width; }
    virtual void set_width(const int width) { this->width = width; }

    int get_height() const { return height; }
    virtual void set_height(const int height) { this->height = height; }

    int area() const { return width * height; }
};

class Square : public Rectangle {
public:
    Square(int size): Rectangle(size,size) {}
    void set_width(const int width) override {
        this->width = height = width;
    }
    void set_height(const int height) override {
        this->height = width = height;
    }
};

struct RectangleFactory {
    static Rectangle create_rectangle(int w, int h) { return Rectangle {w, h}; }
    static Rectangle create_square(int size) { return Rectangle {size, size}; }
};

void process(Rectangle& r)
{
    int w = r.get_width();
    r.set_height(10);

    std::cout << "expected area = " << (w * 10)
              << ", got " << r.area() << std::endl;
}

void main() {
//    Rectangle r{ 5,5 };
//    process(r);

//    Square s{ 5 };
//    process(s);

    auto rect = RectangleFactory::create_rectangle(5,5);
    process(rect);

    auto sqr = RectangleFactory::create_square(5);
    process(sqr);
}


}

#endif // LISKOV_HPP
