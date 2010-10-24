#include <stdlib.h>
#include <iostream>
#include "tree.cpp"
#include "diff.cpp"
#include "simplify.cpp"

using namespace std;


bool test_print_copy_simpl(Tree** test_expr, int n_expr) {
  // Проверяем печать, копирование и упращение
  Tree* expr;
  cout << "print, copy and simpl test:" << endl;
  for(int i = 0; i < n_expr; i++) {
    expr = test_expr[i];
    expr->print();
    Tree* copy = Tree::copy(expr);
    cout << "copy of expression: ";
    copy->print();
    if (!copy->equal_to(expr)) {
      cout << "not equal_to" << endl;
      return false;
    }
    if (copy->n_nodes() != expr->n_nodes()) {
      cout << "n_nodes not equal" << endl;
      return false;
    }
    cout << "simplification of expression: ";
    Tree* simpl = simplify(expr);
    simpl->print();
    cout << "Original expr: " << expr->n_nodes() << " nodes, simplified "
	 << simpl->n_nodes() << " nodes" << endl;
    cout << endl;
  }
  cout << endl;
  return true;
}


bool test_diff(Tree** test_expr, int n_expr) {
  Tree* expr;
  cout << "diff test:" << endl;
  for(int i = 0; i < n_expr; i++) {
    expr = test_expr[i];
    expr->print();
    cout << "diff = ";
    simplify(get_diff(expr, "x"))->print();
    cout << endl;
  }
  cout << endl;
  return true;
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
  test_expr[i++] = new Tree(new Tree(new Tree("x"),
				     "+", new Tree(new Tree("x"), "*", new Tree("7"))),
			    "+", new Tree(new Tree("x"), "*", new Tree("5"))); 
  test_expr[i++] = new Tree(new Tree(new Tree("x"),
				     "*", new Tree(new Tree("x"), "^", new Tree("7"))),
			    "*", new Tree(new Tree("x"), "^", new Tree("5"))); 
  test_expr[i++] = new Tree(new Tree("x"),
			    "*", new Tree(new Tree(new Tree("7"), "/", new Tree("x")),
					  "-", new Tree(new Tree("x"),
							"^", new Tree("x"))));
  test_expr[i++] = new Tree("-", new Tree(new Tree(new Tree("x"),
						   "+", new Tree("7")),
					"!"));
  int n_pc_tests = i; // end of print and copy tests
  
  if (test_print_copy_simpl(test_expr, n_pc_tests) &&
      test_diff(test_expr, n_diff_tests)) {
    cout << "All tests passed"<< endl;
  } else {
    cout << "Error" << endl;
  }
  
}


int main() {
  test();
}
