#pragma once

#include <stdlib.h>
#include <string.h>
#include "syntax.h"

#define FRAME_SIZE 1024

typedef struct frame {
  int count;
  char *keys[FRAME_SIZE];
  expr *values[FRAME_SIZE];
  struct frame *next;
} frame;

typedef struct env {
  frame *frame;
} env;

expr *lookup(env *env, char *key);
void insert(env *env, char *key, expr *value);
void frame_insert(frame *f, char *key, expr *value);
void push_frame(env *e, frame *f);
void pop_frame(env *e);

int find_index(frame *f, char *key);

void make_default_env(env *env, frame *f);

expr *func_plus(int n, expr *args[]);
expr *func_eq(int n, expr *args[]);


/* primitives */
