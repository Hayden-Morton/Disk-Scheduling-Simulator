
CC = gcc
EXEC = schedulSim
CFLAGS = -Wall -ansi -pedantic -Werror -g
OBJ = main.o linkedlist.o readFile.o buffer1.o

ifdef DEBUG
CFLAGS += -D DEBUG
DEBUG : clean $(EXEC)
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c buffer1.h linkedlist.h readFile.h
	$(CC) $(CFLAGS) main.c -c

readFile.o : readFile.c buffer1.h linkedlist.h
	$(CC) $(CFLAGS) readFile.c -c

buffer1.o : buffer1.h linkedlist.h
	$(CC) $(CFLAGS) buffer1.c -c

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) linkedlist.c -c

clean:
	rm -f $(EXEC) $(OBJ)

run : $(EXEC)
	./$(EXEC) testfile.txt 

val: $(EXEC)
	valgrind --leak-check=full --track-origins=yes -s ./$(EXEC) testfile.txt
	
