#ifndef __COMMON_H__
#define __COMMON_H__

/**
 * @brief: This file includes basic definitions and other
 *         tools, including exceptions, types and others
 * @date:  Last modified on 2020/1/25
 */

/* Types */

#include <string>

/*
typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef signed int int32_t;
typedef unsigned uint32_t;

typedef signed long long int64_t;
typedef unsigned long long uint64_t;
*/

typedef std::string string;  // So you could use string easily

/* Exception */

class exception {
public:
    string message;
    string note;

    exception(string message) : message(message), note("None") {}
    exception(string message, string note) : message(message), note(note) {}
    ~exception() {}

    string to_string() {
        return ">>> A error occurred\nMessage : " + message + "\n" + "Note    : " + note;
    }
};

/* Tag */

// We define tag for some types, 0 for bool, 1 for int64_t, 2 for double and 3 for string
template<typename T>
int8_t get_tag(T value) {
    auto origin_id = typeid(value);
    if(origin_id == typeid(bool))
        return 0;
    else if(origin_id == typeid(int64_t))
        return 1;
    else if(origin_id == typeid(double))
        return 2;
    else if(origin_id == typeid(string))
        return 3;
    else
        throw new exception("unrecognized type", "in get_tag function");
}

#endif