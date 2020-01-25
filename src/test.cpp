#include <iostream>
#include "common.hpp"
#include "pvm.hpp"

p_object generate_int64(int64_t value) {
    p_object tmp;
    tmp.tag = 1;
    tmp.value.p_integer = value;
    return tmp;
}

p_object generate_number(double value) {
    p_object tmp;
    tmp.tag = 2;
    tmp.value.p_number = value;
    return tmp;
}

int main() {
    pvm vm;
    std::cout << vm.get_state();
    std::cout << "Safe end" << std::endl;
    return 0;
}