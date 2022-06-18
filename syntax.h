#pragma once

#include <string.h>

#define NIL  0
#define ATOM 1
#define NUM  2
#define CONS 3

struct expr;

struct cons {
  struct expr *car;
  struct expr *cdr;
};

typedef struct cons cons;

union contents
{
  char *atom;
  int num;
  cons cell;
};

typedef union contents contents;

struct expr
{
  int tag;
  contents c;
};

typedef struct expr expr;

expr *car(expr *e);
expr *cdr(expr *e);
int is_atom(expr *e, char *atom);
