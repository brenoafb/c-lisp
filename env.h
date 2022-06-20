#pragma once

#include <stdlib.h>
#include <string.h>
#include "syntax.h"

#define ENV_SIZE 1024

typedef struct env {
  int count;
  char *keys[ENV_SIZE];
  expr *values[ENV_SIZE];
} env;

expr *lookup(env *env, char *key);
void insert(env *env, char *key, expr *value);
void del(env *env, char *key);

int find_index(env *env, char *key);

/* TODO write a function to dealloc the env keys */
