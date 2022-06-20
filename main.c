#include "bestline.h"
#include "env.h"
#include "interpreter.h"
#include "parser.h"
#include "syntax.h"
#include "utils.h"
#include "mem.h"

#define MAX_SEXPRS 10

expr *func_plus(int n, expr *args[]) {
  int i;
  expr *result;

  if (n < 2) {
    return NULL;
  }

  result = alloc();
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

  result = alloc();
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

  f_plus = alloc();
  f_plus->tag = NATIVE;
  f_plus->c.f = &func_plus;

  f_eq = alloc();
  f_eq->tag = NATIVE;
  f_eq->c.f = &func_eq;

  env->frame = f;

  insert(env, "+", f_plus);
  insert(env, "eq", f_eq);
}

int main(void) {
  env env;
  frame f;
  char *line;
  expr *e[MAX_SEXPRS];
  expr *result;
  init_mem();
  make_default_env(&env, &f);
  f.next = NULL;

  while ((line = bestline("lisp> ")) != NULL) {
    if (line[0] != '\0') {
      /* bestlineHistoryAdd(line); /\* Add to the history. *\/ */
      /* bestlineHistorySave("history.txt"); /\* Save the history on disk. *\/
       */
      int len = strlen(line);
      int i = 0;
      int j = 0;
      while (i < len) {
        e[j] = parse_sexpr(line, len, &i);

        printf("Expr: ");
        print_sexpr(e[j], 1, 0);
        printf("\n");

        /* traverse(e[j]); */
        result = eval(&env, e[j]);

        print_sexpr(result, 1, 0);
        printf("\n");
        j++;
      }
    }
    free(line);

    if (memused >= 0.8 * MEMSIZE) {
      printf("Memory almost full (%lu/%lu bytes); running gc\n", memused * sizeof(expr), MEMSIZE * sizeof(expr));
      gc(&env);
      printf("Usage after gc: %lu\n", memused * sizeof(expr));
    }
  }

  return 0;
}
