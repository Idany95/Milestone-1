#include <sstream>
#include "Commands.h"
//DefineVarCommand* DefineVarCommand::theInstance = 0;
int DefineVarCommand::execute(list<string>::iterator it) {
    std::ostringstream oss;
    string varName = *it;
    string direction = *(++it);
    string simPath = *(++(++it));
    //inserting to Variable Symbol Table
    //oss<< simPath;
    //string s = oss.str();
    Variable* v = this->simSymbolTable->find(simPath)->second;
    this->varSymbolTable->insert({varName, v});
    //we return 3, cause we went over 3 items in the list
    return 3;
}

map<string,Variable*>* DefineVarCommand::getVarSymbolTable() {
    return this->varSymbolTable;
}

map<string,Variable*>* DefineVarCommand::getSimSymbolTable() {
    return this->simSymbolTable;
}

queue<Variable*>* DefineVarCommand::getQueue() {
    return this->updateVariablesQueue;
}

map<int, struct Variable *> *DefineVarCommand::getOrderedMap() {
    return this->orderedMap;
}
