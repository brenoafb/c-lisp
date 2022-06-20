#include "interpreter.h"
#include "parser.h"
#include "utils.h"

expr *eval(env *env, expr *e) {
  expr *op, *e1, *e2, *result;
  int x1, x2;

  if (e == NULL) {
    return NULL;
  }

  if (is_self_evaluating(e)) {
    return e;
  }

  /* assuming we have a cons */

  op = eval(env, car(e));
  e1 = eval(env, car(cdr(e)));
  e2 = eval(env, car(cdr(cdr(e))));

  if (!(op->tag == ATOM && e1->tag == NUM && e2->tag == NUM)) {
    return NULL;
  }

  x1 = e1->c.num;
  x2 = e2->c.num;

  result = malloc(sizeof(expr));
  result->tag = NUM;

  if (is_atom(op, "+")) {
    result->c.num = x1 + x2;
  } else if (is_atom(op, "*")) {
    result->c.num = x1 * x2;
  } else if (is_atom(op, "-")) {
    result->c.num = x1 - x2;
  } else if (is_atom(op, "/")) {
    result->c.num = x1 / x2;
  } else {
    free(result);
    return NULL;
  }

  return result;
}

int is_self_evaluating(expr *e) {
  switch (e->tag) {
  case NIL:
    return 1;
  case ATOM:
    return 1;
  case NUM:
    return 1;
  case CONS:
    return 0;
  default:
    return 0;
  }
}

void traverse(expr *e) {
  if (e == NULL) {
    return;
  }
  switch (e->tag) {
  case NIL:
    printf("nil\n");
    break;
  case ATOM:
    printf("atom: %s\n", e->c.atom);
    break;
  case NUM:
    printf("num: %d\n", e->c.num);
    break;
  case CONS:
    printf("cons\n");
    traverse(e->c.cell.car);
    traverse(e->c.cell.cdr);
    break;
  default:
    break;
  }
}
