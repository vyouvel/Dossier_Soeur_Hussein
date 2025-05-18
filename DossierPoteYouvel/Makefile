CC = gcc
CFLAGS = -Wall -g

SRC = main.c Exercice1/*.c Exercice2/*.c Exercice3/*.c Exercice4/*.c Exercice5/*.c Exercice6/*.c Exercice7/*.c Exercice8/*.c
OBJ = $(SRC:.c=.o)
EXEC = cpu_prog

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(EXEC)