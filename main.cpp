#include "ex3.h"
#include "interpreter/ex1.h"
#include "lexer/Lexer.h"

int main(){
    Command* c = new Command();
    //*Here goes the lexer*
    Lexer* l = new Lexer();
    l->buildLexer();
    c->parser(l->getList());
    return 0;
}
void Command::parser(list<string> LexeredCommandsList) {
    //Initialize command map
    commandMap.insert({"OpenDataServer",new OpenServerCommand()});
    commandMap.insert({"ConnectControlClient",new ConnectCommand()});
    commandMap.insert({"var",new DefineVarCommand()});
    //...ADD ALL COMMANDS

    list<string>::iterator it;
    for(it = LexeredCommandsList.begin(); it!=LexeredCommandsList.end(); ++it) {
        Command* c = this->commandMap.find(*it)->second;
        //if current string is a command
        if (c!= NULL) {
            int i = c->execute(++it);
            //move the iterator i steps forward
            while (i > 0) {
                it++;
                i--;
            }
        //current string isn't a command but a variable, we'll update it
        } else {
            DefineVarCommand* tempCommand = (DefineVarCommand*)(this->commandMap.find("var")->second);
            string varName = *it;
            string strValue = *(++(++it));
            double value;
            value = calculateValue(strValue);
            //find varSymbolTable on "DefineVarCommand" and update variable's value
            tempCommand->getVarSymbolTable().find(varName)->second->setValue(value);
        }
    }//end of for loop
}

int OpenServerCommand::execute(list<string>::iterator it) {

}

int DefineVarCommand::execute(list<string>::iterator it) {
    string varName = *it;
    string direction = *(++it);
    string simPath = *(++(++it));
    //inserting to Variable Symbol Table
    this->varSymbolTable.insert({varName, new Variable(direction, simPath)});
    //inserting to Simulator Symbol Table
    this->simSymbolTable.insert({simPath,this->varSymbolTable.find(varName)->second});
    //we return 3, cause we went over 3 items in the list
    return 3;
}

map<string,Variable*> DefineVarCommand::getVarSymbolTable() {
    return this->varSymbolTable;
}

double Variable::getValue() {
    return this->value;
}

void Variable::setValue(double newValue) {
    this->value = newValue;
}

bool Command::checkIfNumber(string s) {
    if(s[0] == '"') {
        return false;
    }
    return true;
};
double Command::calculateValue(string strValue){
    DefineVarCommand* tempCommand = (DefineVarCommand*)(this->commandMap.find("var")->second);
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