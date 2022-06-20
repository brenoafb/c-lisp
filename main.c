#include "syntax.h"
#include "parser.h"
#include "interpreter.h"
#include "utils.h"

int main(void)
{
  expr *e, *result;
  char *s = "(+ 1 (+ 2 3))";
  int len = strlen(s);
  int i = 0;

  e = parse_sexpr(s, len, &i);
  if (e == NULL)
  {
    printf("error\n");
  }
  else
  {
    print_sexpr(e, 0);
    traverse(e);
    result = eval(NULL, e);
    printf("Result:\n");
    print_sexpr(result, 0);
  }

  dealloc(e);

  return 0;
}
