//
// Created by Idan Yarchi on 11/5/19.
//

#include "ex1.h"
BinaryOperator::BinaryOperator(Expression *newLeft, Expression *newRight) {
    this->left = newLeft;
    this->right = newRight;
}

BinaryOperator::~BinaryOperator() {
    delete this->left;
    delete this->right;
}

Plus::Plus(Expression *newLeft, Expression *newRight): BinaryOperator(newLeft, newRight) {}
Minus::Minus(Expression *newLeft, Expression *newRight): BinaryOperator(newLeft, newRight) {}
Mul::Mul(Expression *newLeft, Expression *newRight): BinaryOperator(newLeft, newRight) {}
Div::Div(Expression *newLeft, Expression *newRight): BinaryOperator(newLeft, newRight) {}

double Plus::calculate() {
    return this->left->calculate() + this->right->calculate();
}
double Minus::calculate() {
    return this->left->calculate() - this->right->calculate();
}
double Mul::calculate() {
    return this->left->calculate() * this->right->calculate();
}
double Div::calculate() {
    if (this->right->calculate() != 0) {
        return this->left->calculate() / this->right->calculate();
    }
    else {
        throw "division by zero";
    }
}
Value::Value(double newValue) {
    this->value = newValue;
}

double Value::calculate() {
return this->value;
}

Value::~Value() {}

Var::Var(string newName, double newValue) {
    this->name = newName;
    this->value = newValue;
}

double Var::calculate() {
    return this->value;
}

string Var::getName() {
    return this->name;
}
Var& Var::operator++() {
    this->value = this->value + 1;
    return *this;
}

Var& Var::operator--(int) {
    //Var *temp = new Var(this->name, this->value);
    //this->value = this->value - 1;
    //return *temp;
    this->value = this->value - 1;
    return *this;
}
Var& Var::operator++(int) {
    //Var *temp = new Var(this->name, this->value);
    //this->value = this->value + 1;
    //return *temp;
    this->value = this->value + 1;
    return *this;
}

Var& Var::operator--() {
    this->value = this->value - 1;
    return *this;
}

Var& Var::operator+=(Var *var) {
    this->value = this->value + var->value;
    return *this;
}

Var& Var::operator-=(Var *var) {
    this->value = this->value - var->value;
    return *this;
}

Var::~Var() {}

UnaryOperator::UnaryOperator(Expression *newExp) {
    this->exp = newExp;
}
UnaryOperator::~UnaryOperator() {
    delete this->exp;
}

UPlus::UPlus(Expression *newExp): UnaryOperator(newExp) {}
UMinus::UMinus(Expression *newExp): UnaryOperator(newExp) {}

double UPlus::calculate() {
    return this->exp->calculate();
}
double UMinus::calculate() {
    return -(this->exp->calculate());
}

int Interpreter::searchVars(string s) {
    for (int i = 0; i < (int)this->vars.size(); i++){
        // if name is equal
        if (!this->vars[i]->getName().compare(s)) {
            return i;
        }
    }
    return -1;
}

void Interpreter::setVars(vector <Var*> newVars) {
    this->vars = newVars;
}


void Interpreter::oldSetVariables(string arr) {
    int i = 0, length = 0;
    double value;
    string varName;
    while (i < (int)arr.length()) {
        if (!((arr[i] >= 'a' && arr[i] <= 'z') || (arr[i] >= 'A' && arr[i] <= 'Z') || arr[i] == '_')) {
            throw "illegal Var assignment!";
        }
        length++;
        while (arr[i+length] != '=') {
            if (!((arr[i+length] >= 'a' && arr[i+length] <= 'z')
                    || (arr[i+length] >= 'A' && arr[i+length] <= 'Z')
                    || (arr[i+length] >= '0' && arr[i+length] <= '9')
                    || (arr[i+length] == '_'))) {
                throw "illegal Var assignment!";
            }
            length++;
        }
        varName = arr.substr(i, length);
        i = i + length + 1;
        length = 0;
        while ((arr[i+length] != ';') && ((i+length) < (int)arr.length())) {
            length++;
        }
        try {
            value = stod(arr.substr(i, length));
        }
        catch(...) {
            throw "illegal Var assignment!";
        }
        Var *var = new Var(varName, value);
        int checkVar = searchVars(varName);
        if (checkVar == -1) {
            this->vars.push_back(var);
        }
        else {
            this->vars.erase(this->vars.begin() + checkVar);
            this->vars.push_back(var);
        }
        i = i + length + 1;
        length = 0;
    }
}

