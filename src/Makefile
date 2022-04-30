
CC = gcc
EXEC = simulator
CFLAGS = -Wall -ansi -pedantic -Werror -g
OBJ = simulator.o linkedlist.o readFile.o buffer1.o algorithms.o

ifdef DEBUG
CFLAGS += -D DEBUG
DEBUG : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

simulator.o : simulator.c buffer1.h linkedlist.h readFile.h algorithms.h assumptions.h
	$(CC) $(CFLAGS) simulator.c -c

readFile.o : readFile.c buffer1.h linkedlist.h
	$(CC) $(CFLAGS) readFile.c -c

buffer1.o : buffer1.h linkedlist.h
	$(CC) $(CFLAGS) buffer1.c -c

algorithms.o : algorithms.h buffer1.h linkedlist.h
	$(CC) $(CFLAGS) algorithms.c -c

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) linkedlist.c -c

clean:
	rm -f $(EXEC) $(OBJ)

run : $(EXEC)
	./$(EXEC)

test : $(EXEC)
	./$(EXEC) < userInput.txt

val: $(EXEC)
	valgrind --leak-check=full --track-origins=yes -s ./$(EXEC) < userInput.txt > /dev/null
	
