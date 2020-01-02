#include <sstream>
#include "Commands.h"
//DefineVarCommand* DefineVarCommand::theInstance = 0;
int DefineVarCommand::execute(list<string>::iterator it) {
    string varName = *it;
    string sign = *(++it);
    if(sign == "->" || sign == "<-") {
        string direction = sign;
        string simPath = *(++(++it));
        simPath = (simPath).substr(1,simPath.length()-2);
        //inserting to Variable Symbol Table
        Variable* v = this->simSymbolTable->find(simPath)->second;
        this->varSymbolTable->insert({varName, v});
        v->setDirection(sign);
        //we return 3, cause we went over 3 items in the list
        return 3;
    }
    else {
        string secondVarName = *(++it);
        this->varSymbolTable->insert({varName, new Variable("<-", "")});
        this->varSymbolTable->find(varName)->second->setValue(calculateValue(secondVarName));
        return 2;
    }
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
