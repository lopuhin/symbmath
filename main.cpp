#include <stdlib.h>
#include <iostream>
#include "tree.cpp"
#include "diff.cpp"

using namespace std;

const int n_test_expr = 4;

Tree** get_test_expressions() {
  Tree** expressions = new Tree*[n_test_expr];
  expressions[0] = new Tree(new Tree("2"), "+", new Tree("x"));
  expressions[1] = new Tree(new Tree("x"), "*", new Tree(new Tree("4"), "+", new Tree("x")));
  expressions[2] = new Tree(new Tree("x"), "*",
			    new Tree(new Tree(new Tree("7"), "/", new Tree("x")), "-",
				     new Tree(new Tree("x"), "^", new Tree("x"))));
  expressions[3] = new Tree("-", new Tree(new Tree(new Tree("x"), "+", new Tree("7")),
					  "!"));
  return expressions;
}


void test_print_and_copy(Tree** test_expressions) {
  Tree* expr;
  cout << "print and copy test:" << endl;
  for(int i = 0; i < n_test_expr; i++) {
    expr = test_expressions[i];
    expr->print();
    cout << "copy of expression: ";
    Tree::copy(expr)->print();
  }
  cout << endl;
}


void test_diff(Tree** test_expressions) {
  Tree* expr;
  cout << "diff test:" << endl;
  for(int i = 0; i < n_test_expr; i++) {
    expr = test_expressions[i];
    expr->print();
    cout << "diff = ";
    get_diff(expr, "x")->print();
  }
  cout << endl;
}


int main() {
  Tree** test_expressions = get_test_expressions();
  test_print_and_copy(test_expressions);
  test_diff(test_expressions);
}
