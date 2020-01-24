#ifndef __VM_H__
#define __VM_H__

#include "CommandSet.h"
#include "Exception.h"
#include "Types.h"

typedef struct {
    PObject stack[1000];
    int sp;
    int maxSize;
} Stack;

Int64 InstructionPointer = 0;

// Basic stack operations

PObject PopStack(Stack* stack) {
    if (stack->sp == 0)
        Throw(InvalidPointerException);
    PObject result = stack->stack[stack->sp - 1];
    stack->sp--;
    return result;
}

void PushStack(Stack* stack, PObject value) {
    if (stack->sp == stack->maxSize)
        Throw(StackOverflowException);
    stack->stack[stack->sp] = value;
    stack->sp++;
}

PObject Top(Stack* stack) {
    if (stack->sp == 0)
        Throw(InvalidPointerException);
    return stack->stack[stack->sp - 1];
}

// Arithmetic operations

void Arith(Stack* stack, Instructions instruction, PObject* instant) {
    PObject op2 = instant == 0 ? PopStack(stack) : *instant;
    if (op2.tag == 4)
        Throw(TypeMismatchException);
    PObject push_value;
    // If the instruction is not, we should do it instantly
    if (instruction == OP_NOT || instruction == OP_LNOT) {
        if (instruction == OP_NOT && op2.tag != 3) {
            Int64 result = ~GetInt64(op2);
            push_value.tag = op2.tag;
            push_value.v = RetriveInt64(result, push_value.tag);
        } else if (instruction == OP_LNOT && op2.tag != 3) {
            Int64 result = !GetInt64(op2);
            push_value.tag = op2.tag;
            push_value.v = RetriveInt64(result, push_value.tag);
        } else
            Throw(TypeMismatchException);
    } else {
        PObject op1 = PopStack(stack);
        push_value.tag = max(op1.tag, op2.tag);
        // To decimal operations, then boolean is not allowed in such operation
        if (op1.tag == 1 || op2.tag == 1)
            Throw(TypeMismatchException);
        if (instruction <= OP_DIV && instruction >= OP_ADD) {
            Decimal result;
            switch (instruction) {
                case OP_ADD:
                    result = GetDecimal(op1) + GetDecimal(op2);
                    break;
                case OP_SUB:
                    result = GetDecimal(op1) - GetDecimal(op2);
                    break;
                case OP_MUL:
                    result = GetDecimal(op1) * GetDecimal(op2);
                    break;
                case OP_DIV:
                    if (GetDecimal(op2) == 0)
                        Throw(DivideByZeroException);
                    result = GetDecimal(op1) / GetDecimal(op2);
                    break;
            }
            push_value.v = RetriveDecimal(result, push_value.tag);
        } else {
            // To int64 operaions, then decimal is not allowed in such operation
            if (op1.tag == 3 || op2.tag == 3)
                Throw(TypeMismatchException);
            Int64 result;
            switch (instruction) {
                case OP_AND:
                    result = GetInt64(op1) & GetInt64(op2);
                    break;
                case OP_OR:
                    result = GetInt64(op1) | GetInt64(op2);
                    break;
                case OP_NOR:
                    result = GetInt64(op1) ^ GetInt64(op2);
                    break;
                case OP_SLEFT:
                    result = GetInt64(op1) << GetInt64(op2);
                    break;
                case OP_SRIGHT:
                    result = GetInt64(op1) >> GetInt64(op2);
                    break;
                case OP_LAND:
                    result = GetInt64(op1) && GetInt64(op2);
                    break;
                case OP_LOR:
                    result = GetInt64(op1) || GetInt64(op2);
                    break;
            }
            push_value.v = RetriveInt64(result, push_value.tag);
        }
    }
    PushStack(stack, push_value);
}

// Control Flow
void Jump(Stack* stack, Int16 value, Bool relateQ);
inline void Jump(Stack* stack, Int16 value, Bool relateQ) {
    if (relateQ == true)
        InstructionPointer += value;
    else
        InstructionPointer == value;
}

void JumpTrue(Stack* stack, Int16 value, Bool relateQ) {
    if (Top(stack).tag == 1 && Top(stack).v.boolean == true)
        Jump(stack, value, relateQ);
    PopStack(stack);
}

void JumpFalse(Stack* stack, Int16 value, Bool relateQ) {
    if (Top(stack).tag == 1 && Top(stack).v.boolean == false)
        Jump(stack, value, relateQ);
    PopStack(stack);
}

void JumpEqual(Stack* stack, Int16 value, Bool relateQ) {
    PObject ob2 = PopStack(stack);
    PObject ob1 = PopStack(stack);
    if (ob2.tag == ob1.tag && ob2.v.interger == ob1.v.interger)
        Jump(stack, value, relateQ);
}

void JumpNotEqual(Stack* stack, Int16 value, Bool relateQ) {
    PObject ob2 = PopStack(stack);
    PObject ob1 = PopStack(stack);
    if (!(ob2.tag == ob1.tag && ob2.v.interger == ob1.v.interger))
        Jump(stack, value, relateQ);
}
void JumpBigger(Stack* stack, Int16 value, Bool relateQ) {
    PObject ob2 = PopStack(stack);
    PObject ob1 = PopStack(stack);
    if (GetDecimal(ob2) < GetDecimal(ob1))
        Jump(stack, value, relateQ);
}
void JumpLesser(Stack* stack, Int16 value, Bool relateQ) {
    PObject ob2 = PopStack(stack);
    PObject ob1 = PopStack(stack);
    if (GetDecimal(ob2) > GetDecimal(ob1))
        Jump(stack, value, relateQ);
}
void JumpBiggerEqual(Stack* stack, Int16 value, Bool relateQ) {
    PObject ob2 = PopStack(stack);
    PObject ob1 = PopStack(stack);
    if (GetDecimal(ob2) <= GetDecimal(ob1))
        Jump(stack, value, relateQ);
}
void JumpLesserEqual(Stack* stack, Int16 value, Bool relateQ) {
    PObject ob2 = PopStack(stack);
    PObject ob1 = PopStack(stack);
    if (GetDecimal(ob2) >= GetDecimal(ob1))
        Jump(stack, value, relateQ);
}

#endif