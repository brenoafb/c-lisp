#pragma once

#include <stdio.h>
#include "env.h"
#include "syntax.h"

#define MEMSIZE 4096

extern expr *mem;
extern int *used;
extern int memused;
extern int *found;

void init_mem();
void deinit_mem();
expr *alloc();
void gc(env *e);
void gc_prepare();
void gc_traverse(int found[], expr *e);
void print_heap();
void free_expr(int i);
