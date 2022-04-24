
SRC_DIR = src
BUILD_DIR = build
DEST_DIR = dest


CC = gcc
EXEC = simulator
CFLAGS = -Wall -ansi -pedantic -Werror -g

EXECTOTAL = $(DEST_DIR)/$(EXEC)

SRCS = $(shell find $(SRC_DIR) -name '*.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $(EXECTOTAL)

$(BUILD_DIR)/%.c.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm $(EXECTOTAL)
	rm -r $(BUILD_DIR)

run : $(BUILD_DIR)/$(EXEC)
	./$(EXECTOTAL)

test : $(BUILD_DIR)/$(EXEC)
	./$(EXECTOTAL) < $(DEST_DIR)/userInput.txt

val : $(BUILD_DIR)/$(EXEC)
	valgrind --leak-check=full --track-origins=yes -s ./$(EXECTOTAL) < $(DEST_DIR)/userInput.txt
