#include <stdio.h>
#include "Vm.h"
#include 

void PrintStack(Stack* stack) {
    printf("Stack pointer: %d\n", stack->sp);
    printf("=================================================\n");
    for (int i = 0; i < stack->sp; ++i) {
        PObject tmp = stack->stack[i];
        if (tmp.tag == 1)
            printf("Boolean value : %d at %d\n", tmp.v.boolean, i);
        else if (tmp.tag == 2)
            printf("Int64 value : %d at %d\n", tmp.v.interger, i);
        else if (tmp.tag == 3)
            printf("Decimal value : %f at %d\n", tmp.v.decimal, i);
    }
    printf("=================================================\n");
    printf("\n");
}

int main() {
    Stack callStack;
    callStack.sp = 0;
    callStack.maxSize = 1000;

    PObject obj1;
    obj1.tag = 2;
    obj1.v.interger = 1000;

    PObject obj2;
    obj2.tag = 3;
    obj2.v.decimal = 100.2;

    PushStack(&callStack, obj1);
    PrintStack(&callStack);

    PushStack(&callStack, obj2);
    PrintStack(&callStack);

    Arith(&callStack, OP_ADD, 0);
    PrintStack(&callStack);

    PushStack(&callStack, obj1);
    PrintStack(&callStack);

    PushStack(&callStack, obj2);
    PrintStack(&callStack);

    Arith(&callStack, OP_SUB, 0);
    PrintStack(&callStack);

    return 0;
}