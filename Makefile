
CC = gcc
EXEC = schedulSim
CFLAGS = -Wall -ansi -pedantic -Werror -g
OBJ = main.o linkedlist.o readFile.o cylinderHead.o


$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c cylinderHead.h linkedlist.h readFile.h
	$(CC) $(CFLAGS) main.c -c

readFile.o : readFile.c cylinderHead.h linkedlist.h
	$(CC) $(CFLAGS) readFile.c -c

cylinderHead.o : cylinderHead.h
	$(CC) $(CFLAGS) cylinderHead.c -c

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) linkedlist.c -c

clean:
	rm -f $(EXEC) $(OBJ)

run : $(EXEC)
	./$(EXEC) testfile.txt

val: $(EXEC)
	valgrind --leak-check=full --track-origins=yes -s ./$(EXEC) testfile.txt
	
