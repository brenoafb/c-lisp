#include "env.h"
#include "syntax.h"
#include "parser.h"
#include "interpreter.h"
#include "utils.h"

expr *func_plus(int n, expr *args[]) {
  int i;
  expr *result;

  if (n < 2) {
    return NULL;
  }

  result = malloc(sizeof(expr));
  result->tag = NUM;
  result->c.num = 0;

  for (i = 0; i < n; i++) {
    if (args[i]->tag != NUM) {
      return NULL;
    }
    result->c.num += args[i]->c.num;
  }

  return result;
}

expr *func_eq(int n, expr *args[]) {
  int i;
  expr *result;

  if (n < 2) {
    return NULL;
  }

  result = malloc(sizeof(expr));
  result->tag = ATOM;
  result->c.atom = "#t";

  for (i = 1; i < n; i++) {
    if (!eq(args[0], args[i])) {
      result->c.atom = "#f";
      return result;
    }
  }

  return result;
}

void make_default_env(env *env, frame *f) {
  expr *f_plus, *f_eq;

  f_plus = malloc(sizeof(expr));
  f_plus->tag = NATIVE;
  f_plus->c.f = &func_plus;

  f_eq = malloc(sizeof(expr));
  f_eq->tag = NATIVE;
  f_eq->c.f = &func_eq;

  env->frame = f;

  insert(env, "+", f_plus);
  insert(env, "eq", f_eq);
}

int main(void)
{
  env env;
  frame f;
  expr *e, *result;
  char *s = "(eq (+ 2 1) (+ 1 2))";
  int len = strlen(s);
  int i = 0;

  make_default_env(&env, &f);
  e = parse_sexpr(s, len, &i);
  if (e == NULL)
  {
    printf("error\n");
  }
  else
  {
    print_sexpr(e, 0, 0);
    printf("\n");

    traverse(e);
    result = eval(&env, e);

    printf("Result:\n");
    print_sexpr(result, 0, 0);
    printf("\n");
  }

  dealloc(e);

  return 0;
}
