#include <iostream>
#include <string.h>

// Tree, representing math expression

using namespace std;

class Tree {
public:
  Tree* left;
  Tree* right;
  char* x;

  Tree(Tree* left, char* x, Tree* right) :
    left(left),
    right(right),
    x(x) {}

  Tree(char* x) :
    x(x) {}

  void print() {
    // print expression, represented by tree
    print_rec(false);
    cout << "\n";
  }

  void print_rec(bool at_top) {
    // print expression, represented by tree. Skip brackets if at_top is true
    if (this->left && this->right) {
      if (at_top)
	cout << "(";
      this->left->print_rec(true);
      cout << " " << this->x << " ";
      this->right->print_rec(true);
      if (at_top)
	cout << ")";
    } else
      cout << this->x;
  }

  static Tree* copy(Tree* tree) {
    // copy whole tree in memory
    char* new_x = new char[strlen(tree->x) + 1];
    strcpy(new_x, tree->x);
    if (tree->left && tree->right)
      return new Tree(Tree::copy(tree->left), new_x, Tree::copy(tree->right));
    else
      return new Tree(new_x);
  }

};
