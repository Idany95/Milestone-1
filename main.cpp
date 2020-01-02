#include "commands/Commands.h"
#include "interpreter/ex1.h"
#include "lexer/Lexer.h"

/**
 * main function
 * @param argc with no use
 * @param argv the name of txt file
 * @return 0
 */
int main(int argc, char* argv[]){
    Lexer* l = new Lexer();
    l->buildLexer(argv[1]);
    ParseCommand::getInstance()->parser(l->getList());
    return 0;
}