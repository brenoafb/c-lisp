#pragma once

#include "syntax.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

expr *lookup(env *env, char *key);
void insert(env *env, char *key, expr *value);
void frame_insert(frame *f, char *key, expr *value);
void push_frame(env *e, frame *f);
void pop_frame(env *e);

int find_index(frame *f, char *key);

void make_default_env(env *env, frame *f);

expr *func_plus(int n, expr *args[]);
expr *func_eq(int n, expr *args[]);
