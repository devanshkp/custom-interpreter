#pragma once
#include <string>

enum class TokenType {
    Keyword,
    Identifier,
    Integer,
    Float,
    String,
    Boolean,
    Operator,
    Punctuation,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;
};

inline std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::Keyword: return "Keyword";
        case TokenType::Identifier: return "Identifier";
        case TokenType::Integer: return "Integer";
        case TokenType::Float: return "Float";
        case TokenType::String: return "String";
        case TokenType::Boolean: return "Boolean";
        case TokenType::Operator: return "Operator";
        case TokenType::Punctuation: return "Punctuation";
        case TokenType::EndOfFile: return "EndOfFile";
        default: return "Unknown";
    }
}