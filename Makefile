# La siguiente no es necesariamente requerida, se agrega para
# mostrar cómo funciona.

.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS) $<


# Macros

CC = gcc
CFLAGS = -g -Wall -O2
SRC = main.c Parametros.c Parametros.h
OBJ = main.o Parametros.o


# Reglas explícitas

all: $(OBJ)
	$(CC) $(CFLAGS) -o batalla $(OBJ)

clean:
	$(RM) $(OBJ) batalla

# Reglas implícitas

Parametros.o: Parametros.c Parametros.h
main.o: main.c Parametros.h
