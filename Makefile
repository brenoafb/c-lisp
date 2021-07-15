CFLAGS = -Wall -Wextra -Werror -pedantic -ansi -O2 -I.
DEPS = utils.h parser.h syntax.h
OBJ = utils.o parser.o 

all: main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) main.c -o $@ $^ $(CFLAGS)

clean:
	rm -f ${OBJ} main

.PHONY: all clean