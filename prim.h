#pragma once

#include "env.h"
#include "interpreter.h"
#include "mem.h"
#include "syntax.h"

void make_default_env(env *env, frame *f);

expr *prim_plus(int n, expr *args[]);
expr *prim_minus(int n, expr *args[]);
expr *prim_eq(int n, expr *args[]);
expr *prim_car(int n, expr *args[]);
expr *prim_cdr(int n, expr *args[]);
expr *prim_cons(int n, expr *args[]);

typedef struct prim_entry {
  char *name;
  native_func f;
} prim_entry;
