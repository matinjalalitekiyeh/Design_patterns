#ifndef OPEN_CLOSE_HPP
#define OPEN_CLOSE_HPP

#include <iostream>
#include <string>
#include <vector>

namespace solid::open_close {

enum class Color { red, blue, green };
enum class Size { small, medium, large };

struct Product {
    std::string name;
    Color color;
    Size size;
};

template<typename T>
struct Specification {
    virtual bool is_satisfied(T* item) = 0;
};

template<typename T>
struct Filter {
    virtual std::vector<T*> filter(std::vector<T*> &items,
                                   Specification<T> &spec) = 0;
};

struct Product_filter
        : Filter<Product> {
    std::vector<Product*> filter(std::vector<Product*> &items,
                                 Specification<Product> &spec) override {
        std::vector<Product*> result;
        for (auto &item : items)
            if (spec.is_satisfied(item))
                result.push_back(item);

        return result;
    }
};

struct by_color : Specification<Product> {
    Color color;
    by_color(Color color)
        : color {color} {}
    bool is_satisfied(Product *item) {
        return color == item->color;
    }
};

struct by_size : Specification<Product> {
    Size size;
    by_size(Size size)
        : size {size} {}
    bool is_satisfied(Product *item) {
        return size == item->size;
    }
};

template<typename T>
struct And_specification : Specification<T> {
    Specification<T> &first;
    Specification<T> &second;
    And_specification(Specification<T> &first, Specification<T> &second)
        : first(first), second(second) {/*Nill*/}

    bool is_satisfied(Product *item) override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

void main() {
    Product apple {"Apple", Color::green, Size::small};
    Product tree  {"Tree",  Color::green, Size::large};
    Product house {"House", Color::blue,  Size::large};

    std::vector<Product*> items {&apple, &tree, &house};

    by_color green_spec(Color::green);
    by_size small_spec(Size::small);
    And_specification<Product> and_spec(green_spec, small_spec);

    Product_filter pf;
    const auto green_and_small_things = pf.filter(items, and_spec);
    for (const auto &o : green_and_small_things)
        std::cout << o->name << '\n';
}
}

#endif // OPEN_CLOSE_HPP
