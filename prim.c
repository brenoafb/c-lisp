#include "prim.h"

prim_entry entries[] = {{"+", &prim_plus},      {"-", &prim_minus},
                        {"eq", &prim_eq},       {"car", &prim_car},
                        {"cdr", &prim_cdr},     {"cons", &prim_cons},
                        {"print", &prim_print}, {"println", &prim_println},
                        {"env", &prim_env},     {NULL, NULL}};

void make_default_env(env *env, frame *f) {
  int i;
  expr *fe;
  prim_entry entry;

  env->frame = f;

  i = 0;
  entry = entries[i++];
  while (entry.name) {
    fe = alloc();
    fe->tag = NATIVE;
    fe->c.f = entry.f;
    insert(env, entry.name, fe);
    entry = entries[i++];
  }
}

expr *prim_plus(env *e, int n, expr *args[]) {
  int i;
  expr *result;

  if (n < 2) {
    printf("Wrong number of arguments for +\n");
    return NULL;
  }

  result = alloc();
  result->tag = NUM;
  result->c.num = 0;

  for (i = 0; i < n; i++) {
    if (args[i]->tag != NUM) {
      printf("Wrong type of argument for +\n");
      return NULL;
    }
    result->c.num += args[i]->c.num;
  }

  return result;
}

expr *prim_minus(env *e, int n, expr *args[]) {
  int i;
  expr *result;

  if (n < 2) {
    printf("Wrong number of arguments for -\n");
    return NULL;
  }

  result = alloc();
  result->tag = NUM;
  result->c.num = 0;

  for (i = 0; i < n; i++) {
    if (args[i]->tag != NUM) {
      printf("Wrong type of argument for -\n");
      return NULL;
    }
    result->c.num += i == 0 ? args[i]->c.num : -args[i]->c.num;
  }

  return result;
}

expr *prim_eq(env *e, int n, expr *args[]) {
  int i;

  if (n < 2) {
    printf("Wrong number of arguments for eq\n");
    return NULL;
  }

  for (i = 1; i < n; i++) {
    if (!eq(args[0], args[i])) {
      return nil();
    }
  }

  return t();
}

expr *prim_car(env *e, int n, expr *args[]) {
  if (n != 1) {
    printf("Error: wrong number of arguments for primitive car\n");
    return NULL;
  }

  if (args[0]->tag != CONS) {
    printf("Wrong type of argument for car\n");
    return NULL;
  }

  return args[0]->c.cell.car;
}

expr *prim_cdr(env *e, int n, expr *args[]) {
  if (n != 1) {
    printf("Error: wrong number of arguments for primitive cdr\n");
    return NULL;
  }

  if (args[0]->tag != CONS) {
    printf("Wrong type of argument for cdr\n");
    return NULL;
  }

  return args[0]->c.cell.cdr;
}

expr *prim_cons(env *e, int n, expr *args[]) {
  expr *result;

  if (n != 2) {
    printf("Error: wrong number of arguments for primitive cons\n");
    return NULL;
  }

  result = alloc();
  result->tag = CONS;
  result->c.cell.car = args[0];
  result->c.cell.cdr = args[1];

  return result;
}

expr *prim_env(env *e, int n, expr *args[]) {
  frame *f;
  expr *result;
  expr *curr;
  int i;

  if (n != 0) {
    printf("Error: wrong number of arguments for primitive env\n");
    return NULL;
  }

  result = alloc();
  result->tag = CONS;
  curr = result;

  f = e->frame;
  while (f) {
    for (i = 0; i < f->count; i++) {
      curr->c.cell.car = str(f->keys[i]);
      if (i == f->count - 1 && f->next == NULL) {
        curr->c.cell.cdr = nil();
        return result;
      }
      curr->c.cell.cdr = alloc();
      curr->c.cell.cdr->tag = CONS;
      curr = curr->c.cell.cdr;
    }
    f = f->next;
  }

  /* should never reach here */
  printf("Error: primitive env failed\n");
  return nil();
}

void print_expr(expr *e) {
  switch (e->tag) {
  case NIL:
    printf("nil");
    break;
  case ATOM:
  case STR:
    printf("%s", e->c.str);
    break;
  case NUM:
    printf("%d", e->c.num);
    break;
  case CONS:
    printf("<cons>");
    break;
  case NATIVE:
    printf("<prim>");
    break;
  case PROC:
    printf("<proc>");
    break;
  default:
    break;
  }
}

expr *prim_print(env *e, int n, expr *args[]) {
  int i;
  for (i = 0; i < n; i++) {
    print_expr(args[i]);
  }

  return nil();
}

expr *prim_println(env *e, int n, expr *args[]) {
  expr *r;
  r = prim_print(e, n, args);
  printf("\n");
  return r;
}
