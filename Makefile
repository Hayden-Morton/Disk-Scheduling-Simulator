
CC = gcc
EXEC = schedulSim
CFLAGS = -Wall -ansi -pedantic -Werror -g
OBJ = main.o linkedlist.o

ifdef DEBUG
CFLAGS += -D DEBUG
DEBUG : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o:	main.c cylinderHead.h linkedlist.h
	$(CC) $(CFLAGS) main.c -c

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) linkedlist.c -c

clean:
	rm -f $(EXEC) $(OBJ)

run : $(EXEC)
	./$(EXEC) testfile.txt

val : $(EXEC)
	valgrind --leak-check=full --track-origins=yes -s ./$(EXEC) testfile.txt