Expression* Interpreter::interpret(string arr) {
    arr.erase(remove(arr.begin(), arr.end(), ' '), arr.end());
    queue <string> q;
    stack <char> s;
    int i = 0, length = 0;
    string num;
    //Shunting yard (infix to postfix)
    while (i < (int)arr.length()) {
        // if it's a number
        if (arr[i] >= '0' && arr[i] <= '9') {
            // going over the number
            while ((arr[i+length] >= '0' && arr[i+length] <= '9') || arr[i+length] == '.') {
                length++;
            }
            num = arr.substr(i, length);
            i = i + length;
            length = 0;
            q.push(num);
        }
        // if it's a sign
        else {
            if (arr[i] == '(') {
                    s.push(arr[i]);
                    i++;
            }
            else {
                if (arr[i] == '/' || arr[i] == '*') {
                    if (s.empty() || s.top() == '+' || s.top() == '-' || s.top() == '('){
                        s.push(arr[i]);
                        i++;
                    }
                    else {
                        string temp(1, s.top());
                        q.push(temp);
                        s.pop();
                        s.push(arr[i]);
                        i++;
                    }
                }
                else if (arr[i] == '+' || arr[i] == '-') {
                    //check if it's unary operator
                    if (arr[i-1] == '(' ||i == 0) {
                        if (!(s.empty() || s.top() == '*' || s.top() == '*' ||
                            s.top() == '+' || s.top() == '-' || s.top() == '(')) {
                            string temp(1, s.top());
                            q.push(temp);
                        }
                        if (arr[i] == '+') {
                            s.push('$');
                            i++;
                        }
                        else {
                            s.push('#');
                            i++;
                        }
                    }
                    // else it's a binary operator
                    else {
                        if (s.empty() || s.top() == '(') {
                            s.push(arr[i]);
                            i++;
                        }
                        else {
                            string temp(1, s.top());
                            q.push(temp);
                            s.pop();
                            s.push(arr[i]);
                            i++;
                        }
                    }
                }
                else if (arr[i] == ')') {
                    while(!(s.empty()) && s.top() != '(') {
                        string temp(1, s.top());
                        q.push(temp);
                        s.pop();
                    }
                    if (s.empty()) {
                        throw "bad input";
                    }
                    s.pop();
                    i++;
                }
                else {
                    //check if it's a Var
                    while (arr[i+length] != '+' && arr[i+length] !='-' &&
                            arr[i+length] != '*' && arr[i+length] != '/' &&
                            arr[i+length] !='(' && arr[i+length] != ')') {
                        length++;
                    }
                    num = arr.substr(i, length);
                    i = i + length;
                    length = 0;
                    int checkVar = searchVars(num);
                    if (checkVar != (-1)) {
                        q.push(num);
                    }
                    else {
                        throw ("illegal math expression");
                    }
                }
            }
        }
    }
    // emptying our stack
    while (!s.empty()) {
        if (s.top() == '(') {
            throw "bad input";
        }
        string temp(1, s.top());
        q.push(temp);
        s.pop();
    }
    // postfix to Expression
    stack <Expression*> s2;
    Expression *e, *left, *right;
    while (!q.empty()) {
        string current;
        current = q.front();
        q.pop();
        // if it's an number
        if (current[0] >= '0' && current[0] <= '9') {
            e = new Value(stod(current));
            s2.push(e);
            continue;
        }
        // if it's a Var
        int checkVar = searchVars(current);
        if (checkVar != (-1)) {
            e = this->vars[checkVar];
            s2.push(e);
            continue;
        }
        // else (it's an operator)
        else {
            switch(current[0]) {
                case ('*'):
                    right = s2.top();
                    s2.pop();
                    left = s2.top();
                    s2.pop();
                    e = new Mul(left, right);
                    s2.push(e);
                    break;
                case ('/'):
                    right = s2.top();
                    s2.pop();
                    left = s2.top();
                    s2.pop();
                    e = new Div(left, right);
                    s2.push(e);
                    break;
                case ('+'):
                    right = s2.top();
                    s2.pop();
                    left = s2.top();
                    s2.pop();
                    e = new Plus(left, right);
                    s2.push(e);
                    break;
                case ('-'):
                    right = s2.top();
                    s2.pop();
                    left = s2.top();
                    s2.pop();
                    e = new Minus(left, right);
                    s2.push(e);
                    break;
                case ('$'):
                    right = s2.top();
                    s2.pop();
                    e = new UPlus(right);
                    s2.push(e);
                    break;
                case ('#'):
                    right = s2.top();
                    s2.pop();
                    e = new UMinus(right);
                    s2.push(e);
                    break;
            }
        }
    }
    return s2.top();
}