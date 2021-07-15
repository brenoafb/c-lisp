#pragma once

#define ATOM 0
#define NUM 1
#define CONS 2

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