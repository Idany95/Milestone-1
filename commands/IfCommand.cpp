#include "Commands.h"
#include "../interpreter/ex1.h"

int IfCommand::execute(list<string>::iterator it) {
    bool ifCorrect = false;
    string varName1 = *it;
    string condition = *(++it);
    string varName2 = *(++it);
    string openScope = *(++it);
    double varVal1 = this->calculateValue(varName1);
    double varVal2 = this->calculateValue(varName2);
    if (condition.compare("==") == 0) {
        if (varVal1 == varVal2) {
            ifCorrect = true;
        }
    }
    if (condition.compare("!=") == 0) {
        if (varVal1 != varVal2) {
            ifCorrect = true;
        }
    }
    if (condition.compare(">=") == 0) {
        if (varVal1 >= varVal2) {
            ifCorrect = true;
        }
    }
    if (condition.compare("<=") == 0) {
        if (varVal1 <= varVal2) {
            ifCorrect = true;
        }
    }
    if (condition.compare(">") == 0) {
        if (varVal1 > varVal2) {
            ifCorrect = true;
        }
    }
    if (condition.compare("<") == 0) {
        if (varVal1 < varVal2) {
            ifCorrect = true;
        }
    }
    if (ifCorrect) {
        ++it;
        while(*it != "}") {
            //if current string is a commands
            //P R O B L E M - need to fix
            if (ParseCommand::getInstance()->getMap().find(*it) != ParseCommand::getInstance()->getMap().end()) {
                Command* tempC = nullptr;
                tempC = ParseCommand::getInstance()->getMap().find(*it)->second;
                int i = tempC->execute(++it);
                //move the iterator i steps forward
                while (i > 0) {
                    it++;
                    i--;
                }
                //current string isn't a commands but a variable, we'll update it
            } else {
                Command* setVariable = new SetVariableCommand();
                int i = setVariable->execute(it);
                //move the iterator i steps forward
                while (i > 0) {
                    it++;
                    i--;
                }
            }
        }
        ++it;
        commandCounter++;
    }
    if (!ifCorrect) {
        while (*it != "}") {
            ++it;
            commandCounter++;
        }
    }
    return commandCounter + 3;
}