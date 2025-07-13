#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <unordered_set>
#include <token.h>

using namespace std;

// LEXER CLASS
class Lexer {
public:
    Lexer(const string& source) : src(source), pos(0), line(1), column(1) {}

    vector<Token> tokenize() {
        vector<Token> tokens;

        while (pos < src.length()){
            char current = peek();

            if (isspace(current)){
                skipWhitespace();
            } else if (isOperatorStart(current)){
                tokens.push_back(readOperator());
            } else if (isdigit(current)){
                tokens.push_back(readNumericalLiteral());
            } else if (current == '"'){
                tokens.push_back(readString());
            } else if (isalpha(current) || current == '_'){
                tokens.push_back(readIdentifierOrKeyword());
            } else if (isPunctuation(current)){
                tokens.push_back(makeToken(TokenType::Punctuation, string(1, current)));
                advance();
            } else {
                throw runtime_error("Unexpected character at line " + to_string(line) + ", column " + to_string(column));
            }

        }

        tokens.push_back(makeToken(TokenType::EndOfFile, ""));
        return tokens;
    }


private:
    string src;
    size_t pos;
    int line;
    int column;
    const unordered_set<string> keywords = {
        "fn", "int", "float", "string", "bool", "arr",
        "if", "else", "while", "return"
    };

    const unordered_set<string> keywordOperators = {
        "is", "and", "or", "not"
    };

    const unordered_set<string> multiCharOperators = {
        "==", "!=", "<=", ">=", "&&", "||",
        "++", "--", "+=", "-=", "*=", "/=",
        "%=", "&=", "|=", "^=", "->"
    };

    const unordered_set<char> singleCharOperators = {
        '+', '-', '*', '/', '%', '=', '!', '<', '>',
        '&', '|', '^'
    };


    char peek() {
        return pos < src.size() ? src[pos] : '\0';
    }

    char peekNext() {
        return (pos + 1 < src.size()) ? src[pos + 1] : '\0';
    }

    void advance() {
        if (src[pos] == '\n') {
            line++;
            column = 1;
        } else {
            column++;
        }
        pos++;
    }

    void skipWhitespace() {
        while (pos < src.size() && isspace(src[pos])) {
            advance();
        }
    }

    bool isPunctuation(char c) {
        static const string punctuations = "(){},.[]";
        return punctuations.find(c) != string::npos;
    }

    bool isOperatorStart(char c) {
        return singleCharOperators.count(c);
    }


    Token makeToken(TokenType type, const string& value) {
        return Token{type, value, line, column};
    }


    Token readIdentifierOrKeyword(){
        size_t startPos = pos;
        int tokenLine = line;
        int tokenColumn = column;

        while (isalnum(peek()) || peek() == '_') advance();

        string word = src.substr(startPos, pos - startPos);

        if (keywords.count(word)) {
            return Token{TokenType::Keyword, word, tokenLine, tokenColumn};
        }

        if (keywordOperators.count(word)) {
            return Token{TokenType::Operator, word, tokenLine, tokenColumn};
        }

        if (word == "true" || word == "false") {
            return Token{TokenType::Boolean, word, tokenLine, tokenColumn};
        }

        return Token{TokenType::Identifier, word, tokenLine, tokenColumn};
    }

    Token readNumericalLiteral(){
        size_t startPos = pos;
        int tokenLine = line;
        int tokenColumn = column;
        bool isFloat = false;

        while (isdigit(peek())) advance();

        if (peek() == '.' && isdigit(peekNext())){
            isFloat = true;
            advance();
            while (isdigit(peek())) advance();
        } 

        string num = src.substr(startPos, pos - startPos);
        return Token{isFloat ? TokenType::Float : TokenType::Integer, num, tokenLine, tokenColumn};
    }

    Token readString(){
        advance(); // skip starting quote
        size_t startPos = pos;
        int tokenLine = line;
        int tokenColumn = column;

        while (peek() != '"' && peek() != '\0') {
            advance();
        }

        if (peek() != '"'){
            throw runtime_error("Unterminated string at line " + to_string(tokenLine) + ", column " + to_string(tokenColumn));
        }
        
        string str = src.substr(startPos, pos - startPos);
        advance();
        return Token{TokenType::String, str, tokenLine, tokenColumn};
    }

    Token readOperator()
    {
        int tokenLine = line;
        int tokenColumn = column;
        
        char firstOp = peek();
        char secondOp = peekNext();

        string currentOp = string(1, firstOp) + string(1, secondOp);

        if (multiCharOperators.count(currentOp)){
            advance();
        } else {
            currentOp = string(1, firstOp);
        }

        advance();
        return Token{TokenType::Operator, currentOp, tokenLine, tokenColumn};
    }
};

int main() {
    ifstream infile("code.txt");
    string code = {istreambuf_iterator<char>(infile), istreambuf_iterator<char>()};

    Lexer lexer(code);
    auto tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        cout << "Token(" << tokenTypeToString(token.type) << ", \"" << token.value 
             << "\", Line: " << token.line << ", Col: " << token.column << ")\n";
    }

    return 0;
}
