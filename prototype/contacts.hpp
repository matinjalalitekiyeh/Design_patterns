#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <iostream>
#include <string>
#include <ostream>

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

void main() {
    Contact John {"John", new Address {"london", "123 Dr", 123}}; // grt to delete everyone created
    Contact Jame = John; // clone

    Jame.address->street = "124 Dr";
    Jame.address->suite = 111;

    std::cout << John << '\n' << Jame << std::endl;
}
}

#endif // CONTACT_HPP
