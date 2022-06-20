#include "env.h"

expr *lookup(env *env, char *key) {
  int i;

  if ((i = find_index(env, key)) == -1) {
    return NULL;
  }

  return env->values[i];
}

void insert(env *env, char *key, expr *value) {
  int len;
  /* TODO check whether env is full */
  len = strlen(key);
  env->count++;
  env->keys[env->count] = malloc(len+1);
  strcpy(env->keys[env->count], key);
  env->values[env->count] = value;
  return;
}

void remove(env *env, char *key) {
  int i, j;

  if ((i = find_index(env, key)) == -1) {
    return;
  }

  free(env->keys[i]);

  for (j = i; j < env->count - 1; j++) {
    env->keys[j+1] = env->keys[j];
    env->values[j+1] = env->values[j];
  }
}

int find_index(env *env, char *key) {
  int i;
  for (i = 0; i < env->count; i++) {
    if (0 == strcmp(key, env->keys[i])) {
      return i;
    }
  }

  return -1;
}
