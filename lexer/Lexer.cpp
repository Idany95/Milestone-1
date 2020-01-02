#include "Lexer.h"

void Lexer::buildLexer() {
    ifstream f("../fly.txt", ios::in);
    if (!f.is_open()) {
        cout << "can't open file";
        exit(1);
    }
    string line;
    while (getline(f, line)) {
        /*
         * just read the lines as they are from the file and put in build - a temp
         * list that helps us to build lex
         */
        this->build->push_front(line);
    }
    f.close();
    /**
     * build is a list that helps us to build the lexer (lex).
     * if an element is ready to get into the lexer (has no delemiters),
     * the program deletes it from bulid and put in lex. if an element still has
     * delimiters, it still be in bulid.
     */
    while (!this->build->empty()) {
        string line = this->build->front();
        if (ifExists(line,"=") && !ifExists(line, "==") && !ifExists(line, "!=")
            && !ifExists(line, "<=") && !ifExists(line, ">=")) {
            delimEquation(line);
            continue;
        }
        if (ifExists(line,"==") && line != "==") {
            delimCondition(line, "==");
            continue;
        }
        if (ifExists(line,"<=") && line != "<=") {
            delimCondition(line, "<=");
            continue;
        }
        if (ifExists(line,">=") && line != ">=") {
            delimCondition(line, ">=");
            continue;
        }
        if (ifExists(line,"!=") && line != "!=") {
            delimCondition(line, "!=");
            continue;
        }
        if (ifExists(line,"=") && line != "=" && !ifExists(line, "==") && !ifExists(line, "!=")
            && !ifExists(line, "<=") && !ifExists(line, ">=")) {
            delimCondition(line, "=");
            continue;
        }
        if (ifExists(line,">") && line != ">" && !ifExists(line, "->") && !ifExists(line,"=>")) {
            delimCondition(line, ">");
            continue;
        }
        if (ifExists(line,"<") && line != "<" && !ifExists(line, "<-") && !ifExists(line, "<=")) {
            delimCondition(line, "<");
            continue;
        }
        if (ifExists(line, "(") && !ifExists(line,"=")) {
            delimiterOpenParentheses(line);
            continue;
        }
        if (ifExists(line, ")") && !ifExists(line,"=")) {
            delimiterCloseParentheses(line);
            continue;
        }
        if (ifExists(line, ",")) {
            delimiterComma(line);
            continue;
        }
        if (ifExists(line, " ") && !ifExists(line, "\t") && !ifExists(line, "\"")) {
            delimiterSpace(line);
            continue;
        }
        // because we push -> to lex and we dont want to tuch it
        if (ifExists(line, "->") && !line.compare("->")==0) {
            delimiterArrowRight(line);
            continue;
        }
        // because we push <- to lex and we dont want to tuch it
        if (ifExists(line, "<-") && !line.compare("<-")==0) {
            delimiterArrowLeft(line);
            continue;
        }
        if (ifExists(line, "\t")) {
            delimiterTab(line);
            continue;
        }
        // the empty string has no delimiters but we shouldn't put it in the lexer
        if (line != "") {
            this->lex->push_front(line);
        }
        // checks if build isn't empty so we can remove a line from it
        if (!this->build->empty()) {
            this->build->pop_front();
        }
    }
    /**CAN BE ADDED TO THE CODE JUST TO PRINT THE LEXER
    while (!this->lex.empty()) {
        cout << this->lex.front() << endl;
        this->lex.pop_front();
    }*/
}
void Lexer::delimEquation(string s) {
    string delim = "=";
    string begin = "";
    string left = "";
    auto start = 0U;
    auto end = s.find(delim);
    begin = s.substr(start, end);
    left = s.substr(end+1, s.length());
    this->build->pop_front();
    string newLeft = left;
    string newBegin = begin;
    if (left[0] == ' ') {
        newLeft = left.substr(1, left.length());
        this->lex->push_front(newLeft);
    }
    else {
        this->lex->push_front(newLeft);
    }
    this->lex->push_front("=");
    if (ifExists(begin, "\t")) {
        newBegin = begin.substr(1, begin.length());
        this->lex->push_front(newBegin);
    }
    else if (ifExists(begin, " ")) {
        if (ifExists(begin, "var")) {
            newBegin = begin.substr(3, begin.length());
            std::string::iterator end_pos = std::remove(newBegin.begin(), newBegin.end(), ' ');
            newBegin.erase(end_pos, newBegin.end());
            this->lex->push_front(newBegin);
            this->lex->push_front("var");
        }
        else {
            std::string::iterator end_pos = std::remove(newBegin.begin(), newBegin.end(), ' ');
            newBegin.erase(end_pos, newBegin.end());
            this->lex->push_front(newBegin);
        }
    }
    else {
        this->lex->push_front(newBegin);
    }
}
void Lexer::delimCondition(string s, string con) {
    string begin = "";
    string left = "";
    auto start = 0U;
    auto end = s.find(con);
    begin = s.substr(start, end);
    left = s.substr(end+con.length(), s.length());
    this->build->pop_front();
    this->build->push_front(begin);
    this->build->push_front(con);
    this->build->push_front(left);
}
void Lexer::delimiterOpenParentheses(string s) {
    string delim = "(";
    string begin = "";
    string left = "";
    auto start = 0U;
    auto end = s.find(delim);
    begin = s.substr(start, end);
    left = s.substr(end+1, s.length());
    this -> build->pop_front();
    this -> build->push_front(begin);
    this -> build->push_front(left);
}
void Lexer::delimiterTab(string s) {
    string left = "";
    left = s.substr(1);
    this -> build->pop_front();
    this->build->push_front(left);
}
void Lexer::delimiterCloseParentheses(string s) {
    string delim = ")";
    string begin = "";
    string left = "";
    auto start = 0U;
    auto end = s.find(delim);
    begin = s.substr(start, end);
    left = s.substr(end+1, s.length());
    this -> build->pop_front();
    this -> build->push_front(begin);
    this -> build->push_front(left);
}

