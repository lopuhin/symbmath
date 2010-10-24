#include <stdio.h>

// Simplify expressions


using namespace std;


bool leaf_with_value(Tree* expr, char* value);
bool leaf_number(Tree* expr);

Tree* simplify(Tree* expr) {
  // return simplified copy of expr
  // TODO - remove mirrored simplifications
  // TODO - calculate integer constants
  // TODO - division
  char* new_x = new char[strlen(expr->x) + 1];
  strcpy(new_x, expr->x);
  if (!expr->left && !expr->right) {
    return Tree::copy(expr);
  } else if (expr->left && expr->right) {
    Tree* simp_expr = new Tree(simplify(expr->left), new_x, simplify(expr->right));
    Tree* left = simp_expr->left;
    Tree* right = simp_expr->right;
    char* x = simp_expr->x;
    if (!strcmp(x, "*")) { // multiplication
      if (leaf_number(left) && leaf_number(right)) { // calc constant
	int value = atoi(left->x) * atoi(right->x);
	char* value_s = new char[10];
	sprintf(value_s, "%d", value);
	return new Tree(value_s); 
      }
      if (leaf_with_value(left, "1")) // 1 * x = x
	return right;
      if (leaf_with_value(left, "0")) // 0 * x = 0
	return new Tree("0");
      if (leaf_with_value(right, "1")) // x * 1 = x
	return left;
      if (leaf_with_value(right, "0")) // x * 0 = 0
	return new Tree("0");
      if (left->equal_to(right)) // x * x = x ^ 2
	return new Tree(left, "^", new Tree("2"));
      if (!strcmp(left->x, "^") && left->left->equal_to(right)) // x ^ a * x = x ^ (a + 1)
	return new Tree(right, "^", simplify(new Tree(left->right, "+", new Tree("1"))));
      if (!strcmp(right->x, "^") && right->left->equal_to(left)) // x * x ^ a = x ^ (a + 1)
	return new Tree(left, "^", simplify(new Tree(right->right, "+", new Tree("1"))));
      // TODO - and all inverse combinations...
      if (!strcmp(left->x, "^") && !strcmp(right->x, "^") &&
	  left->left->equal_to(right->left)) // x ^ a * x ^ b = x ^ (a + b)
	return new Tree(left->left, "^", simplify(new Tree(left->right, "+", right->right)));
    }
    else if (!strcmp(x, "+")) { // addition
      if (leaf_number(left) && leaf_number(right)) { // calc constant
	int value = atoi(left->x) + atoi(right->x);
	char* value_s = new char[10];
	sprintf(value_s, "%d", value);
	return new Tree(value_s); 
      }
      if (leaf_with_value(left, "0")) // 0 + x = x
	return right;
      if (leaf_with_value(right, "0")) // x + 0 = x
	return left;
      if (left->equal_to(right)) // x + x = 2 * x
	return new Tree(new Tree("2"), "*", right);
      if (!strcmp(left->x, "*") && left->left->equal_to(right)) // x * a + x = x * (a + 1)
	return new Tree(right, "*", simplify(new Tree(left->right, "+", new Tree("1"))));
      if (!strcmp(right->x, "*") && right->left->equal_to(left)) // x + x * a = x * (1 + a)
	return new Tree(left, "*", simplify(new Tree(right->right, "+", new Tree("1"))));
      // TODO - and all inverse combinations...
      if (!strcmp(left->x, "*") && !strcmp(right->x, "*") &&
	  left->left->equal_to(right->left)) // x * a + x * b = x * (a + b)
	return new Tree(left->left, "*", simplify(new Tree(left->right, "+", right->right)));
    }
    else if (!strcmp(x, "-")) { // substraction
      if (leaf_number(left) && leaf_number(right)) { // calc constant
	int value = atoi(left->x) - atoi(right->x);
	char* value_s = new char[10];
	sprintf(value_s, "%d", value);
	return new Tree(value_s); 
      }
      if (leaf_with_value(left, "0")) // 0 - x = - x
	return new Tree("-", right);
      if (leaf_with_value(right, "0")) // x - 0 = x
	return left;
      if (left->equal_to(right)) // x - x = 0
	return new Tree("0");
      if (!strcmp(left->x, "*") && left->left->equal_to(right)) // x * a - x = x * (a - 1)
	return new Tree(right, "*", simplify(new Tree(left->right, "-", new Tree("1"))));
      if (!strcmp(right->x, "*") && right->left->equal_to(left)) // x - x * a = x * (1 - a)
	return new Tree(left, "*", simplify(new Tree(new Tree("1"), "-", right->right)));
      // TODO - and all inverse combinations...
      if (!strcmp(left->x, "*") && !strcmp(right->x, "*") &&
	  left->left->equal_to(right->left)) // x * a - x * b = x * (a - b)
	return new Tree(left->left, "*", simplify(new Tree(left->right, "-", right->right)));
    }
    return simp_expr;
  } else if (expr->left) {
    return new Tree(simplify(expr->left), new_x);
  } else if (expr->right) {
    return new Tree(new_x, simplify(expr->right));
  }
}


bool is_number(char* s) {
  // s is an integer number
  char c;
  int i = 0;
  while(c = s[i++]) {
    if ((c < '0' || c > '9') && !(c == '-' && i == 1))
      return false;
  }
  return true;
}

bool leaf_number(Tree* expr) {
  // expr is a single integer
  return expr->is_leaf() && is_number(expr->x);
}

bool leaf_with_value(Tree* expr, char* value) {
  return expr->is_leaf() && !strcmp(expr->x, value);
}
