#include "commands/Commands.h"
#include "interpreter/ex1.h"
#include "lexer/Lexer.h"

int main(){
    Command* c = new ParseCommand();
    Lexer* l = new Lexer();
    l->buildLexer();
    c->parser(l->getList());
    return 0;
}
