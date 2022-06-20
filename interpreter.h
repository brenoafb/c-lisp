#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "syntax.h"
#include "parser.h"
#include "utils.h"

expr *eval(env *env, expr *e);
expr *eval_atom(env *env, char *atom);
expr *eval_cons(env *env, expr *e);
expr *eval_if(env *env, expr *cond, expr *conseq, expr *alt);
expr *eval_lambda(env *env, expr *arglist, expr *body);

expr *apply(env *e, expr *p, expr *args[], int n);
expr *apply_native(native_func f, expr *args[], int n);
expr *apply_procedure(env *e, proc p, expr *args[], int n);

int is_self_evaluating(expr *e);

void traverse(expr *e);
