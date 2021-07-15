#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "syntax.h"

void dealloc(expr *e);

void print_spaces(int n);

void print_sexpr(expr *e, int indent);