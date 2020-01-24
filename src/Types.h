#ifndef __TYPES_H__
#define __TYPES_H__

/**
 * Three basic type in this programming language, including bool-type, integer,
 * which is locked to long long, and decimal, which is locked to double, in order 
 * to make it easier
 */

#define true 1
#define false 0

#include "Exception.h"

typedef char Bool;
typedef long long int Int64;
typedef double Decimal;
typedef int Int32;
typedef short Int16;

typedef union {
    Bool boolean;
    Int64 interger;
    Decimal decimal;
    char* string;    // For string extension, since there's no string operation yet
} Value;

typedef struct {
    int tag;
    Value v;
} PObject;

Decimal GetDecimal(PObject);
inline Decimal GetDecimal(PObject obj) {
    if(obj.tag == 2)
        return (Decimal)obj.v.interger;
    else if(obj.tag == 3)
        return obj.v.decimal;
    else
        Throw(TypeMismatchException);
}

Int64 GetInt64(PObject);
inline Int64 GetInt64(PObject obj) {
    if(obj.tag == 1)
        return (Int64)obj.v.boolean;
    else if(obj.tag == 2)
        return obj.v.interger;
    else if(obj.tag == 3)
        return (Int64)obj.v.decimal;
    else
        Throw(TypeMismatchException);
}

Value RetriveInt64(Int64, int);
inline Value RetriveInt64(Int64 value, int tag) {
    Value result;
    switch(tag) {
        case 1:
            result.boolean = (Bool)value;
            return result;
        case 2:
            result.interger = value;
            return result;
        case 3:
            result.decimal = (Decimal)value;
            return result;
        case 4:
            result.string = (char*)value;
            return result;
    }
}

Value RetriveDecimal(Decimal, int);
inline Value RetriveDecimal(Decimal value, int tag) {
    Value result;
    switch(tag) {
        case 1:
            result.boolean = (Bool)value;
            return result;
        case 2:
            result.interger = (Int64)value;
            return result;
        case 3:
            result.decimal = value;
            return result;
        case 4:
            result.string = "null";
            return result;
    }
}

int max(int, int);
inline int max(int a, int b) {
    return a > b ? a : b;
}

#endif