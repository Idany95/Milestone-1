#include "Commands.h"

int SetVariableCommand::execute(list<string>::iterator it) {
    string varName = *it;
    string strValue = *(++(++it));
    double value;
    value = calculateValue(strValue);
    //find varSymbolTable on "DefineVarCommand" and update variable's value
    DefineVarCommand::getInstance()->getVarSymbolTable().find(varName)->second->setValue(value);
    return 2;
}
