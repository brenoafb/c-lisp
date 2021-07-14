SRC = parser.c
OBJ = ${SRC:.c=.o}

all: lisp

$(OBJ): $(SRC)
	$(CC) -c -o $@ $(CFLAGS) $^
	
lisp: ${OBJ} main.c
	${CC} -o $@ main.c ${OBJ}

clean:
	rm -f ${OBJ} lisp

.PHONY: all clean
