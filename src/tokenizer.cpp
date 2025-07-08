#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <unordered_set>

using namespace std;

// TokenType enum
enum class TokenType {
    Keyword,
    Identifier,
    Integer,
    Float,
    String,
    Boolean,
    Operator,
    Punctuation,
    EndOfFile,
};

// Token struct
struct Token {
    TokenType type;
    string value;
    int line;
    int column;
};

// Lexer class definition and implementation
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
        "fn", "int", "str", "bool", "arr",
        "if", "else", "while", "return", "true", "false"
    };

    const unordered_set<string> keywordOperators = {
        "is", "and", "or", "not"
    };

    const unordered_set<string> symbolicOperators = {
        "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">="
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
        static const string ops = "+-*/%=!<>|&";
        return ops.find(c) != std::string::npos;
    }


    Token makeToken(TokenType type, const std::string& value) {
        return Token{type, value, line, column};
    }


    // Declarations for helper functions
    Token readIdentifierOrKeyword();
    Token readNumericalLiteral();
    Token readString();
    Token readOperator();
};

// Implement helper functions here
// e.g., Token Lexer::readIdentifierOrKeyword() { ... }
