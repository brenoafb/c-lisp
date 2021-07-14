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

expr *parse_atom(char *s, int len, int *i)
{
  if (*i >= len) {
    return NULL;
  }
  char buffer[BUFSIZE];
  int j = 0;
  expr *e = malloc(sizeof(expr));
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
  if (*i >= len) {
    return NULL;
  }
  int k = 0;
  while (*i < len && !isspace(s[*i]) && s[*i] != ')')
  {
    if (!isdigit(s[*i]))
    {
      // error: found non number character
      return NULL;
    }
    k = k * 10 + (s[*i] - '0');
    *i += 1;
  }
  expr *e = malloc(sizeof(expr));
  e->tag = NUM;
  e->c.num = k;
  return e;
}

expr *parse_list(char *s, int len, int *i) {
  int counter = 0;
  expr *curr;
  expr *exprs[MAX_EXPRS];

  *i += 1; // skip '('
  while (s[*i] != ')')
  {
    exprs[counter++] = parse_sexpr(s, len, i);
  }
  *i += 1; // skip ')'
  curr = malloc(sizeof(expr));
  curr->tag = LIST;
  curr->exprs = malloc(sizeof(expr *) * counter);
  curr->n = counter;
  memcpy(curr->exprs, exprs, sizeof(expr *) * counter);
  return curr;
}

expr *parse_sexpr(char *s, int len, int *i)
{
  skip_spaces(s, len, i);

  if (*i >= len)
    return NULL;

  switch (s[*i])
  {
  case ')':
    // error: unexpected end of list
    return NULL;
  case '(':
    return parse_list(s, len, i);
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
      // error
      return NULL;
    }
  }
}

void print_spaces(int n)
{
  while (n > 0)
  {
    printf(" ");
    n--;
  }
}

void print_sexpr(expr *e, int indent)
{
  print_spaces(indent);
  switch (e->tag)
  {
  case ATOM:
    printf("%s\n", e->c.atom);
    break;
  case NUM:
    printf("%d\n", e->c.num);
    break;
  case LIST:
    printf("(\n");
    for (int i = 0; i < e->n; i++)
    {
      print_sexpr(e->exprs[i], indent + 2);
    }
    print_spaces(indent);
    printf(")\n");
  }
}