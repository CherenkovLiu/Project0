#ifndef __PVM_H__
#define __PVM_H__

/**
 * @brief: This is the virtual machine for project 0, a stack machine.
 * @note:  Since I follow the Java and C# style to write a program, class and 
 *         their implements would be putting together
 * @date:  Last modified on 2020/1/25
 */

#include <cstdlib>
#include "common.hpp"

/* Data structure */

union p_value {
    bool gc_tag;  // For garbage collection, if there is one
    bool p_bool;
    int64_t p_integer;
    double p_number;
    string* p_string;  // a string pointer
};

struct p_object {
    int8_t tag;  // 0 => bool, 1 => integer, 2 => double, 3 => string
    p_value value;
};

bool operator==(p_object p1, p_object p2) {
    if (p1.tag == p2.tag) {
        switch (p1.tag) {
            case 0:
                return p1.value.p_bool == p2.value.p_bool;
            case 1:
                return p1.value.p_integer == p2.value.p_integer;
            case 2:
                return p1.value.p_number == p2.value.p_number;
            case 3:
                return (*p1.value.p_string) == (*p2.value.p_string);
            default:
                break;
        }
    }
    return false;
}

bool operator!=(p_object p1, p_object p2) {
    return !(p1 == p2);
}

inline int64_t cast_int64(p_value v, int8_t tag) {
    switch (tag) {
        case 0:
            return v.p_bool;
        case 1:
            return v.p_integer;
        case 2:
            return v.p_number;
        case 3:
            return atoi((*v.p_string).c_str());
        default:
            throw new exception("unrecognized tag", "in casting p_value to int64_t, tag " + std::to_string(tag));
    }
}

inline double cast_number(p_value v, int8_t tag) {
    switch (tag) {
        case 0:
            return v.p_bool;
        case 1:
            return v.p_integer;
        case 2:
            return v.p_number;
        case 3:
            return atof((*v.p_string).c_str());
        default:
            throw new exception("unrecognized tag", "in casting p_value to number, tag " + std::to_string(tag));
    }
}

template <typename T>
p_value cast_pvalue(T v, int8_t tag) {
    p_value result;
    switch (tag) {
        case 0:
            result.p_bool = (bool)v;
            break;
        case 1:
            result.p_integer = (int64_t)v;
            break;
        case 2:
            result.p_number = (double)v;
            break;
        case 3:
            result.p_string = new string(std::to_string(v));
            break;
        default:
            throw new exception("unrecognized tag", "in casting value to p_value, tag " + std::to_string(tag));
    }
    return result;
}

string p_value_tostring(p_value p, int8_t tag) {
    switch (tag) {
        case 0:
            return std::to_string(p.p_bool);
        case 1:
            return std::to_string(p.p_integer);
        case 2:
            return std::to_string(p.p_number);
        case 3:
            return *p.p_string;
        default:
            throw new exception("unrecognized tag", "in casting p_value to string, tag " + std::to_string(tag));
    }
}

/* Instruction Set */

enum instruction {
    OP_PUSH,    // push stack
    OP_POP,     // pop stack
    OP_TOP,     // the top of stack
    OP_ADD,     // A B +
    OP_SUB,     // A B -
    OP_MUL,     // A B *
    OP_DIV,     // A B /
    OP_AND,     // A B &
    OP_OR,      // A B |
    OP_NOR,     // A B ^
    OP_NOT,     // A ~
    OP_LAND,    // A B &&
    OP_LOR,     // A B ||
    OP_LNOT,    // A !
    OP_SLEFT,   // A B <<
    OP_SRIGHT,  // A B >>
    OP_JMP,     // jump, relative index or absolute
    OP_JIT,     // jump A == T
    OP_JIF,     // jump A == F
    OP_JEQ,     // jump A == B
    OP_JNE,     // jump A != B
    OP_JBT,     // jump A > B
    OP_JLT,     // jump A < B
    OP_JBE,     // jump A >= B
    OP_JLE,     // jump A <= B
    OP_STRLEN,  // get a.length
    OP_CONCAT,  // concat a and b
    OP_STRCMP   // compare a and b, push result c, a number
};

#include <vector>

// Since some properties might be useful, I would make getter/setter for debug
class pvm {
private:
    int64_t sp;                  // stack pointer
    int64_t ip;                  // instruction pointer
    std::vector<p_object> opnd;  // operand stack

    string stack_to_string() {
        string result = "";
        std::vector<p_object>::iterator it = opnd.begin();
        for (; it != opnd.end(); ++it)
            result += "     " + p_value_tostring((*it).value, (*it).tag) + " <= tag : " + std::to_string((*it).tag) + "\n";
        result.pop_back();
        return result;
    }

    void push(const p_object& value) {
        opnd.push_back(value);
        sp++;
    }

    p_object pop() {
        if (opnd.empty())
            throw new exception("opnd emptied", "pvm running command pop, with ip " + std::to_string(ip));
        sp--;
        p_object tmp = opnd.back();
        opnd.pop_back();
        return tmp;
    }

