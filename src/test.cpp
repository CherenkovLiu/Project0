#include <iostream>
#include "common.hpp"
#include "pvm.hpp"
#include "lexer.hpp"

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
    /*
    pvm vm;
    std::cout << vm.get_state();

    p_object integer_2 = generate_int64(2);
    p_object double_3 = generate_number(3.5);

    vm.push_stack(integer_2);
    std::cout << vm.get_state();

    vm.push_stack(double_3);
    std::cout << vm.get_state();

    vm.arith_operation(OP_ADD);
    std::cout << vm.get_state();
    */

    lexer lex("3#hello world#3");
    lex.print_chunk();

    lex.next_token();
    lex.print_chunk();

    lex.next_token();
    lex.print_chunk();

    lex.next_token();
    return 0;
}