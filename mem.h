#pragma once

#include <stdio.h>
#include "env.h"
#include "syntax.h"

#define MEMSIZE 64

expr mem[MEMSIZE];
int used[MEMSIZE];
int memused;

void init_mem();
expr *alloc();
void gc(env *e);
void gc_traverse(int found[], expr *e);
void print_heap();
