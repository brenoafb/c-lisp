#include "bestline.h"
#include "env.h"
#include "interpreter.h"
#include "mem.h"
#include "parser.h"
#include "syntax.h"
#include "utils.h"

int main(void) {
  env env;
  frame f;
  char *line;
  expr *e;
  expr *result;
  init_mem();
  make_default_env(&env, &f);
  f.next = NULL;

  bestlineHistoryLoad("history.txt");

  while ((line = bestline("lisp> ")) != NULL) {
    if (line[0] != '\0') {
      int len = strlen(line);
      int i = 0;
      while (i < len) {
        e = parse_sexpr(line, len, &i);

        printf("Expr: ");
        print_sexpr(e, 1, 0);
        printf("\n");

        result = eval(&env, e);

        print_sexpr(result, 1, 0);
        printf("\n");
      }
    }

    printf("Memory usage: (%lu/%lu bytes)\n",
           memused * sizeof(expr), MEMSIZE * sizeof(expr));
    if (memused >= 0.5 * MEMSIZE) {
      printf("Running GC\n");
      gc_prepare();
      gc(&env);
      printf("Usage after gc: %lu bytes\n", memused * sizeof(expr));
    }

  }

  deinit_mem();
  
  return 0;
}
