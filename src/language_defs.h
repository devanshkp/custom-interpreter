#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// =====================
// === Operators =======
// =====================

// Single-character operators
const unordered_set<char> singleCharOperators = {
    '+', '-', '*', '/', '%', '=', '!', '<', '>',
    '&', '|', '^'
};

// Multi-character operators
const unordered_set<string> multiCharOperators = {
    "==", "!=", "<=", ">=", "&&", "||",
    "++", "--", "+=", "-=", "*=", "/=",
    "%=", "&=", "|=", "^=", "->"
};

// Keyword-like operators 
const unordered_set<string> keywordOperators = {
    "and", "or", "not", "is"
};

// =====================
// === Keywords =========
// =====================

const unordered_set<string> keywords = {
    "fn", "int", "float", "string", "bool", "arr",
    "if", "else", "while", "return"
};

// =====================
// === Variable Types ===
// =====================

const unordered_set<string> variableTypes = {
    "int", "float", "bool", "string"
};


