#ifndef EX3_COMMANDS_H
#define EX3_COMMANDS_H
#include <iostream>
#include "map"
#include "list"
#include "vector"
#include <thread>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
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
public:
    virtual int execute(list<string>::iterator it) = 0;
    virtual ~Command() = default;
    bool checkIfNumber(string s);
    double calculateValue(string s);
};

class ParseCommand: public Command {
private:
    map <string,Command*> commandMap;
    ParseCommand(){};
public:
    //SINGLETON
    static ParseCommand *getInstance() {
        static ParseCommand c;
        return &c;
    }
    int execute(list<string>::iterator it);
    void parser(list<string> LexeredCommandsList);
    map <string,Command*> getMap() {
        return this->commandMap;
    };
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
    DefineVarCommand(){};
    static DefineVarCommand *theInstance;
public:
    //SINGELTON
    static DefineVarCommand *getInstance(){
            static DefineVarCommand c;
            return &c;
        /**if(theInstance == nullptr) {
            return new DefineVarCommand();
        }
        return theInstance;**/
    }
    map <string,Variable*> getVarSymbolTable();
    int execute(list<string>::iterator it);
};

class SetVariableCommand: public Command {
public:
    int execute(list<string>::iterator it);
};

class ConditionParser: public Command {
protected:
    list<Command*> CommandList;
    int commandCounter;
public:
    int execute(list<string>::iterator it){
        return 0;
    };
};
class IfCommand: public ConditionParser {
    int execute(list<string>::iterator it);
};
class LoopCommand: public ConditionParser {
protected:
    int commandCounter;
    int execute(list<string>::iterator it);
    bool condition(string var1, string con, string var2);
};
class PrintCommand: public Command {
    int execute(list<string>::iterator it);
};
class SleepCommand: public Command {
    int execute(list<string>::iterator it);
};
#endif //EX3_COMMANDS_H