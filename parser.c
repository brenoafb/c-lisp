#include "parser.h"

void skip_spaces(char *s, int len, int *i)
{
  while (*i < len && s[*i] == ' ')
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
  );
}

expr *parse_sexpr(char *s, int len, int *i)
{
  skip_spaces(s, len, i);

  if (*i >= len)
    return NULL;

  switch (s[*i])
  {
  case ')':
    /* error: unexpected end of list */
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

  if (*i >= len) {
    return NULL;
  }
  e = malloc(sizeof(expr));
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
  e = malloc(sizeof(expr));
  e->tag = NUM;
  e->c.num = k;
  return e;
}

expr *parse_cons(char *s, int len, int *i) {
  expr *curr;

  if (s[*i] == ')') { return NULL; }

  curr = malloc(sizeof(expr));
  curr->tag = CONS;

  /* parse first expr */
  curr->c.cell.car = parse_sexpr(s, len, i);
  curr->c.cell.cdr = parse_cons(s, len, i);

  return curr;
}