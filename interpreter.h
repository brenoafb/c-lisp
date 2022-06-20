#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "syntax.h"

expr *eval(env *env, expr *e);
void traverse(expr *e);
int is_self_evaluating(expr *e);
