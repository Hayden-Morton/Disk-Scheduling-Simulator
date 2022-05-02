
SRC_DIR = src
BUILD_DIR = build
DEST_DIR = dest


CC = gcc
EXEC = scheduler
CFLAGS = -Wall -ansi -pedantic -Werror -g
THREADFLAGS = -pthread

EXECTOTAL = $(DEST_DIR)/$(EXEC)

SRCS = $(shell find $(SRC_DIR) -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

$(EXECTOTAL) : $(OBJS)
	$(CC) $(THREADFLAGS) $(OBJS) -o $(EXECTOTAL)

$(BUILD_DIR)/%.c.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm $(EXECTOTAL)
	rm -r $(BUILD_DIR)

run : $(EXECTOTAL)
	./$(EXECTOTAL)

test : $(EXECTOTAL)
	./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt

val : $(EXECTOTAL)
	valgrind --leak-check=full --track-origins=yes -s ./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt > /dev/null

stress : $(EXECTOTAL)
	./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt
	./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt
	./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt
	./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt
	./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt
	./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt
	./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt
	./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt
	./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt
	./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt
	./$(EXECTOTAL) < $(DEST_DIR)/userOuterInput.txt
