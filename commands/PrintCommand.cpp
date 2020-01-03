#include "Commands.h"

/**
 * This is PrintCommand class for print command
 * @param it the iterator
 * @return the number of jumps for the outside loop
 */
int PrintCommand::execute(list<string>::iterator it) {
    //if it's a text
    if ((*it)[0] == '"'){
        cout << (*it).substr(1,(*it).length()-2) << endl;
    }
    //else it's a variable
    else {
        cout << DefineVarCommand::getInstance()->getVarSymbolTable()->find(*it)->second->getValue() << endl;
    }
    return 0;
}