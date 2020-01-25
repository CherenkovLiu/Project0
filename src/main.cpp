#include <iostream>
#include <string>
#include "Vm.hpp"

int main() {
    Stack<std::string> callStack;
    try {
        GetTag(callStack);
        callStack.Pop();
    } catch (Exception* exp) {
        std::cout << exp->ToString() << std::endl;;
    }

    int a = 2;
    double b = 3;
    auto c = a + b;

    std::cout << (typeid(c) == typeid(double)) << std::endl;
}