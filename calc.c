#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

#define OP 0
#define NUM 1

typedef union uexpr {
  int num;
  char op;
} uexpr;

typedef struct expr {
  int tag;
  uexpr e;
  struct expr *e1;
  struct expr *e2;
} expr;

int parse_num(char *buffer, int len, int *i) {
  int n = 0;
  while (*i < len && buffer[*i] >= '0' && buffer[*i] <= '9') {
    n *= 10;
    n += buffer[*i] - '0';
    *i += 1;
  }

  return n;
}

void skip_space(char *buffer, int *i) {
  while (buffer[*i] == ' ') {
    *i += 1;
  }
}

expr *parse_expr(char *buffer, int len, int *i) {
  expr *curr;
  char op;
  int n;

  curr = malloc(sizeof(expr));

  while (*i < len) {
    skip_space(buffer, i);
    switch (buffer[*i]) {
    case '+':
    case '*':
    case '-':
    case '/':
      op = buffer[*i];

      *i += 1;

      skip_space(buffer, i);

      expr *e1 = parse_expr(buffer, len, i);
      expr *e2 = parse_expr(buffer, len, i);

      curr->tag = OP;
      curr->e.op = op;
      curr->e1 = e1;
      curr->e2 = e2;

      return curr;
    default:
      n = parse_num(buffer, len, i);

      curr->tag = NUM;
      curr->e.num = n;
      curr->e1 = NULL;
      curr->e2 = NULL;

      return curr;
    };
  }

  return NULL;
}

int eval(expr *e) {
  int n1;
  int n2;
  switch (e->tag) {
  case NUM:
    return e->e.num;
  case OP:
    n1 = eval(e->e1);
    n2 = eval(e->e2);
    switch (e->e.op) {
    case '+':
      return n1 + n2;
    case '*':
      return n1 * n2;
    case '-':
      return n1 - n2;
    case '/':
      return n1 / n2;
    default:
      return 0;
    };
  }
  return 0;
}

void print_spaces(int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf(" ");
  }
  return;
}

void print_expr(expr *e, int indent) {
  switch (e->tag) {
  case OP:
    print_spaces(indent);
    printf("%c\n", e->e.op);
    print_expr(e->e1, indent + 2);
    print_expr(e->e2, indent + 2);
    return;
  case NUM:
    print_spaces(indent);
    printf("%d\n", e->e.num);
    return;
  }
}

void dealloc(expr *e) {
  switch (e->tag) {
  case OP:
    dealloc(e->e1);
    dealloc(e->e2);
    free(e);
    return;
  case NUM:
    free(e);
    return;
  }
}

int main(void) {
  char buffer[SIZE];
  int len;
  int i = 0;
  expr *e;

  scanf("%[^\n]", buffer);
  len = strlen(buffer);

  i = 0;
  e = parse_expr(buffer, len, &i);

  print_expr(e, 0);

  printf("%d\n", eval(e));

  dealloc(e);

  return 0;
}
