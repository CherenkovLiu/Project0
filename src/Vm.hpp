#ifndef __VM_HPP__
#define __VM_HPP__

#include <stack>
#include "Exception.hpp"
#include "Types.hpp"

// A self modified stack onto the stl stack
#pragma region 
template <class T>
class Stack {
private:
    std::stack<T>* _stack;

public:
    Int32 stackPointer;

    Stack() {
        this->stackPointer = -1; // Always point to the top element
        this->_stack = new std::stack<T>();
    };

    ~Stack() {
        delete _stack;
    };

    T Pop() {
        if (!_stack->empty()) {
            stackPointer--;
            T result = _stack->top();
            _stack->pop();
            return result;
        } else
            throw new Exception(InvalidPointerException, 34);
    }

    T Top() {
        return _stack->top();
    }

    void Push(T item) {
        stackPointer++;
        _stack->push(item);
    }

    Bool Empty() {
        return _stack->empty();
    }

    Int32 Size() {
        return _stack->size();
    }
};
#pragma endregion

// The instruction set
enum Instruction {
    OP_PUSH,
    OP_POP,
    OP_TOP,

    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,

    OP_AND,
    OP_OR,
    OP_NOR,
    OP_NOT,

    OP_LAND,
    OP_LOR,
    OP_LNOT,

    OP_JMP,
    OP_JIT,
    OP_JIF,
    OP_JEQ,
    OP_JNE,
    OP_JBT,
    OP_JLT,
    OP_JBE,
    OP_JLE,
};

#endif