#include "prim.h"

prim_entry entries[] = {
  {"+", &prim_plus},
  {"-", &prim_minus},
  {"eq", &prim_eq},
  {"car", &prim_car},
  {"cdr", &prim_cdr},
  {"cons", &prim_cons},
  {NULL, NULL}
};

void make_default_env(env *env, frame *f) {
  env->frame = f;
  int i = 0;
  prim_entry entry = entries[i++];
  while (entry.name) {
    expr *f;
    f = alloc();
    f->tag = NATIVE;
    f->c.f = entry.f;
    insert(env, entry.name, f);
    entry = entries[i++];
  }
}

expr *prim_plus(int n, expr *args[]) {
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

expr *prim_minus(int n, expr *args[]) {
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

expr *prim_eq(int n, expr *args[]) {
  int i;
  expr *result;

  if (n < 2) {
    printf("Wrong number of arguments for eq\n");
    return NULL;
  }


  for (i = 1; i < n; i++) {
    if (!eq(args[0], args[i])) {
      return nil();
    }
  }

  result = alloc();
  result->tag = ATOM;
  result->c.atom = "#t";
  return result;
}

expr *prim_car(int n, expr *args[]) {
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

expr *prim_cdr(int n, expr *args[]) {
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

expr *prim_cons(int n, expr *args[]) {
  if (n != 2) {
    printf("Error: wrong number of arguments for primitive cons\n");
    return NULL;
  }

  expr *result = alloc();
  result->tag = CONS;
  result->c.cell.car = args[0];
  result->c.cell.cdr = args[1];

  return result;
}
