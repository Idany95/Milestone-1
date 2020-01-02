#include "Commands.h"

int SetVariableCommand::execute(list<string>::iterator it) {
    string varName = *it;
    string strValue = *(++(++it));
    double value;
    //cout << "setvarCommand: ";
    //cout << strValue << endl;
    value = calculateValue(strValue);
    //find varSymbolTable on "DefineVarCommand" and update variable's value
    cout << varName << " is our varName " << endl;
    if(varName == "1000") {
        cout << "i'm 1000!!!";
    }
    mu.lock();
    Variable* temp = DefineVarCommand::getInstance()->getVarSymbolTable()->find(varName)->second;
    if (temp == nullptr) {
        cout << value << " x" << endl;
    }
    temp->setValue(value);
    cout << value << " a" << endl;
    Variable* v = DefineVarCommand::getInstance()->getVarSymbolTable()->find(varName)->second;
    cout << " b" << endl;
    //check variable's direction
    if(v->getDirection() == "->") {
        DefineVarCommand::getInstance()->getQueue()->push(v);
        cout << " c" << endl;

    }
    mu.unlock();
    //PUSHING DOESENT WORK
    //cout << "queue in set variable" << DefineVarCommand::getInstance()->getQueue()->size() << endl;
    return 2;
}
