/**
 * Stupied tools for lexical analysis
 */

/* Token */

#include "common.hpp"

enum token_type {

};

struct token {
    int line_num;
    string symbol;
    token_type type;
};

/* Lexer */

#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>

class lexer {
private:
    char* chunk;
    int64_t line_num;
    int64_t chunk_ptr;
    int64_t chunk_len;

private:
    // skip until a meaning symbol appears
    void skip_any() {
        while (!(chunk_ptr == chunk_len)) {
            if (chunk[chunk_ptr] == '\n' || chunk[chunk_ptr] == '\r') {
                line_num++;
                chunk_ptr++;
            } else if (chunk[chunk_ptr] == ' ' || chunk[chunk_ptr] == '\t' || chunk[chunk_ptr] == '\v' || chunk[chunk_ptr] == '\f')
                chunk_ptr++;
            else if (chunk[chunk_ptr] == '#')
                skip_comment();
            else
                break;
        }
    }

    // skip the comment
    void skip_comment() {
        chunk_ptr++;
        bool enclose = false;
        while (!(chunk_ptr == chunk_len)) {
            if (chunk[chunk_ptr] == '#') {
                chunk_ptr++;
                enclose = true;
                break;
            } else
                chunk_ptr++;
        }
        if (!enclose)
            throw new exception("unclosed comment", "in line : " + std::to_string(line_num));
    }

public:
    lexer(string program) {
        load_chunk(program);
    }

    ~lexer() {
        delete chunk;
    }

    void load_chunk(string program) {
        chunk = new char[program.length() + 1];
        strcpy(chunk, program.c_str());
        line_num = chunk_ptr = 0;
        chunk_len = program.length();
    }

    void print_chunk() {
        std::cout << "\n==========" << std::endl;
        std::cout << chunk_ptr << std::endl;
        for (int i = chunk_ptr; i < chunk_len; ++i)
            std::cout << chunk[i] << " ";
        std::cout << std::endl;
        std::cout << "==========\n";
    }

    void next_token() {
        if(chunk_ptr >= chunk_len)
            throw new exception("eof");
        skip_any();
        std::cout << chunk[chunk_ptr] << " <<<<" << std::endl;
        chunk_ptr++;
    }
};