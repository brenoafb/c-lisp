#include "interpreter.h"
#include "env.h"
#include <string.h>

expr *eval(env *env, expr *e) {
  if (e == NULL) {
    return NULL;
  }

  switch (e->tag) {
  case ATOM:
    return eval_atom(env, e->c.atom);
  case CONS:
    return eval_cons(env, e);
  default:
    return e;
  }
}

expr *eval_atom(env *env, char *atom) {
  return lookup(env, atom);
}

expr *eval_cons(env *env, expr *e) {
  expr *p, *arg;
  expr *args[ARG_MAX];
  int i;

  if (is_atom(car(e), "if")) {
    expr *cond, *conseq, *alt;
    cond = car(cdr(e));
    conseq = car(cdr(cdr(e)));
    alt = car(cdr(cdr(cdr(e))));
    return eval_if(env, cond, conseq, alt);
  }

  /* assuming we have a procedure */
  p = eval(env, car(e));

  arg = cdr(e);
  i = 0;
  while (!is_nil(arg)) {
    args[i++] = eval(env, car(arg));
    arg = cdr(arg);
  }

  return apply(env, p, args, i);
}

expr *eval_if(env *env, expr *cond, expr *conseq, expr *alt) {
  expr *cond_evald;

  cond_evald = eval(env, cond);
  if (is_false(cond_evald)) {
    return eval(env, alt);
  } else {
    return eval(env, conseq);
  }
}

int is_self_evaluating(expr *e) {
  switch (e->tag) {
  case NIL:
    return 1;
  case ATOM:
    return 0;
  case NUM:
    return 1;
  case CONS:
    return 0;
  default:
    return 0;
  }
}

expr *apply(env *e, expr *p, expr *args[], int n) {
  if (p->tag == NATIVE) {
    return apply_native(p->c.f, args, n);
  }

  e = NULL; /* silence warning */

  /* TODO actual procedure application*/
  return p;
}

expr *apply_native(native_func f, expr *args[], int n) {
  return f(n, args);
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
