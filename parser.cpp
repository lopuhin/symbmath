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

void assert(Symbol s, Symbol expected) {
  // TODO - raise Exception
}

void expression(Symbol* tokens, char** strings);

void factor(Symbol* tokens, char** strings) {
  Symbol s = nextsym(tokens);
  if (s == NUMBER || s == VARIABLE) {
    getsym(tokens);
    
  } else {
    assert(s, LPAREN);
    expression(tokens, strings);
    assert(getsym(tokens), RPAREN);
  }
}

void term(Symbol* tokens, char** strings) {
  factor(tokens, strings);
  Symbol s = nextsym(tokens);
  if (s == DIVIDE || s == MULTIPLY) {
    getsym(tokens);
    factor(tokens, strings);
  }
}

void expression(Symbol* tokens, char** strings) {
  term(tokens, strings);
  Symbol s = nextsym(tokens);
  if (s == PLUS || s == MINUS) {
    getsym(tokens);
    term(tokens, strings);
  }
}

void parse(const char* input) {
  int max_tokens = strlen(input);
  Symbol* tokens = new Symbol[max_tokens];
  char** strings = new char*[max_tokens];
  int n_tokens = lexer(input, tokens, strings);
  pos = 0;
  expression(tokens, strings);
  cout << endl << pos << " " << n_tokens << endl;
}


int main() {
  parse("1 + 2 * 3");
  parse("1 * 2 + 3");
  return 0;
}
