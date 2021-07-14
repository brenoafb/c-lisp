#pragma once

#define ATOM 0
#define NUM 1
#define LIST 2

typedef union contents
{
  char *atom;
  int num;
} contents;

typedef struct expr
{
  int tag;
  contents c; // used for nums and atoms
  int n;
  struct expr **exprs; // used for lists
} expr;