#include <stdlib.h>
#include <stdio.h>
#include "lexer.cpp"
#include "tree.cpp"

int pos;

Symbol nextsym(Symbol* tokens) {
  return tokens[pos];
}

Symbol getsym(Symbol* tokens) {
  cout << token_to_str(tokens[pos]) << " ";
  return tokens[pos++];
}

char* getstring(char** strings) {
  cout << strings[pos] << " ";
  return strings[pos++];
}

void assert(Symbol s, Symbol expected) {
  if (s != expected)
    cout << "Error: expected " << token_to_str(expected)
	 << " got " << token_to_str(s) << endl;
    exit(-1);
  // TODO - raise Exception
}

Tree* expression(Symbol* tokens, char** strings);

Tree* factor(Symbol* tokens, char** strings) {
  Symbol s = nextsym(tokens);
  if (s == NUMBER || s == VARIABLE) {
    return new Tree(getstring(strings));
  } else {
    assert(s, LPAREN);
    Tree* expr = expression(tokens, strings);
    assert(getsym(tokens), RPAREN);
    return expr;
  }
}

Tree* term(Symbol* tokens, char** strings) {
  Tree* f1 = factor(tokens, strings);
  Symbol s = nextsym(tokens);
  if (s == DIVIDE || s == MULTIPLY) {
    char* op = getstring(strings);
    return new Tree(f1, op, factor(tokens, strings));
  }
  return f1;
}

Tree* expression(Symbol* tokens, char** strings) {
  Tree* t1 = term(tokens, strings);
  Symbol s = nextsym(tokens);
  if (s == PLUS || s == MINUS) {
    char* op = getstring(strings);
    return new Tree(t1, op, term(tokens, strings));
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
  cout << endl << pos << " " << n_tokens << endl;
  if (pos == n_tokens)
    return expr;
  return NULL;
}


int main() {
  parse("1")->print();
  parse("1 + 2 * 3")->print();
  parse("1 * 2 + 3")->print();
  return 0;
}
