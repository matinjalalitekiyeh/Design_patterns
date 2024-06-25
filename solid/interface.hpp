#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <string>

namespace solid::interface {

struct Document { std::string title; };

struct IPrint {
    virtual void print(Document &doc) = 0;
};
struct IScan {
    virtual void scan(Document &doc) = 0;
};
struct IFax {
    virtual void fax(Document &doc) = 0;
};

struct IMachine : IScan, IPrint {};

struct Machine : public IMachine {
    void print(Document &doc) override { std::cout << "Print: " << doc.title << std::endl; }
    void scan(Document &doc) override { std::cout << "Scan: " << doc.title << std::endl; }
};

void main() {
    Document doc {"Document"};
    Machine m;
    m.scan(doc);
    m.print(doc);
}
}

#endif // INTERFACE_HPP
