#ifndef __COMMANDSET_H__
#define __COMMANDSET_H__
// This is the basic command set of the virtual machine

// Programming Code -> Virtual Machine Code -> Assembly Code -> Machine Code
typedef enum {
    // [> Arithmetic Operations <]

    // Basic operations
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,

    OP_AND,
    OP_OR,
    OP_NOR,
    OP_NOT,

    OP_SLEFT,
    OP_SRIGHT,

    // Logic operations
    OP_LAND,
    OP_LOR,
    OP_LNOT,

    // [> Control Flow <]
    OP_JMP,

    OP_JT,
    OP_JF,

    OP_JEQ,
    OP_JNE,

    OP_JBT,
    OP_JLT,
    OP_JBE,
    OP_JLE,

    // [> Stack Operation <]
    OP_PUSH,
    OP_POP,
    OP_TOP
} Instructions;

#endif