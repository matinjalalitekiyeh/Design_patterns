#include "solid/solid.hpp"
#include "factory/factory.h"
#include "prototype/contacts.hpp"

void solid_opr() {
    solid::single_responsibility::main();
    solid::open_close::main();
    solid::liskov::main();
    solid::interface::main();
    solid::dependencies::main();
}

int main() {
    //solid
    //solid_opr();

    //factory
    //factory::point_factory::main();
    //factory::drink_factory::main();

    //prototype
    prototype::record_kepping::main();

    return 0;
}
