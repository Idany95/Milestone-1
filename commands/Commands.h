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
#include <queue>
#include <mutex>
using namespace std;
//global mutex
static mutex mu;

/**
 * definition of class variable
 */
class Variable {
private:
    // initialization (we want a very big number)
    double value = 888888888;
    string sim;
    //gets -> or <-
    string direction;
public:
    Variable(string direction, string sim);
    void setValue(double newValue);
    void setDirection(string newDirection);
    double getValue();
    string getSim();
    string getDirection();
};

/**
 * definition of class Command
 */
class Command {
public:
    virtual int execute(list<string>::iterator it) = 0;
    virtual ~Command() = default;
    bool checkIfNumber(string s);
    double calculateValue(string s);
};

/**
 * definition of class ParseCommand (the parser)
 */
class ParseCommand: public Command {
private:
    bool parsingFlag = false;
    // map of all the commands
    map <string,Command*> commandMap;
    ParseCommand(){};
public:
    //SINGLETON
    static ParseCommand *getInstance() {
        static ParseCommand c;
        return &c;
    }
    int execute(list<string>::iterator it);
    void parser(list<string>* LexeredCommandsList);
    map <string,Command*> getMap() {
        return this->commandMap;
    };
    bool getParsingFlag();
    void setParsingFlag(bool b);
};

/**
 * definition of class OpenServerCommand
 */
class OpenServerCommand: public Command {
private:
    OpenServerCommand() {};
public:
    //using singelton
    static OpenServerCommand *getInstance() {
        static OpenServerCommand c;
        return &c;
    }
    // global thread
    thread loopThread;
    int execute(list<string>::iterator it);
};

/**
 * definition of class ConnectCommand
 */
class ConnectCommand: public Command {
private:
    ConnectCommand() {};
public:
    //using singelton
    static ConnectCommand *getInstance() {
        static ConnectCommand c;
        return &c;
    }
    // global thread
    thread loopThread;
    int execute(list<string>::iterator it);
};

/**
 * definition of class DefineVarCommand
 */
class DefineVarCommand: public Command {
private:
    map <string,Variable*> *varSymbolTable = new map<string,Variable*>();
    map <string,Variable*> *simSymbolTable = new map<string,Variable*>();
    map <int,Variable*> *orderedMap = new map<int,Variable*>();
    queue <Variable*> *updateVariablesQueue = new queue<Variable*>();
    DefineVarCommand(){};
    static DefineVarCommand *theInstance;
public:
    //using singeltn
    static DefineVarCommand *getInstance(){
            static DefineVarCommand c;
            return &c;
    }
    map <string,Variable*>* getVarSymbolTable();
    map<string, struct Variable *>* getSimSymbolTable();
    map<int, struct Variable *>* getOrderedMap();
    queue <Variable*>* getQueue();
    int execute(list<string>::iterator it);
};

/**
 * definition of class SetVariableCommand
 */
class SetVariableCommand: public Command {
public:
    int execute(list<string>::iterator it);
};

/**
 * definition of class ConditionParser (another condition parser)
 */
class ConditionParser: public Command {
protected:
    list<Command*> CommandList;
public:
    int execute(list<string>::iterator it){
        return 0;
    };
};

/**
 * definition of class IfCommand
 */
class IfCommand: public ConditionParser {
    // member field for jumps
    int commandCounter = 0;
    int execute(list<string>::iterator it);
};

/**
 * definition of class LoopCommand
 */
class LoopCommand: public ConditionParser {
protected:
    // member field for jumps
    int commandCounter = 0;
    int execute(list<string>::iterator it);
    bool condition(string var1, string con, string var2);
};

/**
 * definition of class PrintCommand
 */
class PrintCommand: public Command {
    int execute(list<string>::iterator it);
};

/**
 * definition of class SleepCommand
 */
class SleepCommand: public Command {
    int execute(list<string>::iterator it);
};
#endif //EX3_COMMANDS_H