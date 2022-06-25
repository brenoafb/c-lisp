#include "parser.h"

void skip_spaces(char *s, int len, int *i)
{
  while (*i < len && isspace(s[*i]))
  {
    *i += 1;
  }
}

int is_atom_start_char(char c) {
  return (isalpha(c)
    || c == '_'
    || c == '-'
    || c == '+'
    || c == '.'
    || c == '*'
    || c == '/'
    || c == '='
    || c == '<'
    || c == '>'
    || c == '#'
    || c == '!'
    || c == '?'
  );
}

int is_atom_char(char c) {
  return (isalnum(c)
    || c == '_'
    || c == '-'
    || c == '+'
    || c == '.'
    || c == '*'
    || c == '/'
    || c == '='
    || c == '<'
    || c == '>'
    || c == '#'
    || c == '!'
    || c == '?'
  );
}

expr *parse_sexpr(char *s, int len, int *i)
{
  skip_spaces(s, len, i);

  /* printf("parse_sexpr (%d)\n", *i); */
  /* print_state(s, len, i); */

  if (*i >= len)
    return NULL;

  switch (s[*i])
  {
  case ')':
    printf("parse error: unexpected end of list\n");
    return NULL;
  case '(':
    *i += 1; /* skip '(' */
    return parse_cons(s, len, i);
  default:
    if (is_atom_start_char(s[*i]))
    {
      return parse_atom(s, len, i);
    }
    if (isdigit(s[*i]))
    {
      return parse_num(s, len, i);
    }
    else
    {
      /* error: invalid character */
      return NULL;
    }
  }
}

expr *parse_atom(char *s, int len, int *i)
{
  char buffer[BUFSIZE];
  expr *e;
  int j = 0;

  /* printf("parse_atom (%d)\n", *i); */
  /* print_state(s, len, i); */

  if (*i >= len) {
    return NULL;
  }
  e = alloc();

  if (e == NULL) {
    printf("parse_atom: Alloc error while parsing expression\n");
    return NULL;
  }

  e->tag = ATOM;

  while (*i < len && is_atom_char(s[*i]))
  {
    buffer[j++] = s[*i];
    *i += 1;
  }
  e->c.atom = malloc(j + 1);
  e->c.atom[j] = '\0';
  memcpy(e->c.atom, buffer, j);
  return e;
}

expr *parse_num(char *s, int len, int *i)
{
  expr *e;
  int k = 0;

  /* printf("parse_num (%d)\n", *i); */
  /* print_state(s, len, i); */

  if (*i >= len) {
    return NULL;
  }

  while (*i < len && !isspace(s[*i]) && s[*i] != ')')
  {
    if (!isdigit(s[*i]))
    {
      /* error: found non number character */
      return NULL;
    }
    k = k * 10 + (s[*i] - '0');
    *i += 1;
  }
  e = alloc();

  if (e == NULL) {
    printf("parse_num: Alloc error while parsing expression\n");
    return NULL;
  }

  e->tag = NUM;
  e->c.num = k;
  return e;
}

expr *parse_cons(char *s, int len, int *i) {
  expr *curr, *e, *car, *cdr;

  /* printf("parse_cons (%d)\n", *i); */
  /* print_state(s, len, i); */

  if (s[*i] == ')') {
    e = alloc();
    if (e == NULL) {
      printf("parse_cons: Alloc error while parsing expression\n");
      return NULL;
    }
    e->tag = NIL;
    *i += 1;
    return e;
  }

  car = parse_sexpr(s, len, i);

  if (car == NULL) {
    printf("parse_cons: error parsing car\n");
    return NULL;
  }
  
  cdr = parse_cons(s, len, i);

  if (cdr == NULL) {
    printf("parse_cons: error parsing cdr\n");
    return NULL;
  }

  curr = alloc();
  if (e == NULL) {
    printf("parse_cons: Alloc error while parsing expression\n");
    return NULL;
  }
  curr->tag = CONS;
  curr->c.cell.car = car;
  curr->c.cell.cdr = cdr;

  return curr;
}

void print_state(char *s, int len, int *i) {
  int j = *i;
  printf("%s\n", s);
  while (j-- > 0) {
    printf(" ");
  }
  printf("^");
  printf("\n");
}
