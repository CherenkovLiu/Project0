#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <string>



// Basic types
typedef char Int8;
typedef unsigned char UInt8;

typedef short Int16;
typedef unsigned short UInt16;

typedef int Int32;
typedef unsigned UInt32;

typedef long long int Int64;
typedef unsigned long long int UInt64;

typedef double Double;
typedef bool Bool;
typedef std::string String;
// Data type of the language

union Value {
    Bool PBoolean;
    Int64 PInteger;
    Double PNumber;
    String PString;
};

struct PObject {
    Int8 tag;     // The tag for the value, 0 means bool, 1 means Int64, 2 means double, 3 means string
    Value value;
};


enum ExpType {
    InvalidPointerException,
    StackOverflowException,
    TypeMismatchException,
    DivideByZeroException
};

class Exception {
private:
    String ToMessage(ExpType type) {
        switch(type) {
            case ExpType::DivideByZeroException:
                return "DivideByZeroException";
            case ExpType::InvalidPointerException:
                return "InvalidPointerException";
            case ExpType::StackOverflowException:
                return "StackOverflowException";
            case ExpType::TypeMismatchException:
                return "TypeMismatchException";
            default:
                return "Exception";
        }
    }

public:
    String message;
    ExpType type;
    UInt16 lineNumber;

    Exception(ExpType type, UInt16 lineNumber) {
        this->type = type;
        this->lineNumber = lineNumber;
        this->message = ToMessage(type);
    }

    String ToString() {
        return this->message + " " + std::to_string(lineNumber);
    }
};

template<typename T>
Int8 GetTag(T value) {
    if(typeid(value) == typeid(Bool))
        return 0;
    else if (typeid(value) == typeid(Int64))
        return 1;
    else if (typeid(value) == typeid(Double))
        return 2;
    else if (typeid(value) == typeid(String))
        return 3;
    else
        throw new Exception(TypeMismatchException, 48);
}


#endif