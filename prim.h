/* primitive procedures */
#pragma once

#include "env.h"
#include "interpreter.h"
#include "mem.h"
#include "syntax.h"

void make_default_env(env *env, frame *f);

expr *prim_plus(env *e, int n, expr *args[]);
expr *prim_minus(env *e, int n, expr *args[]);
expr *prim_eq(env *e, int n, expr *args[]);
expr *prim_car(env *e, int n, expr *args[]);
expr *prim_cdr(env *e, int n, expr *args[]);
expr *prim_cons(env *e, int n, expr *args[]);
expr *prim_print(env *e, int n, expr *args[]);
expr *prim_println(env *e, int n, expr *args[]);
expr *prim_env(env *e, int n, expr *args[]);

typedef struct prim_entry {
  char *name;
  native_func f;
} prim_entry;
