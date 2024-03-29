CC = clang
CFLAGS = -Wall -pedantic -I. -g -std=c89
DEPS = utils.h bestline.h parser.h syntax.h mem.h interpreter.h prim.h env.h
OBJ = utils.o bestline.o parser.o syntax.o mem.o interpreter.o prim.o env.o  main.o

all: lisp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lisp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f ${OBJ} lisp

format:
	clang-format -i *.c *.h

.PHONY: all clean format
