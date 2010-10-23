// Simplify expressions


using namespace std;


bool leaf_with_value(Tree* expr, char* value) {
  return !expr->left && !expr->right && !strcmp(expr->x, value);
}

Tree* simplify(Tree* expr) {
  // return simplified copy of expr
  char* new_x = new char[strlen(expr->x) + 1];
  strcpy(new_x, expr->x);
  if (!expr->left && !expr->right) {
    return Tree::copy(expr);
  } else if (expr->left && expr->right) {
    Tree* simp_expr = new Tree(simplify(expr->left), new_x, simplify(expr->right));
    if (!strcmp(simp_expr->x, "*")) {
      if (leaf_with_value(simp_expr->left, "1"))
	return Tree::copy(simp_expr->right);
      if (leaf_with_value(simp_expr->left, "0"))
	return new Tree("0");
      if (leaf_with_value(simp_expr->right, "1"))
	return Tree::copy(simp_expr->left);
      if (leaf_with_value(simp_expr->right, "0"))
	return new Tree("0");
    } else if (!strcmp(simp_expr->x, "+")) {
      if (leaf_with_value(simp_expr->left, "0"))
	return Tree::copy(simp_expr->right);
      if (leaf_with_value(simp_expr->right, "0"))
	return Tree::copy(simp_expr->left);
    }
    return simp_expr;
  } else if (expr->left) {
    return new Tree(simplify(expr->left), new_x);
  } else if (expr->right) {
    return new Tree(new_x, simplify(expr->right));
  }
}
