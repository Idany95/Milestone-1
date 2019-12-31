#include "Commands.h"

int SetVariableCommand::execute(list<string>::iterator it) {
    string varName = *it;
    string strValue = *(++(++it));
    double value;
    cout << "setvarCommand: ";
    cout << strValue << endl;
    value = calculateValue(strValue);
    //find varSymbolTable on "DefineVarCommand" and update variable's value
    DefineVarCommand::getInstance()->getVarSymbolTable()->find(varName)->second->setValue(value);
    Variable* v = DefineVarCommand::getInstance()->getVarSymbolTable()->find(varName)->second;
    DefineVarCommand::getInstance()->getQueue()->push(v);
    //PUSHING DOESENT WORK
    cout << "queue in set variable" << DefineVarCommand::getInstance()->getQueue()->size() << endl;
    return 2;
}
