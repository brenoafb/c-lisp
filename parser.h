#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem.h"
#include "syntax.h"

#define BUFSIZE 256
#define MAX_EXPRS 256

int is_atom_start_char(char c);

int is_atom_char(char c);

void skip_spaces(char *s, int len, int *i);

expr *parse_atom(char *s, int len, int *i);

expr *parse_num(char *s, int len, int *i);

expr *parse_str(char *s, int len, int *i);

expr *parse_cons(char *s, int len, int *i);

expr *parse_sexpr(char *s, int len, int *i);

void print_state(char *s, int len, int *i);
