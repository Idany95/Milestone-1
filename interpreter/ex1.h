
#ifndef EX1_EX1_H
#define EX1_EX1_H
#include <string>
#include <stack>
#include <queue>
#include <typeinfo>
#include "Expression.h"
#include <algorithm>
class BinaryOperator: public Expression {
protected:
    Expression* right;
    Expression* left;

public:
     BinaryOperator(Expression *left, Expression *right);
     virtual ~BinaryOperator();
};
class Plus: public BinaryOperator {
public:
    Plus(Expression *left, Expression *right);
    double calculate();
};
class Minus: public BinaryOperator {
public:
    Minus(Expression *left, Expression *right);
    double calculate();
};
class Mul: public BinaryOperator {
public:
    Mul(Expression *left, Expression *right);
    double calculate();
};
class Div: public BinaryOperator {
public:
    Div(Expression *left, Expression *right);
    double calculate();
};
class Value: public Expression {
private:
    double value;
public:
    Value(double value);
    double calculate();
    virtual ~Value();
};

class Var: public Expression {
private:
    string name;
    double value;
public:
    Var (string name, double value);
    double calculate();
    string getName();
    Var& operator++();
    Var& operator--();
    Var& operator+=(Var *var);
    Var& operator-=(Var *var);
    Var& operator++(int);
    Var& operator--(int);
    virtual ~Var();
};

class UnaryOperator: public Expression {
protected:
    Expression *exp;
public:
     UnaryOperator(Expression *exp);
     virtual ~UnaryOperator();
};

class UPlus: public UnaryOperator {
public:
    UPlus(Expression *exp);
    double calculate();
};

class UMinus: public UnaryOperator {
public:
    UMinus(Expression *exp);
    double calculate();
};

class Interpreter {
private:
    vector <Var*> vars;
public:
    int searchVars(string s);
    void oldSetVariables(string s);
    Expression* interpret(string s);
    void setVars(vector<Var*> vars);
};
#endif //EX1_EX1_H
