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

  Tree(Tree* left, char* x) :
    left(left),
    x(x) {}

  Tree(char* x, Tree* right) :
    x(x),
    right(right) {}

  Tree(char* x) :
    x(x) {}

  bool is_leaf() {
    return !this->left && !this->right;
  }

  void print() {
    // print expression, represented by tree
    print_rec(false);
    cout << "\n";
  }

  void print_rec(bool brackets) {
    // Print expression, represented by tree.
    // include enclosing brackets only if brackets is true
    if (this->left || this->right) {
      if (brackets)
	cout << "(";
      bool infix = this->left && this->right;
      if (this->left) {
	this->left->print_rec(true);
	if (infix) cout << " ";
      }
      cout << this->x;
      if (this->right) {
	if (infix) cout << " ";
	this->right->print_rec(true);
      }
      if (brackets)
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
    else if (tree->left)
      return new Tree(Tree::copy(tree->left), new_x);
    else if (tree->right)
      return new Tree(new_x, Tree::copy(tree->right));
    else
      return new Tree(new_x);
  }

  bool equal_to(Tree* tree) {
    // compare this to tree
    if (strcmp(this->x, tree->x))
      return false;
    if (this->left) {
      if (!(tree->left && this->left->equal_to(tree->left)))
	return false;
    }
    if (this->right) {
      if (!(tree->right && this->right->equal_to(tree->right)))
	return false;
    }
    return true;
  }

  int n_nodes() {
    // number of nodes in tree
    int n_nodes = 1;
    if (this->left)
      n_nodes += this->left->n_nodes();
    if (this->right)
      n_nodes += this->right->n_nodes();
    return n_nodes;
  }
  
};
