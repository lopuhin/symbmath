#include <stdio.h>
#include "lexer.cpp"
#include "tree.cpp"

int pos;

Symbol getsym(Symbol* tokens) {
  cout << token_to_str(tokens[pos]) << " ";
  return tokens[pos++];
}

void assert(Symbol s, Symbol expected) {
  // TODO - raise Exception
}

void expression(Symbol* tokens);

void factor(Symbol* tokens) {
  Symbol s = getsym(tokens);
  if (s == NUMBER || s == VARIABLE)
    ;
  else {
    assert(s, LPAREN);
    expression(tokens);
    assert(getsym(tokens), RPAREN);
  }
}

void term(Symbol* tokens) {
  factor(tokens);
  Symbol s = getsym(tokens);
  if (s == DIVIDE || s == MULTIPLY)
    factor(tokens);
}

void expression(Symbol* tokens) {
  term(tokens);
  Symbol s = getsym(tokens);
  if (s == PLUS || s == MINUS)
    term(tokens);
}

void parse(const char* input) {
  Symbol* tokens = new Symbol[strlen(input)];
  int n_tokens = lexer(input, tokens);
  pos = 0;
  expression(tokens);
  cout << pos << " " << n_tokens << endl;
}


int main() {
  parse("1 + 2 * 3");
  return 0;
}
