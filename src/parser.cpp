#include "parser.h"
#include <stdexcept>


Parser::Parser(const vector<Token>& tokens)
    : tokens(tokens), current(0) {}


// =====================
// === Token Helpers ===
// =====================

const Token& Parser::peek(){
    return tokens.at(current);
}

const Token& Parser::previous(){
    if (current == 0) {
        throw runtime_error("Called previous() at beginning of token stream.");
    }
    return tokens.at(current - 1);
}

bool Parser::isAtEnd(){
    return peek().type == TokenType::EndOfFile;
}

const Token& Parser::advance(){
    if (!isAtEnd()) current++;
    return previous();
}

bool Parser::check(TokenType type, const string& value =""){
    if (isAtEnd()) return false;
    const Token& curToken = peek();
    if (curToken.type != type) return false;
    return value.empty() || curToken.value == value;
}

bool Parser::match(TokenType type, const string& value =""){
    if (check(type, value)){
        advance();
        return true;
    } else {
        return false;
    }
}

const Token& Parser::consume(TokenType type, const string& message){
    if (match(type)){
        return previous();
    }
    throw runtime_error("Parse error: " + message + " at line " + to_string(peek().line));
}

// =====================
// === Parsing methods ===
// =====================

vector<unique_ptr<Statement>> Parser::parse() {
    while (!isAtEnd()){

    }

    return vector<unique_ptr<Statement>>();
}

