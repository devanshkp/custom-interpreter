#include "parser.h"
#include <language_defs.h>
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

vector<unique_ptr<Statement>> Parser::parse(){
    vector<unique_ptr<Statement>> statements;
    while (!isAtEnd()){
        statements.push_back(declaration());
    }

    return statements;
}


unique_ptr<Statement> Parser::declaration(){
    if (match(TokenType::Keyword) && previous().value == "fn") return functionDeclaration();
    if (match(TokenType::Keyword) && variableTypes.count(previous().value)) return varDeclaration();
    return statement();
}

unique_ptr<Statement> Parser::statement(){
    if (match(TokenType::Keyword) && previous().value == "if") return ifStatement();
    if (match(TokenType::Keyword) && previous().value == "while") return whileStatement();
    if (match(TokenType::Keyword) && previous().value == "return") return returnStatement();
    return expressionStatement();
}

unique_ptr<Statement> Parser::varDeclaration(){

}

unique_ptr<Statement> Parser::ifStatement(){

}

unique_ptr<Statement> Parser::whileStatement(){

}

unique_ptr<Statement> Parser::returnStatement(){

}

unique_ptr<Statement> Parser::functionDeclaration(){

}

unique_ptr<Statement> Parser::expressionStatement(){

}

unique_ptr<Expression> expression();
unique_ptr<Expression> assignment();
unique_ptr<Expression> equality();
unique_ptr<Expression> comparison();
unique_ptr<Expression> term();
unique_ptr<Expression> factor();
unique_ptr<Expression> unary();
unique_ptr<Expression> call();
unique_ptr<Expression> primary();
