#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "syntax.h"

expr *eval(expr *e);
void traverse(expr *e);
int is_self_evaluating(expr *e);