    p_object& top() { return opnd.back(); }

    void arith(instruction op, p_object* instant = 0) {
        p_object obj2 = instant == 0 ? pop() : *instant;  // You could use a instant number to do operation
        if (obj2.tag == 3)
            throw new exception("type error", "string in arithmetic operation, expected number");
        p_object result;
        // One number operation
        if ((op == OP_NOT || op == OP_LNOT)) {
            // check the type
            if (obj2.tag == 2)
                throw new exception("type error", "number in not/lnot operation");
            result.tag = obj2.tag;
            if (op == OP_NOT)
                result.value = cast_pvalue(~cast_int64(obj2.value, obj2.tag), obj2.tag);
            else
                result.value = cast_pvalue(!cast_int64(obj2.value, obj2.tag), obj2.tag);
        } else {
            p_object obj1 = pop();
            result.tag = std::max(obj1.tag, obj2.tag);  // This is the upcast
            if (OP_ADD <= op && op <= OP_DIV) {
                // cast to double to do the operation
                if (obj1.tag == 0 || obj2.tag == 0)
                    throw new exception("type error", "bool in +-*/ operation");
                double num1 = cast_number(obj1.value, obj1.tag), num2 = cast_number(obj2.value, obj2.tag);
                double re;
                switch (op) {
                    case OP_ADD:
                        re = num1 + num2;
                        break;
                    case OP_SUB:
                        re = num1 - num2;
                        break;
                    case OP_MUL:
                        re = num1 * num2;
                        break;
                    case OP_DIV:
                        if (num2 == 0.0)
                            throw new exception("divide by zero", "in doing division");
                        re = num1 / num2;
                        break;
                }
                result.value = cast_pvalue(re, result.tag);
            } else {
                // cast to int64_t to do the operation
                if (obj1.tag == 2 || obj2.tag == 2)
                    throw new exception("type error", "number in logic operation");
                int64_t num1 = cast_int64(obj1.value, obj1.tag), num2 = cast_int64(obj2.value, obj2.tag);
                int64_t re;
                switch (op) {
                    case OP_AND:
                        re = num1 & num2;
                        break;
                    case OP_OR:
                        re = num1 | num2;
                        break;
                    case OP_NOR:
                        re = num1 ^ num2;
                        break;
                    case OP_LAND:
                        re = num1 && num2;
                        break;
                    case OP_LOR:
                        re = num1 || num2;
                        break;
                    case OP_SLEFT:
                        re = num1 << num2;
                        break;
                    case OP_SRIGHT:
                        re = num1 >> num2;
                        break;
                }
                result.value = cast_pvalue(re, result.tag);
            }
        }
        push(result);
    }

    inline void jump(int64_t idx, bool rel) {
        if (rel)
            ip += idx;
        else
            ip = idx;
    }

    void jump_t(int64_t idx, bool rel) {
        if (top().tag == 0 && top().value.p_bool)
            jump(idx, rel);
        pop();
    }

    void jump_f(int64_t idx, bool rel) {
        if (top().tag == 0 && !top().value.p_bool)
            jump(idx, rel);
        pop();
    }

    void jump_eq(int64_t idx, bool rel) {
        p_object obj1 = pop(), obj2 = pop();
        if (obj1 == obj2)
            jump(idx, rel);
    }

    void jump_neq(int64_t idx, bool rel) {
        p_object obj1 = pop(), obj2 = pop();
        if (obj1 != obj2)
            jump(idx, rel);
    }

public:
    /**
     * @brief initialization, ip to 0, sp to 0, return value 0 is pushed into the stack
     */
    pvm() {
        sp = ip = 0;
        opnd.clear();
        p_object tmp;
        tmp.tag = 1;
        tmp.value.p_integer = 0;
        opnd.push_back(tmp);
    }

    ~pvm() { opnd.~vector(); }

    /**
     * @brief reset the state of the virtual machine
     * @note  empty the opnd and set ip to 0 again
     */
    void reset() {
        ip = 0;
        opnd.clear();
    }

    /**
     * @brief  get the instruction pointer
     * @return int64_t
     */
    int64_t get_ip() { return this->ip; }

    /**
     * @brief  get the stack pointer, perhaps useless
     * @return int64_t
     */
    int64_t get_sp() { return this->sp; }

    /**
     * @brief print out the whole stack into string
     * @note including stack pointer and instruction pointer
     */
    string get_state() {
        string result = "Stack pointer : " + std::to_string(sp) + "\nInstruction pointer : " + std::to_string(ip) + "\n[> Bottom <]\n" + stack_to_string();
        result += "\n[> Top <]\n\n";
        return result;
    }

    void push_stack(p_object obj) {
        push(obj);
    }

    void pop_stack() {
        pop();
    }

    void arith_operation(instruction ins) {
        arith(ins);
    }
};
#endif