void Lexer::delimiterSpace(string s) {
    string delim = " ";
    string begin = "";
    string left = "";
    auto start = 0U;
    auto end = s.find(delim);
    begin = s.substr(start, end);
    left = s.substr(end+1, s.length());
    this -> build->pop_front();
    if (ifExists(left, "=")) {
        auto startnew = 0U;
        auto endnew = left.find(" ");
        string beginnew = left.substr(startnew, endnew);
        string leftnew = left.substr(endnew+1, s.length());
        this->lex->push_front(leftnew);
        this->lex->push_front(beginnew);
        this->lex->push_front(begin);
    }
    else {
        this -> build->push_front(begin);
        this -> build->push_front(left);

    }
}
void Lexer::delimiterComma(string s) {
    string delim = ",";
    string begin = "";
    string left = "";
    auto start = 0U;
    auto end = s.find(delim);
    begin = s.substr(start, end);
    left = s.substr(end+1, s.length());
    this -> build->pop_front();
    this -> build->push_front(begin);
    this -> build->push_front(left);
}

void Lexer::delimiterArrowRight(string s) {
    string delim = "->";
    string begin = "";
    string arrow = delim;
    string left = "";
    auto start = 0U;
    auto end = s.find(delim);
    begin = s.substr(start, end);
    left = s.substr(end + delim.length(), s.length());
    this -> build->pop_front();
    this -> build->push_front(begin);
    this->build->push_front(arrow);
    this -> build->push_front(left);
}

void Lexer::delimiterArrowLeft(string s) {
    string delim = "<-";
    string begin = "";
    string arrow = delim;
    string left = "";
    auto start = 0U;
    auto end = s.find(delim);
    begin = s.substr(start, end);
    left = s.substr(end + delim.length(), s.length());
    this -> build->pop_front();
    this -> build->push_front(begin);
    this->build->push_front(arrow);
    this -> build->push_front(left);
}
bool Lexer ::ifExists(string s, string c) {
    /**
     * checks if c is a substring of s
     */
    if (s.find(c) != string::npos) {
        return true;
    }
    return false;
}

list<string>* Lexer::getList() {
    return this->lex;
}