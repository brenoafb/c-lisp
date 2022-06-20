CFLAGS = -Wall -pedantic -I. -g
DEPS = utils.h bestline.h parser.h syntax.h mem.h interpreter.h env.h 
OBJ = utils.o bestline.o parser.o syntax.o mem.o interpreter.o env.o  main.o 

all: lisp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

lisp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f ${OBJ} lisp

.PHONY: all clean
