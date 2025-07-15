#pragma once
#include "ast.h"

class Parser {
public:
    Parser(const vector<Token>& tokens);

    vector<unique_ptr<Statement>> parse();

private:
    const vector<Token>& tokens;
    size_t current;

    // Core helpers
    const Token& peek();
    const Token& previous();
    bool isAtEnd();
    const Token& advance();
    bool match(TokenType type, const string& value = "");
    bool check(TokenType type, const string& value = "");
    const Token& consume(TokenType type, const string& message);
    bool matchkeyword(const string& keyword);

    // Parsing methods
    unique_ptr<Statement> declaration();
    unique_ptr<Statement> varDeclaration();
    unique_ptr<Statement> statement();
    unique_ptr<Statement> ifStatement();
    unique_ptr<Statement> whileStatement();
    unique_ptr<Statement> returnStatement();
    unique_ptr<Statement> functionDeclaration();
    unique_ptr<Statement> expressionStatement();

    unique_ptr<Expression> expression();
    unique_ptr<Expression> assignment();
    unique_ptr<Expression> equality();
    unique_ptr<Expression> comparison();
    unique_ptr<Expression> term();
    unique_ptr<Expression> factor();
    unique_ptr<Expression> unary();
    unique_ptr<Expression> call();
    unique_ptr<Expression> primary();
};
