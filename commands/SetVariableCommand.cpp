#include "Commands.h"

/**
 * This is SetVariableCommand class for set variable command
 * @param it the iterator
 * @return the number of jumps for the outside loop
 */
int SetVariableCommand::execute(list<string>::iterator it) {
    string varName = *it;
    string strValue = *(++(++it));
    double value;
    // calculates the value of the variable
    value = calculateValue(strValue);
    Variable* temp = DefineVarCommand::getInstance()->getVarSymbolTable()->find(varName)->second;
    // updates the new value
    if (temp->getValue() != value) {
        temp->setValue(value);
        Variable* v = DefineVarCommand::getInstance()->getVarSymbolTable()->find(varName)->second;
        //check variable's direction
        if(v->getDirection() == "->") {
            DefineVarCommand::getInstance()->getQueue()->push(v);
        }
        else {
            cout << "didn't push " << varName << " to queue" << endl;
        }
    }
    return 2;
}
