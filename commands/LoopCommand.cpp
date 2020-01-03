#include "Commands.h"
#include "../interpreter/ex1.h"

int LoopCommand::execute(list<string>::iterator it) {
    commandCounter = 0;
    string varName1 = *it;
    string con = *(++it);
    string varName2 = *(++it);
    string openScope = *(++it);
    bool ifCondition = false;
    ifCondition = condition(varName1, con, varName2);
    ++it;
    if (!ifCondition) {
        cout << "i didn't went in loop" << endl;
        while (*it != "}") {
            it++;
            commandCounter++;
        }
    }
    while (ifCondition) {
        if(*it == "}") {
            ifCondition = condition(varName1, con, varName2);
            continue;
        }
        map<string,Command*>::iterator end = ParseCommand::getInstance()->getMap().end();
        //if current string is a commands
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
            if (i == 0) {
                commandCounter++;
            }
            //current string isn't a commands but a variable, we'll update it
        } else {
            Command* setVariable = new SetVariableCommand();
            //cout << "execute setVariable " << *it << endl;
            int i = setVariable->execute(it);
            //move the iterator i steps forward
            while (i > 0) {
                it++;
                i--;
                commandCounter++;
            }
        }
        it++;
        commandCounter++;
        if (*it == "}") {
            ifCondition = condition(varName1, con, varName2);
            if (ifCondition) {
                for (int i=0; i<commandCounter; i++) {
                    it--;
                }
                int temp = commandCounter;
                for (int i=0; i<temp; i++) {
                    commandCounter--;
                }
            }
        }
    }
    return commandCounter + 4;
}
bool LoopCommand::condition(string var1, string con, string var2) {
    /**cout << "loopCommand: ";
    cout << var1 << endl;
    cout << "loopCommand: ";
    cout << var2 << endl;**/
    double varVal1 = this->calculateValue(var1);
    double varVal2 = this->calculateValue(var2);
    if (con.compare("==") == 0) {
        if (varVal1 == varVal2) {
            return true;
        }
    }
    if (con.compare("!=") == 0) {
        if (varVal1 != varVal2) {
            return true;
        }
    }
    if (con.compare(">=") == 0) {
        if (varVal1 >= varVal2) {
            return true;
        }
    }
    if (con.compare("<=") == 0) {
        if (varVal1 <= varVal2) {
            return true;
        }
    }
    if (con.compare(">") == 0) {
        if (varVal1 > varVal2) {
            return true;
        }
    }
    if (con.compare("<") == 0) {
        if (varVal1 < varVal2) {
            return true;
        }
    }
    return false;
}