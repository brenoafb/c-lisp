#pragma once

#include <stdlib.h>
#include <string.h>

#define NIL 0
#define ATOM 1
#define NUM 2
#define CONS 3
#define NATIVE 4
#define PROC 5
#define STR 6

#define ARG_MAX 10

struct expr;

struct env;

struct cons {
  struct expr *car;
  struct expr *cdr;
};

typedef struct cons cons;

typedef struct expr *(*native_func)(struct env *env, int, struct expr *[]);

typedef struct proc {
  char *name; /* not used at the moment */
  int n;
  char *args[ARG_MAX];
  struct expr *body;
  void *env; /* cannot use env type due to cyclic deps */
} proc;

union contents {
  char *str;
  int num;
  cons cell;
  proc proc;
  native_func f;
};

typedef union contents contents;

typedef struct expr {
  int tag;
  contents c;
} expr;

void expr_to_string(expr *e, char *str);
expr *car(expr *e);
expr *cdr(expr *e);

int is_atom(expr *e, char *atom);
int is_num(expr *e, int n);
int is_true(expr *e);
int is_false(expr *e);
int is_nil(expr *e);
int eq(expr *x, expr *y);

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
