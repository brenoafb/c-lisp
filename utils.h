#pragma once

#include "syntax.h"
#include <stdio.h>
#include <stdlib.h>

void dealloc(expr *e);

void print_spaces(int n);

void print_sexpr(expr *e, int print_inline, int indent);
