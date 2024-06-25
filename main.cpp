#include "solid/solid.hpp"

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

    return 0;
}
