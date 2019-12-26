
#include "Commands.h"
#include "../interpreter/ex1.h"

void ParseCommand::parser(list<string> LexeredCommandsList) {
    //Initialize commands map
    this->commandMap.insert({"openDataServer",new OpenServerCommand()});
    this->commandMap.insert({"connectControlClient",new ConnectCommand()});
    this->commandMap.insert({"var",DefineVarCommand::getInstance()});
    this->commandMap.insert({"if",new IfCommand()});
    this->commandMap.insert({"while",new LoopCommand()});
    this->commandMap.insert({"Print",new PrintCommand()});
    this->commandMap.insert({"Sleep",new SleepCommand()});
    //...ADD ALL COMMANDS
    list<string>::iterator it;
    for(it = LexeredCommandsList.begin(); it!=LexeredCommandsList.end(); ++it) {
        Command* tempC = nullptr;
        tempC = this->commandMap.find(*it)->second;
        //if current string is a commands
        if (this->commandMap.find(*it) != this->commandMap.end()) {
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
    }//end of for loop
}

bool Command::checkIfNumber(string s) {
    if(s[0] == '"') {
        return false;
    }
    return true;
};

double Command::calculateValue(string strValue){
    DefineVarCommand* tempCommand = (DefineVarCommand*)(ParseCommand::getInstance()->getMap().find("var")->second);
    vector <Var*> vars;
    Interpreter* i = new Interpreter();
    //inserting all Variables to a vector
    map<string, int>::iterator j;
    for (auto const& x: tempCommand->getVarSymbolTable()){
        vars.push_back(new Var(x.first, x.second->getValue()));
    }
    i->setVars(vars);
    Expression* e = i->interpret(strValue);
    return e->calculate();
}

double Variable::getValue() {
    return this->value;
}

string Variable::getDirection() {
    return this->direction;
}

void Variable::setValue(double newValue) {
    this->value = newValue;
}

Variable::Variable(string newDirection, string newSim) {
    this->direction = newDirection;
    this->sim = newSim;
}

int ParseCommand::execute(list<string>::iterator it) {
    return 0;
}