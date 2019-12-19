#ifndef EX3_EX3_H
#define EX3_EX3_H
#include <iostream>
#include "map"
#include "list"
#include "vector"
using namespace std;

class Variable {
private:
    double value;
    string sim;
    string direction; //gets -> or <-
public:
    Variable(string direction, string sim);
    void setValue(double newValue);
    double getValue();
};

class Command {
protected:
    map <string,Command*> commandMap;
public:
    virtual int execute(list<string>::iterator it);
    void parser(list<string> LexeredCommandsList);
    virtual ~Command() {}
    bool checkIfNumber(string s);
    double calculateValue(string s);
};

class OpenServerCommand: public Command {
    int execute(list<string>::iterator it);
};

class ConnectCommand: public Command {
    int execute(list<string>::iterator it);
};

class DefineVarCommand: public Command {
private:
    map <string,Variable*> varSymbolTable;
    map <string,Variable*> simSymbolTable;
public:
    map <string,Variable*> getVarSymbolTable();
    int execute(list<string>::iterator it);
};
#endif //EX3_EX3_H