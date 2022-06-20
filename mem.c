#include "mem.h"

void init_mem() {
  memused = 0;
  for (int i = 0; i < MEMSIZE; i++) {
    used[i] = 0;
  }
}

expr *alloc() {
  expr *ptr;
  printf("allocating expr\n");
  // find first unused space
  int i = 0;
  for (; i < MEMSIZE; i++) {
    if (!used[i]) {
      printf("found free slot at index %d\n", i);
      ptr = &mem[i];
      used[i] = 1;
      memused += 1;
      printf("memory used: %lu/%lu bytes\n", sizeof(expr) * memused, sizeof(expr) * MEMSIZE);
      print_heap();
      return ptr;
    }
  }
  /* TODO handle case where we have no free space */
  return NULL;
}

void gc(env *e) {
  frame *f = e->frame;
  int found[MEMSIZE];

  for (int i = 0; i < MEMSIZE; i++) {
    found[i] = 0;
  }

  while (f) {
    for (int i = 0; i < f->count; i++) {
      gc_traverse(found, f->values[i]);
    }
    f = f->next;
  }

  for (int i = 0; i < MEMSIZE; i++) {
    if (used[i] && !found[i]) {
      // TODO dealloc string if atom
      memused--;
      used[i] = 0;
    }
  }
  
  return;
}

void gc_traverse(int found[], expr *e) {
  int mi = (e - mem) / sizeof(expr);
  found[mi] = 1;
  if (found[mi]) {
    // already visited this node
    return;
  }
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
