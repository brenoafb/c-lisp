#pragma once

#define ATOM 0
#define NUM 1
#define LIST 2

union contents
{
  char *atom;
  int num;
};

typedef union contents contents;

struct expr
{
  int tag;
  /* used for nums and atoms */
  contents c;
  /* used for lists */
  int n;
  struct expr **exprs;
};

typedef struct expr expr;