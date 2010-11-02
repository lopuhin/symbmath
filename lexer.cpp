#include <iostream>
#include <regex.h>

using namespace std;

typedef enum {VARIABLE, NUMBER, LPAREN, RPAREN,
	      PLUS, MINUS, MULTIPLY, DIVIDE, POWER} Symbol;
	      

int lexer(const char* input, Symbol* result) {
  const char pattern[] = "([_a-zA-Z]+[_a-zA-Z0-9]*|[0-9]+|\\+|\\-|\\*|\\^|\\(|\\))";
  regex_t re;
  regmatch_t pm;
  int error;
  if (regcomp(&re, pattern, REG_EXTENDED) != 0) {
    cout << "error" << endl;
    return 0; // error
  }
  // this call to regexec() finds the first match on the line
  error = regexec(&re, input, 1, &pm, 0);
  int pos = 0, token_index = 0;
  Symbol token;
  char token_start;
  while (error == 0) {  // while matches found
    // substring found between pm.rm_so and pm.rm_eo
    // this call to regexec() finds the next match
    token_start = input[pos + pm.rm_so];
    cout << "match at " << pos + pm.rm_so << " " << pos + pm.rm_eo
	 << " " << token_start << endl;
    switch(token_start) {
    case '(': token = LPAREN; break;
    case ')': token = RPAREN; break;
    case '-': token = MINUS; break;
    case '+': token = PLUS; break;
    case '/': token = DIVIDE; break;
    case '*': token = MULTIPLY; break;
    case '^': token = POWER; break;
    default:
      if (token_start >= '0' && token_start <= '9')
	token = NUMBER;
      else
	token = VARIABLE;
    }
    result[token_index++] = token;
    pos += pm.rm_eo;
    error = regexec(&re, input + pos, 1, &pm, REG_NOTBOL);
  }
  return token_index;
}

void test_lexer(const char* input) {
  Symbol result[100];
  int n_tokens = lexer(input, result);
  for(int i = 0; i < n_tokens; i++) {
    switch(result[i]) {
    case LPAREN: cout << "LPAREN"; break;
    case RPAREN: cout << "RPAREN"; break;
    case PLUS: cout << "PLUS"; break;
    case MINUS: cout << "MINUS"; break;
    case MULTIPLY: cout << "MULTIPLY"; break;
    case DIVIDE: cout << "DIVIDE"; break;
    case POWER: cout << "POWER"; break;
    case VARIABLE: cout << "VARIABLE"; break;
    case NUMBER: cout << "NUMBER"; break;
    }
    cout << " ";
  }
  cout << endl;
}
  

int main() {
  test_lexer("-12*35 + (sin(45) - 93*a + a_1_1 - _var7)^3");
  return 0;
}
