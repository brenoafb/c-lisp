#include "env.h"

expr *lookup(env *env, char *key) {
  int i;
  frame *f;

  f = env->frame;

  while (f) {
    if ((i = find_index(f, key)) != -1) {
      return f->values[i];
    }
    f = f->next;
  }

  printf("Error: no binding for %s\n", key);
  return NULL;
}

void insert(env *env, char *key, expr *value) {
  frame_insert(env->frame, key, value);
}

void frame_insert(frame *f, char *key, expr *value) {
  int len;
  /* TODO check whether env is full */
  if (f->count >= FRAME_SIZE) {
    printf("frame_insert: error inserting new element into frame: frame is full\n");
    return;
  }
  
  len = strlen(key);
  f->keys[f->count] = malloc(len+1);
  strcpy(f->keys[f->count], key);
  f->values[f->count] = value;
  f->count++;
  return;
}

void push_frame(env *e, frame *f) {
  frame *t;

  t = e->frame;
  e->frame = f;
  f->next = t;
}

void pop_frame(env *e) {
  int i;
  for (i = 0; i < e->frame->count; i++) {
    free(e->frame->keys[i]);
  }
  e->frame = e->frame->next;
}

int find_index(frame *f, char *key) {
  int i;
  for (i = 0; i < f->count; i++) {
    if (0 == strcmp(key, f->keys[i])) {
      return i;
    }
  }

  return -1;
}
