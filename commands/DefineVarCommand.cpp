#include "Commands.h"
int DefineVarCommand::execute(list<string>::iterator it) {
    string varName = *it;
    string direction = *(++it);
    string simPath = *(++(++it));
    //inserting to Variable Symbol Table
    this->varSymbolTable.insert({varName, new Variable(direction, simPath)});
    //inserting to Simulator Symbol Table
    this->simSymbolTable.insert({simPath,this->varSymbolTable.find(varName)->second});
    //we return 3, cause we went over 3 items in the list
    return 3;
}

map<string,Variable*> DefineVarCommand::getVarSymbolTable() {
    return this->varSymbolTable;
}
