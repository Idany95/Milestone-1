#include "Commands.h"
#include "../interpreter/ex1.h"

/**
 * Execute the command
 * @param it the iterator
 * @return the number of jumps for the outside loop
 */
int IfCommand::execute(list<string>::iterator it) {
    // checks if the condition is true (initialize to false)
    bool ifCorrect = false;
    // four first tokens of the condition
    string varName1 = *it;
    string condition = *(++it);
    string varName2 = *(++it);
    string openScope = *(++it);
    // calculates the variables of the condition
    double varVal1 = this->calculateValue(varName1);
    double varVal2 = this->calculateValue(varName2);
    /**
     * All the follow if statments checks the condition token and if it is same to the
     * condition checks if the condition is true, and assign the result in ifCorrect
     */
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
    // if the condition is true
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
                // cases of sleep and print
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
    // if the condition is false
    if (!ifCorrect) {
        while (*it != "}") {
            ++it;
            commandCounter++;
        }
    }
    return commandCounter + 4;
}