#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <string>
#include <ostream>
#include <memory>

namespace prototype::record_kepping {

struct Address {
    std::string city, street;
    int suite;

    Address(const std::string &&city, const std::string &&street, int suite)
        : city {city}, street {street}, suite {suite} {}

    Address(Address const &other)
        : city{other.city}
        , street{other.street}
        , suite{other.suite} {}

    friend std::ostream& operator<<(std::ostream &os, const Address &add) {
        return os << "City: " << add.city << " Street: " << add.street << " Suite: " << add.suite;
    }
};

struct Contact {
    std::string name;
    Address* address;

    Contact(const std::string &&name, Address* address)
        : name {name}, address {address} {}

    Contact(Contact const &o)
        : name {o.name}
        , address { new Address {o.address->city.c_str(),
                    o.address->street.c_str(),
                    o.address->suite} }
    {}

    ~Contact() { delete address; }

    friend std::ostream& operator<<(std::ostream &os, const Contact &con) {
        return os << "Name: " << con.name << " Address: " << *con.address;
    }
};


struct Employee_factory
{
    static Contact main;
    static Contact aux;

    static std::unique_ptr<Contact> NewMainOfficeEmployee(std::string name, int suite) {
        return NewEmployee(name, suite, main);
    }

    static std::unique_ptr<Contact> NewAuxOfficeEmployee(std::string name, int suite) {
        return NewEmployee(name, suite, aux);
    }

private:
    static std::unique_ptr<Contact> NewEmployee(std::string name, int suite, Contact& proto) {
        auto result = std::make_unique<Contact>(proto);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};

Contact Employee_factory::main{ "", new Address{ "123 East Dr", "London", 0 } };
Contact Employee_factory::aux{ "", new Address{ "123B East Dr", "London", 0 } };

void main() {
    //Contact John {"John", new Address {"london", "123 East Dr", 123}}; // grt to delete everyone created
    //Contact Jame = John; // clone
    //Jame.address->street = "124 Dr";
    //Jame.address->suite = 111;
    //std::cout << John << '\n' << Jame << std::endl;

    auto John = Employee_factory::NewAuxOfficeEmployee("John Doe", 123);
    auto Jane = Employee_factory::NewMainOfficeEmployee("Jane Doe", 125);

    std::cout << *John << "\n" << *Jane << "\n"; // note the stars here
}
}

#endif // CONTACT_HPP
