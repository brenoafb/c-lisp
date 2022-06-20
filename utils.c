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

void print_sexpr(expr *e, int print_inline, int indent)
{
  char *sep = print_inline ? " " : "\n";
  if (!e) { return; }

  if (!print_inline) print_spaces(indent);
  switch (e->tag)
  {
  case NIL:
    printf("nil%s", sep);
    break;
  case ATOM:
    printf("%s%s", e->c.atom, sep);
    break;
  case NUM:
    printf("%d%s", e->c.num, sep);
    break;
  case NATIVE:
    printf("<native>%s", sep);
    break;
  case PROC:
    printf("<procedure>%s", sep);
    break;
  case CONS:
  default:
    printf("(%s", sep);
    print_sexpr(e->c.cell.car, print_inline, indent + 2);
    print_sexpr(e->c.cell.cdr, print_inline, indent + 2);
    if (!print_inline) print_spaces(indent);
    printf(")%s", sep);
  }
}
