CFLAGS = -Wall -Wextra -Werror -pedantic -ansi -O2 -I. -g
DEPS = utils.h parser.h syntax.h interpreter.h env.h
OBJ = utils.o parser.o syntax.o interpreter.o env.o

all: main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) main.c -o $@ $^ $(CFLAGS)

clean:
	rm -f ${OBJ} main

.PHONY: all clean
