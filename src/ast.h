#include "token.h"
#include <vector>
#include <memory>
#include <string>

using namespace std;


// =====================
// === Base Classes  ===
// =====================


struct Statement {
    virtual ~Statement() = default;
};

struct Expression {
    virtual ~Expression() = default;
};

struct FunctionParameter {
    string type;
    string name;
};


// =====================
// === Expressions  ===
// =====================


struct LiteralExpr : Expression {
    Token value;

    LiteralExpr(Token value) : value(value) {}
};

struct VariableExpr : Expression {
    string name;

    VariableExpr(string n) : name(n) {}
};

struct UnaryExpr : Expression {
    Token op;
    unique_ptr<Expression> right;

    UnaryExpr(Token op, unique_ptr<Expression> right)
        : op(move(op)), right(move(right)) {}
};


struct BinaryExpr : Expression {
    unique_ptr<Expression> left;
    Token op;
    unique_ptr<Expression> right;

    BinaryExpr(unique_ptr<Expression> l, Token o, unique_ptr<Expression> r) : left(move(l)), op(o), right(move(r)) {}
};

struct CallExpr : Expression {
    string callee;
    vector<unique_ptr<Expression>> arguments;

    CallExpr(string c, vector<unique_ptr<Expression>> args) : callee(c), arguments(move(args)) {}
};

struct AssignmentExpr : Expression {
    string name;
    unique_ptr<Expression> value;

    AssignmentExpr(string name, unique_ptr<Expression> value)
        : name(move(name)), value(move(value)) {}
};


struct GroupingExpr : Expression {
    unique_ptr<Expression> expression;

    GroupingExpr(unique_ptr<Expression> expr) : expression(move(expr)) {}
};



// =====================
// === Statements  ===
// =====================


struct VarDeclaration : Statement {
    string type;
    string name;
    unique_ptr<Expression> initializer;

    VarDeclaration(string type, string name, unique_ptr<Expression> initializer)
        : type(move(type)), name(move(name)), initializer(move(initializer)) {}
};


struct ExpressionStatement : Statement {
    unique_ptr<Expression> expression;

    ExpressionStatement(unique_ptr<Expression> exp) : expression(move(exp)) {}
};

struct IfStatement : Statement {
    unique_ptr<Expression> condition;
    vector<unique_ptr<Statement>> thenBranch;
    vector<unique_ptr<Statement>> elseBranch;

    IfStatement(unique_ptr<Expression> cond, vector<unique_ptr<Statement>> thenBranch, vector<unique_ptr<Statement>> elseBranch = {}) :
        condition(move(cond)), thenBranch(move(thenBranch)), elseBranch(move(elseBranch)) {}
};


struct WhileStatement : Statement {
    unique_ptr<Expression> condition;
    vector<unique_ptr<Statement>> body;

    WhileStatement(unique_ptr<Expression> cond, vector<unique_ptr<Statement>> body) : condition(move(cond)), body(move(body)) {}
};

struct FunctionDeclaration : Statement {
    string name;
    string type;
    vector<FunctionParameter> arguments;
    vector<unique_ptr<Statement>> body;

    FunctionDeclaration(string n, string type, vector<FunctionParameter> args, vector<unique_ptr<Statement>> body) : 
        name(n), type(type), arguments(move(args)), body(move(body)) {}
};

struct ReturnStatement : Statement {
    unique_ptr<Expression> value;

    ReturnStatement(unique_ptr<Expression> val) : value(move(val)) {}
};

