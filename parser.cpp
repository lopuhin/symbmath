#include <stdlib.h>
#include <stdio.h>
#include "lexer.cpp"

#ifndef TREE_CPP
#include "tree.cpp"
#endif

int pos;

Symbol nextsym(Symbol* tokens) {
  return tokens[pos];
}

Symbol getsym(Symbol* tokens) {
  return tokens[pos++];
}

char* getstring(char** strings) {
  return strings[pos++];
}

void assert(Symbol s, Symbol expected) {
  if (s != expected) {
    cout << "Error: expected " << token_to_str(expected)
	 << " got " << token_to_str(s) << endl;
    //exit(-1); // TODO - raise Exception
  }
}

Tree* expression(Symbol* tokens, char** strings);

Tree* factor(Symbol* tokens, char** strings) {
  Symbol s = nextsym(tokens);
  if (s == NUMBER || s == VARIABLE) {
    return new Tree(getstring(strings));
  } else {
    assert(getsym(tokens), LPAREN);
    Tree* expr = expression(tokens, strings);
    assert(getsym(tokens), RPAREN);
    return expr;
  }
}

Tree* term(Symbol* tokens, char** strings) {
  Tree* f1 = factor(tokens, strings);
  while (nextsym(tokens) == DIVIDE || nextsym(tokens) == MULTIPLY) {
    char* op = getstring(strings);
    f1 = new Tree(f1, op, factor(tokens, strings));
  }
  return f1;
}

Tree* expression(Symbol* tokens, char** strings) {
  Tree* t1 = term(tokens, strings);
  while (nextsym(tokens) == PLUS || nextsym(tokens) == MINUS) {
    char* op = getstring(strings);
    t1 = new Tree(t1, op, term(tokens, strings));
  }
  return t1;
}

Tree* parse(const char* input) {
  int max_tokens = strlen(input);
  Symbol* tokens = new Symbol[max_tokens];
  char** strings = new char*[max_tokens];
  int n_tokens = lexer(input, tokens, strings);
  pos = 0;
  Tree* expr = expression(tokens, strings);
  if (pos != n_tokens)
    cout << "parsed only partly: " << pos << " " << n_tokens << endl;
  return expr;
}


/*int main() {
  parse("1")->print();
  parse("1 + 2 * 3")->print();
  parse("1 * 2 + 3")->print();
  return 0;
}*/
