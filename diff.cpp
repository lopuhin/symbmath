// Differentiating expressions

using namespace std;


Tree* get_diff(Tree* expr, char* var) {
  // Differentiate expression (create new expression) by given var

  // TODO recognize constant expressions!
  if (expr->left && expr->right) {
    if (!strcmp(expr->x, "+")) // (a + b)' = a' + b'
      return new Tree(get_diff(expr->left, var), "+", get_diff(expr->right, var));
    if (!strcmp(expr->x, "*")) // (a * b)' = a' * b + a * b'
      return new Tree(new Tree(get_diff(expr->left, var),
			       "*", Tree::copy(expr->right)),
		      "+", new Tree(Tree::copy(expr->left),
				    "*", get_diff(expr->right, var)));
    // TODO  "/" "^", "log"
  } else if (expr->right) {
    if (!strcmp(expr->x, "-")) // (-a)' = - (a)'
      return new Tree("-", get_diff(expr->right, var));
    if (!strcmp(expr->x, "sin")) // (sin(a))' = cos(a') * a' ???
      return new Tree(new Tree("cos", get_diff(expr->right, var)),
		      "*", get_diff(expr->right, var));
    // TODO  "sin", "exp"
  } else if (expr->left) {
    // TODO
    // "!" with constants, what else?
  } else {
    if (!strcmp(expr->x, var))
      return new Tree("1");
    else
      return new Tree("0");
  }
}
