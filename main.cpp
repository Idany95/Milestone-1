#include "commands/Commands.h"
#include "interpreter/ex1.h"
#include "lexer/Lexer.h"

int main(){
    Lexer* l = new Lexer();
    l->buildLexer();
    ParseCommand::getInstance()->parser(l->getList());
    return 0;
}