
CC = gcc
EXEC = schedulSim
CFLAGS = -Wall -ansi -pedantic -Werror -g
OBJ = main.o

ifdef DEBUG
CFLAGS += -D DEBUG
DEBUG : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o:	main.c cylinderHead.h
	$(CC) $(CFLAGS) main.c -c


clean:
	rm -f $(EXEC) $(OBJ)

run:
	./$(EXEC) testfile.txt
