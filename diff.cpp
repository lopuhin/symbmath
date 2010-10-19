// Differentiating expressions

using namespace std;


Tree* get_diff(Tree* expr, char* x) {
  // Differentiate expression (create new expression) by given x
  if (expr->left && expr->right) {
    if (!strcmp(expr->x, "+"))
      return new Tree(get_diff(expr->left, x), "+", get_diff(expr->right, x));
    if (!strcmp(expr->x, "*"))
      return new Tree(new Tree(get_diff(expr->left, x), "*", Tree::copy(expr->right)),
		      "+", new Tree(Tree::copy(expr->left), "*", get_diff(expr->right, x)));
    // TODO - more functions "/" "sin" "cos" "^"
    // TODO recognize constants?
  } else if (expr->left) {
    // TODO
    // "-", what else?
  } else if (expr->right) {
    // TODO
    // "!", what else?
  } else {
    if (!strcmp(expr->x, x)) 
      return Tree::copy(expr);
    else
      return new Tree("0");
  }
}
