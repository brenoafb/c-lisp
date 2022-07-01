#include "syntax.h"

expr *car(expr *e) {
  return e->c.cell.car;
}

expr *cdr(expr *e) {
  return e->c.cell.cdr;
}

int is_atom(expr *e, char *atom) {
  return e->tag == ATOM && 0 == strcmp(e->c.str, atom);
}

int is_num(expr *e, int n) {
  return e->tag == NUM && e->c.num == n;
}

int is_true(expr *e) {
  return is_atom(e, "#t");
}

int is_false(expr *e) {
  return is_nil(e);
}

int is_nil(expr *e) {
  return e->tag == NIL;
}

int eq(expr *x, expr *y) {
  if (x == y) {
    return 1;
  }

  if (x->tag != y->tag) {
    return 0;
  }

  switch (x->tag) {
  case NIL:
    return is_nil(y);
  case ATOM:
    return is_atom(y, x->c.str);
  case NUM:
    return is_num(y, x->c.num);
  default:
    return 0;
  }
}
