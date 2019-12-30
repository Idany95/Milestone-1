#include "Commands.h"
#include "../interpreter/ex1.h"

int IfCommand::execute(list<string>::iterator it) {
    bool ifCorrect = false;
    string varName1 = *it;
    string condition = *(++it);
    string varName2 = *(++it);
    string openScope = *(++it);
    cout << "ifCommand: ";
    cout << varName1 << endl;
    cout << "ifCommand: ";
    cout << varName2 << endl;
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
            map<string,Command*>::iterator end = ParseCommand::getInstance()->getMap().end();
            if (ParseCommand::getInstance()->getMap().find(*it) != end) {
                Command* tempC = nullptr;
                tempC = ParseCommand::getInstance()->getMap().find(*it)->second;
                int i = tempC->execute(++it);
                //move the iterator i steps forward
                while (i > 0) {
                    it++;
                    i--;
                    commandCounter++;
                }
                if (i == 0){
                    commandCounter++;
                }
                //current string isn't a commands but a variable, we'll update it
            } else {
                Command* setVariable = new SetVariableCommand();
                int i = setVariable->execute(it);
                //move the iterator i steps forward
                while (i > 0) {
                    it++;
                    i--;
                    commandCounter++;
                }
            }
            ++it;
            commandCounter++;
        }
    }
    if (!ifCorrect) {
        while (*it != "}") {
            ++it;
            commandCounter++;
        }
    }
    return commandCounter + 4;
}