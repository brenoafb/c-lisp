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

  if (is_atom(car(e), "lambda")) {
    expr *arglist, *body;
    arglist = car(cdr(e));
    body = car(cdr(cdr(e)));
    return eval_lambda(env, arglist, body);
  }

  if (is_atom(car(e), "quote")) {
    /* TODO */
    return eval_quote(car(cdr(e)));
  }

  if (is_atom(car(e), "define")) {
    /* TODO */
    expr *name, *expr;
    name = car(cdr(e));
    expr = car(cdr(cdr(e)));
    return eval_define(env, name, expr);
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

expr *eval_lambda(env *env, expr *arglist, expr *body) {
  int i;
  expr *proc;
  expr *arg;

  proc = alloc();

  proc->tag = PROC;

  i = 0;
  while (!is_nil(arglist)) {
    arg = car(arglist);
    if (arg->tag != ATOM) {
      printf("malformed procedure");
      return NULL;
    }
    proc->c.proc.args[i++] = arg->c.atom;
    arglist = cdr(arglist);
  }

  proc->c.proc.body = body;
  proc->c.proc.n = i;

  /* for now we just use the pointer to env as the closure */
  /* thus we have dynamic scope */
  proc->c.proc.env = env;

  return proc;
}

expr *eval_quote(expr *e) {
  return e;
}

expr *eval_define(env *env, expr *name, expr *e) {
  char *v;

  if (name->tag != ATOM) {
    printf("Malformed define\n");
    return NULL;
  }

  v = name->c.atom;
  insert(env, v, eval(env, e));

  return nil();
}

expr *apply(env *e, expr *p, expr *args[], int n) {
  switch (p->tag) {
  case NATIVE:
    return apply_native(p->c.f, args, n);
  case PROC:
    return apply_procedure(e, p->c.proc, args, n);
  default:
    return NULL;
  }
}

expr *apply_native(native_func f, expr *args[], int n) {
  return f(n, args);
}

expr *apply_procedure(env *e, proc p, expr *args[], int n) {
  int i;
  frame *nf;
  env *pe;
  expr *value, *result;

  /* TODO */
  if (n != p.n) {
    printf("Error applying procedure: argument number mismatch\n");
    return NULL;
  }

  pe = (env *) p.env;
  nf = malloc(sizeof(frame));
  nf->count = 0;

  for (i = 0; i < n; i++) {
    value = eval(e, args[i]);
    insert(pe, p.args[i], value);
  }

  push_frame(pe, nf);
  result = eval(pe, p.body);

  pop_frame(pe);
  free(nf);

  return result;
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

expr *nil() {
  expr *n = alloc();
  n->tag = NIL;
  return n;
}
