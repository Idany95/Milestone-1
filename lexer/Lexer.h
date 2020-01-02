#ifndef EX3_LEXER_H
#define EX3_LEXER_H
#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
class Lexer {
private:
    // the list with all the commands
    list<string>* lex = new list<string>();
    // a temp list that helps us to build lex
    list<string>* build = new list<string>();
public :
    void buildLexer();
    void delimiterOpenParentheses(string s);
    void delimiterCloseParentheses(string s);
    void delimiterSpace(string s);
    void delimiterComma(string s);
    void delimiterArrowRight(string s);
    void delimiterArrowLeft(string s);
    void delimiterTab(string s);
    void delimCondition(string s, string con);
    void delimEquation(string s);
    bool ifExists(string c, string s);
    list<std::__cxx11::string> * getList();
};
#endif //EX3_LEXER_H