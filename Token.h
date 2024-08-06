#pragma once

#include <string>

enum TokenType
{
    UNKNOWN = 0,
    IDENT,
    QUIT,
    NEQ,
    GT,
    LT,
    ASSIGN,
    COMMENT,
    NUM, // 0-8
    LEFT_PAREN,
    RIGHT_PAREN,
    MUL,
    DIV,
    PLS,
    MNS,
    G,
    L,
    COLON,
    EQU, // 9-18
    SEMI,
    EOFTOKEN // 19 20
};

class Token {
public:
    TokenType type;
    std::string val;
    Token() { 
        type = UNKNOWN;
        val = "";
    }
    void set(TokenType t, string v) {
        type = t;
        val = v ;
    }
};

struct ID
{
    TokenType type;
    string val;
    float num;
};
