#include <stdlib.h>
#include <iostream>
#include "tree.cpp"
#include "diff.cpp"

using namespace std;


void test_print_and_copy(Tree** test_expr, int n_expr) {
  Tree* expr;
  cout << "print and copy test:" << endl;
  for(int i = 0; i < n_expr; i++) {
    expr = test_expr[i];
    expr->print();
    cout << "copy of expression: ";
    Tree::copy(expr)->print();
  }
  cout << endl;
}


void test_diff(Tree** test_expr, int n_expr) {
  Tree* expr;
  cout << "diff test:" << endl;
  for(int i = 0; i < n_expr; i++) {
    expr = test_expr[i];
    expr->print();
    cout << "diff = ";
    get_diff(expr, "x")->print();
  }
  cout << endl;
}


void test() {
    // test everything
  Tree** test_expr = new Tree*[100];
  int i = 0;
  test_expr[i++] = new Tree(new Tree("2"), "+", new Tree("x"));
  test_expr[i++] = new Tree(new Tree("x"), "*", new Tree("x"));
  test_expr[i++] = new Tree(new Tree("x"), "*",
			    new Tree(new Tree("4"), "+", new Tree("x")));
  test_expr[i++] = new Tree("-", new Tree(new Tree("x"), "*", new Tree("7")));
  test_expr[i++] = new Tree("sin", new Tree(new Tree("x"),
					    "*", new Tree("x")));
  int n_diff_tests = i; // end of diff tests
  test_expr[i++] = new Tree(new Tree("x"),
			    "*", new Tree(new Tree(new Tree("7"), "/", new Tree("x")),
					  "-", new Tree(new Tree("x"),
							"^", new Tree("x"))));
  test_expr[i++] = new Tree("-", new Tree(new Tree(new Tree("x"),
						   "+", new Tree("7")),
					"!"));
  int n_pc_tests = i; // end of print and copy tests
  
  test_print_and_copy(test_expr, n_pc_tests);
  test_diff(test_expr, n_diff_tests);
}


int main() {
  test();
}
