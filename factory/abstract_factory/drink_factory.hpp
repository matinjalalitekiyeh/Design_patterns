#ifndef DRINK_FACTORY_HPP
#define DRINK_FACTORY_HPP

#include <iostream>
#include <memory>
#include <map>
#include <functional>

namespace factory::drink_factory {

struct Hot_drink {
    virtual void prepare(int volume) = 0;
};

struct Tea : Hot_drink {
    void prepare(int volume) override {
        std::cout << "Take tea bag, boil water, pour "
                  << volume << "ml, add some lemon." << std::endl;
    }
};

struct Coffee : Hot_drink {
    void prepare(int volume) override {
        std::cout << "Grind some beans, boil water, pour "
                  << volume << "ml, add cream, enjoy!" << std::endl;
    }
};

struct Hot_drink_factory {
    virtual std::unique_ptr<Hot_drink> make() const = 0;
};

struct Tea_factory : Hot_drink_factory {
    std::unique_ptr<Hot_drink> make() const override {
        return std::make_unique<Tea>();
    }
};

struct Coffee_factory : Hot_drink_factory {
    std::unique_ptr<Hot_drink> make() const override {
        return std::make_unique<Coffee>();
    }
};

struct Drink_factory_map {
    std::map<std::string, std::unique_ptr<Hot_drink_factory>> drinks;
    Drink_factory_map() {
        drinks["Tea"] = std::make_unique<Tea_factory>();
        drinks["Coffee"] = std::make_unique<Coffee_factory>();
    }

    std::unique_ptr<Hot_drink> drink(const std::string &&name) {
        auto drink = drinks[name]->make();
        drink->prepare(150); // use functional to prepare it.
        return drink;
    }
};

struct Drink_factory_func {
    std::map<std::string, std::function<std::unique_ptr<Hot_drink>()>> drinks;
    Drink_factory_func() {
        drinks["Tea"] = [] {
            auto drink =std::make_unique<Tea>();
            drink->prepare(150);
            return drink;
        };
        drinks["Coffee"] = [] {
            auto drink =std::make_unique<Coffee>();
            drink->prepare(200);
            return drink;
        };
    }

    void drink(const std::string &&name) {
        drinks[name]();
    }
};


void main() {
    //Drink_factory_map dfm;
    //dfm.drink("Tea");

    Drink_factory_func dff;
    dff.drink("Tea");
    dff.drink("Coffee");

}
}

#endif // DRINK_FACTORY_HPP
