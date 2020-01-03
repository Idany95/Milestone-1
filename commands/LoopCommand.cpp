#include "Commands.h"
#include "../interpreter/ex1.h"

/**
 * Execute the command
 * @param it the iterator
 * @return the number of jumps for the outside loop
 */
int LoopCommand::execute(list<string>::iterator it) {
    // initialize the global command counter to zero
    commandCounter = 0;
    // four first tokens of the condition
    string varName1 = *it;
    string con = *(++it);
    string varName2 = *(++it);
    string openScope = *(++it);
    // checks if the condition is true (initialize to false)
    bool ifCondition = false;
    /**
     * Case that the condition is false at the first iteration
     */
    ifCondition = condition(varName1, con, varName2);
    ++it;
    if (!ifCondition) {
        while (*it != "}") {
            it++;
            commandCounter++;
        }
    }
    /**
     * Case true at the first iteration
     */
    while (ifCondition) {
        // case of empty loop
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
            // case sleep and print
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
        // go to the next line
        it++;
        commandCounter++;
        /**
         * if the iteration ended, check the condition again and takes the iterator to
         * the begining of the loop
         */
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

/**
 * A function that checks the condition
 * @param var1 the first operand
 * @param con the condition
 * @param var2 the second operand
 * @return true if the condition is true, false otherwise
 */
bool LoopCommand::condition(string var1, string con, string var2) {
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