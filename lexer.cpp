#include <iostream>
#include <regex.h>

using namespace std;

int lexer(const char* pattern, const char* input) {
  regex_t re;
  regmatch_t pm;
  int error;
  if (regcomp(&re, pattern, REG_EXTENDED) != 0) {
    cout << "error" << endl;
    return 0; // error
  }
  // this call to regexec() finds the first match on the line
  error = regexec(&re, input, 1, &pm, 0);
  while (error == 0) {  // while matches found
    // substring found between pm.rm_so and pm.rm_eo
    // this call to regexec() finds the next match
    cout << "match at " << pm.rm_so << " " << pm.rm_eo << endl;
    error = regexec(&re, input + pm.rm_eo, 1, &pm, REG_NOTBOL);
  }
}

int main() {
  lexer("[0-9]+", "123 + 45");
  cout << "fini" << endl;
  return 0;
}
