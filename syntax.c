#include "syntax.h"

expr *car(expr *e) {
  return e->c.cell.car;
}

expr *cdr(expr *e) {
  return e->c.cell.cdr;
}

int is_atom(expr *e, char *atom) {
  if (e->tag != ATOM) {
    return 0;
  }

  return 0 == strcmp(e->c.atom, atom);
}
