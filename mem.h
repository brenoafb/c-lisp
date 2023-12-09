#pragma once

#include "env.h"
#include "syntax.h"
#include <stdio.h>

#define MEMSIZE 4096

extern expr *mem;
extern int *used;
extern int memused;
extern int *found;

/* init_mem initializes the interpreter's memory */
void init_mem();

/* deinit_mem frees the interpreter's memory */
void deinit_mem();

/* alloc allocates a new expr in the heap */
expr *alloc();

/* gc performs garbage collection */
void gc(env *e);

/* gc_prepare initializes the garbage collector's state */
void gc_prepare();

/* gc_traverse traverses the heap, marking all reachable exprs */
void gc_traverse(int found[], expr *e);

/* print_heap prints a heap visualization to stdout */
void print_heap();

/* free_expr frees an expr */
void free_expr(int i);
