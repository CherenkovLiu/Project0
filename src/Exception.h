#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    // Define your own exceptions here
    InvalidPointerException,
    StackOverflowException,
    TypeMismatchException,
    DivideByZeroException
} Exceptions;

void Throw(Exceptions exception) {
    fprintf(stderr, "Exception occured, exception code: %d", exception);
    exit(1);
}

#endif