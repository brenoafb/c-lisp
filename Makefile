CFLAGS = -Wall -pedantic -ansi -I. -g
DEPS = utils.h parser.h syntax.h interpreter.h env.h
OBJ = utils.o parser.o syntax.o interpreter.o env.o main.o

all: main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f ${OBJ} main

.PHONY: all clean
