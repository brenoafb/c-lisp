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

  while ((line = bestline("lisp> ")) != NULL) {
    if (line[0] != '\0') {
      /* bestlineHistoryAdd(line); /\* Add to the history. *\/ */
      /* bestlineHistorySave("history.txt"); /\* Save the history on disk. *\/
       */
      int len = strlen(line);
      int i = 0;
      while (i < len) {
        e = parse_sexpr(line, len, &i);

        printf("Expr: ");
        print_sexpr(e, 1, 0);
        printf("\n");

        /* traverse(e[j]); */
        result = eval(&env, e);

        print_sexpr(result, 1, 0);
        printf("\n");
      }
    }
    free(line);

    if (memused >= 0.8 * MEMSIZE) {
      printf("Memory almost full (%lu/%lu bytes); running gc\n",
             memused * sizeof(expr), MEMSIZE * sizeof(expr));
      gc(&env);
      printf("Usage after gc: %lu\n", memused * sizeof(expr));
    }
  }

  return 0;
}
