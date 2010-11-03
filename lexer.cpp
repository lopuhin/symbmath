#include <iostream>
#include <regex.h>

using namespace std;

typedef enum {VARIABLE, NUMBER, LPAREN, RPAREN,
	      PLUS, MINUS, MULTIPLY, DIVIDE, POWER} Symbol;
	      

int lexer(const char* input, Symbol* result, char** result_strings) {
  // return number of tokens. Fill result with tokens,
  // and result_strings with corresponding strings
  const char pattern[] = "([_a-zA-Z]+[_a-zA-Z0-9]*|[0-9]+|\\+|\\-|\\*|\\^|\\(|\\))";
  regex_t re;
  regmatch_t pm;
  int error;
  if (regcomp(&re, pattern, REG_EXTENDED) != 0) {
    return 0; // error
  }
  // this call to regexec() finds the first match on the line
  error = regexec(&re, input, 1, &pm, 0);
  int pos = 0, token_index = 0, match_len;
  Symbol token;
  char token_start;
  while (error == 0) {  // while matches found
    // substring found between pm.rm_so and pm.rm_eo
    // this call to regexec() finds the next match
    token_start = input[pos + pm.rm_so];
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
    match_len = pm.rm_eo - pm.rm_so;
    char* s = new char[match_len + 1];
    for(int i = pm.rm_so; i <= pm.rm_eo; i++ )
      s[i - pm.rm_so] = input[pos + i];
    s[match_len] = 0;
    result_strings[token_index] = s;
    result[token_index] = token;
    token_index++;
    pos += pm.rm_eo;
    error = regexec(&re, input + pos, 1, &pm, REG_NOTBOL);
  }
  return token_index;
}

const char* token_to_str(Symbol token) {
  switch(token) {
  case LPAREN: return "LPAREN";
  case RPAREN: return "RPAREN";
  case PLUS: return "PLUS";
  case MINUS: return "MINUS";
  case MULTIPLY: return "MULTIPLY";
  case DIVIDE: return "DIVIDE";
  case POWER: return "POWER";
  case VARIABLE: return "VARIABLE";
  case NUMBER: return "NUMBER";
  }
}

void test_lexer(const char* input) {
  Symbol result[100];
  char* strings[100];
  int n_tokens = lexer(input, result, strings);
  for(int i = 0; i < n_tokens; i++) {
    cout << token_to_str(result[i]) << ": " << strings[i] << endl;
  }
  cout << endl;
}
  

/*
int main() {
  test_lexer("-12*35 + (sin(45) - 93*a + a_1_1 - _var7)^3");
  return 0;
}
*/
