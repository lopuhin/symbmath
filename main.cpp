#include <stdlib.h>
#include <iostream>
#include "tree.cpp"

using namespace std;

int main() {
  Tree* tree = new Tree(new Tree("2"), "+", new Tree("3"));
  tree->print();
  tree = new Tree(new Tree("x"), "*", new Tree(new Tree("4"), "+", new Tree("x")));
  tree->print();
  //Tree::copy(tree)->print();
  return 1;
}
