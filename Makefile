
SRC_DIR = src
BUILD_DIR = build
DEST_DIR = dest


CC = gcc
EXEC = simulator
CFLAGS = -Wall -ansi -pedantic -Werror -g

SRCS = $(shell find $(SRC_DIR) -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $(DEST_DIR)/$(EXEC)

$(BUILD_DIR)/%.c.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
	rm $(DEST_DIR)/$(EXEC)

run:
	./$(DEST_DIR)/$(EXEC)

test:
	./$(DEST_DIR)/$(EXEC) < $(DEST_DIR)/userInput.txt

val:
	valgrind --leak-check=full --track-origins=yes -s ./$(DEST_DIR)/$(EXEC) < $(DEST_DIR)/userInput.txt
