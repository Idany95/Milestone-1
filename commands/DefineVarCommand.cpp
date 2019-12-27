#include "Commands.h"
int DefineVarCommand::execute(list<string>::iterator it) {
    string varName = *it;
    string direction = *(++it);
    string simPath = *(++(++it));
    //inserting to Variable Symbol Table
    this->varSymbolTable.insert({varName, this->varSymbolTable.find(simPath)->second});
    //we return 3, cause we went over 3 items in the list
    return 3;
}

map<string,Variable*> DefineVarCommand::getVarSymbolTable() {
    return this->varSymbolTable;
}

map<string,Variable*> DefineVarCommand::getSimSymbolTable() {
    return this->simSymbolTable;
}

queue<Variable*> DefineVarCommand::getQueue() {
    return this->updateVariablesQueue;
}