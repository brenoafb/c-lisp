# Lisp interpreter written in C

This project is a garbage-collected Lisp in ANSI C with a [bestline](https://github.com/jart/bestline)-powered REPL.

```
make
./lisp

lisp> (+ 1 2)
3
lisp> (define inc (lambda (x) (+ x 1)))
nil
lisp> (inc 1)
2
```

## Primitive Procedures

Primitive procedures are defined in `prim.h/prim.c`. As an example, here's the signature of the `+` primitive.

```
expr *prim_plus(env *e, int n, expr *args[]);
```

You can add new primitive procedures by adding a `prim_` function in `prim.h/prim.c` and add the corresponding entry in the `entries` array (`prim.c`).