#include "syntax.h"
#include "parser.h"
#include "utils.h"

int main(void)
{
  expr *e;
  char *s = "(+ 1 22 3213)";
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
  }

  dealloc(e);

  return 0;
}
