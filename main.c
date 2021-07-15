#include "syntax.h"
#include "parser.h"

int main(void)
{
  char *s = "(+ 1 22 3213)";
  int len = strlen(s);
  int i = 0;
  printf("parsing sexpr\n");
  expr *e = parse_sexpr(s, len, &i);
  if (e == NULL)
  {
    printf("error\n");
  }
  else
  {
    print_sexpr(e, 0);
  }
}
