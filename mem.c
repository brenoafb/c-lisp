#include "mem.h"

expr *mem = NULL;
int *used = NULL;
int memused = 0;
int *found = NULL;

void init_mem() {
  mem = malloc(sizeof(expr) * MEMSIZE);
  used = malloc(sizeof(int) * MEMSIZE);
  found = malloc(sizeof(int) * MEMSIZE);
  memused = 0;
  for (int i = 0; i < MEMSIZE; i++) {
    used[i] = 0;
  }
}

void deinit_mem() {
  free(mem);
  free(used);
}

expr *alloc() {
  expr *ptr;
  // printf("allocating expr\n");
  // find first unused space
  int i = 0;
  for (; i < MEMSIZE; i++) {
    if (!used[i]) {
      // printf("found free slot at index %d\n", i);
      ptr = &mem[i];
      used[i] = 1;
      memused += 1;
      // printf("memory used: %lu/%lu bytes\n", sizeof(expr) * memused, sizeof(expr) * MEMSIZE);
      // print_heap();
      return ptr;
    }
  }
  /* TODO handle case where we have no free space */
  printf("No available memory left\n");
  return NULL;
}

void gc_prepare() {
  for (int i = 0; i < MEMSIZE; i++) {
    found[i] = 0;
  }
}

void gc(env *e) {
  frame *f = e->frame;

  while (f) {
    for (int i = 0; i < f->count; i++) {
      /* printf("gc traversing %s\n", f->keys[i]); */
      gc_traverse(found, f->values[i]);
    }
    f = f->next;
  }

  for (int i = 0; i < MEMSIZE; i++) {
    if (used[i] && !found[i]) {
      free_expr(i);
    }
  }

  return;
}

void gc_traverse(int found[], expr *e) {
  unsigned long mi = ((unsigned long) e - (unsigned long) mem) / sizeof(expr);
  /* printf("sizeof(expr): %lu\n", sizeof(expr)); */
  /* printf("mem: 0x%x, e: 0x%x, mi: %lu\n", mem, e, mi); */
  if (found[mi]) {
    // already visited this node
    return;
  }
  /* printf("marking %lu as found\n", mi); */
  found[mi] = 1;
  switch (e->tag) {
  case CONS:
    gc_traverse(found, car(e));
    gc_traverse(found, cdr(e));
    break;
  case PROC:
    gc_traverse(found, e->c.proc.body);
    gc(e->c.proc.env);
    break;
  case NIL:
  case ATOM:
  case NUM:
  case NATIVE:
  default:
    break;
  }
}

void print_heap() {
  int rowlen = 64;
  for (int i = 1; i <= MEMSIZE; i++) {
    if (i % rowlen == 1) {
      printf("[");
    }
    if (used[i-1]) {
      printf("X");
    } else {
      printf(" ");
    }
    if (i && i % rowlen == 0) {
      printf("]\n");
    }
  }
}

void free_expr(int i) {
  switch (mem[i].tag) {
    case ATOM:
    case STR:
      free(mem[i].c.str);
      break;
    case PROC:
      free(mem[i].c.proc.env);
      for (int i = 0; i < mem[i].c.proc.n; i++) {
        free(mem[i].c.proc.args[i]);
      }
      break;
    default:
      break;
  }
  memused--;
  used[i] = 0;
}
