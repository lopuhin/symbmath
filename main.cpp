#include <stdlib.h>
#include <iostream>
#include "tree.cpp"

using namespace std;

void test_print_and_copy() {
  Tree* tree = new Tree(new Tree("2"), "+", new Tree("3"));
  tree->print();
  tree = new Tree(new Tree("x"), "*", new Tree(new Tree("4"), "+", new Tree("x")));
  tree->print();
  tree = new Tree(new Tree("x"), "*",
		  new Tree(new Tree(new Tree("7"), "/", new Tree("x")), "-",
			   new Tree(new Tree("x"), "^", new Tree("x"))));
  tree->print();
  cout << "copy of tree: ";
  Tree::copy(tree)->print();
  tree = new Tree("-", new Tree(new Tree(new Tree("x"), "+", new Tree("7")), "!"));
  tree->print();
  cout << "copy of tree: ";
  Tree::copy(tree)->print();
}

int main() {
  test_print_and_copy();
}
