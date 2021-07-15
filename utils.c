#include "utils.h"

void dealloc(expr *e) {
  if (!e) return;
  switch (e->tag) {
    case ATOM:
      free(e->c.atom);
      break;
    case CONS:
      dealloc(e->c.cell.car);
      dealloc(e->c.cell.cdr);
      break;
    default:
      break;
  }
  free(e);
}

void print_spaces(int n)
{
  while (n > 0)
  {
    printf(" ");
    n--;
  }
}

void print_sexpr(expr *e, int indent)
{
  if (!e) { return; }

  print_spaces(indent);
  switch (e->tag)
  {
  case ATOM:
    printf("%s\n", e->c.atom);
    break;
  case NUM:
    printf("%d\n", e->c.num);
    break;
  case CONS:
  default:
    printf("(\n");
    print_sexpr(e->c.cell.car, indent + 2);
    print_sexpr(e->c.cell.cdr, indent + 2);
    print_spaces(indent);
    printf(")\n");
  }
}