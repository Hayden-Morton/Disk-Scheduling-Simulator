SRC_DIR = src
BUILD_DIR = build
DEST_DIR = dest

EXECS = scheduler simulator
EXECTOTALS := $(EXECS:%=$(DEST_DIR)/%)
CC = gcc
CFLAGS = -Wall -ansi -pedantic -Werror -g
THREADFLAGS = -pthread

SRCS = $(shell find $(SRC_DIR) -name '*.c' -not -name 'scheduler.c' -not -name 'simulator.c')

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

STRESSLOOPS = 100

all : $(EXECTOTALS)

$(DEST_DIR)/simulator : $(BUILD_DIR)/$(SRC_DIR)/simulator.c.o $(OBJS)
	$(CC) $(THREADFLAGS) $(OBJS) $< -o $@

$(DEST_DIR)/scheduler : $(BUILD_DIR)/$(SRC_DIR)/scheduler.c.o $(OBJS)
	$(CC) $(THREADFLAGS) $(OBJS) $< -o $@

$(BUILD_DIR)/%.c.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm $(EXECTOTALS)
	rm -r $(BUILD_DIR)

test : $(EXECTOTALS)
	./$(DEST_DIR)/simulator < $(DEST_DIR)/userOuterInput.txt
	./$(DEST_DIR)/scheduler < $(DEST_DIR)/userOuterInput.txt
	
val : $(EXECTOTALS)
	valgrind --leak-check=full --track-origins=yes -s ./$(DEST_DIR)/simulator < $(DEST_DIR)/userOuterInput.txt > /dev/null
	valgrind --leak-check=full --track-origins=yes -s ./$(DEST_DIR)/scheduler < $(DEST_DIR)/userOuterInput.txt > /dev/null

stress : $(EXECTOTALS)
	$(MAKE) test
	$(MAKE) test
	$(MAKE) test
	$(MAKE) test
	$(MAKE) test
	$(MAKE) test
	$(MAKE) test
	$(MAKE) test
	$(MAKE) test
	$(MAKE) test

